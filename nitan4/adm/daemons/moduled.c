// moduled.c
// Created by Jingxue 2007-11-21 18:53

#include <ansi.h>
#include <dbase.h>

inherit F_DBASE;

#define EQUIP_LIST      "/adm/etc/equiplist/"

class eqmod
{
        string modnum;          // 套装序号
        string modname;         // 套装名称
        array file;           // 套装组件文件
        array name;           // 套装组件中文
        mapping stats;          // 套装组合属性
}

class eqmod load_mod(string modnum);
string mod_stats(object obj, object owner);
int valid_mod(class eqmod mod_stats);

void equip_mod(object ob, object owner);
void unequip_mod(object ob, object owner);

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "套装精灵");
        CHANNEL_D->do_channel(this_object(), "sys", "套装组合精灵启动。");
}

// 根据套装部件和持有部件者打印部件信息
// 应用于look.c
string mod_stats(object obj, object owner)
{
        class eqmod mod_stats;
        string modnum, *mod_file, *mod_name, *eq_files, *keys_stats;
        mapping stats;
        int i;
        string msg, str, eq_str;

        // 初始化资料
        msg = "";
        modnum = obj->query("mod");
        mod_stats = new(class eqmod);
        // 读取套装资料
        mod_stats = load_mod(modnum);
        // 检查合法性
        if (valid_mod(mod_stats))
        {
                msg = sprintf(NOR "┏━━━━━━━━━━┓\n");
                mod_file = mod_stats->file;
                mod_name = mod_stats->name;
                eq_files = owner->query_temp("modfiles_"+modnum);
                if ( !pointerp(eq_files) )
                        eq_files = ({ });
                for (i=0;i<sizeof(mod_file);i++)
                {
                        eq_str = "  ";
                        if (member_array(mod_file[i], eq_files) != -1)
                                eq_str = WHT"√"NOR;
                        if (obj->query("mark") == mod_file[i])
                                if (obj->query_temp("mod_equip"))
                                        eq_str = HIR"√"NOR;
                                else
                                        eq_str = RED"×"NOR;
                        str = sprintf(NOR "┃%s%-" + (18 + color_len(mod_name[i])) + "s"NOR"┃\n",eq_str, mod_name[i]);
                        // str = sprintf("┃%s%-14s"NOR"┃\n",eq_str, mod_name[i]);
                        msg += str;
                }
                msg += sprintf(NOR "┗━━━━━━━━━━┛\n");
                if ( (int)owner->query_temp("modamount_"+modnum) == sizeof(mod_file) )
                {
                        eq_str = HIR;
                /*
                else
                        eq_str = YEL;
                */
                        msg += sprintf(" %-s(%s%d/%d"NOR")\n",
                                       trans_color(mod_stats->modname, 3),
                                       eq_str,
                                       (int)owner->query_temp("modamount_"+modnum),
                                       sizeof(mod_file));
                        msg += sprintf(NOR "%s┏━━━━━━━━━━┓"NOR"\n", eq_str);
                        stats = mod_stats->stats;
                        keys_stats = keys(stats);
                        if (sizeof(keys_stats)>0)
                        {
                                for (i=0;i<sizeof(keys_stats);i++)
                                {
                                        str = EQUIPMENT_D->chinese(keys_stats[i], stats[keys_stats[i]]);
                                        msg += sprintf(NOR "%s┃"NOR"%-" + (20 + color_len(str)) + "s%s┃"NOR"\n",
                                                       eq_str, str, eq_str);
                                }
                        }
                        msg += sprintf(NOR "%s┗━━━━━━━━━━┛"NOR"\n", eq_str);
                }
        }
        return msg;
}

// 根据检查一个套装是否合法，即是否存在，如果套装数据还是初始化数据，就是不存在。
int valid_mod(class eqmod mod_stats)
{
        if( mod_stats->modnum == "" )
                return 0;

        if( mod_stats->modname == "" )
                return 0;

        if( !(sizeof(mod_stats->file)) )
                return 0;

        if( !(sizeof(mod_stats->name)) )
                return 0;
        /*
        if( !(mod_stats->stats) )
                return 0;
        */
        return 1;
}

// 根据序号查找套装数据
class eqmod load_mod(string modnum)
{
        string filename, this_file, temp_str;
        object ob;
        class eqmod item;
        array field;
        string modname, modfile, modstats;
        int i;
        mapping stats;
        string stats_key;
        mixed stats_value;

        item = new(class eqmod);

        if ( modnum[0] == 'M' )
        {
                if ( modnum[1] == '0' && strlen(modnum) == 5)
                        filename = EQUIP_LIST+"basic.mod";
                else if ( modnum[1] == '1' && strlen(modnum) == 5)
                        filename = EQUIP_LIST+"advance.mod";
                else if ( modnum[1] == '2' && strlen(modnum) == 5)
                        filename = EQUIP_LIST+"expert.mod";
                else if ( modnum[1] == '3' && strlen(modnum) == 5)
                        filename = EQUIP_LIST+"boss.mod";
        }

        // 初始化一个空的套装文件
        item->modnum = "";
        item->modname = "";
        item->file = ({});
        item->name = ({});

        // 文件为空。返回空值。
        if(!stringp(filename) || file_size(filename) < 0)
                return item;

        this_file = read_file(filename);

        // 根据套装序号查找序号所在文件表，查找匹配套装数据
        // modname      套装名字
        // modfile      套装文件表
        // modstats     套装属性表
        sscanf( this_file, "%*s<"+modnum+">%s</"+modnum+">%*s", temp_str);
        sscanf( temp_str, "%*s<name>%s</name>%*s", modname);
        sscanf( temp_str, "%*s<file>\n%s\n</file>%*s", modfile);
        sscanf( temp_str, "%*s<stats>\n%s\n</stats>%*s", modstats);

        item->modnum = modnum;
        item->modname = modname;

        // 解析文件表，填入文件名称和套装部件中文名字。
        field = explode(modfile, "\n");
        if( sizeof(field) < 2 )         // 少于2个就不称之为套装了。
                return item;

        for (i=0;i<sizeof(field);i++)
        {
                ob = EQUIPMENT_D->create_module(field[i]);
                if( !ob )
                        return 0;

                item->file += ({ field[i] });
                item->name += ({ ob->query("name") });
                destruct(ob);
        }

        // 解析属性表，填入属性关键字和套装属性。
        if (modstats != "")
        {
                field = explode(modstats, "\n");
                stats = ([ ]);
                for (i=0;i<sizeof(field);i++)
                {
                        field[i] = replace_string(field[i], " ", "");
                        sscanf( field[i], "%s:%d", stats_key, stats_value );
                        stats[stats_key] = stats_value;
                }
                item->stats = stats;
        }

        return item;
}

// 装备套装部件
// ob套装部件 owner装备者
void equip_mod(object ob, object owner)
{
        string modnum, file;
        class eqmod mod_stats;
        array modfiles;

        mapping stats, applied_prop;
        int i, flag;
        array apply;

        modnum = ob->query("mod");
        mod_stats = new(class eqmod);
        // 读取套装资料
        mod_stats = load_mod(modnum);
        // 检查合法性
        if (!valid_mod(mod_stats))
                return;
        // 检查套装部件ob是否是套装里的一件
        file = ob->query("mark");
        if (member_array(file, mod_stats->file) == -1)
                return;

        // 标记套装件数
        owner->add_temp("modamount_"+modnum,1);
        // 标记套装文件
        modfiles = owner->query_temp("modfiles_"+modnum);
        if ( pointerp(modfiles) )
                modfiles += ({ file });
        else
                modfiles = ({ file });
        owner->set_temp("modfiles_"+modnum,modfiles);
        // 装备的套装设置标记
        ob->set_temp("mod_equip", 1);

        // 如果onwer身上装备的套装件数未达到套装总件数时，不赋予onwer套装属性
        if ((int)owner->query_temp("modamount_"+modnum) < sizeof(mod_stats->file))
                return;
        // 读取套装附加属性
        stats = mod_stats->stats;
        apply = keys(stats);
        if ( sizeof(apply) )
        {
                applied_prop = owner->query_temp("apply");
                if( !mapp(applied_prop) )
                        applied_prop = ([]);
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
                owner->set_temp("apply", applied_prop);
                if (flag) CHAR_D->setup_char(owner);
        }
}
// 卸下套装部件
// ob套装部件 owner装备者
void unequip_mod(object ob, object owner)
{
        string modnum, file;
        class eqmod mod_stats;
        array modfiles;

        mapping stats, applied_prop;
        int i, flag;
        array apply;

        modnum = ob->query("mod");
        mod_stats = new(class eqmod);
        // 读取套装资料
        mod_stats = load_mod(modnum);
        // 检查合法性
        if (!valid_mod(mod_stats))
                return;
        // 检查套装部件ob是否是套装里的一件
        file = ob->query("mark");
        if (member_array(file, mod_stats->file) == -1)
                return;

        // 标记套装件数
        owner->add_temp("modamount_"+modnum,-1);
        if ((int)owner->query_temp("modamount_"+modnum)<0)
                owner->delete_temp("modamount_"+modnum);
        // 标记套装文件
        modfiles = owner->query_temp("modfiles_"+modnum);
        if ( pointerp(modfiles) )
                modfiles -= ({ file });
        else
                modfiles = ({ });
        owner->set_temp("modfiles_"+modnum,modfiles);
        // 删除装备套装部件标记
        ob->delete_temp("mod_equip");

        // 如果onwer身上装备的套装件数+1未达到套装总件数时，
        // 因为没附加过套装属性，所以不需要执行删除onwer套装属性
        if (((int)owner->query_temp("modamount_"+modnum) + 1) < sizeof(mod_stats->file))
                return;
        // 读取套装附加属性
        stats = mod_stats->stats;
        apply = keys(stats);
        if ( sizeof(apply) )
        {
                applied_prop = owner->query_temp("apply");
                for(i = 0; i<sizeof(apply); i++)
                {
                        if (apply[i] == "int" || apply[i] == "str" ||
                            apply[i] == "con" || apply[i] == "add_skill" ||
                            apply[i] == "max_qi" || apply[i] == "max_jing")
                                flag = 1;

                        applied_prop[apply[i]] -= stats[apply[i]];
                }
                if (flag) CHAR_D->setup_char(owner);
        }
}
