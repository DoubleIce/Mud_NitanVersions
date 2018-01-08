inherit ROOM;

void create()
{
  	set ("short", "中州道");
        set("long", @LONG
这是条连接南北的交通要道，来往行人不断。道旁的树木下多有
作小生意的商人。向南是中州城，北面通向扬州。
LONG );

  	set("outdoors", "zhongzhou");
  	set("exits", ([
  		"south" : __DIR__"to_zhongzhou3",
  		"north" : __DIR__"to_zhongzhou",
	]));

  	set("coor/x", -230);
	set("coor/y", 60);
	set("coor/z", 0);
	setup();
}
