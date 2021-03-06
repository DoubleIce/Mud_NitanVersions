// Room: /guiyun/dating.c
// Date: Nov.18 1998 by Winder
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "大厅");
        set("long", @LONG
这是归云庄的正厅，由于修建年代久远，看起来已颇为陈旧，但
打扫得十分干净，光线也较为充足，完全没有陈年旧宅的阴晦之气。
四壁挂着一些古人书画精品，皆为上乘之作，显得主人眼光不凡，胸
中大有丘壑。
LONG );
//      set("outdoors", "guiyun");
//	set("no_clean_up", 0);

	set("exits", ([
		"north" : __DIR__"huating",
		"south" : __DIR__"qianyuan",
		"east"  : __DIR__"shufang",
	]));
	set("objects", ([
		__DIR__"npc/kezhene" : 1,
		__DIR__"npc/zhucong" : 1,
		__DIR__"npc/hanbaoju" : 1,
		__DIR__"npc/nanxiren" : 1,
		__DIR__"npc/zhangasheng" : 1,
		__DIR__"npc/quanjinfa" : 1,
		__DIR__"npc/hanxiaoyin" : 1,
	]));
	setup();
	// replace_program(ROOM);
}

void init()
{
        object me = this_player();
        int score, skill, age;

        if (me->query("age") >= 30 || random(me->query("kar")) < 15)
                return;
                
        if (me->query("family/master_id") != "lu chengfeng" &&   
            me->query("family/master_id") != "qu lingfeng")
                return;


        age = me->query("age") - 13;
        skill = (me->query_skill("force") + me->query_skill("dodge") +
                me->query_skill("strike") + me->query_skill("qimen-wuxing")) / 4;
        skill *= atoi(count_div(me->query("combat_exp"), 1000));
        score = skill / age;

        if (score < 1000) 
                return;
        
        remove_call_out("recruit_ob");
        call_out("recruit_ob", 50, me);
        
        tell_object(me, CYN "你觉得身后有点古怪，似乎有人跟随？\n" NOR);
}

void recruit_ob(object me)
{
        object ob, *obj;
        int i, j = 0;

        if (! me) return;

        obj = all_inventory(environment(me));
        
        for(i = 0; i < sizeof(obj); i++)
        {
                if (playerp(obj[i]))
                j++;
        }
        
        if (j > 1) return;

        ob = new(CLASS_D("taohua/huang"));
        if (! me->is_busy())
                me->start_busy(1);
        ob->move(environment(me));

        message_sort("$N前面突然出现了一人，身材高瘦，身穿青色布袍，脸色古怪之极，两颗眼珠似乎尚能"
                       "微微转动，除此之外，肌肉口鼻，尽皆僵硬如木石，直是一个死人头装在活人的躯体上。\n\n", me);
                       
        message_sort("$N一见之下，登时一阵凉气从背脊上直冷下来，目光与这张脸孔相触，便都不敢再看，立时将"
                       "头转开，心中怦然而动：莫非这就是祖师爷爷，江湖中传闻的桃花岛主？ 忙上前恭恭敬敬的"
                       "磕了四个头，说道：“孙儿叩见师祖。”黄药师道：“罢了！”并不俯身相扶，却伸左手抓住$N后"
                       "心一提，右掌便向$N肩头拍下。。。\n", me);
        message_sort("$N一见不妙，来不及细想，赶紧身形疾闪，使出一招“海燕腾空”，身体如同为海风所激，向后飘开一丈有余。\n\n", me);
        message_sort("黄药师微一愣，哼了一声道：" + RANK_D->query_rude(me) + "却有几分资质，我就成全你吧。\n\n", me);
        
        message_sort("$N想要收$n为弟子。\n", ob, me);
        tell_object(me, YEL "如果你愿意拜" + ob->name() + "为师父，用 apprentice 指令。\n" NOR);
        me->set_temp("huang_recr", 1);
        
        remove_call_out("finish_recr");
        call_out("finish_recr", 30, me, ob);
}

void finish_recr(object me, object ob)
{
        if (! objectp(me) || ! objectp(ob))
                return;
                
        if (me->query("family/master_id") != "huang yaoshi")
        {
                message_vision("$N冷笑一声：" + RANK_D->query_rude(me) + "居然有几分臭架子。说完飘然而去。\n", ob);
                me->delete_temp("huang_recr");
                destruct(ob);
        }
        return;
}
