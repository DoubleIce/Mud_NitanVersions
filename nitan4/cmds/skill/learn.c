// learn.c

#include <skill.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int can_learn(object me, string skill);

array reject_msg = ({
        "˵������̫�����ˣ�����ô�ҵ���\n",
        "�����ܳ�����һ����˵������̣�����ô�ҵ���\n",
        "Ц��˵��������Ц�ˣ��������С�������ʸ�ָ����ʲô��\n",
});

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        array args;
        string skill, teacher, master, skill_name;
        object ob;
        mixed flag;
        int master_skill, my_skill, jing_cost, times, i;
        int lvl, neili_cost, t1, t2, t3, t4;
        int rand;
        int diff;
        int c;
        int r;
        int t = time();

        if (where->query("pigging"))
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if (me->is_busy())
                return notify_fail("��������æ���ء�\n");

        if (t == me->query_temp("time/learn"))
                return notify_fail("��ող�ѧϰ���������Ҫ����ѧϰ������ָ��ѧϰ�Ĵ�������\n");

        if (! arg || (i = sizeof(args = explode(arg, " "))) < 2)
                return notify_fail("ָ���ʽ��learn|xue <ĳ��> <����> <����>\n");

        i--;
        if (i >= 2 && sscanf(args[i], "%d", times) && times)
                i--;
        else
                times = 1;
        skill = args[i--];
        if (args[i] == "about" && i >= 1)
                i--;
        teacher = implode(args[0..i], " ");

        c = 300 + me->query_temp("apply/learn_times");
        if (present("learn emblem", me))
                c += 800;
        // ת����������ѧϰ����
        if (me->query("special_skill/wisdom"))
                c += 800;
        if (times < 1 || times > c)
                return notify_fail("ѧϰ��������һ�Σ����Ҳ���ܳ���" + chinese_number(c) +"�Ρ�\n");

        if (me->is_fighting())
                return notify_fail("����ĥǹ������������\n");

        if (! (ob = present(teacher, environment(me))) || ! ob->is_character())
                return notify_fail("��Ҫ��˭��̣�\n");

        if (! living(ob))
                return notify_fail("�š�������Ȱ�" + ob->name() +
                                   "Ū����˵��\n");

        if (! me->is_apprentice_of(ob) &&
            (me->query("family/family_name") != ob->query("family/family_name") ||
             me->query("family/generation") > ob->query("family/generation") ||
             ! ob->can_learn_from() ||
             playerp(ob)))
        {
                switch (ob->recognize_apprentice(me, skill))
                {
                case 0:
                        return notify_fail(CYN + ob ->name() + CYN +
                                           reject_msg[random(sizeof(reject_msg))]
                                           + NOR);
                case -1:
                        return 1;
                }
        }

        if (! master_skill = ob->query_skill(skill, 1))
                return notify_fail("���������±����ұ���ѧ�ˡ�\n");

        if (stringp(flag = ob->query("no_teach/" + skill)))
        {
                message_vision(CYN "$N" CYN "ҡҡͷ��˵����" + flag + "\n" NOR, ob);
                return 1;
        } else
        if (intp(flag) && flag)
        {
                if (flag != -1)
                        // show the messaeg if the result was not -1
                        write(CYN + ob->name() + CYN "˵�����Բ���" +
                              to_chinese(skill) + "�ɲ�����㴫�ڡ�\n" NOR);
                return 1;
        }

        // ����npc���Գɳ������ܶ�recognize_apprentice()û�����Ƶȼ���������������
        // if (me->is_apprentice_of(ob) &&
        if (
            SKILL_D(skill)->type() == "martial" &&
            me->query_skillo(skill, 1) >= SKILL_D(skill)->valid_learn_level())
        {
                write(CYN + ob->name() + CYN "˵�������" + to_chinese(skill) +
                      CYN "�����Ѿ��Ƿ�ͬ�����ˣ��ҾͲ��ٽ��㣬���Լ����о��ɡ�"
                      "\n" NOR);
                return 1;
        }

        my_skill = me->query_skillo(skill, 1);
        if (my_skill >= master_skill)
                return notify_fail("�������ĳ̶��Ѿ�������ʦ���ˡ�\n");

        if (my_skill >= (int)(master_skill - me->query("betrayer/times") * 2))
                return notify_fail(CYN + ob->name() + CYN "������üͷ��������"
                                   "�����ȥ����ʦ������\n" NOR);

        if (! can_learn(me, skill))
                return 0;

        notify_fail("����Ŀǰ��������û�а취ѧϰ���ּ��ܡ�\n");
        if (! SKILL_D(skill)->valid_learn(me)) return 0;

        jing_cost = (100 + my_skill * 2) / (int) me->query("int");
        if (! my_skill)
        {
                jing_cost *= 2;
                me->set_skill(skill,0);
        }

        if (count_lt(count_sub(me->query("potential"), me->query("learned_points")), times))
                return notify_fail("���Ǳ�ܲ���ѧϰ��ô����ˡ�\n");

        write(sprintf(HIC "�㿪ʼ��%s���" + chinese_number(times) +
                      "���йء�%s�������ʡ�\n" NOR,
                      ob->name(),
                      to_chinese(skill)));

        if (ob->query("env/no_teach"))
        {
                write("����" + ob->name() + "���ڲ���׼���ش�������⡣\n");
                return 1;
        }

        tell_object(ob, sprintf("%s��������йء�%s�������⡣\n",
                    me->name(), to_chinese(skill)));

        if (! me->can_improve_skill(skill))
        {
                write("Ҳ����ȱ��ʵս���飬���" +
                      ob->name() + "�Ļش������޷���ᡣ\n");
                return 1;
        }

        if (playerp(ob))
        {
                if ((int)ob->query("jing") > jing_cost * times / 5 + 1)
                        ob->receive_damage("jing", jing_cost / 5 + 1);
                else
                {
                        write("����" + ob->name() + "��Ȼ̫"
                              "���ˣ�û�а취����ʲ�ᡣ\n");
                        tell_object(ob, "������̫���ˣ�û�а취��" +
                                    me->name() + "��\n");
                        return 1;
                }
        }

        me->set_temp("time/learn", t);

        t1 = me->query("jing") / jing_cost;
        t2 = times - t1;
        if (t2 > 0)
        {
                lvl = me->query_skill("force");
                if (lvl <= 0) lvl = 1;

                neili_cost =  jing_cost * 60 / lvl;
                if (me->query("breakup"))
                        neili_cost = neili_cost * 7 / 10;

                if (neili_cost < 20) neili_cost = 20;

                if ((int)me->query("neili") >= neili_cost * t2)
                {
                        t4 = times;
                        me->add("neili", -neili_cost * t2);
                }
                else
                {
                        t3 = (int)me->query("neili") / neili_cost;
                        t4 = t1 + t3;
                        if (t4 == 0)
                        {
                                write("Ȼ�������̫���ˣ��޷��ٽ����κ�ѧϰ�ˡ�\n");
                                return 1;
                        }

                        me->set("neili", 0);
                }
        } else
                t4 = times;

        if (times > t1)
                me->receive_damage("jing", jing_cost * t1);
        else
                me->receive_damage("jing", jing_cost * times);

        if (me->query("env/auto_regenerate"))
                SKILL_D("force/regenerate")->exert(me, me);

        me->add("learned_points", t4);
        rand = me->query_int() + my_skill / 5;
        rand /= 2;
        if (intp(r = me->query_temp("apply/learn_effect")))
                rand += rand * r / 100;

        if (me->query("time_reward/study"))
                rand += rand * 50 / 100;

        if (me->query("special_skill/wisdom"))
                rand += rand * 50 / 100;

        diff = SKILLS_D->query_skill_difficult(skill);
        if (! diff) diff = SKILL_D(skill)->difficult_level();
        rand /= (diff / 100 + 1);

        // me->improve_skill(skill, 4 + random(rand));
        me->improve_skill(skill, t4 * (4 + rand));

        if(skill_name = SKILL_D(skill)->query_skill_name(my_skill))
                write(sprintf("������%s��ָ�����ԡ�%s��"
                              "��һ���ƺ���Щ�ĵá�\n",
                              ob->name(), skill_name));
        else
                write(sprintf("������%s��ָ�����ƺ���Щ"
                              "�ĵá�\n", ob->name()));

        if (t4 > 0 && t4 < times)
                write("���������̫���ˣ�ѧϰ��" + chinese_number(t4) +
                      "���Ժ�ֻ����ͣ������\n");

        return 1;
}

int can_learn(object me, string skill)
{
        string skill_name;
        mapping skills;
        string mskill;
        int tmp;
        int i;

        if (stringp(mskill = SKILL_D(skill)->main_skill()) &&
            mskill != skill &&
            me->query_skill(mskill, 1) > 0)
                return notify_fail("������û�б�Ҫ�ٵ���ѧϰ" + to_chinese(skill) + "�ˡ�\n");

        skills = me->query_skills();
        if (! mapp(skills))
                return 1;

        if (! SKILL_D(skill)->valid_enable("force") ||
            SKILL_D(skill)->valid_force("*"))
                return 1;

        foreach (skill_name in keys(skills))
        {
                if (file_size(SKILL_D(skill_name) + ".c") == -1)
                {
                        // No such skill
                        continue;
                }

                if (! SKILL_D(skill_name)->valid_enable("force") ||
                    skill_name == skill)
                        continue;

                if (! SKILL_D(skill_name)->valid_force(skill))
                        return notify_fail(HIR "�㷢��������ѧ��" HIY +
                                           to_chinese(skill_name) + HIR
                                           "��" HIY + to_chinese(skill) +
                                           HIR "��ͻ���ѣ�����û�취��"
                                           "�档\n" NOR);
        }

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : learn|xue <ĳ��> [about] <����> <����>

���ָ������������������й�ĳһ�ּ��ܵ��������⣬��Ȼ������̵Ķ�������
����ϵ�����������ߣ����㾭�����ַ�ʽѧϰ�����ļ���Ҳ�����ܸ��������
�̵��ˣ�Ȼ����Ϊ����ѧϰ��ʽ�൱�һ�֡�����Ĵ��С������ѧϰ����˵����Ϥ
һ���¼������ķ�����

����ѧϰҲ��Ҫ����һЩ�����������ĵľ��������Լ�������ѧϰ����������йء�

�������ָ�� : apprentice, practice, skills, study
HELP
        );
        return 1;
}

