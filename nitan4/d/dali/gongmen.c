//Room: /d/dali/road1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","");
	set("short", "����");
        set("long", @LONG
�����Ǵ����ʹ��Ĺ��ţ��ſڷ��������ߴ�ʯʨ�������ʵ�û��
һ����ӣ���������ֹ���ǽ���ʹ������������֣������ͽ���ʹ�
�ˡ�
LONG );
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/qiandian",
	    "south"  : "/d/dali/yujie",
	]));
	setup();
}
