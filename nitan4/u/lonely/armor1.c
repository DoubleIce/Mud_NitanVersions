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
        
        str =  sprintf( YEL "\n��Ʒ���� : ����<ս��>������%d�ˣ�����%d��������%s��ʧ\n" NOR,
                        this_object()->query_weight(),
                        query("enchase/flute"),
                        (this_object()->query_autoload() || query("autoload")) ? "��" : "" );

        if( query("bindowner") ) {
                msg = sprintf( "�Ѿ���ʹ����(%s)", query("bindowner") );    
        } else {    
                msg = "��δ��ʹ����";       
        }
        
        if( intp(t = query("bindable")) && t > 0 ) {
                if( t == 1 )      msg += "<װ����>";
                else if( t == 2 ) msg += "<ʰȡ�ﶨ>";
                else if( t == 3 ) msg += "<ֱ�Ӱ�>";
        }  
           
        str += sprintf( YEL "��״̬ : %s\n" NOR, msg);
        
        if( mapp(ret = query("wear_require")) && sizeof(ret) > 0 ) {
                str += "\n";
                ks = keys(ret);
                for( i=0; i<sizeof(ks); i++ ) {
                        str += sprintf( RED "װ��Ҫ�� : %s %d\n" NOR,
                                        to_chinese(ks[i]), ret[ks[i]] );
                }
        }
        return str;
}

