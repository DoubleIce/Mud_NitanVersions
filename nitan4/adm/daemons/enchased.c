// Written By Lonely@Nitan3

#include <ansi.h>

#pragma optimize
#pragma save_binary

array gem_name = ({
        "宝石碎片",
        "宝石",
        "稀世宝石",
        "帝之宝石",
        "圣之宝石",
        "魔之宝石",
        "神之宝石",
});

array skull_name = ({
        "骷髅头碎片",
        "骷髅头",
        "稀世骷髅头",
        "帝之骷髅头",
        "圣之骷髅头",
        "魔之骷髅头",
        "神之骷髅头",
});

mixed identify_ob(object me, object ob)
{
        int     i, level;
        string  file, filename, color, id;
        string  *types, base_file;
        mixed   obj;
        mapping data, temp, dbase;

        data = ([ ]);
        temp = ([ ]);
        dbase = ([ ]);

        filename = base_name(ob);
        filename += ".c";

        if (filename == "/clone/enchase/skull.c")
        {
                if (random(100) == 0) level = 4;
                else if (random(50) == 0) level = 3;
                else if (random(10) == 0) level = 2;
                else level = 1;

                base_file = "skull";
                id = base_file + level;
        } else
        if (sscanf(filename, "/clone/enchase/skull%d.c", level))
        {
                base_file = "skull";
                id = base_file + level;
        } else
        if (sscanf(filename, "/clone/enchase/%sgem.c", color))
        {
                if (random(100) == 0) level = 4;
                else if (random(50) == 0) level = 3;
                else if (random(10) == 0) level = 2;
                else level = 1;

                base_file = "gem";
                id = color + " " + base_file + level;
        } else
        if (sscanf(filename, "/clone/enchase/%sgem%d.c", color, level) == 2)
        {
                base_file = "gem";
                id = color + " " + base_file + level;
        } else
                return 0;

        dbase = ([ ]);
        types = EQUIPMENT_D->apply_stats("weapon", level / 2);
        for (i = 0; i < level/2; i++)
                dbase[types[i]] = EQUIPMENT_D->query_stats_value(types[i], level);
        temp["weapon_prop"] = dbase;

        dbase = ([ ]);
        types = EQUIPMENT_D->apply_stats("armor", level / 2);
        for (i = 0; i < level/2; i++)
                dbase[types[i]] = EQUIPMENT_D->query_stats_value(types[i], level);
        temp["armor_prop"] = dbase;

        temp["level"] = level;
        temp["SN"] = 1 + random(9);
        temp["consistence"] = 80 + random(21);

        if (! stringp(color) || ! color)
                data["name"] = HIB + skull_name[level-1] + NOR;
        else
                data["name"] = convert_color(upper_case(color)) + gem_name[level-1] + NOR;

        data["enchase"] = temp;
        if (level == 7)
        {
                temp = ([ "type" : "magic", "power" : 15 + random(16) ]);
                data["magic"] = temp;
                data["can_be_enchased"] = 1;
        }

        obj = TEMPLATE_D->create_object("/template/gem/" + base_file, id, data, 1);

        return obj;
}
// 无上神品->上古神品->中古神品->远古神品->太古神品
// 太始、太初、太玄 太虚、洪荒
// 冥古宙、太古宙、元古宙和显生宙
// 其中元古宙又划分为古元古代、中元古代和新元古代；
// 显生宙划分古生代、中生代和新生代。
varargs int identify_ultimate_ob(object item, int close)
{
        mapping data, prop;
        array inset, apply;
        int i, n, s;
        int r_effect, d_effect, p_effect;

        r_effect = 0;
        d_effect = 0;
        p_effect = 0;

        s = (int)item->query("enchase/SN");
        if (s == 37 && ! item->query("ultimate/37"))
        {
                item->add("enchase/apply_prop/research_effect", 10);
                if (item->query("enchase/apply_prop/research_effect") > 40)
                        item->set("enchase/apply_prop/research_effect", 40);
                item->add("enchase/apply_prop/practice_effect", 10);
                if (item->query("enchase/apply_prop/practice_effect") > 40)
                        item->set("enchase/apply_prop/practice_effect", 40);
                item->add("enchase/apply_prop/derive_effect", 10);
                if (item->query("enchase/apply_prop/derive_effect") > 40)
                        item->set("enchase/apply_prop/derive_effect", 40);
                item->add("enchase/flute", 1);
                item->add("enchase/SN", -(random(9) + 1));
                item->set("ultimate/37", 1);
                item->save();
                return 1;
        } else
        if (s == 39 && ! item->query("ultimate/39"))
        {
                item->add("enchase/apply_prop/research_effect", 15);
                if (item->query("enchase/apply_prop/research_effect") > 40)
                        item->set("enchase/apply_prop/research_effect", 40);
                item->add("enchase/apply_prop/practice_effect", 15);
                if (item->query("enchase/apply_prop/practice_effect") > 40)
                        item->set("enchase/apply_prop/practice_effect", 40);
                item->add("enchase/apply_prop/derive_effect", 15);
                if (item->query("enchase/apply_prop/derive_effect") > 40)
                        item->set("enchase/apply_prop/derive_effect", 40);
                item->add("enchase/flute", 1);
                item->set("ultimate/39", 1);
                item->save();
                return 1;
        } else
        if (s == 69 && ! item->query("ultimate/69") &&
            item->query("armor_type") && item->query("armor_type") != "hands")
        {
                data = item->query("enchase/apply_prop");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] = data[apply[i]] * 3 / 2;

                inset = item->query("enchase/inset");
                if (! inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                        {
                                if (! undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (! undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (! undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }
                data["research_effect"] = r_effect * 3 / 2;
                data["derive_effect"] = d_effect * 3 / 2;
                data["practice_effect"] = p_effect * 3 / 2;

                data["reduce_busy"]     = EQUIPMENT_D->query_stats_value("reduce_busy", 1 + random(2));
                // data["avoid_busy"]      = EQUIPMENT_D->query_stats_value("avoid_busy", 1 + random(4));
                data["def_damage"]       = EQUIPMENT_D->query_stats_value("def_damage", 1 + random(6));
                data["avoid_xuruo"]     = EQUIPMENT_D->query_stats_value("avoid_xuruo", 1 + random(4));
                data["add_locked"]= EQUIPMENT_D->query_stats_value("add_locked", 1 + random(4));
                data["reduce_damage"]   = EQUIPMENT_D->query_stats_value("reduce_damage", 1 + random(3));

                item->set("enchase/apply_prop", data);
                item->set("ultimate/69", 1);
                item->set("ultimate/ob", 1);
                item->save();

                if (! close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说上古神品" + item->name() + HIM +
                              "来到了人间。");


                log_file("static/ultimate", sprintf("%s Have 69 SN. Wash %d Times. %s\n",
                          base_name(item), item->query("enchase/wash"), ctime(time())));
                return 1;
        } else
        if (s == 87 && ! item->query("ultimate/87"))
        {
                data = item->query("enchase/apply_prop");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                if (item->query("skill_type") ||
                    (item->query("armor_type") && item->query("armor_type") == "hands"))
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] = data[apply[i]] * 3 / 2;

                        inset = item->query("enchase/inset");
                        if (! inset) inset = ({});
                        n = sizeof(inset);
                        for (i = 0; i < n; i++)
                        {
                                if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                                {
                                        if (! undefinedp(prop["research_effect"]))
                                                r_effect += prop["research_effect"];
                                        if (! undefinedp(prop["derive_effect"]))
                                                d_effect += prop["derive_effect"];
                                        if (! undefinedp(prop["practice_effect"]))
                                                p_effect += prop["practice_effect"];
                                }
                        }
                        data["research_effect"] = r_effect * 3 / 2;
                        data["derive_effect"] = d_effect * 3 / 2;
                        data["practice_effect"] = p_effect * 3 / 2;

                        data["add_busy"]        = EQUIPMENT_D->query_stats_value("add_busy", 1 + random(5));
                        data["add_xuruo"]    = EQUIPMENT_D->query_stats_value("add_xuruo", 1 + random(3));
                        data["avoid_locked"] = EQUIPMENT_D->query_stats_value("avoid_locked", 1 + random(3));
                        data["add_damage"] = EQUIPMENT_D->query_stats_value("add_damage", 1 + random(3));
                        data["add_skill"]  = EQUIPMENT_D->query_stats_value("add_skill", 1 + random(4));

                        item->set("enchase/apply_prop", data);
                        item->set("ultimate/87", 1);

                        if (! close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "听说上古神品" + item->name() + HIM +
                                "来到了人间。");

                } else
                {
                        for(i=0; i<sizeof(apply); i++)
                                data[apply[i]] *= 2;
                        
                        
                        inset = item->query("enchase/inset");
                        if (! inset) inset = ({});
                        n = sizeof(inset);
                        for (i = 0; i < n; i++)
                        {
                                if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                                {
                                        if (! undefinedp(prop["research_effect"]))
                                                r_effect += prop["research_effect"];
                                        if (! undefinedp(prop["derive_effect"]))
                                                d_effect += prop["derive_effect"];
                                        if (! undefinedp(prop["practice_effect"]))
                                                p_effect += prop["practice_effect"];
                                }
                        }
                        
                        data["research_effect"] = 20 + r_effect * 2;
                        data["derive_effect"] = 20 + d_effect * 2;
                        data["practice_effect"] = 20 + p_effect * 2;

                        data["reduce_busy"]     = 6;
                        // data["avoid_busy"]      = 16;
                        data["def_damage"]      = 2000;
                        data["avoid_xuruo"]     = 16;
                        data["add_locked"]= 16;
                        data["reduce_damage"]   = 16;
                        item->set("enchase/apply_prop", data);
                        item->set("ultimate/87", 1);

                        if (! close)
                        CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                                "听说远古神品" + item->name() + HIM +
                                "来到了人间。");
                }

                item->set("ultimate/ob", 1);
                item->save();
                log_file("static/ultimate", sprintf("%s Have 87 SN. Wash %d Times. %s\n",
                          base_name(item), item->query("enchase/wash"), ctime(time())));
                return 1;
        } else
        if (s == 105 && ! item->query("ultimate/105"))
        {
                data = item->query("enchase/apply_prop");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 2;

                inset = item->query("enchase/inset");
                if (! inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                        {
                                if (! undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (! undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (! undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }
                data["research_effect"] = 65 + r_effect * 5;
                data["derive_effect"] = 65 + d_effect * 5;
                data["practice_effect"] = 65 + p_effect * 5;

                data["add_busy"]        = 16;
                data["add_xuruo"]    = 40;
                // data["double_damage"]    = 40;
                data["avoid_locked"] = 40;
                data["add_damage"]      = 40;
                data["add_skill"]  = 500;
                        
                item->set("enchase/apply_prop", data);
                item->set("ultimate/105", 1);
                item->set("ultimate/ob", 1);
                item->save();
                if (! close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说远古神品" + item->name() + HIM +
                              "来到了人间。");

                log_file("static/ultimate", sprintf("%s Have 105 SN. Wash %d Times. %s\n",
                          base_name(item), item->query("enchase/wash"), ctime(time())));
                return 1;
        } else
        if (s == 121 && ! item->query("ultimate/121"))
        {
                data = item->query("enchase/apply_prop");
                if (! mapp(data)) data = ([ ]);
                apply = keys(data);
                for(i=0; i<sizeof(apply); i++)
                        data[apply[i]] *= 3;

                inset = item->query("enchase/inset");
                if (! inset) inset = ({});
                n = sizeof(inset);
                for (i = 0; i < n; i++)
                {
                        if (mapp(prop = inset[i]["enchase_prop"]) && sizeof(prop))
                        {
                                if (! undefinedp(prop["research_effect"]))
                                        r_effect += prop["research_effect"];
                                if (! undefinedp(prop["derive_effect"]))
                                        d_effect += prop["derive_effect"];
                                if (! undefinedp(prop["practice_effect"]))
                                        p_effect += prop["practice_effect"];
                        }
                }
                data["research_effect"] = 1000 + r_effect * 3;
                data["derive_effect"] = 1000 + d_effect * 3;
                data["practice_effect"] = 1000 + p_effect * 3;

                data["add_busy"]        = 36;
                data["add_xuruo"]    = 96;
                data["avoid_locked"] = 96;
                data["add_damage"]      = 96;
                data["add_skill"]  = 800;

                data["reduce_busy"]     = 32;
                // data["avoid_busy"]      = 96;
                data["def_damage"]       = 6000;
                data["avoid_xuruo"]     = 96;
                data["add_locked"]= 96;
                data["reduce_damage"]   = 96;

                data["ap_power"]        = 96;
                data["dp_power"]        = 96;
                data["da_power"]        = 96;
                data["avoid_parry"]     = 96;
                data["avoid_dodge"]     = 96;
                data["avoid_attack"]    = 96;

                item->set("enchase/apply_prop", data);
                item->set("ultimate/121", 1);
                item->set("ultimate/ob", 1);
                item->save();
                if (! close)
                CHANNEL_D->do_channel(find_object(ITEM_D), "rumor",
                              "听说太古神品" + item->name() + HIM +
                              "来到了人间。");

                log_file("static/ultimate", sprintf("%s Have 121 SN. Wash %d Times. %s\n",
                          base_name(item), item->query("enchase/wash"), ctime(time())));
                return 1;
        } else
                return 0;
}
