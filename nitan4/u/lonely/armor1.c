// Written by Lonely@IsMUD.net (05/21/2009)
// armor.c
#include <ansi.h>
#include <armor.h>
inherit EQUIP;

int is_armor() { return 1; }
void setup()
{
        if( !clonep(this_object()) )
                set("armor_type", TYPE_ARMOR);
        ::setup();
}

string extra_long()
{
        int i, t;
        mapping ret;
        string *ks, str, msg;
        
        str =  sprintf( YEL "\n物品属性 : 防具<战甲>，重量%d克，凹槽%d个，下线%s丢失\n" NOR,
                        this_object()->query_weight(),
                        query("enchase/flute"),
                        (this_object()->query_autoload() || query("autoload")) ? "不" : "" );

        if( query("bindowner") ) {
                msg = sprintf( "已经绑定使用者(%s)", query("bindowner") );    
        } else {    
                msg = "暂未绑定使用者";       
        }
        
        if( intp(t = query("bindable")) && t > 0 ) {
                if( t == 1 )      msg += "<装备绑定>";
                else if( t == 2 ) msg += "<拾取帮定>";
                else if( t == 3 ) msg += "<直接绑定>";
        }  
           
        str += sprintf( YEL "绑定状态 : %s\n" NOR, msg);
        
        if( mapp(ret = query("wear_require")) && sizeof(ret) > 0 ) {
                str += "\n";
                ks = keys(ret);
                for( i=0; i<sizeof(ks); i++ ) {
                        str += sprintf( RED "装备要求 : %s %d\n" NOR,
                                        to_chinese(ks[i]), ret[ks[i]] );
                }
        }
        return str;
}

