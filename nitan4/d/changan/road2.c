inherit  ROOM;

void  create  ()
{
        set("short",  "大官道");
        set("long", @LONG
这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向函谷
关，往西则直达长安城。北边有一条小路通往山里。
LONG );
        set("exits",  ([
                "north"  :  "/d/village/hsroad1",
                "east"   :  "/d/changan/hanguguan",
                "west"   :  "/d/changan/zhongnan",
        ]));

        set("outdoors", "changan");
        set("coor/x", -310);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

