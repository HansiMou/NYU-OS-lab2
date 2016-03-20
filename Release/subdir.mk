################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../event.cpp \
../main.cpp \
../prepare.cpp \
../process.cpp \
../scheduler.cpp 

OBJS += \
./event.o \
./main.o \
./prepare.o \
./process.o \
./scheduler.o 

CPP_DEPS += \
./event.d \
./main.d \
./prepare.d \
./process.d \
./scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


