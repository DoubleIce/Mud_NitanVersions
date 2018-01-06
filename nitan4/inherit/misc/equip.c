// equip.c
 
inherit ITEM;
inherit F_EQUIP;
 
void setup()
{
        /*
        int w;
        
        w = weight();
        
        if (!(this_object()->query("armor_prop/dodge")) && (w >= 3000))
                this_object()->set("armor_prop/dodge", -w / 3000);
        if (!(this_object()->query("weapon_prop/dodge")) && (w >= 3000))
                this_object()->set("weapon_prop/dodge", -w / 3000);
        */
 
        ITEM_D->equip_setup(this_object());
}

