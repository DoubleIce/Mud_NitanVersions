// Written by Lonely@IsMUD.net
// crystal.c ˮ��

#include <ansi.h>
#include <armor.h>

inherit INLAID; 

int is_inlaid() { return 1; }
int is_magic_item() { return 1; }

void create()
{
        set_name("��ˮ��", ({ "black crystal", "crystal" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "һ���ɫ��ˮ�������Գ�ȡ(extra)��ʯ�е�ħ�����ԡ�\n" NOR);
                set("value", 50000);
                set("unit", "��");
                set("autoload", 1);
        }
        setup();
}

void init()
{
        add_action("do_extra", "extra");
}

int do_extra(string arg)
{
        object me;
        object ob, obj;
        int    i, n, t, flag;
        string item, what;
        mixed  inset;
        array  apply;
        mapping data, dbase, prop;
        
        me = this_player();
        
        if( !arg ) return notify_fail("ָ���ʽ�� extra <����> from <��Ʒ> \n");
                
        if( this_object()->query("enchase") )
                return notify_fail("��ˮ���Ѿ���ȡ��һ�������ˡ�\n");
                
        if( sscanf(arg, "%s from %s", what, item) != 2 )
                return notify_fail("ָ���ʽ�� extra <����> from <��Ʒ> \n");
                
        if( !objectp(ob = present(item, me)) &&
            !objectp(ob = present(item, environment(me))) )
                return notify_fail("�����Ϻ͸���û��������Ʒ��\n");
                
        if( ob->query("equipped") )
                return notify_fail("����ж�����ȡ�\n");
                
        if( ob->is_item_make() )
                return notify_fail("����װ�������Ա���ȡ���ԡ�\n");
        
        if( !ob->query("enchase") )
                return notify_fail("�����Ʒ����û�п�������ȡ�����ԡ�\n");
        
        if( !ob->query("enchase/armor_prop/" + what) &&
            !ob->query("enchase/weapon_prop/" + what) )
                return notify_fail("�����Ʒ����û�������ȡ�����ԡ�\n");
        
        if( ob->query("enchase/armor_prop/" + what) ) {
                this_object()->set("enchase/armor_prop/" + what, ob->query("enchase/armor_prop/" + what));
                ob->delete("enchase/armor_prop/" + what);     
        } else {
                this_object()->set("enchase/weapon_prop/" + what, ob->query("enchase/weapon_prop/" + what));
                ob->delete("enchase/weapon_prop/" + what);   
        }
        
        this_object()->set("setdbase", 1);
           
        message_vision(HIR "\nһ���ڹ��������ƺ���һ������������������У���\n" NOR, me);
        return 1;
}

