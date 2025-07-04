/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32l0xx_ll_lpuart.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_crs.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_system.h"
#include "stm32l0xx_ll_exti.h"
#include "stm32l0xx_ll_cortex.h"
#include "stm32l0xx_ll_utils.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_dma.h"
#include "stm32l0xx_ll_tim.h"
#include "stm32l0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define PROGRAM_NAME "batprofiler"

#define NB_ELEMENTS(x) (sizeof(x)/sizeof(x[0]))
#define BITVALUE(x) (1 << x)

extern volatile uint32_t global_event;
#define EV_BTN0 BITVALUE(0)
#define EV_BTN0_TIMEOUT BITVALUE(1)
#define EV_BTN1 BITVALUE(2)
#define EV_BTN1_TIMEOUT BITVALUE(3)

#define EV_BPROFILER_TIMEOUT1 BITVALUE(7)

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN0_Pin LL_GPIO_PIN_14
#define BTN0_GPIO_Port GPIOC
#define BTN0_EXTI_IRQn EXTI4_15_IRQn
#define BTN1_Pin LL_GPIO_PIN_15
#define BTN1_GPIO_Port GPIOC
#define BTN1_EXTI_IRQn EXTI4_15_IRQn
#define VREF_PWM_Pin LL_GPIO_PIN_0
#define VREF_PWM_GPIO_Port GPIOA
#define LED1_Pin LL_GPIO_PIN_1
#define LED1_GPIO_Port GPIOA
#define LED0_Pin LL_GPIO_PIN_4
#define LED0_GPIO_Port GPIOA
#define LED2_Pin LL_GPIO_PIN_5
#define LED2_GPIO_Port GPIOA
#define LED3_Pin LL_GPIO_PIN_6
#define LED3_GPIO_Port GPIOA
#define LED4_Pin LL_GPIO_PIN_7
#define LED4_GPIO_Port GPIOA
#define LED5_Pin LL_GPIO_PIN_1
#define LED5_GPIO_Port GPIOB
#define LED6_Pin LL_GPIO_PIN_9
#define LED6_GPIO_Port GPIOA
#define LED7_Pin LL_GPIO_PIN_10
#define LED7_GPIO_Port GPIOA
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
