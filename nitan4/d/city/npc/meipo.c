//meipo.c

#include <ansi.h>
inherit NPC;

string ask_hunyin();

void create()
{
      set_name("花媒婆",({"mei po", "mei"}));
      set("age", 65);
      set("gender", "女性");
      set("nickname", "姻缘天定");
      set_skill("unarmed", 40);

      set("inquiry",([
            "介绍对象" :  (: ask_hunyin :),
      ]));

        set("chat_chance", 15); 
        set("chat_msg", ({ 
                "花媒婆神秘兮兮的说道：据说灵山上有传说中的雪莲花，那可是送给心上人最好的礼物哦。\n",
                "花媒婆讪讪的说：这个～～他是个瘸子，老婆子我可没说他不是啊，这嫁都嫁了，还能怪我？\n",
                "花媒婆偷偷一笑：这雪莲花戴上了真是花容月貌啊，我老婆子可要想个法子留下，不能就这么给了那小娘子。\n"
        }) ); 

      setup();
      carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
      object ob;

      ::init();

      if (interactive(ob=this_player())&&!is_fighting())
      {
           remove_call_out("greeting");
           call_out("greeting", 1, ob);
      }
      add_action("do_agree", "agree");
}

void greeting(object ob)
{
      if (!ob||environment(ob)!=environment())   return;
      if (ob->query("age") >= 18 && !ob->query("couple"))
      {
           if (ob->query("gender") == "无性")
           {
                 message_vision("$N对$n摇头叹道：可惜是个太监，不然也到" +
                                "娶媳妇的时候了。\n", this_object(), ob);
                 return;
           }

           if (ob->query("gender") == "男性")
           {
                 if (ob->query("per") < 20)

                 message_vision("$N看见$n，吓了一跳：这位公子可是要老婆子" +
                                "给你介绍对象？难哪！\n", this_object(), ob);
                 else

                 message_vision("$N凑上前对$n道：公子一表人材，可要老婆子" +
                                "给你介绍对象？\n", this_object(), ob);
                 return;
           }

           if (ob->query("gender") == "女性")
           {
                 if (ob->query("per") < 20)

                 message_vision("$N看见$n，叹了口气：这位姑娘虽不愁嫁，可要找" +
                                "个好人家却非易事！\n", this_object(), ob);
                 else

                 message_vision("$N凑上前对$n道：好俊俏的人儿，可要老婆子" +
                                "给你介绍对象？\n", this_object(), ob);
                 return;
           }
      }
      return;
}

string ask_hunyin()
{
      object *list = users();
      object ob = this_player();
      string who, gender = ob->query("gender");
      int i, p;

      if (gender == "无性")
           return "你个死太监，还想找对象结婚害人？";

      if (ob->query("couple"))
           return "你都是结了婚的人了, 还找什么对象？";

      if (ob->query("age") < 18)
           return "这么小就想找对象啦，嘻嘻。\n";

      if (ob->query_temp("mameipo/agree"))
           return "怎么？" + ob->query_temp("mameipo/agree") +
                  "还没有答应你这门亲事吗？\n";

      i = 0;
      while ( i <sizeof(list))
      {
           if (list[i]->query("gender") == gender ||
               list[i]->query("gender") == "无性" ||
               list[i]->query("age") < 18 ||
               list[i]->query("age") > ob->query("age") + 5 ||
               list[i]->query("age") < ob->query("age") - 5 ||
               list[i]->query("class") == "bonze" ||
               list[i]->query("couple"))
           list[i] = 0;
           i++;
      }

      list -= ({ 0 });
      if ( sizeof(list) > 0 )
      {
           p = random(sizeof(list));
           who = list[p]->query("id");
           ob->set_temp("mameipo/who", who);
           return "看来" + list[p]->query("name") + "(" + list[p]->query("id") + ")" +
                  "和你很相配，你意下如何？(agree)\n";
      }
      else   return "暂时还找不到与你相配的人。";
}

int do_agree()
{
      object who, ob = this_player();

      if (!ob->query_temp("mameipo/who"))
      {
           tell_object(ob, "花媒婆对你道：你是想老婆子给你介绍对象么？\n");
           return 1;
      }

      tell_object(ob, HIC"花媒婆对你道：既如此，老婆子就给你把这好事儿跟对方说说。\n"NOR);
      who = find_player(ob->query_temp("mameipo/who"));
      if (!who)
      {
           tell_object(ob,HIC"花媒婆对你道：可惜，现在老婆子找不到你的意中人。\n"NOR);
           return 1;
      }

      tell_object(who, ob->query("name") + "托花媒婆给你送来朵"+ HIR +"红玫瑰"NOR+"。\n");
      command("tell " + ob->query_temp("mameipo/who") + " " + ob->query("name") + "(" +
              ob->query("id") + ")对你很有意思，托老婆子给你说说。\n");
      new("/d/city/obj/rrose")->move(who);
      tell_object(ob, HIC"花媒婆对你道：老婆子已经把你的意思转告了，你这就去提亲吧。\n"NOR);
      ob->delete_temp("mameipo/who");
      ob->set_temp("mameipo/agree", who->query("name") + "(" + who->query("id") + ")");
      return 1;
}

