// Room:/d/welcome/regroom.c
// Updated by Lonely (08/11/2002)

#include <ansi.h>
inherit ROOM;
int do_register(string arg);

void create()
{
        set("short", "ע�᷿��");
        set("long", "\n    ����������ҽ���ע��ĵط�������ʹ������ " HIC "register " NOR "������\n"
                    "��" HIC "�����ʼ���ַ" NOR "����ע��(" HIW "register lonely-21@163.com" NOR ")��\n\n"
                    "    ���������ע����ĵ����ʼ���ַ��" HIR "�����ʼ���ַ�Ǳ�����һ��\n"
                    "Ȩ�������" NOR "������������Ķ�ʧ����£�����ͨ����ע���������ȷ\n"
                    "��������ݺ͹黹������롣\n");

        set("item_desc", ([
        "sign":
"\t     [1;33m�йص����ʼ�ע��ļ���˵��[0m
[37m����������������������������������������������������[0m
����������ϸ���ע������������ĵ����ʼ���ַ�Ƿ���ȷ��

�����Ϸ��ע��������ɻ����Զ���ɵģ����㻹û���뿪
��Ϸ��ʱ��ע���ž��Ѿ������ˡ����ע����δ����ȷ����
����ʾ���������ע�����ֻ����ȷ�����Ժ�ŻὫע��
��Ҷ��ߡ�
���յ���ʱ����������ʼ������ṩ�߾����ģ��������ת
�ŵ�ʱ��죬�����������Ӧ����[1;33m10[0m����֮���յ���Ҳ����
����� zMud���ڴ��ʼ����򣬾�Ӧ�����յ��ˡ����[1;33m1-2[0m
��СʱҲӦ���յ���
���ǵ���Ϸ��������� [1;36m48[0m ��Сʱ������ʱ��Ӧ���Ǻܳ��
�ġ���������ʱ���ڻ�δ���յ����Ƿ�������ţ�������
��һ��ת�ſ���ʼ������ṩ���ٴ����룬����������ʼ�
�����ṩ�߽�����ѯ��

��л��������Ϸ�Ĺ�ע��  (ע���ʼ�ע���ƶ��ݻ�ʵ��)
[37m����������������������������������������������������[0m
                               \t\t[1;36m" + MUD_NAME + "��ʦ��[0m\n"
        ]));


        set("no_fight", 1);
        set("no_magic", 1);
        set("no_steal", 1);
        set("no_beg", 1);   
        // set("valid_startroom", 1); 
     
        setup();
}

void init()
{
        add_action("do_register", "register");
        add_action("do_register", "zhuce");
}

int do_register(string arg)
{
        object me = this_player();
        string mail;
        string msg;
        
        if (! arg|| strsrch(arg, "@") == -1 
        || sscanf(arg, "%*s@%*s.%*s") != 3 
        || strsrch(arg, ",") != -1)
                return notify_fail("�����ʼ���ַ������ "
                                   "player@me.com ��ʽ��\n");
        else
        {
                mail = arg;
                me->set("email", mail);

                msg = me->query("name") + "��" + me->query("id") + "����\n\n";

                msg += "    ��ӭ������̶�����磬����һ���������л������鵽����MUD ��\n" +
                       "���������Ŀ��֡�\n";
                msg += "    �������һ��ϲ��������ˣ������и��࣬����Ȥ��Ҳ��ȫ���\n" +
                       "emote ���������������֣���Цŭ���ȫ���ظ����Ρ�\n";
                msg += "    �������һ��ϲ���������ˣ����������֮�佫�ﵽ����޶ȵ�\n" +
                       "ƽ�⣬����������ϵͳ���������Ƚ�˳���ĳɾ�һ����ʦ��\n";
                msg += "    ����ܲ��ɵ�����һ������Ѭ�ĵ��ˣ�����Ĺ�ְϵͳһ������\n" +
                       "���������������󽫾���������\n";
                msg += "    �������һ������������ˣ�������������Ȣ�����ӣ��򷿵���\n" +
                       "Ϊ�֣�������һ��������˵����뵭�š�\n";
                msg += "    �������MUD ��Ϸ�е���İ�������ǵ���̶�������Ƶ�����ָ��\n" +
                       "ϵͳ��������ר�ŵ����˵�ʦ�Ը�λ����ҽ���ָ����\n";
                msg += "    ͬʱ�������ϸ�᳹����ƽ���������������������ԣ�Ŭ��Ϊ��\n" +
                       "λ��Ҵ���һƬ��������Ϸ��ա�\n";
                msg += "    �������Ϸ��ɫ�����Է������ǵ���վwww.chinesemud.org����\n" +
                       "��ֱ�ӽ�����Ϸ�ڲ���help������в�ѯ������������ǵ���Ϸ����\n" +
                       "�����������������Ϸ�ڲ������԰������ԣ�����ֱ�ӵ�½���ǵ���\n" +
                       "̳bbs.chinesemud.org��\n";
                msg += "    �ٴ����ĸ�л���������ǵ���Ϸ���ڴ���̶����ʦ�ǽ�������\n" +
                       "����ر��������ǵ�֧�֡�\n";
                msg += "    лл��\n\n";

                msg += "����        ������������������                ��̶��ʦ����Ⱥ\n";

                /*
                if (! MAIL_D->queue_mail(me, "nitan@chinesemud.org",
                        me->query("email"), "��л��������̶������Ϸ", msg))
                {
                        tell_object(me, query_fail_msg());
                        tell_object(me, "����ע���ʼ�ʧ�ܣ���ע������ȷ���ʼ���ַ��\n");
                        return 1;
                }
                */
                
                me->set("registered", 1);
                /*
                tell_object(me, "\n��һ���ʼ��Ѹ������Ǽǵĵ�ַ����\n\n" +
                                "    " + HIW + me->query("email") + NOR + "\n\n����" 
                                HIG "������" NOR "�������ĵ����ʼ����䡣\n");
                */
                tell_object(me, HIR "\nף������̶�����죡:)\n\n" NOR);
                // SMTP_D->send_mail(me,mail);
                me->move("/d/register/entry");  
                
                return 1;
        }
}
