//Room: /d/dali/louti.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","¥��");
        set("long", @LONG
�����ͨ����¥��ӭ��ի����¥�ݣ�¥�ݸ�����ʮ�༶��������
���ʺ��ëձ��¥������վ��һЩ������ʿ��¥�����ǹ����Ϣ�ĵ�
����
LONG );
	set("objects", ([
	   "/d/dali/npc/weishi": 3,
	   CLASS_D("dali")+"/gaoshengtai": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "up"      : "/d/dali/zoulang1",
	    "south"   : "/d/dali/dating",
	]));
	setup();
	replace_program(ROOM);
}
