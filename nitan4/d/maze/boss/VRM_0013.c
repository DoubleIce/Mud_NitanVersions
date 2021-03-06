
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// 迷宫房间所继承的物件的档案名称。
	set_inherit_room( ROOM );

	// 迷宫进入要求最低等级。
	set_enter_min_level(5);

	// 迷宫进入要求最高等级。
	set_enter_max_level(13);

	// 迷宫房间时间ID和刷新时间。
	set_build_time("VRM_0013");

	//迷宫房间里的怪物。
	set_maze_npcs(VRM_NPC"0013/beast");

	// 迷宫中的怪物出现可能性
	set_maze_npcs_rate(50);

	//迷宫房间里的BOSS。
	set_maze_boss(VRM_NPC"0013/leijiu");

	//迷宫的单边长
	set_maze_long(8);

	//入口方向(出口在对面)
	set_entry_dir("east");

	//入口与区域的连接方向
	set_link_entry_dir("east");

	//入口与区域的连接档案名
	set_link_entry_room("/d/emei/shangu");

	//出口与区域的连接方向
	set_link_exit_dir("west");

	//出口与区域的连接档案名
	set_link_exit_room("/d/emei/shangu");

	//入口房间短描述
	set_entry_short("回音山谷");

	//入口房间描述
	set_entry_desc(HIY"
	是一个纵深七百二十米的断岩绝壁。这是悬崖下的小山谷，周围一片寂静。
偶尔一个碎石落下，传来阵阵回声。抑或阵阵雷鸣，震耳欲聋。
"NOR);

	//BOSS房间短描述
	set_exit_short("回音山谷");

	//BOSS房间描述
	set_exit_desc(HIY"
	是一个纵深七百二十米的断岩绝壁。这是悬崖下的小山谷，周围一片寂静。
偶尔一个碎石落下，传来阵阵回声。抑或阵阵雷鸣，震耳欲聋。
"NOR);

	//迷宫房间的短描述
	set_maze_room_short("回音山谷");

	//迷宫房间的描述，如果有多条描述，制造每个房
	//间的时候会从中随机选择一个。
	set_maze_room_desc(HIY"
	是一个纵深七百二十米的断岩绝壁。这是悬崖下的小山谷，周围一片寂静。
偶尔一个碎石落下，传来阵阵回声。抑或阵阵雷鸣，震耳欲聋。
"NOR);

	// 迷宫房间是否为户外房间？
	//set_outdoors(1);
}
