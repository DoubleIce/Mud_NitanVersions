// broadcastd.c

#include <ansi.h>

inherit F_SAVE;
inherit F_DBASE;

string *news;
string query_save_file() { return DATA_DIR + "broadcastd"; }

void create()
{
        seteuid(getuid());
        set("channel_id", "信息通告");
        CHANNEL_D->do_channel( this_object(), "sys", "宣传系统已经启动。\n");

        if( !restore() && !arrayp(news) )
                news = ({});

        SCHEDULE_D->set_event(10, 1, this_object(), "broadcast_news");
}

void broadcast_news()
{
        if( !sizeof(news) ) {
                CHANNEL_D->do_channel(this_object(), "chat",
                        HIW "王者归来" HIY "服务器已经更换，请去新服务器练功，本服务器即将关闭。\n" NOR);
                return;
        }

        CHANNEL_D->do_channel(this_object(), "chat", news[random(sizeof(news))]);
        return;
}

string add_news(string arg)
{
        if( !arg || arg == "" )
                return "非法的信息\n";

        news += ({ arg });
        save();

        return "信息增加完毕\n";
}

string list_news()
{
        int i;
        string str;

        if( !sizeof(news) )
                return "没有任何信息通告。\n";

        str = "";
        for( i=0;i<sizeof(news);i++ )
                str += sprintf("%4d  :  %s\n", i+1, news[i]);

        return str;
}

string delete_news(string arg)
{
        int n;

        if( !arg || sscanf(arg, "%d", n) != 1 )
                return "你要删除哪一条信息？\n";

        if( n > sizeof(news) || n < 1 )
                return "没有这一条信息。\n";

        news -= ({ news[n-1] });
        save();

        return "指定信息删除完毕\n";
}

int remove()
{
        save();
        return 1;
}
