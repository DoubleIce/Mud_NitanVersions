// Room: /d/shaolin/duchuan1.c

inherit ROOM;

void create()
{
	set("short", "渡船");
        set("long", @LONG
一叶小舟，一次就能载七、八个人。一名三十多岁日月教徒装扮
的艄公手持长竹篙，正在船尾撑着船，这艄公臂力惊人，小舟在他的
操控之下，一支箭般飞快地射向对岸。
LONG );
	set("no_clean_up", 0);
	set("outdoors", "heimuya");
	setup();
	replace_program(ROOM);
}

