// shibi.c 石壁

inherit ROOM;
#include "lookwall.h"

int do_study(string arg);
void create()
{
        set("short", "石壁");
        set("long", @LONG
你的面前是块打磨光滑的大石壁(shibi)。 石壁边上点燃着八根
大火把，照耀明亮。石室中已有十多人，有的注目凝思，有的打坐练
功，有的毕目喃喃自语，更有几人在大声争辩。
LONG );
        set("item_desc",([
                "shibi"  :
"\n\t石壁上有首诗：\n\n\n"
"\t∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　侠客行　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　赵客缦胡缨，吴钩霜雪明。银鞍照白马，飒沓如流星。　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　十步杀一人，千里不留行，事了拂衣去，深藏身与名。　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　闲过信陵饮，脱剑膝前横。将炙啖朱亥，持觞劝侯嬴。　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　三杯吐然诺，五岳倒为轻。眼花耳热后，意气素霓生。　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　救赵挥金锤，邯郸先震惊，千秋二壮士，煊赫大梁城。　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷　纵死侠骨香，不惭世上英，谁能书阁下，白首太玄经。　∷∷∷\n"
"\t∷∷∷　　　　　　　　　　　　　　　　　　　　　　　　　　∷∷∷\n"
"\t∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷\n",
        ]));
        set("exits", ([
                "west" : __DIR__"neiting",
                "out"  : __DIR__"shimen",
                "east" : __DIR__"wuchang",
                "south" : __DIR__"xiaowu",
        ]));
        set("item_desc", ([
                "shibi" : (: do_look :),
        ]));
        set("objects", ([
                CLASS_D("xiakedao") + "/shi" : 1,
        ]));

        setup();
}

void init()
{
        add_action("do_look", "look");
}

