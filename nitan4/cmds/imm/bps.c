/*
 * bps.c
 *
 * query_bandwide() 返回值为 float *
        0 为 到来数据
        1 为 发送出去的数据
*/

inherit F_CLEAN_UP;

int main(object me)
{
        float *bps;
        string out;

        bps = query_bandwide();

        out = sprintf("端口进入数据流量：%.2f K/秒，送出流量：%.2f K/秒\n",bps[0]*8/1000, bps[1]*8/1000);
        write(out);
        return 1;
}

