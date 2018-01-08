
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define FENG "��" HIW "�����" NOR "��"

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon, weapon2;
        string w1, w2;
        int ap, dp;
     
        me = this_player();

        if (userp(me) && ! me->query("can_perform/yinsuo-jinling/feng"))
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(FENG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("����������ԣ��޷�ʹ��" FENG "��\n");

        if (me->query_skill_mapped("whip") != "yinsuo-jinling")
                return notify_fail("��û�м������������壬����ʹ��" FENG "��\n");

        if ((int)me->query_skill("yinsuo-jinling", 1) < 140)
                return notify_fail("����������岻����죬��ʹ����" FENG "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" FENG "��\n");

        if ((int)me->query("neili") < 400)
               return notify_fail("��������������������ʩչ" FENG "��\n"NOR);

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        w1 = weapon->name();

        damage = (int)me->query_skill("whip") / 2;
        damage += random(damage);

        ap = me->query_skill("whip");
        dp = target->query_skill("parry");

        msg = "\n" HIW "ֻ��$N" HIW "����" + w1
              + HIW "ĺ��һ�����ó�������Ӱ����"
              "ʱ�Ʒ�������" + w1 + HIW "Я��"
              "����֮��ɨ��$n" HIW "��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "$n" HIR "ֻ����Ӱ���أ��ۻ�����"
                                           "�������޷������ֵ���һ���Һ�����Ѫ��"
                                           "��������\n" NOR);
        } else
        {
                msg += CYN "����$p" CYN "�����磬"
                       "˿����Ϊ����Ī�����ʽ����"
                       "������ֵ������⿪����\n" NOR;
        }

        ap = me->query_skill("whip");
        dp = target->query_skill("dodge");

        msg += "\n" HIW "������$N" HIW "һ��"
               "���ȣ�" + w1 + HIW "�͵����"
               "һ����" + w1 + HIW "��ʱ����"
               "һ�����磬�Ѵ�$n" HIW "����"
               "Ϯ����\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$n" HIR "��һ���ɣ�ͻȻ�е���"
                                           "һ��" HIR "�ι�֮ʹ���ѱ����д��Ѫ"
                                           "��ģ����\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "һ����ߣ���Ԥ��$N"
                       CYN "�д�һ�ţ������������������"
                       "��񿪣�\n" NOR;
        }

        if (objectp(weapon2 = target->query_temp("weapon")))
        {
                msg += "\n" HIW "$N" HIW "üͷ΢�壬��"
                       "������һ��ֻ����쬡���һ����"
                       "�ֹ���һ�У�" + w1 + HIW "����"
                       "�ǰ㵯��$n" HIW "�󲿣�\n" NOR;

                ap = me->query_skill("whip");
                dp = target->query_skill("force");

                if (ap / 4 + random(ap) > dp)
                {
                        w2 = weapon2->name();
                        msg += HIR "ֻ����������һ����" + w1 +
                               HIR "������$p" + w2 + HIR "�ϣ�"
                               "$p" HIR "����һ�飬" + w2 + HIR
                               "��Ҳ�óֲ�ס�����ֵ��ڵ��ϡ�\n"
                               NOR;
                        me->add("neili", -50);
                        weapon2->move(environment(target));
                } else
                {
                        msg += CYN "����$p" CYN "������$P" CYN
                               "����ͼ����æб���㿪��\n" NOR;
                        me->add("neili", -30);
                }
        }
        me->start_busy(2 + random(4));
        me->add("neili", -300);
        message_combatd(msg, me, target);
        return 1;
}