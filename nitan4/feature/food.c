// food.c

#include <dbase.h>
#include <name.h>

mixed func = 0;

int is_food() { return 1; }

void apply_effect(function f)
{
        if (! func)
                func = f;
        else
        if (functionp(func))
                func = ({ func, f });
        else
        if (sizeof(func) < 12)
                func += ({ f });
}

void clear_effect()
{
        func = 0;
}

mixed query_effect()
{
        return func;
}

void do_effect()
{
        int i;

        if (functionp(func))
                evaluate(func);
        if (arrayp(func))
                for (i = 0; i < sizeof(func); i++)
                        evaluate(func[i]);
}

string extra_long()
{
        string str;
        
        str =  "��Ʒ����    ��    ʳ��\n";
        str += sprintf("��    ��    ��    %d\n", this_object()->query_weight());
        str += sprintf("��    ��    ��    %d\n", query("food_supply"));
        str += sprintf("ʣ    ��    ��    %d\n", query("food_remaining"));
        str += sprintf("ʹ�÷�ʽ    ��    ����ָ�� eat %s ʳ�á�\n", query("id"));
        if (this_object()->query_autoload())
                str += "���߶�ʧ    ��    ��\n";
        else
                str += "���߶�ʧ    ��    ��\n";
        return str;
}
