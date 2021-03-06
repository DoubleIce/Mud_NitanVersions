#include <ansi.h>
inherit NPC;
string *first_name = ({ "雷", "雷霆"});
string *first_id = ({ "lei", "leiting"});
string *name_words = ({ "妖", "怪"});
string *id_words = ({ "yao", "guai"});
int combatpower();

void create()
{
        string name;
        int i, j;
        
        i = random(sizeof(first_name));
        name = first_name[i];
        j = random(sizeof(name_words));
        name += name_words[j];

        set_name(name, ({ first_id[i]+" "+id_words[j] }) );
        random_name_color(this_object());
        
        set("age", 20);
        set("vrm_guard", 1);
	set("attitude", "aggressive");

	set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		(: combatpower :),
	}) );
	set("is_servitor", 1);
	set("killer_reward", 
		([
		"QU&MODMP1"					:	1000,	// 一级门派套装
		"QU&MODMP2"					:	200,	// 二级门派套装
		"QU&MODMP3"					:	10,	// 三级门派套装
		"QU&GENER1"					:	2000,	// 低级普通装备
		"QU&GENER2"					:	300,	// 中级普通装备
		"QU&GENER3"					:	20,	// 高级普通装备
	])
	);

	set_weight(500000);
	set("bonus", 150);
        setup();
        
        // init_npc(this_object(), 10, 9, 9, 100);
// 自动配置NPC属性和技能，第一个参数必须。
// 第一个参数为NPC的OB
// 第二个参数为NPC的门派，0普陀1地府2方寸3月宫4雪山5五庄6龙宫7无底洞其他为基本，不设置为随机门派
// 第三个参数为NPC的技能，按NPC的等级设置(1:50)，缺省或0为不设置
// 第四个参数为NPC的属性和状态等级，按NPC的等级设置，缺省或0为不设置
// 第五个参数为NPC的强度，缺省为100
}

int combatpower()
{
	switch (random(6))
	{
		case 0	:
			NPC_D->npc_random_powerup("receive_curing_jing_lv1", this_object());
        		break;
		case 1	:
			NPC_D->npc_random_powerup("receive_curing_qi_lv1", this_object());
        		break;
		case 2	:
			NPC_D->npc_random_powerup("receive_powerup_attack_lv1", this_object());
        		break;
		case 3	:
			NPC_D->npc_random_powerup("receive_powerup_armor_lv1", this_object());
        		break;
		case 4	:
			NPC_D->npc_random_powerup("receive_powerup_spells_lv1", this_object());
        		break;
		case 5	:
			NPC_D->npc_random_powerup("receive_powerup_neili_lv1", this_object());
        		break;
        	default:	
        		break;
	}
	return 1;
}

void unconcious()
{
	die();
}

void die()
{
        ::die();
}


