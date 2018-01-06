// Copyright (C) 2003-2004, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit NPC;

mixed ask_gift();
mixed ask_gift1();
mixed ask_gift2();
mixed ask_gift3();
mixed ask_gift4();
mixed ask_gift5();
mixed ask_gift6();

void create()
{
        set_name(HIM "������ʹ" NOR, ({ "gift angel", "liwu tianshi" }));
        set("long", @LONG
������ʹ��������̶�����ڼ����﷢�ŵ���ʹ��
LONG);
        set("gender", "Ů��" );
        set("age", 18);
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
                "����" : (: ask_gift :),  
                "gift" : (: ask_gift :),
                // "��������" : (: ask_gift1 :),
                // "��Ա����" : (: ask_gift2 :),
                // "Ԫ������" : (: ask_gift3 :),
                "��������" : (: ask_gift4 :),
                // "������������" : (: ask_gift5 :),
                "���˸���" : (: ask_gift6 :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}

mixed ask_gift()
{
        object ob, me = this_player();
        array lines;
        string file, gift;
        int time1, time2;
        
        file = read_file(CONFIG_DIR + "gift");
        if (! stringp(file)) 
        {
                command("say ��ϧ������û�д��������������أ�");
                return 1;
        }
        
        lines = explode(file, "\n");
        file = lines[sizeof(lines) -1];
        
        if (sscanf(file, "%s %d to %d", gift, time1, time2) != 3)
        {
                command("say ��֣�������ô�����ˣ��ѵ������������֣���");
                return 1;
        }
        
        if ((int)me->query("gifter/" + time1))
        {
                command("say �Ǻǡ���������Ĳ����ˣ����Ѿ������������˰���");
                return 1;
        }
        
        if (time() < time1 || time() > time2)
        {
                command("say �Բ��������Ĳ���ʱ������������������ͷ��ҵģ�");
                return 1;
        }
        
        if (! ob = new(gift)) 
        {
                 command("say ��֣������д����⣬��Ͽ�����񱨸�ɣ�");  
                 return 1;
        } else
        {
                me->set("gifter/" + time1, 1);
                ob->move(me, 1); 
                                      
                message_vision(HIW "$N" HIW "���һָ��ͻȻ�����һ��" HIM "��" HIY "��" HIR "ϼ" HIC "��" HIW "����$n��ת˲���ţ�\n" NOR, 
                               this_object(), me);
                               
                tell_object(me, HIG "�����Ϻ������һ�����gift������쿴����ʲô����ɡ�\n" NOR);
                return 1;
        }
}

mixed ask_gift1()
{
        int td;        
        object ob;
        object me = this_player();
        
        td = time() / 86400;

        if ((int)me->query("gifter/which_day") == td)
                return "������Ѿ���������ˡ�";            

        tell_object(me, HIY "\n����ȡ��һ�����������(" HIM "��ʦ�����" NOR + HIY ")��ף�������߹����������죡\n" NOR);
        
        ob = new("/clone/goods/tianshi-charm");
        ob->move(me, 1);
        ob->set("bindable", 3);
        ob->set("bind_owner", me->query("id")); 
        ob->set("autoload", 1);
        ob->set("setdbase", 1); 
        me->set("gifter/which_day", td);
        return 1;
}

mixed ask_gift2()
{
        string id, sql;
        int    jointime, endtime, day; 
        object me = this_player();
        

        if (me->query("gifter/monfee1"))
                return "���Ѿ��������Ա�ˡ�";
        
        id = me->query("id");
        
        if (! MEMBER_D->is_member(id))
        {      
                day = time() + 2678400;                         
                sql = sprintf("INSERT INTO %s SET id = \"%s\", jointime = %d, endtime = %d", 
                              "members", id, time(), day);
                DATABASE_D->db_query(sql);
        } else
        {
                jointime = (int)MEMBER_D->db_query_member(id, "jointime");
                if (jointime < 1) jointime = time();
                
                endtime  = (int)MEMBER_D->db_query_member(id, "endtime");
                if (endtime < 1) day = time() + 2678400;
                else day = endtime + 2678400;
                        
                sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                              "members", jointime, day, id);

                DATABASE_D->db_query(sql);
        }
        
        me->set("gifter/monfee1", 1);
        
        tell_object(me, HIY "\n����ȡ��һ���µ�(" HIM "��Ա����" NOR + HIY ")��ף�������߹����������죡\n" NOR);
        
        return 1;
}

mixed ask_gift3()
{
        object me = this_player();
        

        if (me->query("gifter/20081224"))
                return "���Ѿ����Ԫ�������ˣ���Ҫ̫̰�ġ�:)";

        if (! MEMBER_D->is_valid_member(me))
        {      
                me->add("combat_exp", "5000000");
                me->add("potential", "3000000");
                me->add("experience", "8000000");
                me->add("time_reward/quest", 86400); 
        } else
        {
                me->add("combat_exp", "10000000");
                me->add("potential", "6000000");
                me->add("experience", "3000000");
                me->add("balance", "500000000");
                me->add("time_reward/quest", 172800); 
        }
                
        me->set("gifter/20081224", 1);
        
        tell_object(me, HIY "\n���ͻ��һ�������ҫ���㣬��ڤڤ�ио�����2009�꽫��������������\n" NOR);
        
        return 1;
}

mixed ask_gift4()
{
        string mapsk;
        object me = this_player();
        

        if (me->query("gifter/20090120"))
                return "���Ѿ�������������ˣ���Ҫ̫̰�ġ�:)";

        me->add("combat_exp", "50000000");
        me->add("potential", "20000000");
                	                
        if (MEMBER_D->is_valid_member(me))
        {
        	mapsk = me->query_skill_mapped("force");
                	me->improve_skill("force", 2000000);
                	me->improve_skill("force", 2000000);
                	me->improve_skill("force", 2000000);
                	me->improve_skill("force", 2000000);
        	if (stringp(mapsk))
        	{
                	me->improve_skill(mapsk, 2000000);
                	me->improve_skill(mapsk, 2000000);
                	me->improve_skill(mapsk, 2000000);
                	me->improve_skill(mapsk, 2000000);
                }

        	mapsk = me->query_skill_mapped("parry");
                	me->improve_skill("parry", 2000000);
                	me->improve_skill("parry", 2000000);
                	me->improve_skill("parry", 2000000);
                	me->improve_skill("parry", 2000000);
        	if (stringp(mapsk))
        	{
        	        me->improve_skill(mapsk, 2000000);
        	        me->improve_skill(mapsk, 2000000);
        	        me->improve_skill(mapsk, 2000000);
        	        me->improve_skill(mapsk, 2000000);
                }

        	mapsk = me->query_skill_mapped("dodge");
                	me->improve_skill("dodge", 2000000);
                	me->improve_skill("dodge", 2000000);
                	me->improve_skill("dodge", 2000000);
                	me->improve_skill("dodge", 2000000);
        	if (stringp(mapsk))
        	{
                	me->improve_skill(mapsk, 2000000);
                	me->improve_skill(mapsk, 2000000);
                	me->improve_skill(mapsk, 2000000);
                	me->improve_skill(mapsk, 2000000);
                }
        }
                
        me->set("gifter/20090120", 1);

                tell_object(me,
HIW"\n"+
"     ������������������ "HIR"���ڿ���"HIW" ������������������\n"+
"     ��  ���������� Happy  New  Year ����������  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��                                  ��  ��\n");
                if(strlen(me->query("name")) == 2) tell_object(me,
HIW"     ��  ��  �װ���"+me->query("name")+"��                      ��  ��\n");
                if(strlen(me->query("name")) == 4) tell_object(me,
HIW"     ��  ��  �װ���"+me->query("name")+"��                    ��  ��\n");
                if(strlen(me->query("name")) == 6) tell_object(me,
HIW"     ��  ��  �װ���"+me->query("name")+"��                  ��  ��\n");
                if(strlen(me->query("name")) == 8) tell_object(me,
HIW"     ��  ��  �װ���"+me->query("name")+"��                ��  ��\n");
                if(strlen(me->query("name")) == 10) tell_object(me,
HIW"     ��  ��  �װ���"+me->query("name")+"��              ��  ��\n");
        tell_object(me,
HIW"     ��  ��      Ը�������ļ������µ�һ��    ��  ��\n"+
"     ��  ��  ����������֡�ƽ����          ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��             *  *"HIR"r"HIW"*  *            ��  ��\n"+
"     ��  ��          * *"HIR"a"HIW"* "HIG"^"HIY"Y"HIG"^"HIW" *"HIR"i"HIW"* *         ��  ��\n"+
"     ��  ��         *"HIM"m"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"HIG"^\\^"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"*"RED"s"HIW"*        ��  ��\n"+
"     ��  ��         "HIG"^"HIY"Y"HIG"^"HIW"*"HIG"\\"HIW"*"RED"e"HIW"*"HIG"/"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*"HIG"^"HIY"Y"HIG"^"HIW"        ��  ��\n"+
"     ��  ��         *"HIG"\\"HIW"*"CYN"t"HIW"*"HIG"|"HIY"Y"HIG"^\\^"HIY"Y"HIG"|"HIW"*"HIG"l"HIW"*"HIG"/"HIW"*        ��  ��\n"+
"     ��  ��        *"MAG"s"HIW"*"HIG"|"HIY"Y"HIG"^\\\\^/^//^"HIY"Y"HIG"|"HIW"*"HIR"a"HIW"*       ��  ��\n"+
"     ��  ��        "GRN"^"YEL"Y"GRN"^\\\\_^\\\\\\//^_//^"YEL"Y"GRN"^"HIW"       ��  ��\n"+
"     ��  ��        "GRN"^\\_^\\_\\_\\//_/_/^_/^"HIW"       ��  ��\n"+
"     ��  ��         "GRN"^^\\_^\\_\\\\/_/^_/^^"HIW"        ��  ��\n"+
"     ��  ��           "GRN"^^\\_ \\// _/^^"HIW"          ��  ��\n"+
"     ��  ��               "GRN"\\_\\_/"HIW"              ��  ��\n"+
"     ��  ��                "GRN"/|\\"HIW"               ��  ��\n"+
"     ��  ��               "GRN"/\\\\/\\"HIW"              ��  ��\n"+
"     ��  ��                                  ��  ��\n"+
"     ��  ��                  "RED"��̶��ʦ�鹧��"HIW"  ��  ��\n"+
HIW"     ��  ��������������������������������������  ��\n"+
"     ����������������������������������������������\n"+
"\n" NOR);        
        
        return 1;
}

mixed ask_gift5()
{
        object me = this_player();

        if (me->query("gifter/20090121"))
                return "���Ѿ�����������������ˣ���Ҫ̫̰�ġ�:)";

        if (! MEMBER_D->is_valid_member(me))
                me->add("time_reward/quest", 259200); 
        else
                me->add("time_reward/quest", 518400); 

        me->set("gifter/20090121", 1);
        tell_object(me, HIY "\n����ȡ�˴����������ף��������֣�\n" NOR);

        return 1;
}

mixed ask_gift6()
{
        object me = this_player();
        if (me->query("gifter/20090701"))
                return "���Ѿ�������˸����ˣ���Ҫ̫̰�ġ�:)";

        me->add("max_neili", 100000);
        me->add("max_jingli", 100000);
        me->set("gifter/20090701", 1);
        tell_object(me, HIY "\n����ȡ�����˸�����ף�������죡\n" NOR);
        return 1;
}
