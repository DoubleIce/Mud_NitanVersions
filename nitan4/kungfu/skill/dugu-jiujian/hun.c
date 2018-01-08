// This program is a part of NITAN MudLIB
// hun.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define HUN     "��" HIM "����" NOR "��"

int can_not_hubo() { return 1;}

void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        string msg;
        object *ob, weapon;
        int ap, dp, count, p;
        int i, damage;

        if( !me->query("reborn/times") )    
                return notify_fail("����δת���������޷�ʩչ" HUN "��\n");

        if( me->query("family/family_name") != "��ɽ��" )
                return notify_fail("�㲻�ǻ�ɽ�ɵ��ӣ��޷�ʩչ" HUN "��\n");
        /*
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(HUN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        */

        if( !me->is_fighting() )
                return notify_fail(HUN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_temp("dugu_jianhun") )
                return notify_fail("������ʹ��" HUN "�ˣ�\n");

        weapon = me->query_temp("weapon");
        if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
                return notify_fail("�������޽�������ܹ�ʩչ" HUN "��\n");

        if( (int)me->query_skill("dugu-jiujian", 1) < 1000 )
                return notify_fail("��Ķ��¾Ž�������죬����ʩչ" HUN "��\n");

        if( me->query_skill("force") < 1200 )
                return notify_fail("����ڹ����δ�����޷�����ȷ�ʩչ" HUN "��\n");

        if( me->query_skill("sword", 1) < 1000 )
                return notify_fail("�㽣����Ϊ���㣬������ʹ��" HUN "��\n");

        if( me->query_skill("sword-cognize", 1) < 500 )
                return notify_fail("�㽣���������δ����������ʹ��" HUN "��\n");

        if( me->query_skill("martial-cognize", 1) < 500 )
                return notify_fail("����ѧ�������δ����������ʹ��" HUN "��\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʩչ" HUN "��\n");

        if( me->query("jingli") <= 500 )
                return notify_fail("��ľ�������ʩչ" HUN "��\n");

        count = me->query_skill("sword-cognize", 1) + me->query_skill("martial-cognize", 1);
        count /= 500;

        msg = HIW "$N" HIW "��̬д�⣬���ḧŪ���е�" + weapon->name() + HIW "��ֻ��" + weapon->name() +
              HIW "�����ӹ�һ˿��Ӱ��΢΢���������ѽ����鶯�������������\n" NOR
              HIM "$N" HIM "������" + weapon->query("name") + HIM "�����̳��������������£�\n" NOR
              HIM "���п��ƻ�������ʵ�������磬�����������£�ȴ�Ǻ�" + weapon->name() + HIM "��Ϊһ�壬��и�ɻ����̺��ŷ�豹�����⾳��\n" NOR;

        message_vision(msg, me);

        damage = damage_power(me, "sword");
        ap = attack_power(me, "sword") +
             me->query_skill("dodge");

        ob = me->query_enemy();
        me->add_temp("apply/ap_power", 100);
        for (i = 0; i < sizeof(ob); i++)
        {
                dp = defense_power(ob[i], "parry") +
                     ob[i]->query_skill("dodge");

                if (ap / 2 + random(ap) > dp)
                {
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        ob[i]->set_status_xuruo(5);
                        ob[i]->set("neili", 0);
                        ob[i]->set("jiali", 0);
                        ob[i]->apply_condition("no_exert", 10);
                        ob[i]->query_condition("no_perform", 10);

                        msg = HIR "$n" HIR "���м�ȴ���޴��мܣ�����Ҳ�е��޴��ɶ㣬��ʱ��$N" HIR "һ��������\n"
                              HIR "�����ش���һ��׶�ĵĴ�ʹ��ȫ������ԴԴ��к��\n" NOR;
                        
                        p = (int)ob[i]->query("qi")*100/(int)ob[i]->query("max_qi");
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_vision(msg, me, ob[i]);
                } else
                {
                        ob[i]->start_busy(2);
                        msg = HIC "$n" HIC "�鼱֮�£��������ǣ�����һ�������ұܿ�$N" HIC "��һ�еĹ������亹ֱ�ܣ�\n" NOR;
                        message_vision(msg, me, ob[i]);
                }
        } ;
        me->add_temp("apply/ap_power", -100);
        me->start_busy(2);
        me->set_temp("dugu_jianhun", 1);
        me->add("neili", -200);
        me->add("jingli", -100);

        msg = HIY "$N" HIY "�ս�" + weapon->name() + HIY "����һָ, �е� : ����һ�� �� Ѫ������ �� \n"
              HIY "��ʱ" + weapon->name() + HIY "������һ����ɫ�Ľ��Σ������������������ ...\n" NOR;

        message_vision(msg, me);
        call_out("check_fight", 1, me, weapon, count);

        return 1;
}

void check_fight(object me, object weapon, int count)
{
        object *ob;
        int damage, ap, dp, p;
        string msg, limb;
        array limbs;
        int i;

        if( !objectp( me ) || !objectp(weapon) ) return;

        if( me->query_temp("dugu_jianhun") >= count
        ||      !me->is_fighting() )
        {
                call_out("remove_attack", 1, me, weapon);
                return;
        }

        me->add_temp("dugu_jianhun", 1);
        message_vision(HIR "\n�����������ĸ����ڿ��д���, �Կ����ޱȵ����龡����� ...\n" NOR, me);

        ob = me->query_enemy();
        ap = me->query_skill("sword-cognize", 1) +
             me->query_skill("martial-cognize", 1);
        damage = ap + weapon->query("weapon_prop/damage");
        damage *= 10;

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! objectp(ob)) continue;
                dp = ob[i]->query("parry", 1) +
                     ob[i]->query_skill("dodge", 1);

                if (dp / 3 + random(dp) < ap)
                {
                        limbs = ob[i]->query("limbs");
                        if (! arrayp(limbs))
                        {
                                limbs = ({ "����" });
                                ob[i]->set("limbs", limbs);
                        }
                        limb = limbs[random(sizeof(limbs))];
                        ob[i]->start_busy(1);
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        p = (int)ob[i]->query("qi")*100/(int)ob[i]->query("max_qi");
                        msg = COMBAT_D->damage_msg(damage, "����");
                        msg = replace_string(msg, "$l", limb);
                        msg = replace_string(msg, "$w", weapon->name());
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_vision(msg, me, ob[i]);
                }
        }

        call_out("check_fight", 1, me, weapon, count);
}

int remove_attack(object me, object weapon)
{
        if( !objectp( me ) ) return 1;
        if( !me->query_temp("dugu_jianhun")) return 1;
        
        me->delete_temp("dugu_jianhun");
        message_vision(HIW "һ�����֮��, �������Զ������������" + weapon->name() + HIW " ...\n" NOR, me);

        return 1;
}

