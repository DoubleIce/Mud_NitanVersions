
#include <ansi.h>
inherit ITEM;

void create()
{
                
        set_name(HIC"�Թ�����������"NOR, ({ "maze door"}) );
        set_weight(5);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIB"Ŀǰ�Ĺ����У�\n"+
                            "enter <�Թ�����>������һ�������Լ����Թ�������\n"+
                            "�Թ����룺forest-ԭʼɭ�֣�icecave-���ߣ�darkhole-���춴Ѩ��desert-�޾�ɳĮ��temple-ʧ������deathvalley-����Ͽ�ȣ�???-Ⱥħ����???-����� ��\n"+
                            "\n"NOR); 
                set("unit", "��");
                set("no_get",1);
                set("value", 20);
        }
        setup();
}

void init()
{
        add_action("do_enter","enter");
}

int do_enter(string arg) {
        
        if( !arg || arg == "" )
                return 0;
                
        FUBEN_D->enter_fuben(this_player(), arg);
        return 1;
}


