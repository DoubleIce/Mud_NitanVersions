// apprentice.c
// From ES2
// Modified by Xiang for XKX (12/15/95)
// Modified by Lonely (04/05/2009)

#include <dbase.h>

int is_apprentice_of(object ob)
{
        mapping family;
        
        if (! mapp(family = query("family"))) return 0;

        if (family["master_id"] == (string)ob->query("id") &&
            family["master_name"] == (string)ob->query("name"))
                return 1;

        if (! query("reborn/family_name") || 
            ! ob->query("family/family_name"))
                return 0;       

        if (query("reborn/family_name") == ob->query("family/family_name"))
                return 1;       

        return 0;       
}

void assign_apprentice(string title, int privs)
{
        mapping family;

        if (! mapp(family = query("family"))) return;

        family["title"] = title;
        family["privs"] = privs;

        if (userp(this_object()) || ! query("title"))
        {
                switch (family["generation"])
                {
                case 0:
                        set("title", family["family_name"] + family["title"]);
                        break;
                case 1:
                        set("title", family["family_name"] + "开山祖师");
                        break;
                default:
                        set("title", sprintf("%s第%s代%s", family["family_name"],
                                chinese_number(family["generation"]), family["title"]));
                        break;
                }
        }
}

// This is used for NPC, or start a new family for a player.
void create_family(string family_name, int generation, string title)
{
        mapping family;

        family = allocate_mapping(6);

        family["family_name"] = family_name;
        family["generation"] = generation;

        set("family", family);

        // priv = -1 for ALL privileges.
        assign_apprentice( title, -1 );
}

int recruit_apprentice(object ob)
{
        mapping my_family, family;

        if (ob->is_apprentice_of(this_object()))
                return 0;

        if (! mapp(my_family = query("family")))
                return 0;

        if (stringp(query("class")) &&
           (ob->query("class") != "bonze") &&
           (ob->query("class") != "eunach") &&
           (query("class") != "bonze") &&
           (query("class")!="eunach"))
              ob->set("class", query("class"));

        family = allocate_mapping(sizeof(my_family));
        family["master_id"]   = query("id");
        family["master_name"] = query("name");
        family["family_name"] = my_family["family_name"];
        family["generation"]  = my_family["generation"] + 1;
        family["enter_time"]  = time();

        if (family["family_name"] == "欧阳世家")
        {
                if (ob->query("can_not_change") && ! ob->query("old_surname"))
                        ob->set("old_surname", ob->query("surname"));
                ob->set("surname","欧阳");
                ob->set("born_family", "欧阳世家");
                ob->set_name();
        }

        if (family["family_name"] == "关外胡家")
        {
                if (ob->query("can_not_change") && ! ob->query("old_surname"))
                        ob->set("old_surname", ob->query("surname"));
                ob->set("surname", "胡");
                ob->set("born_family", "关外胡家");
                ob->set_name();
        }
        if (family["family_name"] == "慕容世家")
        {
                if (ob->query("can_not_change") && ! ob->query("old_surname"))
                        ob->set("old_surname", ob->query("surname"));
                ob->set("surname", "慕容");
                ob->set("born_family", "慕容世家");
                ob->set_name();
        }
        if (family["family_name"] == "段氏皇族")
        {
                if (ob->query("can_not_change") && ! ob->query("old_surname"))
                        ob->set("old_surname", ob->query("surname"));
                ob->set("surname", "段");
                ob->set("born_family", "段氏皇族");
                ob->set_name();
        }


        if (!ob->query("can_not_change"))
                ob->set("can_not_change", 1);

        if (stringp(ob->query("family/family_name")) &&
            ob->query("family/family_name") == family["family_name"])
                family["gongji"] = ob->query("family/gongji");

        if (query("inherit_title"))
        {
                ob->set("title", query("inherit_title"));
                ob->set("family", family);
                return 1;
        } else
        if (query("born_family") != "没有")
                family["title"] = "传人";
        else
                family["title"] = "弟子";

        ob->set("family", family);
        ob->assign_apprentice(family["title"], 0);
        return 1;
}

string query_bunch()
{       
        return query("bunch/bunch_name");
}

string query_family()
{
        return query("family/family_name");
}

string query_master()
{
        return query("family/master_name");
}

string query_generation()
{       
        return query("family/generation");
}
