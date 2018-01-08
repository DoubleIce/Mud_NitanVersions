#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "惊神峰"NOR);
        set("long", @LONG
你折而向北，又过了一岭，只见古柏三把百余章，皆挺直端秀，
凌霄托根树旁，作花柏顶，灿若云荼。走出十余丈，只听得琴声之中
杂有着无数鸟语，细细的听来，琴声竟似和鸟语互相应答，间间关关，
宛转啼鸣。只见三株大松树下一个白衣男子背向而坐，膝上放这一张
焦尾琴，整自弹奏。他身周树木上停满了鸟雀，黄莺，杜鹃，喜鹊，
八哥，还有许多不知其名的，和琴声或一问一答，或齐声和唱。
LONG );
	set("exits", ([
		"south" : __DIR__"sanshengao",
	]));

	set("objects",([
                CLASS_D("kunlun") + "/hezudao" : 1,
    	]));

        set("outdoors", "kunlun");
        setup();
	replace_program(ROOM);
}
