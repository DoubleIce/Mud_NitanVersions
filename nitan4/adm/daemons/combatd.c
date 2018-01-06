// This program is a part of NITAN MudLIB
// Combatd.c
// Modified by Lonely@NITAN (03/29/2005)

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

inherit F_DBASE;

// �����������(/combat/)��˵��
// PKS��ɱ���������Ŀ
// MKS��ɱ����NPC��Ŀ(���ﲻ����)
// WPK������ɱ����ҵĴ���
// WPK_NOTGOOD������ɱ��������(shen < 500)��ҵĴ���
// WPK_BAD��    ����ɱ����а��(shen <-500)��ҵĴ���
// WPK_NOTBAD�� ����ɱ����а��(shen >-500)��ҵĴ���
// WPK_GOOD��   ����ɱ��������(shen > 500)��ҵĴ���
// DPS������������ҵĴ���
// DPS_NOTGOOD���������η�����(shen < 500)��ҵĴ���
// DPS_BAD��    �������ε�а��(shen <-500)��ҵĴ���
// DPS_NOTBAD�� �������η�а��(shen >-500)��ҵĴ���
// DPS_GOOD��   �������ε�����(shen > 500)��ҵĴ���
// dietimes��   �����Ĵ���
// last_dieexp��������ʧ�ľ���

// combat/today��¼(mapping)
// which_day: ����(ʵ��ʱ��������)
// id       : n, ��������ĳ��ID�Ĵ���

// �������(random(my_exp) > EXP_LIMIT���򲻼Ӿ���)
#define EXP_LIMIT       200000000

#define ATTACK          0
#define DODGE           1
#define PARRY           2
#define DAMAGE          3
#define FORCE           4

#undef REDUCE_PVP_DAMAGE

#define DEFAULT_MAX_PK_PERDAY   16
#define DEFAULT_MAX_PK_PERMAN   3
#define PVP_DAMAGE_SCALE        20;  // ��Ҷ����ʱ�˺�����ǰֵ���½�Ϊ 20%
#define PVP_WOUND_SCALE         10;  // ��Ҷ����ʱ�˺������ֵ���½�Ϊ 10%
nosave mapping limb_damage = ([
    "ͷ��"  :   100,
    "����"  :   90,
    "�ؿ�"  :   90,
    "����"  :   80,
    "���"  :   50,
    "�Ҽ�"  :   55,
    "���"  :   40,
    "�ұ�"  :   45,
    "����"  :   20,
    "����"  :   30,
    "����"  :   60,
    "С��"  :   70,
    "����"  :   40,
    "����"  :   50,
    "���"  :   35,
    "�ҽ�"  :   40,
    "����"  :   80,
    "ǰ��"  :   40,
    "���"  :   50,
    "�Ȳ�"  :   40,
    "β��"  :   10,
    "���"  :   50,
    "צ��"  :   40,
]);

nosave array danger_limbs = ({
        "ͷ��", "����", "�ؿ�", "����","С��",
});

array head_damage_me_msg = ({
        append_color(HIR "�����ͷ��һ�㷢�Ρ�\n" NOR, HIR),
        append_color(HIB "�����һ����ѣ���������һ�¡�\n" NOR, HIB),
        append_color(BLU "��ֻ����ð���ǣ�������Ʈ��\n" NOR, BLU),
});

array body_damage_me_msg = ({
        append_color(HIR "��ֻ��$l������ʹ�����������ܵ�һ���񵴡�\n" NOR, HIR),
        append_color(HIB "��ֻ��$l���ۣ���������һ���Ҵܡ�\n" NOR, HIB),
        append_color(BLU "��ֻ����$l����ʹ����������������һ����й��\n" NOR, BLU),
});

array guard_msg = ({
        append_color(CYN "$Nע����$n���ж�����ͼѰ�һ�����֡�\n" NOR, CYN),
        append_color(CYN "$N������$n��һ��һ������ʱ׼���������ơ�\n" NOR, CYN),
        append_color(CYN "$N�������ƶ��Ų�����Ҫ�ҳ�$n��������\n" NOR, CYN),
        append_color(CYN "$NĿ��ת���ض���$n�Ķ�����Ѱ�ҽ��������ʱ����\n" NOR, CYN),
        append_color(CYN "$N�������ƶ����Ų����Ż����֡�\n" NOR, CYN),
});

array catch_hunt_human_msg = ({
        append_color(HIW "$N��$n������������ۺ죬���̴���������\n" NOR, HIW),
        append_color(HIW "$N����$n��ȣ����ɶ������㣡��\n" NOR, HIW),
        append_color(HIW "$N��$nһ���棬������˵�ʹ���������\n" NOR, HIW),
        append_color(HIW "$Nһ��Ƴ��$n�����ߡ���һ�����˹�����\n" NOR, HIW),
        append_color(HIW "$Nһ����$n�����һ㶣���У����������㣡��\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����ǵ��ʻ�û���꣬���У���\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����У���\n" NOR, HIW),
});

array catch_hunt_beast_msg = ({
        append_color(HIW "$Nŭ��һ�������˹�������$n��\n" NOR, HIW),
        append_color(HIW "$N����$n�����ɱ��$n��\n" NOR, HIW),
        append_color(HIW "$N���������ͺ�ͻȻ���𹥻�$n��\n" NOR, HIW),
});

array catch_hunt_bird_msg = ({
        append_color(HIW "$N����$nһ��ŭ�����ɳ��˹�����\n" NOR, HIW),
        append_color(HIW "$Nŭ��������ͻȻ���𹥻�$n��\n" NOR, HIW),
        append_color(HIW "$Nһ����������Ȼ��$n����������\n" NOR, HIW),
});

array catch_hunt_msg = ({
        append_color(HIW "$N��$n������������ۺ죬���̴���������\n" NOR, HIW),
        append_color(HIW "$N����$n��ȣ����ɶ������㣡��\n" NOR, HIW),
        append_color(HIW "$N��$nһ���棬������˵�ʹ���������\n" NOR, HIW),
        append_color(HIW "$Nһ��Ƴ��$n�����ߡ���һ�����˹�����\n" NOR, HIW),
        append_color(HIW "$Nһ����$n�����һ㶣���У����������㣡��\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����ǵ��ʻ�û���꣬���У���\n" NOR, HIW),
        append_color(HIW "$N�ȵ�����$n�����У���\n" NOR, HIW),
});

array winner_msg = ({
        append_color(CYN "\n$N������Ц��˵���������ˣ�\n\n" NOR, CYN),
        append_color(CYN "\n$N˫��һ����Ц��˵�������ã�\n\n" NOR, CYN),
        append_color(CYN "\n$Nʤ�����У����Ծ�����ߣ�Ц�������ã�\n\n" NOR, CYN),
        append_color(CYN "\n$N˫��һ����Ц��˵����֪���ҵ������˰ɣ�\n\n" NOR, CYN),
        append_color(CYN "\n$Nʤ�����У����Ծ�����ߣ�̾�������ǰν��Ĺ���ãȻ��\n\n" NOR, CYN),
        append_color(CYN "\n$n������˼�����˵�����ⳡ�����������ˣ��»ؿ�����ô��ʰ�㣡\n\n" NOR, CYN),
        append_color(CYN "\n$n���һ�ݣ��޺޵�˵�������ӱ���ʮ�겻����\n\n" NOR, CYN),
        append_color(CYN "\n$n��ɫһ����˵�����������ˣ��͵���������ɣ�\n\n" NOR, CYN),
        append_color(CYN "\n$n������Ц���е������������ã��������ã���һ���������������\n\n" NOR, CYN),
        append_color(CYN "\n$n��ɫ΢�䣬˵��������������\n\n" NOR, CYN),
        append_color(CYN "\n$n������˼�����˵�����ⳡ�����������ˣ�����������\n\n" NOR, CYN),
        append_color(CYN "\n$n���һ�ݣ�������Ҿ˵�����������ղ�������Ȼ������\n\n" NOR, CYN),
});

string *weapon_parry_throwing = ({
        "$n����$vһ�ӣ���$w��ɡ�\n",
        "$n��$v����ǰһ�ᣬ$w����$v�ϣ�$n���Ͼ���һ�����顣\n",
        "$n�����Ӷ�����$v����$w�����Ӱ���١�\n",
        });

string *unarm_parry_throwing = ({
        "$n����һ������$w�������С�\n",
        "$n���������ָ����һ�У��㽫$w�������С�\n",
        "$n����һֻЬ�Ӷ�׼$wһ�̣�$w����$n��Ь�С�\n",
        });
string *weapon_parry_sixmai = ({
        "$n�趯$v������������һ����Ļ֮�У���ס��$N�����񽣵Ĺ��ơ�\n",
        "$n�Ӷ�$v����ס��$N�����񽣵����ν�����\n",
        "$n����$v�������񽣵����ν�����������$v�ϡ�\n",
        });
string *unarm_parry_sixmai = ({
        "$n��������������ķ��ǰ����ס��$N�������񽣣�����ȴ�����ν�������һƬ��\n",
        "$n����ǰ����һ����ǽ��ֻ�����͡������͡�֮����$N�Ľ�������������ǽ�ϡ�\n",
        "$n��������������$l����������$N�������񽣣���$l���ı�Ƥȴ���ս���\n",
        });
string *star_move_weapon = ({
        "ֻ��$n������$N��$w��һ��һ�ͣ�$w�ڿ���Ӳ����ת�˸��壬����$P�Լ���$l��\n",
        "$nʹһ�ж�ת���ƣ�$N��$w��Ȼ��ת����������$P�Լ���$l��\n",
        });

string *star_move_unarm = ({
        "$n���ö�ת���ƣ����н�$N�������������˻�ȥ��$Nֻ����$l��һ����ۡ�\n",
        "$n�ĳ���һ��һ�ͣ�$N����һ�о�Ȼ�����Լ����ϡ�\n",
        });
string *qiankun_move_weapon = ({
        "ֻ��$n������$N��$w��һ��һ�ͣ�$w�ڿ���Ӳ����ת�˸��壬����$P�Լ���$l��\n",
        "$nʹһ��Ǭ����Ų�ƣ�$N��$w��Ȼ��ת����������$P�Լ���$l��\n",
        });

string *qiankun_move_unarm = ({
        "$n����Ǭ����Ų�ƣ����н�$N�������������˻�ȥ��$Nֻ����$l��һ����ۡ�\n",
        "$n�ĳ���һ��һ�ͣ�$N����һ�о�Ȼ�����Լ����ϡ�\n",
        });

varargs void report_status(object ob, int effective);
protected void quest_kill(object killer, object victim);

void create()
{
        int pd, pm;

        seteuid(getuid());
        set("channel_id", "ս������");

        if (undefinedp(pd = CONFIG_D->query_int("max pk perday")))
                pd = DEFAULT_MAX_PK_PERDAY;

        if (undefinedp(pm = CONFIG_D->query_int("max pk perman")))
                pm = DEFAULT_MAX_PK_PERMAN;

        set("pk_perday", pd);
        set("pk_perman", pm);
}

// message after damage info
nosave string foo_before_hit = 0;
nosave string foo_after_hit = 0;
string query_bhinfo() { return foo_before_hit; }
string query_ahinfo() { return foo_after_hit; }
void clear_bhinfo() { foo_before_hit = 0; }
void clear_ahinfo() { foo_after_hit = 0; }

void set_bhinfo(string msg)
{
        if (! foo_before_hit)
        {
                foo_before_hit = msg;
                return;
        }

        foo_before_hit += msg;
}

void set_ahinfo(string msg)
{
        if (! foo_after_hit)
        {
                foo_after_hit = msg;
                return;
        }

        foo_after_hit += msg;
}

string damage_msg(int damage, string type)
{
        string str;

        if (damage == 0)
                return "���û������κ��˺���\n";

        switch (type)
        {
        case "����":
        case "����":
                if (damage < 15)  return "���ֻ������ػ���$p��Ƥ�⡣\n"; else
                if (damage < 40)  return "�����$p$l����һ��ϸ����Ѫ�ۡ�\n"; else
                if (damage < 100) return "������͡���һ����$w����$p$l����һ���˿ڣ�\n"; else
                if (damage < 200) return "������͡���һ����$w����$p$l����һ��Ѫ���ܵ��˿ڣ�\n"; else
                if (damage < 400) return "������͡���һ����$w����$p$l����һ���ֳ�������˿ڣ�����$N������Ѫ��\n"; else
                                  return "���ֻ����$nһ���Һ���$w����$p$l����һ������ǵĿ����˿ڣ�\n";
                break;
        case "����":
                if (damage < 15)  return "���ֻ������ش���$p��Ƥ�⡣\n"; else
                if (damage < 40)  return "�����$p$l�̳�һ�����ڡ�\n"; else
                if (damage < 100) return "������ۡ���һ����$w�Ѵ�����$n$l������\n"; else
                if (damage < 200) return "������ۡ���һ����$w�Ѵ̽�$n��$l��ʹ$p�������������˼�����\n"; else
                if (damage < 400) return "��������͡���һ����$w����$p$l�̳�һ��Ѫ�������Ѫ������\n"; else
                                  return "���ֻ����$nһ���Һ���$w����$p��$l�Դ���������Ѫ�������أ�\n";
                break;
        case "����":
        case "����":
                if (damage < 15)  return "���ֻ����������������Ĳ�Ӭ��΢���˵㡣\n"; else
                if (damage < 40)  return "�����$p��$l���һ�����ࡣ\n"; else
                if (damage < 100) return "���һ�����У�$n��$l��ʱ����һ���ϸߣ�\n"; else
                if (damage < 150) return "���һ�����У�$n�ƺ���һ����Ȼ���˲�С�Ŀ���\n"; else
                if (damage < 200) return "������项��һ����$n����������\n"; else
                if (damage < 400) return "�����һ�¡��项��һ�����$n�����˺ü�������һ��ˤ����\n"; else
                if (damage < 800) return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n"; else
                                  return "���ֻ�������项��һ�����죬$n��һ�����ݰ���˳�ȥ��\n";
                break;
        case "ץ��":
                if( damage < 10 ) return "���ֻ�������ץ������ץ����΢���˵㡣\n";
                else if( damage < 20 ) return "�����$p��$lץ������Ѫ�ۡ�\n";
                else if( damage < 40 ) return "���һץ���У�$n��$l��ץ����Ѫ�ɽ���\n";
                else if( damage < 80 ) return "������͡���һ����$l��ץ����ɼ��ǣ���\n";
                else if( damage < 120 ) return "���һץ���У�$n��$l��ץ��Ѫ���ɣ�����\n";
                else if( damage < 160 ) return "�����һ�¡��͡���һ��ץ��$n���κü��£���һ��ˤ����\n";
                else if( damage < 240 ) return "���$n����һ����$l��ץ�ý�Ϲ��ۣ���\n";
                else return "���ֻ����$nһ���Һ���$l��ץ�����Ѫ��������Ѫ�������أ���\n";
                break;
        case "����":
                if (damage < 15)  return "���ֻ�ǰ�$n������˰벽����������\n"; else
                if (damage < 40)  return "���$nʹ��һ������$p��$l���һ�����ˡ�\n"; else
                if (damage < 100) return "���һ�����У���$n���ʹ��������ȥ��\n"; else
                if (damage < 150) return "���$n�ƺ���һ��������һ����һ��ף���Ȼ���˵����ˣ�\n"; else
                if (damage < 200) return "���$n��ɫһ�±�òҰף��������������˺ü�����\n"; else
                if (damage < 400) return "������صػ��У�$n���ۡ���һ���³�һ����Ѫ��\n"; else
                if (damage < 800) return "������䡹��һ����$nȫ����Ѫ������������Ѫ���������\n"; else
                                  return "���ֻ���������������죬$nһ���ҽУ���̲�����������ȥ��\n";
                break;
        case "��Ѩ":
                if (damage < 15)  return "���ֻ�����������$n��$l������û�е㵽Ѩ����\n"; else
                if (damage < 40)  return "���$nʹ��һ������$p��$l���һ�����ࡣ\n"; else
                if (damage < 100) return "���һ�����У�$N������$n$l�ϵ�Ѩ����$nֻ��һ����ľ��\n"; else
                if (damage < 200) return "���$n�ƺ���һ��������һ����һ��ף���ʱ����$l��ľ��\n"; else
                if (damage < 400) return "���$n��ɫһ�±�òҰף���$N����$l��Ѩ��,һ����ʹ�鲼����$l��\n"; else
                if (damage < 800) return "���$nһ����У�$l��Ѩ��������,��ʹֱ���ķΣ�\n"; else
                                  return "���ֻ����$nһ���ҽУ�һ���ʹ�����������α�ȫ��������ֱͦͦ�ĵ�����ȥ��\n";
                break;
        case "����":
        case "����":
                if (damage < 15)  return "���ֻ����$n��Ƥ����������������ֻ���Ƶ�Ƥ��\n"; else
                if (damage < 40)  return "�����$n$l���һ����΢���Ϻۡ�\n"; else
                if (damage < 100) return "�����ž����һ����$n$l���һ��������Ѫ�ۣ�\n"; else
                if (damage < 200) return "���ֻ����ž����һ����$n��$l�����Ƥ��������ʹ��$pҧ���гݣ�\n"; else
                if (damage < 400) return "���ֻ����ž����һ����$n��$l�����Ƥ��������ʹ��$pҧ���гݣ�\n"; else
                if (damage < 800) return "�����ž����һ�����죡��һ�º�������ֻ���$nƤ��������Ѫ���ɽ���\n"; else
                                  return "���ֻ����$nһ���Һ���$w���صس�����$p��$l��$n��ʱѪ���ɣ�ʮ�����˾�����\n";
                break;
        case "������":
                if (damage < 15)  return "���$N�ܵ�$n�����������ƺ�һ����\n"; else
                if (damage < 40)  return "���$N��$n�ķ������Ѫ���ڣ���ʧɫ��\n"; else
                if (damage < 100) return "���$N��$n�ķ����վ�����ȣ�ҡҡ�λΡ�\n"; else
                if (damage < 200) return "���$N��$n���������𣬡��١���һ������������\n"; else
                if (damage < 300) return "���$N��$n����÷���������������ð������顣\n"; else
                if (damage < 400) return "���$N��$n�����������ؿ������ܵ�һ���ػ�����������������\n"; else
                if (damage < 600) return "���$N��$n����������ǰһ�ڣ���������ɳ�������\n"; else
                                  return "���$N��$n����������ǰһ�ڣ�������Ѫ������������ߵķ��������ȥ��\n";
                break;
        case "����":
        case "����":
                if (damage < 10)  return "���ֻ����������������Ǹ�$nɦ��һ������\n"; else
                if (damage < 40)  return "�����$n��$l�ҳ�һ��С������\n"; else
                if (damage < 100) return "���$N��һ���Ҹ����ţ�$n��$l��ʱ����һ���ϸߣ�\n"; else
                if (damage < 150) return "���$N��һ���Ҹ����ţ�$n�ƺ�һ����Ȼ���˲�С�Ŀ���\n"; else
                if (damage < 200) return "���ֻ�����项��һ����$n�۵�����������������\n"; else
                if (damage < 400) return "�����һ�¡��䡹��һ���ҵ�$n��ð���ǣ���һ��ˤ����\n"; else
                if (damage < 800) return "������ص����У�$n��ǰһ�ڣ����ۡ���һ���³�һ����Ѫ��\n"; else
                                  return "���ֻ�������䡹��һ�����죬$n���ҵ�Ѫ��ģ�����Ҳ��̶ã�\n";
                break;
        case "ҧ��":
                if( damage < 100 ) return "���ֻ������ز���һ��$p��Ƥ�⡣\n";
                else if( damage < 200 ) return "�����$p$lҧ��һ����ӡ��\n";
                else if( damage < 400 ) return "���$p��ҧ��һƬ������\n";
                else if( damage < 800 ) return "���$p��Ƥ���ⱻҧ��һ��飡\n";
                else if( damage < 1600 ) return "�����$p������ҧ����Ѫ��ģ����һ���$l�⣡\n";
                else return "���ֻ����$nһ���Һ���$p��$l�ϵ��ⱻһ��ҧ����¶����ͷ����\n";
                break;
        case "����":
        case "����":
                if( damage < 100 ) return "���ֻ�ǰ�$p��$l����һ�¡�\n";
                else if( damage < 200 ) return "���$p��$l��$w���˵����˸�С�塣\n";
                else if( damage < 400 ) return "���$p��$l��$w�յú�����ʹ��ʹ�ò�סð��ҧ����\n";
                else if( damage < 800 ) return "������͡�һ�����죬$p���$l��һƬ��ʹ���ѱ�$w�ճ��˰���ɫ�����罹̿��\n";
                else if( damage < 1600 ) return "��������͡�һ�������ȥ��$n��ɫʹ���ѵ���$l��$w�յ�һƬ���ڣ�����ֱð��\n";
                else return "���ֻ����$n�����Һ����ڵ��ϲ�ס�����$l�ѱ�$w�յ�Ƥ�⾡�ã��������磡��\n";
                break;
        case "����":
                if( damage < 100 ) return "���$p���Ǿ���$l��Щ���쬵أ���ͦ����ġ�\n";
                else if( damage < 200 ) return "���$p��$l��������Щ��ľ��\n";
                else if( damage < 400 ) return "���$p������ش��˸�������\n";
                else if( damage < 800 ) return "���$p��ɫһ�䣬������Щ��Ӳ������Ҳ���ɪɪ������\n";
                else if( damage < 1600 ) return "���$p���Ӵ������ɫ�԰ף��촽���÷��ϣ����ظ��ֱ�죡\n";
                else return "���������$n����һ�ƣ����ϲҰ׵�û���Ѫɫ���������ݣ�����ѪҺ�ƺ�������˱�����\n";
                break;
        default:
                if (! type) type = "�˺�";
                if (damage < 15)  str = "���ֻ����ǿ���һ����΢"; else
                if (damage < 40)  str = "��������΢��"; else
                if (damage < 100) str = "������һ��"; else
                if (damage < 150) str = "���һ������"; else
                if (damage < 200) str = "��������Ϊ���ص�"; else
                if (damage < 300) str = "�������൱���ص�"; else
                if (damage < 400) str = "������ʮ�����ص�"; else
                if (damage < 600) str = "�����ɼ������ص�"; else
                                  str = "�����ɷǳ����µ�����";
                return str + type + "��\n";
        }
}

string eff_status_msg(int ratio)
{
        if (ratio==100) return HIG "��������Ѫ��ӯ����û�����ˡ�" NOR;
        if (ratio > 95) return HIG "�ƺ����˵����ˣ����������������������" NOR;
        if (ratio > 90) return HIY "�������������˵����ˡ�" NOR;
        if (ratio > 80) return HIY "���˼����ˣ������ƺ��������¡�" NOR;
        if (ratio > 60) return HIY "���˲��ᣬ������״������̫�á�" NOR;
        if (ratio > 40) return HIR "��Ϣ���أ�������ʼɢ�ң��������ܵ�����ʵ���ᡣ" NOR;
        if (ratio > 30) return HIR "�Ѿ��˺����ۣ���������֧����������ȥ��" NOR;
        if (ratio > 20) return HIR "�����൱�ص��ˣ�ֻ�»�������Σ�ա�" NOR;
        if (ratio > 10) return RED "����֮���Ѿ�����֧�ţ��ۿ���Ҫ���ڵ��ϡ�" NOR;
        if (ratio > 5 ) return RED "���˹��أ��Ѿ�����һϢ�����ڵ�Ϧ�ˡ�" NOR;
        return RED "���˹��أ��Ѿ�������в�����ʱ�����ܶ�����" NOR;
}

string status_msg(int ratio)
{
        if (ratio==100) return HIG "����������������һ��Ҳ���ۡ�" NOR;
        if (ratio > 95) return HIG "�ƺ���Щƣ����������Ȼʮ���л�����" NOR;
        if (ratio > 90) return HIY "������������Щ���ˡ�" NOR;
        if (ratio > 80) return HIY "�����ƺ���ʼ�е㲻̫��⣬������Ȼ�������ɡ�" NOR;
        if (ratio > 60) return HIY "�������꣬������״������̫�á�" NOR;
        if (ratio > 40) return HIR "�ƺ�ʮ��ƣ����������Ҫ�ú���Ϣ�ˡ�" NOR;
        if (ratio > 30) return HIR "�Ѿ�һ��ͷ�ؽ����ģ������������֧����������ȥ��" NOR;
        if (ratio > 20) return HIR "�������Ѿ����������ˡ�" NOR;
        if (ratio > 10) return RED "ҡͷ���ԡ�����бб��վ��վ���ȣ��ۿ���Ҫ���ڵ��ϡ�" NOR;
        return RED "�Ѿ���������״̬����ʱ������ˤ����ȥ��" NOR;
}

varargs void report_status(object ob, int effective)
{
        if (! ob || ! ob->query("max_qi"))
                return;

        if (effective)
                message_vision( "( $N" + eff_status_msg(
                        (int)ob->query("eff_qi") * 100 / (int)ob->query("max_qi") )
                        + " )\n", ob);
        else
                message_vision( "( $N" + status_msg(
                        (int)ob->query("qi") * 100 / (int)ob->query("max_qi") )
                        + " )\n", ob);
}

#ifdef REDUCE_PVP_DAMAGE
int reduce_damage(object attacker, object victim, int damage)
{
        if (objectp(attacker) && objectp(victim) &&
            playerp(attacker) && playerp(victim))
        {
                damage = damage * PVP_DAMAGE_SCALE / 100;
        }

        return damage;
}

int reduce_wound(object attacker, object victim, int wound)
{
        if (objectp(attacker) && objectp(victim) &&
            playerp(attacker) && playerp(victim))
        {
                wound = wound * PVP_WOUND_SCALE / 100;
        }

        return wound;
}
#endif

mixed valid_power(mixed combat_exp)
{
#ifdef LONELY_IMPROVED
        if (count_lt(combat_exp, 200000000))
                return combat_exp;

        combat_exp = count_sub(combat_exp, 200000000);
        if (count_lt(combat_exp, 200000000))
                return count_add(200000000, count_div(combat_exp, 100));

        combat_exp = count_sub(combat_exp, 200000000);
        return count_add(220000000, count_div(combat_exp, 200));
#endif
        if (combat_exp < 200000000)
                return combat_exp;

        combat_exp -= 200000000;
        if (combat_exp < 200000000)
                return 200000000 + combat_exp / 10;

        combat_exp -= 200000000;
        return 220000000 + (combat_exp / 20);
}

// This function calculates the combined skill/combat_exp power of a certain
// skill. This value is used for A/(A+B) probability use.
varargs mixed skill_power(object ob, string skill, int usage, int delta)
{
        int status, level;
        mixed power;
        mapping dbase;
        mapping temp;
        mapping fight;
        mapping apply;

        if (! living(ob)) return 0;

        level = ob->query_skill(skill);

        dbase = ob->query_entire_dbase();
        temp = ob->query_entire_temp_dbase();
        if (temp)
        {
                apply = temp["apply"];
                fight = temp["fight"];
        }

        switch (usage)
        {
                case SKILL_USAGE_ATTACK:
                        if (apply) level += apply["attack"];
                        break;
                case SKILL_USAGE_DEFENSE:
                        if (apply)
                        {
                                level += apply[skill];
                                level += apply["defense"];
                        }
                        break;
        }

        level += delta;

#ifdef LONELY_IMPROVED
        if (level < 1)
        {
                power = count_div(valid_power(ob->query("combat_exp")), 2);
                if (usage == SKILL_USAGE_ATTACK)
                        power = count_mul(count_div(power, 30), dbase["str"]);
                else
                        power = count_mul(count_div(power, 30), dbase["dex"]);

                if (ob->query("reborn/times"))
                        power = count_mul(power, (ob->query("reborn/times") + 1));

                return  power;
        }

        power = count_div(big_number_pow(level, 3), 10);
        power = count_add(power, valid_power(dbase["combat_exp"]));

        if (usage == SKILL_USAGE_ATTACK)
        {
                power = count_mul(count_div(power, 30), (dbase["str"] + (temp ? temp["str"] : 0))/10);
                if (fight && ob->is_fighting())
                         power = count_add(power, count_mul(count_div(power, 200), fight["attack"]));
        }
        else
        {
                power = count_mul(count_div(power, 30), (dbase["dex"] + (temp ? temp["dex"] : 0))/10);
                if (fight && ob->is_fighting())
                         power = count_add(power, count_mul(count_div(power, 200), fight[skill]));

                // ����󷨵ķ�����
                if (ob->in_array())
                {
                        int n;

                        if ((n = ob->query_array_level() / 100))
                                power = count_add(power, count_div(count_mul(power, n), 100));
                }
        }

        if (ob->query("reborn/times"))
                power = count_mul(power, (ob->query("reborn/times") + 1));

        if (ob->query_xuruo())
                power = count_div(power, 2);

        return power;
#endif
        if (level < 1)
        {
                power = valid_power((int)ob->query("combat_exp")) / 2;
                if (usage == SKILL_USAGE_ATTACK)
                        power = power / 30 * dbase["str"];
                else
                        power = power / 30 * dbase["dex"];

                if (ob->query("reborn/times"))
                        power = power * (ob->query("reborn/times") + 1);

                return  power;
        }

        if (level > 500)
                power = (level / 10) * level * level;
        else
                power = level * level * level / 10;

        power += valid_power(dbase["combat_exp"]);

        if (usage == SKILL_USAGE_ATTACK)
        {
                power = power / 30 * (dbase["str"] + (temp ? temp["str"] : 0));
                if (fight && ob->is_fighting())
                         power += power / 200 * fight["attack"];
        } else
        {
                power = power / 30 * (dbase["dex"] + (temp ? temp["dex"] : 0));
                if (fight && ob->is_fighting())
                         power += power / 200 * fight[skill];

                // ����󷨵ķ�����
                if (ob->in_array())
                {
                        int n;

                        if ((n =  ob->query_array_level() / 100))
                        {
                                if (n < 10)
                                        power += power * n / 100;
                                else
                                        power += power / 100 * n;
                        }
                }
        }

        if (ob->query("reborn/times"))
                power = power * (ob->query("reborn/times") + 1);

        // ����״̬����������
        if (ob->query_xuruo()) power /= 2;

        return power;
}

// do_attack()
//
// Perform an attack action. This function is called by fight() or as an
// interface for some special utilize in quests.
//
varargs int do_attack(object me, object victim, object weapon, int attack_type)
{
        mapping my, your;
        mapping my_temp, your_temp;
        mapping prepare, action;
        mapping fight;
        array limbs;
        string limb, res;
        string attack_skill, force_skill, martial_skill, dodge_skill, parry_skill;
        string parry_msg;
        mixed foo;
        int has_weapon;

        int delta;
        mixed ap, dp, pp;
        int damage, damage_bonus;
        int def_damage;
        int def_count;
        int wounded;
        int array_flag;
        int attack;
        int avoid;

        object weapon2; // weapon of victim
        object cloth;   // armor of victim

        string result;
        string damage_info;
        array att, def;

        object env_me;
        object env_v;

        if (environment(me)->query("no_fight"))
        {
                message_vision("$N��$n��������һ������ס���С�\n",
                               me, victim);
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        if (environment(me) != environment(victim))
        {
                me->remove_enemy(victim);
                victim->remove_enemy(me);
                return 0;
        }

        my = me->query_entire_dbase();
        your = victim->query_entire_dbase();

        if (! (my_temp = me->query_entire_temp_dbase()))
                my_temp = allocate_mapping(5);

        if (! (your_temp = victim->query_entire_temp_dbase()))
                your_temp = allocate_mapping(5);

        //
        // (0) Choose skills.
        //
        prepare = me->query_skill_prepare();
        if (! prepare) prepare = ([]);

        if (objectp(weapon))
                attack_skill = weapon->query("skill_type");
        else
        {
                switch (sizeof(prepare))
                {
                case 0: attack_skill = "unarmed"; break;
                case 1: attack_skill = (keys(prepare))[0]; break;
                case 2: attack_skill = (keys(prepare))[me->query_temp("action_flag")]; break;
                }
        }

        if (attack_skill == "pin")
                // the pin skill will the same as the sword skill,
                // why don't I remove pin skill ? because I don't
                // combatd, they as same.
                attack_skill = "sword";

        //
        // (1) Find out what action the offenser will take.
        //
        me->reset_action();
        action = me->query_action();

        has_weapon = objectp(weapon) || objectp(me->query_temp("armor/hands"));

        if (! action)
        {
                // reconfirm
                me->reset_action();
                action = me->query_action();
                if (! mapp(action))
                {
                        CHANNEL_D->do_channel( this_object(), "sys",
                                sprintf("%s(%s): bad action = %O",
                                        me->query("name"), me->query("id"),
                                        me->query_action(1)));
                        return 0;
                }
        }

        if (stringp(me->query_temp("action_msg"))){
                result = "\n" + (string)me->query_temp("action_msg")+ action["action"] + "��\n";
                me->delete_temp("action_msg");
        } else
        if (me->query_temp("action_flag") == 0)
                result = "\n" + action["action"] + "��\n";
        else
                result = "\n������" + action["action"] + "��\n";

        // �жϹ�����λ
        //
        // (2) Prepare AP, DP for checking if hit.
        //
        /* �����ÿ���ʹһЩ�书ѡ��ʹ�ô��书���˵Ĺ�����λ��
         * ���Բ���������˵���ר������·��Ч����
         * �������Ӳ���ϵͳ������
         */
        if (martial_skill = me->query_skill_mapped(attack_skill))
                limb = SKILL_D(martial_skill)->query_attack_limb(me, victim);

        if (! limb)
        {
                limbs = victim->query("limbs");
                if (! arrayp(limbs))
                {
                        limbs = ({ "����" });
                        victim->set("limbs", limbs);
                }
                limb = limbs[random(sizeof(limbs))];

        }

        // �󷨹���
        if (victim->in_array() &&
            victim->query_array_status() &&
            (random(100) < (victim->query_array_level() / 100 + 40)))
        {
                object ob;

                if (((your["qi"] < your["max_qi"] * 2 / 5) ||
                    (your["jing"] < your["max_jing"] * 2 / 5)) &&
                    objectp(ob = victim->query_array_obstructor()) &&
                    ! ob->is_busy())
                {
                        result = replace_string(result, "$l", limb);
                        if (objectp(weapon))
                                result = replace_string(result, "$w", weapon->name());
                        else if (stringp(action["weapon"]))
                                result = replace_string(result, "$w", action["weapon"]);
                        else if (attack_skill == "finger" || attack_skill == "hand")
                                result = replace_string(result, "$w", "��ָ" );
                        else if (attack_skill == "strike" || attack_skill == "claw")
                                result = replace_string(result, "$w", "����" );
                        else    result = replace_string(result, "$w", "ȭͷ" );

                        message_combatd(result, me, victim);
                        message_combatd(HIC BWHT "$N�����Ʋ���������$n����ǰ��\n" NOR, ob, victim);
                        result = "";

                        victim = ob;
                        your = ob->query_entire_dbase();
                        array_flag = 1;
                        attack_type = TYPE_QUICK;
                }
        }

        fight = allocate_mapping(3);
        if (att = SKILLS_D->skill_query_power(martial_skill))
        {
                fight["attack"] = atoi(att[ATTACK]) - 200;
                fight["dodge"]  = atoi(att[DODGE])  - 200;
                fight["parry"]  = atoi(att[PARRY])  - 200;
        }
        else
        {
                fight["attack"] = action["attack"];
                fight["dodge"]  = action["dodge"];
                fight["parry"]  = action["parry"];
        }
        my_temp["fight"] = fight;

#ifdef LONELY_IMPROVED
        ap = atoi(count_div(skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0), 10000));
#else
        ap = skill_power(me, attack_skill, SKILL_USAGE_ATTACK, 0);
#endif
        if (ap < 1) ap = 1;
        if (def_count = sizeof(me->query_enemy()) > 1)
                ap = ap * 9 / (8 + def_count);
        if (member_array(limb, danger_limbs) != -1) /* ��Σ�ղ�λ��������  */
                ap -= ap / 10;                      /* ���еĿ����Լ�С10% */
        if (! me->visible(victim)) ap /= 10;
        if (my["character"] == "���ռ�թ")
                ap += ap * 20 / 100;

        // ��������˵���ֻ���мܲ��ɶ���
        if (array_flag) dp = 0;
        else
        {
#ifdef LONELY_IMPROVED
                dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
                if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
                        dp = count_add(dp, count_mul(count_div(dp, 100), SKILL_D(dodge_skill)->query_effect_dodge(me, victim)));
                dp = atoi(count_div(dp, 10000));
#else
                dp = skill_power(victim, "dodge", SKILL_USAGE_DEFENSE, 0);
                if (stringp(dodge_skill = victim->query_skill_mapped("dodge")))
                        dp += dp / 100 * SKILL_D(dodge_skill)->query_effect_dodge(me, victim);
#endif
                if (dp < 1) dp = 1;
                // ������������������ж���ͬʱ����һ����ʱ�����ͷ����ĳɹ��ʣ�����ϵ��Ϊ 9/(8+N).
                if (def_count = sizeof(victim->query_enemy()) > 1)
                        dp = dp * 9 / (8 + def_count);
                if (! victim->visible(me)) dp /= 10;
                if (victim->is_busy()) dp /= 3;
        }
        //
        // (3) Fight!
        //     Give us a chance of AP/(AP+DP) to "hit" our opponent. Since both
        //     AP and DP are greater than zero, so we always have chance to hit
        //     or be hit.
        //
        damage = 0;
        wounded = 0;
        def_damage = 0;
        damage_info = "";

        if (random(ap + dp) < dp || (victim->query_temp("immortal") && random(100) < 90))
        {  // Does the victim dodge this hit?
#if INSTALL_COMBAT_TEST
                if (wizardp(me) && me->query("env/combat_test"))
                        tell_object(me, HIY "��ս�����顿������ AP��" + ap +
                                    "��DP��" + dp + "��\n" NOR);
                if (wizardp(victim) && victim->query("env/combat_test"))
                        tell_object(victim, HIC "��ս�����顿���Է� AP��" + ap +
                                    "��DP��" + dp + "��\n" NOR);
#endif
                if (! dodge_skill) dodge_skill = "dodge";
                result += SKILL_D(dodge_skill)->query_dodge_msg(limb);

                if (dp < ap && (! userp(victim) || ! userp(me)))
                {
#ifdef LONELY_IMPROVED
                        if (count_lt(your["combat_exp"], EXP_LIMIT))
                        {
                                your["combat_exp"] = count_add(your["combat_exp"], victim->query_int() / 20);
#else
                        if (random(your["combat_exp"]) < EXP_LIMIT && random(2))
                        {
                                your["combat_exp"] += victim->query_int() / 20;
#endif
                                victim->improve_skill("dodge", random(victim->query_int()) / 20);
                        }
                }
                damage = RESULT_DODGE;
        } else
        {
                //
                //      (4) Check if the victim can parry this attack.
                //
                if (! userp(me) || ! userp(victim))
                {
                        if (ap < dp && random(my["int"]) > 8)
                        {
#ifdef LONELY_IMPROVED
                                if (count_lt(my["potential"], me->query_potential_limit()))
                                        my["potential"] = count_add(my["potential"], 2);
#else
                                if (my["potential"] < me->query_potential_limit())
                                        my["potential"]++;
#endif
                                me->improve_skill(attack_skill, random(me->query_int()) / 20);
                        }
                }
                delta = 0;
                if (weapon2 = your_temp["weapon"])
                {
                        if (! weapon) delta = 10;
                } else
                {
                        if (weapon) delta = -10;
                }
#ifdef LONELY_IMPROVED
                pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);
                if (stringp(parry_skill = victim->query_skill_mapped("parry")))
                        pp = count_add(pp, count_mul(count_div(pp, 100), SKILL_D(parry_skill)->query_effect_parry(me, victim)));
                pp = atoi(count_div(pp, 10000));
#else
                pp = skill_power(victim, "parry", SKILL_USAGE_DEFENSE, delta);
                if (stringp(parry_skill = victim->query_skill_mapped("parry")))
                        pp += pp / 100 * SKILL_D(parry_skill)->query_effect_parry(me, victim);
#endif
                if (pp < 1) pp = 1;
                if (def_count = sizeof(victim->query_enemy()) > 1)
                        pp = pp * 9 / (8 + def_count);
                if (victim->is_busy()) pp /= 3;

                if (random(ap + pp) < pp)
                {
#if INSTALL_COMBAT_TEST
                        if (wizardp(me) && me->query("env/combat_test"))
                                tell_object(me, HIY "��ս�����顿������ AP��" + ap +
                                            "��PP��" + pp + "��\n" NOR);
                        if (wizardp(victim) && victim->query("env/combat_test"))
                                tell_object(victim, HIC "��ս�����顿���Է� AP��" + ap +
                                            "��PP��" + pp + "��\n" NOR);
#endif
                        if (! parry_skill) parry_skill = "parry";

                        if (attack_skill == "throwing" && your["race"] ==  "����" ) {
                                if (weapon2)
                                        parry_msg = weapon_parry_throwing[random(sizeof(weapon_parry_throwing))];
                                else {
                                        parry_msg = unarm_parry_throwing[random(sizeof(unarm_parry_throwing))];
                                }
                        } else  if (martial_skill == "six-finger") {
                                if( me->query_skill("six-finger", 1) > victim->query_skill("force", 1) ) {
                                        if (weapon2) {
                                                parry_msg = weapon_parry_sixmai[random(sizeof(weapon_parry_sixmai))];
                                                if (my["jiali"] > weapon2->weight()) {
                                                        parry_msg = replace_string(parry_msg, "$v", weapon2->name());
                                                        weapon2->unequip();
                                                        weapon2->move(environment(victim));
                                                        weapon2->set("consistence", 0);
                                                        if (weapon2->is_item_make()) {
                                                                parry_msg += HIW "$n" HIW "ֻ���û��ھ��𣬱������ֶ�������\n" NOR;
                                                        } else {
                                                                parry_msg += HIW "ֻ������ž����һ����$n" HIW "���е�" + weapon2->name() +
                                                                             HIW "�ѱ�$N" HIW "�����ν�����Ϊ���أ�\n" NOR;
                                                                weapon2->set("name", "�ϵ���" + weapon2->query("name"));
                                                                weapon2->set("value", 0);
                                                                weapon2->set("weapon_prop", 0);
                                                        }
                                                        victim->reset_action();
                                                }
                                        } else parry_msg = unarm_parry_sixmai[random(sizeof(unarm_parry_sixmai))];
                                } else  parry_msg = SKILL_D(parry_skill)->query_parry_msg(weapon2);
                        } else  if (martial_skill == "dragon-strike" || martial_skill == "dugu-jiujian") {
                                parry_msg = SKILL_D(parry_skill)->query_parry_msg(weapon2);
                        } else  if (parry_skill == "douzhuan-xingyi" || parry_skill == "qiankun-danuoyi") {
                                if( victim->query_temp("nuozhuan") ) {
                                        victim->stop_busy();
                                        victim->clear_xuruo();
                                }
                                if( victim->query_skill(parry_skill, 1) > victim->query_skill("force", 1) ) {
                                        if (weapon) {
                                                if (parry_skill == "douzhuan-xingyi")
                                                        parry_msg = star_move_weapon[random(sizeof(star_move_weapon))];
                                                else 
                                                        parry_msg = qiankun_move_weapon[random(sizeof(qiankun_move_weapon))];
                                        } else {
                                                if (parry_skill == "douzhuan-xingyi")
                                                        parry_msg = star_move_unarm[random(sizeof(star_move_unarm))];
                                                else 
                                                        parry_msg = qiankun_move_unarm[random(sizeof(qiankun_move_unarm))];
                                        }

                                        if (weapon)
                                                damage = me->query_temp("apply/damage");
                                        else
                                                damage = me->query_temp("apply/unarmed_damage");

                                        damage += (int)me->query_skill(attack_skill, 1);
                                        damage = (damage + random(damage)) / 2;
                                        if (arrayp(att) && sizeof(att))
                                                //damage += (int)att[DAMAGE] * damage / 100;
                                                damage += (int)att[DAMAGE] * damage / 10;
                                        else if (action["damage"])
                                                //damage += action["damage"] * damage / 100;
                                                damage += action["damage"] * damage / 10;
                                        damage_bonus = me->query_str();
                                        if (arrayp(att) && sizeof(att))
                                                //damage_bonus += (int)att[FORCE] * damage_bonus / 100;
                                                damage_bonus += (int)att[FORCE] * damage_bonus / 10;
                                        else if (action["force"])
                                                //damage_bonus += action["force"] * damage_bonus / 100;
                                                damage_bonus += action["force"] * damage_bonus / 10;
                                        // calculate the damage
                                        if (damage_bonus > 0)
                                                damage += (damage_bonus + random(damage_bonus)) / 2;

                                        me->receive_damage("qi", damage, victim);
                                        if (damage > (int)me->query_temp("apply/armor") + 2)
                                                me->receive_wound("qi", (damage - (int)me->query_temp("apply/armor"))/2, victim);

                                        res = damage_msg(damage, action["damage_type"]);
                                        res = replace_string(res,"n","N");
                                        res = replace_string(res,"p","P");
                                        parry_msg += res;
                                } else
                                        parry_msg = SKILL_D(parry_skill)->query_parry_msg(weapon2);
                        } else {
                                // change to SKILL_D(parry_skill) after added parry msg to those
                                // martial arts that can parry.
                                parry_msg = SKILL_D(parry_skill)->query_parry_msg(weapon2);
                        }

                        if (! stringp(parry_msg))
                                parry_msg = SKILL_D("parry")->query_parry_msg(weapon2);

                        if (stringp(parry_msg))
                                result += parry_msg;

                        if (pp < ap && (! userp(victim) || ! userp(me)))
                        {
#ifdef LONELY_IMPROVED
                                if (count_lt(your["combat_exp"], EXP_LIMIT))
                                {
                                        your["combat_exp"] = count_add(your["combat_exp"], victim->query_int() / 20);
#else
                                if (random(your["combat_exp"]) < EXP_LIMIT && random(2))
                                {
                                        your["combat_exp"] += victim->query_int() / 20;
#endif
                                        victim->improve_skill("parry", random(victim->query_int()) / 20);
                                }
                        }
                        damage = RESULT_PARRY;
                } else
                {
                        //
                        //      (5) We hit the victim and the victim failed to parry
                        //
                        attack = 1;

                        if (weapon)
                                damage = me->query_temp("apply/damage");
                        else
                                damage = me->query_temp("apply/unarmed_damage");

                        damage += (int)me->query_skill(attack_skill, 1);
                        damage = (damage + random(damage)) / 2;
                        if (arrayp(att) && sizeof(att))
                                //damage += (int)att[DAMAGE] * damage / 100;
                                damage += (int)att[DAMAGE] * damage / 10;
                        else
                        if (action["damage"])
                                //damage += action["damage"] * damage / 100;
                                damage += action["damage"] * damage / 10;

                        damage_bonus = me->query_str();

                        if (my["jianu"])
                        {
                                // does angry bonus
                                damage_bonus += me->cost_craze(my["jianu"]);
                                if (me->query_craze() > 1000 &&
                                    random(my["jianu"] + 200) > 200)
                                {
                                        damage_info += random(2) ? HIR "$N" HIR "���һ����˫ĿԲ����һ��������ɱ����Ȼ����\n" NOR
                                                                 : HIR "$N" HIR "�ܲ�����������ǰ�������н���$n" HIR "���������顣\n" NOR;
                                        me->cost_craze(200 + random(300));
                                        damage_bonus += my["jianu"] * 2;
                                }
                        }

                        // Clear the special message info after damage info
                        foo_before_hit = 0;
                        foo_after_hit = 0;

                        // Let force skill take effect.
                        if (my["jiali"] && (my["neili"] > my["jiali"]))
                        {
                                // avoid = victim->query_temp("apply/avoid_attack");
                                if (force_skill = me->query_skill_mapped("force"))
                                {
                                        foo = SKILL_D(force_skill)->hit_ob(me, victim, damage_bonus, my["jiali"]);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage_bonus += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
                        }

                        if (arrayp(att) && sizeof(att))
                                //damage_bonus += (int)att[FORCE] * damage_bonus / 100;
                                damage_bonus += (int)att[FORCE] * damage_bonus / 10;
                        else
                        if (action["force"])
                                //damage_bonus += action["force"] * damage_bonus / 100;
                                damage_bonus += action["force"] * damage_bonus / 10;

                        // calculate the damage
                        if (damage_bonus > 0)
                                damage += (damage_bonus + random(damage_bonus)) / 2;

                        // ���ݹ����Ĳ�λӰ���˺�
                        if (! undefinedp(limb_damage[limb]))
                                damage = (damage * limb_damage[limb] / 100);

                        // Let's attack & parry skill, weapon & armor do effect
                        while (damage > 0)
                        {
                                if (my["not_living"] || your["not_living"])
                                        // Only two living do this
                                        break;

                                if (! living(me) || ! living(victim)) break;

                                if (damage < 1) break;

                                // 20%�Ļ���ֱ�ӱܿ��������
                                if (random(100) < 20) break;

                                // Let parry skill take its special effort.
                                avoid = me->query_temp("apply/avoid_dodge");
                                if (random(100) >= avoid &&
                                    stringp(dodge_skill = victim->query_skill_mapped("dodge")))
                                {
                                        // Ӧ�������ж�def���ж�foo��
                                        if (def = SKILLS_D->skill_query_power(dodge_skill))
                                        {
                                                if (! sizeof(att) ||
                                                    (int)att[ATTACK] - (int)def[DODGE] < 50)
                                                {
                                                        foo = SKILL_D(dodge_skill)->valid_damage(me, victim, damage, weapon);
                                                        if (stringp(foo)) damage_info += foo; else
                                                        if (intp(foo)) damage += foo; else
                                                        if (mapp(foo))
                                                        {
                                                                damage_info += foo["msg"];
                                                                damage += foo["damage"];
                                                        }
                                                }
                                        }
                                        if (damage < 1) break;
                                }

                                avoid = me->query_temp("apply/avoid_parry");
                                if (random(100) >= avoid &&
                                    stringp(parry_skill = victim->query_skill_mapped("parry")) &&
                                    ! me->query("special_skill/drift"))
                                {
                                        if (def = SKILLS_D->skill_query_power(parry_skill))
                                        {
                                                if (! sizeof(att) ||
                                                    (int)att[ATTACK] - (int)def[PARRY] < 50)
                                                {
                                                        foo = SKILL_D(parry_skill)->valid_damage(me, victim, damage, weapon);
                                                        if (stringp(foo)) damage_info += foo; else
                                                        if (intp(foo)) damage += foo; else
                                                        if (mapp(foo))
                                                        {
                                                                damage_info += foo["msg"];
                                                                damage += foo["damage"];
                                                        }
                                                }
                                        }
                                        if (damage < 1) break;
                                }

                                if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["beast"]))
                                {
                                        foo = cloth->valid_damage(me, victim, damage, weapon);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }

                                // Let armor/cloth take its special effort
                                if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["armor"]))
                                {
                                        foo = cloth->valid_damage(me, victim, damage, weapon);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                } else
                                if (mapp(your_temp["armor"]) && objectp(cloth = your_temp["armor"]["cloth"]))
                                {
                                        foo = cloth->valid_damage(me, victim, damage, weapon);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }

                                if (damage < 1) break;

                                // Let attack skill take its special effort.
                                avoid = victim->query_temp("apply/avoid_attack");
                                if (random(100) >= avoid &&
                                    stringp(martial_skill = me->query_skill_mapped(attack_skill)) &&
                                    sizeof(att) && (int)att[ATTACK] > 150)
                                {
                                        foo = SKILL_D(martial_skill)->hit_ob(me, victim, damage);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                        if (damage < 1) break;
                                }

                                // Let weapon or living have their special damage.
                                if (weapon)
                                {
                                        foo = weapon->hit_ob(me, victim, damage);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                } else
                                {
                                        foo = me->hit_ob(me, victim, damage);
                                        if (stringp(foo)) damage_info += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                damage_info += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }

                                if (damage < 1) break;

                                if (mapp(my_temp["apply"]) && my_temp["apply"]["double_damage"] > 0)
                                {
                                        if (random(100) < my_temp["apply"]["double_damage"])
                                        {
                                                int damage2, scale;
                                                damage2 = random(damage);
                                                scale = 100 + damage2 * 100 / damage;
                                                damage += damage2;
                                                damage_info += HIY "$N" HIY "�������飬����������һ��֮�о����������˺�������$n" HIY "��ɡ�" + scale + "%�����˺���\n" NOR;
                                        }
                                }

                                // finish
                                break;
                        }

                        //
                        //      (6) Inflict the damage.
                        //

                        if (damage > 0)
                        {
                                int def_exp, att_exp;

                                // Let combat exp take effect
                                def_exp = atoi(count_div(your["combat_exp"], 10000));
                                att_exp = atoi(count_div(my["combat_exp"], 10000));
                                while( random(def_exp) > att_exp ) {
                                        damage -= damage / 4;
                                        def_exp /= 2;
                                }
                                if (damage < 1) damage = 1;

                                if (my["character"] == "�ĺ�����")
                                        damage += damage * 20 / 100;

                                // calculate wounded
                                wounded = damage;
                                if (mapp(your_temp["apply"]) && your_temp["apply"]["armor"] > 0)
                                        wounded -= random(your_temp["apply"]["armor"]);

                                if (wounded > 400)
                                        wounded = (wounded - 400) / 4 + 300;
                                else
                                if (wounded > 200)
                                        wounded = (wounded - 200) / 2 + 200;
                                else
                                if (wounded < 1)
                                        wounded = 0;

                                // recalculate damage
                                if (damage > 400)
                                        damage = (damage - 400) / 4 + 300;
                                else
                                if (damage > 200)
                                        damage = (damage - 200) / 2 + 200;

                                if (your["character"] == "��������")
                                        wounded -= wounded * 20 / 100;
#ifdef REDUCE_PVP_DAMAGE
                                damage = COMBAT_D->reduce_damage(me, victim, damage);
#endif
                                damage = victim->receive_damage("qi", damage, me);
                                if (damage < 1)
                                        damage_info += BLU "$n" BLU "����Ļ�����$N" BLU "��һ���������˺���\n" NOR;

                                if (wounded > 0 &&
                                    // ((me->is_killing(your["id"]) && random(3) == 1) ||
                                    (has_weapon ||
                                     random(3) == 1))
                                {
                                        // We are sure that damage is greater than victim's armor here.
#ifdef REDUCE_PVP_DAMAGE
                                        wounded = COMBAT_D->reduce_wound(me, victim, wounded);
#endif
                                        wounded = victim->receive_wound("qi", wounded, me);
                                } else
                                        wounded = 0;

                                // add message before hit in victim
                                if (foo_before_hit)
                                        result += foo_before_hit;

                                result += damage_msg(damage, action["damage_type"]);
                                damage_info += "( $n" +
                                        status_msg(victim->query("qi") * 100 /
                                        (victim->query("max_qi") ? victim->query("max_qi") : 100)) + ")\n";

                                // ��Ʒ���߷���Ч��
                                def_damage = victim->query_temp("apply/def_damage");
                                if (def_damage && random(3) == 1)
                                {
                                        if (objectp(cloth = victim->query_temp("armor/armor")) &&
                                            cloth->query("enchase/apply_prop/def_damage"))
                                                damage_info += BLINK + HIM + cloth->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                                        else
                                        if (objectp(cloth = victim->query_temp("armor/cloth")) &&
                                            cloth->query("enchase/apply_prop/def_damage"))
                                                damage_info += BLINK + HIM + cloth->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                                        else
                                                damage_info += BLINK + HIM "$n" BLINK + HIM "��������һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;

                                        me->receive_damage("qi", def_damage, victim);
                                        me->receive_damage("jing", def_damage, victim);
                                        damage_info += "( $N" +
                                                status_msg(me->query("qi") * 100 /
                                                (me->query("max_qi") ? me->query("max_qi") : 100)) + ")\n";
                                }
                        }

                        if (foo_after_hit)
                                damage_info += foo_after_hit;

#ifdef LONELY_IMPROVED
                        if (count_lt(my["combat_exp"], EXP_LIMIT) && random(2))
                        {
                                my["combat_exp"] = count_add(my["combat_exp"], me->query_int() / 20);

                                if (count_lt(my["potential"], me->query_potential_limit()))
                                        my["potential"] = count_add(my["potential"], 2);
#else
                        if (random(my["combat_exp"]) < EXP_LIMIT && random(2))
                        {
                                my["combat_exp"] += me->query_int() / 20;

                                if (my["potential"] < me->query_potential_limit())
                                        my["potential"]++;
#endif
                                me->improve_skill(attack_skill, random(me->query_int()) / 20);
                        }
                }
        }

        result = replace_string(result, "$l", limb);
        if (objectp(weapon2 = victim->query_temp("weapon")))
                result = replace_string(result, "$v", weapon2->name());
        if (objectp(weapon))
                result = replace_string(result, "$w", weapon->name());
        else if (stringp(action["weapon"]))
                result = replace_string(result, "$w", action["weapon"]);
        else if (attack_skill == "finger" || attack_skill == "hand")
                result = replace_string(result, "$w", "��ָ" );
        else if (attack_skill == "strike" || attack_skill == "claw")
                result = replace_string(result, "$w", "����" );
        else    result = replace_string(result, "$w", "ȭͷ" );

        message_combatd(result, me, victim, damage_info);

        if (damage > 0)
        {
#if INSTALL_COMBAT_TEST
                if (userp(me) && me->query("env/combat_test"))
                        tell_object(me, HIW "( ���" +
                                        victim->query("name") + HIW "���" +
                                        damage + "���˺���" +
                                        wounded + "�㴴�ˡ�)\n" NOR);
                if (userp(victim) && victim->query("env/combat_test"))
                        tell_object(victim, HIG "( ���ܵ�" +
                                        me->query("name") + HIG + damage + "���˺���" +
                                        wounded + "�㴴�ˡ�)\n" NOR);
#endif
                if (attack == 1)
                {
                        int pers;

                        switch(limb)
                        {
                        // ͷ�������˻���һЩ��
                        case "ͷ��":
                        case "����":
                                damage /= 4;
                                if (damage < 1)
                                        damage = 1;
                                if (damage > 8000)
                                        damage = 8000;
                                victim->receive_damage("jing", damage, me );
                                pers = victim->query("jing")*100/victim->query("max_jing");
                                if (pers <= 30)
                                        tell_object(victim, head_damage_me_msg[2]);
                                else if (pers <= 70)
                                        tell_object(victim, head_damage_me_msg[1]);
                                else
                                        tell_object(victim, head_damage_me_msg[0]);
                                break;
                        // ������Щ��λ�������ܵ��񵴡�
                        case "�ؿ�":
                        case "����":
                        case "С��":
                                if (victim->query("max_neili") && victim->query("neili"))
                                {
                                        string report_limb_msg;

                                        damage /= 4;
                                        if (damage < 1)
                                                damage = 1;
                                        if (damage > 10000)
                                                damage = 10000;
                                        if (victim->query("neili") <= damage)
                                                victim->set("neili", 0);
                                        else
                                                victim->add("neili", -damage);
                                        if (damage <= 500)
                                                report_limb_msg = body_damage_me_msg[0];
                                        else if (damage <= 1000)
                                                report_limb_msg = body_damage_me_msg[1];
                                        else
                                                report_limb_msg = body_damage_me_msg[2];
                                        report_limb_msg = replace_string(report_limb_msg, "$l", limb);
                                        tell_object(victim, report_limb_msg);
                                }
                                break;
                        }
                }

                // ת������������������Ч��
                if (victim->query("special_skill/monster") && random(5) == 1)
                {
                        message_vision(HIG "$N" HIG "ʩչ����������������$n" HIG "����ͬʱҲ�ܵ����ˡ�\n" NOR, victim, me);
                        me->receive_damage("qi", damage, victim);
                        if (random(2) == 1) me->receive_wound("qi", damage / 2, victim);
                        damage_info = "(" + me->name() + status_msg(me->query("qi") * 100 / me->query("max_qi")) + ")\n";
                        message_vision(damage_info, me);
                }

                // if(victim->query("special_skill/demon") && random(5) == 1)
                // message_vision(HIW"$Nǿ��һ�ڵ���֮����������ת֮�£���������������\n"NOR,victim,me);
                // victim->receive_curing("qi", victim->query("max_qi") / 3);

                // �����к󽵵�æ��
                if (victim->is_busy()) victim->interrupt_me(me, 30 + random(10));

                if ((! me->is_killing(your["id"])) &&
                    (! victim->is_killing(my["id"])) &&
                    ! victim->query("not_living") &&
                    your["qi"] * 3 <= your["max_qi"])
                {
                        me->remove_enemy(victim);
                        victim->remove_enemy(me);
                        if (me->query("can_speak") && victim->query("can_speak"))
                                message_vision(winner_msg[random(sizeof(winner_msg))],
                                               me, victim);
                        if (me == victim->query_competitor())
                        {
                                me->win();
                                victim->lost();
                        }
                }

                // if(me->query("special_skill/tianmo") && random(5) == 1)
                // {
                //         message_vision(HIR"$N���и��ֳ���ħ����ʱ��������ѧ�������Ե�Ѫ�����������Ƹ���������\n" NOR, me, victim);
                //         me->receive_curing("qi", (me->query("max_qi")*(int)me->query("special_skill/tianmo",1)*2/100));
                //         do_attack(me, victim, weapon, 3);
                // }
                /*
                if (me->is_busy() && !random(6))
                {
                        message_vision(HIW "$N�ж�΢�����ƣ���æĬ���������ƿ�������ҪѨ��\n" NOR, me);
                        me->interrupt_me(random((int)me->query_busy()));
                }
                */

                if (me->query_condition("no_perform") && ! random(6))
                {
                        message_vision(HIY"$N�����Լ���Ѫ���в�������æĬ��������Ӳ��ѹ���˷��ڲ��ѵ���Ѫ��\n"NOR, me);
                        me->apply_condition("no_perform", random((int)me->query_condition("no_perform")));
                }

                if (me->query_condition("no_exert") && ! random(6))
                {
                        message_vision(HIC"$N�����Լ���Ϣ���ȣ���æĬ��������������Ϣ��\n"NOR, me);
                        me->apply_condition("no_exert", random((int)me->query_condition("no_exert")));
                }
        }

        if (functionp(action["post_action"]))
                evaluate(action["post_action"], me, victim, weapon, damage);

        // See if the victim can make a riposte.
        if (attack_type == TYPE_REGULAR &&
            damage < 1 &&
            your_temp["guarding"])
        {
                your_temp["guarding"];
                if (random(my["dex"]) < 5)
                {
                        message_combatd("$Nһ�����У�¶����������\n",
                                        me, 0, "");
                        do_attack(victim, me, your["weapon"],
                                  TYPE_QUICK);
                } else
                {
                        message_combatd("$N��$n����ʧ�󣬳û�����������\n",
                                        victim, me, "");
                        do_attack(victim, me, your_temp["weapon"],
                                  TYPE_RIPOSTE);
                }
        }
}

// do damage when perform
// I will consider the damage of the weapon
// what is final: final may be a function with result type string,
// or a single string.
// The syntax of the final string is info:damage_type@limb or info only,
// If the limb if ?, the system will auto select limb of
// target, if the final is a single string, the system will
// treat as damage infomation.
varargs string do_damage(object me, object target, mixed type,
                         int damage, int percent, mixed final)
{
        mapping my;
        object weapon;
        object cloth;
        int apply;
        int armor;
        int wound;
        int jiali;
        int bonus;
        mixed foo;
        string msg;
        string skill;
        array limbs;
        string limb;
        string damage_type;
        string result;
        int str;
        int damage_bonus;
        int def_damage;
        mapping prepare;
        string attack_skill;
        array att, def;
        int avoid;
        int def_exp, att_exp;

        if (environment(me) != environment(target))
        {
                me->remove_enemy(target);
                target->remove_enemy(me);
                return "";
        }

        // Am I use weapon
        if (type == WEAPON_ATTACK)
        {
                apply  = me->query_temp("apply/damage");
                weapon = me->query_temp("weapon");
        } else
        if (type == UNARMED_ATTACK)
        {
                apply  = me->query_temp("apply/unarmed_damage");
                weapon = 0;
        } else
        if (type == REMOTE_ATTACK)
        {
                apply  = 0;
                weapon = 0;
        } else
        {
                if (me->query_temp("weapon"))
                {
                        apply  = me->query_temp("apply/damage");
                        weapon = me->query_temp("weapon");
                } else
                {
                        apply  = me->query_temp("apply/unarmed_damage");
                        weapon = 0;
                }
        }

        prepare = me->query_skill_prepare();
        if (! prepare) prepare = ([]);

        if (type == REMOTE_ATTACK)
                skill = "force";
        else
        if (weapon)
                skill = weapon->query("skill_type");
        else
        {
                switch (sizeof(prepare))
                {
                case 0: skill = "unarmed"; break;
                case 1:
                case 2: skill = (keys(prepare))[0]; break;
                }
        }

        if (skill == "pin") skill = "sword";

        attack_skill = me->query_skill_mapped(skill);
        if (SKILLS_D->skill_query_power(attack_skill))
                att = SKILLS_D->skill_query_power(attack_skill);

        // Check the target's armor
        armor = target->query_temp("apply/armor");

        damage += apply;
        msg = "";
        foo_after_hit = 0;

        while (type == SPECIAL_ATTACK || type == REMOTE_ATTACK)
        {
                skill = target->query_skill_mapped("dodge");
                if (stringp(skill) && skill == "lingbo-weibu")
                {
                        foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                } 
                break;
        }                

        while (type == UNARMED_ATTACK || type == WEAPON_ATTACK)
        {
                if (! living(target)) break;

                if (random(100) < 20)
                        break;

                if (attack_skill == "six-finger" ||
                    attack_skill == "dragon-strike" ||
                    attack_skill == "moon-blade" ||
                    attack_skill == "dugu-jiujian")
                        break;

                avoid = me->query_temp("apply/avoid_parry");
                skill = target->query_skill_mapped("parry");

                // Let parry skill take its special effort
                if (stringp(skill) && (skill == "qiankun-danuoyi" ||
                    skill == "douzhuan-xingyi"))
                {
                        foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                } else
                if (random(100) >= avoid &&
                    stringp(skill) && ! me->query("special_skill/drift"))
                {
                        if (def = SKILLS_D->skill_query_power(skill))
                        {
                                if (! sizeof(att) ||
                                    (int)att[ATTACK] - (int)def[PARRY] < 50)
                                {
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                        if (stringp(foo)) msg += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                msg += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }
                        }
                }

                if (damage < 1) break;

                avoid = me->query_temp("apply/avoid_dodge");
                skill = target->query_skill_mapped("dodge");

                // Let dodge skill take its special effort
                if (stringp(skill) && skill == "lingbo-weibu")
                {
                        foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                } else
                if (random(100) > avoid && stringp(skill))
                {
                        if (def = SKILLS_D->skill_query_power(skill))
                        {
                                if (! sizeof(att) ||
                                    (int)att[ATTACK] - (int)def[DODGE] < 50)
                                {
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage, weapon);
                                        if (stringp(foo)) msg += foo; else
                                        if (intp(foo)) damage += foo; else
                                        if (mapp(foo))
                                        {
                                                msg += foo["msg"];
                                                damage += foo["damage"];
                                        }
                                }
                        }
                }

                if (damage < 1) break;

                if (cloth = target->query_temp("armor/beast"))
                {
                        foo = cloth->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                } else
                // Let cloth & armor take its special effort
                if (cloth = target->query_temp("armor/armor"))
                {
                        foo = cloth->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                } else
                if (cloth = target->query_temp("armor/cloth"))
                {
                        foo = cloth->valid_damage(me, target, damage, weapon);
                        if (stringp(foo)) msg += foo; else
                        if (intp(foo)) damage += foo; else
                        if (mapp(foo))
                        {
                                msg += foo["msg"];
                                damage += foo["damage"];
                        }
                }

                // Finish
                break;
        }

        // Let combat exp take effect
        def_exp = atoi(count_div(target->query("combat_exp"), 10000));
        att_exp = atoi(count_div(me->query("combat_exp"), 10000));
        while( random(def_exp) > att_exp )
        {
                damage -= damage / 4;
                def_exp /= 2;
        }

        while (damage > 0)
        {
                if (target->is_busy()) target->interrupt_me(target, 30 + random(10));

                // Let weapon/unarmed attack take its special effort
                if (type == WEAPON_ATTACK && objectp(weapon))
                        // weapon attack
                        foo = weapon->hit_ob(me, target, damage);
                else
                if (type == UNARMED_ATTACK)
                        // unarmed attack
                        foo = me->hit_ob(me, target, damage);
                else
                if (type == SPECIAL_ATTACK)
                {
                        if (objectp(weapon))
                                foo = weapon->hit_ob(me, target, damage);
                        else
                                foo = me->hit_ob(me, target, damage);
                }
                else
                if (objectp(type))
                        // special item attack
                        foo = type->hit_ob(me, target, damage);

                if (stringp(foo)) msg += foo; else
                if (intp(foo)) damage += foo; else
                if (mapp(foo))
                {
                        msg += foo["msg"];
                        damage += foo["damage"];
                }

                // do enforce effect
                my = me->query_entire_dbase();
                if ((jiali = my["jiali"]) > 0 && my["neili"] >= jiali)
                {
                        // eforced
                        my["neili"] -= jiali;
                        if (type == REMOTE_ATTACK || type == SPECIAL_ATTACK)
                        {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);
                        } else
                        {
                                damage_bonus = SKILLS_D->enforce_power(me, jiali);

                                if (! living(target)) break;
                                // check special force effort
                                skill = target->query_skill_mapped("force");
                                if (stringp(skill))
                                {
                                        foo = SKILL_D(skill)->valid_damage(me, target, damage_bonus);
                                        if (stringp(foo)) msg += foo; else
                                        if (intp(foo)) damage_bonus += foo; else
                                        if (mapp(foo))
                                        {
                                                msg += foo["msg"];
                                                damage_bonus += foo["damage"];
                                        }
                                }
                        }
                        damage += damage_bonus;
                }

                if (damage < 1) break;

                if (me->query_temp("apply/double_damage") > 0)
                {
                        if (random(100) < me->query_temp("apply/double_damage"))
                        {
                                int damage2, scale;
                                damage2 = random(damage);
                                scale = 100 + (damage2 * 10) / damage * 10;
                                damage += damage2;
                                msg += HIY "$N" HIY "�������飬����������һ��֮�о����������˺�������$n" HIY "��ɡ�" + scale + "%�����˺���\n" NOR;
                        }
                }

                // do strength effect
                str = me->query_str() + me->query_temp("str");
                if (str < 20)
                        damage += damage * str / 50;
                else
                if (str < 40)
                        damage += damage * ((str - 20) / 2 + 20) / 50;
                else
                        damage += damage / 50 * ((str - 40) / 4 + 30);

                // recalculate damage
                if (damage > 1500)
                        damage = (damage - 1500) / 4 + 1000;
                else
                if (damage > 500)
                        damage = (damage - 500) / 2 + 500;

                // do damage
#ifdef REDUCE_PVP_DAMAGE
                damage = COMBAT_D->reduce_damage(me, target, damage);
#endif
                wound = (damage - random(armor)) * percent / 100;
                damage = target->receive_damage("qi", damage, me);
                if (damage < 1) 
                        msg += BLU "$n" BLU "����Ļ�����$N" BLU "��һ���������˺���\n" NOR;

                if (target->query("character") == "��������")
                        wound -= wound * 20 / 100;
                if (wound > 0)
                {
#ifdef REDUCE_PVP_DAMAGE
                        wound = COMBAT_D->reduce_wound(me, target, wound);
#endif
                        wound = target->receive_wound("qi", wound, me);
                }

                if (functionp(final)) final = evaluate(final);
                if (stringp(final))
                {
                        if (sscanf(final, "%s@%s", final, limb) == 2)
                        {
                                if (sscanf(final, "%s:%s", result, damage_type) != 2)
                                {
                                        result = HIR "���д��˸����У�";
                                        damage_type = final;
                                }
                                if (sscanf(limb, "?%*s"))
                                {
                                        // auto select limb
                                        limbs = target->query("limbs");
                                        if (! arrayp(limbs))
                                        {
                                                limbs = ({ "����" });
                                                target->set("limbs", limbs);
                                        }
                                        limb = limbs[random(sizeof(limbs))];
                                }

                                // indicate damage type & limb
                                final = replace_string(damage_msg(damage, damage_type), "$l", limb);
                                final = replace_string(final, "$n", "$n" HIR);
                                final = replace_string(final, "$N", "$N" HIR);
                                final = replace_string(final, "$p", "$p" HIR);
                                final = replace_string(final, "$P", "$P" HIR);
                                if (weapon)
                                        final = replace_string(final, "$w", weapon->name() + HIR);
                                final = result + HIR + final + NOR;
                        }

                        msg += final;
                        msg += "( $n" + status_msg(target->query("qi") * 100 / (target->query("max_qi") ?
                                                   target->query("max_qi") : 100)) + ")\n";
                }
#if INSTALL_COMBAT_TEST
                msg += HIW "( $N" HIW "��$n" HIW "���" + damage + "���˺���" + wound + "�㴴�ˡ�)\n" NOR;
#endif
                // ��Ʒ���߷���Ч��
                def_damage = target->query_temp("apply/def_damage");
                if (def_damage && random(5) == 1)
                {
                        if (objectp(cloth = target->query_temp("armor/armor")) &&
                            cloth->query("enchase/apply_prop/def_damage"))
                                msg += BLINK + HIM + cloth->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                        else
                        if (objectp(cloth = target->query_temp("armor/cloth")) &&
                            cloth->query("enchase/apply_prop/def_damage"))
                                msg += BLINK + HIM + cloth->name() + BLINK + HIM "����һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;
                        else
                                msg += BLINK + HIM "$n" BLINK + HIM "��������һ������ѣĿ�ĺ��Ϯ��$N��\n" NOR;

                        me->receive_damage("qi", def_damage, target);
                        me->receive_damage("jing", def_damage, target);
                        msg += "( $N" +
                                status_msg(me->query("qi") * 100 /
                                (me->query("max_qi") ? me->query("max_qi") : 100)) + ")\n";
                } else
                if (target->query("special_skill/monster") && random(5) == 1)
                {
                        message_vision(HIG "$N" HIG "ʩչ����������������$n" HIG "����ͬʱҲ�ܵ����ˡ�\n" NOR, target, me);
                        me->receive_damage("qi", damage, target);
                        if (random(2) == 1) me->receive_wound("qi", damage / 2, target);
                        msg += "( $N" +
                                status_msg(me->query("qi") * 100 /
                                (me->query("max_qi") ? me->query("max_qi") : 100)) + ")\n";
                }
                break;
        }

        if (foo_after_hit) msg += foo_after_hit;
        if (foo_before_hit) msg = foo_before_hit + msg;
        // Clear the special message info after damage info
        foo_before_hit = 0;
        foo_after_hit = 0;

        return msg;
}

//      auto_perform()
//      �Զ�������
int auto_perform(object me, object target, string perform_skill)
{
        int l;
        string dir;
        string file;
        mixed *all_file;

        if (! stringp(dir = SKILL_D(perform_skill) + "/") ||
                file_size(dir) != -2)   // ����书û�о���
                return 0;

        if (file_size(dir + "perform/") == -2)  // ����书��һ��perform/��Ŀ¼
        {
                all_file = get_dir(dir + "perform/");
                if (! sizeof(all_file))
                        all_file = get_dir(dir);
                else
                        dir += "perform/";
        }
        else
                all_file = get_dir(dir);

        if (! sizeof(all_file)) // ����书û�о���
                return 0;

        all_file = filter_array(all_file, (: is_c_file($1) :));     // ȡ��*.c�ļ�
        if (! sizeof(all_file)) // ����书û�о���
                return 0;

        file = all_file[random(sizeof(all_file))];      // �����ȡ�书�ľ���
        l = strlen(file);
        file = dir + file[0..l-3];
        return (int)call_other(file, "perform", me, target);
}

//      fight()
//
//      This is called in the attack() defined in F_ATTACK, which handles fighting
//      in the heart_beat() of all livings. Be sure to optimize it carefully.
//
void fight(object me, object victim)
{
        object ob;
        object weapon, weapon2;
        string askill;
        int double_attack;
        mapping prepare;
        string result;
        mapping my_temp;
        int i, auto_perform, can_auto_perform;
        string the_perform_skill, perform_skill_1, perform_skill_2;

        if (! living(me)) return;

        if (! me->visible(victim)) return;

        if (! mapp(my_temp = me->query_entire_temp_dbase()))
                my_temp = ([ ]);

        auto_perform = 0;

        if (me->query("auto_perform"))
                auto_perform = me->query("auto_perform");
        else
                auto_perform = me->query_auto_perform();

        if (auto_perform < 0) auto_perform = 0;
        if (auto_perform > 10) auto_perform = 10;

        prepare = me->query_skill_prepare();
        if (sizeof(prepare) && stringp(askill = (keys(prepare))[0]))
        {
                if (! me->query_temp("weapon") && (askill == "sword" ||
                    askill == "blade" || askill == "hammer" || askill == "whip"))
                {
                        for (i=0; i<sizeof(keys(prepare)); i++)
                                me->prepare_skill((keys(prepare))[i]);

                        tell_object(me, HIY "�����ڲ���" HIR "���ּ���" HIY "���й�����"
                                        HIY "ȡ������" HIR "��������" HIY "������\n" NOR);
                }
        }

        if (weapon = my_temp["weapon"])
                askill = weapon->query("skill_type");
        else if (! prepare || sizeof(prepare) == 0) askill = "unarmed";
        else if (sizeof(prepare)) askill = (keys(prepare))[0];
        if (askill == "pin") askill = "sword";

        askill = me->query_skill_mapped(askill);

        if (auto_perform == 1 || (random(auto_perform) == 1))
        {
                can_auto_perform = 0;
                if (askill)
                {
                        perform_skill_1 = askill;
                        can_auto_perform = 1;
                }

                if (! weapon && prepare && sizeof(prepare) > 1)
                        perform_skill_2 = me->query_skill_mapped((keys(prepare))[1]);

                if (perform_skill_2) can_auto_perform = 2;

                if (can_auto_perform == 1)
                        auto_perform(me, victim, perform_skill_1);
                else if (can_auto_perform == 2)
                {
                        if (random(2))
                                the_perform_skill = perform_skill_1;
                        else
                                the_perform_skill = perform_skill_2;

                        if (! auto_perform(me, victim, the_perform_skill))
                                auto_perform(me, victim, (the_perform_skill == perform_skill_1) ?
                                                        perform_skill_2 : perform_skill_1);
                }
        }

        if (! objectp(me) || ! objectp(victim)) return;

        if (me->is_busy()) return;

        if (askill && random(me->query_dex()) >= 8)
                double_attack = (sizeof(prepare) >= 2 && ! weapon) ||
                        SKILL_D(askill)->double_attack();

        // If victim is busy or unconcious, always take the chance to make an attack.
        if (victim->is_busy() || ! living(victim))
        {
                me->set_temp("guarding", 0);
                if (! victim->is_fighting(me)) victim->fight_ob(me);
                do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);

                if (me->is_fighting(victim) && victim->is_fighting(me))
                {
                        if (double_attack)
                        {
                                me->set_temp("action_flag", 1);
                                do_attack(me, victim, my_temp["weapon"], TYPE_QUICK);
                                me->set_temp("action_flag", 0);
                        } else // ��������
                        if (objectp(weapon) &&
                            objectp(weapon2 = me->query_temp("secondary_weapon")) &&
                            sizeof(me->query_skill_prepare()) > 1 &&
                            me->query_skill_prepared(weapon->query("skill_type")) &&
                            me->query_skill_prepared(weapon2->query("skill_type")))
                        {
                                me->set_temp("secondly_weapon", 1);
                                do_attack(me, victim, weapon2, TYPE_QUICK);
                                me->delete_temp("secondly_weapon");
                        }
                } else // ���ֱ���
                if ((random(me->query_int()) > 50 || random(10) < 3) && victim->is_fighting(me))
                {
                        me->set_temp("secondly_weapon", 1);
                        do_attack(me, victim, me->query_temp("secondary_weapon"), TYPE_QUICK);
                        me->delete_temp("secondly_weapon");
                }

                if (living(victim))
                {
                        if (stringp(askill))
                        {
                                me->set_temp("action_flag", 1);
                                SKILL_D(askill)->do_interlink(me, victim);
                                me->set_temp("action_flag", 0);
                        }
                }
        // Else, see if we are brave enough to make an aggressive action.
        } else
        if (me->query_str() > random(victim->query_str() * 3 / 4))
        {
                me->set_temp("guarding", 0);
                if (! victim->is_fighting(me))
                        victim->fight_ob(me);
                do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);

                if (me->is_fighting(victim) && victim->is_fighting(me))
                {
                        if (double_attack)
                        {
                                me->set_temp("action_flag", 1);
                                do_attack(me, victim, my_temp["weapon"], TYPE_REGULAR);
                                me->set_temp("action_flag", 0);
                        } else // ��������
                        if (objectp(weapon) &&
                            objectp(weapon2 = me->query_temp("secondary_weapon")) &&
                            sizeof(me->query_skill_prepare()) > 1 &&
                            me->query_skill_prepared(weapon->query("skill_type")) &&
                            me->query_skill_prepared(weapon2->query("skill_type")))
                        {
                                me->set_temp("secondly_weapon", 1);
                                do_attack(me, victim, weapon2, TYPE_REGULAR);
                                me->delete_temp("secondly_weapon");
                        }
                } else // ���ֱ���
                if ((random(me->query_int()) > 50 || random(10) < 3) && victim->is_fighting(me))
                {
                        me->set_temp("secondly_weapon", 1);
                        do_attack(me, victim, me->query_temp("secondary_weapon"), TYPE_REGULAR);
                        me->delete_temp("secondly_weapon");
                }

                if (stringp(askill))
                {
                        me->set_temp("action_flag", 1);
                        SKILL_D(askill)->do_interlink(me, victim);
                        me->set_temp("action_flag", 0);
                }

        // Else, we just start guarding.
        } else
        if (! me->query_temp("guarding"))
        {
                me->set_temp("guarding", 1);
                message_combatd( guard_msg[random(sizeof(guard_msg))], me, victim, "");
                return;
        } else return;
}

//      auto_fight()
//
//      This function is to start an automatically fight. Currently this is
//      used in "aggressive", "vendetta", "hatred", "berserk" fight.
//
void auto_fight(object me, object obj, string type)
{
        // Don't let NPC autofight NPC.
        if (! userp(me) && ! userp(obj)) return;

        if (me->query_temp("owner") == obj ||
            obj->quety_temp("owner") == me)
                return;

        // Because most of the cases that we cannot start a fight cannot be checked
        // before we really call the kill_ob(), so we just make sure we have no
        // aggressive callout wating here.
        if (me->query_temp("looking_for_trouble")) return;
        me->set_temp("looking_for_trouble", 1);

        // This call_out gives victim a chance to slip trough the fierce guys.
        call_out("start_" + type, 0, me, obj);
}

void start_berserk(object me, object obj)
{
        int shen;

        // Are we still exist( not becoming a corpse )?
        if (! me || ! obj || ! living(me)) return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me)!=environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        shen = 0 - (int)me->query("shen");
        message_vision("$N��һ������������ɨ�����ڳ���ÿһ���ˡ�\n", me);

        if (! userp(me) || (int)me->query("neili") > (random(shen) + shen)/10 )
                return;

        /*
        if (shen > (int)me->query("score") && ! wizardp(obj))
        {
                message_vision("$N����$n�ȵ���" + RANK_D->query_self_rude(me)
                        + "����ʵ�ںܲ�˳�ۣ�ȥ���ɡ�\n", me, obj);
                me->kill_ob(obj);
        } else
        */
        {
                message_vision("$N����$n�ȵ���ι��" + RANK_D->query_rude(obj) +
                               "��" + RANK_D->query_self_rude(me) +
                               "�������˴�ܣ����������ְɣ�\n",
                               me, obj);
                me->fight_ob(obj);
        }
}

void start_hatred(object me, object obj)
{
        if (! me || ! obj || ! living(me))
                return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me) != environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        if (me->query_temp("owner") == obj->query("id") ||
            obj->query_temp("owner") == me->query("id"))
                return;

        // We found our hatred! Charge!
        if ( me->query("race") == "����" )
                message_vision( catch_hunt_human_msg[random(sizeof(catch_hunt_human_msg))], me, obj);
        if ( me->query("race") == "Ұ��" )
                message_vision( catch_hunt_beast_msg[random(sizeof(catch_hunt_beast_msg))], me, obj);
        if ( me->query("race") == "����" )
                message_vision( catch_hunt_bird_msg[random(sizeof(catch_hunt_bird_msg))], me, obj);
        me->want_kill(obj);
        me->kill_ob(obj);

        if (! playerp(me) && me->is_busy() && ! intp(me->query_busy()))
                me->interrupt_me(me);
}

void start_vendetta(object me, object obj)
{
        if (! me || ! obj || ! living(me))
                return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me) != environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        message_vision(HIC"$Nŭ���������������$n��ɱ���ۣ�\n"NOR, me, obj);
        tell_object(obj, HIR "������" + me->name() + "��ɱ���㣡\n" NOR);
        // We found our vendetta opponent! Charge!
        me->want_kill(obj);
        me->kill_ob(obj);
}

void start_aggressive(object me, object obj)
{
        if (! me || ! obj || ! living(me)) return;

        me->set_temp("looking_for_trouble", 0);

        if (me->is_fighting(obj) ||
            environment(me) != environment(obj) ||
            environment(me)->query("no_fight"))
                return;

        // We got a nice victim! Kill him/her/it!!!
        me->want_kill(obj);
        me->kill_ob(obj);
}

int player_escape(object killer, object ob)
{
        object iob;
        string msg;

        if (! objectp(ob))
                return 0;

        // �����ô��
        if (! playerp(ob))
                return 0;

        if ((int)ob->query("combat/which_day") == time() / 86400 &&
            (int)ob->query("total_count") > 0)
                return 0;

        // ����ε��ˣ��쿴�Ƿ��Ǳ�����������ε�
        if (! killer) killer = ob->query_defeated_by();
        if (! killer || ! playerp(killer) ||
            ! killer->is_want_kill(ob->query("id")))
                return 0;

#ifdef LONELY_IMPROVED
        if (ob->query("no_newbie") ||
            ob->query("combat/WPK") ||
            (ob->query("age") >= 20 &&
            count_ge(ob->query("combat_exp"), 20000000)))
#else
        if (ob->query("no_newbie") ||
            ob->query("combat/WPK") ||
            (ob->query("age") >= 20 &&
            ob->query("combat_exp") >= 20000000))
#endif
                return 0;

        switch (random(7))
        {
        case 0:
                msg = "ͻȻֻ������һ����̾��һ�����ᰴ����$N���һ��������"
                      "���˼����ֻ��̧��һ�񡣴�æ֮��ֻ�¶��ֹ�����������"
                      "���мܣ���æ���Ծ����ȴ�����˲���׷����ֻ��һ������"
                      "��$n��ת��ƮȻ��ȥ��������Ȼ��\n";
                break;

        case 1:
                msg = "$N��$n���ڵأ���������һ��Ц����δ���£�ֻ��������"
                      "��һ������Ȼ���Ʒ�Ϯ�壬$N�ٸк���������������Ϣ����"
                      "æ�м�æ�˺󣬴������ȽŸ���ȴ��$n������Ӱ���١�\n";
                break;

        case 2:
                msg = "һ�˺�Ȼ�������ȵ��������д���������������޴�������"
                      "��֮�������ߣ���˵��һ�ƻ�����$N�����мܣ�һ��֮�¼�"
                      "����Ѫ��ֻ��������������$n����Ц������ת����ȥ��$N��"
                      "��֮�£���Ȼ˵����һ�仰����\n";
                break;

        case 3:
                msg = "ͻȻһ�˺ȵ�������������ֻ��һ����Ӱ�ӵ�������һ�Ž�"
                      "$N���˸���ͷ����������$n�������$N����������������δ"
                      "����������������������ȥ�ɣ���$N������������ס��Ϣ"
                      "���������Ŀ�������ȥ�ˡ�\n";
                break;

        case 4:
                msg = "$N��ǰһ������Ȼ������ǰ�Ѷ������ˣ�һ��һ�ݣ�һϲһ"
                      "ŭ�����ɰ�����񼡣һ����������һ��ͭ�ƣ�Ц��������λ" +
                      RANK_D->quert_respect(killer)+ "�����淣��ͭ�������¿�"
                      "�ã���$N���˴��һ������ֻ��һ�������ﻹ�Ҵ��仰��"
                      "���������俴�˹�����Ŀ����磬$NڨڨЦ��������Ŀ����"
                      "�˴���$n��ң��ȥ��\n";

        case 5:
                msg = "ǡ�ڴ�ʱ������һ����·����ֻ����΢һ�ü���ȵ�����أ"
                      "��" + RANK_D->query_rude(killer)+ "��������������$N��"
                      "ŭ���������Ǻ��ˣ�������ţ������ߴ�ŭ��һ�����䣬$N"
                      "����ֻ��һ�񣬡����ࡱһ��˫���������У����а�ߡ���"
                      "��ɭȻ�������������͵�ľ������Ҳ�����в�����������"
                      "������ʱ$N��Ϣ������䳡�滰Ҳ˵��������ֻ���ۿ�$n"
                      "����ľ����������ȥ��\n";
                break;

        default:
                msg = "������������һ��Ц��һ�˵��������֣��벻��������ʮ"
                      "�겻����������Щ���ָ���ȴ��Խ��Խ�������ˣ�����һ��"
                      "���������ǣ��������Ʒ����������ڣ����޾�ͷ����$N��"
                      "�ô��乶��£������ķ�ȴ��һ�ˣ�ת��ͷ�������Ǵ��"
                      "һ������$nҲ�����ˡ�\n";
                break;
        }

        if ((environment(killer) == environment(ob)) &&
            killer->is_fighting(ob))
        {
                msg = replace_string(msg, "$n", ob->name());
                message_sort(msg, killer);
        } else
        {
                msg = "����һ����·��������" + ob->name() + "�ε��ڵأ�̾��"
                      "����������������ˡ�\n";
                message("vision", msg, environment(ob));
        }

        // �����ϴ��Ķ�������
        /*
        foreach (iob in all_inventory(ob))
                if (! iob->query("money_id") &&
                    ! iob->query("equipped"))
                        iob->move(environment(ob));
        */

        // ��ʼ����ҵ�״̬
        ob->clear_condition();
        ob->remove_killer(killer);
        killer->remove_killer(ob);

        // ͨ����������
        if (! killer->query_condition("killer"))
        {
                msg = "��˵�ٸ����º������飬������������" +
                             killer->name(1) + "��";
                killer->apply_condition("killer", 500);
        } else
        {
                msg = "��˵�ٸ��ӽ�׽���۴����˵ı�ͽ" +
                             killer->name(1) + "��";
                killer->apply_condition("killer", 800 +
                        (int)killer->query_condition("killer"));
        }
        CHANNEL_D->do_channel(this_object(), "rumor", msg);

        ob->move("/d/xiakedao/shiroom24");
        ob->set("startroom", "/d/xiakedao/shiroom24");
        ob->revive();
        ob->set("eff_qi", ob->query("max_qi"));
        ob->set("eff_jing", ob->query("max_jing"));
        ob->set("qi", 0);
        ob->set("jing", 0);

        if (intp(ob->query_busy()))
                ob->start_busy(30);

        tell_object(ob, "������������������λ�������ھ���������\n"
                    HIG "�����������㣺" + RANK_D->query_respect(ob) +
                        "����Ҫ���뵺��������˵һ��(ask long about �뵺)��\n" NOR);

        return 1;
}

// This function is to announce the special events of the combat.
// This should be moved to another daemon in the future.
void announce(object ob, string event)
{
    if (ob->query("race") == "����")
    {
        switch (event)
        {
        case "dead":
                message_vision(NOR "\n$N���ڵ��������˼��£���һ�죬�����������"
                               HIR "��Ѫ" NOR "�����ˣ�\n\n" NOR, ob);
                if (environment(ob) && userp(environment(ob)) && living(environment(ob)))
                        tell_object(environment(ob),NOR "\n" + ob->name() + "�����˼��£���һ�죬�����������"
                               HIR "��Ѫ" NOR "�����ˣ�\n\n" NOR);
                break;

        case "unconcious":
                message_vision("\n$N����һ�����ȣ����ڵ���һ��Ҳ�����ˡ�\n\n", ob);
                player_escape(0, ob);
                break;

        case "revive":
                message_vision("\n$N���������۾��������˹�����\n\n", ob);
                break;
        }
    } else
    {
        switch(event)
        {
        case "dead":
                message_vision(ob->query("dead_message"), ob);
                break;
        case "unconcious":
                message_vision(ob->query("unconcious_message"), ob);
                break;
        case "revive":
                message_vision(ob->query("revive_message"), ob);
                break;
        }
    }
}

// called when winner hit the victim to unconcious
void winner_reward(object winner, object victim)
{
        object owner;
        int temp;
        int td;
        mapping today;

        owner = winner->query_temp("owner");
        if (objectp(owner))
                winner = owner;

        winner->defeated_enemy(victim);

        if (! playerp(winner) || wizardp(victim) && 0)
                return;

        if (! winner->is_want_kill(victim->query("id")))
                // only if I want kill ob, I will record it.
                return;

        winner->add("combat/DPS", 1);
        if (victim->is_not_bad())  winner->add("combat/DPS_NOTBAD", 1);
        if (victim->is_not_good()) winner->add("combat/DPS_NOTGOOD", 1);
        if (victim->is_bad())      winner->add("combat/DPS_BAD", 1);
        if (victim->is_good())     winner->add("combat/DPS_GOOD", 1);

        if (victim->query_condition("killer"))
                return;

        log_file("static/killrecord",
                 sprintf("%s %s defeat %s\n",
                         log_time(), log_id(winner), log_id(victim)));

        td = time() / 86400;
        today = winner->query("combat/today");
        if (! mapp(today) || today["which_day"] != td)
        {
                today = ([ "which_day" : td,
                           "total_count" : 1,
                           victim->query("id") : 1, ]);
        } else
        {
                // count how many times that winner hit the victim to unconcious
                temp = ++today[victim->query("id")];
                if (victim->query("newbie"))
                {
                        today[victim->query("id")] = temp + 1;
                        temp = today[victim->query("id")];
                }

                if (temp == query("pk_perman"))
                {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n�������Ѿ�����" +
                                    victim->name() + chinese_number(temp) +
                                    "���ˣ�������"
                                    "��ɣ������鷳��Ҫ�������ˡ�\n" NOR);
                } else
                if (temp > query("pk_perman"))
                        // too many times
                        winner->set("combat/need_punish", "���˱���̫�����������д�����");

                // count how many users that winner hit to unconcious
                temp = ++today["total_count"];
                if (victim->query("newbie"))
                {
                        today["total_count"] = temp + 5;
                        temp = today["total_count"];
                }

                if (temp == query("pk_perday"))
                {
                        // reach limit
                        tell_object(winner, BLINK HIR "\n�������Ѿ�����" +
                                    chinese_number(temp) + "������ˣ�������"
                                    "��ɣ������鷳��Ҫ�������ˡ�\n" NOR);
                } else
                if (temp > query("pk_perday"))
                        // too many users
                        winner->set("combat/need_punish", "ɥ��������������¾�����޿�ˡ��");
        }
        winner->set("combat/today", today);
}

void family_kill(object killer, object victim)
{
        // ����Ϊ���ɹ�������
        if (! objectp(killer) || ! userp(killer) ||
            ! objectp(victim) ||
            ! stringp(killer->query("family/family_name")))
                return;

        if (killer->query("family/family_name") !=
            victim->query("family/family_name"))
                return;

        // quest ����
        if (stringp(killer->query("quest/id")) &&
            killer->query("quest/id") == victim->query("id"))
                return;

        // free ����
        if (! userp(victim) && victim->query_temp("quest_ob"))
                return;

        // ultra ����
        if (! userp(victim) && stringp(victim->query_temp("quester")) &&
            victim->query_temp("quester") == killer->query("id"))
                return;

        // ultra ����
        if (! userp(victim) && (killer->query("quest_dg") ||
            killer->query("quest_hs") || killer->query("quest_sn") ||
            killer->query("quest_kh")))
                return;

        if (userp(victim))
        {
                killer->add("family/gongji", -500);
                tell_object(killer, sprintf("������к�ͬ�ŵ��ӣ�ʦ�Ź����½� %d �㡣\n", 500));
        }
        else
        {
                if (killer->is_apprentice_of(victim))
                {
                        killer->add("family/gongji", -1000);
                        tell_object(killer,sprintf("������ʦ�������Ϊ��ʦ�Ź����½� %d �㡣\n", 1000));
                }
                else
                if (killer->query("family/generation") >
                    victim->query("family/generation"))
                {
                        killer->add("family/gongji", -600);
                        tell_object(killer,sprintf("������к�ͬ���𳤣�ʦ�Ź����½� %d �㡣\n", 600));
                }
                else
                {
                        killer->add("family/gongji", -300);
                        tell_object(killer,sprintf("������к�ͬ�ţ�ʦ�Ź����½� %d �㡣\n", 300));
                }
        }
        if (killer->query("family/gongji") < 0)
                killer->set("family/gongji", 0);
}

void killer_reward(object killer, object victim)
{
        object owner, charm;
        string vmark;
        string msg = "Ī�����������";
        string follow_msg = 0;
        object weapon;
        mapping actions;
        int shen_delta,exp_damage;
        mixed exp_lost;
        mapping ks, vs, kcombat;
        int no_loss = 0;

        if (! objectp(victim))
                return;

        if (objectp(killer))
        {
                owner = killer->query_temp("owner");
                if (objectp(owner))
                        killer = owner;
        }

        // This while is only to enable "break"
        vs = victim->query_entire_dbase();
        while (1)
        {
                if (! objectp(killer))
                        break;

                // call the killer's override function
                killer->killed_enemy(victim);

                if (! objectp(killer) || ! playerp(killer))
                        break;

                // assure the killer's dbase
                ks = killer->query_entire_dbase();
                if (! mapp(kcombat = ks["combat"]))
                {
                        kcombat = ([ ]);
                        ks["combat"] = kcombat;
                }

                // adjust the "shen" & "experience" of the killer
#ifdef LONELY_IMPROVED
                if (count_lt(count_div(ks["combat_exp"], 2), vs["combat_exp"]))
                {
                        if (count_ge(ks["combat_exp"], 100000) &&
                            count_ge(ks["combat_exp"], count_div(count_mul(vs["combat_exp"], 2), 3)))
#else
                if (ks["combat_exp"]/2 < vs["combat_exp"])
                {
                        if (ks["combat_exp"] >= 100000 &&
                            ks["combat_exp"] >= vs["combat_exp"] * 2 / 3)
#endif
                        {
                                // adjust experience
                                if (! ks["experience"])
                                        ks["experience"] = 0;
                                killer->improve_experience(1 + random(5));
                        }

                        // adjust shen
                        shen_delta = -vs["shen"] / 2;
                        if (shen_delta > 100)
                        {
                                // ������У����õ�����
                                shen_delta = (shen_delta - 100) / 3 + 100;

                                if (shen_delta > 200)
                                        shen_delta = (shen_delta - 200) / 3 + 200;

                                if (shen_delta > 300)
                                        shen_delta = (shen_delta - 300) / 3 + 300;
                        } else
                        if (shen_delta < -100)
                        {
                                // ������У����õĸ���
                                shen_delta = (shen_delta + 100) / 3 - 100;

                                if (shen_delta < -200)
                                        shen_delta = (shen_delta + 200) / 3 - 200;

                                if (shen_delta < -300)
                                        shen_delta = (shen_delta + 300) / 3 - 300;
                        }

                        ks["shen"] += shen_delta;
                }

                // weapon get the bonus
                if (weapon = killer->query_temp("weapon") ||
                    weapon = killer->query_temp("armor/hands"))
                        weapon->killer_reward(killer, victim);

                if (weapon = killer->query_temp("secondary_weapon"))
                        weapon->killer_reward(killer, victim);

                if (weapon = killer->query_temp("handing"))
                        weapon->killer_reward(killer, victim);

                // record the user's killing
                if (userp(victim))
                {
                        if (! intp(kcombat["PKS"]))
                                kcombat["PKS"] = 1;
                        else
                                kcombat["PKS"]++;

                        killer->set("pktime", (int)killer->query("mud_age"));

                        // do family action
                        FAMILY_D->family_kill(killer, victim);

                        // do pvp action
                        // PVP_D->pvp_kill(killer, victim);

                        // do league action
                        LEAGUE_D->league_kill(killer, victim);

                        // do bunch action
                        BUNCH_D->bunch_kill(killer, victim);

                        if (victim->query_condition("killer"))
                        {
                                follow_msg = "��˵ɱ������" + victim->name(1) +
                                             "��" + killer->name(1) + "��" +
                                             environment(victim)->short() + HIM
                                             "�͵������ˡ�";
                                break;
                        }

                        if (userp(killer) && killer->in_array() && killer->query_array_status())
                        {
                                follow_msg = sprintf("%s(%s)��%s(%s)����ġ�%s������������\n",
                                                victim->name(1),
                                                capitalize(victim->query("id")),
                                                killer->query_array_master()->name(1),
                                                capitalize(killer->query_array_master()->query("id")),
                                                killer->query_array_name());
                                break;
                        }

                        if (userp(killer) && killer->in_team())
                        {
                                follow_msg = sprintf("%s(%s)��%s(%s)����Ķ�������������\n",
                                                victim->name(1),
                                                capitalize(victim->query("id")),
                                                killer->query_team_leader()->name(1),
                                                capitalize(killer->query_team_leader()->query("id")));
                                break;
                        }

                        if (! killer->is_want_kill(vs["id"]))
                                break;

                        if (! intp(kcombat["WPK"]))
                                kcombat["WPK"] = 1;
                        else
                                kcombat["WPK"]++;

                        if (! killer->query_condition("killer"))
                        {
                                follow_msg = "��˵�ٸ����º������飬����ɱ������" +
                                             killer->name(1) + "��";
                                killer->apply_condition("killer", 500);
                        } else
                        {
                                follow_msg = "��˵�ٸ��ӽ�׽���۷��ذ��ı�ͽ" +
                                             killer->name(1) + "��";
                                killer->apply_condition("killer", 800 +
                                        (int)killer->query_condition("killer"));
                        }

                        // assure data of kcombat
                        if (! intp(kcombat["WPK_NOTBAD"])) kcombat["WPK_NOTBAD"] = 0;
                        if (! intp(kcombat["WPK_NOTGOOD"])) kcombat["WPK_NOTGOOD"] = 0;
                        if (! intp(kcombat["WPK_GOOD"])) kcombat["WPK_GOOD"] = 0;
                        if (! intp(kcombat["WPK_BAD"])) kcombat["WPK_BAD"] = 0;

                        // record the combat info.
                        if (victim->is_not_bad())  kcombat["WPK_NOTBAD"]++;
                        if (victim->is_not_good()) kcombat["WPK_NOTGOOD"]++;
                        if (victim->is_good())     kcombat["WPK_GOOD"]++;
                        if (victim->is_bad())      kcombat["WPK_BAD"]++;
                        break;
                } else
                {
                        if (mapp(victim->query("killer_reward")))
                                EQUIPMENT_D->killer_reward(killer, victim, victim->query("killer_reward"));
                }

                if (vs["can_speak"])
                        if (! intp(kcombat["MKS"]))
                                kcombat["MKS"] = 1;
                        else
                                kcombat["MKS"]++;

                family_kill(killer, victim);
                quest_kill(killer, victim);

                break;
        }

        // die penalty & message of victim
        if (playerp(victim))
        {
                // clear punish info.
                victim->delete("combat/need_punish");

                // remove vendetta
                map_delete(vs, "vendetta");

                // ��tianshi charm�Ҳ���ͨ����������ʧ
                if (objectp(charm = present("tianshi charm", victim)) /*&&
                    ! victim->query_condition("killer")*/)
                        no_loss = 1;

                // �����ɱ�����Լ��ܵ�������������ʧ
                else
                if (objectp(killer) && playerp(killer) &&
                    (victim->query("age") < 20 ||
#ifdef LONELY_IMPROVED
                    count_lt(victim->query("combat_exp"), 20000000)) &&
#else
                    victim->query("combat_exp") < 20000000) &&
#endif
                    ! victim->query("no_newbie") &&
                    ! victim->query("combat/WPK"))
                        no_loss = 1;

                // �����ɱ����ɱ�����С��20�����С��2000����������ʧ
                else
                if (objectp(killer) && playerp(killer) &&
                    (killer->query("age") < 20 ||
#ifdef LONELY_IMPROVED
                    count_lt(killer->query("combat_exp"), 20000000)))
#else
                    killer->query("combat_exp") < 20000000))
#endif
                        no_loss = 1;

                // clear all condition
                victim->clear_condition();

                if (! no_loss)
                {
                        // adjust shen
                        vs["shen"] -= vs["shen"] / 10;
                        if (vs["max_neili"] >= 20)
                                vs["max_neili"] -= 20;
                        else
                                vs["max_neili"] = 0;

                        // adjust combat exp.
                        if (!mapp(vs["combat"])) exp_damage = 1;
                        else exp_damage = vs["combat"]["WPK"];
                        if (exp_damage < 1) exp_damage = 1;
                        if (exp_damage > 5) exp_damage = 5;
#ifdef LONELY_IMPROVED
                        exp_lost = count_div(count_mul(vs["combat_exp"], exp_damage), 100);
                        vs["combat_exp"] = count_sub(vs["combat_exp"], exp_lost);
#else
                        exp_lost = vs["combat_exp"] * exp_damage / 100;
                        vs["combat_exp"] -= exp_lost;
#endif

#ifdef LONELY_IMPROVED
                        if (killer)
                                killer->set("combat/WPKEXP", count_add(killer->query("combat/WPKEXP"), exp_lost));
                        victim->set("combat/dieexp", count_add(victim->query("combat/dieexp"), exp_lost));
#else
                        if (killer)
                                killer->add("combat/WPKEXP",exp_lost);
                        victim->add("combat/dieexp",exp_lost);
#endif
                        victim->set("combat/last_dieexp", exp_lost);

                        // adjust weiwang
                        vs["weiwang"] -= vs["weiwang"] / 10;

                        // adjust score
                        vs["score"] -= vs["score"] / 10;


                        // lost half of potential
#ifdef LONELY_IMPROVED
                        if (count_gt(vs["potential"], vs["learned_points"]))
                                vs["potential"] = count_sub(vs["potential"], count_div(count_sub(vs["potential"], vs["learned_points"]), 2));
#else
                        if (vs["potential"] > vs["learned_points"])
                                vs["potential"] += (vs["learned_points"] - vs["potential"]) / 2;
#endif
                        // lost half of experience
                        if (count_gt(vs["experience"], vs["learned_experience"]))
                                vs["experience"] = count_sub(vs["experience"], count_div(count_sub(vs["experience"], vs["learned_experience"]), 2));

                        victim->skill_death_penalty();
                }

                if (objectp(charm) && no_loss)
                        destruct(charm);

                // generate message of die reason
                if (objectp(killer) && killer->is_character())
                {
                        msg = "��" + filter_color(killer->name(1));

                        if( killer->query("race") == "Ұ��"
                        ||  killer->query("race") == "����"
                        ||  killer->query("race") == "����"
                        ||  killer->query("race") == "����" )      msg += "ҧ����";
                        else if( killer->query("race") == "����" ) msg += "������";
                        else if( killer->query("race") == "����" ) msg += "������";
                        else
                        {
                                actions = killer->query_action();
                                switch (mapp(actions) ? actions["damage_type"] : "ɱ��") {
                                case "����":
                                case "����":
                                        msg+="������";
                                        break;
                                case "����":
                                        msg+="������";
                                        break;
                                case "����":
                                case "����":
                                        msg+="������";
                                        break;
                                case "����":
                                        msg+="������";
                                        break;
                                default:
                                        msg+="ɱ����";
                                }
                        }
                }

                if (stringp(victim->query_temp("die_reason")))
                        msg = filter_color(victim->query_temp("die_reason"));

                victim->delete_temp("die_reason");
                CHANNEL_D->do_channel(this_object(), "rumor",
                        sprintf("��˵%s" HIM + msg + "��", victim->name(1)));

                // show the follow msg after victim die
                if (follow_msg)
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                              follow_msg);

                victim->set("combat/last_die", filter_color(msg));
                if (objectp(killer) && playerp(killer) && playerp(victim))
                {
                        string cname;
                        object couple;

                        log_file("static/killrecord",
                                 sprintf("%s %s killed %s\n",
                                         log_time(),
                                         log_id(killer), log_id(victim)));

                        killer->remove_killer(victim);

                        // check sadly
                        cname = victim->query("couple/couple_id");
                        if (cname &&
                            victim->query("gender") == "Ů��" &&
#ifdef LONELY_IMPROVED
                            count_ge(victim->query("combat_exp"), 970000) &&
#else
                            victim->query("combat_exp") >= 970000 &&
#endif
                            objectp(couple = find_player(cname)) &&
                            couple != killer &&
                            couple->query("couple/married") <= 1 &&
                            victim->query("couple/married") <= 1)
                        {
                                couple->add("static/sadly", 1);
                                tell_object(couple, "�������������" +
                                            killer->name(1) + "������" +
                                            "����е���һ������İ��ˡ�\n");
                        }
                }
        }

        if (stringp(vmark = victim->query("vendetta_mark")) && objectp(killer))
                killer->add("vendetta/" + vmark, 1);
}

// me hit victim with poison in ob
void hit_with_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if (! mapp(p = ob->query_temp("daub/poison")))
                return;

        if (! stringp(poison_type = ob->query_temp("daub/poison_type")))
                return;

        if (! p["remain"])
                return;

        // affect parameter
        ap = allocate_mapping(4);
        if (ob == me)
                ap["level"] = p["level"] * 9 / 10 + 1;
        else
                ap["level"] = p["level"] * 8 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if (p["remain"] > p["level"])
        {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else
        {
                // the poison has run out
                ob->delete_temp("daub");
        }

        msg = HIG "ͻȻ$n�������˵ĵط���һЩ����";
        if (p["id"] == victim->query("id"))
        {
                if (! victim->query_temp("has_announce/defense1"))
                {
                        victim->set_temp("has_announce/defense1", 1);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "��\n" NOR HIC "$nĬһ�˹�����Ц�������������" +
                               RANK_D->query_rude(me) + "����Ȼ������ǰ��Ū" +
                               RANK_D->query_self_rude(victim) +
                               "��ҩ�����Ǽ���������������ˣ���\n" NOR;
                } else
                        msg += "������$n��û�����⡣\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < victim->query_skill("poison", 1))
        {
                if (! victim->query_temp("has_announce/defense2"))
                {
                        victim->set_temp("has_announce/defense2", 1);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "��\n" NOR HIC "$n�������Σ���Ȼ��Ц����"
                               "������֮�飬Ҳ�Ź⻪����\n" NOR;
                } else
                        msg += "������$n��Ȼ��û�а����������ϡ�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < victim->query_skill("force") / 2)
        {
                if (! victim->query_temp("has_announce/defense3"))
                {
                        victim->set_temp("has_announce/defense3", 1);
                        victim->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", victim :), victim), 15);
                        msg += "��\n" NOR HIC "$n����һ������������Ц�������üһ��Ȼ" +
                               (ob == me ? "�����ϴ㶾" : "ʹ�ô㶾����") +
                               "������Щ�����ĵ��ֶ�Ҳ�ҵ�����ǰ��Ū����\n" NOR;
                } else
                        msg += "������$n�������ƺ����޴󰭡�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        victim->affect_by(poison_type, ap);

        msg += "��������ж��ˡ�\n" NOR;
        if (p["level"] < victim->query_skill("force"))
        {
                msg += HIG "$n������һ�˿�������Ŀ���أ����еĹ��ƶ�Ȼһ����\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$n�ƺ�һ�������ƶٻ�����������ʹ�ࡣ\n" NOR;
        if (! victim->is_busy())
                victim->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

// me hit victim, but poison by victim in ob
void hit_poison(object me, object victim, object ob)
{
        mapping p, ap;
        string msg;
        string poison_type;

        if (! mapp(p = ob->query_temp("daub/poison")))
                return;

        if (! stringp(poison_type = ob->query_temp("daub/poison_type")))
                return;

        if (! p["remain"])
                return;

        if (me->query_temp("armor/hands"))
                return;

        // affect parameter
        ap = allocate_mapping(4);
        ap["level"]    = p["level"] * 7 / 10 + 1;

        ap["id"]       = p["id"];
        ap["name"]     = p["name"];
        ap["duration"] = 1;

        if (p["remain"] > p["level"])
        {
                // decrase the remain poison
                p["remain"] -= p["level"];
        } else
        {
                // the poison has run out
                ob->delete_temp("daub");
        }

        msg = HIG "ͻȻ$N���û�����Щ����";
        if (p["id"] == me->query("id"))
        {
                if (! me->query_temp("has_announce/defense1"))
                {
                        me->set_temp("has_announce/defense1", 1);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "��\n" NOR HIC "$NĬһ�˹�����Ц�������������" +
                               RANK_D->query_rude(victim) + "����Ȼ������ǰ��Ū" +
                               RANK_D->query_self_rude(victim) +
                               "�Ķ�ҩ�������·��ϵĶ�ҩ�������ң���\n" NOR;
                } else
                        msg += "������$N��û�����⡣\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < me->query_skill("poison", 1))
        {
                if (! me->query_temp("has_announce/defense2"))
                {
                        me->set_temp("has_announce/defense2", 1);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "��\n" NOR HIC "$N�������Σ���Ȼ��Ц����������֮�飬Ҳ"
                               "�Ź⻪�����������ϴ㶾�Ҿ������ˣ���\n" NOR;
                } else
                        msg += "������$N��Ȼ��û�а����������ϡ�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        if (p["level"] < me->query_skill("force") / 2)
        {
                if (! me->query_temp("has_announce/defense3"))
                {
                        me->set_temp("has_announce/defense3", 1);
                        me->start_call_out(bind((: call_other,
                                __FILE__, "clear_announce", me :), me), 15);
                        msg += "��\n" NOR HIC "$N����һ������������Ц���������Ȼ��������"
                               "�㶾����Щ�����ĵ��ֶ�Ҳ�ҵ�����ǰ��Ū����\n" NOR;
                } else
                        msg += "������$N�������ƺ����޴󰭡�\n" NOR;
                set_ahinfo(msg);
                return;
        }

        me->affect_by(poison_type, ap);

        msg += "��������Щ���\n" NOR;
        if (p["level"] < me->query_skill("force"))
        {
                msg += HIG "$N������һ�˿�������Ŀ���أ����еĹ��ƶ�Ȼһ����\n" NOR;
                set_ahinfo(msg);
                return;
        }

        msg += HIR "$N�Ų�һ�����ԣ����ƶٻ�����ɫ�ѿ�֮����\n" NOR;
        me->start_busy(1 + random(2));
        set_ahinfo(msg);
        return;
}

void clear_announce(object me)
{
        if (! objectp(me))
                return;

        me->delete_temp("has_announce");
}

void quest_kill(object killer, object victim)
{
        mapping quest,b;
        int level,i,exp,pot,score,weiwang,mar,quest_count,all_quest;
        mixed special = 0;
        mixed money = 0;
        object ob,*all_killer,obj;

        //������NPC��������Ľ���
        //�����׷ɱ����
        if (! userp(victim) && victim->query("bunch_quest"))
        {
                quest = victim->query("bunch_quest");
                if (quest["type"] == "׷ɱ" &&
                   ((quest["bunch_type"] == "good" && good_bunch(killer) && killer->query("shen") >= 0) ||
                   (quest["bunch_type"] == "bad" && bad_bunch(killer)  && killer->query("shen") <= 0)) &&
#ifdef LONELY_IMPROVED
                   count_lt(killer->query("combat_exp"), 600000))
#else
                   killer->query("combat_exp") < 600000)
#endif
                {
                        exp = quest["bonus"];
                        exp += 100;
                        exp += random(exp/2);
                        pot = exp/(2 + random(2));
                        score = 25 + random(20);
                        weiwang = 25 + random(20);

                        b = ([ "exp" : exp,
                               "pot" : pot,
                               "score" : score,
                               "weiwang" : weiwang,
                               "prompt": "��׷ɱ" + victim->name() + HIG "�Ĺ����У���������"
                        ]);

                        QUEST_D->delay_bonus(killer, b);
                }
                return;
        }

        //����ǲ����������
        if (killer->query("bunch_quest") &&
          killer->query("bunch_quest")["type"] == "�������" &&
          killer->query("bunch_quest")["ob"] == victim)
        {
                quest = killer->query("bunch_quest");

                exp = quest["bonus"];
                exp += 120;
                exp += random(exp/2);
                pot = exp/(2 + random(2));
                score = 25 + random(20);
                weiwang = 25 + random(20);

                b = ([ "exp" : exp,
                       "pot" : pot,
                       "score" : score,
                       "weiwang" : weiwang,
                       "prompt": "�ڲ�����������" + victim->name() + HIG "�Ĺ����У���������"
                ]);

                QUEST_D->delay_bonus(killer, b);

                killer->delete("bunch_quest");
                killer->add_temp("finish_bunch_times",1);
                return;
        }

        //�������������Ľ���
        if (! userp(victim) && victim->query("my_type"))
        {
                /*
                if (objectp(victim->query_defeated_by()) &&
                    userp(victim->query_defeated_by()))
                    killer = victim->query_defeated_by();
                */
                switch(victim->query("my_type"))
                {
                case "�������":
                        GROUP_QUEST_D->be_killed(1);
                        GROUP_QUEST_D->add_killer(killer);
                        exp = victim->query("bonus");
                        pot = exp;
                        score = random(exp);
                        weiwang = exp + random(exp);
                        mar = random(exp/2);
                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                        "weiwang" : weiwang, "score" : score ]), 1);
                        if (GROUP_QUEST_D->query_enemy() == 0)
                        {
                                all_killer = GROUP_QUEST_D->query_killer();
                                exp = 2000;
                                pot = 2000;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if (! objectp(ob) || ! userp(ob))
                                                continue;

                                        tell_object(ob, HIW "�������ֵĵ��˶��������ˣ�������Ҳ������ս����" +
                                                            "���������Ҳһ�����ʤ����ʵ��\n" NOR);
                                            QUEST_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                           "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                case "����":
                        GROUP_QUEST_D->be_killed(1);
                        if (victim->query("����") == killer->query("family/family_name"))
                        {
                                GROUP_QUEST_D->add_killer(killer);
                                exp = victim->query("bonus");
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                                QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                "weiwang" : weiwang, "score" : score, "gongxian" : score ]), 1);
                        }
                        if (GROUP_QUEST_D->query_enemy() == 0)
                        {
                                all_killer = GROUP_QUEST_D->query_killer();
                                exp = 2000;
                                pot = 2000;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if (! objectp(ob) || ! userp(ob))
                                                continue;

                                        tell_object(ob, HIW "�������ֵĵ��˶��������ˣ�������Ҳ������ս����" +
                                                            "���������Ҳһ�����ʤ����ʵ��\n" NOR);
                                        QUEST_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                        "weiwang" : weiwang, "score" : score, "gongxian" : score ]), 1);
                                }
                        }
                        break;
                case "����":
                        GROUP_QUEST_D->be_killed(1);
                        if (victim->query("����") == killer->query("bunch/bunch_name"))
                        {
                                GROUP_QUEST_D->add_killer(killer);
                                exp = victim->query("bonus");
                                pot = exp;
                                score = random(exp);
                                weiwang = exp + random(exp);
                                mar = random(exp/2);
                                QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                   "weiwang" : weiwang, "score" : score ]), 1);
                        }
                        if (GROUP_QUEST_D->query_enemy() == 0)
                        {
                                all_killer = GROUP_QUEST_D->query_killer();
                                exp = 2000;
                                pot = 2000;
                                score = 1000;
                                weiwang = 3000;
                                mar = 500;
                                foreach (ob in all_killer)
                                {
                                        if (! objectp(ob) || ! userp(ob))
                                                continue;

                                        tell_object(ob, HIW "�������ֵĵ��˶��������ˣ�������Ҳ������ս����" +
                                                            "���������Ҳһ�����ʤ����ʵ��\n" NOR);
                                        QUEST_D->bonus(ob, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                                        "weiwang" : weiwang, "score" : score ]), 1);
                                }
                        }
                        break;
                }
                return;
        }

        //��������ʦ����Ľ���
        if (mapp(quest = killer->query("quest_kh")) && quest["desc"] == "��")    //��������
        {
                if ((quest["name"] == "����" && victim->query("gender") == "����") ||
                (quest["name"] == "Ů��" && victim->query("gender") == "Ů��") ||
                (quest["type"] == "�ص�" && (domain_file(base_name(victim)) == quest["dir"] ||
                   (stringp(victim->query("startroom")) && (domain_file(victim->query("startroom")) == quest["dir"])) ||
                base_dir(victim) == quest["dir1"])))
                {
                        if((quest["time"]-time()) < 0)
                        {
                                killer->delete("quest_kh");
                                return ;
                        }
                        else if(victim->query("race")=="Ұ��") return;
                        else
                        {
                                level = (quest["level"]+1)*(70+random(20));
                                exp = level;
                                pot = exp/(2+random(2));
                                score = random(exp/20);
                                weiwang = random(exp/15);
                                if (killer->query("questkh_times") + 1 > 200)
                                        mar = exp/5 + random(killer->query("questkh_times"));
                                else mar = random(20);
                                if (mar > 5000) mar = 5000;

                                QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                              "weiwang" : weiwang, "score" : score ]), 1);

                                return ;
                        }
                }
        }

        if (mapp(quest = killer->query("quest_dg")))    //�������
        {
                if(quest["type"] == "ɱ" && victim->name(1) == quest["name"])
                {
                        if((i=killer->query("questdg_times")) < 8)
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*105 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if (level == 9)
                                exp += killer->query("questdg_times");
                        /*
                        if (level == 9)
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);

                        if (killer->query("questdg_times") + 1 > 200)
                                mar = exp/5 + random(killer->query("questdg_times"));
                        else mar = random(20);
                        if (mar > 5000) mar = 5000;

                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);

                        killer->add("questdg_times",1);

                        quest_count = killer->query("questdg_times")%500;
                        if (quest_count == 50)
                                special = 1;
                        else if (quest_count == 100)
                               special = "/clone/gift/puti-zi";
                        else if (quest_count == 150)
                               money = 1;
                        else if (quest_count == 200)
                               money = 1;
                        else if (quest_count == 250)
                               money = 1;
                        else if (quest_count == 300)
                               special = "/clone/gift/tianxiang";
                        else if (quest_count == 350)
                               special = "/clone/gift/tianxiang";
                        else if (quest_count == 400)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 450)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 0)
                                special = "/clone/gift/xuanhuang";

                        if (special) QUEST_D->special_bonus(victim, killer, special);
                        if (money) QUEST_D->money_bonus(victim, killer, money);

                        killer->add("total_hatred",-5);
                        if (killer->query("total_hatred") < 0) killer->set("total_hatred",0);
                        killer->delete("quest_dg");

#ifdef DB_SAVE
                        if (MEMBER_D->is_valid_member(killer->query("id")))
                        {
                                if (killer->query("special_skill/sophistry"))
                                {
                                        if (killer->query("questdg_times") >= 4000)
                                                killer->set("questdg_times", 0);
                                } else {          
                                        if (killer->query("questdg_times") >= 2000)
                                                killer->set("questdg_times", 0);
                                }
                        }
                        else
                        {
#endif
                                if (killer->query("questdg_times") >= 1000)
                                        killer->set("questdg_times", 0);
#ifdef DB_SAVE
                        }
#endif
                        all_quest = (int)killer->query("all_quest_dg");
                        if (!all_quest) all_quest = 0;
                        all_quest += 1;
                        if (all_quest == 1000)
                        {
                                obj = new("/clone/enchase/yelgem");
                                tell_object(killer,"�������Ѿ��ۼ������һǧ�����������õ���һ��" +
                                                obj->query("name") + "��Ϊ����\n");
                                if (!obj->move(killer))
                                obj->move(environment(killer));
                                killer->set("all_quest_dg",0);
                        } else killer->set("all_quest_dg",all_quest);
                        return ;
                }
        }

        if (mapp(quest = killer->query("quest_hs")))    //����
        {
                if (quest["type"]=="ɱ"&&quest["name"]==victim->name(1))
                {
                        tell_object(killer,"��ϲ�㣡����Ϊ��������һ����\n");
                        if((i=killer->query("quesths_times")) < 15)
                                i = 15-i;
                        else
                                i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if (level > 4 && i > 5)
                                exp /= 2;
                        if (level == 9)
                                exp += killer->query("quesths_times");
                        /*
                        if (level == 9)
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if (killer->query("quesths_times") + 1 > 200)
                                mar = exp/5 + random(killer->query("quesths_times"));
                        else mar = random(20);
                        if (mar > 5000) mar = 5000;

                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);

                        killer->add("quesths_times",1);
                        quest_count = killer->query("quesths_times")%500;
                        if (quest_count == 50)
                                special = 1;
                        else if (quest_count == 100)
                               special = "/clone/gift/puti-zi";
                        else if (quest_count == 150)
                               money = 1;
                        else if (quest_count == 200)
                               money = 1;
                        else if (quest_count == 250)
                               money = 1;
                        else if (quest_count == 300)
                               special = "/clone/gift/tianxiang";
                        else if (quest_count == 350)
                               special = "/clone/gift/tianxiang";
                        else if (quest_count == 400)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 450)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 0)
                                special = "/clone/gift/xuanhuang";

                        if (special) QUEST_D->special_bonus(victim, killer, special);
                        if (money) QUEST_D->money_bonus(victim, killer, money);

                        killer->add("total_hatred",-5);
                        if (killer->query("total_hatred") < 0) killer->set("total_hatred",0);
                        killer->delete("quest_hs");
                        killer->set_temp("hs_giveup",0);

#ifdef DB_SAVE
                        if (MEMBER_D->is_valid_member(killer->query("id")))
                        {
                                if (killer->query("special_skill/sophistry"))
                                {
                                        if (killer->query("quesths_times") >= 4000)
                                                killer->set("quesths_times", 0);
                                } else {          
                                        if (killer->query("quesths_times") >= 2000)
                                                killer->set("quesths_times", 0);
                                }
                        }
                        else
                        {
#endif
                        if (killer->query("quesths_times") >= 1000)
                                killer->set("quesths_times", 0);
#ifdef DB_SAVE
                        }
#endif

                        all_quest = (int)killer->query("all_quest_hs");
                        if (!all_quest) all_quest = 0;
                        all_quest += 1;
                        if (all_quest == 1000)
                        {
                                obj = new("/clone/enchase/grngem");
                                tell_object(killer,"�������Ѿ��ۼ������һǧ�����������õ���һ��" +
                                                obj->query("name") + "��Ϊ����\n");
                                if (!obj->move(killer))
                                obj->move(environment(killer));
                                killer->set("all_quest_hs",0);
                        } else killer->set("all_quest_hs",all_quest);
                        return ;
                }
        }

        if (mapp(quest = killer->query("quest_sn")))    //�Ϻ�����
        {
                if (quest["type"]=="ɱ"&&quest["name"]==victim->name(1))
                {
                        tell_object(killer,"��ϲ�㣡����Ϊ�Ϻ���������һ����\n");
                        if ((i=killer->query("questsn_times")) < 15)
                                i = 15-i;
                        else i = 1;
                        level = quest["level"]+1;
                        exp = level*80 + quest["bonus"]*3;
                        exp += random(exp/2);
                        exp = exp/i;
                        if (level > 4 && i > 5)
                                exp /= 2;
                        if (level == 9)
                                exp += killer->query("questsn_times");
                        /*
                        if (level == 9)
                                pot = exp*(2+random(2));
                        else
                        */
                                pot = exp/(2+random(2));
                        score = random(exp/20);
                        weiwang = random(exp/15);
                        if (killer->query("questsn_times") + 1 > 200)
                                mar = exp/5 + random(killer->query("questsn_times"));
                        else mar = random(20);
                        if (mar > 5000) mar = 5000;

                        QUEST_D->bonus(killer, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                                            "weiwang" : weiwang, "score" : score ]), 1);

                        killer->add("questsn_times",1);
                        quest_count = killer->query("questsn_times")%500;
                        if (quest_count == 50)
                                special = 1;
                        else if (quest_count == 100)
                               special = "/clone/gift/puti-zi";
                        else if (quest_count == 150)
                               money = 1;
                        else if (quest_count == 200)
                               money = 1;
                        else if (quest_count == 250)
                               money = 1;
                        else if (quest_count == 300)
                               special = "/clone/gift/tianxiang";
                        else if (quest_count == 350)
                               special = "/clone/gift/tianxiang";
                        else if (quest_count == 400)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 450)
                               special = "/clone/gift/jiuzhuan";
                        else if (quest_count == 0)
                                special = "/clone/gift/xuanhuang";

                        if (special) QUEST_D->special_bonus(victim, killer, special);
                        if (money) QUEST_D->money_bonus(victim, killer, money);

                        killer->add("total_hatred",-5);
                        if (killer->query("total_hatred") < 0) killer->set("total_hatred",0);
                        killer->delete("quest_sn");
                        killer->set_temp("sn_giveup",0);

#ifdef DB_SAVE
                        if (MEMBER_D->is_valid_member(killer->query("id")))
                        {
                                if (killer->query("special_skill/sophistry"))
                                {
                                        if (killer->query("questsn_times") >= 4000)
                                                killer->set("questsn_times", 0);
                                } else {          
                                        if (killer->query("questsn_times") >= 2000)
                                                killer->set("questsn_times", 0);
                                }
                        } else
                        {
#endif
                        if (killer->query("questsn_times") >= 1000)
                                killer->set("questsn_times", 0);
#ifdef DB_SAVE
                        }
#endif

                        all_quest = (int)killer->query("all_quest_sn");
                        if (!all_quest) all_quest = 0;
                        all_quest += 1;
                        if (all_quest == 1000)
                        {
                                obj = new("/clone/enchase/blugem");
                                tell_object(killer,"�������Ѿ��ۼ������һǧ�����������õ���һ��" +
                                                obj->query("name") + "��Ϊ����\n");
                                if (!obj->move(killer))
                                obj->move(environment(killer));
                                killer->set("all_quest_sn",0);
                        } else killer->set("all_quest_sn",all_quest);
                        return ;
                }
       }
}