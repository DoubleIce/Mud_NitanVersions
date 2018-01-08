#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", GRN "¡¾ÇàÁú¶´¡¿" NOR);
        set("long", @LONG
[32m                    Çà         Áú         ¶´    ÕâÀïÊÇÒõ
Ë¾±ÌË®º®Ì¶×îÉî´¦µÄÒ»¸ö¶´Ñ¨£¬¶´µÄÉÏ²¿¿Õ¿õ£¬´æÓĞÉÙÁ¿µÄ¿ÕÆø£¬Äã
ÖÕÓÚ¿ÉÒÔ»»ÆøÁË¡£´«ËµËÄÉñÊŞÖ®Ê×µÄÇàÁú¾ÍÆÜÏ¢ÓÚ´ËµØ¡£¶´ÄÚÓÄ°µÎŞ
±È£¬ÁîÄã¸ù±¾¿´²»ÇåÖÜÎ§µÄÊÂÎï£¬ºÜÄÑ×·Ñ°(xun) µ½ÇàÁúµÄ×ÙÓ°¡£Ì¶
Ë®±ùÀä´Ì¹Ç£¬ÁîÈËÄÑÒÔÈÌÊÜ£¬ÄãÖ»¾õµÃÆøÁ¦ÔÚÒ»µãÒ»µãÏûÊ§¡£¶´Ñ¨Éî
´¦ÓĞÒ»¹ÉÁİÙıµÄº®Á÷ĞÎ³ÉÁËÒ»¸ö¼±ËÙÁ÷¶¯µÄĞıÎĞ(xuanwo)¡£[2£»37£»0m
LONG );

        set("objects", ([
                __DIR__"obj/shuizao" : 1,
        ]));

        set("item_desc", ([
                "xuanwo" : HIW "\nÒ»¹ÉÓÉº®Á÷ĞÎ³ÉµÄĞıÎĞ£¬ÄãËÆºõ"
                           "¿ÉÒÔÍ¨¹ıËü»Øµ½µØÃæ¡£\n" NOR,
        ]));

        set("qinglong", 1);
        setup();
}

void init()
{
        object me;
        int meqi, meneili, decqi, mq;
        me = this_player();

        add_action("do_move", "enter");
        add_action("do_xun", "xun");

        if (me->query("id") == "e long"
           || present("diyin xuemai", me))
        {
                tell_object(me, RED "Äã»³ÖĞµÄµØÒõÑªÂö·¢³öÒ»ÕóÕóÈÈ"
                                "Á¿£¬»¤×¡ÁËÖÜÉíµÄ¾­Âö£¡\n" NOR);
                return 0;
        }
        tell_object(me, HIW "ÄãÉíÏİ±ÌË®º®Ì¶£¬Ì¶ÖĞº®±ùÏ÷Èâ¹Î¹Ç£¬Äã"
                                "Ö»¾õ»ëÉíÑªÒº¶¼±»¶³×¡Ò»°ã£¡\n" NOR);
        me->set_temp("die_reason", "ÔÚ±ÌË®º®Ì¶¸ø»î»î¶³ËÀÁË");
        me->die();
        return 0;
}

int do_xun(string arg)
{
        object me = this_player();
        object ob;
        object ob1;

        if (objectp(present("e long", environment(me))))
                return notify_fail("ÇàÁúÒÑ¾­ÏÖÉíÁË£¬»¹Ñ°Ê²Ã´Ñ½£¬¸Ï¿ìÕ½¶·°É£¡\n");

        if (query("qinglong") < 1)
                return notify_fail("ÇàÁúÒÑ¾­±»Ô×ÁË£¬ÄãÔÙÔõÃ´Ñ°Ò²ÊÇÑ°²»µ½µÄ£¡\n");

        if (me->is_busy())
                return notify_fail("ÄãÏÖÔÚÕıÃ¦×ÅÄØ¡£\n");
       
        if ((int)me->query("jing") < 100)
                return notify_fail("ÄãÌ«ÀÛÁË£¬ÉÔÎ¢ĞİÏ¢Ò»ÏÂ°É¡£\n");

        if ((int)me->query("qi") < 100)
                return notify_fail("ÄãÌ«ÀÛÁË£¬ÉÔÎ¢ĞİÏ¢Ò»ÏÂ°É¡£\n");

        message_vision(HIC "\n$N" HIC "ÔÚ¶´ÄÚËÄ´¦ÓÎ×ß£¬²»·Å¹ı°ëµãÖë"
                       "Ë¿Âí¼££¬×ĞÏ¸µÄËÑÑ°×Å¶´Ñ¨ÄÚµÄÒ»ÇĞ¡£\n" NOR, me); 
        remove_call_out("xun"); 
        call_out("xun", 5, me);
        me->start_busy(5);
        return 1;
}
 
int xun(object me)
{ 
        object ob;
        object ob1;
        if (random(10) < 1)
        {
                me->receive_damage("jing", 50 + random(50));
                me->receive_damage("qi", 50 + random(50));
                me->start_busy(5);
                message_vision(WHT "$N" WHT "Ñ°ÃÙÁË°ëÌì£¬»¹ÊÇÃ»·¢ÏÖÇà"
                               "Áú³öÃ»µÄ¼£Ïó£¬Ò»¿ÚÆøÔÙÒ²±ï²»×¡£¬Á¬Ã¦"
                               "ÓÎµ½¶´µÄÉÏ²¿»»Æø¡£\n" NOR, me);
                return 1;
        }

        if (random(10) < 5)
        {
                me->receive_damage("jing", 50 + random(50));
                me->receive_damage("qi", 50 + random(50));
                me->start_busy(5);
                message_vision(HIY "½á¹û$N" HIY "Ò»×ªÉí£¬Ë«½Å²»Ğ¡ĞÄ±»"
                              "ÑÒ±ÚÉÏÉì³öµÄË®Ôå²ø×¡£¬·ÑÁËºÃ´ó¾¢²ÅÕõÔú"
                              "¿ª¡£\n" NOR, me);
                return 1;
        }

   else if (random(10) < 4) 
        {         
                me->receive_damage("jing", 300 + random(50));
                me->receive_damage("qi", 300 + random(50));
                me->receive_wound("jing", 200 + random(50));
                me->receive_wound("qi", 200 + random(50));
                me->start_busy(5);
                message_vision(HIR "½á¹û$N" HIR "·­×ªÉíÌåÊ±£¬¡°Åé¡±µÄÒ»"
                               "Éù£¬Í·×²ÔÚÁË¼âÍ»µÄÑÒ±ÚÉÏ£¬µÇÊ±ÏÊÑª·É½¦£¬"
                               "Í´µÃ$N" HIR "¡°à»à»¡±¹Ö½Ğ²»Ö¹¡£\n"
                               NOR, me);
                return 1;
        }

   else { 
                ob = new("/d/jingyan/npc/long");
                ob->move("/d/jingyan/qinglongtan");
                add("qinglong", -1);
                message_vision(HIW "\n\nÖ»Ìı¶´Ñ¨Éî´¦´«À´ÕğÌì¶¯µØµÄÒ»Éù"
                                   "Å­º¿£¬½ĞÉùÕğµÃÄãÁ½¶úºäÃù£¬¹ÄÄ¤ÒşÒş"
                                   "×÷\nÍ´¡£ÄãÖÜÎ§µÄ±ÌÌ¶º®Ë®¼±ËÙ¾í¶¯£¬"
                                   "¼¤ÆğÌÏÌì²¨ÀË£¬ÑÛÇ°Ò»»¨£¬Ò»¸öÅÓÈ»´ó"
                                   "Îï\n³öÏÖÔÚÄãÃæÇ°£¬ËÄÉñÊŞÖ®Ê×µÄÇàÁú"
                                   "ÖÕÓÚÏÖÉíÁË¡£\n\n" NOR, me); 
                return 1;
        }
       
}

int do_move(string arg)
{
        object paper,
        me = this_player();

        if (! arg || arg == "")
                return 0;

        if (arg == "xuanwo")
        {
                if ( objectp(present("qing long", environment(me))))
                {
                        write(HIW "\nÇàÁúÒ»ÉùÅ­º¿£¬ÁúÎ²Ö±É¨¶ø³ö£¬Åü´òÔÚÄã"
                              "ÉíÅÔµÄÑÒ±ÚÉÏ£¬Ê¯Ğ¼·ÉÕÀ£¬µ²×¡ÁËÈ¥Â·¡£\n" NOR);
                        return 1;
                }
                message_vision(HIW "\n$N" HIW "ÄãÒ»×İÉí£¬Ìø½øÁËº®Á÷ĞıÎĞ¡­¡­\n"
                               NOR, me);
                me->move("/d/city/guangchang");
                message_vision(HIW "\nÖ»¼û$N" HIW "±»º®Á÷ĞıÎĞÅ×µ½¿Õ"
                                   "ÖĞ£¬È»ºóÖØÖØµÄµøÂäÔÚÑïÖİ¹ã³¡¡£\n" NOR, me);
                me->set("neili", 0);
                me->set("jingli", 0);
                me->set("qi", 10);
                me->set("eff_qi", 10);
                me->set("jing", 10);
                me->set("eff_jing", 10);
                tell_object(me, HIR "Äã±»µøµÃÍ·ÔÎÄ¿Ğı£¬Á½¶úºäÃù£¬¡°ÍÛ¡±µÄÅç³ö"
                                "Ò»´ó¿ÚÏÊÑª¡£\n" NOR);
                destruct(present("diyin xuemai", me));
                tell_object(me, HIC "\nÄã»³ÖĞµÄ" NOR + RED "µØÒõÑªÂö" NOR +
                                HIC "ºÄ¾¡ÄÜÔ´£¬»¯×÷ÁËÒ»ÂÅÆøÌåÆ®³ö¡£\n" NOR);
                return 1;
        }
        return 0;
}
