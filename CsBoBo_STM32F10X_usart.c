#include "CsBoBo_STM32F10X_usart.h"
#include "CsBoBo_STM32F10X_LIB.h"
/******ʹ�÷���****************************************************************************************************/
/*
@��:	
		USART_init(	USART2,
					GPIOD,GPIO_Pin_5,	
					GPIOD,GPIO_Pin_6,
					9600,					//������
					USART_WordLength_8b,	//8λ�ֳ� �ֳ�(����λ+У��λ)
					USART_StopBits_1,		//ֹͣλ 1	λ
					USART_Parity_No,		//��ʹ��У��
					USART_Mode_Rx | USART_Mode_Tx,	//���պͷ���ģʽ
					USART_HardwareFlowControl_None,	//Ӳ��������ʧ��
					0,0
					);

	����1��USART���
						USART1
						USART2
						USART3
						UART4
						UART5

	����2��TX GPIO 

	����3��TX GPIO_Pin

	����4��RX GPIO 

	����5��RX GPIO_Pin 

			��������:	(ͬһ���������ſ�������䣬����: TX(PA9) RX(PB7) )
			����		TX		RX
			USART1		PA9		PA10
						PB6		PB7

			USART2		PA2		PA3
						PD5		PD6 

			USART3		PB10	PB11
						PC10	PC11
						PD8		PD9
						
			UART4		PC10	PC11
										
			UART5		PC12	PD2
			
	����6��������ȡֵ��Χ(600,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,230400,460800)
	
	����7���ֳ�(����λ+У��λ)
			USART_WordLength_8b		8λ�ֳ�
			USART_WordLength_9b		9λ�ֳ�

	����8��ֹͣλ
			USART_StopBits_1		ֹͣλ 1	λ
			USART_StopBits_0_5		ֹͣλ 0.5	λ
			USART_StopBits_2		ֹͣλ 2	λ
			USART_StopBits_1_5		ֹͣλ 1.5	λ

	����9��У��λѡ��
			USART_Parity_No			��ʹ��У��
			USART_Parity_Even		żУ��
			USART_Parity_Odd		��У��

	����10��USARTģʽ���ƣ�
			USART_Mode_Tx		����ģʽ
			USART_Mode_Rx		����ģʽ
			USART_Mode_Rx | USART_Mode_Tx	���պͷ���ģʽ
	
	����11��Ӳ�������ƣ�
			USART_HardwareFlowControl_None		Ӳ��������ʧ��
			USART_HardwareFlowControl_RTS		��������RTSʹ��
			USART_HardwareFlowControl_CTS		�������CTSʹ��
			USART_HardwareFlowControl_RTS_CTS	RTS��CTSʹ��

	����12����Ӧ�������ȼ�����	��ֵԽ�����ȼ�Խ��

	����13����Ӧ��Ӧ���ȼ�����	��ֵԽ�����ȼ�Խ��
*/
/******************************************************************************************************************/

/*

@��:	USART_SendByte(USART1,c);	//����һ���ַ���
		����1��USART_TypeDef* ��
					USART1
					USART2
					USART3
					UART4
					UART5
		����2��unsigned char ������
		
@��:	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//����һ������

		����1��USART_TypeDef* ��
					USART1
					USART2
					USART3
					UART4
					UART5
		����2��unsigned char ��ָ��
		����3�����ݸ���
************************************************************************
@ע:

	���մ�������ͨ���жϽ��գ�ͨ����ʱ���ж��Ƿ�ʱ��
��CsBoBo_STM32F10X_usart.h�����ó�ʱʱ�䣬����ջ�������С,���δ�õ��Ĵ��ڿ���ע�ͣ���Լ�ڴ棬

����Ϊ��ʱ����ӳ�ʱ�㷨�Ĵ���:

#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
USART_ReceiveOvertimeProcess();
#endif


������ʹ�ô���ʱ�Ĵ��ڽ��մ���

NVIC_Configuration(NVIC_PriorityGroup_4);//�������ȼ����飺�������ȼ�����Ӧ���ȼ�
TIM_Common_Init(2,7200,10,TIM_CounterMode_Up,3,0);	//��ʱ����ʼ�� 1MS
USART_init(	USART2,
			GPIOD,GPIO_Pin_5,	
			GPIOD,GPIO_Pin_6,
			9600,					//������
			USART_WordLength_8b,	//8λ�ֳ� �ֳ�(����λ+У��λ)
			USART_StopBits_1,		//ֹͣλ 1	λ
			USART_Parity_No,		//��ʹ��У��
			USART_Mode_Rx | USART_Mode_Tx,	//���պͷ���ģʽ
			USART_HardwareFlowControl_None,	//Ӳ��������ʧ��
			0,0
			);	//���ڳ�ʼ��

if(Get_USART_ready_buf_ok(USART1))	//�жϳ�ʱ��һ֡���ݽ��ճɹ�
{
	Clean_USART_ready_buf_OK(USART1);//��������Ƿ������ϱ�־
	
	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//�ط�
	
	Clean_USART_ready_buf(USART1);//������ڻ�������
}

USART1_ready_buf ���յ�������
USART1_ready_buf_len �������ݳ���

*/
/******************************************************************************************************************/
USART_TypeDef* USART_printf;

#ifdef USING_USART1
uint8_t USART1_receive_buf[USART1_BUF_SIZE];	//���ݽ��ջ�����
uint8_t USART1_ready_buf[USART1_BUF_SIZE];		//���ճɹ����������
static int32_t USART1_ReceiveTimeCounter = 0;	//��ʱʣ��ʱ��
__IO uint16_t USART1_receive_index=0; 		//���ڽ��յ����ݳ���
__IO uint8_t USART1_ready_buf_ok = 0;		//�Ƿ�ɹ�����
__IO uint16_t USART1_ready_buf_len = 0;		//�ɹ����պ�����ݳ���
#endif

#ifdef USING_USART2
uint8_t USART2_receive_buf[USART2_BUF_SIZE],USART2_ready_buf[USART2_BUF_SIZE];
static int32_t USART2_ReceiveTimeCounter = 0;
__IO uint16_t USART2_receive_index=0; 
__IO uint8_t USART2_ready_buf_ok = 0;
__IO uint16_t USART2_ready_buf_len=0;
#endif

#ifdef USING_USART3
static int32_t USART3_ReceiveTimeCounter = 0;
uint8_t USART3_receive_buf[USART3_BUF_SIZE],USART3_ready_buf[USART3_BUF_SIZE];
__IO uint16_t USART3_receive_index=0; 
__IO uint8_t USART3_ready_buf_ok = 0;
__IO uint16_t USART3_ready_buf_len=0;
#endif

#ifdef USING_UART4
uint8_t UART4_receive_buf[UART4_BUF_SIZE],UART4_ready_buf[UART4_BUF_SIZE];
static int32_t UART4_ReceiveTimeCounter = 0;
__IO uint16_t UART4_receive_index=0; 
__IO uint8_t UART4_ready_buf_ok = 0;
__IO uint16_t UART4_ready_buf_len=0;
#endif

#ifdef USING_UART5
uint8_t UART5_receive_buf[UART5_BUF_SIZE],UART5_ready_buf[UART5_BUF_SIZE];
static int32_t UART5_ReceiveTimeCounter = 0;
__IO uint16_t UART5_receive_index=0; 
__IO uint8_t UART5_ready_buf_ok = 0;
__IO uint16_t UART5_ready_buf_len=0;
#endif

void USART1_ISR(void); //�����жϺ���
void USART2_ISR(void); //�����жϺ���
void USART3_ISR(void); //�����жϺ���
void UART4_ISR(void); //�����жϺ���
void UART5_ISR(void); //�����жϺ���

/**********************�жϺ���***************************************************************************************************/
#if defined(STM32F10X_LD)||defined(STM32F10X_LD_VL)||defined(STM32F10X_MD)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)		
void USART1_IRQHandler(void)
{
	#ifdef USING_USART1
	USART1_ISR();
	#endif
}

void USART2_IRQHandler(void)
{
	#ifdef USING_USART2
	USART2_ISR();
	#endif
}
#endif

#if defined(STM32F10X_MD)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)					
void USART3_IRQHandler(void)
{
	#ifdef USING_USART3
	USART3_ISR();
	#endif
}
#endif

#if defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)
void UART4_IRQHandler(void)
{
	#ifdef USING_UART4
	UART4_ISR();
	#endif
}

void UART5_IRQHandler(void)
{
	#ifdef USING_UART5
	UART5_ISR();
	#endif
}
#endif
/**********************���ж���ִ�еĴ���***************************************************************************************************/
void USART_ReceiveOvertimeProcess(void)	//���ж���ִ�еĴ���
{
	#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
	uint16_t i = 0;	
	#endif
	
	#ifdef USING_USART1
	if(USART1_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART1_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART1_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART1_ready_buf_len = USART1_receive_index;

			for(i = 0;i <= USART1_ready_buf_len; i ++)
				USART1_ready_buf[i] = USART1_receive_buf[i];
	
			USART1_ready_buf_ok = UART_OK;
			USART1_receive_index=0;
			USART1_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_USART2
	if(USART2_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART2_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART2_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART2_ready_buf_len = USART2_receive_index;

			for(i = 0;i <= USART2_ready_buf_len; i ++)
				USART2_ready_buf[i] = USART2_receive_buf[i];
	
			USART2_ready_buf_ok = UART_OK;
			USART2_receive_index=0;
			USART2_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_USART3
	if(USART3_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART3_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART3_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART3_ready_buf_len = USART3_receive_index;

			for(i = 0;i <= USART3_ready_buf_len; i ++)
				USART3_ready_buf[i] = USART3_receive_buf[i];
	
			USART3_ready_buf_ok = UART_OK;
			USART3_receive_index=0;
			USART3_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_UART4
	if(UART4_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART4_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART4_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART4_ready_buf_len = UART4_receive_index;

			for(i = 0;i <= UART4_ready_buf_len; i ++)
				UART4_ready_buf[i] = UART4_receive_buf[i];
	
			UART4_ready_buf_ok = UART_OK;
			UART4_receive_index=0;
			UART4_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_UART5
	if(UART5_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART5_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART5_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART5_ready_buf_len = UART5_receive_index;

			for(i = 0;i <= UART5_ready_buf_len; i ++)
				UART5_ready_buf[i] = UART5_receive_buf[i];
	
			UART5_ready_buf_ok = UART_OK;
			UART5_receive_index=0;
			UART5_ReceiveTimeCounter = 0;
		}
	}
	#endif
}
/*************************************************************************************************************************/
/**********************����1�жϽ���һ���ַ�***************************************************************************************************/
#ifdef USING_USART1
void USART1_ISR(void)   
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//�ж��Ƿ����ж�
	{
		USART1_ReceiveTimeCounter = USART1_RECEIVE_OVERTIME;

		if(USART1_receive_index >= USART1_BUF_SIZE)//������λ��Խ�磬��ô��ͷ��ʼ���
			USART1_receive_index = 0;
		
		USART1_receive_buf[USART1_receive_index++] = (uint8_t)USART_ReceiveData(USART1);//�����ַ�����λ�ü�1		
	}	
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//���ش���ֻҪ��״̬�Ĵ��������ݼĴ����Ϳ��Զ�����˱�־
	{
		(void)USART_ReceiveData(USART1);
	}

} 
#endif

#ifdef USING_USART2
void USART2_ISR(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�ж��Ƿ����ж�
	{	
		USART2_ReceiveTimeCounter = USART2_RECEIVE_OVERTIME;
		
		if(USART2_receive_index >= USART2_BUF_SIZE)	//������λ��Խ�磬��ô��ͷ��ʼ���
			USART2_receive_index = 0;
		
		USART2_receive_buf[USART2_receive_index++] = (uint8_t)USART_ReceiveData(USART2);//�����ַ�����λ�ü�1
		
	}		
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//���ش���ֻҪ��״̬�Ĵ��������ݼĴ����Ϳ��Զ�����˱�־
	{
		(void)USART_ReceiveData(USART2);
	}
}
#endif

#ifdef USING_USART3
void USART3_ISR(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART3_ReceiveTimeCounter = USART3_RECEIVE_OVERTIME;
		if(USART3_receive_index >= USART3_BUF_SIZE)
			USART3_receive_index = 0;
		
		USART3_receive_buf[USART3_receive_index++] = (uint8_t)USART_ReceiveData(USART3);
		
	}
		
	if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(USART3);
	}
}
#endif

#ifdef USING_UART4
void UART4_ISR(void)
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		UART4_ReceiveTimeCounter = UART4_RECEIVE_OVERTIME;
		if(UART4_receive_index >= UART4_BUF_SIZE)
			UART4_receive_index = 0;
		
		UART4_receive_buf[UART4_receive_index++] = (uint8_t)USART_ReceiveData(UART4);
		
	}
		
	if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART4);
	}
}
#endif

#ifdef USING_UART5
void UART5_ISR(void)
{
	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{		
		UART5_ReceiveTimeCounter = UART5_RECEIVE_OVERTIME;
		if(UART5_receive_index >= UART5_BUF_SIZE)
			UART5_receive_index = 0;
		
		UART5_receive_buf[UART5_receive_index++] = (uint8_t)USART_ReceiveData(UART5);
		
	}
		
	if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART5);
	}
}
#endif

/****************************************************************************************************************************************/

//�жϴ����Ƿ�������
//���ճɹ����� UART_OK
//����ʧ�ܷ��� UART_ERROR
int Get_USART_ready_buf_ok(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)return USART1_ready_buf_ok;
#endif	
	
#ifdef USING_USART2
	if(usart==USART2)return USART2_ready_buf_ok;
#endif

#ifdef USING_USART3
	if(usart==USART3)return USART3_ready_buf_ok;
#endif
	
#ifdef USING_UART4
	if(usart==UART4)return UART4_ready_buf_ok;
#endif	
	
#ifdef USING_UART5
	if(usart==UART5)return UART5_ready_buf_ok;
#endif			
	return UART_ERROR;
}

//��������Ƿ������ϱ�־
void Clean_USART_ready_buf_OK(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)
	{
		USART1_ready_buf_ok=UART_ERROR;
	}
#endif	
	
#ifdef USING_USART2
	if(usart==USART2)
	{
		USART2_ready_buf_ok=UART_ERROR;
	}
#endif

#ifdef USING_USART3
	if(usart==USART3)
	{
		USART3_ready_buf_ok=UART_ERROR;
	}		
#endif
	
#ifdef USING_UART4
	if(usart==UART4)
	{
		UART4_ready_buf_ok=UART_ERROR;
	}		
#endif	
	
#ifdef USING_UART5
	if(usart==UART5)
	{
		UART5_ready_buf_ok=UART_ERROR;
	}
#endif			

}

//������ڻ�������
void Clean_USART_ready_buf(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)
	{
		memset(USART1_ready_buf,0,USART1_BUF_SIZE);
	}
#endif	
	
#ifdef USING_USART2
	if(usart==USART2)
	{
		memset(USART2_ready_buf,0,USART2_BUF_SIZE);
	}
#endif

#ifdef USING_USART3
	if(usart==USART3)
	{
		memset(USART3_ready_buf,0,USART3_BUF_SIZE);
	}		
#endif
	
#ifdef USING_UART4
	if(usart==UART4)
	{
		memset(UART4_ready_buf,0,UART4_BUF_SIZE);
	}		
#endif	
	
#ifdef USING_UART5
	if(usart==UART5)
	{
		memset(UART5_ready_buf,0,UART5_BUF_SIZE);
	}
#endif			

}

/****************************************************************************************************************************************/

static void USART_RCC_PeriphClockCmd(USART_TypeDef * USARTx)
{
	#if defined(STM32F10X_LD)||defined(STM32F10X_LD_VL)||defined(STM32F10X_MD)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)		
	if		(USARTx==USART1) {	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);}
	else if	(USARTx==USART2) {	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);}
	#endif
	
	#if defined(STM32F10X_MD)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)					
	else if	(USARTx==USART3) {	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);}
	#endif
	
	#if defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)
	else if	(USARTx==UART4) {RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);}
	else if	(USARTx==UART5) {RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);}
	#endif

}

static uint8_t Get_NVIC_IRQChannel_USART(USART_TypeDef * USARTx)
{
	#if defined(STM32F10X_LD)||defined(STM32F10X_LD_VL)||defined(STM32F10X_MD)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)		
	if		(USARTx==USART1) {return USART1_IRQn;}
	else if	(USARTx==USART2) {return USART2_IRQn;}
	#endif
	
	#if defined(STM32F10X_MD)||defined(STM32F10X_MD_VL)||defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)					
	else if	(USARTx==USART3) {return USART3_IRQn;}
	#endif
	
	#if defined(STM32F10X_HD)||defined(STM32F10X_HD_VL)||defined(STM32F10X_XL)||defined(STM32F10X_CL)
	else if	(USARTx==UART4) {return UART4_IRQn;}
	else if	(USARTx==UART5) {return UART5_IRQn;}
	#endif
	
	return 0;
}

static void USART_GPIO_PinRemapConfig	(	USART_TypeDef * USARTx,				
											GPIO_TypeDef* USART_TX_GPIOx,	
											u16 USART_TX_PIN,
											GPIO_TypeDef* USART_RX_GPIOx,
											u16 USART_RX_PIN
										)	//���ù���ӳ��
{
		if(USARTx==USART1)
		{
			if(USART_TX_GPIOx==GPIOB && USART_TX_PIN==GPIO_Pin_6 && USART_TX_GPIOx==GPIOB && USART_TX_PIN==GPIO_Pin_7)
			{
				GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 ���ù���ӳ��
			}
		}
		if(USARTx==USART2)
		{
			if(USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_5 && USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_6)
			{
				GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 ���ù���ӳ��
			}
		}
		if(USARTx==USART3)
		{
			if(USART_TX_GPIOx==GPIOC && USART_TX_PIN==GPIO_Pin_10 && USART_TX_GPIOx==GPIOC && USART_TX_PIN==GPIO_Pin_11)
			{
				GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);//USART3 ���ù��ܲ���ӳ��1
			}
			if(USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_8 && USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_9)
			{
				GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 ���ù��ܲ���ӳ��2
			}			
		}
		
}

//���ڳ�ʼ������
void USART_init	(	USART_TypeDef * USARTx,			
					GPIO_TypeDef* USART_TX_GPIOx,	
					u16 USART_TX_PIN,
					GPIO_TypeDef* USART_RX_GPIOx,
					u16 USART_RX_PIN,
					uint32_t USART_BaudRate,			//����������
					uint16_t USART_WordLength,			//�ֳ�(����λ+У��λ)
					uint16_t USART_StopBits,			//ֹͣλ		
					uint16_t USART_Parity,				//У��λѡ��
					uint16_t USART_Mode,				//USARTģʽ����
					uint16_t USART_HardwareFlowControl,	//Ӳ��������
					uint8_t PreemptionPriority,			//��ռ���ȼ�
					uint8_t SubPriority					//�����ȼ�
				)
{

	USART_InitTypeDef USART_InitStructure;
	uint8_t NVIC_IRQChannel_USART;
	
	USART_RCC_PeriphClockCmd(USARTx);	/* ʹ�� USART ʱ�� */
	
	GPIO_Common_Init(USART_TX_GPIOx,USART_TX_PIN,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);	//GPIO��ʼ��
	GPIO_Common_Init(USART_RX_GPIOx,USART_RX_PIN,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);	//GPIO��ʼ��

	USART_GPIO_PinRemapConfig(USARTx,USART_TX_GPIOx,USART_TX_PIN,USART_RX_GPIOx,USART_RX_PIN);	//���ù���ӳ��
	
	USART_InitStructure.USART_BaudRate = USART_BaudRate;/* ���������ã�*/	
	USART_InitStructure.USART_WordLength = USART_WordLength;/* �ֳ�(����λ+У��λ)��8 USART_WordLength_8b*/
	USART_InitStructure.USART_StopBits = USART_StopBits;	/* ֹͣλ��1��ֹͣλ USART_StopBits_1*/
	USART_InitStructure.USART_Parity = USART_Parity;	/* У��λѡ�񣺲�ʹ��У�� USART_Parity_No*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl	/* Ӳ�������ƣ���ʹ��Ӳ���� USART_HardwareFlowControl_None*/;
	USART_InitStructure.USART_Mode = USART_Mode;	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� USART_Mode_Rx | USART_Mode_Tx*/
	USART_Init(USARTx, &USART_InitStructure); 	/* ���USART��ʼ������ */	
	
	NVIC_IRQChannel_USART=Get_NVIC_IRQChannel_USART(USARTx);
	NVIC_Init_IRQChannel(NVIC_IRQChannel_USART,PreemptionPriority,SubPriority,ENABLE);//���� NVIC	
	
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	/* ʹ�ܴ��ڽ����ж� */

	USART_Cmd(USARTx, ENABLE);	/* ʹ�ܴ��� */	
}

/******************************************************************************************************************/

void Change_printf(USART_TypeDef* USART_prt)//�ض��򴮿�ѡ��
{
	USART_printf=USART_prt;
}

//����һ���ֽ�
void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte)	//����һ���ֽ�
{

    	USARTx->DR = (SendByte & (uint16_t)0x01FF);
  		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}
//����һ������
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len)	//����һ������
{
	uint16_t i = 0;
	for(i = 0; i < len; i++)
	{
    	USARTx->DR = (*(SendChars + i) & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

//USART�����ַ���
void UART_SendString(USART_TypeDef* USARTx,char* s)
{
	while(*s)//����ַ���������
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
		USART_SendData(USARTx ,*s++);//���͵�ǰ�ַ�
	}
}
/******************************************************************************************************************/

/*
  * log:

  *	2018��4��27��
	�Ż��������룬�ô�����ӦSTM32F10Xȫϵ��оƬ
	Programmer:����

  *	2018��4��15��
	�����������룬δ�õ��Ĵ��ڲ�ʹ�ó�ʱ������,�����ڴ�ռ��
	����ע��
	Programmer:����

  *	2018��4��6��
	������ʱ���մ���:
		void USART_ReceiveOvertimeProcess(void);	//�ڵδ��ж� SysTick_Handler��ִ�еĴ���
	ɾ�����º�����
		void USART_Putc(unsigned char c);	//����һ���ַ���
		void USART_Puts(unsigned char *str,int num);   //����num������
		void Change_printf(USART_TypeDef* USART_prt);//�ض��򴮿�ѡ��
	ȡ����֮���ǣ�
		void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte);	//����һ���ֽ�
		void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len);	//����һ������
	��������ʱȷ��ʹ��ʲô���ڷ���

	�жϺ���ת��stm32f10x_it.c��,���ӹ淶(Ӧ�����е��жϺ�����Ӧ�÷ŵ�stm32f10x_it.c��)
	
	Programmer:����

  *	2016��7��8��
	�½�����
	ʵ�ֻ�����ʼ������
	ʵ�ֻ�����������չ���
	Programmer:����
	
*/

