// name.c

#include <ansi.h>
#include <dbase.h>
#include <condition.h>

nosave array my_id;

varargs void set_name(string name, array id)
{
        string fullname;

        if (! stringp(name))
        {
                if (! stringp(fullname = query("surname")))
                        fullname = "";

                if (stringp(query("purename")))
                        fullname += query("purename");

                if (fullname == "")
                        fullname = "ÎÞÃûÊÏ";

                set("name", fullname);
        } else
        {
	        set("name", name);
        }

	if (pointerp(id))
        {
                set("id", id[0]);
	        my_id = id;
        }
}

void set_color(string color)
{
        string colorname;

        colorname = color + query("name");
        colorname = trans_color(colorname, 3);

        set("colorname", colorname + NOR);
}

int id(string str)
{
	array applied_id;

        if (! str) return 0;
	if (this_object()->is_character() && this_player() &&
	    ! this_player()->visible(this_object())) return 0;

	// Remove apply/id for speed
	// If apply/id exists, this object is "pretending" something, don't
	// recognize original id to prevent breaking the pretending with "id"
	// command.

	if (my_id && member_array(str, my_id) != -1)
		return 1;
	else
		return 0;
}

array parse_command_id_list()
{
	array applied_id;

	if( pointerp(applied_id = query_temp("apply/id")) 
	&&	sizeof(applied_id) )
		return applied_id;
	else
		return my_id;
}

varargs string name(int raw)
{
	string str, *mask;
	
	if (! raw && sizeof(mask = query_temp("apply/name")))
		return mask[sizeof(mask)-1];
	else
        {
		if (stringp(str = query("name")))
			return str;
		else
			return file_name(this_object());
	}
}

varargs string short(int raw)
{
        string str;
        string colorname;
        
        if (! stringp(colorname = query("colorname")))
                colorname = name(raw);
                                
        if (raw || ! stringp(str = query("short")))
                str = colorname + "(" + capitalize(query("id")) + ")";
        return str;
}

varargs string long(int raw)
{
	string str, extra, *mask;
	
	if (! raw && sizeof(mask = query_temp("apply/long")))
		str = mask[sizeof(mask)-1];
	else
        if (! stringp(str = query("long")))
		str = short(raw) + "¡£\n";

	if (stringp(extra = this_object()->extra_long()))
		str += extra;

	return str;
}
