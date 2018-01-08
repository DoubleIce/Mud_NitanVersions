// seller.c

inherit KNOWER;
inherit F_VENDOR;

void create()
{
	set_name("С��", ({ "seller" }) );
	set("gender", "����" );
	set("age", 32);
	set("long",
		"���Ǹ�С����������������ʵʵ�������������Ƕ��ͱ��ˡ�\n");
	set("combat_exp", 300);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
	set("attitude", "friendly");
	set("vendor_goods", ({
		__DIR__"obj/stick",
		__DIR__"obj/shoes",
                __DIR__"obj/bottle",
                __DIR__"obj/egg",
	}));

        set("chat_msg_chance", 5);
        set("chat_msg", ({
                "С��һ����������һ����죺����ƽʱ���߶�����Ϣ֪���û����١�\n",
                "С�����ܿ�������������������ô��ô̫ƽ��\n",
                "С�����˸���Ƿ�����������������˵����ɽ����Щ���СС�������һ�֪��һ�㡣\n",
        }));

	setup();

        carry_object("/clone/cloth/cloth")->wear();
	add_money("coin", 100);
}

void init()
{
        ::init();
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}