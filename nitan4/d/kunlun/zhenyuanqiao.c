inherit ROOM;

void create()
{
	set("short", "镇远桥");
        set("long", @LONG
这座桥号称『天下黄河第一桥』，气势极为雄伟，扼守西域，东
往中原。黄河水从桥底倾泻而过，轰隆作响。
LONG );

         set("exits",([
                 "west" : __DIR__"shanlu",
 	         "eastdown" : "/d/mingjiao/shanjiao",
         ]));

         set("objects", ([
	         "/d/city/npc/wujiang" :  1,
                 "/d/city/npc/bing" :     3,
         ]));

         set("outdoors", "kunlun");
         setup();
         replace_program(ROOM);
}
