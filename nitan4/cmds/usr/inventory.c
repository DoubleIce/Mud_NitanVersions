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
                        return notify_fail("��Ҫ�쿴˭��״̬��\n"); 
        }

        if( !ob ) ob = me;
        
        total_item = 0;
        inv = filter_array(all_inventory(ob), "visible", me);
        if( !sizeof(inv) ) {
                write((ob==me)? "Ŀǰ������û���κζ�����\n"
                        : ob->name() + "����û��Я���κζ�����\n");
                return 1;
        }

        output = sprintf("%s���ϴ���������Щ����(���� %d%%)��\n",
                (ob==me)? "��": ob->name(),
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
                output += "Ŀǰû��Я����Ʒ��\n";
        else
                output += "ĿǰЯ����" + chinese_number(total_item) +
                          "����Ʒ��\n";
        write(output);
        return 1;
}

string inventory_desc(object ob,object me)
{
        return sprintf("%s%s\n",
                ob->query("equipped")?
                        ((ob == me->query_temp("secondary_weapon"))?
                        HIM "��" NOR:
                        HIC "��" NOR):
                        ((ob == me->query_temp("handing"))?
                        HIC "��" NOR:
                        HIR "��" NOR),
                ob->short()
        );
}

int help (object me)
{
        write(@HELP
ָ���ʽ: inventory
 
���г���Ŀǰ������Я����������Ʒ��

"��" ���˵������ƷΪ���Ѿ�װ���ı��������Ѵ���
     �Ļ��ף���ɫ��ʾ����Ʒװ����������֡�
"��" ���˵������Ʒ����������С�

ע : ��ָ����� " i " ���档
 
HELP
);
        return 1;
}

