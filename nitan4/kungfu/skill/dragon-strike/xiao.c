// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define XIAO "��" HIW "��Х����" NOR "��"

int can_not_hubo() { return 1;}

int perform(object me)
{
        string msg;
        object weapon, target;
        int ap, dp, count;
        int i, damage;

        if( me->query("family/family_name") != "ؤ��" )
                return notify_fail("�㲻��ؤ����ӣ��޷�ʹ��" XIAO "��\n");

        if( !me->query("reborn/times") )        
                return notify_fail("����δת���������޷�ʹ��" XIAO "��\n");
                
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAO "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(XIAO "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("dragon-strike", 1) < 1000)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" XIAO "��\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" XIAO "��\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" XIAO "��\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("����ڹ���Ϊ����������ʩչ" XIAO "��\n");

        if ((int)me->query("max_neili") < 30000)
                return notify_fail("���������Ϊ����������ʩչ" XIAO "��\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("�����ڵ��������㣬����ʩչ" XIAO "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if (objectp(weapon = target->query_temp("weapon")))
        {        
                msg = HIW "$N" HIW "����һ����ȫ���ھ��ŷ��������ұ۷����⳶����ͼ��$n"
                      HIW "��" + weapon->name() + HIW "�������С�\n" NOR;

                ap = attack_power(me, "strike");
                dp = defense_power(target, "parry");
                        
                if (ap / 2 + random(ap) > dp)
                {
                        me->add("neili", -300);
                        msg += HIR "$n" HIR "ֻ����Χ����ӿ��������" + weapon->name() +
                               HIR "��Ȼ����ס����$N" HIR "�������ַ�ȥ��\n" NOR;
                        
                        weapon->move(environment());
                } else
                {
                        me->add("neili", -200);
                        msg += CYN "$n" CYN "ֻ����Χ����ӿ������æ����������" + weapon->name() + 
                               CYN "������ܲ�͸�磬ʹ��$N" CYN "�޴����֡�\n" NOR;                        
                }
                message_combatd(msg, me, target);
        } 
        
        msg = WHT "��Ȼ$N" WHT "���μ�����ʩ������ʮ����֮��" HIW "�𾪰���" NOR +
              WHT "����ȫ�������Ķ���˫������ɽ������ѹ��$n" WHT "��\n"NOR;  

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        damage = damage_power(me, "strike");
        
        if (ap / 2 + random(ap) > dp)
        {                
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 50,
                                           HIR "$n" HIR "ֻ��һ���ӿ����������"
                                           "����ܣ�$N" HIR "˫������ǰ�أ���Ѫ��"
                                           "���������\n" NOR);
                target->set_status_xuruo(5);
                me->add("neili", -400);                
        } else
        {
                msg += CYN "$n" CYN "�ۼ�$N" CYN "������ӿ��˿����"
                       "��С���æ������һ�ԡ�\n" NOR;
                me->add("neili", -200);
        }
        
        message_combatd(msg, me, target);    
        
        msg = HIY "������$N" HIY "ʩ������ʮ���ơ�" HIW "��������"
              HIY "����˫�Ʒ���������һ�����������ھ���֮�ϡ�\n" NOR;                      

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");
        
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "���$N" HIR "����ɽ������Ĺ�"
                       "�ƣ���ȫ�޷��ֵ����м�ɢ�ң������˺�\n" NOR;
                count = ap / 10;
        } else
        {
                msg += HIC "$n" HIC "�ĵ�΢΢һ������֪�����æ"
                       "�������񣬽߾����ܻ���$N" HIC "����������\n" NOR;
                count = 0;
        }
        
        message_combatd(msg, me, target);

        me->add_temp("apply/attack", count);
        me->add_temp("apply/unarmed_damage", count / 3);

        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (! target->is_busy())
                        target->start_busy(5);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add("neili", -300);
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 3);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIW "$N" HIW "����б�ӣ�ǰ������δ�������������ֵ�����Ȼ�ֹ���һ�С�" HIR "�����л�" HIW "�����Ƽз��ƣ���������\n"
              HIW "����һ��������ǽ����ǰ�����ȥ��$n" HIW "ֻ����Ѫ��ӿ����Ϣ���ǡ�\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage * 3;
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 80 + random(20),
                                          HIR "���$p����������$P�ƾ���ʱ���ض�"
                                          "������ʱ������Ѫ���硣\n" NOR);
        } else
        {
                msg += HIC "$p�ۼ��������ͣ����μ��ˣ�˲��"
                       "Ʈ�����ɣ��ѳ�����֮�⡣\n" NOR;
        }
        message_combatd(msg, me, target);
        me->start_busy(3 + random(4));
        me->add("neili", -400 - random(600));
        return 1;        
}

