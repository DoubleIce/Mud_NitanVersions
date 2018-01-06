//test.c

#define PATH_D  "/adm/daemons/pathd.c" 

int main(object ob,string arg)
{
        mixed a;

        if (! SECURITY_D->valid_grant(ob, "(admin)"))
                return 0;
                    
        if (! arg) return notify_fail("你想得到去哪儿的路径？\n");
     
        a = PATH_D->search_for_path(ob, arg);
     
        if (! a) return notify_fail("没有这个地方，或者这个地方不可到达。\n");
     
        write("沿途经过：\n");
     
        for(int i = sizeof(a[1]) - 1; i > 1; i--)
        {
                write(a[1][i]->query("short") + " - " + file_name(a[1][i]) + "\n");
        }
        return 1;
}

