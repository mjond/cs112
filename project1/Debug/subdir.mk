################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CollectionTester.cpp \
../Movie.cpp \
../MovieCollection.cpp \
../MovieTester.cpp \
../tester.cpp 

OBJS += \
./CollectionTester.o \
./Movie.o \
./MovieCollection.o \
./MovieTester.o \
./tester.o 

CPP_DEPS += \
./CollectionTester.d \
./Movie.d \
./MovieCollection.d \
./MovieTester.d \
./tester.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


