
#include <ansi.h>

#ifndef GOODS_D 
#define GOODS_D          "/adm/daemons/goodsd"
#endif

int paying;
int help(object me);

int main(object me, string arg)
{
        string str1, str2;
        object tar;
        string me_id, tar_id;
        int amount;

        if (time() - me->query_temp("last_member") < 3 && 
            arg != "?" && ! wizardp(me))
                return notify_fail("系统忙，请稍后再试！\n");
          
        if (arg != "?" && ! wizardp(me))
                me->set_temp("last_member", time());
          
        // 仅允许非会员使用member ?, member ??, member stats, member show goods指令
        if (! MEMBER_D->is_member(me->query("id")))
        {
                if (! arg)return help(me);
                if (arg == "?")return help(me);
                if (arg == "??")return help(me);
                if (arg == "stats")
                        return MEMBER_D->show_all_members(0);

                if (sscanf(arg, "%s %s", str1, str2) != 2)
                        return 0;

                if (str1 != "look" && (str1 != "show" || str2 != "goods"))
                        return 0;
        }

        if (! arg)
        {
                MEMBER_D->show_member_info(me, "info");
                return 1;
        }

        if (arg == "?") return help(me);
        if (arg == "??") return help(me);
        if (arg == "stats")
        {
                return MEMBER_D->show_all_members(0);
        }
        
        if (sscanf(arg, "%s %s", str1, str2) != 2)
                return help(me);

        switch(str1)
        {
        case "show":
                if (str2 == "info")
                {
                        MEMBER_D->show_member_info(me, "info");
                        return 1;
                }
                else if (str2 == "payinfo")
                {
                        MEMBER_D->show_member_info(me, "payinfo");
                        return 1;
                }
                else if (str2 == "buyinfo")
                {
                        MEMBER_D->show_member_info(me, "buyinfo");
                        return 1;
                }
                else if (str2 == "goods")
                {
                        MEMBER_D->show_member_info(me, "goods");
                        return 1;
                }
                else if (str2 == "zhuaninfo")
                {
                        MEMBER_D->show_member_info(me, "transferinfo");
                        return 1;
                }
                else return help(me);

        case "look":
                return GOODS_D->do_look(me, str2);

        case "buy":
                if (! GOODS_D->buy_goods(me, str2))
                {
                        write("购买失败！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "zhuan":
                if (sscanf(str2, "%d to %s", amount, tar_id) != 2)
                        return help(me);
                        
                me_id = me->query("id");
                
                if (me_id == tar_id)
                        return notify_fail("你白痴啊，给自己转帐！\n");       
                               
                if (amount < 1 || amount > 100000)
                        return notify_fail("每次转帐的单位必须在 1 至 100000 之间！\n");
                        
                if (! MEMBER_D->db_transfer_member(me_id, tar_id, amount))
                {
                        write("转帐失败！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "check":
                if (wiz_level(me) < 4)
                        return help(me);
                    
                // 检查对方是否为会员
                if (! MEMBER_D->is_member(str2))
                        return notify_fail("目标为非会员，无法查询！\n");
                   
                tar = UPDATE_D->global_find_player(str2);
                if (! objectp(tar))
                        return notify_fail("没有这个玩家！\n");
                    
                MEMBER_D->show_member_info(tar, "info");

                UPDATE_D->global_destruct_player(tar, 1);

                return 1;
     
        case "remove":
                if (wiz_level(me) < 5)
                        return help(me);
                             
                if (! MEMBER_D->db_remove_member(str2))
                {
                        write("删除会员失败！\n");
                        return 1;
                }
                write("OK.\n");
                return 1;

        default:     
                return help(me);
        }

        return 1;
}

int help (object me)
{
        write(
        
HIY "充值请在官方主页(" HIC "http://www.ourmud.cn/pay.php" HIY ")上完成\n\n" NOR
@HELP
指令格式 : member show [info | payinfo | buyinfo | goods]
           member look 物品代号          查看物品
           member buy 物品代号           购买物品
           member check id               检查会员信息
           member stats                  列出所有的会员
           member zhuan amount to id     泥潭金币($NT)转帐
           member ??                     member 指令帮助
           member ?                      泥潭会员系统简明向导

info    : 显示会员系统面板
payinfo : 显示历史充值交费信息
buyinfo : 显示历史购买物品信息
goods   : 显示英雄商店出售的物品

member check id 为arch以上巫师使用参数。

相关参考文件：help member

HELP );
        return 1;
}
