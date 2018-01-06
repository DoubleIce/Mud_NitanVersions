// broadcastd.c

#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;

string *news;
string query_save_file() { return DATA_DIR + "broadcastd"; }

void create()
{
        seteuid(getuid());
        set("channel_id", "��Ϣͨ��");
        CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������\n");

        if( !restore() && !arrayp(news) )
                news = ({});

        SCHEDULE_D->set_event(10, 1, this_object(), "broadcast_news");
}

void broadcast_news()
{
        if( !sizeof(news) ) {
                CHANNEL_D->do_channel(this_object(), "chat",
                        HIW "���߹���" HIY "�������Ѿ���������ȥ�·������������������������رա�\n" NOR);
                return;
        }

        CHANNEL_D->do_channel(this_object(), "chat", news[random(sizeof(news))]);
        return;
}

string add_news(string arg)
{
        if( !arg || arg == "" )
                return "�Ƿ�����Ϣ\n";

        news += ({ arg });
        save();

        return "��Ϣ�������\n";
}

string list_news()
{
        int i;
        string str;

        if( !sizeof(news) )
                return "û���κ���Ϣͨ�档\n";

        str = "";
        for( i=0;i<sizeof(news);i++ )
                str += sprintf("%4d  :  %s\n", i+1, news[i]);

        return str;
}

string delete_news(string arg)
{
        int n;

        if( !arg || sscanf(arg, "%d", n) != 1 )
                return "��Ҫɾ����һ����Ϣ��\n";

        if( n > sizeof(news) || n < 1 )
                return "û����һ����Ϣ��\n";

        news -= ({ news[n-1] });
        save();

        return "ָ����Ϣɾ�����\n";
}

int remove()
{
        save();
        return 1;
}
