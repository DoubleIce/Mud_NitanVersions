
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string target;
        int    money;
        object ob;
        
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;
        
        if (! arg || sscanf(arg, "%s %d", target, money) != 2)
                return notify_fail("指令格式：recharge <id> <amount>。\n");
        
        if (! objectp(ob = UPDATE_D->global_find_player(target)))
                return notify_fail("没有这个人！\n");
        
        UPDATE_D->global_destruct_player(ob, 1);
                
        if (MEMBER_D->is_member(target))
                MEMBER_D->db_pay_member(target, money);
        else
                MEMBER_D->db_create_member(target, money);
                
        write("ok.\n");
        return 1;
}


