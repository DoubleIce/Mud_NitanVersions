// This program is a part of NITAN MudLIB
// mingyu-gong.c

#include <ansi.h>

inherit FORCE;

int valid_force(string force) { return 1; }  
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("mingyu-gong", 1);
        return lvl /10 * lvl /10 * 15 * 28 / 10 / 20;
}
string *dodge_msg = ({
        "$N���μ��٣����Ų�ƣ�����$n������Χ�ȹ�������ȴ�����ڼ䲻�ݷ��Ŀ�϶�ܹ�",
        "$N���п���ת�ۣ���$nÿ�ι���ǰ��ٿ����ʧ��һ���Ӿ��ѳ�$n�Ĺ�����Χ",        
        "$Nֻ����ǰһ����ֻ����$n����һ�ϣ��Լ���������ȻĪ������������", 
        "$Nƾ��������������$n�Ĺ�����Χ�ڽ������ܣ���������һ����һ���Ĺ���",
        "$N��Ų���٣���Ȼ�ڿ����γ���Ӱ������������$Nһ��Ų��",
        "$n��ǰ��Ȼһ������ǰ$N����Ӱ�ƺ���Щ������������һ��$N������������ǰ����һ�ߵĽ���",
});

string *parry_msg = ({
        "�ۿ�$nת���ѹ�����$N���赭д��ȴ�ֿ���ޱȣ���$n����ʽ��������",
        "$n�ۿ�����֮�ʣ�ͻ��һ�����ᾢ��ʴ$W���ϣ�û�ȽӴ��������ֱ��Ѿ�ʹ������æ��һ�����ã���Ȼ����",
        "$n�������Ͼ�������ţ�뺣�������ŵ״������в��$Nȴ���Ѿ�����",
        "$n����һ�ݣ������������ƣ������ﳤ�գ���Զ��֪�����������޴�����",
});


string *action_msg = ({
        "$Nʮָ΢�ţ����Ƽ򵥵ģ�ȴ���ſ���ͬʱ����������ȻĪ�еĳ��������$n",
        "$N�������񹦣������𽥱��͸����ɭ��ɱ������ʵ�ʣ���������ס$n",
        "$N˫��һ��һ�գ�ƽʵ��һ��ȴ��$n���紦������֮�У���������",
        "$N�������������ޣ�һ��һʽ�������޷����������������ݺ���ȥ",
        "$N����$w�û���������꣬����������˷���ȥ���γ�����С����",
        "$n����һ��������ѹ���£������Լ����β�����ͬʱһ�������ھ�����䣬����������$n������·",
        "$Nһ�л���$n��ͬʱһ�������ھ����಻����ӿ��$n�����ڣ��ֽ�ʴ��",
        "$N�������񹦣������������ýݣ��������ߴܶ���$nֻ�����ۻ�����",
        "$N΢һ���֣����������綾�ߺ�ˮ�Ƶر���Ⱥ�����裬�ҹ���$n",
        "$nֻ���ù������ھ�������������������һ����������ʲô���������ֱ۱��ǧ������ϵ��Լ�ֱ��ǰ��",
});

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "force" : 500 + random(120),
                "attack": 200 + random(60),
                "dodge" : 180 + random(60),
                "parry" : 180 + random(60),
                "damage" : 180 + random(60),
                "damage_type" : random(2)?"����":"����",  
        ]);
}

string query_dodge_msg(string limb){        return dodge_msg[random(sizeof(dodge_msg))];}

string query_parry_msg(object weapon){        return parry_msg[random(sizeof(parry_msg))];}

int valid_enable(string usage)
{
         return usage == "force" || usage == "unarmed" || usage == "sword" ||
                usage == "dodge" || usage == "parry";
}

int double_attack() { return 1; }

int valid_learn(object me)
{
        int level;
        int i;

        if (me->query("gender") != "Ů��")
                return notify_fail("�㴿��֮�����㣬��������������񹦡�\n");
                
        if (me->query("sex/times"))
                return notify_fail("�������񹦱����Ǵ���֮����\n");

        if (me->query("int") < 30)
                return notify_fail("��������񹦹��ڼ���������⡣\n");

        if ((int)me->query("max_neili") < 3500)
            return notify_fail("���������Ϊ̫ǳ���޷���ת���񹦡�\n");

        level = me->query_skill("mingyu-gong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 100)
                return notify_fail("��������񹦹�����£����Լ�����ѧ����"
                                   "ȫȻ�޷����ס�\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("��Ļ����ڹ���Ϊ���㣬������ת���񹦡�\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("��Ի����ڹ������⻹�������޷���������"
                                   "��������񹦡�\n");

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("��Ի���ȭ�ŵ����⻹�������޷���������"
                                   "��������񹦡�\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;

        if ((int)me->query_skill("mingyu-gong", 1) < 150
           || me->query_skill_mapped("parry") != "mingyu-gong"
           || me->query_skill_mapped("force") != "mingyu-gong"
           || me->query_skill_mapped("unarmed") != "mingyu-gong"
           || (int)me->query("neili") < 500
           || ! living(me))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force") * 12 + ob->query_skill("count", 1) * 6;
        dp = me->query_skill("force") * 12;

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "Ĭ�������ܾ�������"
                                            "�ھ�������$N" + HIR "��һ�У�$N" HIR
                                            "ֻ������������೤���У�˿���������á�\n"
                                            NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "һ�л���$n" HIR "����"
                                            "����ȴ��������޻���һ�㣬������ʱ"
                                            "��ʧ����Ӱ���١�\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "����$n" HIR "΢΢һЦ����������"
                                            "�Ľ�����$N" HIR "��һ�У�����֮����֮����"
                                            "û���ܵ�����˺���\n" NOR]);
                        break;
                }
                return result;
        }
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int i;
        object weapon;

        lvl = me->query_skill("mingyu-gong", 1);
        weapon = me->query_temp("weapon");

        if ( me->query_temp("mingyu_pfm/qiong")
             && me->query_temp("mingyu_pfm/qiong") > 0
             && !me->query_temp("mingyu_pfm/qiong_hit_done")
             && living(victim)
             && !weapon)
        {
                me->add("neili", -40);
                message_vision(HIY"\n$Nǰ�н��䣬����������ǰ����������һʽ������˷������಻����\n"NOR,me);
                me->set_temp("mingyu_pfm/qiong_hit_done", 1);
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2));
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2));
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2));
                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2));
//                COMBAT_D->do_attack(me, victim, me->query_temp("weapon"), random(2));
                me->delete_temp("mingyu_pfm/qiong_hit_done");
        }


        if (damage_bonus < 100
           || lvl < 150
           || me->query("neili") < 300
           || me->query_skill_mapped("force") != "mingyu-gong"
           || me->query_skill_mapped("unarmed") != "mingyu-gong"
           || me->query_skill_prepared("unarmed") != "mingyu-gong")
                return 0;
        // if (damage_bonus / 2 > victim->query_con())
        if (damage_bonus > victim->query_con())
        {
                me->add("neili", -50);
                victim->receive_wound("qi", (damage_bonus - 80) / 2, me);
                return random(2) ? HIR "ֻ��$N" HIR "�����ھ������ڱŷ���һ���ᾢ����ʽ"
                                   "���������ݻ���$n" HIR "����Ԫ��\n" NOR:

                                   HIR "$N" HIR "���񹦵�Ǳ�������˳�����ͻȻ��$n"
                                   HIR "ֻ�к���һ�����һ����Ѫ��\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("mingyu-gong", 1);
        if (lvl < 150) return 0;
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;
        if (lvl < 300) return 90;
        if (lvl < 350) return 100;
        if (lvl < 400) return 110;
        return 120;
}

int practice_skill(object me)
{
        return notify_fail("����ֻ����ѧ(learn)�������������ȡ�\n");
}

int difficult_level()
{
        return 1000;
}

string perform_action_file(string action)
{
        return __DIR__"mingyu-gong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"mingyu-gong/exert/" + action;
}

void skill_improved(object me)
{
        int lvl, layer;

        lvl = me->query_skill("mingyu-gong", 1);
        layer = lvl / 40;

        if ((lvl % 40) == 0 && layer > 9)
        {
                tell_object(me, HIY "��������ֽ���һ�㡣\n" NOR);
        } else
        if ((lvl % 40) == 0)
        {
                tell_object(me, HIY "�������˵�" + chinese_number(layer) +
                                "������񹦡�\n" NOR);
        }
}