inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "¹ù¸®´óÃÅ");
        set("long", @LONG
½¨Öş¹ÅÆÓµÄ´óÕ¬Ôº³öÏÖÔÚÄãµÄÑÛÇ°¡£Ö»¼ûÃÅÂ¥¸ßÌô£¬ÃÅÇ°Á¢ÁËÁ½
¸öÊ¯Ê¨£¬´óÃÅÉÏÊéÁ½¸ö´ó×Ö[33m              ¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù
              ¡ù                  ¡ù              ¡ù[2£»37£»0m[1£»33m     ¹ù 
   ¸®[2£»37£»0m[33m     ¡ù              ¡ù                  ¡ù            
  ¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù¡ù[2£»37£»0mÄã´Ó´óÃÅÇÆ½øÈ¥£¬ºÃÏóÀïÃæÈËÀ´ÈËÍù£¬¶¼
ºÜ·±Ã¦µÄÑù×Ó¡£ÕâÀïÕ¾×ÅÎ»ÇàÄê£¬ÉñÇéÍşÑÏ¡£½Ó´ıÇ°À´±£ÎÀÏåÑôµÄ¸÷
·½ÒåÊ¿¡£
LONG );
        set("outdoors", "xiangyang");
	set("exits", ([
		"south" : "/d/xiangyang/westjie1",
		"north" : __DIR__"guofu_dayuan",
	]));
	set("objects", ([
		__DIR__"npc/wudunru" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
        if (me->query("mark/guofu_ok")
           && present("wu dunru", environment(me)) 
           && dir == "south")
             return notify_fail(CYN "\nÎä¶ØÈåÉìÊÖ½«ÄãÀ¹×¡µÀ£ºÏÖÔÚ"
                                "ÏåÑô³ÇÄÚ²»Ì«Æ½£¬Äã»¹ÊÇ¶à´ôÒ»»á°É"
                                "¡£\n" NOR);

        if (me->query("mark/guofu_over")
           && present("wu dunru", environment(me))
           && dir == "north")
             return notify_fail(CYN "\nÎä¶ØÈå½«ÄãÀ¹×¡£¬ÀäĞ¦µÀ£º¹ù"
                                "¸®ÁôÄã²»ÏÂ£¬Äã»¹ÊÇ×ß°É¡£\n" NOR);

        if (me->query("mark/guofu_out")
           && present("wu dunru", environment(me)) 
           && dir == "north")
             return notify_fail(CYN "\nÎä¶ØÈåĞ¦µÀ£ºÄãÔÙÁôÔÚ¹ù¸®ÒÑ"
                                "ÎŞ¶à´óµÄÓÃ´¦£¬»¹ÊÇ¶àÈ¥´³µ´´³µ´°É"
                                "¡£\n" NOR);

        if (count_gt(me->query("combat_exp"), 5000)
           && ! me->query("mark/guofu_ok")
           && present("wu dunru", environment(me)) 
           && dir == "north")
             return notify_fail(CYN "\nÎä¶ØÈå±§È­µÀ£ºÏÖÏåÑôÕıÖµ¶¯"
                                "ÂÒÊ±ÆÚ£¬Ã»Ê¦¸¸Ğí¿É£¬ÈÎºÎÈË²»µÃÈë"
                                "ÄÚ¡£\n" NOR);

        if (! me->query("mark/guofu_ok")
           && present("wu dunru", environment(me)) 
           && dir == "north")
             return notify_fail(CYN "\nÎä¶ØÈåÉìÊÖ½«ÄãÀ¹×¡µÀ£ºÈç¹û"
                                "Äã²»´òËã°ïÃ¦´òÔÓ£¬¾Í±ğ½øÀ´¡£\n" NOR);

        return ::valid_leave(me, dir);
}
