// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int reply_whisper(object me, object who, string msg);
int ultra_whisper(object me, object who, string msg);
protected void special_bonus(object me, mixed arg);
protected void money_bonus(object me, mixed arg);

int main(object me, string arg)
{
       int r;
	string dest, msg;
	object ob;

	if (! arg)
		return notify_fail("你要对谁耳语些什么？\n");

	if (sscanf(arg, "%s about %s", dest, msg) != 2)
		if (sscanf(arg, "%s %s", dest, msg) != 2)
			return notify_fail("你要对谁耳语些什么？\n");

	ob = present(dest, environment(me));
	if (! ob || ! ob->is_character())
		return notify_fail("你要对谁耳语？\n");

        if (me->ban_say(1))
                return 0;

        if (me->query("doing") == "scheme")
        {
                if (me->query("jing") < 100)
                        return notify_fail("你现在的精神不济，等一会儿吧。\n");
                me->add("jing", -50);
        }

	write(WHT "你在" + ob->name() + WHT "的耳边悄声说道：" +
	      msg + "\n" NOR);
	tell_room(environment(me), me->name() + "在" + ob->name()
		+ "耳边小声地说了些话。\n", ({ me, ob }));
	if (! userp(ob)) 
        {
              r = 0;
              if (me->query("bunch_quest") && me->query("bunch_quest/type") == "传口信")
                      r = reply_whisper(me, ob, msg);
              if (! r)
                      if ((me->query("quest_dg") && me->query("quest_dg")["type"] == "传") ||
                          (me->query("quest_kh") && me->query("quest_kh")["type"] == "传") ||
                          (me->query("quest_hs") && me->query("quest_hs")["type"] == "传") ||
                          (me->query("quest_sn") && me->query("quest_sn")["type"] == "传"))
                              r = ultra_whisper(me, ob, msg);

              if (! r)
                      ob->relay_whisper(me, msg);
       }
	else
		tell_object(ob, WHT + me->name() +
				WHT "在你的耳边悄声说道：" + msg + "\n" NOR);
	return 1;
}

int reply_whisper(object me, object who, string msg)
{
        mapping bunch_quest,b;

        int exp;
        int pot;
        int score;
        int weiwang;

        bunch_quest = me->query("bunch_quest");

        //传错人了
        if (bunch_quest["target"] != base_name(who))
                return 0;

        //传错话了
        if (msg != bunch_quest["send_msg"])
                return 0;

        message_sort("$N面色凝重，一边听着一边对$n使劲的点头：“这位" +
                     RANK_D->query_respect(me) +
                     "，多谢你把话带到！”\n", who, me);

        // 奖励
        me->add("total_hatred",-2);
        if (me->query("total_hatred") < 0) me->set("total_hatred",0);

        exp = bunch_quest["bonus"];
        exp += random(exp/2);
        exp += atoi(count_div(me->query("combat_exp"), 5000));
        pot = exp/(2 + random(2));
        score = 5 + random(10);
        weiwang = 5 + random(10);

        b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "在把口信传给" + who->name() +
                         HIG "的过程中，经过锻炼" ]);

        GIFT_D->delay_bonus(me, b);

        me->delete("bunch_quest");
        me->add_temp("finish_bunch_times",1);

        return 1;
}

int ultra_whisper(object me, object who, string msg)
{
        mapping quest;
        int level;
        int i;
        int exp;
        int pot;
        int score;
        int weiwang;
        int mar;
	int quest_count;
        string the_quest;
	mixed special = 0;
        mixed money = 0;

        quest = me->query("quest_dg");
        the_quest = "独孤求败";
        if (!quest || quest["type"] != "传")
        {
                quest = me->query("quest_kh");
                the_quest = "葵花太监";
        }
        if (!quest || quest["type"] != "传")
        {
                quest = me->query("quest_hs");
                the_quest = "黄裳";
        }
        if (!quest || quest["type"] != "传")
        {
                quest = me->query("quest_sn");
                the_quest = "南海神尼";
        }

        if (!quest) return 0;

        if (userp(who)) return 0;

        //传错人了
        if (quest["name"] != who->name(1))
                return 0;

        //传错话了
        if (msg != quest["answer"])
                return 0;

        message_sort("$N面色凝重，一边听着一边对$n使劲的点头：“这位" +
                     RANK_D->query_respect(me) +
                     "，多谢你把口令带到！”\n", who, me);

        // 奖励
        level = quest["level"]+1;
        if (the_quest == "独孤求败")
        {
                if((i=me->query("questdg_times")) < 8)   i = 15-i;
                else i = 1;
        }
        if (the_quest == "葵花太监")
        {
                if((i=me->query("questkh_times")) < 15)   i = 15-i;
                else i = 1;
        }
        if (the_quest == "南海神尼")
        {
                if((i=me->query("questsn_times")) < 15)   i = 15-i;
                else i = 1;
        }
        if (the_quest == "黄裳")
        {
                if((i=me->query("quesths_times")) < 15)   i = 15-i;
                else i = 1;
        }

        exp = level*1000 + quest["bonus"]*50;
        exp *= 2;
        exp /= i;
        pot = exp/(2+random(2));
        score = random(exp/20);
        weiwang = random(exp/15);
        mar = 10 + random(40);

        GIFT_D->bonus(me, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                              "weiwang" : weiwang, "score" : score ]), 1);

        if (the_quest == "独孤求败")
        {
                me->add("questdg_times",1);
                quest_count = me->query("questdg_times")%500;
#ifdef DB_SAVE
                if (MEMBER_D->is_valid_member(me->query("id")))
                {
                        if (me->query("special_skill/sophistry"))
                        {
                        if (me->query("quesths_times") >= 4000)
                        me->set("questdg_times", 0);
                        } else {
                        if (me->query("questdg_times") >= 2000)
                        me->set("questdg_times", 0);
                        }
                }
                else
                {
#endif
                        if (me->query("questdg_times") >= 1000)
                        me->set("questdg_times", 0);
#ifdef DB_SAVE
                }
#endif
                me->delete("quest_dg");
        }
        if (the_quest == "葵花太监")
        {
                me->add("questkh_times",1);
                quest_count = me->query("questkh_times")%500;
#ifdef DB_SAVE
                if (MEMBER_D->is_valid_member(me->query("id")))
                {
                        if (me->query("special_skill/sophistry"))
                        {
                        if (me->query("questkh_times") >= 4000)
                        me->set("questkh_times", 0);
                        } else {
                        if (me->query("questkh_times") >= 2000)
                        me->set("questkh_times", 0);
                        } 
                } else
                {
#endif
                if (me->query("questkh_times") >= 1000)
                        me->set("questkh_times", 0);
#ifdef DB_SAVE
                } 
#endif
                me->delete("quest_kh");
        }
        if (the_quest == "黄裳")
        {
                me->add("quesths_times",1);
                quest_count = me->query("quesths_times")%500;
#ifdef DB_SAVE
                if (MEMBER_D->is_valid_member(me->query("id")))
                {
                        if (me->query("special_skill/sophistry"))
                        {
                        if (me->query("quesths_times") >= 4000)
                        me->set("quesths_times", 0);
                        } else {
                        if (me->query("quesths_times") >= 2000)
                        me->set("quesths_times", 0);
                        }
                }
                else
                {
#endif
                if (me->query("quesths_times") >= 1000)
                        me->set("quesths_times", 0);
#ifdef DB_SAVE
                }
#endif
                me->delete("quest_hs");
        }
        if (the_quest == "南海神尼")
        {
                me->add("questsn_times",1);
                quest_count = me->query("questsn_times")%500;
#ifdef DB_SAVE
                if (MEMBER_D->is_valid_member(me->query("id")))
                {
                        if (me->query("special_skill/sophistry"))
                        {
                        if (me->query("questsn_times") >= 4000)
                        me->set("questsn_times", 0);
                        } else {
                        if (me->query("questsn_times") >= 2000)
                        me->set("questsn_times", 0);
                        }
                }
                else
                {
#endif
                if (me->query("questsn_times") >= 1000)
                        me->set("questsn_times", 0);
#ifdef DB_SAVE
                }
#endif
                me->delete("quest_sn");
        }

        if (quest_count == 50)
		special = 1;
	else if (quest_count == 100)
		special = "/clone/gift/puti-zi";
        else if (quest_count == 150)
                money = 1;
        else if (quest_count == 200)
                money = 1;
        else if (quest_count == 250)
                money = 1;
   	else if (quest_count == 300)
		special = "/clone/gift/tianxiang";
   	else if (quest_count == 350)
		special = "/clone/gift/tianxiang";
   	else if (quest_count == 400)
                special = "/clone/misc/jiuzhuan";
	else if (quest_count == 450)
		special = "/clone/gift/jiuzhuan";
   	else if (quest_count == 0)
                special = "/clone/gift/xuanhuang";

	if (special) special_bonus(me, special);
        if (money) money_bonus(me,money);
            		
        me->add("total_hatred",-5);
        if (me->query("total_hatred") < 0) me->set("total_hatred",0);
        return 1;
}

protected void special_bonus(object me, mixed arg)
{
        array ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/hantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(me, 1);
        tell_object(me, HIM "你获得了一" + ob->query("unit") + ob->name() +
                        HIM "。\n" NOR);
}

void money_bonus(object me, mixed arg)
{
        array ob_list = ({
                "/clone/gift/jinkuai",
                "/clone/gift/jintiao",
                "/clone/gift/xiaoyuanbao",
                "/clone/gift/dayuanbao",
                "/clone/gift/jinding",
        });
        object ob;

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);

        ob->move(me,1);

        tell_object(me, HIM "你获得了一" + ob->query("unit") + ob->name() +
                        HIM "。\n" NOR);
}

int help(object me)
{
	write( @TEXT
指令格式：whisper <某人> about <讯息>

这个指令可以用来和同一房间中的人耳语，包括 NPC 在内。
其中的about可以省略。
TEXT );
	return 1;
}

