// $file_name.c                                                 /* COMMENT_ENTRY */
// Create by TEMPLATE_D. $time.                                 /* COMMENT_ENTRY */
// sword.c
// Written by Lonely                                            /* COMMENT_EXIT  */

#include <ansi.h>

inherit INLAID;

void create()
{
//**    set_name("$name", ({ "$id", }));                        /* NAME_ENTRY */
        set_name(RED "��ʯ" NOR, ({ "red gem", "gem" }));       /* NAME_EXIT  */

        if (clonep())
                set_default_object(__FILE__);
        else
        {
//**            set("$dbase_key", "$dbase_value\n");            /* DBASE_ENTRY */
                set("long", RED "һƬ��ɫ�ı�ʯ��\n" NOR);      /* DBASE_EXIT  */
                set("unit", "��");
                set("wear_msg", HIC "$N" HIC "����ذ�$n" HIC "����ͷ�ϡ�\n" NOR);
                set("remove_msg", HIC "$N" HIC "����ذ�$n" HIC "��ͷ��ժ��������\n" NOR);
        }

        set_weight(20);   
        setup();        
}

