// houhuayuan.c ��Է

inherit ROOM;

void create()
{
        set("short", "��Է");
        set("long", @LONG
�����ǻ����ͻ��ĺ�Է��ƽ�������ʱ������������͹�����
��һ���ͻ�Ʒ�������ԣ������ƽ��̫�࣬�����������ġ�����Ĺ�
Ů�����������ɣ���ͨ�����ġ������Ĺˣ���Ŀ�����ƽ�����������
ϸ�ֱ棬��ȻƷĿ��ȫ��������õģ��������붼������ģ�����
�����ˡ��㲻����Щ�ʼ���ʵ��϶�����
LONG );
        set("outdoors", "huanggon");
        set("exits", ([
                "west" : __DIR__"houhuayuan2",
                "south" : __DIR__"qihedian",
        ]) );
        set("objects", ([
                "/d/huanggon/npc/gonnv" : 2,
        ]) );
        setup();
        replace_program(ROOM);
}
