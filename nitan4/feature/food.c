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
        
        str =  "物品类型    ：    食物\n";
        str += sprintf("重    量    ：    %d\n", this_object()->query_weight());
        str += sprintf("能    量    ：    %d\n", query("food_supply"));
        str += sprintf("剩    余    ：    %d\n", query("food_remaining"));
        str += sprintf("使用方式    ：    输入指令 eat %s 食用。\n", query("id"));
        if (this_object()->query_autoload())
                str += "下线丢失    ：    否\n";
        else
                str += "下线丢失    ：    是\n";
        return str;
}
