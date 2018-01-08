// This program is a part of NT mudlib
// boss ģ��

#include <ansi.h>

inherit BOSS;

int big_blowing();

void create()
{
        set_name(HIC "�˵���" NOR, ({ "rendao fo", "rendao", "fo" }) );
        set("gender", "����");
        set("title", HIW "�˵��ػ���" NOR);
        set("age", 200);
        set("long", 
HIR"����һ��ȫ���죬�����֮��Ļ������������������ȫ��ɢ���ų��ɫ�Ļ��棡\n\n"NOR);

        set("dex",100);
        set("con",100);
        set("int",100);
        set("str",100);

        set("combat_exp", 60000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("level", 60);
        set("qi", 12000000);
        set("max_qi", 12000000);
        set("jing", 6000000);
        set("max_jing", 6000000);
        set("neili", 24000000);
        set("max_neili", 24000000);
        set("jiali", 60000);

        set_skill("unarmed", 6200);
        set_skill("sword", 6200);
        set_skill("parry", 6200);
        set_skill("dodge", 6200);
        set_skill("force", 6200);
        
        set("chat_chance", 5);
        set("chat_msg", ({
                HIB "һ�Ż�����˹������������ճɻң�\n" NOR,
                HIB "�һ�����ͻȻ�³�һ�ų������ӣ��־��˻�ȥ��\n" NOR,
        }));

        set("chat_chance_combat", 50 + random(10));
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));

        set_temp("apply/attack", 6000+random(6000));
        set_temp("apply/unarmed_damage",6000+random(6000));
        set_temp("apply/armor", 6000+random(6000));
        
        // ��Ʒ����
        set("killer_reward", killer_reward("red_dragon"));

        setup();
        carry_object("/clone/money/gold")->set_amount(200);
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

int big_blowing()
{
        message_vision(HIB "$N" HIB "�ӻ��������������һ�ڻ�����ȫ��תΪ�ʺ�Ļ�ɫ��"
                       "���������ʹ��˼�������\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;
        
        message_vision(HIB "$N" HIB "�³�һ�ɳ�ɷٽ�Ļ��森������������������ƺ�����ȼ���ţ�����\n" NOR,
                       this_object());
                       
        inv = all_inventory(environment(this_object()));        

        num = sizeof(inv);       
        if (num < 1) num = 1;
        if (num > 5) num = 5;
        
        dam = 4000 / num;
        
        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam -= inv[i]->query_temp("apply/reduce_wind");
                        if (dam <0) dam = 0;
                        
                        inv[i]->receive_wound("qi", dam, this_object());
                        inv[i]->receive_wound("jing", dam/2, this_object());
                        COMBAT_D->report_status(inv[i], 1);
                }
        }
        return 1;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIW "$N" HIW "���һ����һ�����������"
                       "���������ƻá�\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if (! is_killing(ob->query("id")))
                kill_ob(ob);
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        int damage;
        
        damage = 6000 + random(6000);
        damage -= ob->query_temp("apply/reduce_fire");
        if (damage < 0) damage = 0;
        ob->receive_wound("qi", damage, me);
        me->set("neili", me->query("max_neili"));
        return HIB "$N" HIB "���𡱵�һ���³�һ���һ𣬵�ʱ��$n"
               HIB "��������һ������\n" NOR;
}

void die()
{
        object ob;

        ob = new("/clone/gift/cdiamond");
        command("chat ѽ���벻������Ҳ����������ģ�");
        message_sort(HIR "$N" HIR "��һ����Ѫ�����ƶ�ȥ��ֻ��������һ��"
                     "���죬$N" HIR "\n������һ" + ob->query("unit") +
                     ob->name() + HIR "��\n", this_object());
        ob->move(environment());
        destruct(this_object());
}
