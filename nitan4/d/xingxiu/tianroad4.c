#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ɽɽ·");
        set("long", @LONG
��������ɽ��´��ɽ���ɽ�ϴ����������ɪɪ������·����һ
Ƭ��Ҷ�֡�ʯ����ʢ����һ���׵���ɽѩ����һ����ҩ�����ڲ�ҩ��
����һ���(valley)��ס����ɽ��·��
LONG );
        set("exits", ([
            "westup" : __DIR__"tianroad5"
        ]));

                set("objects", ([
                        "/clone/fam/pill/xuelian1" : 1,
                "/d/xingxiu/obj/xuelian" : 1,
                "/d/xingxiu/npc/caiyaoren"  : 1,
                ]));

        set("item_desc", ([
                "valley" : WHT "\n��������ɶ������֪���ܲ�������ȥ��\n" NOR,
        ]));
        set("outdoors", "xingxiu");

        setup();
}

void init()
{
        add_action("do_jump", "jump");
        add_action("do_jump", "tiao");
}

int do_jump(string arg)
{
        object me;
        me = this_player();

        if (! arg || arg != "valley")
                return notify_fail("��Ҫ��������\n");

        message_vision(HIY "\n$N" HIY "ԥ��һ�£��������������Ŷ����ɽ�����˹�"
                       "ȥ��\n\n" NOR, me);

        if ((int)me->query_skill("dodge", 1) < 100 )
        {
                me->move(__DIR__"shanjiao");
                me->receive_wound("qi", 300);
                me->unconcious();
                message("vision", HIR "\nͻȻ���á��项��һ����ֻ��һ���˴�����"
                                  "��ɽ����׹������������׳�ۡ�\n" NOR,
                                  environment(me), ({me}));
        } else
        {
                me->move(__DIR__"tianroad3");
                message("vision", HIY "\nֻ��" + me->name() + HIY "�Ӷ����ɽ��"
                                  "�����˹�����\n" NOR, environment(me), ({me}));
        }
        return 1;
}