/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "gpio.h"

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

/* USER CODE BEGIN PV */

// CAN variables
CAN_TxHeaderTypeDef CAN_tx_header0;
CAN_TxHeaderTypeDef CAN_tx_header1;
CAN_TxHeaderTypeDef CAN_tx_header2;
CAN_TxHeaderTypeDef CAN_tx_header3;
CAN_TxHeaderTypeDef CAN_tx_header4;
CAN_TxHeaderTypeDef CAN_tx_header5;
CAN_TxHeaderTypeDef CAN_tx_header6;
CAN_TxHeaderTypeDef CAN_tx_header7;
CAN_TxHeaderTypeDef CAN_tx_header8;
CAN_TxHeaderTypeDef CAN_tx_header9;
CAN_TxHeaderTypeDef CAN_tx_header10;

uint8_t CAN_tx_data[8] = {
	  'H',
	  'E',
	  'L',
	  'L',
	  'O',
	  'A',
	  'B',
	  'C'
};
uint32_t mailbox;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

  // Start CAN Module (4)
  HAL_CAN_Start(&hcan);

  // CAN transmitting
  CanTransmitSetup();

  // CAN Testing Temporary
  CAN_TxHeaderTypeDef tx_headers[] = {
		  CAN_tx_header0,
		  CAN_tx_header1,
		  CAN_tx_header2,
		  CAN_tx_header3,
		  CAN_tx_header4,
		  CAN_tx_header5,
		  CAN_tx_header6,
		  CAN_tx_header7,
		  CAN_tx_header8,
		  CAN_tx_header9,
		  CAN_tx_header10

  };
  int total_tx_headers = sizeof(tx_headers)/sizeof(CAN_TxHeaderTypeDef);

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);	// set to low
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0); 	// reset blinker

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // NIC blue led

	  /*
	  // Transmit on BUTTON PRESS A0
	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 1)
	  {
		  if(HAL_CAN_AddTxMessage(&hcan, &CAN_tx_header1, CAN_tx_data, &mailbox) != HAL_OK) {
			  Error_Handler();
		  }
	  }
	  */

	  // Transmit different IDs from a FOR LOOP
	  for (int i = 0; i < total_tx_headers; i++)
	  {
		  if(HAL_CAN_AddTxMessage(&hcan, &tx_headers[i], CAN_tx_data, &mailbox) != HAL_OK) {
			  Error_Handler();
		  }
		  // Send message blinker: blinks i times where i is header number
		  for (int blinks = total_tx_headers - (i + 1); blinks < total_tx_headers; blinks++)
		  {
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
			  HAL_Delay(100);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
			  HAL_Delay(100);
		  }
		  // Delay before next message
		  HAL_Delay(1000);
	  }



	  /*
	  // Message pending blinker
	  while(HAL_CAN_IsTxMessagePending(&hcan, mailbox) ) {
		  // stale when message waiting to send
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	  }
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0); // reset pending transmit status led
	  */
  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
