#include <ansi.h>
inherit ROOM;

string look_notice();
void create()
{
        set("short", "׳����");
        set("long", @LONG
����ǰ��һƬ��ɫ�Ĵ��ƺ,��ƺ��������һ���ʯ̨��ʯ̨���Ա߷�����
һ��ʯ��(notice)�ͼ���������(jia)��ʯ���ĺ���һ�����(flag)ӭ����չ!!!!!!!
��ʯ̨�ϸ߸�����һ���ľ��(paizi)������д���������̰��������
LONG
    );
        set("item_desc", ([ /* sizeof() == 1 */
                "���" : "����һֻţƤ�Ƴɵľ޹ģ�������ʿ�ڻ�ɽ�۽�ʱ����(knock)����ʼ���䡣",
                "flag" : " �� �� Ӣ �� �� �� �� \n",
                "jia"  : "������(na)�ı����н�(sword)����(blade)����(staff)����(whip)������(hammer)��\n"
                         "����(throwing)������(club)�������·�(cloth)������(hand)��ָ��(finger)��\n",
                "notice" : (: look_notice :),
        ]));
        
        set("exits", ([ /* sizeof() == 2 */
                "out" : "/d/huashan/houzhiwangyu",
        ]));
        
        set("no_fight", 1);
        set("no_magic", 1);
        set("objects",([
                "/adm/npc/obj/drum3" : 1,
        ]));
        setup();
}

void init()
{
        object me = this_player();
        int age = (int)me->query("age");
        
        /*
        if (! wizardp(me) && (age >= 40 || age < 30))
        {
                tell_object(me,"������ָ����㣺�㲻������������ر��䣡��ѡ����������Ӧ�ĳ��أ���\n");
                me->move("/d/huashan/houzhiwangyu");
                return;
        }
        */

        add_action("get_weapon", ({ "na", "qu", })); 
        add_action("discmds", ({
                "respitate", "exert", "array", "ansuan", "touxi", "persuade", 
                "teach", "exert", "exercise", "study", "learn", "sleep", "kill",
                "steal", "cast", "conjure", "expell", "fight", "hit", "perform", 
                "prcatice", "scribe", "surrender", "sha", "recall", "quit", "exit", "team"}));
        // call_out("do_recover", 1, me);
}
void do_recover(object me)
{
        if (! me || environment(me) != this_object()) return;
                me->delete("no_get");
        if (! living(me)) me->revive();
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("max_jing"));
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("max_qi"));
        if (me->query("neili") < me->query("max_neili"))
                me->set("neili", me->query("max_neili"));
        if (me->query("jingli") < me->query("max_jingli"))
                me->set("jingli", me->query("max_jingli"));
        me->clear_condition();
        me->set("food", me->max_food_capacity());
        me->set("water", me->max_water_capacity());
        me->start_busy(0);
}

int discmds()
{
        tell_object(this_player(),"�����㻹��ר�Ŀ�����ɣ�\n");

        return 1;
}

int get_weapon(string arg)
{
        object me, ob;
        object *obs;
        int cloth, sword, blade, staff, whip, hammer, throwing, hand, finger, club;
        int i;
        
        me = this_player();
        
        if (! arg) return notify_fail("��Ҫ��ȡʲô��Ʒ��\n");
        
        cloth = sword = blade = staff = whip = hammer = throwing = hand = finger = club = 0;
        
        obs = all_inventory(me);
        for (i = 0; i < sizeof(obs); i++)
        {
                switch (base_name(obs[i])) 
                {
                case "/clone/cloth/cloth":
                        cloth = 1;
                        break;
                case "/clone/weapon/changjian":
                        sword = 1;
                        break;
                case "/clone/weapon/blade":
                        blade = 1;
                        break;
                case "/clone/weapon/zhubang":
                        staff = 1;
                        break;
                case "/clone/weapon/changbian":
                        whip = 1;
                        break;
                case "/clone/weapon/qimeigun":
                        club = 1;
                        break;
                case "/d/city/npc/obj/tieshou":
                        hand = 1;
                        break;
                case "/d/city/npc/obj/zhitao":
                        finger = 1;
                        break;
                case "/clone/weapon/hammer":
                        hammer = 1;
                        break;
                case "/d/tangmen/obj/qinglianzi":
                        if (obs[i]->query_amount() > 1000)
                                throwing = 1;
                        break;
                default:                  
                        break;
                }
        }
                
        switch (arg) 
        {
        case "cloth":
                if (cloth) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/clone/cloth/cloth");
                break;
        case "sword":
                if (sword) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/clone/weapon/changjian");
                break;
        case "blade":
                if (blade) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/clone/weapon/blade");
                break;
        case "staff":
                if (staff) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/clone/weapon/zhubang");
                break;
        case "club":
                if (club) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/clone/weapon/qimeigun");
                break;
        case "whip":
                if (whip) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/clone/weapon/changbian");
                break;
        case "hammer":
                if (hammer) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/clone/weapon/hammer");
                break;
        case "throwing":
                if (throwing) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/d/tangmen/obj/qinglianzi");
                ob->set_amount(1000);
                break;
        case "finger":
                if (finger) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/d/city/npc/obj/zhitao");
                break;
        case "hand":
                if (hand) return notify_fail("�����ϲ����Ѿ�������\n");
                ob = new("/d/city/npc/obj/tieshou");
                break;
        default:  
                return notify_fail("��Ҫ��ȡʲô��Ʒ��\n"); 
                break;
        }
        
        ob->move(me, 1);
        
        tell_object(me, "��Ӽ���������һ" + ob->query("unit") + ob->name() + "��\n");
        return 1;
}
        
string look_notice()
{
        object who;
        array name_list;
        string file;
        int i, j = 0, k;
        
        who = this_player();
        file = read_file("/log/static/lunjian3");
        if (! file)
                return "Ŀǰû���κα����¼��\n";
        name_list = explode(file, "\n");
        for (i = 0; i < sizeof(name_list); i++) 
        {
                if (name_list[i] == "seperator") 
                {
                        j++;
                        k = 0;
                        printf("\n��" + chinese_number(j) + "��(׳����)��ɽ�۽������\n");
                        continue;
                }
                k++;
                printf(GRN "��" + chinese_number(k) + "����%-50s\n" NOR, name_list[i]);
        }
        return "\n";
}
