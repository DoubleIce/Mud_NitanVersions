/*****************************************************************************\
**                                                                           **
**  p9.c  赌牌九  系统做庄 & 玩家互动 综合版                                 **
**        可赌大、小牌九，可由系统做庄或玩家做庄，最高可 8 人同局            **
**  by naihe 2004-3~4 广东茂名  玩玩而已啦……                               **
**                                                                           **
**  写的时候参看了 p9room.c (by kafei)，发现难以理解，其规律是？其规则是？   **
**  奈何十分羞愧，想来自己技术甚低，竟无法得到任何借鉴。于是用我自己的方式， **
**  用这个容易理解的、粗浅显露的方式去写。                                   **
**  当然，以这个方式写的，需要修改规则、名字时，竟也变得十分的简单了；而让   **
**  我欣慰的是，核心部分的代码居然并不是想象中的那么长。而整个游戏写得很是   **
**  繁琐，却是写之前所料不到的了！                                           **
**                                                                           **
**  P.S:                                                                     **
**  规则及名字等，根据个人经验、网上资料等来源而定，如有谬误，请自行更正！   **
**  最好来信告知奈何： lovesb@21cn.com  ||  lonely@163.com(请先通知)         **
**                QQ:  107507                                                **
**                                                                           **
**  zmud 字体： 宋体 小四(12)/小五(10)                                       **
**                                                                           **
**  关于本游戏的奖励 / 赌注：                                                **
**      由于在许多历史悠久的MUD里，金钱已泛滥成灾，甚至连exp等，             **
**      也已经不再是玩家们热衷追求的了。所以这个赌博游戏的赌注               **
**      十分特别，不使用传统的赌金赌银之类的旧法，而采用了                   **
**      “积分奖励”的方式——各MUD自己定下积分兑换的规则，而                **
**      这个游戏本身，无论是系统做庄，或是玩家互动的游戏，都只               **
**      是以“积分”进行。                                                   **
**      请参照 GAME_SCORE_DATA 的定义，自行建立文件（例如房间啦NPC啦cmds啦） **
**      来进行兑换的手续。而不得不提的是，这个值的默认定义是:                **
**              "naihe_game_data/game_score"                                 **
**      很明显，奈何已写的和将写的各类乱78糟小游戏，都将沿用这个规范。       **
**      当然，你也可以将这个值改为“balance”之类的，也就直接以存款进行了！  **
**                                                                           **
**       赌牌九，中国人的赌技，运气与实力的双重考验！(小牌九好无聊……)      **
**                                                                           **
\*****************************************************************************/

// 晕，无聊地画了个框子之后，居然看起来舒服多了！ :)
// 没有 ctime_new() 函数的MUD，请取消下一行的注释：
// string ctime_new() { return ctime(time()); }

#include <ansi.h>

// ------------------------------ 可更改之设置 ------------------------------

#define		GAME_ON			1		// 游戏是否开放
#define		GAME_NAME		"赌牌九 综合版"	// 本游戏名称
#define		GAME_VERSION		"V1.5"		// 版本，方便自己查看
#define		LOG_ON			1		// 是否 log
#define		LOG_FILE_NAME		"p9_log"	// log 文件位置

#define		GAME_SCORE_DATA		"naihe_game_data/game_score"
							// 积分记录于玩家 dbase 里
#define		GAME_SCORE_NAME		"游戏点"	// 名字
#define		BET_MIN			1		// 最小押注
#define		BET_MAX			1000		// 最大押注
#define		WAIT_TIME_JOIN		20		// 游戏准备开始，等待一定时间接受玩家加入
#define		WAIT_TIME_LINEUP	90		// 大牌九时，给一定的时间给玩家将牌排列（分组）
#define		WAIT_TIME_NEXTPAIR	15		// 大牌九时，一定时间后比下门的牌
#define		SYSTEM_SCORE		99999		// 系统积分，输光了之后，强制停止由系统开庄的赌局
							// 因为，概率问题难以具体确定，如果由于现有的设置不当，
							//     而导致总是会让玩家大量赢得积分，那么此时就需要
							//     强制停止由系统开庄，以避免越错越深。
							// 这个值可以设置 0 ，即系统不开庄，仅由玩家互动游戏。
							// 这个机制是由 dvunix(211.91.166.197:2008) 提出意见增加的。

#define		IsTest			0		// 1 测试状态，各环节时间紧凑些，某些地方报告一下，
							// 及 "naihe" 启动赌局时不作上次启动时间的限制
#define		ChannelColor		HIM		// 频道颜色，随意
#define		StartGameBusy		60

// --------------------------------------------------------------------------



// 真正的中文格式 ctime()，而不是什么 Sun Apr 27 00:44:44 2003 之类
// 的 ctime() ........ 永远弄不清英文星期、月份大白痴 奈何 ，献给
// 所有同此类者 ............

// by naihe 2003-04-29
// 改变了一下参数的含义，与以前的无法兼容……tnnd
// by naihe 2004-03-24

string ctime_new( int arguments, int type )
{
        string msg, *temp;
        mapping to_cn_month, to_cn_week;
        int temp_xxx;

        to_cn_month = ([ "Jan":" 1月", "Feb":" 2月", "Mar":" 3月", "Apr":" 4月",
                         "May":" 5月", "Jun":" 6月", "Jul":" 7月", "Aug":" 8月", 
                         "Sep":" 9月", "Oct":"10月", "Nov":"11月", "Dec":"12月", ]);

        to_cn_week = ([ "Mon":"星期一", "Tue":"星期二", "Wed":"星期三", "Thu":"星期四",
                        "Fri":"星期五", "Sat":"星期六", "Sun":"星期日", ]);

// 1，无参数
// 2，指定单一参数，该参数为时间参数    例如： ctime_new(1058076012);
// 3，双参数，顺序正确                  例如： ctime_new(1058076012, 1);

// 上述3个情况是正确的。下面的情况，需要进行纠错：

// 4，指定单一参数，该参数为信息形式的参数      例如：ctime_new(1); ctime_new(2); 等
//    纠正为： 时间采用当前时间，形式采用指定的形式
// 5，双参数，顺序不正确                例如： ctime_new(1,1058076012); ctime_new(0,1058076012);
//    之前我写的 ctime_new.c 就是这个格式的，所以……为当初的考虑不周悲哀中
//    纠正为：位置互换


// 无参数的时候，默认当前时间，返回完整信息字串
        if( !type && !arguments )
        {
                arguments = time();
                type = 8;
        }
// 强力纠错功能 // add by naihe 2003-07-13

// 当时间参数没有，或者它是个很小的数字，那么，意味着参数出现了错误了。
        if( !arguments || arguments < 3153600 )  // 这个数字是一年的大概秒数……
        {
                if( !type || type < 3153600 )  // 这就是  4  的情况。纠正，OK :)
                {
                        type = arguments;
                        arguments = time();
                }
                else            // 否则，只可能是位置互换了。 纠正，OK :)
                {
                        temp_xxx = type;
                        type = arguments;
                        arguments = temp_xxx;
                }
        }

// 这个是强制参数，否则会报BUG……我宁愿它别报BUG。
        if( !arguments ) arguments = time();

        msg = efun::ctime( arguments );
        if( !msg ) return 0;

        temp = explode( msg , " ");

// 这个地方原来绝想不到……有的地方的 ctime(time()) return
// 的东西格式不对，如果是单日例如 1日，2日，会多出一个空格
// 来。那么， explode 之后，就得到 sizeof() = 6 的 array！
// 而我的机器上，ctime(time()) 在这种情况，会加为： 01, 02
// 等。晕吧？
// 为了安全安全再安全，决定添多一个元素，即连 " " 都删掉！

        temp -= ({ "", " " });

        if( sizeof( temp ) != 5 ) return 0;

        switch( type )
        {
// 日期及时刻		"2003年 4月30日 01:50:56"

                case 1 : return sprintf("%s年%s%s日 %s",
        temp[4], to_cn_month[ temp[1] ], temp[2], temp[3] );

// 仅日期		"2003年 4月30日"

                case 2 : return sprintf("%s年%s%s日",
        temp[4], to_cn_month[ temp[1] ], temp[2] );

// 日期及星期		"2003年 4月30日 星期三"

                case 3 : return sprintf("%s年%s%s日 %s",
        temp[4], to_cn_month[ temp[1] ], temp[2], to_cn_week[ temp[0] ] );
        }

// 参数有误，或省略了该参数的话，返回完整信息
//      "2003年 4月30日 01:50:56 星期三"

        return sprintf("%s年%s%s日 %s %s", temp[4], to_cn_month[ temp[1] ],
                         temp[2], temp[3], to_cn_week[ temp[0] ] );
}

int system_score;	// 一个简单的避免因设置不当而导致恶劣后果的机制。

protected void game_log( string msg )
{
	if( !LOG_ON || !msg )
		return;

	log_file( LOG_FILE_NAME, msg );
}

void create()
{
        /*
	game_log( sprintf(
	"\n--------------------------------------------------------------------------------------------\n"
        "    牌九赌局文件于被载入，恢复预设系统积分 %d 点。\n"
	"--------------------------------------------------------------------------------------------\n",
                SYSTEM_SCORE ));
        */
	system_score = SYSTEM_SCORE;
}

varargs int help()
{
	string msg;

	msg = "--------------------------------------------------------
"BGRN+HIY"                    [ 牌 九 介 绍 ]　　　　　　　　　　 "NOR"
--------------------------------------------------------

    牌九是源自中国的古老游戏，也许由于其外形质感，牌九也
俗称“骨牌”。其规则较难解释，但它是一种十分需要讲究技巧
及心理战术的赌博游戏。总的来说，一副牌九共有 32 个牌，有
大小级别之分；而在习俗上，这 32 个牌又被分为两个大类，一
类“文子”，一类“武子”。\n";

	msg += "
    文子共 11 对，每对 2 个，按大小排列如下： 
"HIY"天、地、人、和、梅花、长衫、板凳、斧头、红头、幺六、幺五"NOR"

    武子比文子小，共 4 对及两个特殊牌，按大小排列如下：
"HIY"杂九、杂八、杂七、六头、杂五、三鸡"NOR"

    “杂”字的子各一对，而 [六头] 和 [三鸡] 是特殊的对子，
下文另述。而这些名称叫法，各地有所不同，为了方便，这里仅
采用如上所述的名称。您可以输入指令：<"HIY"p9 showcards"NOR">  查看
所有的图案示范。\n";

	msg += "
    赌牌九时，以两张牌（一组）为基本单位，庄闲之间相互比
较而定输赢。这两张牌可能可以组成一些“对子”，亦可能毫无
联系；当然，能组成“对子”的一组牌要比不能组成的“散牌”
大。但若双方的牌都是“散牌”，则各自将两张牌上的点数相加，
再取总数之和的个位数相比较，大者为胜。\n";

	msg += "
    对子由大到小排列如下：
"HIY"至尊宝"NOR"  --------   [六头] + [三鸡]
"HIY"双天宝"NOR"  --------   两个 [天] （下同，略）
"HIY"双地宝、双人宝、双和宝、梅花对、长衫对、板凳对、斧头对、
"HIY"红头对、幺六对、幺五对、杂九对、杂八对、杂七对、杂五对、
"HIY"天王"NOR"    --------   [天]   + [杂九]
"HIY"地王"NOR"    --------   [地]   + [杂九]
"HIY"天杠"NOR"    --------   [天]   + [人] 或 [杂八]
"HIY"地杠"NOR"    --------   [地]   + [人] 或 [杂八]\n"NOR;

	msg += "
    如果两个牌组不成上述的任意一对，算作“散牌”。散牌最
大是九点，最小是零点——俗称“憋十”。又，如果双方的牌的
对子同样或是点数同样，则比较其最大的一张牌；若最大牌同样，
则继续比较剩下的一张牌；若还是同样，则庄家胜。例如：

天+板凳  比  地+板凳  ：  都是 六点，前者 [天]   大，胜。
天+幺六  比  天+杂七  ：  都是 九点，前者 [幺六] 大，胜。
天+人    比  天+杂八  ：  都是 天杠，前者 [人]   大，胜。
天+人    比  天+人    ：  完全一样， 庄家胜。\n";

	msg += "
    赌牌九有两种俗定的玩法，一“大牌九”，一“小牌九”。
赌的是“大牌九”的时候，每家取四张牌，可以随自己的心意将
其分为两组，称作“上门”、“下门”，开牌后先后比较，两门
皆胜者赢得该局。赌“大牌九”可能出现一门牌胜、一门牌负的
情形，即和局。
    而赌“小牌九”时又不同，每家只取两张牌，不必分组，一
开牌就见胜负。小牌九又俗称“一翻两瞪眼”，就是取其完全不
由自己控制，全凭运气的意思。并且小牌九绝无和局，所以也
格外的刺激。\n";

	msg += sprintf(
"--------------------------------------------------------
"BGRN+HIY"         [ %s(%s) 本游戏介绍 ]             "NOR"
--------------------------------------------------------\n", GAME_NAME, GAME_VERSION);

	msg += "
    这个游戏可以让玩家们进行如同真正的牌九赌局。根据您个
人的喜好，您可以选择自己做庄、或由电脑做庄；亦可以选择赌
大牌九或小牌九；如果您要做庄的话，还可以设置接受赌注的额
度、设置参与人数的限制等等。这一切，都可以在输入了游戏开
始的指令：<"HIY"p9 new"NOR">之后，获得详细的提示说明，您只要根据提
示简单地进行一些设置，就可以轻松地开始赌局了。

    游戏的详细指令介绍，您可以输入：<"HIY"p9 help cmds"NOR"> 查询。
    这个游戏会公布一些公开的信息，如果您觉得厌烦，请输入：
      <"HIY"p9 set no_p9_msg"NOR">  那么您将不会再接到这些信息。

                                 By 奈何(naihe) 2004-04
--------------------------------------------------------\n";

	this_player()->start_more( msg );

	write( "
    赌牌九 游戏流程图

   ┌ <- - - - -<- - - - -<- - - - -<- - - - -  ┐
   │                                           ↑
   ↓                          ┌> 没有玩家加入 ┘
 无赌局 -> 开始 -> 等待玩家加入┤                          ┌> 大牌九：玩家将牌分成两组┐
   ↑                          └> 有玩家加入 -> 开始，发牌┤                          ↓
   │                                                      └> 小牌九：┐              │
   │                                                                  ↓              ↓
   └ <- - - - -<- - - - -<- - - - -<- - - - -<- - - - -<- -  与庄比大小及计算得分 ←─┘\n");

	return 1;
}

// ###################################################################
//      ################### 牌 九 核 心 部 分 ###################
//          #################################################

// 下面这些值都应该用 #define 的，不过 #define 值不能换行，看起来乱，就算了。
// 但是名字还是用大写~

	// 整副牌的基本顺序，如需更改，必须更改下面所有变量的相应位置、值等
string		*P9_BASE = ({
	"tian1","tian2","di1","di2","ren1","ren2","he1","he2", 
	"mh1","mh2","cs1","cs2","bd1","bd2","ft1","ft2",
	"ht1","ht2","161","162","151","152", 
	"91","92","81","82","71","72","6","51","52","3",
	});

	// 每张牌单张时的名称，顺序需与 P9_BASE 对应
string		*P9_NAME = ({
	"天", "天", "地", "地", "人", "人", "和", "和",
	"梅花", "梅花", "长衫", "长衫", "板凳", "板凳", "斧头", "斧头",
	"红头", "红头", "幺六", "幺六", "幺五", "幺五",
	 "杂九", "杂九", "杂八", "杂八", "杂七", "杂七", "六头", "杂五", "杂五", "三鸡",
	});

	// 每张牌上的点数，顺序需与 P9_BASE 对应
int		*P9_AMOUNT = ({
	12, 12, 2, 2, 8, 8, 4, 4,
	10, 10, 6, 6, 4, 4, 11, 11,
	10, 10, 7, 7, 6, 6, 
	9, 9, 8, 8, 7, 7, 6, 5, 5, 3,
	});

	// 每张牌的大小判断值，及成对时的判断值，顺序需与 P9_BASE 对应
	// 也就是说，如果需要更改某种对子、或某子的大小，在此对应更改即可
int		*P9_VALUE = ({
	99, 99, 88, 88, 77, 77, 66, 66,
	49, 49, 48, 48, 47, 47, 46, 46,
	45, 45, 44, 44, 43, 43,
	39, 39, 38, 38, 37, 37, 36, 35, 35, 34,
	});

	// 特殊对子的大小判断值
	// 更改特殊对子的判断，请参看 get_value() 函数
mapping		SPECIAL_VALUE = ([
	"TianWang"	: 10,
	"DiWang"	: 9,
	"TianGang"	: 8,
	"DiGang"	: 7,
	]);

	// 对子的名称，key 需与 P9_VALUE 对应
mapping		PAIR_NAME = ([
	999:"至尊宝", 99:"双天宝", 88:"双地宝", 77:"双人宝", 66:"双和宝",
	49:"梅花对", 48:"长衫对", 47:"板凳对", 46:"斧头对",
	45:"红头对", 44:"幺六对", 43:"幺五对",
	39:"杂九对", 38:"杂八对", 37:"杂七对",
	36:"出错了，没有两个六作对", 35:"杂五对", 34:"出错了，没有两个三作对",

	//===== 特殊对子的 key 需与 SPECIAL_VALUE 同步 =====//
	10:"天王", 9:"地王", 8:"天杠", 7:"地杠",
	]);

	// key 需与 P9_BASE 元素对应，顺序不限
mapping		P9_PIC = ([
	"none"	: ({ "      "," /    ","      ","      ","    / ","      ", }),
// 文子图案
	"tian1" : ({ "●  ○","●  ○","●  ○","○  ●","○  ●","○  ●", }),
	"tian2" : ({ "○  ●","○  ●","○  ●","●  ○","●  ○","●  ○", }),
	"di1"	: ({ "  ●  ","      ","      ","      ","      ","  ●  ", }),
	"di2"	: ({ "  ●  ","      ","      ","      ","      ","  ●  ", }),
	"ren1"	: ({ "      ","●  ●","●  ●","●  ●","●  ●","      ", }),
	"ren2"	: ({ "      ","●  ●","●  ●","●  ●","●  ●","      ", }),
	"he1"	: ({ "  ●  ","      ","      ","    ○","  ○  ","○    ", }),
	"he2"	: ({ "  ●  ","      ","      ","    ○","  ○  ","○    ", }),
	"mh1"	: ({ "○  ○","  ○  ","○  ○","○  ○","  ○  ","○  ○", }),
	"mh2"	: ({ "○  ○","  ○  ","○  ○","○  ○","  ○  ","○  ○", }),
	"cs1"	: ({ "      ","  ○  ","  ○  ","○  ○","  ○  ","  ○  ", }),
	"cs2"	: ({ "      ","  ○  ","  ○  ","○  ○","  ○  ","  ○  ", }),
	"bd1"	: ({ "○  ○","      ","      ","      ","      ","○  ○", }),
	"bd2"	: ({ "○  ○","      ","      ","      ","      ","○  ○", }),
	"ft1"	: ({ "○  ○","  ○  ","○  ○","○  ○","○  ○","○  ○", }),
	"ft2"	: ({ "○  ○","  ○  ","○  ○","○  ○","○  ○","○  ○", }),
	"ht1"	: ({ "●  ●","●  ●","      ","○  ○","○  ○","○  ○", }),
	"ht2"	: ({ "●  ●","●  ●","      ","○  ○","○  ○","○  ○", }),
	"161"	: ({ "  ●  ","      ","      ","○  ○","○  ○","○  ○", }),
	"162"	: ({ "  ●  ","      ","      ","○  ○","○  ○","○  ○", }),
	"151"	: ({ "  ●  ","      ","      ","○  ○","  ○  ","○  ○", }),
	"152"	: ({ "  ●  ","      ","      ","○  ○","  ○  ","○  ○", }),
// 武子图案
	"91"	: ({ "    ○","  ○  ","○    ","○  ○","○  ○","○  ○", }),
	"92"	: ({ "●  ●","●  ●","      ","○  ○","  ○  ","○  ○", }),
	"81"	: ({ "    ○","  ○  ","○    ","○  ○","  ○  ","○  ○", }),
	"82"	: ({ "○  ○","      ","      ","○  ○","○  ○","○  ○", }),
	"71"	: ({ "○  ○","      ","      ","○  ○","  ○  ","○  ○", }),
	"72"	: ({ "    ○","  ○  ","○    ","●  ●","      ","●  ●", }),
	"6"	: ({ "○  ○","      ","      ","●  ●","      ","●  ●", }),
	"51"	: ({ "○  ○","      ","      ","    ○","  ○  ","○    ", }),
	"52"	: ({ "  ●  ","      ","      ","●  ●","      ","●  ●", }),
	"3"	: ({ "  ●  ","      ","      ","      ","      ","○  ○", }),
	]);

// ---------------------------------------------------------------------------------

// 组成牌九核心系统的函数
protected int			*get_value( string p1, string p2 );
protected string			get_cname( int *v );
protected int			which_one_is_bigger( int *v1, int *v2 );
protected varargs string		get_pic( array card, int type, int need_name );
protected string			*get_random_all_cards();
protected varargs string		get_show_all_msg( array v, int need_name );
protected string			*lineup( array p );
protected string			*system_AI( array p );


// 传入两张牌，返回它们的“价值”（即判断大小的依据）
protected int *get_value( string p1, string p2 )
{
	int	pair_value, amount_value, big_value, small_value,
		p1_value, p2_value, p1_amount, p2_amount, t1, t2;

	// 返回： int*
	// ({ 对子的价值，加起来的点数，大牌的价值，小牌的价值 })

	t1 = member_array( p1, P9_BASE );	// 获得 p1 在 P9_BASE 里的位置
	t2 = member_array( p2, P9_BASE );	// p2

	if( t1 == -1 || t2 == -1 )
		return 0;			// 发生意外错误

	p1_value = P9_VALUE[ t1 ];		// 第一张牌的价值
	p2_value = P9_VALUE[ t2 ];		// 第二张牌的价值

	if( p1_value > p2_value )
	{
		big_value = p1_value;
		small_value = p2_value;
	}
	else
	{
		big_value = p2_value;
		small_value = p1_value;
	}

	p1_amount = P9_AMOUNT[ t1 ];
	p2_amount = P9_AMOUNT[ t2 ];

	amount_value = (p1_amount + p2_amount) % 10;

	// 计算作为对子的价值

	// 至尊
	if( (p1 == "3" && p2 == "6") || (p2 == "3" && p1 == "6") )
		pair_value = 999;

	// 两者价值是同样的对子
	if( p1_value == p2_value )
		pair_value = p1_value;

	// 不是的话，是否特殊情况
	if( !pair_value )
	{
		// 特殊：天王
		if( (p1_amount == 12 && p2_amount == 9 )
		 || (p2_amount == 12 && p1_amount == 9 ) )
			pair_value = SPECIAL_VALUE[ "TianWang" ];
		// 特殊：地王
		if( (p1_amount == 2 && p2_amount == 9 )
		 || (p2_amount == 2 && p1_amount == 9 ) )
			pair_value = SPECIAL_VALUE[ "DiWang" ];
		// 特殊：天杠
		if( (p1_amount == 12 && p2_amount == 8 )
		 || (p2_amount == 12 && p1_amount == 8 ) )
			pair_value = SPECIAL_VALUE[ "TianGang" ];
		// 特殊：地杠
		if( (p1_amount == 2 && p2_amount == 8 )
		 || (p2_amount == 2 && p1_amount == 8 ) )
			pair_value = SPECIAL_VALUE[ "DiGang" ];
	}
	return ({ pair_value, amount_value, big_value, small_value, });
}

// 传入 get_value() 返回的值，取得这两张牌的称呼
protected string get_cname( int *v )
{
	if( !v || sizeof(v) != 4 )
		return "----";

	if( !v[0] )	// 非对子
	{
		if( !v[1] )
			return "憋十";
		return chinese_number(v[1])+"点";
	}

	if( undefinedp( PAIR_NAME[ v[0] ] ) )
		return "----";
	return PAIR_NAME[ v[0] ];
}

// 传入两个 get_value() 返回的值，判断两值的大小
// 值1大返回1，值2大返回2，打和返回3。
protected int which_one_is_bigger( int *v1, int *v2 )
{
	int i;

	if( !v1 || !v2 || sizeof(v1) != 4 || sizeof(v2) != 4 )
		return 0;

	// 比大小次序： 对子、点数、大牌比较、小牌比较
	// 由于“原因”看起来烦琐，所以略去了
	// 不明白规则的玩家，还是多看看 help 咯
	for( i=0; i<4; i++ )
	{
		if( v1[i] > v2[i] )
			return 1;
		else if( v1[i] < v2[i] )
			return 2;
	}
	return 3;
}

// 得到显示牌面的画面字串
// 可支持 1-8 张牌（多了一个屏幕放不下（行的长度不够），会乱）
protected varargs string get_pic( array card, int type, int need_name )
{
	// type 0: 无空隙
	// type 1: 两个牌间有空隙
	// type 2: 四个牌间有空隙

	string msg = "";
	int i, j, size;

	if( !card || (size = sizeof(card)) > 8 )
		return "只能显示 1-8 张牌！\n";

	// 做好头先
	for( i=1;i<=size;i++ )
	{
		msg += "┏━━━┓";
		switch( type )
		{
			case 1: if( i%2 == 0 )
					msg += "      ";
				break;
			case 2:	if( i%4 == 0 )
					msg += "      ";
				break;
		}
	}
	msg += "\n";

	// 做中间
	for( i=0;i<6;i++ )
	{
		for( j=0;j<size;j++ )
		{
			msg += sprintf( "┃%s┃", P9_PIC[card[j]][i] );
			switch( type )
			{
				case 1:	if( (j+1)%2 == 0 )
						msg += "      ";
					break;
				case 2:	if( (j+1)%4 == 0 )
						msg += "      ";
					break;
			}
		}
		msg += "\n";
	}
	//这里不必 msg+="\n" ，不是忘记  -_-"

	// 做尾
	for( i=1;i<=size;i++ )
	{
		msg += "┗━━━┛";
		switch( type )
		{
			case 1:	if( i%2 == 0 )
					msg += "      ";
				break;
			case 2:	if( i%4 == 0 )
					msg += "      ";
				break;
		}
	}
	msg += "\n";

	// 如果不需要名字，完成
	if( !need_name )
		return msg;

	// 否则加上名字显示
	for( i=0;i<size;i++ )
	{
		if( member_array(card[i], P9_BASE) < 0 )
			msg += "          ";
		else 
			msg += sprintf( " [%|6s] ", P9_NAME[ member_array(card[i], P9_BASE) ] );
		switch( type )
		{
			case 1:	if( (i+1)%2 == 0 )
					msg += "      ";
				break;
			case 2:	if( (i+1)%4 == 0 )
					msg += "      ";
				break;
		}
	}
	msg += "\n";

	return msg;
}

// 得到一整副随机的牌（用于每局开局前“洗牌”）
protected array get_random_all_cards()
{
	string t, *p1, *p2;
	int i;
	p1 = copy(P9_BASE);
	p2 = allocate(32);
	for( i=31; i>=0; i-- )
	{
		t = p1[ random(i+1) ];
		p1 -= ({ t });
		p2[i] = t;
	}
	return p2;
}

// 列出整副牌的图案，可选参数"need_name"，非零值时，在牌下标明牌的中文名字
protected varargs string get_show_all_msg( array v, int need_name )
{
	string msg = "";
	int i;

	if( !v || sizeof(v) != 32 )
		return "传入的参数发生错误，无法组成图案显示。\n";

	for( i=0;i<4;i++ )
	{
		msg += get_pic( v[i*8..(i+1)*8-1], 2, need_name );
	}
	return msg;
}

// 将两个牌排列一下，大的在前，小的在后  例如  地、天，就排成 天、地 返回，
// 并不影响这对牌的大小。
protected array lineup( array p )
{
	int t1, t2;

	if( !p || sizeof(p) != 2 )
		return p;
	t1 = member_array( p[0], P9_BASE );	// 获得 p1 在 P9_BASE 里的位置
	t2 = member_array( p[1], P9_BASE );	// p2
	if( t1 == -1 || t2 == -1 )
		return p;			// 发生意外错误

	if( P9_VALUE[t2] > P9_VALUE[t1] )
		return ({ p[1], p[0] });
	return p;
}

// ------------------ 弱智系统分析器 -------------------
// 用于赌大牌九，并由系统做庄时。
// 传入一个 sizeof(4) 的 string* ，返回同样大小的。
// 经弱智系统将4张牌分为“最适合”的两组，哈哈哈
// 谁能写个更强的分析器呀……会分宝、会用大牌带同样点的，
// 严重请求！  naihe 04-4-1
// -----------------------------------------------------
protected array system_AI( array p )
{
	mapping card_case, values;
	int i, j, k;
	array t;
	if( !p || sizeof(p) != 4 )
		return p;
	// 3个方案，每个方案又可头尾掉转，实共 6 个方案……
	card_case = ([
		"c1" : p,
		"c2" : ({ p[0],p[2],p[1],p[3], }),
		"c3" : ({ p[0],p[3],p[1],p[2], }),
	]);
	// 原则：不求赢，但求和——组最大的两个子，求赢一门再说！
	// 1、有自然对子，取自然对子，剩下两个做一组
	// 2、无自然对子，取特殊对子，剩下两个做一组
	// 3、无任何对子，取最大点组合，剩下两个做一组
	// 4、最大点组合时，如何用大牌带？？？bite
	// 5、不考虑分宝的情况
	values = ([ ]);
	for( i=1;i<6;i+=2 )
	{
		j = (i+1)/2;
		t = card_case[ "c" + j ];
		values[ "v"+i ] 	= get_value( t[0], t[1] );
		values[ "v"+(i+1) ]	= get_value( t[2], t[3] );
	}
	// 如果该 case 有自然对子，是它了
	for( i=1;i<6;i+=2 )
	{
		j = (i+1)/2;
		if( values["v"+i][0] >= P9_VALUE[31] || values["v"+(i+1)][0] >= P9_VALUE[31] )
		{
			// 随机摆大头或大尾
			t = card_case["c"+j];
			if( random(2) )
				return t;
			return ({ t[2], t[3], t[0], t[1], });
		}
	}
	// 否则，如果有特殊对子，也决定了
	for( i=1;i<6;i+=2 )
	{
		j = (i+1)/2;
		if( values["v"+i][0] > 0 || values["v"+(i+1)][0] > 0 )
		{
			// 随机摆大头或大尾
			t = card_case["c"+j];
			if( random(2) )
				return t;
			return ({ t[2], t[3], t[0], t[1], });
		}
	}
	// 什么都没有？……那么组一对大点的就好
	for( k=8;k>=0;k-- )
	{
		for( i=1;i<6;i+=2 )
		{
			j = (i+1)/2;
			if( values["v"+i][1] > k || values["v"+(i+1)][1] > k )
			{
				// 随机摆大头或大尾
				t = card_case["c"+j];
				if( random(2) )
					return t;
				return ({ t[2], t[3], t[0], t[1], });
			}
		}
	}

	// 靠，算得到这里？！怎摸可能？？？
	return p;
}

// 附带巫师测试函数
protected int do_wiz( string arg )
{
	object me = this_player();
	array p1, p2, t;
	int i, *v1, *v2;

	if( !me || !wizardp(me) )
		return 0;

	if( !arg )
		arg = "!!!";

	switch( arg )
	{
		case "show all":
			write( CLR + "\n牌九全部图案一览：\n" + get_show_all_msg( P9_BASE, 1 ) );
			return 1;
		case "show all random":
			write(CLR+"\n牌九全部图案一览(随机)：\n"+get_show_all_msg(get_random_all_cards(),1));
			return 1;
		case "test":
			t = get_random_all_cards();
			p1 = ({ t[0], t[1], });
			p2 = ({ t[2], t[3], });
			p1 = lineup( p1 );
			p2 = lineup( p2 );
			v1 = get_value( p1[0], p1[1] );
			v2 = get_value( p2[0], p2[1] );

			write( sprintf(
				"牌九巫师测试，一次随机的判断测试(小牌九)：\n\n%s\n"
				"      [%|6s]                  [%|6s]\n\n",
				get_pic( p1+p2, 1, 1 ),
				get_cname( v1 ),
				get_cname( v2 ),
			));

			i = which_one_is_bigger( v1, v2 );
			if( i == 1 )
				write( "      "HIG"◆Win!◆"NOR"\n" );
			else if( i == 2 )
				write( "                                "HIG"◆Win!◆"NOR"\n");
			else if( i == 3 )
				write( "            -------- 和局 --------\n");
			else write( "    发生了未知的错误！\n");

			return notify_fail( sprintf(
				"\n内部判断值参考：\n"
				"[一组]  对子：%2d  点数：%d  大牌：%2d  小牌：%2d\n"
				"[二组]  对子：%2d  点数：%d  大牌：%2d  小牌：%2d\n",
				v1[0], v1[1], v1[2], v1[3],  
				v2[0], v2[1], v2[2], v2[3], ) );
		case "test system ai":
			t = get_random_all_cards();
			p1 = ({ t[0], t[1], t[2], t[3], });
			write( sprintf( 
				"牌九巫师测试，一次系统庄家的策略测试(大牌九)：\n\n得牌：\n\n%s\n",
				get_pic( p1 )
			));

			p2 = system_AI( p1 );
			p1 = lineup( ({ p2[0], p2[1]}) );
			p2 = lineup( ({ p2[2], p2[3]}) );
			v1 = get_value( p1[0], p1[1] );
			v2 = get_value( p2[0], p2[1] );
			write( sprintf(
				"经弱智系统排列后：\n\n%s\n"
				"      [%|6s]                  [%|6s]\n\n",
				get_pic( p1+p2, 1, 1 ),
				get_cname( v1 ),
				get_cname( v2 ),
			));
			return 1;
		default:
			return notify_fail( 
				"[ "+GAME_NAME+" ]之巫师测试指令，可加参数：\n"
				"\n"
				"[show all]          查看所有牌的图案\n"
				"[show all random]   查看随机的所有牌的图案\n"
				"[test]              进行一次随机的判断测试(小牌九)\n"
				"[test system ai]    进行一次系统庄家的策略测试(大牌九)\n\n",
			);
//		case "ttt":
//			write( get_pic( ({"tian1","tian2","di2","he2","ft1", "82", "none", "none", }), 1, 1) );
//			return 1;
	}
	return 1;
}

//         #################################################
//     ##########################################################
// ###################################################################

// 以下是游戏程序部分
// 赌牌九 游戏部分

protected int filter_listener( object ob )
{
        if ( ob->query("naihe_game_data/p9/no_p9_msg") )
		return 0;
        return 1;
}

// 省略 *p 时，对所有玩家发布信息（设置了不接收信息的除外）
// 有 *p 时，对 *p 内列表玩家发布信息。
protected varargs void message_p9( string msg, array p )
{
	object listener_list, listener;
	string t;

	if( !msg )
		return;

	if( !p || !sizeof(p) )
	{
		listener_list = filter_array( users(), (: filter_listener :) );
		if( !listener_list || sizeof( listener_list ) < 1 )
			return;
		foreach( listener in listener_list )
		{
			tell_object( listener , ChannelColor"【牌九赌局】 " + msg + NOR);
		}
		return;
	}
	foreach( t in p )
	{
		if( t && (listener=find_player(t)) )
			tell_object( listener, ChannelColor"【牌九赌局】 " + msg + NOR);
	}
	return;
}

protected void set_del_no_msg_env( object me, string t )
{
	if( !me || !userp(me) )
		return;
	if( t == "set" )
	{
		if( !me->query( "naihe_game_data/p9/no_p9_msg" ) )
		{
			me->set("naihe_game_data/p9/no_p9_msg", "YES" );
			tell_object( me, "你已设置“不接收关于["+GAME_NAME+"]的信息”。\n");
		}
		return;
	}
	if( me->query( "naihe_game_data/p9/no_p9_msg" ) )
	{
		me->delete( "naihe_game_data/p9/no_p9_msg" );
		tell_object( me, "你已取消了“不接收关于["+GAME_NAME+"]的信息” 的设置。\n");
	}
}

protected int	help_cmds();				// help commands
protected int	do_showcards();				// 查看所有图案演示
protected int	do_check_now();				// 查询现在的游戏状态
protected int	do_chk( string arg );			// 玩家查询他人积分
protected int	do_lineup_card( string arg );		// 玩家将牌排列（仅大牌九时有效）
protected int	do_is_ready();				// 玩家准备好了（仅大牌九时有效）
protected int	do_join_game( int bet );		// 玩家加入游戏

protected void	do_start_game();			// 准备启动赌局
protected void	start_game_set( string inp );		// 启动赌局设置中
protected void	start_game_ok( object me );		// 设置成功，启动赌局
protected void	game_running_start();			// 游戏运行中 - 开始
protected void	game_running_ready_open( string t );	// 游戏运行中 - 准备开牌 (大牌九局时用)
protected void	game_running_open( int round );		// 游戏运行中 - 开牌 (大牌九局时调用两次)
protected void	game_running_over();			// 游戏运行中 - 结束 (恢复空闲)

protected string	*system_host_get_special_card();	// 允许系统的庄家获得一副特别的牌

string
	GameNow = "无赌局",
	*CardsNow,
	*HostCard,
	*NoReadyPlayers,

	end1;

int
	HostScore,

	end2;

mapping
	GameSettings,
	PlayerCard,
	PlayerBet,
	PlayerPower,
	HostPower,

	end3;

protected void do_start_game()
{
	object me = this_player();
	int my_score;

	if( !me || !userp(me) )
		return;
	if( ! GAME_ON )
	{
		write( "对不起，游戏暂停开放。\n");
		return;
	}
	if( GameNow != "无赌局" )
	{
		write( "你只能在 \"无赌局\" 时开始游戏。现在状态是 \""+GameNow+"\" 。\n");
		return;
	}
	my_score = me->query( GAME_SCORE_DATA );
	if( my_score < BET_MIN )
	{
		write( sprintf( "你的%s太低了，至少需要 %d 点。\n",
			GAME_SCORE_NAME, BET_MIN ));
		return;
	}
	if( me->query("naihe_game_data/p9/freetime") > time() )
	{
		write( "现在离你上一次成功启动赌局的时间太短，请稍后再试。\n");
		if ( !IsTest || getuid(me) != "naihe" )
			return;
	}

	write( sprintf( 
		" ========================== 你准备开始一局新的牌九赌局 ==========================\n"
		"如果你希望"HIR"由系统做庄，请输入 [big] 或 [small] 选择赌大牌九或小牌九，即直接开始"NOR"。\n"
		"\n"
		"否则，即"HIM"你自己做庄"NOR"。那么，你需要决定下面这些设置：\n"
		"1、决定赌局的方式，big = 赌大牌九  small = 赌小牌九\n"
		"2、决定最多可参与的人数(不包括你自己)，范围是 1 ~ 7\n"
		"3、决定每人最少押注多少，这个数字的范围是 %d ~ %d\n"
		"4、决定每人最多押注多少，这个数字的范围同上，并且不得小于“最少押注”\n"
		"\n"
		"你的%s是 %d 点。如果你决定自己做庄，请看指令示例： <"HIM"big 7 50 100"NOR">\n"
		"    表示：赌的是大牌九，最多接受7个人玩，其中每人最少押50点，最多押100点。\n"
		" ================================================================================\n"
		"请输入（取消请输入 cancel）：",
			BET_MIN, BET_MAX,GAME_SCORE_NAME,my_score,  ));

	input_to( "start_game_set" );
	return;
}

// 我认为，启动游戏时的设置提示写到这份上，应该是够清晰的了！
protected void start_game_set( string inp )
{
	object me = this_player();
	int bet_min, bet_max, player_max,t;
	string game_type, id, name ;

	if( !me || !userp(me) )
		return;
	if( ! GAME_ON )
	{
		write( "对不起，游戏暂停开放。\n");
		return;
	}
	if( GameNow != "无赌局" )
	{
		write(HIR"很遗憾，您的决定已经慢了，赌局已经由别人开始了。请直接输入 <p9> 查询。\n"NOR);
		return;
	}
	if( !inp )
		inp = "@#$@#$@#";

	if( inp == "cancel" || inp == "q" || inp == "Q" )
	{
		write( "好的，取消了你的要求，赌局恢复了空闲的状态。\n");
		return;
	}

	id = me->query("id");
	name = sprintf( "%s(%s)", me->query("name"), id );

	if( inp == "big" || inp == "small" )
	{
		// 如果庄家钱数太少了，那么，也许是由于概率设置不当，玩家赢了太多了，系统停止开庄。
		if( system_score < 1 )
		{
			write( HIR"对不起，系统暂停开庄。如想进行游戏，请自己做庄。\n"NOR
				"请重新输入（取消请输入cancel）：", );
			input_to( "start_game_set" );
			return;
		}
		// 同一玩家不要频繁地要求开庄……
		me->set( "naihe_game_data/p9/freetime", time() + StartGameBusy );
		set_del_no_msg_env( me,"del" );

		// 将游戏设置记录下来
		GameSettings = ([
			"host_id"	:	"SYSTEM",
			"host_name"	:	"系统",
			"p_amount"	:	7,
			"b_min"		:	BET_MIN,
			"b_max"		:	BET_MAX,
			"is_dp9"	:	inp == "big" ? 1 : 0,
		]);

		GameNow = "准备开始新赌局";
		HostScore = 0;
		start_game_ok( me );
		return;
	}

	// 玩家做庄
	sscanf( inp, "%s %d %d %d", game_type, player_max, bet_min, bet_max );
	if( !game_type || !player_max || !bet_min || !bet_max )
	{
		write( "输入指令的格式不正确，请确定你输入的格式是“字符 数字 数字 数字”，并且数字不能为 0 。\n"
			"请仔细查看说明，更正后重新输入指令（取消请输入cancel）：");
		input_to( "start_game_set" );
		return;
	}
	write( "\n" );
	if( !game_type || (game_type != "big" && game_type != "small" ) )
	{
		write( sprintf( 
		BLINK+HIR"%s"NOR" %d %d %d\n"
		"\"赌大牌九还是小牌九\"的决定有错误，它只能是 \"big\" 或 \"small\"。\n"
		"请重新输入（取消请输入cancel）：",
			game_type, player_max, bet_min, bet_max,
			));
		input_to( "start_game_set" );
		return;
	}
	if( player_max < 1 || player_max > 7 )
	{
		write( sprintf( 
		"%s "BLINK+HIR"%d"NOR" %d %d \n"
		"\"最多参与人数\"的决定有错误，它的范围是 1 ~ 7 。\n"
		"请重新输入（取消请输入cancel）：",
			game_type, player_max, bet_min, bet_max,
			));
		input_to( "start_game_set" );
		return;
	}
	if( bet_min < BET_MIN || bet_min > BET_MAX )
	{
		write( sprintf(
		"%s %d "BLINK+HIR"%d"NOR" %d\n"
		"\"最少押注额\"的决定有错误，它的范围是 %d ~ %d 。\n"
		"请重新输入（取消请输入cancel）：",
			game_type, player_max, bet_min, bet_max, BET_MIN, BET_MAX,
			));
		input_to( "start_game_set" );
		return;
	}
	if( bet_max < bet_min || bet_max > BET_MAX )
	{
		write( sprintf(
		"%s %d %d "BLINK+HIR"%d"NOR"\n"
		"\"最大押注额\"的决定有错误，它的范围是 %d ~ %d 。\n"
		"请重新输入（取消请输入cancel）：",
			game_type, player_max, bet_min, bet_max, bet_min, BET_MAX,
			));
		input_to( "start_game_set" );
		return;
	}

	t = me->query( GAME_SCORE_DATA );
	if( t < bet_max * player_max )
	{
		write( sprintf(
			"你希望自己做庄，但是如果允许最多 %d 个人参与赌局，那你必须有 %d 点的%s才够本钱做庄。\n"
			"你的积分不够(你有 %d 点)，你可以降低最大押注额，或减少允许参与的人数。\n"
			"请重新输入（取消请输入cancel）：",
			player_max, bet_max*player_max, GAME_SCORE_NAME,t,
			));
		input_to( "start_game_set" );
		return;
	}

	// 成功！
	// 同一玩家不要频繁地要求开庄……
	me->set( "naihe_game_data/p9/freetime", time() + StartGameBusy );
	set_del_no_msg_env( me,"del" );


	// 将游戏设置记录下来
	GameSettings = ([
		"host_id"	:	id,
		"host_name"	:	name,
		"p_amount"	:	player_max,
		"b_min"		:	bet_min,
		"b_max"		:	bet_max,
		"is_dp9"	:	game_type == "big" ? 1 : 0,
	]);

	// 由于玩家做庄，所以要进行特别的设置

	HostScore = bet_max * player_max;
	me->add( GAME_SCORE_DATA, -HostScore );
	write( sprintf( 
		HIG"你是庄家，根据你规定的最大押注(每家最多可以押 %d 点 x %d 家)，你必须交付至少 %d 点的庄家押金。\n"
		"它已经从你的%s里扣除了，在赌局结束后，你才能得回它（如果还没输光的话 :P）。你现在还有 %d 点。\n",
		bet_max, player_max, HostScore, GAME_SCORE_NAME, me->query( GAME_SCORE_DATA ),
	));
	GameNow = "准备开始新赌局";
	start_game_ok( me );
	return;
}

protected void start_game_ok( object me )
{
	if( !me || !userp(me) || !GAME_ON || GameNow != "准备开始新赌局" )
		return;
	message_p9( sprintf(
		"\n---------------------------------------------------------------------------------------\n"
		"应 %s 要求，由 %s 做庄，开始了一局牌九赌局！\n"
		"赌的是%s"+ChannelColor+"，受%s家，每家限注 %d ~ %d 点！想赢钱的就来呀！ (p9 in 赌注)\n"
		"---------------------------------------------------------------------------------------\n",
			sprintf( "%s(%s)", me->query("name"), me->query("id") ),
			GameSettings[ "host_name" ],
			GameSettings[ "is_dp9" ] ? HIY"大牌九"NOR : HIG"小牌九"NOR,
			chinese_number( GameSettings[ "p_amount" ] ),
			GameSettings[ "b_min" ],
			GameSettings[ "b_max" ],
	));

	// 将需要的变量重置
	PlayerBet = ([ ]);
	PlayerCard = ([ ]);
	PlayerPower = ([ ]);
	HostPower = ([ ]);
	HostCard = ({ });
	NoReadyPlayers = ({ });

	GameNow = "等待玩家加入";		// 此时，其他玩家就可以加入了
	if( IsTest )
		call_out( "game_running_start", 5 );
	else
		call_out( "game_running_start", WAIT_TIME_JOIN );	// 直接于 N 秒后启动
	return;
}

protected void game_running_start()
{
	string hid;
	object hob;
	// 第二部分使用
	array p;
	string t;
	int i, is_dp9, i2;

	remove_call_out( "game_running_start" );
	if( !GAME_ON || GameNow != "等待玩家加入" )
		return;

	GameNow = "赌局启动前检测"; // 这个状态一刹那即过，也是为了防止未知的冲突而已(player join)

	// 是否至少有一位玩家参与赌局？否，游戏无法开始  若>7 时会出BUG，取消 game
	if( (i=sizeof(PlayerBet)) < 1 || i > 7 )
	{
		message_p9( "真遗憾，本局牌九赌局无人加入(或发生意外)，宣布取消。\n" );
		hid = GameSettings[ "host_id" ];
		if( hid != "SYSTEM" )  // 如果是玩家做庄，那么他已经押下了“庄家押金”。把这个钱还给他。
		{
			if( hid )
				hob = find_player( hid );
			if( hob )
			{
				tell_object( hob, sprintf("你得回了之前押下的庄家押金 %d 点。\n", HostScore ));
				hob->add( GAME_SCORE_DATA, HostScore );
			}
		}
		GameNow = "无赌局";
		return;
	}

	// 那么，开始
	GameNow = "赌局正在进行：[取牌中]";
	if( GameSettings[ "is_dp9" ] )	// 这个标记表示这局 “是大牌九”
		is_dp9 = 1;
	message_p9( sprintf( "赌局开始了！共有 %d 位玩家参与了 %s 做庄的 %s 赌局！\n",
			i, GameSettings[ "host_name" ], is_dp9 ? "大牌九" : "小牌九",
		));

	p = keys( PlayerBet ); // 玩家列表

	// 记录日志
	for( i=sizeof(p)-1;i>=0;i-- )
		i2 += PlayerBet[p[i]];
        game_log( sprintf( "\n%s 赌注类型：%s(\"%s\")\n"
			   "   庄：[%s]  方式：[%s牌九]  参与：[%d人]  押注：[%d点]  系统积分：[%d]\n",
                        GameSettings["host_id"] == "SYSTEM" ? "★" : "◎",  GAME_SCORE_NAME,
			GAME_SCORE_DATA, GameSettings["host_name"], is_dp9?"大":"小", sizeof(PlayerBet),
			i2, system_score,
		));
	CardsNow = get_random_all_cards();					// 洗牌

	// 庄家先拿牌，并将庄家的牌排列一下，符合普通人的思维
	HostCard = lineup( ({ CardsNow[0], CardsNow[1] }) ) + lineup( ({ CardsNow[2], CardsNow[3] }) );

	message_p9( sprintf( NOR+
		"\n---------------------------------------------------------------------------------------\n"
		"你是庄家。拿到了：\n"
		"%s"
		"---------------------------------------------------------------------------------------\n",
		is_dp9  ? get_pic( HostCard, 0, 1 )
			: get_pic( ({ HostCard[0], HostCard[1],}), 0, 1 ),
		), ({ GameSettings[ "host_id" ] }),
	);
	// 如果是系统做庄，需要进行一些特别的记录。
	// 并且，为了弥补其弱智，庄家有机会得到特殊的牌，以增大赢钱的几率。
	// 并且，如果是大牌九赌局，庄家需要自动排列它自己的牌。
	if( GameSettings[ "host_id" ] == "SYSTEM" )
	{
		HostScore += GameSettings[ "b_max" ] * 7;   // 庄家本金 = 原庄家本金 + 玩家押注
		system_score -= GameSettings[ "b_max" ] * 7; // 这里是一个防止 由于设置不当而导致恶劣后果 的情形出现的机制

		// 1/5 的机会得到特别的牌
		if( !random(5) )
		{
			if( IsTest )
				message_p9( sprintf( "庄家特别得牌！原来的是：%s %s %s %s\n",
					HostCard[0], HostCard[1],HostCard[2],HostCard[3],));
			HostCard = 0;
			HostCard = system_host_get_special_card();
			if( IsTest )
				message_p9( sprintf( "经过特别处理后的是：%s %s %s %s\n",
					HostCard[0], HostCard[1],HostCard[2],HostCard[3],));
		}
		// 好，如果是大牌九，允许庄家自动排列
		if( is_dp9 )
		{
			HostCard = system_AI( HostCard );
		}
	}
	else	// 否则，庄家由玩家控制，那么它被添加“未准备好”的标记
	{
		NoReadyPlayers += ({ GameSettings[ "host_id" ], });
	}

	/*// 特别的测试需要
	while( sizeof(PlayerBet) < 7 )
	{
		PlayerBet[ random(10000) + "" ] = 9;
	}*/

	i = 4;
	foreach( t in p )							// 玩家拿牌
	{
		// 玩家拿牌，并将其排列一下
		PlayerCard[ t ] = lineup( ({CardsNow[i],CardsNow[i+1]}) ) + lineup( ({CardsNow[i+2],CardsNow[i+3]}) );
		i += 4;
		message_p9( sprintf( NOR+
			"\n---------------------------------------------------------------------------------------\n"
			"你是闲 [%s] 家。拿到了：\n"
			"%s"
			"---------------------------------------------------------------------------------------\n",
			chinese_number( i/4 ), is_dp9  ? get_pic( PlayerCard[t], 0, 1 )
				: get_pic( ({ PlayerCard[t][0], PlayerCard[t][1],}), 0, 1 ),
			), ({ t }),
		);
		PlayerPower[ t ] = 0;
		HostPower[ t ] = 0;
		NoReadyPlayers += ({ t });
	}

	// 好，都拿到牌了，如果是小牌九，立即开牌（3秒）；否则，等待一定时间，让各位玩家将牌排序。
	if( !is_dp9 )
	{
		GameNow = "赌局正在进行：[即将开牌]";
		message_p9( "这局赌的是小牌九，“一翻两瞪眼”，开牌咯！\n", ({ GameSettings[ "host_id" ] }) + p );
		call_out( "game_running_open", 3, 1, );		// 3秒后执行，参数1 表示判断第1、2张牌
		return;
	}
	// 否则给出提示信息，让玩家排列自己的牌，等待 N 秒后继续
	GameNow = "赌局正在进行：[等待玩家将牌分组]";
	message_p9(
		"\n"
		"              这局赌的是大牌九，你要把牌排成你认为合适的两组（分别叫做上、下门）。\n"
		"              用指令参数 ["HIW"card 2 3 1 4"+ChannelColor+"] 这样的形式来排列它们。\n"
		"              例子里的意思是，新的顺序是：现在的牌的第 2、3、1、4 张。\n"
		"              那么也就是说，现在的第 2、3 张将作为 上门；第 1、4 张作为 下门。\n\n",
		({ GameSettings[ "host_id" ] }) + p );
	call_out( "game_running_ready_open", WAIT_TIME_LINEUP, "时间到了" );
}

protected array system_host_get_special_card()
{
	array base, c;
	string t, t1, t2;
	int i;
	if( HostCard || !CardsNow || sizeof(CardsNow) != 32 )
		return 0;
	base = ({ "tian", "di", "ren", "he", "mh", "cs", "bd", "ft", "ht", "16", "15",
		"9", "8", "7", "5" });
	t = base[ random(sizeof(base)) ];
	t1 = t+"1";
	t2 = t+"2";
	// 将洗好的牌中的这两个换掉
	for( i=0;i<32;i++ )
	{
		if( CardsNow[i] == t1 )
			CardsNow[i] = CardsNow[0];
		if( CardsNow[i] == t2 )
			CardsNow[i] = CardsNow[1];
	}
	CardsNow[0] = t1;
	CardsNow[1] = t2;
	c = ({ CardsNow[0],CardsNow[1],CardsNow[2], CardsNow[3], });
	return c;
}


protected void game_running_ready_open( string t )
{
	remove_call_out( "game_running_ready_open" );
	if( !GAME_ON || GameNow != "赌局正在进行：[等待玩家将牌分组]" || !GameSettings[ "is_dp9" ] )
		return;
	GameNow = "赌局正在进行：[即将开牌]";
	message_p9( t+"，开牌咯！\n",  ({ GameSettings[ "host_id" ] }) + keys(PlayerCard) );
	call_out( "game_running_open", 1, 1);
}

// 开牌了啊
protected void game_running_open( int round )
{
	array c, tc, p;
	string t, ttt, win_id, lost_id, msg;
	array cname, cl;
	int *v1, *v2, win_times, lost_times, i;

	remove_call_out( "game_running_open" );
	if( !GAME_ON || (GameNow != "赌局正在进行：[即将开牌]" && GameNow != "赌局正在进行：[开牌中]") )
		return;

	GameNow = "赌局正在进行：[开牌中]";

	win_id = "";
	lost_id = "";

	// 为了显示图片，要一个个将牌的标记记录下来。先记庄家的
	if( round == 1 )
	{
		c = ({ HostCard[0], HostCard[1], });
		if( GameSettings[ "is_dp9" ] )
			ttt = "上门";
		else
			ttt = "";
	}
	else
	{
		c = ({ HostCard[2], HostCard[3], });
		ttt = "下门";
	}

	c = lineup( c );		// 排列一下它的大小顺序
	v1 = get_value( c[0], c[1] );	// 得到庄家的牌的“价值”哈
	cname = ({ get_cname(v1) });	// 得到其对子的名称

	cl = ({ HIW });
	p = keys( PlayerBet );		// 玩家列表
	foreach( t in p )		// 逐个与庄家较量
	{
		if( round == 1 )	// 得到要比较的是哪一门牌先。不搞罗嗦的安全判断了，出 bug 了我可不管啊
			tc = ({ PlayerCard[t][0], PlayerCard[t][1], });
		else
			tc = ({ PlayerCard[t][2], PlayerCard[t][3], });
		tc = lineup( tc );			// 将其大小顺序排列一下
		c += tc;				// 将这几个标记凑进去，到时候要显示图片啊
		v2 = get_value( tc[0], tc[1] );		// 搞到它的“价值”
		cname += ({ get_cname(v2) });		// 搞到它的“名称”
		if( which_one_is_bigger(v1,v2 ) == 2 )	// 哈哈，闲家大
		{
			win_times ++;
			win_id += t + " 、";
			PlayerPower[ t ] ++;		// 这一家的 power 大了些哈
			cl += ({ BLINK+HIG });
		}
		else					// 否则即使是和，也算庄赢
		{
			lost_times ++;
			lost_id += t + " 、";
			HostPower[ t ] ++;		// 庄家的 power 大了些哈
			cl += ({ HIR });
		}
	}

	// 好了，比完了，show 出结果来；没有人参与的闲家，也要显示空位
	while( sizeof(c) < 16 )		// 给我凑
	{
		c += ({ "none", });
	}
	while( sizeof(p) < 7 )
	{
		p += ({ "----", });
	}
	while( sizeof(cname) < 8 )
	{
		cname += ({ "----" });
	}
	while( sizeof(cl) < 8 )
	{
		cl += ({ NOR });
	}

	// 好啦，一段段来，搞好头先
	// 这一段是庄、123闲的名字和押注额
	t = sprintf( HIY"  %-16s  "NOR, "[庄家 "+GameSettings[ "host_id" ]+"]", );
	for( i=0;i<3;i++ )
	{
		t += sprintf( "      "HIY"%|10s"NOR" (%|6d) ",
			"["+p[i]+"]", PlayerBet[ p[i] ], );
	}
	msg = sprintf(
		"\n----------------------------------------------%s----------------------------------------------\n"
		"%s\n"
		"%s",
			ttt == "" ? "------------" : sprintf( "[%|10s]", ttt ),
			t, get_pic( ({c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7],}), 1, 1 ),
		);
	// 搞出这几门牌的中文名称
	t = " ";
	for( i=0;i<4;i++ )
	{
		t += sprintf( "     %s%|8s"NOR"             ", cl[i], "["+cname[i]+"]" );
	}
	msg += t + "\n\n";

	// 好，继续搞后边4门牌  搞名字先
	t = "";
	for( i=3;i<7;i++ )
	{
		t += sprintf( ""HIY"%|10s"NOR" (%|6d)       ",
			"["+p[i]+"]", PlayerBet[ p[i] ], );
	}
	msg += sprintf(
		"%s\n"
		"%s",
			t, get_pic( ({c[8],c[9],c[10],c[11],c[12],c[13],c[14],c[15],}), 1, 1 ),
		);
	// 搞出后面几门牌的中文名称
	t = " ";
	for( i=4;i<8;i++ )
	{
		t += sprintf( "     %s%|8s"NOR"             ", cl[i], "["+cname[i]+"]" );
	}
	msg += t + "\n\n";
	// 最后的统计报告
	if( win_times == sizeof( PlayerBet ) )
	{
		msg += sprintf( HIG" 庄家%s是 [%s]，通赔！\n"NOR, ttt, cname[0] );
	}
	else if( lost_times == sizeof(PlayerBet) )
	{
		msg += sprintf( HIY" 庄家%s是 [%s]，通吃！\n"NOR, ttt, cname[0] );
	}
	else
	{
		msg += sprintf( HIW" 庄家%s是 [%s]，吃 %s 共 %d 门，\n"
			     "                    赔 %s 共 %d 门。\n"NOR,
			ttt, cname[0], lost_id, lost_times, win_id, win_times, );
	}

	msg +=
	  "---------------------------------------------------------------------------------------------------------\n";
	message_p9( NOR + msg, p+({ GameSettings[ "host_id"]}) );


	// 好了，show 完了，如果是小牌九，统计游戏；大牌九，如果是上门就继续比，下门也统计游戏
	if( GameSettings[ "is_dp9" ] && round == 1 )
	{
		message_p9 ( "接下来比下门的牌！\n", p+({ GameSettings[ "host_id"]}) );
		if( IsTest )
			call_out( "game_running_open", 3, 2 );
		else
			call_out( "game_running_open", WAIT_TIME_NEXTPAIR, 2 );
		return;
	}

	GameNow = "赌局输赢统计中";
	if( IsTest )
		call_out( "game_running_over", 3 );
	else
		call_out( "game_running_over", WAIT_TIME_NEXTPAIR );
}

// 结束，统计，恢复空闲状态
protected void game_running_over()
{
	array p;
	string t, Hmsg;
	object ob;
	int old_HostScore,i, i2;

	remove_call_out( "game_running_over" );
	if( !GAME_ON || GameNow != "赌局输赢统计中" )
		return;

	// Power 逐个看
	Hmsg = "\n";
	p = keys( PlayerBet );
	foreach( t in p )
	{
		i = PlayerBet[t];
		if( i<BET_MIN || i>BET_MAX )
			i = BET_MIN;
		if( t )
			ob = find_player( t );
		if( !ob )					// 人不在了，作弃权论
		{
			Hmsg += sprintf( HIY"弃权：%s 赌着赌着跑掉了。赚进了 %d 点 %s。\n"NOR, t, i, GAME_SCORE_NAME );
			continue;
		}
		if( HostPower[t] > PlayerPower[t] )		// 这个玩家输了，不必做什么
		{
			message_p9( sprintf( HIR"你输了！输掉了 %d 点 %s。  :(    押注前：[%d] 现在：[%d]\n"NOR,
				i, GAME_SCORE_NAME,(i2=ob->query( GAME_SCORE_DATA )+i),(i2-i), ), ({t}) );
			Hmsg += sprintf( HIG"赢了 %s ，赚进了 %d 点 %s。\n"NOR, t, i, GAME_SCORE_NAME);
		}
		else if( HostPower[t] < PlayerPower[t] )	// 赢了，从庄家押金中扣除
		{
			message_p9( sprintf( HIG"你赢了！赢了 %d 点 %s ，哈哈哈。  押注前：[%d] 现在：[%d]\n"NOR,
				i, GAME_SCORE_NAME,(i2=ob->query( GAME_SCORE_DATA )+i),(i2+i), ), ({t}) );
			Hmsg += sprintf( HIR"输给了 %s ，赔出了 %d 点 %s。\n"NOR, t,i,GAME_SCORE_NAME);
			ob->add( GAME_SCORE_DATA, i*2 );	// 连本带利得到了
			HostScore -= i*2;
		}
		else						// 和局
		{
			message_p9( sprintf( HIW"和局！得回了 %d 点 %s ，真是白费劲～  押注前：[%d] 现在：[%d]\n"NOR,
				i, GAME_SCORE_NAME,(i2=ob->query( GAME_SCORE_DATA )+i),i2, ), ({t}) );
			Hmsg += sprintf( HIW"和局： %s ，%d 点 %s 无输赢～～\n"NOR, t,i,GAME_SCORE_NAME);
			ob->add( GAME_SCORE_DATA, i );		// 拿回本钱
			HostScore -= i;
		}
	}

	old_HostScore = GameSettings[ "b_max" ] * GameSettings[ "p_amount" ];
	i = HostScore - old_HostScore;

	if( (t=GameSettings[ "host_id" ]) != "SYSTEM" )		// 玩家做的庄，要特别处理一下
	{
		if( t )
			ob = find_player( t );
		if( ob )
		{
			Hmsg += sprintf( "\n你在开局之前押下的“庄家押金”是 %d 点，现余 %d 点。%s"NOR"\n",
				old_HostScore, HostScore,
				i == 0 ? HIW"刚好回本！呵呵。" : i<0 ? HIR"输了 "+i*-1+" 点！" : HIG"赢了 "+i+" 点。 :)",);
			Hmsg += sprintf( "开始前：[%d]", ob->query( GAME_SCORE_DATA ) + old_HostScore );
			if( HostScore > 0 )
				ob->add( GAME_SCORE_DATA, HostScore );
			Hmsg += sprintf( "  现在：[%d]\n", ob->query( GAME_SCORE_DATA ) );
			message_p9( Hmsg, ({t}) );
		}
	}
	else
	{
		system_score += HostScore;
	}

	// 记录
	game_log( sprintf( "---- 赌局结束。开庄：[%d]  结束：[%d]  %s。%s\n",
			old_HostScore, HostScore,
			i==0 ? "庄家回本" : i<0 ? "庄家输了 "+i*-1+" 点" : "庄家赢了 "+i+" 点",
			t == "SYSTEM" ? "系统积分剩余 "+system_score+" 点。" : "",
		));
	GameNow = "无赌局";
	message_p9( sprintf( "由 %s 做庄的这一局牌九赌局结束了！\n", GameSettings["host_name"]));
}
// 完毕！一个圈子循环咯。


protected int do_check_now()
{
	array gn_ok, p;
	string msg, t;
	int i;

	// 游戏状态描述必须与此统一    所有的 GameNow :
	//	"无赌局",			"准备开始新赌局",		"等待玩家加入",
	//	"赌局启动前检测",		"赌局正在进行：[取牌中]",	"赌局正在进行：[即将开牌]",
	//	"赌局正在进行：[等待玩家将牌分组]",	"赌局输赢统计中",

	gn_ok = ({ "等待玩家加入", "赌局正在进行：[取牌中]", "赌局正在进行：[等待玩家将牌分组]", 
			"赌局正在进行：[即将开牌]", "赌局输赢统计中",});

	msg = sprintf( "----------------------------------------------------------------------\n"
		BGRN+HIY"[ %s(%s) 状态查询 ]\n\n"NOR
		"  现在状态：["HIG"%s"NOR"]  你的%s：["HIY"%d"NOR"]  %s\n\n",
			GAME_NAME, GAME_VERSION, GameNow,
			GAME_SCORE_NAME, this_player()->query( GAME_SCORE_DATA ),
			wizardp(this_player()) ? "系统积分：["HIM+system_score+NOR"]" : "", );

	// 当状态是允许列表内时，添加额外的查询信息
	if( member_array( GameNow, gn_ok ) != -1 )
	{
		msg += sprintf( "  庄家：[%s]  限注：[%d - %d]  限人：[%d]  方式：[%s牌九]  %s\n\n",
				GameSettings["host_name"], GameSettings["b_min"],
				GameSettings["b_max"], GameSettings["p_amount"],
				GameSettings["is_dp9"] ? "大" : "小",
				GameNow == "赌局正在进行：[等待玩家将牌分组]" ?
					member_array( GameSettings["host_id"], NoReadyPlayers ) == -1 ?
						HIG"●"NOR : HIR"●"NOR : "", );
		if( PlayerBet && mapp(PlayerBet) )
		{
			p = keys( PlayerBet );
			for( i=0;i<sizeof(p);i++ )
			{
				if( GameNow == "赌局正在进行：[等待玩家将牌分组]" )
				{
					if( member_array( p[i], NoReadyPlayers ) == -1 )
						t = HIG"将牌分好组了"NOR;
					else t = HIR"还未将牌分好组"NOR;
				}
				else t = "";
				msg += sprintf( "  [闲·%s家]  %-10s   押注：[%-12s %s\n",
					chinese_number(i+2),p[i], PlayerBet[p[i]] +"]", t);
			}
		}
	}

	return notify_fail( msg + "----------------------------------------------------------------------\n");
}

protected int do_lineup_card( string arg )
{
	object me = this_player();
	int *c, *c1, i;
	string id, *bc, *bc2;	// bc = base card

	if( !arg || !me || !userp(me) || !GAME_ON || GameNow != "赌局正在进行：[等待玩家将牌分组]"
	 || !GameSettings[ "is_dp9" ] || !PlayerBet || !sizeof(PlayerBet)
	 || member_array( getuid(me), keys(PlayerBet)+({ GameSettings["host_id"]}) ) == -1 
	 )
		return 0;

	c = allocate(4);
	c1 = ({ 1, 2, 3, 4 });
	sscanf( arg, "card %d %d %d %d", c[0], c[1],c[2],c[3] );
	for( i=0;i<4;i++ )
	{
		if( c[i] < 1 || c[i] > 4 )
			return notify_fail("指令参数格式： [card 数字 数字 数字 数字]\n"
					"数字范围在 1-4 之间，并且不得相同。\n");
		c1 -= ({ c[i] });
		c[i] -= 1;
	}
	if( sizeof(c1) )
		return notify_fail("指令参数格式： [card 数字 数字 数字 数字]\n"
					"数字范围在 1-4 之间，并且不得相同。\n");
	if( (id=getuid(me)) == GameSettings["host_id"] )
	{
		HostCard = ({ HostCard[ c[0] ], HostCard[ c[1] ], HostCard[ c[2] ], HostCard[ c[3] ], });
		write( sprintf( "\n%s\n\n"
			"如果你准备好了，请输入指令及参数 [ok] 表示“准备好了”，可以使赌局更快继续下去。\n",
			get_pic( HostCard, 1, 1 ) ));
	}
	else
	{
		PlayerCard[ id ] = ({ PlayerCard[id][c[0]],PlayerCard[id][c[1]],
					PlayerCard[id][c[2]],PlayerCard[id][c[3]], });
		write( sprintf( "\n%s\n\n"
			"如果你准备好了，请输入指令及参数 [ok] 表示“准备好了”，可以使赌局更快继续下去。\n",
			get_pic( PlayerCard[id], 1, 1 ) ));
	}
	return 1;
}

protected int do_is_ready()
{
	object me = this_player();
	string t, *p;

	if( !me || !userp(me) )
		return 0;
	t = getuid(me);
	if( !GAME_ON || GameNow != "赌局正在进行：[等待玩家将牌分组]" || !GameSettings[ "is_dp9" ]
	 || !PlayerBet || !sizeof(PlayerBet) )
		return 0;
	p = keys(PlayerBet) + ({ GameSettings["host_id"]} );
	if( member_array( t, p ) == -1 || member_array( t, NoReadyPlayers ) == -1 )
		return 0;

	NoReadyPlayers -= ({ t });
	set_del_no_msg_env( me,"del" );
	message_p9( sprintf( HIW"%s 准备好了！\n"NOR, t, ), p );
	if( sizeof( NoReadyPlayers ) < 1 )
	{
		remove_call_out( "game_running_ready_open" );
		call_out( "game_running_ready_open", 1, "所有人都准备好了" );
	}
	return 1;
}

protected int do_join_game( int bet )
{
	object me = this_player();
	string id;
	int i;

	if( !me || !userp(me) )
		return 0;

	if( !GAME_ON )
		return notify_fail("对不起，["+GAME_NAME+"] 暂停开放。\n");
	if( GameNow != "等待玩家加入" )
		return notify_fail("对不起，现在的时机并不能加入赌局。\n");
	id = getuid(me);
	if( GameSettings["host_id"] == id )
		return notify_fail("这一局你是庄家。\n");
	if( PlayerBet[ id ] )
		return notify_fail("你已经加入赌局了！\n");
	if( sizeof(PlayerBet) >= GameSettings[ "p_amount" ] )
		return notify_fail("对不起，本局赌局已经人满了。\n");
	if( bet > (i=me->query( GAME_SCORE_DATA )) )
		return notify_fail( sprintf( 
			"你的%s只有 %d ，恐怕押不了 %d 那么多吧。\n",
				GAME_SCORE_NAME, i, bet ) );
	if( bet < GameSettings[ "b_min" ] || bet > GameSettings[ "b_max" ] )
		return notify_fail( sprintf(
			"押注范围是 %d - %d 点！\n",
				GameSettings[ "b_min" ], GameSettings[ "b_max" ] ));
	// ok.
	me->add( GAME_SCORE_DATA, -bet );
	HostScore += bet;
	PlayerBet[ id ] = bet;
	// 加入游戏的玩家，当然要接收游戏的信息
	set_del_no_msg_env( me,"del" );
	message_p9( sprintf( HIW"%s(%s)押下了%s %d ，加入了赌局。\n",
			me->query("name"), id, GAME_SCORE_NAME, bet, ));
	write( sprintf( "你加入了赌局，押下%s %d 后，还剩下 %d 。\n",
		GAME_SCORE_NAME, bet, me->query( GAME_SCORE_DATA ) ));
	if( sizeof(PlayerBet) >= GameSettings[ "p_amount" ] )
	{
		remove_call_out( "game_running_start" );
		call_out( "game_running_start",1);
	}
	return 1;
}

protected int do_showcards()
{
	write( CLR + "\n牌九全部图案一览：\n" + get_show_all_msg( P9_BASE, 1 ) );
	return 1;
}

protected int do_chk( string arg )
{
	object who;

	if( !arg || arg == "" )
		return notify_fail( "你要查询谁的"+GAME_SCORE_NAME+"？\n");

	if( !(who=find_player(arg)) )
		return notify_fail( "现在并没有 ["+arg+"] 这个玩家在线。\n");

	write( sprintf( "%s(%s) 共有%s： %d\n",
		who->query("name"), who->query("id"), GAME_SCORE_NAME, who->query( GAME_SCORE_DATA ) ));
	return 1;
}

protected int help_cmds()
{
	write( sprintf( 
BGRN+HIY"[ %s(%s) 指令介绍 ]"NOR"

------[参数]---------------[说明]---------------------[有效时机]---------

  check(可省略)        查询你的有效积分、游戏状态      任意时机

  chk 人物ID           查询他人的有效积分              任意时机

  set no_p9_msg        设置“不接收本游戏的公众信息”  任意时机

  unset no_p9_msg      取消设置                        任意时机

  showcards            查看所有牌的图案示范            任意时机

  new                  启动一局新的赌局                无赌局时

  in 赌注(数字)        作为闲家加入赌局                赌局已开始，并
                                                       在等待玩家加入时
  card 排列次序        大牌九赌局时，将你的牌分组      游戏开始后有提示

  ok                   大牌九赌局时，表示“已分好组”  与 [card] 同一时机

  wiz                  巫师参数，仅限巫师使用          任意时机

                                            By 奈何(naihe) 2004-04
-------------------------------------------------------------------------\n",
	GAME_NAME, GAME_VERSION ));
	return 1;
}


int main( object me, string arg )
{
	string t;
	int i;

	if( !me || !userp(me) )
		return 0;

//	这个地方不要作这个判断，由各函数自己去作
//	if( !GAME_ON )
//		return notify_fail( sprintf( "[%s] 暂停开放。\n", GAME_NAME));

	if( !arg )
		arg = "check";

	// 参数不确定的，用 if() 判断
	// 巫师测试指令
	if( arg == "wiz" || sscanf(arg, "wiz %s", t) )
		return do_wiz( t );

	// 任何玩家均可查询他人的积分
	if( arg == "chk" || sscanf(arg, "chk %s", t) )
		return do_chk( t );

	// 分组时的指令可以简化
	if( sscanf( arg,"%*d %*d %*d %*d" ) )
		arg = "card "+arg;

	// 大牌九时，玩家可将牌的顺序改变，即分组
	if( strlen(arg) > 3 && arg[0..3] == "card" )
		return do_lineup_card( arg );

	// “我准备好了”
	if( arg == "ok" || arg == "ready" )
		return do_is_ready();

	// 加入游戏
	if( arg == "in" || sscanf( arg, "in %d", i) )
		return do_join_game( i );
	// 同样是加入游戏，来个正确的英文
	if( arg == "join" || sscanf( arg, "join %d", i)) 
		return do_join_game( i );

	// 固定参数的，可以用 switch() 来判断
	switch( arg )
	{
		case "help":
			return help();

		case "help cmds":
		case "help cmd":
		case "help commands":
		case "help command":
			return help_cmds();

		case "set no_p9_msg":
			set_del_no_msg_env( me, "set" );
			return 1;

		case "unset no_p9_msg":
			set_del_no_msg_env( me, "del" );
			return 1;

		case "check":
			return do_check_now();

		case "showcards":
			return do_showcards();

		case "new":
		case "start":
			do_start_game(); // 内含 input_to() 步骤，所以不直接 return 该函数
			return 1;
	}

	write( "没有 \""+arg+"\" 这个参数，请以参数 [help] 及 [help cmds] 查询说明。\n");
	return 1;
}
