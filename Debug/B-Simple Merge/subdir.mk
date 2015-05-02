################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../B-Simple\ Merge/Sequential-B.c 

OBJS += \
./B-Simple\ Merge/Sequential-B.o 

C_DEPS += \
./B-Simple\ Merge/Sequential-B.d 


# Each subdirectory must supply rules for building sources it contributes
B-Simple\ Merge/Sequential-B.o: ../B-Simple\ Merge/Sequential-B.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"B-Simple Merge/Sequential-B.d" -MT"B-Simple\ Merge/Sequential-B.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


