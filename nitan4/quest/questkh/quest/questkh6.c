#include <ansi.h>
#define QUESTKH_D(x)      ("/quest/questkh/quest/questkh" + x)

mapping query_questkh() 
{
        if (random(50) == 25) 
        	return QUESTKH_D("7find")->query_questkh();
        if (random(2) == 1)
                return QUESTKH_D("6find")->query_questkh();
	return QUESTKH_D("6kill")->query_questkh(); 
}
