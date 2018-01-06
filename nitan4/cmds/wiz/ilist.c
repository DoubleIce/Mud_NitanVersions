// ilist.c

inherit F_CLEAN_UP;

protected string format_inherit_list(object , array , array ,
        string , int );

int main(object me, string arg)
{
        object ob;
        array list;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if( !arg ) return notify_fail("ָ���ʽ��ilist <�������>\n");

        ob = present(arg, me);
        if( !ob ) ob = present(arg, environment(me));
        if( !ob ) ob = find_object(resolve_path(me->query("cwd"), arg));
        if( !ob ) return notify_fail("û������������������û�б����롡\n");

        list = inherit_list(ob);
        printf("%O��\n%s", ob,
                format_inherit_list(ob, inherit_list(ob), deep_inherit_list(ob), "  ", 1));

        return 1;
}

protected string format_inherit_list(object ob, array list, array deeplist,
        string indent, int recursive)
{
        string msg;
        object deep_ob;

        msg = "";
        for(int i=sizeof(list)-1; i>=0; i--) {
                msg += indent + (member_array(list[i], deeplist)==-1? "��": (i==0 ? "�� " : "�� "))  + list[i];
                switch(inherits(list[i], ob)) {
                        case 0: msg += " (���°��У��������δ�̳�)"; break;
                        case 1: break;
                        case 2: msg += " (�ɰ�)"; break;
                }
                if( deep_ob = find_object(list[i]) ) {
                        array l;
                        msg += "\n";
                        if( recursive && sizeof(l = inherit_list(deep_ob)) )
                                msg += format_inherit_list(ob, l, deeplist, indent + (i==0 ? "  " : "��")+ "  ", 1);
                }
                else msg += " (δ���룬���ܼ̳��������)\n";
        }
        return msg;
}

int help ()
{
        write(@HELP
ָ���ʽ: ilist <�������>
 
�г�һ��������̳е����������
 
HELP
);
        return 1;
}
