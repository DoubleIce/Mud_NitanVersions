// fuben_cron_d.c
// 创建的副本的记录文件。
// 并且负责定期清理副本

mixed fuben_cron = ([]);
// fuben_d 来保证name是正确的
void create()
{
        call_out("cron",60);
}

int register_fuben_cron(string name,string owner,int delay_time)
{
        if(undefinedp(fuben_cron[name])) {
                fuben_cron[name] = ([]);
                return( fuben_cron[name][owner] = time()+delay_time);
        } else if(undefinedp(fuben_cron[name][owner])) {
                return( fuben_cron[name][owner] = time()+delay_time);
        } else {
                return fuben_cron[name][owner];
        }
}

void cron()
{
        int now,i,j,sz,sz2;
        int ret;
        mixed key,key2;
        now = time();
        ret = 0;
        remove_call_out("cron");
        key = keys(fuben_cron);
        sz = sizeof(key);
        for(i=0;i<sz;i++) {
                key2 = keys(fuben_cron[key[i]]);
                sz2 = sizeof(key2);
                for(j=0;j<sz2;j++) {
                        if(fuben_cron[key[i]][key2[j]] < now) {
                                "/adm/daemons/fuben_d"->clear_fuben(key[i],key2[j]);
                                map_delete(fuben_cron[key[i]],key2[j]);
                                ret ++;
                        }
                }
        }
        CHANNEL_D->do_channel(this_object(),"wiz","本次清理了"+chinese_number(ret)+"个副本。");
        call_out("cron",60);
}       
