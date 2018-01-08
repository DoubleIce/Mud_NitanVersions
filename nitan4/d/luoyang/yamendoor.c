inherit ROOM;

void create()
{
	set("short", "衙门");
        set("long", @LONG
这里是衙门大门，两扇朱木大门紧紧关闭着。『肃静』『回避』
的牌子分放两头石狮子的旁边。前面有一个大鼓，显然是供小民鸣冤
用的。几名衙役在门前巡逻。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"yamen",
  		"west" : __DIR__"nroad2",
	]));
        set("objects", ([
                "/d/zhongzhou/npc/yayi" : 4,
        ]));
	set("coor/x", -160);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
