// Room: youyi.c
// smallfish 2002/12/7 

#include <ansi.h>

inherit ROOM;

int is_chat_room() { return 1;} 
void create()
{
        set("short", "ÄàÌ¶æäÕ¾¡¤ÑïÖİ");
        set("long", @LONG
ÕâÀï¾ÍÊÇÑïÖİæäÕ¾£¬ÀïÃæÒ»ÅÅÅÅµÄ¶¼ÊÇÕûÕûÆëÆë¡¢ÃÜÃÜÂéÂéµÄĞ¡
ĞÅÏä¡£½­ºşÖĞ´óÏÀ´óÄ§ÃÇÆ½Ê±ÀïËù½»·¢µÄĞÅº¯¶¼½«·¢ËÍµ½ÕâÀï¡£ÓÉÓÚ
ÅÅÁĞÏàµ±ÓĞÖÈĞò£¬ÄãºÜÈİÒ×¾ÍÄÜÕÒµ½([1£»37mfind[2£»37£»0m)×Ô¼ºµÄĞÅÏä£¬Äã¿ÉÒÔÔÚÕâ
Àï²é¿´¡¢ÕûÀí×Ô¼ºµÄÓÊÏä¡£²¢ÇÒÒ²¿É¸øÅóÓÑĞ´ĞÅ¡£
LONG );
    set("objects", ([
    ]));

 set("no_fight",1);
        set("exits", ([
                "west" : "/d/city/yizhan",
        ]));

        set("coor/x", -5);
	set("coor/y", 15);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_find","find");
   add_action("do_nothing",({
      "practice","lian","meditate","respirate","study","du",
               "tuna","exercise","dazuo","learn","xue","perform","xun"}));
}

int do_find()
{
        object me,ob;
        string id;
        
        me = this_player();
        id = me->query("id");
        
        if(present("mailbox",me))
        {
                write("ÄãÒÑ¾­´ò¿ªÁËĞÅÏä£¬Èç¹û²»»áÓÃ£¬Çë look mailbox\n");
                return 1;
        }
        if(file_size("/data/mail/"+id[0..0]+"/"+id+".o")<0)
                write("ÄãµÄĞÅÏäÖĞÄ¿Ç°Ã»ÓĞÈÎºÎĞÅ¼ş¡£\n");
        ob = new("/clone/misc/mailbox");
        ob->move(me);
        
        write("Äã¸Ï½ô´ò¿ª×Ô¼ºµÄĞÅÏä£¬ÏÖÔÚ¿ÉÒÔÊ¹ÓÃÒÔÏÂÖ¸ÁîÀ´´¦ÀíÄãµÄÓÊ¼ş£º\n\n"
                "mail <Ä³ÈË>               ¼ÄĞÅ¸ø±ğÈË¡£\n"
                "forward <ĞÅ¼ş±àºÅ> <Ä³ÈË> ½«Ä³·âĞÅ×ª¼Ä¸ø±ğÈË¡£\n"
                "from                      ²é¿´ĞÅÏäÖĞµÄĞÅ¼ş¡£\n"
                "read <ĞÅ¼ş±àºÅ>           ÔÄ¶ÁÒ»·âĞÅ¼ş¡£\n"
                "discard <ĞÅ¼ş±àºÅ>        ¶ªÆúÒ»·âĞÅ¼ş¡£\n");
        return 1;
}

int do_nothing()
{
   write("ÕâÀï²»ÊÇÁ·¹¦µÄµØ·½¡£\n");
   return 1;
}
int valid_leave(object me, string dir)
{
        object obn;

        if( dir== "west"&&obn = present("mailbox",me))
        {
                destruct(obn);
                write("Äã°ÑĞÅÏäËøºÃ·ÅÏÂ£¬¾ÍÀë¿ªÁËÕâÀï¡£\n");
        }
        return ::valid_leave(me,dir);
}
