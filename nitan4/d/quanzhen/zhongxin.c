inherit ROOM;

void create()
{
        set("short", "���Ĺ㳡");
        set("long", @LONG
�������书������Ĺ㳡���书���Ǹ�С��ֻ��������ֱַ�
�Ƕ��֣����֣��Ͻֺͱ��֣����������ϡ��ߵ�����·�ϵ����˶�
��Щ�������㶼�ͺ������ع���Ϊ��
LONG );
        set("outdoors", "wugong");
        set("exits", ([
                "east" : __DIR__"dongjie",
                "west" : __DIR__"xijie",
                "north" : __DIR__"beijie",
                "south" : __DIR__"nanjie",
        ]));

        set("objects", ([
                __DIR__"npc/liumang" : 2,
        ]));

        setup();
        replace_program(ROOM);
}