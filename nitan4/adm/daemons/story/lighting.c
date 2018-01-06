// story:lighting 电击

#include <ansi.h>

mixed random_gift();

nosave mixed *story = ({
        "电母：这...这是啥？",
        "雷公：怎么了你？",
        "电母杏目圆睁：岂有此理！快说，你背地里都瞒着我干些什么？",
        "雷公：变态！",
        "电母：你...",
        "...",
        "嘿...",
        "哎呦...",
        "噼哑！！！！！！！！！！！～～～～～",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIR "【天灾人祸】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob, pob;
        string msg;
        mapping ips;
        string ip, *ks;

        ips = ([ ]);
        /*
        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 environment($1)->query("outdoors") &&
                                                 ! $1->query("env/no_story") &&
                                                 ! $1->query("doing") :));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        */

        foreach (pob in all_interactive())
        {
                if (wizardp(pob) || ! pob->query("born") ||
                    ! living(pob) || ! environment(pob) ||
                    ! environment(pob)->query("outdoors") ||
                    pob->is_ghost() ||
                    pob->query("env/no_story") ||
                    pob->query("doing") ||
                    environment(pob)->is_chat_room())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (! sizeof(ips))
                return 0;

        // 随即抽一个IP
        ks = keys(ips);
        ip = ks[random(sizeof(ks))];

        // 在该IP地址上随即抽取一个玩家
        ob = ips[ip][random(sizeof(ips[ip]))];
        
        if (ob->query("gift/lighting") > 4 || random(5) > 1)
        {
                msg = HIR + ob->name(1) + "一声惨叫，软软的倒了下去。" NOR;
                if (count_lt(ob->query("combat_exp"), 1000000) ||
                    ob->query("qi") < 1000)
                        ob->unconcious();
                else
                {
                        ob->set("qi", 10);
                        ob->set("eff_qi", 10);
                        ob->set("jing", 1);
                        ob->set("eff_jing", 1);
                }
        } else
        {
                msg = HIC "霎那间" + ob->name(1) + "浑身火花四射，犹如天神一般，神威凛凛。" NOR;
                ob->add("con", 1);
                ob->add("gift/lighting", 1);
        }
        return msg;
}

