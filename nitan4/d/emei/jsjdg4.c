inherit ROOM;

void create()
{
      set("short","九十九道拐");
        set("long", @LONG
这是著名的「九十九道拐」，道路纡曲陡竖千折百回。据说过去
曾有个百余岁的疯僧至此，见一巨蟒挡路，便念咒驱蟒。但人们得知
此处有巨蟒出没后，便再无人敢碰这里的草木，并以「龙居」名之。
由此东可至千佛庵，西达九老洞。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown" : __DIR__"jsjdg3",
          "west"     : __DIR__"jldongkou",
      ]));
	set("coor/x", -510);
	set("coor/y", -250);
	set("coor/z", 130);
	setup();
      replace_program(ROOM);
}
