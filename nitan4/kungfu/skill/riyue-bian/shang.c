// This program is a part of NITAN MudLIB
// shang.c ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/riyue-bian/shang"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ�����־�����\n");
                 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����־���ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("riyue-bian", 1) < 180)
                return notify_fail("������±޷���Ϊ������Ŀǰ����ʹ�����־���\n");

        if (me->query("neili") < 400)
                return notify_fail("��������������޷�ʹ�����־���\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("��û�м������±޷�������ʹ�����־���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��Ȼ��Ц�����е�" + weapon->name() +
              HIY "һ����ʱ��ñ�ֱ����ͬ����һ��ɴ���$n" + HIY "��\n" NOR;

        ap = attack_power(me, "whip") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                me->add("neili", -300);                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "ֻ��$p" HIR "һ���ҽУ�" + weapon->name() +
                                           HIR "��Ȼ����$p" + HIR "�����ϣ������Ѿ�"
                                           "�Դ�����Ѫ�ɽ����ߣ��Ҳ����ԣ�\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                me->add("neili", -100);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�����Ī���һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
