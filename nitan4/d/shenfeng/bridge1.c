#include <ansi.h>; 
inherit ROOM;

void create()
{
        set("short", "��ľ��");
        set("long", @LONG
�������������Ӳ��죬ע��ѩ�׵�ɽ�壬���˲�����Ȼ����˼��
֮���顣��ǰֻ��һ�����ң����پ��£�ֻ��һ����խ�Ķ�ľ��(bri
dge)ͨ����£�Σ���ڹȷ��в�ͣ�ض�����
LONG );
        set("outdoors", "gaochang");

        set("exits", ([ 
        	"south" : __DIR__"xiaojing",
	]));
        set("item_desc",([
                "bridge" : YEL "����һ����Լ�ߴ�Ķ�ľ�ţ�����ֻ"
                           "����(zou)��һ�ˡ�\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_zou", "zou");
}

int do_zou(string arg)
{
        object me = this_player(), room;

        if (! arg || arg != "bridge")
                return notify_fail("��Ҫ��ʲô��\n");

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail(HIY "\n��սս��������ǰ������"
                                   "������ͻȻ��ȷ�ι���Σ��һ"
                                   "���\n�����ŵ����æ�ջ��˽�"
                                   "����\n" NOR);

        if (! (room = find_object(__DIR__"bridge2")))
                room = load_object(__DIR__"bridge2");

        if (! objectp(room))
                return notify_fail(HIW "���е���BUG��BUG��\n" NOR);

        message_vision(HIW "\nֻ��$N" HIW "����Ծ�϶�ľ�ţ�ƮȻ��"
                       "ȥ��\n" NOR, me);
        me->move(room);
        message_vision(HIW "$N" HIW "�Ӷ�ľ����ƮȻ���£�������ɽ"
                       "��Ķ��档\n" NOR, me);
        return 1;
}