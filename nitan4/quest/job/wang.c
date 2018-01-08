#include <ansi.h>
inherit NPC;
int ask_job();
int ask_peichang();

void create()
{
        set_name("��Ԫ��", ({ "wang yuanba", "wang", "yuanba" }));
        set("nickname",HIY "��" NOR);
        set("gender", "����");
        set("age", 45);
        set("long", "�����Ǻպ�������ʦ������Ԫ�ԡ�\n");

        set("combat_exp", 300000);
        set("shen_type", 1);

        set("max_force", 500);
        set("force", 500);
        set("jiali", 10);

        set_skill("force", 40);
        set_skill("sword", 50);
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);

        set("inquiry", ([
                "�⳥" : (:ask_peichang:),
                "job" : (:ask_job:),
        ]) );


        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);

        setup();
        carry_object(__DIR__"obj/gangjian")->wield();
        carry_object(__DIR__"obj/jinduan")->wear();
}
int ask_job()
{
        object *uob;
        object me = this_player(), ob; 
        
        if (file_name(environment(this_object())) !="/d/changan/biaoju-dating") {
                command("shrug");
                command("whisper "+me->query("id")+" �����ھ֣����޷�������ʦ��");
                return 1;
                }                               

        if (count_lt(me->query("combat_exp"), 2500000)) {
                command("pat "+ me->query("id"));
                command("say "+ me->query("name")+"������������֣�������̫Σ�գ�����ȥ�ú������ɣ�");
                return 1;
                }
       
        if (count_gt(me->query("combat_exp"), 15000000)) {
                command("say "+ me->query("name")+"������������̫���ˣ�����С�ھֿ��벻�����ˣ�");
                return 1;
                }

        if (me->query("quest2/yunbiao")==1) {
                command("whisper "+me->query("id")+" �Ҳ��ǽ��㻤��һλ��ʦ���㲻������ͷ��������ʲô��");
                return 1;
                }
        uob = filter_array(users(), (: query_ip_name($1) == $(query_ip_name(me)) :));
        uob = filter_array(uob, (: objectp($1) && $1->query("quest2/yunbiao") :));
/*
        if (sizeof(uob) > 1)
        {
                me->start_busy(3);
                command("say �Բ��������IP���ڵ�ID̫���ˣ�");
                return 1;
        }
*/
        me->set("quest2/yunbiao",1);
        ob = new(__DIR__"biaotou");

        ob->set_temp("owner/id", me->query("id"));
        ob->set("combat_exp", me->query("combat_exp"));

        ob->set("max_qi",me->query("max_qi") * 5);
        ob->set("eff_qi",me->query("eff_qi") * 5);
        ob->set("qi", me->query("qi") * 5); 
        ob->set("max_jing",me->query("max_jing") * 5);
        ob->set("eff_jing",me->query("eff_jing") * 5);
        ob->set("jing", me->query("jing") * 5);
        ob->set("max_neili",me->query("max_neili"));
        ob->set("neili",me->query("neili"));
        ob->set("max_jingli",me->query("max_jingli"));
        ob->set("jingli",me->query("jingli"));
        ob->set("jiali",me->query("jiali"));
        ob->set_skill("force",me->query_skill("force"));
        ob->set_skill("dodge",me->query_skill("force"));
        ob->set_skill("parry",me->query_skill("force"));
        ob->set_skill("sword",me->query_skill("force"));
        ob->set_skill("taiji-quan",me->query_skill("unarmed"));
        ob->set_skill("tiyunzong",me->query_skill("unarmed"));
        ob->set_skill("taiji-shengong",me->query_skill("unarmed"));
        ob->set_skill("taiji-jian",me->query_skill("unarmed"));
        ob->map_skill("force", "taiji-shengong");
        ob->map_skill("sword", "taiji-jian");
        ob->map_skill("parry", "taiji-quan");
        ob->map_skill("dodge", "tiyunzong");

        if(random(2)==0)
        {
                command("whisper "+me->query("id")+" "+ RANK_D->query_respect(me) +"�������ã�����һ����Ҫ�˵��������ھ� ���� ����ͷ�����������С�");
                ob->set_temp("fuzhou",1);
        }  else
        {
                command("whisper "+me->query("id")+" " + RANK_D->query_respect(me) +"�������ã�����һ����Ҫ�˵�����������Ǯ�ۿ����С�");
                ob->set_temp("yangzhou",1);
        }
        ob->move(environment(me));
        command("whisper "+me->query("id")+" ���ͬ��λ��ʦһͬǰ���ɡ�");
//        command("chat "+ me->query("name") + "���Ϸ�������������·Ӣ�ۺ��ܸ��㱡�棬�����ա�");
        return 1;
}       

int ask_peichang()
{
        object me = this_player();
        object *biaotou;
        int kar, dot, i;
        mixed balance;

        kar = (20 + random(20));
        dot = (50 - random(kar)) * (50 - random(kar)) * 250;
        balance = me->query("balance");
        
        if (! me->query("quest2/yunbiao"))
        {
                command("? "+me->query("id"));
                command("tell "+me->query("id")+" ����û�ж��ڣ���̸�⳥��");
                return 1;
        }

        if (me->query("quest2/wait_time"))
        {
            if (time() - me->query("quest2/wait_time") < 300)
            {
                command("whisper "+me->query("id")+" ����⳥������û����ء�");
                return 1;
            }  else
            {
                command("whisper "+me->query("id")+" ������ȥ�ˣ��⳥������͸������ˡ�");
                me->set("quest2/yunbiao",0);
                me->set("quest2/wait_time",0);
                return 1;
            }
        }

#ifdef LONELY_IMPROVED
        if (count_lt(balance, dot)) {
#else
        if (balance < dot) {
#endif
                command("?");
                command("whisper "+me->query("id")+" ����Ҫ��" + chinese_number(dot / 100000) + "���ƽ����⳥���ǵ���ʧ��");
                }
        else {
                me->add("balance",-dot/10);
                command("nod");
                command("whisper "+me->query("id")+" �õģ����ȥ����Ϣ�ɣ�");
                me->set("quest2/wait_time", time());

                biaotou = children(__DIR__"biaotou");
                for ( i = 0; i < sizeof(biaotou); i++)
                {
                       if (biaotou[i]->query_temp("owner/id") == me->query("id"))
                               destruct(biaotou[i]);
                }

                call_out("cancel", 300);
                }
        return 1;
}

int cancel()
{
        object me = this_player();
        me->set("quest2/yunbiao",0);
        me->set("quest2/wait_time",0);
        command("tell " + me->query("id") + " ����⳥�����Ѿ������ˡ�");
}
