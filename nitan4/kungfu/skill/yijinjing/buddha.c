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
                return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ�÷�����ա�\n");

        if( !me->query("reborn/times") )        
                return notify_fail("����δת���������޷�ʹ�÷�����գ�\n");
                
        if( target != me )
                return notify_fail("��ֻ�����׽������������ա�\n");

        if( (skill = me->query_skill("yijinjing", 1)) < 1000 )
                return notify_fail("����׽��û��ѧ�ɣ��޷�ʹ�÷�����գ�\n");

        if( me->query_skill("jingang-buhuaiti", 1) < 1000 )
                return notify_fail("��Ľ�ղ���������Ϊ�������޷�ʹ�÷�����գ�\n");

        if( me->query_skill("buddhism", 1) < 1000 )
                return notify_fail("��������ķ��Ĳ��򻹲������޷�ʹ�÷�����գ�\n");
        
        if( me->query_skill_mapped("parry") != "jingang-buhuaiti" )
                return notify_fail("����뼤����ղ����壬����ʹ�÷�����գ�\n");

        if( (int)me->query_temp("buddha") )
                return notify_fail("���Ѿ��������������ˡ�\n");

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("�������������\n");

        if( (int)me->query("neili") < 5000 )
                return notify_fail("�������������\n");

        me->add("neili", -1000);
        me->receive_damage("qi", 0);

        message_combatd(HIY "ֻ��$N" HIY "�ߺ���ţ����������գ����Ǽ�ȫ������ƽ�һ�㣬�����Ӳӽ�⡣\n" NOR, me);

        me->set_temp("apply/avoid_busy_effect", 1);
        me->set_temp("apply/avoid_xuruo_effect", 1);
        me->set_temp("apply/avoid_damage_effect", 1);
        me->set_temp("buddha", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), skill/10);
        
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me)
{
        if( me->query_temp("buddha") ) {
                me->delete_temp("apply/avoid_busy_effect");
                me->delete_temp("apply/avoid_xuruo_effect");
                me->delete_temp("apply/avoid_damage_effect");
                me->delete_temp("buddha");
                tell_object(me, "��������ϣ��������ջص�������ʧ��\n");
        }
}

