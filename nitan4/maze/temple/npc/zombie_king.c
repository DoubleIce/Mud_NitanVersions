#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void do_summon();
void set_from_me(object me);
void create()
{
        ::create();
        set_name( "ǧ��������", ({ "zombie king" }));
        set("vendetta_mark","zombie");
        set("long", "ǧ���ë�����Ӱ����������ÿ��¡�����\n");
        set("title", HIB "(����)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 50); 
        set("int", 50);
        set("max_qi", 25000000);
        set("eff_qi", 25000000);
        set("max_jing", 15000000);
        set("eff_jing", 15000000);
        set("neili", 550000);
        set("max_neili", 550000);
        set("max_jingli", 80000);
        set("attitude", "peaceful");
        set("combat_exp", 2000000000);
        
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: do_summon() :),
        }) ); 

        set("bellicosity", 5 );
        set("death_msg",RED"\n$N������һ̲Ѫˮ��\n\n"NOR);
        set("clear_fuben", 1);
        
        set("auto_perform", 1);
        set_temp("apply/attack", 15000);
        set_temp("apply/parry", 15000);
        set_temp("apply/unarmed_damage", 8000);
        set_temp("apply/add_xuruo", 80);
        set_temp("apply/reduce_damage", 90);
        set_temp("apply/reduce_busy", 30);
        set_temp("apply/add_busy", 15);

        set("bonus", 100000);
        set("killer_reward", ([
                "RA&RANDOM90"                    :       10000,  // �߼���ͨװ����ʯ
                "TY&gem6"                    :       100000,  // �߼���ͨװ����ʯ
        ]));
        setup();
        add_money("gold", 300 + random(500));
} 

void init()
{
        object me;

        ::init();
        if (! interactive(me = this_player()) || 
            this_object()->is_fighting())
                return;
                
        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void set_from_me(object me)
{
        mapping my;
        
        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        set("jiali", query_skill("force") / 2);
}

void do_summon() 
{
        object zombie,me,enemy,*enemies;
        object *obs;
        me = this_object();
        
        obs = all_inventory(environment(me)); 
        obs = filter_array(obs, (: $1->query("id") == "zombie" :) ); 
        if( sizeof(obs) > 5 ) return; 
        message_vision(HIM "\n$N�����ɺ�����Χ�Ľ�ʬ��Ӧ��������\n" NOR, me);   
        zombie = new(__DIR__"zombie_lord");
        zombie->move(environment(me));
        enemies = me->query_enemy();
        foreach(enemy in enemies) {
                if( !userp(enemy) ) continue; 
                zombie->kill_ob(enemy);
                enemy->kill_ob(zombie);
        } 
        message_vision( "\n\n$N��ݺݵ�����������\n" , zombie);
        call_out("leave",30+random(10),zombie);
        if( !this_object()->is_busy() )
                this_object()->start_busy(3);
}

void leave(object zombie){
        if( !zombie || zombie->is_fighting() ) return;
        message_vision("\n$N��ʧ�ˡ�\n",zombie);
        destruct(zombie);
}

