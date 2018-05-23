#include "CsBoBo_STM32F10X_GPIO.h"

/*******ʹ�÷���***********************************************************/
/*

@��:	GPIO_Common_Init(GPIOA,GPIO_Pin_2|GPIO_Pin_3,GPIO_Mode_Out_PP);	//GPIO��ʼ��
		��ʼ��GPIOA	;PA2��PA3;�������
	
*/
/*************************************************************************/
/*
@��:	GPIO_ResetBits(GPIOD,GPIO_Pin_2);	//��������

@��:	GPIO_SetBits(GPIOD,GPIO_Pin_2);		//�����ø�

@��:	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)//��ȡָ���˿ڹܽŵ�����	

@��:	GPIO_ReadInputData(GPIOD)	//��ȡָ���� GPIO �˿�����

@��:	GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)//��ȡָ���˿ڹܽŵ����

@��:	GPIO_Write(GPIOD, 0x55)//��ָ�� GPIO ���ݶ˿�д������
*/
/*************************************************************************/
/*
//����1��GPIO_TypeDef
					GPIOA
					GPIOB
					GPIOC
					GPIOD
					GPIOF
					GPIOG
					GPIOH
					GPIOI
					GPIOJ
					GPIOK
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

//����3����Ӧģʽ	 GPIO_Mode				����			����
					GPIO_Mode_AIN 			ģ������		ADC����
					GPIO_Mode_IN_FLOATING 	��������		����
					GPIO_Mode_IPD 			��������
					GPIO_Mode_IPU 			��������		���벶��
					GPIO_Mode_Out_OD 		��©���		I2C�� SMBUS ͨѶ
					GPIO_Mode_Out_PP 		�������		����С��
					GPIO_Mode_AF_OD 		���ÿ�©���
					GPIO_Mode_AF_PP 		�����������	PWM
//����3��GPIO�ٶ�
					GPIO_Speed_10MHz
					GPIO_Speed_2MHz
					GPIO_Speed_50MHz
*/
/********************************************************************/

/*
�� PA15�� JTDI��������ģʽ
�� PA14�� JTCK��������ģʽ
�� PA13�� JTMS��������ģʽ
�� PB4�� JNTRST��������ģʽ

JTMS/SWDIO 		���� JTAGģʽѡ�� ����/��� ������������/��� 		PA13
JTCK/SWCLK 		���� JTAGʱ�� 		���� 	����ʱ�� 				PA14
JTDI 			���� JTAG��������  ����  	����					PA15
JTDO/TRACESWO 	��� JTAG�������  ���� 	����ʱΪTRACESWO�ź� 	PB3
JNTRST 			���� JTAGģ�鸴λ  ����  	����					PB4
��ʹ���������ţ�
//�ر�jtag �ı�ָ���ܽŵ�ӳ��	JTAG-DP ʧ�� + SW-DP ʹ��
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	
*/


uint32_t Get_GPIO_PeriphClockCmd(GPIO_TypeDef* GPIOx)
{
	if		(GPIOx==GPIOA){return RCC_APB2Periph_GPIOA;}
	else if	(GPIOx==GPIOB){return RCC_APB2Periph_GPIOB;}
	else if	(GPIOx==GPIOC){return RCC_APB2Periph_GPIOC;}
	else if	(GPIOx==GPIOD){return RCC_APB2Periph_GPIOD;}
	else if	(GPIOx==GPIOE){return RCC_APB2Periph_GPIOE;}
	else if	(GPIOx==GPIOF){return RCC_APB2Periph_GPIOF;}
	else if	(GPIOx==GPIOG){return RCC_APB2Periph_GPIOG;}
	return 0;
}

void GPIO_Common_Init(GPIO_TypeDef* GPIOx,u16 GPIO_PIN,GPIOMode_TypeDef GPIO_Mode,GPIOSpeed_TypeDef GPIO_Speed)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;	//����һ��GPIO_InitTypeDef���͵Ľṹ��
	
	uint32_t GPIO_PeriphClockCmd;
	GPIO_PeriphClockCmd=Get_GPIO_PeriphClockCmd(GPIOx);
	
	RCC_APB2PeriphClockCmd( GPIO_PeriphClockCmd, ENABLE);	//������ص�GPIO����ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN;	//ѡ��Ҫ���Ƶ�GPIO����	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode; //��������ģʽ

 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;	//������������

	GPIO_Init(GPIOx, &GPIO_InitStructure);	//���ÿ⺯������ʼ��GPIO
}

/*
  * log:

  *	2018��4��6��
	�޸ĳ�ʼ����������
	Programmer:����

  *	2016��7��8��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
