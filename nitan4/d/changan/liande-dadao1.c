//Room: liande-dadao1.c

inherit ROOM;

void create ()
{
        set ("short", "���´��");
        set("long", @LONG
���ڽֵ������ϱ��������еĴ�֣��Ͷ����Ķ������ֻ��ཻ��
���ɡ���������������ʵ�ҹ����ȴ�������������ƻ�ͨ��������һ
�����֡�����С�ֺ��������Щ���ֽ������ã���Ȼ����
LONG );
        set("exits",([//sizeof() == 2
        	"south" : "/d/changan/liande-dadao2",
        	"north" : "/d/changan/liande-beikou",
        ]));

        set("outdoors", "changan");
        set("coor/x", -360);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
        