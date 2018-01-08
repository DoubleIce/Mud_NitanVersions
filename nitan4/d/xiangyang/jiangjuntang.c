// Room: /d/xiangyang/jiangjuntang.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
	set("short", "将军府大堂");
        set("long", @LONG
这里是将军府的大堂，公案后端坐着一个威猛的将军，但一脸疲
惫，看来征战刚归的模样。大堂两边摆着兵器架，架上锋刃仍留血迹，
映着架后的战旗，分外耀眼。两班将佐，虽征尘未洗，但斗志昂扬，
甚是雄壮。
LONG );
	set("exits", ([
		"south" : "/d/xiangyang/jiangjunyuan",
	]));
	set("objects", ([
		"/d/xiangyang/npc/wang" : 1,
		"/d/xiangyang/npc/zuo" : 1,
		"/d/xiangyang/npc/pian" : 1,
		"/d/xiangyang/npc/ya" : 1,
		"/d/xiangyang/npc/pi" : 1,
	]));
	set("coor/x", -280);
	set("coor/y", -60);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

