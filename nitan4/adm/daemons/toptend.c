#include <ansi.h>
#include <mudlib.h>
#include <getconfig.h>

#define TOPTEN_RICH     "/data/topten/rich.txt"
#define TOPTEN_PKER     "/data/topten/pker.txt"
#define TOPTEN_EXP      "/data/topten/exp.txt"
#define TOPTEN_AGE      "/data/topten/age.txt"
#define TOPTEN_KILLED   "/data/topten/killed.txt"
#define RICH_B          "十大富翁排行榜"
#define PKER_B          "十大魔头排行榜"
#define EXP_B           "十大高手排行榜"
#define AGE_B           "十大老手排行榜"
#define KILLED_B        "十大悲情人物排行榜"

int paiming;
void topten_checkplayer(object);
mixed get_all_data(object, string);
int topten_del(string, string);
int topten_add(object, string);
int topten_save(string, string, string);
string topten_query(string);

void topten_checkplayer(object player)
{
        if (! wizardp(player))
        {
        	paiming = 0;
        	topten_add(player, "rich");
        	topten_add(player, "pker");
        	topten_add(player, "exp");
        	topten_add(player, "age");
        	topten_add(player, "killed");
        }
        return;
}

int topten_save(string f_name, string b_name, string str)
{
        array astr;
        int i;
        
        astr = explode(str, "\n");
        str = "";
        
        for (i = 0; i < sizeof(astr) && i < 10; i++)
                str += astr[i] + "\n";
                
        if (! write_file(f_name, str, 1))
                return notify_fail("无法写文件" + f_name + "，权限不够！不能更新" + b_name + "！\n");
                
        if (paiming > 0 && paiming <= 10)
                write("\t你名列最近" YEL + b_name + NOR "第" RED + chinese_number(paiming) + NOR "名！\n");
        paiming = 0;
        return 1;
}

string topten_query(string type)
{
        string b_name, f_name, str, *astr, *bstr, title, name, id;
        int i, j, k;
        mixed data;
        
        array top = ({
                YEL"    ΩΩΩΩΩΩΩ=    " + LOCAL_MUD_NAME() + "十大富翁排行榜    =ΩΩΩΩΩΩΩΩ\n",
                GRN"    ♀♀♀♀♀♀♀=    " + LOCAL_MUD_NAME() + "十大高手排行榜    =♀♀♀♀♀♀♀♀\n",
                RED"    ※※※※※※※=    " + LOCAL_MUD_NAME() + "十大魔头排行榜    =※※※※※※※※\n",
                CYN"    ≈≈≈≈≈≈≈=    " + LOCAL_MUD_NAME() + "十大老手排行榜    =≈≈≈≈≈≈≈≈\n",
                BLU"    〓〓〓〓〓〓〓   " + LOCAL_MUD_NAME() + "十大悲情人物排行榜   〓〓〓〓〓〓〓〓\n",
                });
        array bottom = ({
                YEL"    ΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩΩ\n"NOR,
                GRN"    ♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂♂\n"NOR,
                RED"    ※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"NOR,
                CYN"    ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈\n"NOR,
                BLU"    〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓\n"NOR,
                });
        array middle = ({
                YEL"    ＄                                                          ＄\n",
                GRN"    ☆                                                          ☆\n",
                RED"    ★                                                          ★\n",
                CYN"    §                                                          §\n",
                BLU"    △                                                          △\n",
                });
        array str_left = ({
                YEL"    ＄ "MAG,
                GRN"    ☆ "YEL,
                RED"    ★ "BLU,
                CYN"    § "YEL,
                BLU"    △ "MAG,
                });
        array str_center = ({
                GRN,
                CYN,
                MAG,
                WHT,
                CYN,
                });
        array str_right = ({
                YEL "      ＄\n"NOR,
                GRN "      ☆\n"NOR,
                RED "      ★\n"NOR,
                CYN "      §\n"NOR,
                BLU "      △\n"NOR,
                });
        
        switch(type)
        {
                case "rich":
                        k = 0;
                        b_name = RICH_B;
                        f_name = TOPTEN_RICH;
                        break;
                case "pker":
                        k = 2;
                        b_name = PKER_B;
                        f_name = TOPTEN_PKER;
                        break;
                case "exp":
                        k = 1;
                        b_name = EXP_B;
                        f_name = TOPTEN_EXP;
                        break;
                case "age":
                        k = 3;
                        b_name = AGE_B;
                        f_name = TOPTEN_AGE;
                        break;
                case "killed":
                        k = 4;
                        b_name = KILLED_B;
                        f_name = TOPTEN_KILLED;
                        break; 
                default:
                        return "对不起，暂时没有这种排行榜！\n";
        }
        
        if (file_size(f_name) == -1)
                return b_name + "的数据文件还没有创建！\n";
                
        astr = explode(read_file(f_name), "\n");
        str = top[k] + middle[k];
        paiming = 0;
        for (i = 0; i < sizeof(astr) && paiming < 10; i++)
        {                
                bstr = explode(astr[i], ";");
                for (j = 0; j < sizeof(bstr) && paiming + j < 10; j++)
                {
                        if (sscanf(bstr[j],"%s(%s)%d", name, id, data) != 3)
                                return "数据错误!文件：" + f_name + "第" + i + "行第" + j + "项！\n" +
                                        "该行数据：" + bstr[j] + "\n";
                        
                        title = "排行第" + chinese_number(paiming + 1) + ":";
                        if (j >= 1) 
                                title = "并列第" + chinese_number(paiming + 1) + ":";
                        str += str_left[k] + sprintf("%24s %s %-25s", title, 
                               str_center[k], name+"("+id+")") + str_right[k];            
                
                }
                paiming += sizeof(bstr);
            }
            
       str += middle[k];
       str += bottom[k];
       return str;
}

mixed get_all_data(object player, string type)
{
        mixed total;
        
        switch(type)
        {
                case "rich":
                        total = MONEY_D->player_carry(player);
                        break;
                case "pker":
                        total = player->query("combat/WPKEXP");
                        break;
                case "exp":
                        total = this_player()->query("combat_exp");
                        break;
                case "age":
                        total = (int)player->query("mud_age");
                        break;
                case "killed":
                        total = player->query("combat/dieexp");
                        break;
                default:
                        total = -1; 
        }
        return total;
}

int topten_del(string pid,string type)
{
        string str, *astr, *bstr, b_name, f_name;
        int i, j, k;
        
        switch(type)
        {
                case "rich":
                        b_name = RICH_B;
                        f_name = TOPTEN_RICH;
                        break;
                case "pker":
                        b_name = PKER_B;
                        f_name = TOPTEN_PKER;
                        break;
                case "exp":
                        b_name = EXP_B;
                        f_name = TOPTEN_EXP;
                        break;
                case "age":
                        b_name = AGE_B;
                        f_name = TOPTEN_AGE;
                        break;
                case "killed":
                        b_name = KILLED_B;
                        f_name = TOPTEN_KILLED;
                        break;
               default:
                        return notify_fail("没有" + type + "这种排行榜！\n");
        }
        
        if (file_size(f_name) == -1)
                return notify_fail(b_name + "还没有创建！\n");
                
        str = read_file(f_name);
        astr = explode(str, "\n");
        
        for (i = 0; i < sizeof(astr); i++)
        {
                if (strsrch(astr[i], pid) != -1)
                {
                        if (strsrch(astr[i], ";") == -1)
                        {
                                str = "";
                                for (j = 0; j < sizeof(astr); j++)
                                        if (j != i)
                                                str += astr[j] + "\n";
                                return topten_save(f_name, b_name, str);
                        }
                        else
                        {
                                bstr = explode(astr[i], ";");
                                for (j = 0; j < sizeof(bstr); j++)
                                        if (strsrch(bstr[j], pid) != -1)
                                        {
                                                astr[i] = "";
                                                for (k = 0; k <sizeof(bstr); k++)
                                                        if (k != j)
                                                        {
                                                                if ((k + 1) != sizeof(bstr)
                                                                   && !(( j + 1) == sizeof(bstr) && j == (k + 1)))
                                                                        astr[i] += bstr[k] + ";";
                                                                else
                                                                        astr[i] += bstr[k];
                                                        }                                                
                                        }
                                
                                str = implode(astr, "\n");
                                return topten_save(f_name, b_name, str);
                        }
                }
        }
        return 1;
}

int topten_add(object player, string type)
{
        string str, name, id, b_name, f_name;
        array astr;
        int i, j;
        mixed data;
        
        if (wizardp(player))
                return 0;
                
        switch(type)
        {
                case "rich":
                        b_name = RICH_B;
                        f_name = TOPTEN_RICH;
                        break;
                case "pker":
                        b_name = PKER_B;
                        f_name = TOPTEN_PKER;
                        break;
                case "exp":
                        b_name = EXP_B;
                        f_name = TOPTEN_EXP;
                        break;
                case "age":
                        b_name = AGE_B;
                        f_name = TOPTEN_AGE;
                        break;
                case "killed":
                        b_name = KILLED_B;
                        f_name = TOPTEN_KILLED;
                        break;
                
                default:
                        return notify_fail("没有" + type + "这种排行榜！\n");
        }
        
        if (! objectp(player) || ! userp(player))
                return 0;

        if (file_size(f_name) == -1)
        {
                str = player->query("name") + "(" + player->query("id") + ")" +          
                      get_all_data(player, type);
                
                paiming = 1;
                return topten_save(f_name, b_name, str);
        }
        
        if (get_all_data(player, type) == -1)
                return notify_fail("数据查询错误，可能是查询类型错误！\n");
                

        if (get_all_data(player,type) == 0)
                return 0;
                
        topten_del(player->query("id"), type);
        str = read_file(f_name);
        astr = explode(str, "\n");
        i = 0;
        while (i < sizeof(astr))
        {
                if (! astr[i] || sscanf(astr[i], "%s(%s)%s", name, id, data) != 3)
                        if (! astr[i] || sscanf(astr[i], "%s(%s)%s;%*s", name, id, data) != 4)
                                return notify_fail(b_name + "文件数据错误！请呼叫巫师！\n");
                str = "";

#ifdef LONELY_IMPROVED
                if (count_lt(data, get_all_data(player, type)))
#else
                if (data < get_all_data(player, type))
#endif
                {
                        for (j = 0; j < sizeof(astr); j++)
                        {                               
                                if (j == i)
                                        str += player->query("name") + "(" + player->query("id") + ")" +
                                               get_all_data(player, type) + "\n";
                                
                                str += astr[j] + "\n";
                        }
                        
                        paiming = i + 1;
                        return topten_save(f_name, b_name, str);
                }
                else
#ifdef LONELY_IMPROVED
                if (count_eq(data, get_all_data(player, type)))
#else
                if (data == get_all_data(player, type))
#endif
                {

                        for (j = 0; j < sizeof(astr); j++)
                        {
                                if (j == i)
                                        str += astr[j] + ";" + player->query("name") + "(" + 
                                               player->query("id") + ")" + get_all_data(player,type) + "\n";
                                else
                                        str += astr[j] + "\n";
                        } 
                
                        paiming = i + 1;
                        return topten_save(f_name, b_name, str);
                }
                i++;
        }
        
        if (sizeof(astr) < 10)
        {
                paiming = sizeof(astr) + 1;
                str = implode(astr, "\n") + "\n" + player->query("name") + "(" + player->query("id") + ")" + 
                              get_all_data(player, type);
                return topten_save(f_name, b_name, str);
        }
        return 0;
}
