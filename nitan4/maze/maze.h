#include <ansi.h>
mapping *mazes = ({ 
              ([      "name":         HIG"原始森林"NOR,
                                 "code":         "forest",
                "len":               10,     
                "lvl":                      1,
                "outdoor":            1,
                "time":               3600,
        ]),
        ([      "name":         HIW"神秘冰窟"NOR,
                                "code":         "icecave",
                "len":               6,
                "lvl":                      2,
                "outdoor":            0,
                "time":               900,
        ]),
        ([      "name":         CYN"诡异洞穴"NOR,
                                "code":         "darkhole",
                "len":               6,
                "lvl":                      3,
                "outdoor":            0,
                "time":               1200,
        ]),
        ([      "name":         WHT"无尽大漠"NOR,
                                "code":         "desert",
                "len":               6,
                "lvl":                      4,
                "outdoor":            1,
                "time":               1200,
        ]),
        ([      "name":         HIY"失落神庙"NOR,
                                "code":         "temple",
                "len":               6,
                "lvl":                      5,
                "outdoor":            0,
                "time":               1500,
        ]),
        ([      "name":         RED"墓园"NOR,
                                "code":         "necropolis",
                "len":               7,
                "lvl":                      6,
                "outdoor":            1,
                "time":               5400,
        ]),
});
mapping maze_desc = ([
"forest" :
"原始森林树叶苍黑如盖，遮天蔽日，林中弥漫着枯叶腐烂
和树脂混合的味道，地上的苔鲜落叶踩上去软绵绵的，上面还
布满野兽的痕迹，四周浓密的山雾，让人难以分辨方向。",
"icecave" :
"冰窟内温度极低，四面都是厚厚的冰层，地面很滑，虽然
没有任何阳光透入，但冰笋，冰墙反射的出的寒光让冰窟里的
东西一清二楚，再往里面走，即便不遇上什么怪物，寒冷的空
气足可以把任何人冻僵。",
"darkhole" :
"洞穴很暗，几乎伸手不见五指，地上很滑，偶尔有些小动
物的叫声，蝙蝠突然掠过，你总觉得四周有一双诡异的眼睛盯
着你，一股股寒意从心里冒出，你总想往身后看，但却十分害
怕，只能不断的往前走。",
"desert" :
"一望无际的大漠，烈日、风沙、苦寒、酷热，无时不在折
磨着每一个人，在这里，如果你没有饮水，很有可能就会被晒
死，沙子滚烫，足以把脚烫烂，一到晚上，却又冰冷得透骨。",
"temple" :
"神庙很大，柱子上雕刻着千奇百怪的动物，有的人身上却
长着一颗狼头，人身上生出一双翅膀，怪异的怪首的雕刻让人
叹为观止，庙顶成八角，屋脊曲线柔美,泥塑,剪黏,木雕,彩绘
皆为上品。",
"necropolis" :
"墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。",
]);
