inherit ROOM;

void create()
{
	set("short", "卧室");
        set("long", @LONG
这里就是郭靖和黄蓉的卧室。屋子里的陈设很简单。门的左边有
一张软床。床上的被褥被叠得整整齐齐。床头正对的地方摆着一张梳
妆台。桌上摆着一个光亮的铜镜，铜镜旁边的花瓶里，有一束百合花，
正在散发出淡淡的幽香。里边放着两张木椅，中间是一茶几，上面摆
着一盆山茶花。
LONG );
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("exits", ([
		"west" : __DIR__"guofu_huayuan",
	]));
	setup();
	replace_program(ROOM);
}

