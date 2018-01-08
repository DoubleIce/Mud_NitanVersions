inherit ROOM;

void create()
{
	set("short", "草原");
        set("long", @LONG
这里是一望无际的大草原。绿色的草地美丽得就象晴朗的蓝天。
草原上三三两两的羊群则是蓝天上飘浮的朵朵白云。远处的昆仑山在
骄阳下看来亮如纯银；到了夕阳西下时又变得灿烂如黄金。你也许从
没想到，在塞外的边陲之地竟有如此美妙的地方，美得辉煌而神秘，
美得令人迷惑。
LONG );
        set("outdoors", "gaochang");
	set("exits", ([
  		"westup" : __DIR__"caoyuan7",
  		"east" : __DIR__"xingxing2",
	]));
	setup();
	replace_program(ROOM);
}
