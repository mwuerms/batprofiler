/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "tim.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* TIM2 init function */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  TIM_InitStruct.Prescaler = 0;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 10000;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
  LL_TIM_Init(TIM2, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM2);
  LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_INTERNAL);
  LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH1);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 2000;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM2, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
  LL_TIM_OC_EnableFast(TIM2, LL_TIM_CHANNEL_CH1);
  LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM2);
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /**TIM2 GPIO Configuration
    PA0-CK_IN     ------> TIM2_CH1
    */
  GPIO_InitStruct.Pin = VREF_PWM_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_2;
  LL_GPIO_Init(VREF_PWM_GPIO_Port, &GPIO_InitStruct);

}
/* TIM21 init function */
void MX_TIM21_Init(void)
{

  /* USER CODE BEGIN TIM21_Init 0 */

  /* USER CODE END TIM21_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM21);

  /* TIM21 interrupt Init */
  NVIC_SetPriority(TIM21_IRQn, 0);
  NVIC_EnableIRQ(TIM21_IRQn);

  /* USER CODE BEGIN TIM21_Init 1 */

  /* USER CODE END TIM21_Init 1 */
  TIM_InitStruct.Prescaler = 4000;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 65535;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV4;
  LL_TIM_Init(TIM21, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM21);
  LL_TIM_SetClockSource(TIM21, LL_TIM_CLOCKSOURCE_INTERNAL);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_FROZEN;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM21, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
  LL_TIM_OC_DisableFast(TIM21, LL_TIM_CHANNEL_CH1);
  LL_TIM_OC_Init(TIM21, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);
  LL_TIM_OC_DisableFast(TIM21, LL_TIM_CHANNEL_CH2);
  LL_TIM_SetTriggerOutput(TIM21, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM21);
  /* USER CODE BEGIN TIM21_Init 2 */

  /* USER CODE END TIM21_Init 2 */

}
/* TIM22 init function */
void MX_TIM22_Init(void)
{

  /* USER CODE BEGIN TIM22_Init 0 */

  /* USER CODE END TIM22_Init 0 */

  LL_TIM_InitTypeDef TIM_InitStruct = {0};
  LL_TIM_OC_InitTypeDef TIM_OC_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM22);

  /* TIM22 interrupt Init */
  NVIC_SetPriority(TIM22_IRQn, 0);
  NVIC_EnableIRQ(TIM22_IRQn);

  /* USER CODE BEGIN TIM22_Init 1 */

  /* USER CODE END TIM22_Init 1 */
  TIM_InitStruct.Prescaler = 4000;
  TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
  TIM_InitStruct.Autoreload = 65535;
  TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV4;
  LL_TIM_Init(TIM22, &TIM_InitStruct);
  LL_TIM_DisableARRPreload(TIM22);
  LL_TIM_SetClockSource(TIM22, LL_TIM_CLOCKSOURCE_INTERNAL);
  TIM_OC_InitStruct.OCMode = LL_TIM_OCMODE_FROZEN;
  TIM_OC_InitStruct.OCState = LL_TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct.CompareValue = 0;
  TIM_OC_InitStruct.OCPolarity = LL_TIM_OCPOLARITY_HIGH;
  LL_TIM_OC_Init(TIM22, LL_TIM_CHANNEL_CH1, &TIM_OC_InitStruct);
  LL_TIM_OC_DisableFast(TIM22, LL_TIM_CHANNEL_CH1);
  LL_TIM_OC_Init(TIM22, LL_TIM_CHANNEL_CH2, &TIM_OC_InitStruct);
  LL_TIM_OC_DisableFast(TIM22, LL_TIM_CHANNEL_CH2);
  LL_TIM_SetTriggerOutput(TIM22, LL_TIM_TRGO_RESET);
  LL_TIM_DisableMasterSlaveMode(TIM22);
  /* USER CODE BEGIN TIM22_Init 2 */

  /* USER CODE END TIM22_Init 2 */

}

/* USER CODE BEGIN 1 */

// - TIM2 -> pwm signal -------------------------------------------------------
void pwm_start(uint16_t cmp) {
  if(cmp == 0) {
    pwm_stop();
  }
  else {
    LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetCompareCH1(TIM2, cmp);
    LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
    LL_TIM_EnableCounter(TIM2);
  }
}

void pwm_stop(void) {
  LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_FORCED_INACTIVE);
  LL_TIM_OC_SetCompareCH1(TIM2, 0);
  LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH1);
  LL_TIM_DisableCounter(TIM2);
}

// - TIM21 --------------------------------------------------------------------
/**
 * TIM21 free running @ 1000 Hz -> 1 tick = 1 ms
 */
volatile uint16_t tim21_cnt;
void tim21_start(void) {
	LL_TIM_EnableCounter(TIM21);
}

void tim21_stop(void) {
	LL_TIM_DisableCounter(TIM21);
}

/**
 * TIM21.CH1
 */
void tim21_ch1_start_single_timeout(uint16_t ms) {
	tim21_cnt = (uint16_t)LL_TIM_GetCounter(TIM21);
	LL_TIM_OC_SetCompareCH1(TIM21, (uint32_t)(tim21_cnt + ms));
	LL_TIM_ClearFlag_CC1(TIM21);
	LL_TIM_EnableIT_CC1(TIM21);
}

void tim21_ch1_stop_timeout(void) {
	LL_TIM_DisableIT_CC1(TIM21);
}

/**
 * TIM21.CH2
 */
void tim21_ch2_start_single_timeout(uint16_t ms) {
	tim21_cnt = (uint16_t)LL_TIM_GetCounter(TIM21);
	LL_TIM_OC_SetCompareCH2(TIM21, (uint32_t)(tim21_cnt + ms));
	LL_TIM_ClearFlag_CC2(TIM21);
	LL_TIM_EnableIT_CC2(TIM21);
}

void tim21_ch2_stop_timeout(void) {
	LL_TIM_DisableIT_CC2(TIM21);
}

// - TIM22 --------------------------------------------------------------------
/**
 * TIM22 free running @ 1000 Hz -> 1 tick = 1 ms
 */
volatile uint16_t tim22_cnt;
void tim22_start(void) {
	LL_TIM_EnableCounter(TIM22);
}

void tim22_stop(void) {
	LL_TIM_DisableCounter(TIM22);
}

/**
 * TIM22.CH1
 */
void tim22_ch1_start_single_timeout(uint16_t ms) {
	tim22_cnt = (uint16_t)LL_TIM_GetCounter(TIM22);
	LL_TIM_OC_SetCompareCH1(TIM22, (uint32_t)(tim22_cnt + ms));
	LL_TIM_ClearFlag_CC1(TIM22);
	LL_TIM_EnableIT_CC1(TIM22);
}

void tim22_ch1_stop_timeout(void) {
	LL_TIM_DisableIT_CC1(TIM22);
}

/**
 * TIM22.CH2
 */
void tim22_ch2_start_single_timeout(uint16_t ms) {
	tim22_cnt = (uint16_t)LL_TIM_GetCounter(TIM22);
	LL_TIM_OC_SetCompareCH2(TIM22, (uint32_t)(tim22_cnt + ms));
	LL_TIM_ClearFlag_CC2(TIM22);
	LL_TIM_EnableIT_CC2(TIM22);
}

void tim22_ch2_stop_timeout(void) {
	LL_TIM_DisableIT_CC2(TIM22);
}

/* USER CODE END 1 */
