
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// 迷宫房间所继承的物件的档案名称。
	set_inherit_room( ROOM );

	// 迷宫进入要求最低等级。
	set_enter_min_level(10);

	// 迷宫进入要求最高等级。
	set_enter_max_level(20);

	// 迷宫房间时间ID和刷新时间。
	set_build_time("VRM_0014");

	//迷宫房间里的怪物。
	set_maze_npcs(VRM_NPC"0014/beast");

	// 迷宫中的怪物出现可能性
	set_maze_npcs_rate(50);

	//迷宫房间里的BOSS。
	set_maze_boss(VRM_NPC"0014/leishen");

	//迷宫的单边长
	set_maze_long(10);

	//入口方向(出口在对面)
	set_entry_dir("east");

	//入口与区域的连接方向
	set_link_entry_dir("east");

	//入口与区域的连接档案名
	set_link_entry_room("/d/fangzhang/shanding");

	//出口与区域的连接方向
	set_link_exit_dir("west");

	//出口与区域的连接档案名
	set_link_exit_room("/d/fangzhang/shanding");

	//入口房间短描述
	set_entry_short("九天雷云");

	//入口房间描述
	set_entry_desc(HIC"
	你站在云端，向四周望去，四面是一望无际的云海，头顶是碧蓝的天空。
向下望去，只见一片青翠的绿色，偶尔有一些细细的白线贯穿其中。一只小黄莺
悄悄地从云丛中探出头来，很惊讶地看着你。
"NOR);

	//BOSS房间短描述
	set_exit_short("九天雷云");

	//BOSS房间描述
	set_exit_desc(HIC"
	你站在云端，向四周望去，四面是一望无际的云海，头顶是碧蓝的天空。
向下望去，只见一片青翠的绿色，偶尔有一些细细的白线贯穿其中。一只小黄莺
悄悄地从云丛中探出头来，很惊讶地看着你。
"NOR);

	//迷宫房间的短描述
	set_maze_room_short("九天雷云");

	//迷宫房间的描述，如果有多条描述，制造每个房
	//间的时候会从中随机选择一个。
	set_maze_room_desc(HIC"
	你站在云端，向四周望去，四面是一望无际的云海，头顶是碧蓝的天空。
向下望去，只见一片青翠的绿色，偶尔有一些细细的白线贯穿其中。一只小黄莺
悄悄地从云丛中探出头来，很惊讶地看着你。
"NOR);

	// 迷宫房间是否为户外房间？
	//set_outdoors(1);
}
