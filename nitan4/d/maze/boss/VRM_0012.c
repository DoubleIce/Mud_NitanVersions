
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// 迷宫房间所继承的物件的档案名称。
	set_inherit_room( ROOM );

	// 迷宫进入要求最低等级。
	set_enter_min_level(6);

	// 迷宫进入要求最高等级。
	set_enter_max_level(12);

	// 迷宫房间时间ID和刷新时间。
	set_build_time("VRM_0012");

	//迷宫房间里的怪物。
	set_maze_npcs(VRM_NPC"0012/beast");

	// 迷宫中的怪物出现可能性
	set_maze_npcs_rate(50);

	//迷宫房间里的BOSS。
	set_maze_boss(VRM_NPC"0012/baihuaxianzi");

	//迷宫的单边长
	set_maze_long(7);

	//入口方向(出口在对面)
	set_entry_dir("north");

	//入口与区域的连接方向
	set_link_entry_dir("north");

	//入口与区域的连接档案名
	set_link_entry_room("/d/penglai/bomingyan");

	//出口与区域的连接方向
	set_link_exit_dir("south");

	//出口与区域的连接档案名
	set_link_exit_room("/d/penglai/bomingyan");

	//入口房间短描述
	set_entry_short("百花谷");

	//入口房间描述
	set_entry_desc(HIM"
	一片平坦谷地，四周是青山环绕，山腰间白云悠悠，真是一片神仙福地。
谷内四季常春，各色鲜花，竞相争艳，满目青翠萦目，红紫迎人，好一片锦绣乾
坤，花花世界。
"NOR);

	//BOSS房间短描述
	set_exit_short("百花谷中");

	//BOSS房间描述
	set_exit_desc(HIM"
	一片平坦谷地，四周是青山环绕，山腰间白云悠悠，真是一片神仙福地。
谷内四季常春，各色鲜花，竞相争艳，满目青翠萦目，红紫迎人，好一片锦绣乾
坤，花花世界。
"NOR);

	//迷宫房间的短描述
	set_maze_room_short("百花谷内");

	//迷宫房间的描述，如果有多条描述，制造每个房
	//间的时候会从中随机选择一个。
	set_maze_room_desc(HIM"
	一片平坦谷地，四周是青山环绕，山腰间白云悠悠，真是一片神仙福地。
谷内四季常春，各色鲜花，竞相争艳，满目青翠萦目，红紫迎人，好一片锦绣乾
坤，花花世界。
"NOR);

	// 迷宫房间是否为户外房间？
	//set_outdoors(1);
}
