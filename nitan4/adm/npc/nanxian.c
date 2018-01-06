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
        set_name("����", ({ "nan xian", "nan", "xian" }));
        set("long", @LONG
����������ɼ���뷢�԰ס�������ò���ʵ
ȴΪ����ͷ���������������кųơ�����
���󡹵����͡���Ϊ��������а������ʱ����
�����������춯�صĴ�١���ƽ��ս��������
�ڱ�������ʧ���֡�
LONG);
        set("nickname", HIW "��������" NOR);
        set("title", HIC "����̩��" NOR);
        set("gender", "����" );
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
                "name" : "����������һ�ִ��Ŷ��ѣ������к����壿",
                "����" : "�㾡���Ǹ������ļһ�������",
                "��̶" : (: ask_me1 :),
                "����" : (: ask_me1 :),
                "gift" : (: ask_me1 :),
                "��Ч����": (: ask_me2 :),
                "˫������": (: ask_me3 :),
                "����"    : (: ask_me4 :),
                "������": (: ask_me4 :),
                "��ɽ����": (: ask_me4 :),
                "�μӱ���": (: ask_me4 :),
                "������Ա": (: ask_me5 :),
                "������Ա����": (: ask_me5 :),
                "������Ա�ȼ�": (: ask_me5 :),
                "ת������" : (: ask_reborn :),
                "ת��" : (: ask_reborn :),
                "����" : (: ask_reborn :),
                "ת��" : (: ask_reborn :),
//               "����" : (: ask_buchang :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

        /*
        if (! clonep(this_object()))
        {
                move("/d/city/wumiao");
                message_vision(WHT "\nͻȻ������ǰһ��������ƺ����˸�"
                               "��Ӱ��\n" NOR, this_object());
                set("startroom", "/d/city/wumiao");
        }
        */
        set("startroom", "/d/city/wumiao");
        check_clone();
}

// ����ѯ��
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

        command("say �ߣ���֪���");
        command("exert powerup");
        command("exert sword");
        ::fight_ob(ob);
}

int accept_fight(object who)
{
        command("say û��Ȥ��");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("����밵�㣬������ǰһ��������̫�����\n");
}

mixed ask_me1()
{
        object me = this_player();
        object ob;

        if ((int) me->query("welcomegift"))
        {
                command("say �Ǻǡ���������Ĳ����ˣ��Ϸ��Ѿ������������ˣ�");
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
                CHANNEL_D->do_channel(me, "es", sprintf("����%s���չ��١���̶����61.128.162.81 : 2001��\n            ���ѵõ����͵İ����ͽ�����������ʼ������ˣ�",
                                      me->name(1)));
                */

                message_vision(HIW "$N" HIW "���һָ��ͻȻ�����һ��" HIM "��" HIY "��" HIR "ϼ" HIC "��" HIW "����$n��ת˲���ţ�\n" NOR,
                               this_object(), me);

                tell_object(me, HIG "�����͸�����һ�����gift��������� look gift ��������ʲô���\n" NOR);
                return 1;
        }
}

mixed ask_me2()
{
        int td;
        object me = this_player();

        td = time() / 86400;

        if ((int)me->query("time_reward/which_day1") == td)
                return "������Ѿ������Ч��������ʱ���ˡ�";

        if (! MEMBER_D->is_valid_member(me))
        // || (int)MEMBER_D->db_query_member(me, "endtime") < 1888888888)
                return "�㲻�ǻ�Ա����Ҫ��Ч�������������ȹ����Ա���ɡ�\n";

/*
        message("member", HIM "\n����̶��Ա��" + me->query_idname() + HIM " ��ȡ��Сʱ�ĸ�Ч����ʱ�俪ʼ��ʱ��\n" NOR,
                all_interactive(), 0);
*/

        tell_object(me, HIR "\n����ȡ��Сʱ�ĸ�Ч����ʱ�俪ʼ��ʱ������ָ��stats���Բ鿴ʣ��ʱ�䡣\n" NOR);

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
                return "������Ѿ��������е�˫�����齱��ʱ���ˡ�";

        if (! MEMBER_D->is_valid_member(me))
                return "�㲻�ǻ�Ա����Ҫ˫�����齱�������ȹ����Ա���ɡ�\n";

        /*
        t = localtime(time())[2];
        if (t >= 20 && t < 24)
                return "ÿ��20~24���Ϊ˫������ʱ�䣬����������˫������ʱ����㻹�ǹ�һ��������ɡ�\n";

        message("member", HIM "\n����̶��Ա��" + me->query_idname() + HIM " ��ȡ��Сʱ��˫������ʱ�俪ʼ��ʱ��\n" NOR,
                all_interactive(), 0);
        */

        tell_object(me, HIR "\n����ȡ��Сʱ��˫������ʱ�俪ʼ��ʱ������ָ��stats���Բ鿴ʣ��ʱ�䡣\n" NOR);

        me->set("time_reward/which_day2", td);
        me->add("time_reward/quest", 7200);
        me->add("time_reward/times", 1);
        return 1;
}

mixed ask_me4()
{
        object me = this_player();

        tell_object(me, HIY "����˵������Ȼ��Ҫ�μӱ��䣬��ô�Ϸ������һ�̣�\n" NOR);
        message_vision(HIY "ֻ����������һ�У�һ���������$N��$N�ڿշ�ȥ��\n" NOR, me);
        me->move("/d/huashan/houzhiwangyu");
        return 1;
}

mixed ask_me5()
{
        int value, trans, t;
        object me = this_player();

        t = time();
        if (! wizardp(me) && t - me->query_temp("identify_member") < 10)
                return "��ողż����������ǵȻ������ɡ�\n";

        if (! MEMBER_D->is_member(me))
                return "�㲻�ǻ�Ա����Ҫ������Ա�ȼ������ȹ����Ա���ɡ�\n";

        if (MEMBER_D->db_query_member(me, "vip") == 3)
                return "��ϲ�㣬���Ѿ��ǰ׽��Ա�ˣ�\n";

        me->set_temp("identify_member", t);

        value = MEMBER_D->db_query_member(me, "payvalue");
        trans = MEMBER_D->db_query_member(me, "transfervalue");
        value -= trans;

        if (value >= 2000)
        {
                MEMBER_D->db_set_member(me, "vip", 3);
                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ����׽��Ա�����Ա�̵깺��Ʒ���� 8 �ۣ�\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 1000)
        {
                MEMBER_D->db_set_member(me, "vip", 2);
                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ���ƽ��Ա����Ա�̵깺��Ʒ���� 8.5 �ۣ�\n\n" NOR);
                return 1;
        }
        else
        if  (value >= 500 && MEMBER_D->db_query_member(me, "vip") < 2)
        {
                MEMBER_D->db_set_member(me, "vip", 1);
                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ�������Ա���Ա�̵깺��Ʒ���� 9 �ۣ�\n\n" NOR);
                return 1;
        }
        else
        {
                if (MEMBER_D->db_query_member(me, "vip") == 2)
                        return "��Ŀǰ�Ļ�Ա�ȼ�Ϊ�ƽ��Ա��\n";

                if (MEMBER_D->db_query_member(me, "vip") == 1)
                        return "��Ŀǰ�Ļ�Ա�ȼ�Ϊ������Ա��\n";

                tell_object(me, HIY "\n��Ŀǰ�Ļ�Ա�ȼ�Ϊ��ͨ��Ա��\n" NOR);
                return 1;
        }
}

mixed ask_buchang()
{
        string id, sql;
        int    jointime, endtime, day; 
        object me = this_player();
        

        if (me->query("gifter/buchang"))
                return "���Ѿ����������,��Ҫ̫̰��Ŷ��";
        
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
                        // �Ƿ������
                        if( !me->query("reborn/times") && (endtime - jointime < 31536000 ||
                            me->query("online_time") < 259200) )
                        {
                                if( endtime > time() )
                                        day = endtime + 7948800;
                                else
                                        day = time() + 7948800;
                        } else {
                                // �Ƿ�����
                                if( endtime - jointime > 63072000 )
                                        MEMBER_D->db_pay_member(id, 50); 
                                else
                                        MEMBER_D->db_pay_member(id, 36); 
                                
                                me->set("gifter/buchang", 1);
                                me->save();
                                tell_object(me, HIY "\n����ȡ��(" HIM "�ص�����" NOR + 
                                                HIY ")��$NT�Ѿ��嵽����ʻ��ף�������߹����������죡\n" NOR);
                                return 1;
                        }
                }
                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }
        
        me->set("gifter/buchang", 1);
        me->save();
        tell_object(me, HIY "\n����ȡ��(" HIM "�ص�����" NOR + HIY ")��ף�������߹����������죡\n" NOR);    
        return 1;
}

mixed ask_reborn()
{
        object ob, who, weapon;
        string map_skill, type;

        who = this_player();

        if (who->query("reborn/times"))
        {
                message_vision("$N��$nһ���֣��������Ѿ�ת���ֻع��ˣ��ҿ��Ͳ����˰ɣ�\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("reborn_offer"))
        {
                message_vision("$N��$nŭ�����Ϸ��Ѿ�������һ��������(Contract)��Ϊ�λ������ң�\n",
                               this_object(), who);
                return 1;
        }

        if (count_lt(who->query("combat_exp"), 2000000000))
        {
                message_vision("$N��$nһ���֣��������鲻����ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("force");
        if (who->query_skill("force", 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N��$nһ���֣������ڹ�������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("dodge");
        if (who->query_skill("dodge", 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N��$nһ���֣������Ṧ������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        map_skill = who->query_skill_mapped("parry");
        if (who->query_skill("parry", 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N��$nһ���֣������мܲ�����ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        if (who->query_skill("martial-cognize", 1) < 2700)
        {
                message_vision("$N��$nһ���֣�������ѧ����������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        weapon = who->query_temp("weapon");
        if (! weapon || ! weapon->is_ultimate() ||
            who->query("id") != weapon->item_owner())
        {
                message_vision("$N��$nһ���֣����������ӵ��һ��10LV���ϱ���������ת��������\n",
                               this_object(), who);
                return 1;
        }

        type = weapon->query("skill_type");
        map_skill = who->query_skill_mapped(type);
        if (! map_skill)
        {
                message_vision("$N��$nһ���֣�����������ȼ�������װ���ı�����Ӧ�ı������ܡ�\n",
                               this_object(), who);
                return 1;
        }
                        
        if (who->query_skill(type, 1) < 2700 ||
            who->query_skill(map_skill, 1) < 2700)
        {
                message_vision("$N��$nһ���֣�����" + to_chinese(map_skill) + "������ǿ��������Ȼ��\n",
                               this_object(), who);
                return 1;
        }

        if (! ultrap(who))
        {
                message_vision("�㻹û�е�����ʦ�ľ��磬���Ǻú�ѧϰ�����ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if (! who->query("breakup"))
        {
                message_vision("$N��$nһ���֣������㻹û�д�ͨ���ζ������ء�\n",
                               this_object(), who);
                return 1;
        }

        if (! who->query("animaout"))
        {
                message_vision("$N��$nһ���֣������㻹û�д�ͨ�����������ء�\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("couple"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���ļ�ͥ����������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("bunch"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���İ�������������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("brothers"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ���Ľ����ֵ�����������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("league"))
        {
                message_vision("$N��$nһ���֣������㻹���Ⱥ����ͬ������������ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        if (who->query("private_room"))
        {
                message_vision("$N��$nһ���֣������㻹���Ȱ����ס����ٵ���ת���ɡ�\n",
                               this_object(), who);
                return 1;
        }

        message_vision(CYN "$N̾�������˼䱾�ǰ�׮ĥ����Ȼ������֮ʿ��ѯ���Ϸ�Ҳ����׾��������������°ɡ���\n" NOR,
                       this_object(), who);

        ob = new(CONTRACT);
        ob->move(who, 1);
        ob->set("bindable", 3);
        ob->set("bind_owner", who->query("id"));
        ob->set("owner", who->query("id"));
        ob->set("no_store", 1);
        ob->set("autoload", 1);
        ob->set("setdbase", 1);

        message_vision(HIC "$N�ó�һ��������(Contract)��$n��\n" NOR
                       CYN "$N������������ת����Ե����������ɽ���׼��������ǰ��̩ɽ����ɽ����ɽ����ɽ����ɽһ�аɡ���\n" NOR,
                       this_object(), who);

        message("channel:rumor", HBRED "��ת���������˼䣺" + who->query("name") + "(" + who->query("id") + ")"
                HBRED "�õ�����������ʼǰ�������׼�������ת����Ե��\n\n" NOR, users());

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
                return notify_fail(CYN "����ҡҡͷ�����������׼�δ�ɣ�Ϊʱ���硣��\n" NOR);

        ob->delete("bindable");
        ob->delete("bind_owner");
        call_out("to_return", 1, who, ob);
        return 1;
}

int to_return(object who, object ob)
{
        if (! ob || ! who) return 0;

        message_vision(CYN "$N���˵�ͷ�����������������ˣ������߹�����ɽ���ǰ�������ĥ������������Ǹ�Ѫָӡ����\n" NOR
                       HIC "$n����$Nָʾ��ҧ��Ĵָ�����������ϸ���Ѫָӡ��\n" NOR
                       HIM "ֻ��������(Contract)ͻ���Ϲ⣬Ѫָӡ��ƾ���ֳ���$n�����֡�\n" NOR
                       CYN "$N����������ȥ����֮��Ѱ�����ؾ�����������Ͷ�����У����ɻ������������������֮�ʸ�·���ն����С�ġ���\n" NOR,
                       this_object(), who);

        ob->set("name", MAG "������" NOR);
        ob->set_name(MAG "������" NOR, ({ "contract" }));
        ob->set("long", MAG "����һ��������������Ѫָӡ����" + who->query_idname() + "�����֡�\n" NOR);
        ob->move(who, 1);
        ob->set("bindable", 3);
        ob->set("bind_owner", who->query("id"));
        who->set("reborn_offer", "finish");
        tell_object(who, HIC "���ͽ����Ϲ��������(Contract)�����㡣\n" NOR);

        return 1;
}

void unconcious()
{
        die();
}
