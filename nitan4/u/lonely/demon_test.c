#define L1          0x000001
#define L2          0x000002
#define L3          0x000004
#define L4          0x000008
#define L5          0x000010
#define L6          0x000020

#define MAX         L1 | L2 | L3 | L4 | L5 | L6

protected void test_result(array turns);

public void start()
{
    int a, b, c, d;
    int i1, i2, i3, i4;

    // ����һ�����ط���ĵ�
    for(i1 = 0; i1 < MAX; i1++) 
    {
        a = i1;

        // ���ڶ������ط���ĵ�
        for(i2 = 0; i2 < MAX; i2++) 
        {
            b = i2;

            // �����������ط���ĵ�
            for(i3 = 0; i3 < MAX; i3++) 
            {
                c = i3;

                // �����ĸ����ط���ĵ�
                for(i4 = 0; i4 < MAX; i4++) 
                {
                    d = i4;

                    // ����������䷽���ܷ���������
reset_eval_cost(); 
                    test_result(({ a, b, c, d }));
                }
            }
        }
    }
}

private void test_result(array turns)
{
    int t1, t2, t3;
    int count = 0;

    foreach(t1 in turns)
    {
        foreach(t2 in turns - ({ t1 }))
        {
            foreach(t3 in turns - ({ t1,t2 }))
            {
                if (t1 ^ t2 ^ t3 ^ (turns - ({ t1, t2, t3}))[0] == MAX)
                    // ��һ����������ȫ��
                    count++;

                if (count > 1)
                    // ����һ�ַ�������ȫ����������
                    return;
            }
        }
    }

    if (turns[0] ^ turns[1] ^ turns[2] ^ turns[3] != MAX)
        // ָ����������ȫ��
        return;

    // �ҵ������ˣ���Ӧ���
    printf("result is %O\n", turns);
}

