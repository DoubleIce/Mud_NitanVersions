#include <ansi.h>

inherit "/d/maze/necropolis/necropolis_npc";
void do_bone_spirit();
void create()
{
        string *names = ({"����"}); 
        // set_name( names[random(sizeof(names))], ({ "skeleton lich","skeleton"}));
        set_name( names[random(sizeof(names))], ({ "skeleton lich" }));
        set("vendetta_mark","skeleton");
        set("long", "����һֻ��ͷ���ӡ�\n");
        set("title", HIB "(����)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("max_qi", 100000);
        set("max_jing", 105000);
        set("neili", 450000);
        set("max_neili", 450000);
        set("max_jingli", 50000);
        set("attitude", "peaceful");
        
        set("chat_chance", 1);
        set("chat_msg", ({
                "���ÿն����ۿ�����˸�ſ��µ�ӫ�⡣\n"
        }) ); 

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
	        (: do_bone_spirit() :),
        }) ); 
        set("death_msg",BLU"\n$Nɢ����һ�����ͷ��\n\n"NOR);
        set("combat_exp", 200000000);
        set("bellicosity", 5 );

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("unarmed", 120);
        set_skill("staff", 120);
        set_skill("parry", 120);        
        set_temp("apply/attack", 2000);
        set_temp("apply/parry", 1500);
        set_temp("apply/damage", 2000);

        setup();
        carry_object(__DIR__"obj/bone_staff")->wield();
} 

int is_undead() {
	return 1;
}

void do_bone_spirit() {
	object *enemies,enemy;
	int i,no_busy;
        if (! this_object()) return;

	message_vision(BLU"\n$Nɳ�Ƶ������������������������һ����ɢ����������Ϣ�Ĺ���\n\n"NOR,this_object());
	enemies = query_enemy();
	foreach(enemy in enemies) {
		if(!enemy)
			continue;
		i = random(5);
		if(i>=3)
			i=random(2);
		switch (i)
		{
		case(0):
		        message_vision(RED"һ����ɫ�������$N��ը������\n"NOR,enemy);
			enemy->receive_damage("qi",4000+random(4000),this_object());
			COMBAT_D->report_status(enemy);
			break;
		case(1):
		        message_vision(GRN"һ����ɫ����Χ��$Nת��һȦ��\n"NOR,enemy);
		        message_vision(GRN"$N��־���ģ������......\n"NOR,enemy);
			if(!enemy->is_busy())
			        enemy->start_busy(3);
			break;
		case(2):
		        message_vision(BLU"һ����ɫ����������Ϣ��������$N��ü�Ĵ���"NOR,enemy);
			enemy->unconcious();
			break;
		}
	}
        if (this_object() && ! this_object()->is_busy())
	        this_object()->start_busy(2);
}