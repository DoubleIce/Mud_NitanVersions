inherit ROOM;

void create()
{
	set("short", "ɽ·");
        set("long", @LONG
ǰ�洫�������������������쵽�ˣ��㲻�ɵüӿ��˽Ų���ԶԶ
��ȥ���ƺ��Ǹ���㳡��Χ�Ų����������䡣
LONG );
        set("exits",([
		"northdown" : __DIR__"shanlu03",
		"south" : __DIR__"guangchang",
		"southwest" : __DIR__"guangchangw",
		"southeast" : __DIR__"guangchange",
	]));

	set("outdoors", "kunlun");
	setup();
	replace_program(ROOM);
}