// uptime.c
// From ES2
// Modified by Xiang for XKX (12/15/95)

#include <ansi.h>
#include <mudlib.h>
#include <getconfig.h>

#define AUTOBOOT_D     "/adm/daemons/autobootd.c"
inherit F_CLEAN_UP;

// This command is also called by LOGIN_D, so we don't want it use 
// arguments.
int main()
{
        int t, d, h, m, s, r;
        string time, rtime;

	t = uptime();
	s = t % 60;		t /= 60;
	m = t % 60;		t /= 60;
	h = t % 24;		t /= 24;
	d = t;

	if (d) time = chinese_number(d) + "��";
	else time = "";

	if (h) time += chinese_number(h) + "Сʱ";
	if (m) time += chinese_number(m) + "��";
        time += chinese_number(s) + "��";

/*
        r = time() + AUTOBOOT_D->query_time() * 60;
        rtime = TIME_D->replace_ctime(r);
*/

        //write(HIC + LOCAL_MUD_NAME() + "�Ѿ�ִ����" + time + "������ " + rtime + " ������\n\n" NOR);
        write(HIC + LOCAL_MUD_NAME() + "�Ѿ�ִ����" + time + "��\n\n" NOR);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : uptime
 
���ָ���������������Ϸ�Ѿ�����ִ���˶�á�
 
HELP
    );
    return 1;
}