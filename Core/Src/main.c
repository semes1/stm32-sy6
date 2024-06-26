/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd_init.h"
#include "lcd.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
unsigned int screen_num = 0;
unsigned int key_change_flag = 1;
unsigned int recive_flag = 0;
unsigned int pwm_lcd_flag = 0;
unsigned int pwm_freq = 0;
unsigned int pwm_duty = 0;
unsigned int student = 2021900372;
unsigned int engine_temp = 0;
unsigned int Alarm_flag =0;
uint16_t ADC_Value = 0;
uint8_t str[50] = {0};
float num2 = 12.13;
uint8_t  rx_dat1 = 0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
void draw_lcd0(void);
void draw_lcd1(void);
void pwm_solve(void);
void adc_solve(void);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
void draw_lcd0()
{
	if(screen_num == 0 && key_change_flag==1)
		{
	   LCD_Fill(0,0,128,160,WHITE);
		sprintf((char*)str,"USER INIRFACE:%d",1);
		LCD_ShowString(20,3,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"level:%d",0);
		LCD_ShowString(3,15,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"PWM freq:%dKhz",pwm_freq);
		LCD_ShowString(3,27,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"PWM duty:%d%%",pwm_duty);
		LCD_ShowString(3,39,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"num:%d",student);
		LCD_ShowString(3,51,str,BLACK,WHITE,12,0);
		LCD_ShowChinese(64,115,2,RED,GREEN,16);
		LCD_ShowChinese(80,115,3,RED,GREEN,16);
		LCD_ShowChinese(96,115,4,RED,GREEN,16);
		LCD_ShowChinese(112,115,5,RED,GREEN,16);
		key_change_flag=0;
		}
}

void draw_lcd1()
{
	if(screen_num == 1 && key_change_flag==1)
		{
		LCD_Fill(0,0,128,160,WHITE);
		sprintf((char*)str,"USER INIRFACE: %d",2);
		LCD_ShowString(20,3,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"Engine temp: %d",engine_temp);
		LCD_ShowString(3,15,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"Alarm threshold: %d",100);
		LCD_ShowString(3,27,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"Alarm flag: NO");
		LCD_ShowString(3,39,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"num:%d",student);
		LCD_ShowString(3,51,str,BLACK,WHITE,12,0);
		LCD_ShowChinese(64,115,2,RED,GREEN,16);
		LCD_ShowChinese(80,115,3,RED,GREEN,16);
		LCD_ShowChinese(96,115,4,RED,GREEN,16);
		LCD_ShowChinese(112,115,5,RED,GREEN,16);
		key_change_flag=0;
		}
}

void pwm_solve()
{
	if(rx_dat1 == 48 && recive_flag == 1)   //0
	{
		recive_flag=0;
		pwm_lcd_flag=1;
		pwm_freq = 0;
		pwm_duty = 0;
		__HAL_TIM_SET_AUTORELOAD(&htim3,499);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,0);
	}
	if(rx_dat1 == 49 && recive_flag == 1)   //1
	{
		recive_flag=0;
		pwm_lcd_flag=1;
		pwm_freq = 1;
		pwm_duty = 20;
		__HAL_TIM_SET_AUTORELOAD(&htim3,499);		 //1kHz
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,99);		//20%
	}
	if(rx_dat1 == 50 && recive_flag == 1)   //2
	{
		recive_flag=0;
		pwm_lcd_flag=1;
		pwm_freq = 2;
		pwm_duty = 40;
		__HAL_TIM_SET_AUTORELOAD(&htim3,249);		 //2kHz
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,99);		//40%
	}
	if(rx_dat1 == 51 && recive_flag == 1)   //3
	{
		recive_flag=0;
		pwm_lcd_flag=1;
		pwm_freq = 5;
		pwm_duty = 50;
		__HAL_TIM_SET_AUTORELOAD(&htim3,99);     //5kHz
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,49);		//50%
	}
	if(rx_dat1 == 52 && recive_flag == 1)   //4
	{
		recive_flag=0;
		pwm_lcd_flag=1;
		pwm_freq = 10;
		pwm_duty = 80;
		__HAL_TIM_SET_AUTORELOAD(&htim3,49);     //10kHz
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,39);		//80%
	}
	if(rx_dat1 == 53 && recive_flag == 1)   //5
	{
		recive_flag=0;
		pwm_lcd_flag=1;
		pwm_freq = 50;
		pwm_duty = 90;
		__HAL_TIM_SET_AUTORELOAD(&htim3,9);	 		 //50kHz
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,9);		//90%
	}

		if (screen_num == 0 && pwm_lcd_flag == 1)
	{
		pwm_lcd_flag = 0;
		sprintf((char*)str,"level:%c       ",rx_dat1);
		LCD_ShowString(3, 15, str, BLACK, WHITE, 12, 0);
		sprintf((char*)str,"PWM freq:%dKHz    ",pwm_freq);
		LCD_ShowString(3,27,str,BLACK,WHITE,12,0);
		sprintf((char*)str,"PWM duty:%d%%     ",pwm_duty);
		LCD_ShowString(3,39,str,BLACK,WHITE,12,0);
	}
}

void adc_solve()
{
	HAL_ADC_Start(&hadc1);
	if(HAL_ADC_PollForConversion(&hadc1,10) == HAL_OK)
	{
		ADC_Value = HAL_ADC_GetValue(&hadc1);
		engine_temp =  (ADC_Value*140/4095)+20;

			if(engine_temp>100)
			{
				Alarm_flag =1;
				if(screen_num == 1)
				{
					sprintf((char*)str,"Engine temp:%d ",engine_temp);
					LCD_ShowString(3,15,str,BLACK,WHITE,12,0);
					sprintf((char*)str,"Alarm flag:YES");
					LCD_ShowString(3,39,str,BLACK,WHITE,12,0);
				}
			}
			if(engine_temp <= 100)
			{
				Alarm_flag =0;
				if(screen_num == 1)
				{
					sprintf((char*)str,"Engine temp:%d ",engine_temp);
					LCD_ShowString(3,15,str,BLACK,WHITE,12,0);
					sprintf((char*)str,"Alarm flag:NO ");
					LCD_ShowString(3,39,str,BLACK,WHITE,12,0);
				}
			}

	}
	HAL_ADC_Stop(&hadc1);
}


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	if(hadc->Instance == ADC1)
	{
	ADC_Value = HAL_ADC_GetValue(&hadc1);
	sprintf((char*)str,"Value: %d",ADC_Value);
	printf("%s\r\n",str);
	HAL_UART_Transmit(&huart1,str,sizeof(str),1000);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_0)
	{
			screen_num=screen_num+1;
			key_change_flag = 1;
		  if(screen_num == 2)
        {
            screen_num=0;
        }
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		recive_flag=1;
		HAL_UART_Receive_IT(&huart1,&rx_dat1,1);
	}

}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(engine_temp >= 100)
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
			printf("[%d]PWMFREQUENCE:%dKHz,duty:%d%%,Engine TEMP=%d,Alarm flag=yes\r\n",student,pwm_freq,pwm_duty,engine_temp);
		}
		if(engine_temp < 100)
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
			printf("[%d]PWMFREQUENCE:%dKHz,duty:%d%%,Engine TEMP=%d,Alarm flag=no\r\n",student,pwm_freq,pwm_duty,engine_temp);
		}		
	}
		if(htim->Instance == TIM7)
		{
			if(engine_temp >= 100)
			{
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1);
			}
		}
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_USART6_UART_Init();
  MX_TIM6_Init();
  MX_TIM3_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
	LCD_Init();
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
	HAL_UART_Receive_IT(&huart1,&rx_dat1,1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
  /* USER CODE END 2 */

  /* Infinite loop */
	
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		draw_lcd0();
		draw_lcd1();
		pwm_solve();
		adc_solve();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
