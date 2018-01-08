inherit ROOM;

void create()
{
        set("short", "苦寒楼二层");
        set("long", @LONG
每个楼层上都铺设了结实的木楼板，八角形的墙身上则开了四扇
大窗。四周墙壁贴着昆仑派历代掌门和高手的画像，并有专门的文字
记载着他们的事迹。从这里往外眺望，只能看到围绕塔周的密密匝匝
的云杉林，正是通过这种忍饥耐寒，清心寡欲的办法以求得对武学孜
孜不倦的追求。
LONG );

        set("exits", ([
                "up" : __DIR__"kuhanlou3",
                "down" : __DIR__"kuhanlou1",
        ]));

        setup();
        replace_program(ROOM);
}
