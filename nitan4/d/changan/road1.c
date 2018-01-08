inherit  ROOM;

void  create  ()
{
        set("short",  "关洛道");
        set("long", @LONG
    这是一条宽阔笔直的官道，足可容得下十马并驰。往东通向
脂粉之都的洛阳，往西则直达长安城。一条车痕向西向东伸展，不时
有人骑着马匆匆而过。
LONG );
        set("exits",  ([
                "east"  :  "/d/luoyang/guandaow4",
                "west"  :  "/d/changan/hanguguan",
        ]));

        set("outdoors", "changan");
        set("coor/x", -290);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}

