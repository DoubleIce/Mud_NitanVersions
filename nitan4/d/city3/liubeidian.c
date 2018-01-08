// Room: liubeidian.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
	set("short", "刘备殿");
        set("long", @LONG
这里是武侯祠的刘备殿。正中供着汉昭烈帝，高可丈许。后主却
没得供奉，所谓 "扶不起来" 的阿斗吧。而哭庙玉碎的北地王刘谌得
能和英父同祀，令人不胜唏嘘。    殿下左右是赵云等的武将廊和蒋
琬为首的文臣廊。
LONG );
	set("exits", ([
		"south"   : "/d/city3/wuhoucigate",
		"northup" : "/d/city3/wuhouci",
	]));
	set("no_clean_up", 0);
	set("coor/x", -450);
	set("coor/y", -200);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
