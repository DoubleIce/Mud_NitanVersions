inherit ROOM;

void create()
{
        set("short", "��÷԰");
        set("long", @LONG
������������÷������ɫ��ǳһ���һ����ٴ�˿������״���ƺ�
÷����ɽ�е����������ഫ��һ������۰�÷֦�����Ƹ��ϣ��ö���
�ϣ��ɴ����֡���˵��÷���˲��ɴ����䵱ɽ��Υ�߱��ⲻ����
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/shouyuan": 1,
        ]));
        set("exits", ([
                "northup"  : __DIR__"taiziyan",
                "southup"  : __DIR__"wuyaling",
                "westup"   : __DIR__"nanyanfeng",
        ]));
        set("outdoors", "wudang");
	set("coor/x", -350);
	set("coor/y", -320);
	set("coor/z", 100);
	setup();
        replace_program(ROOM);
}