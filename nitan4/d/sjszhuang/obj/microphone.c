//Cracked by Roath
// Microphone to broadcast in sjsz
// Apache 10/98

inherit ITEM;

void create() {
    set_name("��Ͳ", ({ "huatong" }));
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "��");
        set("long", "�������Ͳ��������(announce)һЩ֪ͨ���Խ�ɽׯ���ˡ�\n");
        set("material", "steel");
        set("weight", 5000);
        set("value", 10000000);
        set("no_get", 1);
    }
    setup();
}

int init() {
    add_action("do_announce", "announce");
}

int do_announce(string arg) {
    object me = this_player();
    string msg;

    if(!wizardp(me))
        return 0;
    if(!arg)
        return notify_fail("��������ʲô��\n");

    msg = "һ���ն����������˹�������" + arg + "����\n";

    tell_room("/d/sjszhuang/square", msg);
    tell_room("/d/sjszhuang/gamble_room", msg);
    tell_room("/d/sjszhuang/kantai_s", msg);
    tell_room("/d/sjszhuang/kantai_n", msg);
    tell_room("/d/sjszhuang/kantai_e1", msg);
    tell_room("/d/sjszhuang/kantai_e2", msg);
    tell_room("/d/sjszhuang/kantai_e3", msg);
    tell_room("/d/sjszhuang/kantai_e4", msg);
    tell_room("/d/sjszhuang/kantai_e5", msg);
    tell_room("/d/sjszhuang/kantai_w1", msg);
    tell_room("/d/sjszhuang/kantai_w2", msg);
    tell_room("/d/sjszhuang/kantai_w3", msg);
    tell_room("/d/sjszhuang/kantai_w4", msg);
    tell_room("/d/sjszhuang/kantai_w5", msg);
    tell_room("/d/sjszhuang/east_xiangfang", msg);
    tell_room("/d/sjszhuang/west_xiangfang", msg);

    return 1;
}



