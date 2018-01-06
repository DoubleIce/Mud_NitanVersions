// by ephq@YSZZ
// A��
#include <net/socket.h>
#include <net/socket_errors.h>
#include <ansi.h>

#define IP_ADDRESS "60.28.2.64 80"
#define MAX_ARRAY 20
inherit ITEM;

nosave mapping stock = ([]);
string *now_array = ({});		/*��ǰ��ȡ����*/

nosave string addresurl, buffer_msg;
nosave int online = 0, socket, waiting = 0;
//nosave object owner;
//nosave string *array_stock;
nosave object *waiting_buy;
nosave mapping times = allocate_mapping(6);
nosave int flag = 0, size = 0;

mapping query_stock_info() { return stock; }
mapping query_update_time() { return times; }
string *query_array() { return now_array; }
int is_waiting() { return waiting; }
int is_online() { return online; }


void start_connect();
void get_addressurl();
string stockurl()
{ 
return "GET " + addresurl + " HTTP/1.1
Pragma: No-Cache
Host: hq.sinajs.cn\n\n";
}

//just test...
void test()
{ now_array = ({
  "sh600500",  "sh600050",  "sh601398",  "sh601099",  "sz000629",  "sh600010",  "sz000002",  "sh601600",  "sh600068",  "sz000016",  "sz000678",
  "sz000703",  "sz000063",  "sz002124",  "sz002157",  "sh601318",  "sh600690",  "sz000609",  "sh600812",  "sh600008",  "sz000777",  "sh600266",
  "sz000839",
});
}

private void sys_info(string msg)
{
        CHANNEL_D->do_channel(this_object(), "sys", msg);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "��Ʊ����");
        sys_info("��Ʊ�����Ѿ�������");
	set_heart_beat(6);
}
int clean_up()
{
        return 1;
}

void heart_beat()
{
	int fd;
	if( waiting ) {
		socket_close(socket);
		sys_info("���ӳ�ʱ����������\n");
		start_connect();
		return;
	}

	if( online ) {
		if( sizeof(now_array) == 0 ) return;
		flag = 0;
		get_addressurl();
		size = 0;
		fd = socket_write( socket, stockurl());
		if( fd != EESUCCESS ) {
			sys_info("�޷����ӷ�����1\n");
			return;
		}
		waiting = 1;
		return;
	}
	start_connect();

}

void get_addressurl()
{
	string *current_array;

	if( flag == 0 ) {
		if( sizeof(now_array) < MAX_ARRAY ) {
			addresurl = "/list=sh000001,s_" + implode(now_array,",s_");
			flag = -1;
			return;
		}
		current_array = now_array[0..MAX_ARRAY-1];
		addresurl = "/list=sh000001,s_" + implode(current_array,",s_");
		flag = MAX_ARRAY;
		return;
	}

	if( sizeof(now_array) < flag + MAX_ARRAY ) {
		current_array = now_array[flag..sizeof(now_array)-1];
		addresurl = "/list=sh000001,s_" + implode(current_array,",s_");
		flag = -1;
		return;
	}

	current_array = now_array[flag..flag + MAX_ARRAY - 1];
	addresurl = "/list=sh000001,s_" + implode(current_array,",s_");
	flag += MAX_ARRAY;
}

void start_connect()
{
	int fd;

	if( sizeof(now_array) == 0 ) return;

	flag = 0;
	get_addressurl();
	socket = socket_create(STREAM, "read_callback", "close_getstock_callback");
	fd=socket_connect( socket, IP_ADDRESS, "read_callback","write_getstock_callback");
        if( fd == EESUCCESS ) {
        	waiting = 1;
        	return;
        }  else {
		sys_info("�޷����ӷ�����2\n");
	}

}

void par_result(string msg)
{
	string str, *strs, t;
	int year, mon, day, hour, min, sec;

	if( sscanf(msg,"%*s charset=GBK\r\n\r\n%s", str) < 1 )
		return;;


	str = replace_string(str, "\n", "");

	strs = explode(str,";");

	if( sizeof(strs[0]) > 25 ) {
		t = strs[0][(strlen(strs[0])-20)..(strlen(strs[0])-2)];
		if( sscanf(t,"%d-%d-%d,%d:%d:%d\"",year, mon, day, hour, min, sec) != 6 ) {
			sys_info("�޷�ȡ�ù�Ʊ����ʱ��1��\n");
			return;;
		} else {
			times = ([
			"year" :  year,
			"mon" : mon,
			"day" : day,
			"hour" : hour,
			"min" : min,
			"sec" : sec,
			]);
		}
	} else {
		sys_info("�޷�ȡ�ù�Ʊ����ʱ��2��\n");
		return;;
	}

	if( sizeof(strs) < 2 ) {
		sys_info("�޷�ȡ�ù�Ʊ����ʱ��3��\n");
		return;;
	}

	strs = strs[1..sizeof(strs)-1];

	foreach(str in strs) {
		string code, name;
		int val,vals, per, s1, s2;
		if( sscanf(str, "var hq_str_s_%s=\"%s,%f,%f,%f,%d,%d\"", code, name, val,vals, per, s1, s2) == 7 ) {
			stock[code] = ([
			"name" : name,
			"price" : val,
			"sprice" : vals,
			"per" : per,
			"s1" : s1,
			"s2" : s2,
			"year" :  year,
			"mon" : mon,
			"day" : day,
			"hour" : hour,
			"min" : min,
			"sec" : sec,
			]);
			size++;
		}
	}
}


void continue_connect()
{
	int fd;

	get_addressurl();
	if( online ) {
		fd = socket_write( socket, stockurl());
		if( fd != EESUCCESS ) {
			sys_info("�޷����ӷ�����5\n");
			return;
		}

		waiting = 1;
	} else {
		sys_info("�������ӡ�\n");
		socket = socket_create(STREAM, "read_callback", "close_getstock_callback");
		fd=socket_connect( socket, IP_ADDRESS, "read_callback","write_getstock_callback");
        	if( fd == EESUCCESS ) {
        		waiting = 1;
        		return;
        	}  else {
        		sys_info("�޷����ӷ�����3\n");
			return;
		}
	}

}

void read_callback(int f, mixed msg)
{
	par_result(msg);

	waiting = 0;
	if( flag == -1 ) {
		sys_info("���� " + size + " ����Ʊ��Ϣ���� " +sizeof(now_array) + " �����С�\n");
		size = 0;
		return;
	}
	continue_connect();
}

void add_stock(string arg)
{
	if( strlen(arg) != 6 ) return;

	if( arg[0..0] == "0" ) arg = "sz" + arg;
	else if( arg[0..0] == "6" ) arg = "sh" + arg;
	else return;

	if( member_array(arg, now_array) != -1 ) {
		tell_object(this_player(), sprintf("%O\n",stock[arg]));
		return;
	}

	now_array += ({ arg });
}

void del_stock(string arg)
{
	if( strlen(arg) != 6 ) return;

	if( arg[0..0] == "0" ) arg = "sz" + arg;
	else if( arg[0..0] == "6" ) arg = "sh" + arg;
	else return;

	if( member_array(arg, now_array) == -1 )
		return;

	now_array -= ({ arg });
}

void write_getstock_callback(int f)
{
	int fd;

	online = 1;
	fd=socket_write( socket, stockurl());
	if( fd != EESUCCESS ) {
		sys_info("�޷����ӷ�����4\n");
		return;
	}

	waiting = 1;
}

void close_getstock_callback(int f)
{
	online = 0;
	waiting = 0;
	sys_info("�������Ͽ�\n");
}
