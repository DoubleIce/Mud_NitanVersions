inherit ROOM;
void create()
{
        set("short", "树林");
        set("long", @LONG
这是一片茂密的树林，林中芳草鲜美，落英缤纷，一层淡淡的薄
雾，混合着青青的草香，弥漫在空气之中。偶尔的一两声鸟鸣，愈发
地显出幽静来。林边有一石山，山边有条岩缝。
LONG );
        set("outdoors", "kunlun");
        set("objects", ([ 
                __DIR__"obj/kuzhi" : 2,
        ]));
        set("exits", ([ 
                "south" : __DIR__"kunlun10",
        ]));
       
        set("item_desc", ([
                "岩缝" : "这岩缝窄得连手都塞不进去，旁边的岩石上入石三分的刻着“张无忌埋经处”。\n", 
        ])); 
        setup();        
}
