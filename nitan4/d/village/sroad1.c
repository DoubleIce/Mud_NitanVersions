// Room: /d/village/sroad1.c

inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ��������С���ӣ�ϡϡ����ķֲ��ż�ʮ�������෿����
�������˼Ҳ��࣬���Ҵ�����ܼ�����һ����ʯ·������ͨ�����
�����ģ����Ͼ��ǳ����·�ˡ�
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "north" : __DIR__"sroad2",
            "south" : __DIR__"sexit",
        ]));
        set("outdoors", "village");
        set("objects", ([
		__DIR__"npc/girl": 1,
		__DIR__"npc/boy": 1
	]), );

        setup();
        replace_program(ROOM);
}
