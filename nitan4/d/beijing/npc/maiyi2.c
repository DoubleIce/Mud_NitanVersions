inherit BUNCHER;

void create()
{
        set_name("������", ({ "maiyi ren", "ren" }) );
        set("gender", "����" );
        set("age", 25);
        set("long",
              "һ���ؽ����յ��ˡ�\n");
        set("shen_type", 1);
        set("combat_exp", 10000);
        set("str", 20);
        set("dex", 20);
        set("con", 20);
        set("int", 20);
        set("attitude", "peaceful");
        set_skill("dodge",20);
        set_skill("unarmed",20);
        set("chat_chance", 1);
        set("chat_msg", ({
                 "�����˴����е���������ұ��ݰ��ľ��\n",
        }) );       

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
        add_money("silver", 10);
}
