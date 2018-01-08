// Written by Lonely@IsMUD.net
// ������� ת������
// buddha.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;
        
        if( me->query("family/family_name") != "������" )
                return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ�÷�����͡�\n");

        if( !me->query("reborn/times") )        
                return notify_fail("����δת���������޷�ʹ�÷�����ͣ�\n");
                
        if( skill = me->query_skill("linji-zhuang", 1) < 1000 )
                return notify_fail("����ټ�ʮ��ׯ��Ϊ���������޷�ʹ�÷�����ͣ�\n");

        if( (int)me->query_temp("niepan") )
                return notify_fail("���Ѿ��������������ˡ�\n");

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("�������������\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("�������������\n");

        if( target != me ) {
                if( !target->query_xuruo() )
                        return notify_fail(target->name() + "��û�д�������״̬��\n");
                
                me->add("neili", -1000);
                me->receive_damage("qi", 0);
                target->clear_xuruo();
                message_combatd(HIY "ֻ��$N" HIY "��Ϣ������˫������"+target->name()+"���󣬽������д�С��ׯ��ֻ��"+target->name()+"ȫ����â���֡�\n" NOR, me);
                tell_object(target, HIG"\n��о�����״̬�����ĸ�ԭ�ˡ�����\n\n" NOR); 
                tell_object(me, HIG"\n����"+target->name()+"����������״̬������\n\n" NOR); 
                if( me->is_fighting() ) me->start_busy(3);
                return 1;
        }

        me->add("neili", -1000);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "��ɫ������̾���������ġ�ת˲���ֻ�����ϲ����֮״��\n����$N" HIY "�ſ�����һ�ž���է�ּ��ţ�$N"HIY"����ϰȴ��ȫȻ��ͬ��\n" NOR, me);

        me->set_temp("apply/avoid_busy_effect", 1);
        me->set_temp("apply/avoid_xuruo_effect", 1);
        me->add_temp("apply/reduce_damage", 30);
        me->set_temp("niepan", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);
        
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( me->query_temp("niepan") ) {
                me->delete_temp("apply/avoid_busy_effect");
                me->delete_temp("apply/avoid_xuruo_effect");
                me->add_temp("apply/reduce_damage", -30);
                me->delete_temp("niepan");
                tell_object(me, "����ټ�ׯ������ϣ��������ջص��\n");
        }
}

