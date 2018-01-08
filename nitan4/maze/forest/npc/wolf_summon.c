#include <ansi.h>
#include <combat.h>
inherit NPC;
void do_attack();
void create()
{
        string *names = ({"Ѫ��"}); 
        set_name( names[random(sizeof(names))], ({ "blood wolf","wolf"}));
        set("vendetta_mark","wolf");
        set("race", "Ұ��");
        set("gender", "����");
        set("age", 20);
        set("long", "����һֻ���µ�Ѫ�ǡ�\n");
      
        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("fle",50);
        set("resistance/qi",25);
        set("max_qi", 8000);
        set("max_jing", 3000);
        set("max_neili", 3000);
        set("attitude", "peaceful");
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
	        (: do_attack() :),
        }) ); 

        set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
        set("verbs", ({ "bite", "claw" }) ); 
        set("combat_exp", 3000000);
        set("bellicosity", 5 );
        
        set_temp("apply/attack", 200);
        set_temp("apply/dodge", 200);
        set_temp("apply/parry", 200);
        set_temp("apply/unarmed_damage", 80);
        setup();
        //carry_object(__DIR__"obj/wolf_meat");
} 

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("qi",300+random(300), me);
        victim->receive_wound("qi",200+random(200), me);
        message_combatd(HIW"\n$N"+HIW"������צ����$n"+HIW"��������һ��Ѫ���ܵ��˿ڣ�"NOR,me,victim);
        return;
}      

void do_attack() {
	object *enemies,enemy;
	string msg;
	int be_damaged,i;
	enemies = query_enemy();
	if (!enemies || sizeof(enemies)==0)
			return;
	enemy = enemies[random(sizeof(enemies))];
	msg = HIR"\n$NͻȻ���ܣ���$n���ʺ�ҧȥ��\n"NOR;
	message_combatd(msg,this_object(),enemy);
	if (random(atoi(count_div(query("combat_exp"),100)))*6>atoi(count_div(enemy->query("combat_exp"),100))) {
			msg = HIR"$n������������ҧ�����ţ�\n"NOR;
			message_combatd(msg,this_object(),enemy);
			enemy->receive_damage("qi",500+random(500));
			COMBAT_D->report_status(enemy);
	} else {
			msg = HIY"���Ǳ�$n�㿪�ˡ�\n"NOR;
			message_combatd(msg,this_object(),enemy);
	}
	
	
}