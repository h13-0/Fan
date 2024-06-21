/**
  ******************************************************************************
  * @file UART1_Printf\main.c
  * @brief This file contains the main function for: retarget the C library printf
  *        /scanf functions to the UART1 example.
  * @author  MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure TIM2 peripheral in PWM mode
  * @param  None
  * @retval None
  */
static void TIM2_Config(void)
{
  /* Time base configuration */
  TIM2_TimeBaseInit(TIM2_PRESCALER_16, 19999);

  /* PWM1 Mode configuration: Channel1 */ 
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
  TIM2_CCxCmd(TIM2_CHANNEL_1, ENABLE);
  TIM2_OC1PreloadConfig(ENABLE);
  //TIM2_CtrlPWMOutputs(ENABLE);

  TIM2_ARRPreloadConfig(ENABLE);

  /* TIM2 enable counter */
  TIM2_Cmd(ENABLE);
}

static void GPIO_Config(void)
{
  /* Set PC.5 pin */
  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_NO_IT);
  //GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
}

static void TIM1_Config(void)
{
    TIM1_DeInit();
    TIM1_TimeBaseInit(0,TIM1_COUNTERMODE_UP,65536-1,0);
    TIM1_ICInit((TIM1_Channel_TypeDef)(TIM1_CHANNEL_1 | TIM1_CHANNEL_2), TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV1, 0);
    TIM1_EncoderInterfaceConfig(TIM1_ENCODERMODE_TI12, TIM1_ICPOLARITY_RISING, TIM1_ICPOLARITY_RISING);
    TIM1_ClearFlag(TIM1_FLAG_UPDATE);
    TIM1_SetCounter(0);
    TIM1_Cmd(ENABLE);
}

static void sleepOneMilliseond(void)
{
	uint8_t Ms = 1;
	uint8_t j = 30;
	
	while( Ms-- )
	{
		while( j-- );
	}
}

void SleepMilliseonds( uint16_t MilliSeconds )
{
  while(MilliSeconds--)
  {
    sleepOneMilliseond();
   }
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
  //TIM1 -> Encoder C6 C7.
  //TIM2 -> PWM
  // Set clock to 16MHz.
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  //Init GPIO.
  GPIO_Config();
  
  //Init TIM2.
  TIM2_Config();
  
  TIM1_Config();
  
  while(1)
  {
    if(GPIO_ReadInputPin(GPIOD, GPIO_PIN_3))
    {
      int32_t count = 0;
      count = TIM1_GetCounter();
      
      if(count > 32768)
      {
        count = 65535 - count;
      } else {
        count = - count;
      }
      
      // 60 Pulses per turn.
      // 20% duty cycle per turn.
      if(count > 300)
      {
        TIM1_SetCounter(-300);
        count = 300;
      } else if(count < 0)
      {
        TIM1_SetCounter(0);
        count = 0;
      }
      
      uint16_t cmpValue = 20000 * count / 300;
      TIM2_SetCompare1(cmpValue);
    } else {
      TIM2_SetCompare1(20000);
    }
    SleepMilliseonds(100);
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
