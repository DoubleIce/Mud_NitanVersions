// Room: /d/fuzhou/xiaochang.c
// Date: may.12 1998 Java
inherit ROOM;

void create()
{
	set("short", "У��");
        set("long", @LONG
����У��Ϊ����ˮʦУ�������е㽫¥�ϸ߹ҡ�ʩ���ֺ�����
˧�죬��ǹҫ�����ԡ�ˮʦ�ᶽʩ��ʩ��������ʮ���۱�������������
׳�Ĳ��ѡ�
LONG );
	set("exits", ([ /* sizeof() == 1 */
	    "west"   : __DIR__"nanmendou",
	]));
	set("outdoors", "fuzhou");
	set("coor/x", 160);
	set("coor/y", -130);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}