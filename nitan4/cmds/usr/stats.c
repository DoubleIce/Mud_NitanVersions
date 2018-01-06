// stats cmds

#include <ansi.h>
#include <mudlib.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string sp;
 
        seteuid(getuid(me));

        if (! wizardp(me) && time() - me->query_temp("last_stats") < 5) 
                return notify_fail("ϵͳ�������̾���������� ....\n");  

        me->set_temp("last_stats", time());  
        if (arg && arg != "")
        {
                if (wizardp(me) || me->query("couple/child_id"))
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob)) 
                                return notify_fail("��Ҫ�쿴˭��״̬��\n");

                        if (! wizardp(me) && me->query("couple/child_id") != ob->query("id"))
                                return notify_fail("��Ҫ�쿴˭��״̬��\n");

                } else
                        return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");
        } else
                ob = me;

        if (userp(ob) && (! stringp(ob->query("born")) || ! ob->query("born")))
                return notify_fail("��û�г����ţ��쿴ʲô��\n");
        
        sp = (ob == me ? "��" : ob->name()) + "Ŀǰ�ĸ���������Ч��һ��\n";
        sp += HIC "��" HIY "��������������������������������������������������������������" HIC "��\n" NOR;
        
        sp += sprintf(HIW BRED "\n%|66s\n\n" NOR, "�������Լ�����������");
        
        sp += sprintf(HIC "���������ӡ� " HIW " %-10d" HIC "�����Ը��ӡ� " HIW " %-10d" HIC "�����Ǹ��ӡ� " HIW " %-10d\n",
                      ob->query_temp("apply/str"), ob->query_temp("apply/int"), ob->query_temp("apply/con"));
                      
        sp += sprintf(HIC "�������ӡ� " HIW " %-10d" HIC "��Ǳ�����ޡ� " HIW " %-10d" HIC "��������ޡ� " HIW " %-10d\n",
                      ob->query_temp("apply/dex"), ob->query_temp("apply/max_potential"), ob->query_temp("apply/max_experience"));

        sp += sprintf(HIC "���������ޡ� " HIW " %-10d" HIC "���������ޡ� " HIW " %-10d" HIC "����Ѫ���ޡ� " HIW " %-10d\n",
                      ob->query_temp("apply/max_neili"), ob->query_temp("apply/max_jingli"), ob->query_temp("apply/max_qi"));

        sp += sprintf(HIC "���������ޡ� " HIW " %-10d" HIC "���о������� " HIW " %-10d" HIC "���о�Ч���� " HIW " %-10s\n",
                       ob->query_temp("apply/max_jing"), ob->query_temp("apply/research_times"), ob->query_temp("apply/research_effect") + "%");

        sp += sprintf(HIC "����ϰ������ " HIW " %-10d" HIC "����ϰЧ���� " HIW " %-10s" HIC "��ѧϰ������ " HIW " %-10d\n",
                      ob->query_temp("apply/practice_times"), ob->query_temp("apply/practice_effect") + "%", ob->query_temp("apply/learn_times"));                                                                  

        sp += sprintf(HIC "��ѧϰЧ���� " HIW " %-10s" HIC "����ȡ������ " HIW " %-10d" HIC "����ȡЧ���� " HIW " %-10s\n",
                      ob->query_temp("apply/learn_effect") + "%", ob->query_temp("apply/derive_times"), ob->query_temp("apply/derive_effect") + "%");
                                            
        sp += sprintf(BRED "\n%|66s\n\n" NOR, "ս����ؼ�װ��������");
        
        sp += sprintf(HIC "�������ȼ��� " HIW " %-10d" HIC "�������ȼ��� " HIW " %-10d" HIC "�������ȼ��� " HIW " %-10d\n",
                      ob->query_temp("apply/attack"), ob->query_temp("apply/defense"), ob->query_temp("apply/dodge"));

        sp += sprintf(HIC "���мܵȼ��� " HIW " %-10d" HIC "���������С� " HIW " %-10s" HIC "�����з����� " HIW " %-10s\n",
                      ob->query_temp("apply/parry"), ob->query_temp("apply/ap_power") + "%", ob->query_temp("apply/dp_power") + "%");

        sp += sprintf(HIC "�������мܡ� " HIW " %-10s" HIC "�����Ӷ����� " HIW " %-10s" HIC "�����ӹ����� " HIW " %-10s\n",
                      ob->query_temp("apply/avoid_parry") + "%", ob->query_temp("apply/avoid_dodge") + "%", ob->query_temp("apply/avoid_attack") + "%");

        sp += sprintf(HIC "�������ڹ��� " HIW " %-10s" HIC "�������˺��� " HIW " %-10d" HIC "�������˺��� " HIW " %-10d\n",
                      ob->query_temp("apply/avoid_force") + "%", ob->query_temp("apply/damage"), ob->query_temp("apply/unarmed_damage"));
                                                                  
        sp += sprintf(HIC "�������˺��� " HIW " %-10s" HIC "��ս�������� " HIW " %-10d" HIC "�������˺��� " HIW " %-10s\n",
                      ob->query_temp("apply/da_damage") + "%", ob->query_temp("apply/armor"), ob->query_temp("apply/add_poison") + "%");
        
        sp += sprintf(HIC "������Ч���� " HIW " %-10s" HIC "���䶳�˺��� " HIW " %-10s" HIC "������Ч���� " HIW " %-10s\n",
                      ob->query_temp("apply/reduce_poison") + "%", ob->query_temp("apply/add_cold") + "%", ob->query_temp("apply/reduce_cold") + "%");

        sp += sprintf(HIC "�������˺��� " HIW " %-10s" HIC "������Ч���� " HIW " %-10s" HIC "�������˺��� " HIW " %-10s\n",
                      ob->query_temp("apply/add_fire") + "%", ob->query_temp("apply/reduce_fire") + "%", ob->query_temp("apply/add_lighting") + "%");

        sp += sprintf(HIC "������Ч���� " HIW " %-10s" HIC "��ħ���˺��� " HIW " %-10s" HIC "����ħЧ���� " HIW " %-10s\n",
                      ob->query_temp("apply/reduce_lighting") + "%", ob->query_temp("apply/add_magic") + "%", ob->query_temp("apply/reduce_magic") + "%");

        sp += sprintf(BRED "\n%|66s\n\n" NOR, "�ռ�������");
        
        sp += sprintf(HIC "��������Ѫ�� " HIW " %-10d" HIC "�����ɾ����� " HIW " %-10d" HIC "�������С� " HIW " %-10s\n",
                      ob->query_temp("apply/def_damage"), ob->query_temp("apply/def_damage"), ob->query_temp("apply/add_locked") + "%");

        sp += sprintf(HIC "�������С� " HIW " %-10s" HIC "��æ�Ҷ��֡� " HIW " %-10d" HIC "������æ�ҡ� " HIW " %-10d\n",
                      ob->query_temp("apply/avoid_locked") + "%", ob->query_temp("apply/add_busy"), ob->query_temp("apply/reduce_busy"));

        sp += sprintf(HIC "���������֡� " HIW " %-10s" HIC "���ֿ������� " HIW " %-10s" HIC "��׷���˺��� " HIW " %-10s\n",
                      ob->query_temp("apply/add_xuruo") + "%", ob->query_temp("apply/avoid_xuruo") + "%", ob->query_temp("apply/add_damage") + "%");

        sp += sprintf(HIC "�������˺��� " HIW " %-10s" HIC "���������ܡ� " HIW " %-10d\n",
                       ob->query_temp("apply/reduce_damage") + "%", ob->query_temp("apply/add_skill"));
                      
        sp += sprintf(BRED "\n%|66s\n\n" NOR, "��Ա������");                
                                                                                                                      
        sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "��%s���Ѿ������� " NOR + HIC "%s\n" NOR, 
                        LOCAL_MUD_NAME(), time_period(ob->query("online_time")));
        
        if (MEMBER_D->is_valid_member(ob))
                sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "��������������ʱ�仹�� " NOR + HIY "������\n" NOR); 
        else
        {
                if (ob->query("online_time") / 3 < ob->query("offline_time"))
                        ob->set("offline_time", ob->query("online_time") / 3);
                sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "��������������ʱ�仹�� " NOR + HIY "%s\n" NOR, 
                              time_period(ob->query("online_time") / 3 - ob->query("offline_time")));
        }
                              
        sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "�����˫������ʱ�仹�� " NOR + HIW "%s\n" NOR,
                      time_period(ob->query("time_reward/quest")));         
        sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "����ĸ�Ч����ʱ�仹�� " NOR + HIM "%s\n" NOR,
                      time_period(ob->query("time_reward/study")));      
                        
        sp += "\n";
        sp += HIC "��" HIY "��������������������������������������������������������������" HIC "��\n" NOR;
        
        me->start_more(sp);
        return 1;
}

