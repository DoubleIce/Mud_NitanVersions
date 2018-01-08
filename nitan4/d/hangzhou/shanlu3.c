// shanlu3.c
// Date: Nov.1997 by Venus

inherit BUILD_ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
小溪横过山路，跨溪有一座小石桥。溪边农家小孩在嬉戏玩乐。
如此情趣让你不禁慨然生叹，一时间颇有远避江湖之意。南上便到了
上天竺，北下就是中天竺。
LONG );
        set("exits", ([
            "southup"   : "/d/hangzhou/faxisi",
            "northdown" : "/d/hangzhou/fajinsi",
        ]));
        set("objects", ([
            "/d/hangzhou/npc/boy" : 3,
        ]));
        set("outdoors", "hangzhou");
        set("max_room", 4);
        setup();
}
