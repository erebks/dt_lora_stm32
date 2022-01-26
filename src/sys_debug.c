/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sys_debug.c
  * @author  MCD Application Team
  * @brief   Enables 4 debug pins for internal signals RealTime debugging
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "sys_debug.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions --------------------------------------------------------*/

/**
  * @brief Disable debugger (serial wires pins)
  */
void DBG_Disable(void)
{
  /* USER CODE BEGIN DBG_Init_1 */

  /* USER CODE END DBG_Init_1 */

#if defined (DEBUGGER_ENABLED) && ( DEBUGGER_ENABLED == 0 ) /* DEBUGGER_DISABLED */
  /* Put the debugger pin PA13 and P14 in analog for LowPower*/
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Mode   = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull   = GPIO_NOPULL;
  GPIO_InitStruct.Pin    = (GPIO_PIN_13 | GPIO_PIN_14);
  /* make sure clock is enabled before setting the pins with HAL_GPIO_Init() */
  __HAL_RCC_GPIOA_CLK_ENABLE() ;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

#elif !defined (DEBUGGER_ENABLED)
#error "DEBUGGER_ENABLED not defined or out of range <0,1>"
#endif /* DEBUGGER_OFF */

  /* Disabled HAL_DBGMCU_  */
  DBG_ConfigForLpm(1);

  /* USER CODE BEGIN DBG_Init_Last */

  /* USER CODE END DBG_Init_Last */
}

/**
  * @brief Config debugger when working in Low Power Mode
  * @note  When in Dual Core DbgMcu pins should be better disable only after Cm0 is started
  */
void DBG_ConfigForLpm(uint8_t enableDbg)
{
  uint8_t enable_dbg = enableDbg;
  /* USER CODE BEGIN DBG_ConfigForLpm_1 */

  /* USER CODE END DBG_ConfigForLpm_1 */

#if defined (DEBUGGER_ENABLED) && ( DEBUGGER_ENABLED == 0 )
  enable_dbg = 0;
#elif !defined (DEBUGGER_ENABLED)
#error "DEBUGGER_ENABLED not defined or out of range <0,1>"
#endif /* DEBUGGER_OFF */

  if (enable_dbg == 1)
  {
    __HAL_RCC_DBGMCU_CLK_ENABLE();

    HAL_DBGMCU_EnableDBGSleepMode();
    HAL_DBGMCU_EnableDBGStopMode();
    HAL_DBGMCU_EnableDBGStandbyMode();
  }
  else
  {
    __HAL_RCC_DBGMCU_CLK_ENABLE();
    HAL_DBGMCU_DisableDBGSleepMode();
    HAL_DBGMCU_DisableDBGStopMode();
    HAL_DBGMCU_DisableDBGStandbyMode();
    __HAL_RCC_DBGMCU_CLK_DISABLE();
  }

  /* USER CODE BEGIN DBG_ConfigForLpm_Last */

  /* USER CODE END DBG_ConfigForLpm_Last */
}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Private Functions Definition -----------------------------------------------*/
void DBG_ProbesInit(void)
{
  /* USER CODE BEGIN DBG_ProbesInit_1 */

  /* USER CODE END DBG_ProbesInit_1 */

  /* SW probes */

#if defined (PROBE_PINS_ENABLED) && ( PROBE_PINS_ENABLED == 1 )
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  /* Configure the GPIO pin */
  GPIO_InitStruct.Mode   = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull   = GPIO_PULLUP;
  GPIO_InitStruct.Speed  = GPIO_SPEED_FREQ_VERY_HIGH;

  /* Enable the GPIO Clock */
  PROBE_LINE1_CLK_ENABLE();
  PROBE_LINE2_CLK_ENABLE();
  PROBE_LINE3_CLK_ENABLE();
  PROBE_LINE4_CLK_ENABLE();

  GPIO_InitStruct.Pin    = PROBE_LINE1_PIN;
  HAL_GPIO_Init(PROBE_LINE1_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.Pin    = PROBE_LINE2_PIN;
  HAL_GPIO_Init(PROBE_LINE2_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.Pin    = PROBE_LINE3_PIN;
  HAL_GPIO_Init(PROBE_LINE3_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.Pin    = PROBE_LINE4_PIN;
  HAL_GPIO_Init(PROBE_LINE4_PORT, &GPIO_InitStruct);

  /* Reset probe Pins */
  HAL_GPIO_WritePin(PROBE_LINE1_PORT, PROBE_LINE1_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PROBE_LINE2_PORT, PROBE_LINE2_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PROBE_LINE3_PORT, PROBE_LINE3_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(PROBE_LINE4_PORT, PROBE_LINE4_PIN, GPIO_PIN_RESET);

#elif !defined (PROBE_PINS_ENABLED)
#error "PROBE_PINS_ENABLED not defined or out of range <0,1>"
#endif /* PROBE_PINS_ENABLED */

  /* USER CODE BEGIN DBG_ProbesInit_Last */

  /* USER CODE END DBG_ProbesInit_Last */
}
/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
