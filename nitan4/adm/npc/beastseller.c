// beastseller.c

#include <ansi.h>
inherit NPC;
inherit F_DEALER;

#define BEAST_OB          "/clone/npc/magic-beast.c"
#define BEAST_DIR         "/data/beast/"
#define CRUISE_OB         "/clone/misc/cruise-ob.c"

void get_subtype(string arg, object ob);
void get_gender(string arg, object ob);
void get_id(string arg, object ob);
void get_name(string arg, object ob);
void get_desc(string arg, object ob);
void build_beast(object ob);
int check_legal_name(string name, int max_len);
int check_legal_id(string arg);

string* beast_type_name = ({
        "马", "驴", "骡", "驼", "牛", "象",
        "狮", "虎", "豹", "鹿", "鹤", "雕",
        "羊", "猴", "熊", "狼", "狐", "貂",
        "驹", "兽",
});

string* beast_id_surfix = ({
        "ma", "lv", "luo", "tuo", "niu", "xiang",
        "shi", "hu", "bao", "lu", "he", "diao",
        "yang", "hou", "xiong", "lang", "hu", "diao",
        "ju", "shou",
});

string* beast_unit_name=({
        "匹", "头", "头", "头", "头", "头",
        "只", "只", "只", "头", "只", "只",
        "头", "只", "只", "条", "只", "只",
        "匹", "头",
});

void create()
{        
        set_name("狂风使者", ({ "kuangfeng shizhe", "kuangfeng", "shizhe" }) );
        set("gender", "男性" );
        set("age", 21);
        set("long",@LONG
狂风使者来自神秘的精意山庄，最近突然出现在扬州城，并出售
人们从没有见过的魔幻兽卵，传说这个魔幻兽卵一经孵化将具有
神奇的功能，你如果喜欢的话，不妨也选(choose)一只。
LONG );
        // set("title",HIW"魔幻兽商人"NOR);
        set("combat_exp", 5);
        
        set("inquiry", ([ 
                "魔幻兽"     : "只要给我一百两黄金，你就能拥有魔幻兽了！", 
                "漫游传送包" : "先给我材料地藏之石，再给我5000两黄金，你就可以拥有漫游包了。",
                "漫游包" : "先给我材料地藏之石，再给我5000两黄金，你就可以拥有漫游包了。",
                // 虎皮＋龙筋＋朱雀羽毛，合成一个玄天玲珑锦
        ]));

        set_skill("training", 400);    
        set_skill("huisheng-jue", 400);    
        set("chat_chance", 15);
        set("attitude", "friendly");
        
	set("vendor_goods", ({
                "/clone/misc/energy",
	}));
	        
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        create_family("精意山庄", 21, "弟子");      
}

void init()
{       
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_choose", "choose");
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(5) ) {
                case 0:
                        say( "狂风使者说道：这位" + RANK_D->query_respect(ob)
                                + "，要魔幻兽么？\n");
                        break;
                case 1:
                        say( "狂风使者说道：这位" + RANK_D->query_respect(ob)
                                + "，魔幻兽可以铠化，保护主人的哦。\n");
                        break;
        }
}

int do_choose()
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你上一个动作还没有完成。\n");
                
        if (file_size(me->query_save_file() + "-beast.o") > 0 &&
            mapp(me->query("can_whistle")))
                return notify_fail("你已经拥有你心爱的魔幻兽了。\n");
                                   
        if (count_lt(me->query_skill("training", 1),30))
                return notify_fail("你的驭兽术太低了，即使养了魔幻兽，也会背弃你而去。\n");
        
        if (! me->query_temp("beast/money"))
        {
                command("say 这位" + RANK_D->query_respect(me) + "，每只魔幻兽一百两黄金，你必须先给钱！");
                return 1;
        }
                               
        write("您要养哪类魔幻兽：\n");
        write(" 1. 马   2. 驴   3. 骡   4. 驼  5. 牛  6. 象\n");
        write(" 7. 狮   8. 虎   9. 豹  10. 鹿 11. 鹤 12. 雕\n");
        write("13. 羊  14. 猴  15. 熊  16. 狼 17. 狐 18. 貂\n");
        write("19. 驹  20. 兽\n");
        write("请选择数字代号：(q 键取消)");
        
        input_to( (: get_subtype :), me);
        return 1;
}

void get_subtype(string arg, object ob)
{
        int n;
   
        if (arg == "q" || arg == "Q")    
                return;

        sscanf(arg, "%d", n);
    
        if (n <= 0 || n > 20)  
        {               
                write("您要养哪类魔幻兽：\n");
                write(" 1. 马   2. 驴   3. 骡   4. 驼  5. 牛  6. 象\n");
                write(" 7. 狮   8. 虎   9. 豹  10. 鹿 11. 鹤 12. 雕\n");
                write("13. 羊  14. 猴  15. 熊  16. 狼 17. 狐 18. 貂\n");
                write("19. 驹  20. 兽\n");
                write("请选择数字代号：(q 键取消)");
                input_to( (: get_subtype :), ob);
                return;
        }
        ob->set_temp("beast/beast_type", n);

        write("\n");
        write("请设定魔幻兽的性别(雄性：1  雌性：0)：");
        input_to( (: get_gender :), ob ); 
}

void get_gender(string arg, object ob)
{
        int n;
        object beast;
        
        sscanf(arg, "%d", n);

        if (n != 0 && n != 1)  
        {
                write("\n");
                write("请设定魔幻兽的性别(雄性：1  雌性：0)：");
                input_to( (: get_gender :), ob );
                return;
        }
        ob->set_temp("beast/beast_gender", n ? "男性" : "女性");
          
        write("\n");
        /*
        write(sort_string(CYN "狂风使者淡淡说道：“既然如此，下面将进行魔幻兽"
              "择主仪式，你不需要有任何的心理负担，放松全身即可，这是个短"
              "暂的仪式！”接着又道：“仪式开始！” \n“魔幻兽，择主”，随着一"
              "声沉喝，狂风使者身上闪起一道光柱，只见从光柱中飞舞无数魔幻"
              "兽卵，此时狂风使者收回光柱，紧接着挥出一道红光打在魔幻兽卵"
              "上。魔幻兽卵在红光的照射下开始出现强烈的骚动，紧接着便纷纷"
              "漂浮起来，飞向半空。这时你才发见原来在表面一层魔幻兽卵下面"
              "还有着更多的魔幻兽卵，魔幻兽卵不断漂浮而起，停在空中散发着"
              "微弱的光芒，照在你的脸上，仿佛在寻找主人，魔幻兽卵刹那间开"
              "始在空中乱舞，一只魔幻兽卵向你手中飞来。你本能的伸出双手去"
              "接飞到身前的魔幻兽卵。\n" NOR, 64)); 
        write(CYN "\n只听狂风使者说道：“仪式结束，恭喜你！”\n" NOR); 
        write(sort_string(CYN "\n只听狂风使者又道：“鉴于你目前功力尚潜，不足"
                "以于魔幻兽卵进行心灵沟通，我就帮你一次吧。”\n" NOR, 64)); 
        */
        write(sort_string(CYN "你按照狂风使者的指点开始飞快的念道：“在天的见"
                "证之下，集勇气、智慧、与美丽于一身的强大生物，幻兽呀！请"
                "你以最深的灵性，聆听我的倾诉，我－" + ob->query("name") +
                "－将与你缔结永生的血之盟约，终此生惟有你与我为终生之盟友"
                "，契。”\n" NOR, 64));        

        write(sort_string(WHT "只见你手中的幻兽卵却传来一阵异样，合在掌中的魔"
                "幻兽卵温度异常的升高，升到几乎烫手的高温，而且里面隐隐有东"
                "西活动的感觉。$N满心期待中，原本光华的外壳开是出现裂痕，然"
                "后裂痕加大，一股奇特，说不上香或臭的味道开始散出，充斥整个"
                "空间。接着，一颗龙眼大小的头伸了出来，看起来有点像" + 
                beast_type_name[ob->query_temp("beast/beast_type") - 1] +  "的样子，接着整个身子全露"
                "了出来，看来只有巴掌不到的大小，一身应该是银色的，但因为沾"
                "满了湿滑黏液而泛出珍珠色泽，小幻兽看了$N一眼，伸出小舌头在"
                "你拇指上舔了几下，发出一声如蚊声的叫声，随即开始吃起卵壳，"
                "一下子，和它等体积的卵壳一下子就被吃光了，只见它可爱的打了"
                "个饱嗝，身个懒腰，舒服的窝在$N的掌心中。\n" NOR, 64));
                
        write("\n");
        write("请设定魔幻兽的英文 id ：");
        input_to( (: get_id :), ob ); 
}

void get_id(string arg, object ob)
{
        arg = lower_case(arg);
        
        if (! check_legal_id(arg))   
        {
                write("\n");
             
                write("请设定魔幻兽的英文 id ：");
                input_to( (: get_id :), ob ); 
                return;
        }

        arg = replace_string(arg, " ", "_");    
        
        // ob->set_temp("beast/beast_id", arg + " " + beast_id_surfix[ob->query_temp("beast/beast_type") - 1]);
        ob->set_temp("beast/beast_id", arg);
        ob->set_temp("beast/beast_unit", beast_unit_name[ob->query_temp("beast/beast_type") - 1]);
        
        write("\n");
        write("请设定魔幻兽的中文名：(可加颜色)");
        input_to( (: get_name :), ob);
}

void get_name(string arg, object ob)
{
        string  arg_old;
        string  result;
        
        if (arg && ob->query_temp("big5"))
                arg = LANGUAGE_D->toGB(arg);
                
        arg_old = arg;
        /*
        arg = trans_color(arg, 1);
        arg = filter_color(arg);
        */
        arg = replace_string(arg, "$BLK$", "");
        arg = replace_string(arg, "$RED$", "");
        arg = replace_string(arg, "$GRN$", "");
        arg = replace_string(arg, "$YEL$", "");
        arg = replace_string(arg, "$BLU$", "");
        arg = replace_string(arg, "$MAG$", "");
        arg = replace_string(arg, "$CYN$", "");
        arg = replace_string(arg, "$WHT$", "");
        arg = replace_string(arg, "$HIR$", "");
        arg = replace_string(arg, "$HIG$", "");
        arg = replace_string(arg, "$HIY$", "");
        arg = replace_string(arg, "$HIB$", "");
        arg = replace_string(arg, "$HIM$", "");
        arg = replace_string(arg, "$HIC$", "");
        arg = replace_string(arg, "$HIW$", "");
        arg = replace_string(arg, "$NOR$", "");

        if (! check_legal_name(arg, 12))  
        {
                write("请设定魔幻兽的中文名：(可加颜色)");
                input_to( (: get_name :), ob);
                return;
        }

        if (stringp(result = NAME_D->invalid_new_name(arg)))
        {
                write("对不起，" + result);
                write(HIR "禁止使用与他人姓名相同或接近的魔幻兽名。并因循RULES中对名字的相关规定。"NOR+"\n");
                input_to( (: get_name :), ob);
                return;
        }
        
        arg = arg_old;
        // arg = trans_color(arg, 1); 
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);
        
        ob->set_temp("beast/beast_name", arg);
        
        write("\n");
        write("请描述魔幻兽：(不可加颜色)");
        input_to( (: get_desc :), ob);
}

void get_desc(string arg, object ob)
{
        if (arg && ob->query_temp("big5"))
                arg = LANGUAGE_D->toGB(arg);
                
        arg = replace_string(arg, "\"", "");
        arg = replace_string(arg, "\\", "");  
        if (! check_legal_name(arg, 60))  
        {
                write("请描述魔幻兽：");
                input_to( (: get_desc :), ob);
                return;
        }

        ob->set_temp("beast/beast_desc",  arg);
        write("ok\n");
        build_beast(ob);
}

void build_beast(object ob)
{
        string file, filename;
        object beast, money;        
        string beast_id;
        string beast_name;
        string beast_unit;
        string beast_desc;
        string beast_gender;

        beast_id = ob->query_temp("beast/beast_id");
        beast_name = ob->query_temp("beast/beast_name");
        beast_name += NOR;
        beast_unit = ob->query_temp("beast/beast_unit");
        beast_desc = ob->query_temp("beast/beast_desc");
        beast_desc += NOR;
        beast_gender = ob->query_temp("beast/beast_gender");
        
        file = read_file(BEAST_OB);
        
        file = replace_string(file, "BEAST_NAME", beast_name);
        file = replace_string(file, "BEAST_ID", beast_id);                                                       
        file = replace_string(file, "BEAST_GENDER", beast_gender);                           
        file = replace_string(file, "BEAST_UNIT", beast_unit);                          
        file = replace_string(file, "LONG_DESCRIPTION", 
                            beast_desc + "\n" + "它是" + 
                            ob->query("name") + "的魔幻兽。\n");
        
        file = replace_string(file, "OWNER_ID", ob->query("id"));
        file = replace_string(file, "OWNER_NAME", ob->query("name"));
                            
        filename = BEAST_DIR + ob->query("id") + "-" + "beast";
        
        if (file_size(filename + ".c") > 0)
        {
                if (beast = find_object(filename)) 
                        destruct(beast);
                DBASE_D->clear_object(filename);
                rm(filename + ".c");
        }

        assure_file(filename);
        write_file(filename + ".c", file); // 写入文件
        VERSION_D->append_sn(filename + ".c"); // 给物品增加识别码
  
        catch(call_other(filename, "???"));
        beast = find_object(filename);
        if (! beast)
        {
                ob->delete_temp("beast"); 
                money = new("/clone/money/gold");
                money->set_amount(100);
                money->move(ob, 1);
                message_vision("$N一呆，对$n道：抱歉抱歉！出了一些问题！钱我还是还你吧。\n",
                               this_object(), ob);
                return;
        }
        
#ifdef DB_SAVE
        if (! DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database(); 
        DATABASE_D->db_remove_item(filename); 
        DATABASE_D->db_create_item(beast, beast->query_entire_dbase());
#endif
        beast->save();
        destruct(beast);              

        ob->set("can_whistle/" + beast_id, filename);     
        ob->delete_temp("beast");        
        command("say 你可以吹声口哨召唤你的魔幻兽！<whistle " + beast_id +">\n");
        return;
}

int accept_object(object me, object ob)
{
        string filename;
        string file;
        object cruise_ob, xob;

        // if (ob->query("id") == "xuantian linglongjin" && ob->query("material_attrib"))
        if (ob->query("id") == "dizang zhishi")
        {
                command("say 这可是制作漫游包的特殊材料！");
                command("say 这样吧，你再给我5000两黄金，我就给你制作漫游包！");
                me->set_temp("make_cruise_ob", 1);
                destruct(ob);
                return 1;              
        }
        
        command("xixi");
        command("say 呵呵，多谢这位" + RANK_D->query_respect(me) + " ！");

        if (me->query_temp("make_cruise_ob") && ob->query("money_id"))
        {
               if (ob->value() >= 50000000)
               {                        
                        file = read_file(CRUISE_OB);
                        file = replace_string(file, "LONG_DESCRIPTION",
                                                "这是" + me->query_idname(1) + "的漫游传送包。\n");

                        // give cruise ob to me
                        filename = ITEM_DIR + "cruise/" + me->query("id");
                        if (file_size(filename + ".c") > 0)
                        {
                                if (cruise_ob = find_object(filename)) 
                                        destruct(cruise_ob);
                                        
                                DBASE_D->clear_object(filename);
                                rm(filename + ".c");
                                log_file("cruise_ob", sprintf("%s have new cruise ob.\n", me->query("id")));
                        }
                        assure_file(filename);
                        write_file(filename + ".c", file);
                        VERSION_D->append_sn(filename + ".c");
                        
                        catch(call_other(filename, "???"));
                        cruise_ob = find_object(filename);
                        if (! cruise_ob)
                        {
                                me->delete_temp("make_cruise_ob");
                                xob = new("/clone/item/dizangshi");
                                xob->move(me, 1);
                                message_vision("$N一呆，对$n道：抱歉抱歉！出了一些问题！材料我还是还你吧。\n",
                                               this_object(), me);
                                return 0;
                        }
#ifdef DB_SAVE
                        if (! DATABASE_D->query_db_status())
                                DATABASE_D->connect_to_database(); 
                        DATABASE_D->db_remove_item(filename);  
                        DATABASE_D->db_create_item(cruise_ob, cruise_ob->query_entire_dbase());
#endif
                        
                        cruise_ob->move(me, 1);
                        cruise_ob->save();
                        tell_object(me, HIY "你获得了一个漫游传送包。\n" NOR);
                        me->set("can_summon/cruise ob", filename);
                        me->delete_temp("make_cruise_ob");
                        destruct(ob);
                        return 1;
                }
        }

        if (me->query_skill("training", 1) < 30)
        {
                command("say 你的驭兽术不够，即使养了魔幻兽，也会离你而去！");
                return 0;
        }

        if (ob->query("money_id"))
        {
                if (ob->value() < 1000000)
                {
                        command("say 这位给的未免少了点！每只魔幻兽卵要一百两黄金！");
                        return 0;
                }
                else
                {
                        me->set_temp("beast/money",1);
                        command("say 好我收下了！");
                        command("say " + me->name() +
                                     "，现在我这里有各种魔幻兽卵！");
                        command("say 请选择你要的魔幻兽卵 < choose >");
                        destruct(ob);
                        return 1;
                }
        }
        return 0;
}

int check_legal_id(string id)
{
        int i;
        array legalid;
        object ppl;   
          
        i = strlen(id);
        
        if ((strlen(id) < 3) || (strlen(id) > 20)) 
        {
                write("对不起，英文 id 必须是 3 到 20 个英文字母。\n");
                return 0;
        }
        
        while(i--)
        
        if (id[i] != ' ' && (id[i] < 'a' || id[i] > 'z'))  
        {
                write("对不起，英文 id 只能用英文字母。\n");
                return 0;
        }

        ppl = LOGIN_D->find_body(id);
        
        if (ppl || id == "guest" || id == "new") 
        {
                write("这个名字与别的玩家ID相同了．．．");
                return 0;
        }

        if (file_size(sprintf("/data/user/%c/%s", id[0], id)
                    + __SAVE_EXTENSION__) >= 0) 
        {
                write("这个名字已经被别的玩家使用了．．．");
                return 0;
        } 

        return 1;
}

int check_legal_name(string name, int max_len)
{
        int i;
        string  *legalname;             //not implemented..may add later
        
        i = strlen(name);
        if ((strlen(name) < 2) || (strlen(name) > max_len )) 
        {
                write(sprintf("对不起，魔幻兽中文字必须是 1 到 %d 个中文字。\n",
                      max_len / 2));
                return 0;
        }
        
        if (max_len < 13 && ! is_chinese(name))
        {
                write("对不起，请您用「中文」为宠物取名字或描述。\n");
                return 0;
        }
        return 1; 
}

int attempt_apprentice(object ob)
{
        command("say 滚！给我一边儿去！");
}

int recognize_apprentice(object me, string skill) 
{
        if (skill == "training" || skill == "huisheng-jue") 
                return 1;                
        else 
                return 0;
}
