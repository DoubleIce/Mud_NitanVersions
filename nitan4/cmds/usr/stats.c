// stats cmds

#include <ansi.h>
#include <mudlib.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        string sp;
 
        seteuid(getuid(me));

        if (! wizardp(me) && time() - me->query_temp("last_stats") < 5) 
                return notify_fail("系统气喘嘘地叹道：慢慢来 ....\n");  

        me->set_temp("last_stats", time());  
        if (arg && arg != "")
        {
                if (wizardp(me) || me->query("couple/child_id"))
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob)) 
                                return notify_fail("你要察看谁的状态？\n");

                        if (! wizardp(me) && me->query("couple/child_id") != ob->query("id"))
                                return notify_fail("你要察看谁的状态？\n");

                } else
                        return notify_fail("只有巫师能察看别人的状态。\n");
        } else
                ob = me;

        if (userp(ob) && (! stringp(ob->query("born")) || ! ob->query("born")))
                return notify_fail("还没有出生呐，察看什么？\n");
        
        sp = (ob == me ? "你" : ob->name()) + "目前的各附加属性效果一览\n";
        sp += HIC "≡" HIY "───────────────────────────────" HIC "≡\n" NOR;
        
        sp += sprintf(HIW BRED "\n%|66s\n\n" NOR, "人物属性及辅助练功类");
        
        sp += sprintf(HIC "【臂力附加】 " HIW " %-10d" HIC "【悟性附加】 " HIW " %-10d" HIC "【根骨附加】 " HIW " %-10d\n",
                      ob->query_temp("apply/str"), ob->query_temp("apply/int"), ob->query_temp("apply/con"));
                      
        sp += sprintf(HIC "【身法附加】 " HIW " %-10d" HIC "【潜能上限】 " HIW " %-10d" HIC "【体会上限】 " HIW " %-10d\n",
                      ob->query_temp("apply/dex"), ob->query_temp("apply/max_potential"), ob->query_temp("apply/max_experience"));

        sp += sprintf(HIC "【内力上限】 " HIW " %-10d" HIC "【精力上限】 " HIW " %-10d" HIC "【气血上限】 " HIW " %-10d\n",
                      ob->query_temp("apply/max_neili"), ob->query_temp("apply/max_jingli"), ob->query_temp("apply/max_qi"));

        sp += sprintf(HIC "【精气上限】 " HIW " %-10d" HIC "【研究次数】 " HIW " %-10d" HIC "【研究效果】 " HIW " %-10s\n",
                       ob->query_temp("apply/max_jing"), ob->query_temp("apply/research_times"), ob->query_temp("apply/research_effect") + "%");

        sp += sprintf(HIC "【练习次数】 " HIW " %-10d" HIC "【练习效果】 " HIW " %-10s" HIC "【学习次数】 " HIW " %-10d\n",
                      ob->query_temp("apply/practice_times"), ob->query_temp("apply/practice_effect") + "%", ob->query_temp("apply/learn_times"));                                                                  

        sp += sprintf(HIC "【学习效果】 " HIW " %-10s" HIC "【汲取次数】 " HIW " %-10d" HIC "【汲取效果】 " HIW " %-10s\n",
                      ob->query_temp("apply/learn_effect") + "%", ob->query_temp("apply/derive_times"), ob->query_temp("apply/derive_effect") + "%");
                                            
        sp += sprintf(BRED "\n%|66s\n\n" NOR, "战斗相关及装备附加类");
        
        sp += sprintf(HIC "【攻击等级】 " HIW " %-10d" HIC "【防御等级】 " HIW " %-10d" HIC "【躲闪等级】 " HIW " %-10d\n",
                      ob->query_temp("apply/attack"), ob->query_temp("apply/defense"), ob->query_temp("apply/dodge"));

        sp += sprintf(HIC "【招架等级】 " HIW " %-10d" HIC "【绝招命中】 " HIW " %-10s" HIC "【绝招防御】 " HIW " %-10s\n",
                      ob->query_temp("apply/parry"), ob->query_temp("apply/ap_power") + "%", ob->query_temp("apply/dp_power") + "%");

        sp += sprintf(HIC "【无视招架】 " HIW " %-10s" HIC "【无视躲闪】 " HIW " %-10s" HIC "【无视攻击】 " HIW " %-10s\n",
                      ob->query_temp("apply/avoid_parry") + "%", ob->query_temp("apply/avoid_dodge") + "%", ob->query_temp("apply/avoid_attack") + "%");

        sp += sprintf(HIC "【无视内功】 " HIW " %-10s" HIC "【兵器伤害】 " HIW " %-10d" HIC "【空手伤害】 " HIW " %-10d\n",
                      ob->query_temp("apply/avoid_force") + "%", ob->query_temp("apply/damage"), ob->query_temp("apply/unarmed_damage"));
                                                                  
        sp += sprintf(HIC "【绝招伤害】 " HIW " %-10s" HIC "【战斗保护】 " HIW " %-10d" HIC "【毒素伤害】 " HIW " %-10s\n",
                      ob->query_temp("apply/da_damage") + "%", ob->query_temp("apply/armor"), ob->query_temp("apply/add_poison") + "%");
        
        sp += sprintf(HIC "【抗毒效果】 " HIW " %-10s" HIC "【冷冻伤害】 " HIW " %-10s" HIC "【抗冰效果】 " HIW " %-10s\n",
                      ob->query_temp("apply/reduce_poison") + "%", ob->query_temp("apply/add_cold") + "%", ob->query_temp("apply/reduce_cold") + "%");

        sp += sprintf(HIC "【火焰伤害】 " HIW " %-10s" HIC "【抗火效果】 " HIW " %-10s" HIC "【闪电伤害】 " HIW " %-10s\n",
                      ob->query_temp("apply/add_fire") + "%", ob->query_temp("apply/reduce_fire") + "%", ob->query_temp("apply/add_lighting") + "%");

        sp += sprintf(HIC "【抗电效果】 " HIW " %-10s" HIC "【魔法伤害】 " HIW " %-10s" HIC "【抗魔效果】 " HIW " %-10s\n",
                      ob->query_temp("apply/reduce_lighting") + "%", ob->query_temp("apply/add_magic") + "%", ob->query_temp("apply/reduce_magic") + "%");

        sp += sprintf(BRED "\n%|66s\n\n" NOR, "终极属性类");
        
        sp += sprintf(HIC "【反噬气血】 " HIW " %-10d" HIC "【反噬精气】 " HIW " %-10d" HIC "【封存绝招】 " HIW " %-10s\n",
                      ob->query_temp("apply/def_damage"), ob->query_temp("apply/def_damage"), ob->query_temp("apply/add_locked") + "%");

        sp += sprintf(HIC "【解封绝招】 " HIW " %-10s" HIC "【忙乱对手】 " HIW " %-10d" HIC "【化解忙乱】 " HIW " %-10d\n",
                      ob->query_temp("apply/avoid_locked") + "%", ob->query_temp("apply/add_busy"), ob->query_temp("apply/reduce_busy"));

        sp += sprintf(HIC "【虚弱对手】 " HIW " %-10s" HIC "【抵抗虚弱】 " HIW " %-10s" HIC "【追加伤害】 " HIW " %-10s\n",
                      ob->query_temp("apply/add_xuruo") + "%", ob->query_temp("apply/avoid_xuruo") + "%", ob->query_temp("apply/add_damage") + "%");

        sp += sprintf(HIC "【化解伤害】 " HIW " %-10s" HIC "【提升技能】 " HIW " %-10d\n",
                       ob->query_temp("apply/reduce_damage") + "%", ob->query_temp("apply/add_skill"));
                      
        sp += sprintf(BRED "\n%|66s\n\n" NOR, "会员服务类");                
                                                                                                                      
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "在%s里已经历练了 " NOR + HIC "%s\n" NOR, 
                        LOCAL_MUD_NAME(), time_period(ob->query("online_time")));
        
        if (MEMBER_D->is_valid_member(ob))
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "无限制\n" NOR); 
        else
        {
                if (ob->query("online_time") / 3 < ob->query("offline_time"))
                        ob->set("offline_time", ob->query("online_time") / 3);
                sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "可用来离线练功时间还有 " NOR + HIY "%s\n" NOR, 
                              time_period(ob->query("online_time") / 3 - ob->query("offline_time")));
        }
                              
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的双倍经验时间还余 " NOR + HIW "%s\n" NOR,
                      time_period(ob->query("time_reward/quest")));         
        sp += sprintf(HIG + (ob == me ? "你" : ob->name()) + HIG "今天的高效练功时间还余 " NOR + HIM "%s\n" NOR,
                      time_period(ob->query("time_reward/study")));      
                        
        sp += "\n";
        sp += HIC "≡" HIY "───────────────────────────────" HIC "≡\n" NOR;
        
        me->start_more(sp);
        return 1;
}

