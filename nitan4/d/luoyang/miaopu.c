inherit ROOM;

void create()
{
	set("short", "����");
        set("long", @LONG
δ��˴������µĻ������������ԡ������г����Ÿ�����������
����Ŀ������Ŀ��Ͼ�ӡ������䲻���������֣������������˵Ļ���
һ�ش�ʢ�ŵ�ĵ�������»�����ĵ��Ϊ������ĵ��֮����������ĵ��
Ϊ�𣬹ֲ������������������ô�����������������οͣ�Ҳ�е���
�������Ͳ��ָߵ͹�����������������Ц����ӭ��
LONG );
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
  		"east" : __DIR__"miaoyuan",
  		"west" : __DIR__"sroad7",
	]));
        set("objects", ([
                __DIR__"npc/huanong" : 1,
        ]));

	set("coor/x", -160);
	set("coor/y", -40);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}