// do.c chain-command

inherit F_CLEAN_UP;

#define MAX_CHAIN     15

int main(object me, string arg)
{
        array args;

        if (! arg || arg == "") return notify_fail("你想要串连什么指令？\n");

        if (strsrch(arg, "do ") >= 0)
                return notify_fail("你不可再串连指令里再度使用串连指令（do）！\n");

        if (me->query_temp("do_chain")) {
                return notify_fail("系统在处理你的串连指令！\n");
        }
        args = explode(arg, ",");
        if (sizeof(args) > MAX_CHAIN) {
                return notify_fail("你不可串连超过十五个指令！\n");
        }
        me->set_temp("do_chain", 1);
/*
        for(int i=0; i<sizeof(args); i++)
        {
                array commands = explode(args[i], " ");
                if (sizeof(commands) && commands[0] == "do") {
                        me->delete_temp("do_chain");
                        return notify_fail("你不可再串连指令里再度使用串连指令（do）！\n");
                }
        }
*/
        for(int i=0; i<sizeof(args); i++)
        {
                me->command(me->process_input(args[i]));
        }
        me->delete_temp("do_chain");
        return 1;
}

int help(object me)
{
        write( @HELP
指令格式: do <串连指令>

这个指令可以让你一次把一串指令交给伺服器处理，如此网路
封包将从多封包被压缩成单封包。
串连指令范例：
(六封包)原 ZMUD 多封包: e;s;s;enter door;kill liu mang;perform cuff.ji
(一封包)使用 do 单封包: do e,s,s,enter door,kill liu mang,perform cuff.ji

HELP );
        return 1;
}



