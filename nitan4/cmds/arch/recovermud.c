// recover.c
// Smallfish@Huaxia

#include <login.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *ob;
	string src, dst, playerid;
	object link_ob;
	int i;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
		return notify_fail("ֻ�� (arch) ���ϵ���ʦ���ָܻ�����ס��ʱ��\n");
	
	seteuid(getuid());
	message("system", "\n*** " + RANK_D->query_rank(me) + me->short(1) + "���ڽ�����ʱ�ս�� ***\n*** ����������������ָ�����ǰ������... ***\n", users());
        write("�����У�");

	ob = users();
	for(i=0; i<sizeof(ob); i++) {
		if( objectp(link_ob = ob[i]->query_temp("link_ob")) ) { 
			playerid = ob[i]->query("id");
			dst = "/data/user/" + playerid[0..0] + "/" + playerid + ".o" ;
			src = "data/keep/" + playerid ;

			cp(src, dst);
			rm(src);
			ob[i]->restore();
		}
//		else {
//			return notify_fail("ʱ�ս��ʧ���ˣ����\n?);
//		}
	}
	
	write("ʱ�ս����ϡ�\n");
	LOGIN_D->set_madlock(0);
        //wind try
	log_file("/static/RECOVER", sprintf("%s call recover ON %s.\n", this_player()->query("name"),ctime(time())));
	return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: recover
 
��ⱻ��ס��ʱ�ա�
 
HELP
);
        return 1;
}
 