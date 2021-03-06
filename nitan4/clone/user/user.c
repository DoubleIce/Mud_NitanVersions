// user.c

#include <origin.h>
#include <user.h>
#include <ansi.h>
#include <command.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;
inherit F_BUSINESS;

#define DEFAULT_PRISON          "/d/register/prison"

// 死亡保护
protected int die_protect(object ob);
protected void cancle_die_protect(object ob);

// 分站使用
nosave int admin_flag = 0;              // 是否是特殊的管理员？

// 数据是否完整？
nosave int user_cracked = 0;            // RESTORE 时检查数据并设置该标志

nosave int net_dead;                    // 标志：是否断开了连接
nosave int last_age_set = 0;            // 上一次更新AGE的时间
nosave int user_say = 0;                // 一定时间以内玩家做的say-action
nosave int user_command = 0;            // 一定时间以内玩家发送的命令
nosave int attach_flag = 0;             // 是否正在和系统联络
int        at_time = 0;                 // 在什么时间计算的
int        ban_to = 0;                  // 在什么时间解禁玩家
string     ban_say_msg = "";            // 禁止说话的消息

nosave string my_defeater_id;           // 上一次打晕你的人ID
nosave string my_killer_id;             // 上一次杀你的人的ID
nosave int    craze = 0;                // 愤怒

// globals variables
string  prison = 0;
int     time_to_leave = 0;

nosave array big_number = ({
        "combat_exp", "balance", "potential",
        "learned_points", "experience", "learned_experience",
});

#ifdef GLOBALS_DEBUG
nosave string impts = ({
        "quest_count", "questdg_times", "quesths_times",
        "questkj_times", "questsn_times",
});
#endif

int     is_stay_in_room()       { return 1; }
int     is_player()             { return clonep(); }
string  query_prison()          { return prison; }
int     query_time_to_leave()   { return time_to_leave; }
int     is_in_prison()          { return stringp(prison); }
int     is_net_dead()           { return net_dead || ! interactive(this_object()); }

varargs string calc_sec_id(int raw);

#define MAX_COMMAND_ONE_SECTION         40
#define MAX_SAY_ONE_SECTION             4
#define BAN_SAY_PERIOD                  60

int query_current_neili_limit();
int query_neili_limit();
int query_current_jingli_limit();
int query_jingli_limit();
mixed query_potential_limit();
int query_experience_limit();

int is_user() { return 1; }

mapping query_USER()
{
        mapping m=([]);
        m["at_time"] = at_time;
        m["ban_to"] = ban_to;
        m["ban_say_msg"] = ban_say_msg;
        m["prison"] = prison;
        m["time_to_leave"] = time_to_leave;
        return m;
}

int set_USER(mapping m)
{
        if (! mapp(m)) return 0;
        at_time = m["at_time"];
        ban_to = m["ban_to"];
        ban_say_msg = m["ban_say_msg"];
        prison = m["prison"];
        time_to_leave = m["time_to_leave"];
        return 1;
}

// 判断是否具有管理权限：如果是版本发布站点或是通过 PASSWD
// 命令设置过，则具有管理权限。具有该权限的巫师可是使用诸如
// clone、call、log、smash、copyskill等命令。
// int is_admin()  { return VERSION_D->is_release_server() || admin_flag == 21 || getuid() == "lonely"; }
int is_admin()  { return VERSION_D->is_release_server() || getuid() == "lonely" ; }
int set_admin() { if (is_root(previous_object())) admin_flag = 21; }

void create()
{
        ::create();
        set_name("使用者物件", ({ "user object", "user", "object" }) );
}

void terminal_type(string term_type)
{
        set_temp("terminal_type", term_type);
        message("system", "终端机型态设定为 " + term_type + "。\n", this_object());
}

void window_size(int width, int height)
{
        set_temp("window_size", ({width, height}));
        message("system", "终端窗口大小设置为 " + width + " × " + height + "。\n", this_object());
}

void reset()
{
        int lv;

        if ((int)query("thief") > 0)
                add("thief", -1);

        if ((int)query("total_hatred") > 0)
                add("total_hatred", -1);

        if ((lv = query_skill("xiantian-gong", 1)) >= 60 ||
            (lv = query_skill("quanzhen-xinfa", 1)) >= 60)
        {
                if (can_improve_skill("force"))
                        improve_skill("force", lv * 20);

                if (query_skill("quanzhen-xinfa", 1) >= 60 &&
                    can_improve_skill("quanzhen-xinfa"))
                        improve_skill("quanzhen-xinfa", lv * 10);

                if (query_skill("xiantian-gong", 1) >= 60 &&
                    can_improve_skill("xiantian-gong") &&
                    SKILL_D("xiantian-gong")->valid_learn(this_object()))
                        improve_skill("xiantian-gong", lv * 10);
        }
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
        string id;

        id = geteuid();
        if (! id) id = getuid();
        if (! stringp(id)) return 0;
        return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}

// override set function
mixed set(string idx, mixed para)
{
        int i, j, lvl, level;
        object ob = this_object();

        if (idx == "combat_exp" && para && clonep(ob) && geteuid(ob))
        {
#ifdef LONELY_IMPROVED
                para = to_string(para);
                if (count_gt(para, query("combat_exp"))) {
#else
                if (para > (int)query("combat_exp", 1)) {
#endif
#ifdef GLOBALS_DEBUG
                        if (objectp(previous_object()) &&
                            count_gt(count_sub(para, query("combat_exp")), 10000000))
                                log_file("static/illegal",
                                         sprintf("%s  %s(%s) want to set %s exp from %s to %s.\n",
                                                 ctime(time()),
                                                 (string)base_name(previous_object()),
                                                 (this_player(1) ? geteuid(this_player(1)) : "???"),
                                                 (string)geteuid(ob),
                                                 to_string(query("combat_exp")),
                                                 to_string(para)));
#endif
                        level = (int)query("level", 1);
                        if (! level || level < 1) level = 1;

                        for (i = level; ;i++) {
#ifdef LONELY_IMPROVED
                                if (count_gt(count_mul(big_number_pow((i + 1), 3), 10000), para))
#else
                                if ((i + 1) * (i + 1) * (i + 1) > (para / 10000))
#endif
                                {
                                        lvl = i;
                                        break;
                                }
                        }

                        if (lvl > level)
                        {
                                j = lvl - level;
                                set("level", lvl);
                                add("points", 4 * j);
                                add("experience", 20 * j);
                                add("potential", 200 * j);
                                add("magic_points", 20 * j);
                                tell_object(ob, HIY "只见一道红光飞进你的体内，你的人物等级提升了！\n" +
                                        "此次升级，你获得了" + chinese_number(4 * j) +
                                        "点技能点、" + chinese_number(200 * j) +
                                        "点潜能、" + chinese_number(20 * j) +
                                        "点实战体会和" + chinese_number(20 * j) +
                                        "点灵慧！\n" NOR);
                        }
                }
                return ::set(idx, para);
        } else
        if (member_array(idx, big_number) != -1 && para &&
            clonep(ob) && geteuid(ob))
        {
                para = to_string(para);
                return ::set(idx, para);
        } else
        if (idx == "name" && clonep(ob) && geteuid(ob))
        {
                NAME_D->change_name(ob, para, 1);
                return para;
        } else
#ifdef GLOBALS_DEBUG        
        if (member_array(idx, impts) != -1 && para &&
            clonep(ob) && geteuid(ob) && objectp(previous_object()))
        {
                if (count_gt(count_sub(para, query(idx)), 1))
                        log_file("static/illegal",
                                 sprintf("%s  %s(%s) want to set %s %s from %s to %s.\n",
                                         ctime(time()),
                                         (string)base_name(previous_object()),
                                         (this_player(1) ? geteuid(this_player(1)) : "???"),
                                         (string)geteuid(ob),
                                         (string)idx,
                                         to_string(query(idx)),
                                         to_string(para)));                
        } else
#endif
                return ::set(idx, para);
}

// override add function by Lonely
mixed add(string prop, mixed data)
{
        string para;
        mixed old;

#ifdef LONELY_IMPROVED
        if (member_array(prop, big_number) != -1 &&
            clonep(this_object()) &&
            geteuid(this_object()))
        {
                if (! (old = query(prop, 1)))
                       old = 0;

                para = count_add(old, data);
                if (prop == "combat_exp")
                        return set(prop, para);

                return ::set(prop, para);

        } else
#else

        if (prop == "combat_exp" && clonep(this_object()) &&
            geteuid(this_object())) {
                if (! (old = query(prop, 1)))
                        return set(prop, data);

                return set(prop, old + data);
        } else
#endif

#ifdef GLOBALS_DEBUG        
        if (member_array(prop, impts) != -1 && para &&
            clonep(this_object()) && geteuid(this_object()) && 
            objectp(previous_object())) {
                if (count_gt(data, 1))
                        log_file("static/illegal",
                                 sprintf("%s  %s(%s) want to add %s %s %s.\n",
                                         ctime(time()),
                                         (string)base_name(previous_object()),
                                         (this_player(1) ? geteuid(this_player(1)) : "???"),
                                         (string)geteuid(this_object()),
                                         to_string(data),
                                         (string)prop)); 
                                           
                return ::add(prop, data);             
        } else
#endif
                return ::add(prop, data);
}

int save()
{
        int res;

        if (user_cracked)
                // 数据不完整，不能保存
                return 1;

        if (query_temp("user_setup"))
        {
                save_autoload();
                set("sec_id", calc_sec_id());   // save sec_id
#ifdef DB_SAVE
                res = DATABASE_D->db_save_all(this_object());
                if (TX_SAVE)
                        res = ::save();
#else
                res = ::save();
#endif
                clean_up_autoload();            // To save memory
        } else
        {
                set("sec_id", calc_sec_id());   // save sec_id
#ifdef DB_SAVE
                res = DATABASE_D->db_save_all(this_object());
                if (TX_SAVE)
                        res = ::save();
#else
                res = ::save();
#endif
        }

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(me);
#endif
        return res;
}

int restore()
{
        int res;
        string sec_id;

#ifdef DB_SAVE
        res = DATABASE_D->db_restore_all(this_object());

        if ((int)query_temp("restore_mysql"))
                 res = ::restore();

        // if (res && ! DATABASE_D->crc_status())
        if (res)
#else
        res = ::restore();

        if (res)
#endif
        {
                /*
                if (stringp(sec_id = query("sec_id")))
                {
                        if (crypt(calc_sec_id(1), sec_id) != sec_id)
                        {
                                // 数据不完整
                                log_file("static/user",
                                         sprintf("%s %s's data my be corrupt.\n",
                                                 log_time(), getuid()));
                                user_cracked = 1;
                                return 0;
                        }
                } else
                {
                        log_file("static/user",
                                 sprintf("%s %s lost assure key.\n",
                                         log_time(), getuid()));
                        user_cracked = 1;
                        return 0;
                }
                */

                // 数据完整
                user_cracked = 0;
        }
        if (! query("on_time"))
                set("on_time", query("mud_age"));

        return res;
}

// This function updates player's age, called by heart_beat()
void update_age()
{
        int age;
        int delta;

        if (! last_age_set)
        {
                last_age_set = time();
                add("mud_age", 0);
        }

        if ((delta = (time() - last_age_set)) > 100)
                // time too long
                delta = 100;

        // 离线练功时间
        if (! interactive(this_object()) && query("doing"))
                add("offline_time", delta);
        else        
        if (interactive(this_object()))     
                add("online_time", delta);

        if (! environment() ||
            ! environment()->is_chat_room() ||
            ! query("env/halt_age"))
        {
                // Update age
                add("mud_age", delta);
                if (query("monfee") < time()) // 月费控制，非月费用户才在这里扣点
                        add("on_time", delta);
                if (time_to_leave)
                        time_to_leave -= delta;
        }

        last_age_set = time();
        age = query("age_modify") + query("mud_age") / 86400;
        if (age > 118) age = 46 + (age - 118) / 4; else
        if (age > 28)  age = 16 + (age - 28) / 3; else
        if (age > 4)   age = 4  + (age - 4) / 2;
        age -= (int)query_temp("apply/reduce_age");
        if (age < 0) age = 0;
        age += 14;
        set("age", age);
        if (query("age") > 19)
        {
                if (query("newbie"))  delete("newbie");
                if (query("map"))
                {
                        delete("map");
                        set("map_all", 1); 
                }
        }
        if (query("age") < 20 && ! query("no_newbie")) set("newbie", 1);

        // 八荒六合唯我独尊功
        if (query_skill_mapped("force") == "bahuang-gong")
        {
                if (age >= 60)
                {
                        set("mud_age", 1382400);
                        set("age", 30);
                }
        }

        // 全真先天功
        if (query_skill_mapped("force") == "xiantian-gong" &&
            !query("sex") &&
            query("age") >= 40)
        {
                set("mud_age", 2246400);
                set("age", 40);
                return;
        }

        //设置生日状态
        if ((int)query("mud_age") % 86400 < 240)
                set("on_birthday", 1);
        else
                set("on_birthday", 0);

}

void setup()
{
        // We want set age first before new player got initialized with
        // random age.
        last_age_set = 0;
        update_age();

        ::setup();

        // set the enable flag to enable save
        set_temp("user_setup", 1);

        restore_autoload();

        if (query("doing"))
                CLOSE_D->continue_doing(this_object());
}

void user_dump(int type)
{
        switch(type)
        {
        case DUMP_NET_DEAD:
                if (environment())
                {
                        tell_room(environment(), query("name") + "断线超过 " +
                                  NET_DEAD_TIMEOUT / 60 + " 分钟，自动退出这个世界。\n");
                }
                catch(command("quit"));
                if (this_object() && ! query("doing"))
                {
                        // command quit failed.
                        QUIT_CMD->force_quit(this_object());
                }
                break;

        case DUMP_IDLE:
                if (query_temp("learned_idle_force"))
                {
                        message_vision("$N狂笑三声，道：我终于明白了！\n",
                                       this_object());
                        tell_object(this_object(), "你经过长时间的发"
                                    "呆，终于对发呆神功的理解又深了一层！\n");
                        improve_skill("idle-force", 360000);
                        delete_temp("learned_idle_force");
                } else
                        tell_object(this_object(), "对不起，您已经发呆超过 " +
                                    IDLE_TIMEOUT / 60 + " 分钟了，请下次再来。\n");
                if (environment())
                {
                        tell_room(environment(), "一阵风吹来，将发呆中的" + query("name") +
                                   "化为一堆飞灰，消失了。\n", ({this_object()}));
                }
                command("quit");
                if (this_object() && ! query("doing"))
                {
                        // command quit failed.
                        QUIT_CMD->force_quit(this_object());
                }
                break;
        default:
                return;
        }
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
protected void net_dead()
{
        object link_ob;

        this_object()->remove_interactive();

        if (! query("doing"))
                set_heart_beat(0);

        if (objectp(link_ob = query_temp("link_ob")))
        {
                if (link_ob->query_temp("ip_number"))
                {
                        link_ob->set("last_on", time());
                        link_ob->set("last_from",
                                     link_ob->query_temp("ip_number"));
                        link_ob->save();
                }
                destruct(link_ob);
        }

        net_dead = 1;
        if (userp(this_object()) && ! query("doing"))
        {
                call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
                tell_room(environment(), query("name") + "断线了。\n", this_object());
                // CHANNEL_D->do_channel(this_object(), "sys", "断线了。");
                remove_all_enemy(1);
        } else
        {
                if (environment())
                        message("vision", name() + "离线了。\n",
                                environment(), ({ this_object() }));
        }
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
        set_heart_beat(1);
        net_dead = 0;
        remove_call_out("user_dump");
        tell_object(this_object(), "重新连线完毕。\n");
}

// skill variable & function
#define MAX_NEILI_IMPROVE       query("con")
#define MAX_JINGLI_IMPROVE      query("con")

int query_neili_limit()
{
        string *skill_names;
        mapping skills;
        int neili_limit;
        int base_lvl, lvl;
        int tmp;
        int i;
        string fam;
        int reborn;

        skills = this_object()->query_skills();
        if (! mapp(skills))
                return 0;

        skill_names = keys(skills);

        base_lvl = ((int) skills["force"]) / 2;
        neili_limit = base_lvl * 30;
        for (i = 0; i < sizeof(skill_names); i++)
        {
                if (file_size(SKILL_D(skill_names[i]) + ".c") == -1)
                {
                        // No such skill
                        continue;
                }

                if (! SKILL_D(skill_names[i])->valid_enable("force"))
                        continue;

                lvl = (int) skills[skill_names[i]];
                tmp = (base_lvl + lvl) * 30;
                tmp += (int) SKILLS_D->query_neili_improve(skill_names[i], lvl);
                if (tmp > neili_limit) neili_limit = tmp;
        }

        neili_limit += neili_limit / 100 * query("improve/neili");
        if (query("breakup"))
                neili_limit += neili_limit / 10 * 3;

        if (query("special_skill/mystery"))
                neili_limit += query_con() * 150;

        fam = query("family/family_name");
        if (query("class") == "bonze" &&
            (fam == "大轮寺" || fam == "少林派" || fam == "峨嵋派" || fam == "血刀门"))
                neili_limit += 500;
        
#ifdef DB_SAVE
        if (MEMBER_D->is_valid_member(query("id")))
                neili_limit += neili_limit / 2;
#endif

        if (reborn = (int)query("reborn/times"))
                neili_limit *= (reborn + 1);

        // 转世技能增加内力上限
        if (query("special_skill/ghost"))
                neili_limit += neili_limit * 50 / 100;

        if (query_temp("apply/max_neili"))
                neili_limit += query_temp("apply/max_neili");

        return neili_limit;
}

int query_current_neili_limit()
{
        int neili, lvl;
        int reborn;
        string force;
        string fam;

        force = query_skill_mapped("force");
        neili = (int)query_skill("force", 1) / 2 * 30;
        if (stringp(force) && force != "")
        {
                lvl = (int)query_skill(force, 1);
                neili += lvl * 30;
                neili += SKILLS_D->query_neili_improve(force, lvl);
        }

        neili += neili / 100 * query("improve/neili");
        if (query("breakup"))
                neili += neili / 10 * 3;

        if (query("special_skill/mystery"))
                neili += query_con() * 150;

        fam = query("family/family_name");
        if (query("class") == "bonze" &&
//            (fam == "雪山寺" || fam == "少林派" || fam == "峨嵋派" || fam == "血刀门"))
            (fam == "大轮寺" || fam == "少林派" || fam == "峨嵋派" || fam == "血刀门"))
                neili += 500;
        
        // 先天加权
        neili += neili * (query("con") - 20) / 100;
                
#ifdef DB_SAVE
        if (MEMBER_D->is_valid_member(query("id")))
                neili += neili / 2;
#endif

        if (reborn = (int)query("reborn/times"))
                neili *= (reborn + 1);

        // 转世技能增加内力上限
        if (query("special_skill/ghost"))
                neili += neili * 30 / 100;

        if (query_temp("apply/max_neili"))
                neili += query_temp("apply/max_neili");

        return neili;
}

int query_jingli_limit()
{
        int limit;
        int reborn;

        limit = ((int)query("magic_points") / 20) + query("int") * 90;
        limit += limit / 100 * query("improve/jingli");
        if (query("animaout"))
                limit += limit / 10 * 4;

#ifdef DB_SAVE
        if (MEMBER_D->is_valid_member(query("id")))
                limit += limit / 2;
#endif

        if (reborn = (int)query("reborn/times"))
                limit *= (reborn + 1);

        if (query("special_skill/demon"))
                limit += limit * 50 / 100;
        /*
        if (limit > query_neili_limit() / 2)
                limit = query_neili_limit() / 2;
        */
        if (query_temp("apply/max_jingli"))
                limit += query_temp("apply/max_jingli");

        return limit;
}

int query_current_jingli_limit()
{
        return query_jingli_limit();
}

mixed query_potential_limit()
{
        mixed p;

#ifdef LONELY_IMPROVED
        p = count_div(query("combat_exp"), 20);
        p = count_add(p, count_div(count_mul(p, query_int()), 100));
        if (ultrap(this_object()))
                p = count_add(p, 1000000);
        p = count_add(p, 100000);

        if (query_temp("apply/max_potential"))
                p = count_add(p, query_temp("apply/max_potential"));

        return count_add(query("learned_points"), p);
#else
        p = (int)query("combat_exp") / 20;
        p += (query_int() * p / 100);
        if (ultrap(this_object()))
                p += 1000000;
        p += 100000;

#ifdef DB_SAVE
        if (MEMBER_D->is_valid_member(query("id")))
                p += p / 2;
#endif

        if (query_temp("apply/max_potential"))
                p += query_temp("apply/max_potential");

        return (int)query("learned_points") + p;
#endif
}

mixed query_experience_limit()
{
        int p;

        if (ultrap(this_object()))
                p = 100000;
        else
        {
                p = query("score");
                if (p < 100)
                        p = p / 2;
                else
                if (p < 300)
                        p = p / 4 + 25;
                else
                if (p < 1100)
                        p = (p - 300) / 8 + 100;
                else
                        p = (p - 1100) / 16 + 200;
                if (p > 80000)
                        p = 80000;
        }

#ifdef DB_SAVE
        if (MEMBER_D->is_valid_member(query("id")))
                p *= 2;
#endif

        if (query_temp("apply/max_experience"))
                p += query_temp("apply/max_experience");

        return count_add(query("learned_experience"), p);
}

mixed improve_potential(int n)
{
        mixed max;

#ifdef LONELY_IMPROVED
        max = count_sub(query_potential_limit(), query("potential"));
        if (count_le(max, 0)) return 0;
        if (count_gt(max, n)) max = n;
#else
        max = query_potential_limit() - query("potential");
        if (max <= 0) return 0;
        if (max > n) max = n;
#endif
        add("potential", max);
        return max;
}

mixed improve_experience(mixed n)
{
        mixed max;

        max = count_sub(query_experience_limit(), query("experience"));
        if (count_le(max, 0)) return 0;
        if (count_gt(n, max)) n = max;

        add("experience", n);
        return n;
}

int can_improve_neili()
{
        return query("improve/neili") < MAX_NEILI_IMPROVE;
}

int can_improve_jingli()
{
        return query("improve/jingli") < MAX_NEILI_IMPROVE;
}

int improve_neili(int n)
{
        int delta;

        if ((delta = query_neili_limit() - query("max_neili")) <= 0)
                return 0;

        if (n > delta) n = delta;
        add("max_neili", n);
        setup();
        return n;
}

int improve_jingli(int n)
{
        int delta;

        if ((delta = query_jingli_limit() - query("max_jingli")) <= 0)
                return 0;

        if (n > delta) n = delta;
        add("max_jingli", n);
        setup();
        return n;
}

int accept_fight(object ob)
{
        if (query_temp("pending/fight") == ob)
                return 1;

        tell_object(this_object(), YEL "如果你愿意和对方进行比试，请你也对" +
                    ob->name() + "("+ (string)ob->query("id")+")"+
                    "下一次 fight 指令。\n" NOR);

        tell_object(ob, YEL "由于对方是由玩家控制的人物，你必须等对方同意才" +
              "能进行比试。\n" NOR);

        return 0;
}

int accept_hit(object ob)
{
        if (! die_protect(ob))
                return 0;
                
        message_vision("$N大喝道：" + ob->name() + "，你要干什么？\n",
                       this_object(), ob);
        return 1;
}

int accept_kill(object ob)
{
        if (is_killing(ob->query("id")))
                return 1;

        if (! die_protect(ob))
                return -1;
                
        tell_object(this_object(), HIR "如果你要和" + ob->name() +
                "性命相搏，请你也对这个人(" + (string)ob->query("id") +
                ")下一次 kill 指令。\n" NOR);
        return 1;
}

int accept_ansuan(object who)
{
        if (! die_protect(who))
                return 0;
                
        command(random(2) ? "say 嗯！怎么..." : "say 啊！不好！");
        return 1;
}

int accept_touxi(object who)
{
        if (! die_protect(who))
                return -1;
                
        switch (random(2))
        {
        case 0:
                message_vision("$N大吃一惊，叫道：“好你个" +
                               RANK_D->query_rude(who) + "！真不要脸！”\n",
                               this_object(), who);
                break;

        default:
                message_vision("$N仓皇之间，不及说话，只得接下$n"
                               "这一招。\n", this_object(), who);
                break;
        }

        return 1;
}

int die_protect(object ob)
{
        object env;
        object me = this_object();

        // 只有玩家之间才有死亡保护
        if (! userp(me) || ! userp(ob))
                return 1;

        // 在比武场所不考虑死亡保护
        if (me->query_temp("in_pkd"))
                return 1;

        env = environment(me);
        if (env->query("fight_room") ||
            env->query("no_death"))
                return 1;

        // 去除攻击者的死亡保护信息
        if (userp(me))
                cancle_die_protect(ob);

        // 被攻击者处于保护时期，本攻击失败
        if (me->query("die_protect/last_dead") + me->query("die_protect/duration") > time())
        {
                message_vision("$N处于被保护时期，$n不能进行攻击。\n",
                               me, ob);
                return 0;
        }

        return 1;
}

void cancle_die_protect(object ob)
{
        ob->delete("die_protect");
}

int reject_command()
{
        int t;

        if (wizardp(this_object()))
                return 0;

        t = time() & 0xFFFFFFFE;
        if (at_time != t)
        {
                at_time = t;
                user_command = 1;
                user_say = 0;
        } else
                user_command++;

        if (user_command > MAX_COMMAND_ONE_SECTION)
        {
                user_command = 0;
                if (! query("born"))
                        // not born yet
                        return 0;
                return 1;
        }

        return 0;
}

void ban_say_until(int ban_period, string msg)
{
        int t;

        t = time();
        if (ban_to > t)
                ban_to += ban_period;
        else
                ban_to = t + ban_period;
        ban_say_msg = msg;
}

int ban_say(int raw)
{
        int t;

        if (wizardp(this_object()))
                return 0;

        if (is_in_prison())
        {
                notify_fail("你省省吧，好好做你的牢，少折腾。\n");
                return 1;
        }

        t = time() & 0xFFFFFFFE;
        if (ban_to > t)
        {
                notify_fail(ban_say_msg + "，请于" +
                            appromix_time(ban_to - t) + "以后再尝试。\n");
                return 1;
        }

        if (! raw)
                return 0;

        if (at_time != t)
        {
                at_time = t;
                user_say = 1;
                user_command  = 0;
        } else
                user_say++;

        if (user_say > MAX_SAY_ONE_SECTION)
        {
                ban_say_until(BAN_SAY_PERIOD, "系统禁止你送出信息");
                /*
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "因为太罗嗦，被人堵住了嘴。");
                */
                notify_fail(HIR "由于你发布的信息太多，因此系统暂时"
                            "禁止你发出信息。\n" NOR);
                return 1;
        }

        return 0;
}

void permit_say(int n)
{
        if (ban_to <= time())
                return;

        if (! n)
                ban_to = 0;
        else
                ban_to -= n;

        if (ban_to <= time())
                tell_object(this_object(), "你可以继续发布信息了！\n");
}

// thow the person into prison
void get_into_prison(object ob, string p, int time)
{
        object me;

        me = this_object();
        if (! p) p = prison;
        if (! p) p = DEFAULT_PRISON;

        if (prison && base_name(environment()) == p)
        {
                time_to_leave += time * 60;
                if (ob && time)
                        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                                "听说" + query("name") + "的刑期被" +
                                ob->query("name") + "加长了" +
                                appromix_time(time * 60) + "。");
                return;
        }

        if (prison && prison == p && base_name(environment()) != prison)
        {
                p->catch_back(me);
                me->set("startroom", prison);
                me->move(prison);
                message_vision("“啪”的一声，$N狠狠的摔倒了地上。\n", me);
                // if (living(me)) me->unconcious();
                if (living(me))
                        me->enable_player();
                        
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "越狱潜逃，结果被抓"
                        "回去了。");

                save();
                return;
        }

        p->catch_ob(me);

        if (ob)
        {
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "被" + ob->query("name") +
                        "送进了" + p->short() + HIM "，禁闭" +
                        appromix_time(time * 60) + "。");
        }

        me->set("startroom", prison);
        me->move(p);
        prison = p;
        time_to_leave += time * 60;
        save();

        message_vision("“啪”的一声，$N重重的摔倒了地上。\n", me);
        me->set("jing", 1);
        me->set("eff_jing", 1);
        me->set("qi", 1);
        me->set("eff_qi", 1);
        me->set("jingli", 0);
        me->set("neili", 0);
        me->receive_damage("jing", 0);
        // if (living(me)) me->unconcious();
        if (living(me))
                        me->enable_player();
}

// out of prison
void leave_prison(object ob, int time)
{
        object me;

        me = this_object();
        if (time)
        {
                time_to_leave -= time * 60;
                if (time_to_leave > 0)
                {
                        CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                                "听说" + query("name") + "的刑期被" +
                                ob->query("name") + "缩短了" +
                                appromix_time(time * 60) + "。");
                        return;
                }
        }

        time_to_leave = 0;

        if (! prison->free_ob(me))
                return;

        prison = 0;

        if (living(me))
                me->enable_player();
        else
                me->revive();
        save();

        if (ob)
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "被" + ob->name() +
                        "提前释放了。");
        else
                CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
                        "听说" + query("name") + "已经刑满释放了。");
}

varargs void die(object killer)
{
        if (prison)
        {
                set_temp("die_reason", "惨死在监狱中");
                clear_condition(0);
                receive_damage("qi", 0);
                prison = 0;
                if (living(this_object()))
                        enable_player();
        }

        ::die(killer);
        save();
}

// when the user was in prison, the heart beaten function of
// char will call damage heal_up, then the function will call
// it
void update_in_prison()
{
        object me;

        me = this_object();
        me->set("qi", 0);
        me->set("jing", 0);
        me->set("neili", 0);

        if (! living(me))
                return;

        if (time_to_leave > 0)
        {
                if (environment() && base_name(environment()) != prison)
                {
                        // escape from prison?
                        get_into_prison(0, 0, 0);
                }
                return;
        }

        leave_prison(0, 0);
}

// return true if the user was attached system, such as
// command sameip will run a much long time, in the period
// the user shouldn't receive message except from the system
int is_attach_system()
{
        return attach_flag;
}

// start attaching
int attach_system()
{
        attach_flag = 1;
}

// stop, deatched
int detach_system()
{
        attach_flag = 0;
}

string command_verb()
{
        return query_verb();
}

#define CRAZE_LIMIT_1   7000    // for 光明磊落
#define CRAZE_LIMIT_2   5000    // for 心狠手辣

// 愤怒气息
int query_craze() { return craze; }

// 最大的愤怒气息
int query_max_craze()
{
        switch (query("character"))
        {
        case "光明磊落" :
                return CRAZE_LIMIT_1;

        case "心狠手辣" :
                return CRAZE_LIMIT_2;
        default:
                return 0;
        }
}

// 现在是否处于最愤怒的状态
int is_most_craze()
{
        return (craze > 0) && (craze >= query_max_craze());
}

// 因为被打倒而震怒
void craze_of_defeated(string defeater_id)
{
        my_defeater_id = defeater_id;
}

// 因为被击毙而震怒
void craze_of_die(string killer_id)
{
        my_killer_id = killer_id;
        craze = query_max_craze();
}

// 愤怒的攻击对手后调用这个函数清除对象
void craze_defeated(string enemy_id)
{
        if (enemy_id == my_defeater_id)
                my_defeater_id = 0;

        if (enemy_id == my_killer_id)
                my_killer_id = 0;
}

// 是否憎恨某人
int is_hating(string enemy_id)
{
        if (enemy_id == my_defeater_id ||
            enemy_id == my_killer_id)
                return 1;

        return 0;
}

// 提升愤怒，返回提升的有效值
int improve_craze(int amount)
{
        int limit;

        if (amount < 0)
                error("error: improve_craze amount to be less than 0\n");

        limit = query_max_craze();
        craze += amount;
        if (craze > limit)
        {
                amount += limit - craze;
                craze = limit;
        }
        return amount;
}

// 消耗愤怒，返回消耗的有效值
int cost_craze(int n)
{
        if (n < 0)
                error("error: improve_craze amount to be less than 0\n");

        if (n > craze)
        {
                n = craze;
                craze = 0;
        } else
                craze -= n;
        return n;
}

/*
// 编辑文件
void edit_file(string file)
{
        ed(file);
}
*/

// 是否是结拜兄弟？
int is_brother(mixed ob)
{
        string id;

        if (stringp(ob))
                id = ob;
        else
        if (objectp(ob))
                id = ob->query("id");
        else
                return 0;

        // 是否是普通结拜兄弟
        if (query("brothers/" + id))
                return 1;

        // 是否是结盟的兄弟
        return 0;
}

string query_vip()
{
        int vip_type;
        int vip_date;
        int date;
        vip_type = query("vip_type");
        vip_date = query("vip_date");
        date = time();
        if(!vip_date )
                return "零";
        if(vip_date < date) 
                return "零（已过期）";
        else
                return to_chinese(vip_type)+"（剩余 "+to_chinese((vip_date-date)/86400)+" 天）";
}

int is_vip()
{
        int vip_type;
        int vip_date;
        int date;
        vip_type = query("vip_type");
        vip_date = query("vip_date");
        date = time();
        if(vip_date < date)
                return 0;
        else
                return vip_type;
}

// 计算完整性数据和
string calc_sec_id(int raw)
{
        mapping my;
        string *list;
        string key;
        int sum;
        string str;
        int i;

        sum = 0;

        // 累计所有的数据
        if (mapp(my = query_entire_dbase()))
        {
                foreach (key in keys(my) - ({ "sec_id" }))
                {
                        sum += sizeof(key);
                        if (intp(my[key]))
                                sum += my[key];
                        else
                                sum += sizeof(my[key]);
                }
        }

        // 累计所有的武功技能
        // if (mapp(my = query_skills()))
        if (mapp(my = query_skillc()))
        {
                foreach (key in keys(my))
                {
                        sum += sizeof(key);
                        if (intp(my[key]))
                                sum += my[key];
                        else
                                sum += sizeof(my[key]);
                }
        }

        // 因动态装备在载入前后涉及到字符转换的问题，累计结果会不一样
        // 故取消累计所有携带的物品 
        /*
        // 累计所有携带的物品 
        if (arrayp(list = query_autoload_info()))
        {
                foreach (key in list)
                {
                        sum += sizeof(key);
                        if (stringp(key))
                                for (i = 0; i < strlen(key); i++) sum += key[i];
                }
        }
        */

        // 转化成字符串
        str = sprintf("%d", sum);
        str[0] = (sum % 26) + 'a';

        if (! raw) str = crypt(str, 0);
        return str;
}

string query_info()
{
        string msg;
	int dexp, dpot, dmar, dage, dquest, dt;

	if (wiz_level(this_object()) > 0)
		return 0;

	msg = "";
        if (query("chblk_on"))
        {
                if (stringp(query("chblk_by")))
                        msg += "频道已经被 " + query("chblk_by") + " 关闭。\n";
                else
                        msg += "频道被关闭中。\n";
        }

	dexp = atoi(count_sub(query("combat_exp"), query("last_examine/combat_exp")));
	dpot = atoi(count_sub(query("potential"), query("last_examine/potential")));
	dmar = atoi(count_sub(query("experience"), query("last_examine/experience")));
	dage = query("mud_age") - query("last_examine/mud_age");
	dquest = query("all_quest") - query("last_examine/all_quest");
	dt = time() - query("last_examine/time");
	if (dquest < 0) dquest += 1000;

	if (dt > 60)
	{
		msg += sprintf("自上次检查 %s 以来：\n"
			       "连线时间增加了 %s。\n"
			       "师门任务完成了 %d 个。\n"
		               "平均每分钟获得经验速度：%d\n"
		               "平均每分钟获得潜能速度：%d\n"
		               "平均每分钟获得体会速度：%d\n",
			       appromix_time(dt),
			       appromix_time(dage),
			       dquest,
			       dexp * 60 / dt, dpot * 60 / dt, dmar * 60 /dt);
	}

        return msg;
}
