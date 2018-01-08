inherit ROOM;

void create()
{
	set("short", "书房");
        set("long", @LONG
这是郭靖的书房。右边是书架，上面陈列着道家和儒家的一些典
籍，却没有一本与武学有关的书。左边靠窗的地方摆着一张木桌，上
面放着笔墨纸砚，边上放着几本书，摆放得整整齐齐，搽拭得一尘不
染，阁里到处被打扫得一尘不染，窗明几净，可以看到外面松竹掩映，
时有微风入户，门后桌上还燃着一炉檀香，氲氲的香气轻轻横散，使
人俗念尽消，心情完全平静下来。
LONG );
        set("no_fight", 1);
	set("no_clean_up", 0);
	set("exits", ([
		"south" : __DIR__"guofu_huayuan",
	]));
	setup();
	replace_program(ROOM);
}

