// fuben_d.c
#define FUBEN_PRE_DIR 0
#define FUBEN_NAME_DIR 1
#define FUBEN_OWNER_DIR 2
#define FUBEN_ROOM_DIR 3
#define FUBEN_NPCPRE_DIR 3
#define FUBEN_NPC_DIR   4
mixed fuben_list = ([]);
mixed fuben_data = ([]);
mixed fuben_all = ([]);
mixed fuben_npc = ([]);
void load_fuben_data(string name,string data)
{
        mixed lines;
        string key,value;
        int i,sz;       
        // get map file and get data
        lines = explode(data,"\n");
        fuben_data[name] = ([]);
        sz = sizeof(lines);
        for(i=0;i<sz;i++) {
                if(!stringp(lines[i]) || lines[i]=="" || sscanf(lines[i],"%s=%s",key,value)!=2)
                        continue;
                fuben_data[name][key] = value;
        }
}

void load_fuben_npc_data(string name,string data)
{
        mixed lines,tmp,tmp2;
        string key,value,npcname,a,b;
        int i,sz,j,sz2,k,sz3;
        
        // get map file and get data
        lines = explode(data,"\n");
        fuben_npc[name] = ([]);
        sz = sizeof(lines);
        tmp = ([]);
        npcname = "";
        for(i=0;i<sz;i++) {
                if(!stringp(lines[i]) || lines[i]=="" || sscanf(lines[i],"%s=%s",key,value)!=2) 
                        continue;
                //log_file("fb_npc",sprintf("%O\n",lines[i]));
                switch(key) {
                        case "npc" :
                                // new npc....
                                sz2 = sizeof(tmp);
                                if(!sz2) {//��һ��npc������ɶ������ 
                                        npcname = value;
                                } else {
                                        //��������һ��������                                    
                                        fuben_npc[name][npcname] = copy(tmp);
                                        npcname = value;
                                        tmp = ([]);
                                }
                                break;
                        case "long":
                                tmp[key] = format_string(value);
                                break;
                        default :
                                tmp[key] = value;
                                break;
                }
        }
        //���������һ��room
        fuben_npc[name][npcname] = copy(tmp);
        //log_file("fb_npc",sprintf("%O\n",fuben_npc));
}

void load_fuben_list(string name,string data)
{
        mixed lines,tmp,tmp2;
        string key,value,roomname,a,b;
        int i,sz,j,sz2,k,sz3;
        
        // get map file and get data
        lines = explode(data,"\n");
        fuben_list[name] = ([]);
        sz = sizeof(lines);
        tmp = ([]);
        roomname = "";
        for(i=0;i<sz;i++) {
                if(!stringp(lines[i]) || lines[i]=="" || sscanf(lines[i],"%s=%s",key,value)!=2) 
                        continue;
                switch(key) {
                        case "room" :
                                // new room....
                                sz2 = sizeof(tmp);
                                if(!sz2) {//��һ��room������ɶ������ 
                                        roomname = value;
                                } else {
                                        //��������һ��������                                    
                                        fuben_list[name][roomname] = copy(tmp);
                                        roomname = value;
                                        tmp = ([]);
                                }
                                break;
                        case "exits" :
                                tmp2 = explode(value,",");                              
                                tmp[key] = ([]);
                                for(k=sizeof(tmp2)-1;k>=0;k--) {
                                        if(sscanf(tmp2[k],"%s:%s",a,b)==2) {
                                                tmp[key][a] = b;
                                        }
                                }
                                break;
                        case "npcs" :
                                tmp2 = explode(value,",");                              
                                tmp[key] = ([]);
                                for(k=sizeof(tmp2)-1;k>=0;k--) {
                                        if(sscanf(tmp2[k],"%s:%s",a,b)==2) {
                                                tmp[key][a] = b;
                                        }
                                }
                                break;
                        case "long":
                                tmp[key] = format_string(value);
                                break;
                        default :
                                tmp[key] = value;
                                break;
                }
        }
        //���������һ��room
        fuben_list[name][roomname] = copy(tmp);
}

void get_all_fuben()
{
        mixed f;
        int i;
        string a,b;
        int c;
        f = read_file("/adm/etc/fuben_list");
        f = explode(f,"\n");
        for(i=sizeof(f)-1;i>=0;i--) {
                if(sscanf(f[i],"%s,%s,%d",a,b,c))
                        fuben_all[a] = ({b,c});
        }
}

mixed get_all_fuben_name()
{
        return keys(fuben_all);
}
string query_fuben_name(string name) 
{
        return fuben_all[name][0];
}
void create()
{
        // test
        string file,name;
        mixed key;
        get_all_fuben();
        key = keys(fuben_all);
        foreach(name in key) {
                file = "/adm/etc/fuben/"+name+".map";
                load_fuben_list(name,replace_string(read_file(file),"\r",""));
                file = "/adm/etc/fuben/"+name+".data";
                load_fuben_data(name,replace_string(read_file(file),"\r",""));
                file = "/adm/etc/fuben/"+name+".npc";
                load_fuben_npc_data(name,replace_string(read_file(file),"\r",""));
        }
}

int set_default_npc_data(object npc,string fbname,string name,int basic_exp) {
        mixed npc_data;
        mixed key;
        npc_data = fuben_npc[fbname][name];
        key = keys(npc_data);
        npc->set("basic_exp",basic_exp);
        npc->set_name(fuben_npc[fbname][name]["name"],({fuben_npc[fbname][name]["id"]}));
        foreach(string key2 in key ) {
                switch(key2){
                case "name":
                case "id":
                        break;
                default :
                        npc->set(key2,npc_data[key2]);
                        break;
                }
        }
        "/adm/daemons/fuben_npc_d"->set_npc_data(npc);
        return 1;
}
mixed query_fuben_ob(string file)
{
        mixed dir;
        int i,j,k,sz;
        mixed key,key2;
        mixed exits;
        string file_dir;
        object room,npc;

        
        dir = explode(file,"/");        
        
        sz = sizeof(dir);
        if(sz <= FUBEN_ROOM_DIR) {
                return 0;
        }
        if(dir[FUBEN_ROOM_DIR] == "npc") {
//              log_file("fb4","in new virtual npc\n");
                npc = new("/obj/fuben_npc");
//              log_file("fb4",sprintf("in new virtual npc %O\n",npc));
                set_default_npc_data(npc,dir[FUBEN_NAME_DIR],dir[FUBEN_NPC_DIR],atoi(fuben_data[dir[FUBEN_NAME_DIR]]["basic_exp"]));
                
                return npc;
        }
        file_dir = "/"+dir[FUBEN_PRE_DIR]+"/"+dir[FUBEN_NAME_DIR]+"/"+dir[FUBEN_OWNER_DIR]+"/"; 
        if(!undefinedp(fuben_list[dir[FUBEN_NAME_DIR]] )
                && !undefinedp(fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]])) {
                room = new("/obj/fuben_room");
                sz = sizeof(fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]]);
                key = keys(fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]]);
                for(i=0;i<sz;i++) {
                        if(key[i]=="exits") {
                                exits = ([]);
                                key2 = keys(fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]][key[i]]);
                                for(j=0;j<sizeof(key2);j++ ) {
                                        exits[key2[j]] = file_dir + fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]][key[i]][key2[j]];
                                }                               
                                room->set((string)key[i],copy(exits));
                        } else if(key[i]=="long") {
                                room->set((string)key[i],(string)fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]][key[i]]);
                        } else if(key[i]=="npcs") {                             
                                key2 = keys(fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]][key[i]]);
                                log_file("fb2",sprintf("%O\n",key2));
                                for(j=0;j<sizeof(key2);j++ ) {
                                        for(k=0;k<atoi(fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]][key[i]][key2[j]]);k++) {
                                                log_file("fb3",file_dir + "npc/" + key2[j]);
                                                npc = new(file_dir + "npc/" + key2[j]);                         
                                                npc->move(room);
                                        }
                                }
                        } else {
                                room->set((string)key[i],(string)fuben_list[dir[FUBEN_NAME_DIR]][dir[FUBEN_ROOM_DIR]][key[i]]);
                        }
                }
                if(room->query("out_fuben")) {
                        room->set("exits/out",fuben_data[dir[FUBEN_NAME_DIR]]["out"]);
                }
                return room;
        }
        return 0;
}

int this_fuben_have_ppl(string fbname,string owner)
{
        mixed key;
        mixed *inv;
        object room;
        string file;
        int sz,i,j;
        int ret;
        ret = 0;
        key = keys(fuben_list[fbname]);
        sz = sizeof(key);
        for(i=0;i<sz;i++) {
                file = "/f/"+fbname+"/"+owner+"/"+key[i];
                if(objectp(room=find_object(file))) {
                        if(arrayp(inv =all_inventory(room))) {
                                for(j=sizeof(inv)-1;j>=0;j--) {
                                        if(interactive(inv[j]) && living(inv[j]))
                                                ret ++;
                                }
                        }
                }
        }
        return ret;
}
int clear_fuben(string fbname,string owner)
{
        mixed key,*inv; 
        object room,outroom;
        string file,out;
        int sz,i,j;
        key = keys(fuben_list[fbname]);
        sz = sizeof(key);
        out = fuben_data[fbname]["out"];
        if( !sscanf(out, "%*s.c") ) 
                out += ".c";
        
        outroom = load_object(out);
        log_file("fb_clear",sprintf("%O  %s",outroom,out));
        for(i=0;i<sz;i++) {
                file = "/f/"+fbname+"/"+owner+"/"+key[i];
                if(objectp(room=find_object(file))) {
                        if(arrayp(inv =all_inventory(room))) {
                                for(j=sizeof(inv)-1;j>=0;j--) {
                                        if(interactive(inv[j]) || base_name(inv[j])=="/obj/user") {
                                                if(outroom)
                                                        inv[j]->move(outroom);
                                                else
                                                        inv[j]->move(VOID_OB);
                                        }
                                }
                        }
                        destruct(room);
                }
        }
        return 1;       
}
void check_clear(object room)
{
        string name;
        mixed dir;
        int tmp;
        int sz;
        if(!objectp(room))
                return;
        if(!room->is_fuben())
                return;
        name = base_name(room);
        dir = explode(name,"/");
        log_file("fb_clear",name+"\n");
        sz = sizeof(dir);
        if(sz <= FUBEN_ROOM_DIR)
                return;
        if(tmp = this_fuben_have_ppl(dir[FUBEN_NAME_DIR],dir[FUBEN_OWNER_DIR])) {
                return;
        } 
        clear_fuben(dir[FUBEN_NAME_DIR],dir[FUBEN_OWNER_DIR]);
        return;
}

int enter_fuben(string fbname,object me) 
{
        object startroom;
        mixed this_fb;
        string owner;
        int ret;
        mixed t;
        if(undefinedp(fuben_all[fbname]))
                return 0;
        this_fb = me->query("fuben/"+fbname);
        if(arrayp(this_fb)) {
                if(this_fb[1]>time()) {//�����ϸ���
                        owner = this_fb[0];
                } else {
                        //����ӵĻ���ȥ�Ҷӳ�
                        if(!pointerp(t = me->query_team())) {
                                owner = me->query("id");
                        } else {
                                foreach(object ob in t) {
                                        if(ob->is_team_leader()) {
                                                owner = ob->query("id");
                                                break;
                                        }
                                }
                        }
                        
                }
        } else {
                if(!pointerp(t = me->query_team())) {
                        owner = me->query("id");
                } else {
                        foreach(object ob in t) {
                                if(ob->is_team_leader()) {
                                        owner = ob->query("id");
                                        break;
                                }
                        }
                }
                
        }
        ret ="/adm/daemons/fuben_cron_d"->register_fuben_cron(fbname,owner,fuben_all[fbname][1]);
        
        me->set("fuben/"+fbname,({owner,ret}));
        startroom = load_object("/f/"+fbname+"/"+owner+"/"+fuben_data[fbname]["in"]);
        if(startroom) {
                CHANNEL_D->do_channel(this_object(),"wiz",me->query("name")+"("+me->query("id")+")"+"�����˸���"+fbname+"("+owner+")��");
                me->move(startroom);
        }
}

int valid_enter(object usr,string fbname)
{
        if(usr->query("combat_exp")<atoi(fuben_data[fbname]["basic_exp"]))
                return 0;
        if(usr->query("combat_exp")>=atoi(fuben_data[fbname]["basic_exp"])*3)
                return -1;      
        return 1;
}
