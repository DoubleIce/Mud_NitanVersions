int do_rideht()
{
	string hname;
	object ob = this_player();
	int i;
	string *bj_gw=({
                HIC"����"NOR,
                HIC"����"NOR,
                HIC"����"NOR,
                HIC"��������"NOR,
                HIC"�������㳡"NOR,
                HIC"�찲�Ź㳡"NOR,
                HIC"�������㳡"NOR,
                HIC"��������"NOR,
                HIC"���������"NOR,
                HIC"���������"NOR,
                HIC"���������"NOR,
                HIC"������"NOR,
                HIC"������"NOR,
                HIC"������"NOR,
                HIC"�����"NOR,
                HIC"�����"NOR,
                HIC"�����"NOR,
                HIC"����ͷ"NOR,
                HIC"ɽ����"NOR,
                HIC"�ٵ�"NOR,
                HIC"�ٵ�"NOR,
                HIC"�ٵ�"NOR,
                HIC"��Զ"NOR,
                HIC"���"NOR,
                HIC"���"NOR,
                HIC"���"NOR,
                HIC"���"NOR,
                HIC"���"NOR,
                HIC"ľ��"NOR,
                HIC"�ϳ�"NOR,
                HIC"����"NOR,
	});
	if (ob->query_temp("marks/horserent")!=1 && ob->query("age")>14)
                return notify_fail("С���Ӳſ��������������Ҫ��Ǯ��\n");
	switch (random(3))
	{
		case 1:
			hname=MAG"������"NOR;
			break;
		case 2:
			hname=RED"�����"NOR;
			break;
		default:
			hname=HIY"������"NOR;
			break;
	}
	message_vision(
"�������ָ�$Nǣ��һƥ"+hname+"��$N����Ծ����������������������·������һ��
���: �����ޡ�\n"NOR , ob );
	message_vision("\nֻ��$N������һ�У�"+hname+"�����͵��ȥ��\n",ob);
	for (i = 0; i < sizeof(bj_gw);i++)
		tell_object(ob,bj_gw[i] + "\n");
	ob->move("/d/guanwai/majiu");
	tell_room(environment(ob),ob->query("name")+"����"+hname+"һ·˳�������ͼ������\n");
	message_vision("\n$N����һת��Ծ����������̬ʮ������������Ҳ��$Nһ��� !\n" ,ob);
	ob->delete_temp("marks/horserent");
	return 1;
}