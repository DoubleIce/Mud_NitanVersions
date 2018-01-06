// puliu.c �¼����ƹ����ٲ�

#include <ansi.h>

void create() { seteuid(getuid()); }

// ��ʼ�����¼�
void create_event()
{
        // ����5���������
        EVENT_D->at_after(0, 0, 1, -5);
}

// ����
private void do_bonus(object room)
{
        object *obs;
        object ob;
        string msg;
        int lvl;
        int r;

        obs = all_inventory(room);
        obs = filter_array(obs, (: playerp($1) && living($1) :));
        if (sizeof(obs) < 1)
                return;

        r = random(365);
        if (r == 0)
        { 
                msg = HIR "ֻ����¡¡�����������������������������ҡ����̧ͷ��ȥ��ֻ��\n"
                          "�����лƹ����ٲ������Ų������������Ҫ�ˡ�ˮ����к�����ƾ��ˣ�\n" NOR;
                msg += HIG "�������ļ����ٲ�������Ϊ������������̾���ѣ���"
                           "�в�����������ѧ�ĵ�����\n" NOR; 
                obs->add("combat_exp", 1000);
                obs->add("potential", 500);
                obs->add("magic_points", 200); 

                message("vision", msg, obs);

                // ��¼�¼�
                MAP_D->record_rumor(obs, "�ƹ�������", this_object());

                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "��˵�ƹ����������ȣ��澰�Ƿ�����������̾�۲��ѡ�");
        } else 
        if (r < 250) 
        {
                msg = HIY "һ���¡��¡�ĵ�������������̧ͷһ����ֻ���������ٲ�������������\n" NOR;
                switch (random(3)) 
                { 
                case 0: 
                        msg += HIY "������׳�����������㲻����̾������ν������ֱ"
                                    "����ǧ�ߣ�������������졹����\n" NOR; 
                        break; 
                case 1: 
                        msg += HIY "��������һϯ���ҵİ�����������磬��ض�����Ϊ֮ʧɫ��\n" NOR; 
                        break; 
                default: 

                        msg += HIY "����ֱ��ˮ��й��һ�㣬ˮ���Ľ���\n" NOR; 
                        break; 
                } 
                msg += HIG "�����ŷ���ֱ�µ�ˮ�٣��㲻�ɵø�̾��Ȼ�컯�������"
                           "��Ȼ����ѧҲ����һ����ᡣ\n" NOR; 
                obs->improve_potential(50 + random(70));
                obs->add("combat_exp", 200 + random(100));
                obs->add("magic_points", 50); 
 
                message("vision", msg, obs);

                // ��¼�¼�
                MAP_D->record_rumor(obs, "�ƹ����ٲ�", this_object());
        } else
        {
                switch (random(3))
                {
                case 0:
                        msg = WHT "������������������\n" NOR;
                        break;
                case 1:
                        msg = WHT "�������ǲ�������ǿ�����ơ�\n" NOR;
                        break;
                default:
                        msg = WHT "��������С����ˮ���������ˣ������������������Զ��\n" NOR;
                        break;
                }
                msg += HIG "�����д��ʧ����\n" NOR;

                message("vision", msg, obs);
        }
} 
 
// �¼����� 
void trigger_event() 
{ 
        object room; 
        // �ƹ������� 
        if (objectp(room = find_object("/d/dali/huanggs"))) 
                do_bonus(room); 
 
        create_event(); 
} 

// ���� 
string query_detail(string topic) 
{ 
        switch (topic) 
        { 
        case "�ƹ�������": 
                return "�ƹ����ٲ�ˮ���ļ���ʱ�м������ȣ����Ǻ����ľ��ۡ�\n"; 
 
        case "�ƹ����ٲ�": 
                return "�����Ļƹ����ٲ���Ȼ������ˣ���������׳�ۡ�\n"; 
        }
} 
