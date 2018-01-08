// six-fingers.c ������
// by Lonely

#include <ansi.h>
inherit SKILL;

string main_skill() { return "yinyang-shiertian"; }

mapping *action = ({
        ([ "name":   "���̽�",
           "action": "$N����������˫��Ĵָͬʱ����������������죬��" HIW "���̽�" NOR "������ʯ���쾪���������֮�ƣ�ָ\n"
                     "��$n��$l",
           "force" : 460,
           "attack": 140,
           "dodge" : 90,
           "parry" : 90,
           "damage": 200,
           "damage_type":  "����"
        ]),
        ([ "name":   "������",
           "action": "$Nʳָ����������԰ת����" HIR "������" NOR "��һ����һ���Ĵ̳�������Ѹ�٣����ɻ��ã������ݺᣬ����\n"
                     "�ܹ����彣������·",
           "force" : 440,
           "attack": 145,
           "dodge" : 110,
           "parry" : 95,
           "damage": 225,
           "damage_type":  "����"
        ]),
        ([ "name":   "�г彣",
           "action": "$N������ָһ������" HIY "�г彣" NOR "����ǰ�̳��������ĵ�����Ȼ���죬���ν���ֱָ$n��$l",
           "force" : 560,
           "attack": 135,
           "dodge" : 10,
           "parry" : 70,
           "damage": 275,
           "damage_type":  "����"
        ]),
        ([ "name":   "�س彣",
           "action": "$N��������ָ�������" HIY "�س彣" NOR "����·׾�͹��ӣ�һ���ۻ��ޱȵ������ĵ�����������ɽ����һ��\n"
                     "$nӿȥ",
           "force" : 530,
           "attack": 140,
           "dodge" : 100,
           "parry" : 95,
           "damage": 225,
           "damage_type":  "����"
        ]),
        ([ "name":   "����",
           "action": "$N����Сָһ�죬һ���������ٳ�Ѩ�м����������" HIW "����" NOR "��������磬ָ��$n��$l",
           "force" : 500,
           "attack": 130,
           "dodge" : 95,                            
           "parry" : 92,
           "damage": 215,
           "damage_type":  "����"
        ]),
        ([ "name":   "�ٳ彣",
           "action": "$N���ַ�ָ��Сָ������������ٳ�Ѩ������������" HIW "�ٳ彣" NOR "��������䣬�������벻���ķ����\n"
                     "��$n��$l",
           "force" : 430,
           "attack": 140,
           "dodge" : 90,
           "parry" : 95,
           "damage": 175,
           "damage_type":  "����"
        ]),
});

mapping sub_skills = ([ 
        "shaoshang-sword"  : 120,
        "shangyang-sword"  : 120,
        "zhongchong-sword" : 120,
        "guanchong-sword"  : 120,
        "shaoze-sword"     : 120,
        "shaochong-sword"  : 120,
]); 

int get_ready(object me) 
{ 
        return 1; 
} 

int get_finish(object me) 
{ 
        if (! me->query("family/family_name") || 
            me->query("family/family_name") != "���ϻ���") 
        { 
                tell_object(me, "���о���һ�����ֻ���Ĳ��Ƕ��ϻ���ĸ����޷��������а���\n"); 
                return 0; 
        }

        if (me->query("int") < 32 || me->query_int() < 44) 
        { 
                tell_object(me, "��������ϣ�ֻ�����ֽ�������ǣ����������������ԣ���"
                                "�������һ��\n");
                return 0; 
        } 

        if (me->query("con") < 26 || me->query_con() < 39) 
        { 
                tell_object(me, "��������ϣ�ֻ��ȫ�������Ҵܣ���ð���ǣ�������������"
                                "�����ײſ���������\n");
                return 0; 
        } 

        if (me->query("gender") == "����")
        {
                tell_object(me, "���޸����ԣ������������������������񽣡�\n");
                return 0; 
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "����������񽣼�����£��������о�һ��ѧ�ʿ��ܸ��а�"
                                "����\n");
                return 0;
        }

        if (me->query_skill("lamaism", 1) < 200)
        {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }

        if (me->query_skill("buddhism", 1) < 200)
        {
                tell_object(me, "��������ϣ��������ͨ�������ķ�Ӧ�ø��а�����\n");
                return 0;
        }
        
        if ((int)me->query_skill("force") < 300) 
        { 
                tell_object(me, "��������ϣ��������ѣ��Լ����ڹ�ˮƽ�������д���ߡ�\n"); 
                return 0; 
        } 

        if ((int)me->query("max_neili") < 5000) 
        { 
                tell_object(me, "��������ϣ������᲻��������������Ӧ�ü�������������\n"); 
                return 0; 
        } 

        if ((int)me->query_skill("martial-cognize", 1) < 100)
        {
                tell_object(me, "��������ϣ����������ѧ��������һ����ø�����������\n");
                return 0;           
        }
        
        if (random(10) < 5) 
        { 
                tell_object(me, "��������񽣵İ����������򣬻���������һ�ξ��ܹ��ڻ��ͨ��\n"); 
                return 0; 
        } 

        tell_object(me, HIY "һ�󷲳�����ӿ����ͷ���㼸��������̾����ǰ�������ֳ�����"
                            "������\n���Ǽ䣬������ͨ�������񽣡�\n" NOR);
                            
        return 1; 
} 

mapping query_sub_skills() 
{ 
        return sub_skills; 
} 

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������񽣱�����֡�\n");

        if (! me->query("family/family_name") || 
            me->query("family/family_name") != "���ϻ���") 
                return notify_fail("���о���һ�����ֻ���Ĳ��Ƕ��ϻ���ĸ����޷��������а���\n"); 

        if (me->query("int") < 32)
                return notify_fail("���о��˰��죬ֻ�����ֽ�������ǣ�����޷������о���\n");

        if (me->query("con") < 26)
                return notify_fail("���о���һ�����ֻ������ǰ������ð��̫��Ѩͻͻ������\n");
                
        if (me->query_skill("literate", 1) < 200)
                return notify_fail("����������񽣼�����£�����������ѧ��ˮƽ�����о��ġ�\n");

        if (me->query_skill("lamaism", 1) < 200)
                return notify_fail("�㷢���������кܶ����������ķ��йأ��������⡣\n");

        if (me->query_skill("buddhism", 1) < 200)
                return notify_fail("�㷢���������кܶ����������ķ��йأ��������⡣\n");
                            
        if ((int)me->query("max_neili") < 5000)
                return notify_fail("�������̫�����޷�ѧ�����񽣡�\n");

        if ((int)me->query_skill("finger", 1) < 200)
                return notify_fail("��Ļ���ָ����򲻹���\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("liumai-shenjian", 1) + 10)
                return notify_fail("������ڱ��������������ڹ���ˮƽ��\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("liumai-shenjian", 1) + 10)
                return notify_fail("������ڱ�������������ָ����ˮƽ��\n");
                
        return 1;
}

int practice_skill(object me)
{
        object* ob, obj;
        int i,skill,damage;

        if ((int)me->query("qi") < 160)
                return notify_fail("�������̫���ˡ�\n");
                
        if ((int)me->query("neili") < 160)
                return notify_fail("������������������񽣡�\n");
                
        if( skill > 100 && me->query("shen") < 1)
                return notify_fail("�����书�����������¡�\n");
                
        me->receive_damage("qi", 150);
        me->add("neili", -150);
        return 1;
}
                                          
mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        
        if (damage_bonus < 50) return 0;

        if (random(damage_bonus/2) > victim->query_str())
        {
                result =  ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "��������������һ�����죬���Ͼ�����һЩѪ�Σ�\n" NOR]);
                return result;
        }
}

string perform_action_file(string action) 
{ 
        return __DIR__"six-finger/" + action; 
} 

void skill_improved(object me) 
{ 
        int i; 
        string *sub_skillnames; 

        sub_skillnames = keys(sub_skills); 
        for (i = 0; i < sizeof(sub_skillnames); i++) 
                me->delete_skill(sub_skillnames); 
} 

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        if (! undefinedp(me->query_temp("six-action")))
                return action[me->query_temp("six-action")];

        if (random(10) == 8)
        {
                me->add("neili", -200);
                return ([
        "action": HIC "$N" HIC "��Ȼ���ý����е���·����һһӿ����ͷ��ʮָ�׵�����ȥ�����������޾���\n" NOR
                      "��ʱֻ���Ĵ������ݺᣬ����������·������ת��ʹ��$n��ʱ������ң�����ȫ��������\n"
                      "ʹ������" HIR "��Ѫ" NOR "�����ϱ������ʹ̧ͷһ����һ������ӭ���ֵ�",
        "attack": 140,
        "dodge" : 150,
        "parry" : 120,
        "damage": 340,
        "force" : 580,
        "damage_type": "����"]);
        }
        return action[random(sizeof(action))];
}

string query_parry_msg(object victim_weapon)
{
        switch (random(4))
        {
        case 0:
                return "$n������������������ݺύ��������������$NΨ��������̾��ͽ���κΡ�\n";
        case 1:
                return "$n�������ܣ�һ���г彣ֱϮ$N����ǰ��Ѩ���ȵ�$Nֻ�л����Ծȡ�\n";
        case 2:
                return "$n���������������ص���ֱ���$Nüë���䣬������ͨ����Ҳ����ǰ����֣�\n";
        default:
                return "$nһ����Ц�����ν����Ĵ�ɢ������$N����ס��Ω����ǿ֧�š���Լ�԰�����$n�ķ�����\n";
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("six-finger", 1)) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + ob->query_skill("parry") + mp;
        dp = me->query_skill("parry") / 2 +
             me->query_skill("force") / 2 +
             me->query_skill("six-finger", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

     
                result += (["msg" : HIC "$n" HIC "Σ��֮ʱ������һ�ң�����һָ��һ�����������ֱ��$N��ȥ��\n"
                                    HIC "$N" HIC "�����������׺ݣ����ò��������أ������ܿ���\n" NOR]);

                return result;
        } 
}

/*
int query_effect_parry(object attacker, object me) 
{
        int lvl;
        if (objectp(me->query_temp("weapon")))
                return 0;

        lvl = me->query_skill("six-finger", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

*/
int difficult_level() 
{
        return 500; 
}