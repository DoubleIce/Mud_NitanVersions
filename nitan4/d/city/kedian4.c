// Room: /city/kedian4.c 
// SMALLFISH 1995/12/04 
 
#include <ansi.h> 
#include <room.h>  

inherit ROOM;

int is_chat_room() { return 1; }  

void create() 
{
        set("short", "大隐阁");
        set("long", @LONG
这里是扬州客店附设的餐厅大堂，往来的旅人来到客店住宿歇脚，
大多会选择在此点几个具有扬州特色的小菜，就着温热的黄酒小酌几
杯，以驱散周身的疲累。现在尚未到用餐时间，是以偌大的厅内空荡
荡的，连侍候客人的店小二也不知躲到哪去了。靠墙竖着一块留言板，
上面密密麻麻写着许多过往客人留下的手迹。
LONG );

        set("no_fight", 1);
        set("no_drift", 1);
        set("no_steal", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1); 
        set("exits", ([
                "north"   : "/d/city/kedian",
        ]));
        set("objects", ([
                // "/adm/npc/huangdaxian" : 1,
        ]));

	set("coor/x", 10);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();

}
