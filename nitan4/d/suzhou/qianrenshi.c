// Room: /d/suzhou/qianrenshi.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "千人石");
        set("long", @LONG
在虎丘山中心，有一块千人石，巨石呈暗紫红色，由南向北倾斜
石面甚平坦，石壁如斧削。传说吴王墓筑成后，其子夫差怕泄露筑墓
秘密假借墓成祝酒观舞之名，将千余名工匠全部杀戮，鲜血渗透石中，
成暗红色。
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"east"      : "/d/suzhou/erxianting",
		"north"     : "/d/suzhou/shijianshi",
		"northwest" : "/d/suzhou/zhishuang",
	]));
	set("coor/x", 190);
	set("coor/y", -190);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}

