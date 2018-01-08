#include <ansi.h>
inherit ROOM;
   

void create ()
{
        set("short", "¸ß²ý´óÃÅ");
        set("long", @LONG
Äã×ª¹ýÁËÒ»ÅÅÊ÷Ä¾£¬À´µ½ÕâÀï¡£Ö»¼ûÒ»×ùÊ¯É½ÉÏÇ¶ÖøÁ½ÉÈÌúÖýµÄ
´óÃÅ¡£Á½ÉÈ´óÃÅ¿´Ñù×ÓÖØÓâÇ§¾û£¬¾ÝËµÊÇ¹Å´ú¸ß²ý¹úÍõÎªÁËµÖÓùÇ¿µÐ
¶øÉè¼ÆµÄ¡£ÌúÃÅÉÏÌúÐâ°ß²µ£¬ÏÔÊÇÀúÊ±ÒÑ¾ÃµÄ¾ÉÎï¡£µ«ÊÇÃÅÉÏµÄÃÅ»·
(huan)¡£ÌúÃÅÉÏÐ´×Å£º        [37m¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù
¡ù¡ù¡ù        ¡ù                                  ¡ù        
¡ù     [2£»37£»0m[1£»31m¸ß     ²ý      ´ó     µî[2£»37£»0m[37m     ¡ù        ¡ù            
                      ¡ù        ¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù
¡ù¡ù¡ù¡ù¡ù[2£»37£»0m
LONG );

        set("outdoors", "gaochang");
        set("exits", ([
                "southdown" : __DIR__"shijie3",
        ]));
        set("item_desc", ([
                "huan" : HIY "\nÒ»Ö»Ðâ¼£°ß°ßµÄ½ðÊôÃÅ»·£¬¿´Ñù×ÓËÆºõ¿ÉÒÔÅ¤(turn)¶¯¡£\n" NOR,
        ]) );
        setup();
}

void init()
{
        add_action("do_turn", "turn");
}

void check_trigger()
{
   	object room;
   	object me = this_player();
        int exp, pot, sc;

        exp = 500 + random(1000);
        pot = random(300);
        sc = random(10);

	if ((int)query("left_trigger") == 2 &&
           (int)query("right_trigger") == 5 &&
           ! query("exits/down"))
	{
     		message("vision", WHT "\nºöÈ»¼ä£¬Ö»ÌýÌúÃÅ·¢³öÔþÔþµÄÉùÒô£¬Â¶³öÒ»¸öÏòÏÂµÄ½×"
                                  "ÌÝ¡£\n" NOR, this_object());

		if (! (room = find_object(__DIR__"dadian")))
		room = load_object(__DIR__"dadian");

	     	if (room = find_object(__DIR__"dadian"))
		{
			set("exits/down", __DIR__"dadian");
		        room->set("exits/up", __FILE__);
                	message("vision", HIY "ºöÈ»¼ä£¬Ö»ÌýÌúÃÅ·¢³öÔþÔþµÄÉùÒô£¬Â¶³öÒ»¸öÏò"
                                          "ÉÏµÄ½×ÌÝ¡£\n" NOR, room);

			if (! (int)me->query("skybook/baima/enter"))
			{
                		me->add("combat_exp", exp);
                		me->add("potential", pot);
                		me->add("score", sc);
                		tell_object(me, HIW "\nÄã³É¹¦µÄ¿ªÆôÁË¸ß²ýÃÔ¹¬Èë¿Ú£¡\n" NOR + HIC "Í¨"
                                                "¹ýÕâ´ÎµÄÀúÁ·£¬Äã»ñµÃÁË" + chinese_number(exp) + "µã"
                                                "¾­Ñé¡¢" + chinese_number(pot) + "µãÇ±ÄÜÒÔ¼°" +
                                                 chinese_number(sc) + "µã½­ºþÔÄÀú¡£\n\n" NOR);
                                me->set("skybook/baima/enter", 1);
			}
     		}
     		delete("left_trigger");
     		delete("right_trigger");
     		call_out("close_passage", 10);
   	}
}

void close_passage()
{
   	object room;

   	if (! query("exits/down")) return;
   	message("vision", WHT "ÌúÃÅºöÈ»·¢³öÔþÔþµÄÉùÒô£¬½«ÏòÏÂµÄÍ¨µÀ¸Ç"
                          "×¡ÁË¡£\n" NOR, this_object() );
   	if (room = find_object(__DIR__"dadian"))
	{
     		room->delete("exits/up");
     		message("vision", WHT "ÌúÃÅºöÈ»·¢³öÔþÔþµÄÉùÒô£¬ÏòÉÏµÄ"
                                  "Í¨µÀÓÖ»º»ºµØ±»¸Ç×¡ÁË¡£\n" NOR, room);
   	}
   	delete("exits/down");
	delete("left_trigger");
	delete("right_trigger");
}


int do_turn(string arg)
{
   	string dir;
   	object me = this_player();

   	if (! arg || arg == "" ) return 0;

   	if (arg == "huan")
	{
	        if (me->query("max_neili") < 300)
		{
     			write(HIC "\nÄãÊ¹×ã¾¢Å¤¶¯ÃÅ»·£¬¿ÉÊÇÃÅ»·»¹ÊÇÎÆË¿²»¶¯¡£\n" NOR);
     			return 1;
		} else
		{
   	  		write(HIC "\nÄãÊÔ×ÅÅ¤¶¯ÃÅ»·£¬·¢ÏÖÃÅ»·ËÆºõ¿ÉÒÔ×óÓÒ»¬¶¯¡£\n" NOR);
			delete("left_trigger");
			delete("right_trigger");
	     		return 1;
		}
   	}

   	if (sscanf(arg, "huan %s", dir) == 1)
	{
	        if (me->query("max_neili") < 300)
		{
     			write(HIC "\nÄãÊ¹×ã¾¢Å¤¶¯ÃÅ»·£¬¿ÉÊÇÃÅ»·»¹ÊÇÎÆË¿²»¶¯¡£\n" NOR);
     			return 1;
		} else
     		if (dir == "right" )
		{
			if (query("exits/down"))
				return notify_fail("ÌúÃÅÒÑ¾­±»Å¤¿ªÁË¡£\n");

	        	message_vision(HIY "$N" HIY "½«ÃÅ»·ÍùÓÒÅ¤¡­¡­ºöÈ»¡¸¿¦¡¹Ò»ÉùÌú"
                                       "ÃÅÓÖÒÆ»ØÔ­Î»¡£\n" NOR, me);
        		add("right_trigger", 1);
        		check_trigger();
        		return 1;
     		} else
		if (dir == "left")
		{
			if (query("exits/down")) return notify_fail("ÌúÃÅÒÑ¾­±»Å¤¿ªÁË¡£\n");
        		message_vision(HIY "$N" HIY "½«ÃÅ»·Íù×óÅ¤¡­¡­ºöÈ»¡¸¿¦¡¹Ò»ÉùÌú"
                                       "ÃÅÓÖÒÆ»ØÔ­Î»¡£\n" NOR, me);
        		add("left_trigger", 1);
        		check_trigger();
        		return 1;
     		} else
		{
        		write("ÄãÒª½«ÃÅ»·ÍùÄÄ±ßÅ¤£¿\n");
        		return 1;
     		}
   	}
}


void reset()
{
   	::reset();
   	delete("left_trigger");
   	delete("right_trigger");
}
