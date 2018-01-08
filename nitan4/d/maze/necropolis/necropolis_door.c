#include <ansi.h>
inherit ITEM;

void create()
{
    		
        set_name(RED"Ĺ԰���"NOR, ({ "necropolis door","door"}) );
        set_weight(5);
        set("no_get",1);

        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", GRN"�������ڿ��Խ������Ĺ԰�Թ�������(enter door)\n"NOR); 
                set("unit", "��");
                set("lore",1);
                set("value", 20);
        }
        setup();
}
void init()
{
        add_action("do_enter","enter");
}


int do_enter(string arg) 
{
        int valid;
                
        if( !arg || (arg != "door" && arg != "necropolis") )
                return 0;
        
        arg = "necropolis";
        valid = FUBEN_D->valid_enter(this_player(), arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(this_player(), arg);
        else {
                if( valid == 0 )
                        write("��ʵս���鲻�㣬���������в��⣬����������һ�������ɡ�\n");
                else if( valid == -1 )
                        write("������̫���ˣ��Ͳ�Ҫ��ȥ�۸���Щ������С�����˰ɡ�\n");
                else if( valid == -2 )
                        write("��Ϸ��Ŀǰ��û�п��Ÿø����������˶Ժ����ԡ�\n");
                else if( valid == -3 )
                        write("�ø�������IP���ؽ��룬���Ѿ�����������ޡ�\n");
                else if( valid == -4 )
                        write("�ø�������ʦ�رգ�����ʱ�޷����롣\n");
        }        
        return 1;
}

/*
int do_enter(string arg) {
	if (arg!="door")
		return 0;
	MAZE_D->enter_virtual_maze(this_player(), "necropolis");
	return 1;
}
*/
