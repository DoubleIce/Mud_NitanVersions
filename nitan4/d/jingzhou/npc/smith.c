#include <ansi.h> 

inherit "/inherit/char/smith.c"; 

void create()
{
        set_name("����", ({ "tiejiang", "smith" }));
	set("title", "�������ϰ�");
	set("shen_type", 1);

        set("gender", "����" );
        set("age", 33);
        set("long", "����������ǯ��סһ����ȵ�����Ž�¯�С�\n");

        set("combat_exp", 400);
	set("attitude", "friendly");
        set("vendor_goods",({
                   "/d/jingzhou/obj/changjian",
                   "/d/jingzhou/obj/gangdao",
                  "/d/jingzhou/obj/armor",
                  "/d/jingzhou/obj/beixin",
                          }));


	setup();

	carry_object("/clone/misc/cloth")->wear();
}
