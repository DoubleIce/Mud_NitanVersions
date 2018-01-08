// This program is a part of NITAN MudLIB
// xiang.c �������

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;

        if (userp(me) && ! me->query("can_perform/dragon-strike/xiang"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ������졣\n"); 
                 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������졹ֻ����ս���жԶ���ʹ�á�\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("��������졹ֻ�ܿ���ʹ�á�\n");
                
        if (me->query("max_neili") < 2000)
                return notify_fail("���������Ϊ���������޷�ʩչ��������졹��\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("�������������\n");

        if ((int)me->query("qi") < 800)
                return notify_fail("����������ڲ�����\n");

        if ((int)me->query_skill("dragon-strike", 1) < 150)
                return notify_fail("��Ľ���ʮ���ƻ�򲻹����޷�ʹ�á�������졹��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�������޷�ʹ�á�������졹��\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("������û��׼��ʹ�ý���ʮ���ƣ��޷�ʹ�á�������졹��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����һ��������ǰһ����˫����Ȼ������"
              "�ͷ׶���������һ�����������ھ���֮�ϣ�\n\n" NOR;
              
        ap = attack_power(me, "strike") + me->query_str();
        dp = defense_power(target, "parry") + target->query_dex();
        
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 9;
                msg += HIR "$n" HIR "���$P" HIR "����ɽ�������ƣ���ȫ"
                       "�޷��ֵ���Ψ���˺�\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "����Ӧս���߾����ܻ���$P" HIC
                       "�⼸�ơ�\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -300);
        me->add("qi", -100);    // Why I don't use receive_damage ?
                                // Becuase now I was use it as a cost
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1 + random(5));
        me->add_temp("apply/attack", -count);

        return 1;
}
