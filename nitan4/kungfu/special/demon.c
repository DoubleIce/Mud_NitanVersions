// This program is a part of NITAN MudLIB
// demon.c ��ħ����
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "��ħ����" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int n;

        if (me->query_temp("special_skill/demon"))
                return notify_fail("����ħ����֮������ʩչ���ˡ�\n");

        message_vision(HIG "$N" HIG "ʩչ����ħ����֮����ɲ�Ǽ�ȫ�������ŷ�������������֣������ޱȣ�\n" NOR, me);

        n = me->query_skill("force");
        if (n < 100) n = 100;

        me->add_temp("apply/armor", n * 3);         
        me->add_temp("apply/reduce_damage", 30);
        me->set_temp("special_skill/demon", 1); 
 
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, n * 3 :), n/10);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("special_skill/demon"))
        {
                me->add_temp("apply/armor", -amount);
                me->add_temp("apply/reduce_damage", -30);
                me->delete_temp("special_skill/demon");
                tell_object(me, "����ħ����֮����ʩչ��ϡ�\n");
        }
        
}


