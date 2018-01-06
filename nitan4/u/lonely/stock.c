// by ephq@YSZZ
#define STOCK_CHECK_OB "/obj/stock/stock_check"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	if( strlen(arg) != 6 ) return notify_fail("请输入正确的股票代码\n");

	if( arg[0..0] == "0" ) arg = "sz" + arg;
	else if( arg[0..0] == "6" ) arg = "sh" + arg;
	else return notify_fail("请输入正确的股票代码\n");

	ob = new(STOCK_CHECK_OB);
//	ob->set("owner",me);
	ob->get_stock(arg,me);
	write("开始查询\n");
	return 1;
}


int help(object me)
{
        write(@HELP
指令格式：stock <股票代码>              例如： stock 600050

HELP
        );
        return 1;
}

