inherit DATABASE_BOARD;

void create()
{
        set_name("华山派", ({ "board" }) );
        set("location", "/u/lonely/workroom");
        set("board_id", "mudbbs_b");
        // set("forum_id", 1);
        set("forum_name", "华山派");
        set("long", "这是一个MUD与论坛同步的留言板。\n" );
        setup();
        set("capacity", 100);
        replace_program(DATABASE_BOARD); 
}

