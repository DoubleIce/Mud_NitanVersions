// Room: /d/suzhou/wanjing.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
        set("short", "憨憨泉");
        set("long", @LONG
在山道西侧有一憨憨泉，系南朝梁代高僧憨憨尊者所开凿，距今
一千四百多年。据说泉眼通海，姑又名『海涌泉』。水甚清冽为『天
下第五泉』。石刻『憨憨泉』三字，系北宋吕升卿所题。
LONG );
        set("resource/water", 1); 
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "eastdown"   : "/d/suzhou/wanjing",
        ]));
        set("max_room", 1);  
        set("coor/x", 170);
	set("coor/y", -180);
	set("coor/z", 10);
	setup();
}

