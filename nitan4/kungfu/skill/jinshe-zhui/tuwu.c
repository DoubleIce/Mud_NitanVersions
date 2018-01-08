// This program is a part of NITAN MudLIB
// tuwu.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, ap, dp;
        int damage;
        string msg;
        object weapon;

        /*
        if (me->query_temp("jinshe/tuwu"))
                return notify_fail("����õĽ�������û�����žͳ��С�\n");
        */

        if (! target) target = offensive_target(me);
        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ����ս����ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("handing")) ||
            // (string)weapon->query("id") != "jinshe zhui" ||
            weapon->query_amount() < 1)
                // return notify_fail("������û�ý���׶������ʹ�þ��У�\n");
                return notify_fail("������û�ý���׶����������������ʹ�þ��У�\n");

        if ((skill = me->query_skill("jinshe-zhui", 1)) < 100)
                return notify_fail("��Ľ���׶��������죬����ʹ�ý�������\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�����������ˡ�\n");

        if (target->query_temp("jinshe/tuwu"))
                return notify_fail("�Է��Ѿ������ˣ���Ͳ����˰ɡ�\n");

        weapon->add_amount(-1);

        msg = HIY "$N" HIY "һ����Х������΢�������н���׶��Ȼ���Ϸ�"
              "�����˸�Ȧ�����Ѹ��Ϯ��$n" HIY "����ǰ��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -200);
                damage = damage_power(me, "strike");
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 3, me);
        
                msg += HIM "ֻ��һ����ɨҶ��������У�$N" HIM "���е�"
                       "����׶������Ŀ�Ĺ�â����ҫ��$n" HIM "��ð�𻨣�"
                       "\n������ǰһ���ص������⣬$n" HIM
                       "ɶҲ�������ˣ�\n" NOR;
                message_combatd(msg, me, target);
                target->set_temp("jinshe/tuwu", 1);
                target->set_temp("block_msg/all", 1);
                me->start_call_out((: call_other, __FILE__, "tuwu_end", me, target :),
                                   skill / 100);
        } else
        {
                msg += CYN "$n" CYN "���а���һ������æ��"
                       "�ˣ���������ö����׶��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}

void tuwu_end(object me, object target)
{
        if (target && living(target))
        {
                message_combatd("$NĨ��Ĩ������" HIR "��Ѫ" NOR "�������������ۡ�\n",
                                target);
                target->set_temp("block_msg/all", 0);
                write(HIR "������Ĩ������������Ѫ����������Χ���龰��\n"NOR);
                target->delete_temp("jinshe/tuwu");
        }

        return;
}
