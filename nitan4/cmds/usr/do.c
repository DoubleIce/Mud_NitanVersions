// do.c chain-command

inherit F_CLEAN_UP;

#define MAX_CHAIN     15

int main(object me, string arg)
{
        array args;

        if (! arg || arg == "") return notify_fail("����Ҫ����ʲôָ�\n");

        if (strsrch(arg, "do ") >= 0)
                return notify_fail("�㲻���ٴ���ָ�����ٶ�ʹ�ô���ָ�do����\n");

        if (me->query_temp("do_chain")) {
                return notify_fail("ϵͳ�ڴ�����Ĵ���ָ�\n");
        }
        args = explode(arg, ",");
        if (sizeof(args) > MAX_CHAIN) {
                return notify_fail("�㲻�ɴ�������ʮ���ָ�\n");
        }
        me->set_temp("do_chain", 1);
/*
        for(int i=0; i<sizeof(args); i++)
        {
                array commands = explode(args[i], " ");
                if (sizeof(commands) && commands[0] == "do") {
                        me->delete_temp("do_chain");
                        return notify_fail("�㲻���ٴ���ָ�����ٶ�ʹ�ô���ָ�do����\n");
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
ָ���ʽ: do <����ָ��>

���ָ���������һ�ΰ�һ��ָ����ŷ������������·
������Ӷ�����ѹ���ɵ������
����ָ�����
(�����)ԭ ZMUD ����: e;s;s;enter door;kill liu mang;perform cuff.ji
(һ���)ʹ�� do �����: do e,s,s,enter door,kill liu mang,perform cuff.ji

HELP );
        return 1;
}



