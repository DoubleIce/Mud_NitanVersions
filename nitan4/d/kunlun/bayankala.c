inherit ROOM;

void create()
{
        set("short", "���տ���ɽ");
        set("long", @LONG
���տ���ɽɽ�Ƶ�ƽ����������ɽ��ڣ�����ͨ���֧��������
��������鲼����ɽ���·�����ȥ���洦�ɼ�һ��������ݵ飬����
������������ĺõط���Զ��ɢ����һ����������ɹŰ���
LONG );
        set("exits",([
                "northdown" : __DIR__"shanlu2",
                "west" : __DIR__"kekexili",
        ]));

        set("objects",([
                __DIR__"obj/da-shitou" :  1,
        ]));

        set("outdoors", "kunlun");
        setup();
        replace_program(ROOM);
}
