// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        //if (userp(me) && ! me->query("can_perform/zhenshan-zhang/da"))
        //        return notify_fail("�����ڻ�����ʹ�á���ɽ��ţ����һ�У�\n");
                
        if (! target || ! me->is_fighting(target))
                return notify_fail("��ɽ��ţֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�ø�ɽ��ţ��\n");         
                
        if ((int)me->query_skill("zhenshan-zhang", 1) < 60)
                return notify_fail("�����ɽ�Ʋ�����죬����ʹ�ø�ɽ��ţ��\n");

        if (me->query("max_neili") < 500)
                return notify_fail("����ڹ���Ϊ���㣬�޷�ʩչ��ɽ��ţ��\n");

        if (me->query("neili") < 150)
                return notify_fail("����������̫�����޷�ʩչ��ɽ��ţ��\n");
                        
        msg = WHT "$N" WHT "�Ŷ���������һ������ʹ����ɽ��ţ��˫�ƶ�׼$n"
              WHT "ƽƽ�Ƴ���\n" NOR;
        me->add("neili", -100);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 50,
                                           HIR "$n" HIR "������æ���һ�ݣ����ֻ��"
                                           "�ؿ�һ�𣬶�ʱ����������ԭ��$N" HIR 
                                           "���ھ����ˣ�\n"
                                           ":����@?");
                if (! target->is_busy())
                        target->start_busy(3 + random(2));
                me->start_busy(1);
        } else 
        {
                me->start_busy(2);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ����û���ϵ���\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

