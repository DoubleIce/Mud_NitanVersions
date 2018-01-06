// fuben_npc_d

#define NPC_DIR "/adm/etc/fuben_npc/"
#define NPC_SKILL_EXT   "_skill"
mixed npc_data = ([]);
int set_npc_skill(object npc,string type,int level);

int set_npc_data(object npc) {
        int cexp,skill;
        int diff;
        diff = atoi(npc->query("difficult"));
        if(diff<3) {
                npc->set("title","��ͨ");
        } else if(diff < 6) {
                npc->set("title","ǿ׳");
        } else if(diff < 10) {
                npc->set("title","��Ӣ");
        } else {
                npc->set("title","��Ӣ");
        }
        cexp = npc->query("basic_exp")*(10+diff)/10;
        log_file("cexp",cexp+"\n");
        skill = to_int(exp(log(to_float(cexp))/3));
        npc->set("combat_exp",cexp);
        set_npc_skill(npc,npc->query("type"),skill);
        return 1;
}
int set_npc_skill(object npc,string type,int level)
{
        mixed key;
        string skill;
        if(undefinedp(npc_data[type]))
                return 0;
        if(!npc)
                return 0;
        foreach(skill in npc_data[type]["basic_skill"]) {
                npc->set_skill(skill,level*100/SKILL_D(skill)->effective_level());
        }
        key = keys(npc_data[type]["advance_skill"]);
        foreach(skill in key) {
                npc->set_skill(skill,level*100/SKILL_D(skill)->effective_level());
                foreach(string map in npc_data[type]["advance_skill"][skill]) {
                        npc->map_skill(map,skill);
                }
        }
        return 1;
}
int setup_npc_skill_data(string type)
{
        string file;
        mixed f;
        string skill;
        mixed enable;
        file = NPC_DIR+type+NPC_SKILL_EXT;
        f = read_file(file);
        f = explode(replace_string(f,"\r",""),"\n");
        if(undefinedp(npc_data[type])) {
                npc_data[type] = ([]);
        }
        foreach(string line in f) {
                if(sscanf(line,"%s:%s",skill,enable) != 2) {
                        if(undefinedp(npc_data[type]["basic_skill"])) {
                                npc_data[type]["basic_skill"] = ({line});
                        } else {
                                npc_data[type]["basic_skill"] += ({line});
                        }
                } else {
                        if(undefinedp(npc_data[type]["advance_skill"])) {
                                npc_data[type]["advance_skill"] = ([]);
                        }
                        enable = explode(enable,",");
                        npc_data[type]["advance_skill"][skill] = copy(enable);
                }
        }
        log_file("fb_npc",sprintf("%O\n",npc_data));
}
void create()
{
        setup_npc_skill_data("tianchui");
}
