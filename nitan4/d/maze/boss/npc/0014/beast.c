#include <ansi.h>
inherit NPC;
string *first_name = ({ "��", "����"});
string *first_id = ({ "lei", "leiting"});
string *name_words = ({ "��", "��"});
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
		"QU&MODMP1"					:	1000,	// һ��������װ
		"QU&MODMP2"					:	200,	// ����������װ
		"QU&MODMP3"					:	10,	// ����������װ
		"QU&GENER1"					:	2000,	// �ͼ���ͨװ��
		"QU&GENER2"					:	300,	// �м���ͨװ��
		"QU&GENER3"					:	20,	// �߼���ͨװ��
	])
	);

	set_weight(500000);
	set("bonus", 150);
        setup();
        
        // init_npc(this_object(), 10, 9, 9, 100);
// �Զ�����NPC���Ժͼ��ܣ���һ���������롣
// ��һ������ΪNPC��OB
// �ڶ�������ΪNPC�����ɣ�0����1�ظ�2����3�¹�4ѩɽ5��ׯ6����7�޵׶�����Ϊ������������Ϊ�������
// ����������ΪNPC�ļ��ܣ���NPC�ĵȼ�����(1:50)��ȱʡ��0Ϊ������
// ���ĸ�����ΪNPC�����Ժ�״̬�ȼ�����NPC�ĵȼ����ã�ȱʡ��0Ϊ������
// ���������ΪNPC��ǿ�ȣ�ȱʡΪ100
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


