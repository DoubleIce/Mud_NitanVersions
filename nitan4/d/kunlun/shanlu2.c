inherit ROOM;

void create()
{
	set("short", "西域山路");
        set("long", @LONG
渐行渐西，天气一天冷似一天，西域昆仑派势力雄强，沿途倒并
无什么强盗，只是黄沙扑面，寒风透骨，却也着实难熬。
LONG );
        set("exits",([
		"eastdown" : __DIR__"shanlu1",
		"southup" : __DIR__"bayankala",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}
