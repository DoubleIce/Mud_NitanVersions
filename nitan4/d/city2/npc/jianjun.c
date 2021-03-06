#include <ansi.h>
#define RIDE_CMD        "/cmds/std/ride" 
inherit NPC;

int give_quest(string arg);

void create()
{
        set_name("大宋监军", ({"jian jun"}));
        set("gender", "无性");
        set("age", random(20) + 20);

        set("long", "这是一个京城皇宫中的一名太监，负责抗击蒙古军队入侵大宋的监军。\n");
        set("combat_exp", 800000);
        set("attitude", "peaceful");
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("max_neili", 2000);
        set("neili", 1000);
        set("no_get", 1);

        setup();
        carry_object("clone/cloth/cloth")->wear();
}

void init()
{
        add_action("give_quest", ({ "lingming" }));
}


int give_quest(string arg)
{
        object me, ob, ling;
        object horse;
        
        ob = this_player();
        me = this_object();
        
        if (! arg)
        {
                tell_object(ob, "你想要领命去干什么事情？！\n");
                return 1;
        }
        
        if (ob->query_temp("warquest/party") != "song")
        {
                tell_object(ob, "你还没有参加宋军，如何领命啊？！\n");
                return 1;
        }
                
        switch(arg)
        {
        case "enlist":
        case "zhaomu-xinbing" :          
                count = 600000;
                if (WAR_D->query_moneys() < count)
                {
                        tell_object(ob, "军中银两已经不多，不足以用来支付招募新兵的开支！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中兵员匮乏，\n命你火速率部，赶去襄阳城内招募新兵" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                ob->set("party/party_name", HIY "大宋" NOR);
                ob->set("party/rank", HIY "军备营统领" NOR);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/purchase", "enlist");
                ob->set_temp("warquest/quest", "招募新兵，补充兵源");
                WAR_D->change_moneys(-count);
                ob->command("stock");
                break;
        case "stock-weapon":
        case "gouzhi-bingjia" :
                count = 600000;
                if (WAR_D->query_moneys() < count)
                {
                        tell_object(ob, "军中银两已经不多，不足以用来支付购置兵甲的开支！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中兵器和盔甲匮乏，\n命你火速率部，赶去襄阳城内采购兵器和盔甲" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                ob->set("party/party_name", HIY "大宋" NOR);
                ob->set("party/rank", HIY "军备营统领" NOR);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/purchase", "weapon");
                ob->set_temp("warquest/quest", "购置兵甲，补充军备");
                WAR_D->change_moneys(-count);
                ob->command("stock");
                break;
        case "stock-arrow":
        case "gouzhi-yujian" :
                count = 600000;
                if (WAR_D->query_moneys() < count)
                {
                        tell_object(ob, "军中银两已经不多，不足以用来支付购置羽箭的开支！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军营箭楼羽箭匮乏，\n命你火速率部，赶去襄阳城内采购羽箭" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                ob->set("party/party_name", HIY "大宋" NOR);
                ob->set("party/rank", HIY "军备营统领" NOR);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/purchase", "arrow");
                ob->set_temp("warquest/quest", "购置羽箭，补充军备");
                WAR_D->change_moneys(-count);
                ob->command("stock");
                break;
        case "stock-horse":
        case "gouzhi-zhanma" :
                count = 600000;
                if (WAR_D->query_moneys() < count)
                {
                        tell_object(ob, "军中银两已经不多，不足以用来支付购置战马的开支！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中战马匮乏，\n命你火速率部，赶去襄阳城内采购战马" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                ob->set("party/party_name", HIY "大宋" NOR);
                ob->set("party/rank", HIY "军备营统领" NOR);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/purchase", "horse");
                ob->set_temp("warquest/quest", "购置战马，补充军备");
                WAR_D->change_moneys(-count);
                ob->command("stock");
                break;
        case "stock-stone":
        case "gouzhi-shimu" :
                count = 600000;
                if (WAR_D->query_moneys() < count)
                {
                        tell_object(ob, "军中银两已经不多，不足以用来支付购置石木的开支！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中滚石和檑木匮乏，\n命你火速率部，赶去襄阳城内采购石头和木材" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);
                ob->set("party/party_name", HIY "大宋" NOR);
                ob->set("party/rank", HIY "军备营统领" NOR);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/purchase", "stone");
                ob->set_temp("warquest/quest", "购置石木，补充军备");
                WAR_D->change_moneys(-count);
                ob->command("stock");
                break;
        case "guard-xiangyang":
        case "shouwei-xiangyang" :
                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来蒙古骑兵常骚扰我大宋襄阳城，\n命你火速率部，赶去襄阳驻守城池" +
                               "，如有延误，军法论处！\n" NOR, me, ob);
                ob->set("party/party_name", HIY "大宋" NOR);
                ob->set("party/rank", HIY "后防营统领" NOR);

                ob->set_temp("warquest/guard", 1);
                ob->set_temp("warquest/quest", "守卫襄阳，稳固后方");
                // ob->command("guard");
                ob->move("/d/xiangyang/guofuting");
                break;
        case "yayun-liangcao":
        case "escort-forage" :
                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中粮草匮乏，\n命你火速率部，在半月内将京师供应之粮草押解" +
                               "至军中，如有延误，军法论处！\n" NOR, me, ob);

                ob->set("party/party_name", HIY "大宋" NOR);
                ob->set("party/rank", HIY "军备营统领" NOR);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/purchase", "forage");
                ob->set_temp("warquest/quest", "押运粮草，补充军备");
                ob->command("stock");
                break;
        case "train-infantry":
        case "xunlian-bubing":
                if (ob->query_temp("warquest/train")
                &&  ob->query_temp("warquest/train") != "infantry")
                {
                        tell_object(ob, "你已经另有他职了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐步兵，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);
                ob->set("party/party_name", HIW "大宋" NOR);
                ob->set("party/rank", HIW "步兵营统领" NOR);
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/train", "infantry");
                ob->set_temp("warquest/quest", "训练步兵，作战准备");
                ob->command("drill");
                break;

        case "xunlian-qibing":
        case "train-cavalry":
                if (ob->query_temp("warquest/train")
                &&  ob->query_temp("warquest/train") != "cavalry")
                {
                        tell_object(ob, "你已经另有他职了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐骑兵，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);

                ob->set("party/party_name", HIR "大宋" NOR);
                ob->set("party/rank", HIR "车骑营统领" NOR);
                if (! present("zhan ma", ob))
                {
                        horse = new("/d/city2/song/horse");
                        if (horse->move(environment(ob)))
                                RIDE_CMD->do_ride(ob, horse);
                        else destruct(horse);
                }
                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }
                ob->set_temp("warquest/train", "cavalry");
                ob->set_temp("warquest/quest", "训练骑兵，作战准备");
                ob->command("drill");
                break;

        case "train-archer":
        case "xunlian-gongnu":
                if (ob->query_temp("warquest/train")
                &&  ob->query_temp("warquest/train") != "archer")
                {
                        tell_object(ob, "你已经另有他职了！\n");
                        return 1;
                }

                message_vision(HIR "$N略一沉思，从案前抽出一枚令箭道：“$n听令，" +
                               "近来军中几无能战之师，\n命你加紧训练一支精锐弓箭手，以备不时之需，" +
                               "不得有误！\n" NOR, me, ob);
                ob->set("party/party_name", HIB "大宋" NOR);
                ob->set("party/rank", HIB "神弩营统领" NOR);

                if (! present("ling jian", ob))
                {
                        ling = new("/adm/npc/obj/lingjian");
                        ling->set("owner", ob->query("id"));
                        ling->move(ob);
                }

                ob->set_temp("warquest/train", "archer");
                ob->set_temp("warquest/quest", "训练弓兵，作战准备");
                ob->command("drill");
                break;
        default:
                tell_object(ob, "你想要领命做什么事情？！\n");
                return 1;
        }

        message_vision("众将领大声应道：末将遵命！！\n", me, ob);
        return 1;
}

int accept_hit(object me)
{
        if (playerp(me))
        {
                command("heng");
                command("say 你要想要找死吗！");
                return 0;
        }
}

int accept_fight(object me)
{
        if (playerp(me))
        {
                command("heng");
                command("say 你要想要找死吗！");
                return 0;
        }
}

int accept_kill(object me)
{
        if (playerp(me))
        {
                message_vision(CYN "$N" CYN "大怒道：“看来你是真的想找死！”，说罢一掌把$n" CYN
                               "劈倒在地。\n" NOR, this_object(), me);
                me->unconcious();
                return -1;
        }
}
