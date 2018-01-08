inherit ROOM;

void create()
{
        set("short", "哈萨克群落");
        set("long", @LONG
这儿有一片哈萨克帐蓬。哈萨克人的帐蓬一年四季在草原上东西
南北的迁移。其中一帐蓬前挂着一张大狼皮显得格外醒目。一个身材
苗条的女孩捧了酒浆出来，很客气地招呼你。
LONG );
        set("outdoors", "gaochang");
        set("exits", ([
            	"south" : __DIR__"huijiang5",
        ]));
        set("objects", ([
                __DIR__"npc/aman"  : 1,
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
