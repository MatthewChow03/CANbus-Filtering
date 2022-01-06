/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

void CanTransmitSetup()
{

	CAN_tx_header0.StdId = 0x401;
	CAN_tx_header0.ExtId = 0;
	CAN_tx_header0.IDE = CAN_ID_STD;
	CAN_tx_header0.RTR = CAN_RTR_DATA;
	CAN_tx_header0.DLC = 8;
	CAN_tx_header0.TransmitGlobalTime = DISABLE;

	CAN_tx_header1.StdId = 0x501;
	CAN_tx_header1.ExtId = 0;
	CAN_tx_header1.IDE = CAN_ID_STD;
	CAN_tx_header1.RTR = CAN_RTR_DATA;
	CAN_tx_header1.DLC = 8;
	CAN_tx_header1.TransmitGlobalTime = DISABLE;

	CAN_tx_header2.StdId = 0x503;
	CAN_tx_header2.ExtId = 0;
	CAN_tx_header2.IDE = CAN_ID_STD;
	CAN_tx_header2.RTR = CAN_RTR_DATA;
	CAN_tx_header2.DLC = 8;
	CAN_tx_header2.TransmitGlobalTime = DISABLE;

	CAN_tx_header3.StdId = 0x50B;
	CAN_tx_header3.ExtId = 0;
	CAN_tx_header3.IDE = CAN_ID_STD;
	CAN_tx_header3.RTR = CAN_RTR_DATA;
	CAN_tx_header3.DLC = 8;
	CAN_tx_header3.TransmitGlobalTime = DISABLE;

	CAN_tx_header4.StdId = 0x622;
	CAN_tx_header4.ExtId = 0;
	CAN_tx_header4.IDE = CAN_ID_STD;
	CAN_tx_header4.RTR = CAN_RTR_DATA;
	CAN_tx_header4.DLC = 8;
	CAN_tx_header4.TransmitGlobalTime = DISABLE;

	CAN_tx_header5.StdId = 0x623;
	CAN_tx_header5.ExtId = 0;
	CAN_tx_header5.IDE = CAN_ID_STD;
	CAN_tx_header5.RTR = CAN_RTR_DATA;
	CAN_tx_header5.DLC = 8;
	CAN_tx_header5.TransmitGlobalTime = DISABLE;

	CAN_tx_header6.StdId = 0x626;
	CAN_tx_header6.ExtId = 0;
	CAN_tx_header6.IDE = CAN_ID_STD;
	CAN_tx_header6.RTR = CAN_RTR_DATA;
	CAN_tx_header6.DLC = 8;
	CAN_tx_header6.TransmitGlobalTime = DISABLE;

	CAN_tx_header7.StdId = 0x627;
	CAN_tx_header7.ExtId = 0;
	CAN_tx_header7.IDE = CAN_ID_STD;
	CAN_tx_header7.RTR = CAN_RTR_DATA;
	CAN_tx_header7.DLC = 8;
	CAN_tx_header7.TransmitGlobalTime = DISABLE;

	// IDs for demo purposes
	CAN_tx_header8.StdId = 0x301;
	CAN_tx_header8.ExtId = 0;
	CAN_tx_header8.IDE = CAN_ID_STD;
	CAN_tx_header8.RTR = CAN_RTR_DATA;
	CAN_tx_header8.DLC = 8;
	CAN_tx_header8.TransmitGlobalTime = DISABLE;

	CAN_tx_header9.StdId = 0x302;
	CAN_tx_header9.ExtId = 0;
	CAN_tx_header9.IDE = CAN_ID_STD;
	CAN_tx_header9.RTR = CAN_RTR_DATA;
	CAN_tx_header9.DLC = 8;
	CAN_tx_header9.TransmitGlobalTime = DISABLE;

	CAN_tx_header10.StdId = 0x303;
	CAN_tx_header10.ExtId = 0;
	CAN_tx_header10.IDE = CAN_ID_STD;
	CAN_tx_header10.RTR = CAN_RTR_DATA;
	CAN_tx_header10.DLC = 8;
	CAN_tx_header10.TransmitGlobalTime = DISABLE;

}

/* USER CODE END 0 */

CAN_HandleTypeDef hcan;

/* CAN init function */
void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 12;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_13TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_CAN1_2();

  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN GPIO Configuration
    PB8     ------> CAN_RX
    PB9     ------> CAN_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
