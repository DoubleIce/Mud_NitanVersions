//Room: /d/dali/titian1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","����");
        set("long", @LONG
����ˮ�ӹ��������ů������������ɽ�¿����˲�������˼�
���ǵ��£�����������¶��ϣ����ؿ����������֣������ϡ�裬��
�ĵ���ũҵ��Ϊ��󣬶��л����ָ�������ɽ�ϵ�һЩ�����������
���������š�
LONG );
	set("objects", ([
	   "/d/dali/npc/nongfu": 1,
	]));
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "west"      : "/d/dali/zhenxiong",
	]));
	setup();
	replace_program(ROOM);
}
