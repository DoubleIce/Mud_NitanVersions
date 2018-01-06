// save.c
static string line = "";
void get_inv(object ob,int deep)
{
        mixed *inv;
        int i,sz;
        string base_name,tmp;
        string ex2;
        string db;
        inv = all_inventory(ob);        
        sz = sizeof(inv);
        ex2 = sprintf("%c",2);
        for(i=sz-1;i>=0;i--) {
                base_name = base_name(inv[i]);
                if(!sscanf(base_name,"/data/login/%s",tmp) && !sscanf(base_name,"/questobj/%s",tmp) && !inv[i]->query("no_save")) { // self made we dont save
                              db = save_variable(inv[i]->query_entire_dbase());
                              db =replace_string(db,"\n",ex2);
                              //tell_object(this_object(),db+"\n");
                        line +=sprintf("%d%c%s%c%s%c%d%c%s\n",deep,1,base_name(inv[i]),1,db,1,inv[i]->query_amount(),1,save_variable(inv[i]->my_id()));
                }

                if(inv[i]->is_container())
                        get_inv(inv[i],deep+1);
        }
}

int save() {
        string file;
        int deep;
        int ret = 0;
        if(stringp(file = this_object()->query_save_file())) {
                assure_file(file+ __SAVE_EXTENSION__);
                if(userp(this_object()) ) {
                        if(this_object()->is_vip()) {
                                deep = 0;
                                line = "";
                                get_inv(this_object(),deep);    
                                assure_file(file + ".package" + __SAVE_EXTENSION__);
                                ret = write_file(file + ".package" + __SAVE_EXTENSION__,line,1);
                        } else {
                                write_file(file + ".package" + __SAVE_EXTENSION__,"\n",1);
                        }
                }       
                ret += save_object(file);
                return ret;
        }
        
        return 0;
} 
int restore() {
        string file;
        
        if(stringp(file = this_object()->query_save_file())) {
                return restore_object(file);
        }
        return 0;
}     

int restore_package() {
        string file;
        mixed * sen;
        mixed *ab;
        string ex,ex2;
        string equipped;
        mixed tmp;
        object *pac = allocate(255);
        int last_pac;
        int size;
        int i;
        object ob;
        ex = sprintf("%c",1);
        ex2 = sprintf("%c",2);
        if(stringp(file = this_object()->query_save_file())) {
                file += ".package" +__SAVE_EXTENSION__;
                if(file_size(file)<=1)
                        return 0;
                
                if(file_size(file)>0) {
                        sen = explode(read_file(file),"\n");
                        //rm(file);
                        //rm(file);
                        size = sizeof(sen);
                        pac[0] = this_object();
                        for(i=0;i<size;i++) {
                                ab = explode(replace_string(sen[i],ex2,"\n"),ex);
                                if(sizeof(ab)==4) {//���ݾɰ汾
                                        ob = new(ab[1]);
                                        pac[atoi(ab[0])+1] = ob;
                                        
                                        tmp = restore_variable(ab[2]);
                                        
                                        if(!tmp || !mapp(tmp) ) {
                                                log_file("wrong_restore_ob",this_object()->query("id")+":"+ab[2]+"\n");
                                                continue;
                                        }
                                                
                                        ob ->set_entire_dbase(copy(tmp));
                                        //ob->set_name(ob->query("name"),({ob->query("id")}));
                                        if(ob->query_amount())
                                                ob->set_amount(atoi(ab[3]));
                                        equipped = ob->query("equipped");
                                        switch(equipped) {
                                        case "worn":
                                                ob->delete("equipped");
                                                ob->move(this_object());
                                                ob->wear();     
                                                break;
                                        case "wielded": 
                                                ob->delete("equipped");
                                                ob->move(this_object());
                                                ob->wield();
                                                break;  
                                        default:        
                                                ob->move( pac[atoi(ab[0])] );
                                                break;  
                                        }
                                }
                                if(sizeof(ab)==5) {//�������°汾
                                        ob = new(ab[1]);
                                        if(!ob) {
                                                log_file("wrong_restore_ob",this_object()->query("id")+":"+ab[1]+"\n");
                                                continue;
                                        }
                                        pac[atoi(ab[0])+1] = ob;
                                        
                                        tmp = restore_variable(ab[2]);
                                        
                                        if(!tmp || !mapp(tmp) ) {
                                                log_file("wrong_restore_ob",this_object()->query("id")+":"+ab[2]+"\n");
                                                continue;
                                        }
                                                
                                        ob ->set_entire_dbase(copy(tmp));
                                        if(!undefinedp(ab[4]) && ab[4]!="" && ab[4]!=0) {
                                                ob->set_name(ob->query("name"),restore_variable(ab[4]));
                                        }
                                        if(ob->query_amount())
                                                ob->set_amount(atoi(ab[3]));
                                        equipped = ob->query("equipped");
                                        switch(equipped) {
                                        case "worn":
                                                ob->delete("equipped");
                                                ob->move(this_object());
                                                ob->wear();     
                                                break;
                                        case "wielded": 
                                                ob->delete("equipped");
                                                ob->move(this_object());
                                                ob->wield();
                                                break;  
                                        default:        
                                                ob->move( pac[atoi(ab[0])] );
                                                break;  
                                        }
                                }
                        }
                        return 1;
                } else {
                        return 0;
                }
        }
        return 0;
}

