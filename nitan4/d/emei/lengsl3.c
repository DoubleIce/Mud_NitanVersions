inherit ROOM;

void create()
{
      set("short", "冷杉林");
        set("long", @LONG
这是片遮天蔽日的冷杉林。数人也合抱不过来的冷杉树簇在一块，
枝繁叶茂，象一蓬蓬巨伞恒伸向天空，把阳光遮得丝毫也无。看地上
厚厚的枯枝烂叶，显然游客很少踏足此处。
LONG );
      set("exits", ([
          "west"      : __DIR__"bashisipan2",
          "northeast" : __DIR__"lengsl2",
          "southup"   : __DIR__"lengsl4",
      ]));
      set("no_clean_up", 0);
      set("coor/x", -560);
	set("coor/y", -280);
	set("coor/z", 190);
	set("coor/x", -560);
	set("coor/y", -280);
	set("coor/z", 190);
	setup();
      replace_program(ROOM);
}
