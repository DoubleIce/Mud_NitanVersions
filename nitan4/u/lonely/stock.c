// by ephq@YSZZ
#define STOCK_CHECK_OB "/obj/stock/stock_check"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	if( strlen(arg) != 6 ) return notify_fail("��������ȷ�Ĺ�Ʊ����\n");

	if( arg[0..0] == "0" ) arg = "sz" + arg;
	else if( arg[0..0] == "6" ) arg = "sh" + arg;
	else return notify_fail("��������ȷ�Ĺ�Ʊ����\n");

	ob = new(STOCK_CHECK_OB);
//	ob->set("owner",me);
	ob->get_stock(arg,me);
	write("��ʼ��ѯ\n");
	return 1;
}


int help(object me)
{
        write(@HELP
ָ���ʽ��stock <��Ʊ����>              ���磺 stock 600050

HELP
        );
        return 1;
}

