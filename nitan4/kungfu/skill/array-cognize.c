#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
    return 1;
}

void skill_improved(object me) 
{ 
        int lvl;
                
        lvl = me->query_skill("array-cognize", 1); 
        
        if (lvl > 100  
        &&  ! me->query("array/yulin")) 
        { 
                me->set("array/yulin", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "������" HIC "���İ��ء�\n" NOR); 
        }
                
        if (lvl > 140  
        &&  ! me->query("array/fengshi")) 
        { 
                me->set("array/fengshi", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "��ʸ��" HIC "���İ��ء�\n" NOR); 
        }  

        if (lvl > 180  
        &&  ! me->query("array/heyi")) 
        { 
                me->set("array/heyi", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "������" HIC "���İ��ء�\n" NOR); 
        }  

        if (lvl > 220  
        &&  ! me->query("array/yanyue")) 
        { 
                me->set("array/yanyue", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "������" HIC "���İ��ء�\n" NOR); 
        }                      

        if (lvl > 260  
        &&  ! me->query("array/fangyuan")) 
        { 
                me->set("array/fangyuan", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "��Բ��" HIC "���İ��ء�\n" NOR); 
        }

        if (lvl > 300  
        &&  ! me->query("array/yanxing")) 
        { 
                me->set("array/yanxing", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "������" HIC "���İ��ء�\n" NOR); 
        }

        if (lvl > 340  
        &&  ! me->query("array/changshe")) 
        { 
                me->set("array/changshe", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "������" HIC "���İ��ء�\n" NOR); 
        }
        
        if (lvl > 380  
        &&  ! me->query("array/yunlong")) 
        { 
                me->set("array/yunlong", 1);
                tell_object(me, HIC "���ͨ���ˡ�" HIW "��" HIC "���С�" HIW "������" HIC "���İ��ء�\n" NOR); 
        }
} 

