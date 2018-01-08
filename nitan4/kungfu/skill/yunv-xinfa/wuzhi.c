// Written by Lonely@IsMUD.net
// �������� ת������
// wuzhi.c

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int skill);

int exert(object me, object target)
{
        int skill;
        
        if( me->query("family/family_name") != "��Ĺ��" )
                return notify_fail("�㲻�ǹ�Ĺ���ӣ��޷�ʹ���������͡�\n");

        if( !me->query("reborn/times") )        
                return notify_fail("����δת���������޷�ʹ���������ͣ�\n");
                
        if( (skill = me->query_skill("yunv-xinfa", 1)) < 1000 )
                return notify_fail("�����Ů�ķ����������죬�޷�ʹ���������ͣ�\n");
                        
        if( (int)me->query_temp("wuzhi") )
                return notify_fail("���Ѿ����������������ˡ�\n");

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("�������������\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("�������������\n");

        me->add("neili", -1000);
        me->receive_damage("qi", 0);
        
        skill += me->query_skill("martial-cognize", 1);
        skill /= 300;
        
        message_combatd(HIY "ֻ��$N" HIY "�ľ���ˮ����Ϣ����ͣ�ͣ�������ѧ����ˮ�����������\n" NOR, me);
        
        me->add_temp("apply/ap_power", skill);
        me->add_temp("apply/add_xuruo", skill);
        me->add_temp("apply/add_busy", skill/2);
        me->add_temp("apply/double_damage", skill);
        me->set_temp("niepan", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int skill)
{
        if( me->query_temp("niepan") ) {
                me->add_temp("apply/ap_power", -skill);
                me->add_temp("apply/add_xuruo", -skill);
                me->add_temp("apply/add_busy", -skill/2);
                me->add_temp("apply/double_damage", -skill);
                me->delete_temp("wuzhi");
                tell_object(me, "�����Ů�ķ�������ϣ��������ջص��\n");
        }
}

