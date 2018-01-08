// This program is a part of NITAN MudLIB

#include <ansi.h>

#define LING "��" MAG "������" NOR "��"

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        
        if( me->query("family/family_name") != "��ң��" )
                return notify_fail("�㲻����ң�ɵ��ӣ��޷�ʩչ" LING "��\n" NOR);

        if( !me->query("reborn/times") )        
                return notify_fail("����δת���������޷�ʩչ" LING "��\n" NOR);

        if( me->query_skill("lingbo-weibu", 1) < 1000 )
                return notify_fail("����貨΢������������������ʩչ" LING "��\n" NOR);

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("�������������㣬����ʩչ" LING "��\n" NOR);

        if( (int)me->query("neili") < 5000 )
                return notify_fail("��������������������ʩչ" LING "��\n" NOR);
                
        if (me->query_temp("immortal"))
                return notify_fail("���Ѿ�����" LING "��\n" NOR);

        me->add("neili", -1000);
        me->receive_damage("qi", 0);
        me->set_temp("immortal", 1);

        msg = MAG "\n$N" MAG "����������ʩչ" LING + "��������Σ���⽻������ѷ֣��������Կ������ڡ�\n" NOR;

        message_combatd(msg, me);
        
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 15);
        
        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)me->query_temp("immortal"))
        {
                me->delete_temp("immortal");
                tell_object(me, "��ġ������ϡ��˹���ϣ��������ջص��\n");
        }
}

