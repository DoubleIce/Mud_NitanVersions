// database.h

// �Ƿ������������
#define STATIC_LINK
// �Ƿ����״̬
// #define DEBUG
// �Ƿ������վ�����ע��
// #define REFUSE_NEW_PLAYER

protected mapping all_others_db = ([
        // "61.184.100.7" : "nitan.dx",
]);

protected mapping stations = ([
        "218.89.171.162" : "����̶����վ��",
        "61.184.100.7"   : "����̶�����š�",
        "202.110.119.87" : "����̶����ͨ��",
        "219.134.89.94"  : "����̶�����ڡ�",
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

// ���õļ����㷨
nosave string DB_CRYPT               = "PASSWORD";
