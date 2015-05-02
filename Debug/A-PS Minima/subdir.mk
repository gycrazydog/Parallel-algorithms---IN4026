################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../A-PS\ Minima/Sequential-A.c 

OBJS += \
./A-PS\ Minima/Sequential-A.o 

C_DEPS += \
./A-PS\ Minima/Sequential-A.d 


# Each subdirectory must supply rules for building sources it contributes
A-PS\ Minima/Sequential-A.o: ../A-PS\ Minima/Sequential-A.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"A-PS Minima/Sequential-A.d" -MT"A-PS\ Minima/Sequential-A.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


