################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../tivaRTSC_JS.cfg 

C_SRCS += \
../roveBIOS_Init.c \
../roveDeviceTemplate_Thread.c 

OBJS += \
./roveBIOS_Init.obj \
./roveDeviceTemplate_Thread.obj 

C_DEPS += \
./roveBIOS_Init.pp \
./roveDeviceTemplate_Thread.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg/linker.cmd" \
"configPkg/compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg/" 

C_DEPS__QUOTED += \
"roveBIOS_Init.pp" \
"roveDeviceTemplate_Thread.pp" 

OBJS__QUOTED += \
"roveBIOS_Init.obj" \
"roveDeviceTemplate_Thread.obj" 

C_SRCS__QUOTED += \
"../roveBIOS_Init.c" \
"../roveDeviceTemplate_Thread.c" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 


