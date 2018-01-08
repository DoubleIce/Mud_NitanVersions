// This program is a part of NITAN MudLIB
// dian.c ָ�㽭ɽ

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        object ob;              // ���ֵ�����
        string msg;
        int ap, dp;

        if (userp(me) && ! me->query("can_perform/yizhi-chan/dian"))
                return notify_fail("�㻹û���ܹ�����ָ�㣬�޷�ʩչָ�㽭ɽ��\n");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("������ָ�㽭ɽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(weapon = me->query_temp("weapon")))
                        return notify_fail("�㲻��ʹ��������\n");


        if( (int)me->query_skill("yizhi-chan", 1) < 150 )
                return notify_fail("���һָ��̫���裬����ʹ�á�ָ�㽭ɽ����\n");

        if ( me->query("neili") < 500)
                return notify_fail("������������������޷�ʹ�á�ָ�㽭ɽ����\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -100);

        msg = HIY " $N��������һ�����������ָ��ʹ�����ŷ�ħ���Ͼ���ָ������������$n���˹�ȥ��\n";

        ob = target->query_temp("weapon");
        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                if (! objectp(ob))
                {
                        int damage = 0;

                        if (target->query_skill("dodge") > 200 && random(2) == 0)
                        {
                                switch (random(2))
                                {
                                case 0:
                                        msg += HIR " $n�������˼����ϳ���������û�ܶ����"
                                                "$N����һָ������$n�ĵ����ϣ�\n$nֻ����һ��"
                                                "�������Ե�����ϣ���������˵���������ܡ�\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR " $n����Ʈ�������鶯֮����������Ҫ�Ȳʣ�"
                                                "�����ۡ���һ��������ܸ$n��ɫɷ�ף�ҡҡ��׹��\n";
                                        damage = 5;
                                        break;
                                }
                        } else
                        if (target->query_skill("force") > 200 && random(2) == 0)
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR " $n���һ�����Գ�������ǿ�����ֳ��У���࣡�"
                                                "��һ����ָ�ཻ��$n����΢�Σ������ֽ��\n";
                                        damage = 3;
                                        break;
                                case 1:
                                        msg += HIR " $nһ����Х��˫�ֻû���������Ӱ����ס��ǰ��"
                                                "ֻ�����͡���һ������Ӱ������$n�Ѿ������ɫ�Ұס�\n";
                                        damage = 4;
                                        break;
                                }
                        } else
                        {
                                switch(random(2))
                                {
                                case 0:
                                        msg += HIR " $n�������У���Ȼ��֪��ܣ����͡���һ����$N"
                                                "��һָ������$n��̴�д�Ѩ��\n";
                                        damage = 0;
                                        break;
                                case 1:
                                        msg += HIR " $nһת��Ѿ�����˾�ʮ���ֻ���İ취��"
                                                "��δ���ü�ʩչ��ֻ�����͡���һ�����ѱ�$N����̴"
                                                "�д�Ѩ��\n";
                                        damage = 0;
                                        break;
                                }
                        }
                        message_vision(msg + NOR, me, target);
                        if (damage > 0)
                        {
                                target->receive_damage("qi", target->query("max_qi") * damage / 12, me);
                                COMBAT_D->report_status(target);
                        }
                        else
                                target->unconcious();

                        me->start_busy(2);
                        return 1;
                }
                if (ob->is_item_make())
                {
                        ob->move(environment(target));
                        ob->set("consistence", 0);
                        msg += HIR " $næ��" + ob->query("name") + "�мܣ�ֻ���û��ھ��𣬱������ֶ�������\n" NOR;
                } else
                {
                        msg += HIW " $n��æ�мܣ�ֻ������ž����һ����$n���е�" + ob->name()
                                + "�����ѣ�ɢ��һ�أ�\n";
                        ob->unequip();
                        ob->move(environment(target));
                        ob->set("name", "�ϵ���" + ob->query("name"));
                        ob->set("value", 0);
                        ob->set("weapon_prop", 0);
                }
                me->start_busy(2);
                if (! target->is_busy()) target->start_busy(4 + random(2));
        } else
        {
                int busy = 0;
                if (target->query_skill("dodge") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += " $nһ����Ц�������仯�˼����������˶�Ŀ��һʱ��$N�޷�������\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += " $nͻȻ���Ʈȥ���������磬��$N��һָ���еĺ�̱仯�޴�ʩչ��\n";
                                busy = 1;
                                break;
                        }
                } else
                if (target->query_skill("force") > 200 && random(2) == 0)
                {
                        switch (random(2))
                        {
                        case 0:
                                msg += " $n��ɫ���أ��������ƣ���׾��׾����Ȼ��$N�޴����֣�ֻ����ָ��\n";
                                busy = 3;
                                break;
                        case 1:
                                msg += " $n������м����Цһ����˫�����������ޱȣ���$Nֻ�ܻ����Ծȡ�\n";
                                busy = 1;
                                break;
                        }
                } else
                {
                        switch (random(3))
                        {
                        case 0:
                                msg += " $n��ҡ�һΣ�����ȥ�����·���ƫƫ�����$N��һ����\n";
                                busy = 2;
                                break;
                        case 1:
                                msg += " $nһָ���������ȥ����Ҳ�Ƿ��ž���ָ����$Nһ�������ƶٻ���\n";
                                busy = 2;
                                break;
                        case 2:
                                if (objectp(ob))
                                msg += "$n��ס����������ע" + ob->query("name")
                                         + "��������ס��$N�Ľ�����\n";
                                else
                                msg += "$n��ס����������ע˫�ƣ�������ס��$N�Ľ�����\n";
                                busy = 2;
                                break;
                        }
                }
                if (! target->is_busy())
                target->start_busy(busy);
                me->start_busy(3);
        }
        message_combatd(msg + NOR, me, target);

        return 1;
}
