// This program is a part of NITAN MudLIB
// Fujun4.c
// Written by Lonely@NITAN (03/29/2009)

#include <ansi.h>

inherit NPC;

int  ask_offer();
void destroy();
int  do_offer(string arg);
int  do_answer(string arg);
int  do_report(string arg);

void create()
{
	set_name(BLU "恒山府君" NOR, ({ "hengshan fujun", "hengshan", "fujun" }));
	set("long", "他就是恒山府君。\n");
	set("title", HIW "北岳" NOR);
	set("gender", "男性");
	set("age", 50);
	set("str", 91);
	set("int", 39);
	set("con", 50);
	set("dex", 62);
	
	set("max_qi", 10000000);
	set("max_jing", 10000000);
        set("max_jingli", 10000000);
        set("jingli", 10000000);
	set("max_neili", 12000000);
	set("neili", 12000000);
	set("jiali", 55000);
	set("combat_exp", 2000000000);
	set("score", 1200000);

	set_skill("force", 2700);
        set_skill("parry", 2700);
        set_skill("dodge", 2700);
        set_skill("sword", 2700);
        set_skill("unarmed", 2700);
        set_skill("pixie-jian", 2700);        
        set_skill("literate", 2700);
        set_skill("martial-cognize", 2700);
        set_skill("kuihua-mogong", 2700);

	map_skill("force", "kuihua-mogong");
	map_skill("dodge", "kuihua-mogong");
	map_skill("unarmed", "kuihua-mogong");
	map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

	prepare_skill("unarmed", "kuihua-mogong");

        set("inquiry", ([
                "献祭"  : (: ask_offer : ),
                "offer" : (: ask_offer : ),
        ])); 
        
	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "dodge.sheng" :),
		(: perform_action, "sword.bian" :),
		(: perform_action, "sword.tian" :),
		(: perform_action, "sword.qiong" :),
		(: perform_action, "sword.zhenwu" :),
                (: perform_action, "dodge.sheng" :),
                (: perform_action, "unarmed.bian" :),
                (: perform_action, "unarmed.tian" :),
                (: perform_action, "unarmed.qiong" :),
		(: exert_function, "recover" :),
		(: exert_function, "powerup" :),
		(: exert_function, "shield" :),
		(: exert_function, "roar" :),
	}) );
        
        set_temp("apply/attack", 5000); 
        set_temp("apply/armor", 10000); 
        set_temp("apply/damage", 50000); 
        set_temp("apply/unarmed_damage", 50000); 
        set_temp("apply/add_xuruo", 90); 
        set_temp("apply/reduce_xuruo", 100);
        set_temp("apply/add_damage", 100);
        set_temp("apply/reduce_damage", 90); 
        set_temp("apply/reduce_busy", 30); 
        set_temp("apply/add_busy", 10); 
         
        set("auto_perform", 1); 
        // set("bonus", 100000); 

	setup();

        carry_object("/clone/weapon/sword")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_report", "report");
}

int ask_offer()
{
        object me, ob;

        me = this_player();
        if( this_object()->query("worship") != me->query("id") )
                return 0;
                
        if( !objectp( ob = present("contract", me) ) ||
            ob->query("owner") != me->query("id") ) {
                tell_object(me, BLU "恒山府君说道：「你还没有去领取阎王契(contract)，我不会接受你的献祭请求。」\n" NOR);
                return 1;
        }
        
        message_vision(CYN "$N" CYN "讶道：「既是身怀阎王契，本府君这便给你一个机会吧。」\n"
                       CYN "$N" CYN "目射奇光续道：「本府君嗜武如命，近日神功有成，你我打上一架，你若胜了，本府君便准了你的献祭。」\n" NOR, 
                       this_object(), me); 
                       
        tell_object(me, BLU "恒山府君想要与你切磋，你是否同意(answer yes/no)？\n" NOR);
        add_action("do_answer", "answer"); 
                       
        return 1; 
} 

int do_answer(string arg)
{
        object ob, me = this_player();

        if( this_object()->query("worship") != me->query("id") )
                return 0;
                
        if( arg == "yes" ) { 
                message_vision(BLU "$N" BLU "大笑道：「好好好！你和我的幻象痛痛快快打上一场！」\n" NOR, 
                               this_object(), me);
                ob = new(__DIR__"fujun4-shadow");
                ob->move(environment(me)); 
                me->set_temp("shadow/to_kill", 1);                
        } else if( arg == "no" ) { 
                message_vision(BLU "$N" BLU "大怒道：没有用的东西！」\n" NOR,
                               this_object(), me); 
                remove_call_out("destroy");
                call_out("destroy", 1);
        } else 
                return notify_fail("你要回答什么？\n"); 
                
        return 1; 
}

int do_report(string arg)
{
        object me, ob;

        me = this_player();
        ob = this_object();

        if( ob->query("worship") != me->query("id") )
                return 0;

        if( !me->query_temp("shadow/to_kill") )
                return notify_fail(BLU "恒山府君皱眉道：「你想要干什么？」\n" NOR);

        if( !me->query_temp("shadow/killed") )
                return notify_fail(BLU "恒山府君皱眉道：「你还没有战胜我的幻象呀！」\n" NOR);

        message_vision( BLU "$N" BLU "笑道：「果然很有诚意，果真是阎王契的有缘人！」\n"
                        BLU "$N" BLU "又道：「本府君最重神兵之技，你必须献祭(offer)一门兵器技能。」\n" NOR,
                        ob, me);
        me->delete_temp("shadow");
        me->set_temp("can_offer", ob->query("id"));
        add_action("do_offer", "offer");
        return 1;
}

void do_broadcast(int index)
{
        if( !environment() )
                return;

        switch (index)
        {
        case(0):
                tell_room(environment(),
                        BLU "恒山府君点头道：「如此甚好，我这便记载到阎王契上。」\n" NOR);
                break;
        case(1):
                tell_room(environment(),
                        BLU "只见恒山府君喃喃有词，乍时山岚乱动、云间溢出光芒，只见一授案飘然而下，其上文房四宝一应俱全。\n" NOR);
                break;
        case(2):
                tell_room(environment(),
                        BLU "恒山府君提笔挥洒，只见丝丝紫光渗入阎王契上，片刻即成。\n" NOR);
                break;
        case(3):
                tell_room(environment(),
                        BLU "恒山府君满意道：「这便成了。本府君功成身退，小友多多保重。」\n" NOR);
                break;
        default:
                tell_room(environment(),
                        BLU "恒山府君化做一阵清烟消失，转瞬便已飘渺无踪。\n授案化做一阵清烟消失，转瞬便已飘渺无踪。\n" NOR);

                remove_call_out("destroy");
                destruct(this_object());
                return;
        }
        call_out("do_broadcast", 1, ++index);
}

int do_offer(string arg)
{
        object me, ob, weapon;
        string skill, msg;
        array rec;
        int level;

        me = this_player();

        if( this_object()->query("worship") != me->query("id") )
                return 0;
                
        if( !arg || sscanf(arg, "%s %d", skill, level) != 2 )
                return notify_fail("格式：offer skill level\n");

        if( !objectp( ob = present("contract", me) ) ||
                ob->query("owner") != me->query("id") )
                return notify_fail(BLU "恒山府君说道：「你还没有去领取阎王契(contract)，我不会接受你的献祭请求。」\n" NOR);

        if( ob->query("offer_hengshan") ) 
                return notify_fail(BLU "恒山府君说道：「你已经在恒山献祭过了，就不用再来献祭吧。」\n" NOR);
                
        if( !me->query_temp("can_offer") ||
                me->query_temp("can_offer") != this_object()->query("id") )
                return notify_fail(BLU "恒山府君皱眉道：「你还是先去完成我的条件再来献祭吧。」\n" NOR);

        if( me->query_skillo(skill, 1) < 2000 || level < 2000 )
                return notify_fail(BLU "恒山府君皱眉道：「这点小玩意你还是拿回家自己玩吧。」\n" NOR);

        if( me->query_skillo(skill, 1) < level )
                return notify_fail(BLU "恒山府君皱眉道：「你这门技能没有这么高的等级。」\n" NOR);
        
        if( !objectp(weapon = me->query_temp("weapon")) )
                return notify_fail(BLU "恒山府君皱眉道：「你先把你的兵器装备上再说。」\n" NOR);
                    
        if( me->query_skill_mapped(weapon->query("skill_type")) != skill )
                return notify_fail(BLU "恒山府君皱眉道：「你还是先把这个技能激发到兵器技能上吧。」\n" NOR);

        me->add_skill(skill, -level); 
        me->delete_temp("can_offer");
        me->set("offer/" + skill, level);
        
        message_vision( HIR "$N" HIR "略一沉思道：「既然如此，为显诚意，我决定献祭" + to_chinese(skill) + level + "级。」\n" NOR, me );
        tell_object(me, BLU "恒山府君凌空一掏，你忽然觉得自己身上少了什么。\n" NOR);                  
        msg = HIW + NATURE_D->game_time() + "，" + me->query_idname() + HIW "于恒山献祭" + to_chinese(skill) + level + "级。\n";
        
        rec = ob->query("offer");
        if( ! rec ) rec = ({});
        rec += ({ msg });
        ob->set("offer", rec);
        ob->set("offer_hengshan", 1);
        
        do_broadcast(0);
        return 1;
}

void destroy()
{
        message_vision( BLU "$N化做一阵清烟消失，转瞬便已飘渺无踪。\n" NOR,
                        this_object() );
        destruct(this_object());
        return;
}

void start_borrowing()
{
        remove_call_out("destroy");
        call_out("destroy", 900);
}

varargs void die(object killer)
{
        object me = this_object();

        me->recover();
        return;
}

void unconcious()
{
        object me = this_object();

        me->recover();
        return;
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}
