inherit DATABASE_BOARD;

void create()
{
        set_name("��ɽ��", ({ "board" }) );
        set("location", "/u/lonely/workroom");
        set("board_id", "mudbbs_b");
        // set("forum_id", 1);
        set("forum_name", "��ɽ��");
        set("long", "����һ��MUD����̳ͬ�������԰塣\n" );
        setup();
        set("capacity", 100);
        replace_program(DATABASE_BOARD); 
}

