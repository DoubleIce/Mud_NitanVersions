inherit ROOM;

void create()
{
        set("short", "书房");
        set("long", @LONG
这里是书房，靠墙一排大书架，摆放着很多的书籍，昆仑三圣何
足道以琴棋剑而号称以「三圣」，故昆仑派一直引以为荣，鼓励弟子
学琴棋艺。
LONG );
        set("exits", ([
                "west"  : __DIR__"shilu1",
        ]));
        
        setup();
        replace_program(ROOM);
}
