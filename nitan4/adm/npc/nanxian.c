// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
inherit F_NOCLONE;

#define CONTRACT        "/d/reborn/obj/contract"

mixed ask_me1();
mixed ask_me2();
mixed ask_me3();
mixed ask_me4();
mixed ask_me5();
mixed ask_reborn();
mixed ask_buchang();

void create()
{
        set_name("南贤", ({ "nan xian", "nan", "xian" }));
        set("long", @LONG
此人衣着青杉，须发皆白。看似其貌不扬，实
却为世上头号人物。这便是武林中号称「南贤
北丑」的南贤。其为人亦正亦邪，年轻时曾干
下了无数轰天动地的大举。生平决战无数，仅
在北丑手下失过手。
LONG);
        set("nickname", HIW "天下至贤" NOR);
        set("title", HIC "武林泰斗" NOR);
        set("gender", "男性" );
        set("age", 74);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);
        set("level", 100);

        /*
        set_skill("force", 500);
        set_skill("huntian-baojian", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("lunhui-jian", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("buddhism", 500);
        set_skill("taoism", 500);
        set_skill("literate", 500);
        set_skill("martial-cognize", 500);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("unarmed", "huntian-baojian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("sword", "lunhui-jian");

        prepare_skill("unarmed", "huntian-baojian");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: perform_action, "sword.hui" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "sword" :),
                (: exert_function, "recover" :),
                (: exert_function, "regenerate" :),
                (: exert_function, "powerup" :),
        }));
        */

        set("inquiry", ([
                "name" : "姓名不过是一种代号而已，问它有何意义？",
                "北丑" : "你尽提那个龌龊的家伙做甚？",
                "泥潭" : (: ask_me1 :),
                "礼物" : (: ask_me1 :),
                "gift" : (: ask_me1 :),
                "高效练功": (: ask_me2 :),
                "双倍经验": (: ask_me3 :),
                "比武"    : (: ask_me4 :),
                "比武大会": (: ask_me4 :),
                "华山绝顶": (: ask_me4 :),
                "参加比武": (: ask_me4 :),
                "鉴定会员": (: ask_me5 :),
                "鉴定会员级别": (: ask_me5 :),
                "鉴定会员等级": (: ask_me5 :),
                "转世重生" : (: ask_reborn :),
                "转世" : (: ask_reborn :),
                "重生" : (: ask_reborn :),
                "转生" : (: ask_reborn :),
//               "补偿" : (: ask_buchang :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

        /*
        if (! clonep(this_object()))
        {
                move("/d/city/wumiao");
                message_vision(WHT "\n突然间你眼前一花，身后似乎多了个"
                               "人影。\n" NOR, this_object());
                set("startroom", "/d/city/wumiao");
        }
        */
        set("startroom", "/d/city/wumiao");
        check_clone();
}

// 接受询问
/*
mixed accept_ask(object who, string topic)
{
        return ULTRA_QUEST_D->accept_ask(this_object(), who, topic);
}
*/

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        command("say 哼！不知死活。");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say 没兴趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你刚想暗算，可是眼前一花，看不太清楚。\n");
}

mixed ask_me1()
{
        object me = this_player();
        object ob;

        if ((int) me->query("welcomegift"))
        {
                command("say 呵呵～这就是您的不是了！老夫已经给过您礼物了！");
                return 1;
        }
        else
        {
                me->set("welcomegift", 1);
                me->add("food", 5000);
                me->add("water", 10000);
                me->add("score", 1000);
                me->add("weiwang", 100);
                me->set("tianfu", 4);
                // me->add("potential", 1000);
                me->add_skill("training", 30);

                ob = new("/adm/npc/obj/gift");
                ob->move(me, 1);
                /*
                ob->set("bindable", 3);
                ob->set("bind_owner", me->query("id"));
                ob->set("autoload", 1);
                ob->set("setdbase", 1);
                */

                // ob->move(this_object());
                // command("give gift to " + me->query("id"));

                /*
                CHANNEL_D->do_channel(me, "es", sprintf("在下%s今日光临〖泥潭〗（61.128.162.81 : 2001）\n            现已得到南贤的帮助和奖励！即日起开始玩泥巴了！",
                                      me->name(1)));
                */

                message_vision(HIW "$N" HIW "凌空一指，突然天空中一道" HIM "七" HIY "彩" HIR "霞" HIC "光" HIW "笼罩$n，转瞬即逝！\n" NOR,
                               this_object(), me);

                tell_object(me, HIG "南贤送给了你一个礼物（gift），你可以 look gift 来看看是什么礼物。\n" NOR);
                return 1;
        }
}

mixed ask_me2()
{
        int td;
        object me = this_player();

        td = time() / 86400;

        if ((int)me->query("time_reward/which_day1") == td)
                return "你今天已经领过高效练功奖励时间了。";

        if (! MEMBER_D->is_valid_member(me))
        // || (int)MEMBER_D->db_query_member(me, "endtime") < 1888888888)
                return "你不是会员，想要高效练功奖励还是先购买会员卡吧。\n";

/*
        message("member", HIM "\n【泥潭会员】" + me->query_idname() + HIM " 领取二小时的高效练功时间开始计时。\n" NOR,
                all_interactive(), 0);
*/

        tell_object(me, HIR "\n你领取二小时的高效练功时间开始计时，输入指令stats可以查看剩余时间。\n" NOR);

        me->set("time_reward/study", 7200);
        me->set("time_reward/which_day1", td);
        return 1;
}

mixed ask_me3()
{
        // int t;
        int td;
        object me = this_player();

        td = time() / 86400;

        if ((int)me->query("time_reward/which_day2") != td)
                me->delete("time_reward/times");

        if ((int)me->query("time_reward/which_day2") == td &&
            (int)me->query("time_reward/times") >= 3)
                return "你今天已经领完所有的双倍经验奖励时间了。";

        if (! MEMBER_D->is_valid_member(me))
                return "你不是会员，想要双倍经验奖励还是先购买会员卡吧。\n";

        /*
        t = localtime(time())[2];
        if (t >= 20 && t < 24)
                return "每天20~24点均为双倍经验时间，现在正处于双倍经验时间段你还是过一会再来领吧。\n";

        message("member", HIM "\n【泥潭会员】" + me->query_idname() + HIM " 领取二小时的双倍奖励时间开始计时。\n" NOR,
                all_interactive(), 0);
        */

        tell_object(me, HIR "\n你领取二小时的双倍经验时间开始计时，输入指令stats可以查看剩余时间。\n" NOR);

        me->set("time_reward/which_day2", td);
        me->add("time_reward/quest", 7200);
        me->add("time_reward/times", 1);
        return 1;
}

mixed ask_me4()
{
        object me = this_player();

        tell_object(me, HIY "南贤说道：既然你要参加比武，那么老夫就送你一程！\n" NOR);
        message_vision(HIY "只见南贤伸手一招，一道红光照向$N，$N腾空飞去！\n" NOR, me);
        me->move("/d/huashan/houzhiwangyu");
        return 1;
}

mixed ask_me5()
{
        int value, trans, t;
        object me = this_player();

        t = time();
        if (! wizardp(me) && t - me->query_temp("identify_member") < 10)
                return "你刚刚才鉴定过，还是等会再来吧。\n";

        if (! MEMBER_D->is_member(me))
                return "你不是会员，想要鉴定会员等级还是先购买会员卡吧。\n";

        if (MEMBER_D->db_query_member(me, "vip") == 3)
                return "恭喜你，你已经是白金会员了！\n";

        me->set_temp("identify_member", t);

        value = MEMBER_D->db_query_member(me, "payvalue");
        trans = MEMBER_D->db_query_member(me, "transfervalue");
        value -= trans;

        if (value >= 2000)
        {
                MEMBER_D->db_set_member(me, "vip", 3);
                tell_object(me, HIY "\n你目前的会员等级为★★★白金会员★★★，会员商店购物品享受 8 折！\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 1000)
        {
                MEMBER_D->db_set_member(me, "vip", 2);
                tell_object(me, HIY "\n你目前的会员等级为★★黄金会员★★，会员商店购物品享受 8.5 折！\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 500 && MEMBER_D->db_query_member(me, "vip") < 2)
        {
                MEMBER_D->db_set_member(me, "vip", 1);
                tell_object(me, HIY "\n你目前的会员等级为★白银会员★，会员商店购物品享受 9 折！\n\n" NOR);
                return 1;
        }
        else
        {
                if (MEMBER_D->db_query_member(me, "vip") == 2)
                        return "你目前的会员等级为黄金会员！\n";

                if (MEMBER_D->db_query_member(me, "vip") == 1)
                        return "你目前的会员等级为白银会员！\n";

                tell_object(me, HIY "\n你目前的会员等级为普通会员。\n" NOR);
                return 1;
        }
}

mixed ask_buchang()
{
        string id, sql;
        int    jointime, endtime, day; 
        object me = this_player();
        

        if (me->query("gifter/buchang"))
                return "你已经领过补偿了,不要太贪心哦。";
        
        id = me->query("id");
        
        if (! MEMBER_D->is_member(id))
        {      
                day = time() + 7948800;
                sql = sprintf("INSERT INTO %s SET id = \"%s\", jointime = %d, endtime = %d", 
                              "members", id, time(), day);
                DATABASE_D->db_query(sql);
        } else
        {
                jointime = (int)MEMBER_D->db_query_member(id, "jointime");
                if (jointime < 1) jointime = time();
                
                endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
                if (endtime < 1) 
                        day = time() + 7948800;
                else
                {
                        // 是否是年度
                        if( !me->query("reborn/times") && (endtime - jointime < 31536000 ||
                            me->query("online_time") < 259200) )
                        {
                                if( endtime > time() )
                                        day = endtime + 7948800;
                                else
                                        day = time() + 7948800;
                        } else {
                                // 是否终身
                                if( endtime - jointime > 63072000 )
                                        MEMBER_D->db_pay_member(id, 50); 
                                else
                                        MEMBER_D->db_pay_member(id, 36); 
                                
                                me->set("gifter/buchang", 1);
                                me->save();
                                tell_object(me, HIY "\n你领取了(" HIM "回档补偿" NOR + 
                                                HIY ")，$NT已经冲到你的帐户里，祝你在王者归来里玩的愉快！\n" NOR);
                                return 1;
                        }
                }
                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }
        
        me->set("gifter/buchang", 1);
        me->save();
        tell_object(me, HIY "\n你领取了(" HIM "回档补偿" NOR + HIY ")，祝你在王者归来里玩的愉快！\n" NOR);    
        return 1;
}

mixed ask_reborn()
{
        object ob, who, weapon;
        string map_skill, type;

        who = this_player();

        if (who->query("reborn/times"))
        {
                message_vision("$N对$n一拱手，道：你已经转世轮回过了，我看就不用了吧！\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("reborn_offer"))
        {
                message_vision("$N对$n怒道：老夫已经给过你一份阎王契(Contract)，为何还来找我！\n",
                               this_object(), who);
                return 1;
        }

        if (count_lt(who->query("combat_exp"), 2000000000))
        {
                message_vision("$N对$n一拱手，道：经验不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("force");
        if (who->query_skill("force", 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N对$n一拱手，道：内功不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("dodge");
        if (who->query_skill("dodge", 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N对$n一拱手，道：轻功不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("parry");
        if (who->query_skill("parry", 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N对$n一拱手，道：招架不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query_skill("martial-cognize", 1) < 2700)
        {
                message_vision("$N对$n一拱手，道：武学修养不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        weapon = who->query_temp("weapon");
        if (! weapon || ! weapon->is_ultimate() ||
            who->query("id") != weapon->item_owner())
        {
                message_vision("$N对$n一拱手，道：你必须拥有一把10LV以上兵器，才能转世重生。\n",
                               this_object(), who);
                return 1;
        }

        type = weapon->query("skill_type");
        map_skill = who->query_skill_mapped(type);
        if (! map_skill)
        {
                message_vision("$N对$n一拱手，道：你必须先激发和你装备的兵器对应的兵器技能。\n",
                               this_object(), who);
                return 1;
        }
                        
        if (who->query_skill(type, 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N对$n一拱手，道：" + to_chinese(map_skill) + "不够，强求亦是枉然。\n",
                               this_object(), who);
                return 1;
        }

        if (! ultrap(who))
        {
                message_vision("你还没有到大宗师的境界，还是好好学习锻炼吧。\n",
                               this_object(), who);
                return 1;
        }

        if (! who->query("breakup"))
        {
                message_vision("$N对$n一拱手，道：你还没有打通过任督二脉呢。\n",
                               this_object(), who);
                return 1;
        }

        if (! who->query("animaout"))
        {
                message_vision("$N对$n一拱手，道：你还没有打通过生死玄关呢。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("couple"))
        {
                message_vision("$N对$n一拱手，道：你还是先和你的家庭做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("bunch"))
        {
                message_vision("$N对$n一拱手，道：你还是先和你的帮派做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("brothers"))
        {
                message_vision("$N对$n一拱手，道：你还是先和你的结义兄弟做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("league"))
        {
                message_vision("$N对$n一拱手，道：你还是先和你的同盟做个交代再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("private_room"))
        {
                message_vision("$N对$n一拱手，道：你还是先把你的住房拆毁掉再转世吧。\n",
                               this_object(), who);
                return 1;
        }

        message_vision(CYN "$N叹道：「人间本是百桩磨，既然是有心之士相询，老夫也不藏拙，这物事你便收下吧。」\n" NOR,
                       this_object(), who);

        ob = new(CONTRACT);
        ob->move(who, 1);
        ob->set("bindable", 3);
        ob->set("bind_owner", who->query("id"));
        ob->set("owner", who->query("id"));
        ob->set("no_store", 1);
        ob->set("autoload", 1);
        ob->set("setdbase", 1);

        message_vision(HIC "$N拿出一份阎王契(Contract)给$n。\n" NOR
                       CYN "$N续道：「欲成转世奇缘，需向五岳山君献祭，你这便前往泰山、华山、衡山、恒山与嵩山一行吧。」\n" NOR,
                       this_object(), who);

        message("channel:rumor", HBRED "【转世重生】人间：" + who->query("name") + "(" + who->query("id") + ")"
                HBRED "拿到阎王契，开始前往五岳献祭，欲成转世奇缘！\n\n" NOR, users());

        who->set("reborn_offer", "start");

        return 1;
}

int accept_object(object who, object ob)
{
        // return ULTRA_QUEST_D->accept_object(this_object(), who, ob);

        if (base_name(ob) != CONTRACT ||
            ob->query("owner") != who->query("id"))
                return 0;

        if (sizeof(ob->query("offer")) < 5)
                return notify_fail(CYN "南贤摇摇头道：「五岳献祭未成，为时尚早。」\n" NOR);

        ob->delete("bindable");
        ob->delete("bind_owner");
        call_out("to_return", 1, who, ob);
        return 1;
}

int to_return(object who, object ob)
{
        if (! ob || ! who) return 0;

        message_vision(CYN "$N点了点头道：「果真是有心人，竟能捱过五岳山君那般挑剔折磨，来，在这里盖个血指印。」\n" NOR
                       HIC "$n依从$N指示，咬破拇指，在阎王契上盖上血指印。\n" NOR
                       HIM "只见阎王契(Contract)突生紫光，血指印旁凭空现出了$n的名字。\n" NOR
                       CYN "$N续道：「速去昆仑之巅寻那昆仑镜，将阎王契投入其中，方可获得肉身入地狱面见阎王之资格。路程险恶，务必小心。」\n" NOR,
                       this_object(), who);

        ob->set("name", MAG "阎王契" NOR);
        ob->set_name(MAG "阎王契" NOR, ({ "contract" }));
        ob->set("long", MAG "这是一份阎王契，上面血指印旁有" + who->query_idname() + "的名字。\n" NOR);
        ob->move(who, 1);
        ob->set("bindable", 3);
        ob->set("bind_owner", who->query("id"));
        who->set("reborn_offer", "finish");
        tell_object(who, HIC "南贤将泛紫光的阎王契(Contract)还给你。\n" NOR);

        return 1;
}

void unconcious()
{
        die();
}
