// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define HUAN "��" HIR "�ұػ�֮" NOR "��"

inherit F_SSERVER;

int can_not_hubo(){ return 1; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int per;

        if (userp(me) && ! me->query("can_perform/xuedao-dafa/huan"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" HUAN "��\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("����ڹ���򲻹�������ʩչ" HUAN "��\n");

        if ((int)me->query_skill("xuedao-dafa", 1) < 1000)
                return notify_fail("���Ѫ���󷨻������ң�����ʩչ" HUAN "��\n");

        if (me->query_skill_mapped("force") != "xuedao-dafa")
                return notify_fail("��û�м���Ѫ����Ϊ�ڹ�������ʩչ" HUAN "��\n");

        if (me->query_skill_mapped("blade") != "xuedao-dafa")
                return notify_fail("��û�м���Ѫ����Ϊ����������ʩչ" HUAN "��\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("��Ŀǰ��Ѫ����������ʩչ" HUAN "��\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("��Ŀǰ�������㣬����ʩչ" HUAN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        msg = HIR "$N" HIR "����" + weapon->name() + "ֱָ$n" HIR"�����к������������ʲô���Ծ��ǲ�֪�����������ң��ұػ�֮����\n"
              HIR "ֻ��" + weapon->name() + "����Ũ��Ѫ�⡢��ζ�̱ǣ�ӳ������ֱ��ŨѪ������\n";
              
        if (ap / 2 + random(ap) > dp)
        {
                per = atoi(count_div(count_mul(me->query("eff_qi"), 100), me->query("max_qi")));
                if (per > 60)
                        damage = damage_power(me, "blade");
                else
                if (per < 20)
                        damage = -1;
                else
                        damage = target->query("max_qi") * per / 100;      
                          
                me->add("neili", -150);
                me->start_busy(2);
                
                if (damage > 0)
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "��$n" HIR "���У�" + weapon->name() + "�ĵ���Խ��Խ��ѹ���Լ�����͸��������"
                                           HIR "ֱ����ȻһŻѪ��ȴ����" + weapon->name() + "�Ѿ����Լ��������������Ĺ켣��\n" NOR);
                else
                {
                        msg += HIR "��$n" HIR "���У�" + weapon->name() + "�ĵ���Խ��Խ��ѹ���Լ�����͸��������"
                               HIR "ֱ����ȻһŻѪ��ȴ����" + weapon->name() + "�Ѿ����Լ��������������Ĺ켣��\n" NOR;
                        target->die(me);
                }
        } else
        {
                me->start_busy(2);
                msg += CYN "�����⵶Ҫ����$n" CYN "���ϣ�$N" CYN "����һ����Ѫ�������$n" CYN "˳�ƹ���һ�ԣ����ǲ����з��������$N"
                       CYN "�ı�ɱһ����\n"NOR;
                me->add("neili", -100);
        }
        
        message_combatd(msg, me, target);
        return 1;
}
