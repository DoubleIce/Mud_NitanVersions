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
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "鱼鳞阵" HIC "」的奥秘。\n" NOR); 
        }
                
        if (lvl > 140  
        &&  ! me->query("array/fengshi")) 
        { 
                me->set("array/fengshi", 1);
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "锋矢阵" HIC "」的奥秘。\n" NOR); 
        }  

        if (lvl > 180  
        &&  ! me->query("array/heyi")) 
        { 
                me->set("array/heyi", 1);
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "鹤翼阵" HIC "」的奥秘。\n" NOR); 
        }  

        if (lvl > 220  
        &&  ! me->query("array/yanyue")) 
        { 
                me->set("array/yanyue", 1);
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "偃月阵" HIC "」的奥秘。\n" NOR); 
        }                      

        if (lvl > 260  
        &&  ! me->query("array/fangyuan")) 
        { 
                me->set("array/fangyuan", 1);
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "方圆阵" HIC "」的奥秘。\n" NOR); 
        }

        if (lvl > 300  
        &&  ! me->query("array/yanxing")) 
        { 
                me->set("array/yanxing", 1);
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "雁行阵" HIC "」的奥秘。\n" NOR); 
        }

        if (lvl > 340  
        &&  ! me->query("array/changshe")) 
        { 
                me->set("array/changshe", 1);
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "长蛇阵" HIC "」的奥秘。\n" NOR); 
        }
        
        if (lvl > 380  
        &&  ! me->query("array/yunlong")) 
        { 
                me->set("array/yunlong", 1);
                tell_object(me, HIC "你从通晓了「" HIW "阵法" HIC "」中「" HIW "云龙阵" HIC "」的奥秘。\n" NOR); 
        }
} 

