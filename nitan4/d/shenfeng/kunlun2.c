// Room: /u/mei/room54.c// This is a room made by roommaker. write by Fan. :)
inherit ROOM;
void create()
{
	set("short", "����ɽ");
        set("long", @LONG
ɽ�������･�����ߣ���Χ�ľ�����Ũ�����������֡�Ũ���е�
ˮ��������͸��������ѣ����������������ܡ��⡭�������˼�ͨ
�����õ�·������ͨ������֮�ţ�
LONG );
	set("exits", ([ /* sizeof() == 2 */
                "southup" : __DIR__"kunlun3",
                "eastdown" : __DIR__"kunlun1",
                "enter" : "/d/llszhuang/road",
]));
	set("no_new_clean_up", 0);
	set("outdoors", "kunlun");

	setup();
	replace_program(ROOM);
}