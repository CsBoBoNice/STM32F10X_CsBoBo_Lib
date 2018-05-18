#include "CsBoBo_STM32F10X_exti.h"
#include "CsBoBo_STM32F10X_NVIC.h"
/*******ʹ�÷���***********************************************************/
/*

@��:	EXTIX_Init(GPIOA,GPIO_Pin_0,EXTI_Trigger_Falling,0,0);

*/
/*******˵��******************************************************************/
/*	
˵����	��ʼ���������д��Ӧ�жϺ������жϺ����ڱ�ҳ
		�ж���0-4ÿ���ж��߶�Ӧһ���жϺ�����
		�ж���5-9�����жϺ���EXTI9_5_IRQHandler��
		�ж���10-15�����жϺ���EXTI15_10_IRQHandler��	
*/
/*******˵��******************************************************************/
/*
(Ĭ�ϣ�EXTI_Mode_Interrupt�ж�ģʽ���ɻ�ΪEXTI_Mode_Event�¼�����)
//����1��		GPIO_TypeDef
					GPIOA
					GPIOB
					GPIOC
					GPIOD
					GPIOF
					GPIOG
				
//����2����Ӧ����	
					GPIO_Pin_0
					GPIO_Pin_1
					GPIO_Pin_2
					GPIO_Pin_3
					GPIO_Pin_4
					GPIO_Pin_5
					GPIO_Pin_6
					GPIO_Pin_7
					GPIO_Pin_8
					GPIO_Pin_9
					GPIO_Pin_10
					GPIO_Pin_11
					GPIO_Pin_12
					GPIO_Pin_13
					GPIO_Pin_14
					GPIO_Pin_15
					
//����3����Ӧģʽ	 

						EXTI_Trigger 					����
					EXTI_Trigger_Falling 			����������·�½���Ϊ�ж�����
					EXTI_Trigger_Rising 			����������·������Ϊ�ж�����
					EXTI_Trigger_Rising_Falling 	����������·�����غ��½���Ϊ�ж�����

//����4����Ӧ�������ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

//����5����Ӧ��Ӧ���ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

*/
/*****************************************************************************/

//�������ȼ��ߵ��ܽ��������ȼ��͵Ĵ��
//�����ж�ͬʱ����ں˾ͻ�������Ӧ��Ӧ���ȼ��ߵ�

/***�жϺ���**********************************************************************/

void EXTI0_IRQHandler(void)
{		
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������

		EXTI_ClearITPendingBit(EXTI_Line0);  //����жϱ�־λ
	}  
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line1);  //����жϱ�־λ
	}  
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line2);  //����жϱ�־λ
	}  	
}

void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line3);  //����жϱ�־λ
	}	
}

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line4);  //����жϱ�־λ
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line5);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line6);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line7);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line8);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line9);  //����жϱ�־λ
	}		
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line10);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line11);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line12);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line13) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
	
		EXTI_ClearITPendingBit(EXTI_Line13);  //����жϱ�־λ
	}
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line14) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line14);  //����жϱ�־λ
	}	
	/******************************************************************************/	
	if(EXTI_GetITStatus(EXTI_Line15) != RESET)//ȷ���Ƿ������EXTI Line�ж� 
	{
		//�жϴ������
		
		EXTI_ClearITPendingBit(EXTI_Line15);  //����жϱ�־λ
	}
}

static uint32_t Get_EXTI_Line(u16 GPIO_PIN)
{
	switch(GPIO_PIN)
	{
		case GPIO_Pin_0: return EXTI_Line0; 
		case GPIO_Pin_1: return EXTI_Line1;
		case GPIO_Pin_2: return EXTI_Line2; 
		case GPIO_Pin_3: return EXTI_Line3;
		case GPIO_Pin_4: return EXTI_Line4; 
		case GPIO_Pin_5: return EXTI_Line5;
		case GPIO_Pin_6: return EXTI_Line6; 
		case GPIO_Pin_7: return EXTI_Line7;
		case GPIO_Pin_8: return EXTI_Line8; 
		case GPIO_Pin_9: return EXTI_Line9;
		case GPIO_Pin_10: return EXTI_Line10; 
		case GPIO_Pin_11: return EXTI_Line11;
		case GPIO_Pin_12: return EXTI_Line12; 
		case GPIO_Pin_13: return EXTI_Line13;
		case GPIO_Pin_14: return EXTI_Line14; 
		case GPIO_Pin_15: return EXTI_Line15;
	}
	return 0;
}

static uint8_t Get_EXTI_PortSource(GPIO_TypeDef* GPIOx)
{
	if		(GPIOx==GPIOA){return GPIO_PortSourceGPIOA;}
	else if	(GPIOx==GPIOB){return GPIO_PortSourceGPIOB;}
	else if	(GPIOx==GPIOC){return GPIO_PortSourceGPIOC;}
	else if	(GPIOx==GPIOD){return GPIO_PortSourceGPIOD;}
	else if	(GPIOx==GPIOE){return GPIO_PortSourceGPIOE;}
	else if	(GPIOx==GPIOF){return GPIO_PortSourceGPIOF;}
	else if	(GPIOx==GPIOG){return GPIO_PortSourceGPIOG;}

	return 0;	
}

static uint8_t Get_EXTI_PinSource_PIN(u16 GPIO_PIN)
{
	switch(GPIO_PIN)
	{
		case GPIO_Pin_0: return GPIO_PinSource0; 
		case GPIO_Pin_1: return GPIO_PinSource1;
		case GPIO_Pin_2: return GPIO_PinSource2; 
		case GPIO_Pin_3: return GPIO_PinSource3;
		case GPIO_Pin_4: return GPIO_PinSource4; 
		case GPIO_Pin_5: return GPIO_PinSource5;
		case GPIO_Pin_6: return GPIO_PinSource6; 
		case GPIO_Pin_7: return GPIO_PinSource7;
		case GPIO_Pin_8: return GPIO_PinSource8; 
		case GPIO_Pin_9: return GPIO_PinSource9;
		case GPIO_Pin_10: return GPIO_PinSource10; 
		case GPIO_Pin_11: return GPIO_PinSource11;
		case GPIO_Pin_12: return GPIO_PinSource12; 
		case GPIO_Pin_13: return GPIO_PinSource13;
		case GPIO_Pin_14: return GPIO_PinSource14; 
		case GPIO_Pin_15: return GPIO_PinSource15;
	}
	return 0;
}

static uint8_t Get_NVIC_IRQChannel(u16 GPIO_PIN)
{
	switch(GPIO_PIN)
	{
		case GPIO_Pin_0: return EXTI0_IRQn; 
		case GPIO_Pin_1: return EXTI1_IRQn;
		case GPIO_Pin_2: return EXTI2_IRQn; 
		case GPIO_Pin_3: return EXTI3_IRQn;
		case GPIO_Pin_4: return EXTI4_IRQn; 
		case GPIO_Pin_5: return EXTI9_5_IRQn;
		case GPIO_Pin_6: return EXTI9_5_IRQn; 
		case GPIO_Pin_7: return EXTI9_5_IRQn;
		case GPIO_Pin_8: return EXTI9_5_IRQn; 
		case GPIO_Pin_9: return EXTI9_5_IRQn;
		case GPIO_Pin_10: return EXTI15_10_IRQn; 
		case GPIO_Pin_11: return EXTI15_10_IRQn;
		case GPIO_Pin_12: return EXTI15_10_IRQn; 
		case GPIO_Pin_13: return EXTI15_10_IRQn;
		case GPIO_Pin_14: return EXTI15_10_IRQn; 
		case GPIO_Pin_15: return EXTI15_10_IRQn;
	}
	return 0;
}

/*������ص�GPIO����ʱ��*/
static void RCC_APB2PeriphClockCmd_GPIO_Init(u8 GPIOx)
{
	switch(GPIOx)
	{
		case 1:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);return;
		case 2:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);return;
		case 3:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);return;
		case 4:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);return;
		case 5:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);return;
		case 6:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);return;
		case 7:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);return;
	}
	return;
}

/*�õ�GPIO��ţ������ʼ��*/
static u8 Get_GPIO_num(GPIO_TypeDef* GPIOx)
{
	if		(GPIOx==GPIOA){return 1;}
	else if	(GPIOx==GPIOB){return 2;}
	else if	(GPIOx==GPIOC){return 3;}
	else if	(GPIOx==GPIOD){return 4;}
	else if	(GPIOx==GPIOE){return 5;}
	else if	(GPIOx==GPIOF){return 6;}
	else if	(GPIOx==GPIOG){return 7;}
	return 0;
}

static void EXIT_Init_Config(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	uint8_t EXTI_PortSource;
	uint8_t EXTI_PortSource_PIN;
	uint32_t EXTI_Line_V;
	
	EXTI_PortSource=Get_EXTI_PortSource(GPIOx);
	EXTI_PortSource_PIN=Get_EXTI_PinSource_PIN(GPIO_PIN);
	EXTI_Line_V=Get_EXTI_Line(GPIO_PIN);
	
	/* ѡ��EXTI���ź�Դ */
	GPIO_EXTILineConfig(EXTI_PortSource,EXTI_PortSource_PIN);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line_V;/* ѡ�� EXTI �ж�Դ */
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;/* �ж�ģʽ */
	EXTI_InitStructure.EXTI_Trigger = EXTI_Mode;	/* ������ʽ */  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;/* ʹ���ж�/�¼��� */
	EXTI_Init(&EXTI_InitStructure);	
}


/*****************************************************************************/
/*
	�жϳ�ʼ������
*/
void EXTIX_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	u8 GPIO_num;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	uint8_t exti_NVIC_IRQChannel;
	
	GPIO_num=Get_GPIO_num(GPIOx);
	RCC_APB2PeriphClockCmd_GPIO_Init(GPIO_num);//������ص�GPIO����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);/* ����AFIO��ʱ�� */		

	exti_NVIC_IRQChannel=Get_NVIC_IRQChannel(GPIO_PIN);
	NVIC_Init_IRQChannel(exti_NVIC_IRQChannel,PreemptionPriority,SubPriority,ENABLE);//���� NVIC

	 
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;/*ѡ������ */			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;/* ����Ϊ�������� */	
	GPIO_Init(GPIOx, &GPIO_InitStructure); /* ʹ������Ľṹ���ʼ��*/

	EXIT_Init_Config(GPIOx,GPIO_PIN,EXTI_Mode);
}
/*
  * log:

  *	2016��7��6��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

