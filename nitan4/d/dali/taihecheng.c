//Room: /d/dali/taihecheng.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","̫�ͳ�");
        set("long", @LONG
�˳�����������θ���ȫ����İ����ʯ�ݳɣ������࣬��������
���ϡ�̫�Ͳ����ǣ����˿�Ϊ�������٣������Ϻ;������Ǵ����
�ı��Ż������������������ڴ˼ӹ̳ǳأ���פ������������һЩ��
�Ĳ���۾ӡ�������һƬƽԭ����ʮ���������ǡ�
LONG );
	set("outdoors", "dali");
	set("objects",([
	    "/d/dali/npc/bing": 2,
	    "/d/dali/npc/jiang": 1,
	]));
	set("exits",([ /* sizeof() == 1 */
	    "north"  : "/d/dali/dehuabei",
	    "south"  : "/d/dali/dalinorth",
	]));
	setup();
	replace_program(ROOM);
}

