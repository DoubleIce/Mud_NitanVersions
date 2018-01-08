inherit ROOM;

void create()
{
      set("short","白龙洞");
        set("long", @LONG
白龙洞据说是「白蛇传」中的白娘子修炼成仙之处。这里楠木参
天，林荫夹道，株株秀挺俊何，枝叶分披上捧，如两手拥佛，传为古
时一高僧按「法华经」口诵一字植树一株，共植六万九千七百七十七
株，时称古德林。这里北上至万年庵，南下是清音阁。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "east"      : __DIR__"qingyinge",
          "west"      : __DIR__"gudelin2",
          "northup"   : __DIR__"wannianan",
          "southeast" : __DIR__"gudelin1",
      ]));
      set("no_clean_up", 0);
	set("coor/x", -470);
	set("coor/y", -230);
	set("coor/z", 80);
	setup();
      replace_program(ROOM);
}
