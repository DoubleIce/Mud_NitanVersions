// Room: /d/xiangyang/guofugate.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;
void create()
{
	set("short", "¹ù¸®´óÃÅ");
        set("long", @LONG
Ò»×ù½¨Öş¹ÅÆÓµÄ´óÕ¬Ôº³öÏÖÔÚÄãµÄÑÛÇ°¡£Ö»¼ûÃÅÂ¥¸ßÌô£¬ÉÏÊéÁ½
¸ö´ó×Ö[1£»32m                     ¹ù   ¸®[2£»37£»0mÈ«Õæ½ÌµÚ¶ş´úµÜ×ÓÒ®ÂÉÆëºÍ¼¸
¸ö¼Ò¶¡Õ¾ÔÚÃÅÇ°½Ó´ıÇ°À´±£ÎÀÏåÑôµÄ¸÷·½ÒåÊ¿¡£
LONG );
        set("outdoors", "xiangyang");
	set("exits", ([
		"south" : "/d/xiangyang/westjie1",
		"north" : "/d/xiangyang/guofuyuan",
	]));
	set("objects", ([
		"/d/xiangyang/npc/yelvqi" : 1,
		"/d/xiangyang/npc/jiading" : 2,
	]));
	set("coor/x", -300);
	set("coor/y", -80);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}

