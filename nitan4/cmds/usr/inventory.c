// This program is a part of NITAN MudLIB
// Inventory.c
// Modified by Lonely@NITAN (12/15/2005) 

#include <ansi.h>

inherit F_CLEAN_UP;

string inventory_desc(object ob,object me);

int main(object me, string arg)
{
        object *inv, ob, *equ, *end;
        int     n, total_item;
        string  output;
        mixed   groups;

        if( (wizardp(me) || me->query("couple/child_id")) && arg )
        {
                ob = find_player(arg);
                if( !ob ) ob = find_living(arg);
                if( !ob ) ob = present(arg, environment(me));
                if( !wizardp(me) && (! ob || me->query("couple/child_id") != ob->query("id")) ) 
                        return notify_fail("你要察看谁的状态？\n"); 
        }

        if( !ob ) ob = me;
        
        total_item = 0;
        inv = filter_array(all_inventory(ob), "visible", me);
        if( !sizeof(inv) ) {
                write((ob==me)? "目前你身上没有任何东西。\n"
                        : ob->name() + "身上没有携带任何东西。\n");
                return 1;
        }

        output = sprintf("%s身上带著下列这些东西(负重 %d%%)：\n",
                (ob==me)? "你": ob->name(),
                (int)ob->query_encumbrance() * 100 / (int)ob->query_max_encumbrance());

        if( me->query_temp("tomud") && ob == me )
        {
                output += CLEAN1;
                foreach( object obn in inv ) 
                        output += ADD1(obn); //By JackyBoy@XAJH 2001/5/6
        }

        equ = filter_array(inv,
                (: $1->is_character() :)
        );
        equ += filter_array(inv,
                (: $1->query("equipped") :)
        );
        equ += filter_array(inv,
                (: $1->query("embedded") :)
        );
        equ += filter_array(inv,
                (: $1==$(ob)->query_temp("handing") :)
        );
        end = filter_array(inv,
                (: $1->query_amount() :)
        );
        
        if( n = sizeof(equ) )
        {                                               
                for( int i=0;i<n;i++ )
                {
                        if( equ[i]->is_character() )
                        {
                                if( !equ[i]->query("ridable") ) total_item++;
                                output += sprintf("  %s\n",equ[i]->short());
                        } else  
                        if( equ[i]->query("equipped") || equ[i]->query("embedded") 
                        ||      equ[i] == ob->query_temp("handing") )
                        {
                                if( equ[i] == ob->query_temp("handing") ) total_item++;
                                output += inventory_desc(equ[i],ob);
                        }
                }
        }
        inv -= equ;
        inv -= end;
        groups = unique_array(inv,(: sprintf("%s%s",base_name($1),$1->name()) :));      
        if( sizeof(groups) )
        {
                foreach( object *group in groups )
                {
                        // if( !ob->visible(group[0]) ) continue;
                        if( (n=sizeof(group)) == 1)
                                output += sprintf("  %s\n",group[0]->short());
                        else
                                output += sprintf("  %s%s%s\n",chinese_number(n),
                                        group[0]->query("unit"),
                                        group[0]->query("base_cname")?
                                        sprintf("%s(%s)",group[0]->query("base_cname"),
                                        capitalize(group[0]->query("id"))):
                                        group[0]->short());
                        total_item += n;
                }
        }
        
        if( sizeof(end) )
        {
                total_item += sizeof(end);
                foreach( object item in end ) 
                        output += sprintf("  %s\n",item->short());
        }
        
        if( !total_item )
                output += "目前没有携带物品。\n";
        else
                output += "目前携带了" + chinese_number(total_item) +
                          "件物品。\n";
        write(output);
        return 1;
}

string inventory_desc(object ob,object me)
{
        return sprintf("%s%s\n",
                ob->query("equipped")?
                        ((ob == me->query_temp("secondary_weapon"))?
                        HIM "□" NOR:
                        HIC "□" NOR):
                        ((ob == me->query_temp("handing"))?
                        HIC "○" NOR:
                        HIR "☆" NOR),
                ob->short()
        );
}

int help (object me)
{
        write(@HELP
指令格式: inventory
 
可列出你目前身上所携带的所有物品。

"□" 标记说明此物品为你已经装备的兵器或者已穿戴
     的护甲，粉色表示此物品装备于你的左手。
"○" 标记说明此物品握在你的手中。

注 : 此指令可以 " i " 代替。
 
HELP
);
        return 1;
}

