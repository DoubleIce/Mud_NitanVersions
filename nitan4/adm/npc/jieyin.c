
#include <ansi.h>

inherit NPC;
inherit F_NOCLONE;

void create()
{
        set_name(HIY "�ռ����ʹ��" NOR, ({ "jieyin shizhe", "jieyin", "shizhe" }));
        set("long", @LONG
����Ϧ��ר�ɵĿռ����ʹ�ߣ�ӵ��������������ܹ�Ťתʱ�գ��ߵ�Ǭ����
LONG);

        set("title", HIG "BOSS��ս�����" NOR);
        set("gender", "����" );
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
                "��սBOSS" : "����սBOSS������ ask shizhe about <BOSS�ȼ�> ���ɽ�����ս�ռ�",
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
        
        if( arg == "all" || arg == "��սBOSS" )
                return "����սBOSS������ ask shizhe about <BOSS�ȼ�> ���ɽ�����ս�ռ䡣\n";
        
        valid = FUBEN_D->valid_enter(this_player(), arg); 
        if( valid >=1 )
                FUBEN_D->enter_fuben(this_player(), arg);
        else {
                if( valid == 0 )
                        write("��ʵս���鲻�㣬����սBOSS���в��⣬����������һ�������ɡ�\n");
                else if( valid == -1 )
                        write("������̫���ˣ��Ͳ�Ҫ��ȥ�۸���Щ������С�����˰ɡ�\n");
                else if( valid == -2 )
                        write("��Ϸ��Ŀǰ��û�п��Ÿõȼ�BOSS�������˶Ժ����ԡ�\n");
                else if( valid == -3 )
                        write("��սBOSS����IP���ؽ��룬���Ѿ�����������ޡ�\n");
                else if( valid == -4 )
                        write("��BOSS����ʦ�رգ�����ʱ�޷����롣\n");
                else if( valid == -5 )
                        write("�����ϴ���ս��BOSS��ʱ��̫�̣�����Ϣ��������\n");
        }        
        return 1;
}


