// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <localtime.h>
#include <mudlib.h>
#include <command.h>

inherit F_DBASE;

#define MIN             0
#define HOUR            1
#define WDAY            2
#define MDAY            3
#define MON             4
#define YEAR            5

#define DATA_PATH       "/data/timed.o"
#define MAZE_DOOR1      "/clone/misc/maze_door1"
#define MAZE_DOOR2      "/clone/misc/maze_door2"
#define SEA_DRAGON      "sea_dragon"
#define SKY_DRAGON      "sky_dragon"
#define CLOUD_DRAGON    "cloud_dragon"
#define BOSS_DAOKE      "daoke"
#define BOSS_TAOFAN     "taofan"

int gametime;
nosave int realtime;
nosave int tick;
nosave mapping event = allocate_mapping(0);
nosave int *real_time = allocate(6);
nosave int *game_time = allocate(6);

nosave mapping vrm_name_list = ([
        "sea_dragon"  : "海底迷宫",
        "sky_dragon"  : "天之尽头",
        "cloud_dragon": "苍之风云",
        "daoke"       : "剑冢刀客",
        "taofan"      : "朝廷逃犯",
]);

void auto_relaim()
{
        int i;
        if (i = reclaim_objects())
                CHANNEL_D->do_channel( this_object(), "sys",
                        sprintf("系统自动清除 %d 个变量。", i));
}

void game_new_year()
{
        shout(BEEP WHT "\n" + CHINESE_MUD_NAME + CHINESE_D->chinese_number(game_time[YEAR]) + "年终于来到，举世欢腾！！！\n" NOR);
}

void real_new_year()
{
        shout(BEEP WHT"\n西元" HIW+CHINESE_D->chinese_number(real_time[YEAR])+WHT"年终于来到，举世欢腾！！！\n"NOR);
        shout(BEEP WHT"\n西元" HIW+CHINESE_D->chinese_number(real_time[YEAR])+WHT"年终于来到，举世欢腾！！！\n"NOR);
        shout(BEEP WHT"\n西元" HIW+CHINESE_D->chinese_number(real_time[YEAR])+WHT"年终于来到，举世欢腾！！！\n"NOR);
}

void broadcast_message()
{
        shout(HIW "【系统提示】加入会员享受更多的会员服务(help member)，详情请查看帮助文件！！！\n" NOR);
        shout(HIW "【系统提示】本站支持网路传输压缩(MCCP)功能，建议您启动该功能让网路更顺畅！\n"
              HIW "            使用说明详见论坛 http://bbs.mudbuilder.com/read.php?tid=4866\n" NOR);
}

void double_reward_start()
{
        shout(BEEP BLINK HIR"【会员通告】现在的时间为 20 点，系统开放会员双倍奖励时间开始！！！\n"NOR);
}

void double_reward_end()
{
        shout(BEEP BLINK HIR"【会员通告】现在的时间为 24 点，系统开放会员双倍奖励时间结束！！！\n"NOR);
}

void create_rdm_entry(string arg)
{
        object room, npc, maze_target, maze_door;
        string filename, mazename;
        mapping maze; 
        
        switch( arg )
        {
        case BOSS_DAOKE :  
                filename = "/d/sdxl/pubu";  
                room = get_object(filename);  
                npc = new("/kungfu/class/boss/daoke");   
                break;
        case BOSS_TAOFAN :  
                filename = "/d/beijing/yongdingmen";  
                room = get_object(filename);  
                npc = new("/kungfu/class/boss/taofan");   
                break;
        default:
                return;
        }

        maze_target = MAZE_D->create_maze(npc); 
        npc->move(maze_target); 
        mazename = maze_target->query("maze/mazename");  
        maze = MAZE_D->query_maze(mazename);       
        maze_door = new(MAZE_DOOR2);
        maze_door->set("maze_entry", file_name(maze["entry"]));
        maze_door->move(room);
                                
        message("vision", HIG "【" HIR "江湖传言" HIG "】" HIW +
                vrm_name_list[arg] + HIW "在" +
                room->short() + HIW "(" + LOOK_CMD->locate(filename) + 
                ")一带出现了。\n" NOR, users());
                
        SCHEDULE_D->set_event(3600, 0, this_object(), "close_rdm_entry", mazename, maze_door);
} 

void close_rdm_entry(string mazename, object maze_door)
{
        object ob;
        
        if ( maze_door ) destruct(maze_door);
        
        MAZE_D->remove_maze(mazename);
}

void create_vrm_entry(string arg)
{
        object room, maze_door;
        string filename;
        
        switch( arg )
        {
        case SEA_DRAGON :    
                filename = "/d/xiakedao/haibin";  
                room = get_object(filename);          
                maze_door = new(MAZE_DOOR1);
                maze_door->set("maze_entry", "/d/maze/boss/VRM_0001/entry");
                maze_door->move(room);
                break;
        case SKY_DRAGON :
                filename = "/d/guanwai/tianchi1";  
                room = get_object(filename); 
                maze_door = new(MAZE_DOOR1);
                maze_door->set("maze_entry", "/d/maze/boss/VRM_0002/entry");
                maze_door->move(room);
                break;
        case CLOUD_DRAGON :
                filename = "/d/xueshan/hubian3";
                room = get_object(filename); 
                maze_door = new(MAZE_DOOR1);
                maze_door->set("maze_entry", "/d/maze/boss/VRM_0003/entry");
                maze_door->move(room);
                break;
        default:
                return;
        }
        
        message("vision", HIG "【" HIR "江湖传言" HIG "】" HIW +
                room->short() + HIW "(" + LOOK_CMD->locate(filename) + 
                ")一带出现了" + vrm_name_list[arg] + HIW "。\n" NOR, users());
        
        SCHEDULE_D->set_event(3600, 0, this_object(), "close_vrm_entry", arg, room, maze_door);
}

void close_vrm_entry(string arg, object room, object maze_door)
{
        if ( !room || !maze_door ) return;
        
        destruct(maze_door);
    
        message("vision", HIG"【" HIR"江湖传言" HIG"】" HIW +
                room->short() + HIW "(" + LOOK_CMD->locate(base_name(room)) + ")一带出现的" + 
                vrm_name_list[arg] + HIW "消失了。\n" NOR, users());
}

// 游戏时间的工作排程
nosave array game_crontab = ({
//"min hour wday mday mon year" : ({ function })
"0 0 * 0 0 *"           , (: game_new_year :),                  "每年发一次红包",
});

// 真实时间的工作排程
nosave array real_crontab = ({
//"min hour wday mday mon year" : ({ function })
"0 0 * 0 0 *"           , (: real_new_year :),                  "真实时间过年",
//"0 20 * * * *"          , (: double_reward_start :),            "每天 20 点会员双倍奖励时间开始",
//"0 0 * * * *"           , (: double_reward_end :),              "每天 24 点会员双倍奖励时间结束",
"* * * * * *"           , (: SCHEDULE_D->start_events() :),     "每分钟检测排程心跳情况",
"*/30 * * * * *"         , (: broadcast_message :),             "每五分钟播放系统消息",
"10 * * * * *"         , (: BUSINESS_D->random_check() :),             "每个小时期货刷新一次",
"0 */3 * * * *"         , (: create_rdm_entry(BOSS_TAOFAN) :),  "每 3 个小时刷新一次",
"1 */4 * * * *"         , (: create_rdm_entry(BOSS_DAOKE) :),   "每 4 个小时刷新一次",
"1 */5 * * * *"         , (: create_vrm_entry(SEA_DRAGON) :),   "每 5 个小时刷新一次",
"11 */5 * * * *"         , (: create_vrm_entry(SKY_DRAGON) :),   "每 5 个小时刷新一次",
"21 */5 * * * *"         , (: create_vrm_entry(CLOUD_DRAGON) :),   "每 5 个小时刷新一次",
});

// 可取代 call_out 之功能
void add_event(function fevent, int delay_time)
{
        if( !sizeof(event) || !event[fevent] )
                event = ([ fevent : delay_time ]);
        else
                event[fevent] = delay_time;
}

// 执行事件
void exec_event(function fevent)
{
        if( objectp(function_owner(fevent)) )
                evaluate(fevent);

        map_delete(event, fevent);
}

string replace_ctime(int t)
{
        string month, ctime = ctime(t);

        switch(ctime[4..6])
        {
                case "Jan"      :       month = "01";break;
                case "Feb"      :       month = "02";break;
                case "Mar"      :       month = "03";break;
                case "Apr"      :       month = "04";break;
                case "May"      :       month = "05";break;
                case "Jun"      :       month = "06";break;
                case "Jul"      :       month = "07";break;
                case "Aug"      :       month = "08";break;
                case "Sep"      :       month = "09";break;
                case "Oct"      :       month = "10";break;
                case "Nov"      :       month = "11";break;
                case "Dec"      :       month = "12";break;
        }

        return sprintf("%s/%s/%s %s", month, (ctime[8]==' '?"0"+ctime[9..9]:ctime[8..9]), ctime[<4..<1], ctime[11..15]);
}

string season_period(int m)
{
        switch(m)
        {
                case 2..4:      return "春";
                case 5..7:      return "夏";
                case 8..10:     return "秋";
                case 11:        return "冬";
                case 0..1:      return "冬";
                default:        return 0;
        }
}

string week_period(int w)
{
        switch(w)
        {
                case 0:         return "日";
                case 1:         return "一";
                case 2:         return "二";
                case 3:         return "三";
                case 4:         return "四";
                case 5:         return "五";
                case 6:         return "六";
                default:        return 0;
        }
}

string hour_period(int h)
{
        switch(h)
        {
                case 0..5:      return "凌晨";
                case 6..11:     return "上午";
                case 12:        return "中午";
                case 13..18:    return "下午";
                case 19..23:    return "晚上";
                default:        return 0;
        }
}

/* 回传时间阵列 ({ 分 时 礼 日 月 年 }) */
int *query_gametime_array()
{
        return game_time;
}

int *query_realtime_array()
{
        return real_time;
}

/* 回传数位时间表示 下午 3:39 */
string gametime_digital_clock()
{
        int h = game_time[HOUR];
        int m = game_time[MIN];

        return hour_period(h)+" "+(h==12 || (h%=12)>9?""+h:" "+h)+":"+(m>9?""+m:"0"+m);
}
string realtime_digital_clock()
{
        int h = real_time[HOUR];
        int m = real_time[MIN];

        return hour_period(h)+" "+(h==12 || (h%=12)>9?""+h:" "+h)+":"+(m>9?""+m:"0"+m);
}

string time_description(string title, int *t)
{
        return sprintf( NOR WHT+title+NOR"%s年，%s，%s月%s日星期%s，%s%s点%s分"NOR
            ,t[YEAR]==1?"元":CHINESE_D->chinese_number(t[YEAR])
            ,season_period(t[MON])
            ,!t[MON]?"元":CHINESE_D->chinese_number(t[MON]+1)
            ,CHINESE_D->chinese_number(t[MDAY]+1)
            ,week_period(t[WDAY])
            ,hour_period(t[HOUR])
            ,CHINESE_D->chinese_number(t[HOUR] > 12 ? t[HOUR]%12 : t[HOUR])
            ,CHINESE_D->chinese_number(t[MIN])
        );
}

string game_time_description()
{
        return time_description(CHINESE_MUD_NAME, game_time);
}

string real_time_description()
{
        return time_description("公元", real_time);
}

int query_game_time()
{
        return gametime*60;
}

int query_real_time()
{
        return realtime;
}

int *analyse_time(int t)
{
        int *ret = allocate(6);
        string ctime;

        ctime = ctime(t);

        sscanf(ctime,"%*s %*s %d %d:%d:%*d %d",ret[MDAY], ret[HOUR], ret[MIN], ret[YEAR]);

        switch(ctime[0..2])
        {
                case "Sun": ret[WDAY] = 0; break;
                case "Mon": ret[WDAY] = 1; break;
                case "Tue": ret[WDAY] = 2; break;
                case "Wed": ret[WDAY] = 3; break;
                case "Thu": ret[WDAY] = 4; break;
                case "Fri": ret[WDAY] = 5; break;
                case "Sat": ret[WDAY] = 6; break;
                default   : return 0;
        }

        switch(ctime[4..6])
        {
                case "Jan": ret[MON] = 0; break;
                case "Feb": ret[MON] = 1; break;
                case "Mar": ret[MON] = 2; break;
                case "Apr": ret[MON] = 3; break;
                case "May": ret[MON] = 4; break;
                case "Jun": ret[MON] = 5; break;
                case "Jul": ret[MON] = 6; break;
                case "Aug": ret[MON] = 7; break;
                case "Sep": ret[MON] = 8; break;
                case "Oct": ret[MON] = 9; break;
                case "Nov": ret[MON] = 10; break;
                case "Dec": ret[MON] = 11; break;
                default   : return 0;
        }
        ret[MDAY] -= 1;
        return ret;
}

void process_crontab(array crontab, int *timearray)
{
        int i, j, row, divider, fit, timecost, crontabsize;
        string s, script, note, *timescript;
        function fp;

        crontabsize = sizeof(crontab);

        for(row=0;row<crontabsize;row+=3)
        {
                reset_eval_cost();
                script = crontab[row];
                fp = crontab[row+1];
                note = crontab[row+2];

                timescript = allocate(6);

                // %s%*(( |\t)+) 的意思是 %s(空格 or \t 跳过)接著 + 可以相配一串一个以上符合的单元
                if( sscanf(script, "%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s%*(( |\t)+)%s",
                        timescript[0],
                        timescript[1],
                        timescript[2],
                        timescript[3],
                        timescript[4],
                        timescript[5]) != 11 ) continue;

                for( i=0;i<6;i++ )
                {
                        fit = 0;

                        foreach(s in explode(timescript[i], ","))
                        {
                                j = to_int(s);

                                // 不同的mudos的undefinedp函数返回的值有区别
                                if( s == "*" || (sscanf(s, "*/%d", divider) && !(timearray[i]%divider)) )
                                {
                                        fit = 1;
                                        break;
                                }
                                else if( !undefinedp(j) )
                                {
                                        if( j == timearray[i] )
                                        {
                                                fit = 1;
                                                break;
                                        }
                                }
                        }

                        if( !fit ) break;
                }

                if( !fit )
                        continue;

                timecost = time_expression {
                        catch(evaluate(fp));
                };

                if( timecost > 1000000 )
                        CHANNEL_D->do_channel(this_object(), "sys",
                                sprintf("TIME_D: crontab '%s'(%.6f sec) %s", script, timecost/1000000., note));

        }
}

// 独立出来每秒执行函式
void process_per_second()
{

}

void reset_gametime()
{
        gametime = -20000000;
}

/* 游戏时间每一分钟(即实际时间每2.5秒)执行一次 process_gametime */
void process_gametime()
{
        game_time = analyse_time(++gametime * 60);
        game_time[YEAR] -= 1970;

        process_crontab(game_crontab, game_time);
}

/* 真实时间每一秒钟执行一次 process_realtime */
void process_realtime()
{
        array localtime = localtime(realtime);

        real_time = ({
                localtime[LT_MIN],
                localtime[LT_HOUR],
                localtime[LT_WDAY],
                localtime[LT_MDAY]-1,
                localtime[LT_MON],
                localtime[LT_YEAR] });
        
        // 每秒执行函式
        process_per_second();

        if( !localtime[LT_SEC] )
                process_crontab(real_crontab, real_time);
}

// 每 1 秒运算一次
// 实际一天等于游戏一月

void heart_beat()
{
        realtime = time();

        // 执行 event 处理
        if( sizeof(event) )
        foreach( function fevent, int delay_time in event )
                if( !--event[fevent] )
                        exec_event(fevent);

        // 每 2 秒相当于游戏一分钟, time 每增加 1 代表游戏一分钟
        if( !(++tick % 2) )
                process_gametime();

        process_realtime();
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "时间精灵");
        write("时间精灵已经启动。\n");
        if( !restore_object(DATA_PATH) )
                save_object(DATA_PATH);

        game_time = allocate(6);
        real_time = allocate(6);
        event = allocate_mapping(0);

        process_gametime();
        set_heart_beat(1);
}

int remove()
{
        return save_object(DATA_PATH);
}

string query_name()
{
        return "时间系统(TIME_D)";
}
