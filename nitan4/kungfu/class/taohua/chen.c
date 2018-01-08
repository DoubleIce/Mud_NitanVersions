// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// chen.c 陈玄风

#include <ansi.h>;
inherit NPC;

#define ZHENJING    "/clone/book/jiuyin2"

void create()
{
        object ob;
        set_name("陈玄风", ({ "chen xuanfeng", "chen", "xuanfeng" }));
        set("title", "黑风双煞");
        set("nickname", YEL "铜尸" NOR);
        set("gender", "男性");
        set("age", 35);
        set("long", "此人是黄药师的二弟子，他浓眉大眼，背厚膀宽，躯体甚\n"
                    "是壮健，只是面色微微泛黄。\n");
        set("attitude", "aggressive");
        set("str", 28);
        set("int", 25);
        set("con", 30);
        set("dex", 25);
        set("shen_type", -1);

        set("max_qi", 5000);
        set("max_jing", 3500);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 220);
        set("level", 20);
        set("combat_exp", 2000000);

        set_skill("claw", 240);
        set_skill("strike", 240);
        set_skill("force", 220);
        set_skill("parry", 240);
        set_skill("dodge", 220);
        set_skill("bibo-shengong", 240);
        set_skill("cuixin-zhang", 240);
        set_skill("jiuyin-zhao", 240);
        set_skill("luoying-shenfa", 220);
        set_skill("martial-cognize", 220);

        map_skill("force", "bibo-shengong");
        map_skill("parry", "jiuyin-zhao");
        map_skill("dodge", "luoying-shenfa");
        map_skill("claw", "jiuyin-zhao");
        map_skill("strike", "cuixin-zhang");

        prepare_skill("claw", "jiuyin-zhao");
        prepare_skill("strike", "cuixin-zhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.duo" :),
                (: perform_action, "claw.sha" :),
                (: perform_action, "strike.cui" :),
                (: exert_function, "recover" :),
        }));

        create_family("桃花岛", 2, "被逐弟子");
        set("inquiry", ([
                "铜尸" : "江湖上的人都这么叫我的，你怕不怕？哈哈哈哈。",
                "东邪" : "那是我师父的绰号。",
                "西毒" : "那是与家师齐名的高手之一，是个老毒物，住在白驼山。",
                "南帝" : "段王爷已出家当和尚去了，法名叫一灯。",
                "北丐" : "北丐统领中原的丐帮，势力颇为强大。",
                "黄蓉" : "她是我师父的独女，最是刁蛮任性。",
                "洪七公" : "洪七公武功高强，而且教会郭靖那小儿降龙十八掌，可恨！",
                "梅超风" : "她是我的师妹，也是我的内室。",
                "陈玄风" : "不就是我么？你是白痴啊？",
                "黄药师" : "他是我师父。"
        ]));
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        setup();
        if (clonep())
        {
                ob = find_object(ZHENJING);
                if (! ob) ob = load_object(ZHENJING);

                if (environment(ob) && random(3) == 1)
                {
                        ob = new(ZHENJING);
                        ob->move(this_object());
                }
                else if (! environment(ob))
                        ob->move(this_object());
        }
        carry_object("/clone/cloth/bupao")->wear();
}

void attempt_apprentice(object ob)
{
        command("say 少烦我，快滚！");
}

int accept_fight(object me)
{
        command("say 给我滚开！");
        return 0;
}

int accept_hit(object me)
{
        command("say 找死！");
        kill_ob(me);
        return 1;
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment(me);
        object guard = present("mei chaofeng", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);

        if (guard && ! guard->is_fighting())
        {
                message_vision(HIW "\n$N" HIW "大怒道：居然欺负到我们黑风双煞"
                               "头上来了，死吧！\n\n" NOR, guard);
                guard->kill_ob(ob);
        }
}

void die()
{
        object obj, me;
        int i, flag;

	flag = 0;
	me = this_object();
        if (objectp(obj = query_last_damage_from()))
		obj->set_temp("kill_xuanfeng", 1);
	else
		return;
	
	if (obj->query_temp("kill_chaofeng")) 
	{
		obj->set("kill_th_traitor", 1);
		flag = 1;
	}

        if (flag) 
	        message_vision(HIR"陈玄风惨嚎一声，道：贼婆娘，我陪你来了！！！\n"NOR, this_object());
	else 
	        message_vision(HIR"陈玄风惨嚎一声，道：贼婆娘，给我报仇！！！\n"NOR, this_object());
        
	::die();
}
