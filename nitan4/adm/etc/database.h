// database.h

// 是否采用永久连接
#define STATIC_LINK
// 是否调试状态
// #define DEBUG
// 是否允许分站新玩家注册
// #define REFUSE_NEW_PLAYER

protected mapping all_others_db = ([
        // "61.184.100.7" : "nitan.dx",
]);

protected mapping stations = ([
        "218.89.171.162" : "《泥潭·总站》",
        "61.184.100.7"   : "《泥潭·电信》",
        "202.110.119.87" : "《泥潭·网通》",
        "219.134.89.94"  : "《泥潭·深圳》",
]);

#ifndef DATABASE
nosave string DATABASE               = "mud";
#endif
#ifndef DB_USER
nosave string DB_USER                = "lonely";
#endif
nosave string USER_TABLE             = "users";
nosave string IP_TABLE               = "ip";
nosave string NEWS_TABLE             = "news";
nosave string ITEM_TABLE             = "item";
nosave string MEMBER_TABLE           = "members";

// 采用的加密算法
nosave string DB_CRYPT               = "PASSWORD";
