/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
#define LED0_MASK BITVALUE(0)
#define LED1_MASK BITVALUE(1)
#define LED2_MASK BITVALUE(2)
#define LED3_MASK BITVALUE(3)
#define LED4_MASK BITVALUE(4)
#define LED5_MASK BITVALUE(5)
#define LED6_MASK BITVALUE(6)
#define LED7_MASK BITVALUE(7)

#define ALL_LEDS_MASK (LED7_MASK|LED6_MASK|LED5_MASK|LED4_MASK|LED3_MASK|LED2_MASK|LED1_MASK|LED0_MASK)

void gpio_set_led(uint32_t led_mask);
void gpio_clear_led(uint32_t led_mask);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

