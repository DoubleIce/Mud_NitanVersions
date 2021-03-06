// 活动精灵，负责发起和关闭每日的活动
// 这个daemon我倾向于做成广播器和活动状态的容器
// 他本身什么也不做，其他系统从他这里获取某个活动是否开启的状态

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
        set("channel_id", HIY "活动精灵");
        if( setup() ) {
                CHANNEL_D->do_channel( this_object(), "sys", "活动精灵已经启动。\n");
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
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN]; // 当前分钟，这里要用localtime(获取本地时间)
        
        // 逐个setting做判断，60秒一次，这个效率可以接受
        foreach( string key in keys(action_settings) ) {
                // 当前时间在开始时间以前，那么什么也不做
                if( now_min<action_settings[key]["start"] )
                        continue;
                // 当前时间在结束时间之后，则需要试试是否应该关闭它
                if( now_min>=action_settings[key]["end"] ) {
                        // 存在于活跃列表，则结束之
                        if( !undefinedp(active_actions[key]) ) {
                                map_delete(active_actions,key);
                                // 广播
                                CHANNEL_D->do_channel(this_object(),"chat","本日活动："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]已经结束。");
                        } // 否则什么也不做
                        continue;
                }
                // 考虑到create的情况，所以当时间落在start和end之间的时候，需要多一个判断
                
                if( undefinedp(active_actions[key]) ) {
                        tmp ++;
                        active_actions[key] = action_settings[key]["times"];// 获得倍率
                        // 广播
                        CHANNEL_D->do_channel(this_object(),"chat","本日活动："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]已经开始（本活动将持续约"+chinese_number(action_settings[key]["end"]-now_min)+"分钟）。");
                }
        }
        if( !tmp && !random(3) ) {// 平均每三分钟announc一次
                foreach( string key in keys(active_actions) ) {
                        CHANNEL_D->do_channel(this_object(),"chat","当前活动："+action_settings[key]["name"]+"[倍率："+action_settings[key]["times"]+"]进行中（本活动将持续约"+chinese_number(action_settings[key]["end"]-now_min)+"分钟）。");
                }
        }
}
//测试接口，获取所有的action列表
mixed query_action_settings()
{
        return action_settings;
}

// 给查询指令留的接口
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
//              return HIY"当前没有正在进行中的活动。\n"NOR;
        
        ltime = localtime(time());
        now_min = ltime[LT_HOUR]*60+ltime[LT_MIN];
/*      ret = HIY"当前正在进行中的活动有：\n";
        foreach(string key in keys(active_actions)) {
                ret += action_settings[key]["name"]+"："+chinese_number(action_settings[key]["times"])+"倍[剩余"+chinese_number(action_settings[key]["end"]-now_min)+"分钟]\n";
        }
        ret += NOR;
        return ret;
*/
        ret = HIY"目前王者归来提供的活动包括：\n";
        foreach( string key in keys(action_settings) ) {
                ret += "\t"+action_settings[key]["name"]+"："+str2(action_settings[key]["start"]/60)+":"+str2(action_settings[key]["start"]%60)+"～"+str2(action_settings[key]["end"]/60)+":"+str2(action_settings[key]["end"]%60)+"（"+chinese_number(action_settings[key]["times"])+"倍）";
                if( active_actions[key] ) {
                        ret += HIG"-当前进行中-剩余"+chinese_number(action_settings[key]["end"]-now_min)+"分钟\n"HIY;
                } else {
                        ret +=HIG"-当前未开启\n"HIY;
                }
        }
        
        return ret+NOR;
}

// 这里是其他系统调用查询当前是否处于某个活动中的接口，返回的是倍率
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
        
        // 这里应该判断是否有文件
        if( !(file = read_file("/adm/etc/action_list")) )
                return 0;
        // 过滤win的换行符
        file = replace_string(file,"\r","");
        file = explode(file,"\n");
        foreach( string line in file ) {
                //确保不是空行
                if( strlen(line) ) {
                        // action_list形如：
                        // action_name:chinese_name:starttime:endtime:times
                        // task_reward:多倍TASK奖励:1500:1700:2
                        // 活动英文标识:活动中文名:开始时间:结束时间:倍率
                        // 时间应该形如0830(前两位表示小时-24小时制，后两位表示分钟)，并且开始时间应当小于结束时间
                        // 这里假设配置文件是对的。。。
                        tmp = explode(line, ":");
                        action_settings[tmp[0]] = ([]);
                        action_settings[tmp[0]]["name"] = tmp[1];
                        action_settings[tmp[0]]["start"] = get_minute_by_string(tmp[2]);//一天的第几分钟
                        action_settings[tmp[0]]["end"] = get_minute_by_string(tmp[3]);  //一天的第几分钟
                        action_settings[tmp[0]]["times"] = atoi(tmp[4]);
                }
        }
        return 1;
}

