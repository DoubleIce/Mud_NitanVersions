// /job/japan/killer1.c
// by akuma 8:40 PM 8/3/2003

#include <ansi.h>
inherit NPC;

void create()
{
	int i;
	set_name("东瀛武士", ({ "dongying wushi", "dongyin", "wushi", "shi" }));
	set("gender", "男性");
	set("long", "　　来自于东瀛的武官，烧杀劫略无恶不作。\n");
	set("age", random(18) + 10);
        set("str", 20 + random(10));
        set("int", 20 + random(10));
        set("con", 20 + random(10));
        set("dex", 20 + random(10));
        create_family("武士道", 4, "武士");
	//shifu("东瀛武官");
	if (random(10)>6)i=60+random(30);
	else i=40-random(20);
	set("chat_chance_combat", i);
	set("chat_msg_combat", ({
		(: perform_action, "blade.slash" :),
		(: perform_action, "cuff.dao" :),
	}));
	setup();
	//if ( random(5) > 1 ) carry_object(BINGQI_D("blade"))->wield();
	//carry_object(MISC_D("cloth"))->wear();
	//carry_object(ARMOR_D("armor"))->wear();
	//carry_object(MISC_D("kuzi"))->wear();
	//carry_object(ARMOR_D("udwear/underwear"))->wear();
	add_money("silver", random(20) + 10);
	this_object()->start_call_out( (: call_other, this_object(), "dest", this_object() :), 300);
}

void init()
{
	object me, ob;

	::init();
	ob = this_object();

	if ( interactive(me = this_player()) && me->query_temp("japan/job") ) {
		message_vision(HIR "$N对$n说道：「グイス，プタ！」\n" NOR, ob, me);
		ob->kill_ob(me);
		me->fight_ob(ob);
		me->start_busy(1);
	}
}

int do_clone()
{
	int number;
	object ob = this_object();

	number = (int)ob->query("max");
	if ( number < 1 ) number = 300;
        /*
	ob->set_skill("cuff", number);
	ob->set_skill("dodge", number);
	ob->set_skill("force", number);
	ob->set_skill("parry", number);
	ob->set_skill("blade", number);
	ob->set_skill("kongshou-dao", number);
	ob->set_skill("renshu", number);
	ob->set_skill("wushi-dao", number);
	ob->map_skill("cuff","kongshou-dao");
	ob->map_skill("dodge","kongshou-dao");
	ob->map_skill("force","renshu");
	ob->map_skill("parry","kongshou-dao");
	ob->map_skill("blade","wushi-dao");
        prepare_skill("cuff", "kongshou-dao");
        */
	return 1;
}

void dest()
{
	object me = this_object();

	if ( !me ) return;

	command("emote 急急忙忙离开了。");
	destruct(me);
}

void die()
{
	int exp, i, pot;
	mapping reward;
	object corpse, *inv, me, victim = this_object();

	COMBAT_D->announce(this_object(), "dead");
	me = victim->query_temp("last_damage_from");

	if ( me->query_temp("japan/job") ) {
		reward = TASK_D->get_reward(me, 100, 1, 40 + random(20), me->query("job/japan_job"));
		exp = reward["exp_reward"];
		pot = reward["pot_reward"];
		me->add("combat_exp", exp);
		me->add("potential", pot);
		tell_object(me, MAG"杀敌有功，你获得了" + exp + "点实战经验，" + pot + "点潜能。\n"NOR);
		me->set_temp("japan/kill", 1);
	}
	corpse = new(CORPSE_OB);
	corpse->set_name( victim->name(1) + "的尸体", ({ "corpse" }) );
	corpse->set("age", victim->query("age"));
	corpse->set("gender", victim->query("gender"));
	corpse->set("victim_name", victim->name(1));
	corpse->set("victim_id", victim->query("id"));
	corpse->set("victim_user", userp(victim));
	corpse->set("victim_exp", victim->query("combat_exp"));
	corpse->set("victim_shen", victim->query("shen"));
	corpse->set("kill_by", victim->query_temp("last_damage_from"));
        corpse->set_weight( victim->query_weight() );
        corpse->set_max_encumbrance( victim->query_max_encumbrance() );
	victim->set_temp("die_by_from", corpse->query("kill_by"));

	if ( victim->query_temp("faint_by") ) corpse->set("kill_by", victim->query_temp("faint_by"));
	else corpse->set("kill_by", me);

	inv = all_inventory(victim);
	inv->owner_is_killed(me);
	inv -= ({ 0 });
	i = sizeof(inv);
	while( i-- ) {
		if ( (string)inv[i]->query("equipped")=="worn" ) {
			inv[i]->move(corpse);
			if ( !inv[i]->wear() ) inv[i]->move(environment(victim));
		}
		if ( inv[i]->query("embedded") ) {
			inv[i]->delete("embedded");
			inv[i]->move(corpse);
		}
		else inv[i]->move(corpse);
	}
	corpse->set("long", victim->long(1) + "然而，" + gender_pronoun(victim->query("gender")) + "已经死了，只剩下一具尸体静静地躺在这里。\n");
        corpse->move(environment(victim));
	destruct(victim);
}
