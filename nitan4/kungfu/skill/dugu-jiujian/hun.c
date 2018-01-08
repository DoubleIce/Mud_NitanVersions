// This program is a part of NITAN MudLIB
// hun.c 剑魂

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define HUN     "「" HIM "剑魂" NOR "」"

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
                return notify_fail("你尚未转世重生，无法施展" HUN "。\n");

        if( me->query("family/family_name") != "华山派" )
                return notify_fail("你不是华山派弟子，无法施展" HUN "。\n");
        /*
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(HUN "只能对战斗中的对手使用。\n");
        */

        if( !me->is_fighting() )
                return notify_fail(HUN "只能对战斗中的对手使用。\n");

        if( me->query_temp("dugu_jianhun") )
                return notify_fail("你已在使用" HUN "了！\n");

        weapon = me->query_temp("weapon");
        if( !objectp(weapon) || weapon->query("skill_type") != "sword" )
                return notify_fail("你手中无剑，如何能够施展" HUN "？\n");

        if( (int)me->query_skill("dugu-jiujian", 1) < 1000 )
                return notify_fail("你的独孤九剑不够娴熟，难以施展" HUN "。\n");

        if( me->query_skill("force") < 1200 )
                return notify_fail("你的内功火候未到，无法配合杖法施展" HUN "！\n");

        if( me->query_skill("sword", 1) < 1000 )
                return notify_fail("你剑法修为不足，还不会使用" HUN "！\n");

        if( me->query_skill("sword-cognize", 1) < 500 )
                return notify_fail("你剑道修养火候未到，还不会使用" HUN "！\n");

        if( me->query_skill("martial-cognize", 1) < 500 )
                return notify_fail("你武学修养火候未到，还不会使用" HUN "！\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("你的内力不够施展" HUN "！\n");

        if( me->query("jingli") <= 500 )
                return notify_fail("你的精力不够施展" HUN "！\n");

        count = me->query_skill("sword-cognize", 1) + me->query_skill("martial-cognize", 1);
        count /= 500;

        msg = HIW "$N" HIW "神态写意，温柔抚弄手中的" + weapon->name() + HIW "，只见" + weapon->name() +
              HIW "表面掠过一丝光影，微微颤动，整把剑竟灵动起来、有若生物。\n" NOR
              HIM "$N" HIM "将手中" + weapon->query("name") + HIM "缓缓刺出，剑招随意无章！\n" NOR
              HIM "这招看似缓慢，其实疾如闪电，看似随意无章，却是和" + weapon->name() + HIM "融为一体，无懈可击，蕴涵着返璞归真的意境。\n" NOR;

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

                        msg = HIR "$n" HIR "想招架却感无从招架，想躲避也感到无处可躲，登时被$N" HIR "一剑划过，\n"
                              HIR "遭受重创，一阵锥心的刺痛，全身真气源源而泻！\n" NOR;
                        
                        p = (int)ob[i]->query("qi")*100/(int)ob[i]->query("max_qi");
                        msg += "( $n"+COMBAT_D->eff_status_msg(p)+" )\n";
                        message_vision(msg, me, ob[i]);
                } else
                {
                        ob[i]->start_busy(2);
                        msg = HIC "$n" HIC "情急之下，不及考虑，倒地一滚，侥幸避开$N" HIC "这一招的攻击，冷汗直淋！\n" NOR;
                        message_vision(msg, me, ob[i]);
                }
        } ;
        me->add_temp("apply/ap_power", -100);
        me->start_busy(2);
        me->set_temp("dugu_jianhun", 1);
        me->add("neili", -200);
        me->add("jingli", -100);

        msg = HIY "$N" HIY "握紧" + weapon->name() + HIY "向天一指, 叫道 : 剑魂一出 ～ 血光漫天 ～ \n"
              HIY "顿时" + weapon->name() + HIY "剑身化出一道红色的剑形，在天空中恣意飞旋穿梭 ...\n" NOR;

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
        message_vision(HIR "\n剑魂以闪电般的高速在空中穿梭, 以狂乱无比的热情尽情狂舞 ...\n" NOR, me);

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
                                limbs = ({ "身体" });
                                ob[i]->set("limbs", limbs);
                        }
                        limb = limbs[random(sizeof(limbs))];
                        ob[i]->start_busy(1);
                        ob[i]->receive_damage("qi", damage, me);
                        ob[i]->receive_wound("qi", damage / 2, me);
                        p = (int)ob[i]->query("qi")*100/(int)ob[i]->query("max_qi");
                        msg = COMBAT_D->damage_msg(damage, "割伤");
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
        message_vision(HIW "一阵狂舞之后, 剑魂又自动飞入你的手中" + weapon->name() + HIW " ...\n" NOR, me);

        return 1;
}

