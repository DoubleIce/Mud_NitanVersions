// liuhe2.c
// Date: Nov.1997 by Java
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "������");
        set("long", @LONG
�������������Ķ��㡣��(window)����Ũױ��Ĩ�����Ӻ�������
����˽ǣ���ש���أ��������ܼ�ճ����Щ��������
LONG );
        set("exits", ([
            "down"  : "/d/hangzhou/liuhe1",
            "up"    : "/d/hangzhou/liuhe3",
        ]));
        set("objects", ([
            "/d/hangzhou/honghua/xinyan" :1,
            "/d/hangzhou/honghua/zhouyi" :1,
        ]));
        set("item_desc", ([
            "window": "�Ӵ�������ȥ��Ǯ����ȥ������ũ���У���һũ�����ɳ����š�\n",
        ]));
        set("no_clean_up", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "up" &&
            objectp(present("xin yan", environment(me)))) 
            return notify_fail("�������һЦ�����ﻹû����أ�������¥��\n");
        if (dir == "up" &&
            objectp(present("zhou yi", environment(me))))
            return notify_fail("�������һ�ɣ�û������������������\n");

        return ::valid_leave(me, dir);
}