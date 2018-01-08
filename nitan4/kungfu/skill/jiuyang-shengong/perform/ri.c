// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#include "/kungfu/skill/eff_msg.h";

inherit F_SSERVER;

#define RI "��" HIW "ħ�����޼�" NOR "��"

int perform(object me)
{
        object *obs;
        string msg;
        int damage;
        int ap, dp;
        int flag;
        int i;
        int p;

        if (userp(me) && ! me->query("can_perform/jiuyang-shengong/ri"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" RI "��\n");

        me->clean_up_enemy();
        if (! me->is_fighting())
                return notify_fail(RI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(RI "ֻ�ܿ���ʩչ��\n");
                
        if (me->query("max_neili") < 8000)
                return notify_fail("�����������Ϊ�����������޷�ʹ��" RI "��\n");

        if (me->query_skill("jiuyang-shengong", 1) < 250)
                return notify_fail("��ľ����񹦻�������죬����ʩչ" RI "��\n");

        if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊȭ�ţ�����ʩչ" RI "��\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("������û�м���������Ϊ�ڹ�������ʩչ" RI "��\n");

        if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return notify_fail("������û��׼��ʹ�þ����񹦣�����ʩչ" RI "��\n");

        if ((int)me->query("neili") < 2000)
                return notify_fail("��������������޷�����" RI "��\n");

        msg = HIY "ֻ��$N" HIY "˫Ŀ΢�գ��������졣���Ķ�ʱ����һ���ޱȴ��۵�"
              "���ţ����ǰ�\n�塸" NOR + HIW "ħ�����޼�" NOR + HIY "������ʱ"
              "����������ɳ���𣬿������ȣ��������ڡ�$N" HIY "\n�漴��£����"
              "�����ű��ѿ����������ܵ����������â���Ժ��������ԡ�\n\n" NOR;

        message_combatd(msg, me);

        me->add("neili", -1000);
        me->start_busy(5);

        ap = attack_power(me, "unarmed") + me->query_con();

        obs = me->query_enemy();
        for (flag = 0, i = 0; i < sizeof(obs); i++)
        {
                dp = defense_power(obs[i], "force") + obs[i]->query_con();

                if (ap * 2 / 3 + random(ap) > dp)
                {
                        switch (random(2))
                        {
                        case 0:
                                tell_object(obs[i], HIR "��ֻ����ǰ����������Χ����������"
                                                    "�ڣ���â��������һ��͸����롣\n" NOR);
                                break;

                        default:
                                tell_object(obs[i], HIR "��ֻ����ǰ����������Χ����������"
                                                    "�ڣ���â����ǧ��ϸ��һ����������㡣\n"
                                                    NOR);
                                break;
                        }

                        damage = attack_power(me, "force");
                        damage = damage * 3 / 2;

                        obs[i]->receive_damage("qi", damage, me);
                        obs[i]->receive_wound("qi", damage, me);

                        obs[i]->receive_damage("jing", damage / 6, me);
                        obs[i]->receive_wound("jing", damage / 10, me);

                        p = (int)obs[i]->query("qi") * 100 / (int)obs[i]->query("max_qi");

                        switch (random(5))
                        {
                        case 0:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "һ���Һ�������������������"
                                      "�ۡ���Ż��һ�����Ѫ��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 1:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "���ɳ���Զ�����صĵ�����"
                                      "���ϣ������ս�����Ҳû����վ��"
                                      "��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 2:
                                msg = HIR "ֻ��" + obs[i]->name() +
                                      HIR "����ײײ�����������������"
                                      "�ڵء���ü������������һ�ɽ���"
                                      "��\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        case 3:
                                msg = HIR "��â������" + obs[i]->name() +
                                      HIR "ȴ�Ǵ�����������Ҳ��������"
                                      "����Ѫ������Ť����ɷ�ǿֲ���\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;

                        default:
                                msg = HIR + obs[i]->name() +
                                      HIR "��æ�������ˣ���ֻ����ǰ��"
                                      "â���ǣ�һ��������ȫ���Ѷ�����"
                                      "���˿ڣ���Ѫ�ɽ���\n" NOR;
                                msg += "( " + obs[i]->name() + eff_status_msg(p) + " )\n\n";
                                break;
                        }
                        if (! obs[i]->is_busy())
                        obs[i]->start_busy(1);
                        message("vision", msg, environment(me), ({ obs[i] }));
                        obs[i]->add("neili", -500);
                        flag = 1;
                } else
                {
                        tell_object(obs[i], HIY "��ֻ����ǰ����������Χ������"
                                            "�����ڣ���֮����æ�����ڹ�������"
                                            "������\n" NOR);
                }
                if (obs[i]->query("neili") < 0)
                        obs[i]->set("neili", 0);
        }

        if (! flag) 
                message_vision(HIY "ֻ����â������ȴû���κ��˱�$N"
                               HIY "���л��С�\n\n" NOR, me, 0, obs);

        return 1;
}
