/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_TIM2_Init(void);
void MX_TIM21_Init(void);
void MX_TIM22_Init(void);

/* USER CODE BEGIN Prototypes */
void pwm_start(uint16_t cmp);
void pwm_stop(void);

void tim21_start(void);
void tim21_stop(void);
void tim21_ch1_start_single_timeout(uint16_t ms);
void tim21_ch1_stop_timeout(void);
void tim21_ch2_start_single_timeout(uint16_t ms);
void tim21_ch2_stop_timeout(void);

void tim22_start(void);
void tim22_stop(void);
void tim22_ch1_start_single_timeout(uint16_t ms);
void tim22_ch1_stop_timeout(void);
void tim22_ch2_start_single_timeout(uint16_t ms);
void tim22_ch2_stop_timeout(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

