// 五彩喇叭
#include <ansi.h>
inherit ITEM;
 
void create()
{
        set_name(HIM"五彩喇叭" NOR, ({ "wucai laba","laba","wucai"}));
        set("long", 
                  "一个五彩喇叭，用它说话可以带颜色哦。\n"
                  "用法：\n"
                  "cui 动作 你的词语 动作可以是say reply shout chat 等 \n"
                  "比如 cui chat $HIG$ hi\n"
                  "颜色列表：\n"
                         "                     $NOR$ - 恢复正常颜色\n"
 "$RED$ - "RED"红色"NOR"         $HIR$ - "HIR"亮红色\n"NOR
 "$GRN$ - "GRN"绿色"NOR"         $HIG$ - "HIG"亮绿色\n"NOR
 "$YEL$ - "YEL"土黄色"NOR"       $HIY$ - "HIY"黄色\n"NOR
 "$BLU$ - "BLU"深蓝色"NOR"       $HIB$ - "HIB"蓝色\n"NOR
 "$MAG$ - "MAG"浅紫色"NOR"       $HIM$ - "HIM"粉红色\n"NOR
 "$CYN$ - "CYN"蓝绿色"NOR"       $HIC$ - "HIC"天青色\n"NOR
 "$WHT$ - 浅灰色       $HIW$ - "HIW"白色\n"NOR
                         );
        set("unit","个");
        set_weight(100);
        set("value",3000000);
        set("degree",20);
        set("flag","spec/laba");
        set("desc","用它说话可以带颜色。");
        set("credit",5);
        setup();
}
 
/*
void init()
{
        add_action("do_cui", "cui");
        add_action("do_cui", "chui");
}
*/
 
int do_cui(string arg)
{
        string arg1,arg2;
        object me = this_player(); 

        if (!arg) return notify_fail("你要吹什么？\n");
        sscanf(arg,"%s %s",arg1,arg2);
        if (arg1 != "chat" && arg1 != "rumor" && arg1 !="party" && arg1 != "group" 
        &&      arg1 !="say" && arg1 !="tell" && arg1 !="reply" && arg1 !="whisper" && arg1 !="shout" &&arg1 !="nt")
                return notify_fail("你想用五彩喇叭吹什么？\n");
        
        arg2 = trans_color(arg2, 3);

        me->force_me(arg1+" "+arg2);

        return 1;
}
