// Code of ShenZhou
// jinxian.c
// ���޽��ɻ�����
// sdong 7/6/99

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

void qi_suck(object me, object target);
void neili_suck(object me, object target);

int perform(object me, object target)
{
  object ob,weapon;
  string msg;
  int damage;
  int finger, skill, jiali, my_rate, your_rate;
        int sp, dp;
        int dmg;

        if( !target ) target = offensive_target(me);

        if( !target ) return notify_fail("��Ҫ��ȡ˭��������\n");

        if( !objectp(target) || target == me )
                return notify_fail("��Ҫ��ȡ˭��������\n");

        if ( me->query_temp("sucked") )
                return notify_fail("��ո���ȡ��������\n");

	if( me->query_temp("pifeng",1) && me->query("tianshan")!=1 )
                return notify_fail("������ʹ�������ȷ����޷����ý��ɣ�\n");

        if( !me->is_fighting() || !target->is_fighting() || !living(target) )
                return notify_fail("�������ս���в�����ȡ�Է���������\n");

  	if( me->query_skill_mapped("force") != "huagong-dafa" )
         	return notify_fail("�����õĲ��ǻ����󷨣�������ȡ�Է���������\n");

        if( !objectp(weapon = me->query_temp("weapon")) )
		return notify_fail("�����Ҳ�����ȷ���\n");

	if( weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õı������ԣ�\n");

        if( (int)me->query_skill("huagong-dafa",1) < 120 )
                return notify_fail("��Ļ����󷨹���������������ȡ�Է���������\n");

        if( (int)me->query("neili") < 50 )
                return notify_fail("�����������������ʹ����ɽ�ȷ���\n");

        if( (int)me->query("neili") >= (int)me->query("max_neili") * 5 )
                return notify_fail("����ȡ����������ȫ�����޷�����ȡ������\n");

  	if( (skill = (int)me->query_skill("tianshan-zhang", 1)) < 120 )
         	return notify_fail("�����ɽ�ȷ�������죬����ʹ���޽��ɻ����ȡ�\n");

        if (!living(target))
                return notify_fail("�Է��Ѿ�����ս���ˣ����޷���ȡ������\n");

        msg = HIM "\n$NͻȻ�������㵸�����������дʣ��е����������񹦣��������Ž��ޱȡ���\n";
        msg += HIM "���Ž�������������������ͣ������·������������޽����裬�����Ŀ���ࡣ\n\n"NOR;

        message_vision(msg, me, target );
        me->start_busy(1);

        if( (int)target->query("neili") < (int)target->query("max_neili") / 10
         || (int)target->query("jingli") < (int)target->query("max_jingli") / 5 )
         {
                if( random(4) ) call_out("qi_suck", 1 + random(3), me, target );
                else return notify_fail( target->name() + "�Ѿ�������ɢ�����Ѿ��޷�����������ȡ�κ������ˣ�\n");
                return 1;
         }

         if(random(3)) call_out("neili_suck", 1 + random(5), me, target );
         else  call_out("qi_suck", 1 + random(5), me, target );

  return 1;
}

void neili_suck(object me, object target)
{
  object ob;
  string msg;
  int damage;
  int finger, skill, jiali, my_rate, your_rate;
        int sp, dp;
        int dmg;

        if( !objectp(me) )  return;
        if( !target ) target = offensive_target(me);
        if( !target ) return;
        if( !objectp(target) ) return;
        if( !environment(target) || !environment(target) || environment(target) != environment(me) )
        return;

        if (!me->is_fighting(target)) return; 
        message_vision(
                HIW "$Nһ����ͻȻ��òҰף�������֮�У�����ֱ�����͵ض�׼$n�����д�Ѩ������ȥ��\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp = me->query_skill("force") + me->query_skill("dodge") + me->query("kar")*5;
        dp = target->query_skill("force") + target->query_skill("dodge") + target->query("kar")*5;
                       sp += atoi(count_div(me->query("combat_exp"), 1000)); 
                       dp += atoi(count_div(target->query("combat_exp"), 1000)); 

        me->set_temp("sucked", 1);

        if( random(sp+dp) > dp )
        {
                message_vision(
                        HIR "$N�پ�����΢ʹ����ͬ��������˸�С�ף�ȫ��������ˮ����ѭ�׷�й������\n\n" NOR,
                        target );

                tell_object(me, HIG "�����" + target->name() + "������������ԴԴ���������˽�����\n" NOR);

                target->add("neili", -1*(int)me->query_skill("force") );

                me->add("neili", ((int)me->query_skill("force")));
                if( count_ge(target->query("combat_exp"), count_div(me->query("combat_exp"), 2)) ) {
                        me->add("potential", 1);
                        me->add("combat_exp", 1);
                }

                if (! me->is_busy())
                me->start_busy(1+random(3));
                if (! target->is_busy())
                target->start_busy(1+random(3));
                me->add("neili", -(int)me->query_skill("force")/6 );
                me->add("jingli", -5);


                dmg = random( me->query_skill("force") ) + me->query("neili")/10;
                if( dmg > 3000) dmg=3000;
                if( dmg < 700) dmg=700;
                target->receive_damage("qi", dmg/2,me );
                target->receive_wound("qi", random(dmg/2), me);
                target->add("jingli", -random(dmg)/4);
                COMBAT_D->report_status(target);
                call_out("del_sucked", 1+random(2), me);
        }
        else
        {
                if( target->query("race") != "����" )
                        message_vision(HIY "����$p������$P����ͼ�������ˡ�\n" NOR, me, target);
                else
                        message_vision(HIY "����$p������$P����ͼ����Ц������������۷�Ҳƭ�����ң�����˵��ٿ�������ˡ�\n" NOR, me, target);

                message_vision(RED "���$N������æ���ң��պ��˲���������\n" NOR, me );
                me->add("jingli", -5);
                me->add("neili", -random(me->query_skill("force")) );
                if (! me->is_busy())
                me->start_busy(2 + random(2) );
                call_out("del_sucked", 1+random(3), me);
        }

}

void qi_suck(object me, object target)
{
  object ob;
  string msg;
  int damage;
  int finger, skill, jiali, my_rate, your_rate;
  int sp, dp;
  int dmg;

        if( !objectp(me) )  return;
        if( !target ) target = offensive_target(me);
        if( !target ) return;
        if( !objectp(target) ) return;

        if( !environment(target) || !environment(me) || environment(target) != environment(me) )
        return;
        if (!me->is_fighting(target)) return; 

        message_vision(
                HIB "$NͻȻ�����һЦ��˫��һ�������֮�У�Ĵָ��׼$n�����İ��˹�����\n\n" NOR,
                me, target );

        if( !target->is_killing(me) ) target->kill_ob(me);

        sp = me->query_skill("force") + me->query_skill("dodge") + me->query("kar");
        dp = target->query_skill("force") + target->query_skill("dodge") + target->query("kar");
                  sp += atoi(count_div(me->query("combat_exp"), 1000));
                  dp += atoi(count_div(target->query("combat_exp"), 1000));

        me->set_temp("sucked", 1);

        if( random(sp+dp) > dp )
        {
                tell_object(target, HIR "��ͻȻ����ȫ�����������Ʊ�ӿ��������֫��������Ҳʹ����������\n" NOR);
                tell_object(me, HIG "�����" + target->name() + "������������ԴԴ���������˽�����\n" NOR);
                message_vision(
                        HIR "$N����ȫ�����������Ʊ�ӿ��������֫��������Ҳʹ����������\n\n" NOR,
                        target );

                me->add("qi", (int)me->query_skill("force") );

                if( count_ge(target->query("combat_exp"), count_div(me->query("combat_exp"), 2)) )
                        me->add("combat_exp",1);

                if (! me->is_busy())
                me->start_busy(random(2));
                if (! target->is_busy())
                target->start_busy(random(2));
                me->add("neili", -(int)me->query_skill("force")/6);
                me->add("jingli", -5);

                dmg = random( me->query_skill("force") ) + me->query("neili")/10;
                if( dmg > 3000) dmg=3000;
                if( dmg <700) dmg=700;
                target->receive_damage("qi", dmg/2, me );
                target->receive_wound("qi", random(dmg/2), me);
                COMBAT_D->report_status(target);

                call_out("del_sucked", 1, me);
        }
        else
        {
                if( target->query("race") != "����" )
                        message_vision(HIY "����$p������$P����ͼ���ߵ�һ�����˿�ȥ��\n" NOR, me, target);
                else if( target->query("family/family_name") != "������")
                        message_vision(HIY "����$p������$P����ͼ���ߵ�һ����������������ͽ��ͽ��Ҳ����ˮƽ������ƮȻ���˿�ȥ��\n" NOR, me, target);
                else
                        message_vision(HIY "����$p������$P����ͼ���ߵ�һ����������ƭ���˻��У�ƭ�ң�����ƮȻ���˿�ȥ��\n" NOR, me, target);

                message_vision(RED "���$N������æ���ң��׷Ѿ���\n" NOR, me );

                me->add("jingli", -5);
                me->add("neili", -random(me->query_skill("force")) );
                if (! me->is_busy()) me->start_busy(2 + random(2));
                call_out("del_sucked", 1+random(2), me);
        }

}

void del_sucked(object me)
{
        if (!me) return;
        if ( me->query_temp("sucked"))
        me->delete_temp("sucked");
}
