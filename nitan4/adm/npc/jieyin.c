
#include <ansi.h>

inherit NPC;
inherit F_NOCLONE;

void create()
{
        set_name(HIY "空间接引使者" NOR, ({ "jieyin shizhe", "jieyin", "shizhe" }));
        set("long", @LONG
这是夕阳专派的空间接引使者，拥有无穷的力量，能够扭转时空，颠倒乾坤。
LONG);

        set("title", HIG "BOSS挑战进入点" NOR);
        set("gender", "男性" );
        set("age", 34);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("no_suck", 1);
        set("combat_exp", 12000000);
        set("level", 100);
        
        set("inquiry", ([
                "挑战BOSS" : "想挑战BOSS？输入 ask shizhe about <BOSS等级> 即可进入挑战空间",
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

        set("startroom", "/d/shaolin/hanshui1");
        check_clone();
}

mixed accept_ask(object me, string arg)
{
        int valid;
           
        if( !arg || arg == "" )
                return 0;
        
        if( arg == "all" || arg == "挑战BOSS" )
                return "想挑战BOSS？输入 ask shizhe about <BOSS等级> 即可进入挑战空间。\n";
        
        valid = FUBEN_D->valid_enter(this_player(), arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(this_player(), arg);
        else {
                if( valid == 0 )
                        write("您实战经验不足，进挑战BOSS恐有不测，还是先历练一下再来吧。\n");
                else if( valid == -1 )
                        write("您经验太高了，就不要进去欺负那些可怜的小怪物了吧。\n");
                else if( valid == -2 )
                        write("游戏中目前并没有开放该等级BOSS，请您核对后再试。\n");
                else if( valid == -3 )
                        write("挑战BOSS限制IP多重进入，您已经超过最高上限。\n");
                else if( valid == -4 )
                        write("该BOSS被巫师关闭，您暂时无法进入。\n");
                else if( valid == -5 )
                        write("你离上次挑战该BOSS的时间太短，请休息会再来。\n");
        }        
        return 1;
}


