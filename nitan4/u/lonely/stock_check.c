#include <net/socket_errors.h>
#include <net/config.h>
#include <net/daemons.h>
#include <localtime.h>
#include <net/dns.h>
#include <net/socket.h>
#include <net/services.h>
#include <net/macros.h>
#include <ansi.h>

inherit ITEM;

int socket, flag;
string stock_code;
string *stock_data = allocate(32);
string *stock_data_sum = allocate(6);
object owner;

varargs void time_out(string arg);
varargs void get_stock(string arg, object ob, int f);

string stockurl()
{ 
	return sprintf("GET /list=%s,s_%s HTTP/1.1\nPragma: No-Cache\nHost: hq.sinajs.cn\n\n",
		stock_code, stock_code);
}


void create()
{
	if( clonep(this_object()) ) call_out("time_out",10);
}

void get_result()
{
	int up = 0;
	string msg;


	if( !stock_code || !stock_data[0] || !stock_data_sum[0] ) {
		time_out("5");
		return;
	}

	if( stock_data_sum[3][0..0] == "-" ) up = -1;
	else up = 1;

	if( to_int(to_float(stock_data_sum[3]) * 100 ) == 0 ) up = 0;

	msg = sprintf(WHT "���������ש����������������ש�������������������������������������������\n"
		HIK "%8s" NOR WHT "��%|16s��������:"HIK"%6s" NOR WHT " ��߼�:%6s " NOR WHT "�ɽ���:"HIK"%-10s \n"
		"%8s" NOR WHT "��%|7s  %|7s������:%6s" NOR WHT " ��ͼ�:%6s " NOR WHT "�ɽ���:"HIK"%-10s\n"NOR
		WHT "���������ߩ����������������ߩ�������������������������������������������\n" NOR "%s������%s %s\n"NOR,
		stock_data[0],
		(up==1?HIR:(up==-1?HIG:WHT)) + stock_data[3] + (up==1?"��" NOR WHT :(up==-1?"��" NOR  WHT:"--" NOR WHT)),
		stock_data[2],
		((to_float(stock_data[4]) > to_float(stock_data[2]))? HIR : ((to_float(stock_data[4]) < to_float(stock_data[2]))?HIG:WHT)) + stock_data[4],
		stock_data_sum[4],
		HIK + stock_code,
		(up==1?HIR:(up==-1?HIG:WHT)) + stock_data_sum[2],
		stock_data_sum[3]+"%" NOR WHT,
		((to_float(stock_data[1]) > to_float(stock_data[2]))? HIR : ((to_float(stock_data[1]) < to_float(stock_data[2]))?HIG:WHT)) + stock_data[1],
		((to_float(stock_data[5]) > to_float(stock_data[2]))? HIR : ((to_float(stock_data[5]) < to_float(stock_data[2]))?HIG:WHT)) +stock_data[5],
		stock_data_sum[5],
		(up==1?HIR:(up==-1?HIG:WHT)),
		stock_data[30],
		stock_data[31]
		);

	tell_object(owner, msg);
	if( flag ) {
		owner->set_temp("stock/price", stock_data[3]);
		owner->set_temp("stock/code", stock_code);
		owner->force_me("buystock prepare step");
	}
	remove_call_out("time_out");
	destruct(this_object());
}

void read_callback(int f, mixed msg)
{
	string stockstr, stockstr_sum;

	tell_object(owner, msg);
	if ( sscanf(msg,"%*svar hq_str_%s=\"%s\";\nvar hq_str_s_%s=\"%s\";\n",stock_code, stockstr, stock_code, stockstr_sum) == 5 ) {
		stock_data = explode(stockstr,",");
		stock_data_sum = explode(stockstr_sum,",");
		socket_close(socket);
		get_result();
	} else time_out("4");
}

varargs void get_stock(string arg, object ob, int f)
{
	owner = ob;
	stock_code = arg;
	flag = f;

	socket = socket_create(STREAM, "read_callback","close_getstock_callback");
	if( socket < 0 || socket_connect( socket, "60.28.2.64 80","read_callback","write_getstock_callback") != EESUCCESS )
		time_out("1");
}

void write_getstock_callback(int f)
{
	if( socket_write( socket, stockurl()) !=EESUCCESS ) time_out("2");
}

void close_getstock_callback(int f)
{
        time_out("3");
}

varargs void time_out(string arg)
{
	remove_call_out("time_out");
	socket_close(socket);
	tell_object(owner,"�޷���ȡ��Ʊ��Ϣ�����Ժ����ԡ�" + arg + "\n");
	destruct(this_object());
}