#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
�Ϸ���������壬�ǻ�ɽ��߷塣��ͷ��̼��࣬�硺̫����ͷ
�������������졻����������ǡ��ȣ����Ի���֮�ߡ��������ܣ���
�����¡���׼ʫ��Ի��ֻ�������ϣ�����ɽ���룻��ͷ���ս�������
���Ƶ͡���˵���ʱ�����ʿ���Ҿ������������̫��������گ��
����ɽ���٣�����������д��лگ��˵����һƬҰ�Ķ���������ס��
���س�گ�ݽ̵�������������ʾ��Ը��ɽ���١�
LONG );
        set("exits", ([
                "northdown" : __DIR__"zhandao",
        ]));
        /*
        if (random(10) > 8)
	        set("objects", ([
        	         CLASS_D("huashan") + "/feng" : 1,
        	]));
        */
        set("outdoors", "huashan");
        setup();
        replace_program(ROOM);
}