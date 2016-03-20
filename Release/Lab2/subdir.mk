################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Lab2/lab2_event.o \
../Lab2/lab2_main.o \
../Lab2/lab2_monitor.o \
../Lab2/lab2_process.o \
../Lab2/lab2_scheduler.o 

CPP_SRCS += \
../Lab2/lab2_event.cpp \
../Lab2/lab2_main.cpp \
../Lab2/lab2_monitor.cpp \
../Lab2/lab2_process.cpp \
../Lab2/lab2_scheduler.cpp 

OBJS += \
./Lab2/lab2_event.o \
./Lab2/lab2_main.o \
./Lab2/lab2_monitor.o \
./Lab2/lab2_process.o \
./Lab2/lab2_scheduler.o 

CPP_DEPS += \
./Lab2/lab2_event.d \
./Lab2/lab2_main.d \
./Lab2/lab2_monitor.d \
./Lab2/lab2_process.d \
./Lab2/lab2_scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
Lab2/%.o: ../Lab2/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


