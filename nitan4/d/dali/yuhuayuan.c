//Room: /d/dali/yuhuayuan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","����԰");
        set("long", @LONG
�����Ǵ������ʹ�������԰�����ԵĻ��������涷�ޣ�������һ
��Сˮ�أ�ɽ����������Ȫˮ�ͻἯ�������ֻ�ɺ���ˮ��ץ�㣬
һ���������˵����ӣ������ǻ��ȣ�������ǰ�
LONG );
	set("objects", ([
	   "/d/dali/npc/xianhe": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/hualang",
	    "south"  : "/d/dali/qiandian",
	]));
	setup();
	replace_program(ROOM);
}
