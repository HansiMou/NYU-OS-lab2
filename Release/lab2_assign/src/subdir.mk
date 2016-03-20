################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lab2_assign/src/event.cpp \
../lab2_assign/src/main.cpp \
../lab2_assign/src/prepare.cpp \
../lab2_assign/src/process.cpp \
../lab2_assign/src/scheduler.cpp 

OBJS += \
./lab2_assign/src/event.o \
./lab2_assign/src/main.o \
./lab2_assign/src/prepare.o \
./lab2_assign/src/process.o \
./lab2_assign/src/scheduler.o 

CPP_DEPS += \
./lab2_assign/src/event.d \
./lab2_assign/src/main.d \
./lab2_assign/src/prepare.d \
./lab2_assign/src/process.d \
./lab2_assign/src/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
lab2_assign/src/%.o: ../lab2_assign/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


