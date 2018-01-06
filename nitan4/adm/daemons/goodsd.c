// 黑店出售物品小型数据库系统

#include <ansi.h>
#include <command.h>

mapping goods = ([
        "liandan"  : "炼丹秘本:1:/clone/book/wudang:object:武当炼丹秘本有玉清散的秘方",
        "int3"  : "神恩通慧仙丹:1:/clone/fam/gift/int3:object:增加先天悟性吃的第六点丹",
        "con3"  : "洗髓再造仙丹:1:/clone/fam/gift/con3:object:增加先天根骨吃的第六点丹",
        "str3"  : "蚩尤诛元仙丹:1:/clone/fam/gift/str3:object:增加先天臂力吃的第六点丹",
        "dex3"  : "破阳无极仙丹:1:/clone/fam/gift/dex3:object:增加先天身法吃的第六点丹",

        "clearint"      : "消慧糊涂丹:5:/clone/item/clearint:object:可减少吃丹增加的先天悟性",

        "putizi"        : "菩提子:1:/clone/gift/puti-zi:objamount:可增加最大内力100-129点，数量20个",
        "jiuzhuan"      : "九转金丹:1:/clone/gift/jiuzhuan:objamount:可增加所有先天前4点丹，数量10个",
        "tianxiang"     : "天香玉露:1:/clone/gift/tianxiang:objamount:参考help item，数量15个",
        "xuanhuang1"    : "玄黄紫清丹:1:/clone/gift/xuanhuang:objamount:参考help item，数量5个",
        "yuqingsan"     : "玉清散:1:/clone/medicine/yuqing:objamount:可增加最大精力10-11点，数量120包",
        "zhenyu"        : "镇狱惊天丸:20:/clone/fam/max/zhenyu:object:参考help item,只能吃一次",
        "longjia"       : "子午龙甲丹:15:/clone/fam/max/longjia:object:参考help item级,只能吃一次",
        "xuanhuang2"    : "玄黄紫箐丹:15:/clone/fam/max/xuanhuang:object:参考help item,只能吃一次",
        "xiaoli"        : "消戾丹:1:/clone/item/xiaolidan:object:可以清除人物的戾气",
        "zhaoshenxiang"        : "召神香:10:/d/reborn/obj/xiang:object:转世时召唤五岳府君用的",

        "learn"         : "紫金学习勋章:60:/clone/item/learn-emblem:object:提升每次学习次数800",
        "derive"        : "紫金汲取勋章:70:/clone/item/derive-emblem:object:提升每次汲取二倍速度",
        "practice"      : "紫金练习勋章:70:/clone/item/practice-emblem:object:提升每次练习次数800",
        "research"      : "紫金研究勋章:80:/clone/item/research-emblem:object:提升每次研究次数800",
        "research2"     : "钻石研究勋章:120:/clone/item/research-emblem2:object:提升每次研究次数1500",

        "ganjiang"      : "干将圣符:30:/adm/npc/obj/ganjiang-charm:object:可将装备及勋章设置为可SUMMON属性",
        "moye"          : "莫邪圣符:20:/clone/item/moye-charm:object:可将物品设置为下线不掉属性",
        "bored"         : "玄兵圣水:10:/clone/item/bored-water:object:可将装备最大化打孔辅助物品",
        "bindable"      : "绑定神符:1:/clone/item/bindable-charm:object:可将物品绑定",
        "enchaseA"      : "镶嵌之符:5:/clone/item/enchaseA-charm:object:可使得镶嵌游戏中的装备成功率100%",
        "enchaseB"      : "镶嵌之符:5:/clone/item/enchaseB-charm:object:可使得镶嵌自造装备成功率100%",
        // "extracte"              : "抽取之符:30:/clone/item/extracte-charm:object",
        "ouyezi"                : "欧冶子圣符:60:/clone/item/ouyezi-charm:object:可将自造兵器设置为准10LV状态",
        "tianshi"               : "天师护身符:3:/clone/item/tianshi-charm:object:佩带在身上可以让死亡无损失",
        "changename"         : "装备更名卡:30:/adm/npc/obj/cname-card:object:可以修改自造装备的名称及英文代号",
        "closed"         : "闭关符:30:/clone/item/closed-charm:object:可以提高四倍的闭关速度",
        "expcard"         : "双倍经验卡:1:/clone/item/exp-card:object:可以获得2个小时双倍经验时间，只能未转世玩家使用",

        "butian"             : "补天石:20:/d/item/obj/butian:object:用来制作兵器的材料",
        "bingcans"             : "冰蚕丝:20:/d/item/obj/tiancs:object:用来制作防具的材料",
        "dizangshi"             : "地藏之石:100:/clone/item/dizangshi:object:用来制作漫游包的材料",
        "noname"                : "无名之物:120:/clone/item/noname:object:目前最好的打造装备材料",
        "washgift"              : "洗天赋丹:50:/clone/item/washgift:object:可以重新分配先天天赋一次，检查已学技能是否符合新的天赋",
        "wuji"              : "无极圣水:50:/clone/item/wuji-water:object:可将自造装备直接扩展为最大孔数即防具7孔兵器9孔",
        "bcrystal"            : "黑色水晶:20:/clone/item/bcrystal:object:可抽取宝石类物品中的魔法属性",
        /*
        "taixu"                 : "上古太虚:90:/clone/item/taixu:object",
        "hupo"                  : "上古虎魄:80:/clone/item/hupo:object",
        "shihun"                : "地心噬魂:70:/clone/item/shihun:object",
        "xuanyu"                : "九地玄玉:60:/clone/item/xuanyu:object",
        */
        "tianjing"              : "寰宇天晶:60:/clone/item/tianjing:object:仅次于无名的打造材料,适用于打造防具",

        "leishentong"           : "雷神之瞳·电:10:/clone/item/leishentong:object:电属性终极10LV镶嵌材料",
        "mozhixin"              : "圣魔之心·魔:10:/clone/item/mozhixin:object:魔属性终极10LV镶嵌材料",
        "hanjing"               : "神之寒晶·冰:10:/clone/item/hanjing:object:冰属性终极10LV镶嵌材料",
        "huojingling"           : "火之精灵·火:10:/clone/item/huojingling:object:火属性终极10LV镶嵌材料",

        "rune06"                : "符文伊司:10:/clone/enchase/rune06:object:可镶嵌在装备上,详细参考help rune",
        "rune07"                : "符文塔爾:10:/clone/enchase/rune07:object:可镶嵌在装备上,详细参考help rune",
        "rune08"                : "符文拉爾:10:/clone/enchase/rune08:object:可镶嵌在装备上,详细参考help rune",
        "rune09"                : "符文歐特:10:/clone/enchase/rune09:object:可镶嵌在装备上,详细参考help rune",
        "rune10"                : "符文書爾:10:/clone/enchase/rune10:object:可镶嵌在装备上,详细参考help rune",
        "rune11"                : "符文安姆:10:/clone/enchase/rune11:object:可镶嵌在装备上,详细参考help rune",
        "rune12"                : "符文索爾:10:/clone/enchase/rune12:object:可镶嵌在装备上,详细参考help rune",
        "rune13"                : "符文沙爾:10:/clone/enchase/rune13:object:可镶嵌在装备上,详细参考help rune",
        "rune14"                : "符文多爾:10:/clone/enchase/rune14:object:可镶嵌在装备上,详细参考help rune",
        "rune15"                : "符文海爾:10:/clone/enchase/rune15:object:可镶嵌在装备上,详细参考help rune",
        "rune16"                : "符文埃歐:10:/clone/enchase/rune16:object:可镶嵌在装备上,详细参考help rune",
        "rune17"                : "符文盧姆:10:/clone/enchase/rune17:object:可镶嵌在装备上,详细参考help rune",
        "rune18"                : "符文科:10:/clone/enchase/rune18:object:可镶嵌在装备上,详细参考help rune",
        "rune19"                : "符文法爾:10:/clone/enchase/rune19:object:可镶嵌在装备上,详细参考help rune",
        "rune20"                : "符文藍姆:20:/clone/enchase/rune20:object:可镶嵌在装备上,详细参考help rune",
        "rune21"                : "符文普爾:20:/clone/enchase/rune21:object:可镶嵌在装备上,详细参考help rune",
        "rune22"                : "符文烏姆:20:/clone/enchase/rune22:object:可镶嵌在装备上,详细参考help rune",
        "rune23"                : "符文马尔:20:/clone/enchase/rune23:object:可镶嵌在装备上,详细参考help rune",
        "rune24"                : "符文伊司特:20:/clone/enchase/rune24:object:可镶嵌在装备上,详细参考help rune",
        "rune25"                : "符文古爾:20:/clone/enchase/rune25:object:可镶嵌在装备上,详细参考help rune",
        "rune26"                : "符文伐克斯:20:/clone/enchase/rune26:object:可镶嵌在装备上,详细参考help rune",
        "rune27"                : "符文歐姆:20:/clone/enchase/rune27:object:可镶嵌在装备上,详细参考help rune",
        "rune28"                : "符文羅:20:/clone/enchase/rune28:object:可镶嵌在装备上,详细参考help rune",
        "rune29"                : "符文瑟:20:/clone/enchase/rune29:object:可镶嵌在装备上,详细参考help rune",
        "rune30"                : "符文貝:25:/clone/enchase/rune30:object:可镶嵌在装备上,详细参考help rune",
        "rune31"                : "符文喬:25:/clone/enchase/rune31:object:可镶嵌在装备上,详细参考help rune",
        "rune32"                : "符文查姆:25:/clone/enchase/rune32:object:可镶嵌在装备上,详细参考help rune",
        "rune33"                : "符文薩德:25:/clone/enchase/rune33:object:可镶嵌在装备上,详细参考help rune",

        "agile"                 : "如鬼似魅:10:/kungfu/special/accuracy:special:先天技能,最多可拥有四个",
        "hatred"                : "杀气冲霄:10:/kungfu/special/hatred:special:先天技能,最多可拥有四个",
        "mystery"               : "玄黄聚纳:10:/kungfu/special/mystery:special:先天技能,最多可拥有四个",
        "power"                 : "天神降世:10:/kungfu/special/power:special:先天技能,最多可拥有四个",
        "self"                  : "小周天运转:10:/kungfu/special/self:special:先天技能,最多可拥有四个",
        "trick"                 : "鬼话连篇:10:/kungfu/special/trick:special:先天技能,最多可拥有四个",
        "youth"                 : "天颜永驻:10:/kungfu/special/youth:special:先天技能,最多可拥有四个",
        "sophistry"             : "诡辩奇学:20:/kungfu/special/sophistry:special2:转世技能,最多限购四个", 
        "capture"               : "遁影擒踪:20:/kungfu/special/capture:special2:转世技能,最多限购四个", 
        "kingkong"              : "大力金刚:20:/kungfu/special/kingkong:special2:转世技能,最多限购四个", 
        "immortal"              : "不死金身:20:/kungfu/special/immortal:special2:转世技能,最多限购四个", 
        "musha"                 : "武星转世:20:/kungfu/special/musha:special2:转世技能,最多限购四个", 
        "recover"               : "破元大法:20:/kungfu/special/recover:special2:转世技能,最多限购四个", 
        "astral"                : "破妄神瞳:20:/kungfu/special/astral:special2:转世技能,最多限购四个", 
        /*
        "emperor"               : "真命天子:200:/kungfu/special/emperor:special",
        "queen"                 : "九天玄女:200:/kungfu/special/queen:special",
        "lonely"                : "天煞孤星:200:/kungfu/special/lonely:special",
        */

        "water"                 : "圣沐成功:20:int:story:加先天悟性的故事,只可购买一次",
        "sun"                   : "日炽成功:20:str:story:加先天臂力的故事,只可购买一次",
        "feng"                  : "凤舞成功:20:dex:story:加先天身法的故事,只可购买一次",
        "lighting"              : "电击成功:20:con:story:加先天根骨的故事,只可购买一次",

        "gold"                  : "十万两黄金:1:1000000000:gold:游戏中的黄金",

        "newbie"                : "新人大礼包:80:newbie:package:新人大礼包,快速成长",
        "10LVa"                 : "10LV兵器包:150:10LVa:package:冰属性终极10LV包",
        "10LVb"                 : "10LV兵器包:150:10LVb:package:电属性终极10LV包",
        "10LVc"                 : "10LV兵器包:150:10LVc:package:魔属性终极10LV包",
        "10LVd"                 : "10LV兵器包:150:10LVd:package:火属性终极10LV包",
        "yj-rune"               : "研究符文包:140:yj-rune:package:包含7个rune31和7个rune33",
        "rune24-eq"             : "符文伊司特包:70:rune24-eq:package:包含7个rune24",
        "rune30-eq"             : "符文貝包:100:rune30-eq:package:包含10个rune30",
        "rune31-eq"             : "符文喬包:100:rune31-eq:package:包含10个rune31",
        "rune32-eq"             : "符文查姆包:100:rune32-eq:package:包含10个rune32",
        "rune33-eq"             : "符文薩德包:100:rune33-eq:package:包含10个rune33",                                
        "skull5-eq"             : "骷髅头包:50:skull5:package:包含300个没有鉴定属性的骷髅头(skull5)",
        "redgem6-eq"            : "研究宝石包:200:redgem6-eq:package:包含30个镶嵌兵器宝石及70个镶嵌防具宝石，研究、汲取和练习效果各3%属性",

        "monthcard"             : "月度会员:12:monthcard:card:会员月卡,不可转让",
        "seasoncard"            : "季度会员:30:seasoncard:card:会员季卡,不可转让",
        "yearcard"              : "年度会员:100:yearcard:card:会员年卡,不可转让",
        "forevercard"           : "终身会员:280:forevercard:card:会员终身卡,不可转让",
]);

private string chinese_types(string types)
{
        switch(types)
        {
        case "object"             :    return HIC "物品" NOR;
        case "objamount"          :    return HIC "物品" NOR;
        case "special"            :    return HIG "特殊技能" NOR;
        case "special2"           :    return HIW "转世技能" NOR;
        case "story"              :    return HIM "故事" NOR;
        case "package"            :    return HIR "※" NOR;
        case "card"               :    return HIY "★" NOR;
        case "gold"               :    return HIY "＄" NOR;
        default                   :    return HIR "未知" NOR;
        }
}

private void log_buyinfo(object ob, string which, int value)
{
        string buyinfo;

        buyinfo = MEMBER_D->db_query_member(ob, "buyinfo");
        buyinfo += sprintf("%s(%s)于%s花费 %d $NT购买物品 %s 1。\n",
                           ob->name(1),
                           ob->query("id"),
                           TIME_D->replace_ctime(time()),
                           value,
                           which);

        MEMBER_D->db_set_member(ob, "buyinfo", buyinfo);
        MEMBER_D->db_add_member(ob, "buytimes", 1);
        MEMBER_D->db_add_member(ob, "buyvalue", value);
        MEMBER_D->db_set_member(ob, "last_buytime", time());
        MEMBER_D->db_set_member(ob, "last_buyob", which);
        MEMBER_D->db_set_member(ob, "last_buyvalue", value);
        return;
}

/***************显示出售物品的详细清单********************************
*********************************************************************/
string get_types(string arg)
{
        string strtmp;
        array items;

        strtmp = goods[arg];
        items = explode(strtmp, ":");

        return items[3];
}

int sort_object(string str1, string str2)
{
        if( get_types(str1) == "package" ) return 1;
        if( get_types(str2) == "package" ) return -1;

        if( get_types(str1) == "objamount" ) return 1;
        if( get_types(str2) == "objamount" ) return -1;

        if( get_types(str1) == "object" ) return 1;
        if( get_types(str2) == "object" ) return -1;

        if( get_types(str1) == "story" ) return 1;
        if( get_types(str2) == "story" ) return -1;

        if( get_types(str1) == "special" ) return 1;
        if( get_types(str2) == "special" ) return -1;

        if( get_types(str1) == "special2" ) return 1;
        if( get_types(str2) == "special2" ) return -1;
        
        if( get_types(str1) == "card" ) return 1;
        if( get_types(str2) == "card" ) return -1;

        if( get_types(str1) == "gold" ) return 1;
        if( get_types(str2) == "gold" ) return -1;

        return -1;
}

public varargs void show_goods(string arg)
{
        string strtmp;
        int i, j;
        array obs, all, items;

        obs = keys(goods);

        all = unique_array(obs, (:  get_types($1) == "objamount" ? 1 : get_types($1) == "object" ? 2 :
                                    get_types($1) == "story" ? 3 : get_types($1) == "special" ? 4 :
                                    get_types($1) == "special2" ? 5 : get_types($1) == "card" ? 6 : 
                                    get_types($1) == "package" ? 7 : 8 :));

        all = sort_array(all, (: sort_object($1[0], $2[0]) :));

        write(HIY "英雄商店目前出售以下货物：\n" NOR);
        write(sprintf(HIW "%-16s%-16s%-10s%-10s%s\n" NOR,
                      "名称", "代号", "价格($NT)", "种类", "简要说明"));
        write(HIG "-------------------------------------------------------------------------------\n\n" NOR);

        for (i = 0; i < sizeof(all); i ++)
        {
                strtmp = "";
                items = ({});

                for(j = 0; j < sizeof(all[i]); j ++)
                {
                        strtmp = goods[all[i][j]];
                        items = explode(strtmp, ":");
                        if (sizeof(items) != 5)
                        {
                                write("strtmp made items != 5 is : " + strtmp + "\n");
                                return;
                        }
                        write(sprintf(HIW "%-16s%-16s" HIY "%-10s" HIW "%-26s%-50s\n" NOR,
                                      items[0], all[i][j], items[1], chinese_types(items[3]), items[4]));
                }
        }

        write(HIG "\n请使用 " + HIR + "member look 物品代号 " + HIG + "来查看物品！\n" NOR);
        write(HIG "请使用 " + HIR + "member buy 物品代号 " + HIG + "来购买物品！\n" NOR);
        write(HIG "凡是种类带有" HIR "※" HIG "标记的服务均为大礼包。\n" NOR);
        write(HIG "凡是种类带有" HIY "★" HIG "标记的服务均为购买会员期限。\n" NOR);
        write(HIG "请认真阅读有关说明，购买前请考虑清楚， 如无差错，恕不退货！\n" NOR);
        write(HIG "-------------------------------------------------------------------------------\n\n" NOR);
}

/**************************购买物品********************
 1、检查是否为有效会员
 2、查询物品代号是否存在
 3、查询$NT是否足够
 4、购买成功
 5、写入购买记录文件
******************************************************/
public int buy_goods(object ob, string which)
{
        array all, items;
        mixed specials;
        string strtmp;
        int i, vip, value, money;
        object buy_ob;

        if (! MEMBER_D->is_member(ob))
        {
                write("对不起，只有会员才能享受此服务！请参见 " HIR "help member " NOR " ！\n");
                return 0;
        }

        /*
        if (! MEMBER_D->is_valib_member(ob))
        {
                write("您的会员有效期已过， 请及时充值！\n");
                return 0;
        }
        */

        all = keys(goods);
        if (member_array(which, all) == -1)
        {
                write("对不起，没有您要购买的物品 " + HIR + which + NOR + "， 请使用"
                      " member show goods 查询。\n" NOR);
                return 0;

        }

        strtmp = goods[which];
        items = explode(strtmp, ":");
        sscanf(items[1], "%d", value);

        if (items[2] == "manual")
        {
                write("对不起，该服务必须由 admin 手动实现，请及时与 admin 联系！\n");
                return 0;
        }

        vip   = MEMBER_D->db_query_member(ob, "vip");
        money = MEMBER_D->db_query_member(ob, "money");

        // 会员折扣
        if (vip == 3)
                value = value * 80 / 100;
        else
        if (vip == 2)
                value = value * 85 / 100;
        else
        if (vip == 1)
                value = value * 90 / 100;

        if (value < 1) value = 1;

        if (money < value)
        {
                write("对不起，您的泥潭金币数量不够！\n");
                return 0;
        }

        switch(items[3])
        {
        case "package":

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("购买物品失败，请与本站ADMIN联系！\n");
                        destruct(buy_ob);
                        return 0;
                }

                switch( which )
                {
                case "newbie" :
                        buy_ob = new("/clone/gift/xuanhuang");
                        buy_ob->set_amount(10);
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/jiuzhuan");
                        buy_ob->set_amount(10);
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/tianxiang");
                        buy_ob->set_amount(20);
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/puti-zi");
                        buy_ob->set_amount(50);
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/xiandan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/xiandan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/xisuidan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/xisuidan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/shenliwan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/shenliwan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/unknowdan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/gift/unknowdan");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/medicine/yuqing");
                        buy_ob->set_amount(600);
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/max/zhenyu");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/max/longjia");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/max/xuanhuang");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/int3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/int3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/str3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/str3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/con3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/con3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/dex3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/fam/gift/dex3");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/tianjing");
                        buy_ob->move(ob, 1);
                        ob->add("balance", "1000000000");
                        MEMBER_D->db_fee_member(ob, 31);
                        break;

                case "10LVa" :
                        buy_ob = new("/clone/item/ouyezi-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/bored-water");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/noname");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/enchaseB-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/hanjing");
                        buy_ob->move(ob, 1);
                        ob->add_skill("certosina", 200);
                        break;

                case "10LVb" :
                        buy_ob = new("/clone/item/ouyezi-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/bored-water");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/noname");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/enchaseB-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/leishentong");
                        buy_ob->move(ob, 1);
                        ob->add_skill("certosina", 200);
                        break;

                case "10LVc" :
                        buy_ob = new("/clone/item/ouyezi-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/bored-water");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/noname");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/enchaseB-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/mozhixin");
                        buy_ob->move(ob, 1);
                        ob->add_skill("certosina", 200);
                        break;

                case "10LVd" :
                        buy_ob = new("/clone/item/ouyezi-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/bored-water");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/noname");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/enchaseB-charm");
                        buy_ob->move(ob, 1);
                        buy_ob = new("/clone/item/huojingling");
                        buy_ob->move(ob, 1);
                        ob->add_skill("certosina", 200);
                        break;

                case "yj-rune" :
                        for (i = 0; i < 7; i++)
                        {
                                buy_ob = new("/clone/enchase/rune31");
                                buy_ob->move(ob, 1);
                                buy_ob = new("/clone/enchase/rune33");
                                buy_ob->move(ob, 1);
                        }
                        break;
                case "rune24-eq" :
                        for (i = 0; i < 7; i++)
                        {
                                buy_ob = new("/clone/enchase/rune24");
                                buy_ob->move(ob, 1);
                        }
                        break;                
                case "rune30-eq" :
                        for (i = 0; i < 10; i++)
                        {
                                buy_ob = new("/clone/enchase/rune30");
                                buy_ob->move(ob, 1);
                        }
                        break;        
                case "rune31-eq" :
                        for (i = 0; i < 10; i++)
                        {
                                buy_ob = new("/clone/enchase/rune31");
                                buy_ob->move(ob, 1);
                        }
                        break;                                
                case "rune32-eq" :
                        for (i = 0; i < 10; i++)
                        {
                                buy_ob = new("/clone/enchase/rune32");
                                buy_ob->move(ob, 1);
                        }
                        break;     
                case "rune33-eq" :
                        for (i = 0; i < 10; i++)
                        {
                                buy_ob = new("/clone/enchase/rune33");
                                buy_ob->move(ob, 1);
                        }
                        break;                             
                case "skull5-eq" :
                        for (i = 0; i < 300; i++)
                        {
                                buy_ob = new("/clone/enchase/skull5");
                                buy_ob->move(ob, 1);
                        }
                        break;        
                case "redgem6-eq" :
                        for (i = 0; i < 30; i++)
                        {
                               buy_ob = new("/clone/item/yj-weapon-redgem6"); 
                               buy_ob->move(ob, 1);
                        }
                        for (i = 0; i < 70; i++)
                        {
                               buy_ob = new("/clone/item/yj-armor-redgem6"); 
                               buy_ob->move(ob, 1);
                        }     
                        break;                   
                default :
                        break;
                }

                log_buyinfo(ob, items[0], value);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "object":

                buy_ob = new(items[2]);
                if (! objectp(buy_ob))
                {
                        write("复制物品失败，请与本站ADMIN联系！\n");
                        return 0;
                }

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("购买物品失败，请与本站ADMIN联系！\n");
                        destruct(buy_ob);
                        return 0;
                }

                buy_ob->move(ob, 1);
                log_buyinfo(ob, items[0], value);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "objamount":
                buy_ob = new(items[2]);
                if (! objectp(buy_ob))
                {
                        write("复制物品失败，请与本站ADMIN联系！\n");
                        return 0;
                }

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("购买物品失败，请与本站ADMIN联系！\n");
                        destruct(buy_ob);
                        return 0;
                }
                if (which == "putizi")
                        buy_ob->set_amount(20);
                else
                if (which == "jiuzhuan")
                        buy_ob->set_amount(10);
                else
                if (which == "yuqingsan")
                        buy_ob->set_amount(120);
                else
                if (which == "tianxiang")
                        buy_ob->set_amount(15);
                else
                if (which == "xuanhuang1")
                        buy_ob->set_amount(5);

                buy_ob->move(ob, 1);
                log_buyinfo(ob, items[0], value);
                write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "card":

                if (which != "monthcard" && which != "seasoncard" &&
                    which != "yearcard"  && which != "forevercard")
                {
                        write("没有这种类型的会员卡！\n");
                        return 0;
                }

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("购买会员卡失败，请与本站ADMIN联系！\n");
                        return 0;
                }

                if (which == "monthcard")
                        MEMBER_D->db_fee_member(ob, 31);
                else
                if (which == "seasoncard")
                        MEMBER_D->db_fee_member(ob, 92);
                else
                if (which == "yearcard")
                        MEMBER_D->db_fee_member(ob, 365);
                else
                if (which == "forevercard")
                        MEMBER_D->db_fee_member(ob, 365, 1);

                log_buyinfo(ob, items[0], value);
                write(HIG + items[0] + " ， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "story":
                // 首先检查是否中过故事
                if (ob->query("gift/" + which))
                {
                        write("您已经中过该故事了！\n");
                        return 0;
                }
                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("购买故事失败，请与本站ADMIN联系！\n");
                        return 0;
                }
                ob->add("gift/" + which, 1);
                ob->add(items[2], 1);
                log_buyinfo(ob, items[0], value);

                write(HIG + items[0] + " ， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "gold" :
                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("购买故事失败，请与本站ADMIN联系！\n");
                        return 0;
                }

                ob->add("balance", items[2]);
                log_buyinfo(ob, items[0], value);

                write(HIG + items[0] + " ， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                      "info " HIG " 查询！ \n" NOR);
                write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                return 1;

        case "special":
                // 首先检查是否有该special
                // 同时检查总共的special不能大于7
                if (! ob->query("special_skill"))specials = 0;
                else specials = keys(ob->query("special_skill"));
                if (1) // 正常出售
                {
                        if (sizeof(specials) > 0)
                        {
                                if (member_array(which, specials) != -1)
                                {
                                        write("对不起，您已经有这个特殊技能了！\n");
                                        return 0;
                                }
                                if (sizeof(specials) >= 24)
                                {
                                        write("对不起，一个帐号最多只能拥有四个特殊技能！\n");
                                        return 0;
                                }
                        }

                        if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                        {
                                write("购买故事失败，请与本站ADMIN联系！\n");
                                return 0;
                        }

                        ob->set("special_skill/" + which, 1);
                        log_buyinfo(ob, items[0], value);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                              "info " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                }
                else
                {
                        write("暂时停止出售特殊技能！请谅解！\n");
                        return 0;
                }
        
        case "special2":
                if (! ob->query("special_skill")) specials = 0;
                else specials = keys(ob->query("special_skill"));
                if (ob->query("reborn/times")) // 正常出售
                {
                        if (sizeof(specials) > 0)
                        {
                                if (member_array(which, specials) != -1)
                                {
                                        write("对不起，您已经有这个转世技能了！\n");
                                        return 0;
                                }
                                /*
                                if (sizeof(specials) >= 8)
                                {
                                        write("对不起，一个帐号最多只能购买四个转世技能！\n");
                                        return 0;
                                }
                                */
                        }

                        if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                        {
                                write("购买故事失败，请与本站ADMIN联系！\n");
                                return 0;
                        }

                        ob->set("special_skill/" + which, 1);
                        log_buyinfo(ob, items[0], value);
                        write(HIG "购买成功， 您的购买记录已写入文件，请使用 " HIR "member show buy"
                              "info " HIG " 查询！ \n" NOR);
                        write(HIC "您总共花费了 " HIY + value + HIC + " $NT, 祝您好运！\n" NOR);
                        return 1;
                }
                else
                {
                        write("你无法购买转世技能！请谅解！\n");
                        return 0;
                }
                
        default:
                write("无效物品种类！\n");
                return 0;
        }
}

public int do_look(object me, string arg)
{
        string tempstr;
        array items;
        object buy_ob;
        int value;

        if (me->is_busy())
        {
                write("你正在忙着呢！\n");
                return 1;
        }

        if (! arg || arg == "" || undefinedp(goods[arg]))
        {
                write("你想查看什么物品？\n");
                return 1;
        }

        tempstr = goods[arg];
        items = ({});
        items = explode(tempstr, ":");

        if (sizeof(items) != 5)
        {
                write("strtmp made items != 5 is : " + tempstr + "\n");
                return 1;
        }
        
        sscanf(items[1], "%d", value);

        if (items[3] != "object" && items[3] != "objamount")
        {
                write("你要查看的不是一个物品。\n");
                return 1;
        }

        catch(call_other(items[2], "???"));
        buy_ob = find_object(items[2]);
        if (! buy_ob)
        {
                write("文件出错，请与巫师联系！\n");
                return 1;
        }

        LOOK_CMD->look_item(me, buy_ob);
        write(HIY "价格：" + value + " $NT\n\n" NOR);

        return 1;
}
