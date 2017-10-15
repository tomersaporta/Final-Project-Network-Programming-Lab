################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Broker.cpp \
../src/BrokerMng.cpp \
../src/Dispatcher.cpp \
../src/Login.cpp \
../src/Server.cpp \
../src/TCPMSNServer.cpp \
../src/User.cpp 

OBJS += \
./src/Broker.o \
./src/BrokerMng.o \
./src/Dispatcher.o \
./src/Login.o \
./src/Server.o \
./src/TCPMSNServer.o \
./src/User.o 

CPP_DEPS += \
./src/Broker.d \
./src/BrokerMng.d \
./src/Dispatcher.d \
./src/Login.d \
./src/Server.d \
./src/TCPMSNServer.d \
./src/User.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/finalProject/SocketUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


