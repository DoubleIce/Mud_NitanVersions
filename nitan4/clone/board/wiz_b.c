#include <ansi.h>
inherit BULLETIN_BOARD;

void create()
{
        set_name("巫师留言簿", ({ "board" }));
        set("location", "/d/wizard/wizard_room");
        set("board_id", "wiz_b");
        set("wizard_only", 1);
        set("long", HIY "这堵墙上刻满了希奇古怪的咒文，也不知道记载了些什么。\n" NOR);
        setup();
        set("capacity", 1000);
        replace_program(BULLETIN_BOARD);
}
