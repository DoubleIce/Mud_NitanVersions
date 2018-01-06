// tolower.c
// Written by ken@NT
// All rights reserved

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg);
protected int Ctoc(string file);
protected array deep_file_list(string dir);
protected int help(object me);

int main(object me, string arg)
{
        string dir, flag;
        mixed *file;
        int i, len, total = 0;

        if (!SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;
        
        if (!arg || sscanf(arg, "%s", dir) != 1)
                return help( me );
                
        seteuid(geteuid(me));
        if (!SECURITY_D->valid_write(dir, me))
                return notify_fail("û���㹻�Ķ�дȨ��.\n");
                
        else if(file_size(dir) == -2) 
        {
                file = deep_file_list(dir);
                             
                reset_eval_cost();
                for(i=0; i<sizeof(file); i++)
                {                       
                        len = strlen(file[i]);
                        if (file[i][len-2..len-1] == ".C")
                        {                               
                                Ctoc(file[i]);
                                total = total + 1;
                        }
                }
                write(HIW "����" + total + "���ļ���Ҫ����\n");
                write(HIW "�����ļ��������.\n" NOR);
                return 1;
        }
        else return notify_fail("û�����Ŀ¼.\n");
        return 1;  
}

protected array deep_file_list(string dir)
{
        int i;
        array flist, result = ({ });
        string file;
        
        flist = get_dir(dir);

        for (i = 0; i < sizeof(flist); i++)
        {
                file = dir + flist[i];
                
                if (file_size(file + "/") == -2)
                        result += deep_file_list(file + "/");
                else 
                        result += ({ file });

        }
        return result;
}

protected int Ctoc(string file)
{
        write("��" + file + "ת��Сд(*.C->*.c)\n");
        rename(file , lower_case(file));
        return 1;
}
protected int help(object me)
{
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

��Ŀ¼����Ŀ¼�µ����д�д�ļ�ת����Сд�ļ�.
��ʽ : tolower <Ŀ¼>
HELP);
return 1;
}

