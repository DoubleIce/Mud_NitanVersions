#include <ansi.h>
inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "���ݱ���");
        set("long", @LONG
�������ݳǵı����ţ���������Ļ��������������ķ�ɳ��
ʴ�Ե���Щ�ưܡ��������Ϸ�����ǿǿ�����ϳ������������֣���ǽ
�����ż���ͨ����ʾ(gaoshi)������ﷸ�������������ӵ����򣬹�
���ǽ䱸ɭ�ϣ��������ͽ�ס���˽������ʡ�һ����ֱ����ʯ�����
�ϱ��������졣�����ǽ��⣬��������������˶���������ǡ����
������Ҳ�������ڴ����ﾭ����������ȥ�����Լ��ֵĹϹ��������
�������Ʒ���ϱ��ǳ��
LONG );
        set("outdoors", "lanzhou");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "north" : __DIR__"nroad1",
 		"south" : __DIR__"beidajie2",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 4,
                "/clone/npc/xunbu" : 1,
                "/d/beijing/npc/ducha" : 1,
        ]));
        set("coor/x", -510);
	set("coor/y", 140);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n         ����֪��\n                     Ү��Ѳ\n";
}
