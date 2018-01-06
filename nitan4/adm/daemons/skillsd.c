// This program is a part of NITAN MudLIB

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

#define ATTACK          0
#define DODGE           1
#define PARRY           2
#define DAMAGE          3
#define FORCE           4
#define DIFFICULT       5
#define RANK            6
#define ATTRIBUTE       7
#define MAX_POINT       360

#define SKILL_FILE      CONFIG_DIR "skill"
#define SKILL_MIX_FILE  CONFIG_DIR "skill_mix"

// (scores / users - score / user) / 100
#define TO_EFFECT(x, y, a, b)      ((y / 200) < 20 ? 20 - b : (y / 200) - b) + (x / y - a / b) / 100
  
mapping all_skills = ([ ]);
mapping all_record = ([ ]);
mapping initial_skills = ([ ]);
class mix {
string name;            // 技能组合名称
string dodge;           // 技能组合轻功
string parry;           // 技能组合招架
string force;           // 技能组合内功
mapping need;           // 技能特效条件
mapping stats;          // 技能组合效果
}
class mix *all_mixs = ({ });              
// initialization,initializtion
public void add_id_into_skills(object me);
public void remove_id_from_skills(object me);
public void remove_id_from_abandon(object me, string sname);
public void add_skill_into_skills(string sname, mapping p);
public void remove_skill_from_skills(object me, string sname);
public varargs void query_skill_power(object me, string arg);
public mixed skill_query_power(string skill);
public int query_skill_difficult(string skill);
public int enforce_power(object me, int enforce);
public int attack_power(object me, string skill);
public int defense_power(object me, string skill);
public int damage_power(object me, string skill);
public string skill_mix_stats(object me);
protected void manage_skill();
protected void load_skill();
protected void load_skill_mix();
class mix find_skill_mix(object me);
protected mapping trans_data(string mark);
public mixed query_all_mixs() { return all_mixs; }
protected void disable_skill_mix(object me);
varargs void enable_skill_mix(object me, mapping stats, mapping need);
public void check_skill_mix(object me, int flag);
public string query_save_file() { return DATA_DIR "skillsd"; }

nosave array all_poison = ({ 
        "xx_poison", "corpse_poison", "fire_poison", "freezing",
});

nosave mapping family_name = ([ 
        "shaolin"  : "少林", 
        "wudang"   : "武当", 
        "gaibang"  : "丐帮", 
        "quanzhen" : "全真", 
        "huashan"  : "华山", 
        "duan"     : "段氏", 
        "murong"   : "慕容", 
        "xueshan"  : "雪山", 
        "lingjiu"  : "灵鹫", 
        "emei"     : "峨嵋", 
        "taohua"   : "桃花", 
        "shenlong" : "神龙", 
        "gumu"     : "古墓", 
        "xingxiu"  : "星宿", 
        "xiaoyao"  : "逍遥", 
        "xuedao"   : "血刀", 
        "ouyang"   : "欧阳", 
        "hu"       : "胡家", 
        "mingjiao" : "明教", 
        "tang"     : "唐门", 
        "riyue"    : "日月", 
        "mo"       : "魔教", 
]); 

void create()
{
        seteuid(getuid());
        restore();

        if( !mapp(all_skills) ||
            sizeof(all_skills) < 1 )
                load_skill();
        
        if (! (all_mixs) || sizeof(all_mixs) < 1 )
                load_skill_mix();
                
        SCHEDULE_D->set_event(3600, 1, this_object(), "manage_skill");
}

void load_skill()
{
        array tmp;
        string file;
        string line;
        array arg, skl;
        string skill, rank, attribute;
        int attack, dodge, parry, damage, force, difficult;

        file = read_file(SKILL_FILE);
        if( !stringp(file) ) return;

        // 去掉"\r"保证和MSDOS的文件格式兼容
        file = replace_string(file, "\r", "");

        tmp = explode(file, "\n");
        foreach( line in tmp )
        {
                reset_eval_cost();
                // 去掉行首的空格
                while( strlen(line) && line[0] == ' ' ) line = line[1..<1];
                if( line[0] == '#' )
                        // 注释
                        continue;

                if( line[0] == '&' )
                {
                        // 被系统注释的
                        line = line[1..<1];
                        while( strlen(line) && line[0] == ' ' ) line = line[1..<1];
                }

                if( !strlen(line) )
                        continue;

                arg = explode(line, "/");
                if( sizeof(arg) < 9 )
                {
                        log_file("static/skill", sprintf("%s\n", line));
                        break;
                }
                skill = arg[0];
                arg -= ({ arg[0] });
                attack = atoi(arg[ATTACK]);
                dodge = atoi(arg[DODGE]);
                parry = atoi(arg[PARRY]);
                damage = atoi(arg[DAMAGE]);
                force = atoi(arg[FORCE]);
                difficult = atoi(arg[DIFFICULT]);
                rank = arg[RANK];
                attribute = arg[ATTRIBUTE];

                skl = ({ attack, dodge, parry, damage, force, difficult, rank, attribute });

                if( ! mapp(all_skills) || sizeof(all_skills) < 1 )
                        all_skills = allocate_mapping(0);
                all_skills[skill] = skl;

                initial_skills[skill] = skl;
        }
}

void load_skill_mix()
{
        string file, num, mark;
        mapping temp_stats;
        class mix temp;
                
        file = read_file(SKILL_MIX_FILE);
        if( !stringp(file) ) return;

        file = replace_string(file, "\r", "");
        all_mixs = ({ });
           
        while ( sscanf(file, "%*s<S%s>%s</S%s>%s", num, mark, num, file) > 3 )
        {
                temp = new(class mix);    
                temp_stats = trans_data(mark);
                temp->name = temp_stats["name"];
                temp->dodge = temp_stats["dodge"];
                temp->parry = temp_stats["parry"];
                temp->force = temp_stats["force"];
                temp->need  = temp_stats["need"];
                temp->stats = temp_stats["stats"];
                
                all_mixs += ({ temp });
        }
}

class mix find_skill_mix(object me)
{
        class mix temp;
        int i, n;
        mapping map;
        
        temp = new(class mix);

	if (! all_mixs || ! (n=sizeof(all_mixs)))
		return temp;
		        
        map = me->query_skill_map(); 
        if (! mapp(map) || sizeof(map) == 0) 
                return temp;      

        if (undefinedp(map["dodge"]) ||
            undefinedp(map["parry"]) ||
            undefinedp(map["force"]))
                return temp;
                
        temp->dodge = map["dodge"];
        temp->parry = map["parry"];
        temp->force = map["force"];

        for (i=0; i<sizeof(all_mixs); i++)
	{
                if (all_mixs[i]->dodge == temp->dodge &&
                    all_mixs[i]->parry == temp->parry &&
                    all_mixs[i]->force == temp->force)
                {
                        temp->name  = all_mixs[i]->name;
                        temp->need  = all_mixs[i]->need;
                        temp->stats = all_mixs[i]->stats;
                        break;
                }
        }
        return temp;
}

public string skill_mix_stats(object me)
{
        class mix temp;
        mapping stats, need;
        int i;
        array keys_stats, keys_need;
        string msg, str;

        msg = "";
        
        temp = new(class mix);
        temp = find_skill_mix(me); 
        
        if( !temp->stats )
                return msg;
        
        
        msg += "\n\n\n\n\n\n";
        msg += sprintf(NOR "┏━━━━━━━━━━┓\n");
        msg += sprintf(NOR "┃轻功->%-14s" NOR "┃\n", to_chinese(temp->dodge));
        msg += sprintf(NOR "┃招架->%-14s" NOR "┃\n", to_chinese(temp->parry));
        msg += sprintf(NOR "┃内功->%-14s" NOR "┃\n", to_chinese(temp->force));
        
        need = temp->need;
        keys_need = keys(need);
        for (i=0;i<sizeof(keys_need);i++) 
                msg += sprintf(NOR "┃其他->%-14s" NOR "┃\n", 
                               need[keys_need[i]] + to_chinese(keys_need[i]));
              
        msg += sprintf(NOR "┗━━━━━━━━━━┛\n");
        msg += sprintf(" %-22s\n" NOR, trans_color(temp->name, 3));
        msg += sprintf(NOR + HIY "┏━━━━━━━━━━┓" NOR "\n" );

        stats = temp->stats;
        keys_stats = keys(stats);
        for (i=0;i<sizeof(keys_stats);i++)
        {
                str = EQUIPMENT_D->chinese(keys_stats[i], stats[keys_stats[i]]);
                msg += sprintf(NOR + HIY "┃" NOR "%-" + (20 + color_len(str)) + "s" NOR + HIY "┃" NOR "\n", str);
        }
        msg += sprintf(NOR + HIY "┗━━━━━━━━━━┛" NOR "\n");

        return msg;
}

void manage_skill()
{
        int t, delta;
        int last;
        int user, users, score, scores, effect;
        object *obs, ob;
        array skl;
        array record;
        array sname, ids;
        string skill, rank, attribute;
        int attack, dodge, parry, damage, force, difficult;

        t = time();
        last = query("last_check");
        if( (t / 86400) != (last / 86400) )
        {
                sname = keys(initial_skills);
                users = 0;
                scores = 0;

                foreach( skill in sname )
                {
                        reset_eval_cost();
                        if( !query(skill) )
                        {
                                if( !undefinedp(all_record[skill]) )
                                        map_delete(all_record, skill);
                                continue;
                        }

                        ids = keys(query(skill));
                        user = sizeof(ids);
                        users += user;
                        score = 0;
                        foreach(string id in ids)
                                score += query(skill + "/" + id);
                        scores += score;

                        record = ({ user, score });

                        all_record[skill] = record;

                }

                foreach( skill in sname )
                {
                        reset_eval_cost();
                        if( undefinedp(all_record[skill]) )
                        {
                                if( !undefinedp(all_skills[skill]) )
                                        all_skills[skill] = initial_skills[skill];
                                continue;
                        }
                        if( !scores || ! users || !all_record[skill][1] || 
                            !all_record[skill][0] )
                                continue;

                        effect = TO_EFFECT(scores, users, all_record[skill][1], all_record[skill][0]);
                        if( all_record[skill][0] < 2 ) effect += 5;
                        else if( all_record[skill][0] < 3 ) effect += 3;
                        else if( all_record[skill][0] < 4 ) effect += 1;
                        if( effect > 50 ) effect = 50;
                        if( effect < -50 ) effect = -50;

                        if( query("create/" + skill) )
                                effect += 5;

                        if( effect < 0 && (
                            all_skills[skill][ATTRIBUTE] == "shaolin" ||
                            all_skills[skill][ATTRIBUTE] == "public") )
                                effect = 0;

                        all_record[skill] += ({ effect });

                        attack = initial_skills[skill][ATTACK] ? 
                                 initial_skills[skill][ATTACK] + effect : 0;
                        damage = initial_skills[skill][DAMAGE] ?
                                 initial_skills[skill][DAMAGE] + effect : 0;
                        dodge = initial_skills[skill][DODGE] ?
                                initial_skills[skill][DODGE] + effect : 0;
                        parry = initial_skills[skill][PARRY] ?
                                initial_skills[skill][PARRY] + effect : 0;
                        force = initial_skills[skill][FORCE];
                        difficult = initial_skills[skill][DIFFICULT];
                        rank = initial_skills[skill][RANK];
                        attribute = initial_skills[skill][ATTRIBUTE];

                        obs = filter_array(users(), (: ultrap($1) && 
                                                       $1->query_skill($(skill), 1) > 400 &&
                                                       $1->query("doing") :));
                        if( sizeof(obs) )
                        {
                                ob = obs[random(sizeof(obs))];
                                ob->add_skill(skill, 10 + random(6));
                                tell_object(ob, HIM "你脑中突然灵光一闪，你对" + 
                                                to_chinese(skill) + "有了更深的领悟！\n" NOR);
                        }
                        else
                                ob = 0;

                        delta = all_skills[skill][DODGE] - dodge;
                        if( delta == 0 )
                                delta = all_skills[skill][FORCE] - parry;

                        if( delta > 0 )
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "江湖传言，武学大宗师" + (ob ? ob->name(1) : "无名老人") + "闭关修行研究" + 
                                        to_chinese(skill) + "，终于悟出其破解之术。");
                        else
                        if( delta < 0 )
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                        "江湖传言，武学大宗师" + (ob ? ob->name(1) : "无名老人") + "闭关修行研究" + 
                                        to_chinese(skill) + "，终于完善其破绽之处。");

                        skl = ({ attack, dodge, parry, damage, force, difficult, rank, attribute });
                        all_skills[skill] = skl;
                }
        }
        set("last_check", t);
        save();
}

int sort_skill(string f1, string f2, int n)
{
        return all_skills[f2][n] - all_skills[f1][n];
}

varargs void query_skill_power(object me, string arg)
{
        string str1, str2, msg;
        array skl;
        array sname;
        int flag1, flag2, flag3, flag4;
        int i, delta;
        mixed n;

        msg = WHT "目前江湖上所有武功各种参数值如下\n\n" NOR;
        msg += "─────────────────────────────────────────\n";
        msg += BBLU HIW "技能名称                      命中  躲闪  招架  伤害  内功  难度  级别  门派  调整\n" NOR;
        msg += "─────────────────────────────────────────\n";

        if( stringp(arg) && ! undefinedp(all_skills[arg]) )
        {
                n = 0;
                sname = ({ arg });
        }
        else
        {
                flag1 = 0;
                flag2 = 0;
                flag3 = 0;
                flag4 = 0;

                if( !arg ) n = 0;
                else
                {
                        switch(arg)
                        {
                        case "attack"   :
                        case "攻击"     : n = 0; break;
                        case "dodge"    :
                        case "躲闪"     : n = 1; break;
                        case "parry"    :
                        case "招架"     : n = 2; break;
                        case "damage"   :
                        case "伤害"     : n = 3; break;
                        case "force"    :
                        case "内功"     : n = 4; break;
                        case "difficult":
                        case "难度"     : n = 5; break;
                        case "ultimate" :
                        case "expert"   :
                        case "advance"  :
                        case "normal"   : n = 0; flag1 = 1; break;
                        case "public"   :
                        case "shaolin"  :
                        case "wudang"   :
                        case "gaibang"  :
                        case "quanzhen" :
                        case "huashan"  :
                        case "duan"     :
                        case "murong"   :
                        case "xueshan"  :
                        case "lingjiu"  :
                        case "emei"     :
                        case "taohua"   :
                        case "shenlong" :
                        case "gumu"     :
                        case "xingxiu"  :
                        case "xiaoyao"  :
                        case "xuedao"   :
                        case "ouyang"   :
                        case "hu"       :
                        case "mo"       :
                        case "mingjiao" :
                        case "tang"     :
                        case "riyue"    :
                        case "private"  : n = 0; flag2 = 1; break;
                        case "family"   : n = 0; flag3 = 1; break;
                        default         : n = 0; flag4 = 1; break;
                        }
                }
                sname = keys(all_skills) - ({ 0 });
                if( flag1 )
                        sname = filter_array(sname, (: $(all_skills)[$1][RANK] == $(arg) :));
                if( flag2 )
                        sname = filter_array(sname, (: $(all_skills)[$1][ATTRIBUTE] == $(arg) :));
                if( flag3 )
                        sname = filter_array(sname, (: $(all_skills)[$1][ATTRIBUTE] != "public" &&
                                                       $(all_skills)[$1][ATTRIBUTE] != "private" :));
                if( flag4 )
                        sname = filter_array(sname, (: SKILL_D($1)->valid_enable($(arg)) :));
        }
        sname = sort_array(sname, (: sort_skill :), n);
        for( i = 0; i < sizeof(sname); i++ )
        {
                skl = all_skills[sname[i]];

                if( !undefinedp(all_record[sname[i]]) )
                        delta = all_record[sname[i]][2];
                else
                        delta = 0;

                if( skl[RANK] == "ultimate" )
                        str1 = "终极";
                else
                if( skl[RANK] == "expert" )
                        str1 = "超级";
                else
                if( skl[RANK] == "advance" )
                        str1 = "高级";
                else
                        str1 = "普通";

                if( skl[ATTRIBUTE] == "public" )
                        str2 = "公共";
                else
                if( skl[ATTRIBUTE] == "private" )
                        str2 = "自创";
                else
                        str2 = family_name[skl[ATTRIBUTE]];

                msg += sprintf( HIC "%-30s" NOR, to_chinese(sname[i]) + "(" + sname[i] + ")" );
                msg += sprintf( HIC "%-6d%-6d%-6d%-6d%-6d%-6d" HIY "%-6s" HIM "%-6s" NOR,
                                skl[ATTACK], skl[DODGE], skl[PARRY], skl[DAMAGE],
                                skl[FORCE], skl[DIFFICULT], str1, str2 );

                msg += sprintf("(%s%2d%s)\n",
                                (delta > 0) ? HIY "+" :
                                (delta < 0) ? HIR "-" : WHT "+",
                                 abs(delta), NOR);
        }
        msg += "─────────────────────────────────────────\n";
        me->start_more(msg);
}

mixed skill_query_power(string skill)
{
        if( !undefinedp(all_skills[skill]) )
                return all_skills[skill];
        else
                return 0;
}

int query_skill_difficult(string skill)
{
        if( !undefinedp(all_skills[skill]) )
                return all_skills[skill][DIFFICULT];
        else
                return 0;
}

int query_neili_improve(string skill, int level)
{
        int improve;
        
        if( !undefinedp(all_skills[skill]) )
                improve = all_skills[skill][FORCE];
        else
                improve = 150;
        
        return atoi(count_div(count_mul(
                    big_number_pow(level, 2), improve), 10000));
}
        
int enforce_power(object me, int enforce)
{
        int value, damage, scale;
        int max_enforce;
        string map_skill;
        string rank;

        if( !objectp(me) ) return 0;

        if( !stringp(map_skill = me->query_skill_mapped("force")) )
                return 0;

        if( !undefinedp(all_skills[map_skill]) )
        {
                value = all_skills[map_skill][FORCE];
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 12;
                else
                if( rank == "expert" )
                        scale = 16;
                else
                if( rank == "advance" )
                        scale = 18;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 20;

        max_enforce = me->query_skill("force") / 2;
        if (enforce > max_enforce) enforce = max_enforce;

        damage =(me->query_skill("force", 1) / 2 +
                 me->query_skill(map_skill, 1)) * value / scale / max_enforce * enforce;

        if( me->query_xuruo() ) damage /= 2;

        damage += random(damage / 5);
        if( damage < 0 ) damage = 0;
        return damage;
}

void add_id_into_skills(object me)
{
        mapping skills;
        string id, sname;
        array sk;

        if( wizardp(me) ) return;

        id = me->query("id");

        if( !mapp(skills = me->query_skills()) ||
            sizeof(skills) < 1 )
                return;

        sk = keys(skills);

        foreach( sname in sk )
        {
                if( SKILL_D(sname)->type() != "martial" )
                        continue;

                if( undefinedp(initial_skills[sname]) )
                        continue;

                if( !query(sname + "/" + id) && skills[sname] < 400 )
                        continue;

                if( query(sname + "/" + id) && skills[sname] < 400 )
                {
                        delete(sname + "/" + id);
                        if( !sizeof(query(sname)) )
                                delete(sname);
                        continue;
                }

                set(sname + "/" + id, skills[sname]);
        }
        save();
}

void remove_id_from_skills(object me)
{
        mapping skills;
        string id, sname;
        array sk;

        if( wizardp(me) ) return;

        id = me->query("id");

        if( !mapp(skills = me->query_skills()) ||
            sizeof(skills) < 1 )
                return;

        sk = keys(skills);

        foreach( sname in sk )
        {
                if( SKILL_D(sname)->type() != "martial" )
                        continue;

                if( SKILL_D(sname)->is_invent_skill() )
                        remove_skill_from_skills(me, sname);

                /*
                if( undefinedp(initial_skills[sname] )
                        continue;
                */

                if( !query(sname + "/" + id) )
                        continue;

                delete(sname + "/" + id);
                if( !sizeof(query(sname)) )
                        delete(sname);
        }

        save();
}

void remove_id_from_abandon(object me, string sname)
{
        if( SKILL_D(sname)->type() != "martial" )
                return;

        if( SKILL_D(sname)->is_invent_skill() )
                remove_skill_from_skills(me, sname);

        if( !query(sname + "/" + me->query("id")) )
                return;

        delete(sname + "/" + me->query("id"));
        if( !sizeof(query(sname)) )
                delete(sname);

        save();
}

void upgrade_skill_power(string skill)
{
        array sk;
        int attack, dodge, parry, damage, diffi;
        
        if( undefinedp(all_skills[skill]) )
                return;
                
        sk = all_skills[skill];
        attack = (int)sk[ATTACK];
        dodge  = (int)sk[DODGE];
        parry  = (int)sk[PARRY];
        damage = (int)sk[DAMAGE];
        diffi  = (int)sk[DIFFICULT];
        
        if( attack > MAX_POINT && dodge > MAX_POINT &&
            damage > MAX_POINT && parry > MAX_POINT )
                return;
                
        switch(random(4))
        {
        case 0 :
                if( attack < MAX_POINT ) attack += 1; diffi += 1; break;
        case 1 :
                if( dodge < MAX_POINT ) dodge += 1; diffi += 1; break;
        case 2 :
                if( parry < MAX_POINT ) parry += 1; diffi += 1; break;
        case 3 :
                if( damage < MAX_POINT ) damage += 1; diffi += 1; break;
        }
        
        all_skills[skill] = ({ attack, dodge, parry, damage, 0, 
                diffi, "expert", "private" });
      
        save();  
}
  
void add_skill_into_skills(string sname, mapping p)
{
        array sk;
        string rank, att;
        int attack, dodge, parry, damage, force, diffi;        
        
        if( SKILL_D(sname)->type() != "martial" )
                return;
          
        if( undefinedp(all_skills[sname]) )
        {
                if( !undefinedp(p["rank"]) )
                        rank = p["rank"];
                else
                        rank = "expert";                

                if( !undefinedp(p["attribute"]) )
                        att = p["attribute"];
                else
                        att = "private";      
                
                if( att == "private" )
                        force = 0;
                else
                if( !undefinedp(p["force"]) )
                        force = p["force"];
                else
                        force = 0;
                
                if( !undefinedp(p["difficult"]) ) 
                        diffi = p["difficult"];
                else
                        diffi = 1200;
                                                                               
                sk = ({ p["attack"], p["dodge"], p["parry"], p["damage"], force, 
                        diffi, rank, att });

                all_skills[sname] = sk;
                
                save();
                return;
        } 
        
        sk = all_skills[sname];
        attack = (int)sk[ATTACK];
        dodge  = (int)sk[DODGE];
        parry  = (int)sk[PARRY];
        damage = (int)sk[DAMAGE];
        force  = (int)sk[FORCE];
        diffi  = (int)sk[DIFFICULT];      
                
        if( !undefinedp(p["attack"]) && p["attack"] > attack )
                attack = p["attack"];
        if( !undefinedp(p["dodge"]) && p["dodge"] > dodge )
                dodge = p["dodge"];
        if( !undefinedp(p["parry"]) && p["parry"] > parry )
                parry = p["parry"];     
        if( !undefinedp(p["damage"]) && p["damage"] > damage )
                damage = p["damage"]; 
        if( !undefinedp(p["force"]) && p["force"] > force )
                force = p["force"];
        if( !undefinedp(p["difficult"]) && p["difficult"] > diffi )
                diffi = p["difficult"];
        if( !undefinedp(p["rank"]) )
                rank = p["rank"];
        else
                rank = sk[RANK];
                              
        all_skills[sname] = ({ attack, dodge, parry, damage, force, 
                diffi, rank, sk[ATTRIBUTE] });   
        
        save();               
}

void remove_skill_from_skills(object me, string sname)
{
        if( file_size(SKILL_D(sname) + ".c") < 0 )
                return;

        if( SKILL_D(sname)->type() != "martial" )
                return;

        if( query(sname + "/" + me->query("id")) )
                delete(sname + "/" + me->query("id"));

        if( !sizeof(query(sname)) )
                delete(sname);

        // if( SKILL_D(sname)->is_invent_skill() )
                map_delete(all_skills, sname);

        save();
}

int attack_power(object me, string skill)
{
        int i, value, ap, scale;
        string map_skill;
        string rank;

        if( !objectp(me) ) return 0;

        if( !stringp(map_skill = me->query_skill_mapped(skill)) )
        {
                ap = me->query_skill(skill, 1) / 2 +
                     me->query_skill("martial-cognize", 1) +
                     me->query("level") * 30;

                if( me->query("reborn/times") )
                        ap += ap *
                              me->query("reborn/times") / 10;

                if( me->query_temp("apply/ap_power") )
                        ap += ap *
                              me->query_temp("apply/ap_power") / 100;

                if( me->query_xuruo() ) ap /= 2;

                return ap;
        }

        if( !undefinedp(all_skills[map_skill]) )
        {
                value = all_skills[map_skill][ATTACK];
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 60;
                else
                if( rank == "expert" )
                        scale = 80;
                else
                if( rank == "advance" )
                        scale = 90;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 100;

        ap =(me->query_skill(skill, 1) / 2 + 
             me->query_skill(map_skill, 1)) * value / scale +
             me->query_skill("martial-cognize", 1) +
             me->query("level") * 30;

        if( me->query("reborn/times") )
                ap += ap *
                      me->query("reborn/times") / 10;

        if( me->query_temp("apply/ap_power") )
                ap += ap *
                      me->query_temp("apply/ap_power") / 100;

        if( me->query_xuruo() ) ap /= 2;

        for( i = 0; i < sizeof(all_poison); i++ )
                if( me->query_condition(all_poison[i]) ) 
                {
                        ap = ap * 2 / 3;
                        break;
                }
                
        return ap;
}

int defense_power(object me, string skill)
{
        int i, value, dp, scale;
        string map_skill;
        string rank;

        if( !objectp(me) ) return 0;

        if( !stringp(map_skill = me->query_skill_mapped(skill)) )
        {
                dp = me->query_skill(skill, 1) / 2 +
                     me->query_skill("martial-cognize", 1) +
                     me->query("level") * 30;

                if( me->query("reborn/times") )
                        dp += dp *
                              me->query("reborn/times") / 10;

                if( me->query_temp("apply/dp_power") )
                        dp += dp *
                              me->query_temp("apply/dp_power") / 100;

                if( me->query_xuruo() ) dp /= 2;

                return dp;
        }

        switch( skill )
        {
        case "parry" :
                if( !undefinedp(all_skills[map_skill]) )
                        value = all_skills[map_skill][PARRY];
                break;
        case "dodge" :
                if( !undefinedp(all_skills[map_skill]) )
                        value = all_skills[map_skill][DODGE];
                break;
        case "force" :
                if( !undefinedp(all_skills[map_skill]) )
                        value = all_skills[map_skill][FORCE];
                break;
        default:
                break;
        }

        if( !undefinedp(all_skills[map_skill]) )
        {
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 60;
                else
                if( rank == "expert" )
                        scale = 80;
                else
                if( rank == "advance" )
                        scale = 90;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 100;

        dp =(me->query_skill(skill, 1) / 2 +
             me->query_skill(map_skill, 1)) * value / scale +
             me->query_skill("martial-cognize", 1) +
             me->query("level") * 30;

        if( me->query("reborn/times") )
                dp += dp *
                      me->query("reborn/times") / 10;

        if( me->query_temp("apply/dp_power") )
                dp += dp *
                      me->query_temp("apply/dp_power") / 100;

        if( me->query_xuruo() ) dp /= 2;

        for( i = 0; i < sizeof(all_poison); i++ )
                if( me->query_condition(all_poison[i]) ) 
                {
                        dp = dp * 2 / 3;
                        break;
                }
                
        return dp;
}


int damage_power(object me, string skill)
{
        int i, value, damage, scale;
        string map_skill;
        string rank;

        if( !objectp(me) ) return 0;

        if( !stringp(map_skill = me->query_skill_mapped(skill)) )
        {
                damage = me->query_skill(skill, 1) / 2 +
                         me->query_skill("martial-cognize", 1) +
                         me->query("level") * 30;

                /*
                if( me->query("reborn/times") )
                        damage += damage *
                                  me->query("reborn/times") / 10;
                */

                if( me->query_temp("apply/da_power") )
                        damage += damage / 100 *
                                  me->query_temp("apply/da_power");

                if( me->query_xuruo() ) damage /= 2;

                damage += random(damage / 5);
                return damage;
        }

        if( !undefinedp(all_skills[map_skill]) )
        {
                value = all_skills[map_skill][DAMAGE];
                rank = all_skills[map_skill][RANK];

                if( rank == "ultimate" )
                        scale = 12;
                else
                if( rank == "expert" )
                        scale = 16;
                else
                if( rank == "advance" )
                        scale = 18;
        }

        if( !value ) value = 100;
        if( !scale ) scale = 20;
        
        damage =(me->query_skill(skill, 1) / 2 +
                 me->query_skill(map_skill, 1)) * value / scale +
                 me->query_skill("martial-cognize", 1) +
                 me->query("level") * 30;

        /*
        if( me->query("reborn/times") )
                damage += damage *
                          me->query("reborn/times") / 10;
        */

        if( me->query_temp("apply/da_power") )
                damage += damage / 100 *
                          me->query_temp("apply/da_power");

        if( me->query_xuruo() )
                damage /= 2;
        
        for( i = 0; i < sizeof(all_poison); i++ )
                if( me->query_condition(all_poison[i]) ) 
                {
                        damage = damage * 2 / 3;
                        break;
                }

        damage += random(damage / 5);
        return damage;
}

mapping trans_data(string mark)
{
        int     i;
        mixed   temp_value;
        string  temp_str;
        string  *temp_arr, *temp_val;
        string  temp_key, key;
        mapping temp_stats;
        mapping temp_map;

        temp_stats = ([ ]);
        // 开始解析
        while (sscanf(mark, "%*s<%s>%s</%s>%s", key, temp_str, key, mark) > 3)
        {
                temp_map = ([ ]);
                temp_arr = explode(temp_str, "\n");
                if (sizeof(temp_arr) < 2)
                {
                        if (atoi(temp_str))
                                temp_stats[key] = atoi(temp_str);
                        else
                                temp_stats[key] = temp_str;
                       
                } else
                {
                        for (i = 0; i < sizeof(temp_arr); i++)
                        {
                                temp_arr[i] = replace_string(temp_arr[i], " ", "");
                                if (sscanf(temp_arr[i], "%s:%d", temp_key, temp_value) != 2)
                                        sscanf(temp_arr[i], "%s:%s", temp_key, temp_value);
                                
                                // 解析VALUE      
                                if (stringp(temp_value) && strsrch(temp_value, '/') != -1)
                                {       
                                        temp_val = explode(temp_value, "/");
                                        temp_value = ({ });
                                        for (i = 0; i <sizeof(temp_val); i++)
                                                if (atoi(temp_val[i]))
                                                        temp_value += atoi(temp_val[i]);
                                                else
                                                        temp_value += temp_val[i];
                                }                   
                                // 解析KEY   
                                if (stringp(temp_key) && strsrch(temp_key, '/') != -1) 
                                        _set( temp_map, explode(temp_key, "/"), temp_value ); 
                                else
                                        temp_map[temp_key] = temp_value;
                        }
                        temp_stats[key] = temp_map;
                }
        }

        if ( !undefinedp(temp_stats["name"]) )
                temp_stats["name"] = trans_color(temp_stats["name"], 3);

        if ( !undefinedp(temp_stats["long"]) )
                temp_stats["long"] += "\n";
                
        return temp_stats;
}

void disable_skill_mix(object me)
{
        mapping stats, applied_prop;
        array apply;
        int i, flag;
        
        if (! me->query("skill_mix"))
                return;
                                      
        stats = copy(me->query("skill_mix"));
        apply = keys(stats);
        if ( sizeof(apply) )
        {                                
                if( !mapp(me->query_temp("apply")) ) 
                        applied_prop = ([]);
                else
                        applied_prop = me->query_temp("apply");
                for(i = 0; i<sizeof(apply); i++)
                {
                        if (apply[i] == "int" || apply[i] == "str" || 
                            apply[i] == "con" || apply[i] == "add_skill" || 
                            apply[i] == "max_qi" || apply[i] == "max_jing") 
                                flag = 1; 

                        applied_prop[apply[i]] -= stats[apply[i]];
                }
             
                me->set_temp("apply", applied_prop); 
                if (flag) CHAR_D->setup_char(me);  
        }
        me->delete("skill_mix");
}

varargs void enable_skill_mix(object me, mapping stats, mapping need)
{
        mapping applied_prop;
        array apply;
        int i, flag;
        
        if (! mapp(stats) || ! sizeof(stats))
                return;
        
        if (mapp(need) && sizeof(need))
        {
                apply = keys(need);
                for(i = 0; i<sizeof(apply); i++)
                        if (me->query_skill(apply[i], 1) < need[apply[i]])
                                return;
        }
                      
        apply = keys(stats);
        if ( sizeof(apply) )
        {                                
                if( !mapp(me->query_temp("apply")) ) 
                        applied_prop = ([]);
                else
                        applied_prop = me->query_temp("apply");
                for(i = 0; i<sizeof(apply); i++)
                {
                        if (apply[i] == "int" || apply[i] == "str" || 
                            apply[i] == "con" || apply[i] == "add_skill" || 
                            apply[i] == "max_qi" || apply[i] == "max_jing") 
                                flag = 1; 

                        if( undefinedp(applied_prop[apply[i]]) )
                                applied_prop[apply[i]] = stats[apply[i]];
                        else
                                applied_prop[apply[i]] += stats[apply[i]];
                }
                me->set_temp("apply", applied_prop);
                if (flag) CHAR_D->setup_char(me);  
        }
        me->set("skill_mix", stats);
}   
     
public void check_skill_mix(object me, int flag)
{
        class mix temp;
        mixed stats;
        
        if (! flag)
        {
                disable_skill_mix(me);
                return;
        }
        temp = new(class mix);
        temp = find_skill_mix(me);       
        if (flag)  
        {
                if (! temp->stats)
                {
                       disable_skill_mix(me); 
                       return;
                }
        }
        if (flag == 2)
        {                
                if (! me->query("skill_mix"))
                {
                       enable_skill_mix(me, temp->stats, temp->need); 
                       return;
                }      
                stats = me->query("skill_mix");                         
                if (! mapping_eqv(temp->stats, stats))
                {
                        disable_skill_mix(me);                    
                        enable_skill_mix(me, temp->stats, temp->need); 
                }
        }
}
                        
void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}
