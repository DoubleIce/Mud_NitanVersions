inherit ROOM;

void create()
{
	set("short", "金刀王家");
        set("long", @LONG
这里便是洛阳金刀王家的府邸，江湖上提起金刀无敌王元霸当真
是无人不知，无人不晓。只见这府邸房舍高大，朱红漆的大门，门上
两个大铜环，擦得晶光雪亮，八名壮汉垂手在大门外侍候。一进大门，
只见梁上悬着一块黑漆大匾，写着『见义勇为』四个金字，下面落款
是河南省的巡抚某人。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"north" : __DIR__"wroad3",
	]));
        set("objects", ([
                "/d/zhongzhou/npc/jiading" : 2,
        ]));
	set("coor/x", -200);
	set("coor/y", -10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
