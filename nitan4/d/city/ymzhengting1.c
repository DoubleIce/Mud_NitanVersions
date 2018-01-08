#include <ansi.h>
inherit ROOM;
//void kf_same(object who,object me);

void create()
{
        set("short", "衙门正厅");
        set("long", @LONG
    堂上东西有两根楹住，挂着一幅对联，但是你无心细看。正
墙上悬挂一个横匾，上书四个金光闪闪的大字。知府正坐在文案后批
阅文书，师爷随侍在后。大堂正中高悬一匾：[1；31m               明   
 镜    高    悬[2；37；0m
LONG );
        set("valid_startroom",1);
        set("no_steal", "1");
        set("no_magic", "1");
        set("no_fight", "1");
        set("exits", ([
           "east"  : "/d/city/dongting", 
                      "west"  : "/d/city/xiting", 
                      "north" : "/d/city/neizhai", 
                      "south" : "/d/city/yamen", 

        ]));
  

        set("objects", ([
                  "/d/city/npc/cheng" : 1, 
                  "/d/city/npc/shiye" : 1, 
        ]));
        setup();
}

void init ()
{
        add_action("do_work","work");
        add_action("do_finish","finish");
}

int do_work (string arg)
{
        object ob,ob1;
        int kf_npc,kf_whatnpc,worked_num;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        if ((int)me->query("kf_jiangli"))
                return notify_fail("程药发说道：神捕大人还没进京面圣啊？\n");

        if (!(int)me->query("kaifengfu"))
                return notify_fail("两旁衙役大声喝道：大胆刁民，不得咆哮公堂！\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("风云衙役笑道：程药发已经退堂了，要想任务明日请早了您。\n");

        if (present("ling pai",me)||(int)me->query("kf_working"))
                return notify_fail("程药发脸色一沉道：本官前日交与你的差事速去办理，不得捻轻怕重！\n");
        kf_npc = 1 + random(209);
        kf_whatnpc =1+random(8);
        me->set("kf_whatnpc",kf_whatnpc);
        ob = new("/d/city/obj/lingpai");        //50
        if(kf_whatnpc==1){ob1 = new("/d/city/npc/tufei1");}
        if(kf_whatnpc==2){ob1 = new("/d/city/npc/tufei2");}
        if(kf_whatnpc==3){ob1 = new("/d/city/npc/tufei3");}
        if(kf_whatnpc==4){ob1 = new("/d/city/npc/tufei4");}
        if(kf_whatnpc==5){ob1 = new("/d/city/npc/tufei5");}
        if(kf_whatnpc==6){ob1 = new("/d/city/npc/tufei6");}
        if(kf_whatnpc==7){ob1 = new("/d/city/npc/tufei7");}
        if(kf_whatnpc==8){ob1 = new("/d/city/npc/tufei8");}
        ob ->move(me);
        me->set_temp("kf_npc",kf_npc);
        if(kf_npc<210) kf_where = "武当附近";
        if(kf_npc<191) kf_where = "黄山附近";
        if(kf_npc<166) kf_where = "逍遥派附近";
        if(kf_npc<152) kf_where = "星宿派附近";
        if(kf_npc<141) kf_where = "泰山附近";
        if(kf_npc<125) kf_where = "雪山附近";
        if(kf_npc<107) kf_where = "扬州附近";
        if(kf_npc<84) kf_where = "北京城中";
        if(kf_whatnpc==1){ kf_name = "蒙面大盗"; kf_name1 = "拦路抢劫,杀人如麻";}
        if(kf_whatnpc==2){ kf_name = "无影神偷"; kf_name1 = "四处盗窃财物";}
        if(kf_whatnpc==3){ kf_name = "恶人裴风萧"; kf_name1 = "经常劫掠民女，无恶不做";}
        if(kf_whatnpc==4){ kf_name = "魔教细作"; kf_name1 = "四处活动";}
        if(kf_whatnpc==5){ kf_name = "天宗奸细"; kf_name1 = "四处造谣破坏";}
        if(kf_whatnpc==6){ kf_name = "神秘人"; kf_name1 = "刺杀朝廷命官";}
        if(kf_whatnpc==7){ kf_name = "李元奎"; kf_name1 = "大家劫舍";}
        if(kf_whatnpc==8){ kf_name = "古毅"; kf_name1 = "伤人无数";}

        me->set_temp("kf_whatnpc",kf_whatnpc);
        me->set_temp("kf_name",kf_name);
        me->set_temp("kf_where",kf_where);
        message_vision ("程药发一拍惊堂木怒道：据查今有"+kf_name+"在"+kf_where+kf_name1+"，"+me->query("name")+"速去破案，不得有误。\n",me);
        me->set("kf_working",1);
        return 1;
}
int do_finish (string arg)
{
        object ob;
        int kf_npc,kf_whatnpc,kf_exp,kf_qn;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        ob= present("ling pai",me);
        kf_name = me->query_temp("kf_name");
        kf_where = me->query_temp("kf_where");
        
        if (!(int)me->query("kaifengfu"))
                return notify_fail("两旁的风云衙役大声喝道：大胆刁民，不得咆哮公堂！\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("风云衙役笑道：程大人已经退堂了，要想交令明日请早了您。\n");
        if (!me->query("kf_working"))
                return notify_fail("程药发脸色一沉道：本官什么时候派过你差事啊？\n");
        if (!(int)me->query_temp("kf_finish"))
                return notify_fail("程药发脸色一沉道：本府交你的差使至今还未办妥，你还有面目来见我？\n");
        if (present("ling pai",me)){
                tell_object(me, "你恭恭敬敬的缴上令牌。\n" NOR );
        destruct(present("ling pai",me));
        }        
        message_vision (WHT"程药发微微一笑道："+me->query("name")+WHT"在"+kf_where+WHT"破获"+kf_name+WHT"一案，劳苦功高，赶快下去休息吧！\n"NOR,me);
        kf_exp = 2000+random(2000);
        kf_qn = 500+random(500);
        me->add("combat_exp",kf_exp);
        me->add("kf_worked",1);
        me->add("potential",kf_qn);
        me->add("kf_worked",1);
        me->set("kf_working",0);
        me->delete_temp("kf_finish");
        tell_object(me, "你获得了" + chinese_number(kf_exp)+ "点经验。\n" NOR );
        tell_object(me, "你获得了" + chinese_number(kf_qn)+ "点潜能。\n" NOR );
        if (me->query("kf_worked")==4800){
                me->set("kainame",10);
                me->add("shen",3000);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
                message_vision (WHT"程药发微笑着说道："+me->query("name")+"连破大案，天下闻名，本府已经奏明皇上。\n昨日朝旨已下，奖你黄金五千两。你可以到钱庄领取。"NOR,me);
                 me->add("balance",10000000);
               me->set("kf_jiangli",1);

      }
        if (me->query("kf_worked")==3200){
                me->add("shen",3000);
                me->set("kainame",9);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
                message_vision (WHT"程药发微笑着说道："+me->query("name")+"连破大案，天下闻名,继续加油！！"NOR,me);
      }
        if (me->query("kf_worked")==1600){
                me->set("kainame",8);
                me->add("shen",1500);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
      }
        if (me->query("kf_worked")==800){
                me->set("kainame",7);
                me->add("shen",1000);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
        }
        if (me->query("kf_worked")==400){
                me->set("kainame",6);
                me->add("shen",800);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
        }
        if (me->query("kf_worked")==200){
                me->set("kainame",5);
                me->add("shen",400);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
        }
        if (me->query("kf_worked")==100){
                me->set("kainame",4);
                me->add("shen",200);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
        }
        if (me->query("kf_worked")==50){
                me->set("kainame",3);
                me->add("shen",100);
                message_vision(HIC "$N的正气提高了！\n" NOR,me);
                tell_object(me, "你现在的正气是" + chinese_number((string)(me->query("shen")))+"。\n"NOR);
        }
        if (me->query("kf_worked")==20){
                me->set("kainame",2);
        }
        me->save();
        return 1;
}
int valid_leave (object who, string dir)
{
        if(who->query_condition("kf_stop")<1){
                return ::valid_leave(who, dir);
        }
        else{
                message_vision ("$N爬起来就想往外跑。\n",who);
                return notify_fail(WHT"衙役死死把你按在地上喝道：老实点！\n"NOR);
                return 1;
}
}

