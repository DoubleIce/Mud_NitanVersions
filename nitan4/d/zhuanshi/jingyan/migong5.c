inherit ROOM;

void create()
{
        set("short", "雁翔殿");
        set("long", @LONG
一踏进雁翔殿顿时给人一种怪异的感觉，殿顶刻着 一个巨大圆形
的图案，仔细一看，竟是一副星象图，圆形内星罗棋布，满是星点，
除了你熟悉的三恒二十八星宿外，其他的星宿你居然一个都不认识，
不由得看得你汗流浃背！
LONG );

        set("exits", ([
               "up" : "d/jingyan/migong2",
                          ]));
              set("no_stab", 1); 
        setup();
        replace_program(ROOM);
}
