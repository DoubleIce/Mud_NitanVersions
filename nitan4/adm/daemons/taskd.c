// taskd.c

#define TASK_DIR        "/task/"
#define TASK_OB_DIR     TASK_DIR + "obj/"
#define QUEST_LIST      TASK_DIR + "questlist/"
#define ZONES           TASK_DIR + "zones"
#define RESET_T         1800
#define DELAY_RESET_T   150
#define CONSULT         20
#define MIN(x, y)       (x > y ? y : x)
#define BIG_TASK_N      6
#define BIG_TRADER      find_living("tang nan")
#define SHADOW_ENV      "/task/shadow_room"
#define SEARCH_TIMES    10
#define ROOM_TYPE       1 
#define DEBUGER         "lonely"
#define TP(x)           tell_object(find_player(DEBUGER), x)
#define DEBUG

#include <ansi.h>
#include <command.h> 
inherit F_DBASE;

#include "/task/questlist/item"

void    init_task();
void    alloc_task(string arg, int i);
void    delay_init_task();
string  display_locate(int dist, string alti, string dire, string city);
string  ask_for_task(object me, string arg);
void    finish(object ob, object me);
void    reg_info(string arg, object env, int i);
int     die(object me);

nosave mapping *task_status;
nosave mapping search_room;

mapping query_sroom() {return search_room;}
mapping *query_task() {return task_status;}

nosave string  *symbol = ({"∧", "∴", "↑", "∨", "∵", "↓", "＜", "<=", "←", "＞", "=>", "→", "↗", "↘", "↙", "↖", "//", "／", "\\\\", "＼", "||", "‖","==", "〓", "※", "■", "◆", "◇", "□", "◎", "●", "○"});
nosave string  *colors = ({RED, GRN, YEL, BLU, MAG, CYN, WHT, HIR, HIG, HIY, HIB, HIM, HIC, HIW});

void remove()
{
        string  task_ob;
        mapping stat;

        remove_call_out("delay_init_task"); 
        remove_call_out("init_task");

        if (sizeof(task_status)) 
        {
                foreach (stat in task_status) 
                {
                        if (! mapp(stat) || 
                            undefinedp(stat["env"])) 
                                continue;
                                
                        if (objectp(stat["env"]) && 
                            stat["env"]->is_character() &&
                            ! userp(stat["env"])) 
                        {
                                stat["env"]->delete("inquiry/" + filter_color(stat["name"]));
                                stat["env"]->delete_temp("task");
                                stat["env"]->delete_temp("override/accept_object");
                                stat["env"]->delete_override("die");
                        } else
                        if (objectp(stat["env"]) && stat["env"]->is_room())
                                stat["env"]->delete_temp("search_objects");
                }
        }
        task_status = allocate(0);
}

void remove_task()
{
        remove_call_out("delay_init_task"); 
        remove_call_out("init_task");
        task_status = allocate(0);
}

int clean_up() { return 1; }

void create()
{
        seteuid(getuid());
        set("channel_id", "使命精灵");
        get_object("/d/city/dangpu");
        init_task();
}

void init_task()
{
        int i = 0;
        array task_objs = get_dir(TASK_OB_DIR);
        string  task_ob, temp_big_task;
        mapping stat;
        object ob;

        foreach (string file in task_objs)
                if (objectp(ob = find_object(TASK_OB_DIR + file)))
                        destruct(ob);
                
        if (sizeof(task_status))
        { 
                foreach (stat in task_status) 
                {
                        if (! mapp(stat) || 
                            undefinedp(stat["env"])) 
                                continue;
                                
                        if (objectp(stat["env"]) && 
                            stat["env"]->is_character() &&
                            ! userp(stat["env"])) 
                        {
                                stat["env"]->delete("inquiry/" + filter_color(stat["name"]));
                                stat["env"]->delete_temp("task");
                                stat["env"]->delete_temp("override/accept_object");
                                stat["env"]->delete_override("die");
                        } else
                        if (objectp(stat["env"]) && stat["env"]->is_room())
                                stat["env"]->delete_temp("search_objects");
                }
        }

        task_status = allocate(sizeof(task_objs));

        search_room = ([]);
        
        if (! find_object("/d/city/dangpu"))
                load_object("/d/city/dangpu");
                
        BIG_TRADER->clean_big_task(BIG_TASK_N);

        for (int j = 0; j < BIG_TASK_N; j++) {
                temp_big_task = task_objs[random(sizeof(task_objs))];
                task_objs -= ({temp_big_task});
                BIG_TRADER->add_big(temp_big_task, j);
                reg_info(temp_big_task, get_object(SHADOW_ENV), (sizeof(task_status) - j - 1));
        }

        foreach(task_ob in task_objs) 
                alloc_task(task_ob, i++);

        BIG_TRADER->task_announce();

        /************************************************
         message("system", "==========================================\n"
                           "            使命任务分配完毕              \n"
                           "==========================================\n", 
                           filter_array(users(), (: !$1->query("env/no_task") :)));
        ************************************************/

        remove_call_out("delay_init_task");
        call_out("delay_init_task", RESET_T - DELAY_RESET_T);
}

void delay_init_task()
{
        message("system", WHT "【任务频道】任务精灵：使命任务将于三分钟后重新分配。\n" NOR, 
                filter_array(users(), (: !$1->query("env/no_task") :)));
        remove_call_out("init_task");
        call_out("init_task", DELAY_RESET_T);
}

void alloc_task(string arg, int i)
{
        array zones, rooms;
        string zone, room;
        object room_ob, inv, *invs, *target = ({});
        object task_ob, target_ob, env;
        
        zones = explode(read_file(ZONES), "\n");
        zone = zones[random(sizeof(zones))];
        rooms = get_dir(zone);
        room = zone + rooms[random(sizeof(rooms))];

        while (sizeof(rooms) > 0)
        {
                if (file_size(room) == -2 || room[<2..<1] != ".c" || ! room->query("coor")) {
                        rooms -= ({ room });
                        room = zone + rooms[random(sizeof(rooms))];
                } else break;
        }
                       
        if (sizeof(rooms) < 1 || ! objectp(room_ob = get_object(room))) 
        {
                alloc_task(arg, i);
                return;
        }
        
        invs = all_inventory(room_ob);

        foreach (inv in invs) 
                if (((inv->is_character() && ! userp(inv) && 
                    inv->query("race") != "野兽" &&
                    ! inv->query_temp("quest_ob") && 
                    ! inv->is_stay_in_room() &&
                    ! inv->is_master()) || inv->is_container()) && 
                    ! sizeof(filter_array(all_inventory(inv), (: $1->query("task_ob") :)))) 
                        target += ({ inv }); // target is npc or container
        
        if (! sizeof(target)) 
        {
                if (sizeof(search_room) && member_array(base_name(room_ob), keys(search_room)) != -1)
                {
                        alloc_task(arg, i);
                        return;
                }
                
                target = ({ room_ob });
                search_room += ([base_name(room_ob) : arg]);
        }
    
        if (objectp(task_ob = find_object(TASK_OB_DIR + arg)))
                destruct(task_ob);
        task_ob = load_object(TASK_OB_DIR + arg);
                
        task_ob->set("task_ob", 1);
        task_ob->delete("big_task");
        task_ob->delete("keeper_killer");
        task_ob->delete("geter");
        task_ob->set("can_beg", 90);
        target_ob = target[random(sizeof(target))];
        if (target_ob->is_room())
        {
                mapping data;
                        
                data = ([ base_name(task_ob) : 2000000 ]);
                target_ob->set_temp("search_objects", data);
        } else
        {
                task_ob->delete_temp("override/accept_object");
                task_ob->delete_override("die");        
                task_ob->move(target_ob, 1);
        }
        
        if (! objectp(env = environment(task_ob)))
                env = target_ob;
                
        reg_info(arg, env, i);
}

void reg_info(string arg, object env, int i)
{
        object task_ob;
        
        task_ob = get_object(TASK_OB_DIR + arg);
        
        if (! objectp(env))
                env = get_object(SHADOW_ENV);                              
                
        task_status[i] = ([ "name"  :   task_ob->query("name"),
                            "id"    :   task_ob->query("id"),
                            "owner" :   task_ob->query("owner"),
                            "file"  :   arg,
                            "flag"  :   0,
                            "env"   :   env,
        ]);

        if (objectp(task_status[i]["env"]) && 
            objectp(environment(task_status[i]["env"])) && 
            task_status[i]["env"]->is_character() && 
            ! task_status[i]["env"]->is_master())
            // ! function_exists("accept_object", task_status[i]["env"]))
        {                
                if (task_status[i]["env"]->query_temp("override/accept_object"))
                        return;

                if (task_status[i]["env"]->query("race") == "野兽")
                        return;

                task_status[i]["env"]->set("inquiry/" + filter_color(task_status[i]["name"]), 
                        (: call_other, __FILE__, "ask_for_task", task_status[i]["env"], 
                        filter_color(task_status[i]["name"]) :));
                task_status[i]["env"]->set_temp("override/accept_object", 
                        (: call_other, __FILE__, "accept_object" :));

                task_status[i]["env"]->set_override("die", 
                        (: call_other, __FILE__, "die" :));
        }

}


string task_list()
{
        int i = 1;
        string tmp = "", res = "";
        mapping task_info;
 
        if (! sizeof(task_status)) 
                return "目前还没有任何使命被系统分配。\n";
 
        foreach (task_info in task_status) {
                tmp = sprintf("%2s%s的『%s』(%s)", task_info["flag"] ? 
                        WHT "√" NOR : "", task_info["owner"], 
                        task_info["name"], task_info["id"]);
                res += sprintf("%s%" + (38 - strlen(filter_color(tmp))) + "s", tmp, "");
                res += i % 2 ? "" : "\n";
                i++;
        }
 
        return res[<1..<1] == "\n" ? res : res + "\n";
}

string locate_ob(object me, string arg)
{
        array altitude =({
                "高处", "地方", "低处"
        });
        array directions=({
                "周围","北方", "南方", "东方","西方",
                "东北方","西北方","东南方","西南方"
        });

        int dis, x_sub, y_sub, z_sub, task_size = sizeof(task_status) - BIG_TASK_N;
        string alt, dir, city;
        object env, room, ob;
        mapping obj_info, coor_there, coor_here = environment(me)->query("coor");

        for (int i = 0; i < task_size; i++) {
                obj_info = task_status[i];
                if (obj_info["id"] == arg || filter_color(obj_info["name"]) ==  arg) {
                        call_other(TASK_OB_DIR + obj_info["file"], "???");
                        ob = find_object(TASK_OB_DIR + obj_info["file"]);
                        if (obj_info["flag"]) 
                                return "『" + obj_info["name"] + "』已经物归原主了，你还找什么？\n";
                        
                        /*        
                        if (objectp(ob) && ob->query("geter") && playerp(environment(ob)))
                                return "『" + obj_info["name"] + "』已经有人拿到了，你还找什么？\n";
                        */       
                        if (! objectp(env = environment(ob)))
                               env = obj_info["env"]; 
                        
                        while (objectp(env) && ! env->is_room()) 
                                env = environment(env);                         
                        room = env;
                        if (! objectp(room)) {
                                alloc_task(obj_info["file"], i);
                                return locate_ob(me, arg);
                        }
                        city = LOOK_CMD->locate(base_name(room));
                        coor_there = room->query("coor");
                        if (! coor_there) 
                                return "『" + obj_info["name"] + "』在一个方位无法确定的区域，无法搜寻。\n";
                        
                        x_sub = coor_there["x"] - coor_here["x"];
                        y_sub = coor_there["y"] - coor_here["y"];
                        z_sub = coor_there["z"] - coor_here["z"];
                        dis = MIN(((x_sub + y_sub + z_sub) < 0 ? -(x_sub + y_sub + z_sub) : 
                                (x_sub + y_sub + z_sub)) / CONSULT, 48);
                        if (z_sub == 0) alt = altitude[1];
                        else if (z_sub > 0) alt = altitude[0];
                        else alt = altitude[2];
                        if (x_sub > 0) x_sub = 1;
                        else if (x_sub < 0) x_sub = -1;
                        switch (x_sub) {
                        case 1 :
                                if (y_sub > 0) dir = directions[5];
                                else if (y_sub == 0) dir = directions[3];
                                else dir = directions[7];
                                break;
                        case 0 :
                                if (y_sub > 0) dir = directions[1];
                                else if (y_sub == 0) dir = directions[0];
                                else dir = directions[2];
                                break;
                        case -1:
                                if (y_sub > 0) dir = directions[6];
                                else if (y_sub == 0) dir = directions[4];
                                else dir = directions[8];
                                break;
                        }
                return display_locate(dis/2*2, alt, dir, city);
                }
        }
        return "";
}

string filter_symb(string fills, int flag)
{
        int i = random(2) + 1;
        int p;

        while (i--) {
                p = random(sizeof(fills));
                if (fills[p..p] != " ") {
                        i++;
                        continue;
                }
                if (p == (sizeof(fills) - 1) && fills[(p - 1)..(p - 1)] != " ") {
                        i++;
                        continue;
                }
                if (p == 0 && fills[(p + 1)..(p + 1)] != " ") {
                        i++;
                        continue;
                }
                if (fills[(p + 1)..(p + 1)] != " ") {
                        if (flag == 2) fills[(p - 1)..p] = colors[random(sizeof(colors))] + symbol[random(6) + 6] + NOR;
                        else fills[(p - 1)..p] = colors[random(sizeof(colors))] + symbol[random(3) + (flag * 3)] + NOR;
                } else {
                        if (flag == 2) fills[p..(p + 1)] = colors[random(sizeof(colors))] + symbol[random(6) + 6] + NOR;
                        else fills[p..(p + 1)] = colors[random(sizeof(colors))] + symbol[random(3) + (flag * 3)] + NOR;
                }
        }

        return fills;
}

string display_locate(int dist, string alti, string dire, string city)
{
        array msg = allocate(3);
        string color = colors[random(sizeof(colors))];
        string n_color = (colors - ({color}))[random(sizeof(colors - ({color})))];
        int space_f = (random(4) + 6) * 2;
        int space_b = (random(4) + 6) * 2;
        int i;
        string fill_f = sprintf("%"+ space_f + "s", " ");
        string fill_b = sprintf("%"+ space_b + "s", " ");

        switch(dire) {
                case "周围" :
                        msg[0] = color + (random(3) == 0 ? "↖" : (random(2) == 0 ? "＼" : "\\\\")) + (random(3) == 0 ? "∧" : (random(2) == 0 ? "↑" : "∴")) + (random(3) == 0 ? "↗" : (random(2) == 0 ? "／" : "//")) + NOR;
                        msg[1] = color + (random(3) == 0 ? "←" : (random(2) == 0 ? "〓" : "==")) + symbol[random(8) + 24] + (random(3) == 0 ? "→" : (random(2) == 0 ? "〓" : "==")) + NOR;
                        msg[2] = color + (random(3) == 0 ? "↙" : (random(2) == 0 ? "／" : "//")) + (random(3) == 0 ? "∨" : (random(2) == 0 ? "↓" : "∵")) + (random(3) == 0 ? "↘" : (random(2) == 0 ? "＼" : "\\")) + NOR;
                        break;
                case "北方":
                        msg[0] = "  " + color + symbol[random(3)] + NOR + "  ";
                        msg[1] = "  " + color + (random(10) < 2 ? (random(2) == 0 ? "||" : "‖") : symbol[random(8) + 24]) + NOR + "  ";
                        msg[2] = msg[1];
                        break;
                case "南方":
                        msg[0] = "  " + color + (random(10) < 2 ? (random(2) == 0 ? "||" : "‖") : symbol[random(8) + 24]) + NOR + "  ";
                        msg[1] = msg[0];
                        msg[2] = "  " + color + symbol[random(3) + 3] + NOR + "  ";
                        break;
                case "东方":
                        msg[0] = "      ";
                        msg[1] = random(10) < 2 ? (random(2) == 0 ? "==" : "〓") : symbol[random(8) + 24];
                        msg[1] = color + msg[1] + msg[1] + NOR + symbol[random(3) + 9];
                        msg[2] = msg[0];
                        break;
                case "西方":
                        msg[0] = "      ";
                        msg[1] = random(10) < 2 ? (random(2) == 0 ? "==" : "〓") : symbol[random(8) + 24];
                        msg[1] = color + symbol[random(3) + 6] + msg[1] + msg[1] + NOR;
                        msg[2] = msg[0];
                        break;
                case "东北方":
                        msg[0] = "   " + color + (random(4) == 0 ? symbol[12] : symbol[random(3)]) + NOR + " ";
                        msg[1] = color + (random(10) < 2 ? (random(2) == 0 ? "//" : "／") : symbol[random(8) + 24]) + NOR;
                        msg[2] = " " + msg[1] + "   ";
                        msg[1] = "  " + msg[1] + "  ";
                        break;
                case "西北方":
                        msg[0] = " " + color + (random(4) == 0 ? symbol[15] : symbol[random(3)]) + NOR + "   ";
                        msg[1] = color + (random(10) < 2 ? (random(2) == 0 ? "\\\\" : "＼") : symbol[random(8) + 24]) + NOR;
                        msg[2] = "   " + msg[1] + " ";
                        msg[1] = "  " + msg[1] + "  ";
                        break;
                case "东南方":
                        msg[0] = color + (random(10) < 2 ? (random(2) == 0 ? "\\\\" : "＼") : symbol[random(8) + 24]) + NOR;
                        msg[1] = "  " + msg[0] + "  ";
                        msg[0] = " " + msg[0] + "   ";
                        msg[2] = "   " + color + (random(4) == 0 ? symbol[13] : symbol[random(3) + 3]) + NOR + " ";
                        break;
                case "西南方":
                        msg[0] = color + (random(10) < 2 ? (random(2) == 0 ? "//" : "／") : symbol[random(8) + 24]) + NOR;
                        msg[1] = "  " + msg[0] + "  ";
                        msg[0] = "   " + msg[0] + " ";
                        msg[2] = " " + color + (random(4) == 0 ? symbol[14] : symbol[random(3) + 3]) + NOR + "   ";
                        break;
        }
        i = random(4) + 2;
        // 下面是干扰因素
        /**********************************************************/
        msg[0] = filter_symb(fill_f, 0) + sprintf("%" + i + "s", " ") + msg[0] + "   " + filter_symb(fill_b, 0);
        msg[1] = filter_symb(fill_f, 2) + sprintf("%" + i + "s", " ") + msg[1] + "   " + filter_symb(fill_b, 2);
        msg[2] = filter_symb(fill_f, 1) + sprintf("%" + i + "s", " ") + msg[2] + "   " + filter_symb(fill_b, 1);
        if (alti == "高处") msg[0] += " " + colors[random(sizeof(colors))] + alti + NOR;
        if (alti == "低处") msg[2] += " " + colors[random(sizeof(colors))] + alti + NOR;
        return HIW "所在区域：" + city + "\n━━━━━━━━\n\n" NOR + msg[0] + "\n" + msg[1] + "\n" + msg[2] + "\n" NOR + n_color + "距离指数：" + 
                sprintf(color + "%'━'" + dist + "s" + n_color + "%'━'" + (48-dist) + "s\n" NOR, "", "");
        /**********************************************************
        msg[0] = sprintf("%" + i + "s", " ") + msg[0];
        msg[1] = sprintf("%" + i + "s", " ") + msg[1];
        msg[2] = sprintf("%" + i + "s", " ") + msg[2];
        if(alti == "高处") msg[0] += " " + colors[random(sizeof(colors))] + alti + NOR;
        if(alti == "低处") msg[2] += " " + colors[random(sizeof(colors))] + alti + NOR;
        return implode(msg, "\n") + sprintf("\n距离指数：%d\n", dist);
        **********************************************************/
}


string ask_for_task(object me, string arg)
{
        object who = this_player();
        object *inv, ob;
        string type, msg, where, find;
    
        if (! me || ! who || ! arg) return 0;
        inv = all_inventory(me);
        if (! sizeof(inv)) return 0;
        if (type = me->query_temp("task/" + who->query("id")))
        switch(type) {
                case "sell" : 
                        msg = "不是说了吗，要的话一两黄金卖你。";
                        break;
                case "draw" : 
                        msg =  RANK_D->query_respect(who) + "如果已经画好了" + 
                                who->query("task/draw") + "的风景图就请尽快给" + RANK_D->query_self(me) + "吧！";
                        break;
                case "find" : 
                        msg = "告诉过你了，拿" + who->query("task/find") + "来换。";
                        break;
        }
        else 
        {
                for(int i = 0; i < sizeof(inv); i++) 
                        // 关注这个写法
                        // if(filter_color(inv[i]->query("name")) == arg && ob = inv[i])
                        if(filter_color(inv[i]->query("name")) == arg)
                        {
                                ob = inv[i]; 
                                break;
                        }
                if(!objectp(ob)) {
                        me->delete("inquiry/" + arg);
                        return 0;
                }
                switch (random(3)) {
                case 0 : 
                        msg = "这位" + RANK_D->query_respect(who) + "如果愿意出一两黄金的话，" + 
                                RANK_D->query_self(me) + "愿意把" + arg + "卖给" + 
                                RANK_D->query_respect(who) + "。";
                        me->set_temp("task/" + who->query("id"), "sell");
                        break;
                case 1 : 
                        where = explode(read_file(QUEST_LIST + "place"), "\n")[random(sizeof(explode(read_file(QUEST_LIST + "place"), "\n")))];
                        msg = RANK_D->query_self(me) + "非常想得到一幅" + where[0..strsrch(where, "/")-1] + 
                                where[strsrch(where, "/")+1..] + "风景图，如果" + RANK_D->query_respect(who) + 
                                "能画一幅来，" + RANK_D->query_self(me) + "愿将" + arg + "赠与" + 
                                RANK_D->query_respect(who) + "。";
                        me->set_temp("task/" + who->query("id"), "draw");
                        who->set("task/draw", where[strsrch(where, "/")+1..]);
                        break;
                case 2 : 
                        find = explode(read_file(QUEST_LIST + "find"), "\n")[random(sizeof(explode(read_file(QUEST_LIST + "find"), "\n")))];
                        msg = RANK_D->query_self(me) + "这" + arg + "只换不卖，要换得话，拿" + find + "来。";
                        me->set_temp("task/" + who->query("id"), "find");
                        who->set("task/find", find);
                        break;
        }
    }
    return msg;
}

int accept_object(object who, object me, object obj)
{
        string msg, type;
        int gift;
        
        if (! who || !me || playerp(who)) return 0;
        type = who->query_temp("task/" + me->query("id"));

        if (obj->is_character() || obj->is_item_make())
                return 0;
        if (type != "draw" && type != "find" && type != "sell") 
                return 0;
        if (type == "draw") {
                if (obj->query("id") != "paper" || !obj->query("draw/info") || 
                    filter_color((obj->query("draw/info"))->short()) != me->query("task/draw") || 
                    obj->query("draw/content") == "上面乱七八糟的看不出画的是什么。\n") {
                        message_vision(CYN "$N" CYN "皱了皱眉道：我要的是" + me->query("task/draw") + 
                        "的风景图，你这是什么东西？\n", 
                        who);
                        return 0;
                } else {
                        if (obj->query("draw/content")[8..9] == "虽") {
                                msg = "画的虽然不怎么样，但";
                                gift = 300;
                        } else {
                                msg = "画的栩栩如生，正";
                                gift = 600;
                        }
                        message_vision(CYN "$N" CYN "点了点头道：" + msg + "是我要的东西。\n", who);
                        msg = "通过替" + who->query("name") + "画" + me->query("task/draw") + "风景的过程，";
                }
        } else 
        if (type == "find") {
                if (filter_color(obj->query("name")) != me->query("task/find")) {
                        message_vision(CYN "$N" CYN "看了一眼$n道：" + RANK_D->query_respect(me) + "你弄错了吧，我要的是" + 
                                me->query("task/find") + "，不是$n！\n", who, obj);
                        return 0;
                } else {
                        message_vision(CYN "$N" CYN "仔细看了看$n道：不错，不错，我要的就是这个。\n", who, obj);
                        msg = "通过为" + who->query("name") + "寻找" + me->query("task/find") + "的过程，";
                        gift = 400;
                }
        } else {
                if (obj->query("money_id") != "gold" || obj->query_amount() < 1) {
                        message_vision(CYN "$N" CYN "大声道：说了一两黄金就是一两黄金，分毫都不能含糊。\n", who);
                        return 0;
                } else {
                        if (obj->query_amount() > 1) 
                                message_vision(CYN "$N" CYN "笑嘻嘻道：" + RANK_D->query_respect(me) + "既然愿意多给，" + RANK_D->query_sele(who) + "岂有不收之理。\n", who);
                        else
                                message_vision(CYN "$N" CYN "正色道：嗯，分文不差，就是这个数。\n", who);
                        msg = 0;
                }
        }
    
        message_vision("$n接过了$N的" + obj->short() + "。\n", me, who);
        destruct(obj);
        if (sizeof(filter_array(all_inventory(who), (: $1->query("task_ob") :))))
                obj = filter_array(all_inventory(who), (: $1->query("task_ob") :))[0];
        if (objectp(obj)) {
                message_vision("$N拿出" + obj->short() + "给$n。\n", who, me);
                obj->move(me, 1);
                who->delete("inquiry/" + filter_color(obj->query("name")));
                who->delete_temp("override/accept_object");
                who->delete_override("die");
        } else 
                message_vision(CYN "$N" CYN "尴尬的笑道：这位" + RANK_D->query_respect(me) + "实在是对不住，那个东西已经被别人取走了。\n");
    
        who->delete_temp("task/" + me->query("id"));
        me->delete("task/draw");
        me->delete("task/find");
        if (objectp(obj))
                obj->set("geter", me->name(1));
        if (msg) 
                GIFT_D->delay_bonus(me, ([
                        "promot"  : msg,
                        "exp"     : gift + random(gift / 10),
                        "pot"     : gift * 3/5 + random(gift * 3/50),
                        "mar"     : gift * 3/5 + random(gift * 3/50),
                        "score"   : gift/10 + random(gift/50),
                        "weiwang" : gift/15 + random(gift/75),
                ]));
        return -1;
}

int die(object me)
{
        object *invs;
        
        if (! me) return 0;
        
        invs = all_inventory(me);
        
        if (! sizeof(invs))
                return 0;

        for (int i = 0; i < sizeof(invs); i++) 
        {
                if (invs[i]->query("task_ob") && me->query("inquiry/" + filter_color(invs[i]->query("name")))
                && stringp(me->query_last_damage_name()))
                        invs[i]->set("keeper_killer", me->query_last_damage_name());
        }       
        return 0;
}

int task_reward(object me, object who, object ob)
{
        int exp, pot, weiwang, mar, score, td;
        string combat_exp;
        int task_count = me->query("task/count"); 
        string gift;
        object gift_ob;
        string msg;
        int task_times;
        
        td = time() / 86400; 
        if (me->query("task/total_count") >= 300 &&
            me->query("task/which_day") == td)
        {
                tell_object(me, WHT "你今天已经完成TASK任务超过每日规定的限制了。\n" NOR);
                destruct(ob);
                return 1;
        }

        if (me->query("reborn/times"))
        {
                tell_object(me, WHT "转世玩家无法通过做TASK任务获得奖励。\n" NOR);
                destruct(ob);
                return 1;
        }

        if (! who->is_character() || 
            // userp(who) || ! ob->query("task_ob") ||
            userp(who) || ob->is_item_make() ||
            ob->query("owner") != filter_color(who->query("name")))
                return 0; 

        if (me->query("task/which_day") != td) 
        {
                me->set("task/which_day", td);
                me->set("task/total_count", 0);
        }

        me->add("task/total_count", 1);
        combat_exp = me->query("combat_exp");

        if (count_lt(combat_exp, 10000)) 
                exp = 175 + random(200);
        else if (count_lt(combat_exp, 128000))
                exp = 200 + random(300);
        else if(count_lt(combat_exp, 1024000))
                exp = 260 + random(500);
        else if(count_lt(combat_exp, 2400000))
                exp = 360 + random(600);
        else if(count_lt(combat_exp, 3000000))
                exp = 400 + random(800);
        else if(count_lt(combat_exp, 6800000))
                exp = 500 + random(1000);
        else    
                exp = 600 + random(1000);

        if (ob->query("geter") == me->name(1))
                exp = exp*5 + task_count*10;

        if (ob->query("big_task")) exp *= 6;
        task_times = "/adm/daemons/actiond"->query_action("task_reward"); 
        if (task_times) exp *= task_times;

        if (count_gt(combat_exp, 50000000) && count_lt(combat_exp, 200000000))
                pot = exp/2 + random(exp/4);
        else if (count_gt(combat_exp, 200000000)) 
                pot = exp/3 + random(exp/4);
        else
                pot = exp/2 + random(exp/3);

        weiwang = pot / 5;
        mar = pot / 2;
        score = pot / 3;

        /*
        me->add("combat_exp", exp);
        me->add("potential", pot);
        me->add("score", score);
        me->add("experience", mar);
        me->add("weiwang", weiwang);
        */

        msg = WHT "通过为" + filter_color(who->name()) + "寻回" + filter_color(ob->name()) + "的过程" NOR;
        GIFT_D->delay_bonus(me, ([
                "promot"  : msg,
                "exp"     : exp,
                "pot"     : pot,
                "mar"     : mar,
                "score"   : score,
                "weiwang" : weiwang,
        ]), 1);

        finish(ob, me);

        task_count %= 300;
        if (task_count == 300) gift = ob11_list[random(sizeof(ob11_list))];
        else if (task_count == 200) gift = ob10_list[random(sizeof(ob10_list))];
        else if (task_count == 180) gift = ob9_list[random(sizeof(ob9_list))];
        else if (task_count == 160) gift = ob8_list[random(sizeof(ob8_list))];
        else if (task_count == 140) gift = ob7_list[random(sizeof(ob7_list))];
        else if (task_count == 120)  gift = ob6_list[random(sizeof(ob6_list))];
        else if (task_count == 100)  gift = ob5_list[random(sizeof(ob5_list))];
        else if (task_count == 80)  gift = ob4_list[random(sizeof(ob4_list))];
        else if (task_count == 60)  gift = ob3_list[random(sizeof(ob3_list))];
        else if (task_count == 40)  gift = ob2_list[random(sizeof(ob2_list))];
        else if (task_count == 20)  gift = ob1_list[random(sizeof(ob1_list))];
        
        // clear task count
        if (me->query("task/count") >= 1500)
                me->set("task/count", 0);
                
        if (stringp(gift)) {
                gift_ob = new(gift);
                gift_ob->move(me, 1);
                message_vision(CYN "$N" CYN "微笑道：" + RANK_D->query_self(who) + 
                        "这里有一" + (stringp(gift_ob->query("base_unit")) ? 
                        gift_ob->query("base_unit") : 
                        gift_ob->query("unit")) + gift_ob->query("name") + CYN + 
                        "赠给" + RANK_D->query_respect(me) + "以表谢意。\n", who);
        }
        /*
        log_file("static/task", sprintf("%s %s将%s交给%s得到%s点潜能。\n", 
                log_time(), me->name(), filter_color(ob->name()), 
                filter_color(who->name()), chinese_number(pot)));
        */

        destruct(ob);
        return 1;
}


void finish(object ob, object me)
{
        string id = ob->query("id");
        
        for (int i = 0; i < sizeof(task_status); i++) 
                if (id == task_status[i]["id"]) {
                        task_status[i]["flag"] = me->query("name") + "(" + me->query("id") + ")";
                        break;
                }
        if (ob->query("keeper_killer") == me->name(1)) 
                me->add("task/count", 0);
        else if (ob->query("geter") == me->name(1)) 
                me->add("task/count", 1);
}

object search_env(object env)
{
        object ob;
        if (member_array(base_name(env), keys(search_room)) == -1) 
                return 0;
        if (random(SEARCH_TIMES) == 0) {
                if (! objectp(ob = find_object(TASK_OB_DIR + search_room[base_name(env)])))
                        ob = load_object(TASK_OB_DIR + search_room[base_name(env)]);
                map_delete(search_room, base_name(env));
                return ob;
        }
        return 0;
}

