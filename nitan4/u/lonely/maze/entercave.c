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
                        write("你实战经验不足，进洞探险恐有不测，还是先历练一下再来吧。\n");
                if(valid == -1)
                        write("大侠您经验太高了，就不要进去欺负那些可怜的小怪物了吧。\n");
        }
        return 1;
}
