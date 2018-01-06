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
#define NO_FEE_WARNING  "$$��ע�⡿Ϊ������Ա���棬����ǻ�Ա�� " + UNLOG_IDLE + " ��֮��û���κλ��¼�����ｫ��ϵͳ�Զ������$$"

inherit F_DBASE;
nosave int wiz_lock_level = WIZ_LOCK_LEVEL;
nosave int mad_lock = 0;
nosave string Rname;
nosave string *banned_name = ({
        "��", "���", "��","�ҵ�","�Լ�","ƨ", "��", "����","��", "����","��", "����",
        "����","����","��å","��","��","����","����","ү","��","ë��","��Сƽ","������",
        "������", "��","��","���˼","����˹","����","��","����","�ϰ���",
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
        set("channel_id", "���߾���");
        if( intp(WIZ_LOCK_LEVEL))
                wiz_lock_level = WIZ_LOCK_LEVEL;
        else
                wiz_lock_level = 0;
}

void waiting_login(object ob, string arg)
{
        write("�����У����Ժ� ...\n");
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
                write(HIY + MUD_FULL_NAME + "�����У����Ժ� ...\n" NOR);
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
                write(ALERT("��������MUD��Ϸ��Ϧ�����֡���Ⱥ�š�44135826��������ϷΪ�����Ϸ��$$" +
                        "�뵽 http://IsMUD.net �������Ϸ��ҳ����̳�����š�$$"+
                        "������κ����ʣ��뵽����Ϸ��̳ר�����ʣ�����ϵQQ 150867 ��ѯ��$$"));

        str = query_ip_number(ob);
        if( BAN_D->is_banned(str) == 1 ) {
                write(HIR "��ĵ�ַ�ڱ� MUD ���ܻ�ӭ����ȥ��̳ IsMUD.net ������\n" NOR);
                destruct(ob);
                return;
        }
        
        if( mad_lock == 1 ) {
                write("����ʱ���Ѿ�����ˣ����ܽ��룡�� \n");
                destruct(ob);
                return;
        }
        
        if( REBOOT_CMD->is_rebooting())
                write(HIY "���ڱ�վ����׼����������������㲻����ʦ�����Ժ��ٵ�¼��\n\n" NOR);
                                        
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

        write(sprintf(HIR "��" BBLU HIW "Ϧ������" NOR HIR "��" NOR "Ŀǰ����" HIW "%s" NOR "��ע�����\n" NOR, chinese_number(reg_usr)));
        write(        HIR "��" BBLU HIW "Ϧ������" NOR HIR "��" NOR "�Կ�վ�����������������" HIC + chinese_number(max_usr) + NOR " ��(" HIK + TIME_D->replace_ctime(time1) + NOR ")\n");
        write(        HIR "��" BBLU HIW "Ϧ������" NOR HIR "��" NOR "�Կ�վ�����������IP����" HIC + chinese_number(max_ips) + NOR " ��(" HIK + TIME_D->replace_ctime(time2) + NOR ")\n");        
        write("\n\n");         
        
        if( ip_cnt - 1 > 0 ) {
                write(sprintf("�����ڴ�%s���߽��롣",CYN+str+NOR));
                write(sprintf("�������ַ�ϣ�����"+YEL+chinese_number(ip_cnt-1)+NOR+"λ������ҡ�\n"));
        } else write(sprintf("�����ڴ�%s���߽��롣\n",CYN+str+NOR));
        
        write(sprintf("Ŀǰ����" HIY "%s" NOR "λ���ɡ�" HIW "%s" NOR "λ������ʿ�ڽ����У��Լ�" HIB "%s" NOR "λ�������ڲ��뽭����;�С�\n",
                      chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) ));
        
        if( ppl_cnt > max_usr )
                write_file(CONFIG_DIR "max_online", sprintf("%d:%d", to_string(ppl_cnt), time()), 1);

        if( sizeof(ips) > max_ips )
                write_file(CONFIG_DIR "max_ips", sprintf("%d:%d", sizeof(ips), time()), 1);  
                      
        if( ban_cnt > 4 ) {
                write("���IP��ͬʱ�������ߵ����̫���ˣ����Ժ��ٳ��ԣ��� \n");
                destruct(ob);
                return;
        }
        
        if( ip_cnt > MULTI_LOGIN && str != PUBLIC_IP && !BAN_D->is_netclub(str) ) {
                write("�Բ���" + LOCAL_MUD_NAME() + "������ͬip���ص�¼��\n");
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
                write(HIC "�ثe���r�Ŷ��O²��A�п�JGB/BIG5���ܦr�Ŷ��A�Ϊ����n���Τ�C\n" NOR
                      "Ŀǰ���ַ����Ǽ��壬������GB/BIG5�ı��ַ�������ֱ�ӵ�¼�û���\n"
                      "����������Ӣ������(" CYN "�������������롸pass��" NOR ")��\n");
        } else {
                ob->delete_temp("big5");
                write(HIC "Ŀǰ���ַ����Ƿ��壬������GB/BIG5�ı��ַ�������ֱ�ӵ�¼�û���\n" NOR);
                ob->set_temp("big5", 1);
                write("Ŀǰ���ַ����Ƿ��壬������GB/BIG5�ı��ַ�������ֱ�ӵ�¼�û���\n");
                write("����������Ӣ������(" CYN "�������������롸pass��" NOR ")��\n");
        }
        input_to( (: get_id :), ob );
}

protected void get_version(string arg, object ob)
{
        if( !arg || arg[0..3] != CURRENT_CLIENT_VERSION ) {
                write(HIY "������е�ַ����Tomud�ͻ���\n" NOR);
                write(HIG "    http://www.mudbuilder.com/download/tomudsetup.exe\n" NOR);
                write(HIY "��ʹ��Zmud�ͻ���ѡ��6000�˿��������ӡ�\n\n" NOR);
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
        
        write("�÷�����δ���á�\n");
        destruct(ob);
        return;

        if( wiz_level(arg) ) {
                write("��ʦID��������������������޸����롣\n");
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
                write("����Ϸû�� " + arg + " ��λ��ҡ�\n");
                destruct(ob);
                return;
        }     
        if( !ob->restore() ) {
                write("�ý�ɫ���浲����һЩ���⣬������ guest ����֪ͨ��ʦ����\n");
                destruct(ob);
                return;
        }       
        write("������ý�ɫ���������(email)��\n");
        input_to("get_email", 1, ob);
        return;
}

protected void get_email(string arg, object ob)
{
        string pass, msg;
        object user;
        
        user = make_body(ob);        
        if( !user || !user->restore() ) {
                write("�ý�ɫ���浲����һЩ���⣬������ guest ����֪ͨ��ʦ����\n");
                if( user) destruct(user);
                destruct(ob);
                return;
        }
        if( user->query("email") == arg ) {
                write("ϵͳ�ѽ��¹������� Email ���������䡣\n");
                pass = SMTP_D->random_passwd(8);
#ifdef ENABLE_MD5_PASSWORD
                ob->set("ad_password", crypt(pass, sprintf("$1$%d", random(99999999))));
#else
                ob->set("ad_password", crypt(pass, 0));
#endif
                ob->save();

                msg = @LONG
Hello, %id.

��л������������Ϸ%MUD_NAME������ʹ�õ��˺�(%id)�Ĺ���������
�Ѿ���ϵͳ�޸ĳ�Ϊ%passwd���´ε�¼��ʱ������ʹ���µĹ�������
��¼�����������õ�¼ʹ�õ���ͨ���롣�Դ���ɵĲ��㾴��ԭ�¡�

                             %data
LONG ;
                msg = replace_string(msg, "%id", ob->query("id"));
                msg = replace_string(msg, "%MUD_NAME", LOCAL_MUD_NAME());
                msg = replace_string(msg, "%passwd", pass);
                msg = replace_string(msg, "%data", ctime(time()));
                
                MAIL_D->queue_mail(0, 0, arg, "Ϧ������ - " + ob->query("id") + " ��ɫ����", msg);        
                // SMTP_D->send_passmail(0, 0, arg, "Ϧ������ - " + ob->query("id") + " ��ɫ����", msg);
        } else 
                write("�������������ý�ɫ������\n");
        
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
                write("����������Ӣ��ID��\n");
                input_to("pass_id", ob); 
                return;
        }
                
        if( !check_legal_id(arg) ) {
                write(YEL "����������Ӣ�����֣�" NOR);
                input_to("get_id", ob);
                return;
        }
        
        if( intp(MAX_USERS) && MAX_USERS > 0 ) {
                if( (string)SECURITY_D->get_status(arg) == "(player)" &&
                    sizeof(users()) >= MAX_USERS ) {
                        // Only allow reconnect an interactive player when MAX_USERS exceeded.
                        if( !find_body(arg) ) {
                                write("�Բ���" + LOCAL_MUD_NAME() +
                                      "��ʹ�����Ѿ�̫���ˣ������������\n");
                                destruct(ob);
                                return;
                        }
                }
        }

        if( wiz_level(arg) < 1 ) {
                if( REBOOT_CMD->is_rebooting() && !find_body(arg) ) {
                        write("���ڱ�վ��׼��������������ʱ���ܵ�¼�����Ժ��ٳ��ԡ�\n");
                        destruct(ob);
                        return;
                }
        }
                
        if( wiz_level(arg) < wiz_lock_level ) {
                write("�Բ���" + MUD_NAME + "Ŀǰ������ʦ�ȼ� " + WIZ_LOCK_LEVEL + " ���ϵ��˲������ߡ�\n");
                destruct(ob);
                return;
        }

        if( AHACK_D->query_block(arg) ) {
                write(HIY "����˺ű���ʱ�����ˣ����� guest ���������������ʦ��ϵ��\n" NOR);
                destruct(ob);
                return;
        }
            
        if( (string)ob->set("id", arg) != arg ) {
                write("Failed setting user name.\n");
                destruct(ob);
                return;
        }

        if( BAN_D->is_bandid(arg) == 1 ) {
                write("\n�Բ�������ʻ���������һ��ʹ�����ڵ�¼���������������Ӣ������\n");
                write(YEL "����������Ӣ�����֣�" NOR);
                input_to("get_id", ob);
                return;
        }

        if( arg == "guest" ) {
                object user;
		user = find_body("guest");
		if(user)
		{
			write("Ŀǰ guest �˺���������ʹ�ã����һ���ٵ�½��\n");
			destruct(ob);
			return;
		}

		ob->set("body", USER_OB);
		if( !objectp(user = make_body(ob)) )
		{
			destruct(ob);
			return;
		}
		user->set("name","��ʱ����");
		user->set("gender","����");
		user->set("title", "��ͨ����");
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
                                        write("��������ʦר�����룺\n");
                                        input_to("get_wizpwd", 1, ob);
                                        return;
                                }

                                write("\n���棡��û��������ʦר�����룡���½����" HIW " wizpwd " NOR "�������á�\n");
                                write("���������룺\n");
                                input_to("get_passwd", 1, ob);
                                return;
                        }
                        write("�����ɫ�Ѿ����ڣ�������ý�ɫ�����룺\n");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("�������ﴢ�浲����һЩ���⣬������ guest ����֪ͨ��ʦ����\n");
                destruct(ob);
                return;
        }

        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        while (i--)
                if( usr[i] != ob && usr[i]->query("id") == arg )
                        break;
        if( i >= 0 ) {
                write("�������������ʹ����� ID�����������롣\n");
                write("����Ӣ�����֣�\n");
                input_to("get_id", ob);
                return;
        }

        if( ob->query_temp("tomud") )
                write(ALERT(NO_FEE_WARNING)+"ʹ�� " + (string)ob->query("id") +
                        " ������ֽ��ᴴ��һ���µ������ȷ����(y/n)��");
        else
                write("ʹ�� "HIW + (string)ob->query("id") + NOR" ������ֽ��ᴴ��һ���µ������ȷ����("HIR"y"NOR"/"HIY"n"NOR")��");
        
        input_to("confirm_id", ob);
}

protected void get_wizpwd(string pass, object ob)
{
        string old_pass;

        write("\n");
        old_pass = ob->query("wizpwd");

        if( crypt(pass, old_pass) == old_pass ) {
                write(HIG "���ȷ����ɣ���ʦר��������֤ͨ����\n" NOR);
                write("���������룺\n");
                input_to("get_passwd", 1, ob);
                return;
        } else {
                write("�������\n");
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
                        write("�������\n");
                        destruct(ob);
                        return;
                }

                write(HIR "\n������˹������������Ϸ��"
                      "����������޸������ͨ���롣\n" NOR);

                // ����ǣ���ʾĿǰ�������޸������֧��
                ob->set_temp("reset_password", 1);
                write("\n�������趨������ͨ���룺\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( !stringp(ad_pass) ) {
                write(HIC "\n��ע�⣺���IDĿǰ��û�й������룬��������Ĺ������롣\n\n" NOR);
                write(HIW "������ͨ���붪ʧ������£�������������������룬���޸���ͨ\n"
                      "���룬������������һ���ɿ��Ĳ�������ͨ���벻ͬ�Ĺ������룬��\n"
                      "���������ID��ƽʱ��ʹ����ͨ�����½���������Ƶ����ʹ�ù���\n"
                      "�����Ե���Ǳ�ڵ�й©���ա�\n\n" NOR);
                write("��������Ĺ������룺\n");
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
                write("��������ĳ�������Ҫ�����Ԫ�����������Ĺ������룺\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        my_pass = ob->query("password");
        if( stringp(my_pass) && crypt(pass, my_pass) == my_pass ) {
                write(HIR "Ϊ�˰�ȫ�����ϵͳҪ�����������������ͨ���벻����ͬ��\n\n" NOR);
                write("������������Ĺ������룺\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        ob->set_temp("ad_password", crypt(pass, 0));
        write("��������һ�����Ĺ������룬��ȷ����û�Ǵ�\n");
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
                write("����������Ĺ������벢��һ�����������趨һ�ι������룺\n");
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
                write(HIR "�޷���������ң�����Գ������µ�¼���Ǻ���ʦ��ϵ��\n" NOR);
                return ;
        }

        if( rec != 1 && !user->restore()) { // ����Ҫ�ж�rec��ֵ��������������ݷ��ص�ǰһ�δ洢������
                write(HIR "�޷���ȡ��������ݣ�����Գ������µ�¼���Ǻ���ʦ��ϵ��\n" + rec + NOR);
                return ;
        }

#ifdef NO_FEE
        if( ob->query_temp("tomud") )
                write(ALERT("����MUD��Ϸ��Ϧ�����֡�������������ѿ��ţ�����������໥ת�棡\n"));
#endif

        if( rec ) {
                if( user->is_net_dead() ) {
                        reconnect(ob, user);
                        return;
                }
                write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)\n");
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
                        write("�����һ���˳�ʱ��ֻ��" + chinese_number(time() - ob->query("last_on")) +
                              "���ӣ����Ժ��ٵ�¼��\n");
                        destruct(user);
                        destruct(ob);
                        return;
                }

                user->set_temp("logon_time", time());
                user->set("last_save", time());
                if( err = catch(waiting_enter_world(ob, user)) ) {
                        user->set_temp("error", err);
                        msg = HIR "\n���޷�����������磬������ĵ�������һЩ���⣬��Ҫ����ʦ��ϵ��\n\n" NOR;
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
                write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("�ðɣ���ӭ�´�������\n");
                destruct(ob);
                return;
        }

        if( user ) {
                tell_object(user, "���˴ӱ�( " + query_ip_number(ob)
                                + " )����ȡ���������Ƶ����\n");
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
                write("������ҶϿ������ӣ�����Ҫ���µ�½��\n");
                destruct(ob);
                return;
        }

        reconnect(ob, user);
}

protected void confirm_id(string yn, object ob)
{
        if( yn=="" ) {
                write("ʹ��������ֽ��ᴴ��һ���µ����������ȷ����("HIR"y"NOR"/"HIY"n"NOR")��");
                input_to("confirm_id", ob);
                return;
        }   
    
        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("�ðɣ���ô��������������Ӣ�����֣�");
                input_to("get_id", ob);
                return;
        }
        write(CLR);
        write("\n\n");
        write(YEL @TEXT
ע������������������
���������ĸ��մ���������������ִ��������������Ժ��ܸ��ģ���
����������(���Ź۵���������ɾ��)��
 
���벻Ҫѡ���ӹС˵��������������������һ��ѡ���ͺ��Ѹ��ġ����
������ȡ������������֮�⣬,�� mud �����ȡ�ºţ���Ƶ���ƣ�����֣��
��֣�ؽ�����ȡһ���Ƚ������ֵ��������֡�����������������������֣�
��ֱ���ûس����ۣңţԣգңΣ�
��������������������
TEXT NOR
        );
        write("\n����Լ�ȡһ���������֣�");
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
                write("���Ƿ����������������("HIR"y"NOR"/"YEL"n"NOR")��");
                input_to("get_resp", ob);
                return;
        }

        if( arg[0]=='y' || arg[0]=='Y' ) {
                printf("%O\n", ob);
                ob->set("name", Rname);
                write("���趨���Ĺ������룺");
                input_to("new_ad_password", 1, ob);
                return;
        } else if( arg[0]=='n' || arg[0]=='N') {
        Rname = random_name();
        write("���Ƿ����������������("HIR"y"NOR"/"HIY"n"NOR")��");
        printf( HIW" ����"NOR YEL"�� "HIR"%s"NOR YEL" ��"NOR"��"NOR, Rname);
        input_to("get_resp", ob);
        return;
        }
        else {
                write("�Բ�����ֻ��ѡ������("HIR"y"NOR")������("HIY"n"NOR")�� ");
                input_to("get_resp", ob);
                return;
        }


}
protected void get_name(string arg, object ob)
{
        if( arg =="" ) {
                Rname = random_name();
                write("������Ҫ������������������֣���\n");
                write("�������Ƿ����������������("HIR"y"NOR"/"HIY"n"NOR")��");
                write(sprintf( HIW" ����"NOR CYN"�� "HIY"%s"NOR CYN" ��"NOR"��"NOR, Rname));
                input_to("get_resp", ob);
        } else {
                if( !check_legal_name(arg) ) {
                        write("���ٴ����������������֣�");
                        input_to("get_name", ob);
                        return;
                }

                write(printf("%O\n", ob));
                ob->set("name", arg);
                write(HIW "\nΪ�˱�֤�������İ�ȫ����ϷҪ���������������롣һ���ǹ�����\n"
                        "�룬����������������ʧ����ͨ����ʱ��¼��Ϸ���������޸���ͨ\n"
                        "���롣ƽʱ��ʹ����ͨ�����½���������Ƶ����ʹ�ù��������Ե�\n"
                        "��Ǳ�ڵ�й©���ա�\n\n" NOR);
                write("���趨���Ĺ������룺");
                input_to("new_ad_password", 1, ob);
        }
}
protected void new_ad_password(string pass, object ob)
{
        write("\n");
        if (strlen(pass) < 5)
        {
                write("��������ĳ�������Ҫ�����Ԫ�����������Ĺ������룺\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        ob->set_temp("ad_password", crypt(pass, sprintf("$1$%d", random(99999999))));
#else
        ob->set_temp("ad_password", crypt(pass, 0));
#endif

        write("��������һ�����Ĺ������룬��ȷ����û�Ǵ�\n");
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
                write("����������Ĺ������벢��һ�����������趨һ�ι������룺\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

        ob->set("ad_password", old_pass);

        write(HIW "��ͨ��������ƽʱ��¼��Ϸʱʹ�õģ���Ϸ�п���ͨ�� PASSWD ����\n"
              "���޸�������롣\n\n" NOR);
        write("�����������ͨ���룺\n");
        input_to("new_password", 1, ob);
}

protected void new_password(string pass, object ob)
{
        string ad_pass;

        write("\n");
        if (strlen(pass) < 3)
        {
                write("����ĳ�������Ҫ������Ԫ���������������룺\n");
                input_to("new_password", 1, ob);
                return;
        }

        if (stringp(ad_pass = ob->query("ad_password")) &&
            crypt(pass, ad_pass) == ad_pass)
        {
                write(HIR "��ע�⣬Ϊ�˰�ȫ�����ϵͳҪ����Ĺ����������ͨ���벻����ͬ��\n\n" NOR);
                write("����������������ͨ���룺\n");
                input_to("new_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        ob->set_temp("password", crypt(pass, sprintf("$1$%d", random(99999999))));
#else
        ob->set_temp("password", crypt(pass, 0));
#endif

        write("��������һ���������룬��ȷ����û�Ǵ�\n");
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
                write("��������������벢��һ�����������趨һ�����룺\n");
                input_to("new_password", 1, ob);
                return;
        }

        ob->set("password", old_pass);
        if (ob->query_temp("reset_password"))
        {
                // �����û��޸��Լ��������֧���̣����Ǵ���
                // �û���֧�����ת�Ƶ� check_ok ��������ִ
                // �С�
                ob->save();
                check_ok(ob);
                return;
        }

        write("\n");
        write(NOR MAG @TEXT
ѡ���츳������������

һ��������츳��������������ϰ������ϢϢ��ء���Ϸ�е���
����������������츳,���и�Ե����ò���������ԣ�

�١�������Ӱ�칥���������������Ĵ�С��       
�ڡ����ԣ�Ӱ��ѧϰ�书�ؼ����ٶȼ����ʦ����������   
�ۡ����ǣ�Ӱ�������ָ����ٶȼ������������ӵ�������
�ܡ�����Ӱ���������ܵ�������  
�ݡ���Ե��Ӱ����ԡ���������ʦ���������档
��  ��ò��Ӱ����ܣ���ʦ�������Լ���Һ�NPC�����ӡ��      
��������������������
TEXT NOR);
        write("\n���������� "HIR"(1-4)"+NOR" ָ�����е�һ��ֵ���������� "+HIR"0"NOR" ��ϵͳ���ѡ��\n");
        write("����ѡ���� ("CYN"0-4"NOR")��");
        input_to("select_gift", ob);
}
void get_gift(string yn, object ob, mapping my, int select)
{
        if( yn[0] != 'y' && yn[0] != 'Y') {
                random_gift(my, select);
                printf("\n����[%s]������[%s]������[%s]����[%s]\n",
                        display_attr(my["str"]),
                        display_attr(my["int"]),
                        display_attr(my["con"]),
                        display_attr(my["dex"]));
                write("��ͬ����һ���츳��");
                input_to("get_gift", ob, my, select);
                return;
        }
        //write("\n���ĵ����ʼ���ַ��");
        //input_to("get_email", ob, my);
        write("��Ҫ��������("HIG"m"NOR")�Ľ�ɫ��Ů��("HIM"f"NOR")�Ľ�ɫ��");
        input_to("get_gender", ob, my);
}
void select_gift(string yn, object ob)
{
        int i;
        mapping my = ([]);
        if( !sscanf(yn, "%d", i) || i < 0 || i > 4) {
                write("\n�������������ѡ��");
                input_to("select_gift", ob);
                return;
        }
        if( i) {
                write("\n����������Ҫ����ֵ(10-30)��");
                input_to("set_gift", ob, my, i);
        } else get_gift(" ", ob, my, i);
}

void set_gift(string yn, object ob, mapping my, int select)
{
        int i;

        if( !sscanf(yn, "%d", i) || i < 10 || i > 30) {
                write("\n��ֵ�������������룺");
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
                write("��Ҫ��������("HIG"m"NOR")�Ľ�ɫ��Ů��("HIM"f"NOR")�Ľ�ɫ��");
                input_to("get_gender", ob);
                return;
        }
        if( gender[0]=='m' || gender[0]=='M' )
                ob->set_temp("gender", "����");
        else if( gender[0]=='f' || gender[0]=='F' )
                ob->set_temp("gender", "Ů��" );
        else {
                write("�Բ�����ֻ��ѡ������("HIG"m"NOR")��Ů��("HIM"f"NOR")�Ľ�ɫ��");
                input_to("get_gender", ob);
                return;
        }
        if( find_body(ob->query("id")) ) {
                write(HIR "�����������Ѿ���¼������������ˣ���"
                      "�˳��������ӡ�\n" NOR);
                destruct(ob);
                return;
        }
#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() )
                DATABASE_D->connect_to_database();

        if( DATABASE_D->db_find_user("id", ob->query("id")) ) {
                write(HIR "\n�����������Ѿ�������վע���ˣ����˳��������ӡ�\n" NOR);
                destruct(ob);
                return;
        }
#endif
        ob->set("body", USER_OB);
        if( !objectp(user = make_body(ob)) ) {
                write(HIR "\n���޷���¼����µ����������ѡ��\n" NOR);
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
        
        CHANNEL_D->do_channel( this_object(), "sys","����һ������ң�"+user->query("name")+"["+user->query("id")+"]��"NOR);
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
                write("��û��Ȩ�޴�����ҡ�\n");
                return 0;
        }
 
        seteuid(getuid());
        user = new(USER_OB);
        if( !user ) {
                write("���ڿ������������޸�ʹ��������ĳ�ʽ���޷����и��ơ�\n");
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
        user->set("title", "��ͨ����");
        user->set("birthday", time() );
        user->set("potential", 100);
        user->set("food", (user->query("str") + 10) * 10);
        user->set("water", (user->query("str") + 10) * 10);
        user->set("channels", ({ "chat", "rumor","tell","new","sos","bill","family"}) );
        user->set("chann", (["new" : 1, "chat" : 1, "bill" : 1 ])); // Ĭ����ʾ�������ڵ�Ƶ��
        
        // ��¼����
        NAME_D->map_name(user->query("name"), user->query("id"));

        user->set("env/wimpy", 60);
        user->set("env/roomlist", 1);
}

void waiting_enter_world(object ob, object user)
{
        string msg;

        if( !is_root(previous_object()) )
                return;
        
        ob->set_temp("waiting_enter", 1); // ��ֹ������
/*
        if( file_size(NOTICE) > 0 ) {
                msg  = BLINK "��  " NOR + WHT + MUD_CHINESE_NAME + NOR + 
                       HIK "������                            " NOR + 
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

        write(WHT "����������������� " HIR + WAITING_ENTER_TIME + NOR + WHT " ����Զ�������Ϸ\n" NOR);
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
                write(TOTOP(1) + WHT "����������������� " HIR + timer + NOR + WHT " ����Զ�������Ϸ\n" NOR);
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
                if( user->query("gender")=="Ů��") cloth = new("/clone/misc/pink_cloth");
                else cloth = new("/clone/cloth/cloth");
                cloth->move(user);
                catch(cloth->wear());
        } else
                write(HIY ">>>>>>>> ���ѳ���. <<<<<<<<\n" NOR );  
        
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

                write("�����߽���" + LOCAL_MUD_NAME() + "��\n\n");
                tell_room(startroom, user->query("name") +
                          "���߽���������硣\n", ({ user }));

#ifdef MCCP_SUPPORT
                if (! compressedp(user))
                        write(YEL "����ʹ�õ���������δ������·����ѹ��("
                              HIY "MCCP" NOR YEL ")���ܣ������������ù�������·����˳����\n" NOR);
#endif
        }
        
        login_ob = new(LOGIN_OB);
        login_ob->set("id", user->query("id"));
        login_ob->restore();
        if( login_ob->query("registered") ) {
                write("�󩤩��������������������������������Ϣ����������������������������������\n");
                write("��ĿǰȨ�ޣ�" + wizhood(user) + "\n");
                if( !intp(login_ob->query("login_times")) ) {
                        write(NOR "���ǵ�һ�ι���" + LOCAL_MUD_NAME() + "��\n");
                        login_ob->set("login_times", 1);
                        // show rules
                } else {
                        login_ob->add("login_times", 1);
                        write("���ϴι���" + LOCAL_MUD_NAME() + "�� " + HIG +
                                ctime(login_ob->query("last_on")) + NOR + " �� " + HIR +
                                login_ob->query("last_from") + NOR + " ���ӵġ�\n");
                }
                write("�󩤩���������������������������������������������������������������������\n");

        }
        destruct(login_ob);
        
        if( ob->query_temp("no_allow_ip") )   
                write("\n\n���棺��δ�趨�Լ��ĵ�¼��ַ��Χ������"HIR" allowip "NOR"ָ�����á�\n\n");

        if( user->query("gender") == "����"&&user->query("age")<=25 ){
                switch(random(2)) { 
                        case 0 : str = "������ʿ";break;
                        case 1 : str = RANK_D->query_respect(user);break;
                }
        } else if( user->query("gender") == "Ů��"&&user->query("age")<=25 ) {
                switch(random(2)) {
                        case 0 : str = "������Ů";break;
                        case 1 : str = RANK_D->query_respect(user);break;
                }
        } else str = RANK_D->query_respect(user);
        
        if( !(wizardp(user) && user->query("env/no_login_msg")) )
                message("shout", HIR"���м��ջ��"NOR+": "+CYN"��˵������һλ����"+HIW+user->name()+NOR CYN"��"+str+"\n"NOR,users());

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
                BAN_D->open_club_line(user);    // �Զ�������������

        // notice user the user of this mud
        NEWS_D->prompt_user(user);
        ANALECTA_D->prompt_user(user);

        if( mapp(marry = user->query("couple")) && ! undefinedp(marry["couple_id"]) ) {
                string tmpstr, tmpstr1;
                object couple_ob = find_player(marry["couple_id"]);
                if( couple_ob ) {
                        if( (string)user->query("gender") != "����" ) {
                                tmpstr1 = "���";
                                tmpstr  = "����";
                        } else {
                                tmpstr1 = "����";
                                tmpstr  = "���";
                        }
                        write(sprintf(WHT HIM "\n���%s%s�Ѿ����������þ��ˣ���ȥ��%s�ɡ�����\n" NOR,
                                      tmpstr1, couple_ob->name(), gender_pronoun(couple_ob->query("gender"))));
                        tell_object(couple_ob, sprintf(WHT HIM "\n���%s%s���Ʋ�ס�����˼����������������ȥ��%s����к��ɡ�����\n" NOR,
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
                tell_room(environment(user), user->query("name") + YEL"�������߻ص�������硣\n"NOR,
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
                sprintf("%s(%s)��(%s)�������߽��롣", user->query("name"),
                        user->query("id"), query_ip_number(user)) );
        
}

int check_legal_id(string id)
{
        int i;
        i = strlen(id);
    
        if( (strlen(id) < 3) || (strlen(id) > 10 ) ) {
                write("�Բ������"+HIW"Ӣ��"NOR+"���ֱ����� 3 �� 10 ��Ӣ����ĸ��\n");
                return 0;
        }
        if( member_array(id, banned_id) != -1) {
                write("�Բ���" HIC"��" + id + "��" NOR"�����������"
                      "��ĺ��⣬��������Ӣ�����֡�\n");
                return 0;
        }
        while(i--) {
                if( id[i]<'a' || id[i]>'z' ) {
                        write("�Բ������"+HIW"Ӣ��"NOR+"����ֻ����Ӣ����ĸ��\n");
                        return 0;
                }
        }
        return 1;
}

string random_name()
{
        string *lname = ({
"��","Ǯ","��","��","��","��","֣","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","ʩ","��",
"��","��","��","��","��","κ","��","��","��","л","��","��","��","ˮ","�","��","��","��","��","��","��","��","��","��",
"³","Τ","��","��","��","��","��","��","ɵ","��","Ԭ","��","��","��","ʷ","��","��","��","�","Ѧ","��","��","��","��",
"��","��","��","��","��","��","��","��","��","��","ʱ","��","Ƥ","��","��","��","��","��","Ԫ","��","��","ӯ","ƽ","��",
"��","��","Ф","��","Ҧ","��","տ","��","��","ë","��","��","��","��","��","��","��","��","��","��","̸","��","é","��",
"��","��","��","��","��","ף","��","��","��","��","��","��","��","��","֧","��","��","��","¬","Ӣ","��","��","˾��",
"�Ϲ�","ŷ��","�ĺ�","���","����","����","����","�ʸ�","ξ��","����","�̨","����",
"����","���","����","����","̫��","����","����","����","ԯ��","���","����","����",
"����","Ļ��","˾ͽ","ʦ��","��","��ľ","����","����","���","����","����","����",
"��ֺ","�й�","�׸�","����","����","�ַ�","��۳","Ϳ��","��ǧ","����","����","�Ϲ�",
"����","�麣","����","΢��","��","˧","��","��","��","��","��","��","����","����","����","����",
                        });
        return (lname[random(200)] + chinese_number(random(20)));
}

int check_legal_name(string name)
{
        int i;
        
        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > 10 ) ) {
                write("�Բ�������������ֱ����� 1 �� 5 �������֡�\n");
                return 0;
        }
        if( !is_chinese(name) ) {
                write("�Բ��������á����ġ�ȡ���֡�\n");
                return 0;
        }
        if( member_array(name, banned_name) != -1 ) {
                write("�Բ����������ֻ���������˵����š�\n");
                return 0;
        }
        for( i=0;i<sizeof(banned_name);i++ ) {
                if(  strsrch(name, banned_name[i]) != -1 ){
                        write("�Բ����������ֻ���������˵����š�\n");
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
