################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
roveIncludes/roveWareWrappers.obj: ../roveIncludes/roveWareWrappers.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="/opt/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="/opt/ti/tirtos_tivac_2_10_01_38/products/TivaWare_C_Series-2.1.0.12573c" --include_path="/opt/ti/tirtos_tivac_2_10_01_38/products/ndk_2_24_01_18/packages/ti/ndk/inc/bsd" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="roveIncludes/roveWareWrappers.pp" --obj_directory="roveIncludes" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


