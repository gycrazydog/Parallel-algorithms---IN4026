################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../C-List\ Ranking/Sequential-C.c 

OBJS += \
./C-List\ Ranking/Sequential-C.o 

C_DEPS += \
./C-List\ Ranking/Sequential-C.d 


# Each subdirectory must supply rules for building sources it contributes
C-List\ Ranking/Sequential-C.o: ../C-List\ Ranking/Sequential-C.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"C-List Ranking/Sequential-C.d" -MT"C-List\ Ranking/Sequential-C.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


