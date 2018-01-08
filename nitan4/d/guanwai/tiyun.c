// /guanwai/tiyun.c

inherit ROOM;

#include <ansi.h>

int i = 0;

string* msg = ({
  HIC "\nͻȻ��һ�����������ɽ��䴫������\n\n" NOR,
  HIW "���ظ��ˣ�����ϧ����ϧ������\n\n" NOR, 
  HIY "�㲻������һ�������룺�������������ˣ��ѵ�����������ɽ���еĸ��ˣ���\n" NOR,
  HIY "��������������˵����������ǰ��Ϊ�η����ˣ�Ϊ��̾Ϣ����\n\n" NOR,
  HIW "���ظ��˵��������¿��Ǻ��ҵ����Ĵ��ˣ���\n\n" NOR,
  HIY "��ش���������ǣ�ǰ���к�ָ�̣�Ī��ǰ����ʶ��ʦ��\n\n" NOR,
  HIW "���ظ��˶��˶ټ���������������Ҫ���ᡭ����ղſ����������������棿��\n\n" NOR,
  HIY "��̾��һ��������������ֻ�����½�������Ե���ӵ�������֮�ϳ˾����ˣ���\n" NOR,
  HIY "������������������������Ҳδ��Եѧ�ð����ҽ�������ʽ����Ȼ����������Ҳֻ�������ˡ�����\n\n" NOR,
  HIW "���ظ��˴�Ц���������ºδ����ԣ�ϰ��֮�����ڽ������书�ߵ�Ϊ�Σ����Ͷ����ơ���ǿ������Ϊ������������\n"
      "Ϊ�˶�����ʧ�⣿\n\n" NOR,
  HIY "��ˬ�ʵ�Ц������ǰ��������ˣ���������ǰ���̻�é��ٿ����������߽��������ԡ��Ͷ����ơ���ǿ������Ϊ�أ���\n\n" NOR,
  HIW "���ظ��˴�Ц�������ѵø����д˿����ؽ�����Ҳ������Ե�ˣ��Ҿʹ���һ���书�ھ������ն������õõ��ĵط�����\n\n" NOR,
  HIC "˵�գ����ظ��˽��ھ�һ��һʮ�Ĵ������㣬��һһ�������� ����\n\n" NOR,
  HIW "���Ȼ����ʲô���飬��æ�ʵ�����ǰ�������书���� ��������\n\n" NOR,
  HIC "�㷢����������ص���ɽ�ȼ䣬�����ظ���������ȥ��\n\n" NOR,
  HIC "��ѧ���ˡ���ҽ�������\n\n" NOR,
});

void create()
{
	set("short", "���Ʒ�");
        set("long", @LONG
�����山����һɽ�壬�弹���ݺ��ٲ���Զ�����ڰ����ƣ�����
���ݣ��������Ʒ塣
LONG );
	set("exits", ([
		"south"      : __DIR__"yuzhu",
	]));
	set("no_clean_up", 0);
	set("outdoors", "guanwai");
	setup();
}

void init()
{
        add_action("do_yanlian", "yanlian");
}

int do_yanlian(string arg)
{
       object me = this_player();
       object ob;

       if (!arg || arg != "daojian-guizhen")return 0;

       if (me->query_skill("hujia-daofa", 1) >= 250
           && me->query("character") == "��������"
           && !(int)me->query_skill("miaojia-jian", 1)
           && ( (ob = me->query_temp("weapon")) && ((string)ob->query("skill_type") == "blade" 
           || (string)ob->query("skill_type") == "sword"))           
           && random(10) == 1 && me->query("shen") > 50000)
      { 
           if (me->query_temp("learn_now"))return notify_fail("����æ������˵��\n");
           me->set_temp("learn_now", 1);
           write("�㿪ʼ�����������档\n");
           write("������ȴ��������һ����ҽ��������ᣬ���Լ����������㳤̾һ�������а���������׽Ū��\n");
           me->start_busy(3);
           remove_call_out("learn_sword");
           call_out("learn_sword", 3, me);    
      }
      else return 0;
     
      return 1;
}

int learn_sword(object me)
{  
     me->start_busy(3);
   
     write(msg[i]);

     if (i == sizeof(msg) - 1)
     {
          me->set_skill("miaojia-jian", 1);
          i = 0;
          me->delete_temp("learn_now");
          return 1;
     }
 
     remove_call_out("learn_sword");
     call_out("learn_sword", 3, me);
 
     i ++;

}
