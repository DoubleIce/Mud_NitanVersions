inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
这是一所乡间民居，桌椅都很旧了，而且看得出来是自己敲敲打
打给拼补下来的，不过擦拭得很干净。墙壁上斜倚着支猎叉，也许这
家的主人还是个捕猎高手。
LONG );
        set("exits", ([
                "southeast" : __DIR__"guchang",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
