inherit ROOM;

void create()
{
	set("short", "������");
        set("long", @LONG
���������ܹ��򵽸���������Ҫ�Ĵ������۸񰺹���У��۸��
����Ҳ�У�ƽʱ�����ؾ�����������һЩ�谡�����밡֮����
�㲻���ˡ���Ȼ�󾰵�����մ�����Ʒ������������������Ҳ�е�����
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"south" : __DIR__"eroad3",
	]));
        set("objects", ([
                __DIR__"npc/han" : 1,
        ]));
	set("coor/x", -140);
	set("coor/y", 10);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}