 // wander.c
inherit NPC; 
void create()
{
} 

void die()
{
        object killer, owner;
        mixed rewards;
        string key;
        int money;
        int value;
        int difficulty, difficulty2;


        if(!(rewards=query("rewards"))) {
                ::die();
                return;
        }
        if (this_object()->query_temp("last_damage_from")) {
                killer = this_object()->query_temp("last_damage_from");
                if(owner=killer->query("possessed"))
                        killer = owner;
                if(objectp(killer)) {
                        rewards = explode(rewards,",");
                        foreach(string line in rewards) {
                                if(sscanf(line,"%s:%d",key,value)!=2) {
                                        continue;
                                }else {
                                        switch(key) {
                                                case "combat_exp":
                                                        killer->add("combat_exp",value);
                                                        tell_object(killer,"ɱ��"+query("name")+"��������"+chinese_number(value)+"�㾭�顣\n");
                                                        break;
                                                case "potential":
                                                        killer->add("potential",value);
                                                        tell_object(killer,"ɱ��"+query("name")+"��������"+chinese_number(value)+"��Ǳ�ܡ�\n");
                                                        break;
                                                case "gold":
                                                        money = (1+random(value))*10000;
                                                        killer->add("deposit",money);
                                                        tell_object(killer,"ɱ��"+query("name")+"��������"+chinese_number(money)+"�Ĵ�\n");
                                                        break;
                                                case "silver":
                                                        money = (1+random(value))*100;
                                                        killer->add("deposit",money);
                                                        tell_object(killer,"ɱ��"+query("name")+"��������"+chinese_number(money)+"�Ĵ�\n");
                                                        break;
                                                case "coin":
                                                        money = (1+random(value))*1;
                                                        killer->add("deposit",money);
                                                        tell_object(killer,"ɱ��"+query("name")+"��������"+chinese_number(money)+"�Ĵ�\n");
                                                        break;
                                        }
                                }
                        }
                }
        }
        ::die();
}
