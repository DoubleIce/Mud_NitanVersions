//Room: /d/dali/wuyiminju4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","�������");
        set("long", @LONG
����һ����ľ����Ƥ��ɵ�������ӡ��˵صĴ�����Ҫ���¸�
��������ʵ�л����ָ������ò�����Ǩ�㣬������ᶼ�ļ�ª��˵��
���ᣬ������˵�������񣬲𡢽��������㡣
LONG );
	set("objects", ([
	   "/d/dali/npc/kid": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/yixibu",
	]));
	setup();
	replace_program(ROOM);
}
