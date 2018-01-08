inherit ROOM;

void create()
{
        set("short", "会真堂");
        set("long", @LONG
这里是大堂旁的一个侧厅，也是接待重要客人的地方。厅不大，
只摆放着一张桌子和几把椅子。桌上摆放着一盆青松山石的盆景，墙
壁上挂着一些字画。
LONG );
        set("exits", ([
                "east" : __DIR__"cetang",
                "north" : __DIR__"wanwutang",
                "south" : __DIR__"datang1",
        ]));
        set("objects",([
              CLASS_D("quanzhen") + "/cui" : 1,
        ]));

        setup();
        replace_program(ROOM);
}
