// road4.c С��

inherit ROOM;

void create()
{
        object ob;

	set("short", "С��");
        set("long", @LONG
����һ�����ѵ�С������������ͨ��ɽ�·���Ϲ⻬ƽʵ����
���Ǿ������������������Ѿ���ɽ���ˣ�ɽ������һЩ���������
����һЩé�ݡ�ֻ�ж��߲�Զ�ĵط���һ��Сש������Ͳ����ʱ��ʱ
ð��һ�ɹɺ��̣������Ǵ���
LONG );

	set("exits", ([
                "southwest" : __DIR__"road3",
                "east"      : __DIR__"road5",
	]));
	set("outdoors", "suzhou");
	setup();
}

