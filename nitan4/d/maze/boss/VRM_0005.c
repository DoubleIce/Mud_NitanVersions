
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
	set_build_time("VRM_0005");

	//迷宫房间里的怪物。
	set_maze_npcs(VRM_NPC"0005/beast");

	// 迷宫中的怪物出现可能性
	set_maze_npcs_rate(50);

	//迷宫房间里的BOSS。
	set_maze_boss(VRM_NPC"0005/dragon");

	//迷宫的单边长
	set_maze_long(7);

	//入口方向(出口在对面)
	set_entry_dir("south");

	//入口与区域的连接方向
	set_link_entry_dir("south");

	//入口与区域的连接档案名
	set_link_entry_room("/d/qujing/firemount/shanbian");

	//出口与区域的连接方向
	set_link_exit_dir("north");

	//出口与区域的连接档案名
	set_link_exit_room("/d/qujing/firemount/shanbian");

	//入口房间短描述
	set_entry_short("火龙窟");

	//入口房间描述
	set_entry_desc(@LONG
火焰山附近的一个山洞，里面都是赤红的岩石。地上小沟流的居然是
殷红的岩浆。一股股热浪扑人而来，马上就会要了人的性命。那黑红的烟
也毒的要命！洞窟四壁不断吞吐着火焰。
LONG
);

	//BOSS房间短描述
	set_exit_short("火之痕");

	//BOSS房间描述
	set_exit_desc(HIR"

这里就是火焰山底部。。。。。。
"NOR);

	//迷宫房间的短描述
	set_maze_room_short("火龙窟");

	//迷宫房间的描述，如果有多条描述，制造每个房
	//间的时候会从中随机选择一个。
	set_maze_room_desc(@LONG
火焰山附近的一个山洞，里面都是赤红的岩石。地上小沟流的居然是
殷红的岩浆。一股股热浪扑人而来，马上就会要了人的性命。那黑红的烟
也毒的要命！洞窟四壁不断吞吐着火焰。
LONG
);

	// 迷宫房间是否为户外房间？
	//set_outdoors(1);
}
