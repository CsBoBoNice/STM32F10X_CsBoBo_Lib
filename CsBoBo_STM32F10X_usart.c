#include "CsBoBo_STM32F10X_usart.h"
#include "CsBoBo_STM32F10X_LIB.h"
/******使用方法****************************************************************************************************/
/*
@例:	
		USART_init(	USART2,
					GPIOD,GPIO_Pin_5,	
					GPIOD,GPIO_Pin_6,
					9600,					//波特率
					USART_WordLength_8b,	//8位字长 字长(数据位+校验位)
					USART_StopBits_1,		//停止位 1	位
					USART_Parity_No,		//不使用校验
					USART_Mode_Rx | USART_Mode_Tx,	//接收和发送模式
					USART_HardwareFlowControl_None,	//硬件流控制失能
					0,0
					);

	参数1：USART编号
						USART1
						USART2
						USART3
						UART4
						UART5

	参数2：TX GPIO 

	参数3：TX GPIO_Pin

	参数4：RX GPIO 

	参数5：RX GPIO_Pin 

			串口引脚:	(同一个串口引脚可随意搭配，例如: TX(PA9) RX(PB7) )
			串口		TX		RX
			USART1		PA9		PA10
						PB6		PB7

			USART2		PA2		PA3
						PD5		PD6 

			USART3		PB10	PB11
						PC10	PC11
						PD8		PD9
						
			UART4		PC10	PC11
										
			UART5		PC12	PD2
			
	参数6：波特率取值范围(600,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,230400,460800)
	
	参数7：字长(数据位+校验位)
			USART_WordLength_8b		8位字长
			USART_WordLength_9b		9位字长

	参数8：停止位
			USART_StopBits_1		停止位 1	位
			USART_StopBits_0_5		停止位 0.5	位
			USART_StopBits_2		停止位 2	位
			USART_StopBits_1_5		停止位 1.5	位

	参数9：校验位选择
			USART_Parity_No			不使用校验
			USART_Parity_Even		偶校验
			USART_Parity_Odd		奇校验

	参数10：USART模式控制：
			USART_Mode_Tx		发送模式
			USART_Mode_Rx		接收模式
			USART_Mode_Rx | USART_Mode_Tx	接收和发送模式
	
	参数11：硬件流控制：
			USART_HardwareFlowControl_None		硬件流控制失能
			USART_HardwareFlowControl_RTS		发送请求RTS使能
			USART_HardwareFlowControl_CTS		清除发送CTS使能
			USART_HardwareFlowControl_RTS_CTS	RTS和CTS使能

	参数12：对应抢断优先级级别	数值越低优先级越高

	参数13：对应响应优先级级别	数值越低优先级越高
*/
/******************************************************************************************************************/

/*

@例:	USART_SendByte(USART1,c);	//发送一个字符串
		参数1：USART_TypeDef* 型
					USART1
					USART2
					USART3
					UART4
					UART5
		参数2：unsigned char 型数据
		
@例:	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//发送一段数据

		参数1：USART_TypeDef* 型
					USART1
					USART2
					USART3
					UART4
					UART5
		参数2：unsigned char 型指针
		参数3：数据个数
************************************************************************
@注:

	接收串口数据通过中断接收，通过定时器判断是否超时，
在CsBoBo_STM32F10X_usart.h里设置超时时间，与接收缓存区大小,如果未用到的串口可以注释，节约内存，

以下为定时器添加超时算法的代码:

#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
USART_ReceiveOvertimeProcess();
#endif


以下是使用带超时的串口接收代码

NVIC_Configuration(NVIC_PriorityGroup_4);//设置优先级分组：抢断优先级和相应优先级
TIM_Common_Init(2,7200,10,TIM_CounterMode_Up,3,0);	//定时器初始化 1MS
USART_init(	USART2,
			GPIOD,GPIO_Pin_5,	
			GPIOD,GPIO_Pin_6,
			9600,					//波特率
			USART_WordLength_8b,	//8位字长 字长(数据位+校验位)
			USART_StopBits_1,		//停止位 1	位
			USART_Parity_No,		//不使用校验
			USART_Mode_Rx | USART_Mode_Tx,	//接收和发送模式
			USART_HardwareFlowControl_None,	//硬件流控制失能
			0,0
			);	//串口初始化

if(Get_USART_ready_buf_ok(USART1))	//判断超时，一帧数据接收成功
{
	Clean_USART_ready_buf_OK(USART1);//清除串口是否接收完毕标志
	
	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//回发
	
	Clean_USART_ready_buf(USART1);//清除串口缓存数据
}

USART1_ready_buf 接收到的数据
USART1_ready_buf_len 接收数据长度

*/
/******************************************************************************************************************/
USART_TypeDef* USART_printf;

#ifdef USING_USART1
uint8_t USART1_receive_buf[USART1_BUF_SIZE];	//数据接收缓存区
uint8_t USART1_ready_buf[USART1_BUF_SIZE];		//接收成功后的数据区
static int32_t USART1_ReceiveTimeCounter = 0;	//超时剩余时间
__IO uint16_t USART1_receive_index=0; 		//正在接收的数据长度
__IO uint8_t USART1_ready_buf_ok = 0;		//是否成功接收
__IO uint16_t USART1_ready_buf_len = 0;		//成功接收后的数据长度
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

void USART1_ISR(void); //串口中断函数
void USART2_ISR(void); //串口中断函数
void USART3_ISR(void); //串口中断函数
void UART4_ISR(void); //串口中断函数
void UART5_ISR(void); //串口中断函数

/**********************中断函数***************************************************************************************************/
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
/**********************在中断中执行的代码***************************************************************************************************/
void USART_ReceiveOvertimeProcess(void)	//在中断中执行的代码
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
/**********************串口1中断接收一个字符***************************************************************************************************/
#ifdef USING_USART1
void USART1_ISR(void)   
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//判断是否是中断
	{
		USART1_ReceiveTimeCounter = USART1_RECEIVE_OVERTIME;

		if(USART1_receive_index >= USART1_BUF_SIZE)//若接收位置越界，那么重头开始存放
			USART1_receive_index = 0;
		
		USART1_receive_buf[USART1_receive_index++] = (uint8_t)USART_ReceiveData(USART1);//接收字符，并位置加1		
	}	
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//过载处理，只要读状态寄存器和数据寄存器就可自动清理此标志
	{
		(void)USART_ReceiveData(USART1);
	}

} 
#endif

#ifdef USING_USART2
void USART2_ISR(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //判断是否是中断
	{	
		USART2_ReceiveTimeCounter = USART2_RECEIVE_OVERTIME;
		
		if(USART2_receive_index >= USART2_BUF_SIZE)	//若接收位置越界，那么重头开始存放
			USART2_receive_index = 0;
		
		USART2_receive_buf[USART2_receive_index++] = (uint8_t)USART_ReceiveData(USART2);//接收字符，并位置加1
		
	}		
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//过载处理，只要读状态寄存器和数据寄存器就可自动清理此标志
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

//判断串口是否接收完毕
//接收成功返回 UART_OK
//接收失败返回 UART_ERROR
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

//清除串口是否接收完毕标志
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

//清除串口缓存数据
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
										)	//复用功能映射
{
		if(USARTx==USART1)
		{
			if(USART_TX_GPIOx==GPIOB && USART_TX_PIN==GPIO_Pin_6 && USART_TX_GPIOx==GPIOB && USART_TX_PIN==GPIO_Pin_7)
			{
				GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 复用功能映射
			}
		}
		if(USARTx==USART2)
		{
			if(USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_5 && USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_6)
			{
				GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 复用功能映射
			}
		}
		if(USARTx==USART3)
		{
			if(USART_TX_GPIOx==GPIOC && USART_TX_PIN==GPIO_Pin_10 && USART_TX_GPIOx==GPIOC && USART_TX_PIN==GPIO_Pin_11)
			{
				GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);//USART3 复用功能部分映射1
			}
			if(USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_8 && USART_TX_GPIOx==GPIOD && USART_TX_PIN==GPIO_Pin_9)
			{
				GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 复用功能部分映射2
			}			
		}
		
}

//串口初始化函数
void USART_init	(	USART_TypeDef * USARTx,			
					GPIO_TypeDef* USART_TX_GPIOx,	
					u16 USART_TX_PIN,
					GPIO_TypeDef* USART_RX_GPIOx,
					u16 USART_RX_PIN,
					uint32_t USART_BaudRate,			//波特率设置
					uint16_t USART_WordLength,			//字长(数据位+校验位)
					uint16_t USART_StopBits,			//停止位		
					uint16_t USART_Parity,				//校验位选择
					uint16_t USART_Mode,				//USART模式控制
					uint16_t USART_HardwareFlowControl,	//硬件流控制
					uint8_t PreemptionPriority,			//抢占优先级
					uint8_t SubPriority					//子优先级
				)
{

	USART_InitTypeDef USART_InitStructure;
	uint8_t NVIC_IRQChannel_USART;
	
	USART_RCC_PeriphClockCmd(USARTx);	/* 使能 USART 时钟 */
	
	GPIO_Common_Init(USART_TX_GPIOx,USART_TX_PIN,GPIO_Mode_AF_PP,GPIO_Speed_50MHz);	//GPIO初始化
	GPIO_Common_Init(USART_RX_GPIOx,USART_RX_PIN,GPIO_Mode_IN_FLOATING,GPIO_Speed_50MHz);	//GPIO初始化

	USART_GPIO_PinRemapConfig(USARTx,USART_TX_GPIOx,USART_TX_PIN,USART_RX_GPIOx,USART_RX_PIN);	//复用功能映射
	
	USART_InitStructure.USART_BaudRate = USART_BaudRate;/* 波特率设置：*/	
	USART_InitStructure.USART_WordLength = USART_WordLength;/* 字长(数据位+校验位)：8 USART_WordLength_8b*/
	USART_InitStructure.USART_StopBits = USART_StopBits;	/* 停止位：1个停止位 USART_StopBits_1*/
	USART_InitStructure.USART_Parity = USART_Parity;	/* 校验位选择：不使用校验 USART_Parity_No*/
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl	/* 硬件流控制：不使用硬件流 USART_HardwareFlowControl_None*/;
	USART_InitStructure.USART_Mode = USART_Mode;	/* USART模式控制：同时使能接收和发送 USART_Mode_Rx | USART_Mode_Tx*/
	USART_Init(USARTx, &USART_InitStructure); 	/* 完成USART初始化配置 */	
	
	NVIC_IRQChannel_USART=Get_NVIC_IRQChannel_USART(USARTx);
	NVIC_Init_IRQChannel(NVIC_IRQChannel_USART,PreemptionPriority,SubPriority,ENABLE);//配置 NVIC	
	
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);	/* 使能串口接收中断 */

	USART_Cmd(USARTx, ENABLE);	/* 使能串口 */	
}

/******************************************************************************************************************/

void Change_printf(USART_TypeDef* USART_prt)//重定向串口选择
{
	USART_printf=USART_prt;
}

//发送一个字节
void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte)	//发送一个字节
{

    	USARTx->DR = (SendByte & (uint16_t)0x01FF);
  		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}
//发送一串数据
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len)	//发送一串数据
{
	uint16_t i = 0;
	for(i = 0; i < len; i++)
	{
    	USARTx->DR = (*(SendChars + i) & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

//USART发送字符串
void UART_SendString(USART_TypeDef* USARTx,char* s)
{
	while(*s)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
		USART_SendData(USARTx ,*s++);//发送当前字符
	}
}
/******************************************************************************************************************/

/*
  * log:

  *	2018年4月27日
	优化条件编译，让代码适应STM32F10X全系列芯片
	Programmer:陈述

  *	2018年4月15日
	增加条件编译，未用到的串口不使用超时缓存区,减少内存占用
	增加注释
	Programmer:陈述

  *	2018年4月6日
	新增超时接收代码:
		void USART_ReceiveOvertimeProcess(void);	//在滴答中断 SysTick_Handler中执行的代码
	删除以下函数：
		void USART_Putc(unsigned char c);	//发送一个字符串
		void USART_Puts(unsigned char *str,int num);   //发送num个数据
		void Change_printf(USART_TypeDef* USART_prt);//重定向串口选择
	取而代之的是：
		void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte);	//发送一个字节
		void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len);	//发送一串数据
	发送数据时确认使用什么串口发送

	中断函数转到stm32f10x_it.c中,更加规范(应该所有的中断函数都应该放到stm32f10x_it.c中)
	
	Programmer:陈述

  *	2016年7月8日
	新建工程
	实现基本初始化功能
	实现基本发送与接收功能
	Programmer:陈述
	
*/

