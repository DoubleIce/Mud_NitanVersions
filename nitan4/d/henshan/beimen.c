inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������������Ǵ����ĺ��ţ����ں�ɽɽ´��������������ǽ
���ߣ���̻Ի͡���������ɽ����С·��
LONG );
        set("exits", ([ 
                "south"  : __DIR__"houdian",
                "northup": __DIR__"shanlu1",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

        set("coor/x", 0);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
