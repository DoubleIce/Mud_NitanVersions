#include <ansi.h>
inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "兰州西门");
        set("long", @LONG
这是兰州城的西城门，由于这里的环境干燥，经过几年的风沙侵
蚀显得有些破败。城门正上方勉勉强强可以认出西门两个大字，城墙
上贴着几张通缉告示(gaoshi)。许多来边疆做苦力的罪犯常常经过这
里逃回中原，官兵们戒备森严，动不动就截住行人进行盘问。一条笔
直的青石大道向东西两边延伸。西边是郊外，一直向西去就是举世闻
名的敦煌，许多游客在找到向导后都座着骆驼由这里出去游览敦煌。
许多人赶着牲口从这里经过，到城里去卖掉自己种的瓜果，再买回生
活必需品。东边是城里。
LONG );
        set("outdoors", "lanzhou");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "west"  : "/d/xingxiu/xxroad3",
                "east"  : __DIR__"xidajie1",
                
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/d/beijing/npc/ducha" : 1,
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -530);
	set("coor/y", 110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n         兰州知府\n                     耶律巡\n";
}
