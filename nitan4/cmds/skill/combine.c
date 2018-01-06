// combine.c
// Updated by Lonely

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mapping combine_list = ([
        // 宝石的合成: 3个相同的宝石合成为高一级的同类宝石
        ({ "/inherit/template/gem/blugem1-1",
           "/inherit/template/gem/blugem1-2",
           "/inherit/template/gem/blugem1-3", }) : "/clone/enchase/blugem2",

        ({ "/inherit/template/gem/blugem2-1",
           "/inherit/template/gem/blugem2-2",
           "/inherit/template/gem/blugem2-3", }) : "/clone/enchase/blugem3",

        ({ "/inherit/template/gem/blugem3-1",
           "/inherit/template/gem/blugem3-2",
           "/inherit/template/gem/blugem3-3", }) : "/clone/enchase/blugem4",

        ({ "/inherit/template/gem/blugem4-1",
           "/inherit/template/gem/blugem4-2",
           "/inherit/template/gem/blugem4-3", }) : "/clone/enchase/blugem5",

        ({ "/inherit/template/gem/blugem5-1",
           "/inherit/template/gem/blugem5-2",
           "/inherit/template/gem/blugem5-3", }) : "/clone/enchase/blugem6",

/*
        ({ "/inherit/template/gem/blugem6-1",
           "/inherit/template/gem/blugem6-2",
           "/inherit/template/gem/blugem6-3", }) : "/clone/enchase/blugem7",
*/

        ({ "/inherit/template/gem/grngem1-1",
           "/inherit/template/gem/grngem1-2",
           "/inherit/template/gem/grngem1-3", }) : "/clone/enchase/grngem2",

        ({ "/inherit/template/gem/grngem2-1",
           "/inherit/template/gem/grngem2-2",
           "/inherit/template/gem/grngem2-3", }) : "/clone/enchase/grngem3",

        ({ "/inherit/template/gem/grngem3-1",
           "/inherit/template/gem/grngem3-2",
           "/inherit/template/gem/grngem3-3", }) : "/clone/enchase/grngem4",

        ({ "/inherit/template/gem/grngem4-1",
           "/inherit/template/gem/grngem4-2",
           "/inherit/template/gem/grngem4-3", }) : "/clone/enchase/grngem5",

        ({ "/inherit/template/gem/grngem5-1",
           "/inherit/template/gem/grngem5-2",
           "/inherit/template/gem/grngem5-3", }) : "/clone/enchase/grngem6",

/*
        ({ "/inherit/template/gem/grngem6-1",
           "/inherit/template/gem/grngem6-2",
           "/inherit/template/gem/grngem6-3", }) : "/clone/enchase/grngem7",
*/

        ({ "/inherit/template/gem/maggem1-1",
           "/inherit/template/gem/maggem1-2",
           "/inherit/template/gem/maggem1-3", }) : "/clone/enchase/maggem2",

        ({ "/inherit/template/gem/maggem2-1",
           "/inherit/template/gem/maggem2-2",
           "/inherit/template/gem/maggem2-3", }) : "/clone/enchase/maggem3",

        ({ "/inherit/template/gem/maggem3-1",
           "/inherit/template/gem/maggem3-2",
           "/inherit/template/gem/maggem3-3", }) : "/clone/enchase/maggem4",

        ({ "/inherit/template/gem/maggem4-1",
           "/inherit/template/gem/maggem4-2",
           "/inherit/template/gem/maggem4-3", }) : "/clone/enchase/maggem5",

        ({ "/inherit/template/gem/maggem5-1",
           "/inherit/template/gem/maggem5-2",
           "/inherit/template/gem/maggem5-3", }) : "/clone/enchase/maggem6",

/*
        ({ "/inherit/template/gem/maggem6-1",
           "/inherit/template/gem/maggem6-2",
           "/inherit/template/gem/maggem6-3", }) : "/clone/enchase/maggem7",
*/

        ({ "/inherit/template/gem/redgem1-1",
           "/inherit/template/gem/redgem1-2",
           "/inherit/template/gem/redgem1-3", }) : "/clone/enchase/redgem2",

        ({ "/inherit/template/gem/redgem2-1",
           "/inherit/template/gem/redgem2-2",
           "/inherit/template/gem/redgem2-3", }) : "/clone/enchase/redgem3",

        ({ "/inherit/template/gem/redgem3-1",
           "/inherit/template/gem/redgem3-2",
           "/inherit/template/gem/redgem3-3", }) : "/clone/enchase/redgem4",

        ({ "/inherit/template/gem/redgem4-1",
           "/inherit/template/gem/redgem4-2",
           "/inherit/template/gem/redgem4-3", }) : "/clone/enchase/redgem5",

        ({ "/inherit/template/gem/redgem5-1",
           "/inherit/template/gem/redgem5-2",
           "/inherit/template/gem/redgem5-3", }) : "/clone/enchase/redgem6",

/*
        ({ "/inherit/template/gem/redgem6-1",
           "/inherit/template/gem/redgem6-2",
           "/inherit/template/gem/redgem6-3", }) : "/clone/enchase/redgem7",
*/

        ({ "/inherit/template/gem/yelgem1-1",
           "/inherit/template/gem/yelgem1-2",
           "/inherit/template/gem/yelgem1-3", }) : "/clone/enchase/yelgem2",

        ({ "/inherit/template/gem/yelgem2-1",
           "/inherit/template/gem/yelgem2-2",
           "/inherit/template/gem/yelgem2-3", }) : "/clone/enchase/yelgem3",

        ({ "/inherit/template/gem/yelgem3-1",
           "/inherit/template/gem/yelgem3-2",
           "/inherit/template/gem/yelgem3-3", }) : "/clone/enchase/yelgem4",

        ({ "/inherit/template/gem/yelgem4-1",
           "/inherit/template/gem/yelgem4-2",
           "/inherit/template/gem/yelgem4-3", }) : "/clone/enchase/yelgem5",

        ({ "/inherit/template/gem/yelgem5-1",
           "/inherit/template/gem/yelgem5-2",
           "/inherit/template/gem/yelgem5-3", }) : "/clone/enchase/yelgem6",

/*
        ({ "/inherit/template/gem/yelgem6-1",
           "/inherit/template/gem/yelgem6-2",
           "/inherit/template/gem/yelgem6-3", }) : "/clone/enchase/yelgem7",
*/

        ({ "/inherit/template/gem/skull1-1",
           "/inherit/template/gem/skull1-2",
           "/inherit/template/gem/skull1-3", }) : "/clone/enchase/skull2",

        ({ "/inherit/template/gem/skull2-1",
           "/inherit/template/gem/skull2-2",
           "/inherit/template/gem/skull2-3", }) : "/clone/enchase/skull3",

        ({ "/inherit/template/gem/skull3-1",
           "/inherit/template/gem/skull3-2",
           "/inherit/template/gem/skull3-3", }) : "/clone/enchase/skull4",

        ({ "/inherit/template/gem/skull4-1",
           "/inherit/template/gem/skull4-2",
           "/inherit/template/gem/skull4-3", }) : "/clone/enchase/skull5",

        ({ "/inherit/template/gem/skull5-1",
           "/inherit/template/gem/skull5-2",
           "/inherit/template/gem/skull5-3", }) : "/clone/enchase/skull6",

/*
        ({ "/inherit/template/gem/skull6-1",
           "/inherit/template/gem/skull6-2",
           "/inherit/template/gem/skull6-3", }) : "/clone/enchase/skull7",
*/

        ({ "/clone/enchase/blugem1-1",
           "/clone/enchase/blugem1-2",
           "/clone/enchase/blugem1-3", }) : "/clone/enchase/blugem2",

        ({ "/clone/enchase/blugem2-1",
           "/clone/enchase/blugem2-2",
           "/clone/enchase/blugem2-3", }) : "/clone/enchase/blugem3",

        ({ "/clone/enchase/blugem3-1",
           "/clone/enchase/blugem3-2",
           "/clone/enchase/blugem3-3", }) : "/clone/enchase/blugem4",

        ({ "/clone/enchase/blugem4-1",
           "/clone/enchase/blugem4-2",
           "/clone/enchase/blugem4-3", }) : "/clone/enchase/blugem5",

        ({ "/clone/enchase/blugem5-1",
           "/clone/enchase/blugem5-2",
           "/clone/enchase/blugem5-3", }) : "/clone/enchase/blugem6",

/*
        ({ "/clone/enchase/blugem6-1",
           "/clone/enchase/blugem6-2",
           "/clone/enchase/blugem6-3", }) : "/clone/enchase/blugem7",
*/

        ({ "/clone/enchase/grngem1-1",
           "/clone/enchase/grngem1-2",
           "/clone/enchase/grngem1-3", }) : "/clone/enchase/grngem2",

        ({ "/clone/enchase/grngem2-1",
           "/clone/enchase/grngem2-2",
           "/clone/enchase/grngem2-3", }) : "/clone/enchase/grngem3",

        ({ "/clone/enchase/grngem3-1",
           "/clone/enchase/grngem3-2",
           "/clone/enchase/grngem3-3", }) : "/clone/enchase/grngem4",

        ({ "/clone/enchase/grngem4-1",
           "/clone/enchase/grngem4-2",
           "/clone/enchase/grngem4-3", }) : "/clone/enchase/grngem5",

        ({ "/clone/enchase/grngem5-1",
           "/clone/enchase/grngem5-2",
           "/clone/enchase/grngem5-3", }) : "/clone/enchase/grngem6",

/*
        ({ "/clone/enchase/grngem6-1",
           "/clone/enchase/grngem6-2",
           "/clone/enchase/grngem6-3", }) : "/clone/enchase/grngem7",
*/

        ({ "/clone/enchase/maggem1-1",
           "/clone/enchase/maggem1-2",
           "/clone/enchase/maggem1-3", }) : "/clone/enchase/maggem2",

        ({ "/clone/enchase/maggem2-1",
           "/clone/enchase/maggem2-2",
           "/clone/enchase/maggem2-3", }) : "/clone/enchase/maggem3",

        ({ "/clone/enchase/maggem3-1",
           "/clone/enchase/maggem3-2",
           "/clone/enchase/maggem3-3", }) : "/clone/enchase/maggem4",

        ({ "/clone/enchase/maggem4-1",
           "/clone/enchase/maggem4-2",
           "/clone/enchase/maggem4-3", }) : "/clone/enchase/maggem5",

        ({ "/clone/enchase/maggem5-1",
           "/clone/enchase/maggem5-2",
           "/clone/enchase/maggem5-3", }) : "/clone/enchase/maggem6",

/*
        ({ "/clone/enchase/maggem6-1",
           "/clone/enchase/maggem6-2",
           "/clone/enchase/maggem6-3", }) : "/clone/enchase/maggem7",
*/

        ({ "/clone/enchase/redgem1-1",
           "/clone/enchase/redgem1-2",
           "/clone/enchase/redgem1-3", }) : "/clone/enchase/redgem2",

        ({ "/clone/enchase/redgem2-1",
           "/clone/enchase/redgem2-2",
           "/clone/enchase/redgem2-3", }) : "/clone/enchase/redgem3",

        ({ "/clone/enchase/redgem3-1",
           "/clone/enchase/redgem3-2",
           "/clone/enchase/redgem3-3", }) : "/clone/enchase/redgem4",

        ({ "/clone/enchase/redgem4-1",
           "/clone/enchase/redgem4-2",
           "/clone/enchase/redgem4-3", }) : "/clone/enchase/redgem5",

        ({ "/clone/enchase/redgem5-1",
           "/clone/enchase/redgem5-2",
           "/clone/enchase/redgem5-3", }) : "/clone/enchase/redgem6",

/*
        ({ "/clone/enchase/redgem6-1",
           "/clone/enchase/redgem6-2",
           "/clone/enchase/redgem6-3", }) : "/clone/enchase/redgem7",
*/

        ({ "/clone/enchase/yelgem1-1",
           "/clone/enchase/yelgem1-2",
           "/clone/enchase/yelgem1-3", }) : "/clone/enchase/yelgem2",

        ({ "/clone/enchase/yelgem2-1",
           "/clone/enchase/yelgem2-2",
           "/clone/enchase/yelgem2-3", }) : "/clone/enchase/yelgem3",

        ({ "/clone/enchase/yelgem3-1",
           "/clone/enchase/yelgem3-2",
           "/clone/enchase/yelgem3-3", }) : "/clone/enchase/yelgem4",

        ({ "/clone/enchase/yelgem4-1",
           "/clone/enchase/yelgem4-2",
           "/clone/enchase/yelgem4-3", }) : "/clone/enchase/yelgem5",

        ({ "/clone/enchase/yelgem5-1",
           "/clone/enchase/yelgem5-2",
           "/clone/enchase/yelgem5-3", }) : "/clone/enchase/yelgem6",

/*
        ({ "/clone/enchase/yelgem6-1",
           "/clone/enchase/yelgem6-2",
           "/clone/enchase/yelgem6-3", }) : "/clone/enchase/yelgem7",
*/

        ({ "/clone/enchase/skull1-1",
           "/clone/enchase/skull1-2",
           "/clone/enchase/skull1-3", }) : "/clone/enchase/skull2",

        ({ "/clone/enchase/skull2-1",
           "/clone/enchase/skull2-2",
           "/clone/enchase/skull2-3", }) : "/clone/enchase/skull3",

        ({ "/clone/enchase/skull3-1",
           "/clone/enchase/skull3-2",
           "/clone/enchase/skull3-3", }) : "/clone/enchase/skull4",

        ({ "/clone/enchase/skull4-1",
           "/clone/enchase/skull4-2",
           "/clone/enchase/skull4-3", }) : "/clone/enchase/skull5",

        ({ "/clone/enchase/skull5-1",
           "/clone/enchase/skull5-2",
           "/clone/enchase/skull5-3", }) : "/clone/enchase/skull6",

/*
        ({ "/clone/enchase/skull6-1",
           "/clone/enchase/skull6-2",
           "/clone/enchase/skull6-3", }) : "/clone/enchase/skull7",
*/
           
        // 符文的合成公式
        ({ "/clone/enchase/rune01-1",
           "/clone/enchase/rune01-2",
           "/clone/enchase/rune01-3", }) : "/clone/enchase/rune02",

        ({ "/clone/enchase/rune02-1",
           "/clone/enchase/rune02-2",
           "/clone/enchase/rune02-3", }) : "/clone/enchase/rune03",

        ({ "/clone/enchase/rune03-1",
           "/clone/enchase/rune03-2",
           "/clone/enchase/rune03-3", }) : "/clone/enchase/rune04",

        ({ "/clone/enchase/rune04-1",
           "/clone/enchase/rune04-2",
           "/clone/enchase/rune04-3", }) : "/clone/enchase/rune05",

        ({ "/clone/enchase/rune05-1",
           "/clone/enchase/rune05-2",
           "/clone/enchase/rune05-3", }) : "/clone/enchase/rune06",

        ({ "/clone/enchase/rune06-1",
           "/clone/enchase/rune06-2",
           "/clone/enchase/rune06-3", }) : "/clone/enchase/rune07",

        ({ "/clone/enchase/rune07-1",
           "/clone/enchase/rune07-2",
           "/clone/enchase/rune07-3", }) : "/clone/enchase/rune08",

        ({ "/clone/enchase/rune08-1",
           "/clone/enchase/rune08-2",
           "/clone/enchase/rune08-3", }) : "/clone/enchase/rune09",

        ({ "/clone/enchase/rune09-1",
           "/clone/enchase/rune09-2",
           "/clone/enchase/rune09-3", }) : "/clone/enchase/rune10",

        ({ "/clone/enchase/rune10-1",
           "/clone/enchase/rune10-2",
           "/clone/enchase/rune10-3",
           "/inherit/template/gem/yelgem3-1", }) : "/clone/enchase/rune11",

        ({ "/clone/enchase/rune10-1",
           "/clone/enchase/rune10-2",
           "/clone/enchase/rune10-3",
           "/clone/enchase/yelgem3-1", }) : "/clone/enchase/rune11",
           
        ({ "/clone/enchase/rune11-1",
           "/clone/enchase/rune11-2",
           "/clone/enchase/rune11-3",
           "/inherit/template/gem/maggem3-1", }) : "/clone/enchase/rune12",

        ({ "/clone/enchase/rune11-1",
           "/clone/enchase/rune11-2",
           "/clone/enchase/rune11-3",
           "/clone/enchase/maggem3-1", }) : "/clone/enchase/rune12",
           
        ({ "/clone/enchase/rune12-1",
           "/clone/enchase/rune12-2",
           "/clone/enchase/rune12-3",
           "/inherit/template/gem/blugem3-1", }) : "/clone/enchase/rune13",

        ({ "/clone/enchase/rune12-1",
           "/clone/enchase/rune12-2",
           "/clone/enchase/rune12-3",
           "/clone/enchase/blugem3-1", }) : "/clone/enchase/rune13",
           
        ({ "/clone/enchase/rune13-1",
           "/clone/enchase/rune13-2",
           "/clone/enchase/rune13-3",
           "/inherit/template/gem/redgem3-1", }) : "/clone/enchase/rune14",

        ({ "/clone/enchase/rune13-1",
           "/clone/enchase/rune13-2",
           "/clone/enchase/rune13-3",
           "/clone/enchase/redgem3-1", }) : "/clone/enchase/rune14",

        ({ "/clone/enchase/rune14-1",
           "/clone/enchase/rune14-2",
           "/clone/enchase/rune14-3",
           "/inherit/template/gem/grngem3-1", }) : "/clone/enchase/rune15",

        ({ "/clone/enchase/rune14-1",
           "/clone/enchase/rune14-2",
           "/clone/enchase/rune14-3",
           "/clone/enchase/grngem3-1", }) : "/clone/enchase/rune15",

        ({ "/clone/enchase/rune15-1",
           "/clone/enchase/rune15-2",
           "/clone/enchase/rune15-3",
           "/inherit/template/gem/skull3-1", }) : "/clone/enchase/rune16",

        ({ "/clone/enchase/rune15-1",
           "/clone/enchase/rune15-2",
           "/clone/enchase/rune15-3",
           "/clone/enchase/skull3-1", }) : "/clone/enchase/rune16",
           
        ({ "/clone/enchase/rune16-1",
           "/clone/enchase/rune16-2",
           "/clone/enchase/rune16-3",
           "/inherit/template/gem/yelgem4-1", }) : "/clone/enchase/rune17",

        ({ "/clone/enchase/rune16-1",
           "/clone/enchase/rune16-2",
           "/clone/enchase/rune16-3",
           "/clone/enchase/yelgem4-1", }) : "/clone/enchase/rune17",

        ({ "/clone/enchase/rune17-1",
           "/clone/enchase/rune17-2",
           "/clone/enchase/rune17-3",
           "/inherit/template/gem/maggem4-1", }) : "/clone/enchase/rune18",

        ({ "/clone/enchase/rune17-1",
           "/clone/enchase/rune17-2",
           "/clone/enchase/rune17-3",
           "/clone/enchase/maggem4-1", }) : "/clone/enchase/rune18",

        ({ "/clone/enchase/rune18-1",
           "/clone/enchase/rune18-2",
           "/clone/enchase/rune18-3",
           "/inherit/template/gem/blugem4-1", }) : "/clone/enchase/rune19",

        ({ "/clone/enchase/rune18-1",
           "/clone/enchase/rune18-2",
           "/clone/enchase/rune18-3",
           "/clone/enchase/blugem4-1", }) : "/clone/enchase/rune19",

        ({ "/clone/enchase/rune19-1",
           "/clone/enchase/rune19-2",
           "/clone/enchase/rune19-3",
           "/inherit/template/gem/redgem4-1", }) : "/clone/enchase/rune20",

        ({ "/clone/enchase/rune19-1",
           "/clone/enchase/rune19-2",
           "/clone/enchase/rune19-3",
           "/clone/enchase/redgem4-1", }) : "/clone/enchase/rune20",
           
        ({ "/clone/enchase/rune20-1",
           "/clone/enchase/rune20-2",
           "/clone/enchase/rune20-3",
           "/inherit/template/gem/grngem4-1", }) : "/clone/enchase/rune21",

        ({ "/clone/enchase/rune20-1",
           "/clone/enchase/rune20-2",
           "/clone/enchase/rune20-3",
           "/clone/enchase/grngem4-1", }) : "/clone/enchase/rune21",

        ({ "/clone/enchase/rune21-1",
           "/clone/enchase/rune21-2",
           "/inherit/template/gem/skull4-1", }) : "/clone/enchase/rune22",

        ({ "/clone/enchase/rune21-1",
           "/clone/enchase/rune21-2",
           "/clone/enchase/skull4-1", }) : "/clone/enchase/rune22",
           
        ({ "/clone/enchase/rune22-1",
           "/clone/enchase/rune22-2",
           "/inherit/template/gem/yelgem5-1", }) : "/clone/enchase/rune23",

        ({ "/clone/enchase/rune22-1",
           "/clone/enchase/rune22-2",
           "/clone/enchase/yelgem5-1", }) : "/clone/enchase/rune23",
           
        ({ "/clone/enchase/rune23-1",
           "/clone/enchase/rune23-2",
           "/inherit/template/gem/maggem5-1", }) : "/clone/enchase/rune24",

        ({ "/clone/enchase/rune23-1",
           "/clone/enchase/rune23-2",
           "/clone/enchase/maggem5-1", }) : "/clone/enchase/rune24",
           
        ({ "/clone/enchase/rune24-1",
           "/clone/enchase/rune24-2",
           "/inherit/template/gem/blugem5-1", }) : "/clone/enchase/rune25",

        ({ "/clone/enchase/rune24-1",
           "/clone/enchase/rune24-2",
           "/clone/enchase/blugem5-1", }) : "/clone/enchase/rune25",
           
        ({ "/clone/enchase/rune25-1",
           "/clone/enchase/rune25-2",
           "/inherit/template/gem/redgem5-1", }) : "/clone/enchase/rune26",

        ({ "/clone/enchase/rune25-1",
           "/clone/enchase/rune25-2",
           "/clone/enchase/redgem5-1", }) : "/clone/enchase/rune26",

        ({ "/clone/enchase/rune26-1",
           "/clone/enchase/rune26-2",
           "/inherit/template/gem/grngem5-1", }) : "/clone/enchase/rune27",

        ({ "/clone/enchase/rune26-1",
           "/clone/enchase/rune26-2",
           "/clone/enchase/grngem5-1", }) : "/clone/enchase/rune27",
           
        ({ "/clone/enchase/rune27-1",
           "/clone/enchase/rune27-2",
           "/inherit/template/gem/skull5-1", }) : "/clone/enchase/rune28",

        ({ "/clone/enchase/rune27-1",
           "/clone/enchase/rune27-2",
           "/clone/enchase/skull5-1", }) : "/clone/enchase/rune28",
           
        ({ "/clone/enchase/rune28-1",
           "/clone/enchase/rune28-2",
           "/inherit/template/gem/yelgem6-1", }) : "/clone/enchase/rune29",

        ({ "/clone/enchase/rune28-1",
           "/clone/enchase/rune28-2",
           "/clone/enchase/yelgem6-1", }) : "/clone/enchase/rune29",

        ({ "/clone/enchase/rune29-1",
           "/clone/enchase/rune29-2",
           "/inherit/template/gem/maggem6-1", }) : "/clone/enchase/rune30",

        ({ "/clone/enchase/rune29-1",
           "/clone/enchase/rune29-2",
           "/clone/enchase/maggem6-1", }) : "/clone/enchase/rune30",
           
        ({ "/clone/enchase/rune30-1",
           "/clone/enchase/rune30-2",
           "/inherit/template/gem/blugem6-1", }) : "/clone/enchase/rune31",

        ({ "/clone/enchase/rune30-1",
           "/clone/enchase/rune30-2",
           "/clone/enchase/blugem6-1", }) : "/clone/enchase/rune31",
           
        ({ "/clone/enchase/rune31-1",
           "/clone/enchase/rune31-2",
           "/inherit/template/gem/redgem6-1", }) : "/clone/enchase/rune32",

        ({ "/clone/enchase/rune31-1",
           "/clone/enchase/rune31-2",
           "/clone/enchase/redgem6-1", }) : "/clone/enchase/rune32",
           
/*
        ({ "/clone/enchase/rune32-1",
           "/clone/enchase/rune32-2",
           "/inherit/template/gem/grngem6-1", }) : "/clone/enchase/rune33",

        ({ "/clone/enchase/rune32-1",
           "/clone/enchase/rune32-2",
           "/clone/enchase/grngem6-1", }) : "/clone/enchase/rune33",
*/
           
        // 乾坤圣水
        ({ "/clone/fam/gift/int3-1",
           "/clone/fam/gift/con3-1",
           "/clone/fam/gift/str3-1",
           "/clone/fam/gift/dex3-1" }) : "/clone/fam/item/bless_water",

        // 乾坤圣水
        ({ "/clone/fam/gift/int3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 乾坤圣水
        ({ "/clone/fam/gift/con3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 乾坤圣水
        ({ "/clone/fam/gift/dex3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 乾坤圣水
        ({ "/clone/fam/gift/str3-1",
           "/clone/fam/etc/lv7a-1",
           "/clone/fam/item/stone5-1" }) : "/clone/fam/item/bless_water",

        // 辉石
        ({ "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone4",

        // 皓石
        ({ "/clone/fam/item/stone2-1",
           "/clone/fam/item/stone1-1",
           }) : "/clone/fam/item/stone3",


        // 辉月华石
        ({ "/clone/fam/item/stone1-1",
           "/clone/fam/item/stone4-1",
           "/clone/fam/item/stone3-1",
           "/clone/fam/item/stone2-1",
           }) : "/clone/fam/item/stone5",


/*
        // 风洞之眼·风
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/yelgem7-1",
          "/clone/enchase/rune20-1",
           }) : "/clone/item/fengdong.c",

        // 神之寒晶·冰
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/grngem7-1",
          "/clone/enchase/rune21-1",
           }) : "/clone/item/hanjing",

        // 圣魔之心·魔
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/blugem7-1",
          "/clone/enchase/rune22-1",
           }) : "/clone/item/mozhixin",

        // 火之精灵·火
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/redgem7-1",
          "/clone/enchase/rune23-1",
           }) : "/clone/item/huojingling",

        // 雷神之瞳·电
       ({ "/inherit/template/gem/skull7-1",
          "/inherit/template/gem/maggem7-1",
          "/clone/enchase/rune24-1",
           }) : "/clone/item/leishentong",
*/
]);

int main(object me, string arg)
{
        mapping same;                   // 判断重复的物品的需要的mapping
        array item_list, name_list;  // 合并的物品ID表和匹配的基本名字表
        string bname;                   // 物品对应的文件的基本名字
        object *ob_list;                // 合并的所有物品
        array per;                    // mapping中记录的可合并的基本名字表
        object obj;                     // 生成的物品
        int mp, i;

        if (! arg)
                return notify_fail("你要合并什么物品？\n");

        if (me->is_busy())
                return notify_fail("先忙完了你的事情再做这件事情吧！\n");

        if (me->is_fighting())
                return notify_fail("你现在正在打架，没时间做这些事情。\n");

        if (me->query("max_jingli") < 300)
                return notify_fail("你现在的精力修为有限，无法合成物品。\n");

        if (me->query("jingli") < 300)
                return notify_fail("你现在精力不济，无法合成物品。\n");

        item_list = explode(arg, "&");
        ob_list   = allocate(sizeof(item_list));
        name_list = allocate(sizeof(item_list));
        same = allocate_mapping(sizeof(item_list));
        for (i = 0; i < sizeof(item_list); i++)
        {
                bname = item_list[i];
                if (! bname) return notify_fail("格式错误。\n");
                while (bname[0] == ' ') bname = bname[1..<0];
                while (bname[strlen(bname) - 1] == ' ') bname = bname[0..<2];
                ob_list[i] = present(bname, me);

                if (! objectp(ob_list[i]))
                        return notify_fail("你身上没有 " + bname + " 这种物品啊。\n");

                /*
                if (ob_list[i]->query("no_identify"))
                        return notify_fail("你身上的 " + bname + " 还没有去鉴定啊。\n");
                */

                if (i > 0 && member_array(ob_list[i], ob_list[0..i - 1]) != -1)
                        return notify_fail("合并物品需要指明不同的物品，不要重复指"
                                           "明一件物品。\n");

                bname = base_name(ob_list[i]);
                /*
                if (strsrch(bname, "/inherit/template/jewel/") >= 0)
                        sscanf(bname, "%s-%*s", bname);
                */
                if (undefinedp(same[bname]))
                        same[bname] = 1;
                else
                        same[bname]++;
                name_list[i] = bname + "-" + (string) same[bname];
        }

        tell_object(me, HIW "\n你双目微闭，将数样物品凝于掌中，运转内劲迫"
                        "使它们交融。\n" NOR);

        me->start_busy(1);
        me->add("jingli", -200);
        foreach (per in keys(combine_list))
        {
                if (per - name_list == ({ }) && sizeof(per) == sizeof(name_list))
                {
                        // 找到了合适的组合
                        obj = new(combine_list[per]);
                        for (i = 0; i < sizeof(ob_list); i++)
                        {
                                if (ob_list[i]->query_amount())
                                        ob_list[i]->add_amount(-1);
                                else
                                {
                                        /*
                                        if (strsrch(base_name(ob_list[i]), "/data/template/jewel/") >= 0)
                                                rm(base_name(ob_list[i]) + ".c");
                                        */
                                        destruct(ob_list[i]);
                                }
                        }
                        message("vision", HIW "\n霎时间只见" + me->name() + HIW "掌心一道"
                                          "光华闪过，但转瞬即逝，似乎发生了什么不同寻常的"
                                          "事情。\n\n" NOR, environment(me), ({me}));

                        tell_object(me, HIW "霎时间只见万道光华疾闪而过，你急忙摊开手掌，"
                                        "发现掌心\n豁然出现了一" + obj->query("unit") +
                                        obj->name() + HIW "，蕴漾着七色霞光。\n\n" NOR);

                        if (obj->query("value"))
                        {
                                mp = (int)(obj->query("value") / 700);
                                mp = 1 + random(mp);
                                if (mp < 1) mp = 1;
                                if (mp > 100) mp = 100;

                                me->add("magic_points", mp);
                                tell_object(me, HIC "你通过合成"+ obj->name() + HIC "的历"
                                                "练过程，从而获得了" + chinese_number(mp) +
                                                "点灵慧。\n" NOR);
                        }
                        me->add("max_jingli", -1);
                        obj->move(me, 1);
                        return 1;
                }
        }
        tell_object(me, HIR "可是过了半天，似乎没有任何变化，你不禁一声"
                        "长叹。\n" NOR);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : combine <特殊物品> & <特殊物品> & ……

这个指令可以让你将某些特殊物品合并成一种新的物品，哪些才能合
并？这就要靠你去发掘了。每次合并都会损失一点精力的上限。如果
要合并的几个物品名字相同，则需要指明他们的序号，比如有三个钻
石，如果要合一，则需要输入：

  combine diamond & diamond 2 & diamond 3

HELP);
        return 1;
}
