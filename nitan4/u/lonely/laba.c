// �������
#include <ansi.h>
inherit ITEM;
 
void create()
{
        set_name(HIM"�������" NOR, ({ "wucai laba","laba","wucai"}));
        set("long", 
                  "һ��������ȣ�����˵�����Դ���ɫŶ��\n"
                  "�÷���\n"
                  "cui ���� ��Ĵ��� ����������say reply shout chat �� \n"
                  "���� cui chat $HIG$ hi\n"
                  "��ɫ�б�\n"
                         "                     $NOR$ - �ָ�������ɫ\n"
 "$RED$ - "RED"��ɫ"NOR"         $HIR$ - "HIR"����ɫ\n"NOR
 "$GRN$ - "GRN"��ɫ"NOR"         $HIG$ - "HIG"����ɫ\n"NOR
 "$YEL$ - "YEL"����ɫ"NOR"       $HIY$ - "HIY"��ɫ\n"NOR
 "$BLU$ - "BLU"����ɫ"NOR"       $HIB$ - "HIB"��ɫ\n"NOR
 "$MAG$ - "MAG"ǳ��ɫ"NOR"       $HIM$ - "HIM"�ۺ�ɫ\n"NOR
 "$CYN$ - "CYN"����ɫ"NOR"       $HIC$ - "HIC"����ɫ\n"NOR
 "$WHT$ - ǳ��ɫ       $HIW$ - "HIW"��ɫ\n"NOR
                         );
        set("unit","��");
        set_weight(100);
        set("value",3000000);
        set("degree",20);
        set("flag","spec/laba");
        set("desc","����˵�����Դ���ɫ��");
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

        if (!arg) return notify_fail("��Ҫ��ʲô��\n");
        sscanf(arg,"%s %s",arg1,arg2);
        if (arg1 != "chat" && arg1 != "rumor" && arg1 !="party" && arg1 != "group" 
        &&      arg1 !="say" && arg1 !="tell" && arg1 !="reply" && arg1 !="whisper" && arg1 !="shout" &&arg1 !="nt")
                return notify_fail("������������ȴ�ʲô��\n");
        
        arg2 = trans_color(arg2, 3);

        me->force_me(arg1+" "+arg2);

        return 1;
}
