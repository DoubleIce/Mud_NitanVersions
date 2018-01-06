
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
                return notify_fail("ϵͳæ�����Ժ����ԣ�\n");
          
        if (arg != "?" && ! wizardp(me))
                me->set_temp("last_member", time());
          
        // ������ǻ�Աʹ��member ?, member ??, member stats, member show goodsָ��
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
                        write("����ʧ�ܣ�\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "zhuan":
                if (sscanf(str2, "%d to %s", amount, tar_id) != 2)
                        return help(me);
                        
                me_id = me->query("id");
                
                if (me_id == tar_id)
                        return notify_fail("��׳հ������Լ�ת�ʣ�\n");       
                               
                if (amount < 1 || amount > 100000)
                        return notify_fail("ÿ��ת�ʵĵ�λ������ 1 �� 100000 ֮�䣡\n");
                        
                if (! MEMBER_D->db_transfer_member(me_id, tar_id, amount))
                {
                        write("ת��ʧ�ܣ�\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "check":
                if (wiz_level(me) < 4)
                        return help(me);
                    
                // ���Է��Ƿ�Ϊ��Ա
                if (! MEMBER_D->is_member(str2))
                        return notify_fail("Ŀ��Ϊ�ǻ�Ա���޷���ѯ��\n");
                   
                tar = UPDATE_D->global_find_player(str2);
                if (! objectp(tar))
                        return notify_fail("û�������ң�\n");
                    
                MEMBER_D->show_member_info(tar, "info");

                UPDATE_D->global_destruct_player(tar, 1);

                return 1;
     
        case "remove":
                if (wiz_level(me) < 5)
                        return help(me);
                             
                if (! MEMBER_D->db_remove_member(str2))
                {
                        write("ɾ����Աʧ�ܣ�\n");
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
        
HIY "��ֵ���ڹٷ���ҳ(" HIC "http://www.ourmud.cn/pay.php" HIY ")�����\n\n" NOR
@HELP
ָ���ʽ : member show [info | payinfo | buyinfo | goods]
           member look ��Ʒ����          �鿴��Ʒ
           member buy ��Ʒ����           ������Ʒ
           member check id               ����Ա��Ϣ
           member stats                  �г����еĻ�Ա
           member zhuan amount to id     ��̶���($NT)ת��
           member ??                     member ָ�����
           member ?                      ��̶��Աϵͳ������

info    : ��ʾ��Աϵͳ���
payinfo : ��ʾ��ʷ��ֵ������Ϣ
buyinfo : ��ʾ��ʷ������Ʒ��Ϣ
goods   : ��ʾӢ���̵���۵���Ʒ

member check id Ϊarch������ʦʹ�ò�����

��زο��ļ���help member

HELP );
        return 1;
}
