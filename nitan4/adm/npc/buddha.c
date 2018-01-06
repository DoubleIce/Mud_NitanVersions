// This program is a part of NITAN MudLIB
// Buddha.c

#include <ansi.h>
inherit NPC;
inherit F_NOCLONE;
inherit F_SAVE;

nosave array reborn_skill = ({ 
        "sophistry", "capture", "kingkong", "immortal", "musha", 
        "recover", "astral", 
});
nosave array words = ({
        "班", "若", "菠", "萝", "密", "啊", "吗", "咪", "哄",
        "度", "众", "生", "者", "应", "明", "以", "何", "得",
        "有", "空", "净", "相", "我", "虚", "妄", "情", "少",
        "福", "如", "來", "法", "金", "思", "悟", "灭", "失",
});
// 存盘文档
string query_save_file() {
        return DATA_DIR "npc/buddha";
}

mapping reborn_data = ([]);
int ask_reborn();
void remove() { save(); }

varargs mixed query_reborn_data(string ob) { 
        if( !ob ) return reborn_data;   
        if( !undefinedp(reborn_data[ob]) )
                return reborn_data[ob];
        return 0; 
} 

int clear_reborn_data(string ob) {
        if( !undefinedp(reborn_data[ob]) ) {
                map_delete(reborn_data, ob);
                return 1;
        }
        return 0;
}

void create()
{
        seteuid(getuid());
        restore();
        set_name(HIY "释迦牟尼" NOR, ({ "buddha", "fo zu", "fo", "shijia muni" }));
        set("long", @LONG
佛祖庄严宝像，让人不敢正视。
LONG);
        set("nickname", HIW "三界法王" NOR);
        set("title", HIC "佛祖" NOR);
        set("gender", "男性" );
        set("age", 500);
        set("attitude", "friendly");
        set("max_jing", 99999);
        set("max_qi", 99999);
        set("max_jingli", 99999);
        set("jingli", 99999);
        set("max_neili", 99999);
        set("neili", 99999);
        set("jiali", 9999);
        set("str", 99);
        set("int", 99);
        set("con", 99);
        set("dex", 99);
        set("combat_exp", 99999999);

        set_skill("dodge", 999);
        set_skill("unarmed", 999);
        set_skill("force", 999);
        set_skill("parry", 999);
        set_skill("sword", 999);
        set_skill("medical", 999);
        set_skill("literate", 999);
        set_skill("lamaism", 999);
        set_skill("buddhism", 999);
        set_skill("shaolin-yishu", 999);
        set_skill("idle-force", 999);
        set_skill("huntian-baojian", 999);
        set_skill("lunhui-jian", 999);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "lunhui-jian");
        map_skill("sword", "lunhui-jian");
        map_skill("medical", "shaolin-yishu");

        set("inquiry", ([
                "转世重生" : (: ask_reborn :),
        ]));

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("/clone/cloth/y-jiasha")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        set("startroom", "/d/reborn/heaven");
        check_clone();
}

void init()
{
        add_action("do_decide", "decide");
}

int ask_reborn()
{
        object me;

        me = this_player();
        command("look " + me->query("id"));

        if( me->query("reborn/times") ) {
                command("say 你的阿赖耶识不是已经打开了吗？");
                return 1;
        }

        if( !me->query("reborn_lunhui") ) { 
                command("say 你的转世机缘未到，强求不得！");
                return 1;
        }

        command("say 你可是也对此生感到困惑，想要探寻人生真谛吗？");
        command("say 若要转生则你之武学就将尽毁，你可愿意？");
        message_vision( HIC"$N" HIC"对$n" HIC"道：若你心意已决就输入 decide 吧！\n"NOR,
                        this_object(), me) ;

        me->set_temp("reborn/ask", 1);
        return 1;
}

int do_decide()
{
        int i;
        string msg;
        object me;

        msg = "";
        me = this_player();

        if( !me->query_temp("reborn/ask") )
                return 0;

        tell_object(me, HIW "佛祖在你耳边说道：我告诉你一句揭语，"
                "你可参悟一下是啥意思，\n来世你若有缘再见到我，"
                "凭此揭语我会给你开启前生记忆！\n"
                "此揭语须当谨记在心，切记切记！\n" NOR);

        for( i = 0; i < 5; i++)
                msg += words[random(sizeof(words))];

        tell_object(me, HIY "\n佛祖在你耳边说道，给你的揭语是：" HIR + msg + "\n" NOR);
        tell_object(me, HIY "记下了吗？我即刻就送你去投胎了！\n\n"NOR);

        remove_call_out("reborn_player");
        call_out("reborn_player", 3, me, msg);
        return 1;
}

int reborn_player(object me, string msg)
{
        mapping all_skills, off_skills;
        mapping my, spc_data, tmp_data, mem_data;
        array sname, oname, files;
        string skill, dst;
        object ob;
        int i, n, vip, skill_lvl;  
        int money, endtime, day;     
       
        my = me->query_entire_dbase();
        if( my["gender"] == "无性" ) my["gender"] = "男性";
                     
        off_skills = my["offer"];
        all_skills = me->query_skills();
        oname = keys(off_skills);       
        oname -= ({ "neili" });   
        sname = keys(all_skills);        
        n = sizeof(all_skills);
        for( i = 0; i < n; i++ ) {
                if( SKILL_D(sname[i])->type() != "martial" ) {
                        if( all_skills[sname[i]] > 500 )
                                all_skills[sname[i]] = 500;
                } else {
                        if( sizeof(oname) && member_array(sname[i], oname) != -1 ) {
                                if( (skill_lvl = off_skills[sname[i]] - 2000) > 200 )
                                        all_skills[sname[i]] = skill_lvl;
                                else
                                        all_skills[sname[i]] = 200;
                                oname -= ({ sname[i] });
                        } else {
                                if( all_skills[sname[i]] > 200 )
                                        all_skills[sname[i]] = 200;
                        }
                }
        }
        
        if( (n = sizeof(oname)) > 0 ) {
                for( i = 0; i < n; i++ ) {
                        if( (skill_lvl = off_skills[oname[i]] - 2000) > 200 )
                                all_skills[oname[i]] = skill_lvl;
                        else
                                all_skills[oname[i]] = 200;
                }
        }
                
        tmp_data = ([]);
        tmp_data["all_skills"] = copy(all_skills);
        tmp_data["can_perform"] = copy(my["can_perform"]);
        tmp_data["can_summon"] = copy(my["can_summon"]);
        tmp_data["family_name"] = copy(my["family"]["family_name"]);
        tmp_data["reborn_time"] = time();
        tmp_data["reborn_pass"] = msg;
        tmp_data["gender"] = copy(my["gender"]);
        tmp_data["name"] = copy(my["name"]);
        tmp_data["str"] = copy(my["str"]);
        tmp_data["int"] = copy(my["int"]);
        tmp_data["con"] = copy(my["con"]);
        tmp_data["dex"] = copy(my["dex"]);
                
        spc_data = ([ "hermit" : 1 ]);
        files = reborn_skill;
        skill = files[random(sizeof(files))];
        spc_data += ([ skill : 1 ]);
        files -= ({ skill });
        if( random(10) == 1 ) {
                skill = files[random(sizeof(files))];
                spc_data += ([ skill : 1 ]);
        }
        spc_data += my["special_skill"];
        tmp_data["special_skill"] = spc_data;
        
        if( MEMBER_D->is_member(me) ) {
                money = MEMBER_D->db_query_member(me, "money");
                if( MEMBER_D->is_valid_member(me) ) {
                        endtime = MEMBER_D->db_query_member(me, "endtime");
                        day = (endtime - time()) / 86400;
                } else  day = 0;     
                                                          
                vip = MEMBER_D->db_query_member(me, "vip");
                MEMBER_D->db_remove_member(me);
                mem_data = ([ "money" : money, "day" : day, "vip" : vip ]);
                tmp_data["member"] = mem_data;
        }
        reborn_data[me->query("id")] = tmp_data;
        save();
        message("vision", HBRED "【转世重生】天界：" + me->query("name") + "(" + me->query("id") + ")"
                HBRED "已得佛祖点化转世之道，得到人神魔三界庇佑，元神转世重生！\n" NOR, users());

        message_vision("只见$N化作一屡轻烟，渐渐消失了……\n", me);
        UPDATE_D->remove_user(me->query("id"), 1);
        return 1;
}
