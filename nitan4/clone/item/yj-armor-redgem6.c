#include <ansi.h>

inherit INLAID;

void create()
{
        set_name(RED "ħ֮��ʯ" NOR, ({ "red gem6","gem6" }));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "һ����˸�������â�ĺ�ɫ��ʯ��"
                    "���˸е�һ������ļ¡�\n" NOR);
                set("unit", "��");
                set("value", 180000);
                set("enchase",  ([ /* sizeof() == 5 */
                        "weapon_prop" : ([ /* sizeof() == 3 */
                                "derive_times"    : 7,
                                "research_times"  : 7,
                                "practice_times"  : 7,
                        ]),
                        "armor_prop" : ([ /* sizeof() == 3 */
                                "research_effect" : 3,
                                "derive_effect"   : 3,
                                "practice_effect" : 3,
                        ]),
                        "level" : 6,
                        "SN" : 1 + random(9),
                        "consistence" : 80 + random(21),
                ])) ;

                set("wear_msg", HIC "$N" HIC "����ذ�$n" HIC "����ͷ�ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n" HIC "��ͷ��ժ��������\n" NOR);                   
        }
        setup();
}

