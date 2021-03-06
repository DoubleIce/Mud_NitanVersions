
#include <ansi.h>

inherit VRM_SERVER;

void create()
{
	// 迷宫房间所继承的物件的档案名称。
	set_inherit_room( ROOM );

	// 迷宫进入要求最低等级。

        set_lonely_create(1);

	// 迷宫进入要求最高等级。

	// 迷宫房间时间ID和刷新时间。
        set_remove_time(1800);

	//迷宫房间里的怪物。
        set_maze_npcs(__DIR__"npc/0003/beast");

	// 迷宫中的怪物出现可能性
        set_npcs_rate(50);

	//迷宫房间里的BOSS。
        set_exit_npcs(__DIR__"npc/0003/dragon");

	//迷宫的单边长
        set_maze_long(10);

	//入口方向(出口在对面)
	set_entry_dir("east");

	//入口与区域的连接方向
	set_link_entry_dir("east");

	//入口与区域的连接档案名
        set_link_entry_room("/d/xueshan/hubian3");

	//出口与区域的连接方向
	set_link_exit_dir("west");

	//出口与区域的连接档案名
        set_link_exit_room("/d/xueshan/hubian3");

	//入口房间短描述
	set_entry_short("苍之风云");

	//入口房间描述
	set_entry_desc(@LONG
你站在云端，向四周望去，四面是一望无际的云海，头顶是碧蓝的天空。
向下望去，只见一片青翠的绿色，偶尔有一些细细的白线贯穿其中。一只小黄
莺悄悄地从云丛中探出头来，很惊讶地看着你。
LONG
);

	//BOSS房间短描述
	set_exit_short("风之云");

	//BOSS房间描述
	set_exit_desc(HIW"

这里就是天之尽头。。。。。。
"NOR);

	//迷宫房间的短描述
	set_maze_room_short("苍之风云");

	//迷宫房间的描述，如果有多条描述，制造每个房
	//间的时候会从中随机选择一个。
	set_maze_room_desc(@LONG
你站在云端，向四周望去，四面是一望无际的云海，头顶是碧蓝的天空。
向下望去，只见一片青翠的绿色，偶尔有一些细细的白线贯穿其中。一只小黄
莺悄悄地从云丛中探出头来，很惊讶地看着你。
LONG
);

	// 迷宫房间是否为户外房间？
        set_outdoors(1);
}
