#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ǹ�Ĺ�ĺ������ܷ������ʵʵ��û��һ˿�ķ�϶���ڻ谵��
�ƹ��£��㷢��ǽ��������һ���� (picture)���ƺ���һ�������Ф
�����������룬�ڷ��ż��߹ײ�(coffin)������ֻ��һ�߹ײĵĹ�
��û�к��ϣ��ײ��к���տ���Ҳ�������ϰڷ���һ��ʯͷ���ɵĴ�
��(chuang)��
LONG );

        set("exits", ([
                "north" : __DIR__"zhengting",
        ]));

        set("item_desc", ([
                "picture" : WHT "\n������һ�������ʿ�ı�Ӱ��������ʲô��"
                            "ò��������һ��ָ\n�죬�������š�" HIR "������"
                            "��" NOR + WHT "���ĸ����֡�\n" NOR,

                "coffin" : WHT "\n�ú���ʯ�����ɵĹײģ��װ���Ϻ󣬾�û"
                           "��һ˿�ķ�϶�ˡ�\n" NOR
        ]));

        if (random(10) > 8)
                set("getbook", 3);

        setup();
}

void init()
{
        add_action("do_tang", "tang");
          add_action("do_sleep", "sleep"); 
        add_action("do_niu", "niu");
}

int do_tang(string arg)
{
        object ob, paper;
        object me = this_player();

        if (! arg || arg != "coffin")
                return notify_fail("��Ҫ�����Ķ���\n");

        if (me->query_temp("tmarks/��"))
                return notify_fail("�������Ѿ��ɽ��ײ��ˡ�\n");

        paper = present("paper", me);

        if (query("getbook") >= 1
           && objectp(paper)
           && paper->query("can_draw") >= 1)
        {
                message_sort(HIW "\n$N" HIW "�ɽ��ײ��У��ѹװ���ϣ���ʱһƬ"
                             "�ڰ����ƺ���쳾�����ˣ�������$N" HIW "�����װ�"
                             "�ڱ��������֣�ϸϸ��������һͷд�š�" HIY "��Ů"
                             "�ľ�����ѹȫ�档����һ������������" HIW "��ʮ��"
                             "�����֣���һͷ������Щͼ����ķ��š�$N" HIW "��"
                             "֪���ԣ��������ϴ���ֽ�ţ���������������˵������"
                             "ϸϸ�ؽ���������ȫ��������������������֮�䣬����"
                             "�׽��Ͼ�����һ��͹��Ļ���(lock)��\n\n" NOR, me);
                ob = new("/clone/lonely/book/zhenjing3");
                ob->move(me, 1);

                tell_object(me, HIC "��õ���һ��" NOR + ob->name() +
                                HIC "��\n\n" NOR);

                add("getbook", -1);
                destruct(paper);
        } else
        if (query("getbook") >= 1)
        {
                message_sort(HIW "\n$N" HIW "�ɽ��ײ��У��ѹװ���ϣ���ʱһƬ"
                             "�ڰ����ƺ���쳾�����ˣ�������$N" HIW "�����װ�"
                             "�ڱ��������֣�ϸϸ��������һͷд�š�" HIY "��Ů"
                             "�ľ�����ѹȫ�档����һ������������" HIW "��ʮ��"
                             "�����֣���һͷ������Щͼ����ķ��š�$N" HIW "��"
                             "Ȼ�Ķ�����������Χһ����ڣ������޷����壬ֻ����"
                             "�ա�ͻȻ�䣬�����׽��Ͼ�����һ��͹��Ļ���(lock)"
                             "��\n\n" NOR, me);
        } else
        {
                message_sort(HIW "\n$N" HIW "�ɽ��ײ��У��ѹװ���ϣ���ʱһƬ"
                             "�ڰ����ƺ���쳾�����ˣ�������$N" HIW "�����װ�"
                             "�ڱ��������֣�ϸϸ��������һͷд�š�" HIY "��Ů"
                             "�ľ�����ѹȫ�档����һ������������" HIW "��ʮ��"
                             "�����֣���һͷ������Щͼ������š������ּ��ѱ���"
                             "����ε���ͻȻ�䣬�����׽��Ͼ�����һ��͹��Ļ���"
                             "(lock)��\n\n", me);
        }

        me->set_temp("tmarks/��", 1);
        return 1;
}

int do_niu(string arg)
{
        object me = this_player();

        if (! arg || arg != "lock" || ! me->query_temp("tmarks/��"))
                return notify_fail("��ҪŤ��ʲô��\n");

        message_sort(HIY "\n$N" HIY "���ջ��أ���������Ť������Ȼ"
                     "��׵�֨֨���죬�ѿ���һ���󶴣�$N" HIY "��"
                     "����������ȥ��\n\n" NOR, me);
        me->move(__DIR__"mishi2");

        me->delete_temp("tmarks/��");
        return 1;
}
void reset()
{
        if (random(10) > 8)
                set("getbook", 3);
        ::reset();
}
      int do_sleep(string arg) 
     { 
              object me=this_player(); 
              int lvl_force; 

              lvl_force = (int)me->query_skill("force", 1); 
              if (lvl_force > 150) 
              { 
                      message_vision(HIC "\n$N" HIC "�����˺��񴲣���ʼǱ���ڹ���ʹ��" 
                                     "Ϣ���д�С���졣\n", this_player()); 
                      if (random(20) > 12) 
                      { 
tell_object(me,HIM"���Ϣ��ϣ�ֻ���þ���������Ϣ���������ڶ�����\n"NOR );
                              if (me->can_improve_skill("force") && lvl_force < 400) 
                                      me->improve_skill("force", 1 + lvl_force); 

                              me->receive_damage("qi", lvl_force / 3 + random(lvl_force / 3)); 
                      } 
                      else 
                      { 
tell_object(me,"���Ϣ��ϣ�վ������������������������ûʲô������\n" );
                              me->receive_damage("qi", 10 + random(10)); 
                      } 
              } else 
              { 
tell_object(me,"�����Ϻ��񴲣�ֻ���ñ���̹ǣ���������һ���Ǳ�����������������\n" );
              } 
              return 1; 
      } 