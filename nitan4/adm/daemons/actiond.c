// ����飬������͹ر�ÿ�յĻ
// ���daemon�����������ɹ㲥���ͻ״̬������
// ������ʲôҲ����������ϵͳ���������ȡĳ����Ƿ�����״̬

#include <localtime.h>
#include <ansi.h>

inherit F_DBASE;

mapping action_settings = ([]);
mapping active_actions = ([]);
int setup();
int get_minute_by_string(string time);
int check_action_startend();

void create()
{
        seteuid(getuid());
        set("channel_id", HIY "�����");
        if( setup() ) {
                CHANNEL_D->do_channel( this_object(), "sys", "������Ѿ�������\n");
                SCHEDULE_D->set_event(300, 1, this_object(), "check_action_startend");
        }
}

void check_action_startend()
{
        mixed *ltime;
        int now_min;
        int tmp;
        
        tmp = 0;
        ltime = localtime(time());
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN]; // ��ǰ���ӣ�����Ҫ��localtime(��ȡ����ʱ��)
        
        // ���setting���жϣ�60��һ�Σ����Ч�ʿ��Խ���
        foreach( string key in keys(action_settings) ) {
                // ��ǰʱ���ڿ�ʼʱ����ǰ����ôʲôҲ����
                if( now_min<action_settings[key]["start"] )
                        continue;
                // ��ǰʱ���ڽ���ʱ��֮������Ҫ�����Ƿ�Ӧ�ùر���
                if( now_min>=action_settings[key]["end"] ) {
                        // �����ڻ�Ծ�б������֮
                        if( !undefinedp(active_actions[key]) ) {
                                map_delete(active_actions,key);
                                // �㲥
                                CHANNEL_D->do_channel(this_object(),"chat","���ջ��"+action_settings[key]["name"]+"[���ʣ�"+action_settings[key]["times"]+"]�Ѿ�������");
                        } // ����ʲôҲ����
                        continue;
                }
                // ���ǵ�create����������Ե�ʱ������start��end֮���ʱ����Ҫ��һ���ж�
                
                if( undefinedp(active_actions[key]) ) {
                        tmp ++;
                        active_actions[key] = action_settings[key]["times"];// ��ñ���
                        // �㲥
                        CHANNEL_D->do_channel(this_object(),"chat","���ջ��"+action_settings[key]["name"]+"[���ʣ�"+action_settings[key]["times"]+"]�Ѿ���ʼ�����������Լ"+chinese_number(action_settings[key]["end"]-now_min)+"���ӣ���");
                }
        }
        if( !tmp && !random(3) ) {// ƽ��ÿ������announcһ��
                foreach( string key in keys(active_actions) ) {
                        CHANNEL_D->do_channel(this_object(),"chat","��ǰ���"+action_settings[key]["name"]+"[���ʣ�"+action_settings[key]["times"]+"]�����У����������Լ"+chinese_number(action_settings[key]["end"]-now_min)+"���ӣ���");
                }
        }
}
//���Խӿڣ���ȡ���е�action�б�
mixed query_action_settings()
{
        return action_settings;
}

// ����ѯָ�����Ľӿ�
string str2(int i)
{
        return (i<10)?("0"+i):(""+i);
}

string query_action_string()
{
        string ret;
        mixed *ltime;
        int now_min;
        
//      if(!sizeof(active_actions))
//              return HIY"��ǰû�����ڽ����еĻ��\n"NOR;
        
        ltime = localtime(time());
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN];
/*      ret = HIY"��ǰ���ڽ����еĻ�У�\n";
        foreach(string key in keys(active_actions)) {
                ret += action_settings[key]["name"]+"��"+chinese_number(action_settings[key]["times"])+"��[ʣ��"+chinese_number(action_settings[key]["end"]-now_min)+"����]\n";
        }
        ret += NOR;
        return ret;
*/
        ret = HIY"Ŀǰ���߹����ṩ�Ļ������\n";
        foreach( string key in keys(action_settings) ) {
                ret += "\t"+action_settings[key]["name"]+"��"+str2(action_settings[key]["start"]/60)+":"+str2(action_settings[key]["start"]%60)+"��"+str2(action_settings[key]["end"]/60)+":"+str2(action_settings[key]["end"]%60)+"��"+chinese_number(action_settings[key]["times"])+"����";
                if( active_actions[key] ) {
                        ret += HIG"-��ǰ������-ʣ��"+chinese_number(action_settings[key]["end"]-now_min)+"����\n"HIY;
                } else {
                        ret +=HIG"-��ǰδ����\n"HIY;
                }
        }
        
        return ret+NOR;
}

// ����������ϵͳ���ò�ѯ��ǰ�Ƿ���ĳ����еĽӿڣ����ص��Ǳ���
int query_action(string action)
{
        if( undefinedp(active_actions[action]) )
                return 0;
        else
                return active_actions[action];
}

int get_minute_by_string(string time)
{
        int hour,minute;
        hour = atoi(time[0..1]);
        minute = atoi(time[2..3]);
        return hour*60+minute;
}

int setup()
{
        mixed file;
        mixed tmp;
        
        // ����Ӧ���ж��Ƿ����ļ�
        if( !(file = read_file("/adm/etc/action_list")) )
                return 0;
        // ����win�Ļ��з�
        file = replace_string(file,"\r","");
        file = explode(file,"\n");
        foreach( string line in file ) {
                //ȷ�����ǿ���
                if( strlen(line) ) {
                        // action_list���磺
                        // action_name:chinese_name:starttime:endtime:times
                        // task_reward:�౶TASK����:1500:1700:2
                        // �Ӣ�ı�ʶ:�������:��ʼʱ��:����ʱ��:����
                        // ʱ��Ӧ������0830(ǰ��λ��ʾСʱ-24Сʱ�ƣ�����λ��ʾ����)�����ҿ�ʼʱ��Ӧ��С�ڽ���ʱ��
                        // ������������ļ��ǶԵġ�����
                        tmp = explode(line, ":");
                        action_settings[tmp[0]] = ([]);
                        action_settings[tmp[0]]["name"] = tmp[1];
                        action_settings[tmp[0]]["start"] = get_minute_by_string(tmp[2]);//һ��ĵڼ�����
                        action_settings[tmp[0]]["end"] = get_minute_by_string(tmp[3]);  //һ��ĵڼ�����
                        action_settings[tmp[0]]["times"] = atoi(tmp[4]);
                }
        }
        return 1;
}

