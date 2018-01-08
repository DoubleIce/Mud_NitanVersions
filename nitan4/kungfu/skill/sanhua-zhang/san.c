// This program is a part of NITAN MudLIB
// san.c ��Ůɢ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        //if (userp(me) && ! me->query("can_perform/sanhua-zhang/san"))
        //        return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ����Ůɢ������\n");
                
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ůɢ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("sanhua-zhang", 1) < 135)
                return notify_fail("���ɢ���Ʒ�������죬����ʹ����Ůɢ����\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("����ڹ���Ϊ����������ʩչ��Ůɢ����\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("�����������������޷�ʹ����Ůɢ����\n");

        if (me->query_skill_mapped("strike") != "sanhua-zhang") 
                return notify_fail("��û�м���ɢ���ƣ��޷�ʹ����Ůɢ����\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һЦ��˫��һ����Ȼ��������"
              "��Ӱ������ǧ��ֻ����һ�빥��$n" HIY "��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                
                me->add("neili", -150);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "���$p" HIR "û�ܱܿ�$P" HIR
                                           "���Ī����Ʒ�����������������ƣ�"
                                           "����ÿ�����Ѫ������ˤ����\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                me->start_busy(3);
                me->add("neili", -50);
                msg += CYN "����$p" CYN "ʶ����$P"
                       CYN "��һ�У�ббһԾ�ܿ���\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

