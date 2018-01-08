#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIR "¡¾ µØ Òõ ¡¿" NOR);
        set("long", @LONG
[1£»31m                       µØ            Òõ    ÕâÀï±ãÊÇ´«ËµÖĞ
µÄ¡¸µØÒõ¡¹£¬ÄãÃæÇ°ÊÇÒ»¸öÎŞµ×ÉîÔ¨£¬ÉîÔ¨ÄÚ²àĞü¸¡×ÅÒ»¿éÑªºìÉ«µÄ
¾Ş´ó¾§Ìå(jingti)£¬Ê±Ã÷Ê±°µ£¬É¢·¢³ö°µµ­µÄÑªºìÉ«¹âÃ¢£¬Í¶Éä×ÅË¿
Ë¿ÈÈÁ¿¡£Ò²ĞíÕâ¾Í´«ËµÖĞµÄ¡¸µØÒõÑªÂö¡¹°É¡£[2£»37£»0m
LONG );
        set("exits", ([
                "down" : __DIR__"hantan1",
        ]) );

        set("item_desc", ([
                "jingti" : RED "Ò»¿éÑªºìÉ«µÄ¾Ş´ó¾§Ìå£¬·¢³öÑªÉ«¹â"
                           "Ã¢£¬ÄãÈÌ²»×¡ÏëÇÃ(qiao)Ò»¿éÏÂÀ´¡£\n" NOR,
        ]));

        set("no_sleep_room", 1);

        setup();
}

void init()
{
        add_action("do_qiao", "qiao");
}

int do_qiao(string arg)
{
        object me = this_player();
        object ob;

        if( (!arg) || !((arg == "jingti") || (arg == "¾§Ìå")))
                return notify_fail("ÄãÒªÇÃÊ²Ã´£¿\n");

        message_vision(HIW "\n$N" HIW "Ò»Ô¾¶øÆğ£¬·ÉÉíÒ»ÕÆÅüÔÚÑªºìÉ«¾§ÌåÒ»²à¡£\n" NOR, me);
 
        if(query("not_xuemai") || me->query("combat_exp") < 1500000 )
        {
                message("vission", HIY "¿ÉÊÇ¾§ÌåÖ»ÊÇÇáÎ¢µÄ»Î¶¯ÁËÒ»ÏÂ£¬ÔÙÃ»ÆäËü·´Ó¦¡£\n" NOR, me);
                return 1;
        }
        ob = new(__DIR__"obj/diyin");
        ob->move( environment(me) );
        message_vision(HIR "Ö»¼û¾§ÌåÊÜÕğ£¬¡¸¿¦àê¡¹Ò»Éù£¬Ò»Ğ¡¿é¾§ÌåËéÆ¬ÂäÔÚÁËµØÉÏ¡£\n" NOR, me);
        set("not_xuemai", 1);
        remove_call_out("regenerate"); 
        call_out("regenerate", 86400);
        return 1;
}

int regenerate()
{
        set("not_xuemai", 0);
        return 1;
} 

