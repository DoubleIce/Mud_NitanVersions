#include <ansi.h>

mapping type_list = ([
        "weapon" : ({ "blade", "club", "hammer", "sword", "staff", "whip", }),
        "armor"  : ({ "armor", "boots", "cloth", "hands", "head", "waist", "wrists", }),
        "gem"    : ({ "gem", "skull", }),
]);

array weapon_type = ({
        "blade", "hammer", "sword", "staff", "whip",
}); 

array armor_type = ({
        "armor", "boots", "cloth", "hands", "head", "waist", "wrists",
});

// װ������
mapping name_list = ([
	"blade"		:	
		([
			"�𱳴󿳵�"	:	"jinbei blade", 
			"���ȴ�"	:	"menshan blade", 
			"��ﳯ����"	:	"chaoyang blade",  
			"��ǹ��µ�"	:	"guyue blade",  
			"��ɽ��"	:	"kanshan blade",  
			"�������е�"	:	"sanjian blade",  
			"���Ȱ��ŵ�"	:	"heshan blade", 
			"�𱳿�ɽ��"	:	"kanshan blade",  
			"���ᵶ"	:	"yanling blade",  
			"��ͭ��"	:	"qingtong blade",  
			"���ﵶ"	:	"danfeng blade",  
			"���ź�ӧ��"	:	"hongying blade",  
			"���޵�"	:	"xiurong blade",  
			"����ߡ����"	:	"qixing blade",  
			"������"	:	"huya blade", 
			"�Ŷ��˻���"	:	"bahuan blade",  
			"�����Ͻ�"	:	"yulin blade",  
			"�����ͷ��"	:	"guitou blade",  
			"������"	:	"liangyin blade",  
			"��⵶"	:	"dianguang blade",  
			"�߱����"	:	"cuojin blade",  
			"��ͭ��"	:	"chitong blade",  
			"��ˮ��"	:	"pishui blade",  
			"��ֵ�"	:	"qinggang blade", 
		]),

	"hammer"	:	
		([
			"�����Ͻ�"	:	"zijin hammer",   
			"����ƽ�"	:	"huangjin hammer",    
			"������ͭ��"	:	"shengtong hammer",    
			"����������"	:	"liangyin hammer",    
			"�������ʹ�"	:	"bingtie hammer",    
			"����������"	:	"bagua hammer",    
			"�޹��ͽ�"	:	"leigu hammer",    
			"��ͷ���Ӵ�"	:	"longtou hammer",   
			"����������"	:	"baleng hammer",    
			"����������"	:	"bagua hammer",    
			"�ڻ�ͭ��"	:	"heihu hammer",    
			"�ڽ�"	:	"wujin hammer",    
			"ѹ��������"	:	"lanlong hammer",    
			"�����ͭ��"	:	"chitong hammer",    
			"����"	:	"guasuo hammer",    
			"�˱���ⴸ"	:	"dianguang hammer",    
			"��ͭ���Ӵ�"	:	"lianzi hammer",    
			"����Ͻ�"	:	"zijin hammer",    
			"����ͭ��"	:	"baleng hammer",    
			"��Բ��"	:	"hunyuan hammer",    
			"��ͭ�ѹϴ�"	:	"wogua hammer",   
			"��ĸԧ�촸"	:	"zimu hammer",    
			"�������Ӵ�"	:	"lianzi hammer",    
			"�˽��Ͻ�"	:	"bajiao hammer",    
			"��ͭ��"	:	"hongtong hammer",    
			"�˱�������"	:	"babao hammer",    
		]),
	"sword"		:	
		([
			"���ƹŶ���"	:	"guding sword",   
			"�����̺罣"	:	"liuhong sword",    
			"������潣"	:	"qingfeng sword",    
			"͸����"	:	"toulong sword",    
			"ɥ�ű���"	:	"sanmeng sword",    
			"�ϵ���˪��"	:	"zidian sword",    
			"��˪��"	:	"zishuang sword",    
			"���齣"	:	"biling sword",    
			"���߱���"	:	"panshe sword",    
			"��������"	:	"panlong sword",    
			"���ǽ�"	:	"tianlang sword",    
			"�ڹ���"	:	"wugou sword",    
			"��ֽ�"	:	"qinggang sword",    
			"ԧ�콣"	:	"yanyang sword",    
			"��Ƽ��"	:	"qingping sword",    
			"̫�Ͻ�"	:	"taihe sword",    
			"���»�����"	:	"huolong sword",    
			"������"	:	"qinglong sword",    
			"������"	:	"zhulong sword",    
			"������"	:	"kunlong sword",    
			"���⽣"	:	"hanguang sword",    
			"��Ҷ��"	:	"liuye sword",    
			"���콣"	:	"fentian sword",    
			"��Ҷ��潣"	:	"luoye sword",   
			"������ֽ�"	:	"qinggang sword",    
			"���罣"	:	"changhong sword",   
			"ն�ɽ�"	:	"zhanxian sword",    
			"������"	:	"wulong sword",    
			"���ƽ�"	:	"qingyun sword",    
			"�滨����"	:	"lihua sword",    
			"�׹⽣"	:	"baiguang sword",    
			"���Ʊ���"	:	"caiyun sword",    
		]),
	"staff"		:	
		([
			"������"	:	"yinyang staff",   
			"�X����"	:	"lilai staff",  
			"ī����"	:	"mojiao staff",  
			"ţ����"	:	"niujiao staff",  
			"������"	:	"dulong staff",  
			"����������"	:	"woyu staff",  
			"����������"	:	"dingzi staff",  
			"����������"	:	"huaibao staff",  
			"��ͷ��"	:	"longtou staff",  
			"��ͷ��"	:	"hutou staff", 
			"������"	:	"qixing staff",  
			"����˫����"	:	"hushou staff",  
			"ԧ����"	:	"yanyang staff",  
			"����������"	:	"woyu staff",  
			"������"	:	"chenxiang staff",  
			"��§��ͷ��"	:	"goulou staff",  
			"����ԧ����"	:	"yanyang staff", 
		]),
	"club"		:	
		([
			"ˮ��������"	:	"qiulong club",   
			"��ɽ��"	:	"kaishan club", 
			"����������"	:	"dingding club", 
			"������޼��"	:	"shenjin club", 
			"�Ͻ������"	:	"zijin club", 
			"���Ͱ�"	:	"wuyou club", 
			"�����"	:	"baleng club", 
			"��ͷ����"	:	"longtou club", 
			"������"	:	"huntie club", 
			"���"	:	"tiangang club", 
			"���������"	:	"dulong club", 
			"���߰�"	:	"xingzhe club", 
			"����������"	:	"langya club", 
			"��ͭ��޼��"	:	"qingtong club", 
			"������˿��"	:	"luosi club", 
			"��˿���߰�"	:	"tengshe club", 
			"���������"	:	"jinguang club", 
			"�ٶ�������"	:	"baiding club", 
			"��������"	:	"ziteng club", 
			"��ͭ���"	:	"qingtong club", 
			"��˿���"	:	"jinsi club",
		]),
	"whip"		:	
		([
			"������"	:	"liangyin whip",
			"��ڸֱ�"	:	"zhujie whip",
			"��β��"	:	"baowei whip", 
			"�򽫱�"	:	"dajiang whip", 
			"�չ������"	:	"tuogu whip", 
			"������"	:	"jinlong whip", 
			"��β�ֱ�"	:	"huwei whip", 
			"������"	:	"bingtie whip", 
			"��ͷ��β��"	:	"longtou whip", 
			"���۸ֱ�"	:	"huyan whip", 
			"��˿����"	:	"jinsi whip", 
			"��«��"	:	"hulu whip", 
			"��Ǳ�"	:	"guigu whip", 
			"��β��"	:	"yugu whip", 
			"�߹Ǳ�"	:	"shegu whip", 
			"��˿����"	:	"yinsi whip", 
			"����ɨ����"	:	"zheyun whip", 
		]),

	"cloth"		:	
		([
			"�鲼��"	:	"mabu cloth",
			"�޲���"	:	"mianbu cloth",
			"����"	:	"choubu cloth",
			"��ѩ��"	:	"feixue cloth",
			"ҹħ��"	:	"yemo cloth",
			"��˿��"	:	"qingsi cloth",
			"������"	:	"jiutian cloth",
			"������"	:	"xuwu cloth",
			"��ڤ��"	:	"qingming cloth",
			"������"	:	"yunluo cloth",
			"˿����"	:	"silk cloth",
		]),
	"head"		:	
		([
			"������ͷ"	:	"naolong kui",
			"ҹ����"	:	"yeming kui",
			"�����"	:	"fengchi kui",
			"ͭ��Ҷ��"	:	"heye kui",
			"�ƽ�˧�ֿ�"	:	"huangjin kui", 
			"������"	:	"yinlian kui",
			"��ˮ��"	:	"fenshui kui",
			"��ﳯ����"	:	"chaoyang kui", 
			"���������"	:	"fengchi kui", 
			"������"	:	"langya kui", 
			"��ﻨ��"	:	"wufeng kui", 
			"̫���"	:	"taisui kui", 
			"�����"	:	"zuantian kui",
			"������ͷ��"	:	"hutou kui", 
			"���ӿ�"	:	"baozi kui", 
			"�������"	:	"hudie kui", 
			"˫���"	:	"shuangfeng guan", 
			"����"	:	"jinfeng guan",  
			"����"	:	"chijin guan",  
			"��ϼ��"	:	"jinxia guan", 
			"�Ͻ��"	:	"zijin guan",  
			"�������"	:	"shufa guan",  
			"���������"	:	"lieyan guan", 
		]),
	"neck"		:	
		([
			"�ں�����"	:	"heihu necklace",
			"Ů����"	:	"nvshen necklace",
			"������"	:	"yin necklace",
			"ͭ����"	:	"tong necklace",
			"������"	:	"jin necklace",
			"��������"	:	"lanyu necklace",
			"��ˮ������"	:	"shuijing necklace",
			"��ͭ����"	:	"qingtong necklace",
			"��ͷ����"	:	"congtou necklace",
			"��������"	:	"kulou necklace",
			"��������"	:	"gushu necklace",
			"�������"	:	"feicui necklace",
			"��������"	:	"binglin necklace",
		]),
	"armor"		:
		([
			"��Ҷ������"	:	"liuye armor",
			"��Ҷ���ۼ�"	:	"yulin armor",
			"��Ҷ���ۼ�"	:	"longlin armor",
			"������"	:	"bingtie armor", 
			"�������"	:	"chijin armor", 
			"�ƽ��"	:	"huangjin armor",
			"�걳��"	:	"guibei armor",
			"ī���"	:	"moyu armor",
			"��ͭ��Ҷ��"	:	"chitong armor",
			"��װ��"	:	"yinzhuang armor", 
			"����������"	:	"lianhuan armor",
			"������Ƽ�"	:	"yueluo armor",
			"��˿����"	:	"jinsi armor",
			"���ټ�"	:	"ziteng armor",
			"�Ͻ��ļ�"	:	"huxin armor", 
			"��Ҷ������"	:	"heye armor", 
		]),
	"surcoat"	:	
		([
			"ҹ������"	:	"yeguang pifeng",
			"�ƽ�����"	:	"huangjin pifeng",
			"�಼����"	:	"mianbu pifeng",
			"��Ƥ����"	:	"yangpi pifeng",
			"��ж���"	:	"chouduan pifeng",
			"��춷��"	:	"chihong pifeng",
			"�������"	:	"lingjiao pifeng",
			"ս������"	:	"zhanyue pifeng",
			"��������"	:	"yishou pifeng",
		]),
	"waist"		:	
		([
			"��������"	:	"fanbu waist",
			"��Ƥ����"	:	"zhenpi waist",
			"��֯����"	:	"bianzhi waist",
			"�ֲ�����"	:	"cubu waist",
			"��������"	:	"shengtie waist",
			"��������"	:	"hupo waist",
			"��������"	:	"binglin waist",
			"��������"	:	"baiying waist",
			"�������"	:	"feicui waist",
		]),
	"wrists"	:	
		([
			"�ֲ�����"	:	"cubu wrists",
			"������"	:	"zizhu wrists",
			"��ľ����"	:	"gumu wrists",
			"��ͭ����"	:	"qingtong wrists",
			"��������"	:	"jingtie wrists",
			"��令��"	:	"feicui wrists",
			"�ƽ���"	:	"huangjin wrists",
			"���ۻ���"	:	"bingling wrists",
		]),
	"finger"	:
		([
			"�����ָ"	:	"yongheng ring",
			"����ָ"	:	"hua ring",
			"����ָ"	:	"yin ring",
			"���Ͻ�ָ"	:	"weiyan ring",
			"�����ָ"	:	"shouling ring",
			"������ָ"	:	"gushu ring",
			"��ʿ��ָ"	:	"yinshi ring",
			"ʮ�ֹǽ�"	:	"shizi ring",
			"ˮ����ָ"	:	"shuijing ring",
			"���۽�ָ"	:	"bingling ring",
			"����ָ"	:	"feicui ring",
			"��ѩ��ָ"	:	"feixue ring",
			"�����ָ"	:	"zizhu ring",
			"�޹ǽ�ָ"	:	"shougu ring",
		]),
	"hands"		:	
		([
			"��������"	:	"liuyun glove",
			"��������"	:	"chilian glove",
			"��������"	:	"xuwu glove",
			"�ֽ�����"	:	"liujin glove",
			"��������"	:	"bingtie glove",
		]),
	"boots"		:	
		([
			"����ѥ"	:	"liuyun shoes",
			"����ѥ"	:	"chilian shoes",
			"����ѥ"	:	"xuwu shoes",
			"�ֽ�ѥ"	:	"liujin shoes",
			"����ѥ"	:	"huolong shoes",
			"��Ƥѥ"	:	"shoupi shoes",
			"ͭ��ѥ"	:	"tongya shoes",
			"����ѥ"	:	"jingtie shoes",
			"�˷�ѥ"	:	"chengfeng shoes",
			"����ѥ"	:	"huwen shoes",
			"����ѥ"	:	"polang shoes",
		]),
]);

array item_color = ({
  	HIW, 	HIB, 	HIC, 	HIR, 	HIM, 	HIY, 	HIG,
  	WHT, 	BLU, 	CYN, 	RED, 	MAG, 	YEL, 	NOR,
});
