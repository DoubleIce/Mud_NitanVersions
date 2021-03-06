
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
	set_build_time("VRM_0011");

	//迷宫房间里的怪物。
	set_maze_npcs(VRM_NPC"0011/beast");

	// 迷宫中的怪物出现可能性
	set_maze_npcs_rate(50);

	//迷宫房间里的BOSS。
	set_maze_boss(VRM_NPC"0011/shujing");

	//迷宫的单边长
	set_maze_long(5);

	//入口方向(出口在对面)
	set_entry_dir("north");

	//入口与区域的连接方向
	set_link_entry_dir("north");

	//入口与区域的连接档案名
	set_link_entry_room("/d/fangzhang/dongbian");

	//出口与区域的连接方向
	set_link_exit_dir("south");

	//出口与区域的连接档案名
	set_link_exit_room("/d/fangzhang/dongbian");

	//入口房间短描述
	set_entry_short("迷雾林");

	//入口房间描述
	set_entry_desc(@LONG
这是一片茂密的树林，阵阵黑雾飘来，只觉头晕目眩。好象被人
设计了一种阵，一走进来，你仿佛迷失了方向。不时有腥风吹来，
发出阵阵恶臭。
LONG
);

	//BOSS房间短描述
	set_exit_short("迷雾中");

	//BOSS房间描述
	set_exit_desc(HIB"

这里就是迷雾森林底部。。。。。。
"NOR);

	//迷宫房间的短描述
	set_maze_room_short("迷雾林");

	//迷宫房间的描述，如果有多条描述，制造每个房
	//间的时候会从中随机选择一个。
	set_maze_room_desc(@LONG
这是一片茂密的树林，阵阵黑雾飘来，只觉头晕目眩。好象被人
设计了一种阵，一走进来，你仿佛迷失了方向。不时有腥风吹来，
发出阵阵恶臭。
LONG
);

	// 迷宫房间是否为户外房间？
	//set_outdoors(1);
}
