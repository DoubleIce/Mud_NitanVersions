inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
��λ�����ɽ���һ��Ƭ���֣�������Ϊï�ܡ��������ֻ����
����ɳɳ����Ҷ�������ܻ�谵���ģ���ʱ�����չ⴩��Ũ�ܵ�֦ͷ��
Ͷ����¡�ż��Զ�������޺�����������һ�����ܸС��������ϸ���
һ��С����
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "southup"   : __DIR__"shandao2",
                "north"     : __DIR__"shulin11",
        ]));
        setup();
        replace_program(ROOM);
}