//Room: fufeng5.c

inherit ROOM;

void create ()
{
        set ("short", "�����");
        set("long", @LONG
������ǳ��������Ĵ�֣���ʯ��·��ֱ����չ��ȥ��һ·����
�˱ȼ磬�ϸ账��������֮����ֱ�����ɾ��ء������������֡�
LONG );
        set("exits", 
        ([ //sizeof() == 2
		"north" : "/d/changan/fufeng4",
        	"east" : "/d/changan/qinglong1",
        ]));

        set("outdoors", "changan");
        set("coor/x", -420);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}