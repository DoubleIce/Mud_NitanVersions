// Room: /d/quanzhou/nanhu1.c
// Date: May 21, 96   Jay

inherit ROOM;

void create()
{
	set("short", "�����Ϻ�");
        set("long", @LONG
�������̲��������Ϻ������ϼ�ֻ�������ε������ϵ��οͺ���
¥Ů������Ц����ˮ���û�д��Ƕɲ���ȥ�ġ�����֪��˭�ں���
����һЩľ׮��׮��Ǳ��ˮ��֮��һ����ĵط�����ʹ�ǲ����Ṧ��
������ȥҲ����ˮ��Ư�����ӡ�
LONG );
	set("exits", ([
		"south"     : __DIR__"yanyu",
                "northwest" : __DIR__ "nanhu",
	]));
	set("outdoors", "jiaxing");
	set("coor/x", 100);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}