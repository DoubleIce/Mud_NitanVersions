// �ڵ������ƷС�����ݿ�ϵͳ

#include <ansi.h>
#include <command.h>

mapping goods = ([
        "liandan"  : "�����ر�:1:/clone/book/wudang:object:�䵱�����ر�������ɢ���ط�",
        "int3"  : "���ͨ���ɵ�:1:/clone/fam/gift/int3:object:�����������ԳԵĵ����㵤",
        "con3"  : "ϴ�������ɵ�:1:/clone/fam/gift/con3:object:����������ǳԵĵ����㵤",
        "str3"  : "�����Ԫ�ɵ�:1:/clone/fam/gift/str3:object:������������Եĵ����㵤",
        "dex3"  : "�����޼��ɵ�:1:/clone/fam/gift/dex3:object:�����������Եĵ����㵤",

        "clearint"      : "���ۺ�Ϳ��:5:/clone/item/clearint:object:�ɼ��ٳԵ����ӵ���������",

        "putizi"        : "������:1:/clone/gift/puti-zi:objamount:�������������100-129�㣬����20��",
        "jiuzhuan"      : "��ת��:1:/clone/gift/jiuzhuan:objamount:��������������ǰ4�㵤������10��",
        "tianxiang"     : "������¶:1:/clone/gift/tianxiang:objamount:�ο�help item������15��",
        "xuanhuang1"    : "�������嵤:1:/clone/gift/xuanhuang:objamount:�ο�help item������5��",
        "yuqingsan"     : "����ɢ:1:/clone/medicine/yuqing:objamount:�����������10-11�㣬����120��",
        "zhenyu"        : "����������:20:/clone/fam/max/zhenyu:object:�ο�help item,ֻ�ܳ�һ��",
        "longjia"       : "�������׵�:15:/clone/fam/max/longjia:object:�ο�help item��,ֻ�ܳ�һ��",
        "xuanhuang2"    : "�������䵤:15:/clone/fam/max/xuanhuang:object:�ο�help item,ֻ�ܳ�һ��",
        "xiaoli"        : "���嵤:1:/clone/item/xiaolidan:object:����������������",
        "zhaoshenxiang"        : "������:10:/d/reborn/obj/xiang:object:ת��ʱ�ٻ����������õ�",

        "learn"         : "�Ͻ�ѧϰѫ��:60:/clone/item/learn-emblem:object:����ÿ��ѧϰ����800",
        "derive"        : "�Ͻ�ȡѫ��:70:/clone/item/derive-emblem:object:����ÿ�μ�ȡ�����ٶ�",
        "practice"      : "�Ͻ���ϰѫ��:70:/clone/item/practice-emblem:object:����ÿ����ϰ����800",
        "research"      : "�Ͻ��о�ѫ��:80:/clone/item/research-emblem:object:����ÿ���о�����800",
        "research2"     : "��ʯ�о�ѫ��:120:/clone/item/research-emblem2:object:����ÿ���о�����1500",

        "ganjiang"      : "�ɽ�ʥ��:30:/adm/npc/obj/ganjiang-charm:object:�ɽ�װ����ѫ������Ϊ��SUMMON����",
        "moye"          : "Īаʥ��:20:/clone/item/moye-charm:object:�ɽ���Ʒ����Ϊ���߲�������",
        "bored"         : "����ʥˮ:10:/clone/item/bored-water:object:�ɽ�װ����󻯴�׸�����Ʒ",
        "bindable"      : "�����:1:/clone/item/bindable-charm:object:�ɽ���Ʒ��",
        "enchaseA"      : "��Ƕ֮��:5:/clone/item/enchaseA-charm:object:��ʹ����Ƕ��Ϸ�е�װ���ɹ���100%",
        "enchaseB"      : "��Ƕ֮��:5:/clone/item/enchaseB-charm:object:��ʹ����Ƕ����װ���ɹ���100%",
        // "extracte"              : "��ȡ֮��:30:/clone/item/extracte-charm:object",
        "ouyezi"                : "ŷұ��ʥ��:60:/clone/item/ouyezi-charm:object:�ɽ������������Ϊ׼10LV״̬",
        "tianshi"               : "��ʦ�����:3:/clone/item/tianshi-charm:object:��������Ͽ�������������ʧ",
        "changename"         : "װ��������:30:/adm/npc/obj/cname-card:object:�����޸�����װ�������Ƽ�Ӣ�Ĵ���",
        "closed"         : "�չط�:30:/clone/item/closed-charm:object:��������ı��ıչ��ٶ�",
        "expcard"         : "˫�����鿨:1:/clone/item/exp-card:object:���Ի��2��Сʱ˫������ʱ�䣬ֻ��δת�����ʹ��",

        "butian"             : "����ʯ:20:/d/item/obj/butian:object:�������������Ĳ���",
        "bingcans"             : "����˿:20:/d/item/obj/tiancs:object:�����������ߵĲ���",
        "dizangshi"             : "�ز�֮ʯ:100:/clone/item/dizangshi:object:�����������ΰ��Ĳ���",
        "noname"                : "����֮��:120:/clone/item/noname:object:Ŀǰ��õĴ���װ������",
        "washgift"              : "ϴ�츳��:50:/clone/item/washgift:object:�������·��������츳һ�Σ������ѧ�����Ƿ�����µ��츳",
        "wuji"              : "�޼�ʥˮ:50:/clone/item/wuji-water:object:�ɽ�����װ��ֱ����չΪ������������7�ױ���9��",
        "bcrystal"            : "��ɫˮ��:20:/clone/item/bcrystal:object:�ɳ�ȡ��ʯ����Ʒ�е�ħ������",
        /*
        "taixu"                 : "�Ϲ�̫��:90:/clone/item/taixu:object",
        "hupo"                  : "�ϹŻ���:80:/clone/item/hupo:object",
        "shihun"                : "�����ɻ�:70:/clone/item/shihun:object",
        "xuanyu"                : "�ŵ�����:60:/clone/item/xuanyu:object",
        */
        "tianjing"              : "����쾧:60:/clone/item/tianjing:object:�����������Ĵ������,�����ڴ������",

        "leishentong"           : "����֮ͫ����:10:/clone/item/leishentong:object:�������ռ�10LV��Ƕ����",
        "mozhixin"              : "ʥħ֮�ġ�ħ:10:/clone/item/mozhixin:object:ħ�����ռ�10LV��Ƕ����",
        "hanjing"               : "��֮��������:10:/clone/item/hanjing:object:�������ռ�10LV��Ƕ����",
        "huojingling"           : "��֮���顤��:10:/clone/item/huojingling:object:�������ռ�10LV��Ƕ����",

        "rune06"                : "������˾:10:/clone/enchase/rune06:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune07"                : "��������:10:/clone/enchase/rune07:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune08"                : "��������:10:/clone/enchase/rune08:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune09"                : "���ĚW��:10:/clone/enchase/rune09:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune10"                : "���ĕ���:10:/clone/enchase/rune10:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune11"                : "���İ�ķ:10:/clone/enchase/rune11:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune12"                : "��������:10:/clone/enchase/rune12:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune13"                : "����ɳ��:10:/clone/enchase/rune13:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune14"                : "���Ķࠖ:10:/clone/enchase/rune14:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune15"                : "���ĺ���:10:/clone/enchase/rune15:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune16"                : "���İ��W:10:/clone/enchase/rune16:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune17"                : "���ıRķ:10:/clone/enchase/rune17:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune18"                : "���Ŀ�:10:/clone/enchase/rune18:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune19"                : "���ķ���:10:/clone/enchase/rune19:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune20"                : "�����{ķ:20:/clone/enchase/rune20:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune21"                : "�����ՠ�:20:/clone/enchase/rune21:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune22"                : "���Ğ�ķ:20:/clone/enchase/rune22:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune23"                : "�������:20:/clone/enchase/rune23:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune24"                : "������˾��:20:/clone/enchase/rune24:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune25"                : "���ĹŠ�:20:/clone/enchase/rune25:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune26"                : "���ķ���˹:20:/clone/enchase/rune26:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune27"                : "���ĚWķ:20:/clone/enchase/rune27:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune28"                : "�����_:20:/clone/enchase/rune28:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune29"                : "����ɪ:20:/clone/enchase/rune29:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune30"                : "����ؐ:25:/clone/enchase/rune30:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune31"                : "���Ć�:25:/clone/enchase/rune31:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune32"                : "���Ĳ�ķ:25:/clone/enchase/rune32:object:����Ƕ��װ����,��ϸ�ο�help rune",
        "rune33"                : "�����_��:25:/clone/enchase/rune33:object:����Ƕ��װ����,��ϸ�ο�help rune",

        "agile"                 : "�������:10:/kungfu/special/accuracy:special:���켼��,����ӵ���ĸ�",
        "hatred"                : "ɱ������:10:/kungfu/special/hatred:special:���켼��,����ӵ���ĸ�",
        "mystery"               : "���ƾ���:10:/kungfu/special/mystery:special:���켼��,����ӵ���ĸ�",
        "power"                 : "������:10:/kungfu/special/power:special:���켼��,����ӵ���ĸ�",
        "self"                  : "С������ת:10:/kungfu/special/self:special:���켼��,����ӵ���ĸ�",
        "trick"                 : "����ƪ:10:/kungfu/special/trick:special:���켼��,����ӵ���ĸ�",
        "youth"                 : "������פ:10:/kungfu/special/youth:special:���켼��,����ӵ���ĸ�",
        "sophistry"             : "�����ѧ:20:/kungfu/special/sophistry:special2:ת������,����޹��ĸ�", 
        "capture"               : "��Ӱ����:20:/kungfu/special/capture:special2:ת������,����޹��ĸ�", 
        "kingkong"              : "�������:20:/kungfu/special/kingkong:special2:ת������,����޹��ĸ�", 
        "immortal"              : "��������:20:/kungfu/special/immortal:special2:ת������,����޹��ĸ�", 
        "musha"                 : "����ת��:20:/kungfu/special/musha:special2:ת������,����޹��ĸ�", 
        "recover"               : "��Ԫ��:20:/kungfu/special/recover:special2:ת������,����޹��ĸ�", 
        "astral"                : "������ͫ:20:/kungfu/special/astral:special2:ת������,����޹��ĸ�", 
        /*
        "emperor"               : "��������:200:/kungfu/special/emperor:special",
        "queen"                 : "������Ů:200:/kungfu/special/queen:special",
        "lonely"                : "��ɷ����:200:/kungfu/special/lonely:special",
        */

        "water"                 : "ʥ��ɹ�:20:int:story:���������ԵĹ���,ֻ�ɹ���һ��",
        "sun"                   : "�ճ�ɹ�:20:str:story:����������Ĺ���,ֻ�ɹ���һ��",
        "feng"                  : "����ɹ�:20:dex:story:���������Ĺ���,ֻ�ɹ���һ��",
        "lighting"              : "����ɹ�:20:con:story:��������ǵĹ���,ֻ�ɹ���һ��",

        "gold"                  : "ʮ�����ƽ�:1:1000000000:gold:��Ϸ�еĻƽ�",

        "newbie"                : "���˴����:80:newbie:package:���˴����,���ٳɳ�",
        "10LVa"                 : "10LV������:150:10LVa:package:�������ռ�10LV��",
        "10LVb"                 : "10LV������:150:10LVb:package:�������ռ�10LV��",
        "10LVc"                 : "10LV������:150:10LVc:package:ħ�����ռ�10LV��",
        "10LVd"                 : "10LV������:150:10LVd:package:�������ռ�10LV��",
        "yj-rune"               : "�о����İ�:140:yj-rune:package:����7��rune31��7��rune33",
        "rune24-eq"             : "������˾�ذ�:70:rune24-eq:package:����7��rune24",
        "rune30-eq"             : "����ؐ��:100:rune30-eq:package:����10��rune30",
        "rune31-eq"             : "���Ć̰�:100:rune31-eq:package:����10��rune31",
        "rune32-eq"             : "���Ĳ�ķ��:100:rune32-eq:package:����10��rune32",
        "rune33-eq"             : "�����_�°�:100:rune33-eq:package:����10��rune33",                                
        "skull5-eq"             : "����ͷ��:50:skull5:package:����300��û�м������Ե�����ͷ(skull5)",
        "redgem6-eq"            : "�о���ʯ��:200:redgem6-eq:package:����30����Ƕ������ʯ��70����Ƕ���߱�ʯ���о�����ȡ����ϰЧ����3%����",

        "monthcard"             : "�¶Ȼ�Ա:12:monthcard:card:��Ա�¿�,����ת��",
        "seasoncard"            : "���Ȼ�Ա:30:seasoncard:card:��Ա����,����ת��",
        "yearcard"              : "��Ȼ�Ա:100:yearcard:card:��Ա�꿨,����ת��",
        "forevercard"           : "�����Ա:280:forevercard:card:��Ա����,����ת��",
]);

private string chinese_types(string types)
{
        switch(types)
        {
        case "object"             :    return HIC "��Ʒ" NOR;
        case "objamount"          :    return HIC "��Ʒ" NOR;
        case "special"            :    return HIG "���⼼��" NOR;
        case "special2"           :    return HIW "ת������" NOR;
        case "story"              :    return HIM "����" NOR;
        case "package"            :    return HIR "��" NOR;
        case "card"               :    return HIY "��" NOR;
        case "gold"               :    return HIY "��" NOR;
        default                   :    return HIR "δ֪" NOR;
        }
}

private void log_buyinfo(object ob, string which, int value)
{
        string buyinfo;

        buyinfo = MEMBER_D->db_query_member(ob, "buyinfo");
        buyinfo += sprintf("%s(%s)��%s���� %d $NT������Ʒ %s 1��\n",
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

/***************��ʾ������Ʒ����ϸ�嵥********************************
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

        write(HIY "Ӣ���̵�Ŀǰ�������»��\n" NOR);
        write(sprintf(HIW "%-16s%-16s%-10s%-10s%s\n" NOR,
                      "����", "����", "�۸�($NT)", "����", "��Ҫ˵��"));
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

        write(HIG "\n��ʹ�� " + HIR + "member look ��Ʒ���� " + HIG + "���鿴��Ʒ��\n" NOR);
        write(HIG "��ʹ�� " + HIR + "member buy ��Ʒ���� " + HIG + "��������Ʒ��\n" NOR);
        write(HIG "�����������" HIR "��" HIG "��ǵķ����Ϊ�������\n" NOR);
        write(HIG "�����������" HIY "��" HIG "��ǵķ����Ϊ�����Ա���ޡ�\n" NOR);
        write(HIG "�������Ķ��й�˵��������ǰ�뿼������� ���޲��ˡ���˻���\n" NOR);
        write(HIG "-------------------------------------------------------------------------------\n\n" NOR);
}

/**************************������Ʒ********************
 1������Ƿ�Ϊ��Ч��Ա
 2����ѯ��Ʒ�����Ƿ����
 3����ѯ$NT�Ƿ��㹻
 4������ɹ�
 5��д�빺���¼�ļ�
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
                write("�Բ���ֻ�л�Ա�������ܴ˷�����μ� " HIR "help member " NOR " ��\n");
                return 0;
        }

        /*
        if (! MEMBER_D->is_valib_member(ob))
        {
                write("���Ļ�Ա��Ч���ѹ��� �뼰ʱ��ֵ��\n");
                return 0;
        }
        */

        all = keys(goods);
        if (member_array(which, all) == -1)
        {
                write("�Բ���û����Ҫ�������Ʒ " + HIR + which + NOR + "�� ��ʹ��"
                      " member show goods ��ѯ��\n" NOR);
                return 0;

        }

        strtmp = goods[which];
        items = explode(strtmp, ":");
        sscanf(items[1], "%d", value);

        if (items[2] == "manual")
        {
                write("�Բ��𣬸÷�������� admin �ֶ�ʵ�֣��뼰ʱ�� admin ��ϵ��\n");
                return 0;
        }

        vip   = MEMBER_D->db_query_member(ob, "vip");
        money = MEMBER_D->db_query_member(ob, "money");

        // ��Ա�ۿ�
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
                write("�Բ���������̶�������������\n");
                return 0;
        }

        switch(items[3])
        {
        case "package":

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
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
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "object":

                buy_ob = new(items[2]);
                if (! objectp(buy_ob))
                {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 0;
                }

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        destruct(buy_ob);
                        return 0;
                }

                buy_ob->move(ob, 1);
                log_buyinfo(ob, items[0], value);
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "objamount":
                buy_ob = new(items[2]);
                if (! objectp(buy_ob))
                {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 0;
                }

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("������Ʒʧ�ܣ����뱾վADMIN��ϵ��\n");
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
                write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "card":

                if (which != "monthcard" && which != "seasoncard" &&
                    which != "yearcard"  && which != "forevercard")
                {
                        write("û���������͵Ļ�Ա����\n");
                        return 0;
                }

                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("�����Ա��ʧ�ܣ����뱾վADMIN��ϵ��\n");
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
                write(HIG + items[0] + " �� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "story":
                // ���ȼ���Ƿ��й�����
                if (ob->query("gift/" + which))
                {
                        write("���Ѿ��й��ù����ˣ�\n");
                        return 0;
                }
                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("�������ʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 0;
                }
                ob->add("gift/" + which, 1);
                ob->add(items[2], 1);
                log_buyinfo(ob, items[0], value);

                write(HIG + items[0] + " �� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "gold" :
                if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                {
                        write("�������ʧ�ܣ����뱾վADMIN��ϵ��\n");
                        return 0;
                }

                ob->add("balance", items[2]);
                log_buyinfo(ob, items[0], value);

                write(HIG + items[0] + " �� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                      "info " HIG " ��ѯ�� \n" NOR);
                write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                return 1;

        case "special":
                // ���ȼ���Ƿ��и�special
                // ͬʱ����ܹ���special���ܴ���7
                if (! ob->query("special_skill"))specials = 0;
                else specials = keys(ob->query("special_skill"));
                if (1) // ��������
                {
                        if (sizeof(specials) > 0)
                        {
                                if (member_array(which, specials) != -1)
                                {
                                        write("�Բ������Ѿ���������⼼���ˣ�\n");
                                        return 0;
                                }
                                if (sizeof(specials) >= 24)
                                {
                                        write("�Բ���һ���ʺ����ֻ��ӵ���ĸ����⼼�ܣ�\n");
                                        return 0;
                                }
                        }

                        if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                        {
                                write("�������ʧ�ܣ����뱾վADMIN��ϵ��\n");
                                return 0;
                        }

                        ob->set("special_skill/" + which, 1);
                        log_buyinfo(ob, items[0], value);
                        write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                              "info " HIG " ��ѯ�� \n" NOR);
                        write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                        return 1;
                }
                else
                {
                        write("��ʱֹͣ�������⼼�ܣ����½⣡\n");
                        return 0;
                }
        
        case "special2":
                if (! ob->query("special_skill")) specials = 0;
                else specials = keys(ob->query("special_skill"));
                if (ob->query("reborn/times")) // ��������
                {
                        if (sizeof(specials) > 0)
                        {
                                if (member_array(which, specials) != -1)
                                {
                                        write("�Բ������Ѿ������ת�������ˣ�\n");
                                        return 0;
                                }
                                /*
                                if (sizeof(specials) >= 8)
                                {
                                        write("�Բ���һ���ʺ����ֻ�ܹ����ĸ�ת�����ܣ�\n");
                                        return 0;
                                }
                                */
                        }

                        if (! MEMBER_D->db_set_member(ob, "money", (money - value)))
                        {
                                write("�������ʧ�ܣ����뱾վADMIN��ϵ��\n");
                                return 0;
                        }

                        ob->set("special_skill/" + which, 1);
                        log_buyinfo(ob, items[0], value);
                        write(HIG "����ɹ��� ���Ĺ����¼��д���ļ�����ʹ�� " HIR "member show buy"
                              "info " HIG " ��ѯ�� \n" NOR);
                        write(HIC "���ܹ������� " HIY + value + HIC + " $NT, ף�����ˣ�\n" NOR);
                        return 1;
                }
                else
                {
                        write("���޷�����ת�����ܣ����½⣡\n");
                        return 0;
                }
                
        default:
                write("��Ч��Ʒ���࣡\n");
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
                write("������æ���أ�\n");
                return 1;
        }

        if (! arg || arg == "" || undefinedp(goods[arg]))
        {
                write("����鿴ʲô��Ʒ��\n");
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
                write("��Ҫ�鿴�Ĳ���һ����Ʒ��\n");
                return 1;
        }

        catch(call_other(items[2], "???"));
        buy_ob = find_object(items[2]);
        if (! buy_ob)
        {
                write("�ļ�����������ʦ��ϵ��\n");
                return 1;
        }

        LOOK_CMD->look_item(me, buy_ob);
        write(HIY "�۸�" + value + " $NT\n\n" NOR);

        return 1;
}
