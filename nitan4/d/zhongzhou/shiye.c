inherit ROOM;

void create()
{
        set("short", "师爷处");
        set("long", @LONG
一走进师爷的屋子，就见师爷的桌子上零星的散落着一些糖和瓜
果。北面的大墙上贴着一张大的告示，师爷悠闲的坐在太师椅上。
LONG );
        set("exits", ([
                "south" : __DIR__"zoulang1",                 
        ]));

	set("coor/x", -250);
	set("coor/y", 40);
	set("coor/z", 0);
	setup();
}

