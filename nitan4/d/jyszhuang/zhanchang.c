// ����ɽׯ�Թ�
// by Lonely
inherit "/adm/daemons/vrm_server.c";

void create()
{
        //Ψһ����
        set_unique_room( ({
                "/d/maze/necropolis/unique_room/skeleton_room",
                "/d/maze/necropolis/unique_room/ghost_room",
                "/d/maze/necropolis/unique_room/zombie_room",
                "/d/maze/necropolis/unique_room/rest_room",
                "/d/maze/necropolis/unique_room/quest_room",
        }) ); 

        // �Թ��������̳е�����ĵ������ơ�
        set_inherit_room( ROOM );

        //�Թ�������Ĺ��
        set_maze_npcs(__DIR__"npc/wolf");

        //�Թ��ĵ��߳�
        set_maze_long(8);

        //��ڷ���(�����ڶ���)
        set_entry_dir("east");

        //�������������ӷ���
        set_link_entry_dir("west");

        //�������������ӵ�����
        set_link_entry_room(__DIR__"shanlu");

        //��������������ӷ���
        set_link_exit_dir("west");

        //��������������ӵ�����
        set_link_exit_room(__DIR__"shanzhuang");

        //��ڷ��������
        set_entry_short("��Ұ");

        //��ڷ�������
        set_entry_desc(@LONG
�����Ǿ�˵�����Ϲ�ʱ�������ս����ַ���ഫԶ��ʱ��
�����Ĵ�����Ϸ��ĵĴ���Ϊ���������׵�Ȩ���������ﱬ��
��һ�����ҵĴ�ս����������Ѿ��ưܲ������Ӳݴ����Ļ�Ұ
֮���ˣ���С�ľͿ�����ʧ������.
LONG);

        //���ڷ��������
        set_exit_short("��Ұ");

        //���ڷ�������
        set_exit_desc(@LONG
����ǰһ������������˿��������������ǳ����ˡ�����С��
���������ͷ紵�����ֵ�ɳɳ����֯�������Ĵ���Ȼ�����ɡ�
LONG
);

        //�Թ�����Ķ�����
        set_maze_room_short("��ս��");

        //�Թ����������������ж�������������ÿ����
        //���ʱ���������ѡ��һ����
        set_maze_room_desc(@LONG
����Խ��Խ���ˣ��㵨���ľ�����ǰ�����ţ�������һЩ
��·�˵�ʬ������á���ʱ����һ��������˺�,������ʲô
�����ڰ��п����ţ��㲻�ɵļӿ��˽Ų���
LONG
);

        // �Թ������Ƿ�Ϊ���ⷿ�䣿
        set_outdoors(1);
/*
        set_valid_rooms( ({
        __DIR__"zhanchang",
}));
*/
        // create_maze();
}

