// story:lighting ���

#include <ansi.h>

mixed random_gift();

nosave mixed *story = ({
        "��ĸ����...����ɶ��",
        "�׹�����ô���㣿",
        "��ĸ��ĿԲ�������д�����˵���㱳���ﶼ�����Ҹ�Щʲô��",
        "�׹�����̬��",
        "��ĸ����...",
        "...",
        "��...",
        "����...",
        "���ƣ�������������������������������",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIR "�������˻���" NOR; }

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

        // �漴��һ��IP
        ks = keys(ips);
        ip = ks[random(sizeof(ks))];

        // �ڸ�IP��ַ���漴��ȡһ�����
        ob = ips[ip][random(sizeof(ips[ip]))];
        
        if (ob->query("gift/lighting") > 4 || random(5) > 1)
        {
                msg = HIR + ob->name(1) + "һ���ҽУ�����ĵ�����ȥ��" NOR;
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
                msg = HIC "���Ǽ�" + ob->name(1) + "��������䣬��������һ�㣬�������ݡ�" NOR;
                ob->add("con", 1);
                ob->add("gift/lighting", 1);
        }
        return msg;
}

