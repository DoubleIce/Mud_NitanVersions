
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// �Թ��������̳е�����ĵ������ơ�
	set_inherit_room( ROOM );

	// �Թ�����Ҫ����͵ȼ���
	set_enter_min_level(4);

	// �Թ�����Ҫ����ߵȼ���
	set_enter_max_level(9);

	// �Թ�����ʱ��ID��ˢ��ʱ�䡣
	set_build_time("VRM_0502");

	//�Թ�������Ĺ��
	set_maze_npcs(VRM_NPC"0502/beast");

	// �Թ��еĹ�����ֿ�����
	set_maze_npcs_rate(50);

	//�Թ��������BOSS��
	set_maze_boss(VRM_NPC"0502/jinyinshe");

	//�Թ��ĵ��߳�
	set_maze_long(5);

	//��ڷ���(�����ڶ���)
	set_entry_dir("north");

	//�������������ӷ���
	set_link_entry_dir("north");

	//�������������ӵ�����
	set_link_entry_room("/d/city/kezhan");

	//��������������ӷ���
	set_link_exit_dir("south");

	//��������������ӵ�����
	set_link_exit_room("/d/city/kezhan");

	//��ڷ��������
	set_entry_short("���߶�");

	//��ڷ�������
	set_entry_desc(@LONG
�����涼�ǳ�����ʯ������С�����ľ�Ȼ�������ҽ���һ�ɹ��������˶�����
���Ͼͻ�Ҫ���˵��������Ǻں����Ҳ����Ҫ���������ıڲ��������Ż��档
LONG
);

	//BOSS���������
	set_exit_short("�߶���");

	//BOSS��������
	set_exit_desc(HIB"

����������߶��ײ�������������
"NOR);

	//�Թ�����Ķ�����
	set_maze_room_short("���߶�");

	//�Թ����������������ж�������������ÿ����
	//���ʱ���������ѡ��һ����
	set_maze_room_desc(@LONG
�����涼�ǳ�����ʯ������С�����ľ�Ȼ�������ҽ���һ�ɹ��������˶�����
���Ͼͻ�Ҫ���˵��������Ǻں����Ҳ����Ҫ���������ıڲ��������Ż��档
LONG
);

	// �Թ������Ƿ�Ϊ���ⷿ�䣿
	//set_outdoors(1);
}
