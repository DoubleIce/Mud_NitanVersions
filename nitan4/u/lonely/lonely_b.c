#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name("留言簿", ({ "board" }));
        set("location", "/u/lonely/workroom");
        set("board_id", "lonely_b");
        set("wizard_only", 1);
        set("long", HIY "这堵墙上刻满了希奇古怪的咒文，也不知道记载了些什么。\n" NOR);
        setup();
        set("capacity", 1000);
        replace_program(BULLETIN_BOARD);
}
