// This program is a part of NITAN MudLIB

#include <ansi.h>

#define LING "��" MAG "ŲתǬ��" NOR "��"

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        int level;
        
        if( me->query("family/family_name") != "����" )
                return notify_fail("�㲻�����̵��ӣ��޷�ʩչ" LING "��\n" NOR);

        if( !me->query("reborn/times") )        
                return notify_fail("����δת���������޷�ʩչ" LING "��\n" NOR);

        if( (level = me->query_skill("qiankun-danuoyi", 1)) < 1000 )
                return notify_fail("���Ǭ����Ų�ƻ���������������ʩչ" LING "��\n" NOR);

        if( (int)me->query("jingli") < 2000 )
                return notify_fail("�������������㣬����ʩչ" LING "��\n" NOR);

        if( (int)me->query("neili") < 5000 )
                return notify_fail("��������������������ʩչ" LING "��\n" NOR);
                
        if (me->query_temp("nuozhuan"))
                return notify_fail("���Ѿ�����" LING "��\n" NOR);

        me->add("neili", -1000);
        me->receive_damage("qi", 0);
        me->set_temp("nuozhuan", 1);
        msg = MAG "\n$N" MAG "����������Ĭ��" LING + "�ķ�������ж�����еķ����Ѵ﷢����Ȼ֮����\n" NOR;

        message_combatd(msg, me);
        
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), level/80);
        
        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)me->query_temp("nuozhuan"))
        {
                me->delete_temp("nuozhuan");
                tell_object(me, "��ġ�ŲתǬ�����˹���ϣ��������ջص��\n");
        }
}

