//Code by Scatter
//modified by Slow
//V. 1.5
// �޸Ĵ���
/*
������ǧ��һ��
      ָ�perform qianjun
      ����������������Ч�ȼ�300��
            ��Ů�ľ���Ч�ȼ�300��
            �������3000
      �ص㣺����pfm,��������
*/

#include <ansi.h>

inherit F_SSERVER;


int perform(object me, object target)
{
        object weapon;
        int skill, skill1;
        int myskill;
        int damageone;
        int damagesub;
        int damage;
        string msg;
        mixed ap,dp;
        int status_flag=0;

        if (userp(me) && ! me->query("can_perform/xuantie-jian/qianjun"))
                return notify_fail("��δ�ø���ָ�㣬��֪�����ʩչǧ��һ����\n");
                
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("ǧ��һ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");


        if( !objectp(weapon = me->query_temp("weapon") ) )
                return notify_fail("��δ������������ʹ��ǧ��һ����\n");

        if( me->query_skill("force") < 300 )
                return notify_fail("����ڹ����δ�����޷�ʩչǧ��һ����\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("��Ľ������δ�����޷�ʩչǧ��һ����\n");

        if( me->query("max_neili") <= 3000 )
                return notify_fail("�����������ʩչǧ��һ����\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�����������ʩչǧ��һ����\n");

        if( me->query("jingli") <= 1000 )
                return notify_fail("��ľ�������ʩչǧ��һ����\n");


           msg =HIW"\n\n$N������б�����ֳ��������"+weapon->query("name")+"��˳��һ�С�ǧ��һ����!\n"NOR;
         ap=count_add(count_div(me->query("combat_exp"), 2000), count_add(me->query_skill("force"), me->query_skill("sword")));
         ap=atoi(ap);
         dp=count_add(count_div(target->query("combat_exp"), 1000), target->query_skill("dodge"));
         dp=atoi(dp);
               damage=me->query_skill("force")+me->query_skill("sword"); 
                   damage *=2; 
            if ( ap/3 + random(ap*5/3) > dp/3 + random(dp*4/3)) 
        {
msg+=HIB"$N����ʹ�ü���,ͦ���ͳ���$n���������ȴ���벻�����ƾ���������ң��ۼ����ܲ�����
ֻ�����һ�����죬��ʱ������������������ǿ�ô�վ������ʱ�����ֽ��\n"NOR;
           target->receive_damage("qi", damage,  me);
          target->receive_wound("qi", random(damage/2)+damage/2, me);
           me->start_busy(1+random(3));
           status_flag=1;
        }


        else if ( me->query("int") > random(target->query("int")*2) )
        {
msg+=
HIB"$Nһ�����������ֳ���˳�Ʒ�ȥ��$n��̼�ֻ�������������Ʒ�ת�ˣ�վ�ڵ��أ��Ȳ���������
Ҳ�����ƶ��벽�����罩��һ�㡣\n"NOR;
             if (! target->is_busy())
             target->start_busy(3+random(4));
         me->start_busy(2+random(2));
          status_flag=1;
        }
          else if (ap/3 >random(dp*2))
          {
msg+=
HIC"$Nֻ���Է���ײ�����ľ������಻����Խ��Խǿ,�˳������������һ����\n" NOR;
          me->add("neili", -300);
          target->add("neili", -300);
          me->start_busy(1+random(2));
             if (! target->is_busy())
          target->start_busy(1+random(2));
            status_flag=1;
          }
           else
         {
msg += HIG"$n��շ�Ծ�����μ�����ʹ�������Ṧ��������������һ�࣬$N�ķ�����������ա�\n"NOR;
             me->start_busy(2+random(2));
      }
          me->add("neili", -200);

  message_vision(msg+"\n", me, target);
         if (status_flag==1) COMBAT_D->report_status(target);
  return 1;


}