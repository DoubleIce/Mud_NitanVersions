// Create by lonely@NT
inherit ROOM; 
#include <ansi.h>; 
void create() 
{ 
        set("short", "山道"); 
        set("long", @LONG
这里已经快到雁门关了，满眼望去，尽是曲曲折折的山道，大军
行到此处，人畜都开始有些吃力起来。
LONG );
        set("outdoors", "yanmen"); 
        set("no_fly",1); 
        set("exits", ([ 
                "north"  : "/d/guanwai/shanhaiguan", 
                "south"  : __DIR__"luanshi1", 
        ])); 
        setup(); 
} 
