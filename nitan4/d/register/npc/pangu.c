// dizangwang

#include <ansi.h>

inherit NPC;

void greeting(object me);

void create()
{
        set_name("盘古", ({ "pan gu", }));
        set("long", "他容貌威严，不可一世。哇！他就是开天辟地的神仙。\n");
        set("gender", "男性");
        set("age", 999);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("per", 30);

        setup();
        carry_object("/clone/cloth/cloth.c")->wear();
        carry_object("/clone/weapon/bigaxe.c")->wield();
        create_family("万物之神", 1, "天地之主");
        set("title", HIY "万物之神" NOR);
}

void init()
{
        object me;

        ::init();
        me = this_player();
        if (! objectp(me) || ! userp(me))
                return;

        greeting(me);
}

void greeting(object me)
{
        object ob;

        if (! objectp(me) || environment(me) != environment(this_object()))
                return;

        if (! query("startroom") || base_name(environment()) != query("startroom"))
                return;

        if (undefinedp(me->query("born")))
        {
                command("say " + me->query("name") + "，你快快选择(choose)好角色性格，然后投胎去吧！");
                tell_object(me, CYN "特别提示：虽然性格对你拜哪个门派并没有影响，但是它会影响你学某些武功！\n" NOR);
	        tell_object(me, "您可以选择(choose)的角色性格如下：\n"
                            HIC "1" NOR ".光明磊落  "
                            HIC "2" NOR ".狡黠多变  "
                            HIC "3" NOR ".心狠手辣  "
                            HIC "4" NOR ".阴险奸诈 ("
                            HIC "choose 1" NOR "-" HIC "4" NOR ")\n\n");

        } else
        {
                if (wizardp(me))
                        command("heihei " + me->query("id"));
                else
                {
                        command("kick " + me->query("id"));
                        command("say 凡人跑到这里来干什么？");
                        message_vision("$N一脚把$n踢得无影无踪。\n\n",
                                       this_object(), me);
                        me->move(VOID_OB);
                        message_vision("\n$N跌落地上，捂着屁股哇哇叫了几声。\n",
                                       me);
                }
        }

        if (undefinedp(me->query("born")) && ! objectp(present("book", me)))
        {
                command("say 看你初来乍到，未必懂得规矩。给你一本书，你可以看看！(read book)");
                ob = new ("/clone/misc/newbie");
                ob->move(this_object());
                command("give book to " + me->query("id"));
        }
}

int attempt_apprentice(object ob)
{
        if (! ob->query("born"))
        {
                command("say 你快投胎去，在这里瞎搅和什么？");
                return 0;
        }

        command("say 滚！给我一边儿去！");
}

