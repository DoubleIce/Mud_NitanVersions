// moduled.c
// Created by Jingxue 2007-11-21 18:53

#include <ansi.h>
#include <dbase.h>

inherit F_DBASE;

#define EQUIP_LIST      "/adm/etc/equiplist/"

class eqmod
{
        string modnum;          // ��װ���
        string modname;         // ��װ����
        array file;           // ��װ����ļ�
        array name;           // ��װ�������
        mapping stats;          // ��װ�������
}

class eqmod load_mod(string modnum);
string mod_stats(object obj, object owner);
int valid_mod(class eqmod mod_stats);

void equip_mod(object ob, object owner);
void unequip_mod(object ob, object owner);

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "��װ����");
        CHANNEL_D->do_channel(this_object(), "sys", "��װ��Ͼ���������");
}

// ������װ�����ͳ��в����ߴ�ӡ������Ϣ
// Ӧ����look.c
string mod_stats(object obj, object owner)
{
        class eqmod mod_stats;
        string modnum, *mod_file, *mod_name, *eq_files, *keys_stats;
        mapping stats;
        int i;
        string msg, str, eq_str;

        // ��ʼ������
        msg = "";
        modnum = obj->query("mod");
        mod_stats = new(class eqmod);
        // ��ȡ��װ����
        mod_stats = load_mod(modnum);
        // ���Ϸ���
        if (valid_mod(mod_stats))
        {
                msg = sprintf(NOR "������������������������\n");
                mod_file = mod_stats->file;
                mod_name = mod_stats->name;
                eq_files = owner->query_temp("modfiles_"+modnum);
                if ( !pointerp(eq_files) )
                        eq_files = ({ });
                for (i=0;i<sizeof(mod_file);i++)
                {
                        eq_str = "  ";
                        if (member_array(mod_file[i], eq_files) != -1)
                                eq_str = WHT"��"NOR;
                        if (obj->query("mark") == mod_file[i])
                                if (obj->query_temp("mod_equip"))
                                        eq_str = HIR"��"NOR;
                                else
                                        eq_str = RED"��"NOR;
                        str = sprintf(NOR "��%s%-" + (18 + color_len(mod_name[i])) + "s"NOR"��\n",eq_str, mod_name[i]);
                        // str = sprintf("��%s%-14s"NOR"��\n",eq_str, mod_name[i]);
                        msg += str;
                }
                msg += sprintf(NOR "������������������������\n");
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
                        msg += sprintf(NOR "%s������������������������"NOR"\n", eq_str);
                        stats = mod_stats->stats;
                        keys_stats = keys(stats);
                        if (sizeof(keys_stats)>0)
                        {
                                for (i=0;i<sizeof(keys_stats);i++)
                                {
                                        str = EQUIPMENT_D->chinese(keys_stats[i], stats[keys_stats[i]]);
                                        msg += sprintf(NOR "%s��"NOR"%-" + (20 + color_len(str)) + "s%s��"NOR"\n",
                                                       eq_str, str, eq_str);
                                }
                        }
                        msg += sprintf(NOR "%s������������������������"NOR"\n", eq_str);
                }
        }
        return msg;
}

// ���ݼ��һ����װ�Ƿ�Ϸ������Ƿ���ڣ������װ���ݻ��ǳ�ʼ�����ݣ����ǲ����ڡ�
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

// ������Ų�����װ����
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

        // ��ʼ��һ���յ���װ�ļ�
        item->modnum = "";
        item->modname = "";
        item->file = ({});
        item->name = ({});

        // �ļ�Ϊ�ա����ؿ�ֵ��
        if(!stringp(filename) || file_size(filename) < 0)
                return item;

        this_file = read_file(filename);

        // ������װ��Ų�����������ļ�������ƥ����װ����
        // modname      ��װ����
        // modfile      ��װ�ļ���
        // modstats     ��װ���Ա�
        sscanf( this_file, "%*s<"+modnum+">%s</"+modnum+">%*s", temp_str);
        sscanf( temp_str, "%*s<name>%s</name>%*s", modname);
        sscanf( temp_str, "%*s<file>\n%s\n</file>%*s", modfile);
        sscanf( temp_str, "%*s<stats>\n%s\n</stats>%*s", modstats);

        item->modnum = modnum;
        item->modname = modname;

        // �����ļ��������ļ����ƺ���װ�����������֡�
        field = explode(modfile, "\n");
        if( sizeof(field) < 2 )         // ����2���Ͳ���֮Ϊ��װ�ˡ�
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

        // �������Ա��������Թؼ��ֺ���װ���ԡ�
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

// װ����װ����
// ob��װ���� ownerװ����
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
        // ��ȡ��װ����
        mod_stats = load_mod(modnum);
        // ���Ϸ���
        if (!valid_mod(mod_stats))
                return;
        // �����װ����ob�Ƿ�����װ���һ��
        file = ob->query("mark");
        if (member_array(file, mod_stats->file) == -1)
                return;

        // �����װ����
        owner->add_temp("modamount_"+modnum,1);
        // �����װ�ļ�
        modfiles = owner->query_temp("modfiles_"+modnum);
        if ( pointerp(modfiles) )
                modfiles += ({ file });
        else
                modfiles = ({ file });
        owner->set_temp("modfiles_"+modnum,modfiles);
        // װ������װ���ñ��
        ob->set_temp("mod_equip", 1);

        // ���onwer����װ������װ����δ�ﵽ��װ�ܼ���ʱ��������onwer��װ����
        if ((int)owner->query_temp("modamount_"+modnum) < sizeof(mod_stats->file))
                return;
        // ��ȡ��װ��������
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
// ж����װ����
// ob��װ���� ownerװ����
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
        // ��ȡ��װ����
        mod_stats = load_mod(modnum);
        // ���Ϸ���
        if (!valid_mod(mod_stats))
                return;
        // �����װ����ob�Ƿ�����װ���һ��
        file = ob->query("mark");
        if (member_array(file, mod_stats->file) == -1)
                return;

        // �����װ����
        owner->add_temp("modamount_"+modnum,-1);
        if ((int)owner->query_temp("modamount_"+modnum)<0)
                owner->delete_temp("modamount_"+modnum);
        // �����װ�ļ�
        modfiles = owner->query_temp("modfiles_"+modnum);
        if ( pointerp(modfiles) )
                modfiles -= ({ file });
        else
                modfiles = ({ });
        owner->set_temp("modfiles_"+modnum,modfiles);
        // ɾ��װ����װ�������
        ob->delete_temp("mod_equip");

        // ���onwer����װ������װ����+1δ�ﵽ��װ�ܼ���ʱ��
        // ��Ϊû���ӹ���װ���ԣ����Բ���Ҫִ��ɾ��onwer��װ����
        if (((int)owner->query_temp("modamount_"+modnum) + 1) < sizeof(mod_stats->file))
                return;
        // ��ȡ��װ��������
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
