inherit ROOM;

void create()
{
	set("short", "落燕厅");
        set("long", @LONG
四小厅借沉鱼落燕羞花闭月之典故而起名，此厅内高爽宽敞，窗
台明亮。堂中挂一幅无名小画，设一张白木卧榻。桌凳之类，色色洁
净。打扫得地下无纤毫尘垢。堂中花卉无所不有，十分繁茂。真个四
时不谢，八节长春。
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"east" : __DIR__"jiyuan2",
	]));

	set("coor/x", -170);
	set("coor/y", -20);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}
