// unique.c

// This function returns 1 if this_object() is not the unique clone in
// the mud. Note that calling this function on master copy always return
// 0.
#include <dbase.h>
#include <ansi.h>
#include <name.h>
inherit F_OBSAVE;

nomask int violate_unique()
{
        object *ob;

        if( !clonep(this_object()) ) return 0;

        // Find all the cloned instance of this_object()
        ob = filter_array( children(base_name(this_object())), (: clonep :) );

        return sizeof(ob) > 1;
}

// This function returns the replica of this_object() if any.
object create_replica()
{
        string replica;
        object obj;

        seteuid(getuid());
        if( stringp(replica = this_object()->query("replica_ob")) )
                obj = new(replica);
        else
                obj = 0;
        destruct(this_object());
        return obj;
}

// 接受存盘数据的接口函数
int receive_dbase_data(mixed data)
{
        if (! mapp(data))
                return 0;

        if (data["enchase"])
                set("enchase", data["enchase"]);

        return 1;
}

// 进行保存数据的接口函数
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ ]);

        if (query("enchase"))
                data += ([ "enchase" : query("enchase") ]);
                
        return data;
}

int save()
{
        int res;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

        return ::save();
}

