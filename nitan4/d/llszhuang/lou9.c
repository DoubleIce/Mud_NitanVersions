#include <ansi.h>
inherit ROOM;
void create()
{
        set("short",CYN"�� �� ¥"NOR);
        set("long",
"���ǽ���¥�ļ�����������ӽ���յĵط���һ����Ѥ�õľ�ս����\n"
"���У�һλ������������ʮ���ħʦ��һλ���ѳ�Ϊ����ĸ��꽣������\n"
"�ľ�ս�Ѿ�ԶԶ����������ʤ�����ﵽ������һ�����档���ǵ������ƶ�\n"
"ʵ��������Ͷ���Ī�������̺�����ؼ��������\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "down": __DIR__"lou8",
        ]));
        set("no_magic", "1");

        set("objects", ([
               __DIR__"npc/kuangren1" : 2,
               __DIR__"npc/edward" : 1,
        ]));

        setup();
}
