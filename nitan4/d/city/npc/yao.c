// yao.c 姚岳玲
// By Dumbness, 2003-5-24 19:26

inherit BUNCHER;
inherit F_DEALER;

void create()
{
        set_name("姚岳玲", ({ "yao yueling","yueling","yao" }));
        set("title", "胭脂店老板");
        set("shen_type", 1);
        set("gender", "女性");
        set("age", 25);
        set("per", 27);
        set("long", @LONG
一个卖胭脂的女子，瘦削、苍白、纤弱，她淡淡地坐在鹅黄色的窗帘后，丝丝缕
缕的阳光遮去了她的脸，但模糊中仍能辨出那精致的五官和迷离的眼神，落落寡
欢的神情透着风尘与优雅的混合气味，复杂的气质一如她的魅人的各色胭脂，叫
人想入非非，又不敢接近。 
LONG );
        set("attitude", "friendly");
        set("vendor_goods", ([ 
                "/d/city/npc/obj/yanzhi"       : 1000,
                "/d/city/npc/obj/baohuayou"    : 1000,
                "/d/city/npc/obj/huafendai"    : 1000,
                "/clone/gift/xiaobao"     : 200000, 
                "/clone/gift/dabao"       : 500000, 
                "/clone/gift/huirongwan"       : 500000,
        ]));
        
        setup();
        carry_object("/clone/cloth/female1-cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

