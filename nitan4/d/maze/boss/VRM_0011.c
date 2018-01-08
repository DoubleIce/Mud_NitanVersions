
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// �Թ��������̳е�����ĵ������ơ�
	set_inherit_room( ROOM );

	// �Թ�����Ҫ����͵ȼ���
	set_enter_min_level(10);

	// �Թ�����Ҫ����ߵȼ���
	set_enter_max_level(20);

	// �Թ�����ʱ��ID��ˢ��ʱ�䡣
	set_build_time("VRM_0011");

	//�Թ�������Ĺ��
	set_maze_npcs(VRM_NPC"0011/beast");

	// �Թ��еĹ�����ֿ�����
	set_maze_npcs_rate(50);

	//�Թ��������BOSS��
	set_maze_boss(VRM_NPC"0011/shujing");

	//�Թ��ĵ��߳�
	set_maze_long(5);

	//��ڷ���(�����ڶ���)
	set_entry_dir("north");

	//�������������ӷ���
	set_link_entry_dir("north");

	//�������������ӵ�����
	set_link_entry_room("/d/fangzhang/dongbian");

	//��������������ӷ���
	set_link_exit_dir("south");

	//��������������ӵ�����
	set_link_exit_room("/d/fangzhang/dongbian");

	//��ڷ��������
	set_entry_short("������");

	//��ڷ�������
	set_entry_desc(@LONG
����һƬï�ܵ����֣��������Ʈ����ֻ��ͷ��Ŀѣ��������
�����һ����һ�߽�������·���ʧ�˷��򡣲�ʱ���ȷ紵����
������������
LONG
);

	//BOSS���������
	set_exit_short("������");

	//BOSS��������
	set_exit_desc(HIB"

�����������ɭ�ֵײ�������������
"NOR);

	//�Թ�����Ķ�����
	set_maze_room_short("������");

	//�Թ����������������ж�������������ÿ����
	//���ʱ���������ѡ��һ����
	set_maze_room_desc(@LONG
����һƬï�ܵ����֣��������Ʈ����ֻ��ͷ��Ŀѣ��������
�����һ����һ�߽�������·���ʧ�˷��򡣲�ʱ���ȷ紵����
������������
LONG
);

	// �Թ������Ƿ�Ϊ���ⷿ�䣿
	//set_outdoors(1);
}
