#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "九曲廊");
        set("long", @LONG
九曲廊前后共有九进，曲曲折折地盘旋在水面。一路穿花度柳，
抚石依泉，落花浮荡，水色溶溶。两边垂柳杂着桃杏藤蔓绕柱。白石
为栏，飞楼插空，转折处皆由小亭相接。
LONG );
	set("exits",([
		"northwest" : __DIR__"shanlin1",
		"southeast" : __DIR__"sanshengtang",
	]));
	setup();
	replace_program(ROOM);
}
