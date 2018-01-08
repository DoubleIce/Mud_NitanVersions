// dugu.c �������

#include <ansi.h>

inherit NPC;
inherit F_MASTER;
inherit F_NOCLONE;

#define ULTRA_OPINION   "��ʦ"
#define OPINION_TYPE    HIY "��������" NOR 
#define MY_OPINION      "weapon"

#define QUESTGOODS_D(x) ("/quest/questdg/quest/questgoods" + x)
#define QUESTDG_D(x)    ("/quest/questdg/quest/questdg" + x)
#define DGMSG_D         ("/quest/questdg/dugu-msg")
#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

mixed ask_opinion();
int give_quest();
int give_up();
void npc_dest(object npc);
void destory(object ob);
string time_period(int timep);
mixed ask_maze(); 

string  *my_opinions = ({ "sword", "blade", "staff", "hammer",
                          "club", "whip",  "dagger", });

string *dg_msg = ({
        "�������Ц�Ǻǵ�˵����",
        "��������������ŷ���������",
        "������ܵ�ͷ�����룬˵������",
        "������������ڴ���˵������",
        "�������΢Ц�ŵ�����",
});

string* qin_msg1 = ({
        "���������ǵ����ѣ�����name����Ӱ������̬������������Ҳ�Ϳ����ˣ�",
        "����˵name����ķ�ֳ��Ӱ���˵��ص���̬���������ǲ�Ӧ�����ɱ���",
        "�ѵ�nameҲ�����������鷳������ϡ�棬�ҵ����뿴������",
        "������Ļ�԰���źܶ�Ķ������û��name��",
        "�ڿ��е�ʱ�򣬿�������������ܹ�����������name��ʵͦ�ɰ��ģ�",
        "�Ϻ�������һ����ϲ��������ˣ�������name�������͸�����������ò�����",
        "�����ϴ��ɱɱ�ģ��ٲ�����nameҲ�����޹����ۣ������ı�������",
});

string* qin_msg2 = ({
        "��ȥ���������������ɡ���",
        "ȥ�ҵ�����������������",
        "���ܰ�������������ô����",
        "�������һ��ȥ���Ұ��������ɡ���",
        "����Ū�����ҡ���",
});

// ��ͷ�ļ�����������Ƕ��
#include <ultra.h>

void check_weapon();

void create()
{
        set_name("�������", ({ "dugu qiubai", "dugu" }) );
        set("title", HIC "����ʦ" NOR);
        set("gender", "����");
        set("age", 48);
        set("long",
"����һ������ͨͨ�����ߣ�һϮ�ֲ����ѣ�\n"
"���һ�ư��룬������͡�Ŀ��ת��֮�䣬\n"
"������¶��һ˿����֮����\n");      
        set("attitude", "peaceful");
        set("no_get", 1);
        set("str", 38);
        set("int", 39);
        set("con", 32);
        set("dex", 33);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("neili", 30000);
        set("max_neili", 30000);
        set("jiali", 100);

        set("combat_exp", 50000000);

        set("inquiry", ([
                "���¾Ž�" : "�Ұ������书�ı仯����ھŽ�֮�У��㲻���ǽ���������\n"
                             "�������ƾ��޷��������а��\n"
                             "���¾Ž������ľ���֮���������佣�У�������" HIY "����" NOR + CYN "��",
                "����"     : "���������Σ��������������Ứ�ѱ��������ڻ�ɽһɽ��\n"
                             HIY"����" NOR + CYN"�в�������¾Ž�֮���⣬�������¼�ڡ�" HIY "���¾Ž���"
                             "��" NOR + CYN"��" NOR + CYN "�ڡ�\n" NOR,
                "����"     : "�����������ɽ���ͻᷢ��һ���ͱڣ��ҽ��б���������\n"
                             "ɽ���ڣ�������ֽ�����Ƴ����Ѳ�ͬ��������ס��ÿ����"
                             "������һ������\n�Ļ��أ����ز���������ͬ��ʯ���ڣ����"
                             "������" HIY "��" NOR + CYN "�򿪷��ܽ�����ҡ�\n" NOR,
                "��"       : "�����վã������ķ������Ѳ��ǵ��ˡ���ֻ�ǵ����ʯ��\n"
                             "�ϵ����ѻ�涼��ȼ�ˣ�ʯ���ϵ���Ҳ�Ϳ��ˡ�\n",
                "����ʤ����" : "�Ǿ��Ƕ��¾Ž�����߾��磡\n", 
                "���¾Ž��б�" : "����������������ҵ��ǿ��԰Ѷ��¾Ž��еľ���֮����\n�����㡣\n", 
                "����"     : (: ask_opinion :),
                "opinion"  : (: ask_opinion :),
                "��ѧ����" : "��ѧ����(martial-cognize)���������壬��ν����һͨͨ��ͨ��",
                "����"     : "�������̾�˿�������������񽭺���Σ���ķ�����������ʿ���кܶ�����Ҫȥ��������\n",
                "maze"     : (: ask_maze :), 
                "�Թ�"     : (: ask_maze :),                 
        ]));

        set_skill("unarmed", 500);
        set_skill("sword", 500);
        set_skill("blade", 500);
        set_skill("staff", 500);
        set_skill("hammer", 500);
        set_skill("club", 500);
        set_skill("whip", 500);
        set_skill("dagger", 500);
        set_skill("throwing", 500);
        set_skill("parry", 500);
        set_skill("dodge", 500);
        set_skill("force", 500);
        set_skill("never-defeated", 500);
        set_skill("martial-cognize", 500);

        map_skill("sword", "never-defeated");
        map_skill("blade", "never-defeated");
        map_skill("staff", "never-defeated");
        map_skill("hammer", "never-defeated");
        map_skill("club", "never-defeated");
        map_skill("whip", "never-defeated");
        map_skill("dagger", "never-defeated");
        map_skill("parry", "never-defeated");
        map_skill("dodge", "never-defeated");
        map_skill("force", "never-defeated");

        set("opinion/ultra",  1);
        set("opinion/master", 1);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: check_weapon :),
        }) );

        set("rank_info/self", "����");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/zhujian")->wield();

        set("startroom", "/d/huashan/shandong");
        check_clone();
}

void init()
{
        object me;

        if (! interactive(me = this_player()))
                return;

        me->delete_temp("want_opinion");
        if (ultrap(me))
        {
                message_vision(CYN "$N" CYN "΢΢һЦ����$n"
                               CYN "���˵�ͷ��\n" NOR,
                               this_object(), me);
        }

        add_action("give_quest", "quest");
        add_action("give_up", "giveup");        
}

mixed ask_maze()
{
        object me;
        object ob;
        mapping quest;
        mapping maze;
        
        me = this_player();
        ob = this_object();
        quest = me->query("quest_dg");

        if (!quest)
                return "�㲢û�н��ҵ������������Թ��������ʲô��";
        
        if ( undefinedp(quest["maze"]) )
                return "��ӵ�������Թ��޹ذ�����ʲô�����أ�";
        
        /* ȡ���ϵ��Թ�
        maze = MAZE_D->query_maze(quest["maze"]);
        if ( !mapp(maze) || undefinedp(maze["entry"]) )
        */        
        if( !(find_object("/f/ultra/"+me->query("id")+"/maze/exit")) )
                return "������������޷���������Ǹ��Թ���˵�Ѿ���ʧ�ˡ�";
        
        message_vision("$N��$n��ͷ��������Ȼ���Ѿ�׼����Ҫȥ����Ǿ�ף��һ��˳������\n", ob, me);
        FUBEN_D->enter_fuben(me, "ultra");

        return 1;
}

void check_weapon()
{
        if (objectp(query_temp("weapon")))
                return;

        message_vision(CYN "$N" CYN "��̾һ����������$N"
                       CYN "��������������δ����֣��գ���"
                       "�ˣ���ȥҲ��\n" NOR, this_object());
        destruct(this_object());
}

mixed ask_opinion()
{
        object me;
        object ob;

        me = this_player();

        if (count_lt(me->query("combat_exp"), 200000))
                return "�Ǻǣ�������书��̸ʲô���ۣ�";

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
                return "������������������Ϊ�Ѿ��Ƶ�������ʦ�ˣ�����Ҫ��Ҫ�����У�";

        if (is_fighting(me))
                return "��������ʲô������Ӯ���ң����Լ����Լ����۰ɣ�";

        if (me->is_fighting())
                return "��Ȼ���ɣ����Ҹ������ǡ�";

        if (objectp(ob = query_temp("opinion")))
        {
                if (ob == me)
                {
                        command("say ����ʲô������Ҫ���ҡ�");
                        return 1;
                }

                message_vision(CYN "$N" CYN "���ڳ�˼��û�лش�$n"
                               CYN "��ֻ�ǰ��˰��֡�\n" NOR,
                               this_object(), me);
                return 1;
        }

        switch(me->query_temp("want_opinion/dugu"))
        {
        case 0:
                command("look " + me->query("id"));
                command("say �ðɣ����ñ�������һ�У��ҿ������ˮƽ��Ρ�");
                break;
        case 1:
                command("say ����˵������һ���ҿ�����");
                break;
        case 2:
                message_vision(CYN "$N" CYN "��ü��$n" CYN
                               "�������ҿ��������ǹ����µġ���\n" NOR,
                               this_object(), me);
                break;
        case 3:
                command("say ���ұ�������죡");
                return 1;
        }

        me->add_temp("want_opinion/dugu", 1);
        return 1;
}

int calc_level(object me, string skill)
{
        int lvl;
        string sp;
        mapping action;

        lvl = me->query_skill(skill, 1) / 2;
        sp = me->query_skill_mapped(skill);
        if (! sp) return lvl;

        lvl += me->query_skill(sp, 1);
        action = SKILL_D(sp)->query_action(me, me->query_temp("weapon")); 
        if (mapp(action))
                lvl += (action["force"] + action["parry"] + action["dodge"] - 250) / 10;
        return lvl;
}

void do_congration(object me)
{
        command("chat ��λ" + RANK_D->query_respect(me) +
                "��Ҫ�������أ���֪ǿ�и���ǿ���֡�");
}

int accept_hit(object me)
{
        if (me->query_temp("want_hit/dugu") >= 2)
        {
                command("heng");
                command("say �²���������Ҫ�����Ǿ�ȥ���ɣ�");
                kill_ob(me);
                return 1;
        }

        command("shake");
        command("say ��λ" + RANK_D->query_respect(me) + "��"
                "����֮���м�óȻ���ơ�");
        me->add_temp("want_hit/dugu", 1);
        return 0;
}

int accept_fight(object me)
{
        object weapon;

        if (me->query("opinion/" MY_OPINION) == ULTRA_OPINION)
        {
                message_vision(CYN "$N" CYN "��ϲ����$n" CYN
                               "�������ܺã������һ�û�к���"
                               "ʦ���ֹ����У����ɣ���\n" NOR,
                               this_object(), me);
                return 1;
        }

        if (! me->query_temp("want_opinion/dugu"))
        {
                command("say ƽ���޹ʶ�ʲô�֣�");
                return 0;
        }

        if (! objectp(weapon = me->query_temp("weapon")))
        {
                command("say û�����㶯ʲô�֣�");
                return 0;
        }

        if (me->query("qi") * 100 / me->query("max_qi") < 80||
            me->query("jing") * 100 / me->query("max_jing") < 80)
        {
                command("say ������״̬���ѣ�����Ϣ������˵�ɣ�");
                return 0;
        }

        command("nod");
        COMBAT_D->do_attack(me, this_object(), weapon);
        COMBAT_D->do_attack(this_object(), me, query_temp("weapon"));

        if (me->query("qi") <= 0)
        {
                message_vision(CYN "\n$N" CYN "ҡҡͷ��$n" CYN
                               "�����������ڵ��书�����Զ����"
                               "��һ�ж��Ӳ�ס����\n" NOR,
                               this_object(), me);
                return notify_fail("����Ҫ�úõ����������ˡ�\n");
        }

        call_out("check_opinion", 2, me);
        set_temp("opinion", me);
        me->delete_temp("want_opinion");
        message_vision(CYN "\n$N" CYN "���ͷ���������ˣ����ȵ�"
                       "������������롣��\n" NOR,
                       this_object(), me);
        return notify_fail("���������ļ������õ�һ�����\n");
}

int accept_kill(object me)
{
        if (count_lt(me->query("combat_exp"), 500000000))
        {
                message_vision(CYN "$N" CYN "��ŭ����������С����"
                               "ʲô�ң����ҹ�����˵��һ�ư�$n" CYN
                               "�����ڵء�\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
        command("sigh");
        command("say �ܺã����껹��û������ʲô�Һ��ҽ����ĸ��֣�");
        return 1;
}

int recognize_apprentice(object me, string skill)
{
        if (me->query("character") != "������" &&
            me->query("character") != "��ʿ��˫")
        {
                command("say �ҿ�����Ը񲻹�������������"
                        "����ѧϰ�书���������˰ɣ�");
                return -1;
        }

        if (skill == "martial-cognize")
                return 1;

        if (! ultrap(me))
        {
                command("say ��ѧ�ҵĲ����񹦣��㻹�����ʸ�"
                        "������˴���ʦ��˵�ɣ�");
                return -1;
        }

        if (me->query_skill(skill, 1) >= 180)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if (skill != "never-defeated")
                return 1;

        if (me->query_temp("can_learn/dugu/never-defeated"))
                return 1;

        me->set_temp("can_learn/dugu/never-defeated", 1);
        command("nod");
        command("say �ҿ��Խ����Ҷ�����������Ĳ����񹦣�����"
                "���ܲ���ѧ����Ҫ����Ļ�Ե�ˣ�");
        return 1;
}

void unconcious()
{
        /*
        message("vision", "\n"HIR + name() + "��ɫһ�䣬����һ����"
                "Ѫ������һ�������Ų�����\n\n" NOR, environment());
        command("chat �գ��գ��գ�����ȥҲ��");
        destruct(this_object());
        */
        recover();
        return;
}

void die()
{
        /*
        message("vision", "\n"HIR + name() + "���һ����������һ����"
                "Ѫ������һ�����ʹ˲�����\n\n" NOR, environment());
        command("chat ����ȥҲ��");
        destruct(this_object());
        */
        recover();
        return;
}

int give_quest()
{
        mapping questtemp, questgoods, questdg;
        mapping skills, robot_quest;
        string msg, dest, error, dgmsg, place;
        object ob, npc, thing;
        int time, bonus, level, i, lev, lev1;
        mixed exp;
        int all_lvl, lvl;
        object maze_target;      
        object maze_object;  
        
        ob = this_player();
        exp = ob->query("combat_exp");

        if ((ob->query("character") != "��������") && 
            (ob->query("character") != "��ʿ��˫") &&
            (ob->query("character") != "������"))  
        {
                write("������ܿ�����һ�ۣ��������㱾��ɱ��̫�أ����ҵ��ദ�վñ�Ȼ����룬�㻹����������ȥ�ɣ���\n");
                return 1;
        }
        /*
        if (ob->query("shen") < 0)  
        {
                write("������ܶ����������������ͬ������Ϊı���㻹�����գ���\n");
                return 1;
        }
        */
        if (count_lt(exp, 500000))
        {
                write("������ܿ��˿��㣬�ḧ���룬�����������ն��㻹�������û������ɡ���\n");
                return 1;
        }
 
        if (mapp(ob->query("quest_dg")))
        {
                write("���������������ļ�򣬺Ǻ�Ц��������Ҫ�����Ƚ���ͷ��������˵����\n");
                return 1;
        }

        if (mapp(ob->query("quest_hs")))
        {
                write("���������������ļ�򣬺Ǻ�Ц�������������ϼһ���������ˣ���ȥ������ɰɣ���\n");
                return 1;
        }

   
        if (! wizardp(ob) && (time()-ob->query("questdg_giveup_time")) < 30)
        {
                write("��Ҫ������һ���\n");
                return 1;
        }

        if (ob->query("questdg_times") < 3
        ||  (ob->query("questdg_times") > 5 && random(20) == 5))
        {
                X_QuestD->query_quest(ob, this_object());
                return 1;
        }

        if (random(4) + 1)
        {
                // ���¸�����
                if (count_le(exp, 600000))         level = 0;
                else if (count_le(exp, 900000))    level = 1;
				else if (count_le(exp, 1200000))   level = 2;
				else if (count_le(exp, 1800000))   level = 3;
				else if (count_le(exp, 2500000))   level = 4-random(3);
				else if (count_le(exp, 3200000))   level = 5-random(3);
				else if (count_le(exp, 4000000))   level = 6-random(3);
                else
                {
                        if (random(20) == 0 || (count_gt(exp, 10000000) && random(10) == 0))
                                level = 8;
                        else level = 7 - random(3);
                }
                if (level != 8)
                {
                        if (count_gt(ob->query("combat_exp"), 4000000))
                        {
                                all_lvl = 0;
                                lvl = random(28) + 1;
                                for (i = 1;i < 8;i ++)
                                {
                                        all_lvl += i;
                                        if (lvl > all_lvl - i && lvl <= all_lvl)
                                        {
                                                lvl = i;
                                                break;
                                        }
                                }
                        } else lvl = level;
                        while(1)
                        {                               
                                questtemp = QUESTDG_D(lvl)->query_questdg(ob);
                                if (questtemp["type"] == "ɱ" || questtemp["type"] == "��")
                                {
                                    if (! get_object(questtemp["object"])->is_master())
                                        break;
                                } else
                                        break;
                        }
                } 
                if (level == 8)
                {
                        npc = new(CLASS_D("generate") + "/player_npc.c");
                        FUBEN_D->clear_fuben("ultra", ob->query("id"));
                        maze_object = get_object("/f/ultra/"+ob->query("id")+"/maze");
                        maze_object->set_maze_boss(npc);
                        //maze_target = MAZE_D->create_maze(npc);
                        maze_target = get_object("/f/ultra/"+ob->query("id")+"/maze/exit");
                        npc->move(maze_target);
                        /*
                        NPC_D->place_npc(npc, count_lt(ob->query("combat_exp"), 500000)  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                              count_lt(ob->query("combat_exp"), 800000) ? ({ "����һ��", "����ɽ", "����" }) : ({"����һ��", "����"}));
                        */
                        npc->set_from_me(ob, 1);
                        npc->add_temp("apply/attack", npc->query_skill("force") / 3);
                        npc->add_temp("apply/dodge", npc->query_skill("force") / 3);
                        npc->add_temp("apply/parry", npc->query_skill("force") / 3);
                        npc->add_temp("apply/damage", 200 + random(100));
                        npc->add_temp("apply/unarmed_damage", 200 + random(100));
                        npc->add_temp("apply/armor", 200 + random(300));
                        npc->set_temp("quester", ob->query("id"));
                        npc->set("auto_perform",1);
                        /*
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                        NPC_D->random_move(npc);
                      
                        place = npc->query("place");
                        */
                        npc->set("shen", - 20000);
                        /*
                        msg = "���������ɫ���ص�����" + npc->name(1) +
                              "��Ȼ�����ֽ���������ȥ������һ����\n���˿��ܻ���" + place + 
                              "���������˾��Ҳ����ˡ���\n",
                        */
                        msg = "���������ɫ���ص�����"+npc->name(1)+
                              "��Ȼ�����ֽ���������ȥ������һ����\n����ϲ�������Թ�(maze)�У����˾��Ҳ����ˡ���\n",

                        questtemp = ([
                                //"maze" : maze_target->query("maze/mazename"),
                                "maze" : maze_object,
                                "name" : npc->name(1),
                                "id"   : npc->query("id"),
                                "bonus": (200+random(51)),
                                "type" : "ɱ",
                                "level" : level,
                                //"chinese_w" : place,
                                //"where" : npc->query("startroom"),
                                "where": maze_target,
                                "dgmsg" : msg,
		                "object" : base_name(npc),
                        ]);
                        tell_object(ob, questtemp["dgmsg"] + "\n");
                        ob->set("quest_dg", questtemp);

                        return 1;
                }
                else
                {
                        switch(questtemp["type"])
                        {
                        case "ɱ":
                                if (questtemp["object"]->query("race") != "����")
                                {
                                        questtemp["type"] = "��";
                                        msg = dg_msg[random(sizeof(dg_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",questtemp["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                                        break;
                                }
                                if(undefinedp(msg = questtemp["msg1"])||msg==""||random(2))
                                {
                                        if(questtemp["race"])
                                                msg=DGMSG_D->query_dgmsg("��",questtemp["name"]);
                                        else
                                                msg=DGMSG_D->query_dgmsg("ɱ",questtemp["name"]);
                                }
                                break;
                        case "Ѱ":
                                if(undefinedp(msg = questtemp["msg"])||msg==""||random(2))
                                        msg=DGMSG_D->query_dgmsg("Ѱ",questtemp["name"]);
                                break;
                        case "��":
                                if (questtemp["object"]->query("race") != "����")
                                {
                                        msg = dg_msg[random(sizeof(dg_msg))] + replace_string(qin_msg1[random(sizeof(qin_msg1))],"name",questtemp["name"]) + qin_msg2[random(sizeof(qin_msg2))];
                                        break;
                                }
                                if(undefinedp(msg = questtemp["msg2"])||msg==""||random(2))
                                {
                                        if(questtemp["race"])
                                                msg=DGMSG_D->query_dgmsg("׽",questtemp["name"]);
                                        else
                                                msg=DGMSG_D->query_dgmsg("��",questtemp["name"]);
                                }
                                break;
                        case "��":
                                npc = new(CLASS_D("generate") + "/dg_receiver.c");
                                FUBEN_D->clear_fuben("ultra", ob->query("id"));
                                maze_object = get_object("/f/ultra/"+ob->query("id")+"/maze");
                                maze_object->set_maze_boss(npc);
                                maze_target = get_object("/f/ultra/"+ob->query("id")+"/maze/exit");
                                //maze_target = MAZE_D->create_maze(npc);
                                npc->move(maze_target);
                                /*
                                NPC_D->place_npc(npc, count_lt(ob->query("combat_exp"), 500000)  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                              count_lt(ob->query("combat_exp"), 800000) ? ({ "����һ��", "����ɽ", "����" }) : ({"����һ��", "����"}));
                                */
                                NPC_D->set_from_me(npc, ob, 100);
                                npc->set_temp("quester", ob->query("id"));
                                /*
                                NPC_D->random_move(npc);
                                NPC_D->random_move(npc);
                                NPC_D->random_move(npc);
                                */
                                //place = npc->query("place");
                                thing = new(questtemp["object"]);
                                if (! objectp(thing))
                                        log_file("static/Non_things", sprintf("�޷��ҵ���Ʒ %s\n", questtemp["object"]));
                                thing->set("send_to",npc->query("id"));
                                thing->set("send_from",query("id"));
                                thing->set("send_from_name",query("name"));
                                msg = dg_msg[random(5)]+"�鷳����ҽ�"+thing->name(1)+"����"+npc->name(1)+"����"
                                                "�����������Թ��У�����ʱ�������ܾ��뿪�ˡ�";
                                /*
                                msg = dg_msg[random(5)]+"�鷳����ҽ�"+thing->name(1)+"����"+npc->name(1)+"����"
                                                "����������"+place+"������ʱ�������ܾ��뿪�ˡ�";
                                */
                                if (!thing->move(ob))
                                {
                                        thing->move(environment(this_object()));
                                        message_vision("������ܽ�$N������ڵ��ϡ�\n",thing);
                                } else message_vision("������ܽ�$N����$n��\n",thing,ob);
                                break;
                        }
                        questdg=([
                                "name":questtemp["name"],
                                "type":questtemp["type"],
                                "bonus":questtemp["bonus"],
			        "object":questtemp["object"],
                                "dgmsg":msg,
                        ]);
                }
        }  
        if (questdg["type"] == "ɱ" && (random(6) == 2 || wizardp(ob)))
        {
                robot_quest = ANTI_ROBOT->get_question();
                msg = "�������֣��˵�������Ҹս�������֯�Ŀ��������һ�£���ȥ֪ͨһ��" + questdg["name"] + NOR"���¿����ǣ�\n";
                msg += robot_quest["question"];
                msg += "��ֻ��Ҫ��������"HIR"��ͨ��������ʽ"NOR"���͹�ȥ�����ˣ����͵�ָ���ǣ�whisper��\n";
                questdg["type"]   = "��";
                questdg["dgmsg"]  = msg;
                questdg["answer"] = robot_quest["answer"];
        }

        tell_object(ob, questdg["dgmsg"]+"\n");
        questdg["level"]=level;
        if (questdg["type"] == "��") 
        {
                questdg["obj"] = thing;
                questdg["send_to"] = thing->query("send_to");
                if (maze_object)
                        questdg["maze"] = maze_object;
        }
        ob->set("quest_dg",questdg);
        return 1;
}


int accept_object(object who, object ob)
{
        int exp, pot,level,bonus,time,times;
        int i,quest_count,mar,score,weiwang,all_quest_dg;
        int total_count;
        mapping questdg;
        string dest,msg;
        object gold,obj;
        mixed special = 0;
        mixed money = 0;
        mapping my;

        if (base_name(ob) == "/clone/book/dugubook")
        {
                if (who->query_skill("dugu-jiujian", 1) < 340)
                {
                        command("shake"); 
                        command("say ��ϧ����ϧ������¾Ž����������������޷�������¾Ž��ľ���֮����");
                        destruct(ob);
                        return 1;
                }

                if (who->query("can_learn/dugu-jiujian/nothing"))
                {
                        command("nod");
                        command("say ���Ѿ������˶��¾Ž�֮���裬��ȥ�ú���ϰ�ɣ�");
                        destruct(ob);
                        return 1;
                }
                
                // ��ʼ���ڶ��¾Ž�֮����
                command("nod");
                command("say ��������������Ȼ��ˣ��Ҿͽ����¾Ž�֮���贫�����㡣");
                command("say ���¾Ž����֮���Ѿ�������ʽ������һ��" HIY "����" NOR + CYN "��");
                command("say ���¾Ž����������ˣ����������κ���ʽ�����Ķ��������Ķ��գ��ﵽһ\n"
                        "��" HIY "����ʤ����" NOR + CYN "�ľ��磡");
                command("say �����ˣ�");

                who->set("dugu-jiujian/nothing", 1);

                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("sword"))
                        who->improve_skill("sword", 1500000);
                if (who->can_improve_skill("dugu-jiujian"))
                        who->improve_skill("dugu-jiujian", 1500000);
                if (who->can_improve_skill("dugu-jiujian"))
                        who->improve_skill("dugu-jiujian", 1500000);
                if (who->can_improve_skill("dugu-jiujian"))
                        who->improve_skill("dugu-jiujian", 1500000);
                who->improve_skill("martial-cognize", 1500000);
                who->improve_skill("martial-cognize", 1500000);  
                who->improve_skill("martial-cognize", 1500000);  

                tell_object(who, HIG "��ѧ���˶��¾Ž�֮�����С���\n" NOR);

                destruct(ob);
                return 1;
        }

        if(!(questdg =  who->query("quest_dg")))
        {
                tell_object(who,"������ܿ��˿��㣬�ƺ���֪������ʲô��˼��\n");
                return notify_fail("������ܵ���һЦ���������ҿɲ�ȱʲô��������\n");
        }
   
        if(ob->query("money_id"))
        {
                if (ob->value() < 1000000)
                {
                        tell_object(who,"������ܶ��������ĳ���˵��������ô��Ǯ����ʲô�أ����ֲ���ȱǮ����\n");
                        return notify_fail("�������ҡҡͷ���������100���ƽ𣬻����Ҿ��������������\n");
                }
                who->delete("quest_dg");
                tell_object(who,"������ܶ���" + ob->name(1) + "ע�����ã�̾������������������������˰ɡ�\n");
                destruct(ob);
                return 1;
        }

        if(questdg["type"] != "Ѱ" && questdg["type"] != "��" && questdg["type"] != "��")
        {
                tell_object(who,"������ܿ��˿��㣬�ƺ���֪������ʲô��˼��\n");
                return notify_fail("������ܵ���һЦ���������ҿɲ�ȱʲô��������\n");
        }

        if( ob->name(1) != questdg["name"] || userp(ob))
        {
                tell_object(who,"�������̾�˿����������Ⲣ��������Ҫ�ġ�\n");
                return notify_fail("������ܿ����㣬���������ǲ�����ȥ���ҿ�������\n");
        }

        if(questdg["type"]=="��")
        {
                if (!ob->is_receipt() || ob->query("reply_to") != this_object()->query("id") )
                {
                        write("������ܽӹ���һ�������ȵ�˵�����Ҳ��ǽ�������Ͷ�����ô�����ǲ��ǼǴ��ˣ���\n");
                        return 0;
                }
                if ( ob->query("reply_by") != questdg["send_to"] )
                {
                        write("������ܽӹ���һ����������˵�������Ż�ִ��˭����ģ���������Ū�ң���\n");
                        return 0;
                }
                if ( ob->query("receive_from") != who->query("id") )
                {
                        write("������ܽӹ���һ����������˵�������Ż�ִ�����Լ��õ���ô����������Ū�ң���\n");
                        return 0;
                }
        } 

        if (userp(ob) || ob->query("user") ||
            ob->is_item_make() ||
            ob->query_save_file())
        {
                write("������ܴ�ŭ�����������С�ӣ���Ȼ����ƭ����ʦ�����ˣ���������ץ��������\n");
                who->get_into_prison(this_object(), 0, 30);
                log_file( "static/QUEST_DIJIAO", sprintf("%s(%s)(��������)����%s(%s)(%s)����\n", who->query("name"),
                who->query("id"),ob->name(),ob->query("id"),ctime(time()) ) );
                return 1;
        }

        // message_vision("$N��$n����������ܡ�\n",who,ob); ��give��Ϣ�ظ�
        tell_object(who,"������ܵ�ͷ΢Ц��������Ϊ��������������������������\n");
        who->delete("quest_dg");
        if (ob->is_character() && ob->query("startroom"))
        {
                my = ob->query_entire_dbase();
                my["jing"]   = my["eff_jing"]   = my["max_jing"];
                my["jingli"] = my["eff_jingli"] = my["max_jingli"];
                my["qi"]     = my["eff_qi"]     = my["max_qi"];
                my["neili"]  = my["max_neili"];
                if(! living(ob))
                        ob->revive();
                ob->clear_condition();
                ob->remove_all_killer();
                if (! ob->return_home(ob->query("startroom")) )
                        ob->move(ob->query("startroom"));
        } else destruct(ob);

        level = questdg["level"]+1;
        if((i=who->query("questdg_times")) < 8)   
                i = 15-i;
        else i = 1;

        exp = level*400 + questdg["bonus"]*12;
        exp += who->query("questdg_times")*2;
        exp /= i;

        if (questdg["type"] == "��")
        exp += exp/5;
        pot = exp/(2+random(2));
        score = random(exp/20);
        weiwang = random(exp/15);

        if (who->query("questdg_times") + 1 > 200)
	       mar = exp/3 + random(who->query("questdg_times"));
        else mar = 100 + random(100);
   
        if (mar > 3000) mar = 3000;

        if(wizardp(who)||!random(10))
        {
                i=(exp/60+1);
                if(i>30) i=30;
                gold=new("/clone/money/gold");
                gold->set_amount(i);
                tell_object(who,"����˵�������������߽�������ͷ�е���ɣ��������õ�ƽ����̲��ɣ���\n"
                        HIW"\n�㱻������ "+i+" ���ƽ�\n");
                if(!gold->move(who))
                {
                        message_vision("����$N���϶���̫�أ��ƽ�һ���ӵ����˵��ϡ�\n",who);
                        gold->move(environment());
                }
                GIFT_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                      "weiwang" : weiwang, "score" : score, "percent" : 50 ]), 1);
        }
        else 
                GIFT_D->bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar, "percent" : 80, 
                                      "weiwang" : weiwang, "score" : score ]), 1);

        // who->add("questdg_times",1);
        who->add("total_hatred",-5);
        if (who->query("total_hatred") < 0) who->set("total_hatred",0);
        
        
        quest_count = who->query("questdg_times") + 1;
        total_count = quest_count % 500;
        if (total_count == 50)
        {
                msg = "$N�Ǻ�Ц�������������㻹���ԣ�����"+chinese_number(quest_count)+
                      "��������ɵ�ƯƯ����������Ŭ������\n";
	        special = 1;
        } else
        if (total_count == 100)
        { 
                msg = "$NЦ�ĺϲ�£�죬������һ�۵�������־����"+chinese_number(quest_count)+
                      "������ɵøɾ���������\n";
                special = "/clone/gift/puti-zi";
        } else
        if (total_count == 150)
        {
                msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
                      "��������һ��©�����ף����ף���\n";
                money = 1;
        } else
        if (total_count == 200)
        {
                msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
                      "��������һ��©�����ף����ף���\n";
                money = 1;
        } else
        if (total_count == 250)
        {
                msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
                      "��������һ��©�����ף����ף���\n";
                money = 1;
        } else

        if (total_count == 300)
        {
                msg = "$N̾���������ǳ���������ǰ�ˣ��벻�������"+chinese_number(quest_count)+
                      "��������һ��©�����ף����ף���\n";
	        special = "/clone/gift/tianxiang";
        } else
        if (total_count == 350)
        {
                msg = "$N����һ��������������ĺ��ʺ�ѧ�䣬������"+chinese_number(quest_count)+
                      "��������һ��©�����ף����ף���\n";
	        special = "/clone/gift/tianxiang";
        } else
        if (total_count == 400)
        {
                msg = "$N̾����������һ����ѧ��Ű����벻�������"+chinese_number(quest_count)+
                      "��������һ��©�����ף����ף���\n";
                special = "/clone/gift/jiuzhuan";
        } else
        if (total_count == 450)
        {
                msg = "$N����������������ţ�������ţ�����������"+chinese_number(quest_count)+
                      "��������һ��©�����ף����ף���\n";
                special = "/clone/gift/jiuzhuan";
        } else 
        if (total_count == 0)
        {
                msg = "$N����̾�˿�����������û�뵽������"+chinese_number(quest_count)+
                      "��������һʧ�֣������Ժ����������Щ��������������\n";
                special = "/clone/gift/xuanhuang";
#ifdef DB_SAVE
                if (MEMBER_D->is_valid_member(who->query("id")))
		{
					
                        if (who->query("special_skill/sophistry")) 
                        {
                                if (quest_count >= 4000)
					quest_count = 0;
			} else {
                                if (quest_count >= 2000)
                                        quest_count = 0;
			}
                } else {
#endif
                	if (quest_count >= 1000)
                                quest_count = 0;
#ifdef DB_SAVE
		}
#endif
        } else
        if ((total_count % 10) == 0)
        {
                msg = "$N�Ǻ�Ц�ţ�������ֺܲ���������Ȼ����" +
                      chinese_number(quest_count) +
                      "�ζ�û��ʧ�֣���æ����������������\n";
        }
        
        who->set("questdg_times", quest_count);
        
        if (special) 
        {
                // message_vision(msg, this_object(), who);
                QUEST_D->special_bonus(this_object(), who, special);
        }
        if (money) 
        {
                // message_vision(msg, this_object(), who);
                QUEST_D->money_bonus(this_object(), who, money);
        }
   
        // ��¼�������Ĵ�������Ҫ���������������1000��������觲�Ƭ
        all_quest_dg = (int)who->query("all_quest_dg");
        if (!all_quest_dg) all_quest_dg = 0;
        all_quest_dg += 1;
        if (all_quest_dg == 1000)
        {
                obj = new("/clone/enchase/redgem.c");
                tell_object(who,this_object()->name() + "�ֶ�����˵�ͷ�����Ѿ������������һǧ����������������\n" +
                        "�и�" + obj->query("name") + "���ͽ������ˣ�\n");
                if (!obj->move(who))
                        obj->move(environment());
                who->set("all_quest_dg",0);
                FAMILY_D->add_family_fame(who, 20 + random(5));
                LEAGUE_D->add_league_fame(who, 20 + random(5));
                BUNCH_D->add_bunch_fame(who, 20 + random(5));
        } else who->set("all_quest_dg",all_quest_dg);
        return -1;
}

int give_up()
{
        object ob,obj,room;
        mapping questdg;

        ob = this_player();

        if(mapp(questdg =  ob->query("quest_dg")))
        {
                write("�������߲ѣ�����������ȡ���Լ�������\n");
                /*
                if (questdg["type"] == "��")
                {
                        message_vision("$N���ȵض�$nЦЦ�������������Ǻܼ򵥵����񰡣���Ҫ�ż�����ͷ�ٺú����룬Ŭ��������ɣ�\n",this_object(),ob);
                        return 1;
                }
                */
                write("������ܺ�����ɫ����������Դ���������û��ϵ��Ҫ����Ŭ��������\n");
                if(questdg["type"] == "��")
                {
                        if(ob->query("questdg_times") > 0)
                                ob->add("questdg_times",-1);
                }
                else if(questdg["type"] == "ɱ"&&questdg["level"] == 8)    //by llm
                {
                        ob->set("questdg_times",0);
                }
                else
                        ob->set("questdg_times",0);

                if ( stringp(questdg["maze"]) )
                {
                        //MAZE_D->remove_maze(questdg["maze"]);
                        FUBEN_D->clear_fuben("ultra", ob->query("id"));
                }
            
        }
                /*
                if(questdg["type"] == "��")
                {
                        if(objectp(obj = questdg["obj"]))
                        {
                                if(obj->is_character())
                                        message_vision("$NһԾ�����ܵ���Ӱ�����ˡ�\n",obj);
                                obj->move(environment(ob));
                                destruct(obj);
                                if(ob->query("questdg_times") > 0)
                                        ob->add("questdg_times",-1);
                        }
                }
                else 
                if(questdg["type"] == "ɱ"&&questdg["level"] == 8)    //by llm
                {
                        if(!(room = find_object(questdg["where"])) )
                                room = load_object(questdg["where"]);

                        if(objectp(obj = present(questdg["id"],room))
                                &&obj->is_character()
                                &&!userp(obj))
                        {
                                message_vision("$N����һ����ת���߿��ˡ�\n",obj);
                                obj->move("/d/wizard/wizard_room"); 
                                destruct(obj);
                        }
                        ob->set("questdg_times",0);
                }
                else
                        ob->set("questdg_times",0);
        }
        */
        else
                write("������ܺ�����ɫ�ؿ����㣬������û��ϵ�������ڸ�����û�����񰡣���\n");
        ob->delete("quest_dg");
        ob->set("questdg_giveup_time",time());
        return 1;
}

string time_period(int timep)
{
        int t, d, h, m, s;
        string time;
        t = timep;
        s = t % 60;             t /= 60;
        m = t % 60;             t /= 60;
        h = t % 24;             t /= 24;
        d = t;
 
        if(d) time = chinese_number(d) + "��";
        else time = "";
 
        if(h) time += chinese_number(h) + "Сʱ";
        if(m) time += chinese_number(m) + "��";
        time += chinese_number(s) + "��";
        return time;
}

void destory(object ob)
{
        if(!ob)
                return;
        if(ob->is_character())
                message_vision("$NһԾ�����ܵ���Ӱ�����ˡ�\n",ob);
        ob->move("/d/wizard/wizard_room");
        destruct(ob);
        return ;
}
 
void npc_dest(object npc)
{
        if(!npc) return;
        if(npc->is_fighting()&&npc->query_temp("wait_times")<4)
        {
                npc->add_temp("wait_times",1);   //4�λ���
                call_out("npc_dest",60,npc);     //�ٵ�һ����
                return;
        }
        if(npc->is_character())
                message_vision("$N���صغ���һ�������������ǵ�С������ת��һ�Σ��Ѳ�������Ӱ��\n",npc);
        npc->move("/d/wizard/wizard_room");
        destruct(npc);
        return ;
}