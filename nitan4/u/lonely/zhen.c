string *zhen1 = ({"��ͨ��","������","��ʸ��","������","������","��Բ��","������","������","������"});
mapping zhen2 = ([
        "��ͨ��" : ({  0,  -5,   5,  -5,   5,  -5,   5,  -5,   5 }),
        "������" : ({  5,   0,  10,  10,  -5,  10,  -5,   5, -10 }),
        "��ʸ��" : ({ -5, -10,   0,  10,   5,  -5,  10, -10,   5 }),
        "������" : ({  5,  10, -10,   0,  -5,  -5, -10,  10,   5 }),
        "������" : ({ -5,   5,  -5,   5,   0, -10, -10,  10,  10 }),
        "��Բ��" : ({  5, -10,   5,   5,  10,   0,  -5,  -5,  -5 }),
        "������" : ({ -5,   5, -10,  10,  10,   5,   0, -10,  -5 }),
        "������" : ({  5,  -5,  10, -10, -10,   5,  10,   0,  -5 }),
        "������" : ({ -5,  10,  -5,  -5, -10,   5,   5,   5,   0 }),
]);

void zhen_power(string type1, string type2)
{
        int i, type2_i;

        for (i = 0; i < sizeof(zhen1); i++)
        {
                if (type2 == zhen1[i])
                {
                        type2_i = i;
                        break;
                }
        }

        return zhen2[type1][type2_i];

}
