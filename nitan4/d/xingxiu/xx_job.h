// Code of ShenZhou
void dest_bug(object bug);
void setup_npc(object me, object ob);

void init()
{
        add_action("do_search", "search");
	add_action("do_search", "zhao");
}	

int do_search(string arg) {
		

	string* n= ({
		"/d/xingxiu/forest10",
        	"/d/xingxiu/forest2",
        	"/d/xingxiu/forest3",
        	"/d/xingxiu/forest11",
        	"/d/xingxiu/forest4",
        	"/d/xingxiu/forest5",
        	"/d/xingxiu/forest1",
        	"/d/xingxiu/forest12",
        	"/d/xingxiu/forest6",
        	"/d/xingxiu/forest7",
        	"/d/xingxiu/forest8",
        	"/d/xingxiu/forest9",
        });

	object bug, me, fighter, room, gold, ob;

	int kar1, kar2, kar3, pot, max_pot, damage, find;	

	me=this_player();

	if( !arg || arg=="" ) return 0;
	
	if( arg=="bug" || arg=="chong"){

		if (!present("wa guan", me))
                        return notify_fail("你找到虫子用什么来盛呢？\n\n");
                        
               if (me->query("max_jingli")<100)
                       return notify_fail("你的最大精力太少了。\n\n");
                if (me->query("jingli")<me->query("max_jingli")/5)
                        return notify_fail("你先休息一下吧。\n\n");
                        
		if (me->is_busy()) return
                        notify_fail("你上一个动作还没有完成。\n"); 
                        
		if (me->is_fighting()) return
                        notify_fail("您先吧敌人料理了在说吧。:)\n");
                        
		if (me->query_temp("found")==1) return
                        notify_fail("你最好先回去复命，别让老仙等急了。\n");
                                       
                //if (me->query_temp("bug_out")==1)
                //        return notify_fail("毒虫已经出来了，赶快抓吧！\n");
                
                if (me->query_temp("xx_job")!=1)
                        return notify_fail("找来有什么用？\n");
                
		me->add("jingli",-10);
		me->add("jing",-10);
		me->start_busy(random(1)+1);
		
		me->add("find_bug",1);
		me->add_temp("xx/find",1);

                message_vision("$N弯下了腰，伸手将残枝败叶拨开，仔细寻找毒虫的踪迹。\n",me);
		
		kar2=(me->query("int")+me->query("con")+me->query("str"))*(random(2)+1);
		kar1=me->query("kar");		

		if (me->query("find_bug")>random(20)) {
			me->set("find_bug",0);
                                
			room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N又找了找，发现没有丝毫毒虫的踪迹，只好离开这里，到别的地方寻找。\n",me);
			message_vision("$N急急忙忙地离开了。\n",me);
			me->move(room);
			message_vision("$N走了过来。\n",me);			
			return 1;
		}
		
		kar3=random(kar1*3);
		find=me->query_temp("xx/find");
		
		if (wizardp(me)) {
				printf("my kar=%d  kar=%d  randkar=%d  time: %d\n", kar1, kar3, kar2, find);
		}
		
		if ((kar3>kar2 && find>10) || (find>=30)) {

                        message_vision(HIG"突然间一只小虫子钻了出来，迅速地爬动着。\n"NOR, me);
                        bug=new("/d/xingxiu/npc/duchong");
			bug->move(environment(me));
			bug->set("playerid",me->query("id"));
                        me->set_temp("bug_out",1);
			me->set_temp("xx/find", 0);
			
			if (wizardp(me)) {
				printf("player id: %s \n", bug->query("playerid"));
			}
						
			return 1;
			
 		}
		
                   if (random(50)<=3 && count_ge(me->query("combat_exp"), 150000) && me->query_temp("xx_job")) { 

                        message_vision(HIR"突然间从树后越出一个人，高喊一声：“星宿奸人，拿命来！”\n"NOR,me);
                     fighter = new(CLASS_D("generate") + "/xxnpc.c");
                     NPC_D->set_from_me(fighter, me, 110 + random(20));
                     fighter->add_temp("apply/attack", fighter->query_skill("force") *
					     1/ 15);
                     fighter->add_temp("apply/dodge", fighter->query_skill("force") *
					     1/ 15);
                     fighter->add_temp("apply/parry", fighter->query_skill("force") *
					     1/ 15);
                     fighter->add_temp("apply/damage", 5 + 1 * 7);
                     fighter->add_temp("apply/unarmed_damage", 5 + 1 * 7);
                     fighter->add_temp("apply/armor", 10 + 1 * 15);
			fighter->set("player",me->query("id"));
			fighter->move(environment(me));
			fighter->kill_ob(me);
			//fighter->set_busy(random(2));			
			return 1;
		}
		
		
		if (random(kar1*3)<1){
			message_vision(HIW"$N眼前银光一闪，哇，银子！\n"NOR,me);
			gold=new("/clone/money/silver");
			gold->move(environment(me));
			return 1;
		}
		
		if (random(kar1*2)<1){
			message_vision(YEL"$N眼前铜光一闪，哇，铜钱 :(\n"NOR,me);
			gold=new("/clone/money/coin");
			gold->move(environment(me));
			return 1;
		}
		
		if (random(kar1*4)<1){
			message_vision(HIY"$N眼前金光一闪，哇，金子！\n"NOR,me);
			message_vision(HIR"$N看见金子，心中一得意，手中瓦罐掉到地上打的粉碎。\n"NOR,me);
			gold=new("/clone/money/gold");
			gold->move(environment(me));
			ob = present("wa guan", me);
                        if(ob)destruct(ob);
                        me->delete_temp("xx_job");
			return 1;
		}
		
		if (random(20)<1){
			message_vision(MAG"\n$N哎呀一声，被地上的石头绊了一交。\n"NOR,me);
			me->start_busy(random(3)+2);
			damage=me->query_skill("force",1);
			me->receive_wound("qi", random(damage/10));
		}

                
		
        return 1;        
	} else if(arg=="dochong"){
		
		me->set_temp("fresh",1);
		message_vision("$N弯下了腰，伸手将残枝败叶拨开，仔细寻找毒虫的踪迹。\n",me);
		
		if (me->query("find_bug")>random(20)) {
			me->set("find_bug",0);
                                
			room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N又找了找，发现没有丝毫毒虫的踪迹，只好离开这里，到别的地方寻找。\n",me);
			message_vision("$N急急忙忙地离开了。\n",me);
			me->move(room);
			message_vision("$N走了过来。\n",me);			
			return 1;
		}
		
		
		return 1;
	}	
	
}
