#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "×£ÈÚ·å");
        set("long", @LONG
×£ÈÚ·åÖ®¸ßÎªºâÉ½´óËÄ¾øÖ®Ê×¡£ÔÚ´Ë¸©î«Èº·å£¬¾¡ÊÕÑÛµ×¡£¶«Íû
Ïæ½­£¬ÄÏ¼°ÎåÁë£¬±±î«¶´Í¥£¬Î÷ÊÓÑ©É½¡£ÌÆ³¯¶Å¸¦ÍûÔÀÊ«ÖĞÓĞ¡¸[1£»37m×£ÈÚ
Îå·å×ğ£¬·å·å´ÎµÍ°º[2£»37£»0m¡¹¡£ÖøÃûÊ«ÈËº«ÓúÒàÒÔ¡¸[1£»37m×£ÈÚÍòÕÉ°ÎµØÆğ£¬Óû¼û
²»¼ûÇáÑÌÀï[2£»37£»0m¡¹¼«ÑÔÆä¸ß¡£
LONG );
        set("exits", ([
                "eastdown"   : __DIR__"shanlu004",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/mo" : 1,
        ]));    

        set("no_clean_up", 0);

        set("coor/x", -70);
	set("coor/y", 100);
	set("coor/z", 70);
	setup();
        replace_program(ROOM);
}

