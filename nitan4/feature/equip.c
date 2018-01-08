// equip.c

#include <ansi.h>
#include <dbase.h>
#include <weapon.h>

int wear()
{
        object owner;
        mapping armor_prop, enchase_prop, applied_prop;
        mapping need;
        array apply1, apply2;
        string type;
        int flag;

        if (! objectp(this_object())) return 0;
        // Only character object can wear armors.
        owner = environment();
        if (! owner || ! owner->is_character()) return 0;

        if (query("no_identify"))
                return notify_fail(this_object()->name() + "需要鉴定后才可以使用。\n");

        // Does the consistence valid ?
        if (query("consistence") < 1)
                return notify_fail(this_object()->name() + "现在损坏太严重了，不能继续穿戴了。\n");

        // If already worn, just recognize it.
        if (query("equipped")) return 1;

        // If handing it now, stop handing
        if (owner->query_temp("handing") == this_object())
                owner->delete_temp("handing");

        // Check if we have "armor_prop" defined.
        if (! mapp(armor_prop = query("armor_prop")) ||
            ! stringp(type = query("armor_type")))
                return notify_fail("你只能穿戴可当作护具的东西。\n");

        if (owner->query_temp("armor/" + type))
                return notify_fail("你已经穿戴了同类型的护具了。\n");

        if (userp (owner) && !wizardp(owner) &&
            mapp(need = query("need")) && sizeof(need))
        {
                if (! undefinedp(need["level"]) &&
                    owner->query("level") < need["level"])
                        return notify_fail("你的等级不够，无法装备此防具。\n");

                if (! undefinedp(need["str"]) &&
                    owner->query_str() < need["str"])
                        return notify_fail("你的力量不足，无法装备此防具。\n");

                if (! undefinedp(need["dex"]) &&
                    owner->query_dex() < need["dex"])
                        return notify_fail("你的身法不足，无法装备此防具。\n");

                if (! undefinedp(need["neili"]) &&
                    owner->query_dex() < need["neili"])
                        return notify_fail("你的内力不足，无法装备此防具。\n");
        }

        owner->set_temp("armor/" + type, this_object());

        apply1 = keys(armor_prop);
        applied_prop = owner->query_temp("apply");
        if (! mapp(applied_prop)) applied_prop = ([]);
        for(int i = 0; i<sizeof(apply1); i++)
                if (undefinedp(applied_prop[apply1[i]]))
                        applied_prop[apply1[i]] = armor_prop[apply1[i]];
                else
                        applied_prop[apply1[i]] += armor_prop[apply1[i]];

        flag = 0;
        if (mapp(enchase_prop = copy(query("enchase/apply_prop"))))
                apply2 = keys(enchase_prop);
        if (arrayp(apply2) && sizeof(apply2))
        for(int i = 0; i<sizeof(apply2); i++)
        {
                if (apply2[i] == "int" || apply2[i] == "str" ||
                    apply2[i] == "con" || apply2[i] == "add_skill" ||
                    apply2[i] == "max_qi" || apply2[i] == "max_jing")
                        flag = 1;

                if (undefinedp(applied_prop[apply2[i]]))
                        applied_prop[apply2[i]] = enchase_prop[apply2[i]];
                else
                        applied_prop[apply2[i]] += enchase_prop[apply2[i]];
        }

        owner->set_temp("apply", applied_prop);

        if (query("mod"))
                MODULE_D->equip_mod(this_object(), owner);
        set("equipped", "worn");

        // modified by Lonely
        // bindable == 1 装备绑定
        if (query("bindable") && query("bindable") == 1 &&
            ! query("bind_owner") && userp(owner))
        {
                set("bind_owner", owner->query("id"));
                set("setdbase", 1);
                tell_object(owner, HIM "你内心深处隐隐约约的感应到" + this_object()->name() +
                                   HIM "与你融为一体。\n" NOR);
        }

        if (flag) CHAR_D->setup_char(owner);

        return 1;
}

int wield()
{
        object owner, old_weapon;
        mapping weapon_prop, enchase_prop;
        mapping need;
        array apply1, apply2;
        string type;
        mixed no_wield;
        int flag, f;

        if (! objectp(this_object())) return 0;
        // Only character object can wear armors.
        owner = environment();
        if (! owner || ! owner->is_character()) return 0;

        if (query("no_identify"))
                return notify_fail(this_object()->name() + "需要鉴定后才可以使用。\n");

        // Does the consistence valid ?
        if (query("consistence") < 1)
                return notify_fail(this_object()->name() + "现在损坏太严重了，不能继续装备了。\n");

        // If already wielded, just recognize it.
        if (query("equipped")) return 1;

        // If the item can not wield, I will return the fail message
        if (no_wield = query("no_wield"))
        {
                // can not wield
                if (stringp(no_wield))
                        return notify_fail(no_wield);
                else
                        return notify_fail("这样东西无法装备。");
        }

        // If handing it now, stop handing
        if (owner->query_temp("handing") == this_object())
                owner->delete_temp("handing");

        // Check if we have "weapon_prop" defined.
        if (! mapp(weapon_prop = query("weapon_prop")) ||
            ! stringp(query("skill_type")))
                return notify_fail("你只能装备可当作武器的东西。\n");

        if (userp (owner) && !wizardp(owner) &&
            mapp(need = query("need")) && sizeof(need))
        {
                if (! undefinedp(need["level"]) &&
                    owner->query("level") < need["level"])
                        return notify_fail("你的等级不够，无法装备此武器。\n");

                if (! undefinedp(need["str"]) &&
                    owner->query_str() < need["str"])
                        return notify_fail("你的力量不足，无法装备此武器。\n");

                if (! undefinedp(need["dex"]) &&
                    owner->query_dex() < need["dex"])
                        return notify_fail("你的身法不足，无法装备此武器。\n");

                if (! undefinedp(need["neili"]) &&
                    owner->query_dex() < need["neili"])
                        return notify_fail("你的内力不足，无法装备此武器。\n");
        }

        flag = query("flag");

        if (flag & TWO_HANDED)
        {
                if(owner->query_temp("secondary_weapon") ||
                   owner->query_temp("weapon") ||
                   owner->query_temp("armor/shield") ||
                   owner->query_temp("handing"))
                        return notify_fail("你必须空出双手才能装备该武器。\n");
                owner->set_temp("weapon", this_object());
                owner->set_temp("secondary_weapon", this_object());
        } else
        {
                // If we are are using any weapon?
                if (! (old_weapon = owner->query_temp("weapon")))
                        owner->set_temp("weapon", this_object());

                else // If we still have a free hand?
                if (!owner->query_temp("secondary_weapon")
                &&  !owner->query_temp("armor/shield")
                &&  !owner->query_temp("handing"))
                {
                        // If we can wield this as secondary weapon?
                        if(flag & SECONDARY) {
                                owner->set_temp("secondary_weapon", this_object());
                        }
                        // If we can switch our old weapon to secondary weapon ?
                        else if( (int)old_weapon->query("flag") & SECONDARY ) {
                                old_weapon->unequip();
                                owner->set_temp("weapon", this_object());
                                old_weapon->wield();

                        // We need unwield our old weapon before we can use this one.
                        } else
                                return notify_fail("你必须先放下你目前装备的武器。\n");

                // We have both hands wearing something.
                } else
                        return notify_fail("你必须空出一只手来使用武器。\n");
        }

        // add by doing to discard the secondary_weapon's prop
        if (owner->query_temp("secondary_weapon") != this_object())
        {
                apply1 = keys(weapon_prop);
                for(int i = 0; i<sizeof(apply1); i++)
                        owner->add_temp("apply/" + apply1[i], weapon_prop[apply1[i]]);

                f = 0;
                if (mapp(enchase_prop = query("enchase/apply_prop")))
                        apply2 = keys(enchase_prop);
                if (arrayp(apply2) && sizeof(apply2))
                for(int i = 0; i<sizeof(apply2); i++)
                {
                        if (apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing")
                                f = 1;

                        owner->add_temp("apply/" + apply2[i], enchase_prop[apply2[i]]);
                }
        }

        if (query("mod"))
                MODULE_D->equip_mod(this_object(), owner);

        owner->reset_action();
        set("equipped", "wielded");

        // modified by Lonely
        // bindable == 1 装备绑定
        if (query("bindable") && query("bindable") == 1 &&
            ! query("bind_owner") && userp(owner))
        {
                set("bind_owner", owner->query("id"));
                set("setdbase", 1);
                tell_object(owner, HIM "你内心深处隐隐约约的感应到" + this_object()->name() +
                                   HIM "与你融为一体。\n" NOR);
        }

        if (f) CHAR_D->setup_char(owner);
        return 1;
}

int unequip()
{
        object owner, weapon;
        mapping prop1 = 0, prop2 = 0, applied_prop;
        array apply1, apply2;
        string equipped;
        int flag;

        if (! environment()) return 0;

        if (! (owner = environment())->is_character())
                return 0;

        if (! stringp(equipped = query("equipped")))
                return notify_fail("你目前并没有装备这样东西。\n");

        if (equipped == "wielded")
        {
                if ((object)owner->query_temp("weapon") == this_object())
                {
                        prop1 = query("weapon_prop");
                        prop2 = query("enchase/apply_prop");
                        owner->delete_temp("weapon");
                        if ((object)owner->query_temp("secondary_weapon") == this_object())
                                owner->delete_temp("secondary_weapon");
                        if (objectp(weapon = owner->query_temp("secondary_weapon")))
                        {
                                weapon->unequip();
                                weapon->wield();
                        }
                } else
                if ((object)owner->query_temp("secondary_weapon") == this_object())
                {
                        owner->delete_temp("secondary_weapon");
                        prop1 = 0;
                        prop2 = 0;
                }
                owner->reset_action();
        } else
        if (equipped == "worn")
        {
                owner->delete_temp("armor/" + query("armor_type"));
                prop1 = query("armor_prop");
                prop2 = query("enchase/apply_prop");
        }

        if (mapp(prop1))
        {
                apply1 = keys(prop1);
                applied_prop = owner->query_temp("apply");
                for (int i = 0; i<sizeof(apply1); i++)
                        // To support array apply, we cannot add_temp() here.
                        applied_prop[apply1[i]] -= prop1[apply1[i]];
        }

        flag = 0;
        if (mapp(prop2))
        {
                apply2 = keys(prop2);
                applied_prop = owner->query_temp("apply");
                for (int i = 0; i<sizeof(apply2); i++)
                {
                        if (apply2[i] == "int" || apply2[i] == "str" ||
                            apply2[i] == "con" || apply2[i] == "add_skill" ||
                            apply2[i] == "max_qi" || apply2[i] == "max_jing")
                                flag = 1;
                        // To support array apply, we cannot add_temp() here.
                        applied_prop[apply2[i]] -= prop2[apply2[i]];
                }
        }

        if (query("mod"))
                MODULE_D->unequip_mod(this_object(), owner);

        delete("equipped");

        if (flag) CHAR_D->setup_char(owner);

        return 1;
}

// hit the object as a weapon
mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed foo;

        foo = this_object()->weapon_hit_ob(me, victim, damage_bonus);

        ITEM_D->reduce_consistence(this_object());

        if (! mapp(query_temp("daub")))
                return foo;

        COMBAT_D->hit_with_poison(me, victim, this_object());
        return foo;
}

// other one hit me as an armor
mixed valid_damage(object me, object victim, int damage_bonus)
{
        ITEM_D->reduce_consistence(this_object());

        if (! mapp(query_temp("daub")))
                return;

        if (me->query_temp("weapon") || me->query_temp("remote_attack") ||
            me->query("not_living"))
        {
                // the attacker has weapon, or remote attack, or not living,
                // he won't be poisoned by my cloth or armor
                return;
        }

        COMBAT_D->hit_poison(me, victim, this_object());
        return;
}

int do_enchase(object me, object tessera)
{
        mapping *ins;
        mapping data, enchase_prop, ench;
        string  *apply;
        object  obj, ob = this_object();

        if (query("equipped"))
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");
                
        if (tessera->query("can_be_enchased"))
                return notify_fail(tessera->name() + "只能镶嵌到自造10lvl兵器上。\n");

        if (! tessera->is_inlaid() || ! mapp(tessera->query("enchase")))
                return notify_fail(tessera->name() + "不能发挥魔力，"
                                   "没有必要镶嵌在" + ob->name() + "上面。\n");

        if (tessera->is_item_make())
                return notify_fail(tessera->name() + "非镶嵌物品，不能被镶嵌在" + ob->name() + "上面。\n");

        if (me->query_skill("certosina", 1) < 200)
                return notify_fail("你觉得你的镶嵌技艺还不够"
                                   "娴熟，不敢贸然动手。\n");

        if (! query("enchase/flute"))
                return notify_fail(ob->name() + "上没有凹槽用来镶嵌宝石。\n");

        if ((int)query("enchase/used") >= query("enchase/flute"))
                return notify_fail(ob->name() + "上的凹槽已经被镶满了。\n");

        if (tessera->is_rune() && query("enchase/rune" + tessera->query("enchase/SN")))
                return notify_fail(ob->name() + "上的凹槽里已经镶嵌此符文,再镶嵌会产生魔性冲突。\n");

        ench = tessera->query("enchase");
        if (! undefinedp(ench["type"]))
        {
                if (ench["type"] != "all" &&
                    ench["type"] != query("skill_type") &&
                    ench["type"] != query("armor_type"))
                        return notify_fail(tessera->name() + "的魔力属性不适合镶嵌在" + ob->name() + "上。\n");
        }

        if (me->query_skill("certosina", 1) < 500 &&
            random(me->query_skill("certosina", 1)) < 180 && 
            ! (obj = present("enchaseB charm", me)))
        {
                message_sort(HIM "听得“喀啦”一声，只见" + tessera->name() + HIM "撞在$n" +
                             HIM "上，片片裂开。\n" NOR, me, ob);
                tell_object(me, HIC "你镶嵌" + tessera->name() + CYN "失败了。\n" NOR);

                destruct(tessera);
                me->start_busy(1);
                return 1;
        }
        if (objectp(obj)) destruct(obj);
        
        if (! random(100) && ! (obj = present("enchaseA charm", me)))
        {
                message_sort(HIM "听得“喀啦”一声，只见" + tessera->name() + HIM "撞在$n" +
                             HIM "上，撞个粉碎，" + tessera->name() + HIM "被撞个大的裂纹，看"
                             "来是不能再用了。\n" NOR, me, ob);
                tell_object(me, HIC "你镶嵌" + tessera->name() + CYN "失败了，你的装备也损坏了。\n" NOR);

                destruct(tessera);
                destruct(ob);
                me->start_busy(1);
                return 1;
        }  
        if (objectp(obj)) destruct(obj);
                      
        message_sort(HIM "听得“喀啦”一声，$N" HIM "将" + tessera->name() +
                     HIM "镶嵌到了$n" HIM "上面的凹槽里，只见" + tessera->name() + HIM
                     "隐隐的发出一团奇异的光芒，环绕在$n" HIM "的周围，随即变得平静。\n" NOR, me, ob);
        tell_object(me, HIC "你感受" + ob->name() + HIC "发生了"
                    "不可言喻的变化，似乎有一股神奇的力量附在其中！\n" NOR);

        if (query("skill_type"))
                enchase_prop = tessera->query("enchase/weapon_prop");
        else
        if (query("armor_type"))
                enchase_prop = tessera->query("enchase/armor_prop");
        
        if (! mapp(enchase_prop)) enchase_prop = ([ ]);
        apply = keys(enchase_prop);
        data = query("enchase/apply_prop");
        if (! mapp(data)) data = ([ ]);
        
        for(int i = 0; i<sizeof(apply); i++)
                if (undefinedp(data[apply[i]]))
                        data[apply[i]] = enchase_prop[apply[i]];
                else
                        data[apply[i]] += enchase_prop[apply[i]];

        set("enchase/apply_prop", data);

        ins = query("enchase/inset");
        if (! ins) ins = ({ });
        ins += ({ (["name" : tessera->query("name"), "id" : tessera->query("id") + " &" + (sizeof(ins) + 1),
                    "consistence" : tessera->query("enchase/consistence"), 
                    "SN" : tessera->query("enchase/SN"), 
                    "enchase_prop" : enchase_prop]) });

        set("enchase/inset", ins);
        add("enchase/used", 1);
        if (tessera->is_rune()) 
        {
                if (! query("enchase/rune"))
                {
                        add("enchase/SN", tessera->query("enchase/SN")); 
                        set("enchase/rune", 1);
                }
                set("enchase/rune" + tessera->query("enchase/SN"), 1); 
        } else
                add("enchase/SN", random(tessera->query("enchase/SN")) + 1);
        // add_weight(tessera->query_weight());

        destruct(tessera);
        me->start_busy(1);
        return 1;
}
