// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit ITEM;
// 如果字符串被设置成这个值，表示输入的字符串具有非法的格式
#define ILLEGAL_STR     "."
// 在convert时看看要不要去掉彩色
#define NOCOLOR         1
#define COLORABLE       0

int legal_chinese(string str);
string converts(string arg, int max_len, int no_color);

void create()
{
        set_name(HIC "装备更名卡" NOR, ({ "changename card", "card" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一张可以使自造装备改变(name)代号和中文名的更名卡。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "张");
        }

        setup();
}

void init()
{
        add_action("do_name", "name");
}

int do_name(string arg)
{
        object me;
        object ob;
        string what, sname, sid, id;
        string filename, content_str;
        array content;
        int i, n;

        me = this_player();
        if (! arg || sscanf(arg, "%s %s %s", what, sname, sid) != 3)
        {
                write("格式不对！应该是：命名 物品 中文名字 英文名字\n例如：命名 id 长剑 sword\n");
                return 1;
        }

        if (! objectp(ob = present(what, me)))
                return notify_fail("你身上没有这种东西。\n");

        if (! ob->is_item_make())
                return notify_fail("只有自造物品方可用之修改名称或描述。\n");

        if (ob->item_owner() != me->query("id"))
                return notify_fail("这个东西的主人并不是你。\n");

        // ILLEGAL_STR = "." 表示非法的输入
        if ((sname = converts(sname, 14, COLORABLE)) == ILLEGAL_STR)
                return 1;

        if ((sid = converts(sid, 8, NOCOLOR)) == ILLEGAL_STR)
                return 1;

        if (! sname || ! sid)
        {
                write("你好好个定个名字！\n");
                return 1;
        }

        if (! is_chinese(filter_color(sname)))
        {
                write("装备的名字必须是中文。\n");
                return 1;
        }

        if (! is_legal_id(sid))
        {
                write("英文代号必须全部用小写英文才可以！\n");
                return 1;
        }

        if (strlen(filter_color(sname)) < 4)
        {
                write("名字至少两个汉字！\n");
                return 1;
        }

        if (strlen(sid) < 3)
        {
                write("代号至少三个字符！\n");
                return 1;
        }

        if (sname[0] == 27 &&
            sname[4] == 'm')
        {
                // Add color prefix
                sname = NOR + sname;
        }

        filename = base_name(ob) + ".c";
        sscanf(filename, "%*s-%s.c", id);
        content_str = read_file(filename);
        destruct(ob);
        rm(filename);
        content = explode(content_str, "\n");
        n = sizeof(content);
        for (i = 0; i < n; i++)
        {
                if (strsrch(content[i], "set_name") != -1)
                        content[i] = sprintf("\tset_name(\"%s\", ({ \"%s\", \"%s\" }));",
                                             sname, sid, id);
                write_file(filename, content[i] + "\n");
        }

        write("名字：" CYN + sname + "    代号：" CYN + sid + NOR "\n");
        catch(call_other(filename, "???"));
        ob = find_object(filename);
        if (! ob)
        {
                write(HIR "修改出现问题，请汇报给巫师！\n" NOR);
        }
        else
        {
                ob->move(me, 1);
                write("修改成功，SUMMON ID不变。\n");
                destruct(this_object());
        }

        return 1;
}

// 判断是否是合法的汉字
int legal_chinese(string str)
{
        int i;

        if (strlen(str) < 2) return 0;

        for (i = 0; i < strlen(str); i++)
        {
                if (str[i] < 161 || str[i] == 255) return 0;
                if ((! (i % 2)) && str[i] >= 248) return 0;
        }

        return 1;
}

// 转换字符串中的颜色标志
string converts(string arg, int max_len, int no_color)
{
        int i;

        // 去除字符串中的空格，引号，避免被别人利用做破坏
        arg = replace_string(arg, " ", "");
        arg = replace_string(arg, "\"", "'");

        for (i = 0; i < strlen(arg) - 1; i++)
        {
                if (arg[i] == '\\' && arg[i + 1] != 'n')
                {
                        write("字符'\\'后面只能跟随n字符表示回车！\n");
                        return ILLEGAL_STR;
                }
        }

        arg = replace_string(arg, ",", "，");
        arg = replace_string(arg, ":", "：");
        arg = replace_string(arg, "?", "？");

        if (no_color)
        {
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
        } else
        {
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
                if (strlen(arg) < strlen(NOR) ||
                    arg[strlen(arg) - strlen(NOR)..<1] != NOR)
                {
                        // append NOR at tail
                        arg += NOR;
                }
        }
        if (strlen(arg) > max_len + 30 ||
            strlen(filter_color(arg)) > max_len)
        {
                write("对不起，这个字符串太长了，请不要输入超过" + chinese_number(max_len) +
                      "个字符长的字符串。\n");
                // 表示非法的输入
                return ILLEGAL_STR;
        }
        return arg;
}
