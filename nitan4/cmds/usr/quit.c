// quit.c

#include <ansi.h>
#include <command.h>
#include <config.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

#define QUITMSG			"/adm/etc/quitmsg"

int confirm(string yn, object me);

void create() 
{
        seteuid(getuid());
        set("name", "离线指令");
        set("id", "quit");
        set("channel_id", "离线精灵");
}

int main(object me, string arg)
{
        int i;
        int find;
        int doing;
        object *inv, link_ob;
        object *users;

        if (LOGIN_D->get_madlock()) 
                return notify_fail("时空已经封闭，没有人能够退出这个时空了。\n");

        if (me->is_busy() && ! me->query("doing"))
                return notify_fail("你现在正忙着做其他事，不能退出游戏！\n");

        if (me->is_fighting())
                return notify_fail("你现在正在打架，怎么能说走就走？\n");

        if (me->query_competitor())
                return notify_fail("好家伙，你正在和人比武，怎么能开溜？\n");

        if (me->dps_count() > 0)
                return notify_fail("好家伙，你打晕了别人就想开溜？\n");

        if (me->query_condition("killer"))
                return notify_fail("好家伙，你杀了人就别想开溜！\n");

        if (me->over_encumbranced())
                return notify_fail("你身上背的东西太多了，无法离开这个世界。\n");

        if (me->run_override("quit"))
                return 1;

        if (time() - me->query("birthday") < 1800 && ! me->query("reborn")) 
        {
                write(HIG "\n你的账号是新建的，本站规定新建账号必须连续在线半小时才能被有效保\n"
                          "留，退出该游戏将删除你的账号，你确定要放弃该帐号而退出吗？（" HIR "y" HIG "/" HIY "n" HIG "）\n" NOR);
                input_to((: confirm :), me);
                return 1;
        }
      
        link_ob = me->query_temp("link_ob");

        // We might be called on a link_dead player, so check this.
        if (objectp(link_ob))
        {
                // Are we possessing in others body ?
                if (link_ob->is_character())
                {
                        write("你的魂魄回到" + link_ob->name(1) + "的身上。\n");
                        exec(link_ob, me);
                        link_ob->setup();
                        link_ob->write_prompt();
                        return 1;
                }

                if (link_ob->query_temp("ip_number"))
                {
                        link_ob->set("last_on", time());
                        link_ob->set("last_from",
                                     link_ob->query_temp("ip_number"));
                        link_ob->set("registered",
                                     me->query("registered"));
                        link_ob->save();
                }
                destruct(link_ob);
        }

        if (me->query("doing"))
        {
                if (! interactive(me))
                        return 1;

                write("你暂时离线，人物不退出...\n");
                message("vision", me->name() + "离线了。\n",
                                  environment(me), ({ me }));
                me->save(); 
                link_ob = new(LOGIN_OB);
                exec(link_ob, me);
                destruct(link_ob);
#ifdef DB_SAVE
                DATABASE_D->db_set_player(me->query("id"), "online", 2); // 离线练功
                DATABASE_D->db_set_user(me->query("id"), "online", 2); // 离线练功
#endif                
                return 1;
        }

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(me);
#endif

        me->log_command("quit");
        
#ifndef NO_QUIT_DROP    
        if (! wizardp(me))
        {
                int flag;
                flag = 0;
                inv = all_inventory(me);
                for (i = 0; i < sizeof(inv); i++)
                        if (! inv[i]->query_autoload() && ! inv[i]->query("equipped"))
                                        flag += DROP_CMD->do_drop(me, inv[i], 1);
                if (flag)
                        message("vision", me->name() + "将身上的东西都丢了下来。\n",
                                environment(me), ({ me }));
        }
#else  // 如果不丢物品则必须判断某些物品是必须摧毁的
        inv = all_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
                if (userp(inv[i]) || inv[i]->query_unique() || 
                    (! clonep(inv[i]) && 
                    ! sscanf(base_name(inv[i]), "/data/%*s/%*s"))) // 如果成立表示此物品是非 /data 目录下的原件
                {
                        if (inv[i]->query("equipped"))
                                inv[i]->unequip();
                        if (inv[i]->query("no_drop") || inv[i]->query("unique")) 
                                destruct(inv[i]);
                        else
                                DROP_CMD->do_drop(me, inv[i], 1);
                }
#endif

        // write("欢迎下次再来！\n");
        color_cat(QUITMSG);
        if (environment(me))
        {
                message("vision", me->name() + "离开游戏。\n",
                        environment(me), ({ me }));
        }

        CHANNEL_D->do_channel(this_object(), "sys",
                me->name() + "(" + me->query("id") + ")离开游戏了。");


        log_file("stat", sprintf("%-8s %-10s %-18s %-18s %-15s.\n",
                                 me->name(1), me->query("id"),
                                 ctime(me->query_temp("logon_time")),
                                 ctime(time()),
                                 interactive(me) ? query_ip_number(me) : "unknow"));

        users = filter_array(users(), (: $1->query_temp("tomud") :)); 
        message("system", REM2(me), users);

        me->save();
        me->set_magic_move();
        me->end_log();
#ifdef DB_SAVE
        DATABASE_D->db_set_player(me->query("id"), "online", 0); 
#endif        
        destruct(me);
        return 1;
}

int force_quit(object me)
{
        int find;
        object *users;
        
        if (previous_object() != me ||
            ! playerp(me))
                return notify_fail("你不能摧毁这个对象。\n");

        seteuid(getuid());
        
        if (me->query_condition("killer"))
                return notify_fail("好家伙，杀了人就别想开溜！\n");

        if (me->query("mud_age") < 1800 && ! me->query("reborn")) 
        {
                UPDATE_D->remove_user(me->query("id")); 
                return 1;
        }

        me->save();
        if (environment(me) != find_object(VOID_OB))
                me->move(VOID_OB, 1);

        users = filter_array(users(), (: $1->query_temp("tomud") :)); 
        message("system", REM2(me), users);
                     
#ifdef DB_SAVE
     	DATABASE_D->db_set_player(me->query("id"), "online", 0); // 离线练功
#endif                   
        destruct(me);
        return 1;
}

int confirm(string yn, object me)
{
        object *users;
        if (upper_case(yn) == "Y") 
        {
                seteuid(getuid());
                
                log_file("static/register", 
                         sprintf("%s %s commits a suicide from %s\n", 
                                    log_time(), log_id(me), 
                                    query_ip_number(me))); 

                write(HIW "您选择了放弃该账号退出泥潭，档案被删除。。。。。。\n" NOR);
                
                users = filter_array(users(), (: $1->query_temp("tomud") :)); 
                message("system", REM2(me), users);

                UPDATE_D->remove_user(me->query("id")); 
                return 1;
        } else 
        {
                write(HIG "您选择了放弃退出(quit)，继续游戏。\n" NOR);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式 : quit | exit

当你(你)想暂时离开时, 可利用此一指令。
HELP );
    return 1;
}


