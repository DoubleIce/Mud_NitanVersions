// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "mojiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

void create()
{
        set_name("��ʨ", ({"jin shi", "jin", "shi"}));
        set("title", "ħ�̳���");
        set("gender", "����");
        set("age", 52);
        set("shen_type", -1);
        set("long", "ħ���Ĵ���֮�ף��������߶�ߣ����߳������Ӵ��������ϣ��Ѿ������˵ء�\n"
                    "���ĺ��ӱ�������۸��������Ľ��Ⱥ��ӻ���������ȴ���ű��ĳ߳��Ľ�����\n"
                    "�ƽ����ɵĽ��������ڵ��ϣ�����˿�����ʵ��Ҳ�����Ǹ��ˡ�\n");
        set("attitude", "peaceful");

        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 10000);
        set("max_jing", 10000);
        set("neili", 130000);
        set("max_neili", 130000);
        set("jiali", 3000);

        set("combat_exp", 150000000);
        set("score", 0);

        set_skill("force", 480);
        set_skill("moshen-xinfa", 480);
        set_skill("chiyou-kuangzhanjue", 450);
        set_skill("dodge", 480);
        set_skill("moshen-bufa", 480);
        set_skill("jiutian-xiaoyaobu", 450);
        set_skill("strike", 480);
        set_skill("moshen-zhangfa", 480);
        set_skill("cuff", 480);
        set_skill("moshen-quanfa", 480);
        set_skill("sword", 480);
        set_skill("moshen-jianfa", 480);
        set_skill("jinshi-kuangjian", 450);
        set_skill("blade", 480);
        set_skill("moshen-daofa", 480);
        set_skill("parry", 450);
        set_skill("literate", 410);
        set_skill("medical", 400);
        set_skill("mojiao-medical", 400);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "jinshi-kuangjian");
        map_skill("blade", "moshen-daofa");
        map_skill("parry", "jinshi-kuangjian");

        prepare_skill("strike", "moshen-zhangfa");
        
        create_family("ħ��", 40, "����");
  
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({
                (: perform_action, "sword.kuang" :), 
                (: exert_function, "recover" :),
        }) );

        set_temp("apply/attack", 280);
        set_temp("apply/damage", 280);
        set_temp("apply/unarmed_damage", 280);
        set_temp("apply/armor", 280);
                        
        set("master_ob", 5);
	setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  return;

        if ((int)ob->query_skill("moshen-xinfa", 1) < 120) 
        {
                command("say ���̵��ڹ��ķ��㻹û���ã���Ҫ���¿๦���У�");
                return;
        }
        
        command("recruit " + ob->query("id"));
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jinshi-kuangjian/kuang",
                           "name"    : "��",
                           "sk1"     : "jinshi-kuangjian",
                           "lv1"     : 200,
                           "dodge"   : 200,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        default:
                return 0;
        }
}