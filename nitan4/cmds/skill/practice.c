// practice.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        string skillname;
        string base_skname;
        int skill, skill_basic, times, i;
        int c, r;
        int difficult, diff, improve;
        int neili_cost, qi_cost;
        int t1, t2, t3, t4;
        int t = time();

        if (! where) return notify_fail("��Ŀǰ��λ�������⣬����������ʦ����ɣ�\n"); 

        if (where->query("pigging"))
                return notify_fail("�㻹��ר�Ĺ����ɣ�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (t == me->query_temp("time/practice"))
                return notify_fail("��ող���ϰ���������Ҫ������ϰ������ָ����ϰ�Ĵ�������\n");

        if (me->is_fighting())
                return notify_fail("���Ѿ���ս�����ˣ�ѧһ��ʵս����ɡ�\n");

        if (environment(me)->query("no_fight") &&
            // (me->query("doing") != "scheme" || this_player(1)))
            me->query("doing") != "scheme")
                return notify_fail("���޷�������ط�������ϰ��\n");

        if (! arg) return (__DIR__"enable")->main(me, arg);

        if ((sscanf(arg, "%s %d", base_skname, times) != 2))
        {
                times = 1;
                base_skname = arg;
        }
            
        c = 200 + me->query_temp("apply/practice_times");
        if (present("practice emblem", me)) 
                c += 800;

        if (me->query("special_skill/wisdom"))
                c += 800;

        if (times < 1 || times > c)
                return notify_fail("��ϰ�����������һ�Σ������ܳ���" + chinese_number(c) + "�Ρ�\n");

        if (! stringp(skillname = me->query_skill_mapped(base_skname)))
                return notify_fail("��ֻ����ϰ�� enable ָ�������⼼�ܡ�\n");

        skill_basic = me->query_skill(base_skname, 1);
        skill = me->query_skill(skillname, 1);
        if (skill < 1)
                return notify_fail("�����û��ѧ������ܰɣ������ȥ��̱��ˡ�\n");

        if (skill_basic < 1)
                return notify_fail("����ⷽ��ļ��ܻ���һ�ϲ�ͨ����ô��ȴӻ���ѧ��\n");

        if (skill_basic <= skill)
                return notify_fail("���" + to_chinese(base_skname) +
                                   "��򲻹������Լ���������" +
                                   to_chinese(skillname) + "��ˮƽ��\n");

        notify_fail("�����ڲ�����ϰ����ܡ�\n");
        if (! SKILL_D(skillname)->valid_learn(me)) return 0;

        if (! XUE_CMD->can_learn(me, skillname))
                return 0;

        notify_fail("��������ϰ" + to_chinese(skillname) + "�����ǲ�û���κν�����\n");
        if (! me->can_improve_skill(skillname))
                return notify_fail("Ҳ����ȱ��ʵս���飬�����ϰ��û��������\n");

        me->set_temp("time/practice", t);

        if (skill >= 2000)
                improve = skill_basic / 4;
        else
        if (skill >= 1000)
                improve = skill_basic / 2;
        else
                improve = skill_basic;
                
        if (intp(r = me->query_temp("apply/practice_effect")))
                improve += improve * r / 100;

        if (me->query("special_skill/wisdom"))
                improve += improve * 50 / 100;

        if (me->query("time_reward/study"))
                improve += improve * 25 / 100;

        diff = SKILLS_D->query_skill_difficult(skillname);
        difficult = SKILL_D(skillname)->difficult_level();
        if (! diff) diff = difficult;
        if (! diff) diff = 100; 
        improve = improve / (diff / 100 + 1);

        if (! SKILL_D(skillname)->practice_skill(me))
                return 0;
                
        neili_cost = diff / 10 + 20;
        qi_cost = diff / 15 + 15;

        t1 = me->query("neili") / neili_cost + 1;
        t2 = me->query("qi") / qi_cost + 1;       
        t3 = min(t1, t2);

        if (t3 > times) t3 = times;
        t4 = t3 - 1;
        
        me->receive_damage("qi", qi_cost * t4); 
        me->add("neili", -neili_cost * t4); 

        me->improve_skill(skillname, improve * (t3 + 1),
                          skill_basic > skill? 0: 1);

        if (t3 > 0)
                write(HIC "�����Ű�" + to_chinese(skillname) +
                      "����" + chinese_number(t3)+"�ˡ�\n" NOR);

        if (t3 >= times)
                return 1;

        return 1;
}

int help(object me)
{
        write(@TEXT
ָ���ʽ��practice|lian <��������> <����>

���ָ��������ϰĳ������ļ��ܣ�������ܱ����Ǿ��� enable ��רҵ���ܡ�

�������ⷽ��Ļ������ܹ��ߣ����Ծ�����ϰֱ����������������������ֻ��
��������ܵĵȼ��йأ����仰˵���ڼ���ϰ��ʹ�����ѧ���������ʤ������
��Ψһ;������Ȼ������֮ǰ������ʵ�������л���㹻�ľ�����������Ļ�
�����ܡ�
TEXT );
        return 1;
}
