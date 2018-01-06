// questd.c ����������ػ����� 
// ����ʦ�������������ϵͳע������(SYSREG_QUEST) 
  
#include <ansi.h>
#include <quest.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

// �����ṩ���ⲿ���õĽӿں��� 
varargs public void bonus(object who, mapping b, int flag);
public void   delay_bonus(object who, mapping b);
public mixed  accept_ask(object me, object who, string topic); 
public void   set_information(object qob, string key, mixed info); 
public mixed  query_information(object qob, string key); 
public void   remove_information(object qob, string key); 
public void   remove_all_information(object qob); 
public string generate_information(object knower, object who, string topic); 
public void   start_all_quest(); 

// �����������б�
mapping mlist = ([
        "ؤ��"     : CLASS_D("gaibang")  + "/hong.c",
        "ȫ���"   : CLASS_D("quanzhen") + "/ma.c",
        "������"   : CLASS_D("emei")     + "/miejue.c",
        "��Ĺ��"   : CLASS_D("gumu")     + "/longnv.c",
        "��ɽ��"   : CLASS_D("huashan")  + "/yue-buqun.c",
        "���չ�"   : CLASS_D("lingjiu")  + "/xuzhu.c",
        "������"   : CLASS_D("shaolin")  + "/xuan-ci.c",
        "������"   : CLASS_D("shenlong") + "/hong.c",
        "�һ���"   : CLASS_D("taohua")   + "/huang.c",
        "�䵱��"   : CLASS_D("wudang")   + "/zhang.c",
        "��ң��"   : CLASS_D("xiaoyao")  + "/suxingh.c",
        "������"   : CLASS_D("xingxiu")  + "/ding.c",
        "Ѫ����"   : CLASS_D("xuedao")   + "/laozu.c",
        "ѩɽ��"   : CLASS_D("xueshan")  + "/jiumozhi.c",
        "������"   : CLASS_D("yunlong")  + "/chen.c",
        "���ϻ���" : CLASS_D("duan")     + "/duanzc.c",
        "Ľ������" : CLASS_D("murong")   + "/murongbo.c",
        "ŷ������" : CLASS_D("ouyang")   + "/ouyangfeng.c",
        "�������" : CLASS_D("hu")       + "/hufei.c",
        "��ɽ����" : CLASS_D("huashan")  + "/feng-buping.c",
]);

void create() 
{ 
        seteuid(getuid()); 
        set("channel_id", "������"); 
        set_heart_beat(900); 
        call_out("collect_all_quest_information", 1); 
} 
        
#define ONE_DAY                 (86400 / 365) 
#define MAX_QUEST_LEVEL         3 

private void skill_bonus(object me, object who)
{
	array sk_list = ({
		"qishang-quan",
		"qishang-quan",
		"qishang-quan",
		"qishang-quan",
		"zhuihun-jian",
		"zhuihun-jian",
		"zhuihun-jian",
		"zhuihun-jian",
		"baihua-quan",
		"baihua-quan",
		"baihua-quan",
		"baihua-quan",
		"sougu",
		"sougu",
		"sougu",
		"hanbing-mianzhang",
		"hanbing-mianzhang",
		"hanbing-mianzhang",
		"xuanming-zhang",
		"shenzhaojing",
	});
	string sk;

	sk = sk_list[random(sizeof(sk_list))];
	if (who->query_skill(sk, 1) > 0)
		return;

	if (! SKILL_D(sk)->valid_learn(who))
	{
		message_vision("$n����Ķ�$NЦ��Ц������������������" +
		               me->query("family/family_name") +
		               "��ٮٮ�ߣ�������о���" +
		               HIY + to_chinese(sk) + NOR
		               "��\n�����ĵã�ֻ��ϧ�������в�����"
			       "�������а�����ˣ����ˡ���\n",
		               who, me);
		return;
	}

	message_vision("$n����Ķ�$NЦ��Ц������������������" +
		       me->query("family/family_name") +
		       "��ٮٮ�ߣ�����������о���" +
		       HIY + to_chinese(sk) + NOR
		       "��\n�����ĵã��ʹ���һЩ����ɣ���\n",
		       who, me);
	who->set_skill(sk, 50);
}
          
void special_bonus(object me, object who, mixed arg) 
{ 
        // ������� 
        array ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/hantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
                "/clone/enchase/redgem",
                "/clone/enchase/yelgem",
                "/clone/enchase/blugem",
                "/clone/enchase/grngem",
                "/clone/enchase/maggem",
        });
        
        object ob; 

        /*
        message_vision("$n��$N΢΢һЦ�������ɵò���������"
                       "�ˣ������������е㶫���������ȥ�ɡ�\n",
                       who, me);
        */

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(who, 1);
        tell_object(who, HIM "������һ" + ob->query("unit") + ob->name() +
                        HIM "��\n" NOR);
}        

void money_bonus(object me, object who, mixed arg)
{
        array ob_list = ({
                "/clone/gift/jinkuai",
                "/clone/gift/jintiao",
                "/clone/gift/xiaoyuanbao",
                "/clone/gift/dayuanbao",
                "/clone/gift/jinding",
        });
        object ob;

        /*
        message_vision("$n��$N΢΢һЦ�������ɵò���������"
                       "�ˣ����߽��������и��࿪֧Ӧ�꣬������Щ���ӣ������ȥ�ɡ�\n",
                       who, me);
        */

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);

        ob->move(who,1);

        tell_object(who, HIM "������һ" + ob->query("unit") + ob->name() +
                        HIM "��\n" NOR);
}
         
varargs public void bonus(object who, mapping b, int flag)
{ 
        int exp;                // �����ľ��� 
        mixed pot;              // ������Ǳ�� 
        mixed mar;              // ������ʵս���
        int shen;               // �������� 
        int score;              // �����Ľ������� 
        int weiwang;            // �����Ľ������� 
        int gongxian;           // ���������ɹ��� 
        mixed pot_limit;        // Ǳ�ܵĽ��� 
        mixed mar_limit;        // ʵս���Ľ���
        int percent;            // ��������Ч�ٷֱ� 
        string msg;             // ������������Ϣ 
        int t;
        int quest_times;
          
        quest_times = "/adm/daemons/actiond"->query_action("quest_reward");
        // ��ý����İٷֱ� 
        percent = b["percent"]; 
        if (percent < 1 || percent > 100) 
                percent = 100; 
        
        exp = b["exp"] * percent / 100; 
        pot = b["pot"] * percent / 100; 
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100; 
        score = b["score"] * percent / 100; 
        weiwang = b["weiwang"] * percent / 100; 
        gongxian = b["gongxian"] * percent / 100; 

        if (who->query("special_skill/intellect") && random(2))
        {
                exp += exp / 5;
                pot += pot / 5;
        }

        if (quest_times)
        {
                exp = exp*quest_times;
                pot = pot*quest_times;
                mar = mar*quest_times;
        }
                
#ifdef DB_SAVE
        t = localtime(time())[2];
        // ��Ա˫������
        if (MEMBER_D->is_valid_member(who->query("id")) &&
            t >= 20 && t < 24 || 
            who->query("time_reward/quest"))
        {
                exp *= 2;
                pot *= 2;
                mar *= 2;
        }
#endif

        if (! flag)
        {
                pot_limit = count_sub(who->query_potential_limit(), who->query("potential"));
                if (count_gt(pot, pot_limit)) pot = pot_limit;
                if (count_lt(pot, 1)) pot = 0;

                mar_limit = count_sub(who->query_experience_limit(), who->query("experience")); 
                if (count_gt(mar, mar_limit)) mar = mar_limit; 
                if (count_lt(mar, 1)) mar = 0; 
        } else
        {
                if (count_lt(who->query_potential_limit(), who->query("potential")))
                        pot = 1 + random(2);

                if (count_lt(who->query_experience_limit(), who->query("experience"))) 
                        mar = 1;
        }
        
        // ������ʾ��Ϣ 
        if (stringp(msg = b["prompt"])) 
                msg = HIC + msg + HIG "��������"; 
        else 
                msg = HIC "ͨ����ζ�����������"; 
        
        if (exp > 0) msg += chinese_number(exp) + "�㾭�顢"; 
        if (count_gt(pot, 0)) msg += chinese_number(pot) + "��Ǳ�ܡ�";
        if (count_gt(mar, 0)) msg += chinese_number(mar) + "��ʵս��ᡢ";
        if (shen > 0) msg += chinese_number(shen) + "������"; 
        if (shen < 0) msg += chinese_number(-shen) + "�㸺��"; 
        if (score > 0) msg += chinese_number(score) + "�㽭��������"; 
        if (weiwang > 0) msg += chinese_number(weiwang) + "��������"; 
        if (gongxian > 0) msg += chinese_number(gongxian) + "�����ɹ�����"; 
        
        msg += "�����õ���������\n" NOR; 
        tell_object(who, sort_msg(msg)); 
        
        // bonus 
        who->add("combat_exp", exp); 
        who->add("potential", pot); 
        who->add("experience", mar);
        who->add("shen", shen); 
        who->add("score", score); 
        who->add("weiwang", weiwang); 
        who->add("family/gongji", gongxian); 
} 

// �ӳٽ�������ʱ�����������ʱ��Ӧ������ĳЩ�¼������Ժ�
// �����ڸ��¼�����ʱ���뽱����������д�������Խ������ɵ�
// �ط����¼����ڷ�����ʱ�򣬵���Ҫ����ҿ����������¼�����
// �Ժ󡣱���ɱ�ˣ���������ʱ����뽱�����������ģ�������ϣ
// ������ڿ���NPC ��������Ϣ�Ժ�ſ�����������Ϣ����ʱ���
// ��delay_bonus�ˡ�
public void delay_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "bonus", who, b :), 1);
}

public mixed accept_ask(object me, object who, string topic)
{
        string my_fam;

        my_fam = me->query("family/family_name");

        if (topic == "����" || topic == "����" ||
            topic == "����")
        {
                if (my_fam != who->query("family/family_name"))
                        return "����˭��������ʲô����ô��";

                if (who->query("out_family"))
                        return "ȥ�ɣ�" + who->name(1) + "������Ϊ֮��";

                if (count_lt(who->query("combat_exp"), 50000))
                {
                        message_sort(CYN "$N" CYN "̾��һ���������˿�$n"
                                     CYN "����������书��������̫�ã�������"
                                     "�úö����ɣ���\n", me, who);
                        return 1;
                }

                if (who->query("score") < 100)
                {
                        message_sort(CYN "$N" CYN "�ڰ��ֵ�������Ľ���"
                                     "����̫�٣����ڲ�������������߽�������\n",
                                     me, who);
                        return 1;
                }

                who->set("out_family", 1);
                if (me->is_good())
                {
                        message_sort(HIY "$N" HIY "��$n" HIY "��ο�ĵ���"
                                     "��ͷ����������������" + my_fam +
                                     "�ֳ���һλ�˲Ű������ס�ˣ��ұ���"
                                     "�ˣ��мɲ��ɺ���������Ҫ����������"
                                     "��֮�£���\n" NOR, me, who);
                } else
                if (me->is_bad())
                {
                        message_sort(HIR "$N" HIR "��$n" HIR "������Ц��"
                                     "�����ã��ã�����Գ�ȥ���߿����ˣ�"
                                     "����Щ������ν����֮���ɲ�Ҫ����"
                                     "ȥ�ɣ���\n" NOR, me, who);
                } else
                {
                        message_sort(HIY "$N" HIY "��$n" HIY "����������"
                                     "�Ժ������߽��������ǹ���һ�ˣ��ǵ�"
                                     "Ҫ����ǰ�������ɿ����Դ��м��ˣ�"
                                     "ȥ�ɣ���\n" NOR, me, who);
                }

                message_sort("$N����һ��С����������$n��������������߽�"
                             "�������ɽ��������������㶼���Լ�¼����"
                             "����ͼ���ϣ����ɲο����������Ҳ����Щ����"
                             "����\n", me, who);

                tell_object(me, HIY"������ʦ��������ĵ�ͼ�ᣬ��μ���"
                            "��(HELP QUEST)��\n��ø���ϸ����Ϣ��\n" NOR);

                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + who->name(1) + "�Ѿ���ʼ����������");
                return 1;
        }
}
        
// ��ȡ���� 
// ���Ŀǰ����Э�����ˣ�������ȡ���� 
public int ask_quest(object me, object who) 
{ 
        string fam;             // ME��������Ϣ
        object ob;              // �����ص�ĳЩ���������
        mapping q;              // WHO������
        object aob;             // WHOĿǰ����Э���Ķ���
        mixed exp;              // WHO�ľ���
        int t;                  // ��������ʱ��ı���
        int level;              // QUEST�ĵȼ�
        string place;

        message_vision("$n��$N�����й�����������\n", me, who);
        
        fam = me->query("family/family_name");
        if (who->query("family/family_name") != fam)
        {
                message_vision("$N�ɴ��۾�����$n�����������ֲ�������" + fam +
                               "�ģ�����ʲô�ң���\n", me, who);
                return 1;
        }

        q = who->query("quest");
        if (mapp(q)) 
        { 
                if (q["freequest"] > 0) 
                { 
                        message_vision(CYN "$N" CYN "��$n" CYN "˵������������" 
                                       "ʱҲûʲô���飬�㻹���Լ�����һ��ʱ��" 
                                       "�ɡ�\n" NOR, me, who); 
                        tell_object(who, HIY "��ͻȻ�뵽�����ڽ�����ֵ���ң���" 
                                         "���Ĵ��߷ã�Ҳ�������Լ��ľ�������" 
                                         "��\n" NOR); 
                        return 1; 
                } 
        
                if (q["master_id"] && q["master_id"] != me->query("id")) 
                { 
                        message_vision(CYN "$N" CYN "���˿�$n" CYN "��" 
                                       "����һ����û�����$n" CYN "��\n" 
                                       NOR, me, who); 
                        return 1; 
                } 
        
                switch (q["type"]) 
                { 
                case "kill": 
                        message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����" 
                                       "��" + CHINESE_D->chinese_monthday(q["limit"]) + 
                                       "֮ǰɱ��" NOR + HIR + q["name"] + "(" + q["id"] + 
                                       ")" + NOR + CYN "����������" + 
                                       CHINESE_D->chinese_monthday(time()) + 
                                       "��������ͷ�أ�\n" NOR, me, who); 
                        break;
        
                case "letter": 
                        message_vision(CYN "$N" CYN "һ��ŭ�ݶ�$n" CYN "�����Ҳ�����" 
                                       "��" + CHINESE_D->chinese_monthday(q["limit"]) + 
                                       "֮ǰ�����͵�" NOR + HIC + q["name"] + "(" + q["id"] +
                                       ")" + NOR + CYN "�������������" + 
                                       CHINESE_D->chinese_monthday(time()) + 
                                       "�����Ļ�ִ�أ�\n" NOR, me, who); 
                        break; 
        
                } 
                return 1;
        } 
     
        if (me->query("eff_qi") * 2 < me->query("max_qi") || 
            me->query("qi") * 2 < me->query("max_qi")) 
        { 
                message_vision(HIC "$N" HIC "�����ؿڣ�һ���ǳ�ʹ������ӣ������" 
                               "����Ȼû������ȥ��\n" NOR, me); 
                return 1; 
        } 
        
        exp = who->query("combat_exp"); 
        if (count_lt(exp, 10000)) 
        { 
                message_vision(CYN "$N" CYN "̾��һ��������$n" CYN "���������ǵ�ˮƽ��" 
                               "��ʵ��û������������\n" NOR, me, who); 
                return 1; 
        } 
        
        if (objectp(aob = who->query_temp("quest/assist"))) 
        { 
                message_vision(CYN "$N" CYN "���˿�$n" CYN "����������˵�㲻�ǰ�" NOR + 
                               HIY + aob->name(1) + NOR + CYN "ȥ��ô���Ȱ�����" 
                               "��˵�ɣ�\n" NOR, me, who); 
                return 1; 
        } 
        
        if (count_lt(exp, 50000)) 
        { 
                object letter; 
        
                if (who->query("score") < 20) 
                { 
                        message_vision(CYN "$N" CYN "ҡҡͷ����$n" CYN "������ϧ��" 
                                       "�Ľ�������̫���Ȼ�һ�������������ͷ���" 
                                       "��\n" NOR, me, who); 
                        return 1; 
                } 
        
                ob = new(CLASS_D("generate") + "/receiver.c"); 
                NPC_D->place_npc(ob, ({ "����һ��", "����", "���޺�", "��ɽ",
					"����ɽ", "����" }));
                NPC_D->set_from_me(ob, me, 120); 
        
                NPC_D->random_move(ob); 
                NPC_D->random_move(ob); 
                NPC_D->random_move(ob); 
            
                place = ob->query("place"); 
        
                letter = new("/clone/misc/letter"); 
                letter->set("long", "����һ��" + me->name() + "д��" + ob->name() + 
                                    "���ױ��ź���\n"); 
                letter->set("send_from", me->query("id"));
                letter->set("send_to", ob->query("id"));
                letter->set("send_from_name", me->name());
                letter->move(me);
        
                message_vision(CYN "$N" CYN "��$n" CYN "�������������ҽ���" NOR + 
                               HIC + ob->name() + "(" + ob->query("id") + ")" + NOR + 
                               CYN "���У�������Ӧ����" + place + "��Ȼ��ѻ�ִ���������ң�\n" NOR, 
                               me, who); 
        
                me->force_me("give letter to " + who->query("id")); 
                who->set("quest/info", letter->query("id")); 
                who->set("quest/type", "letter"); 
        } else 
        {         
                if (! who->query("out_family"))
                {
                        message_sort(CYN "$N" CYN "�ڰ��֣���$n" CYN "����������" 
                                      "���ﵹ����һЩ���飬�����������������ʱ��" 
                                      "����˵�ɣ�\n" NOR, me, who); 
                        return 1; 
                } 
        
                if (who->query("score") < 2000)
                {
                        message_sort(CYN "$N" CYN "̾��һ��������$n" CYN "�������㻹"
                                     "���ڽ����϶���������������һЩ������˵�ɣ�����"
                                     "�Ҷ��㻹�������ģ���\n" NOR, me, who);
                        return 1;
                }
        
                if (who->query("weiwang") < 20) 
                { 
                        message_sort(CYN "$N" CYN "���˿�$n" CYN "��̾����������" 
                                     "������һ����ͷ��û�У���û�����İ����񽻸�" 
                                     "�㡣\n" NOR, me, who); 
                        tell_object(who, HIY "�������ǵļ�ǿ�Լ��Ľ����������С�\n" NOR); 
                        return 1; 
                } 
                
                if (who->is_bad() && me->is_good())
                {
                        message_sort(CYN "$N" CYN "��ŭ�������д������Ȼ�Ѿ���" 
                                     "����;�����������ң�\n" NOR, me, who); 
                        return 1; 
                } 
        
                if (who->is_good() && me->is_bad())
                {
                        message_sort(CYN "$N" CYN "��ŭ�������д����ż��첻����" 
                                     "���ȻҲѧ����ʼ������ˣ�����ҹ���\n" 
                                     NOR, me, who); 
                        return 1; 
                } 
        
                level = who->query_temp("quest/next_level");
                if (level < 0 || level > MAX_QUEST_LEVEL)
                        level = 0;

                ob = new(CLASS_D("generate") + "/killed.c");
                NPC_D->place_npc(ob, count_lt(who->query("combat_exp"), 500000)  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                     count_lt(who->query("combat_exp"), 800000) ? ({ "����һ��", "����ɽ", "����" }) : 0);
                NPC_D->set_from_me(ob, who, 120); 
                
                ob->add_temp("apply/attack", ob->query_skill("force") *
					     (level - 1) / 15);
                ob->add_temp("apply/dodge", ob->query_skill("force") *
					    (level - 1) / 15);
                ob->add_temp("apply/parry", ob->query_skill("force") *
					    (level - 1) / 15);
                ob->add_temp("apply/damage", 5 + level * 7);
                ob->add_temp("apply/unarmed_damage", 5 + level * 7);
                ob->add_temp("apply/armor", 10 + level * 15);
                ob->set_temp("quester", who->query("id"));
                
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                
                place = ob->query("place");
        
                message("vision", WHT + me->name() + WHT "С���Ķ�" + who->name() + 
                        WHT "�Ը���ʲô��" + who->name() + 
                        WHT "һ������һ�߲�ס�ĵ�ͷ��\n" NOR, 
                        environment(who), ({ who })); 
                        
                if (me->is_good()) 
                { 
                        ob->set("shen", -20000); 
                        if (me->query("family/family_name") == "������") 
                                tell_object(who, CYN + me->name() + CYN "���������" 
                                                 "Ȼ���ǳ������Դȱ�Ϊ�������Ƕ��ڴ�" 
                                                 "�״��֮ͽҲ���ܷŹ���\n���" NOR + 
                                                 HIR + ob->name() + "(" + ob->query("id") + 
                                                 ")" + NOR + CYN "��" + place + "�����ˣ�"
                                                 "��ȥ�������ˣ���ͷ������\n" NOR); 
                        else 
                                tell_object(who, CYN + me->name() + CYN"�������" NOR 
                                                 + HIR + ob->name() + "(" + ob->query("id") + 
                                                 ")" + NOR + CYN "���" 
                                                 "�����ҽ��ᣬ�޶�������˵�����" 
                                                 "��" + place + "����ȥ����������ͷ��" 
                                                 "���ң�\n" NOR); 
                } else 
                if (me->is_bad()) 
                { 
                        ob->set("shen", 20000); 
                        tell_object(who, CYN + me->name() + CYN "�������" NOR + HIR 
                                         + ob->name() + "(" + ob->query("id") + ")" + 
                                         NOR + CYN "�����ν�����Ŵ�" 
                                         "���������ԣ���˵�������" + place + "����" 
                                         "ȥ����������ͷ������\n" NOR); 
                } else 
                { 
                        ob->set("shen_type", 0);
                        ob->set("shen", 0);
                        tell_object(who, CYN + me->name() + CYN "����˵��������Ϳ�" 
                                         NOR + HIR + ob->name() + "(" + ob->query("id") + 
                                         ")" + NOR + CYN "��˳��" 
                                         "����˵�������" + place + "����ȥ��������" 
                                         "��������ͷ�����\n" NOR); 
                } 
                who->set("quest/type", "kill"); 
                switch (level) 
                { 
                case 0: 
                        message_vision(CYN "$N" CYN "���˶٣��ֶ�$n" CYN "�������" 
                                       "�������װ�úܣ���Ҫ�ǻ��첻���ǿɲ��󻰡�" 
                                       "\n" NOR, me, who); 
                        break; 
                case 1: 
                        break; 
                case 2: 
                        message_vision(CYN "$N" CYN "���˿�$n" CYN "�ֵ����������" 
                                       "������Щ�Ѱ죬��Ҫ�ǲ����Ҿ������˰ɡ�\n" 
                                       NOR, me, who); 
                        break; 
                case 3: 
                        message_vision(CYN "$N" CYN "̾�˿�����֣�صĶ�$n" CYN "��" 
                                       "������������յý����㲻Ҫ��ǿ�Լ������о�" 
                                       "���ˡ�\n" NOR, me, who); 
                        break; 
                } 
        
                if (level > 0 && random(10) == 1)
                {
                        string flee_msg;

                        // ������·���NPC��λ��
                        message_sort(CYN "$N" CYN "�������䣬ͻȻһ��"
                                     "����ææ�ĸ��˹���������������"
                                     "���ˣ������ˣ�" HIR + ob->name() +
                                     NOR CYN "��" + place +
                                     "ʧ���ˣ����ڲ�֪��ȥ�������"
                                     "$N" CYN "���˰��Σ���Ŷ�$n" CYN
                                     "�����������鷳�ˣ�����ֻ�п�����"
                                     "��Ŭ���ˣ���\n" NOR, me, who);
                        switch (random(3))
                        {
                        case 0:
                                flee_msg = "��˵$N�����˽�����׷ɱ���ķ�"
                                           "�����Ѿ��㵽PLACEȥ�ˡ�";
                                break;
                        case 1:
                                flee_msg = "����˵$N����������ؽ��أ�"
                                           "����Ҳ����˵����PLACE����֪�������Ǽ١�";
                                break;
                        default:
                                flee_msg = "��֪��...��֪��...Ŷ������"
                                           "����˵������PLACE��";
                                break;
                        }
                        ob->random_place(flee_msg);
                }
        }
        
        who->set("quest/family", fam);
        who->set("quest/master_name", me->name());
        who->set("quest/master_id", me->query("id"));
        who->set("quest/name", ob->name());
        who->set("quest/id", ob->query("id"));
        who->set("quest/level", level);
        who->set("quest/place", place);
        t = time();
        who->set("quest/time", t);
        t = time() / ONE_DAY;
        if (ob->query("place") == "����")
                t += 8;
        else
                t += 4;
        t = t * ONE_DAY - 1;
        who->set("quest/limit", t);
        message("vision", WHT + me->name() + WHT "�����������˵���������Ҫ��" 
                          NOR + HIY + CHINESE_D->chinese_monthday(t) + NOR + WHT 
                         "֮ǰ��ɣ�\n" NOR, who); 
        who->start_busy(1); 
        return 1; 
} 

public int ask_defend(object me, object who) 
{
        function f;
        int r;

        f = me->query_temp("override/ask_defend", 1);
        if (functionp(f))
                r = (*f)(me, who);
        else
                r = 0;
        return r;
}

public int ask_finish(object me, object who) 
{
        function f;
        int r;

        f = me->query_temp("override/ask_finish", 1);
        if (functionp(f))
                r = (*f)(me, who);
        else
                r = 0;
        return r;
}
                                                                
int accept_object(object me, object who, object ob)
{
        mapping q;              // WHO������
        string msg;             // ����˵����Ϣ
        object dob;             // ���ε��˵���
        int bonus;              // ����(��������1������)
        int t;                  // ��������ʱ��ı���
        int exp;                // ��õľ���
        int pot;                // ��õ�Ǳ��
        int mar;                // ��õ�ʵս���
        int weiwang;            // ��õ�����
        int score;              // ��õĽ�������
        int gongxian;           // ��õ����ɹ���
        int lvl;                // ����ĵȼ�
        int quest_level;        // QUEST�ĵȼ�
        int quest_count;        // ����QUEST����Ŀ
        int total_count;        // ......
        int timeover;           // ��־����ʱ�ˣ�
        int added;              // �������ʱ�������ֵĵ��˻��������
	mixed special = 0;      // �Ƿ������⽱��

        if (me->query("family/family_name") != who->query("family/family_name"))
                return 0;

        q = who->query("quest");

        if(ob->query("money_id"))
        {
               if (! mapp(q) || q["master_id"] != me->query("id"))
               {
                       tell_object(who,me->name() + "��ֵĿ�����˵����û����ʲô���񰡣�\n");
                       return 0;
               }

               if (ob->value() < 1000000)
               {
                       tell_object(who,me->name() + "��мһ�˵�˵����ôһ���Ǯ����������ʲô�����Լ����������ðɣ�\n");
                       tell_object(who,me->name() + "����һ����˵����������100���ƽ𣬻����ҿ��Կ����������������\n");
                       return 0;
               }

               who->delete("quest");
               tell_object(who,me->name() + "΢΢Ц��Ц����ͷ����������������������˰ɡ�\n");
               destruct(ob);
               return 1;
        }
        
        if (ob->is_letter())
        {
                if (ob->query("send_from") != me->query("id"))
                {
                        message_vision(CYN "$N" CYN "������Ҫ��ʲô��\n" NOR, me); 
                        return -1; 
                } 
        
                if (! q || q["type"] != "letter" || ob->query("send_to") != q["id"]) 
                { 
                        message_vision(CYN "$N" CYN "�����̾��һ������û˵ʲô��\n" NOR, me); 
                        destruct(ob); 
                        return 1; 
                } 
        
                message_vision(CYN "$N" CYN "����$n" CYN "������ʲô��������" 
                               "�Ļ��㲻������ˣ�\n" NOR, me, who);         
                return -1; 
        } 
        
        if (ob->is_receipt()) 
        { 
                if (ob->query("reply_to") != me->query("id"))
                {
                        message_vision("$N��ü���������������ո�ʲô����\n", me);
                        return 0;
                }

                if (! q || q["type"] != "letter" || q["id"] != ob->query("reply_by"))
                {
                        message_vision("$N���ͷ��������л�ˡ���\n", me);
                        destruct(ob);
                        return 1;
                }

                message_vision(CYN "$N" CYN "�ӹ�" + ob->name() + NOR + CYN"����ϸ����" 
                              "���������˵���ܺá�\n" NOR, me, who);
                
                msg = "";
                t = time(); 
                if (t > q["limit"]) 
                { 
                        msg += CYN + me->name() + CYN "̾�˿������ֵ�����ϧ����������" + 
                               CHINESE_D->chinese_monthday(t) + "ǰ��������" 
                               "�ˣ������������������°ɡ�\n" NOR; 
                        timeover = 1; 
                } else 
                { 
                        if (t - q["time"] < ONE_DAY) 
                        { 
                                msg += CYN + me->name() + CYN "���ͷ������ܲ�����ô" 
                                       "�������ˣ��úøɣ�\n" NOR; 
                        } else 
                                msg += CYN + me->name() + CYN "���ͷ������β�������" 
                                       "�ˡ�\n" NOR; 
                        timeover = 0; 
                } 
                bonus = (ob->query("receive_from") == who->query("id")); 
                exp = 150 + random(100);
                pot = 50 + random(80);
                mar = 10;
                score = 60 + random(50);
                weiwang = 10;
                gongxian = 60 + random(50);
                destruct(ob);
        } else 
        { 
                if (! mapp(q) || ! ob->is_corpse() && ! ob->is_head()) 
                        return 0; 
        
                if (! stringp(ob->query("owner_id"))) 
                { 
                        message_vision(CYN "$N" CYN "���ű��ӿ��˿�" + ob->name() 
                                       + NOR + CYN "������ʲô�����ģ������" 
                                       "���ߡ�\n" NOR, me); 
                        return 0; 
                } 
                
                if (ob->query("owner_id") != q["id"])
                        return 0;
        
                msg = CYN + me->name() + CYN "�ӹ�" + ob->name() + NOR + CYN "���ǺǴ�Ц" 
                      "���������"; 
        
                if (me->is_good()) 
                        msg += CYN "�ֳ���һ�����ܺã�"; 
                else 
                if (me->is_bad()) 
                        msg += CYN "�ü��ˣ�ʲô����������һ����"; 
                else 
                        msg += CYN "�ɵúã�Ư����"; 
        
                msg += "\n" NOR; 
                t = time(); 
                if (who->query_temp("quest/escape_times")) 
                { 
                        msg += CYN + me->name() + CYN "����������û�뵽������ôǿ����ʵ" 
                               "��δ���ϵ������࣬���࣡\n" NOR; 
                        timeover = 0; 
                } else 
                if (t > q["limit"]) 
                { 
                        msg += CYN + me->name() + CYN "ҡҡͷ���ֵ�����ϧ����������" + 
                               CHINESE_D->chinese_monthday(t) + "ǰ��������" 
                               "�ˣ������������������°ɡ�\n" NOR; 
                        timeover = 1; 
                } else 
                { 
                        if (t - q["time"] < ONE_DAY) 
                        { 
                                msg += CYN + me->name() + CYN "���ͷ�����ɵò�����ô" 
                                       "�������ˣ��úøɣ�\n" NOR ; 
                        } else 
                                msg += CYN + me->name() + CYN "���ͷ������β�������" 
                                       "�ˡ�\n" NOR; 
                        timeover = 0; 
                } 
        
                // bonusΪ1��ʾ����������Ϊ2��ʾ�۳�һ�롣 
                /*
                bonus = (ob->query("killed_by") == who->query("id")) &&
                        (ob->query("defeated_by") == who ||
                         ! ob->query("defeated_by") &&
                           ob->query("defeated_by_who") == who->name(1));
                */
                bonus = (ob->query("killed_by") == who->query("id"));
                if (ob->query("assist") == who)
                {
                        dob = ob->query("defeated_by");
                        msg += CYN + me->name() + CYN "��ο�Ķ������������ܹ�" 
                               "�õ�" + (dob ? dob->name(1) : "ͬ��ʦ�ֵ�") + 
                               NOR + CYN "�İ�æ��Ҳ�����ף��Ժ�˴�Ҫ�����" 
                               "Ӧ��\n" NOR; 
                        bonus = 2; 
                } else 
                if (bonus) 
                        bonus = 1; 
        
                destruct(ob); 
                lvl = NPC_D->check_level(who); 
                exp = 40 + random(20) + lvl;
                pot = 20 + random(12) + lvl;
                mar = 4 + random(5);
                weiwang = 8 + random(9) + lvl / 2;
                score = 8 + random(9) + lvl / 2;
                gongxian = 4 + random(5) + lvl / 2;
                quest_count = who->query("quest_count") + 1;
        
                // add temped for keep compactible with old version 
                if (who->query_temp("quest/total_count")) 
                { 
                        quest_count = who->query_temp("quest/total_count") + 1; 
                        who->delete_temp("quest/total_count"); 
                } 
        
                // ����������ɵĴ�����������
                if (quest_count >= 1000)
                {
                        exp += 80 + random(50);
                        pot += 45 + random(40);
                        mar = 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                        gongxian += 4 + random(15);
                } else                   
                if (quest_count >= 500)
                {
                        // ��������˳���500�ε�����
                        exp += 80 + random(quest_count / 20 + 1);
                        pot += 45 + random(quest_count / 25 + 1);
                        mar = 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                        gongxian += 4 + random(15);
                } else 
                if (quest_count >= 200) 
                { 
                        // ��������˳���200�ε����� 
                        exp += 70 + random(quest_count / 20 + 1);
                        pot += 40 + random(quest_count / 25 + 1);
                        mar = 20 + random(10);
                        weiwang += 5 + random(15);
                        score += 3 + random(10);
                } else 
                if (quest_count >= 100)
                {
                        // ��������˳���100�ε�����
                        exp += 50 + random(quest_count / 20 + 1);
                        pot += 30 + random(quest_count / 25 + 1);
                        weiwang += 3 + random(10);
                        score += 2 + random(10);
                } else
                if (quest_count >= 10)
                {
                        // ��������˳���10�ε�����
                        exp += 45 + random(quest_count / 20 + 1);
                        pot += 25 + random(quest_count / 25 + 1);
                        weiwang += 1 + random(5);
                        score += 1 + random(5);
                }
        
                switch (quest_level = q["level"]) 
                { 
                case 0: 
                        exp = exp / 2 + 1; 
                        pot = pot / 2 + 1; 
                        gongxian = gongxian / 2 + 1; 
                        weiwang = weiwang / 3 + 1; 
                        score = score / 4 + 1; 
                        msg += CYN + me->name() + CYN "���������˵�������аɣ���" 
                               "���Ҹ�����ѵ������\n" NOR; 
                        break; 
                case 1: 
                        msg += CYN + me->name() + CYN "�����ֵ������������ҿ���" 
                               "�и�Щ���θ����ˡ�\n" NOR; 
                        break; 
                case 2: 
                        exp += exp / 4; 
                        pot += pot / 4; 
                        mar += mar / 4;
                        weiwang += weiwang / 4; 
                        score += score / 4; 
                        msg += CYN + me->name() + CYN "����Ц�������ǲ���������" 
                               "����" + who->query("family/family_name") + "��" 
                               "�ý��ߡ�\n" NOR; 
                        break; 
                case 3: 
                        exp += exp / 2; 
                        pot += pot / 2; 
                        mar += mar / 2;
                        gongxian += gongxian / 2; 
                        weiwang += weiwang / 2; 
                        score += score / 2; 
                        msg += CYN + me->name() + CYN "��������ǳ�������οɸ�����" + 
                               who->query("family/family_name") + "�����ˡ�\n" 
                               NOR; 
                        break; 
                } 
                total_count = quest_count % 1000;
                if (total_count == 100)
                {
                        msg += CYN + me->name() + CYN "������Ц����������������ģ�����" + chinese_number(quest_count) +
                               "��������ɵ�ƯƯ�������ܺã��ܺá���\n" NOR;
			special = 1;
                } else
                if (total_count == 200)
                {

                        msg += CYN + me->name() + CYN "��ϲ��������������ʵ��������" + chinese_number(quest_count) +
                               "������ɵúܺá���\n NOR";
			special = "/clone/gift/puti-zi";
                } else
                if (total_count == 300)
                {
                        msg += CYN + me->name() + CYN "̾���������ǳ���������ǰ�ˣ��벻���������" + chinese_number(quest_count) +
                               "��������һ��©�����ף����ף���\n" NOR;
			special = "/clone/gift/tianxiang";
                } else
                if (total_count == 500)
                {
                        msg += CYN + me->name() + CYN "����̾�˿������������벻��������" + chinese_number(quest_count) +
                               "��������һʧ�֣���������" + me->query("family/family_name") +
                               "���Ǻ�����˰�����\n";
			special = "/clone/gift/jiuzhuan";
                } else                
                if (total_count == 0)
                {
                        msg += CYN + me->name() + CYN "����̾�˿������������벻��������" + chinese_number(quest_count) +
                               "��������һʧ�֣���������" + me->query("family/family_name") +
                               "������ʦ����������\n" NOR;
			special = "/clone/gift/xuanhuang";
#ifdef DB_SAVE
                        if (MEMBER_D->is_valid_member(who->query("id")))
                        {
                                if (who->query("special_skill/sophistry"))
                                {
                                        if (quest_count >= 4000)
                                                quest_count = 0;
                                } else
                                {
                                        if (quest_count >= 2000)
                                                quest_count = 0;
                                }       
                        }
                        else 
                        {
#endif
                                quest_count = 0;
#ifdef DB_SAVE
                        }
#endif
                } else
                if ((total_count % 10) == 0)
                {
                        msg += CYN + me->name() + CYN "ϲ���������ǲ�������Ȼ����" + chinese_number(quest_count) +
                               "�ζ�û��ʧ�֣��ɵĺã���\n" NOR ;
                }
                
                quest_level = q["level"];
                quest_level++;
                if (quest_level > MAX_QUEST_LEVEL)
                        quest_level = 1;

                who->set("quest_count", quest_count);
                who->set_temp("quest/next_level", quest_level);
        }
        
        if ((added = (int)who->query_temp("quest/help_count")) > 0) 
        { 
                msg += HIY + me->name() + HIY "�ֵ�����ε��˷��°��֣����������Ӧ�䣬" 
                       "������񣬿�ϲ���ɺأ�\n" NOR; 
                who->delete_temp("quest/help_count"); 
        } 
        added += (int)who->query_temp("quest/escape_times") * 2;
        who->delete_temp("quest/escape_times");
        // ����NPC�İ��ֺ����ߵĴ�����������
        if (added)
        {
                exp += exp * added / 2;
                pot += pot * added / 2;
        }
        
        // message_vision(msg, me, who); 
        tell_object(who, msg);
        
        who->delete("quest"); 
        if (! bonus) return 1; 
        
        exp /= bonus; 
        pot /= bonus; 
        mar /= bonus; 
        weiwang /= bonus; 
        score /= bonus; 
        gongxian /= bonus; 
         
        // bouns 
        if (timeover) 
        { 
                exp /= 2; 
                pot /= 3; 
                mar /= 2; 
                weiwang /= 4; 
                score /= 4; 
                gongxian /= 2; 
        } else 
        { 
                // �ٷ�֮һ�ļ���ֱ��������Ʒ���� 
                if ((quest_count >= 100 && random(200) == 1) || special) 
                        special_bonus(me, who, special); 
        } 
                        
        GIFT_D->bonus(who, ([ "exp" : exp * 3 / 2, "pot" : pot * 3 / 2, "mar" : mar * 2,
                              "weiwang" : weiwang, "score" : score, "gongxian" : gongxian ]), 1);
        
        // ���ֹͣ�������񣬱�������һ��������freequest���ܼ����� 
       if (random(60) == 1 && quest_count >= 50) 
                who->add("quest/freequest", 1 + random(3)); 
        
        return 1; 
} 

// Զ�̽���
int remote_bonus(object me)
{
        mapping q;              // WHO������
        string msg;             // ����˵����Ϣ
        object dob;             // ���ε��˵���
        int bonus;              // ����(��������1������)
        int t;                  // ��������ʱ��ı���
        int exp;                // ��õľ���
        int pot;                // ��õ�Ǳ��
        int mar;                // ��õ�ʵս���
        int weiwang;            // ��õ�����
        int score;              // ��õĽ�������
        int lvl;                // ����ĵȼ�
        int quest_level;        // QUEST�ĵȼ�
        int quest_count;        // ����QUEST����Ŀ
        int timeover;           // ��־����ʱ�ˣ�
        int added;              // �������ʱ�������ֵĵ��˻��������

        if (! mapp(q = me->query("quest")))
                return 0;

        msg = "�㷭���ż㷴�棬����ʦ�����л�˵��\n\n�ּ���Ϊʦ"
              "��֪";
        if (me->is_good())
                msg += "���ֳ���" HIR + q["name"] + NOR "��һ�����ܺá�";
        else
        if (me->is_bad())
                msg += "���ѳ���" HIR + q["name"] + NOR "�ǲ���һ������ν"
                       "������";
        else
                msg += "������ɳ���" HIR + q["name"] + NOR "�����񣬲���"
                       "��";
        t = time();
        if (me->query_temp("quest/escape_times"))
        {
                msg += "�Ҳ��ϴ˴ε�����Ϊǿ�����Ŵ��Ӵܣ�׷����"
                       "ν���࣬";
                timeover = 0;
        } else
        if (t > q["limit"])
        {
                msg += "����ϧ��Ϊʦ��������" + 
                       CHINESE_D->chinese_monthday(t) + "ǰ��ɣ�"
                       "�����������˴ξͼ��²��㡣";
                timeover = 1;
        } else
        {
                if (t - q["time"] < ONE_DAY)
                {
                        msg += "����ɵ��ٶ����֮�죬ʵ�ڳ�����"
                               "��Ԥ�ϡ�";
                } else
                        msg += "����������Ĳ��������ˡ�";

                timeover = 0;
        }


        // bonus Ϊ 1 ��ʾ����������Ϊ 2 ��ʾ�۳�һ�롣
        bonus = 1;

        lvl = NPC_D->check_level(me);
        exp = 10 + random(5) + lvl;
        pot = 5 + random(3) + lvl;
        weiwang = 2 + random(3) + lvl / 2;
        score = 2 + random(3) + lvl / 2;
        quest_count = me->query("quest_count") + 1;

        // add temped for keep compactible with old version
        if (me->query_temp("quest/total_count"))
        {
                quest_count = me->query_temp("quest/total_count") + 1;
                me->delete_temp("quest/total_count");
        }

        // ����������ɵĴ�����������
        if (quest_count >= 500)
        {
                // ��������˳���500�ε�����
                exp += 80 + random(quest_count / 20 + 1);
                pot += 45 + random(quest_count / 25 + 1);
                mar = 50 + random(20);
                weiwang += 8 + random(20);
                score += 4 + random(15);
        } else
        if (quest_count >= 200)
        {
                // ��������˳���200�ε�����
                exp += 70 + random(quest_count / 20 + 1);
                pot += 40 + random(quest_count / 25 + 1);
                mar = 20 + random(10);
                weiwang += 5 + random(15);
                score += 3 + random(10);
        } else
        if (quest_count >= 100)
        {
                // ��������˳���100�ε�����
                exp += 50 + random(quest_count / 20 + 1);
                pot += 30 + random(quest_count / 25 + 1);
                weiwang += 3 + random(10);
                score += 2 + random(10);
        } else
        if (quest_count >= 10)
        {
                // ��������˳���10�ε�����
                exp += 45 + random(quest_count / 20 + 1);
                pot += 25 + random(quest_count / 25 + 1);
                weiwang += 1 + random(5);
                score += 1 + random(5);
        }

        switch (quest_level = q["level"])
        {
        case 0:
                exp = exp / 2 + 1;
                pot = pot / 2 + 1;
                weiwang = weiwang / 3 + 1;
                score = score / 4 + 1;
                msg += "�´��ٸ���һ�����ѵ�����ɡ�";
                break;
        case 1:
                msg += "���������ҿ����и�Щ���θ����ˡ�";
                break;
        case 2:
                exp += exp / 4;
                pot += pot / 4;
                weiwang += weiwang / 4;
                score += score / 4;
                msg += "���ǲ�������������" +
                       me->query("family/family_name") +
                       "�Ľý��ߡ�";
                break;
        case 3:
                exp += exp / 2;
                pot += pot / 2;
                weiwang += weiwang / 2;
                score += score / 2;
                msg += "�ǳ�������οɸ�����" +
                       me->query("family/family_name") +
                       "�����ˡ�";
                break;
        }

        if (quest_count == 100)
        {
                msg += "���������ϰٴ�������ɵ�ƯƯ������"
                       "�ܺá�";
        } else
        if (quest_count == 200)
        {
                msg += "���Ҿ�һ�����ٴ����񶼸ɵúܺá�";
        } else
        if (quest_count == 500)
        {
                msg += "���ǳ���������ǰ�ˣ�������������"
                       "��������һ��©�����ף����ף�";
        } else
        if (quest_count >= 1000)
        {
                msg += "�벻����������ǧ��������һʧ�֣���"
                       "������" + me->query("family/family_name") +
                       "��������ӡ�";
                quest_count = 0;
        } else
        if ((quest_count % 10) == 0)
        {
                msg += "�ţ����Ҿ�Ȼ����" +
                       chinese_number(quest_count) +
                       "�ζ�û��ʧ�֡�";
        }

        quest_level = q["level"];
        quest_level++;
        if (quest_level > MAX_QUEST_LEVEL)
                quest_level = 1;

        me->set("quest_count", quest_count);
        me->set_temp("quest/next_level", quest_level);

        if ((added = (int)me->query_temp("quest/help_count")) > 0)
        {
                msg += HIY "������ε��˷��°��֣���������"
                       "��Ӧ�䣬������񣬿�ϲ���ɺء�\n" NOR;
                me->delete_temp("quest/help_count");
        }
        added += (int)me->query_temp("quest/escape_times") * 2;
        me->delete_temp("quest/escape_times");
        // ���� NPC �İ��ֺ����ߵĴ�����������
        if (added)
        {
                exp += exp * added / 2;
                pot += pot * added / 2;
        }
        msg = sort_msg(msg);
        msg += "\n\n";
        tell_object(me, msg);
        me->delete("quest");
        if (! bonus) return 1;

        exp /= bonus;
        pot /= bonus;
        mar /= bonus;
        weiwang /= bonus;
        score /= bonus;
        // bonus
        if (timeover)
        {
                exp /= 2;
                pot /= 3;
                mar /= 2;
                weiwang /= 4;
                score /= 4;
        }

        bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                      "weiwang" : weiwang, "score" : score ]), 1);
        return 1;
}

int cancel_quest(object me, object who) 
{ 
        mapping dbase; 
        mapping q; 
        object ob; 
        string msg; 
        int n; 
        int c; 
        
        dbase = who->query_entire_dbase(); 
        if (! mapp(q = dbase["quest"]) || 
                q["master_id"] != me->query("id")) 
                return notify_fail("��û����ʲô���񰡣�\n"); 
        
        switch (q["type"]) 
        { 
        case "kill": 
                if (q["notice"] == "die") 
                { 
                        message_vision(CYN "$N" CYN "���ͷ����$n" CYN "�������ˣ���˵����" 
                                       "�Ѿ���ɱ�ˣ��㲻���������ˡ�\n" NOR, me, who); 
                } else 
                { 
                        message_vision(CYN "$N" CYN "�ڰ��֣���$n" CYN "������ɲ��˾�����" 
                                       "���ñ������ɣ�\n" NOR, me, who); 
                                       
                        if (! who->query("special_skill/sophistry"))
                                who->delete("quest_count"); 
                } 
        
                who->delete_temp("quest/next_level"); 
                if (who->query("special_skill/sophistry"))
                        break;

                n = (40 + random(40) + NPC_D->check_level(who) * 5); 
                c = (10 + random(10) + NPC_D->check_level(who)); 
                // add temped for keep compactible with old version        
                switch (q["level"]) 
                { 
                case 0:
                        n *= 2;
                        break;
                case 1:
                        break;
                case 2:
                        n = 0;
                        break;
                case 3:
                        n = 0;
                        break;
                }
                if (! n) break;
        
                // adjust weiwang 
                dbase["weiwang"] -= n; 
                if (dbase["weiwang"] < 0) 
                        dbase["weiwang"] = 0; 
                msg = HIR "��Ľ��������ܵ�����ʧ"; 
        
                // adjust gongxian 
                who->add("family/gongji", -c);
                if (who->query("family/gongji") < 0)
                        who->set("family/gongji", 0);
                msg += HIR "��ʦ�Ŷ�������ν�����"; 
        
                // adjust experience
                if (count_gt(dbase["experience"], dbase["learned_experience"]))
                {
                        dbase["experience"] = count_sub(dbase["experience"], 
                                              count_div(count_mul(count_sub(dbase["experience"], 
                                                        dbase["learned_experience"]), 2), 3));
                                
                        // dbase["experience"] += (dbase["learned_experience"] - dbase["experience"]) * 2 / 3;
                        msg += "������ƣ�ڱ��������ʵս������Լ�ʱ��������";
                }

                // notice place
                message("vision", msg + "��\n" NOR, who);
                break;
        
        case "letter": 
                message_vision(CYN "$N" CYN "̾���������˿�$n" CYN "���������С�¶��ɲ��ˣ����˰ɡ�\n" NOR, 
                               me, who); 
        
                who->add("score", -(15 + random(10))); 
                if (who->query("score") < 0) 
                        who->set("score", 0); 
                message("vision", HIR "��Ľ��������ܵ�����ʧ��\n" NOR, who); 
                break; 
        } 
        who->start_busy(2); 
        
        ob = find_living(q["id"]);
        map_delete(dbase, "quest");
        if (who->query_temp("quest/help_count"))
                who->delete_temp("quest/help_count"); 
        if (! ob || ob->query_temp("quester") != who->query("id"))
                return 1;
        
        if (environment(ob)) 
                message_vision(HIC "$N" HIC "���˿����ܣ�����ææ���ߵ��ˡ�\n" NOR, ob); 
        
        destruct(ob); 
        return 1; 
} 

// �������������
void remote_assign_quest(object who, mapping new_quest)
{
        call_out("assign_quest_by_letter", 3 + random(5),
                 who, (string)who->query("quest/id"), new_quest);
}

protected void assign_quest_by_letter(object who, string killed_id, mapping new_quest)
{
        mapping q;
        string  msg;
        string  refuse, accept;
        object  letter;             // ʦ������

        if (! objectp(who) || ! living(who))
                return;

        if (! mapp(q = who->query("quest")))
                return;

        if (! q["finished"])
                return;

        if (q["id"] != killed_id)
                // �����Ѿ��仯��
                return;

        // ʦ�������µ�����ѯ���Ƿ����
        switch (random(7))
        {
        case 0:
                // ������������ʾ
                msg = "ֻ����ٿ��ٿ������һֻ�׸���˹���������"
                      "$N��ͷ��$Nֻ���׸����Ϻ���ϵ��Щʲô����"
                      "æ����һ����ԭ������ʦ�����͡�\n";
                // �ܾ���Ϣ
                refuse = "$Nҡ��ҡͷ�����ź�����һ˺��\n";
                // ������Ϣ
                accept = "$N���˵�ͷ�������ź�����д�˼����֣���"
                         "�ڰ׸����Ϸ��ߡ�\n";
                break;
        case 1:
                msg = "$Nת��һ����������һֻ�ҵ��Ÿ�������ԣ�"
                      "$N�Ͻ���ס���Σ�ȡ���Ÿ���ϸ��ŵľ�����"
                      "�㣬չ�������\n";
                refuse = "$Nҡ��ҡͷ�����ź�����һ˺��\n";
                accept = "$N���˵�ͷ�������ź�����д�˼����֣���"
                         "�ڻҸ����Ϸ��ߡ�\n";
                break;
        case 2:
                msg = "$Nһ��ͷ��ֻ��һλͬ��װ���ĵ�����ͷ��"
                      "�����˹������ߴ����ߵ������ɽ��Һ��ң���"
                      "��ʦ�������͸�������͡���\n";
                refuse = "$N������ü���������һ��ǲ�ȥ�ˣ�����ʦ"
                         "���ұ��ͬ��ȥ�ɡ�����λ����̾�˿�����"
                         "ת���뿪��\n";
                accept = "$Nϲ��������������ʦ������һ��׼ʱ���"
                         "������λ���ӻ��˻��֣��糾���͵��뿪��"
                         "��\n";
                break;
        case 3:
                msg = "ͻȻһλ" + who->query("family/family_name") +
                      "���Ӽ���ææ����������������$N�ļ�򣬰�"
                      "һ���ŵ��ϡ�\n";
                refuse = "$N������ü���������һ��ǲ�ȥ�ˣ�����ʦ"
                         "���ұ��ͬ��ȥ�ɡ�����λ����̾�˿�����"
                         "ת���뿪��\n";
                accept = "$Nϲ��������������ʦ������һ��׼ʱ���"
                         "������λ���ӻ��˻��֣��糾���͵��뿪��"
                         "��\n";
                break;
        case 4:
                msg = "ֻ��$N�����뿪��һλͬ��װ���ĵ���׷����"
                      "����Ĩ��Ĩͷ�ϵĺ��飬˵������ԭ��������"
                      "�ﰡ���쿴��ʦ�������������š���\n";
                refuse = "$N������ü���������һ��ǲ�ȥ�ˣ�����ʦ"
                         "���ұ��ͬ��ȥ�ɡ�����λ����̾�˿�����"
                         "ת���뿪��\n";
                accept = "$Nϲ��������������ʦ������һ��׼ʱ���"
                         "������λ���ӻ��˻��֣��糾���͵��뿪��"
                         "��\n";
                break;
        case 5:
                msg = "$N�����뿪����Ȼ���ֲ�Զ���ĵ���һ��ʯͷ"
                      "�Ͽ���Щʲô���߽�һ�������Ǳ���ר�õļ�"
                      "�ϣ�ԭ��ʯͷ��ѹ��һ�����š�\n";
                refuse = "$Nҡ��ҡͷ�����ź�����һ˺��\n";
                accept = "$N���˵�ͷ�������ź�����д�˼����֣���"
                         "��ѹ��ʯͷ���档\n";
                break;
        default:
                msg = "������ಡ���һ����һ��������$N���������"
                      "$N����������Ͻ�����һ��������ͬ��������"
                      "һ��ʦ�����͡�\n";
                refuse = "$Nҡ��ҡͷ�����ź�����һ˺��\n";
                accept = "$N���˵�ͷ�����ź�����д�˼����֣�һ˦"
                         "�ֽ��ź��򱳺�ƽƽ�ͳ������Ų�֪��˭��"
                         "ס�������̱���ʧ�ˡ�\n";
                break;
        }

        message_sort(HIY + "\n" + msg + NOR, who);

        letter = new("/clone/questob/letter");

        // ������Ǹ�˭�ģ�
        letter->set("killed_id", killed_id);
        letter->set("quester", who->query("id"));
        letter->set("quest", new_quest);
        letter->set("msg/accept", accept);
        letter->set("msg/refuse", refuse);

        // Ҫ��ʲôʱ��֮ǰ�ش�
        letter->set("dest_time", time() + 30);
        letter->move(who);

        // �� 30 ���ڲ����� accept �����ܾ���
        letter->start_auto_cancel(who, 30);
}
 
// ׼������ҷ���Զ������
mapping prepare_quest(object me)
{
        mapping q;      // ��������
        string place;   // npc ���õĵص�
        mapping name;   // npc ������
        int exp;        // ���������ҵľ���ֵ
        int t;          // ʱ��
        string family;  // �������
        object master;  // ʦ��

        exp = me->query("combat_exp");
        t = time();
        name = NPC_D->get_cn_name();
        family = me->query("family/family_name");

        // ʦ��һ���Ǹ��Ƴ����ģ�����Ǹ��ƵĶ���Ҳ��
        if (! objectp(master = find_object(mlist[family])))
        {
                master = load_object(mlist[family]);
                if (! objectp(master))
                    log_file("log", sprintf("Can not load master \"%s\".\n",
                                            mlist[family]));
                return 0;
        }

        q = ([ ]);
        q["place"] = NPC_D->random_place(exp < 500000  ? ({ "����һ��", "����ɽ", "����", "����" }) :
                                         exp < 800000 ? ({ "����һ��", "����ɽ", "����" }) : 0);
        q["name"] = name["name"];
        q["id"] = name["id"][0];
        q["full_id"] = name["id"];
        q["level"] = me->query_temp("quest/next_level");
        q["time"] = t;
        q["count"] = me->query("quest_count") + 1;
        q["family"] = family;
        q["master_name"] = master->name();
        q["master_id"] = master->query("id");
        q["type"] = "kill";

        t = time() / ONE_DAY;
        if (place == "����")
                t += 8;
        else
                t += 4;
        t = t * ONE_DAY - 1;
        q["limit"] = t;

        return q;
}

// ��ʽ��ʼԶ�� quest
int start_quest(object me, mapping quest)
{
        object ob;
        int level;
        string place;

        level = quest["level"];
        ob = new(CLASS_D("generate") + "/killed.c");

        // ����Ԥ�õ�����
        ob->set_name(quest["name"], quest["full_id"]);
        // ��������������Ҫ���� set_living_name������
        // �޷� find_living()
        ob->enable_player();

        // ��Ԥ�����ɵ�ָ���ط�ȥ
        NPC_D->place_npc(ob, 0, ({ quest["place"] }));
        NPC_D->set_from_me(ob, me, 100);

        ob->add_temp("apply/attack", ob->query_skill("force") *
                                     (level - 1) / 15);
        ob->add_temp("apply/dodge", ob->query_skill("force") *
                                    (level - 1) / 15);
        ob->add_temp("apply/parry", ob->query_skill("force") *
                                    (level - 1) / 15);
        ob->add_temp("apply/damage", 5 + level * 7);
        ob->add_temp("apply/unarmed_damage", 5 + level * 7);
        ob->add_temp("apply/armor", 10 + level * 15);
        ob->set_temp("quester", me->query("id"));
        NPC_D->random_move(ob);
        NPC_D->random_move(ob);
        NPC_D->random_move(ob);
        place = ob->query("place");

        if (me->is_good())
        {
                ob->set("shen", -ob->query("combat_exp") / 2000);
        } else
        if (me->is_bad())
        {
                ob->set("shen", ob->query("combat_exp") / 2000);
        } else
        {
                ob->set("shen_type", 0);
                ob->set("shen", 0);
        }

        // 1 �����ϵ������� 10% �������·ֲ�
        if (level > 0 && random(10) == 1)
        {
                string flee_msg;

                // ������·���NPC��λ��
                message_sort(CYN "$N" CYN  "�����뿪��ͻȻһ��"
                             "ͬ��װ���ĵ��Ӽ���ææ�ĸ��˹���"
                             "���������������ˣ������ˣ�" HIR +
                             ob->name() + NOR CYN "��" + place +
                             "ʧ���ˣ����ڲ�֪��ȥ���������"
                             "��̾�˿������������������鷳�ˣ�"
                             "����ֻ�п����Լ�Ŭ���ˡ���\n" NOR, me);
                switch (random(3))
                {
                case 0:
                        flee_msg = "��˵$N�����˽�����׷ɱ���ķ�"
                                   "�����Ѿ��㵽PLACEȥ�ˡ�";
                        break;
                case 1:
                        flee_msg = "����˵$N����������ؽ��أ�"
                                   "����Ҳ����˵����PLACE����֪�������Ǽ١�";
                        break;
                default:
                        flee_msg = "��֪��...��֪��...Ŷ������"
                                   "����˵������PLACE��";
                        break;
                }
                ob->random_place(flee_msg);
        }

        me->set("quest", quest);
        return 1;
}
 
/***********************************************************
  ϵͳע���������

    HELL������������������ڶ��ʽ���������񣬶������ػ�����
�������ǵĹ����ߡ�Ϊʲô��Ҫ�������������Ϊ�󲿷����񶼾�
�����ƵĴ�����̣��ռ��鱨�������������ĳЩҪ��ʵ��������
�񣬻�ý�����Ϊ���ܹ����ٵı�д��ʵ�ֶ������񣬹����ظ���ʵ
�ִ��룬ϵͳ�涨���������ĸ�ʽ��ֻҪ��ѭ�������ĸ�ʽ����
���Կ��ٵ������������

    ���������ȿ�һ������Ľṹ��һ������ʵ���Ͼ���һ���Զ�����
Ȼ������Ҳ��ϵĴ�������Զ������ﵽһ���ȶ�״̬��һ����˵
��������ɹ�������ֹ��ϵͳ����Ϊ��������ƶ�һЩ��׼�¼���Ȼ
���������������Լ��ƶ�һЩ�¼��������ϳ���һ�����������
�¼���Ȼ��ϵͳΪ����ά��һ��״̬�������͹�����һ���������Զ�
����

    ��һ���򵥵ġ�ɱ�ˡ�����

    ɱһ������Ҫ��Ҫ����Ҫ�أ�ʱ�䡢�ص㡢�����ĳһ��ʱ�䣬
ĳ���ص����һ�����ɱ����������ɣ����Ի�ý�������ô����
��Ƶ�����Ԥ���������ģ�һ���˴�������������񣬾�ȥ��Ӧ�ĵ�
�㣬ɱ�ˣ�ɱ���Ժ��ý�����

    ���������Զ�������

                                      ��Ϣ�ռ���ȫ
            <ԭ��̬> -> ��������̬ -----------+ 
                           /                  |
                 <Timeout>/    <Timeout>      |
                   -------<---------------\   |
                 /                         \  v
            <����̬>   <--------------- �������̬
                            ɱ������             

<ԭ��̬>��<����̬>��ϵͳ�涨��״̬��<Timeout> ��ϵͳԭ�ȱ���
���¼�������������̬���������̬�Ǹ��������е�״̬��������Ϣ
�ռ���ȫ��ɱ���������Ǹ�����������е��¼���

<ԭ��̬>�׶�ϵͳ��ʼ������������һЩ��Ҫ�Ĳ�������������
Ȩ���ݸ���������Խ��к����Ĳ�������ʱ��������Զ�����һ����
��ƶ����ĵȼ�����а��Ԥ�ڳ��ֵĵص㣬�������Ѷȵȵȡ�Ȼ��
�ͽ��뵽��������̬��ͬʱ�����Լ���Ҫ���ܳ�ʱ�¼���

��ʱ��������������Ϣ���п��ܴ�����������񣬲���������������
����˸��˳��ֵĵص���Ϣ��������������Ϊ��Ϣ�ռ���ȫ������
���������������Ⱥ���ҽ�������

��������ﱻ������֪ͨ��������������ת�Ƶ�<����̬>����
��һ���������̬�Ŀ����ǳ�ʱ�ˡ�

����<����̬>��ϵͳ�Զ�������������

������������������Ϸ�еĻ��ز��������²�������ϵͳ�������
�ȵȡ�ֻҪ����һ�����󣬾Ϳ��Բ�������

������Ϣ������ͨ������Ϣ����һ����Ϣ��ͨ�����Կ��Ƶ����������
������С��������Ĵ�����Ϣ�������Щ��Ϣ���Է�ӳ����ǰ����
��һЩ��Ϣ����Щ�����Ѿ���ϵͳ��װ����������Ժ�ϵͳ���ý�
�ں�����register_information()���ǼǺ�������ص���Ϣ -- Ϊʲ
ô�������������ͬʱ�������Լ��Ǽǣ�������Ϊ�����ػ������п�
�����������´�������������ʧ���еǼǵ����ݣ���ʱ�����ػ�����
�ͻ����ϵͳ�����е����񣬵���register_information()�ӿ�����
����֯��Щ��Ϣ��

��Ϣ���ݽṹ��

---+-- scheme(1) -*
   |
   +-- scheme(2) -*
   |
   +-- scheme(3) --+-- �ؼ��֣���Ϣ1
                   |
                   +-- �ؼ��֣���Ϣ2
                   |
                   .........

������Ҫһ���Ľ�����������random(��������) > ��Ϣ��ʱ�� ��
�п��ܴ����������Ϣ����Ϣ������һ������������������Ļ�����
������Ϣ��ʱ��ϵͳ�Ѵ����Ķ���ʹ�����Ϣ���ˣ��ؼ��ִ��ݸ���
������ȡ���ķ��ؽ����

QUEST_D�ṩ����ϢAPI��

QUEST_D->add_quest(QUEST_OBJECT);
QUEST_D->set_information(QUEST_OBJECT, key, information);
QUEST_D->query_information(QUEST_OBJECT, key);
QUEST_D->remove_information(QUEST_OBJECT, key);
QUEST_D->remove_all_information(QUEST_OBJECT);

QUEST_OB�����ṩ����Ϣ�ӿڣ�

QUEST_OB->register_information();
QUEST_OB->name();
QUEST_OB->can_know_by(object knower);
QUEST_OB->can_rumor_by(object knower);
QUEST_OB->query_introduce(object knower, object who);

***********************************************************/
        
// ϵͳ����һ������
public void add_quest(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
        {
                // ԭ��û���κ�����
                total = ([ qob : 1 ]);
                set("information", total);
        } else
        {
                // �鿴��������Ƿ��Ѿ��ж���
                if (undefinedp(total[qob]))
                        // ����һ��������Ϊ��ʱ��ոս���
                        // ����룬��û���κ���صľ�����Ϣ��
                        // ���������Ŀ��Ӧ�ľ�ֻ��һ����
                        // ������ʶ��
                        total[qob] = 1;
        }
}

// ������Ϣ
public void set_information(object qob, string key, mixed info)
{
        mixed total;
        mixed all_info;

        if (! stringp(key) || (! stringp(info) && ! functionp(info)))
        {
                log_file("static/quest",
                         sprintf("%s Quest:%O(%s) set illegal info:%s:%O.\n",
                                 log_time(), qob, qob->name(), key, info));
                return;
        }

        if (! mapp(total = query("information")))
                total = ([ ]);

        if (! mapp(all_info = total[qob]))
        {
                // ԭ��û�и�����������Ϣ��Ϣ
                all_info = ([ ]);
                total += ([ qob : all_info ]);
        }

        all_info[key] = info;
        set("information", total);
}

// ��ѯ��Ϣ
public mixed query_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return 0;

        if (! mapp(all_info = total[qob]))
                return 0;

        return all_info[key];
}

// ɾ����Ϣ
public void remove_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return;

        if (! mapp(all_info = total[qob]))
                return;

        map_delete(all_info, key);
        if (! sizeof(all_info))
        {
                // ����������Ѿ�û����Ϣ��
                map_delete(total, qob);
                return;
        }
}

// ɾ��ĳһ�������������Ϣ
public void remove_all_information(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
                return;

        // ��ɾ��������Ϣ��ͬʱ��������Ҳȥ���� -- Ϊʲô
        // ��������������Ϊ�����һ��û���κ���Ϣ�����񣨽�
        // ����������ṩ��Ϣ��������������ĺ�����������
        // ������һ���ṩ��Ϣ���������������ϢҲ������
        // ͬ�ĺ��塣
        map_delete(total, qob);
}

// QUESTϵͳ����������ʱ���ռ���������������Ϣ
protected void collect_all_quest_information()
{
        mapping total;
        object qob;
        object *obs;

        CHANNEL_D->do_channel(this_object(), "sys",
                              "�����鿪ʼ�ռ����е�������Ϣ��");

        if (! mapp(total = query("information")))
        {
                total = ([ ]);
                set("information", total);
        }

        obs = filter_array(objects(), (: $1->is_quest() :));

        // ɨ�����е�QUEST���󣬵Ǽ���Ϣ
        foreach (qob in obs)
        {
                reset_eval_cost();
                total[qob] = 0;
                catch(qob->register_information());
        }

        // ���Ѽ����������ػ�����
        start_all_quest();
}

public void start_all_quest()
{
        string quest;
        array qlist;
        string name;
        int pos;

        if (! VERSION_D->is_version_ok())
                // ����ͬ���汾����ô�����������ػ�����
                return;

        quest = read_file(CONFIG_DIR "quest");
        if (! stringp(quest))
                // �����ļ���û������
                return;

        qlist = explode(quest, "\n");
        foreach (name in qlist)
        {
                // ��ֹ���г�ʱ
                reset_eval_cost();

                if (strlen(name) < 1 || name[0] == '#')
                        // ���л�����ע����
                        continue;

                // ȥ����β��ע�ͺͿո�
                pos = strsrch(name, '#');
                if (pos > 1) name = name[0..pos - 1];
                name = replace_string(name, " ", "");

                // �����ļ�����
                name = QUEST_DIR + name + ".c";
                if (file_size(name) < 0)
                {
                        // û���������
                        log_file("static/quest",
                                 sprintf("%s invalid quest: %s\n",
                                         log_time(), name));
                        continue;
                }

                // �����������
                catch(call_other(name, "startup"));
        }
}

// �������е�����
protected void heart_beat()
{
        mapping total;
        mixed key;
        int live_time;
        int t;

        // �����������е�������̣������Ϊĳ�ֹ���ֹͣ���У�
        // ��ʱ���Խ����������������������ԭ��û�г����ϣ�
        // ��ô��ʱ�����������޸����ǵ�����ʱ�䡣
        // start_all_quest();  ȡ�� by Lonely 2007/11/21

        if (! mapp(total = query("information")))
                return;

        // ���㵱ǰʱ��
        t = time();

        // ɨ�����е�����ֻ������Ч������
        foreach (key in keys(total))
        {
                reset_eval_cost();
                if (! objectp(key))
                        map_delete(total, key);
                else
                switch (key->query_status())
                {
                case QUEST_CREATE:
                        if (t - key->query("start_time") > QUEST_CREATE_PERIOD)
                        {
                                // �������񳬹���Чʱ���ˣ�����֮
                                log_file("static/quest", sprintf("%s quest: %s create timeout\n%O",
                                                                 log_time(), base_name(key),
                                                                 key->query_entire_dbase()));
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;

                case QUEST_FINISH:
                        if (t->query("finish_time") > QUEST_FINISH_PERIOD)
                                // �������񳬹���Чʱ����
                                key->change_status(QUEST_ERROR);
                        break;

                case QUEST_ERROR:
                        // ���������д���״̬��
                        break;

                default:
                        // ������ͨ������״̬��
                        if ((live_time = key->query("live_time")) > 0 &&
                            live_time < t - key->query("start_time"))
                        {
                                // ���泬����ʱ��
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;
                }
        }
}

// ����Ϣ��ͨ��ʿ����ʹ��
public string generate_information(object knower, object who, string topic)
{
        mapping total;
        object *obs;
        object *dest;
        string name, title;
        object last_ob;
        mixed answer;

        total = query("information");

        switch (random(30))
        {
        case 0:
                return "���磡�е��ð��������˼��";
        case 1:
                return "��...�ȵȣ���˵ʲô��û�������";
        case 2:
                return "�ţ��ԵȰ����ͺ�... ���ˣ���ղ�˵ɶ��";
        case 3:
                return "���... ���... Ŷ�����ˣ������������أ�";
        case 4:
                return "���ϣ�... ������˼����������ô��";
        case 5:
                return "�ͺ�... �ͺ�... ���ˣ���˵ɶ��";
        case 7:
                return "!@#$%^&*";
        }

        if (topic == "rumor" || topic == "��Ϣ")
        {
                // ���ɴ���
                if (! mapp(total) ||
                    ! sizeof(obs = filter_array(keys(total), (: objectp($1) :))))
                {
                        // Ŀǰû���κ�����
                        switch (random(3))
                        {
                        case 0:
                                return "���ûɶ��Ϣ��";
                        case 1:
                                return "�������̫ͦƽ�ġ�";
                        default:
                                return "��֪��...��ȥ���ʱ��˰ɡ�";
                        }
                }

                // ���˸�С������ɢ������Ϣ
                obs = filter_array(obs, (: objectp($1) && $1->can_rumor_by($(knower)) :));
                if (! sizeof(obs))
                {
                        // ����ʿ����ɢ����Ϣ
                        switch (random(3))
                        {
                        case 0:
                                return "�ҵ�����˵��������ϳ��˲����¶���";
                        case 1:
                                return "��ѽѽ����Ҳ֪����һЩ���ܣ������˵˵��";
                        default:
                                return "����ͷ����Խ��Խ���ˡ�";
                        }
                }

                // ���ѡ��һ������ɢ����������Ϣ
                last_ob = obs[random(sizeof(obs))];
                knower->set_temp("last_asked_quest", last_ob);
                if (answer = last_ob->query_prompt(knower, who))
                        return answer;

                switch (random(3))
                {
                case 0:
                        return "�������������йء�" HIY +
                               last_ob->name() + NOR CYN "���Ĵ��ţ�";
                case 1:
                        return "�������ʢ����" HIY +
                               last_ob->name() + NOR CYN "����������أ�";
                default:
                        return "��û��������Ҷ������ۡ�" HIY +
                               last_ob->name() + NOR CYN "����";
                }
        }

        if (! mapp(total))
                return 0;

        // ��ø���֪��������������Ϣ
        obs = filter_array(keys(total), (: objectp($1) :));
        obs = filter_array(obs, (: $1->can_know_by($(knower)) :));

        // �鿴�Ƿ���ĳһ�������ĳһ����Ŀ
        if (sscanf(topic, "%s.%s", name, title) == 2)
        {
                dest = filter_array(obs, (: $1->name() == $(name) :));
                if (! sizeof(dest))
                        return 0;

                last_ob = dest[0];
        } else
        {
                // �鿴�Ƿ���ĳһ������
                dest = filter_array(obs, (: $1->name() == $(topic) :));
                if (sizeof(dest) > 0)
                {
                        last_ob = dest[0];
                        knower->set_temp("last_asked_quest", last_ob);
                        answer = last_ob->query_introduce(knower, who);
                        if (stringp(answer))
                                return answer;
                        return "��˵����" HIY + knower->name() +
                               HIY "�Ǽ������������������ʶ����ˡ�" NOR;
                } else
                // �鿴���һ�α�ѯ�ʵ�������Ϣ���Ƿ��и���Ŀ
                {
                        last_ob = knower->query_temp("last_asked_quest");
                        if (! objectp(last_ob) || ! mapp(total[last_ob]))
                                return 0;

                        title = topic;
                }
        }

        // �����й�ĳ�������ĳ����Ŀ����Ϣ
        knower->set_temp("last_asked_quest", last_ob);
        answer = total[last_ob];

        if (! mapp(answer))
                return 0;

        // �������Ǽ��˾������Ϣ
        answer = answer[title];
        if (functionp(answer))
                return evaluate(answer, knower, who, topic);

        if (stringp(answer))
                return answer;

        return 0;
}
