//Cracked by Roath
// arrow.c ��
// kane

#include <ansi.h>
#include <weapon.h>
inherit COMBINED_ITEM;
inherit F_EQUIP;
void create()
{
        set_name("������", ({ "arrow" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
        	set("long", "���λε���������βǶ�ż�����ë��\n");
        	set("unit", "��");
		set("base_unit", "֧");
                set("base_value", 150);
                set("base_weight", 20);
		set("damage", 5);
		set("armor_type", "embed");
		set("weapon_type", "arrow");
                set("armor_prop/armor",1);
		set("armor_prop/attack", -50);
                set("armor_prop/defense", -50);
                set("armor_prop/unarmed", -50);
		set("no_sell", 1);
		set("unequip_msg", HIR"$Nһҧ����$n���˿��ϰ���������һ����Ѫ�͵�ӿ�˳�����\n"NOR);
        }
	set_amount(15);
        setup();
}
int wear() { return 0; }
int do_embed()
{
	::wear();
	set("no_drop", 1);
	set("no_get", 1);
	environment()->apply_condition("embedded", 100);
	return 1;
}
int unequip()
{
	::unequip();
	set("no_drop", 0);
	set("no_get", 0);
	delete("embedded");

	environment()->apply_condition("embedded", 0);
	environment()->receive_damage("qi", 200+random(500*query_amount()));
	environment()->delete("embedded_time");
	return 1;
}
string query_autoload() 
{ 
	if( query("equipped") )
	return query_amount() + ""; 
}

/*
void autoload(string param)
{
        int amt;

        if( sscanf(param, "%d", amt)==1 )
                set_amount(amt);
	set("embedded", 1);
	set("no_drop", 1);
	set("no_get", 1);
	::wear();
}
*/