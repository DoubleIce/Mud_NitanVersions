inherit ROOM;

void create()
{
          set("short", "�ɿ�����ɽ");
        set("long", @LONG
�ɿ�����ɽ�ֳƿɿ�ϡ��ɽ���ɹ�����Ϊ����ɽ������˼������
ľ������壬���Ӱ��տ���ɽ��ɽ��ƽ���������㲼���ߴ���������
��ѩ��������������е�ˮ��������⣬�����ϱ������岼�ĺ�����
Ϊ��ˮ������ľϡ�裬���̼��١�
LONG );
         set("exits",([
                "northwest" : __DIR__"shankou",
                "east" : __DIR__"bayankala",
         ]));
         set("outdoors", "kunlun");
         setup();
         replace_program(ROOM);    
}
