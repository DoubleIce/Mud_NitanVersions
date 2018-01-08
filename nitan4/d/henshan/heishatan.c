#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "ºÚÉ³Ì¶");
        set("long", @LONG
ºÚÉ³Ì¶ÓÖ³ÆºÚÁúÌ¶£¬Éî²»¼ûµ×£¬Ë®É«²ÔºÚ£¬ÆÙ²¼Á÷¼±£¬Ë®ÖÐºÚÅÝ
¹²°×Ä­áäáà£¬ÓÄÓÄ¿É²À¡£Ê¯±ÚÉÏ¡¸[1£»33mº£ÄÏÁúäÐ[2£»37£»0m¡¹ËÄ×Ö¾ÝÔØÎª´óËÎ»Õ×ÚÕÔ
Ù¥ËùÁô¡£ÊÝ½ð×ÖÌå£¬Ò»ÈçÍùÎô¡£
LONG );
        set("exits", ([ 
               "up"  : __DIR__"shanjian",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);
        set("coor/x", -100);
	set("coor/y", 30);
	set("coor/z", -10);
	setup();
}

int valid_leave(object me, string dir)
{
    if ((random((int)me->query_skill("dodge")) <= 30) && dir=="up")    
    {
        return notify_fail("ÄãÊ¹¾¢¶ùÒ»±Ä£¬ÀëÆÙ²¼¶¥»¹ÓÐÊýÕÉÔ¶¾ÍµôÁËÏÂÀ´£¬Ë¤µÄ±ÇÇàÁ³Ö×¡£\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 35) && dir=="up")    
    {
        return notify_fail("Äã·ÜÁ¦Ò»Ô¾£¬È´ÀëÆÙ²¼¶¥»¹ÓÐÒ»ÕÉ¶àÔ¶£¬¿´À´ÊÇ°×·ÑÁ¦Æø¡£\n");
    }
    if ((random((int)me->query_skill("dodge")) <= 40) && dir=="up")    
    {
        return notify_fail("Äã×ÝÉí¶øÆð£¬ÀëÆÙ²¼¶¥Ö»²îÒ»µãµãÁË£¬ÔÙ¼Ó°Ñ¾¢¡£\n");
    }

    return ::valid_leave(me, dir);
}

