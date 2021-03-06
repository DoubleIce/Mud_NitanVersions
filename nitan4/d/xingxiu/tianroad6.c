inherit ROOM;

void create()
{
        set("short", "天山顶峰");
        set("long", @LONG
这里是天山顶峰。从这里向周围望去，帕米尔高原的风光尽收眼
底。东面一条小路可以下山。山风凛冽，极为强劲，几乎无法站立。
LONG );
        set("exits", ([
            	"eastdown" : __DIR__"tianroad5",
        ]));
        set("outdoors", "xingxiu");
        set("resource/quarry", ([
            "/clone/quarry/can" :  50,//蚕
            "/clone/quarry/tiancan" :  10,//天蚕
            "/clone/quarry/he" :  50,//丹顶鹤
            "/clone/quarry/he2" :  10,//雪鹤，没找到仙鹤
            "/clone/quarry/hou" :  50,//猴子
            "/clone/quarry/niao" :  50,//斑鸠
            "/clone/quarry/ying" :  50,//秃鹰
        ]));
        setup();
}
