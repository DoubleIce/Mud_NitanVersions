// /kungfu/class/xueshan/guoshi.c  ���Ʋֹ�ʦ
// by secret

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xueshan.h"

string ask_for_join();

void create()
{
        set_name("���Ʋֹ�ʦ", ({ "gongtangcang guoshi", "guoshi" }));
        set("long",@LONG
���Ʋֹ�ʦ�Ǵ������е�λ�ϸߵ����
����һ����ɫ���ģ�ͷ��ɮñ��
LONG
        );
        set("title", HIY "������" NOR);
        set("nickname", HIG "��ʦ" NOR);
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 24);
        set("int", 28);
        set("con", 26);
        set("dex", 25);

        set("max_qi", 1500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 20);
        set("level", 15);
        set("combat_exp", 120000);

        set_skill("lamaism", 1200);
        set_skill("literate", 50);
        set_skill("force", 100);
        set_skill("mizong-neigong", 100);
        set_skill("dodge", 100);
        set_skill("shenkong-xing", 80);
        set_skill("parry", 70);
        set_skill("staff", 80);
        set_skill("xiangmo-chu", 80 );
        set_skill("sword",50);
        set_skill("mingwang-jian",40);
        set_skill("cuff", 90);
        set_skill("yujiamu-quan", 80);
	set_skill("hand", 90);
	set_skill("dashou-yin", 90);
	set_skill("martial-cognize", 60);

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xiangmo-chu");
        map_skill("staff", "xiangmo-chu");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
	prepare_skill("hand", "dashou-yin");

        create_family("������", 4, "������");
        set("class", "bonze");

        set("inquiry",([
                "���"  : (: ask_for_join :),
                "����"  : (: ask_for_join :),
        ]));

        set("master_ob", 3);
	setup();

        carry_object("/d/shaolin/obj/chanzhang")->wield();
        carry_object("/d/xueshan/obj/c-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",100);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
 
        if ((string)ob->query("gender") != "����")
	{
                command("say ��ϰ�����ڹ���Ҫ����֮�塣");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "������ذɣ�");
                return;
        }

        if ((string)ob->query("class") != "bonze")
	{
                command("say �ҷ��ŵ����������ࡣ");
                ob->set_temp("pending/join_bonze", 1);
                command("say ʩ������������ҷ������(kneel)�ܽ䡣\n");
                return;
        }

        if ((string)ob->query("family/family_name") != "������")
	{
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�ȷǱ��µ��ӣ�������ذɣ�");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 40)
	{
                command("say ���Ҵ����£���ϰ�����ķ�����Ҫ�ġ�");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
                return;
        }

        command("say �ã��ʹ���һЩ�书�ɣ�");
        command("recruit " + ob->query("id"));

        ob->set("title",HIY "����" NOR);
}

void init()
{
        add_action("do_kneel", "kneel");
	add_action("do_say", "say");
}

string ask_for_join()
{
	object me;

	me = this_player();

        if( (string)me->query("class")=="bonze" )
                return "�����ӷ� ���Ѿ��ǳ������ˣ��ιʸ�ƶɮ�������Ц��\n";

        if( (string)me->query("gender") != "����" )
                return "ʩ��������������ǿ�ϲ�ɺأ���ϧ����ֻ����ͽ��\n";

        me->set_temp("pending/join_bonze", 1);

        return "�����ӷ����գ����գ�ʩ�����������"
	       "�ҷ������(kneel)�ܽ䡣\n";
}

int do_kneel()
{
        object me = this_player();

        if (! me->query_temp("pending/join_bonze"))
                return 0;

        message_vision("$N˫�ֺ�ʮ�����������ع���������\n\n"
                       "$n������ƣ���$Nͷ�������Ħ���˼��£���"
		       "$N��ͷ��������ȥ��\n\n", me, this_object());

        me->set("class", "bonze");
        me->set("title",HIY "����" NOR);      

        command("smile");
        command("say �ã��ʹ���һЩ�书�ɣ�");
        command("recruit " + me->query("id"));

        return 1;
}

int do_say(string arg)
{

        object me = this_player();

	if (! arg || arg == "") return 0;

        if (arg == "���ֳ�ת")
	{
                me->move("/d/xueshan/guangchang");
                return 1;
	}
}
