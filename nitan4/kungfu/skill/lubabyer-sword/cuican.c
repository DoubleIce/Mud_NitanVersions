// This is player's own perform (Write by Lonely@nt2)
// Create by Ľ�ݺ���(Lubabyer) at Fri May 22 18:34:08 2009
// ������(cuican)

#include <ansi.h>
#include <combat.h>

#define PFM "��" HIW "������" NOR "��"

inherit F_SSERVER;

string *weapon_sk = ({
        "sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count, damage;
        int attack_time;
        int attack, i;

        if (! me->query("can_perform/" + "lubabyer-sword" + "/" + "cuican"))
                return notify_fail("�㻹û���ܵ�����ָ�㣬����������" PFM "��\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(PFM "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (member_array("sword", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if (! objectp(weapon = me->query_temp("weapon"))
                   || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("����ʹ�õ��������ԣ�����ʩչ" PFM "��\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                        return notify_fail(PFM "ֻ�ܿ���ʹ�á�\n");             
        }
        
        if ((int)me->query_skill("lubabyer-sword", 1) < 400)
                return notify_fail("��" + to_chinese("lubabyer-sword") + "������죬����ʩչ" PFM "��\n");

        if (member_array("sword", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("sword") != "lubabyer-sword")
                        return notify_fail("��û��׼��" + to_chinese("lubabyer-sword") + "������ʩչ" PFM "��\n");
        }
        
        if (me->query("neili") < 500)
                return notify_fail("�����ڵ���������������ʩչ" PFM "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$HIM$$N˫�־ٹ�ƽ����������Χ����$N������ٿ��裡$NĬ�����������ɰ��쾢���ԡ�̫ԨѨ�������ڡ��м�������������������������������վ���˫��֮�ϣ���̼��ɳ��ʯ�������䣬ǡ�Ƽ���������أ���׺�֮һ�ڡ�;ͻȻ�䣬ֻ��һ����Х��;����$N����������Ȼ��Ϊһ�壬�ƽ��ǽ������Ʒ��ƣ�������ǧ����ˣ�����������ơ���գ�ۼ�$N���ὣ��۵糸��Ӱ���к�Х�������ǽ���ҫ�����ǣ����������籼�ף�" + "\n" + NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
         
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 80, HIM "$n��״�󾪣���Ҫ���ܣ�ȴ�ѱ��޿ɱܣ�����һ������ʱ��$N����������������У������ĵ����ˡ�" + "\n" NOR);
                me->add("neili", -200);
             
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$p���Ʋ�������ˣ����ձܹ�$P�����ɱ�У����������У������ѿ���һ������ӣ�" + "\n" NOR;
                me->add("neili", -100);
        }
                
        message_sort(msg, me, target);
    
        msg = HIW "$N" HIW "����δ������ʽ��Ȼ��������ޱȣ�һת�����Ȼ�������С�\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 20;
                msg += HIR "$n" HIR "��$P" HIR "����Ѹ��֮����һʱ��֪����"
                       "�������ֵ���������������\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "��$p" HIY "����Ѹ��֮�������ѷ�������"
                       "æ��������С�ĵֵ���\n" NOR;
                count = 0;
        }

        message_combatd(msg, me, target);
        
        attack_time = 3;
        attack_time += me->query("jieti/times") * 2;
        if (attack_time > 8)
                attack_time = 8;

        me->add("neili", -attack_time * 20);

        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count);
                
        for (i = 0; i < attack_time; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, (member_array("sword", weapon_sk) == -1 ? 0 : weapon), 0);
        }
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count);
        me->start_busy(3 + random(attack_time/ 3));                        
        return 1;
}

