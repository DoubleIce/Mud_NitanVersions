// move.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <dbase.h>
#include <command.h>

nosave int weight = 0;
nosave int encumb = 0, max_encumb = 0;
nosave int magic_move = 0;
nosave int in_temp =0;

nomask int query_encumbrance() { return encumb; }
nomask int over_encumbranced() { return encumb > max_encumb; }

nomask int query_max_encumbrance() { return max_encumb; }
nomask void set_max_encumbrance(int e) { max_encumb = e; }
nomask void add_encumbrance(int w)
{
        object env;
        encumb += w;
        if (encumb < 0)
                log_file("move.bug", sprintf("%O encumbrance underflow.\n", this_object()));
        if (encumb > max_encumb) this_object()->over_encumbrance();
        if (env = environment()) env->add_encumbrance(w);
}

void over_encumbrance()
{
        if (! interactive(this_object())) return;
        tell_object(this_object(), "��ĸ��ɹ����ˣ�\n");
}

nomask int query_weight() { return weight; }
nomask void set_weight(int w)
{
        if (! environment())
        {
                weight = w;
                return;
        }
        if (w != weight) environment()->add_encumbrance(w - weight);
        weight = w;
}


// This is the "current" weight of an object, which is used on weight
// checking in move().
nomask int weight() { return weight + encumb; }

// Magic move flag: the wizard may use it
nomask int is_magic_move() { return magic_move; }
nomask int set_magic_move() { magic_move = 1; }

varargs int move(mixed dest, int raw)
{
        object ob, env;
        object me;
        int is_char;
        mixed old_target;
        mixed *guards;
        object user;
        object *users;

        me = this_object();

        // If we are equipped, unequip first.
        if (! (is_char = me->is_character()) &&
            query("equipped") && ! me->unequip())
                return notify_fail("��û�а취ȡ������������\n");

        // Find the destination ob for moving.
        if (objectp(dest))
                ob = dest;
        else
        if (stringp(dest))
        {
                call_other(dest, "???");
                ob = find_object(dest);
                if (! ob) return notify_fail("move: destination unavailable.\n");
        } else
                return notify_fail(sprintf("move: invalid destination %O.\n", dest));

        // Added by Lonely
        if (! is_char && me->query("bind_owner") && base_name(ob) != VOID_OB &&
           (! userp(ob) || me->query("bind_owner") != ob->query("id")))
        {
                write(sprintf("%s�Ѿ��󶨣��޷��ƶ���\n",
                              me->name()));
                return 0;
        }

        // Check if the destination ob can hold this object.
        // Beforce checking it, we check if the destination is environment of
        // this_object() (or environment of its environment). If it is, then
        // this could be like get something from a bag carried by the player.
        // Since the player can carry the bag, we assume he can carry the this
        // object in the bag and encumbrance checking is unessessary.
        // ----------------------
        // ���Ŀ���Ƿ��ܹ�����ס����Ʒ
        // �ڼ��ǰ�������ȼ���Ƿ�Ŀ��OBJ�Ǹ�����Ļ��������������Ļ����Ļ�����������ǣ��Ǿͺ�����
        // ��һ��������ϱ��ŵİ���ȡ��һ����Ʒ����Ȼ��ҿ��Ա������������ô���ǿ����뵱Ȼ����Ϊ��Ҳ
        // ���Ա������OBJ���ҳ��ؼ���ǲ���Ҫ�ġ� By JackyBoy@TOMUD 2001/5/6
        env = me;
        while (env = environment(env))
                if (env == ob) break;
        if (! env && (int) ob->query_encumbrance() + weight() >
                     (int) ob->query_max_encumbrance())
        {
                // modified by Lonely
                if (raw && environment(ob) && ! me->query("bindable"))
                {
                        message_vision("����$n����$N��������"
                                       "��̫���ˣ�ֻ��������һ�ԡ�\n",
                                       ob, this_object());
                        ob = environment(ob);
                } else
                if (ob == this_player())
                {
                        return notify_fail(this_object()->name() +
                                           "�������̫���ˡ�\n");
                } else
                {
                        return notify_fail(this_object()->name() +
                                           "��" + ob->name() +
                                           "����̫���ˡ�\n");
                }
        }

        // Leave environment
        // Move the object and update encumbrance
        env = environment();
        if (env)
        {
                if (env != ob && magic_move && userp(env))
                {
                        if (env->visible(me))
                                tell_object(env, HIM "���Ȼ�������Ϻ�������һ"
                                                 "Щ��\n" NOR);

                        if (userp(me))
                        {
                                env->add_temp("person_in_you", -1);
                                if (env->query_temp("person_in_you") <= 0)
                                        env->delete_temp("person_in_you");
                        }
                }

                // The owner should remove handing
                if (! is_char && env->query_temp("handing") == me)
                        env->delete_temp("handing");
        }

        // remove the thing I am guarding
        old_target = query_temp("guardfor");

        if (objectp(old_target) && ! old_target->is_character())
        {
                if (arrayp(guards = old_target->query_temp("guarded")))
                {
                        guards -= ({ me });
                        if (! sizeof(guards))
                        {
                                old_target->delete_temp("guarded");
                        } else
                                old_target->set_temp("guarded", guards);
                }
                me->delete_temp("guardfor");
        } else
        if (stringp(old_target))
        {
                guards = env->query_temp("guarded/" + old_target);
                if (arrayp(guards))
                {
                        guards -= ({ me });
                        if (! sizeof(guards))
                        {
                                env->delete_temp("guarded/" + old_target);
                        } else
                                env->set_temp("guarded/" +old_target, guards);
                }
                me->delete_temp("guardfor");
        }

        // If we are players, try look where we are.
        if (is_char && interactive(me) &&       // are we linkdead?
            living(me) &&                       // are we still concious?
            ! raw)
        {
                // look before move, because the init may be kick me
                // to ...
                LOOK_CMD->look_room(me, ob, query("env/brief"));
        }

        // Enter environment
        if (magic_move && userp(ob))
        {
                if (ob->visible(this_object()))
                        tell_object(ob, HIM "���Ȼ�������Ϻ�������һ"
                                         "Щ��\n" NOR);

                if (userp(this_object()))
                        ob->add_temp("person_in_you", 1);
        }
        magic_move = 0;

        // Modify By JackyBoy@TOMUD      2001/5/6
        if (! wizardp(this_object()) || ! query("env/invisible"))
        {
                if (env)
                {
                        env->add_encumbrance(-weight());
                        if (userp(env) && env->query_temp("tomud"))
                                tell_object(env, REM1(this_object())); //����Ǵ���������ƶ��ߣ���Ӧ����REM1
                        else
                        if (! living(env))
                        {
                                users = filter_array(all_inventory(env),
                                                     (: (userp($1) && $1->query_temp("tomud")) :)) -
                                                     ({ this_object() });
                                if (sizeof(users) > 0)
                                foreach (user in users)
                                        tell_object(user, REM0(this_object()));

                                // tell_room(env,REM0(this_object()),this_object() );
                                // ����Ǵӷ������ƶ��ߣ���Ӧ����REM0
                        }
                        // else log_file("move.log",ctime(time())+"����֪�������ʾREM��Ϣ---"+base_name(env)+"\n");
                }
                if (ob)
                {
                        ob->add_encumbrance(weight());
                        if ((userp(ob)|| interactive(ob)) && ob->query_temp("tomud"))
                                tell_object(ob, ADD1(this_object()) );
                                // ������ƶ���������ϣ���Ӧ����ADD1
                        else
                        if (! ob->is_character())
                        {
                                users = filter_array(all_inventory(ob),
                                                     (: (userp($1) && $1->query_temp("tomud")) :)) -
                                                     ({ this_object() });
                                if (sizeof(users) > 0)
                                foreach (user in users)
                                        tell_object(user, ADD0(this_object()));
                                // tell_room(ob, ADD0(this_object()),this_object() );
                                // ������ƶ����������Ӧ����ADD0
                        }
                }
        }
        // Move & run INIT function
        move_object(ob);
              
        // modified by Lonely  
        // bindable == 2 ʰȡ��
        if (me && ! is_char && me->query("bindable") && 
            me->query("bindable") == 2 && userp(ob))
        {
                me->set("bind_owner", ob->query("id"));
                me->set("setdbase", 1);
                tell_object(ob, HIM "�����������ԼԼ�ĸ�Ӧ��" + ob->name() +
                                HIM "������Ϊһ�塣\n" NOR);
        }
                
                                               
        return 1;
}

void remove(string euid)
{
        object me;
        object ob;
        object default_ob;
        object user;
        object *users;

        if (! previous_object() ||
            base_name(previous_object()) != SIMUL_EFUN_OB)
                error("move: remove() can only be called by destruct() simul efun.\n");

        me = this_object();
#ifdef DB_SAVE
        if (userp(me) && sizeof(me->query("id")))
                DATABASE_D->db_set_player(me->query("id"), "online", 0);
#endif

        if (userp(me) && euid != ROOT_UID)
        {
                if (euid != getuid(me))
                {
                        // Failed to destruct
                        log_file("destruct", sprintf("%s attempt to destruct user object %s (%s)\n",
                                 euid, this_object()->query("id"),
                                 ctime(time())));
                        error("��(" + euid + ")���ܴݻ�������ʹ���ߡ�\n");
                }
                log_file("destruct", sprintf("%s in %O destruct on %s.\n",
                                             me->query("id"),
                                             environment(me),
                                             ctime(time())));
                error("ֻ��ROOT���ܴݻ���ҡ�\n");
        } else
        if (me->query("equipped"))
        {
                // Failed to unequip, only log but continue
                if (! me->unequip())
                        log_file("destruct", sprintf("Failed to unequip %s when destructed.\n",
                                                     file_name(me)));
        }

        if (me->is_ob_saved())
                me->save();

        // Leave environment
        if (objectp(ob = environment()))
        {
                ob->add_encumbrance(-weight());

                if (ob->is_character() && ob->query_temp("handing") == me)
                        // remove handing when destruct the object
                        ob->delete_temp("handing");

                //Add By JackyBoy@TOMUD      2001/5/27
                if (userp(ob) && ob->query_temp("tomud"))
                        tell_object(ob, REM1(me) ); //����Ǵ���������ƶ��ߣ���Ӧ����REM1
                else
                if (! living(ob) && ! ob->is_character())
                {
                        users = filter_array(all_inventory(ob),
                                            (: (userp($1) && $1->query_temp("tomud")) :)) -
                                            ({ me });
                        if (sizeof(users) > 0)
                        foreach (user in users)
                                tell_object(user, REM0(me));
                        // tell_room(ob, REM0(me), me );//����Ǵӷ������ƶ��ߣ���Ӧ����REM0
                }

                if (is_magic_move() && userp(ob))
                {
                        if (ob->visible(this_object()))
                                tell_object(ob, HIM "���Ȼ�������Ϻ�������һЩ��\n" NOR);

                        if (userp(me))
                        {
                                // One user enter another user
                                ob->add_temp("person_in_you", -1);
                                if (ob->query_temp("person_in_you") <= 0)
                                        ob->delete_temp("person_in_you");
                        }
                }
        }

        // We only care about our own weight here, since remove() is called once
        // on each destruct(), so our inventory (encumbrance) will be counted as
        // well.

        if (objectp(me->query_default_object()))
        {
                default_ob = me->query_default_object();
                default_ob->add("no_clean_up", -1);
        }

        me->end_log();
}

void move_or_destruct(object dest)
{
        if (userp(this_object()))
        {
                tell_object(this_object(), "һ��ʱ�յ�Ť�����㴫�͵���һ���ط�....\n");
                move(VOID_OB);
        } else
        if (this_object()->is_ob_saved())
                this_object()->save();
}