// baoshishan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "宝石山");
        set("long", @LONG
宝石山不是很高，山上多奇峰怪石。山路旁有一座亭子『来凤亭
』，亭前有块卵形大石，临空搁置在山巅，叫落星石，又称寿星石。
再往北上就到了保淑塔，往南下便回到大道了。
LONG );
        set("exits", ([
            "northup"   : "/d/hangzhou/baoshuta",
            "southdown" : "/d/hangzhou/road8",
        ]));
        set("objects", ([
            "/d/hangzhou/obj/shitou": 1,
            "/d/hangzhou/obj/eluanshi": 1,
        ]));
        set("outdoors", "hangzhou");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
