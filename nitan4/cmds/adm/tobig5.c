/***** Written by ken@NT.  All rights reserved. *****/
// tobig5.c
/****************************************************/
/* 中文字分两种，中国大陆用GB码，香港和台湾用BIG5码 */
/* 由于内码不同，就会出现乱码的情况，GB码的编码是由 */  
/* 0xa1 - 0xf7 ，BIG5码的编码是由 0x40 - 0x7e，因此 */
/* 我们做有两个字库，分别是字库 "BtoG.tab"   和字库 */ 
/* "GtoB.tab" ，在对应的字库中找出对应的文字， 这个 */
/* 动作由"/adm/daemons/languaed.c" 完成，本程序只需 */
/* 调用它里面的函数就可以了。                       */
/****************************************************/

#include <ansi.h>
inherit F_CLEAN_UP;
#define CONVERT "/adm/daemons/languaged.c"

protected int help(object me);
protected int to_big5(string file);
protected array deep_file_list(string dir);

int main(object me, string arg)
{
        string file;
        mixed *dir;
        int i, total;

        if (!SECURITY_D->valid_grant(me, "(admin)"))
                return 0; 

        if (!arg || sscanf(arg, "%s", file) != 1) 
                return help( me );
                
        seteuid(geteuid(me));
     
        if(!SECURITY_D->valid_write(file, me))
                return notify_fail("没有足够的读写权限.\n");
        
        if (file_size(file) == -1 )
                file = resolve_path(me->query("cwd"), file);
                
        if(file_size(file) > 0)
        { 
                to_big5(file);
                write(HIW "文件∶" + file + "内所有内容转换完成.\n" NOR);
                return 1;
        }
   
        else if(file_size(file) == -2) 
        {
                dir = deep_file_list(file);
                for(i=0; i<sizeof(dir); i++)
                {
                        reset_eval_cost();
                        if ( file_size(dir[i]) > 0)
                        {
                                to_big5(dir[i]);
                                total = total + 1;
                                write(dir[i] + " 文转换完成。\n");
                        }
                }
                write("共把" + total + "个文件转换成大五码(BIG5)\n");
                return 1;
        }
        else return notify_fail("没有这个文件或目录.\n");
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

protected int to_big5(string file)
{
        array text;
        int i;   
        
        text = explode(read_file(file), "\n");
        rm(file);
        
        for(i=0; i<sizeof(text); i++)
        {
                text[i] = CONVERT-> toBig5(text[i]);                    
                write_file(file, text[i] + "\n");
        }       
        return 1;
}

protected int help(object me)
{ 
write(@HELP
Written by ken@NT. All rights reserved.
E-mail: printken@yahoo.com.hk

指令格式: tobig5 <文件或目录>
本指令可让你把文件或目录转换成BIG5码。
比如togb /d/　会把 /d/　下的所有文件及目录内的所有文都转成BIG5
我不建意使用转换目录，除非你很了解你想要做什么！
(此指令建议放在/cmds/adm/下)
注意：本命令比较危险，请小心使用。

HELP);
return 1;
}


