inherit ROOM;

void create()
{
	set("short", "�����");
        set("long", @LONG
Ӧ��������������һ��ռ����һ��ǽ�Ĵ���ͼ������Ϊ����������
����ϸ�壬�������֡���յ�񱭣�������칹����һ�����ص�в����
�����з��ż�����ʯԲ�������ϱ�յ�β�˸��޶���ÿ����ҹ��΢
��ϮϮ�����ǵ�㣻һ�����£����������롣���������������Ǿ���
�۵ס���񷰵����Ψ����һյ�����ﾡ����ΨӢ�����ˡ�
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"west" : __DIR__"jiyuan2",
	]));

	set("coor/x", -150);
	set("coor/y", -20);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}