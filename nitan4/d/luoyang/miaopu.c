inherit ROOM;

void create()
{
	set("short", "苗铺");
        set("long", @LONG
未入此处，清新的花香已沁人心裨。苗铺中陈列着各种名花，玲
琅满目，令人目不暇接。其中虽不乏珍奇异种，但是最吸引人的还是
一簇簇盛放的牡丹，天下花卉以牡丹为王，而牡丹之中又以洛阳牡丹
为尊，怪不得这里的生意总是那么的兴旺，既有外来游客，也有当地
居民，来客不分高低贵贱，这里的主人总是笑脸相迎。
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"miaoyuan",
  		"west" : __DIR__"sroad7",
	]));
        set("objects", ([
                __DIR__"npc/huanong" : 1,
        ]));

	set("coor/x", -160);
	set("coor/y", -40);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
