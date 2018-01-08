#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIB "¡¾±ÌË®º®Ì¶¡¿" NOR);
        set("long", @LONG
[1£»34m                    ±Ì     Ë®     º®     Ì¶    ÕâÀï±ãÊÇÒõ
Ë¾µÄ±ÌË®º®Ì¶£¬´«ËµËÄÉñÊŞÖ®Ê×µÄÇàÁú³£³£³öÃ»ÓÚ´ËÌ¶ÖĞ¡£Ì¶ÖĞ±ùË®
ÖĞÓÄ°µÎŞ±È£¬ËÄÖÜËÆºõÓĞ¼¸´¦³ö¿Ú£¬µ«ÊµÔÚ¿´²»ÇåÊÇÍ¨ÏòºÎ´¦¡£Ë®ÖĞ
±ùÀä´Ì¹Ç£¬ÁîÈËÄÑÒÔÈÌÊÜ£¬ÄãÖ»¾õµÃÆøÁ¦ÔÚÒ»µãÒ»µãÏûÊ§¡£ÄãÇ°·½»í
È»³öÏÖÒ»¸öÉî²»¼ûµ×µÄÑÒ¶´£¬´Ó¶´ÄÚ´«³öÕóÕóºğÉù¡£[2£»37£»0m
LONG );

        set("exits", ([
                "enter" : __DIR__"qinglongtan",
                "east" : __DIR__"hantan1",
                "west" : __DIR__"hantan1",
                "south" :__DIR__"hantan1",
                "north" :__DIR__"hantan1",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me;
        int meqi, meneili, decqi, mq;
        me = this_player();

        if ( present("diyin xuemai", me))
        {
                tell_object(me, RED "Äã»³ÖĞµÄµØÒõÑªÂö·¢³öÒ»ÕóÕóÈÈÁ¿£¬»¤×¡ÁËÖÜÉíµÄ"
                                "¾­Âö£¡\n" NOR);
                return 0;
        }
        tell_object(me, HIW "ÄãÉíÏİ±ÌË®º®Ì¶£¬Ì¶ÖĞº®±ùÏ÷Èâ¹Î¹Ç£¬Äã"
                        "Ö»¾õ»ëÉíÑªÒº¶¼±»¶³×¡Ò»°ã£¡\n" NOR);
        meqi = (int)me->query("qi");
        meneili = (int)me->query("neili");
        mq = (int)me->query("max_qi");
        decqi = (int)( mq / (random(4) + 5 + meneili/200) );
        meqi = meqi - decqi;
        me->set("neili", 0);

        if(meqi > 0)
        {
                me->set("qi", meqi);
        }
   else {
                me->set_temp("die_reason", "ÔÚ±ÌË®º®Ì¶¸ø»î»î¶³ËÀÁË");
                me->die();
        }
        return 0;
}
