
inherit VRM_SERVER;
#include <vrm.h>

void create()
{
	// �Թ��������̳е�����ĵ������ơ�
	set_inherit_room( ROOM );

	// �Թ�����Ҫ����͵ȼ���
	set_enter_min_level(6);

	// �Թ�����Ҫ����ߵȼ���
	set_enter_max_level(12);

	// �Թ�����ʱ��ID��ˢ��ʱ�䡣
	set_build_time("VRM_0012");

	//�Թ�������Ĺ��
	set_maze_npcs(VRM_NPC"0012/beast");

	// �Թ��еĹ�����ֿ�����
	set_maze_npcs_rate(50);

	//�Թ��������BOSS��
	set_maze_boss(VRM_NPC"0012/baihuaxianzi");

	//�Թ��ĵ��߳�
	set_maze_long(7);

	//��ڷ���(�����ڶ���)
	set_entry_dir("north");

	//�������������ӷ���
	set_link_entry_dir("north");

	//�������������ӵ�����
	set_link_entry_room("/d/penglai/bomingyan");

	//��������������ӷ���
	set_link_exit_dir("south");

	//��������������ӵ�����
	set_link_exit_room("/d/penglai/bomingyan");

	//��ڷ��������
	set_entry_short("�ٻ���");

	//��ڷ�������
	set_entry_desc(HIM"
	һƬƽ̹�ȵأ���������ɽ���ƣ�ɽ����������ƣ�����һƬ���ɸ��ء�
�����ļ���������ɫ�ʻ����������ޣ���Ŀ�����Ŀ������ӭ�ˣ���һƬ����Ǭ
�����������硣
"NOR);

	//BOSS���������
	set_exit_short("�ٻ�����");

	//BOSS��������
	set_exit_desc(HIM"
	һƬƽ̹�ȵأ���������ɽ���ƣ�ɽ����������ƣ�����һƬ���ɸ��ء�
�����ļ���������ɫ�ʻ����������ޣ���Ŀ�����Ŀ������ӭ�ˣ���һƬ����Ǭ
�����������硣
"NOR);

	//�Թ�����Ķ�����
	set_maze_room_short("�ٻ�����");

	//�Թ����������������ж�������������ÿ����
	//���ʱ���������ѡ��һ����
	set_maze_room_desc(HIM"
	һƬƽ̹�ȵأ���������ɽ���ƣ�ɽ����������ƣ�����һƬ���ɸ��ء�
�����ļ���������ɫ�ʻ����������ޣ���Ŀ�����Ŀ������ӭ�ˣ���һƬ����Ǭ
�����������硣
"NOR);

	// �Թ������Ƿ�Ϊ���ⷿ�䣿
	//set_outdoors(1);
}
