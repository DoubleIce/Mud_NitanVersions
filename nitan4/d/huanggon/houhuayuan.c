// houhuayuan.c 后花苑

inherit ROOM;

void create()
{
        set("short", "后花苑");
        set("long", @LONG
这里是皇上赏花的后花苑。平日里皇上时常会来这儿，和贵妃娘
娘一起赏花品茗。所以，这儿是平常太监，侍卫不能来的。这里的宫
女多是心灵手巧，精通花道的。放眼四顾，满目皆是似锦繁花，你仔
细分辨，竟然品目齐全，大凡你想得的，甚至你想都不敢想的，这里
都有了。你不经有些妒疾起皇帝老儿来。
LONG );
        set("outdoors", "huanggon");
        set("exits", ([
                "west" : __DIR__"houhuayuan2",
                "south" : __DIR__"qihedian",
        ]) );
        set("objects", ([
                "/d/huanggon/npc/gonnv" : 2,
        ]) );
        setup();
        replace_program(ROOM);
}
