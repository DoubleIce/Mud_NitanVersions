#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
������һ����ʯ����ϣ����ܾ����ĵġ�������Ũ�ܵ����֣���
ɭɭ��ʮ�����ˡ���������Զ�����¶��ı߽��ˡ�����ȴ��һƬ�ݵء�
��̧ͷ��Զ������������ԼԼ�ܹ������䵱ɽ��Ӱ�ӣ�ֻ������ɱ�
���ϡ�
LONG );
        set("outdoors", "wudang");
        set("exits", ([
            "northwest" : __DIR__"wdroad6",
            "north"     : "/d/xiangyang/caodi6",
            "east"      : __DIR__"wdroad4",
            "southdown" : "/d/jingzhou/jzbeimen",
        ]));
	set("coor/x", -290);
	set("coor/y", -160);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_float", "float");
        add_action("do_float", "piao");
}

int do_float()
{
        object me;

        me = this_player();

        if (me->query_skill("tiyunzong", 1) < 160 ||
            me->query_skill("dodge", 1) < 160)
        {
                message_vision("$N��������ԭ�ر�����һ�����\n", me);
                return 1;
        }

        if (me->query("neili") < 150)
        {
                tell_object(me, "�������������������Ϣһ����˵�ɡ�\n");
                return 1;
        }

        me->add("neili", -120);

        message_sort(HIC "\n$N" HIC"����һ�����������󲽣�˫��"
                     "��ɣ�����ɽ���Ӳݣ�ƮȻ����ֱ�����䵱"
                     "ɽȥ�ˣ�ת˲������ֻ����ԶԶһ��Ӱ�ӡ�\n"
                     "\n" NOR, me);
        me->move("/d/wudang/guangchang");
        tell_object(me, "Ƭ�̣����Ѿ����������䵱ɽ�ϡ�\n");
        message("vision", "ֻ��һ������ӹ���" + me->name() +
                "�Ѿ�ƮȻ������\n", environment(me), ({ me }));
        return 1;
}