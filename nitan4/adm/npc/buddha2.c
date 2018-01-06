// This program is a part of NITAN MudLIB
// Buddha2.c

#include <ansi.h>
inherit NPC;

#define BUDDHA  "/adm/npc/buddha"
int ask_recover();

void create()
{
        seteuid(getuid());
        set_name(HIY "释迦牟尼" NOR, ({ "buddha", "fo zu", "fo", "shijia muni" }));
        set("long", @LONG
佛祖庄严宝像，让人不敢正视。
LONG);
        set("nickname", HIW "三界法王" NOR);
        set("title", HIC "佛祖" NOR);
        set("gender", "男性" );
        set("age", 500);
        set("attitude", "friendly");
        set("max_jing", 99999);
        set("max_qi", 99999);
        set("max_jingli", 99999);
        set("jingli", 99999);
        set("max_neili", 99999);
        set("neili", 99999);
        set("jiali", 9999);
        set("str", 99);
        set("int", 99);
        set("con", 99);
        set("dex", 99);
        set("combat_exp", 99999999);

        set("inquiry", ([
                "前世" : (: ask_recover :),
        ]));

        set_skill("dodge", 999);
        set_skill("unarmed", 999);
        set_skill("force", 999);
        set_skill("parry", 999);
        set_skill("sword", 999);
        set_skill("medical", 999);
        set_skill("literate", 999);
        set_skill("lamaism", 999);
        set_skill("buddhism", 999);
        set_skill("shaolin-yishu", 999);
        set_skill("idle-force", 999);
        set_skill("huntian-baojian", 999);
        set_skill("lunhui-jian", 999);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "lunhui-jian");
        map_skill("sword", "lunhui-jian");
        map_skill("medical", "shaolin-yishu");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("/clone/cloth/y-jiasha")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        add_action("do_recollect", "recollect");
}

int ask_recover()
{
        object me = this_player();

        command("look " + me->query("id"));
        command("say 你与我前世有缘吗?");
        command("say 你可记得前世你姓甚名谁，我给你的揭语又是什么？");
        command("say 若你能答得上来我便给你开启前生全部记忆。");

        tell_object(me, HIW "佛祖在你耳边说道，若你想起来了就输入 recollect <id> <揭语> \n" NOR);
        return 1;
}

int do_recollect(string arg)
{
        string content, filename, item_filename;
        string my_id, my_name, id, pass;
        mapping all_skills, data, tmp_data, sum_data, my;
        array sname, sum;
        int i, n;
        object buddha, ob, me = this_player();

        if( me->query("reborn/times") )
                return notify_fail("你的阿赖耶识不是已经打开了吗？");

        if( !arg || sscanf(arg, "%s %s", my_id, pass) != 2 )
                return notify_fail("你究竟记不记得自己前世是谁？\n");

        buddha = get_object(BUDDHA);
        data = buddha->query_reborn_data(my_id);
        if( !data ) return notify_fail("我怎么不记得前世跟你有缘呢？\n");

        if( data["reborn_pass"] != pass )
                return notify_fail("这句哪里是我给过的揭语！\n");
        
        if( data["reborn_time"] > me->query("birthday") )
                return notify_fail("此人转世之时你已在世上，你又怎么可能会是他今生投胎之躯？\n");

        if( data["gender"] != me->query("gender") )
                return notify_fail("你于此人转世之前的性别不一致，你怎么可能是他呢？\n");

        if( count_gt(me->query("combat_exp"), 100000000) )
                return notify_fail("你的经验受今世影响太深，我无法帮你打开阿赖耶识。\n");

        command("say 看来你果然是前世与我有缘之人，待我将你前世记忆打开！");

        message_vision( HIY "\n佛祖说着便朝着$N" HIY "轻轻一挥手。\n\n" NOR
                        HIR "$N" HIR "突然感到头痛欲裂......\n\n" NOR, me );

        my_name = data["name"];
        my = me->query_entire_dbase();

        all_skills = copy(data["all_skills"]);
        sname = keys(all_skills);
        n = sizeof(sname);
        for( i = 0; i < n; i++ )
                me->set_skill(sname[i], all_skills[sname[i]]);

        tmp_data  = ([ "times" : 1 ]);
        tmp_data += ([ "time" : data["reborn_time"] ]);
        tmp_data += ([ "family_name" : data["family_name"] ]);
        tmp_data += ([ "id" : my_id ]);
        tmp_data += ([ "name" : my_name ]);
        my["reborn"] = tmp_data;
        my["can_perform"] = copy(data["can_perform"]);
        my["special_skill"] = copy(data["special_skill"]);
        my["str"] = copy(data["str"]);
        my["int"] = copy(data["int"]);
        my["con"] = copy(data["con"]);
        my["dex"] = copy(data["dex"]);
        my["character"] = "国士无双";
        my["welcomegift"] = 1;
                
        if( mapp(data["member"]) ) {
                if( MEMBER_D->is_member(me) ) 
                        MEMBER_D->db_pay_member(me, data["member"]["money"]); 
                else
                        MEMBER_D->db_create_member(me, data["member"]["money"]); 
                
                MEMBER_D->db_fee_member(me, data["member"]["day"]);
                MEMBER_D->db_set_member(me, "vip", data["member"]["vip"]);
        }
        id = me->query("id");                
        sum_data = data["can_summon"];
        sum = keys(sum_data);
        for( i = 0; i < sizeof(sum); i++ ) {
                if( sum[i] == "cruise ob" ) continue;                
                filename = sum_data[sum[i]] + C_FILE_EXTENSION;
                if( file_size(filename) < 0 ) continue;
                if( sscanf(filename, "/data/template/%*s") )
                        me->set("can_summon/" + sum[i], sum_data[sum[i]]);
                else {
                        if( id == my_id ) {
                                me->set("can_summon/" + sum[i], sum_data[sum[i]]);
                                continue;
                        }                        
                        content = read_file(filename);
                        content = replace_string(content, my_id, me->query("id"));
                        content = replace_string(content, my_name, me->query("name"));
                        item_filename = ITEM_DIR + id[0..0] + "/" + id +
                                        "-" + sum[i] + C_FILE_EXTENSION;
                        if( file_size(item_filename) != -1 )
                                write("已经存在原文件档案，现覆盖处理。\n");

                        assure_file(item_filename);
                        rm(item_filename);
                        if( !write_file(item_filename, content, 1) ) {
                                write("写入档案(" + filename + ")时出错，请通知巫师处理。\n");
                                return 0;
                        }

                        catch(call_other(item_filename, "???"));
                        ob = find_object(item_filename);

                        ob->receive_dbase_data(DBASE_D->query_object_data(filename));
                        ob->set("user", me->query("name") + "(" + id + ")");
#ifdef DB_SAVE
                        DATABASE_D->db_remove_item(base_name(ob));
                        DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                        me->set("can_summon/" + sum[i], base_name(ob));
                        DBASE_D->clear_object(filename);
                        rm(filename);
                        ob->save();
                }
        }
        log_file("static/reborn", sprintf("%s(%s) reborn from %s at %s.\n",
                 me->name(1), me->query("id"), my_id, ctime(time())));
        message("vision", HBRED "【转世重生】天界：据说有人已得佛祖恩典，开启了阿赖耶识。\n" NOR, users());
        me->unconcious();

        buddha->clear_reborn_data(my_id);
        buddha->save();
        return 1;
}

