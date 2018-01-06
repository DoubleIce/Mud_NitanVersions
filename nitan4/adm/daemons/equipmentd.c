// This program is a part of NITAN MudLIB
// equipmentd.c

#pragma optimize
#pragma save_binary

inherit F_DBASE;
#include <equipment.h>

#define BASIC_OB_DIR    "/inherit/template/"
#define EQUIP_LIST      "/adm/etc/equiplist/"

nosave array percent_stats = ({
        "add_cold", "add_fire", "add_lighting", "add_poison", "add_magic", "add_wind",
        "reduce_cold", "reduce_fire", "reduce_lighting", "reduce_poison", "reduce_wind",
        "reduce_magic", "research_effect", "learn_effect", "practice_effect", 
        "derive_effect", "study_effect", "ap_power", "dp_power", "da_power",
        "add_xuruo", "add_damage", "avoid_locked", "avoid_busy", "reduce_locked", 
        "avoid_xuruo", "reduce_damage", "add_locked", "double_damage",
        "avoid_attack", "avoid_parry", "avoid_dodge",
});

nosave mapping all_stats = ([
        "int"   : "����",
        "str"   : "����",
        "con"   : "����",
        "dex"   : "��",
        "max_neili"     : "��������",
        "max_jingli"    : "��������",
        "max_qi"        : "��Ѫ����",
        "max_jing"      : "��������",
        "max_potential" : "Ǳ������",
        "max_experience": "�������",
        "attack"        : "������Ч�ȼ�",
        "defense"       : "������Ч�ȼ�",
        "parry"         : "�м���Ч�ȼ�",
        "dodge"         : "������Ч�ȼ�",
        "armor"         : "������",
        "damage"        : "�����˺���",
        "unarmed_damage": "ȭ���˺���",
        "ap_power"      : "���й�����",
        "dp_power"      : "���з�����",
        "da_power"      : "�����˺���",
	"qi_damage"     : "���ɶ�����Ѫ",
	"jing_damage"   : "���ɶ��־���",
        "suck_qi"       : "��ȡ���ֵ���Ѫ",
        "suck_jing"     : "��ȡ���ֵľ���",
        "suck_neili"    : "��ȡ���ֵ�����",
        "add_reward"    : "��ȡ���⾭�齱��",
        "add_gold"      : "��ȡ�ƽ���",
        "magic_find"    : "Ѱ����(MFֵ)",
        "add_poison"            : "�����˺�",
        "add_cold"              : "�䶳�˺�",
        "add_fire"              : "�����˺�",
        "add_lighting"          : "�����˺�",
        "add_wind"              : "�����˺�",
        "add_magic"             : "ħ���˺�",
        "reduce_poison"         : "����",
        "reduce_cold"           : "����",
        "reduce_fire"           : "����",
        "reduce_lighting"       : "����",
        "reduce_wind"           : "����",
        "reduce_magic"          : "��ħ",
        "eff_jing"       : "ÿ�뾫���ָ�",
        "eff_qi"         : "ÿ����Ѫ�ָ�",
        "research_effect"       : "�о�Ч��",
        "practice_effect"       : "��ϰЧ��",
        "derive_effect"         : "��ȡЧ��",
        "research_times": "�о�����",
        "learn_times"   : "ѧϰ����",
        "practice_times": "��ϰ����",
        "derive_times"  : "��ȡ����",
        "study_times"   : "�������",
        "study_effect"  : "����Ч��",
        "learn_effect"  : "ѧϰЧ��",
        "avoid_parry"   : "���Ӷ��������мܷ���",               // ���ķ���
        "avoid_dodge"   : "���Ӷ��������������",               // ���ķ���
        "avoid_attack"  : "���Ӷ������⹥��",               // ���ķ���
        "avoid_force"   : "���Ӷ��������ڹ�����",
        "reduce_age"    : "����",
        "double_damage" : "˫���˺�����",

        "def_damage"    : "���ɶ��־�Ѫ",
        "avoid_locked"  : "������б���",               // �ռ�����
        "add_locked"    : "�����־���",               // �ռ�����
        "add_busy"      : "ս��æ�Ҷ���",               // �ռ�����
        "reduce_busy"   : "����ս��æ��",               // �ռ�����
        "add_xuruo"     : "��������",                   // �ռ�����
        "avoid_xuruo"   : "�ر�����",                   // �ռ�����
        "avoid_busy"    : "����æ��",                   // �ռ�����
        "add_skill"     : "���м���",                   // �ռ�����
        "add_damage"    : "׷���˺�",                   // �ռ�����
        "reduce_damage" : "�����˺�",                   // �ռ�����
]);

nosave mapping stats_value = ([
        "ap_power,dp_power,da_power,reduce_age,int,str,con,dex" : ({ 1, 2, 3, 4, 5, 6, 7 }),
        "max_neili,max_jingli"  : ({ 1000, 1500, 2000, 1500, 3000, 3500, 4000 }),
        "attack,defense,parry,dodge"    : ({ 10, 15, 20, 25, 30, 35, 40 }),
        "eff_jing,eff_qi" : ({ 20, 30, 40, 50, 60, 70, 80 }),
        "suck_qi,suck_neili"    : ({ 200, 300, 400, 500, 600, 700, 800 }),
        "max_potential,max_experience"  : ({ 100000, 150000, 200000, 150000, 300000, 350000, 400000 }),
        "max_qi,max_jing,damage,unarmed_damage,qi_damage,jing_damage,def_damage,armor"  : ({ 200, 300, 400, 500, 600, 700, 800 }),
        "research_times,learn_times,practice_times,derive_times,study_times" : ({ 1, 2, 3, 4, 5, 6, 7 }),
        "add_cold,add_fire,add_lighting,add_poison,add_magic,add_wind" : ({ 5, 8, 11, 14, 17, 20, 23 }),
        "reduce_cold,reduce_fire,reduce_lighting,reduce_poison,reduce_magic,reduce_wind" : ({ 1, 2, 3, 4, 5, 6, 7 }),
        "research_effect,learn_effect,practice_effect,derive_effect,study_effect": ({ 1, 2, 3 }),

        "add_skill"     : ({ 200, 250, 300, 400 }),
        "add_busy"      : ({ 1, 3, 5, 7, 9, 11 }),
        "reduce_busy"   : ({ 2, 3, 4 }),
        "reduce_damage" : ({ 7, 9, 11, 13 }),
        "add_locked,avoid_xuruo"              : ({ 5, 7, 9, 11, 13 }),
        "double_damage"              : ({ 1, 2, 3 }),
        "add_xuruo,add_damage,avoid_locked"       : ({ 20, 25, 30, 35 }),
]);

nosave array weapon_stats = ({
        "int", "str", "con", "dex", "attack", "damage", "add_cold",
        "add_fire", "add_lighting", "add_poison", "add_magic", "add_wind",
        "max_neili", "max_jingli", "max_qi", "max_jing", "max_potential",
        "max_experience", "research_effect", "learn_effect",
        "practice_effect", "derive_effect", "study_effect", "research_times",
        "learn_times", "practice_times","derive_times", "study_times",
        "ap_power", "da_power", "double_damage",
        "suck_qi", "suck_neili",
});

nosave array armor_stats = ({
        "int", "str", "con", "dex", "defense", "parry", "dodge", "armor",
        "reduce_poison", "reduce_cold", "reduce_fire", "reduce_wind",
        "reduce_lighting", "reduce_magic", "unarmed_damage",
        "max_neili", "max_jingli", "max_qi", "max_jing",
        "max_potential", "max_experience", "eff_jing", "eff_qi",
        "research_effect", "learn_effect", "practice_effect", "derive_effect",
        "study_effect", "research_times", "learn_times", "practice_times",
        "derive_times", "study_times", "dp_power", 
});

nosave array ultimate_stats = ({
        "add_busy", "reduce_busy", "avoid_busy", "add_xuruo", "qi_damage", "jing_damage",
        "avoid_xuruo, add_locked", "reduce_locked", "add_damage", "reduce_damage",
});

protected mapping trans_data(string mark);
protected mapping add_stats(string type, int level);

void create()
{
        seteuid(getuid());
        set("name", "װ������");
        set("id", "equipmentd");
}

// Ϊ��������ƥ������
string chinese(string stats, int value)
{
        string desc;

        if( !undefinedp(all_stats[stats]) )
                desc = all_stats[stats];
        else
                desc = to_chinese(stats);

        if( member_array(stats, percent_stats) != -1 )
                desc = sprintf(HIB "%s %s%d%s" NOR, desc,
                               value > 0 ? "+" : "-", abs(value), "%");
        else
                desc = sprintf(HIB "%s %s%d" NOR, desc,
                               value > 0 ? "+" : "-", abs(value));
        /*
        msg = terminal_colour(color_filter(read_file("/adm/etc/logind_motd")), ([
                "MUD_NAME"      : CHINESE_MUD_NAME,
                "ENGLISH_NAME"  : ENGLISH_MUD_NAME,
                "MUDLIB_VERSION": MUDLIB_VERSION_NUMBER,
                "MUDOS_VERSION" : __VERSION__ ,
                "ARCH"          : __ARCH__,
                "UPDATE"        : TIME_D->replace_ctime(stat(MOTD)[1]),
        ]));
        */
        return desc;
}

varargs int query_stats_value(string stats, int level)
{
        int i, j, flag;
        int *value;
        array temp_stats;
        array temp_str;

        flag = 0;
        temp_stats = keys(stats_value);
        for( i=0; i<sizeof(temp_stats); i++ )
        {
                reset_eval_cost();
                temp_str = explode(temp_stats[i], ",");
                for( j=0; j<sizeof(temp_str); j++ )
                        if( temp_str[j] == stats )
                        {
                                value = stats_value[temp_stats[i]];
                                flag = 1;
                                break;
                        }
                if( flag ) break;
        }
        if( !flag || !value ) return 0;
        if( level )
        {
                if( level > sizeof(value) )
                        level = sizeof(value);

                return value[level-1];
        }
        return value[random(sizeof(value))];
}

mixed *apply_stats(string type, int level)
{
        array prop;
        array stats;
        string p1, p2, p3, p4, p5, p6, p7;

        if( type == "weapon" ) 
                prop = weapon_stats;
        else    prop = armor_stats;

        p1 = prop[random(sizeof(prop))];
        prop -= ({ p1 });
        p2 = prop[random(sizeof(prop))];
        prop -= ({ p2 });
        p3 = prop[random(sizeof(prop))];
        prop -= ({ p3 });
        p4 = prop[random(sizeof(prop))];
        prop -= ({ p4 });
        p5 = prop[random(sizeof(prop))];
        prop -= ({ p5 });
        p6 = prop[random(sizeof(prop))];
        prop -= ({ p6 });
        p7 = prop[random(sizeof(prop))];

        if( level == 1 ) stats = ({ p1 });
        else if( level == 2 ) stats = ({ p1, p2 });
        else if( level == 3 ) stats = ({ p1, p2, p3 });
        else if( level == 4 ) stats = ({ p1, p2, p3, p4 });
        else if( level == 5 ) stats = ({ p1, p2, p3, p4, p5 });
        else if( level == 6 ) stats = ({ p1, p2, p3, p4, p5, p6 });
        else stats = ({ p1, p2, p3, p4, p5, p6, p7 });

        return stats;
}

// ����һ��������������
varargs mixed create_object(string num, int level)
{
        array   list;
        string  mark, part, rec;
        string  type, str;
        string  filename, this_file;
        mapping temp_stats;
        mapping temp_function;
        object  ob;

        if ( !num || num == "" )
        {
                if( !level ) level = random(3);

                switch ( random(3) )
                {
                case 0 :
                        rec = "W";
                        if (level == 0) filename = EQUIP_LIST+"basic.weapon";
                        else if (level == 1) filename = EQUIP_LIST+"advance.weapon";
                        else if (level == 2) filename = EQUIP_LIST+"expert.weapon";
                        break;
                case 1 :
                        rec = "A";
                        if (level == 0) filename = EQUIP_LIST+"basic.armor";
                        else if (level == 1) filename = EQUIP_LIST+"advance.armor";
                        else if (level == 2) filename = EQUIP_LIST+"expert.armor";
                        break;
                default:
                        rec = "G";
                        if (level == 0) filename = EQUIP_LIST+"basic.gem";
                        else if (level == 1) filename = EQUIP_LIST+"advance.gem";
                        else if (level == 2) filename = EQUIP_LIST+"expert.gem";
                        break;
                }

                this_file = read_file(filename);
                str = sprintf("%s%d", rec, level);
                list = ({ });
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if (! sizeof(list)) return 0;
                num = list[random(sizeof(list))];
        } else
        {
                // �������
                if ( num[0] == 'W' )
                {
                        if ( num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.weapon";
                        else if ( num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.weapon";
                        else if ( num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.weapon";
                } else
                // �������
                if ( num[0] == 'A' )
                {
                        if ( num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.armor";
                        else if ( num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.armor";
                        else if ( num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.armor";
                } else
                // ��ʯ���
                if ( num[0] == 'G' )
                {
                        if ( num[1] == '0' && strlen(num) == 5)
                                filename = EQUIP_LIST+"basic.gen";
                        else if ( num[1] == '1' && strlen(num) == 5)
                                filename = EQUIP_LIST+"advance.gen";
                        else if ( num[1] == '2' && strlen(num) == 5)
                                filename = EQUIP_LIST+"expert.gen";
                }

                if (! filename)
                        return 0;

                this_file = read_file(filename);
        }

        //������Ŷ�Ӧ���ַ���
        if ( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) )
        {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = BASIC_OB_DIR + type;
                temp_stats = trans_data(mark);
                temp_function = temp_stats["function"];
                if (temp_function)
                        map_delete(temp_stats, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_stats["id"], temp_stats, 1, temp_function);
                ob->set("mark",num);
                if (temp_stats["mod"])
                        ob->set("mod",temp_stats["mod"]);

                return ob;
        } else
        {
                CHANNEL_D->do_channel(this_object(),"sys", "����һ������������");
                return 0;
        }
}

// ����һ����װ�������������
varargs object create_module(string num, int level)
{
        string mark, part, str, rec;
        array  list;
        string type;
        string filename, this_file;
        mapping temp_stats;
        mapping temp_function;
        object ob;

        if ( !num || num == "" )
        {
                if (! level) level = random(4);

                if (level == 0) filename = EQUIP_LIST+"basic.mod";
                else if (level == 1) filename = EQUIP_LIST+"advance.mod";
                else if (level == 2) filename = EQUIP_LIST+"expert.mod";
                else if (level == 3) filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
                str = sprintf("A%d", level);
                list = ({ });
                while (sscanf(this_file, "%*s<"+str+part+">%*s</"+str+part+">%*s"))
                {
                        rec = sprintf("%s%s", str, part);
                        list += ({ rec });
                }
                if (! sizeof(list)) return 0;
                num = list[random(sizeof(list))];
        } else
        {
                if ( num[1] == '0' && strlen(num) == 5)
                        filename = EQUIP_LIST+"basic.mod";
                else if ( num[1] == '1' && strlen(num) == 5)
                        filename = EQUIP_LIST+"advance.mod";
                else if ( num[1] == '2' && strlen(num) == 5)
                        filename = EQUIP_LIST+"expert.mod";
                else if ( num[1] == '3' && strlen(num) == 5)
                        filename = EQUIP_LIST+"boss.mod";

                this_file = read_file(filename);
        }
        //������Ŷ�Ӧ���ַ���
        if ( sscanf(this_file, "%*s<"+num+">%s</"+num+">%*s", mark) )
        {
                sscanf(mark, "%*s<type>%s</type>%s", type, mark);
                filename = BASIC_OB_DIR + type;
                temp_stats = trans_data(mark);
                temp_function = temp_stats["function"];
                if (temp_function)
                        map_delete(temp_stats, "function");
                else
                        temp_function = allocate_mapping(0);

                ob = TEMPLATE_D->create_object(filename, temp_stats["id"], temp_stats, 1, temp_function);
                ob->set("mark",num);
                if (temp_stats["mod"])
                        ob->set("mod",temp_stats["mod"]);

                return ob;
        } else
                CHANNEL_D->do_channel(this_object(), "sys", "����һ����װ��������");
}

// ����һ����Ʒ���������ͺ͵ȼ�
public varargs object create_equip(string type, int level, int flag)
{
        mapping temp_stats, all_list, data;
        array  all_id, types;
        string id;
        string color, filename;
        string base_type;
        object ob;

        if( !type || type == "" )
        {
                int rate;

                if( !level ) level = random(80);
                rate = random(100);
                if( rate < 40 )
	                type = "gem";
	        else
                if( rate < 70 )
		        type = "weapon";
	        else
		        type = "armor";

		flag = 0;
        }

        if( flag )
        {
                if( flag == 1 )
                {
                        if( member_array(type, weapon_type) != -1 )
                                base_type = "weapon";
                        else
                        if( member_array(type, armor_type) != -1 )
                                base_type = "armor";
                        else
                                base_type = "gem";
                } else
                {
                        all_list = name_list[type];
                        all_id = values(all_list);
                        id = all_id[random(sizeof(all_id))];
                }
        } else
        {
                base_type = type;
                types = type_list[type];
                type = types[random(sizeof(types))];
        }

        if( flag && flag > 1 ) // ��ģ���ļ�
                filename = sprintf("%s%s/%s.c", TEMPLATE_DIR, base_type, type);
        else
                filename = sprintf("%s%s/%s.c", BASIC_OB_DIR, base_type, type);

        temp_stats = ([ ]);
        data = ([ "level" : level / 10 ]);
        temp_stats["need"] = copy(data);
        if( base_type == "weapon" )
        {
                data = ([ "damage" : level * 10 ]);
                temp_stats["weapon_prop"] = copy(data);
        } else
        if( base_type == "armor" )
        {
                data = ([ "armor" : level * 10 ]);
                temp_stats["armor_prop"] = copy(data);
        }      
        temp_stats += add_stats(type, level / 10);

        ob = TEMPLATE_D->create_object(filename, type, temp_stats, 1);

        if( base_type != "gem" )
        {
                level /= 10;
                if( level > 8 ) color = HIY;
                else if( level > 6 ) color = HIB;
                else if( level > 4 ) color = HIG;
                else if( level > 2 ) color = HIW;
                else color = NOR;
                ob->set_color(color);
        }

        return ob;
}

protected mapping trans_data(string mark)
{
        int     i;
        mixed   temp_value;
        string  temp_str;
        array   temp_arr, temp_val;
        string  temp_key, key;
        mapping temp_stats;
        mapping temp_map;

        temp_stats = ([ ]);
        // ��ʼ����
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

                                // ����VALUE
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
                                // ����KEY
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

protected mapping add_stats(string type, int level)
{
        array stats;
        mapping dbase;
        mapping data;
        mapping temp;
        int i, flute;

        data = ([ ]);
        temp = ([ ]);
        dbase = ([ ]);

        if (type == "gem")
        {
                stats = apply_stats("weapon", level);
                for( i = 0; i < sizeof(stats); i++ )
                        //temp[stats[i]] = query_stats_value(stats[i], level);
                        temp[stats[i]] = query_stats_value(stats[i], level) + random(30);
                dbase["weapon_prop"] = temp;

                temp = ([ ]);

                stats = apply_stats("armor", level);
                for( i = 0; i < sizeof(stats); i++ )
                        //temp[stats[i]] = query_stats_value(stats[i], level);
                        temp[stats[i]] = query_stats_value(stats[i], level) + random(20);
                dbase["armor_prop"] = temp;
        }
        else
        {
                stats = apply_stats(type, level);
                for( i = 0; i < sizeof(stats); i++ )
                        temp[stats[i]] = query_stats_value(stats[i], level);
                dbase["apply_prop"] = temp;
        }

        flute = random(level);
        if( flute > 5 ) flute = 5;
        if( flute < 1 ) flute = 1;
        dbase["flute"]  = flute;
        data["enchase"] = dbase;

        return data;
}

public varargs void killer_reward(object killer, object victim, mapping award_rate)
{
        object award_ob, *reward, *obs;
        array  award_key;
        string ob_file, ob_quality, ob_num, ob_typ;
        int i, real_rate, level, team_size;

        if ( !mapp(award_rate) || !sizeof(award_rate) )
                return;

	obs = pointerp(killer->query_team()) ? killer->query_team() : ({ killer });
	team_size = sizeof(filter_array(obs, (: objectp($1) && environment($1) == environment($(killer)) :)));

        reward = ({ });
        award_key = keys(award_rate);
        for (i = 0; i < sizeof(award_key); i++)
        {
                real_rate = award_rate[award_key[i]];
                if (team_size >= 5)
                        real_rate = real_rate * 220 / 100;
                else if (team_size == 4)
                        real_rate = real_rate * 182 / 100;
                else if (team_size == 3)
                        real_rate = real_rate * 152 / 100;
                else if (team_size == 2)
                        real_rate = real_rate * 121 / 100;
                /*
                else
                        real_rate = real_rate * 89 / 100;
                */

                if (MEMBER_D->is_valid_member(killer))
                        real_rate *= 2;

                if (random(10000) < real_rate)
                {
                        // �������йؼ����� F I ��ͷ��ʾΪ����ĳ����Ʒ
                        if (award_key[i][0..1] == "FI")
                                if ( sscanf(award_key[i], "FI&%s", ob_file) )
                                        if (objectp(award_ob = new(ob_file)))
                                                reward += ({ award_ob });

                        // �������йؼ����� S E ��ͷ��ʾΪ����ĳ����ŵ���Ʒ
                        if (award_key[i][0..1] == "NU")
                                if ( sscanf(award_key[i], "NU&%s", ob_num) )
                                        if (objectp(award_ob = create_object(ob_num)))
                                                reward += ({ award_ob });

                        // �������йؼ����� T Y ��ͷ��ʾΪ����ĳ�����͵���Ʒ
                        if (award_key[i][0..1] == "TY")
                                if ( sscanf(award_key[i], "TY&%s%d", ob_typ, level) == 2 )
                                        if (objectp(award_ob = create_equip(ob_typ, level)))
                                                reward += ({ award_ob });

                        // �������йؼ����� M O ��ͷ��ʾΪ����ĳ����ŵ���װ����
                        if (award_key[i][0..1] == "MO")
                                if ( sscanf(award_key[i], "MO&%s", ob_num) )
                                        if (objectp(award_ob = create_module(ob_num)))
                                                reward += ({ award_ob });

                        // �������йؼ����� R A ��ͷ��ʾΪ����ĳ��Ʒ�ʵĵ������Ʒ���������ĳ��װ��
                        if (award_key[i][0..1] == "RA")
                        {
                                if ( sscanf(award_key[i], "RA&%s%d", ob_quality, level) == 2 )
                                {
                                        switch (ob_quality)
                                        {
                                        case "MODULE"   :
                                                award_ob = create_module("", level);
                                                break;
                                        case "NUMBER"   :
                                                award_ob = create_object("", level);
                                                break;
                                        case "RANDOM"   :
                                                award_ob = create_equip("", level);
                                        default         :
                                                break;
                                        }
                                        if (objectp(award_ob))
                                                reward += ({ award_ob });
                                }
                        }
                }
        }

        if (!arrayp(reward) || !sizeof(reward))
                return ;

        for (i = 0; i < sizeof(reward); i++)
                reward[i]->move(environment(killer));

        return;
}
