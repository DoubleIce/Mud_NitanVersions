inherit ROOM;

string* books = ({
        "/clone/book/mizong_book",
        "/clone/book/skin",
        "/clone/book/book-bamboo",
        "/clone/book/book-silk",
        "/clone/book/book-stone",
        "/clone/book/book-iron",
        "/clone/book/skin-hammer",
});
void create()
{
        set("short", "�ؾ���");
        set("long", @LONG
�����Ǵ����µĲؾ��ң���ǽ��һ����ܣ������˸���ȭ�ס���
��������ǵ����������Ħ�Ƿ���ķ𾭺ʹ�������ȡ������ѧ�伮��
LONG );
        set("exits", ([
                "north" : __DIR__"dating",
        ]));

        set("objects", ([
                books[random(sizeof(books))] : 1,
                books[random(sizeof(books))] : 1,
                books[random(sizeof(books))] : 1,
                CLASS_D("xueshan")+"/daerba" : 1,
        ]));
        setup();
        replace_program(ROOM);
}