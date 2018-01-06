// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit ITEM;
// ����ַ��������ó����ֵ����ʾ������ַ������зǷ��ĸ�ʽ
#define ILLEGAL_STR     "."
// ��convertʱ����Ҫ��Ҫȥ����ɫ
#define NOCOLOR         1
#define COLORABLE       0

int legal_chinese(string str);
string converts(string arg, int max_len, int no_color);

void create()
{
        set_name(HIC "װ��������" NOR, ({ "changename card", "card" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "һ�ſ���ʹ����װ���ı�(name)���ź��������ĸ�������\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "��");
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
                write("��ʽ���ԣ�Ӧ���ǣ����� ��Ʒ �������� Ӣ������\n���磺���� id ���� sword\n");
                return 1;
        }

        if (! objectp(ob = present(what, me)))
                return notify_fail("������û�����ֶ�����\n");

        if (! ob->is_item_make())
                return notify_fail("ֻ��������Ʒ������֮�޸����ƻ�������\n");

        if (ob->item_owner() != me->query("id"))
                return notify_fail("������������˲������㡣\n");

        // ILLEGAL_STR = "." ��ʾ�Ƿ�������
        if ((sname = converts(sname, 14, COLORABLE)) == ILLEGAL_STR)
                return 1;

        if ((sid = converts(sid, 8, NOCOLOR)) == ILLEGAL_STR)
                return 1;

        if (! sname || ! sid)
        {
                write("��úø��������֣�\n");
                return 1;
        }

        if (! is_chinese(filter_color(sname)))
        {
                write("װ�������ֱ��������ġ�\n");
                return 1;
        }

        if (! is_legal_id(sid))
        {
                write("Ӣ�Ĵ��ű���ȫ����СдӢ�Ĳſ��ԣ�\n");
                return 1;
        }

        if (strlen(filter_color(sname)) < 4)
        {
                write("���������������֣�\n");
                return 1;
        }

        if (strlen(sid) < 3)
        {
                write("�������������ַ���\n");
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

        write("���֣�" CYN + sname + "    ���ţ�" CYN + sid + NOR "\n");
        catch(call_other(filename, "???"));
        ob = find_object(filename);
        if (! ob)
        {
                write(HIR "�޸ĳ������⣬��㱨����ʦ��\n" NOR);
        }
        else
        {
                ob->move(me, 1);
                write("�޸ĳɹ���SUMMON ID���䡣\n");
                destruct(this_object());
        }

        return 1;
}

// �ж��Ƿ��ǺϷ��ĺ���
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

// ת���ַ����е���ɫ��־
string converts(string arg, int max_len, int no_color)
{
        int i;

        // ȥ���ַ����еĿո����ţ����ⱻ�����������ƻ�
        arg = replace_string(arg, " ", "");
        arg = replace_string(arg, "\"", "'");

        for (i = 0; i < strlen(arg) - 1; i++)
        {
                if (arg[i] == '\\' && arg[i + 1] != 'n')
                {
                        write("�ַ�'\\'����ֻ�ܸ���n�ַ���ʾ�س���\n");
                        return ILLEGAL_STR;
                }
        }

        arg = replace_string(arg, ",", "��");
        arg = replace_string(arg, ":", "��");
        arg = replace_string(arg, "?", "��");

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
                write("�Բ�������ַ���̫���ˣ��벻Ҫ���볬��" + chinese_number(max_len) +
                      "���ַ������ַ�����\n");
                // ��ʾ�Ƿ�������
                return ILLEGAL_STR;
        }
        return arg;
}
