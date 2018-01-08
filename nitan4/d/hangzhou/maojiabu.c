// maojiabu.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "茅家埠");
        set("long", @LONG
路两旁盖着几座小土房。房门口一位老大娘正在喂鸡，几个小孩
正在追逐嬉戏。北边是上黄泥岭。南面是丁家山。
LONG );
        set("exits", ([
            "southwest"   : "/d/hangzhou/tulu1",
            "northup"     : "/d/hangzhou/huangniling",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/boy" : 1,
            "/d/hangzhou/npc/oldwoman" : 1,
            "/d/hangzhou/npc/camel" : 1,
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
