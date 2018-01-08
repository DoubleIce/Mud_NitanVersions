// This program is a part of NITAN MudLIB
// feilong.c ��ɽ�����������������ɽ���

#include <ansi.h>
#include <combat.h>

#define XIAN "��" HIM "�����������ɽ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, fp, pp;

        if (userp(me) && ! me->query("can_perform/huashan-jianfa/xian"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" XIAN "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(XIAN "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if (me->query_temp("perform") == 1  ||
            me->query_temp("perform2") == 1 ||
            me->query_temp("perform3") == 1)
                return notify_fail("�����������š���â���ء�\n");


        if ((int)me->query_skill("huashan-jianfa", 1) < 160)
                return notify_fail("�㻪ɽ����������죬�޷�ʩչ" XIAN "��\n");

        if ((int)me->query_skill("dodge", 1) < 160)
                return notify_fail("���Ṧ��Ϊ�������޷�ʩչ" XIAN "��\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�����������������޷�ʩչ" XIAN "��\n");

        if (me->query_skill_mapped("sword") != "huashan-jianfa")
                return notify_fail("��û�м�����ɽ�������޷�ʹ��" XIAN "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -280);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        fp = defense_power(target, "force");
        pp = defense_power(target, "parry");

        message_sort(HIW "\n$N" HIW "��Хһ��������" + weapon->name() + HIW "�漴��ͣת������ӿ��"
                        "�������ǻ�ɽ���ھ�����" HIM "�����������ɽ�" HIW "��������" + weapon->name() + HIW 
                        "����ͻ�䣬һ����ʱ��Ϊ������Ϯ��$n" HIW "����\n" NOR, me, target);        

        msg = HIM "$N" HIM "������ȫ���˵��˽��ϣ�����һ������ͷֱ����\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "б��������\n" NOR;
        else
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40 + random(10),
                                           HIR "$n" HIR "��æ���ˣ���Ȼ��ܲ�������$N"
                                           HIR "��һ����ÿ�����Ѫ���������ˡ�\n" NOR);
        }

        msg += HIM "\n$N" HIM "Ȧת" + weapon->name() + HIM "���������������ƻֺ룬�����ݺᣬ���˷�����˼��\n" NOR;
        if (ap / 2 + random(ap) < fp)
                msg += CYN "$n" CYN "�����ӽ���Խ����\n" NOR;
        else
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40 + random(10),
                                           HIR "�������Ƶ���켰��$n" HIR "�������ü���"
                                           "���мܣ�ֻ��$N" HIR "����������$n"
                                           HIR "������ʱ��Ѫ���죡\n" NOR);
        }

        msg += HIM "\n$N" HIM "�������ã�����$p" HIM "���ģ�����֮�죬��λ֮׼����������δ�š�\n" NOR;
        if (ap / 2 + random(ap) < pp)
                msg += CYN "$n" CYN "���ڿ��У��������У�ֻ�ܻӳ�һ�У�������$N"
                       CYN "���ϣ���һ������ƮȻ��ȥ��\n" NOR;
        else
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50 + random(10),
                                           HIR "$n" HIR "���ڿ��У��������ü����У�ֻ��$N"
                                           HIR "�˽��ӹ���$n" HIR "�����Һ�����Ѫ���·ɽ���\n" NOR);
        }

        me->start_busy(4);
        message_combatd(msg, me, target);
        return 1;
}
