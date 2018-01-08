// This program is a part of NITAN MudLIB
// qi.c ���ν���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
                
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ν���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 360)
                return notify_fail("����ڹ���򲻹���ʹ�������ν�����\n");

        if ((int)me->query_skill("six-finger", 1) < 180)
                return notify_fail("�����ݤ�񽣲�������������ʹ�����ν�����\n");

        if (me->query("max_neili") < 6000)
                return notify_fail("���������Ϊ��������ʹ�����Ϭ�������ν�����\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("��������������޷�ʹ�����ν�����\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("��û�м��������񽣣��޷�ʹ�����ν�����\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "��ָһ����һ���������׵����ν���ֱ��$n" HIC "��ǰ��ȥ��\n" NOR;  

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");
             
        weapon = target->query_temp("weapon");
        me->start_busy(3);
        if (ap * 2 / 3 + random(ap) > dp)
        { 
                damage = damage_power(me, "finger") * 4 / 3;
                target->receive_damage("jing", damage / 2, me);
                target->receive_wound("jing", damage / 3, me);
                me->add("neili", -400);
                if (! objectp(weapon) || weapon->query("skill_type") == "pin")
                        msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 65,
                                                   HIR "$p" HIR "ֻ������ǰһ���ʹ����Ѫ"
                                                   "�Դ��ڼ����������ǰ��ʱһ�ڣ�\n" NOR);
                else
                if (weapon->is_item_make() || weapon->query("damage") > 180 ||
                    weapon->query("skill_type") == "hammer")
                        msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 70,
                                                   HIR "$p" HIR "��" + weapon->name() + HIR "��ͼ�мܣ�"
                                                   HIR "������ɽ������Ϭ����͸��" + weapon->name() +
                                                   HIR "ֱ���$p" HIR "������Ѫ������������Ҫ��ת������\n" NOR);
                else
                {
                        msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 80,
                                                   HIR "$p" HIR "��ת" + weapon->name() + HIR "��������"
                                                   "ǰ��ֻ��ž��һ����" + weapon->name() +
                                                   HIR "������أ��������죡\n$n" HIR "����"
                                                   "���������ۡ�������һ����Ѫ����ɫ��ĲҰס�\n" NOR);
                        weapon->move(environment(me));
                        weapon->set("no_wield", weapon->name() + "�Ѿ�����ˣ�û��װ���ˡ�\n");
                        weapon->set_name("�����" + weapon->name());
                        weapon->set("value", 0);
                }
                if (! target->is_busy())
                target->start_busy(3 + random(2)); 
        } else
        {
                msg += CYN "����$p" CYN "�ڹ���Ϊ������Ὣ����������������Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

