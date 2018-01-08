// This program is a part of NITAN MudLIB

inherit BOSS;

int checking(object me, object ob);
int fast_attack(object me, object ob);

void create()
{
        set_name("剑冢刀客", ({ "jianzhong daoke", "daoke" }));
        set("long", "隐居在剑冢的被仇家追杀的刀客，见人便杀。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);
        
        set("max_qi", 800000);
        set("max_jing", 500000);
        set("neili", 2000000);
        set("max_neili", 1000);
        set("jiali", 2000);
        set("combat_exp", 15000000);
        set("level", 5);
        set("score", 5000);

        set_skill("force", 280);
        set_skill("dodge", 300);
        set_skill("parry", 280);
        set_skill("luan-blade", 300);
        set_skill("blade", 300);
        set_skill("unarmed", 280);
        set_skill("literate", 250);
        set_skill("ding-dodge", 300);
        set_skill("ding-force", 280);

        map_skill("dodge", "ding-dodge");
        map_skill("force", "ding-force");
        map_skill("parry", "luan-blade");
        map_skill("blade", "luan-blade");
        
        set_temp("apply/attack", 400);
        set_temp("apply/armor", 1000);
        set_temp("apply/damage", 600);
        set_temp("apply/unarmed_damage", 600);
        set_temp("apply/add_xuruo", 60);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);
        
        set("auto_perform", 1);
        set("bonus", 40000);
        set("killer_reward", ([ 
                "RA&RANDOM50"    :       20000,   // 低级普通装备 
                "RA&RANDOM60"    :       300,     // 低级普通装备 
                "FI&/clone/fam/skpaper/blade1"   :   5000,
                "FI&/clone/fam/skpaper/sword1"   :   5000,
                "MO&A0000"       :       300,
                "MO&A0001"       :       300,
                "MO&A0002"       :       300,
                "MO&A0003"       :       300,
                "MO&A0004"       :       300,
                "MO&A0005"       :       300,
                
        ]));
        
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void init() 
{
        object me;

        ::init();
        if (interactive(me = this_player()) && !is_fighting()) 
        {
                remove_call_out("kill_ob");
                remove_call_out("checking");
                call_out("kill_ob", 0, me); 
                call_out("checking", 1, this_object(), me);
        }
}

int checking(object me, object ob)
{
        int my_max_qi;
        object weapon;

        if (! objectp(me) || ! objectp(ob)) 
                return 0;
        
        my_max_qi = me->query("max_qi");
        
        if (me->is_fighting()) 
        {
                if (! me->query_temp("attack_pending") 
                &&  objectp(weapon = me->query_temp("weapon"))) 
                {
                        me->set_temp("attack_pending", 1);
                        remove_call_out("fast_attack");
                        call_out("fast_attack", 2, me, ob);
                }
                
                return 1;
        } else
        if (me->query("attack_pending") == 1) 
        {
                me->delete_temp("attack_pending");
                remove_call_out("fast_attack");
                return 1;
        }

        return 1;
}

int fast_attack(object me, object ob)
{
        int i, num;

        me->delete_temp("attack_pending");
        num = random(2) + 5;

        message_vision("剑冢刀客大喊一声，使出其快刀绝技疯狂般向$N连劈了" + chinese_number(num) + "刀。\n", ob);

        for (i = 1; i < num + 1; i++) {
                if (! me->is_fighting(ob)) break;
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"));
        }

        return 1;
}

