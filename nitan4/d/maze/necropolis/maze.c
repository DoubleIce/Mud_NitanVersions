// write by starfish

#include <ansi.h>

inherit VRM_SERVER;

#define ENTER_ROOM_X	0
#define ENTER_ROOM_Y    0
#define ENTER_ROOM_Z    0

void create() 
{ 
        // �Թ��������̳е�����ĵ������ơ� 
        set_inherit_room( ROOM );  
			
        //Ψһ����
        set_unique_room( ({
                "/d/maze/necropolis/unique_room/skeleton_room",
                "/d/maze/necropolis/unique_room/ghost_room",
                "/d/maze/necropolis/unique_room/zombie_room",
                "/d/maze/necropolis/unique_room/rest_room",
                "/d/maze/necropolis/unique_room/quest_room",
        }) ); 

        //�Թ�������Ĺ�� 
        set_maze_npcs( ([
                "/d/maze/necropolis/npc/skeleton": !random(3),  
                "/d/maze/necropolis/npc/skeleton_fighter": !random(5),
                "/d/maze/necropolis/npc/skeleton_mage": !random(5),
                "/d/maze/necropolis/npc/zombie": !random(3),  
                "/d/maze/necropolis/npc/zombie_blood": !random(5),
                "/d/maze/necropolis/npc/zombie_power": !random(5),
                "/d/maze/necropolis/npc/ghost": !random(3),  
                "/d/maze/necropolis/npc/ghost_fire": !random(5),
                "/d/maze/necropolis/npc/ghost_eye": !random(5),
        ]) );	
	//��������		
        //set_no_death(1);
        
        //�Թ��ĵ��߳� 
        set_maze_long(10); 
			
        //��ڷ���(�����ڶ���) 
        set_entry_dir("north"); 
			
        //�������������ӷ��� 
        set_link_entry_dir("north"); 
			
        //�������������ӵ����� 
        set_link_entry_room(__DIR__"enter"); 
			
        //��������������ӷ��� 
        set_link_exit_dir("south"); 
			
        //��������������ӵ����� 
        set_link_exit_room(__DIR__"out"); 
			
        //�������������
        set_link_entry_room_x(ENTER_ROOM_X);
        set_link_entry_room_y(ENTER_ROOM_Y);
        set_link_entry_room_z(ENTER_ROOM_Z);
			
        //��ͨ��������
        set_maze_room_short(RED "����Ĺ԰" NOR);
			
        set_maze_room_desc(@LONG
Ĺ԰��û��һ�����������ϵ����ǿ�֦��Ҷ��ż������һЩ
�ɿݵĶ���ʬ�������˲�������������ɢ����һ��ʬ�׸��õ�
ζ����������һ˿������ڡ�
LONG); 
			
        //��ڷ�������� 
        set_entry_short(HIR "����Ĺ԰���" NOR); 
			
        //��ڷ������� 
        set_entry_desc(@LONG
Ĺ԰��û��һ�����������ϵ����ǿ�֦��Ҷ��ż������һЩ
�ɿݵĶ���ʬ�������˲�������������ɢ����һ��ʬ�׸��õ�
ζ����������һ˿������ڡ�
LONG); 
			
        //���ڷ�������� 
        set_exit_short(HIW "����Ĺ԰����" NOR); 
			
        //���ڷ������� 
        set_exit_desc(@LONG
Ĺ԰��û��һ�����������ϵ����ǿ�֦��Ҷ��ż������һЩ
�ɿݵĶ���ʬ�������˲�������������ɢ����һ��ʬ�׸��õ�
ζ����������һ˿������ڡ�
LONG); 

        // �Թ������Ƿ�Ϊ���ⷿ�䣿 
        set_outdoors(1); 
        
        set_maze_refresh(600); 
        set_remove_time(1800); 
        // �Թ�������ͽ���ȼ�
        set_enter_minlevel(20);
						
} 

string query_my_map(){  return read_file(__DIR__"maze.map");}
