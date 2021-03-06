// ZhuangZheng.c
// pal 1997.05.11

#include <ansi.h>
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

string ask_job();

void create()
{
        set_name("庄铮", ({ "zhuang zheng", "zhuang", "zheng", }));
	set("long",
        "他是一位高大魁伟的中年男子，身穿一件白布长袍。\n"
        "他天生神力，手中的两头狼牙棒有万夫不当之勇，真是一条威风凛凛的汉子。\n"
	);

        set("title", HIG "明教" HIW "锐金旗" NOR "掌旗使");
	set("gender", "男性");
	set("attitude", "friendly");
        set("class", "fighter");

        set("age", 42);
	set("shen_type", 1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);
	set("max_qi", 1000);
	set("max_jing", 1000);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 100);
	set("combat_exp", 100000);
	set("score", 5000);

	set_skill("force", 120);
	set_skill("dodge", 120);
	set_skill("parry", 120);
	set_skill("sword", 120);
	set_skill("cuff", 120);
	set_skill("strike", 120);
	set_skill("throwing", 200);
	set_skill("literate", 100);

	set_skill("shenghuo-xinfa", 120);
	set_skill("lingxu-bu", 120);
	set_skill("shenghuo-quan", 120);
	set_skill("guangming-zhang", 120);
	set_skill("liehuo-jian", 120);
	set_skill("wuxing-jueji", 200);

	map_skill("force", "shenghuo-xinfa");
	map_skill("dodge", "lingxu-bu");
	map_skill("strike", "guangming-zhang");
	map_skill("sword", "liehuo-jian");
	map_skill("parry", "liehuo-jian");
	map_skill("cuff", "shenghuo-quan");
	map_skill("throwing", "wuxing-jueji");

	prepare_skill("cuff", "shenghuo-quan");
	prepare_skill("strike", "guangming-zhang");

        create_family("明教", 37, "锐金旗掌旗使");
        set("inherit_title",HIG"明教"NOR"锐金旗教众"NOR);

	set("inquiry", ([
		"name" : "在下就是明教锐金旗掌旗使庄铮，不知阁下有何指教。",
		"任务" : (: ask_job :),
		"job"  : (: ask_job :),
		"放弃" : (: ask_abandon :),
		"abandon" : (: ask_abandon :),
	]));

	setup();

        carry_object("/d/mingjiao/obj/langyabang")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();
}

#include "zhangqishi.h"

string ask_job()
{
     object player=this_player();
     mapping fam ;
     object ling,qiao;

    if (!(fam = this_player()->query("family")) || fam["family_name"] != "明教")
        return "这位"+RANK_D->query_respect(player)+"并非我教弟兄，在下哪敢分派阁下什么任务呢？\n";

        if (count_gt(player->query("combat_exp"), 400000))
                 return "这位"+RANK_D->query_respect(player)+"实战经验已经颇高，岂敢劳烦大架。\n";

	if (fam["generation"] <37)
		 return "这位"+RANK_D->query_respect(player)+"在我明教中地位颇高，岂敢劳烦大架。\n";

	if(player->query("mingjiao/job"))
		return judge_jobmsg(player,0);

	command("nod "+player->query("id"));

	player->set("mingjiao/job","jin_caikuang");
	
	qiao=new(OBJ_PATH"/qiao");
	qiao->move(player);
	tell_object(player,"庄铮给你一把铁锹。\n");
	
	return "我锐金旗在教内负责采矿炼铁，最近上等精铁快用完了，你去\n"
		"附近的山上找些铁矿，然后到精练场将矿石炼制成精铁。\n"
		"附近山上常有猛兽出没，你自己多加小心。\n";	 
}
