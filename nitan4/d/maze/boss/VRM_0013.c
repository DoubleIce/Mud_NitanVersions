
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// �Թ��������̳е�����ĵ������ơ�
	set_inherit_room( ROOM );

	// �Թ�����Ҫ����͵ȼ���
	set_enter_min_level(5);

	// �Թ�����Ҫ����ߵȼ���
	set_enter_max_level(13);

	// �Թ�����ʱ��ID��ˢ��ʱ�䡣
	set_build_time("VRM_0013");

	//�Թ�������Ĺ��
	set_maze_npcs(VRM_NPC"0013/beast");

	// �Թ��еĹ�����ֿ�����
	set_maze_npcs_rate(50);

	//�Թ��������BOSS��
	set_maze_boss(VRM_NPC"0013/leijiu");

	//�Թ��ĵ��߳�
	set_maze_long(8);

	//��ڷ���(�����ڶ���)
	set_entry_dir("east");

	//�������������ӷ���
	set_link_entry_dir("east");

	//�������������ӵ�����
	set_link_entry_room("/d/emei/shangu");

	//��������������ӷ���
	set_link_exit_dir("west");

	//��������������ӵ�����
	set_link_exit_room("/d/emei/shangu");

	//��ڷ��������
	set_entry_short("����ɽ��");

	//��ڷ�������
	set_entry_desc(HIY"
	��һ�������߰ٶ�ʮ�׵Ķ��Ҿ��ڡ����������µ�Сɽ�ȣ���ΧһƬ�ž���
ż��һ����ʯ���£���������������ֻ��������������������
"NOR);

	//BOSS���������
	set_exit_short("����ɽ��");

	//BOSS��������
	set_exit_desc(HIY"
	��һ�������߰ٶ�ʮ�׵Ķ��Ҿ��ڡ����������µ�Сɽ�ȣ���ΧһƬ�ž���
ż��һ����ʯ���£���������������ֻ��������������������
"NOR);

	//�Թ�����Ķ�����
	set_maze_room_short("����ɽ��");

	//�Թ����������������ж�������������ÿ����
	//���ʱ���������ѡ��һ����
	set_maze_room_desc(HIY"
	��һ�������߰ٶ�ʮ�׵Ķ��Ҿ��ڡ����������µ�Сɽ�ȣ���ΧһƬ�ž���
ż��һ����ʯ���£���������������ֻ��������������������
"NOR);

	// �Թ������Ƿ�Ϊ���ⷿ�䣿
	//set_outdoors(1);
}
