// This is player's own perform (Write by Lonely@nt2)
// Create by 慕容含嫣(Lubabyer) at Fri May 22 18:34:08 2009
// 璀璨流云(cuican)

#include <ansi.h>
#include <combat.h>

#define PFM "「" HIW "璀璨流云" NOR "」"

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
                return notify_fail("你还没有受到高手指点，还不会运用" PFM "。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(PFM "只能对战斗中的对手使用。\n");

        if (member_array("sword", weapon_sk) != -1)
        {
                attack = WEAPON_ATTACK;
                if (! objectp(weapon = me->query_temp("weapon"))
                   || (string)weapon->query("skill_type") != "sword")
                        return notify_fail("你所使用的武器不对，难以施展" PFM "。\n");
        } else
        {
                attack = UNARMED_ATTACK;
                if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                        return notify_fail(PFM "只能空手使用。\n");             
        }
        
        if ((int)me->query_skill("lubabyer-sword", 1) < 400)
                return notify_fail("你" + to_chinese("lubabyer-sword") + "不够娴熟，难以施展" PFM "。\n");

        if (member_array("sword", weapon_sk) == -1)
        {
                if (me->query_skill_prepared("sword") != "lubabyer-sword")
                        return notify_fail("你没有准备" + to_chinese("lubabyer-sword") + "，难以施展" PFM "。\n");
        }
        
        if (me->query("neili") < 500)
                return notify_fail("你现在的真气不够，难以施展" PFM "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$HIM$$N双手举过平顶，武器竟围绕在$N周身飞速狂舞！$N默运真气，数股暗红劲气自“太渊穴”游走于“中极、气海”，反其道而行逆上任脉，终聚于双臂之上！顷刻间飞沙走石，天地骤变，恰似寄蜉蝣与天地，渺沧海之一粟。;突然间，只听一声清啸！;但见$N人与武器已然合为一体，似剑非剑、似云非云，“澎湃千顷巨浪，翻卷万里飞云。”眨眼间$N已提剑风驰电掣般从半空中呼啸而至！那剑光耀如流星，那招力劲如奔雷！" + "\n" + NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
         
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                msg += COMBAT_D->do_damage(me, target, attack, damage, 80, HIM "$n见状大惊，想要闪避，却已避无可避！身形一慢，顿时被$N的万道剑光笼罩其中，慢慢的倒下了。" + "\n" NOR);
                me->add("neili", -200);
             
                /*
                if (! target->is_busy())
                        target->start_busy(2);
                */
        } else
        {
                msg += NOR + CYN "$p见势不妙，抽身急退，险险避过$P的这记杀招，尘土飞扬中，地上裂开了一道大口子！" + "\n" NOR;
                me->add("neili", -100);
        }
                
        message_sort(msg, me, target);
    
        msg = HIW "$N" HIW "余势未尽，招式陡然变得凌厉无比，一转念间已然攻出数招。\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 20;
                msg += HIR "$n" HIR "见$P" HIR "来势迅猛之极，一时不知该如"
                       "何作出抵挡，竟呆立当场。\n" NOR;
        } else
        {
                msg += HIY "$n" HIY "见$p" HIY "来势迅猛之极，甚难防备，连"
                       "忙振作精神，小心抵挡。\n" NOR;
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

