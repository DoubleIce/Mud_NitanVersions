inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǵ������ڵ����ȡ������е��İ����컨������һЩ��֪��
ȷ�к���ĵ�̣�ǽ�������Ǻ�ͨ�׵ķ𾭹��±ڻ��ˡ����ϵ��ż�
��󺣵�������
LONG );
        set("exits", ([
                "southdown" : __DIR__"cedian1",
                "west"      : __DIR__"dating",
                "east"      : __DIR__"dumudian",
                "north"     : __DIR__"zoulang3",
        ]));
        setup();
}