varargs string format_string(string str, int wrap, int ignore_return)
{
    string tmp = "";
    int len= 0, ansi = 0, clen = 0;   // clen ���ѳ��ֵĺ��ָ�����
    if (!str || !stringp(str))
        return 0;
    if (!wrap)
        wrap = 66;
    foreach ( int ch in str )
    {
        if ( ch == '\n' && ignore_return)       // return char
            continue;           // ignore it.
        tmp += sprintf("%c", ch);
        if ( ch == 0x1b )       // esc char
        {
            ansi = 1;
        }
        if ( !ansi )
        {
            len ++;
            if (ch > 127)
                clen ++;
//        printf("ch %c clen: %d len %d ch=%d\n", ch, clen,len,ch);
        }
        else if ( ch == 'm' || ch == 'H' || ch == 'J' )
        {
            ansi = 0;
        }
        if ( len >= wrap )
            if ( ( ! (clen%2) ) || ( ch == ' ' ) )
        {
//            printf("str: %s ch %c clen: %d len %d ch=%d\n", tmp, ch, clen,len,ch);
            tmp += "\n";
            wrap = 70;
            len = 0;
        }
    }
    return tmp + "\n";
}
