inherit ROOM;

void create()
{
        set("short", "�徻��");
        set("long", @LONG
������ȫ������֮ĩ��Ҳ��ΨһŮ�����ﲻ���ľ��ҡ��ⷿ�䴰
��������������λʦ�ֵ����Ҵ���ͬ�������۵��ż����ۣ�������
��һ������ͷ��������ͷ�ɲ�������������˵ġ��ǵ�������������
����Ϊͽʱ������һ������ͼ����������˼��˵������̣��õ�Ϊ����
�ﲻ������ʦ�����ͽ��������ͼ�������Լ��ĵ����ϡ�
LONG );
        set("exits", ([
                "north" : __DIR__"nairongdian",
        ]));

        set("objects", ([
                CLASS_D("quanzhen") + "/sun" : 1,
        ]));

        setup();
        replace_program(ROOM);
}