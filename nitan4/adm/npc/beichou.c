// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("����", ({ "bei chou", "bei", "chou", "xizi" }));
        set("long", @LONG
����һ������Ϸ�Ӵ�����С��ͷ�����ü���
����������һ�����ࡣ˭����֪����ǵ�����
���кųơ����ͱ���Ϸ�ӱ�������������
����֮�£���ȴҲ��������ƽ��η��֮�ˡ�
LONG);
        set("nickname", HIW "��Ϸ��" NOR);
        set("title", HIC "����̩��" NOR);
        set("gender", "����" );
        set("age", 68);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);
        set("combat_exp", 12000000);

        set("inquiry", ([
                "����"  :"Ҫ�������������ӣ������������������Ȼ�� team bunch <�����> �Ϳ����ˡ�\n",
                "���"  :"Ҫ�������������ӣ������������������Ȼ�� team bunch <�����> �Ϳ����ˡ�\n",
                "����"  :"Ҫ�������������ӣ������������������Ȼ�� team bunch <�����> �Ϳ����ˡ�\n",
        ]) );

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "���������е�˵��������㲻�����㣬��������ô��Ϸ���Ҷ�֪����\n" NOR,
        }));

        setup();
        carry_object("d/city/obj/cloth")->wear();

        if (! clonep(this_object()))
        {
                move("/d/city/kedian");
                message_vision(CYN "\n$N" CYN "Ц���������������ˣ�Ϸ�������ˡ�\n"
                               NOR, this_object());
                set("startroom", "/d/city/kedian");
        }
}
