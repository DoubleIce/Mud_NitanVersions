// haha
// f.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object obj;
        string objname, ownerid;
        string ultimate;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg) return notify_fail("指令格式: setultimate obj to LV10|LV69|LV87|LV105|LV121\n"); 

        if (sscanf(arg, "%s to %s", objname, ultimate) != 2)
                return notify_fail("指令格式: setultimate obj to LV10|LV69|LV87|LV105|LV121\n");
        
        obj = present(objname, environment(me)); 
        if (! obj) obj = present(objname, me); 
        if (! obj) return notify_fail("找不到指定的物件。\n"); 

        ownerid = obj->item_owner();
        
        if (ultimate == "LV10")
        {
                obj->set("combat/MKS", 2100);
                obj->set("owner/" + ownerid, 21000000);
                obj->set("magic/imbue_ok", 1);
                obj->set("magic/blood", 21000);
                obj->save();
        
                tell_object(me, "设置 " + obj->short() + " 等级为 LV10 成功。\n");
                return 1;
        } else 
        if (ultimate == "LV69")
        {
                obj->set("ultimate/37", 1);
                obj->set("ultimate/39", 1);
                obj->set("enchase/flute", 7);
                obj->set("enchase/SN", 69);
                ENCHASE_D->identify_ultimate_ob(obj, 1);             
                obj->save(); 

                tell_object(me, "设置 " + obj->short() + " 等级为 LV69 成功。\n");                  
                return 1;
        } else 
        if (ultimate == "LV87") 
        {
                obj->set("ultimate/37", 1);
                obj->set("ultimate/39", 1);
                
                if (obj->query("skill_type") 
                ||  (obj->query("armor_type") && obj->query("armor_type") == "hands"))
                {
                        obj->set("combat/MKS", 2100);
                        obj->set("owner/" + ownerid, 21000000);
                        obj->set("magic/imbue_ok", 1);
                        obj->set("magic/blood", 21000);   
                        obj->set("enchase/flute", 9);
                }                                            
                else
                        obj->set("enchase/flute", 7);
                
                obj->set("enchase/SN", 87);
                ENCHASE_D->identify_ultimate_ob(obj, 1);
                obj->save();
                
                tell_object(me, "设置 " + obj->short() + " 等级为 LV87 成功。\n");
                return 1;  
        } else 
        if (ultimate == "LV105")   
        {
                obj->set("combat/MKS", 2100);
                obj->set("owner/" + ownerid, 21000000);
                obj->set("magic/imbue_ok", 1);
                obj->set("magic/blood", 21000);   
                obj->set("ultimate/37", 1);
                obj->set("ultimate/39", 1);
                obj->set("enchase/flute", 9);
                obj->set("enchase/SN", 105);
                ENCHASE_D->identify_ultimate_ob(obj, 1);
                obj->save();    
                
                tell_object(me, "设置 " + obj->short() + " 等级为 LV105 成功。\n");
                return 1;                
        } else
        if (ultimate == "LV121") 
        {
                obj->set("combat/MKS", 2100);
                obj->set("owner/" + ownerid, 21000000);
                obj->set("magic/imbue_ok", 1);
                obj->set("magic/blood", 21000);   
                obj->set("ultimate/37", 1);
                obj->set("ultimate/39", 1);
                obj->set("enchase/flute", 9);
                obj->set("enchase/SN", 121);
                ENCHASE_D->identify_ultimate_ob(obj, 1);
                obj->save();    

                tell_object(me, "设置 " + obj->short() + " 等级为 LV105 成功。\n");
                return 1;
        } else  return notify_fail("等级格式有LV10/LV69/LV87/LV105/LV121，你要设置他为哪个等级？\n");                                                                                       
}

