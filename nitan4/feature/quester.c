// quester.c ������������

int is_quester() { return 1; } 

/*
// ����ѯ��
mixed accept_ask(object who, string topic)
{
        return QUEST_D->accept_ask(this_object(), who, topic);
}
*/
// ��������
int ask_quest(object who)
{
        return QUEST_D->ask_quest(this_object(), who);
}

/*
int ask_defend(object who)
{
        return QUEST_D->ask_defend(this_object(), who);
}
*/

int ask_finish(object who)
{
        return QUEST_D->ask_finish(this_object(), who);
}
/*
// ������Ʒ
int accept_object(object who, object ob)
{
        return QUEST_D->accept_object(this_object(), who, ob);
}
*/

// ȡ������
int cancel_quest(object who)
{
        return QUEST_D->cancel_quest(this_object(), who);
}

void die() 
{
        this_object()->recover(); 
        return;
}

void unconcious() 
{
        this_object()->recover(); 
        return;
}
