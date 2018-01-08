// This program is a part of NITAN MudLIB
// immortal.c 不死金身
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return YEL "不死金身" NOR; }

int perform(object me, string skill)
{
        if( !me->query("reborn/times") )        
                return notify_fail("你尚未转世重生，无法使用此技能！\n");
            
        if( time() - me->query("special/immortal") < 3600 )        
                return notify_fail("你要过些时候才能再用此技能！\n");

        message_vision(YEL "$N" YEL "脸色一沉，全身散发出一阵金光，"
                       YEL "便如罗汉转世一般。\n" NOR, me);

        me->set_temp("special_skill/immortal", 1);
        me->set("special/immortal", time());
        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);
        return 1;
}

void remove_effect(object me)
{
        me->delete_temp("special_skill/immortal");
        tell_object(me, "你施展完不死金身，松了一口气。\n");
}

