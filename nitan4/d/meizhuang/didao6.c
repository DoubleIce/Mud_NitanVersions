// didao6.c

inherit ROOM;

void create()
{
        set("short", "÷ׯ�ܵ�");
        set("long", @LONG
����һ���谵��ʪ�ĵص����ص��ܳ������ߵ���������̫������
��ѣ��ص����Ե�ǽ���ϻ��źܶ಻֪�����Ժ���֮�ֵıڻ�������
�����൱�ѿ�����ӿ�Ų�����֪���ص��ľ�ͷ��ʲô�ط��� 
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"didao7",
                "east"  : __DIR__"didao6",
		"north" : __DIR__"didao5",
		"west"  : __DIR__"didao4",
        ]));

        setup();
        replace_program(ROOM);
}
