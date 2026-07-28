#include "main.h"
#include "gpio.h"


u8 KEY_GetVal(void)
{
	u8 static stat=0;
	if((!KEY1||KEY2)&&!stat)
	{
		stat=1;
		HAL_Dalay(30);
		if(!KEY1) return 1;
		else if(!KEY2) return 2;
		else return 0;
	}
	else
	{
		if(KEY1&&KEY2) stat=0;
	}
	else
	{
		if(KEY1&&KEY2)stat=0;
	}
	return 0;
}