// wei.c

#include <ansi.h>;

inherit NPC;

void create()
{
	set_name("ΤС��", ({ "wei xiaobao", "wei", "xiaobao" }));
	set("title", HIC"�������Զ�󽫾�"HIY"һ��¹����"NOR);
	set("gender", "����");
	set("age", 18);
	set("str", 20);
	set("int", 30);
	set("con", 30);
	set("dex", 20);
	set("per", 28);
	set("long", 
"��λ���꽫��ͷ���춥�ӣ�������ӣ�ü����Ц����߯��
�⣬������ҡ���ȣ��������֮�������ֵ��ϴ󵶣�ٲȻ��
��֮��������Τ��С����Ҳ�����㿴��������������������
���Ц������ѧ����Ϸ���вܲٵ�ģ�������ʱ�̲�ס�ո�
Ȥ����һ�䣺������Ϊ�η�Ц����\n");
	set("combat_exp", 50000);
	set("shen_type", 1);
	set("attitude", "peaceful");
        set("max_qi", 2500);
        set("max_jing", 1000);
        set("neili", 500);
        set("max_neili", 500);
	set("jiali", 50);

        set_skill("force", 20);
        set_skill("parry", 20);
        set_skill("hand", 20);
        set_skill("dodge", 20);
        /*
        set_skill("shenxing-baibian", 20);
        set_skill("yunlong-shengong", 20);
        set_skill("qianye-shou", 90);

        map_skill("force", "yunlong-shengong");
        map_skill("parry", "qianye-shou");
        map_skill("dodge", "shenxing-baibian");
        map_skill("hand", "qianye-shou");
        prepare_skill("hand", "qianye-shou");
        */
        set("inquiry", ([
            "��ػ�"  : "���ң�\n",
            "�½���"  : "������ʦ����\n",
            "éʮ��"  : "������ʮ�˸�ë�氡������û���ɣ�\n",
            "��������": "��������ò���ʦ����\n",
            "Τ����"  : "�������������Խ��Խ���ˣ����ڸ���������ˣ�\n",
            "����"    : "�����һʵ�ʦ����\n",
            "С����"  : "�����һʵ�ʦ����\n",
            "С����"  : "������������ˣ������£�\n",
            "����"    : "��������ý��Ȣ�Ĵ����ţ�\n",
            "˫��"    : "����ʶ�����󹦸�ɣ��׸������\n",
            "����"    : "������������ô�������Ϻ鸣���죬���޸����죡\n",
            "����"    : "������������ô�������Ϻ鸣���죬���޸����죡\n",
            "����"    : "������������ô�������Ϻ鸣���죬���޸����죡\n",
            "�彣��"  : "������������ô�������Ϻ鸣���죬���޸����죡\n",
            "��������": "���ɧ��Ƥ���׺񲻼�˫������ò�������桢�书��
�����������ɲ������������洿�Ʋ����彣��������˹�Ĳ������ᣬ
����һ��֮���ߣ����������������ѣ�\n",
        ]) );

	setup();
	carry_object("/d/city/obj/cloth")->wear();
        if (! clonep(this_object()))
        {
                move("/d/city/lichunyuan");
                message_vision("$NЦ���������������ˣ������ˡ�\n", this_object());
                set("startroom", "/d/city/kedian");
        }
}

mixed accept_ask(object ob, string topic)
{
        object fob, *obs;

        if (topic == ob->query("id"))
        {
                command("laugh " + topic);
                return 1;
        }

        if (topic[0] > 160)
        {
                if (time() - ob->query_temp("ask_wei_time") < 2)
                {
                        tell_object(ob, HIY "ΤС������һ���۾������𳳣��������ǰɣ�����ô�������\n" NOR);
                        return 1;
                }
                
                ob->set_temp("ask_wei_time", time());
                obs = livings();
                obs = filter_array(obs, (: filter_color($1->name(1)) == $2 && environment($1) :), topic);
                if (sizeof(obs) > 4)
                {
                        obs = 0;
                        message_vision(CYN "$N" CYN "���������$n"
                                CYN "�����۾���������" + topic + "��������ֶ��ǣ�"
                                "�Լ������ң���\n" NOR, this_object(), ob);
                        return 1;
                } else
                if (sizeof(obs) > 0)
                {
                        obs = 0;
                        ob->set_temp("pending/ask_wei", topic);
                        /*
                        message_vision(CYN "$N" CYN "�ٺټ�Ц��������$n"
                                CYN "С��������û�����⣬������Ҫһ����"
                                "�𣬲����ۣ���\n" NOR, this_object(), ob);
                        */
                        tell_object(ob, CYN "ΤС���ٺټ�Ц����������"
                                        CYN "С��������û�����⣬������Ҫһ����"
                                        "�𣬲����ۣ���\n" NOR);
                        return 1;
                } else
                        return;
        }

        fob = find_player(topic);
        if (! fob || ! ob->visible(fob)) fob = find_living(topic);
        if (! fob || ! ob->visible(fob) || ! environment(fob))
                return;

        ob->set_temp("pending/ask_wei", topic);
        /*
        message_vision(CYN "$N" CYN "�ٺټ�Ц��������$n"
                       CYN "С��������û�����⣬������Ҫ10��"
                       "�����������ۣ���\n" NOR, this_object(), ob);
        */
        tell_object(ob, CYN "ΤС���ٺټ�Ц����������"
                        CYN "С��������û�����⣬������Ҫ10��"
                        "�����������ۣ���\n" NOR);
        return 1;
}

int accept_object(object me, object ob)
{
        string wid;

        if (clonep(this_object()))
        {
                command("hehe");
                command("say ������ΤС������ٰ�������");
                return 1;
        }

        if (! stringp(ob->query("money_id")))
        {
                switch (me->query_temp("wei_refused"))
                {
                case 0:
                        command("heihei");
                        command("say �������������Űɡ�");
                        me->set_temp("wei_refused", 1);
                        return 0;

                case 1:
                        message_vision("$N����һ�ţ���$n���˳�ȥ���������ʲô�ң�\n",
                                       this_object(), me);
                        break;

                case 2:
                        message_vision("$N����һ�ţ��ݺݵİ�$n���˳�ȥ��������������ң�\n",
                                       this_object(), me);
                        me->receive_damage("qi", 100);
                        me->receive_wound("qi", 10);
                        break;

                default:
                        message_vision("$N��ŭ��һ������ڣ��ͼ�$n��ֽƬһ�����˳�ȥ��\n",
                                       this_object(), me);
                        command("chat* heng " + me->query("id"));
                        me->unconcious();
                        break;
                }

                me->add_temp("wei_refused", 1);
                me->move("/d/city/nandajie2");
                message_vision("ֻ����ž����һ����$N�ݺݵ�ˤ���˵��ϡ�\n", me);
                return -1;
        }

        if (ob->value() < 500)
        {
                message_vision("$N�ӹ�$n�ݹ�ȥ��" + ob->name() +
                               "��������ü�����������Ǯ�����ˣ��㲻Ҫ�͸��Ұɣ�\n",
                               this_object(), me);
                destruct(ob);
                return 1;
        }

        me->delete_temp("wei_refused", 1);
        if (stringp(wid = me->query_temp("pending/ask_wei", 1)))
        {
                int    i;
                string msg;
                object fob, *obs;

                if (ob->value() < 1000 ||
                    (ob->value() < 10000 && wid[0] > 160))
                {
                        message_vision("$N��Цһ�������������Ǯ��"
                                       "�㻹�Ǵ�³�нŻ���ࡣ��\n",
                                       this_object());
                        return 0;
                }

                me->delete_temp("pending/ask_wei");

                if (wid[0] > 160)
                {
                        obs = livings();
                        obs = filter_array(obs, (: filter_color($1->name(1)) == $2 && environment($1) :) ,wid);
                        if (! sizeof(obs))
                        {
                                message_vision("$N����ͷ��$n����������... ��"
                                               "���һ���������Ϣ�أ���ô��ôһ���...��\n",
                                               this_object(), me);
                                return 0;
                        }
                        msg = " \n�ݿɿ���Ϣ����" + wid + "��һ����" + 
                              chinese_number(sizeof(obs)) + "���ˣ�\n";                     
                        for (i = 0; i < sizeof(obs); i++)
                                msg += obs[i]->name(1) + "(" + obs[i]->query("id") + ")" +
                                       "�ղ���" + environment(obs[i])->short() + "��\n";
                        destruct(ob);
                        obs = 0;
                        command("whisper " + me->query("id") + msg);
                        return 1;
                }
                                
                fob = find_player(wid);
                if (! fob || ! me->visible(fob)) fob = find_living(wid);
                if (! fob || ! me->visible(fob) || ! environment(fob))
                {
                        message_vision("$N����ͷ��$n����������... ��"
                                       "���һ���������Ϣ�أ���ô��ôһ���...��\n",
                                       this_object(), me);
                        return 0;
                }

                destruct(ob);
                command("whisper " + me->query("id") +
                        " �ݿɿ���Ϣ������˸ղ���" +
                        environment(fob)->short() + "��");
                return 1;
        }

        message_vision("$N�ֵúϲ�£�죬��æ�ӹ�" + ob->name() + 
                       "����ͷ�����Ķ�$n�����ã��ã�\n", this_object(), me); 

        destruct(ob);
        return 1;
}
