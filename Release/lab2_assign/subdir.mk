################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lab2_assign/outformat.c \
../lab2_assign/round.c 

OBJS += \
./lab2_assign/outformat.o \
./lab2_assign/round.o 

C_DEPS += \
./lab2_assign/outformat.d \
./lab2_assign/round.d 


# Each subdirectory must supply rules for building sources it contributes
lab2_assign/%.o: ../lab2_assign/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


