/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bat_profiler.h"
#include "str_buf.h"

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
volatile uint32_t global_event = 0;

#define MAIN_STR_SIZE (128)
static char main_str[MAIN_STR_SIZE];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void get_program_id_string(char *str, uint16_t str_size) {
	str_buf_clear(str, str_size);
	str_buf_append_string(str, str_size, "program id: ");
	str_buf_append_string(str, str_size, PROGRAM_NAME);
	str_buf_append_string(str, str_size, ", compiled: ");
	str_buf_append_string(str, str_size, __DATE__);
	str_buf_append_string(str, str_size, ", ");
	str_buf_append_string(str, str_size, __TIME__);
	str_buf_append_string(str, str_size, "\n");
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	uint32_t primask = 0;
	uint32_t local_event = 0;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, 3);

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_LPUART1_UART_Init();
  MX_TIM21_Init();
  MX_TIM22_Init();
  /* USER CODE BEGIN 2 */

  gpio_set_led(ALL_LEDS_MASK);

  get_program_id_string(main_str, MAIN_STR_SIZE);
  uart_send_str_buf_blocking(main_str, MAIN_STR_SIZE);

  tim21_start();
  tim22_start();

  gpio_clear_led(ALL_LEDS_MASK);
  bp_init();
  bp_print_out_profiles();
  bp_start();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(local_event & EV_BTN0) {
	        tim21_ch1_start_single_timeout(1000, EV_BTN0_TIMEOUT);
	        bp_process_events(EV_BTN0_PRESSED);
	      }
	      if(local_event & EV_BTN0_TIMEOUT) {
	      	if(LL_GPIO_IsInputPinSet(BTN0_GPIO_Port, BTN0_Pin) == 0) {
	      		// still pressed
	      		bp_process_events(EV_BTN0_LONG);
	      	}
	      }
	      if(local_event & EV_BTN1) {
	        tim21_ch2_start_single_timeout(1000, EV_BTN1_TIMEOUT);
	        bp_process_events(EV_BTN1_PRESSED);
	      }
	      if(local_event & EV_BTN1_TIMEOUT) {
	      	if(LL_GPIO_IsInputPinSet(BTN1_GPIO_Port, BTN1_Pin) == 0) {
	  			// still pressed
	      		bp_process_events(EV_BTN1_LONG);
	      	}
	      }
	      if(local_event & EV_BPROFILER_TIMEOUT1) {
	    	  bp_process_events(EV_TIMEOUT1);
	      }

	  		// wait for global events
	  		while(1) {
	  			// sync global events
	  			primask = __get_PRIMASK();  // Save current interrupt state
	  			__disable_irq();            // Disable all interrupts

	  			local_event = global_event;
	  			global_event = 0;

	  			__set_PRIMASK(primask);     // Restore previous interrupt state

	  			if(local_event) {
	  				// process event
	  				break;
	  			}

	  			// else go to sleep
	  			LL_LPM_EnableSleep();  // This clears SLEEPDEEP

	  			// Enter sleep mode (Wait For Interrupt)
	  			__WFI();  // or __WFE();

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
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  while (LL_PWR_IsActiveFlag_VOS() != 0)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }

  LL_Init1msTick(16000000);

  LL_SetSystemCoreClock(16000000);
  LL_RCC_SetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE_PCLK1);
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
