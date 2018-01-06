// top.c

#include <ansi.h>

inherit F_CLEAN_UP;

// ��������(�Ӹߵ���)
int sort_family(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}

// ��������(�Ӹߵ���)
int sort_league(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}

// ��������(�Ӹߵ���)
int sort_bunch(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}
int main(object me, string arg)
{
        mapping last, fame;
        array fam;
        string msg;
        int delta;
        int i;
        int cur_time;
        // ��ֹ flood add by ken@NT
        cur_time = time(); 
        if(cur_time-me->query_temp("last_who") < 1){
              return notify_fail("ϵͳ�������̾���������� ....\n"); 
        } 
        me->set_temp("last_who", cur_time); 

        if (! arg || arg == "family")
        {
                fame = FAMILY_D->query_family_fame();
                last = FAMILY_D->query_all_last_family_fame();
        
                fam = keys(fame) - ({ 0 });
                fam = sort_array(fam, (: sort_family :), fame);
        
                msg = WHT "Ŀǰ�������������Ŵ��ɵ�����״��\n" NOR
                      HIY "��������������������������������\n" NOR;
                for (i = 0; i < sizeof(fam); i++)
                {
                        delta = fame[fam[i]] - last[fam[i]];
                        msg += sprintf("%2d. %-12s  %-9d(%s%d%s)\n",
                                       i + 1, fam[i], fame[fam[i]],
                                       (delta > 0) ? HIY "+" :
                                       (delta < 0) ? HIR : WHT,
                                       delta, NOR);
                }
        
                msg += HIY "��������������������������������\n" NOR
                       WHT "һ����" + chinese_number(i) + "�����ɡ�\n" NOR;
        } else
        if (arg == "league")
        {
                fame = LEAGUE_D->query_league_fame();
                last = LEAGUE_D->query_all_last_league_fame();
        
                fam = keys(fame) - ({ 0 });
                if (sizeof(fam) < 1)
                        return notify_fail("Ŀǰ������û��ʲô"
                                           "�����Ľ���ͬ�ˡ�\n");

                fam = sort_array(fam, (: sort_league :), fame);
        
                msg = WHT "Ŀǰ��������������ͬ�˵�����״��\n" NOR
                      HIY "��������������������������������\n" NOR;
                for (i = 0; i < sizeof(fam) && i < 30; i++)
                {
                        delta = fame[fam[i]] - last[fam[i]];
                        msg += sprintf("%2d. %-12s  %-9d(%s%d%s)\n",
                                       i + 1, fam[i], fame[fam[i]],
                                       (delta > 0) ? HIY "+" :
                                       (delta < 0) ? HIR : WHT,
                                       delta, NOR);
                }
        
                msg += HIY "��������������������������������\n" NOR
                       WHT "�г���" + chinese_number(i) + "������ͬ�ˡ�\n" NOR;
        } else
        if (arg == "bunch")
        {
                fame = BUNCH_D->query_bunch_fame();
                last = BUNCH_D->query_all_last_bunch_fame();

                fam = keys(fame) - ({ 0 });
                if (sizeof(fam) < 1)
                        return notify_fail("Ŀǰ������û��ʲô"
                                           "�����İ��ɡ�\n");

                fam = sort_array(fam, (: sort_bunch :), fame);

                msg = WHT "Ŀǰ������������Ұ��ɵ�����״��\n" NOR
                      HIY "��������������������������������\n" NOR;
                for (i = 0; i < sizeof(fam) && i < 30; i++)
                {
                        delta = fame[fam[i]] - last[fam[i]];
                        msg += sprintf("%2d. %-12s  %-9d(%s%d%s)\n",
                                       i + 1, fam[i], fame[fam[i]],
                                       (delta > 0) ? HIY "+" :
                                       (delta < 0) ? HIR : WHT,
                                       delta, NOR);
                }

                msg += HIY "��������������������������������\n" NOR
                       WHT "�г���" + chinese_number(i) + "�����ɡ�\n" NOR;
        } else
                return notify_fail("��Ҫ��ʲô���а�\n");

        write(msg);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: top [family | league | bunch]

�鿴Ŀǰ�����ϴ����ɻ�����������ͬ�˻��ǰ��ɵ�����״�������ȥ��仯
�ĳ̶ȡ�
HELP );
        return 1;
}
