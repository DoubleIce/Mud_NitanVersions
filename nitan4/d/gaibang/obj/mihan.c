//Cracked by Kafei
// mihan.c

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("�ܺ�", ({"mihan", "letter", "han"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "paper");
        }
}

void init()
{
	add_action("do_give", "give");
}

int do_give(string arg)
{
	string target, item;
        object obj, who, me=this_player();

        if(!arg) return notify_fail("��Ҫ��˭ʲô������\n");

        if( sscanf(arg, "%s to %s", item, target)==2
        || sscanf(arg, "%s %s", target, item)==2 );
        else return notify_fail("��Ҫ��˭ʲô������\n");

	if ( item != "mihan" ) return 0;

	if ( !objectp(obj = present(item, me)) )
		return notify_fail("������û������������\n");

	if (me->is_busy())
                return notify_fail("����æ���ء�\n");

        if (!objectp(who = present(target, environment(me))) || !living(who))
                return notify_fail("����û������ˡ�\n");

	if ( userp(who) )
		return notify_fail("�Է�����������������\n");

	if ( who->query("race") != "����" )
		return notify_fail("���Ҳ��������Ҳ�ܶ�����\n");

        if( who == me) return notify_fail("�Լ����Լ�����\n");

	message_vision("$N��$nһ���ܺ���\n", me, who);
	call_out("response", 1, me, who, obj);
	obj->move(who);

	return 1;
}

int response(object me, object who, object obj)
{
	string boss;

	switch(random(3)) {
		case 0:
			boss = "������պ�������ү";
			break;
		case 1:
			boss = "�ɹ���ľ���";
			break;
		case 2:
			boss = "����Ү�ɺ��ʥ��";
			break;
		}

	message_vision("$N����ܺ���ϸ�Ŀ���һ�顣\n", who);
	
	if ( obj->query("target_id") != who->query("id") 
	|| obj->query("target_name") != who->name() ) {
		message_vision("$Ņ��ͷ�����ɻ��˵�������Ų��Ǹ��ҵ�ѽ��\n", who);

		if ( who->query("shen") < 0 ) {
			message_vision("$N����Ц�����ٺ٣��˲�Ϊ��������������ĸ����������������ܷŹ���\n", who);
			message_vision("$N����˵�����ҵøϽ���"+boss+"����ؤ��ļƻ���\n", who);

			if ( random(me->query("kar")) > 10 ) {
				message_vision("$N�����ض�$n˵������ֻ�����ϵ�ù���������߿�ȥ�ɣ�\n", who, me);

				who->kill_ob(me);
				me->kill_ob(who);
			}
			else {
				message_vision("$N������$n˵������������ܺ��������ˣ�\n", who, me);
			}

			destruct(obj);
		}
		else {
			message_vision("$N���ܺ�����$n��֣�ص�˵����������������˴��⣡Ҫ�ö�ͽ����Ϣ��¶�ǿ�����죿\n", who, me);

			obj->move(me);
		}

		return 1;
	}
	else if ( obj->query("owner") != me->query("id") ) {
		message_vision("$Ņ��ͷ�����ɻ��˵�������Ų�Ӧ����������������������ģ�\n", who);

		if ( who->query("shen") < 0 ) {
			message_vision("$N����Ц�����ٺ٣��˲�Ϊ��������������ĸ����������������ܷŹ���\n", who);
			message_vision("$N����˵�����ҵøϽ���"+boss+"����ؤ��ļƻ���\n", who);

			if ( me->query("shen") > 0 && random(me->query("kar")) > 10 ) {
				message_vision("$N�����ض�$n˵������ֻ�����ϵ�ù���������߿�ȥ�ɣ�\n", who, me);

				who->kill_ob(me);
				me->kill_ob(who);
			}
			else if ( me->query("shen") > 0 ) {
				message_vision("$N������$n˵������������ܺ��������ˣ�\n", who, me);
			}
			else {
				message_vision("$N����$n������˵�����ɵúã����ܺ��������ˣ���Ĺ����Ҽ��ű��ǡ�\n", who, me);
			}

			destruct(obj);
		}
		else {
			message_vision("$N���ܺ�����$n��֣�ص�˵����������������˴��⣡Ҫ�ö�ͽ����Ϣ��¶�ǿ�����죿\n", who, me);
			message_vision("$N˵�����콫�ܺ�������ؤ��ɣ�\n", who);

			obj->move(me);
		}
		
		return 1;
	}
	else if ( me->query("gb/job_pending") ) {
		me->set("gb/job_status", 2);                     
	}
	
	if ( who->query("shen") < 0 ) {
		message_vision("$Ņ��ͷ����Ŀ������һ��������˵�����٣����д���������ͬ����Ϊı��\n", who);
				
		if ( random(me->query("kar")) > 10 ) {
			message_vision("$N������$n˵�����٣��׻�˵�������棬��ն��ʹ�������㵹ù��\n", who, me);
			message_vision("$N��Ц���������֪Ҫ�������"+boss+"�Ա����ҵ����⣬���Ը���������������Թ�����ң�\n", who);

			who->set_temp("kill_initiater", 1);
			who->kill_ob(me);
			me->kill_ob(who);
			obj->set("target_name", who->name());

			remove_call_out("check_fight");
			call_out("check_fight", 1, me, who, obj);
//			me->start_call_out( (: call_other, __FILE__, "check_fight", me, obj :), 1);
		}
		else {
			message_vision("$N������$n˵������������ṷƨ����������壿������ֻ�н���Ȩλ���Ǻö�����\n", who, me);
			message_vision("$N����˵����ʶʱ����Ϊ���ܣ�����³�϶���"+boss+"Ͷ�ϣ�������ɱ��������ؤ����Ϊƽ�أ�\n", who);
			destruct(obj);
		}
	}
	else {
		message_vision("$Ņ��ͷ������$n����˵��������"+RANK_D->query_respect(me)+"һ·������������ʺ���³���ϡ�\n", who, me);

		switch(random(3)) {
		case 0:
			message_vision("$N˵�������֪³����˵�������Ĵ��£��ҽ�ʱһ���ᾡ�����Ծ�������ı��֣�\n", who);
			break;
		case 1:
			message_vision("$N˵�������֪³����˵�ҽ�ʱһ����ϯ���ľ�ɽ��ᣬ��������ʢ�١�\n", who);
			break;
		case 2:
			message_vision("$N˵�������֪³����˵�ҵ�ʱ����Ҫ��������δ���ܹ���������к��ա�\n", who);
			break;
		}

		destruct(obj);
	}

	return 1;
}

int check_fight(object me, object who, object obj)
{
	object corpse;

	if ( !objectp(obj) ) return 1;

	if ( objectp(corpse = present("corpse", environment(me))) 
	&& corpse->query("victim_name") == obj->query("target_name")
	&& corpse->query("my_killer") == me->query("id") ) {
		me->set("gb/job_kill", obj->query("target_name"));
		destruct(obj);
	}
	else if ( objectp(who) && !me->is_fighting(who) ) {
		destruct(obj);
	}
	else {
		call_out("check_fight", 1, me, who, obj);
//		me->start_call_out( (: call_other, __FILE__, "check_fight", me, obj :), 1);
	}

	return 1;
}