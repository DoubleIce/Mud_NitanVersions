#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ջ��");
        set("long", @LONG
ջ����ͨ�����Ĵ�����ԭ��Ψһ��·��Ϊ�����վ���ɽ���д�
������·����֪�������˶�������������Ҳ��֪���˶����ˡ�����·
���ؽ����޳ɵģ��ô�ľ׮���������ϣ���������ľ�壬���ܹ�һ��
���ˡ�ջ�������ʧ�ޣ���������ҡҡ�λεģ��ò�Σ�ա� 
LONG );
        set("exits", ([
  		"east" : __DIR__"shudao4",
  		"west" : __DIR__"shudao6",
   	]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("objects", ([
                "/d/beijing/npc/tiaofu" : 1,
        ]));
        set("coor/x", -190);
	set("coor/y", -180);
	set("coor/z", -60);
	setup();
        replace_program(ROOM);
}