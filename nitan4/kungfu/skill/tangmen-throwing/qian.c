#include <ansi.h>
#include <combat.h>

#define HUA "��" HIR "����ǧǧ��" NOR "��"

#include "/kungfu/skill/eff_msg.h";
inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p, n;
        int ap, dp;
        string pmsg;
        string msg;
        object weapon;

        if (playerp(me) && ! me->query("can_perform/tangmen-throwing/qian"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչ" HUA "��\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUA "ֻ����ս���жԶ���ʹ�á�\n");

        if (! objectp(weapon = me->query_temp("handing")) ||
            ((string)weapon->query("id") != "qianqian jie" &&
            (string)weapon->query("skill_type") != "throwing"))
                return notify_fail("����������û�����Ű�������ǧǧ�ᣬ����ʩչ" HUA "��\n");
                
        if ((skill = me->query_skill("tangmen-throwing", 1)) < 140)
                return notify_fail("������Ű���������죬����ʩչ" HUA "��\n");

        if ((int)me->query("tangmen/yanli") < 80)
                return notify_fail("�������̫���ˣ�Ŀ�겻��ȷ���޷�ʩչ" HUA "��\n");
                
        if ((int)me->query_skill("boyun-suowu", 1) < 140)
                return notify_fail("��Ĳ�������������죬�޷�ʩչ" HUA "��\n");
                
        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���Ϊ���㣬����ʩչ" HUA "��\n");

        if ((int)me->query("max_neili") < 1200)
                return notify_fail("���������Ϊ���㣬����ʩչ" HUA "��\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("�������������㣬����ʩչ" HUA "��\n");

        if (! living(target) || target->is_busy())
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -100);

        msg = HIR "\n$N" HIR "ͻȻ����һֹ���ӻ�������һ��" + weapon->name() + HIR "�����������ᣬһ������$n " HIR "��ȥ��\n"
              "ֻ��$n" HIR "�����������������Ĺ�Ӱ��һ�������ӿ����¡�\n"NOR;

        ap = attack_power(me, "throwing"); 
        dp = defense_power(target, "dodge") +
             target->query_skill("dugu-jiujian", 1); 
        
        message_combatd(msg, me, target);
        tell_object(target, HIR "\n�㼱æ��������ϣ���ܹ��㿪��������" + weapon->name() + HIR "��\n"NOR);
        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR"��Ȼ�������Ĺ�Ӱһ����û��$n����һ�٣�����" + weapon->name() + HIR "���ϣ����������\n" NOR;
                message_combatd(msg, me, target);
                tell_object(target, HIR "��ֻ����ȫ������" + weapon->name() + HIR "Խ��Խ������ͷһ��ֻ����" + weapon->name() + HIR "�Ѿ������Ƕ�����Ƥ���С�\n" NOR);
                // weapon->hit_ob(me, target, me->query("jiali") + 200); 
                if (weapon->query("id") != "qianqian jie")
                        weapon->add_amount(-1);
                else
                        weapon->move(target);              
                target->start_busy(ap / 100 + random(ap / 100));
        } else
        {
                tell_object(target, HIR "��Ȼ�������Ĺ�Ӱһ����û��������һ����æ������������䡣\n" NOR);
                msg = HIR "$n" HIR "��æ���Ա�һ�ݣ��㿪��������" + weapon->name() + HIR "�������Ե��Ǳ�������\n" NOR;
                message_combatd(msg, me, target);
                if ( target->query("neili") < 1000 )
                        target->set("neili", 0);
                else
                        target->add("neili", -1000);
                weapon->move(environment(me));
                me->start_busy(3);
        }
        return 1;
}

