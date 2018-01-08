// This program is a part of NITAN MudLIB

inherit BOSS;

int checking(object me, object ob);
int fast_attack(object me, object ob);

void create()
{
        set_name("朝廷逃犯", ({ "chaoting taofan", "taofan" }));
        set("long", "从监狱中逃出的死囚，异常凶悍。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);
        
        set("max_qi", 500000);
        set("max_jing", 250000);
        set("neili", 1000000);
        set("max_neili", 1000);
        set("jiali", 2000);
        set("combat_exp", 15000000);
        set("level", 5);
        set("score", 5000);

        set_skill("blade", 150);
        set_skill("cuff", 150);
        set_skill("feiyan-huixiang", 150);
        set_skill("strike", 150);
        set_skill("hunyuan-zhang", 150);
        set_skill("cuff",150);
        set_skill("poyu-quan", 150);
        set_skill("force", 150);
        set_skill("zixia-shengong", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("sword", 150);
        set_skill("huashan-jianfa", 150);
        set_skill("literate", 150);
        map_skill("force", "zixia-shengong");
        map_skill("cuff", "poyu-quan");
        map_skill("strike", "huashan-zhangfa");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "huashan-jianfa");
        map_skill("sword", "huashan-jianfa");
        
        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");
        
        set_temp("apply/attack", 200);
        set_temp("apply/armor", 500);
        set_temp("apply/damage", 300);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/add_xuruo", 60);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);
        
        set("auto_perform", 1);
        set("bonus", 30000);
        set("killer_reward", ([ 
                "RA&RANDOM30"    :       20000,   // 低级普通装备 
                "RA&RANDOM40"    :       300,     // 低级普通装备 
                "FI&/clone/fam/skpaper/strike1"   :   5000,
                "FI&/clone/fam/skpaper/cuff1"   :   5000,
        ]));
        
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void init() 
{
        object me;

        ::init();
        if (interactive(me = this_player()) && !is_fighting()) 
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, me); 
        }
}

