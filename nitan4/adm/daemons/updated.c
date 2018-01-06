// updated.c
// write by Doing Lu for user management
// because a user may does much association with others,
// so I must assure all the data keep consistant
// Update by Lonely.

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <room.h>

inherit F_SAVE; 

// data need save
mixed title_base;
nosave mixed max_exp = 5000000;

nosave array special_skill = ({ 
        "agile", "hatred", "power", "self", "mystery", "youth", "trick",
});

nosave array special_ultimate = ({
        "emperor", "lonely", "queen",
});
       
string query_save_file() { return DATA_DIR "pinfo"; }

void remove_title(object ob);
void set_title(object ob);
object global_find_player(string user);
void global_destruct_player(object ob, int raw);
//mixed query_max_exp() { return max_exp; }
mixed query_max_exp() { return 200000000; }

void create()
{
        seteuid(getuid());
        restore();

        if (arrayp(title_base))
                title_base = filter_array(title_base, (: arrayp($1) && sizeof($1) == 2 :));
        else
                title_base = 0;
}

#define LUBAN           "/adm/npc/luban"
#define RING_DIR        "/data/item/ring/"

// check the user's data when login
void check_user(object ob)
{
        mapping my;
        mapping skill_status;
        array sname;
        mixed combat_exp;
        int level;
        int i;
        mapping party;
        object budai;

        my = ob->query_entire_dbase();

        if (ob->query("family/generation") == 0)
                ob->delete("family");

        if (ob->query("gender") == "无性")
                ob->set("class", "eunach");

        if ((int)ob->query("combat/today/which_day") != time() / 86400)
                ob->delete("combat/today");

        if (ob->query("couple") && ! ob->query("static/marry"))
                ob->set("static/marry", 1);
        /*
        if (ob->query("family/family_name") == "丐帮" &&
            ob->query("family/beggarlvl"))
        {
                budai = new("/d/gaibang/obj/budai");
                budai->set_amount((int)ob->query("family/beggarlvl"));
                budai->move(ob);
                budai->wear();
        }
        */
        if (mapp(party = my["party"]) && stringp(party["party_name"]))
                party["party_name"] = filter_color(party["party_name"]);

        // 记录名字
        NAME_D->map_name(ob->query("name"), ob->query("id"));

        // 重新设置运行计时器
        reset_eval_cost();

        // 赋予称号
        set_title(ob);

        if (ob->query("have_meirong_dan") && !ob->query_temp("meirong_dan_used"))
        {
                ob->add_temp("apply/per",ob->query("have_meirong_dan"));
                ob->set_temp("meirong_dan_used",1);
        }

        if (undefinedp(my["eff_jing"]))  my["eff_jing"] = my["max_jing"];
        if (undefinedp(my["eff_qi"])) my["eff_qi"] = my["max_qi"];
        if (my["eff_jing"] > my["max_jing"]) my["eff_jing"] = my["max_jing"];
        if (my["eff_qi"] > my["max_qi"]) my["eff_qi"] = my["max_qi"];
        if (my["jing"] > my["eff_jing"]) my["jing"] = my["eff_jing"];
        if (my["jing"] > my["eff_jing"]) my["jing"] = my["eff_jing"];
        if (my["neili"] > my["max_neili"] * 2) my["neili"] = my["max_neili"] * 2;

        combat_exp = ob->query("combat_exp");
        if (! wizardp(ob) && count_gt(combat_exp, max_exp))
                max_exp = combat_exp;

        if (! mapp(skill_status = ob->query_skillc()))
                return;
        sname  = keys(skill_status);

        for (i = 0; i < sizeof(sname); i++)
        {
                if (ob->query("reborn") || ob->query("jieti"))
                        continue;

                level = skill_status[sname[i]];
                if( !find_object(SKILL_D(sname[i])) && !load_object(SKILL_D(sname[i])) )
                {
                        tell_object(ob, "No such skill:" + sname[i] + "\n");
                        continue;
                }

                if (SKILL_D(sname[i])->type() == "martial")
                {
                        while (level &&
                               // count_gt(count_div(big_number_pow((level -1), 3), 10), combat_exp))
                               count_gt(count_div(count_mul(count_mul((level -1), (level -1)), (level -1)), 10), combat_exp))
                               level--;

                        ob->set_skill(sname[i], level);
                }
        }

        /*
        if ((level = ob->query_skill("zuoyou-hubo", 1)) > 0)
                ob->add_temp("apply/parry", -level / 4);
        */
        SKILLS_D->add_id_into_skills(ob);
        if (ob->query("skill_mix"))
                SKILLS_D->enable_skill_mix(ob, ob->query("skill_mix"));
}

// clear the user's data
// when catalog parameter equal to "all", I will remove all
// the informatino of this user. This may be used when the
// user was purged.
varargs string clear_user_data(string user, string cat, int flag_s)
{
        object login_ob;
        object ob;
        string couple_id;
        string path, file_name;
        array dirs;
        object temp;
        string brothers;
        string bro_id;
        array ks;
        mapping bro;
        int flag;
        int i;

        // only root uid can does it
        if (previous_object() &&
            getuid(previous_object()) != ROOT_UID &&
            geteuid(previous_object()) != user)
                return "你无权清除该玩家的数据。\n";

        // find the user's body
        seteuid(getuid());
        login_ob = 0;
        ob = find_player(user);
        if (! ob)
        {
                login_ob = new(LOGIN_OB);
                login_ob->set("id", user);
                ob = LOGIN_D->make_body(login_ob);
                if (! ob)
                {
                        catch(destruct(login_ob));
                        return "暂时无法生成玩家对象。\n";
                }

                if (! ob->restore())
                {
                        catch(destruct(login_ob));
                        catch(destruct(ob));
                        return "没有这个玩家。\n";
                }

                ob->setup();
        }

        // no catalog? treat it as "all"
        if (! cat) cat = "all";
        flag = 0;

        // remove name information
        if (cat == "name" || cat == "all")
                NAME_D->remove_name(ob->query("name"), ob->query("id"));

        // remove room information
        if ((cat == "room" || cat == "all") &&
            mapp(ob->query("private_room")))
        {
                // Demolish the room of the user
                LUBAN->demolish_room(ob);
                flag++;
        }

        // remove marriage information
        if ((cat == "couple" || cat == "all") &&
            mapp(ob->query("couple")))
        {
                // clear the couple infomation

                // remove the ring
                file_name = RING_DIR + ob->query("id");
                if (file_size(file_name + ".c") > 0)
                {
                        if (temp = find_object(file_name))
                        {
                                if (environment(temp))
                                {
                                        message("vision", HIM + temp->name() +
                                                HIM "忽然化作一缕清烟，不见了！\n" NOR,
                                                environment(temp));
                                }
                        }
                        DBASE_D->clear_object(file_name);
                }

                couple_id = ob->query("couple/couple_id");
                ob->delete("couple");
                ob->delete("can_summon/wedding ring");
                if (! sizeof(ob->query("can_summon")))
                        ob->delete("can_summon");
                flag++;
                if (couple_id) clear_user_data(couple_id, "couple");
        }

        // remove item information
        if (cat == "item" || cat == "all")
        {
                object item;
                mapping sum;

                // clear the all item
                path = ITEM_DIR + ob->query("id")[0..0] + "/";
                dirs = get_dir(path + ob->query("id") + "-*");
                for (i = 0; i < sizeof(dirs); i++)
                {
                        file_name = path + dirs[i];
                        if ((item = find_object(file_name)) &&
                            environment(item))
                        {
                                message("vision", HIM + item->name() +
                                        "忽然化作一股轻烟，不见了！\n" NOR,
                                        environment(item));
                        }

                        // rememberd by doing, for keep the item's data in dbased
/*
                        if (! flag_s)
                        {
                                DBASE_D->clear_object(file_name);
                                rm(file_name);
                        }
*/
                }

                if (mapp(sum = ob->query("can_summon")))
                {
                        // clear summon information
                        ks = keys(sum);
                        for (i = 0; i < sizeof(ks); i++)
                                if (sscanf(sum[ks[i]], path + ob->query("id") + "-%*s") == 1)
                                        map_delete(sum, ks[i]);

                        if (! sizeof(sum))
                                ob->delete("can_summon");
                }
        }

        // remove cruise information
        if (cat == "cruise" || cat == "all")
        {
                // clear the all item
                file_name = ITEM_DIR + "curise/" + ob->query("id");
                if (file_size(file_name + ".c") > 0)
                {
                        if (temp = find_object(file_name))
                        {
                                if (environment(temp))
                                {
                                        message("vision", HIM + temp->name() +
                                                HIM "忽然化作一缕清烟，不见了！\n" NOR,
                                                environment(temp));
                                }
                        }
                        DBASE_D->clear_object(file_name);
                        rm(file_name + ".c");
                }
                ob->delete("can_summon/cruise");
                if (! sizeof(ob->query("can_summon")))
                        ob->delete("can_summon");
        }

        // remove beast information
        if (cat == "beast" || cat == "all")
        {
                mapping whi;

                file_name = DATA_DIR + "beast/" + ob->query("id") + "-beast";
                if (file_size(file_name + ".c") > 0)
                {
                        if (temp = find_object(file_name))
                        {
                                if (environment(temp))
                                {
                                        message("vision", HIM + temp->name() +
                                                HIM "忽然化作一缕清烟，不见了！\n" NOR,
                                                environment(temp));
                                }
                        }
                        DBASE_D->clear_object(file_name);
                        rm(file_name + ".c");
                }
                if (mapp(whi = ob->query("can_whistle")))
                {
                        // clear summon information
                        ks = keys(whi);
                        for (i = 0; i < sizeof(ks); i++)
                                if (whi[ks[i]] == file_name)
                                        ob->delete("can_whistle/" + ks[i]);

                        if (! sizeof(ob->query("can_whistle")))
                                ob->delete("can_whistle");
                }

        }

        // remove invent information
        if (cat == "invent" || cat == "all")
        {
                mapping invents;
                string  *meskill;

                if (mapp(invents = ob->query("invent")))
                {
                        meskill = keys(invents);
                        for (i = 0; i < sizeof(meskill); i++)
                        {
                                CHINESE_D->remove_translate(invents[meskill[i]]);
                                SKILLS_D->remove_skill_from_skills(ob, invents[meskill[i]]);
                                ob->delete_skill(invents[meskill[i]]);
                                rm( SKILL_D(invents[meskill[i]]) + ".c" );
                                if (file_size(SKILL_D(invents[meskill[i]])) == -2)
                                rmtree( SKILL_D(invents[meskill[i]]) + "/" );
                        }

                        ob->delete("invent");
                }
        }

        // remove create information
        if (cat == "create" || cat == "all")
        {
                mapping creates;
                string  *skills, *perform;
                string  dir;
                object  pob;

                if (mapp(creates = ob->query("create")))
                {
                        skills = keys(creates);
                        for (i = 0; i < sizeof(skills); i++)
                        {
                                dir = SKILL_D(skills[i]);
                                if (dir[strlen(dir) - 1] != '/')
                                        dir += "/";
                                if (SKILL_D(skills[i])->valid_enable("force"))
                                        dir += "perform/";
                                perform = keys(creates[skills[i]]);
                                foreach (string pfm in perform)
                                {
                                        if (pob = get_object(dir + pfm))
                                                destruct(pob);
                                        rm(dir + pfm + ".c");
                                        ob->delete("can_perform/" + skills[i] + "/" + pfm);
                                }
                                if (sizeof(get_dir(dir)) < 1)
                                        rmdir(dir);
                        }
                        ob->delete("create");
                }
        }

        // remove board information
        if (cat == "board" || cat == "all")
        {
                object *rooms;
                rooms = filter_array(children(CHAT_ROOM),
                                     (: clonep($1) && $1->query("owner_id") == $(user) :));
                for (i = 0; i < sizeof(rooms); i++)
                        destruct(rooms[i]);
                file_name = DATA_DIR + "board/chatroom_" + user + __SAVE_EXTENSION__;
                rm(file_name);
        }

        // remove haterd information
        if (cat == "hatred" || cat == "all")
        {
                // remove the hatred information about the
                // familys & leagues to this player
                FAMILY_D->remove_hatred(ob->query("id"));
                LEAGUE_D->remove_hatred(ob->query("id"));
                BUNCH_D->remove_hatred(ob->query("id"));
        }

        // remove brothers information
        if (mapp(bro = ob->query("brothers")) &&
            (sscanf(cat, "brothers:%s", brothers) == 1 || cat == "all"))
        {
                // remove all the brothers information
                if (cat == "all") brothers = "all";

                // here, I remove the brothers information of
                // ob, when brothers equal to "all", then I
                // will remove all brothers for this ob, Does it
                // cause a BUG? I won't, because the ID "all"
                // can not be registered for this MUD.
                if (brothers == "all")
                {
                        foreach (bro_id in keys(bro))
                                // remove my brother's data for me
                                clear_user_data(bro_id, "brothers:" + ob->query("id"));

                        ob->delete("brothers");
                } else
                if (! undefinedp(bro[brothers]) != -1)
                {
                        // remove this brother
                        map_delete(bro, brothers);
                        if (sizeof(bro) < 1)
                                ob->delete("brothers");
                        else
                                ob->set("brothers", bro);
                }
                flag++;
        }

        // remove league information
        if (cat == "league" || cat == "all")
        {
                // remove the user's league info
                LEAGUE_D->remove_member_from_league(ob);
                ob->delete("league");
        }

        // remove bunch information
        if (cat == "bunch" || cat == "all")
        {
                // remove the user's banghui info
                BUNCH_D->remove_member_from_bunch(ob);
                ob->delete("bunch");
                flag++; 
        }

        if (cat == "skill" || cat == "all")
                SKILLS_D->remove_id_from_skills(ob);

        // remove title information
        if (cat == "title" || cat == "all")
                remove_title(ob);

        // remove granted information
        if (cat == "grant" || cat == "all")
                SECURITY_D->remove_grant(ob, "*");

        // save the data of the user
        if (flag) ob->save();

        // Destrut the object if create temporate
        if (login_ob)
        {
                catch(destruct(login_ob));
                catch(destruct(ob));
        }

        return "成功。\n";
}

// remove an user
varargs string remove_user(string user, int flag)
{
        object ob;
        string result;
        string flogin, fuser;

        // destruct the user object
        if (ob = find_player(user))
        {
                if (ob->query_temp("link_ob"))
                        catch(destruct(ob->query_temp("link_ob")));
                catch(destruct(ob));
        }

        // Remove the user from wizlist if the user was wizard
        SECURITY_D->set_status(user, "(player)");

        flogin = "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__;
        fuser  = "user/"  + user[0..0] + "/" + user + __SAVE_EXTENSION__;
        assure_file(TEMP_DIR + flogin);
        assure_file(TEMP_DIR + fuser);

        // clear the data of user first
        result = clear_user_data(user, "all", flag);

#ifdef DB_SAVE
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_remove_player(user);

        if (TX_SAVE)
        {
                cp(DATA_DIR + flogin, TEMP_DIR + flogin);
                cp(DATA_DIR + fuser,  TEMP_DIR + fuser);
                // remove the file of the user
                rm(DATA_DIR + "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__);
                rm(DATA_DIR + "user/" + user[0..0] + "/" + user + __SAVE_EXTENSION__);
        }
        // 论坛删除ID
        BOARD_D->db_remove_player(user);
#else
        cp(DATA_DIR + flogin, TEMP_DIR + flogin);
        cp(DATA_DIR + fuser,  TEMP_DIR + fuser);
        // remove the file of the user
        rm(DATA_DIR + "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__);
        rm(DATA_DIR + "user/" + user[0..0] + "/" + user + __SAVE_EXTENSION__);
#endif
}

// user born
void born_player(object me)
{
        mixed files;
        int i;
        string special;
        string msg;

        msg = HIG "你与生俱来的技能有：" NOR;

        // 查看所有的特殊技能文件
        // files = get_dir("/kungfu/special/");
        files = special_skill;
        me->delete("special_skill");

        if (sizeof(files))
        {
                // 整理所有的技能文件
                // for (i = 0; i < sizeof(files); i++)
                        // sscanf(files[i], "%s.c", files[i]);

                // 先天容貌 < 20 不会驻颜
                if (me->query("per") < 20)
                        files -= ({ "youth" });

                // 获得第一项技能
                special = files[random(sizeof(files))];
                me->set("special_skill/" + special, 1);
                msg += SPECIAL_D(special)->name();

                files -= ({ special });
                if (sizeof(files) && random(100) == 1)
                {
                        // 获得第二项技能
                        special = files[random(sizeof(files))];
                        me->set("special_skill/" + special, 1);
                        msg += HIG "、" NOR + SPECIAL_D(special)->name();
                }
                
                if (random(1000000) == 1)
                {
                        // 获得终极技能
                        special = special_ultimate[random(sizeof(special_ultimate))];
                        me->set("special_skill/" + special, 1);
                        msg += HIG "、" NOR + SPECIAL_D(special)->name();
                }
                                        
                msg += HIG "。\n" NOR;
                me->start_call_out((: call_other, __FILE__,
                                      "notice_player", me, msg :), 0);
        }
#ifdef DB_BOARD
        // 论坛创建ID
        BOARD_D->db_create_user(me); 
#endif
}

// notice user a piece of message, delay call by born user
void notice_player(object me, string msg)
{
        tell_object(me, msg);
}

// query title dbase
mixed query_title_base()
{
        if (! is_root(previous_object()))
                return 0;

        return title_base;
}

// set title dbase
mixed set_title_base(mixed ts)
{
        if (! is_root(previous_object()))
                return 0;

        title_base = ts;
}

// 清除某个玩家的 title
void remove_title(object ob)
{
        int i;

        if (! arrayp(title_base) || ! ob->query("granted_title"))
                return;

        ob->delete_temp("title");
        ob->delete("granted_title");

        for (i = 0; i < sizeof(title_base); i++)
        {
                // 搜索所有的 title
                if (title_base[i][1] == ob->query("id"))
                        // 去掉title
                        title_base[i][1] = 0;
        }
        save();
        return;
}

// 设置某个玩家的 title
void set_title(object ob)
{
        string id;
        int i;

        if (! arrayp(title_base) || ! ob->query("granted_title"))
                return;

        id = ob->query("id");
        for (i = 0; i < sizeof(title_base); i++)
                if (title_base[i][1] == id)
                {
                        // 加上title
                        ob->set_temp("title", title_base[i][0]);
                        return;
                }

        // 这个用户并没有分配的称号
        ob->delete("granted_title");
}

// 寻找或调入某一个玩家
// 如果程序处理中需要更新那些不在线的玩家，则可以使用该函数
// 将这个玩家调入并且进行修改，请注意：修改完毕以后程序必须
// 保存玩家，并且使用 global_destruct_player 将玩家析构，如
// 果没有调用这个函数，则赋予玩家的定时器会自动析构玩家。
object global_find_player(string user)
{
        object ob;
        object login_ob;

        ob = find_player(user);
        if (! ob)
        {
                login_ob = new(LOGIN_OB);
                login_ob->set("id", user);
                ob = LOGIN_D->make_body(login_ob);
                if (! ob)
                {
                        catch(destruct(login_ob));
                        return 0;
                }

                evaluate(bind((: seteuid(getuid()) :), ob));

                if (! ob->restore())
                {
                        catch(destruct(login_ob));
                        catch(destruct(ob));
                        return 0;
                }

                ob->set_temp("temp_loaded", 1);
                ob->start_call_out(bind((: call_other, __FILE__, "global_destruct_player", ob, 0 :), ob), 0);
                catch(destruct(login_ob));
        }

        return ob;
}

// 析构一个被 UPDATE_D 调入的玩家
void global_destruct_player(object ob, int raw)
{
        if (objectp(ob) && ob->query_temp("temp_loaded"))
        {
                if (raw) ob->save();
                destruct(ob);
        }
}
