inherit ROOM;

void create()
{
	set("short", "����¥");
        set("long", @LONG
��¥�䲻�ھ��ǣ���ȴ����ԭ����������¥�����������ľƣ�
����İ��裬Ҳ�������ʵķ��񣬸�������Ů�ˣ����ɧ������
ζ��Ů�ˡ���Ȼ��ǰ������Ҫ���㹻��Ǯ��¥�ڵ����ŵƽ�ʣ�����
�˱ǡ������æ�Ĳ����ֺ���������������������Ů�˷�վ���Զ�
�㷢����Ц����¥�ϴ���������������ε��������������ϸ���һ
�����ͽ��ң���ɫ��԰��
LONG );
	set("no_clean_up", 0);
	set("exits", ([
  		"up" : __DIR__"jiyuan2",
  		"west" : __DIR__"sroad5",
	]));
        set("objects", ([
                __DIR__"npc/laobao" : 1,
                "/d/beijing/npc/jinv" : 1,
        ]));
	set("coor/x", -160);
	set("coor/y", -20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}