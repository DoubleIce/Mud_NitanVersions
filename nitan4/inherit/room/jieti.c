#include <ansi.h>

array jieti_msg = ({
        HIM "你盘膝坐在地上，平心净气，试着将内息在体内循环十二周天，发现\n" NOR
        HIM "完全畅通无阻，便运起无上心法\n\n" NOR            
        HIR "            天     魔       解      体     大     法\n\n" NOR,
        
        HIW "顿时只听得一阵阵巨雷滚滚而起，天空乌云密布，道道紫色闪电划破\n" NOR 
        HIW "长空！你丝毫不感分心，按照天魔解体大法所述将自身内力分成两部\n" NOR 
        HIW "分，分别归入丹田与百汇中，只感觉丹田和百汇好像绝了堤的水坝一\n" NOR 
        HIW "般，内力如滚滚洪水似的向前冲去，而内力所经过的经脉瞬间被摧毁。\n" NOR,
        HIC "经脉瞬间被毁的巨痛险些使你昏过去，身体传来撕心裂肺的痛苦，更\n" NOR 
        HIC "是让你的脸完全扭曲了。半秒锺的时间都不到，但在你感觉好像经过\n" NOR 
        HIC "半个世纪那麽长一般。\n" NOR ,
        HIM "两穴里冲出来的内力遍会集到龙回穴所处的地方，两股内力互相融合，\n" NOR 
        HIM "慢慢形成太极形状，各分阴阳的流淌著，当所有内力集中在太极上後，\n" NOR 
        HIM "整个太极图案突然一跳，而你的神经也跟著猛地跳动一下，你知道这\n" NOR 
        HIM "是龙回穴成功产生出来後的效果。\n" NOR,
        HIY "就在这时，四周的灵气仿佛被什么牵引着疯狂的开始向你体内涌入，\n" NOR 
        HIY "以惊人的速度飞快的从龙回穴往回开始修复损坏的经脉，瞬间在精神\n" NOR 
        HIY "恍惚间你仿佛感觉回到了母亲的怀里般，终忍不住袭来的倦意，缓缓\n" NOR 
        HIY "的睡过了去。。。。\n" NOR,
        HIG "清晨醒来，乌云四散，清空万里，唯有大地一片寂静。。。。。\n" NOR,
        HIR "你发现体内的情况让你震惊，虽然内力已经减了近三成，但是却是生\n" NOR
        HIR "生不息，取之不尽，用之不完，经脉也被拓宽了几倍。而在眉心已留\n" NOR 
        HIR "下一小道红色胎记，仔细观察的话，会发现这块胎记如同一把倒立的\n" NOR 
        HIR "宝剑一般，散发著阵阵煞灵之气，你摸了摸身子，发现身体外层好像\n" NOR 
        HIR "脱皮一般，稀里哗啦的掉下不少老化的皮肤，而那些脱落旧皮後的新\n" NOR 
        HIR "肌肤比以前更加的白嫩。\n\n" NOR,
});

string get_jieti_place()
{
        string file;
        
        file = domain_file(base_name(this_object()));
        
        return file;
}

int do_jieti();
int do_decide();
void jieti_player(object me);

int do_jieti()
{
        object me;
        string msg, place;
        
        me = this_player();
        if (! ultrap(me) || ! me->query("animaout"))
                return notify_fail("你还没有修成元婴出世，就想天魔解体？\n");
        
        if ((int)me->query_skill("martial-cognize", 1) < 400)
                return notify_fail("你的武学修养没有达到四百级，就想天魔解体，不怕走火入魔？\n");

        if (count_lt(me->query("combat_exp"), 100000000))
                return notify_fail("你的经验还不够，贸然天魔解体，会走火入魔的。\n");

        if (me->query("couple"))
                return notify_fail("解体前，你还是把家里的后顾之忧解决掉吧。\n");

        if (me->query("bunch"))
                return notify_fail("解体前，你还是把帮派的后顾之忧解决掉吧。\n");

        if (me->query("brothers"))
                return notify_fail("解体前，你还是把结义的后顾之忧解决掉吧。\n");

        if (me->query("league"))
                return notify_fail("解体前，你还是把联盟的后顾之忧解决掉吧。\n");

        place = get_jieti_place();

        if (me->query("jieti/" + place))
        {
                if ((int)me->query("jieti/times") < 5 || place != "songshan")
                        return notify_fail("你已经在此解体过，吸收了此地的天地菁华。\n");
        }
        
        if (place == "songshan" && (int)me->query("jieti/times") < 4)
                return notify_fail("中岳嵩山是最高层次的天魔解体，你还没有达到这个境界！\n");

        msg = HIY "天魔解体是一种耗费大量的经验、武技来体悟中华武学精髓的方式，通过天魔\n" +
                  "解体，可以大大的提升你的体质，无论是先天资质、精力上限、内力上限、还\n" +
                  "是你的自身潜力都会得到很大的提高，你战斗中的杀伤力也会大大的加强，你\n" +
                  "是否确定(decide)自己将进行天魔解体？\n" NOR;

        me->set_temp("attempt_jieti", place);
        tell_object(me, msg);
        return 1;
}

int do_decide()
{
        string place;
        object me = this_player();
        
        if (! stringp(place = me->query_temp("attempt_jieti")))
                return notify_fail("你想决定什么？\n");

        if (place != get_jieti_place())
                return notify_fail("你想决定什么？\n");
                
        tell_object(me, HIW "天魔解体已不开放！！\n\n" NOR);
        /*
        tell_object(me, HIW "你闭目沉思，良久，终于下定决心，进行天魔解体！！\n\n" NOR);
        me->delete_temp("attempt_jieti");
        call_out("jieti_msg", 0, me, 0, place);
        */
        return 1;
}

void jieti_player(object me)
{
        mixed files;
        string special;
        string msg, place;
        array skills;
        mapping all_skills;
        int i;
        
        place = get_jieti_place();
        
        if (me->query("gender") == "无性")
                me->set("gender", "男性");   
                             
        me->set("score", 0);
        me->set("shen", 0);
        me->set("mud_age", 0);
        me->set("age", 14); 
        me->set("birthday", time());
        me->delete("weiwang");        
        me->delete("meili");
        me->delete("balance");
        me->delete("total_hatred");
                
        me->set("combat_exp", 10000000);
        me->set("potential", 1000000);
        me->set("learned_points", 0);
        me->set("experience", 100000);
        me->set("learned_experience", 0);
        me->set("magic_points", 20000);        
        me->set("level", 100);

        me->set("max_neili", 5000);
        me->set("max_qi", 2000);
        me->set("max_jing", 1000);
        me->set("max_jingli", 2000);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("eff_jing"));
        me->set("eff_jingli", me->query("max_jingli"));
        
        me->delete("couple");                // 家庭记录
        me->delete("sex");                   // 做爱记录
        me->delete("brothers");              // 结拜兄弟
        me->delete("bunch");                 // 帮派记录
        me->delete("league");                // 同盟记录    
        me->delete("family");                // 门派记录
        me->delete("class");                 // 称号记录
        me->delete("detach");                // 叛师记录
        me->delete("betrayer");              // 叛师记录
        me->delete("long");                  // 个人描述
        me->set("title", "普通百姓");        // 个人称号
        me->set("character", "国士无双");    // 解体性格
        me->delete("combat");                // PK  记录          
        me->delete("animaout");              // 元婴出世     
        me->delete("breakup");               // 任督二脉
        me->delete("can_learn");             // 故事记录
        me->delete("can_make");              // 制药记录
        me->delete("degree");                // 官府职位
        me->delete("degree_jungong");        // 军功记录
        me->delete("gift");                  // 吃丹记录
        me->delete("guo_shoucheng");         // 守城记录
        me->delete("opinion");               // 评价记录
        me->delete("opinions");              // 宗师身份
        me->delete("out_family");            // 出师历练
        me->delete("pawns");                 // 典当记录
        me->delete("task");                  // 使命任务
        me->delete("quest_count");           // 门派任务
        me->delete("questdg_times");         // 宗师任务
        me->delete("quesths_times");         // 宗师任务
        me->delete("questkh_times");         // 宗师任务
        me->delete("questsn_times");         // 宗师任务    
        me->delete("map");                   // 地图标志
        me->delete("rumor");                 // 事件记录
        me->delete("schedule");              // 计划记录
        me->delete("see_feng");              // 见风清扬
        me->delete("skybook");               // 天书记录
        me->delete("sl");                    // 少林武功
        me->delete("sl_gifts");              // 少林武功
        me->delete("luohan_winner");         // 十八罗汉阵
        me->delete("story");                 // 中的故事
             
        all_skills = me->query_skills();
        skills = keys(all_skills);
        
        for (i = 0; i < sizeof(skills); i++)
        {
                if (all_skills[skills[i]] > 400 &&
                    SKILL_D(skills[i])->type() != "knowledge")
                        me->set_skill(skills[i], 400); 
               
                if (all_skills[skills[i]] < 400 &&
                    skills[i] != "zuoyou-hubo")
                        me->delete_skill(skills[i]);
        } 
        
        /*        
        me->set_skill("martial-cognize", 1000); 
        me->set_skill("count", 1000);
        me->set_skill("mathematics", 1000);
        */
        me->set_skill("literate", 1000);
        me->add("jieti/times",1);
        me->set("jieti/" + place, 1);
        
        if (me->is_ghost()) me->reincarnate();
        me->reset_action(); 
                
        msg = HIG "你获得的解体技能有：" NOR;

        // 查看所有的特殊技能文件
        files = ({ "bian", "dispel", "drift", "ghost", 
                   "jin", "sheng", "yuan", 
                });
        
        for (i = 0; i < sizeof(files); i++)
        {
                if (me->query("special_skill/" + files[i]))
                        files[i] = 0;
        }
        
        files -= ({ 0 });
        
        // 获得第一项技能
        special = files[random(sizeof(files))];
        me->set("special_skill/" + special, 1);
        msg += SPECIAL_D(special)->name();
        
        message("channel:rumor", HIM "【天魔解体】" + me->query("name") +
                "获得解体技能--" + SPECIAL_D(special)->name() + HIB "！\n" NOR, users());    
                
        files -= ({ special });
        
        if (sizeof(files) && random(21) == 1) 
        {      
                // 获得第二项技能                             
                special = files[random(sizeof(files))];
                me->set("special_skill/" + special, 1);
                msg += HIG "、" NOR + SPECIAL_D(special)->name();

                message("channel:rumor", HIM "【天魔解体】" + me->query("name") +
                        "获得解体技能--" + SPECIAL_D(special)->name() + HIB "！\n" NOR, users());    
        }
        
        me->set("special_skill/shuang", 1);
        
        msg += HIG "、" NOR + HIY "国士无双" NOR;       
        msg += HIG "。\n" NOR;
                                                         
        tell_object(me, msg);
}

void jieti_msg(object me, int stage, string place)
{
        string msg;

        if (stage == 5) me->revive();

        msg = HIR + jieti_msg[stage] + NOR;
        tell_object(me, HIY + msg + NOR);
        if (stage < sizeof(jieti_msg) - 1)
        {
                if (stage == 4) me->unconcious();

                stage++;
                call_out("jieti_msg", 1, me, stage, place);
        } else
        {
                jieti_player(me);
                CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name(1) +
                                      "在" + this_object()->short() + "天魔解体了！");
        }      
        return;
}
