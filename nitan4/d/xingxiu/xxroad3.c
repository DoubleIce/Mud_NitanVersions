inherit ROOM;

void create()
{
        set("short", "����ɽ");
        set("long", @LONG
����һ����̫�ߵ�Сɽ��ɽ����ȥ�����������Ʈ�ż��䵭����
���ơ�һȺ���㷢�����¸¡��Ľ�������ͷ�Ϸɹ�������ɽ�³��ǵ�
��ԫ�ϱ���ϡ�ɱ档���ǵľ�ͷ��һ����ΰ�Ĺذ���·����һ������
֮�Ͽ����״ʡ�
LONG );
        set("exits", ([
            "westdown" : __DIR__ "jiayuguan",
            "east" : "/d/lanzhou/ximen",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xingxiu");

        setup();
        replace_program(ROOM);
}

