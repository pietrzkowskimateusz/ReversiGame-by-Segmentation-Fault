################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/AlgorithmTest.cpp \
../tests/BoardTest.cpp \
../tests/main_test.cpp 

OBJS += \
./tests/AlgorithmTest.o \
./tests/BoardTest.o \
./tests/main_test.o 

CPP_DEPS += \
./tests/AlgorithmTest.d \
./tests/BoardTest.d \
./tests/main_test.d 


# Each subdirectory must supply rules for building sources it contributes
tests/%.o: ../tests/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


