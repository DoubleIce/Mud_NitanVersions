// dealer.c 商人
// Written by Lonely

#pragma save_binary

#include <ansi.h>
#include <command.h>
#include <dbase.h>
#include <name.h>
#include <config.h>

class goods {
        string name;
        string id;
        string type;
        string file;
        string unit;
        int amount;
        int value;
        int number;
}

nosave int uptime;
nosave int no_trade = 0;
nosave int load_goods = 0;

protected class goods *all_goods = ({});
protected void init_goods();
protected varargs int add_good_all(string file, int price, int amount);

/*
void setup()
{
        init_goods();
        ::setup();
        if (! uptime)
                uptime = time();
}

void init()
{
        add_action("do_buy", ({ "mai", "buy" }) );
        add_action("do_list", "list");
}
*/

protected void init_goods()
{
        array gds;
        string name;
        mixed items;
        int price;
        int i, number;

        no_trade = 1;
        all_goods = ({});

        items = this_object()->query("vendor_goods");
        if (! arrayp(items) && ! mapp(items) || ! sizeof(items))
        {
                no_trade = 0;
                load_goods = 1;                
                return;
        }

        gds = mapp(items) ? keys(items) : items;
        for (i = 0; i < sizeof(gds); i++)
        {
                name = gds[i];
                price = mapp(items) && items[gds[i]] > 0 ? items[gds[i]] : 0;
                add_good_all(name, price);
        }

        no_trade = 0;
        load_goods = 1;
}

protected varargs int add_good_all(string file, int price, int amount)
{
        object ob;
        class goods item;
        string type;

        if (! stringp(file))
                return 0;

        if (amount > 0 && sizeof(all_goods))
        {
                foreach(item in all_goods)
                {
                        if (item->file != file)
                                continue;

                        item->amount = amount;
                        return 1;
                }
        }

        call_other(file, "???");
        if (! objectp(find_object(file)))
        {
                log_file("log", sprintf("No found vendor good:%s\n", file));
                return 0;
        }

        /*
        ob = new(file);
        if (! ob)
        {
                log_file("log", sprintf("No found vendor good:%s\n", file));
                return 0;
        }
        */
        ob = find_object(file);

        if (ob->is_weapon_ob())
                type = "武器";
        else if (ob->is_armor_ob())
                type = "防具";
        else if (ob->is_liquid())
                type = "饮具";
        else if (ob->is_food())
                type = "食物";
        else if (ob->is_container())
                type = "容器";
        else if (ob->is_book())
                type = "书籍";
        else
                type = "其它";


        item = new(class goods);

        item->name = ob->query("name");
        item->id = ob->query("id");
        item->type = type;
        item->file = file;
        item->unit = ob->query("base_unit") ? ob->query("base_unit")
                                            : ob->query("unit");
        item->amount =  amount ? amount : -1;
        item->value = price ? price :
                        (ob->query("base_value") ? ob->query("base_value"):
                                                   ob->query("value"));
        item->number = sizeof(all_goods) + 1;

        all_goods += ({ item });
        // destruct(ob);
        return 1;
}

string is_vendor_good(string arg)
{
        mixed items;
        object ob;
        int i, n;

        n = sizeof(all_goods);
        if (! n) return "";

        for(i=0;i<n;i++)
        {
                if ((all_goods[i]->file)->id(arg)
                ||  all_goods[i]->file == arg
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg)
                {
                        if (all_goods[i]->amount != -1)
                                return "";

                        return all_goods[i]->file;
                }
        }

        return "";
}

void add_carry_good()
{
        mixed obs;
        int i, j;
        int amount;
        
        if (obs = all_inventory())
        {
                obs = unique_array(obs, (: base_name($1) :));

                for (i = 0; i < sizeof(obs); i++)
                {
                        for (j = 0; j < sizeof(obs[i]);  j++)
                        {
                                if (obs[i][j]->query("equipped") ||
                                    obs[i][j]->query("money_id") ||
                                    obs[i][j]->is_character())
                                        continue;

                                if (is_vendor_good(base_name(obs[i][j])) != "")
                                        continue;

                                amount = obs[i][j]->query_amount() ? obs[i][j]->query_amount()
                                                                   : sizeof(obs[i]);
                                add_good_all(base_name(obs[i][j]), 0, amount);
                        }
                }
        }
}
        
varargs int do_list(string arg)
{
        string output, desc;
        int amount;
        class goods item;
        object me, ob;
        mixed obs; 
        int i, j, number;
        
        me = this_player();

        if (no_trade)
                return notify_fail("现在正在盘库，请等一下再来。\n");

        if (! wizardp(me) && me->query_condition("killer"))
                return notify_fail(CYN "店铺不做杀人犯的生意！\n" NOR);

        if (me->is_busy())
        {
                write("你正在忙着呢。\n");
                return 1;
        }

        // 处理同房间有一个以上 dealer 的情况。
        if (arg && ! id(arg) &&
            arg != query("name"))
                return 0;
                
        if (! load_goods)
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }       
        
        add_carry_good();
        if (! sizeof(all_goods))
        {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        output = this_object()->name() + "目前出售以下物品：\n";
        /*
        output += sprintf("%5s%-30s%-10s%-10s\n","序 号", "    商  品","  单  价","       数  量");
        output += "----------------------------------------------------------------\n";
        */
        foreach (item in all_goods)
        {
                if (item->amount > 0)
                {
                        ob = present(item->id, this_object());
                        if (! ob)
                                item->amount = 0;
                }
                if (item->amount < 0)
                        desc = "大量供应";
                else if (item->amount == 0)
                        desc = "暂时缺货";
                else if (item->amount < 11)
                        desc = sprintf("仅剩%2d%2s", item->amount, item->unit);
                else if (item->amount < 31)
                        desc = sprintf("还剩%2d%2s", item->amount, item->unit);
                else
                        desc = "货源充足";

                output += sprintf("(%3d)%" + sprintf("%d", (30 + color_len(item->name))) +
                                  "-s：每%s%s" CYN "(现货%s)\n" NOR,
                                  item->number,
                                  item->name + "(" + item->id + ")",
                                  item->unit,
                                  MONEY_D->price_str(item->value), desc);
        }
        
        output += "\n";
        output += HIY"购买物品"NOR"  "YEL"buy <某物> from <某人>\n"NOR;
        output += HIY"观看物品"NOR"  "YEL"kan <某物> from <某人>\n"NOR;
        output += HIW"备注  一："HIY" <某物> "NOR"可输入 "YEL"序号 中文名字 英文名字"NOR"\n";
        output += HIW"备注  二："HIY" <某人> "NOR"可输入 "YEL"店主英文，店主中文"NOR"\n";
        output += HIW"备注  三："NOR"如果房间只有一个店主时，"YEL"from <某人>"NOR"可以省略。\n";
        write(output);
        return 1;
}

int do_buy(string arg)
{
        mapping room_obmap; 
        string  bunch;
        object *obs;
        object  ob;
        object  room;
        object  me;
        mixed   value;
        int     amount;
        int     val_factor;
        int     i, j, n;
        int     much;
        string  my_id;
        string  start_room;
        
        if (! arg)
                return notify_fail("你想买什么？\n");

        if ((me = this_player())->is_busy())
        {
                write("你正在忙着呢！\n");
                return 1;
        }

        if (no_trade)
                return notify_fail("现在正在盘库，请等一下再来。\n");

        if (query_temp("busy"))
        {
                write(CYN + name() + "不耐烦道：“没看见我这"
                      "儿正忙着么？”\n" NOR);
                return 1;
        }
        
        if (sscanf(arg,"%s from %s", arg, my_id) == 2)
        {
                if (! id(my_id) && my_id != query("name"))
                        return 0;
        }                

        if (! query("carried_items"))
        {
                if (stringp(start_room = query("startroom")) &&
                    (room = find_object(start_room)) != environment())
                {
                        // I am not in start room.
                        message_vision("$N大叫一声：“不好，我怎么跑到这儿来了？”\n"
                                       "说罢头也不回的急急忙忙的溜走了。\n", this_object());
                        if (! objectp(room) ||
                            ! mapp(room_obmap = room->query_temp("objects")) ||
                            member_array(this_object(), values(room_obmap)) == -1)
                        {
                                destruct(this_object());
                        } else
                                this_object()->move(room);
                        return 1;
                }
        }

        if (sizeof(filter_array(all_inventory(me), 
                                (: ! $1->query("equipped") :))) >= MAX_ITEM_CARRIED)
        {
                write("你身上的东西太多了，先处理一下再买东西吧。\n");
                return 1;
        }

        if (sscanf(arg, "%d %s", amount, arg) != 2)
                // not indicate the amount of the items
                amount = 1;

        if (amount < 1)
        {
                write(CYN + name() + "疑惑的问道：“没见过这种买法，你到底想买几个单位呢？”\n" NOR);
                return 1;
        }
        
        if (amount > 5000)
        {
                write(CYN + name() + "忙道：“慢慢来，一次最多买五千个单位。”\n" NOR);
                return 1;
        }

        if (! load_goods)
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }
        
        add_carry_good();
        n = sizeof(all_goods);
        if (! n)
        {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }
        
        val_factor = 10;
        for(i = 0; i < n; i++)
        {
                if ((all_goods[i]->file)->id(arg)
                ||  filter_color(all_goods[i]->name) == arg
                ||  sprintf("%d", all_goods[i]->number) == arg)
                {
                        if (! (all_goods[i]->amount))
                        {
                                command(sprintf("say 对不起，目前这%s" CYN "缺货，您过一段时间再来吧",
                                        all_goods[i]->name));
                                return 1;
                        }

                        if (all_goods[i]->amount > 0)
                        {
                                val_factor = 12;
                                obs = all_inventory(this_object());
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        if (base_name(obs[j]) == all_goods[i]->file)
                                        {
                                                ob = obs[j];
                                                break;
                                        }
                                }
                                
                                if (! ob)
                                {
                                        all_goods[i]->amount = 0;
                                        command(sprintf("say 对不起，目前这%s" CYN "丢失，您过一段时间再来吧",
                                                all_goods[i]->name));
                                        return 1;
                                }
                                if (amount > all_goods[i]->amount)
                                        amount = all_goods[i]->amount;
                        }
                        
                        if (! function_exists("query_amount", get_object(all_goods[i]->file)))
                        {
                                if (amount > 100) 
                                {
                                        amount = 100; 
                                        write("这类物品限制一次最多买一百个单位。\n");
                                }
                        }
                                
                        break;
                }
        }

        if (i >= n)
        {
                write("你想买什么？\n");
                return 1;
        }
        
        value = count_mul(amount, all_goods[i]->value);
        value = count_div(count_mul(value, val_factor), 10);
        
        /*
        if (value > 1000000000 || value * val_factor / val_factor != value)
        {
                write(CYN + name() + CYN "大惊失色道：这么大一笔生意？我"
                      "可不好做。\n" NOR);
                return 1;
        }
        */
        
        if (me->query_skill("higgling", 1) > 99)
        {
                if (me->query_skill("higgling", 1) > 399)
                        value = count_div(count_mul(value, 7), 10);
                else
                if (me->query_skill("higgling", 1) > 199)
                        value = count_div(count_mul(value, 8), 10);
                else
                if (me->query_skill("higgling", 1) > 99)
                        value = count_div(count_mul(value, 9), 10);
        } else
        if (stringp(bunch = me->query("bunch/bunch_name")) &&
            bunch == (string)this_object()->query("bunch/bunch_name"))
                value = count_div(count_mul(value, 8), 10);
        // 开了店的玩家才采购时享受八折优惠
        else
        if (SHOP_D->is_owner(me->query("id")))
                value = count_div(count_mul(value, 8), 10);

        if (count_le(value, 0))
                value = 1;

        switch (MONEY_D->player_pay(me, value))
        {
        case 0:
                write(CYN + name() + "冷笑道：“穷光蛋，一边呆着去！”\n" NOR);
                return 1;
        case 2:
                write(CYN + name() + "皱眉道：“您还有没有零"
                      "钱啊？银票我可找不开。”\n" NOR);
                return 1;
        case 3:
                write(CYN + name() + "皱眉道：“您还有没有零"
                      "钱啊？钻石我可找不开。”\n" NOR);
                return 1;
        default:
                set_temp("busy", 1);

                if (me->query_skill("higgling", 1) > 99 || SHOP_D->is_owner(me->query("id")))
                {
                        switch (random(3))
                        {
                        case 0:
                                command("say 既然大家都是做买卖的，就给你打点折吧。");
                                break;
                        case 1:
                                command("say 也罢，既然是大老板光顾，就便宜点卖给你吧。");
                                break;
                        default:
                                command("say 呵呵。大老板又来采购么？那么就给你打点折吧。");
                                break;
                        }
                }  else
                if (stringp(bunch = me->query("bunch/bunch_name")) &&
                    bunch == (string)this_object()->query("bunch/bunch_name"))
                        command("say 既然大家都是同帮兄弟，就给你打点折吧。");

                much = atoi(count_div(value, 5));
                if (much <= 0) much = 1;

                if (stringp(bunch == (string)this_object()->query("bunch/bunch_name")) &&
                    bunch != me->query("bunch/bunch_name"))
                        BUNCH_D->add_bunch_info(bunch, "npc_money", much);

                if (ob)
                {
                        object old_ob;
                        if (ob->query_amount())
                        {
                                ob = new(base_name(old_ob = ob));
                                ob->set_amount(amount);
                                old_ob->add_amount(-amount);
                                ob->move(me, 1);
                        } else
                        {
                                obs = all_inventory();
                                obs = filter_array(obs, (: base_name($1) == base_name($(ob)) :));
                                n = 0;
                                for (j = 0; j < sizeof(obs); j++)
                                {
                                        n++;
                                        if (n > amount)
                                                break;

                                        obs[j]->move(me, 1);
                                }
                        }
                } else
                {
                        ob = new(all_goods[i]->file);
                        if (! ob)
                        {
                                write("这里出现问题，请找巫师解决。\n");
                                log_file("log", sprintf("No found vendor good:%s\n", all_goods[i]->file));
                                return 1;
                        }
                        
                        if (ob->query_amount())
                        {
                                ob->set_amount(amount);
                                ob->move(me, 1);
                       
                        } else
                        {
                                ob->move(me, 1);
                                for (j = 0; j < amount-1; j++)
                                {
                                        ob = new(all_goods[i]->file);                                       
                                        ob->move(me, 1);
                                }
                        }
                                
                }

                all_goods[i]->amount -= amount;                
                message_vision(sprintf("$N从$n那里买下了%s%s%s%s。\n",
                        all_goods[i]->amount == 0 ? "最后" : "",
                        chinese_number(amount),
                        all_goods[i]->unit,
                        all_goods[i]->name), me, this_object());
        }

        remove_call_out("enough_rest");
        call_out("enough_rest", 1);

        return 1;
}

void destruct_it(object ob)
{
        if (! ob || environment(ob))
                return;
        destruct(ob);
}

void enough_rest()
{
        delete_temp("busy");
}

int do_look(string arg)
{
        string who;
        object ob, me;
        int i, n;

        if ((me = this_player())->is_busy())
        {
                write("你正在忙着呢！\n");
                return 1;
        }

        if (! arg || arg == "")
        {
                write("你想看什么？\n");
                return 1;
        }

        // 处理同房间有一个以上 dealer 的情况。
        if (sscanf(arg,"%s from %s", arg, who) == 2)
        {
                if (! id(who) && who != query("name"))
                        return 0;
        }

        if (! load_goods)
        {
                init_goods();
                if (! uptime)
                        uptime = time();
        }
        
        add_carry_good();
        n = sizeof(all_goods);
        if (! n)
        {
                write(sprintf("目前%s没有可以卖的东西。\n", query("name")));
                return 1;
        }

        for (i = 0; i < n; i++)
        {
                if (all_goods[i]->amount > 0)
                {
                        ob = present(all_goods[i]->id, this_object());
                        if (! ob)
                                all_goods[i]->amount = 0;
                }
                
                if (all_goods[i]->amount == 0)
                        continue;
                        
                if((all_goods[i]->file)->id(arg)
                || filter_color(all_goods[i]->name) == arg
                || sprintf("%d",all_goods[i]->number) == arg)
                {
                        ob = get_object(all_goods[i]->file);
                        LOOK_CMD->look_item(me, ob);
                        // destruct(ob);
                        return 1;
                }
        }
        
        if (i >= n)
        {
                write("你想看什么？\n");
                return 1;
        }
}

int do_value(string arg)
{
        object ob;
        int value;
        mixed ns;

        if (! arg || ! (ob = present(arg, this_player())))
        {
                return notify_fail("你要估什么的价？\n");
        }
        
        if (ob->query("money_id"))
        {
                write(CYN + name() + "道：你没用过钱啊？\n" NOR);
                return 1;
        }

        if (ob->is_character())
        {
                write(CYN + name() + "道：这你也拿来估价？\n" NOR);
                return 1;
        }

        if (ob->query_amount())
                value = ob->query("base_value");
        else
                value = ob->query("value");

        if (ob->query("consistence"))
                value = value * ob->query("consistence") / 100;

        if (value < 1)
                write(CYN + name() + "道：" + ob->query("name") +
                      CYN "一文不值！\n" NOR);
        else
        if (ob->query("no_drop") || (ns = ob->query("no_sell")))
        {
                if (stringp(ns))
                {
                        write(CYN + name() + "道：" + ns + "\n" NOR);
                        return 1;
                }
                write(CYN + name() + "道：“这东西有点古怪，我可不好估价。”\n" NOR);
        } else
                write(CYN + name() + "道：“" + ob->query("name") + CYN "值" +
                        MONEY_D->price_str(value * 50 / 100) + "。”\n" NOR);
        return 1;
}

int do_sell(string arg)
{
        object me;
        object ob;
        object nob;
        string my_id;
        int amount;
        int value;
        int res;
        int max_count;
        mixed ns;

        if (! arg)
                return notify_fail("你要卖什么？\n");

        if (sscanf(arg,"%s to %s", arg, my_id) == 2)
        {
                if (! id(my_id) && my_id != query("name"))
                        return 0;
        }        

        if (sscanf(arg, "%d %s", amount, arg) != 2)
                // not indicate the amount of the goods
                amount = 1;

        if (amount < 1) 
        {
                write(CYN + name() + "疑惑的问道：“没见过这种买法，你到底想买几件呢？”\n" NOR);
                return 1; 
        }
        
        me = this_player();
        if (! (ob = present(arg, me)))
        {
                write("你身上没有这种东西啊！\n");
                return 1;
        }

        max_count = ob->query_amount();
        if (! max_count)
        {
                // not combined object
                if (amount > 1)
                {
                        write(ob->name() + "这种东西不能拆开来卖。\n");
                        return 1;
                }
                max_count = 1;
        } else
        {
                // is combined object
                if (amount > max_count)
                {
                        write("你身上没有这么多" + ob->name() + "。\n");
                        return 1;
                }
        }

        if (ob->query("money_id"))
        {
                write(CYN + name() + "道：“哈哈哈哈！你想卖「钱」？？”\n" NOR);
                return 1;
        }

        if (ob->is_character())
        {
                write(CYN + name() + "道：“哼！我这里做正经生"
                      "意，不贩卖这些！”\n" NOR);
                return 1;
        }

        if (ob->query("unique") || ob->query("no_pawn") ||
            ob->query("replica_ob") || ob->query("bindable"))
        {
                write(CYN + name() + "摇摇头，道：“这种东西我"
                      "不识货，不敢要。”\n" NOR);
                return 1;
        }

        if (ob->query("no_drop") ||
            (ns = ob->query("no_sell")))
        {
                if (stringp(ns))
                {
                        command("say " + ns);
                        return 1;
                }
                write(CYN + name() + "摇摇头，道：“这种东西我"
                      "不识货，不敢要。”\n" NOR);
                return 1;
        }

        if (is_vendor_good(base_name(ob)) != "") 
        {
                write(CYN + name() + "笑道：“我卖给你好不好？”\n" NOR);
                return 1;
        }

        if (ob->query("food_supply"))
        {
                write(CYN + name() + "不屑道：“嘿嘿，剩菜剩饭留给"
                      "您自己用吧。”\n" NOR);
                return 1;
        }
        
        if (ob->query("shaolin"))
        {
                write(CYN + name() + "惊道：“小的胆子很小，可"
                      "不敢买少林庙产。”\n" NOR); 
                return 1;
        }

        if (ob->query("mingjiao"))
        {
                write(CYN + name() + "忙摇头道：“小的只有一个脑袋，可"
                      "不敢买魔教的东西。”\n" NOR);
                return 1;
        }

        if (ob->query("consistence"))
                value = value * ob->query("consistence") / 100;

        if (max_count > 1)
        {
                if (ob->query("base_value") * amount / amount != ob->query("base_value"))
                {
                        write(CYN + name() + CYN "大惊失色道：这么大一笔生意？我"
                              "可不好做。\n" NOR);
                        return 1;
                }
                value = ob->query("base_value") * amount;
        }
        else
                value = ob->query("value");

        if (value < 2)
                write(CYN + name() + "随手一扔，道：" + ob->query("name") +
                      CYN "一文不值！\n" NOR);
        else
        {
                if (max_count == amount)
                        res = ob->move(this_object());
                else
                {
                        nob = new(base_name(ob));
                        nob->set_amount(amount);
                        if (res = nob->move(this_object()))
                                ob->add_amount(-amount);
                        else
                                destruct(nob);
                }

                if (res)
                {
                        message_vision("$N卖掉了一" + ob->query("unit") +
                                       ob->query("name") + "给$n。\n",
                                       this_player(), this_object());
                        MONEY_D->pay_player(this_player(), (value / 2));
                        ob->sold();
                } else
                        write(CYN + name() + "摇摇头，道：“对不起，"
                              "我现在不收货了。”\n" NOR);
        }
        return 1;
}

int do_pawn(string arg)
{
        object me;
        object ob;
        object nob;
        string my_id;
        int amount;
        int value;
        int res;
        int max_count;
        mixed max_pawn_goods_num;
        int have_pawn_num;
        mapping all_pawn;
        mixed ns;

        return notify_fail("暂不开放！\n");
        if (! arg)
                return notify_fail("你要当什么？\n");

        if (sscanf(arg, "%s to %s", arg, my_id) == 2 && ! id(my_id))
                return 0;

        if (sscanf(arg, "%d %s", amount, arg) != 2)
                // not indicate the amount of the goods
                amount = 1;

        if (amount < 1) 
        {
                write(CYN + name() + "疑惑的问道：“没见过这种当法，你到底想当几件呢？”\n" NOR);
                return 1; 
        }
        
        me = this_player();
        if (! (ob = present(arg, me)))
        {
                write("你身上没有这种东西啊！\n");
                return 1;
        }

        max_count = ob->query_amount();
        if (! max_count)
        {
                // not combined object
                if (amount > 1)
                {
                        write(ob->name() + "这种东西不能拆开来当。\n");
                        return 1;
                }
                max_count = 1;
        } else
        {
                // is combined object
                if (amount > max_count)
                {
                        write("你身上没有这么多" + ob->name() + "。\n");
                        return 1;
                }
        }

        max_pawn_goods_num = count_div(me->query("combat_exp"), 500000);
        sscanf(max_pawn_goods_num, "%d", max_pawn_goods_num);

        // if (max_pawn_goods_num > 0)
                max_pawn_goods_num += 4;

        if (max_pawn_goods_num > 20)
                max_pawn_goods_num = 20;

        have_pawn_num = (int)me->query("pawn_goods_num");
        if (amount + have_pawn_num > max_pawn_goods_num)
        {
                write(CYN + name() + "摇头道：按你现在的地位，最多只能在本号存" + 
                            chinese_number(max_pawn_goods_num) + "个物品，" + 
                            (have_pawn_num?"你已经存了" + chinese_number(have_pawn_num) + "个物品，":"") +
                            "东西你收回吧！\n" NOR);
                return 1;
        }

        if (ob->is_no_clone() || ob->query("unique") || ob->query("bindable"))
        {
                write(CYN + name() + "摇摇头道：这个宝贝小号不敢收！\n" NOR);
                return 1;
        }

        if (ob->query("setdbase"))
        {
                write(CYN + name() + "摇摇头道：这个宝贝小号不敢收！\n" NOR);
                return 1;
        }

        if (ob->is_item_make())
        {
                write(CYN + name() + "摇摇头道：玩家自己制造的物品不能拿来当！\n" NOR);
                return 1;
        }

        if (ob->query("money_id"))
        {
                write(CYN + name() + "道：哈哈哈哈！你想当「钱」？？\n" NOR);
                return 1;
        }

        if (ob->is_character())
        {
                write(CYN + name() + "道：哼！我这里做正经生"
                      "意，不贩卖人口！\n" NOR);
                return 1;
        }

        if (ob->query("no_drop") ||
            (ns = ob->query("no_sell")))
        {
                if (stringp(ns))
                {
                        command("say " + ns);
                        return 1;
                }
                write(CYN + name() + "摇摇头，道：这种东西我"
                      "不识货，不敢要。\n" NOR);
                return 1;
        }

        if (ob->query("only_do_effect"))
        {
                write (CYN + name() + "奸笑道：这种药品，不知道是否已经变质，小号也没能力留存，你收回吧！\n" NOR);
                return 1;
        }

        if (ob->query("food_supply"))
        {
                write(CYN + name() + "不屑道：嘿嘿，剩菜剩饭留给"
                      "您自己用吧。\n" NOR);
                return 1;
        }
        
        if (ob->query("shaolin"))
        {
                write(CYN + name() + "惊道：小的胆子很小，可"
                      "不敢收少林庙产。\n" NOR); 
                return 1;
        }

        if (ob->query("mingjiao"))
        {
                write(CYN + name() + "忙摇头道：小的只有一个脑袋，可"
                      "不敢收魔教的东西。\n" NOR);
                return 1;
        }

        if (max_count > 1)
                value = ob->query("base_value") * amount;
        else
                value = ob->query("value");
        if (value < 2)
                write(CYN + name() + "随手一扔，道：" + ob->query("name") +
                      CYN "一文不值！\n" NOR);
        else
        {
                message_vision("$N当掉了一" + ob->query("unit") +
                               ob->query("name") + "给$n。\n",
                               this_player(), this_object());
                MONEY_D->pay_player(this_player(), value * 30 / 100);

                all_pawn = me->query("pawn_goods");
                if (! all_pawn) all_pawn = ([ ]);

                all_pawn[base_name(ob)] += amount;

                me->set("pawn_goods", all_pawn);
                me->add("pawn_goods_num", amount);
                                        
                if (max_count == amount) 
                        destruct(ob);                     
                else ob->add_amount(-amount);
        }
        return 1;
}

int do_redeemp (string target) 
// 丽春院赎玩家（男、女） 
{ 
        object me,ob,dest; 
     
        me=this_player(); 
        ob=this_object(); 
        if(!target || target=="") 
                return notify_fail(ob->query("name")+"俯到你的耳边悄声问道：你要赎什么人？\n");
 
        if(!objectp(dest=find_player(target))) 
        //find_player() - 用名字寻找一个玩家 
                return notify_fail(HIR+"玩家("+target+")目前似乎不在线上！\n"+NOR);
 
        if( !dest->query("selled")) 
        // 是否要用condition来处理？时间长了没有人赎，就自动当妓女或者男妓？ 
                return notify_fail(ob->query("name")+"急道：你可别诬陷好人，我怎么会非法扣押玩家呢！\n");
 
        switch (MONEY_D->player_pay(me, dest->query("per") * 700)) 
        // switch (me->pay_money(dest->query("per") * 700, 0)) 
        { 
                case 0: 
                        return notify_fail("没钱还想赎人？信不信我把你给卖了！\n"); 
                case 2: 
                        return notify_fail("您的零钱不够了，银票又没人找得开。\n"); 
                default: 
                        message_vision(HIG+"$N从$n那里赎回了"+dest->query("name")+"。\n"+NOR, me, ob); 
                        dest->move(environment(ob)); 
                        dest->set("startroom",base_name(environment(ob))); 
                        dest->delete("selled"); 
                        message("vision", HIY+"只听见嗖的一声，一个遍体鳞伤的家伙从天花板上掉了下来！\n"+NOR, 
                                environment(dest), dest); 
                        tell_object(dest, "你被"+HIC+me->query("name")+NOR+"赎了出来。\n"); 
        } 
        return 1; 
} 

int do_redeem(string arg) 
{
        mixed  goods;
        object *obs;
        object me;
        object ob;
        int i;
        int amount;
        int value;
        mapping count;
        mapping price;
        mapping unit;
        mapping all_pawn;
        string short_name;
        string prefix;
        array dk;
        string ob_file;
        string my_id;
        string msg;
        array gks;

        me = this_player();

        if (!arg)
        {
                count   = ([]);
                unit    = ([]);
                price   = ([]);
    
                goods = me->query("pawn_goods");

                if (!mapp(goods) || !sizeof(goods))
                        return notify_fail(name() + "翻了翻帐簿道：你并没有在本号当任何物品！\n");

                gks = keys(goods);

                for (i = 0; i < sizeof(gks); i++)
                {
                        object gob;
                        call_other(gks[i], "???");
                        if (! objectp(find_object(gks[i])))
                        {
                                log_file("log", sprintf("No found pawn good:%s\n", gks[i]));
                                continue;
                        }
                        gob = find_object(gks[i]);

                        short_name = gob->name(1) + "(" + gob->query("id") + ")";
                        if (gob->query("base_unit"))
                                prefix = "base_";
                        else
                                prefix = "";
                        unit  += ([ short_name : gob->query(prefix + "unit") ]);
                        price += ([ short_name : gob->query(prefix + "value") ]);
                        count += ([ short_name : goods[gks[i]] ]);
                }

                msg = name() + "翻了翻帐簿道：你在本号目前典当有以下物品：\n";
                dk = sort_array(keys(unit), 1);
                for (i = 0; i < sizeof(dk); i++)
                {
                        int p;
                        p = price[dk[i]];
                        msg += sprintf("%" + sprintf("%d", (30 + color_len(dk[i]))) +
                               "-s：每%s赎金%s" CYN "(计有%s)\n" NOR, dk[i], unit[dk[i]], MONEY_D->price_str(p),
                               chinese_number(count[dk[i]]) + unit[dk[i]]);
                }
                msg += name() + "嘿嘿一笑：总共" + chinese_number((int)me->query("pawn_goods_num")) + "件物品。\n";
                write(msg);
                return 1;
        } else
        {
              if(me->is_busy())
                        return notify_fail("什么事都得等你忙完再说吧！\n");

                if (sscanf(arg, "%s from %s", arg, my_id) == 2 && ! id(my_id))
                        return 0;

                if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
                {
                        write("你身上的东西太多了，先处理一下再买东西吧。\n");
                        return 1;
                }

                if (sscanf(arg, "%d %s", amount, arg) != 2)
                        // not indicate the amount of the goods
                        amount = 1;

                if (amount < 1) 
                {
                        write(CYN + name() + "疑惑的问道：“没见过这种赎法，你到底想赎几件呢？”\n" NOR);
                        return 1; 
                }
                
                if (amount > 10)
                {
                        write(CYN + name() + "忙道：慢慢来，一次最多赎十件。\n" NOR);
                        return 1;
                }

                goods = me->query("pawn_goods");
                if (!goods) goods = ([]);

                gks = keys(goods);
                if (arrayp(gks))
                        for (i = 0; i < sizeof(gks); i++) 
                        {
                                if (gks[i]->id(arg)) 
                                        ob_file = gks[i];
                                else if (filter_color(gks[i]->name(1)) == arg) 
                                        ob_file = gks[i];
                        }

                if (!ob_file)
                {
                        write(name() + "摇头道：你并没有在本号当这样货物。\n");
                        return 1;
                }

                if (amount > goods[ob_file])
                {
                        write(name() + "摇头道：你在本号当的" + arg + "一共才" + chinese_number(goods[ob_file]) + "件。\n");
                        return 1;
                }

                ob = new(ob_file);

                if (amount > 1 && ! ob->query_amount())
                {
                        write(ob->name() + "只能一" + ob->query("unit") +
                                "一" + ob->query("unit") + "的买。\n");
                        return 1;
                }

                if (amount > 1) ob->set_amount(amount);

                call_out("destruct_it", 0, ob);

                if (ob->query("money_id"))
                {
                        write(CYN + name() + "大笑道：哈哈！你要买"
                                "钱？有意思！\n" NOR);
                        return 1;
                }

                if (query_temp("busy"))
                {
                        write(CYN + name() + "不耐烦道：没看见我这"
                                "儿正忙着么？\n" NOR);
                        return 1;
                }

                value = ob->query("value");


                switch (MONEY_D->player_pay(me, value))
                {
                case 0:
                        write(CYN + name() + "冷笑道：穷光蛋，一边呆着去！\n" NOR);
                        return 1;
                case 2:
                        write(CYN + name() + "皱眉道：您还有没有零"
                                "钱啊？银票我可找不开。\n" NOR);
                        return 1;
                default:
                        set_temp("busy", 1);
                        if (ob->query_amount())
                                message_vision("$N从$n那里赎回了" + ob->short() + "。\n",
                                       this_player(), this_object());
                        else
                                message_vision("$N从$n那里赎回了一" + ob->query("unit") + 
                                       ob->query("name") + "。\n",
                                       this_player(), this_object());
                        ob->move(this_player(), 1);
                        all_pawn = me->query("pawn_goods");
                        all_pawn[base_name(ob)] -= amount;
                        if (all_pawn[base_name(ob)] <= 0) 
                        {
                                map_delete(all_pawn,base_name(ob));
                        }
                        me->set("pawn_goods",all_pawn);
                        me->add("pawn_goods_num",-amount);
                }
                this_player()->start_busy(1);
                remove_call_out("enough_rest");
                call_out("enough_rest", 1 + random(3));

                return 1;
        }
}       

int do_check(string arg) { return do_redeem(0); }

void reset()
{
        int i, t;
        object *obs;

        t = time();
        if (! uptime)
                uptime = t;

        if (t - uptime >= 3600)
        {
                uptime = t;
                init_goods();
        }

        obs = all_inventory();
        for (i = 0; i < sizeof(obs); i++)
                if (i >= 100 || obs[i]->query_weight() >= 1000000)
                        destruct(obs[i]);
}
