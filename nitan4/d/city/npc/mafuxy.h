int do_ridexy()
{
        string hname;
        object ob = this_player();
	int i;
	string *yz_xy = ({
                HIC"客店"NOR,
                HIC"北大街"NOR,
                HIC"中央广场"NOR,
                HIC"西大街"NOR,
                HIC"西大街"NOR,
                HIC"西门"NOR,
                HIC"西门大道"NOR,
                HIC"关洛道"NOR,
                HIC"函谷关"NOR,
                HIC"草地"NOR,
                HIC"玄武外门"NOR,
                HIC"玄武内门"NOR,
                HIC"北大街"NOR,
                HIC"丁字街口"NOR,
                HIC"北内大街"NOR,
	});
        if (ob->query_temp("marks/horserent")!=1 && ob->query("age")>14)
                return notify_fail("小孩子才可以免费坐马！你要交钱！\n");
        switch (random(3))
        {
                case 1:
                        hname=MAG"紫骝马"NOR;
                        break;
                case 2:
                        hname=RED"枣红马"NOR;
                        break;
                default:
                        hname=HIY"黄骠马"NOR;
                        break;
        }
        message_vision(
"马夫随手给$N牵来一匹"+hname+"。$N翻身跃上马背。动作潇洒利索。路边行人一阵
起哄: 喔噢喔噢。\n"NOR , ob );
        message_vision("\n只见$N骑两腿一夹，"+hname+"穿过客店而去。\n",ob);
	for (i = 0;i < sizeof(yz_xy);i ++)
		tell_object(ob,yz_xy[i] + "\n");
        ob->move("/d/xiangyang/majiu");
        tell_room(environment(ob),ob->query("name")+"骑着"+hname+"一路顺利到达襄阳城。\n");
        message_vision("\n$N身形一转，跃下马来，姿态十分优美。闲人也给$N一大哄。\n",ob);
        ob->delete_temp("marks/horserent");
        return 1;
}
