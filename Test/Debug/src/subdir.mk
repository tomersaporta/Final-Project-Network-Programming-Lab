################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FileTest.cpp \
../src/MultipleTCPSocketsListenerTester.cpp \
../src/TCPTest.cpp \
../src/Test.cpp \
../src/UDPTest.cpp 

OBJS += \
./src/FileTest.o \
./src/MultipleTCPSocketsListenerTester.o \
./src/TCPTest.o \
./src/Test.o \
./src/UDPTest.o 

CPP_DEPS += \
./src/FileTest.d \
./src/MultipleTCPSocketsListenerTester.d \
./src/TCPTest.d \
./src/Test.d \
./src/UDPTest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/finalProject/SocketUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


