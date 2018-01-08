inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这条山路盘终南山主峰而上，山路贴着石璧凿出，只容一人可过，
形势极为险峻。往远处望去。群山环绕，列於脚下，百里美景尽收眼
底，顿时令人豪气陡声，往东下和南上各是一条山路。
LONG );
        set("outdoors", "quanzhen");
        set("exits", ([
                "southup"   : __DIR__"shanlu2",
                "eastdown"  : __DIR__"shanlu4",
        ]));

        setup();
        replace_program(ROOM);
}
