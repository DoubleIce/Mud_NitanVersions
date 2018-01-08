#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_tiao(string arg);

void create()
{
        set("short", "Ë®Á±¶´Íâ");
        set("long", @LONG
Ë®Á±¶´ÔÚ×Ï¸Ç·åÏÂ£¬×Ï¸Ç·åÖ®Ë®¾­¹ıÉ½½§»ãÈë×Ï¸ÇÏÉ¶´Ö®ÖĞ£¬Éî
²»¿É²â£¬Ë®ÂúÔòÒç£¬·ÉÆÙ(pubu)¸ß¶şÊ®ÓàÕÉ£¬Êıµş´¹Á±£¬Æ®Ğ¹¶øÏÂ£¬
ÎµÎª×³¹Û¡£Ã÷ÕÅ¾ÓÕıÊ«Ô»¡¸[1£»37mÎóÒÉå­º£·­Çí²¨£¬ÄªÄâÒøºÓµ¹±ÌÁ÷£¬×ÔÊÇ
ÏæåúÉîÒş´¦£¬Ë®¾§Á±¹ÒÎåÔÆÍ·¡£[2£»37£»0m¡¹ÒÔÔŞÌ¾ÕâºâÉ½´óËÄ¾øÖ®Ò»µÄ Ë®Á±¶´
Ö®Ææ ¡£
LONG );
        set("exits", ([ 
               "westdown"    : __DIR__"shanlu12",
	       "northeast"   : __DIR__"shanlu15",	
        ]));

        set("no_clean_up", 0);

        set("outdoors", "henshan");

        set("item_desc",([
	        "pubu" : HIG "\nÖ»¼ûÆÙ²¼·ÉĞº¶øÏÂ£¬ÆøÊÆ°õíç£¬¾°ÖÂ×³¹Û£¬ÏÂÃæÈ´"
                         "ÊÇÍòÕÉÉîÔ¨£¬\nÒ»ÍûÎŞµ×£¬Ë®Á«¶´È´Æ«Æ«ÉúÆÙ²¼Ö®ºó¡£\n\n" NOR,
	]));

        set("coor/x", 20);
	set("coor/y", 10);
	set("coor/z", 20);
	setup();
}


void init()
{
        add_action("do_tiao", ({"tiao", "jump"}));
}

int do_tiao(string arg)
{
        string msg;
        object obj, me = this_player();
        int skill_dodge;

        skill_dodge = me->query_skill("dodge", 1);

        if (! obj = find_object(__DIR__"inhole")) 
		obj = load_object(__DIR__"inhole");
            
        if (! arg || (arg != "pubu" && arg != "ÆÙ²¼"))
        {	
        	write("ÄãÏëÍùÄÄ¶ùÌø£¿\n");
        	return 1;
        }	

        if (skill_dodge < 60)
        {	
        	message_vision(HIC "\n$N" HIC "Ê¹¾¢ÏòÇ°Ò»Ô¾£¬ÑÛ¼ûÒªµ½¶´¿Ú£¬µ«$N"
                               HIC "¸Ğ¾õÆøÁ¦ÒÑ¾¡£¬ÉíÔÚ°ë\n¿ÕÈ´±»ÆÙ²¼³åÁËÏÂÈ¥¡£\n\n"
                               NOR, me);

         	tell_object(me, HIW "ÄãÃÔÃÔºıºıµØÈÎÍÄ¼±µÄË®Á÷½«Äã³å×ß£¬ÉíÉÏ"
                                "È´ÊÇÒ»µãÁ¦ÆøÒ²Ê¹\n²»³öÀ´¡£\n\n" NOR, me);

        	me->move(__DIR__"heishatan");
        	me->unconcious();     

        	return 1;
	}

        if (skill_dodge < 140)
        {
             	message_vision(HIC "\n$N" HIC "·ÜÁ¦ÍùÇ°Ò»Ìø£¬ÏÕĞ©±»ÆÙ²¼´òÂä£¬µ«ÓĞ¾ª"
                               "ÎŞÏÕ£¬$N" HIC "ÖÕÓÚÂäÔÚ¶´¿Ú´¦£¬¿ÉÑù×ÓÈ´ÉõÊÇÀÇ±·¡£\n\n" 
                               NOR, me);
        	me->move(obj);
        	message("vision", HIW "\n" + me->name() + HIW "´ÓÆÙ²¼ÍâÌøÀÇ±·Íò·ÖµØ"
                                  "ÌøÁË½øÀ´¡£\n\n" NOR, obj, me);

        	return 1;
        }

        msg = HIC "\n$N" HIC "ÌáÆøÏòÇ°Ò»×İ£¬ÇáËÉµØÂäÔÚ¶´¿Ú´¦¡£\n\n" NOR;	
        message_vision(msg, me);
        me->move(obj);
        message("vision", HIW "\n" + me->name() + HIW "´ÓÆÙ²¼ÍâÌøÁË½øÀ´¡£\n" NOR, 
                          obj, me);

       	return 1;
}
