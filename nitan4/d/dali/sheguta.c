//Room: /d/dali/sheguta.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","�߹���");
        set("long", @LONG
�߹���λ�ڴ������ڣ����ڵ��ɽб���嶫�¡��ഫ����������
�������١�����β�����ڣ���ˮ���ģ�����ʿ�γ��ֻ�����������
��ͬ���ھ������˽�������ˮ�ƣ����߹ǻ�����ˮ����Ϣ������һ��
�ܴ�ʽ����ש����
LONG );
	set("objects", ([
	   "/d/dali/npc/kid": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "east"  : "/d/dali/taihejiekou",
	    "west"  : "/d/dali/qingchi",
	]));
	setup();
	replace_program(ROOM);
}
