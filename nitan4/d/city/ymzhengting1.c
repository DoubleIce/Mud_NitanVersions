#include <ansi.h>
inherit ROOM;
//void kf_same(object who,object me);

void create()
{
        set("short", "ÑÃÃÅÕýÌü");
        set("long", @LONG
    ÌÃÉÏ¶«Î÷ÓÐÁ½¸ùéº×¡£¬¹Ò×ÅÒ»·ù¶ÔÁª£¬µ«ÊÇÄãÎÞÐÄÏ¸¿´¡£Õý
Ç½ÉÏÐü¹ÒÒ»¸öºáØÒ£¬ÉÏÊéËÄ¸ö½ð¹âÉÁÉÁµÄ´ó×Ö¡£Öª¸®Õý×øÔÚÎÄ°¸ºóÅú
ÔÄÎÄÊé£¬Ê¦Ò¯ËæÊÌÔÚºó¡£´óÌÃÕýÖÐ¸ßÐüÒ»ØÒ£º[1£»31m               Ã÷   
 ¾µ    ¸ß    Ðü[2£»37£»0m
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
                return notify_fail("³ÌÒ©·¢ËµµÀ£ºÉñ²¶´óÈË»¹Ã»½ø¾©ÃæÊ¥°¡£¿\n");

        if (!(int)me->query("kaifengfu"))
                return notify_fail("Á½ÅÔÑÃÒÛ´óÉùºÈµÀ£º´óµ¨µóÃñ£¬²»µÃÅØÏø¹«ÌÃ£¡\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("·çÔÆÑÃÒÛÐ¦µÀ£º³ÌÒ©·¢ÒÑ¾­ÍËÌÃÁË£¬ÒªÏëÈÎÎñÃ÷ÈÕÇëÔçÁËÄú¡£\n");

        if (present("ling pai",me)||(int)me->query("kf_working"))
                return notify_fail("³ÌÒ©·¢Á³É«Ò»³ÁµÀ£º±¾¹ÙÇ°ÈÕ½»ÓëÄãµÄ²îÊÂËÙÈ¥°ìÀí£¬²»µÃÄíÇáÅÂÖØ£¡\n");
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
        if(kf_npc<210) kf_where = "Îäµ±¸½½ü";
        if(kf_npc<191) kf_where = "»ÆÉ½¸½½ü";
        if(kf_npc<166) kf_where = "åÐÒ£ÅÉ¸½½ü";
        if(kf_npc<152) kf_where = "ÐÇËÞÅÉ¸½½ü";
        if(kf_npc<141) kf_where = "Ì©É½¸½½ü";
        if(kf_npc<125) kf_where = "Ñ©É½¸½½ü";
        if(kf_npc<107) kf_where = "ÑïÖÝ¸½½ü";
        if(kf_npc<84) kf_where = "±±¾©³ÇÖÐ";
        if(kf_whatnpc==1){ kf_name = "ÃÉÃæ´óµÁ"; kf_name1 = "À¹Â·ÇÀ½Ù,É±ÈËÈçÂé";}
        if(kf_whatnpc==2){ kf_name = "ÎÞÓ°ÉñÍµ"; kf_name1 = "ËÄ´¦µÁÇÔ²ÆÎï";}
        if(kf_whatnpc==3){ kf_name = "¶ñÈËÅá·çÏô"; kf_name1 = "¾­³£½ÙÂÓÃñÅ®£¬ÎÞ¶ñ²»×ö";}
        if(kf_whatnpc==4){ kf_name = "Ä§½ÌÏ¸×÷"; kf_name1 = "ËÄ´¦»î¶¯";}
        if(kf_whatnpc==5){ kf_name = "Ìì×Ú¼éÏ¸"; kf_name1 = "ËÄ´¦ÔìÒ¥ÆÆ»µ";}
        if(kf_whatnpc==6){ kf_name = "ÉñÃØÈË"; kf_name1 = "´ÌÉ±³¯Í¢Ãü¹Ù";}
        if(kf_whatnpc==7){ kf_name = "ÀîÔª¿ü"; kf_name1 = "´ó¼Ò½ÙÉá";}
        if(kf_whatnpc==8){ kf_name = "¹ÅÒã"; kf_name1 = "ÉËÈËÎÞÊý";}

        me->set_temp("kf_whatnpc",kf_whatnpc);
        me->set_temp("kf_name",kf_name);
        me->set_temp("kf_where",kf_where);
        message_vision ("³ÌÒ©·¢Ò»ÅÄ¾ªÌÃÄ¾Å­µÀ£º¾Ý²é½ñÓÐ"+kf_name+"ÔÚ"+kf_where+kf_name1+"£¬"+me->query("name")+"ËÙÈ¥ÆÆ°¸£¬²»µÃÓÐÎó¡£\n",me);
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
                return notify_fail("Á½ÅÔµÄ·çÔÆÑÃÒÛ´óÉùºÈµÀ£º´óµ¨µóÃñ£¬²»µÃÅØÏø¹«ÌÃ£¡\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("·çÔÆÑÃÒÛÐ¦µÀ£º³Ì´óÈËÒÑ¾­ÍËÌÃÁË£¬ÒªÏë½»ÁîÃ÷ÈÕÇëÔçÁËÄú¡£\n");
        if (!me->query("kf_working"))
                return notify_fail("³ÌÒ©·¢Á³É«Ò»³ÁµÀ£º±¾¹ÙÊ²Ã´Ê±ºòÅÉ¹ýÄã²îÊÂ°¡£¿\n");
        if (!(int)me->query_temp("kf_finish"))
                return notify_fail("³ÌÒ©·¢Á³É«Ò»³ÁµÀ£º±¾¸®½»ÄãµÄ²îÊ¹ÖÁ½ñ»¹Î´°ìÍ×£¬Äã»¹ÓÐÃæÄ¿À´¼ûÎÒ£¿\n");
        if (present("ling pai",me)){
                tell_object(me, "Äã¹§¹§¾´¾´µÄ½ÉÉÏÁîÅÆ¡£\n" NOR );
        destruct(present("ling pai",me));
        }        
        message_vision (WHT"³ÌÒ©·¢Î¢Î¢Ò»Ð¦µÀ£º"+me->query("name")+WHT"ÔÚ"+kf_where+WHT"ÆÆ»ñ"+kf_name+WHT"Ò»°¸£¬ÀÍ¿à¹¦¸ß£¬¸Ï¿ìÏÂÈ¥ÐÝÏ¢°É£¡\n"NOR,me);
        kf_exp = 2000+random(2000);
        kf_qn = 500+random(500);
        me->add("combat_exp",kf_exp);
        me->add("kf_worked",1);
        me->add("potential",kf_qn);
        me->add("kf_worked",1);
        me->set("kf_working",0);
        me->delete_temp("kf_finish");
        tell_object(me, "Äã»ñµÃÁË" + chinese_number(kf_exp)+ "µã¾­Ñé¡£\n" NOR );
        tell_object(me, "Äã»ñµÃÁË" + chinese_number(kf_qn)+ "µãÇ±ÄÜ¡£\n" NOR );
        if (me->query("kf_worked")==4800){
                me->set("kainame",10);
                me->add("shen",3000);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
                message_vision (WHT"³ÌÒ©·¢Î¢Ð¦×ÅËµµÀ£º"+me->query("name")+"Á¬ÆÆ´ó°¸£¬ÌìÏÂÎÅÃû£¬±¾¸®ÒÑ¾­×àÃ÷»ÊÉÏ¡£\n×òÈÕ³¯Ö¼ÒÑÏÂ£¬½±Äã»Æ½ðÎåÇ§Á½¡£Äã¿ÉÒÔµ½Ç®×¯ÁìÈ¡¡£"NOR,me);
                 me->add("balance",10000000);
               me->set("kf_jiangli",1);

      }
        if (me->query("kf_worked")==3200){
                me->add("shen",3000);
                me->set("kainame",9);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
                message_vision (WHT"³ÌÒ©·¢Î¢Ð¦×ÅËµµÀ£º"+me->query("name")+"Á¬ÆÆ´ó°¸£¬ÌìÏÂÎÅÃû,¼ÌÐø¼ÓÓÍ£¡£¡"NOR,me);
      }
        if (me->query("kf_worked")==1600){
                me->set("kainame",8);
                me->add("shen",1500);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
      }
        if (me->query("kf_worked")==800){
                me->set("kainame",7);
                me->add("shen",1000);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
        }
        if (me->query("kf_worked")==400){
                me->set("kainame",6);
                me->add("shen",800);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
        }
        if (me->query("kf_worked")==200){
                me->set("kainame",5);
                me->add("shen",400);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
        }
        if (me->query("kf_worked")==100){
                me->set("kainame",4);
                me->add("shen",200);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
        }
        if (me->query("kf_worked")==50){
                me->set("kainame",3);
                me->add("shen",100);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me, "ÄãÏÖÔÚµÄÕýÆøÊÇ" + chinese_number((string)(me->query("shen")))+"¡£\n"NOR);
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
                message_vision ("$NÅÀÆðÀ´¾ÍÏëÍùÍâÅÜ¡£\n",who);
                return notify_fail(WHT"ÑÃÒÛËÀËÀ°ÑÄã°´ÔÚµØÉÏºÈµÀ£ºÀÏÊµµã£¡\n"NOR);
                return 1;
}
}

