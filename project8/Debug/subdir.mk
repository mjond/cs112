################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AccountManager.cpp \
../ArrayQueue.cpp \
../ArrayQueueTester.cpp \
../PalindromeDetector.cpp \
../Stack.cpp \
../StackTester.cpp \
../tester.cpp 

OBJS += \
./AccountManager.o \
./ArrayQueue.o \
./ArrayQueueTester.o \
./PalindromeDetector.o \
./Stack.o \
./StackTester.o \
./tester.o 

CPP_DEPS += \
./AccountManager.d \
./ArrayQueue.d \
./ArrayQueueTester.d \
./PalindromeDetector.d \
./Stack.d \
./StackTester.d \
./tester.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


