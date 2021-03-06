// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// hong.c 洪七公

#include <ansi.h>;
#include "gaibang.h" 

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT; 
inherit F_NOCLONE; 

mixed ask_skill1(); 
mixed ask_skill2(); 
mixed ask_skill3(); 
mixed ask_skill4(); 
mixed ask_skill5(); 
mixed ask_skill6(); 
mixed ask_skill7(); 
mixed ask_skill8(); 
mixed ask_skill9(); 
mixed ask_skill10(); 
mixed ask_skill11(); 
mixed ask_skill12();

mixed ask_me(); 

#define YUZHU    "/clone/unique/yuzhu-zhang" 

int try_to_learn_ds(); 
int try_to_learn_db(); 

void create()
{
        set_name("洪七公", ({"hong qigong", "hong", "qigong"}));
        set("long", @LONG
他就是丐帮第十七任帮主，号称九指神丐的洪 
七公老爷子。只见他须眉皆白，周身上下邋遢 
不已，模样甚是龌龊。可是他目光如电，显得 
正义凛然，不怒而自威。 
他一张长方脸，颌下微须，粗手大脚，身上衣
服东一块西一块的打满了补丁，却洗得干干净
净。
LONG);

        set("nickname", HIW "北丐" NOR); 
        set("gender", "男性");
        set("class", "beggar");
        set("age", 75);
        set("attitude", "peaceful");
        
        set("str", 35);
        set("int", 24);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 6500); 
        set("max_jing", 55000); 
        set("neili", 75000); 
        set("max_neili", 75000); 
        set("jiali", 300); 
        set("combat_exp", 4000000); 
        set("level", 60);
        set("score", 400000); 
        set("shen_type", 1); 
        set("book_count", 1);
        
        set_skill("force", 500);             // 基本内功
        set_skill("array", 500);         
        set_skill("dagou-zhen", 500);             
        set_skill("huntian-qigong", 500);    // 混天气功
        set_skill("yijin-duangu", 500);      // 易筋锻骨
        set_skill("unarmed", 530);
        set_skill("changquan", 530);
        set_skill("strike", 500);            // 基本掌法
        set_skill("dragon-strike", 500);     // 降龙十八掌
        set_skill("hand", 500);              // 基本手法 
        set_skill("shexing-diaoshou", 500);  // 蛇行刁手
        set_skill("dodge", 500);             // 基本躲闪
        set_skill("feiyan-zoubi", 500);      // 飞檐走壁
        set_skill("xiaoyaoyou", 500);        // 逍遥游掌
        set_skill("parry", 500);             // 基本招架
        set_skill("dagou-bang", 500);        // 打狗棒法
        set_skill("jiaohua-bangfa", 500);
        set_skill("staff", 500);             // 基本杖法
        set_skill("fengmo-zhang", 500);      // 疯魔杖法 
        set_skill("blade", 500);             // 基本刀法
        set_skill("liuhe-dao", 500);         // 六合刀
        set_skill("throwing", 500);          // 基本暗器
        set_skill("mantianhuayu", 500);      // 满天花雨
        set_skill("begging", 500);           // 叫化绝活
        set_skill("checking", 500);          // 道听途说
        set_skill("training", 500);          // 驭兽术
        set_skill("literate", 500);          // 读书写字
        set_skill("martial-cognize", 400);   // 武学修养
        /*
        set_skill("kanglong-youhui", 500);   // 1 
       	set_skill("feilong-zaitian", 500);   // 2 
       	set_skill("jianlong-zaitian", 500);  // 3 
       	set_skill("hongjian-yulu", 500);     // 4 
       	set_skill("qianlong-wuyong", 500);   // 5 
       	set_skill("lishe-dachuan", 500);     // 6 
       	set_skill("turu-qilai", 500);        // 7 
       	set_skill("zhenjing-baili", 500);    // 8 
       	set_skill("huoyue-zaiyuan", 500);    // 9 
       	set_skill("shuanglong-qushui", 500); // 10 
       	set_skill("yuyue-yuyuan", 500);      // 11 
       	set_skill("shicheng-liulong", 500);  // 12 
       	set_skill("miyun-buyu", 500);        // 13 
       	set_skill("sunze-youfu", 500);       // 14 
       	set_skill("longzhan-yuye", 500);     // 15 
       	set_skill("lvshuang-bingzhi", 500);  // 16 
       	set_skill("diyang-chufan", 500);     // 17 
       	set_skill("shenlong-baiwei", 500);   // 18 
       	*/
        
        map_skill("force", "huntian-qigong");
        map_skill("strike", "dragon-strike");
        map_skill("hand",  "shexing-diaoshou");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dagou-bang");
        map_skill("staff", "dagou-bang");
        map_skill("blade", "liuhe-dao");
        map_skill("throwing", "mantianhuayu");
        map_skill("unarmed", "changquan");
        
        prepare_skill("strike", "dragon-strike");
        
        set("no_teach", ([ 
                "dragon-strike" : (: try_to_learn_ds :), 
                "dagou-bang"    : (: try_to_learn_db :), 
        ])); 
       
        set("inquiry", ([ 
                "青竹令"   : "老叫花可没功夫管这么多闲事，你去扬州找小左吧！\n",
                "青竹林"   : "东北西北东西北。\n",
                "丐帮"     : "东北西北东西北。\n",
                "小菜"     : "最想吃的是蓉儿烧的叫化鸡，牛肉条，好逑汤，炒白菜，蒸豆腐……唉！\n",
                "好吃的"   : "最想吃的是蓉儿烧的叫化鸡，牛肉条，好逑汤，炒白菜，蒸豆腐……唉！\n",
                "黄蓉"     : "这小娃娃烧的叫化鸡，牛肉条，好逑汤，炒白菜，蒸豆腐最好吃。\n",
                "蓉儿"     : "这小娃娃烧的叫化鸡，牛肉条，好逑汤，炒白菜，蒸豆腐最好吃。\n",
                // "玉竹杖"   : (: ask_me :), 
                "仙游诀"   : (: ask_skill1 :), 
                "掷金针"   : (: ask_skill2 :), 
                "缠字诀"   : (: ask_skill3 :), 
                "戳字诀"   : (: ask_skill4 :), 
                "封字诀"   : (: ask_skill5 :), 
                "绊字诀"   : (: ask_skill6 :), 
                "天下无狗" : (: ask_skill7 :), 
                "擒龙手"   : (: ask_skill8 :), 
                "雷霆一击" : (: ask_skill9 :), 
                "龙翔九天" : (: ask_skill10 :), 
                "亢龙有悔" : (: ask_skill11 :), 
                "排山倒海" : (: ask_skill12 :),
        ])); 

        set("chat_chance", 1);
        set("chat_msg", ({
                "洪七公摸着肚皮叹道：“唉，好久没吃到蓉儿烧的小菜了……”\n",
                "洪七公往地下角落一躺，开始睡觉，边睡边喃喃道：“啊，叫化鸡……好香！好香！”\n",
                "洪七公说道：“俗话说「吃在江南」，所以老叫化特地跑来扬州看看。”\n",
                "洪七公摇头叹道：“如今这帮小叫化怎么好像都不会烧菜了？”\n",
                "洪七公喃喃道：“我们丐帮的「降龙十八掌」是天下最霸道的掌法。”\n",
        }));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({ 
                (: perform_action, "strike.xiang" :), 
                (: perform_action, "strike.hui" :), 
                (: perform_action, "strike.lei" :), 
                (: perform_action, "dodge.xian" :), 
                (: perform_action, "staff.chan" :), 
                (: perform_action, "staff.chuo" :), 
                (: perform_action, "staff.feng" :), 
                (: perform_action, "staff.ban" :), 
                (: perform_action, "staff.tian" :), 
                (: exert_function, "recover" :), 
                (: exert_function, "powerup" :), 
        })); 

        create_family("丐帮", 17, "帮主");
        set_temp("apply/damage", 100); 
        set_temp("apply/unarmed_damage", 100); 
        set_temp("apply/armor", 200); 

        set("master_ob",5);
	setup();
        
        carry_object("/clone/unique/yuzhu-zhang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        
        set("startroom", "/d/city/gbxiaowu"); 
        check_clone(); 
}

void attempt_apprentice(object ob) 
{ 
        string title = ob->query("title"); 
        int lvl = ob->query("family/beggarlvl"); 

        if (! permit_recruit(ob)) 
                return; 
 
        if ((int)ob->query("level") < 3) 
        { 
                command("hmm"); 
                command("say 你的经验这么差，又能跟我学什么？"); 
                return; 
        } 

        if (ob->query_str() < 40 && ob->query_int() < 40 
            && ob->query_con() < 40 && ob->query_dex() < 40) 
        { 
                command("say 我说你这人体格也不行，脑筋也不灵光，还能和我学什么？"); 
                return; 
        } 

        if ((int)ob->query_skill("force") < 180) 
        { 
                command("hmm"); 
                command("say 你的内功火候太差了，先好好练练再来找我。"); 
                return; 
        } 
 
        if ((int)ob->query("max_neili") < 2000) 
        { 
                command("hmm"); 
                command("say 就你那点内力哪里学得了什么上乘武功？"); 
                return; 
        } 
        command("say 念你平时用功努力，今日老叫花就收下你。"); 
        command("say 以后好好练功，可别给我丢脸。"); 
        command("recruit " + ob->query("id")); 

        if (ob->query("class") != "beggar") 
                ob->set("class", "beggar"); 

        if (lvl > 0) 
        { 
                ob->set("family/beggarlvl", lvl); 
                ob->set("title", title); 
        } 
} 

int recognize_apprentice(object me, string skill) 
{ 
        if (! me->query("can_learn/hong/dragon-strike") 
            && ! me->query("can_learn/hong/xiaoyaoyou")) 
        { 
                command("say 你是谁？哪里来的？要干啥？"); 
                return -1; 
        } 

        if ((me->query("can_learn/hong/dragon-strike") 
            && skill != "dragon-strike" 
            && skill != "strike") 
            || (me->query("can_learn/hong/xiaoyaoyou") 
            && skill != "xiaoyaoyou" 
            && skill != "strike")) 
        { 
                command("say 老叫花教你什么就学什么，你不学就算了。"); 
                return -1; 
        } 
  
        if (skill == "strike" 
            && me->query_skill("strike", 1) > 379) 
        { 
                command("say 到此为止，你的功力也不差了，剩下的自己去练。"); 
                return -1; 
        } 
        return 1; 
} 

int try_to_learn_db() 
{ 
        object me; 

        me = this_player(); 
        if (me->query("can_learn/hong/dagou-bang")) 
                return 0; 

        if (me->query("family/beggarlvl") < 7) 
        { 
                command("say 也不看看你是什么辈分，居然想学打狗棒法？"); 
                return -1; 
        } 

        if (me->query("shen") < 80000) 
        { 
                command("say 你的侠义正事还做得不够，这套杖法我暂时还不能传你。"); 
                return -1; 
        } 

        command("sigh"); 
        command("say 这套打狗棒法乃历代相传，本来只有历代继任帮主才能研学。"); 
        command("say 不过现在江湖争乱，你也算是本帮高手，便是学之无妨。"); 
        me->set("can_learn/hong/dagou-bang", 1); 
        return 0; 
} 

int try_to_learn_ds() 
{ 
        object me; 
        object sob; 
        int i; 
        int flag; 
        string *sub_skills; 

        me = this_player(); 

        if (! me->query("can_learn/hong/dragon-strike")) 
                return -1; 
                
        if (me->query("family/family_name") != query("family/family_name"))
        {
                command("say 本来想传授你降龙十八掌，但可惜你不是我丐帮的。");
                me->delete("can_learn/hong/dragon-strike");
                return -1;
        }
                       
        if (me->query("family/family_name") == query("family/family_name") 
            && me->query("family/beggarlvl") < 9) 
        { 
                command("say 你要学降龙十八掌？等你升到本帮长老再说吧！"); 
                return -1; 
        } 

        if (me->query("family/family_name") != query("family/family_name") 
            && ! me->query("can_learn/hong/dragon-strike")) 
        { 
                command("say 你是哪里来的？一边呆着去。"); 
                return -1; 
        } 

        if (me->query("shen") < 80000) 
        { 
                command("say 你的侠义正事还做得不够，我可不放心传你绝技。"); 
                return -1; 
        } 

        sob = find_object(SKILL_D("dragon-strike")); 

        if (! sob) 
        sob = load_object(SKILL_D("dragon-strike")); 

        if (! sob->valid_learn(me)) 
                return 0; 

        if (me->query_skill("dragon-strike", 1)) 
        { 
                command("say 你不是已经会了么？自己好好练吧。"); 
                return -1; 
        } 
 
        sub_skills = keys(sob->query_sub_skills()); 
   
        flag = 0; 
        for (i = 0; i < sizeof(sub_skills); i++) 
        { 
                if (me->query_skill(sub_skills[i], 1) >= 10) 
                        continue; 

                me->set_skill(sub_skills[i], 10); 

                if (! flag) 
                { 
                        flag = 1; 
                        command("nod"); 
                        command("say 我将十八路掌法传授与你，假以时" 
                                "日，必能融会贯通。"); 
                } 
                tell_object(me, HIC "你对" + to_chinese(sub_skills[i]) + "有了" 
                            "一些领悟。\n" NOR); 
        } 

        if (! flag) 
        { 
                command("say 不是说了待到你融会贯通再来向我讨教吗？"); 
                return -1; 
        } 

        command("say 你先将这十八路掌法融会贯通，合而为一再说吧。"); 
        notify_fail("你自己下去好好练习吧。\n"); 
        return -1; 
}

int accept_object(object who, object ob) 
{ 
        int lv; 
        string by; 
        object me; 
        string hid; 
        object hob; 
        int r;

        me = this_object(); 

        if (r = ::accept_object(who, ob))  
                return r;  

        if (! ob->query("food_supply")) 
        {
                command("say 这东西看上去也没啥特别的，你自个留着吧。");
                return -1; 
        } 
  
        if (! intp(lv = ob->query("level")) 
            || lv < 1 
            || ! stringp(by = ob->query("by"))) 
        { 
                command("say 这东西看上去也没啥特别的，你自个留着吧。"); 
                return -1; 
        } 
   
        if (lv < 100) 
        { 
                message_vision(CYN "$N" CYN "嗅了嗅" + ob->name() + 
                               CYN "，皱眉道：这东西你还是自个留着" 
                               "吧。\n" NOR, me); 
                return -1; 
        } 
   
        if (lv < 120) 
        { 
                message_vision(CYN "$N" CYN "嗅了嗅" + ob->name() + 
                               CYN "道：味道不错，可还是稍微欠那么" 
                               "点儿火候。\n" NOR, me); 
                return -1; 
        } 
   
        message_vision(HIW "$N" HIW "嗅了嗅$n" HIW "递来的" + ob->name() + 
                       HIW "，尝了几口，直咂舌头，连声称赞。\n" NOR, me, who); 
 
        if (! who->id(by)) 
        { 
                command("say 可惜不知道是谁做的，有空可得给我引见引见。"); 
                return 1; 
        } 
   
        if (who->query("gender") != "女性") 
        { 
                command("say 想不到你一个大老爷们手艺也不错。难得，难得。"); 
                return 1; 
        } 
   
        /*
        if (who->query("family/family_name") == query("family/family_name")) 
        { 
                command("say 帮里有你这样的人真不错，以后就靠你多照顾了。"); 
                return 1; 
        } 
        */

        if (who->query("can_learn/hong/xiaoyaoyou") >= 1 &&
            who->query("can_learn/hong/dragon-strike") >= 1)
        { 
                command("pat " + who->query("id")); 
                command("say 又给老叫花解搀来了？多谢，多谢。"); 
                return 1; 
        } 
        command("stuff"); 
        command("say 老叫花没啥值钱的，就传你一套拳法作为报答吧。"); 
 
        tell_object(who, HIC "\n洪七公同意传授你「逍遥游拳法」。\n" NOR); 
        who->add("can_learn/hong/xiaoyaoyou", 1); 
        // who->improve_skill("martial-cognize", 1500000); 
   
        // if (lv >= 200 && (string)ob->query("name") == "叫化鸡") 
        if (lv >= 200)
        {
                // message_vision("洪七公叫道：啊……这正是我想吃的叫化鸡呀！\n", 
                                // me, who);  
                message_vision(CYN "\n$N" CYN "沉思良久，又道：想不" 
                               "到除了黄丫头，居然还有人能做出如此美" 
                               "味。\n" NOR, me, who); 
  
                if (! stringp(hid = who->query("couple/couple_id"))) 
                { 
                        if (who->query("family/family_name") != query("family/family_name") ||
                            ! who->query("zhuanshi"))
                        {
                                command("say 却不知你如今有婆家了没有，可要" 
                                        "老叫花给你介绍？"); 
                                return 1; 
                        } else
                        {
                                tell_object(who, HIC "\n洪七公同意传授你「降龙十八掌」。\n" NOR); 
                                who->add("can_learn/hong/dragon-strike", 1); 
                                who->improve_skill("martial-cognize", 1500000); 
                        }
                } 
   
                if (! objectp(hob = find_player(hid))) 
                {
                        command("sigh"); 
                        command("say 可惜你那位不在，否则我倒是可以" 
                                "传他两手功夫。罢了，罢了。"); 
                        return 1; 
                } 
 
                if (hob->query("family/family_name") != query("family/family_name")) 
                { 
                        command("say " + hob->name(1) + "能娶到你这" 
                                "样的老婆，也不枉了。"); 
                        return 1; 
                } 
                if (hob->query("can_learn/hong/dragon-strike"))
                {
                        command("say " + hob->name(1) + "已经会了「降龙十八掌」，看" 
                                "来我这回是白吃了，多谢，多谢。"); 
                        return 1; 
                } 

                command("say 什么时候空了也叫你那位来，我也教他点东西。"); 
   
                tell_object(hob, HIC "\n洪七公同意传授你「降龙十八掌」。\n" NOR); 
                hob->set("can_learn/hong/dragon-strike", 1); 
                hob->improve_skill("martial-cognize", 1500000); 
        } 
        destruct(ob); 
        return 1; 
} 

mixed ask_skill1()
{
        object me;
        me = this_player();

        if (me->query("can_perform/xiaoyaoyou/xian"))
                return "我不是已经教过你了么？";

        if (me->query("family/family_name") != "丐帮"
            && ! me->query("can_learn/hong/xiaoyaoyou"))
                return "你打听这个干嘛？我认识你么？";

        if (me->query_skill("xiaoyaoyou", 1) < 1)
                return "你连逍遥游拳法都没学过，哪里来绝招？";

        if (me->query("family/family_name") == "丐帮"
            && me->query("family/gongji") < 300)
                return "你在帮中无所作为，还想让我传功给你？。";

        if (me->query("shen") < 10000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 120)
                return "你的内功火候不足，先下去练熟了再来。";

        if (me->query_skill("xiaoyaoyou", 1) < 100)
                return "你的逍遥游拳法火候未到，再下去练练。";

        message_sort(HIY "\n$n" HIY "愣了一愣，随即伸手将$N"
                     HIY "招到了面前，在$N" HIY "耳边轻声嘀"
                     "咕了些话。$N" HIY "听了半天，突然间不"
                     "由会心的一笑，看来大有所悟。\n\n" NOR,
                     me, this_object());

        command("say 口诀都传给你了，自己下去领悟吧。");
        tell_object(me, HIC "你学会了「仙游诀」。\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("xiaoyaoyou"))
                me->improve_skill("xiaoyaoyou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/xiaoyaoyou/xian", 1);

        if (me->query("family/family_name") == "丐帮")
                me->add("family/gongji", -300);

        return 1;
}

mixed ask_skill2()
{
        object me;
        me = this_player();

        if (me->query("can_perform/mantianhuayu/zheng"))
                return "我不是已经教过你了么？还罗嗦什么？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "干啥？我什么时候说过要教你？";

        if (me->query_skill("mantianhuayu", 1) < 1)
                return "你连漫天花雨都没学过，哪里来绝招？";

        if (me->query("family/gongji") < 300)
                return "你在帮中无所作为，还想让我传功给你？。";

        if (me->query("shen") < 10000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 200)
                return "你的内功火候不足，先下去练熟了再来。";

        if (me->query_skill("mantianhuayu", 1) < 150)
                return "你的漫天花雨火候未到，再下去练练。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，将$N" HIY "招至跟前，轻"
                     "声在$N" HIY "耳旁嘀咕了半天。随后又伸出右手，十指"
                     "箕张，一伸一缩，看样子是一种很特别的暗器法门。\n"
                     "\n" NOR, me, this_object());

        command("say 这招的精要就是出手迅捷，攻敌不备，记好了？");
        tell_object(me, HIC "你学会了「掷金针」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("mantianhuayu"))
                me->improve_skill("mantianhuayu", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/mantianhuayu/zheng", 1);
        me->add("family/gongji", -300);

        return 1;
}

mixed ask_skill3()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dagou-bang/chan"))
                return "我不是已经教过你了么？还罗嗦什么？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "干啥？我什么时候说过要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你连打狗棒法都没学过，哪里来绝招？";

        if (me->query("family/gongji") < 300)
                return "你在帮中无所作为，还想让我传功给你？。";

        if (me->query("shen") < 80000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 100)
                return "你的内功火候不足，回去练高点再来。";

        if (me->query_skill("dagou-bang", 1) < 60)
                return "你的打狗棒法火候未到，再回去练练。";

        message_sort(HIY "\n$n" HIY "看了$N" HIY "一眼，皱了皱眉，当"
                     "下拍了拍身上的尘土，起身而立。$N" HIY "正感疑惑"
                     "间，却只见眼前一道绿芒闪过，四周皆是$n" HIY "挥"
                     "出的棒影，窜动不已，顿被闹了个手忙脚乱。\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say 打狗棒招式以轻盈灵巧著称，你在这方面得多下工夫。");
        tell_object(me, HIC "你学会了「缠字诀」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dagou-bang/chan", 1);
        me->add("family/gongji", -300);

        return 1;
}

mixed ask_skill4()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dagou-bang/chuo"))
                return "我不是已经教过你了么？还罗嗦什么？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "干啥？我什么时候说过要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你连打狗棒法都没学过，哪里来绝招？";

        if (me->query("family/gongji") < 600)
                return "你在帮中无所作为，还想让我传功给你？。";

        if (me->query("shen") < 80000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 160)
                return "你的内功火候不足，回去练高点再来。";

        if (me->query_skill("dagou-bang", 1) < 100)
                return "你的打狗棒法火候未到，再回去练练。";

        message_sort(HIY "\n$n" HIY "哈哈一笑，将$N" HIY "招至跟前，轻"
                     "声在$N" HIY "耳旁嘀咕了半天。随后又拔出腰间的玉竹"
                     "杖虚击划圆，再猛的直刺而出，看样子是一种很精妙的"
                     "杖法绝学。$N" HIY "一边听一边不住的点头。\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say 这招容易制敌残废，使用时得多加留意。");
        tell_object(me, HIC "你学会了「戳字诀」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dagou-bang/chuo", 1);
        me->add("family/gongji", -600);

        return 1;
}

mixed ask_skill5()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dagou-bang/feng"))
                return "我不是已经教过你了么？还罗嗦什么？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "干啥？我什么时候说过要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你连打狗棒法都没学过，哪里来绝招？";

        if (me->query("family/gongji") < 1500)
                return "你在帮中无所作为，还想让我传功给你？。";

        if (me->query("shen") < 80000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 180)
                return "你的内功火候不足，回去练高点再来。";

        if (me->query_skill("dagou-bang", 1) < 120)
                return "你的打狗棒法火候未到，再回去练练。";

        message_sort(HIY "\n$n" HIY "愣了一愣，随即伸手将$N"
                     HIY "招到了面前，在$N" HIY "耳边轻声嘀"
                     "咕了些话。$N" HIY "听了半天，突然间不"
                     "由会心的一笑，看来大有所悟。\n\n" NOR,
                     me, this_object());

        command("nod");
        command("say 遇强时使用这招足当自保，下去后再多练练。");
        tell_object(me, HIC "你学会了「封字诀」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dagou-bang/feng", 1);
        me->add("family/gongji", -1500);

        return 1;
}

mixed ask_skill6()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dagou-bang/ban"))
                return "我不是已经教过你了么？还罗嗦什么？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "干啥？我什么时候说过要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你连打狗棒法都没学过，哪里来绝招？";

        if (me->query("family/gongji") < 1800)
                return "你在帮中无所作为，还想让我传功给你？。";

        if (me->query("shen") < 100000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 240)
                return "你的内功火候不足，回去练高点再来。";

        if (me->query_skill("dagou-bang", 1) < 180)
                return "你的打狗棒法火候未到，再回去练练。";

        message_sort(HIY "\n$n" HIY "看了$N" HIY "一眼，皱了皱眉，当"
                     "下拍了拍身上的尘土，起身而立。$N" HIY "正感疑惑"
                     "间，却只见眼前一道绿芒闪过，四周皆是$n" HIY "挥"
                     "出的棒影，窜动不已，顿被闹了个手忙脚乱。\n\n"
                     NOR, me, this_object());

        command("haha");
        command("say 这招的精要乃是出奇制胜，你下去后自己体会吧。");
        tell_object(me, HIC "你学会了「绊字诀」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dagou-bang/ban", 1);
        me->add("family/gongji", -1800);

        return 1;
}
/*
mixed ask_skill7()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dagou-bang/tian"))
                return "自己去练吧，老缠着我干什么？";

        if (me->query("family/family_name") != query("family/family_name"))
                return "干啥？我什么时候说过要教你？";

        if (me->query_skill("dagou-bang", 1) < 1)
                return "你连打狗棒法都没学过，哪里来绝招？";

        if (me->query("family/gongji") < 2000)
                return "你在帮中无所作为，还想让我传功给你？。";

        if (me->query("shen") < 100000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query("family/beggarlvl") < 9)
                return "你在帮中的辈分还不够，等成为长老再说吧。";

        if (! me->query("can_perform/dagou-bang/chan")
           || ! me->query("can_perform/dagou-bang/chuo")
           || ! me->query("can_perform/dagou-bang/feng")
           || ! me->query("can_perform/dagou-bang/ban"))
                return "你打狗棒法的四个棒诀都了解透彻了么？";

        if (me->query_skill("force") < 300)
                return "你的内功火候不足，回去练高点再来。";

        if (me->query_skill("dagou-bang", 1) < 220)
                return "你的打狗棒法火候未到，再回去练练。";

        message_sort(HIY "\n$n" HIY "凝视了$N" HIY "好一会，方才"
                     "点了点头，随手抄起玉竹杖，蓦地一卷，带起阵"
                     "阵风声，便犹若千百根相似，层层叠叠将$N" HIY
                     "笼罩于劲风之中，招式精奇，无与伦比，令人叹"
                     "为观止。\n\n" NOR, me, this_object());

        command("stuff");
        command("say 你到了这个程度，我也没啥好教的了，自己多练吧。");
        tell_object(me, HIC "你学会了「天下无狗」。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1500000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1500000);
        if (me->can_improve_skill("dagou-bang"))
                me->improve_skill("dagou-bang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dagou-bang/tian", 1);
        me->add("family/gongji", -2000);

        return 1;
}
*/
mixed ask_skill7()
{
        object me, obj;

        me = this_player();

        if (me->query("family/family_name") != query("family/family_name"))
                return "你一边去。";

        if (me->query_skill("dagou-bang", 1) < 250)
                return "你的打狗棒法学得怎么样啊？我看还差得远呢！";

        if (query("book_count") <1)
                return "你来晚了，打狗棒秘籍我已经借出去了。";
        obj = new(__DIR__"obj/book.c");
        obj->set("master", me->query("id"));
        obj->move(me);
        tell_object(me, "洪七公说道：“好吧，这本秘籍你拿去好好研究吧！”\n");        
        add("book_count", -1);
        return 1;
}

mixed ask_skill8()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dragon-strike/qin"))
                return "我不是已经教过你了么？";

        if (me->query("family/family_name") != "丐帮"
           && ! me->query("can_learn/hong/dragon-strike"))
                return "你打听这个干嘛？我认识你么？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你连降龙十八掌都没学过，哪里来绝招？";

        if (me->query("family/family_name") == "丐帮"
           && me->query("family/gongji") < 800)
                return "你在帮中无所作为，这招暂时还不能传你。";

        if (me->query("shen") < 100000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 300)
                return "你内功火候不足，暂时还无法运用这招。";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "你的降龙十八掌火候未到，再下去练练。";

        message_sort(HIY "\n$n" HIY "点了点头，转过身来对$N" HIY "说"
                     "道：“我给你演示一遍，看好了。”话音刚落，听得"
                     "$n" HIY "一声暴喝，全身内劲迸发，气贯右臂奋力外"
                     "扯。一时间你只觉周围气流涌动，地上尘土尽数向$n"
                     HIY "的掌心涌去。\n\n" NOR, me, this_object());

        command("say 招式便是如此，你自己下去领悟吧。");
        tell_object(me, HIC "你学会了「擒龙手」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dragon-strike/qin", 1);

        if (me->query("family/family_name") == "丐帮")
                me->add("family/gongji", -800);

        return 1;
}

mixed ask_skill9()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dragon-strike/lei"))
                return "我不是已经教过你了么？";

        if (me->query("family/family_name") != "丐帮"
           && ! me->query("can_learn/hong/dragon-strike"))
                return "你打听这个干嘛？我认识你么？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你连降龙十八掌都没学过，哪里来绝招？";

        if (me->query("family/family_name") == "丐帮"
           && me->query("family/gongji") < 2000)
                return "你在帮中无所作为，这招暂时还不能传你。";

        if (me->query("shen") < 100000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 300)
                return "你内功火候不足，暂时还无法运用这招。";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "你的降龙十八掌火候未到，再下去练练。";

        message_sort(HIY "\n$n" HIY "点了点头，转过身来对$N" HIY "说"
                     "道：“我给你演示一遍，看好了。”话音刚落，听得"
                     "$n" HIY "一声暴喝，全身真气鼓动，双掌排山倒海般"
                     "压出。顿时只听“喀嚓”一声脆响，$n" HIY "身前那"
                     "棵碗口粗的松树应声而倒，直看得$N" HIY "目瞪口呆"
                     "，半天说不出话来。\n\n" NOR, me, this_object());

        command("sweat");
        command("say 招式便是如此，你自己下去领悟吧。");
        tell_object(me, HIC "你学会了「雷霆一击」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dragon-strike/lei", 1);

        if (me->query("family/family_name") == "丐帮")
                me->add("family/gongji", -2000);

        return 1;
}

mixed ask_skill10()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dragon-strike/xiang"))
                return "我不是已经教过你了么？";

        if (me->query("family/family_name") != "丐帮"
           && ! me->query("can_learn/hong/dragon-strike"))
                return "你打听这个干嘛？我认识你么？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你连降龙十八掌都没学过，哪里来绝招？";

        if (me->query("family/family_name") == "丐帮"
           && me->query("family/gongji") < 3000)
                return "你在帮中无所作为，这招暂时还不能传你。";

        if (me->query("shen") < 100000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force") < 300)
                return "你内功火候不足，暂时还无法运用这招。";

        if (me->query_skill("dragon-strike", 1) < 150)
                return "你的降龙十八掌火候未到，再下去练练。";

        message_sort(HIY "\n$n" HIY "沉思良久，方才缓缓点了点头，伸"
                     "手将$N" HIY "招至身旁，低声讲解了良久。过得片"
                     "刻，却见$n" HIY "蓦地起身而立，深深吸入一口气"
                     "，双掌猛然翻滚，宛如一条神龙攀蜒于九天之上，气"
                     "势恢弘，荡气回肠。\n\n" NOR, me, this_object());

        command("nod");
        command("say 修炼这招颇为不易，你下去后需勤加练习。");
        tell_object(me, HIC "你学会了「龙翔九天」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dragon-strike/xiang", 1);

        if (me->query("family/family_name") == "丐帮")
                me->add("family/gongji", -3000);

        return 1;
}

mixed ask_skill11()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dragon-strike/hui"))
                return "我不是已经教过你了么？";

        if (me->query("family/family_name") != "丐帮"
           && ! me->query("can_learn/hong/dragon-strike"))
                return "你打听这个干嘛？我认识你么？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你连降龙十八掌都没学过，哪里来绝招？";

        if (me->query("family/family_name") == "丐帮"
           && me->query("family/gongji") < 3000)
                return "你在帮中无所作为，这招暂时还不能传你。";

        if (me->query("shen") < 120000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force", 1) < 260)
                return "你基本内功火候不足，暂时还无法运用这招。";

        if (me->query_skill("dragon-strike", 1) < 220)
                return "你的降龙十八掌火候未到，再下去练练。";

        message_sort(HIY "\n$n" HIY "沉思良久，方才缓缓点了点头，伸"
                     "手将$N" HIY "招至身旁，低声讲解了良久。过得片"
                     "刻，忽然$n" HIY "身形激进，左手一划，右手呼的一掌"
                     "拍向虚空，正是降龙十八掌“亢龙有悔” 。力自掌生之"
                     "际说到便到，以排山倒海之势向虚空狂涌而去，当真石"
                     "破天惊，威力无比。\n\n" NOR, me, this_object());

        command("nod");
        command("say 修炼这招颇为不易，你下去后需勤加练习。");
        tell_object(me, HIC "你学会了「亢龙有悔」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dragon-strike/hui", 1);

        if (me->query("family/family_name") == "丐帮")
                me->add("family/gongji", -3000);

        return 1;
}

mixed ask_skill12()
{
        object me;
        me = this_player();

        if (me->query("can_perform/dragon-strike/pai"))
                return "我不是已经教过你了么？";

        if (me->query("family/family_name") != "丐帮"
           && ! me->query("can_learn/hong/dragon-strike"))
                return "你打听这个干嘛？我认识你么？";

        if (me->query_skill("dragon-strike", 1) < 1)
                return "你连降龙十八掌都没学过，哪里来绝招？";

        if (me->query("family/family_name") == "丐帮"
           && me->query("family/gongji") < 1000)
                return "你在帮中无所作为，这招暂时还不能传你。";

        if (me->query("shen") < 120000)
                return "你侠义之事做得不够，我可不放心传功予你。";

        if (me->query_skill("force", 1) < 260)
                return "你基本内功火候不足，暂时还无法运用这招。";

        if (me->query_skill("dragon-strike", 1) < 220)
                return "你的降龙十八掌火候未到，再下去练练。";

        message_sort(HIY "\n$n" HIY "沉思良久，方才缓缓点了点头，伸"
                     "手将$N" HIY "招至身旁，低声讲解了良久。过得片"
                     "刻，忽然$n" HIY "身形激进，全身真气鼓动，双掌"
                     "以排山倒海之势向虚空狂涌而去，当真石"
                     "破天惊，威力无比。\n\n" NOR, me, this_object());

        command("nod");
        command("say 修炼这招颇为不易，你下去后需勤加练习。");
        tell_object(me, HIC "你学会了「排山倒海」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("dragon-strike"))
                me->improve_skill("dragon-strike", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/dragon-strike/pai", 1);

        if (me->query("family/family_name") == "丐帮")
                me->add("family/gongji", -1000);

        return 1;
}
    
mixed ask_me() 
{ 
        object me; 
        object ob; 
        object owner; 
      
        me = this_player(); 
      
        if (me->query("family/family_name") != "丐帮") 
                return "你问这个干嘛？呆一边去。"; 
     
        if (me->query("family/master_id") != query("id")) 
                return "嘿，就凭你也想用玉竹杖？"; 
      
        if (me->query_skill("dagou-bang", 1) < 150) 
                return "就你这样的棒法也想用玉竹杖？"; 
      
        if (me->query("shen") < 80000) 
                return "你侠义之事做得不够，我岂能将丐帮信物交与你？"; 
      
        ob = find_object(YUZHU); 
        if (! ob) ob = load_object(YUZHU); 
        owner = environment(ob); 
      
        while (owner) 
        { 
                if (owner->is_character() || ! environment(owner)) 
                        break; 
                owner = environment(owner); 
        } 
      
        if (owner == me) 
                return "玉竹杖不就是你拿着吗，怎么还反倒问起我来了？"; 
     
        if (objectp(owner) && owner != this_object()) 
        { 
                if (! owner->is_character()) 
                        return "玉竹杖现在不在我这里。"; 
     
                if (owner->query("family/family_name") == "丐帮") 
                        return "玉竹杖现在暂时是你同门" + owner->query("name") + 
                               "在用，你要用就去找他吧。"; 
                else 
                        return "本帮的玉竹杖现在落在了" + owner->query("name") + 
                               "手中，你去把它找回来吧。"; 
        } 
        ob->move(me); 
        // command("give yuzhu zhang to " + me->query("id")); 
        return "这根玉竹杖你就暂时拿去用吧，可别给我丐帮丢脸。"; 
} 
