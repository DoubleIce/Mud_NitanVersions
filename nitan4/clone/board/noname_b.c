inherit BULLETIN_BOARD;

void create()
{
	set_name("�������԰�", ({ "board" }) );
	set("location", "/d/wizard/noname_room");
	set("board_id", "noname_b");
        set("noname_board", 1);
	set("private_board", 1);
	set("long", "˵�ɣ�������ʦû��֪������˵�����ݡ�\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}


       