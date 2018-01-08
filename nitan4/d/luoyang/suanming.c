inherit ROOM;

void create()
{
	set("short", "茅草屋");
        set("long", @LONG
这是一座歪歪斜斜的茅草屋，墙头的颜色很怪，一种血色干凝的
暗红色。屋里更是鬼气森森。房子无窗，一盏油灯忽明忽暗。以太极
八卦图为底的招牌上用篆体刻着「刺青」二字，也是黯淡无光的红色。
LONG );
	set("no_clean_up", 0);
    set("no_sleep_room",1);
	set("exits", ([
  		"south" : __DIR__"hutong3",
	]));

	set("coor/x", -120);
	set("coor/y", 40);
	set("coor/z", 10);
	setup();
        "/adm/npc/qingyangzi"->come_here();
        replace_program(ROOM);
}
