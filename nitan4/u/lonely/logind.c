// This program is a part of XYZX MudLIB
// Written by Lonely@IsMUD.net
// logind.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <mudlib.h>

#define WAITING_ENTER_TIME      3
#define MULTI_LOGIN             4
#define UNLOG_IDLE              90
#define PUBLIC_IP               "127.0.0.1"

#define MUDLIST_CMD     "/cmds/usr/mudlist" 
#define REBOOT_CMD      "/cmds/arch/reboot" 
#define INVENTORY_CMD   "/cmds/usr/inventory" 

#define NO_FEE
#define NO_FEE_WARNING  "$$【注意】为保护会员利益，如果非会员在 " + UNLOG_IDLE + " 天之内没有任何活动记录，人物将被系统自动清除。$$"

inherit F_DBASE;
nosave int wiz_lock_level = WIZ_LOCK_LEVEL;
nosave int mad_lock = 0;
nosave string Rname;
nosave string *banned_name = ({
        "你", "你的", "我","我的","自己","屁", "他", "他的","她", "她的","它", "它的",
        "鬼王","风云","流氓","爸","妈","祖先","祖宗","爷","奶","毛泽东","邓小平","江泽民",
        "胡锦涛", "【","】","马克思","恩格斯","列宁","抄","手淫","老百姓",
});
nosave string *start_room = ({
        "/d/xingxiu/beijiang",
        "/d/quanzhou/tieqiang",
        "/d/city/wumiao",
        "/d/city2/kedian",
});
nosave string *banned_id = ({
        "domain", "root", "mudlib", "quit",
        "arch", "wizard", "apprentice",
        "immortal", "player", "fuck", "admin",
        "all", "none", "cancel", "leave", "out",
        "entry", "enter",
});
        
protected void get_id(string arg, object ob);
protected void confirm_id(string yn, object ob);
object make_body(object ob);
protected void init_new_player(object user);
private void check_ok(object ob);
void get_resp(string arg, object ob);
void waiting_enter_world(object ob, object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
string random_name();
void random_gift(mapping my, int select)
{
        int i = 10, j;
        int tmpstr, tmpint, tmpcon, tmpdex;
        tmpstr = tmpint = tmpcon = tmpdex = 10;
        switch( select ) {
                case 1: tmpstr = i = my["str"]; break;
                case 2: tmpint = i = my["int"]; break;
                case 3: tmpcon = i = my["con"]; break;
                case 4: tmpdex = i = my["dex"];
        }
        i = 50 - i;
        while( i-- ) {
                j = random(4);
                if( j == select - 1) {
                        i++;
                        continue;
                }
                switch (j) {
                case 0: tmpstr++; break;
                case 1: tmpint++; break;
                case 2: tmpcon++; break;
                case 3: tmpdex++; break;
                }
        }
        if( tmpstr <= 30 ) my["str"] = tmpstr; else my["str"] = 30;
        if( tmpint <= 30 ) my["int"] = tmpint; else my["int"] = 30;
        if( tmpcon <= 30 ) my["con"] = tmpcon; else my["con"] = 30;
        if( tmpdex <= 30 ) my["dex"] = tmpdex; else my["dex"] = 30;

        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);
}

void create() 
{
        seteuid(ROOT_UID);
        set("channel_id", "连线精灵");
        if( intp(WIZ_LOCK_LEVEL))
                wiz_lock_level = WIZ_LOCK_LEVEL;
        else
                wiz_lock_level = 0;
}

void waiting_login(object ob, string arg)
{
        write("载入中，请稍后 ...\n");
        input_to( (: waiting_login, ob :) );
}

void logon(object ob) 
{    
        object *usr;
        string str, ip_num;    
        string *ips, *vips, *args1, *args2;
        int i, wiz_cnt, ppl_cnt, ip_cnt, ban_cnt, login_cnt;
        int reg_usr, max_usr, max_ips, time1, time2;
        
        /*
        if( !SYSTEM_D->valid_login() ) {
                write(HIY + MUD_FULL_NAME + "载入中，请稍后 ...\n" NOR);
                SYSTEM_D->add_loginuser( ob );
                input_to((: waiting_login, ob :));
                return;
        }
        */
        
        write(ESC "[2J");
        write(color_filter(read_file(WELCOME)));
        write("\n\n");  

        UPTIME_CMD->main();
        if( ob->query_temp("tomud") )
                write(ALERT("经典文字MUD游戏『夕阳再现』，群号『44135826』，本游戏为免费游戏！$$" +
                        "请到 http://IsMUD.net 浏览本游戏主页和论坛、新闻。$$"+
                        "如果有任何疑问，请到本游戏论坛专区提问，或联系QQ 150867 咨询。$$"));

        str = query_ip_number(ob);
        if( BAN_D->is_banned(str) == 1 ) {
                write(HIR "你的地址在本 MUD 不受欢迎，请去论坛 IsMUD.net 申述。\n" NOR);
                destruct(ob);
                return;
        }
        
        if( mad_lock == 1 ) {
                write("现在时空已经封闭了，不能进入！！ \n");
                destruct(ob);
                return;
        }
        
        if( REBOOT_CMD->is_rebooting())
                write(HIY "现在本站正在准备重新启动，如果你不是巫师，请稍候再登录。\n\n" NOR);
                                        
        usr = users() + filter(children(LOGIN_OB), (: interactive :));
        ip_cnt  = 0;        
        wiz_cnt = 0;
        ppl_cnt = 0;
        ban_cnt = 0;        
        login_cnt = 0;
        ips  = ({});
        vips = ({});
        
        reg_usr = to_int(read_file(CONFIG_DIR + "reg_players", 1));
        args1 = explode(read_file(CONFIG_DIR + "max_online", 1), ":");
        args2 = explode(read_file(CONFIG_DIR + "max_ips", 1), ":");
        max_usr = to_int(args1[0]);
        max_ips = to_int(args2[0]);
        time1 = to_int(args1[1]);
        time2 = to_int(args2[1]);
                
        for( i=0;i<sizeof(usr);i++ ) {
                ip_num = query_ip_number(usr[i]);
                if( str == ip_num ) {
                        ip_cnt++;
                        if( !environment(usr[i]) ) ban_cnt++;
                }
                if( usr[i]->is_vip() && member_array(ip_num, vips) == -1 ) vips += ({ ip_num }); 
                if( member_array(ip_num, ips) == -1 ) ips += ({ ip_num });
                if( base_name(usr[i]) == LOGIN_OB ) login_cnt++;
                else if( wizardp(usr[i]) ) { 
                        if( !usr[i]->query("env/invisibility") ) wiz_cnt++;
                }
                else ppl_cnt++;
        }

        write(sprintf(HIR "〖" BBLU HIW "夕阳再现" NOR HIR "〗" NOR "目前共有" HIW "%s" NOR "个注册玩家\n" NOR, chinese_number(reg_usr)));
        write(        HIR "〖" BBLU HIW "夕阳再现" NOR HIR "〗" NOR "自开站以来最高在线人数：" HIC + chinese_number(max_usr) + NOR " 人(" HIK + TIME_D->replace_ctime(time1) + NOR ")\n");
        write(        HIR "〖" BBLU HIW "夕阳再现" NOR HIR "〗" NOR "自开站以来最高在线IP数：" HIC + chinese_number(max_ips) + NOR " 个(" HIK + TIME_D->replace_ctime(time2) + NOR ")\n");        
        write("\n\n");         
        
        if( ip_cnt - 1 > 0 ) {
                write(sprintf("你现在从%s连线进入。",CYN+str+NOR));
                write(sprintf("在这个地址上，还有"+YEL+chinese_number(ip_cnt-1)+NOR+"位其他玩家。\n"));
        } else write(sprintf("你现在从%s连线进入。\n",CYN+str+NOR));
        
        write(sprintf("目前共有" HIY "%s" NOR "位神仙、" HIW "%s" NOR "位江湖人士在江湖中，以及" HIB "%s" NOR "位朋友正在步入江湖的途中。\n",
                      chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) ));
        
        if( ppl_cnt > max_usr )
                write_file(CONFIG_DIR "max_online", sprintf("%d:%d", to_string(ppl_cnt), time()), 1);

        if( sizeof(ips) > max_ips )
                write_file(CONFIG_DIR "max_ips", sprintf("%d:%d", sizeof(ips), time()), 1);  
                      
        if( ban_cnt > 4 ) {
                write("这个IP上同时正在连线的玩家太多了，请稍候再尝试！！ \n");
                destruct(ob);
                return;
        }
        
        if( ip_cnt > MULTI_LOGIN && str != PUBLIC_IP && !BAN_D->is_netclub(str) ) {
                write("对不起，" + LOCAL_MUD_NAME() + "限制相同ip多重登录。\n");
                destruct(ob);
                return;
        }

        if( ob->query_temp("tomud") ) {
                write(CLEAN0);
                write(CLEAN1);
                write(CLEAN2);
                write(TMI("version"));
                input_to("get_version", ob);
        }

        if( !ob->query_temp("big5") ) {
                write(HIC "ヘ玡才栋琌虏砰叫块GB/BIG5э跑才栋┪钡祅魁ノめ\n" NOR
                      "目前的字符集是简体，请输入GB/BIG5改变字符集，或直接登录用户。\n"
                      "请输入您的英文名字(" CYN "忘记密码请输入「pass」" NOR ")：\n");
        } else {
                ob->delete_temp("big5");
                write(HIC "目前的字符集是繁体，请输入GB/BIG5改变字符集，或直接登录用户。\n" NOR);
                ob->set_temp("big5", 1);
                write("目前的字符集是繁体，请输入GB/BIG5改变字符集，或直接登录用户。\n");
                write("请输入您的英文名字(" CYN "忘记密码请输入「pass」" NOR ")：\n");
        }
        input_to( (: get_id :), ob );
}

protected void get_version(string arg, object ob)
{
        if( !arg || arg[0..3] != CURRENT_CLIENT_VERSION ) {
                write(HIY "请从下列地址下载Tomud客户端\n" NOR);
                write(HIG "    http://www.mudbuilder.com/download/tomudsetup.exe\n" NOR);
                write(HIY "或使用Zmud客户端选择6000端口重新连接。\n\n" NOR);
                destruct(ob);
                return;
        }
        input_to( (: get_id :), ob );
}

protected void pass_id(string arg, object ob)
{
        mixed  res;
        int    flag;
        string where;
        
        write("该服务尚未启用。\n");
        destruct(ob);
        return;

        if( wiz_level(arg) ) {
                write("巫师ID密码则必须亲自找天神修改密码。\n");
                destruct(ob);
                return;
        }
        if( (string)ob->set("id", arg) != arg ) {
                write("Failed setting user name.\n");
                destruct(ob);
                return;
        }
#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( !flag ) {
                write("本游戏没有 " + arg + " 这位玩家。\n");
                destruct(ob);
                return;
        }     
        if( !ob->restore() ) {
                write("该角色储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
                destruct(ob);
                return;
        }       
        write("请输入该角色的信箱地置(email)：\n");
        input_to("get_email", 1, ob);
        return;
}

protected void get_email(string arg, object ob)
{
        string pass, msg;
        object user;
        
        user = make_body(ob);        
        if( !user || !user->restore() ) {
                write("该角色储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
                if( user) destruct(user);
                destruct(ob);
                return;
        }
        if( user->query("email") == arg ) {
                write("系统已将新管理密码 Email 至您的信箱。\n");
                pass = SMTP_D->random_passwd(8);
#ifdef ENABLE_MD5_PASSWORD
                ob->set("ad_password", crypt(pass, sprintf("$1$%d", random(99999999))));
#else
                ob->set("ad_password", crypt(pass, 0));
#endif
                ob->save();

                msg = @LONG
Hello, %id.

感谢您参与网络游戏%MUD_NAME，您所使用的账号(%id)的管理密码现
已经被系统修改成为%passwd，下次登录的时候请您使用新的管理密码
登录，并重新设置登录使用的普通密码。对此造成的不便敬请原谅。

                             %data
LONG ;
                msg = replace_string(msg, "%id", ob->query("id"));
                msg = replace_string(msg, "%MUD_NAME", LOCAL_MUD_NAME());
                msg = replace_string(msg, "%passwd", pass);
                msg = replace_string(msg, "%data", ctime(time()));
                
                MAIL_D->queue_mail(0, 0, arg, "夕阳再现 - " + ob->query("id") + " 角色密码", msg);        
                // SMTP_D->send_passmail(0, 0, arg, "夕阳再现 - " + ob->query("id") + " 角色密码", msg);
        } else 
                write("您输入的资料与该角色不符。\n");
        
        destruct(user);
        destruct(ob);
        return;
}

protected void get_id(string arg, object ob)
{
        object *usr;
        string where, ip;        
        mixed  res;
        int    i, flag;
        
        arg = lower_case(arg);

        if( arg == "big5" ) {
                ob->set_temp("big5", 1);
                logon(ob);
                return;
        } else if( arg == "gb" ) {
                ob->delete_temp("big5");
                logon(ob);
                return;
        } else if( arg == "pass" ) {
                write("请输入您的英文ID：\n");
                input_to("pass_id", ob); 
                return;
        }
                
        if( !check_legal_id(arg) ) {
                write(YEL "请输入您的英文名字：" NOR);
                input_to("get_id", ob);
                return;
        }
        
        if( intp(MAX_USERS) && MAX_USERS > 0 ) {
                if( (string)SECURITY_D->get_status(arg) == "(player)" &&
                    sizeof(users()) >= MAX_USERS ) {
                        // Only allow reconnect an interactive player when MAX_USERS exceeded.
                        if( !find_body(arg) ) {
                                write("对不起，" + LOCAL_MUD_NAME() +
                                      "的使用者已经太多了，请待会再来。\n");
                                destruct(ob);
                                return;
                        }
                }
        }

        if( wiz_level(arg) < 1 ) {
                if( REBOOT_CMD->is_rebooting() && !find_body(arg) ) {
                        write("现在本站正准备重新启动，暂时不能登录，请稍候再尝试。\n");
                        destruct(ob);
                        return;
                }
        }
                
        if( wiz_level(arg) < wiz_lock_level ) {
                write("对不起，" + MUD_NAME + "目前限制巫师等级 " + WIZ_LOCK_LEVEL + " 以上的人才能连线。\n");
                destruct(ob);
                return;
        }

        if( AHACK_D->query_block(arg) ) {
                write(HIY "这个账号被暂时封锁了，请用 guest 人物登入与在线巫师联系。\n" NOR);
                destruct(ob);
                return;
        }
            
        if( (string)ob->set("id", arg) != arg ) {
                write("Failed setting user name.\n");
                destruct(ob);
                return;
        }

        if( BAN_D->is_bandid(arg) == 1 ) {
                write("\n对不起，这个帐户正在有另一个使用者在登录，请重新输入你的英文名。\n");
                write(YEL "请输入您的英文名字：" NOR);
                input_to("get_id", ob);
                return;
        }

        if( arg == "guest" ) {
                object user;
		user = find_body("guest");
		if(user)
		{
			write("目前 guest 账号已有人在使用，请等一下再登陆。\n");
			destruct(ob);
			return;
		}

		ob->set("body", USER_OB);
		if( !objectp(user = make_body(ob)) )
		{
			destruct(ob);
			return;
		}
		user->set("name","临时人物");
		user->set("gender","男性");
		user->set("title", "普通百姓");
		user->set("food", 500);
		user->set("water",500);
		user->set("channels", ({ "chat", "rumor", "sos" }) );
		user->set("str",20);
		user->set("int",20);
		user->set("cor",20);
		user->set("con",20);
		user->set("per",20);
		user->set("kar",20);
		waiting_enter_world(ob,user);
		return;
        }
        
#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, on_time, fee_time,
                                  last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
        if( flag ) {
                ob->set_temp("res", res);
        }
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( flag ) {
                if( ob->restore() ) {
                        if( (string)SECURITY_D->get_status(ob->query("id")) != "(player)" ) {
                                if( ob->query("wizpwd") ) {
                                        write("请输入巫师专用密码：\n");
                                        input_to("get_wizpwd", 1, ob);
                                        return;
                                }

                                write("\n警告！您没有设置巫师专用密码！请登陆后用" HIW " wizpwd " NOR "命令设置。\n");
                                write("请输入密码：\n");
                                input_to("get_passwd", 1, ob);
                                return;
                        }
                        write("这个角色已经存在，请输入该角色的密码：\n");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("您的人物储存挡出了一些问题，请利用 guest 人物通知巫师处理。\n");
                destruct(ob);
                return;
        }

        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        while (i--)
                if( usr[i] != ob && usr[i]->query("id") == arg )
                        break;
        if( i >= 0 ) {
                write("有其他玩家正在使用这个 ID，请重新输入。\n");
                write("您的英文名字：\n");
                input_to("get_id", ob);
                return;
        }

        if( ob->query_temp("tomud") )
                write(ALERT(NO_FEE_WARNING)+"使用 " + (string)ob->query("id") +
                        " 这个名字将会创造一个新的人物，您确定吗(y/n)？");
        else
                write("使用 "HIW + (string)ob->query("id") + NOR" 这个名字将会创造一个新的人物，您确定吗("HIR"y"NOR"/"HIY"n"NOR")？");
        
        input_to("confirm_id", ob);
}

protected void get_wizpwd(string pass, object ob)
{
        string old_pass;

        write("\n");
        old_pass = ob->query("wizpwd");

        if( crypt(pass, old_pass) == old_pass ) {
                write(HIG "身份确认完成，巫师专用密码验证通过！\n" NOR);
                write("请输入密码：\n");
                input_to("get_passwd", 1, ob);
                return;
        } else {
                write("密码错误！\n");
                destruct(ob);
                return;
        }
}

protected void get_passwd(string pass, object ob)
{
        string ad_pass;
        string my_pass;

        my_pass = ob->query("password");
        ad_pass = ob->query("ad_password");
        if( !stringp(my_pass) || crypt(pass, my_pass) != my_pass ) {
                if( !stringp(ad_pass) || crypt(pass, ad_pass) != ad_pass ) {
                        write("密码错误！\n");
                        destruct(ob);
                        return;
                }

                write(HIR "\n你采用了管理密码进入游戏，"
                      "因此请你先修改你的普通密码。\n" NOR);

                // 做标记：表示目前流程是修改密码分支。
                ob->set_temp("reset_password", 1);
                write("\n请重新设定您的普通密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( !stringp(ad_pass) ) {
                write(HIC "\n请注意：你的ID目前还没有管理密码，请设置你的管理密码。\n\n" NOR);
                write(HIW "在你普通密码丢失的情况下，你可以输入管理密码进入，并修改普通\n"
                      "密码，所以请你设置一个可靠的并且与普通密码不同的管理密码，用\n"
                      "来保护你的ID。平时请使用普通密码登陆，避免过于频繁的使用管理\n"
                      "密码以导致潜在的泄漏风险。\n\n" NOR);
                write("请输入你的管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        check_ok(ob);
}

protected void reset_ad_password(string pass, object ob)
{
        string my_pass;
        write("\n");

        if( strlen(pass) < 5 ) {
                write("管理密码的长度至少要五个字元，请重设您的管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        my_pass = ob->query("password");
        if( stringp(my_pass) && crypt(pass, my_pass) == my_pass ) {
                write(HIR "为了安全起见，系统要求管理密码的密码和普通密码不能相同。\n\n" NOR);
                write("请重新输入你的管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        ob->set_temp("ad_password", crypt(pass, 0));
        write("请再输入一次您的管理密码，以确认您没记错：\n");
        input_to("confirm_reset_ad_password", 1, ob);
}

protected void confirm_reset_ad_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass = ob->query_temp("ad_password");
        if( crypt(pass, old_pass) != old_pass ) {
                write("您两次输入的管理密码并不一样，请重新设定一次管理密码：\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        ob->set("ad_password", old_pass);
        check_ok(ob);
}

protected void check_ok(object ob)
{
        object user;
        string *res; 
        string str, str1, str2;
        int    on, fee, i, rec = 0;
        
        if( !BAN_D->vaild_allow_address(ob) ) {
                destruct(ob);
                return;
        }
        // Check if we are already playing.
        user = find_body(ob->query("id"));
        if( !objectp(user) )
                user = make_body(ob);
        else
                rec = 1;

        if( !objectp(user)) {
                write(HIR "无法创建该玩家，你可以尝试重新登录或是和巫师联系。\n" NOR);
                return ;
        }

        if( rec != 1 && !user->restore()) { // 必须要判断rec的值，否则会把玩家数据返回到前一次存储的数据
                write(HIR "无法读取该玩家数据，你可以尝试重新登录或是和巫师联系。\n" + rec + NOR);
                return ;
        }

#ifdef NO_FEE
        if( ob->query_temp("tomud") )
                write(ALERT("文字MUD游戏『夕阳再现』将不定期限免费开放！请新老玩家相互转告！\n"));
#endif

        if( rec ) {
                if( user->is_net_dead() ) {
                        reconnect(ob, user);
                        return;
                }
                write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        } else {
                mixed err;
                string msg;

                log_file("usage", sprintf("%s(%s) loggined from %s (%s)\n",
                        user->query("name"), user->query("id"),
                        query_ip_number(ob), ctime(time()) ) );

                if( ob->query("last_on") < time() &&
                    ob->query("last_on") > time() - 30 &&
                    !wiz_level(user) ) {
                        write("你距上一次退出时间只有" + chinese_number(time() - ob->query("last_on")) +
                              "秒钟，请稍候再登录。\n");
                        destruct(user);
                        destruct(ob);
                        return;
                }

                user->set_temp("logon_time", time());
                user->set("last_save", time());
                if( err = catch(waiting_enter_world(ob, user)) ) {
                        user->set_temp("error", err);
                        msg = HIR "\n你无法进入这个世界，可能你的档案出了一些问题，需要和巫师联系。\n\n" NOR;
                        if( mapp(err) )
                                msg += MASTER_OB->standard_trace(err, 1);
                        user->set_temp("error_message", msg);
                        write(msg);
                }
                return;
        }
}

protected void confirm_relogin(string yn, object ob, object user)
{
        object old_link;

        if( !yn || yn=="" ) {
                write("您要将另一个连线中的相同人物赶出去，取而代之吗？(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，欢迎下次再来。\n");
                destruct(ob);
                return;
        }

        if( user ) {
                tell_object(user, "有人从别处( " + query_ip_number(ob)
                                + " )连线取代你所控制的人物。\n");
                log_file("usage", sprintf("%s(%s) replaced by %s (%s)\n",
                         user->query("name"), user->query("id"),
                         query_ip_number(ob), ctime(time())));

                // Kick out tho old player.
                old_link = user->query_temp("link_ob");
                if( old_link ) {
                        exec(old_link, user);
                        destruct(old_link);
                }
        } else {
                write("在线玩家断开了连接，你需要重新登陆。\n");
                destruct(ob);
                return;
        }

        reconnect(ob, user);
}

protected void confirm_id(string yn, object ob)
{
        if( yn=="" ) {
                write("使用这个名字将会创造一个新的人物，请问您确定吗("HIR"y"NOR"/"HIY"n"NOR")？");
                input_to("confirm_id", ob);
                return;
        }   
    
        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("好吧，那么请重新输入您的英文名字：");
                input_to("get_id", ob);
                return;
        }
        write(CLR);
        write("\n\n");
        write(YEL @TEXT
注册姓名——————
请输入您的高姓大名，由于这个名字代表你的人物，而且以后不能更改，务
必慎重择名(不雅观的姓名将被删除)。
 
另：请不要选择金庸小说中已有人物姓名。名字一经选定就很难更改。因此
请慎重取名。除了名字之外，,本 mud 有许多取绰号，别称的设计，所以郑重
以郑重建议您取一个比较像名字的中文名字。如果您有困难输入中文名字，
请直接敲回车键［ＲＥＴＵＲＮ］
——————————
TEXT NOR
        );
        write("\n请给自己取一个中文名字：");
        input_to("get_name", ob);
}

string display_attr(int gift)
{
        if( gift > 24) return HIG + gift + NOR;
        if( gift < 16) return CYN + gift + NOR;
        return "" + gift;
}

void get_resp(string arg, object ob)
{
        if( arg=="" ) {
                write("您是否满意这个中文名字("HIR"y"NOR"/"YEL"n"NOR")？");
                input_to("get_resp", ob);
                return;
        }

        if( arg[0]=='y' || arg[0]=='Y' ) {
                printf("%O\n", ob);
                ob->set("name", Rname);
                write("请设定您的管理密码：");
                input_to("new_ad_password", 1, ob);
                return;
        } else if( arg[0]=='n' || arg[0]=='N') {
        Rname = random_name();
        write("您是否满意这个中文名字("HIR"y"NOR"/"HIY"n"NOR")？");
        printf( HIW" ──"NOR YEL"〖 "HIR"%s"NOR YEL" 〗"NOR"："NOR, Rname);
        input_to("get_resp", ob);
        return;
        }
        else {
                write("对不起，您只能选择满意("HIR"y"NOR")不满意("HIY"n"NOR")： ");
                input_to("get_resp", ob);
                return;
        }


}
protected void get_name(string arg, object ob)
{
        if( arg =="" ) {
                Rname = random_name();
                write("看来您要个随机产生的中文名字．．\n");
                write("请问您是否满意这个中文名字("HIR"y"NOR"/"HIY"n"NOR")？");
                write(sprintf( HIW" ──"NOR CYN"〖 "HIY"%s"NOR CYN" 〗"NOR"："NOR, Rname));
                input_to("get_resp", ob);
        } else {
                if( !check_legal_name(arg) ) {
                        write("请再次输入您的中文名字：");
                        input_to("get_name", ob);
                        return;
                }

                write(printf("%O\n", ob));
                ob->set("name", arg);
                write(HIW "\n为了保证你的人物的安全，游戏要求你设置两个密码。一个是管理密\n"
                        "码，这个密码可以在你遗失了普通密码时登录游戏，并用来修改普通\n"
                        "密码。平时请使用普通密码登陆，避免过于频繁的使用管理密码以导\n"
                        "致潜在的泄漏风险。\n\n" NOR);
                write("请设定您的管理密码：");
                input_to("new_ad_password", 1, ob);
        }
}
protected void new_ad_password(string pass, object ob)
{
        write("\n");
        if (strlen(pass) < 5)
        {
                write("管理密码的长度至少要五个字元，请重设您的管理密码：\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        ob->set_temp("ad_password", crypt(pass, sprintf("$1$%d", random(99999999))));
#else
        ob->set_temp("ad_password", crypt(pass, 0));
#endif

        write("请再输入一次您的管理密码，以确认您没记错：\n");
        input_to("confirm_ad_password", 1, ob);
}

protected void confirm_ad_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass = ob->query_temp("ad_password");
        if (crypt(pass, old_pass) != old_pass)
        {
                write("您两次输入的管理密码并不一样，请重新设定一次管理密码：\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

        ob->set("ad_password", old_pass);

        write(HIW "普通密码是你平时登录游戏时使用的，游戏中可以通过 PASSWD 命令\n"
              "来修改这个密码。\n\n" NOR);
        write("请输入你的普通密码：\n");
        input_to("new_password", 1, ob);
}

protected void new_password(string pass, object ob)
{
        string ad_pass;

        write("\n");
        if (strlen(pass) < 3)
        {
                write("密码的长度至少要三个字元，请重设您的密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

        if (stringp(ad_pass = ob->query("ad_password")) &&
            crypt(pass, ad_pass) == ad_pass)
        {
                write(HIR "请注意，为了安全起见，系统要求你的管理密码和普通密码不能相同。\n\n" NOR);
                write("请重新设置您的普通密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        ob->set_temp("password", crypt(pass, sprintf("$1$%d", random(99999999))));
#else
        ob->set_temp("password", crypt(pass, 0));
#endif

        write("请再输入一次您的密码，以确认您没记错：\n");
        input_to("confirm_password", 1, ob);
}

protected void confirm_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass = ob->query_temp("password");
        if (crypt(pass, old_pass) != old_pass)
        {
                write("您两次输入的密码并不一样，请重新设定一次密码：\n");
                input_to("new_password", 1, ob);
                return;
        }

        ob->set("password", old_pass);
        if (ob->query_temp("reset_password"))
        {
                // 这是用户修改自己的密码分支流程，不是创建
                // 用户分支，因此转移到 check_ok 函数继续执
                // 行。
                ob->save();
                check_ok(ob);
                return;
        }

        write("\n");
        write(NOR MAG @TEXT
选择天赋——————

一个人物的天赋对于他或她所修习的武艺息息相关。游戏中的人
物大多具有以下六项天赋,其中福缘与容貌是隐藏属性：

①　膂力：影响攻击能力及负荷量的大小。       
②　悟性：影响学习武功秘籍的速度及理解师傅的能力。   
③　根骨：影响体力恢复的速度及升级后所增加的体力。
④　身法：影响防御及躲避的能力。  
⑤　福缘：影响解迷、奇遇，拜师等运气方面。
⑥  容貌：影响解密，拜师的条件以及玩家和NPC对你的印象。      
——————————
TEXT NOR);
        write("\n您可以输入 "HIR"(1-4)"+NOR" 指定其中的一项值，或者输入 "+HIR"0"NOR" 由系统随机选择。\n");
        write("您的选择是 ("CYN"0-4"NOR")：");
        input_to("select_gift", ob);
}
void get_gift(string yn, object ob, mapping my, int select)
{
        if( yn[0] != 'y' && yn[0] != 'Y') {
                random_gift(my, select);
                printf("\n膂力[%s]，悟性[%s]，根骨[%s]，身法[%s]\n",
                        display_attr(my["str"]),
                        display_attr(my["int"]),
                        display_attr(my["con"]),
                        display_attr(my["dex"]));
                write("您同意这一组天赋吗？");
                input_to("get_gift", ob, my, select);
                return;
        }
        //write("\n您的电子邮件地址：");
        //input_to("get_email", ob, my);
        write("您要扮演男性("HIG"m"NOR")的角色或女性("HIM"f"NOR")的角色？");
        input_to("get_gender", ob, my);
}
void select_gift(string yn, object ob)
{
        int i;
        mapping my = ([]);
        if( !sscanf(yn, "%d", i) || i < 0 || i > 4) {
                write("\n输入错误，请重新选择：");
                input_to("select_gift", ob);
                return;
        }
        if( i) {
                write("\n请输入您想要的数值(10-30)：");
                input_to("set_gift", ob, my, i);
        } else get_gift(" ", ob, my, i);
}

void set_gift(string yn, object ob, mapping my, int select)
{
        int i;

        if( !sscanf(yn, "%d", i) || i < 10 || i > 30) {
                write("\n数值错误，请重新输入：");
                input_to("set_gift", ob, my, select);
                return;
        }
        switch (select) {
                case 1: my["str"] = i; break;
                case 2: my["int"] = i; break;
                case 3: my["con"] = i; break;
                case 4: my["dex"] = i;
        }
        get_gift(" ", ob, my, select);
}

protected void get_gender(string gender, object ob, mapping my)
{
        object user;
        int id_temp; string id_num;
        
        write("\n");
        if( gender=="" ) {
                write("您要扮演男性("HIG"m"NOR")的角色或女性("HIM"f"NOR")的角色？");
                input_to("get_gender", ob);
                return;
        }
        if( gender[0]=='m' || gender[0]=='M' )
                ob->set_temp("gender", "男性");
        else if( gender[0]=='f' || gender[0]=='F' )
                ob->set_temp("gender", "女性" );
        else {
                write("对不起，您只能选择男性("HIG"m"NOR")或女性("HIM"f"NOR")的角色：");
                input_to("get_gender", ob);
                return;
        }
        if( find_body(ob->query("id")) ) {
                write(HIR "这个玩家现在已经登录到这个世界上了，请"
                      "退出重新连接。\n" NOR);
                destruct(ob);
                return;
        }
#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() )
                DATABASE_D->connect_to_database();

        if( DATABASE_D->db_find_user("id", ob->query("id")) ) {
                write(HIR "\n这个玩家现在已经在其他站注册了，请退出重新连接。\n" NOR);
                destruct(ob);
                return;
        }
#endif
        ob->set("body", USER_OB);
        if( !objectp(user = make_body(ob)) ) {
                write(HIR "\n你无法登录这个新的人物，请重新选择。\n" NOR);
                destruct(ob);
                return;
        }
        user->set("str", my["str"]);
        user->set("dex", my["dex"]);
        user->set("con", my["con"]);
        user->set("int", my["int"]);
        user->set("kar", my["kar"]);
        user->set("per", my["per"]);
        user->set("gender", ob->query_temp("gender")); 
        
        CHANNEL_D->do_channel( this_object(), "sys","又有一个新玩家："+user->query("name")+"["+user->query("id")+"]。"NOR);
        init_new_player(user);
        user->set_temp("newplayer", 1);
        waiting_enter_world(ob, user);
        write("\n");
        
        id_num = read_file(CONFIG_DIR + "reg_players",1);
        id_temp = to_int(id_num); id_temp=id_temp+1;
        id_num = sprintf("%d",id_temp);
        write_file(CONFIG_DIR + "reg_players",id_num,1);
        
}      
 
object make_body(object ob)
{
        string err;
        object user;

        if( !is_root(previous_object()) ){
                log_file("static/security",
                         sprintf("%s try to create player(%s) on %s.\n",
                                 (string)geteuid(previous_object()),
                                 (string)ob->query("id"),
                                 ctime(time())));
                write("你没有权限创建玩家。\n");
                return 0;
        }
 
        seteuid(getuid());
        user = new(USER_OB);
        if( !user ) {
                write("现在可能有人正在修改使用者物件的程式，无法进行复制。\n");
                write(err+"\n");
                return 0;
        }
        seteuid(ob->query("id"));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
                
        user->set("id", ob->query("id"));
        user->set_name( ob->query("name"), ({ ob->query("id")}) );
        return user;
}

private void init_new_player(object user)
{
        user->set("title", "普通百姓");
        user->set("birthday", time() );
        user->set("potential", 100);
        user->set("food", (user->query("str") + 10) * 10);
        user->set("water", (user->query("str") + 10) * 10);
        user->set("channels", ({ "chat", "rumor","tell","new","sos","bill","family"}) );
        user->set("chann", (["new" : 1, "chat" : 1, "bill" : 1 ])); // 默认显示在主窗口的频道
        
        // 记录名字
        NAME_D->map_name(user->query("name"), user->query("id"));

        user->set("env/wimpy", 60);
        user->set("env/roomlist", 1);
}

void waiting_enter_world(object ob, object user)
{
        string msg;

        if( !is_root(previous_object()) )
                return;
        
        ob->set_temp("waiting_enter", 1); // 防止被销毁
/*
        if( file_size(NOTICE) > 0 ) {
                msg  = BLINK "□  " NOR + WHT + MUD_CHINESE_NAME + NOR + 
                       HIK "公怖栏                            " NOR + 
                       HIK + TIME_D->replace_ctime(stat(NOTICE)[1]) + "\n" NOR; 
                msg += HIK "______________________________________________________________\n\n" NOR;
                msg += read_file(NOTICE);
                msg += HIK "______________________________________________________________\n\n" NOR;
        } else {              
                msg = terminal_colour(color_filter(read_file(NOTICE_MOTD)), ([
                        "MUD_NAME"      : MUD_CHINESE_NAME,
                        "ENGLISH_NAME"  : MUD_ENGLISH_NAME,
                        "MUDLIB_VERSION": MUDLIB_VERSION_NUMBER,
                        "MUDOS_VERSION" : __VERSION__ ,
                        "ARCH"          : __ARCH__,
                        "UPDATE"        : TIME_D->replace_ctime(stat(NOTICE_MOTD)[1]),
                ]));
        }
        */
        write(msg);

        write(WHT "请输入任意键继续或 " HIR + WAITING_ENTER_TIME + NOR + WHT " 秒后自动进入游戏\n" NOR);
        ob->set_temp("call_out_handle", call_out( (: enter_world, ob, user, 0, WAITING_ENTER_TIME :), 1 ));

        input_to( (: enter_world, ob, user, 0, 1 :) );
}

varargs void enter_world(object ob, object user, int silent, int timer, string arg)
{
        object cloth;
        string startroom,id,str;
        object login_ob,*users;
        mapping marry;
        int i=random(4);

        if( !ob || !user ) {
                if( objectp(ob) ) destruct(ob);
                if( objectp(user) ) destruct(user);               
                return;
        }    
        if( !is_root(previous_object()) )
                return;              
        if( timer && --timer ) {
                remove_input_to(ob);
                write(TOTOP(1) + WHT "请输入任意键继续或 " HIR + timer + NOR + WHT " 秒后自动进入游戏\n" NOR);
                ob->set_temp("call_out_handle", call_out( (: enter_world, ob, user, silent, timer :), 1 ));
                input_to( (: enter_world, ob, user, silent, 1 :) );
                return;
        }
        
        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
        user->set("registered", ob->query("registered"));
        ob->delete_temp("waiting_enter");
        
        if( intp(ob->query_temp("call_out_handle")) )
                remove_call_out(copy(ob->query_temp("call_out_handle")));
                
        ob->delete_temp("call_out_handle");
        remove_input_to(ob);
        ob->clear_msg_buffer();

        user->set_temp("last_on", time());
        user->set("env/show_reply", "all");
        
        //user->set_encoding(ob->query_encoding());        
        if( ob->query_temp("big5") ) user->set_temp("big5", 1);
        if( ob->query_temp("tomud") ) user->set_temp("tomud", 1);
        
        if( interactive(ob) ) exec(user, ob);   
        user->setup();
        
        if( ob->query("age") == 14 ) {
                user->set("food", user->max_food_capacity());
                user->set("water", user->max_water_capacity());
        }
#ifdef DB_SAVE
        if( user->query_temp("newplayer") && user->query("id") != "guest" ) {
                if( !DATABASE_D->query_db_status() )
                        DATABASE_D->connect_to_database();
                DATABASE_D->db_new_player(ob, user);
        }
#endif
        user->save();
        ob->save();
        
        UPDATE_D->check_user(user);
        
        if( !user->over_encumbranced() ) {
                if( user->query("gender")=="女性") cloth = new("/clone/misc/pink_cloth");
                else cloth = new("/clone/cloth/cloth");
                cloth->move(user);
                catch(cloth->wear());
        } else
                write(HIY ">>>>>>>> 你已超重. <<<<<<<<\n" NOR );  
        
        if( !silent ) {
                write("\n\n");
                
                if( !user->query("registered") ) {
                        if (user->is_ghost())
                                user->reincarnate();
                        startroom = REGISTER_ROOM;
                } 
                else if( (string)SECURITY_D->get_status(ob->query("id")) != "(player)" )
                        startroom = WIZARD_ROOM;
                else if( user->is_in_prison() )
                        startroom = user->query_prison();
                else if( user->is_ghost() )
                        startroom = DEATH_ROOM;
                else if( !stringp(startroom = user->query("startroom")) ||
                        file_size(startroom + ".c") < 0 )
                        startroom = START_ROOM;

                if( !catch(load_object(startroom)) )
                        user->move(startroom);
                else {
                        user->move(START_ROOM);
                        startroom = START_ROOM;
                        user->set("startroom", START_ROOM);
                }

                if( !user->query("registered") )
                        write(color_filter(read_file(UNREG_MOTD)));
                else
                        write(color_filter(read_file(MOTD)));

                write("你连线进入" + LOCAL_MUD_NAME() + "。\n\n");
                tell_room(startroom, user->query("name") +
                          "连线进入这个世界。\n", ({ user }));

#ifdef MCCP_SUPPORT
                if (! compressedp(user))
                        write(YEL "你所使用的连线软体未启动网路传输压缩("
                              HIY "MCCP" NOR YEL ")功能，建议您启动该功能让网路更加顺畅。\n" NOR);
#endif
        }
        
        login_ob = new(LOGIN_OB);
        login_ob->set("id", user->query("id"));
        login_ob->restore();
        if( login_ob->query("registered") ) {
                write("◇───────────────身份消息────────────────◇\n");
                write("您目前权限：" + wizhood(user) + "\n");
                if( !intp(login_ob->query("login_times")) ) {
                        write(NOR "你是第一次光临" + LOCAL_MUD_NAME() + "。\n");
                        login_ob->set("login_times", 1);
                        // show rules
                } else {
                        login_ob->add("login_times", 1);
                        write("你上次光临" + LOCAL_MUD_NAME() + "是 " + HIG +
                                ctime(login_ob->query("last_on")) + NOR + " 从 " + HIR +
                                login_ob->query("last_from") + NOR + " 连接的。\n");
                }
                write("◇────────────────结束─────────────────◇\n");

        }
        destruct(login_ob);
        
        if( ob->query_temp("no_allow_ip") )   
                write("\n\n警告：你未设定自己的登录地址范围。请用"HIR" allowip "NOR"指令设置。\n\n");

        if( user->query("gender") == "男性"&&user->query("age")<=25 ){
                switch(random(2)) { 
                        case 0 : str = "少年侠士";break;
                        case 1 : str = RANK_D->query_respect(user);break;
                }
        } else if( user->query("gender") == "女性"&&user->query("age")<=25 ) {
                switch(random(2)) {
                        case 0 : str = "妙龄少女";break;
                        case 1 : str = RANK_D->query_respect(user);break;
                }
        } else str = RANK_D->query_respect(user);
        
        if( !(wizardp(user) && user->query("env/no_login_msg")) )
                message("shout", HIR"〖有间客栈〗"NOR+": "+CYN"听说又来了一位叫做"+HIW+user->name()+NOR CYN"的"+str+"\n"NOR,users());

#ifdef DB_SAVE
        DATABASE_D->db_set_player(user->query("id"), "online", 1);
        DATABASE_D->db_set_player(user->query("id"), "last_station", LOCAL_STATION);
#endif

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(user);
#endif

        if( wizhood(user) != "(admin)" &&
            EXAMINE_D->query("log_by/" + user->query("id")) )
                user->start_log();

#ifdef DB_SAVE
        if( user->is_vip() && !BAN_D->is_netclub(query_ip_number(user)) )
#else
        if( BAN_D->is_welcome(user->query("id")) && !BAN_D->is_netclub(query_ip_number(user)) )
#endif
                BAN_D->open_club_line(user);    // 自动开放网吧限制

        // notice user the user of this mud
        NEWS_D->prompt_user(user);
        ANALECTA_D->prompt_user(user);

        if( mapp(marry = user->query("couple")) && ! undefinedp(marry["couple_id"]) ) {
                string tmpstr, tmpstr1;
                object couple_ob = find_player(marry["couple_id"]);
                if( couple_ob ) {
                        if( (string)user->query("gender") != "男性" ) {
                                tmpstr1 = "夫君";
                                tmpstr  = "爱妻";
                        } else {
                                tmpstr1 = "爱妻";
                                tmpstr  = "夫君";
                        }
                        write(sprintf(WHT HIM "\n你的%s%s已经在这等了你好久了，快去找%s吧。。。\n" NOR,
                                      tmpstr1, couple_ob->name(), gender_pronoun(couple_ob->query("gender"))));
                        tell_object(couple_ob, sprintf(WHT HIM "\n你的%s%s抑制不住对你的思念跑来看你啦，快去和%s打个招呼吧。。。\n" NOR,
                                                       tmpstr,user->name(),gender_pronoun(user->query("gender"))));
                }
        }
                
        if( (user->query("qi") < 0 || user->query("jing") < 0) && living(user) )
                user->unconcious();
                
        if( !wizardp(user) || !user->query("env/invisibility") ) {
                users = filter_array(users(), (: $1->query_temp("tomud") :));
                message("system",ADD2(user),users);
        }
        if( user->query_temp("tomud") ) {
                foreach( object player in users() )
                        tell_object(user, ADD2(player));
                user->force_me("inventory");
                user->force_me("wear all");
                user->force_me("cmdbar");
        }
}

varargs void reconnect(object ob, object user, int silent)
{
        user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);        
        if( ob->query_temp("big5") ) user->set_temp("big5", 1);
        else user->delete_temp("big5");
        if( ob->query_temp("tomud") ) user->set_temp("tomud", 1);
        else user->delete_temp("tomud");
        
        exec(user, ob);
        user->reconnect();
        
        if( !silent && (!wizardp(user) || !user->query("env/invisibility")) ) {
                tell_room(environment(user), user->query("name") + YEL"重新连线回到这个世界。\n"NOR,
                ({user}));
        }
        
        if( user->query_temp("tomud") ) {
                user->force_me("look");
                user->force_me("inventory");
                user->force_me("cmdbar");
        }
#ifdef DB_SAVE
        DATABASE_D->db_set_player(user->query("id"), "online", 1);
#endif
        CHANNEL_D->do_channel( this_object(), "sys",
                sprintf("%s(%s)由(%s)重新连线进入。", user->query("name"),
                        user->query("id"), query_ip_number(user)) );
        
}

int check_legal_id(string id)
{
        int i;
        i = strlen(id);
    
        if( (strlen(id) < 3) || (strlen(id) > 10 ) ) {
                write("对不起，你的"+HIW"英文"NOR+"名字必须是 3 到 10 个英文字母。\n");
                return 0;
        }
        if( member_array(id, banned_id) != -1) {
                write("对不起，" HIC"“" + id + "”" NOR"这个词有着特"
                      "殊的含意，不能用做英文名字。\n");
                return 0;
        }
        while(i--) {
                if( id[i]<'a' || id[i]>'z' ) {
                        write("对不起，你的"+HIW"英文"NOR+"名字只能用英文字母。\n");
                        return 0;
                }
        }
        return 1;
}

string random_name()
{
        string *lname = ({
"赵","钱","孙","李","周","吴","郑","王","冯","陈","褚","卫","蒋","沈","韩","杨","朱","秦","尤","许","何","吕","施","张",
"孔","曹","严","华","金","魏","陶","姜","戚","谢","邹","喻","柏","水","窦","章","云","苏","潘","葛","奚","范","彭","郎",
"鲁","韦","昌","马","苗","凤","花","方","傻","任","袁","柳","邓","鲍","史","唐","费","廉","岑","薛","雷","贺","倪","汤",
"藤","殷","罗","华","郝","邬","安","常","乐","呆","时","付","皮","卞","齐","康","伍","余","元","卜","顾","盈","平","黄",
"和","穆","肖","尹","姚","邵","湛","汪","祁","毛","禹","狄","米","贝","明","藏","计","伏","成","戴","谈","宋","茅","庞",
"熊","纪","舒","屈","项","祝","董","梁","樊","胡","凌","霍","虞","万","支","柯","昝","管","卢","英","万","候","司马",
"上官","欧阳","夏候","诸葛","闻人","东方","赫连","皇甫","尉迟","公羊","澹台","公治",
"宗政","濮阳","淳于","单于","太叔","申屠","公孙","仲孙","辕轩","令狐","钟离","宇文",
"长孙","幕容","司徒","师空","颛孔","端木","巫马","公西","漆雕","乐正","壤驷","公良",
"拓趾","夹谷","宰父","谷梁","楚晋","阎法","汝鄢","涂钦","段千","百里","东郭","南郭",
"呼延","归海","羊舌","微生","岳","帅","缑","亢","况","后","有","琴","梁丘","左丘","东门","西门",
                        });
        return (lname[random(200)] + chinese_number(random(20)));
}

int check_legal_name(string name)
{
        int i;
        
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 10 ) ) {
                write("对不起，你的中文名字必须是 1 到 5 个中文字。\n");
                return 0;
        }
        if( !is_chinese(name) ) {
                write("对不起，请您用「中文」取名字。\n");
                return 0;
        }
        if( member_array(name, banned_name) != -1 ) {
                write("对不起，这种名字会造成其他人的困扰。\n");
                return 0;
        }
        for( i=0;i<sizeof(banned_name);i++ ) {
                if(  strsrch(name, banned_name[i]) != -1 ){
                        write("对不起，这种名字会造成其他人的困扰。\n");
                        return 0;
                }
        }
        return 1;
}

object find_body(string name)
{
        object ob, *body;
        
        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for( int i=0; i<sizeof(body); i++ ) {
                if( clonep(body[i]) && 
                    getuid(body[i]) == name ) {
                        if( !userp(body[i]) )
                                destruct(body[i]);
                        else    return body[i];
                }
        }        
        return 0;
}

int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) <= level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
}

int set_madlock(int setmark)
{
        if( wiz_level(this_player(1)) < wiz_level("(arch)") )
                return 0;
        if( setmark == 1 ) mad_lock = 1;
        else    mad_lock = 0;
        return 1;
}

int get_madlock()
{
        return mad_lock;
}
