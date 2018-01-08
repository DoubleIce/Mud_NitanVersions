#include <ansi.h>
inherit ROOM;

void message_competition(string msg);
void create()
{
        set("short", "��������");
        set("long", @LONG
�˴�ԭ��һ��������Ƶ��ͱڣ���֪�������˴��ͱڵİ���Ӳ��
����һ��ջ������ջ������һ��ʮ���ɵ�����ʯ����ʯ������һ�ɣ�
������һ������ʯ�������������µĺ��ӡ� 
LONG );
        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
/*
                "northup" : "/adm/npc/huashanjueding",
                "up" : "/adm/npc/kantai",
                "1" : "/adm/npc/biwu1",
                "2" : "/adm/npc/biwu2",
                "3" : "/adm/npc/biwu3",
                "4" : "/adm/npc/biwu4",
*/
        ]));

        set("outdoors", "huashan" );

        set("no_fight", 1);
        setup();
}

void init()
{
        if (wiz_level(this_player()) >= 3)
        {
                add_action("do_open", "open");
                add_action("do_close", "close");
        }
}

int do_open()
{
        object me = this_player();

        if (query("exits/up"))
                return notify_fail("���Ѿ��ǿ��ŵ��ˡ�\n");

        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
                "northup" : "/adm/npc/huashanjueding",
                "up" : "/adm/npc/kantai",
                "1" : "/adm/npc/biwu1",
                "2" : "/adm/npc/biwu2",
                "3" : "/adm/npc/biwu3",
                "4" : "/adm/npc/biwu4",
        ]));

        message_vision(HIY "$N" HIY "����һ�ƣ���ͨ�����ִ��᳡��"
                       "���ſ����ˡ�\n" NOR, me);

        shout(HIY "�����ִ��š�" NOR + WHT + me->name() + WHT "[" +
              me->query("id") + WHT "]�����˻�ɽ���������ִ��᳡��\n" NOR);

        return 1;
}

int do_close()
{
        object me = this_player();

        if (! query("exits/up"))
                return notify_fail("���Ѿ��ǹ��ŵ��ˡ�\n");

        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
        ]));
        message_vision(WHT "$N" WHT "˳��һ������ͨ�����ִ��᳡��"
                       "���Ź����ˡ�\n" NOR, me);
        return 1;
}

void message_competition(string msg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

int valid_leave(object me, string dir)
{
        int i;
        object *inv;
        int age = (int)me->query("age");

        if (dir == "southdown" || dir == "up")
                return 1;
                
        inv = deep_inventory(me);

        for(i=sizeof(inv)-1; i>=0; i--)
        {
                if (me->query_condition("killer"))
                        return notify_fail("ɱ���߲����Խ�����䳡������\n");
                if (! wizardp(me) &&
                    inv[i]->is_cruise_ob())
                        return notify_fail("������Я�����δ��Ͱ�������䳡������\n");
                if (! wizardp(me) &&
                    inv[i]->is_item_make())
                        return notify_fail("������Я����������������䳡������\n");
                if (! wizardp(me) &&
                    inv[i]->query("weapon_prop"))
                        return notify_fail("������Я����������������䳡������\n");
                if (! wizardp(me) &&
                    inv[i]->query("armor_prop"))
                        return notify_fail("������Я����������������䳡������\n");
                if (! wizardp(me) &&
                    inv[i]->query("id") == "tang hua")
                        return notify_fail("������Я�������ƻ�������䳡������\n");
                if (! wizardp(me) &&
                    (inv[i]->query("id") == "god blood" || inv[i]->query("id") == "tianmo shengxuegao"))
                        return notify_fail("������Я���鵤��ҩ������䳡������\n");
        }

        if (wizardp(me)
        ||  (dir == "1" && age < 21) 
        ||  (dir == "2" && (age >= 21 && age < 31)) 
        ||  (dir == "3" && ( age >= 31 && age < 41)) 
        ||  (dir == "4" && age >= 41)) 
        {
                /*
                message_competition((ultrap(me) ? "����ʦ" : "") +
                            me->name(1) + "���뻪ɽ���������ִ��᳡��");
                */
                return 1;
        }
        if (dir == "northup")
        {
                /*
                message_competition((ultrap(me) ? "����ʦ" : "") +
                            me->name(1) + "���뻪ɽ���������ִ��᳡��");
                */
                if (me->query_condition("killer"))
                        return notify_fail("ɱ���߲����Խ�����䳡������\n");
                return 1;
        }
        return notify_fail("�㲻���Ե��Ǳ߱��䣡��\n");
}


