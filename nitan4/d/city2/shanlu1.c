inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "山道");
        set("long", @LONG
这里已经看不到襄阳了，满眼望去，尽是曲曲折折的山道，大军
行到此处，人畜都开始有些吃力起来。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "north"  : __DIR__"shanlu1",
                "south"  : __DIR__"shanlu1",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        if (! me->is_busy())
            me->start_busy(random(2));

        if( me->query_temp("yidao/mark_steps") > 11 )
        {
            me->move(__DIR__"wsling");
            me->delete_temp("yidao");
            tell_object(me,YEL"一路风尘仆仆之后，乌石岭已经近在眼前了......\n"NOR);
            return;
        }

        if( me->query_temp("yidao/mark_steps") < -11 )
        {
            me->move(__DIR__"shanlu");
            me->delete_temp("yidao");
            tell_object(me,YEL"一路风尘仆仆之后，大宋军营已经近在眼前了......\n"NOR);
            return;
        }

        tell_object(me,YEL"你指挥着大军，行进在曲折的山道上......\n"NOR);
}

int valid_leave(object me,string dir)
{
       if( dir == "south" )
       me->add_temp("yidao/mark_steps",-random(2));
       if(  dir == "north" )
       me->add_temp("yidao/mark_steps",random(2));
       return ::valid_leave(me,dir);
}

