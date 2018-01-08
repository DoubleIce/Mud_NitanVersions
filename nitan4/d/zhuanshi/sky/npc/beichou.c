#include <ansi.h>
inherit NPC;

void create()
{
        set_name("����", ({ "bei chou", "bei", "chou", "xizi" }) );
        set("nickname", HIW "��Ϸ��" NOR);
        set("title", HIC "����̩��" NOR);
        set("gender", "����" );
        set("age", 68);
        set("long", HIC "����һ������Ϸ�Ӵ�����С��ͷ�����ü�\n"
                        "�����������һ�����ࡣ����ǵ���������\n"
                        "�ųơ�" HIR "���ͱ���" HIC "��Ϸ�ӱ���"
                        "\n" NOR);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 500);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 20000000);

        set_skill("dodge", 500);
        set_skill("unarmed", 500);
        set_skill("force", 500);
        set_skill("parry", 500);
        set_skill("sword", 500);
        set_skill("poison", 500);
        set_skill("medical", 500);
        set_skill("hand", 500);
        set_skill("strike", 500);
        set_skill("staff", 500);
        set_skill("finger", 500);
        set_skill("claw", 500);
        set_skill("blade", 500);
        set_skill("pixie-jian", 500);
        set_skill("literate", 500);
        set_skill("taoism", 500);
        set_skill("buddhism", 500);
        set_skill("jiuyang-shengong", 500);
        set_skill("lingbo-weibu", 500);
        set_skill("qiankun-danuoyi", 500);
        set_skill("xuanming-zhang", 500);
        set_skill("jiuyin-baiguzhao", 500);
        set_skill("dugu-jiujian", 500);
        set_skill("liumai-shenjian", 500);
        set_skill("qianzhu-wandushou", 500);
        set_skill("ranmu-daofa", 500);
        set_skill("dagou-bang", 500);
        set_skill("shaolin-yishu", 500);
        set_skill("wudu-qishu", 500);
        set_skill("throwing", 500);
        set_skill("mantian-xing", 500);
        set_skill("idle-force", 500);

        map_skill("unarmed", "pixie-jian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "liumai-shenjian");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");

        prepare_skill("finger", "liumai-shenjian");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({                
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),               
                (: perform_action, "hand.zhugu" :),  
                (: perform_action, "finger.zong" :),               
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),              
        }) );

        setup();
        carry_object("d/city/obj/cloth")->wear();
}