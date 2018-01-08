// master.c

#include <dbase.h>
#include <login.h>

int is_master() { return 1; }
int can_learn_from() { return 1; }

int query_auto_perform() { return 2; }

int prevent_learn(object me, string skill)
{
        mapping fam;

        if (! me->is_apprentice_of(this_object()) &&
            mapp(fam = me->query("family")) &&
            fam["family_name"] == query("family/family_name") &&
            fam["generation"] > query("family/generation"))
        {
                command("say ��Ȼ���������µĵ��ӣ����ǲ����ҵĵմ���"
                        "��... ����ȥ����ʦ��ѧ�ɡ�");
                return 1;
        }

        return 0;
}

void attempt_detach(object me)
{
        if (! me->is_apprentice_of(this_object()))
        {
                command("say ��ȥ������ʦ����");
                return;
        }

        command("sigh");
        
        // һת��ֻ������ʧ����һ��
        if (! me->query("reborn/family_name") ||
            me->query("reborn/family_name") != me->query("family/family_name"))
        {
                command("say �߰��߰ɣ����߰ɣ�����ѧ�����书���£�");

                me->skill_expell_penalty();
                me->unconcious();

                message_vision("$N������ճ��$n�ı��������"
                               "��֪����˵Щʲô��\n", this_object(), me);
                me->add("detach/" + me->query("family/family_name"), 1);
        }
        command("say �߰��߰ɣ������ڿ����߰ɣ�");
        me->delete("family");
        me->delete("quest");
        me->delete("quest_count");
        me->set("title", "��ͨ����");
}


nomask void master_accept_kill(object me)
{
        object *inv;

        inv = all_inventory(environment());
        for(int i = 0; i < sizeof(inv); i++) 
        {
                if (! inv[i]->is_character()
                || inv[i] == this_object()
                || inv[i] == me
                || userp(inv[i])
                || inv[i]->query("family/family_name") != this_object()->query("family/family_name"))
                        continue;
                else 
                {
                        message_vision(sprintf("$N��$n�ź���������%s�����ǻ�Ĳ��ͷ��ˣ�����\n\n",
                                (me->is_apprentice_of(this_object()))?
                                "������ʦ����":((me->query("family/family_name") == this_object()->query("family/family_name"))?
                                "��ͬ��ʦ����Ҫɱ":"�Ҷ�����ʦ��" )),inv[i],me );
                        inv[i]->kill_ob(me);
                        me->kill_ob(inv[i]);
                }
        }
        return;
}
