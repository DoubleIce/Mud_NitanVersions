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

    // 给第一个开关分配的灯
    for(i1 = 0; i1 < MAX; i1++) 
    {
        a = i1;

        // 给第二个开关分配的灯
        for(i2 = 0; i2 < MAX; i2++) 
        {
            b = i2;

            // 给第三个开关分配的灯
            for(i3 = 0; i3 < MAX; i3++) 
            {
                c = i3;

                // 给第四个开关分配的灯
                for(i4 = 0; i4 < MAX; i4++) 
                {
                    d = i4;

                    // 测试这个分配方法能否满足条件
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
                    // 有一个方法可以全开
                    count++;

                if (count > 1)
                    // 超过一种方法可以全开，不符合
                    return;
            }
        }
    }

    if (turns[0] ^ turns[1] ^ turns[2] ^ turns[3] != MAX)
        // 指定方法不能全开
        return;

    // 找到方法了，答应结果
    printf("result is %O\n", turns);
}

