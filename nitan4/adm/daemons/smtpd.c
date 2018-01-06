/**************************
 *                        *
 * /adm/daemons/smtp_d.c  *
 *                        *
 * by Find@TX.            *
 *                        *
 **************************/

#include <net/socket.h>
#include <login.h>
#include <ansi.h>
#include <origin.h>
#include <mudlib.h>

#define PUBLIC_MUD_MAIL         "lonely-21@163.com" 
#define RANDOM_PWD_LEN		8 /* ������볤�� */
#define REGFILE			"/data/mail_reg.o"
#define REG_ROOM                "/d/register/regroom"
#define BASE64_D                "/adm/daemons/base64d" 

inherit F_SAVE;

// class������C++�����ģ��벻��LPCҲ֧��
class email
{
	string rcpt;	// �ռ��ߵ�ַ
	string body;	// ����
	int status;     // ״̬��
	string id;	// �û� ID
	string passwd;  // ���� 
	object user;
	int normal;
}

protected void write_callback(int fd,string outgoing);
protected varargs void write_callback(int fd,string outgoing);
protected void close_callback(int fd);
protected int permit_reg_email(string mail);
protected int mail_have_reg(object user,string mail);
string    random_passwd(int len);
void      check_user(object user);

/*
 * �����Ƿ�������ĵ�½�������롣��һЩ����������Ҳ��Ҫ����
 * ������֤�ģ����ڲ����ṩ�����������ʼ��ٻ�����֮�࣬Խ��
 * Խ��Ĳ��÷���������֤�������� Outlook express ���÷���
 * ������ѡ���ҵķ�����Ҫ��������֤����
 * ������� SMTP �� ESMTP �����ã������ķ����ṩ�̲�Ҫ��
 * ������֤���㾡���Բ���������趨��
 */
// ESMTP���µ�FoxMail v3.11Ҳ֧�֡�

string  *mail_reg; // ���ﱣ����ע���Email��ַ��
mapping user_unreg=([]); // ���ﱣ���ʼ��ѷ�������δȷ�ϵ��û���ID

protected string mailname = "lonely-21",mailpasswd = "921121";

protected mixed content = ([]);

/* �����趨��� SMTP �������������� IP ��ַ */
protected string domain_name = "smtp.163.com", address = "202.108.5.82";

/*
 * �����ⲿ���ǽ��� SMTP ������ IP ��ַ�Ľ����õġ�
 * һ�� SMTP �������������ǲ����ģ��� IP ��ַ�п�
 * �ܱ仯����������Ϸ�����к��ٻ�ע�������һ������
 * �仯�Ǻ��鷳�ģ�263 ��һ�ξ͸ı��� IP ��ַҲû��
 * ֪ͨ���ǣ��ҵ������Ժ�ŷ��֣�����Һ����Σ����
 * ������������ܡ�
 */
protected void resolve_callback( string o_address, string resolved, int key )
{
	if( stringp(resolved) && (resolved != "") && (address != resolved) )
	{
		address = resolved;
		save();
		restore();
		log_file("smtp",sprintf("SMTP: Զ�� SMTP �ʼ�������IP��ַ��ת��Ϊ %s\n",address));
	}
}

/* ��������������� CRON_D ��ʱ���еģ�������1Сʱ���һ�Ρ�*/
void update_mail_server_ip()
{/*
	if(previous_object() && (geteuid(previous_object()) != ROOT_UID))
	return;*/
	resolve( domain_name, "resolve_callback" );
}

string query_save_file()
{
	return REGFILE;
}

protected void create()
{
	seteuid(getuid());
	if (file_size(REGFILE)<=0){
		mail_reg=({});
		user_unreg=([]);
		save();
	}
	restore();
	resolve( domain_name, "resolve_callback" );
}

/*
 * ��������������ע���õ��Ǹ��������ע������
 * ���еģ�user �ǽ���ע�����������mail ��ע
 * ��ĵ����ʼ���ַ��
 * ��������Ӧ���Ժ��д˺������������һ�¼�顣
 */

 
void register_mail(object user,string mail)
{
	object link;
	string msg,passwd,server;
	int s,err;
	class email newmail;

	if(!user) return;
	if(!stringp(mail) || mail == "") return;

	mail = lower_case(mail);

	if(!objectp(link = user->query_temp("link_ob")))
	{
		tell_object(user,"���ĵ�������ȫ���޷�����ע�ᣬ�������������ע��.\n\n");
		destruct(user);
		return;
	}

	if(strsrch(mail,',') >= 0)
	{
	write(sprintf("��ĵ����ʼ���ַ��%s ������Ƿ��ַ���\n�������������ע�ᡣ\n",mail));
	return;
	}

	if(mail_have_reg(user,mail)) return;

	passwd = random_passwd(RANDOM_PWD_LEN);
	server = sprintf("%s 25",address);

	/*
	 * PUBLIC_MUD_MAIL ���������ĵط�����ģ�������Ϸ
	 * ���⽻���ĵ����ʼ���ַ��
	 */
	msg = sprintf("From: \"%s\" <%s>\nTo: %s\nSubject: ����%s������\n\n",
	MUD_NAME,PUBLIC_MUD_MAIL,mail,CHINESE_MUD_NAME);
	msg += sprintf(user->name()+"����ã���л������"+MUD_NAME+"������Ϸ��\n\n�����˺ţ�%s\n    ���룺%s\n",user->query("id"),passwd);
	msg += "\nע�⣺����˺�ĿǰΪ��ʱ�˺ţ�������48Сʱ֮�ڵ�½ȷ�ϡ�\n";
	msg +=   "\t  ����δ��½���ᱻ�Զ�ɾ����\n";
	msg +=   "\t  ����ע���½�������������� "+ PUBLIC_MUD_MAIL+" ��ϵ��\n";
	msg += "\n\t  ����Ϸ����ҳ�� "+MUD_WEB+"
	  ��������ϸ�İ��������д������ָ�ϡ�������ܣ����Ż�\n\t  ��������ô���

                 ף����"+CHINESE_MUD_NAME+"�����죡";

	newmail = new(class email);
	newmail->rcpt = mail;
	newmail->body = msg;
	newmail->id = user->query("id");
	newmail->passwd = passwd; 
	newmail->user = user;
	user->start_busy(100);

	s = socket_create(STREAM,"read_callback", "close_callback");
	if(s<0)
	{
		log_file("socket","Socket create err: "+socket_error(s)+"\n");
		tell_object(user,"ע������з�����������������ע��һ�Ρ�\n");
		return;
	}

	content += ([ s : newmail ]);

	err = socket_connect(s,server,"read_callback", "write_call_back");
	if(err < 0)
	{
		map_delete(content,s);
		log_file("socket","Socket connect err: "+socket_error(err)+"\n");
		tell_object(user,"ע������з�����������������ע��һ�Ρ�\n");
		socket_close(s);
		return;
	}

	tell_object(user,"�ʼ������У����Ժ�1�ְ��ӣ���������\n");
	call_out("time_out",90,s);
}

protected void time_out(int fd)
{
	class email mailmsg;

	if(undefinedp(content[fd]))
		return;

	mailmsg = content[fd];

	if(objectp(mailmsg->user))
	{
		tell_object(mailmsg->user,"\n���͹��̳�ʱ������������һ�Ρ�
		�����п����ǣ�SMTP�ʼ���������IP��ַ�Ѿ����ġ�\n");
		(mailmsg->user)->stop_busy();
	}

	map_delete(content,fd);
	socket_close(fd);
}

void send_mail(object user, string mail_from, string mail_to, string topic, string data)
{
	string server;
	int s, err;
	class email newmail;

        if(strlen(data) > 65536)
        {
                write("�㲻�ܷ��ʹ���64K���ʼ���\n");
                return;
        }
        
        log_file("mail", sprintf("%s %s try to send mail <%s> Size:%d\n",
                                 log_time(), (user ? user->query("id") : "SYSTEM"),
                                 topic, strlen(data)));

        if(!mail_from || sscanf(mail_from, "%*s@%*s") != 2)
                mail_from = "lonely-21@163.com";
                
        if(!mail_to || sscanf(mail_to, "%*s@%*s") != 2)
        {
                write("�޷��������ַ�����ʼ���\n");
                return;
        }
                
	mail_to = lower_case(mail_to);

	if(strsrch(mail_to, ',') >= 0)
	{
	        write(sprintf("�����ʼ���ַ��%s ������Ƿ��ַ����޷����͡�\n", mail_to));
	        return;
	}

	server = sprintf("%s 25",address);

	newmail = new(class email);
	newmail->rcpt = mail_to;
	newmail->body = data;
	newmail->id = (user ? user->query("id") : "SYSTEM");
        newmail->passwd = "abcdefg"; 	
	newmail->user = 0;
	
	s = socket_create(STREAM,"read_callback", "close_callback");
	if(s<0)
	{
		log_file("socket","Socket create err: "+socket_error(s)+"\n");
		write("�ʼ����͹����з�������������������һ�Ρ�\n");
		return;
	}

	content += ([ s : newmail ]);

	err = socket_connect(s,server,"read_callback", "write_call_back");
	if(err < 0)
	{
		map_delete(content,s);
		log_file("socket","Socket connect err: "+socket_error(err)+"\n");
		write("�ʼ����͹����з�������������������һ�Ρ�\n");
		socket_close(s);
		return;
	}

	tell_object(user,"�ʼ������У����Ժ�1�ְ��ӣ���������\n");
	call_out("time_out",90,s);
}

protected void success_register(int fd)
{
	class email mailmsg;
	object usr,link;

	if(undefinedp(content[fd]))
		return;

	mailmsg = content[fd];
	if(!objectp(usr = mailmsg->user))
		return;
	if(!objectp(link = usr->query_temp("link_ob")))
		return;

	(mailmsg->user)->stop_busy();
	map_delete(content,fd);
	tell_object(usr,sprintf("�����������������Ѹ������Ǽǵĵ�ַ������"HIW"%s"NOR"
����"HIG"�����"NOR"�����������䡣�������"HIC"24"NOR"Сʱ��δ���յ�����
�����������ʼ��������� "HIY"%s"NOR" ����˵����ϸ�����
���ǻᾡ��Ϊ�����������֮������½⡣
ף����%s�����죬�ټ���\n",mailmsg->rcpt,PUBLIC_MUD_MAIL,MUD_NAME));
	
	mail_reg=mail_reg+({mailmsg->rcpt});
	save();
	restore();

	link->set("last_on", time());
	link->set("last_from", query_ip_name(usr));
	link->set("email",mailmsg->rcpt);
	link->set("oldpass",link->query("ad_password"));
	link->set("ad_password",crypt(mailmsg->passwd,0));
	usr->set("email",mailmsg->rcpt);
	usr->set("have_reg",1);
	usr->delete("new_begin");
	link->save();
	usr->save();
	tell_room(environment(usr),"��ֻ������ǰһ����"+usr->query("name")+"�����ˡ�\n",({usr}));
	message("channel:sys",sprintf(HIR"���ʼ�ע�ᾫ�顿"HIW"%s(%s)�ʼ������˳���Ϸ��\n"NOR,
		usr->name(),geteuid(usr)),filter_array(users(),(: wizardp($1) :)));
	user_unreg[mailmsg->id]=time(); // ��������û���ID��δȷ��������
	log_file("smtp",sprintf("%s(%s)���ʼ��Ѿ����� %s��\n",usr->name(),geteuid(usr),mailmsg->rcpt));
	save();
	restore();
	destruct(link);
	destruct(usr);
}

protected void close_callback(int fd)
{
	socket_close(fd);
}

/* �˺����������͹����е��������� */
protected void mail_error(int fd,string message)
{
	class email mailmsg;

	mailmsg = content[fd];

	log_file("smtp_err",sprintf("ERROR:\n%s\nid: %s\nmail: %s\n\n",
			message,mailmsg->id,mailmsg->rcpt));

	if(objectp(mailmsg->user))
	{
		tell_object(mailmsg->user,sprintf("\n���͹����г����쳣����\n%s\n������һ�Ρ�\n\n",
			message));
		(mailmsg->user)->stop_busy();
	}

	map_delete(content,fd);
	socket_close(fd);
}

protected void read_callback(int fd,string message)
{
	int rcode,err;
	string mechanism;
	class email mailmsg;

	if(undefinedp(content[fd]))
	{
		socket_close(fd);
		return;
	}

	mailmsg = content[fd];

	rcode = atoi(message[0..2]);

	if(!rcode || (rcode > 500))
	{
		mail_error(fd,message);
		return;
	}

	if(!mailmsg->status)  // ������ͨ
	{
		socket_write(fd,sprintf("EHLO %s\r\n",query_host_name()));
		mailmsg->status++;
		return;
	}

	if(mailmsg->status == 1) // server ready
	{
		if((rcode == 500))	// command not recognized
		{
			if(mailmsg->normal)
			{
				mail_error(fd,message);
				return;
			}

			socket_write(fd,sprintf("HELO %s\r\n",query_host_name()));
			mailmsg->normal = 1;
			return;
		}

		if(mailmsg->normal)
		{
			socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
			mailmsg->status = 3;
			return;
		}

		if(sscanf(message,"%*sAUTH=%s\n%*s",mechanism) == 3)
		{

			socket_write(fd,sprintf("AUTH %s\r\n",mechanism));
			mailmsg->status = 2;
			return;
		}

		// ESMTP Э�鲻��Ҫ��֤
		socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
		mailmsg->status = 3;
		return;
	}

	if(mailmsg->status == 2)	// Authentication
	{
		string quest;

		if(rcode == 334)	// ��֤����
		{
			/*
			 * ������ ESMTP Э�����֤���֣�ESMTP Э��涨
			 * ��֤��Ϣʹ�� BASE64 ���롣
			 * ����� base64_decode �� base64_encode ����
			 * ���� base64_d ����� decode �� encode ������
			 * �����Ƕ������ simul_efun��
			 */
			quest = message[4..];
			quest = replace_string(quest,"\n","");
			quest = replace_string(quest,"\r","");
			quest = BASE64_D->decode(quest);
			if(quest[0..3] == "User")
			{
				socket_write(fd,sprintf("%s\r\n",BASE64_D->encode(mailname)));
				return;
			}
			else if(quest[0..3] == "Pass")
			{
				socket_write(fd,sprintf("%s\r\n",BASE64_D->encode(mailpasswd)));
				return;
			}
		}

		// ��֤ͨ��
		socket_write(fd,sprintf("MAIL FROM: <%s>\r\n",PUBLIC_MUD_MAIL));
		mailmsg->status = 3;
		return;
	}

	if(mailmsg->status == 3)
	{
		socket_write(fd,sprintf("RCPT TO: <%s>\r\n",mailmsg->rcpt));
		mailmsg->status = 4;
		return;
	}

	if(mailmsg->status == 4)
	{
		socket_write(fd,sprintf("DATA\r\n"));
		mailmsg->status = 5;
		return;
	}

	if(mailmsg->status == 5)
	{
		if(rcode == 354)	// ready receive data
		{
			err = socket_write(fd,sprintf("%s\r\n.\r\n",mailmsg->body));
			if( (err < 0) && (err != EEALREADY) )
				call_out("write_callback",1,fd,sprintf("%s\r\n.\r\n",mailmsg->body));
			mailmsg->status = 6;
			return;
		}
		else
		{
			mail_error(fd,message);
			return;
		}
	}

	if(mailmsg->status == 6)
	{
		socket_write(fd,sprintf("QUIT\r\n"));
		mailmsg->status = 7;
		return;
	}

	if((mailmsg->status == 7) && (rcode == 221))
	{
		success_register(fd);
		return;
	}

	mail_error(fd,message);
}

protected varargs void write_callback(int fd,string outgoing)
{
	int err;

	if(stringp(outgoing) && (outgoing != ""))
	{
		err = socket_write(fd,outgoing);

		if( (err < 0) && (err != EEALREADY) )
		{
			call_out("write_callback",1,fd,outgoing);
			return;
		}
	}
}

/*
 * �����ע��ĵ����ʼ���ַ�ĸ������������ʵ�֣�
 * ���Ը����Լ�����Ҫ�������롣
 * Ҫ�����ĳЩ mail ��ַ�����ƣ�Ҳ������ʵ�֡�
 */

protected int mail_have_reg(object user,string mail)
{
	object link;
	string id;

	if(!user) return 1;
	link = user->query_temp("link_ob");
	if(!link) return 1;
	if(!stringp(mail)) return 1;

	id = user->query("id");

	if(member_array(mail,mail_reg)!=-1)
	{
		tell_object(user,"����ʼ���ַ�Ѿ�ע����ˣ�����Ϸ������ͬһ��ַ����ע�ᡣ\n�Բ���\n");
		message("channel:sys",sprintf(HIR"���ʼ�ע�ᾫ�顿��%s(%s)ע�����󱻾ܾ����˳���Ϸ��\n"NOR,
		user->name(),geteuid(user)),filter_array(users(),(: wizardp($1) :)));
		destruct(user);
		destruct(link);
		rm(DATA_DIR + "login/" + id[0..0] + "/" + id + ".o");
		rm(DATA_DIR + "user/"  + id[0..0] + "/" + id + ".o");
		return 1;
	}

	else
		return 0;
}

/*
 * ����48Сʱδ����ȷ��ɾ������
 * ��������������� CRON_D ��ʱ���еģ�
 * һСʱ���һ�Ρ�
 */
void user_no_login()
{
	array player;
	string time;
	array name;
	object user,link;
	int i;

// ���������������Ȩ�޵�
	if(!previous_object()||(geteuid(previous_object()) != ROOT_UID)&&(geteuid(previous_object()) != "jjgod"))
		return;

	name=keys(user_unreg); // ��������ʼ��ѷ����ȴ�ȷ�ϵ��û�array
	for(i=0; i<sizeof(name); i++){
		if ((time()-user_unreg[name[i]])>=172800){ // ������Щid��ע��ʱ��������ʱ�����2��=48Сʱ=172800��
			if (!sizeof(player)) player=({name[i]});
			else player+=({name[i]}); // ��player ���array�м���������
			map_delete(user_unreg,name[i]); // ��ԭ�ȵ�mapping��ɾ��������
			save();
			restore();
		}
	}

// ������Ƕ�player���array�Ĵ�����
	if(!player || !sizeof(player)){
		message("system",HIW"�������޷������������" NOR,users() );
		return;
	}

	time = ctime(time());

	foreach(string one in player)
	{
		string f;

		if(objectp(user = find_player(one)))
		{
			if(objectp(link = user->query("link_ob")))
			destruct(link);
			destruct(user);
		}

		if(file_size(f = sprintf(DATA_DIR+"login/%c/%s.o",one[0],one)) > 0)
			rm(f);
		if(file_size(f = sprintf(DATA_DIR+"user/%c/%s.o",one[0],one)) > 0)
			rm(f);
		log_file("smtp",sprintf("(%s)����48Сʱδ����ȷ�ϱ�ɾ����%s\n",one,time));
	}
}

/* �����������һ������Ϊ len ��������� */
string random_passwd(int len)
{
	int cap,low,num,n;
	string passwd;
	string Random_Passwd ="ABCDEFGHIJKL1234567890mnopqrstuvwxyzabcdefghi1jk9MNOPQRS4TUVW9XYZ";

	if(!intp(len))
		return "12345";

	if(len < 4 || len > 8)
		len = 8;

	do
	{
		cap=0; low=0; num=0; passwd = "";
		for(int i=0;i<len;i++)
		{
			n = random(sizeof(Random_Passwd));
			if( Random_Passwd[n] <='Z' && Random_Passwd[n] >='A' )
				cap++;
			else if( Random_Passwd[n] <='z' && Random_Passwd[n] >='a' )
				low++;
			else if( Random_Passwd[n] <='9' && Random_Passwd[n] >='0' )
				num++;
			passwd += Random_Passwd[n..n];
		}
	}
	while(!cap || !low || !num);

	return passwd;
}

// ������������ʱ�Ҽ���Ϊ�˴���48Сʱ���Ѿ���½����ң���δע���û��б���ɾ����Щ��ҡ�
void finish_reg(string id)
{
	int i;

	for (i=0;i<sizeof(user_unreg);i++)
	if (intp(user_unreg[id])&&user_unreg[id]!=0)
	{
		map_delete(user_unreg, id);
		save();
		restore();
		return;
	}
}

// ����������������ԵĽӿں���
mapping query_users()
{return user_unreg;}

array query_mail_reg() { return mail_reg; }

string query_smtp_info()
{
	string msg;
	msg="\n������������"+domain_name;
	msg+=("\n������IP��ַ��"+address);
	msg+=("\n�û�����"+mailname);
	msg+=(" �û����룺*****");
	msg+="\n";
	return msg;
}

void remove_mail(string mail)
{
	mail_reg -= ({ mail });
	save();
}

void stop_reg(object ob)
{
	ob->delete("ad_password");
	ob->set("ad_password", ob->query("oldpass"));

	ob->delete("have_reg");
	ob->delete("oldpass");

	remove_mail(ob->query("email"));
	map_delete(user_unreg, ob->query("id"));
}