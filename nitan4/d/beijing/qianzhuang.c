inherit ROOM;

void create()
{
	set("short", "����Ǯׯ");
        set("long", @LONG
����Ǯׯ�Ǿ���������һ��Ǯׯ���Ѿ��й��������ʷ�ˣ���
���൱�ĺá�Ǯׯ�Ĵ���������һ���߸ߵĹ�̨��Ǯׯ���ϰ����ڹ�
̨������������Ŀ����̨��ߵ�ǽ�Ϲ���һ������(paizi)��
LONG );
	set("item_desc", ([
        "paizi" : "\n��ׯ����Ϣ�����ٰٷ�֮һ��\n
      ��Ǯ        deposit����cun\n
      ȡǮ        withdraw����qu\n
      Ǯ�Ҷһ�    convert����duihuan\n
      ����        check����chazhang\n",
	]));
	set("exits", ([
		"south" : "/d/beijing/di_5",
	]));
	set("no_clean_up", 0);
	set("no_fight", 0);
	set("no_beg", 1);
	set("objects", ([
		"/d/beijing/npc/tiegongji" : 1
	]));

	set("coor/x", -40);
	set("coor/y", 330);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}
