#include "CsBoBo_STM32F10X_Basic_TIM.h"
#include "CsBoBo_STM32F10X_LIB.h"



/**********������ʱ������ʹ�÷���***************************************************************/
/*
*********************************************************************************************

	Basic_TIM_Init(TIM6,10,7200,1,0);	//��ʼ����ʱ��TIM6,1MS����һ���ж�
	
	ע��Ĭ�ϲ�ʹ�ܶ�ʱ������TIM_Cmd()ʹ�ܶ�ʱ��
	TIM_Cmd(TIM6, ENABLE);		// ������ʹ��
	
*********************************************************************************************
*********************************************************************************************

	TIM_Cmd(TIM6, ENABLE);		// ������ʹ��

*********************************************************************************************
*********************************************************************************************
void Basic_TIM_Init(TIM_TypeDef* TIMx,uint16_t TIM_Period,uint16_t TIM_Prescaler,uint8_t PreemptionPriority,uint8_t SubPriority)
//Ĭ��72M��ʱ��Ƶ�ʣ���ʹ�ܶ�ʱ��

//����1��ѡ�õĶ�ʱ��
			TIM6
			TIM7
//����2���Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period��Ƶ�ʺ����һ�����»����ж� (����Ҫ��1)
			ȡֵ��Χ��0����65535

//����3��ʱ��Ԥ��Ƶֵ(���ü�1)
			ȡֵ��Χ��0����65535
			
//����4����Ӧ�������ȼ�����
			��ֵԽ�����ȼ�Խ��

//����5����Ӧ��Ӧ���ȼ�����
			��ֵԽ�����ȼ�Խ��
*/
/*********************************************************************************/




#if defined(STM32F10X_HD)||defined(STM32F10X_XL)||defined(STM32F10X_CL)
void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update); /* �������жϱ�־ */
		/* Do anything */

    }
}
#endif

#if defined(STM32F10X_LD_VL)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)			
void TIM7_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update); /* �������жϱ�־ */
		/* Do anything */
    }
}
#endif

static uint8_t Get_NVIC_IRQChannel_Basic_TIM(TIM_TypeDef* TIMx)
{
	#if defined(STM32F10X_HD)||defined(STM32F10X_XL)||defined(STM32F10X_CL)
	if(TIMx==TIM6)
	{
		return TIM6_IRQn;
	}
	#endif
	
	#if defined(STM32F10X_LD_VL)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)			
	if(TIMx==TIM7)
	{
		return TIM7_IRQn;		
	}
	#endif	
	return 0;
}

static uint32_t RCC_APB1Periph_Basic_TIM(TIM_TypeDef* TIMx)
{
	if(TIMx==TIM6)
	{
		return RCC_APB1Periph_TIM6;
	}else if(TIMx==TIM7)
	{
		return RCC_APB1Periph_TIM7;		
	}
	return 0;
}

void Basic_TIM_Init(TIM_TypeDef* TIMx,uint16_t TIM_Period,uint16_t TIM_Prescaler,uint8_t PreemptionPriority,uint8_t SubPriority)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint32_t Basic_TIM_CLK=0;
	uint8_t Basic_TIM_NVIC_IRQChannel=0;
	Basic_TIM_CLK=RCC_APB1Periph_Basic_TIM(TIMx);
	
    RCC_APB1PeriphClockCmd(Basic_TIM_CLK, ENABLE);		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M

	Basic_TIM_NVIC_IRQChannel=Get_NVIC_IRQChannel_Basic_TIM(TIMx);
	NVIC_Init_IRQChannel(Basic_TIM_NVIC_IRQChannel,PreemptionPriority,SubPriority,ENABLE);//���� NVIC

	
    TIM_TimeBaseStructure.TIM_Period = TIM_Period-1;		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Prescaler= TIM_Prescaler-1;  // ʱ��Ԥ��Ƶ��Ϊ
	
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);  // ��ʼ����ʱ��			
    TIM_ClearFlag(TIMx, TIM_FLAG_Update);	// ����������жϱ�־λ	  	
    TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);	// �����������ж�			
    TIM_Cmd(TIMx, DISABLE);		// ��������ʹ��

}

/*
  * log:

  *	2018��5��29��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

