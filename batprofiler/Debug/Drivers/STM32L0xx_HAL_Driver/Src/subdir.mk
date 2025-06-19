################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.c \
../Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.c 

OBJS += \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.o \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.o 

C_DEPS += \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.d \
./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32L0xx_HAL_Driver/Src/%.o Drivers/STM32L0xx_HAL_Driver/Src/%.su Drivers/STM32L0xx_HAL_Driver/Src/%.cyclo: ../Drivers/STM32L0xx_HAL_Driver/Src/%.c Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DMSI_VALUE=2097000 -DHSI_VALUE=16000000 -DLSI_VALUE=37000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=0 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -DSTM32L031xx -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-STM32L0xx_HAL_Driver-2f-Src

clean-Drivers-2f-STM32L0xx_HAL_Driver-2f-Src:
	-$(RM) ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_dma.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_exti.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_gpio.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lptim.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_lpuart.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_pwr.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_rcc.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_tim.su ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.cyclo ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.d ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.o ./Drivers/STM32L0xx_HAL_Driver/Src/stm32l0xx_ll_utils.su

.PHONY: clean-Drivers-2f-STM32L0xx_HAL_Driver-2f-Src

