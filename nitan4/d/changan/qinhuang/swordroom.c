inherit ROOM;
int do_xue(string arg);
void create()
{
    set("short", "剑俑");
        set("long", @LONG
这里的陶俑手里都拿着剑，摆着各种姿势，神态各异。
LONG );
    set("exits", ([
        "east" : __DIR__"shidao2",
    ]));
    setup();
}
void init()
{
    add_action("do_xue", "xue");
}


int do_xue(string arg)
{
    object me;
    me = this_player();
    if ( !arg || ( arg != "俑" ) )
        return notify_fail("什么？\n");
    if ( (int)me->query_skill("literate", 1) < 1)
        return notify_fail("你是个文盲，先学点文化(literate)吧。\n");
    if(me->query("unarmed")) return notify_fail("你已经学过拳俑了。\n");
    if(me->query("hammer")) return notify_fail("你已经学过锤俑了。\n");
    if(me->query("club")) return notify_fail("你已经学过棍俑了。\n");
    if(me->query("blade")) return notify_fail("你已经学过刀俑了。\n");
    if(me->query("whip")) return notify_fail("你已经学过鞭俑了。\n");
    if(me->query("staff")) return notify_fail("你已经学过杖俑了。\n");
    if(me->query("throwing")) return notify_fail("你已经学过箭俑了。\n");
    if(me->query("axe")) return notify_fail("你已经学过斧俑了。\n");
    me->receive_damage("jing", 1000);
    message_vision("$N开始模仿学习这些秦俑的各种动作。\n", me);
    if ( (int)me->query_skill("sword", 1) < 851)
    {
        me->improve_skill("sword", me->query_int());
        me->set("sword",1);
        return 1;
    }
    write("你对着秦俑瞧了一回儿，发现已经没有什么好学的了。\n");
    return 1;
}
