// This program is a part of NITAN MudLIB
// Jitan3.c

#include <ansi.h>
inherit ROOM;

void start_worship(object who, int n);

void create()
{
	set("short", "衡山祭坛");
        set("long", @LONG
五岳之南岳衡山祭坛处，祭坛上有青铜鼎香炉一座，终年香火不灭，
若身有阎王契，点上召神香，则可召唤「衡山府君」出现。。
LONG );
	set("exits", ([
		"down" : "/d/henshan/wangyuetai",
	]));
	set("objects", ([
	        __DIR__"obj/xianglu" : 1,
	]));
	set("outdoors", "henshan");
	set("worship", 3);	
	setup();
}

void init()
{
        add_action("do_put", "put");
}

int do_put(string arg)
{
        object me, ob, obj, env;
        string what, where;
        int n;
        
        me = this_player();
        env = environment(me);
        if( !objectp(ob = present("xiang lu", env)) )
                return 0;    
                
        if( !arg || sscanf(arg, "%s in %s", what, where) != 2)
                return 0;       
                
        if( where == "xiang lu" ) {
                if( what != "magic xiang" ) {
                        tell_object(me, "青铜鼎香炉里可不能乱扔东西！\n");
                        return 1;
                }  
                             
                if( !objectp(obj = present(what, me)) &&
                    !objectp(obj = present(what, env)) ) {
                        tell_object(me, "你身上和附近没有这样东西啊。\n");
                        return 1;
                }

                if( present("henshan fujun", this_object()) ) {
                        tell_object(me, "衡山府君已经在你面前了，你就没有这个必要了吧。\n");
                        return 1;
                }
                                        
                message_vision( MAG "$N" MAG "将召神香插进铜鼎香炉里，淡淡的香味弥漫着四周。\n" NOR, me);
                obj->move(ob);
                obj->set("no_get", 1);
                obj->start_borrowing();  
                n = env->query("worship");
                if ( n ) start_worship(me, n);
                return 1;
        }
        return 0;
}

void start_worship(object who, int n)
{
        object ob;

        if( !objectp( ob = present("contract", who) ) ||
            ob->query("owner") != who->query("id") ) 
                return;
        
        ob = new("/d/reborn/npc/fujun" + n);
        ob->set("worship", who->query("id"));
        ob->move(this_object());
        ob->start_borrowing(); 
        ob->command("say 「何方来人，斗胆呼唤本君现身？」");
}
