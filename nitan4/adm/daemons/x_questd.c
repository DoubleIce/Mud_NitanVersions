// This program is a part of NITAN MudLIB
// /adm/daemons/x_questd.c ��ʦ��Ѷ�����ػ�����

#define ANTI_ROBOT      "/kungfu/class/ultra/robot"

public int query_quest(object me, object ob)
{
    mapping temp, quest = ([]);
    string arg, msg, str, place, where, question, answer;
    object npc;
    object maze_target;
    object maze_object;

    temp = X_PointD->get_question();    //���ػ����������������
    // temp =  ANTI_ROBOT->get_question();
    question = temp["question"];
    answer = temp["answer"];

    message("vision", sprintf("%sС���Ķ�%s�Ը���ʲô��%sһ������"
                              "һ�߲�ס�ĵ�ͷ��\n",
                                ob->name(1), me->name(), me->name()),
                                environment(me), ({ me }));

    npc = new(CLASS_D("generate") + "/player_npc.c");   //������Ѷ��
    FUBEN_D->clear_fuben("ultra", me->query("id"));
    maze_object = get_object("/f/ultra/"+me->query("id")+"/maze");
    maze_object->set_maze_boss(npc);
    //maze_target = MAZE_D->create_maze(npc);
    maze_target = get_object("/f/ultra/"+me->query("id")+"/maze/exit");
    npc->move(maze_target);
    npc->set_from_me(ob, 1);
    npc->set_temp("quester", me->query("id"));
    npc->set("ultra_whisper", me->query("id"));

    msg = sprintf("\n%s����˵������Ͻ���һ�ˣ��������Ѷ����"
                  "(whisper)��%s����˵������һ���Թ��У���������\n",
                    ob->name(1), npc->name(1));
    msg += question;

    //quest["maze"] = maze_target->query("maze/mazename");
    quest["maze"] = maze_object;
    quest["object"] = base_name(npc);
    quest["bonus"] = 200+random(51);
    quest["name"] = npc->name(1);
    quest["id"] = npc->query("id");
    quest["answer"] = answer;
    quest["type"] = "��";
    switch(ob->query("id"))
    {
        case "dugu qiubai":
        quest["dgmsg"] = msg;
        str = "quest_dg";

        break;

        case "kuihua taijian":
        quest["khmsg"] = msg;
        arg = "player_npc";
        str = "quest_kh";
        break;

        case "huang shang":
        quest["msg"] = msg;
        str = "quest_hs";
        break;

        case "nanhai shenni":
        quest["msg"] = msg;
        str = "quest_sn";
        break;
    }

    me->set(str, quest);
    me->start_more(msg);

    return 1;
}
