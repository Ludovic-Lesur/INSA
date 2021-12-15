################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Exceptions.c" \
"../Sources/IntcInterrupts.c" \
"../Sources/can.c" \
"../Sources/dcu.c" \
"../Sources/global.c" \
"../Sources/gpio.c" \
"../Sources/init_watchd_pll.c" \
"../Sources/ivor_branch_table.c" \
"../Sources/lcd.c" \
"../Sources/main.c" \
"../Sources/pit.c" \
"../Sources/step_motors.c" \

C_SRCS += \
../Sources/Exceptions.c \
../Sources/IntcInterrupts.c \
../Sources/can.c \
../Sources/dcu.c \
../Sources/global.c \
../Sources/gpio.c \
../Sources/init_watchd_pll.c \
../Sources/ivor_branch_table.c \
../Sources/lcd.c \
../Sources/main.c \
../Sources/pit.c \
../Sources/step_motors.c \

OBJS += \
./Sources/Exceptions_c.obj \
./Sources/IntcInterrupts_c.obj \
./Sources/can_c.obj \
./Sources/dcu_c.obj \
./Sources/global_c.obj \
./Sources/gpio_c.obj \
./Sources/init_watchd_pll_c.obj \
./Sources/ivor_branch_table_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \
./Sources/pit_c.obj \
./Sources/step_motors_c.obj \

OBJS_QUOTED += \
"./Sources/Exceptions_c.obj" \
"./Sources/IntcInterrupts_c.obj" \
"./Sources/can_c.obj" \
"./Sources/dcu_c.obj" \
"./Sources/global_c.obj" \
"./Sources/gpio_c.obj" \
"./Sources/init_watchd_pll_c.obj" \
"./Sources/ivor_branch_table_c.obj" \
"./Sources/lcd_c.obj" \
"./Sources/main_c.obj" \
"./Sources/pit_c.obj" \
"./Sources/step_motors_c.obj" \

C_DEPS += \
./Sources/Exceptions_c.d \
./Sources/IntcInterrupts_c.d \
./Sources/can_c.d \
./Sources/dcu_c.d \
./Sources/global_c.d \
./Sources/gpio_c.d \
./Sources/init_watchd_pll_c.d \
./Sources/ivor_branch_table_c.d \
./Sources/lcd_c.d \
./Sources/main_c.d \
./Sources/pit_c.d \
./Sources/step_motors_c.d \

OBJS_OS_FORMAT += \
./Sources/Exceptions_c.obj \
./Sources/IntcInterrupts_c.obj \
./Sources/can_c.obj \
./Sources/dcu_c.obj \
./Sources/global_c.obj \
./Sources/gpio_c.obj \
./Sources/init_watchd_pll_c.obj \
./Sources/ivor_branch_table_c.obj \
./Sources/lcd_c.obj \
./Sources/main_c.obj \
./Sources/pit_c.obj \
./Sources/step_motors_c.obj \

C_DEPS_QUOTED += \
"./Sources/Exceptions_c.d" \
"./Sources/IntcInterrupts_c.d" \
"./Sources/can_c.d" \
"./Sources/dcu_c.d" \
"./Sources/global_c.d" \
"./Sources/gpio_c.d" \
"./Sources/init_watchd_pll_c.d" \
"./Sources/ivor_branch_table_c.d" \
"./Sources/lcd_c.d" \
"./Sources/main_c.d" \
"./Sources/pit_c.d" \
"./Sources/step_motors_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Exceptions_c.obj: ../Sources/Exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/Exceptions.args" -o "Sources/Exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/IntcInterrupts_c.obj: ../Sources/IntcInterrupts.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/IntcInterrupts.args" -o "Sources/IntcInterrupts_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/can_c.obj: ../Sources/can.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/can.args" -o "Sources/can_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/dcu_c.obj: ../Sources/dcu.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/dcu.args" -o "Sources/dcu_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/global_c.obj: ../Sources/global.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/global.args" -o "Sources/global_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/gpio_c.obj: ../Sources/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/gpio.args" -o "Sources/gpio_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/init_watchd_pll_c.obj: ../Sources/init_watchd_pll.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/init_watchd_pll.args" -o "Sources/init_watchd_pll_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/ivor_branch_table_c.obj: ../Sources/ivor_branch_table.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/ivor_branch_table.args" -o "Sources/ivor_branch_table_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/lcd_c.obj: ../Sources/lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/lcd.args" -o "Sources/lcd_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pit_c.obj: ../Sources/pit.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/pit.args" -o "Sources/pit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/step_motors_c.obj: ../Sources/step_motors.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Sources/step_motors.args" -o "Sources/step_motors_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


