
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// 迷宫房间所继承的物件的档案名称。
	set_inherit_room( ROOM );

	// 迷宫进入要求最低等级。
	set_enter_min_level(4);

	// 迷宫进入要求最高等级。
	set_enter_max_level(9);

	// 迷宫房间时间ID和刷新时间。
	set_build_time("VRM_0502");

	//迷宫房间里的怪物。
	set_maze_npcs(VRM_NPC"0502/beast");

	// 迷宫中的怪物出现可能性
	set_maze_npcs_rate(50);

	//迷宫房间里的BOSS。
	set_maze_boss(VRM_NPC"0502/jinyinshe");

	//迷宫的单边长
	set_maze_long(5);

	//入口方向(出口在对面)
	set_entry_dir("north");

	//入口与区域的连接方向
	set_link_entry_dir("north");

	//入口与区域的连接档案名
	set_link_entry_room("/d/city/kezhan");

	//出口与区域的连接方向
	set_link_exit_dir("south");

	//出口与区域的连接档案名
	set_link_exit_room("/d/city/kezhan");

	//入口房间短描述
	set_entry_short("万蛇洞");

	//入口房间描述
	set_entry_desc(@LONG
这里面都是赤红的岩石。地上小沟流的居然是殷红的岩浆。一股股热浪扑人而来，
马上就会要了人的性命。那黑红的烟也毒的要命！洞窟四壁不断吞吐着火焰。
LONG
);

	//BOSS房间短描述
	set_exit_short("蛇洞中");

	//BOSS房间描述
	set_exit_desc(HIB"

这里就是万蛇洞底部。。。。。。
"NOR);

	//迷宫房间的短描述
	set_maze_room_short("万蛇洞");

	//迷宫房间的描述，如果有多条描述，制造每个房
	//间的时候会从中随机选择一个。
	set_maze_room_desc(@LONG
这里面都是赤红的岩石。地上小沟流的居然是殷红的岩浆。一股股热浪扑人而来，
马上就会要了人的性命。那黑红的烟也毒的要命！洞窟四壁不断吞吐着火焰。
LONG
);

	// 迷宫房间是否为户外房间？
	//set_outdoors(1);
}
