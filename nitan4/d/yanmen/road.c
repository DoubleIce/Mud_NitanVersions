// Create by lonely@NT
inherit ROOM; 
#include <ansi.h>; 
void create() 
{ 
        set("short", "ɽ��"); 
        set("long", @LONG
�����Ѿ��쵽���Ź��ˣ�������ȥ�������������۵�ɽ�������
�е��˴������󶼿�ʼ��Щ����������
LONG );
        set("outdoors", "yanmen"); 
        set("no_fly",1); 
        set("exits", ([ 
                "north"  : "/d/guanwai/shanhaiguan", 
                "south"  : __DIR__"luanshi1", 
        ])); 
        setup(); 
} 