#include <ansi.h>
inherit BOOK;

void create()
{
        set_name(HIC "����ͼ��" NOR, ({ "he tu", "he", "tu" }));
        set_weight(500);
        if (clonep())
            set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "����һ���ñ���д�ɵ��顣������ֹ�׭��"
                            HIC "��ͼ" HIY "������Ƥ��Ȼ\n���ƣ������Ѿ�"
                            "����ܾ��ˡ�\n" NOR);
                set("value", 1);
                set("no_sell", "�ţ����õ�����ɶ�����⣿");
                set("material", "silk");
                set("skill", ([
                        "name" : "count",
                        "exp_required" : 1000000,
                        "jing_cost"  : 80,
                        "difficulty" : 80,
                        "max_skill"  : 199,
                        "min_skill"  : 100,
                        "need" : ([ "literate" : 300 ]),
                ]));
        }
}
