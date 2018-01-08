// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

#define LIU "��" HIY "��" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (userp(me) && ! me->query("can_perform/jinshi-kuangjian/kuang"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" LIU "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIU "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" LIU "��\n");

        if (me->query_skill("force") < 180)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" LIU "��\n");

        if (me->query_skill("jinshi-kuangjian", 1) < 120)
                return notify_fail("������ǽ�����Ϊ����������ʩչ" LIU "��\n");

        if (me->query("neili") < 250)
                return notify_fail("�����������������ʩչ" LIU "��\n");

        if (me->query_skill_mapped("sword") != "jinshi-kuangjian")
                return notify_fail("��û�м������ǽ���������ʩչ" LIU "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�ۼ���ȫ����������ʱ����һ����ɫӰ�ӣ�һ�㽣â������$n" 
              HIR "��ǰ���󣬿��ٹ���$n��\n" NOR;
              
        ap = attack_power(me, "sword"); 
        dp = defense_power(target, "parry"); 

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                me->add("neili", -150);
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "�޼᲻�ݵĽ�����͸��" + weapon->name() + HIR "������ʹ$n" 
                                           HIR "������ֹ��ȫ���������$n" HIR "��δ��Ӧ����ʱ�����ش�����Ѫ�ɽ���\n" NOR);
                me->start_busy(2);
        } else
        {
                me->add("neili", -60);
                
                msg += CYN "����$p" CYN "�������ң�������������񵲿���$P"
                       CYN "�Ľ��С�\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
