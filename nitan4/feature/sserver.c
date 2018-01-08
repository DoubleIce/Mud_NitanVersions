// sserver.c

// This function selects a random target for offensive spells/functions.
object offensive_target(object me)
{
        me->clean_up_enemy();
        return me->select_opponent();
}

int attack_power(object me, string skill)
{
        return SKILLS_D->attack_power(me, skill);
}

int defense_power(object target, string skill)
{
        return SKILLS_D->defense_power(target, skill);
}

int damage_power(object me, string skill)
{    
        return SKILLS_D->damage_power(me, skill);
}                        

