// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "碎石小路"); 
        set("long", @LONG
这是一条通往大厅的碎石小路，路上生满了青苔，一不当心就会
跌倒，两侧不知名的野花开得倒也茂盛，淡淡的散发着一种清新的花
香。草窠中偶尔传来一两声蟋蟀的叫声。一抬头，可以看见几个或是
蜈蚣状，或是老鹰状的风筝高高飞舞在蓝天白云中。
LONG );
        set("outdoors", "wansong");
        set("type", "road");
        set("exits",([
                "out":__DIR__"damen",
                "north":__DIR__"fuguitin",
        ]) );
        
        set("objects" , ([
                __DIR__"obj/flower" : 1,
        ])); 
        set("coor/x",-590);
        set("coor/y",210);
        set("coor/z",80);
        
        setup();
        replace_program(ROOM);
}    

