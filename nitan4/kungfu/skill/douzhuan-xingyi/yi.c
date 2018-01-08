// yi.c ��ת����

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        object *obs;
        object der;
        string msg;
        int ap, dp;
        int damage;
        int i;

        if (userp(me) && ! me->query("can_perform/douzhuan-xingyi/yi"))
                return notify_fail("����ʱ������ʹ�ö�ת���ơ�\n");

        me->clean_up_enemy();
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����ת���ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("douzhuan-xingyi", 1) < 100)
                return notify_fail("��Ķ�ת���Ʋ�����죬����ʹ�þ��С�\n");

        if ((int)me->query_skill("shenyuan-gong", 1) < 100)
                return notify_fail("�����Ԫ����Ϊ�������ң�"
                                   "�������á���ת���ơ���\n");

        if (me->query("neili") < 60)
                return notify_fail("�����������������޷�ʹ�á���ת���ơ���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        weapon = target->query_temp("weapon");
        if (weapon && weapon->query("skill_type") == "pin")
                return notify_fail("�Է������õ���һ��СС���룬"
                                   "��û�а취ʩչ����ת���ơ���\n");

        msg = HIM "$N" HIM "�����ϻ��ķ�������������Ѩ��������"
              "�ζ��������������������ǣ����$n" HIM "����ʽ��\n";

        ap = attack_power(me, "parry"); 
        dp = defense_power(target, "force") +
             target->query_skill("dragon-strike", 1);

        der = 0;
        me->start_busy(2);
        me->add("neili", -50);
        if (ap > dp * 11 / 10)
        {
                // Success to make the target attack hiself
                msg += HIR "���$p" HIR "һ�л��������ô����Լ���"
                       "Ҫ���ϣ�����һ���ҽУ�ˤ����ȥ��\n" NOR;
                damage = target->query("max_qi");
                target->receive_damage("qi", damage / 2, me);
                target->receive_wound("qi", damage / 2, me);
        } else
        if (ap * 11 / 20 + random(ap) < dp)
        {
                // The enemy has defense
                msg += CYN "Ȼ��$p" CYN "�ڹ���񣬲�û�б�$P"
                       CYN "������ľ�����������\n" CYN;
        } else
        if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
        {
                // No other enemy
                msg += HIC "���$p" HIC "����ʽĪ������ı�"
                       "�˷��򣬾�Ȼ���Ʋ�ס���Һ�����û�б�"
                       "�ˣ�û����ɴ����\n" NOR;
        } else
        {
                string name;
                // Sucess to make the target attack my enemy
                der = obs[random(sizeof(obs))];
                name = der->name();
                if (name == target->name()) name = "��һ��" + name;
                msg += HIG "���$p" HIG "��������ʽ��������"
                       "�ı��˷���ͻȻ����" + name + HIG "��������" + 
                       name + HIG "���һ�����мܲ�����" NOR;
        }

        message_combatd(msg, me, target);

        if (der)
        {
                // Target attack my enemy
                for (i = 0; i < 2 + random(3); i++)
                {
                        if (! der->is_busy()) der->start_busy(1);
                        COMBAT_D->do_attack(target, der, target->query_temp("weapon"));
                }
        }

        return 1;
}
