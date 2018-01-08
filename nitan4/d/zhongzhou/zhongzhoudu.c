#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
  	set ("short", "中州渡");
        set("long", @LONG
这是通往扬州城的渡口，前面就是滚滚长江 (river)，浊流滚滚，
万舟竞发。两岸渡船来来往往。向南通过中州大桥径直走就是中州府
了。
LONG );
        set("arrive_room", "/d/zhongzhou/yangzhoudu");
  	set("exits", ([
  		"south" : __DIR__"dukoulu",
	]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

  	set("outdoors", "zhongzhou");
        set("coor/x", -230);
	set("coor/y", 90);
	set("coor/z", 0);
	setup();
        replace_program(RIVER);
}
