#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("��Ӣ��", ({ "hua yingxiong", "hua", "yingxiong"}));
        set("long", "һ�����ε��������ӣ����ų����������ǻ�Ӣ�ۡ�\n"
                    "��˵��������ɷ���ǣ�һ��Ư����������ء�����\n"
                    "ϰ��һ����������������л�����������ܡ�����\n"
                    "ս���޵С�\n"); 
        set("nickname", HIW "�л�Ӣ��" NOR);
        set("title", HIY "����ʦ" NOR);
        set("gender", "����");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 40);

        set("max_qi", 20000);
        set("max_jing", 20000);
        set("max_neili", 20000);
        set("neili", 20000);
        set("jiali", 400);
        set("combat_exp", 20000000);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "sword.aojue" :),
                (: perform_action, "sword.jianqi" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_skill("dodge", 500);
        set_skill("strike", 500);
        set_skill("parry", 500);
        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("sword", 500);
        set_skill("siji-jianfa", 500);
        set_skill("china-aojue", 500);
        set_skill("idle-force", 500);
        set_skill("literate", 200);

        map_skill("force", "china-aojue");
        map_skill("sword", "china-aojue");
        map_skill("dodge", "china-aojue");
        map_skill("parry", "china-aojue");
        map_skill("strike", "china-aojue");
        map_skill("unarmed", "china-aojue");

        prepare_skill("strike", "china-aojue");       

        setup();

        carry_object(__DIR__"obj/cloth3")->wear();
        carry_object(__DIR__"obj/chijian")->wield();        
}

