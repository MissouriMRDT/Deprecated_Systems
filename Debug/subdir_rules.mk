################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
roveBIOS_Init.obj: ../roveBIOS_Init.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/opt/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c" --include_path="/opt/ti/tirtos_tivac_2_10_01_38/products/ndk_2_24_01_18/packages/ti/ndk/inc/bsd" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="roveBIOS_Init.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

roveDeviceTemplate_Thread.obj: ../roveDeviceTemplate_Thread.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/opt/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c" --include_path="/opt/ti/tirtos_tivac_2_10_01_38/products/ndk_2_24_01_18/packages/ti/ndk/inc/bsd" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="roveDeviceTemplate_Thread.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../tivaRTSC_JS.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"/opt/ti/xdctools_3_30_03_47_core/xs" --xdcpath="/opt/ti/tirtos_tivac_2_10_01_38/packages;/opt/ti/tirtos_tivac_2_10_01_38/products/bios_6_41_00_26/packages;/opt/ti/tirtos_tivac_2_10_01_38/products/ndk_2_24_01_18/packages;/opt/ti/tirtos_tivac_2_10_01_38/products/uia_2_00_02_39/packages;/opt/ti/ccsv6/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C1294NCPDT -r release -c "/opt/ti/ccsv6/tools/compiler/arm_5.1.6" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path=\"/opt/ti/ccsv6/tools/compiler/arm_5.1.6/include\" --include_path=\"/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c\" --include_path=\"/opt/ti/tirtos_tivac_2_10_01_38/products/ndk_2_24_01_18/packages/ti/ndk/inc/bsd\" -g --gcc --define=ccs=\"ccs\" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd


