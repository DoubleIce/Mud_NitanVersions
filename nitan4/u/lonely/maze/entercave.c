void init()
{
        add_action("do_enter","entercave");
}

int do_enter(string arg)
{
        int valid;
        valid = "/adm/daemons/fuben_d"->valid_enter(this_player(),"test");
        if(valid ==1)
                "/adm/daemons/fuben_d"->enter_fuben("test",this_player());
        else {
                if(valid == 0)
                        write("��ʵս���鲻�㣬����̽�տ��в��⣬����������һ�������ɡ�\n");
                if(valid == -1)
                        write("����������̫���ˣ��Ͳ�Ҫ��ȥ�۸���Щ������С�����˰ɡ�\n");
        }
        return 1;
}
