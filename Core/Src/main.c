/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	//debounce
	static uint32_t last_interrupt_time = 0;
	    uint32_t current_time = HAL_GetTick();
	if ((current_time - last_interrupt_time) < 50)
	return;

	switch (GPIO_Pin){
	case (SWT4_RED_Pin): {
		HAL_GPIO_TogglePin(GPIOD, LED_RED_Pin);
		if (HAL_GPIO_ReadPin(GPIOD, LED_RED_Pin) == GPIO_PIN_SET)
			HAL_UART_Transmit(&huart3, (uint8_t*) " - Red ON\r\n", 11, 100);
		else
			HAL_UART_Transmit(&huart3, (uint8_t*) " - Red OFF\r\n", 12, 100);
		break;
	}
	case (SWT1_BLUE_Pin): {
		HAL_GPIO_TogglePin(GPIOD, LED_BLUE_Pin);
		if (HAL_GPIO_ReadPin(GPIOD, LED_BLUE_Pin) == GPIO_PIN_SET)
			HAL_UART_Transmit(&huart3, (uint8_t*) " - Blue ON\r\n", 12, 100);
		else
			HAL_UART_Transmit(&huart3, (uint8_t*) " - Blue OFF\r\n", 13, 100);
		break;
	}
	case (SWT5_GREEN_Pin): {
		HAL_GPIO_TogglePin(GPIOD, LED_GREEN_Pin);
		if (HAL_GPIO_ReadPin(GPIOD, LED_GREEN_Pin) == GPIO_PIN_SET)
			HAL_UART_Transmit(&huart3, (uint8_t*) " - GREEN ON\r\n", 13, 100);
		else
			HAL_UART_Transmit(&huart3, (uint8_t*) " - GREEN OFF\r\n", 14, 100);
		break;
	}
	case (SWT3_ORANGE_Pin): {
		HAL_GPIO_TogglePin(GPIOD, LED_ORANGE_Pin);
		if (HAL_GPIO_ReadPin(GPIOD, LED_ORANGE_Pin) == GPIO_PIN_SET)
			HAL_UART_Transmit(&huart3, (uint8_t*) " - ORANGE ON\r\n", 14, 100);
		else
			HAL_UART_Transmit(&huart3, (uint8_t*) " - ORANGE OFF\r\n", 15, 100);
		break;
	}
	case (SWT2_ALL_Pin): {
		HAL_GPIO_TogglePin(GPIOD,
		LED_BLUE_Pin | LED_RED_Pin | LED_ORANGE_Pin | LED_GREEN_Pin);
		HAL_UART_Transmit(&huart3, (uint8_t*) " - TOGGLED ALL\r\n", 16, 100);
		break;
	}
	}
	last_interrupt_time = current_time;
	return;
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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  uint8_t rcvBuf[1];
	  HAL_StatusTypeDef result;
	  result = HAL_UART_Receive(&huart3, rcvBuf, 1, 10);

	  if (result == HAL_OK)
	  {
			switch (rcvBuf[0]) {

			case ('1'): {
				HAL_GPIO_TogglePin(GPIOD, LED_RED_Pin);
				if (HAL_GPIO_ReadPin(GPIOD, LED_RED_Pin) == GPIO_PIN_SET)
					HAL_UART_Transmit(&huart3, (uint8_t*) " - Red ON\r\n", 11,
							100);
				else
					HAL_UART_Transmit(&huart3, (uint8_t*) " - Red OFF\r\n", 12,
							100);
				break;
			}
			case ('2'): {
				HAL_GPIO_TogglePin(GPIOD, LED_BLUE_Pin);
				if (HAL_GPIO_ReadPin(GPIOD, LED_BLUE_Pin) == GPIO_PIN_SET)
					HAL_UART_Transmit(&huart3, (uint8_t*) " - Blue ON\r\n", 12,
							100);
				else
					HAL_UART_Transmit(&huart3, (uint8_t*) " - Blue OFF\r\n", 13,
							100);
				break;
			}
			case ('3'): {
				HAL_GPIO_TogglePin(GPIOD, LED_GREEN_Pin);
				if (HAL_GPIO_ReadPin(GPIOD, LED_GREEN_Pin) == GPIO_PIN_SET)
					HAL_UART_Transmit(&huart3, (uint8_t*) " - GREEN ON\r\n", 13,
							100);
				else
					HAL_UART_Transmit(&huart3, (uint8_t*) " - GREEN OFF\r\n", 14,
							100);
				break;
			}
			case ('4'): {
				HAL_GPIO_TogglePin(GPIOD, LED_ORANGE_Pin);
				if (HAL_GPIO_ReadPin(GPIOD, LED_ORANGE_Pin) == GPIO_PIN_SET)
					HAL_UART_Transmit(&huart3, (uint8_t*) " - ORANGE ON\r\n", 14,
							100);
				else
					HAL_UART_Transmit(&huart3, (uint8_t*) " - ORANGE OFF\r\n",
							15, 100);
				break;
			}
			case ('5'): {
				HAL_GPIO_TogglePin(GPIOD,
						LED_BLUE_Pin | LED_RED_Pin | LED_ORANGE_Pin| LED_GREEN_Pin);
				HAL_UART_Transmit(&huart3, (uint8_t*) " - TOGGLED ALL\r\n", 16, 100);
				break;
			}
		  default:{
			  HAL_UART_Transmit(&huart3, (uint8_t *)" - UnexpCmd\r\n", 13, 100);
			  break;
		  }
		  }
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_GREEN_Pin|LED_ORANGE_Pin|LED_RED_Pin|LED_BLUE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_GREEN_Pin LED_ORANGE_Pin LED_RED_Pin LED_BLUE_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin|LED_ORANGE_Pin|LED_RED_Pin|LED_BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : SWT4_RED_Pin SWT5_GREEN_Pin SWT3_ORANGE_Pin SWT1_BLUE_Pin */
  GPIO_InitStruct.Pin = SWT4_RED_Pin|SWT5_GREEN_Pin|SWT3_ORANGE_Pin|SWT1_BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : SWT2_ALL_Pin */
  GPIO_InitStruct.Pin = SWT2_ALL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SWT2_ALL_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
