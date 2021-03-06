// renwoxing.c
// Update by haiyan

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

int ask_bijian();
string ask_jing();
mixed no_learn();
mixed ask_pfm();

void create()
{
        set_name("任我行", ({ "ren woxing", "ren","woxing" }));
        set("title", GRN "日月神教教主" NOR );
        set("long", "只见他一张长长的脸孔，脸色雪白，更无半分血色，眉目清秀，
身材甚高，一头黑发，穿的是一袭青衫。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("per", 27);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("yijinjing_count", 1);
        
        set("max_qi", 3000);
        set("max_jing", 1000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 400);
        set("combat_exp", 2000000);
        set("score", 500000);

        set_skill("force", 350);
        set_skill("riyue-xinfa", 330);
        set_skill("xixing-dafa", 350);
        set_skill("yijinjing", 220);
        set_skill("tianmo-jian", 360);
        set_skill("riyue-jian", 350);
        set_skill("cuff", 320);
        set_skill("xuwu-piaomiao", 320);
        set_skill("hand", 320);
        set_skill("huanmo-longtianwu", 320);
        set_skill("literate", 300);
        set_skill("dodge", 330);
        set_skill("unarmed", 330);
        set_skill("piaomiao-shenfa", 330);
        set_skill("parry", 320);
        set_skill("sword", 360);
        set_skill("damo-jian", 200);
        set_skill("taiji-jian", 200);
        set_skill("huifeng-jian", 200);
        set_skill("taishan-sword", 200);
        set_skill("hengshan-jian", 200);
        set_skill("hengshan-sword", 200);
        set_skill("huashan-jianfa", 200);
        set_skill("songshan-sword", 200);

        map_skill("dodge", "piaomiao-shenfa");
        map_skill("force", "xixing-dafa");
        map_skill("sword", "tianmo-jian");
        map_skill("parry", "tianmo-jian");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("hand", "huanmo-longtianwu");

        prepare_skill("cuff", "xuwu-piaomiao");
        prepare_skill("hand", "huanmo-longtianwu");

        set("no_teach", ([
            "xixing-dafa"    : "我已将吸星大法写成拓本，你去找来自己研读，我没空教你。",
            "yijinjing"      : "易筋经神功乃少林绝技，我虽习得，却也未得要领。",
            "damo-jian"      : (: no_learn :),
            "taiji-jian"     : (: no_learn :),
            "huifeng-jian"   : (: no_learn :),
            "taishan-sword"  : (: no_learn :),
            "hengshan-jian"  : (: no_learn :),
            "hengshan-sword" : (: no_learn :),
            "huashan-jianfa"  : (: no_learn :),
            "songshan-sword" : (: no_learn :),
        ]));

        create_family("日月神教", 1, "教主");

        set("inquiry", ([
                "吸星大法" : "我写的拓本还遗留在梅庄未曾取回，你去找找吧。\n",
                "比剑"     : (: ask_bijian :),
                "剑法"     : (: ask_bijian :),
                "易筋经"   : (: ask_jing :),
                "黑木令"   : "要拿黑木令？老夫想先看看你的剑法！\n",
                "绝招"     : (: ask_pfm :),
                "一剑穿心" : (: ask_pfm :),
        ]) );

        set("master_ob",4);
	setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object ob)
{
     if(! permit_recruit(ob))  return;

     if(ob->query("family/master_name") == "东方不败")
     {
          command("say 好你个" + RANK_D->query_rude(ob) +
                  "，既已跟随那个阉贼，还来找我做什么？快给我滚！");
          return;
     }

//     if((int)ob->query("combat_exp") < 250000)
     if (count_lt(ob->query("combat_exp"), 250000))
     {
          command("say 你经验太低了，还需要再多加磨练！");
          return;
     }

     if((int)ob->query_skill("riyue-xinfa", 1) < 140)
     {
          command("say 本教的内功心法你还没练好，还要多下苦功才行！");
          return;
     }

     command("haha");
     command("recruit " + ob->query("id")); 
     command("say 好！老夫今日又得一高徒，东方不败那阉贼死期就要到了！");
     ob->set("title", HIR "日月神教大护法" NOR);
}

int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        message_vision("$N躬身说道：“晚辈今日有幸拜见任老前辈，还望多加指教。”\n
$n笑道：“不用客气，你来解我寂寞，可多谢你啦。”\n", me, ob );
        message_vision("$N道：“不敢。”\n
$n点了点头，说道：“我只想瞧瞧你的剑法，并非真的过
招，再说，我也未必能胜得了你。”\n\n", me, ob);
        command("enable sword damo-jian");
        say(HIR"任我行大喝一声：“少林剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“才一招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"任我行大喝一声：“武当剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“才两招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"任我行大喝一声：“峨嵋剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“才三招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"任我行大喝一声：“嵩山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“才四招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }

        command("enable sword taishan-sword");
        say(HIR"任我行大喝一声：“泰山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“才五招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huashan-jianfa");
        say(HIR"任我行大喝一声：“华山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“才六招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"任我行大喝一声：“衡山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“才七招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"任我行大喝一声：“恒山剑法！”"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( (int)me->query("qi") < 0 || !present(me, environment()))
        {
                say("任我行叹了口气，说道：“还是没过八招。”\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        if (me->query_temp("heimuling"))
            say("任我行说道：“哈哈，这位" + RANK_D->query_respect(me) +
                "武功不错，快去帮我杀了东方不败那个阉贼！”\n");
        else
        {
            say("任我行说道：“这位" + RANK_D->query_respect(me) +
                "不错，我就送你一块黑木令吧。”\n");
            me->set_temp("heimuling", 1);
        }
            obj = new("/d/heimuya/obj/heimu-ling");
            obj -> move(me);
        command("enable sword tianmo-jian");
        return 1;
}

mixed no_learn()
{
        command("shake");
        command("say 这功夫是我闲时练来玩的，也不知练得对不对，你就不要学了。");
        return -1;
}

mixed ask_pfm()
{
     object me = this_player();

     if (me->query("can_perform/tianmo-jian/chuanxin"))
           return RANK_D->query_respect(me) + "是想和老夫切磋一下武艺？";

     if (me->query("family/family_name") != query("family/family_name"))
           return "本教武功独步武林，这位" + RANK_D->query_respect(me) +
                  "既然想学，不如入我日月神教如何？";

     if (me->query_skill("tianmo-jian", 1) < 250)
           return "你的天魔剑法尚欠火候，还领悟不了这招，再多练练去吧！";

     message_vision(HIY "$n" HIY "对$N" HIY "点了点头：这招讲究以意驭剑，瞧仔细了。\n" HIW
                    "只见$n" HIW "双足一点，腾空而起，手中长剑前探，紧跟着身子连转" HIW
                    "数圈，一道白影笔直向$N" HIW "射来。\n" NOR,
                    me, this_object());
     say(HIC"任我行飘然而落，还剑入鞘，微笑道：“看懂了没有？”\n"NOR);
     tell_object(me, HIY "你学会了「一剑穿心」这一招。\n" NOR);
     if (me->can_improve_skill("sword"))
             me->improve_skill("sword", 160000);
     me->set("can_perform/tianmo-jian/chuanxin", 1);
     return 1;
}

string ask_jing()
{
     object me, ob;
     string msg;

     me = this_player();
     if (me->query("family/family_name") != query("family/family_name"))
            return "少林易筋经神功名满江湖，若有幸习得，终生受用不尽。";

     if (me->query("family/master_id") != query("id"))
            return "据说曾有少林高僧将经文记录下来，不知是真是假。";


     if (objectp(present("yijinjing", me)))
            return "你不是已有经书了，还问我做什么。";

     if (me->query_temp("ask_jing") && time() - me->query_temp("ask_jing") < 120)
            return "跟你说了经书不在老夫身上，你不相信么？";

     if (random(3) != 0 || query("yijinjing_count") < 1)
     {
            if (me->query_temp("ask_jing"))
                  msg = "老夫还未曾将经书找回，你再等等吧。";
            else
                  msg = "经书此时并不在老夫身上。";
            me->set_temp("ask_jing", time());
            return msg;
     }

     add("yijinjing_count", -1);
     ob = new("/clone/book/yijinjing");
     ob->move(me);
     return "这卷经文你可要小心收好，千万勿示于他人。";
}

void reset()
{
     set("yijinjing_count", 1);
}

