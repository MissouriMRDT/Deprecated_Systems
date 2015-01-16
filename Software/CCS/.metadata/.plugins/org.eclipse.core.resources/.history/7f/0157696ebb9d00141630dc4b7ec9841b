################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
EK_TM4C1294XL.obj: ../EK_TM4C1294XL.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="c:/ti/tirtos_tivac_2_01_00_03/products/TivaWare_C_Series-2.1.0.12573c" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=_INCLUDE_NIMU_CODE --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="EK_TM4C1294XL.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

listen_handshake_tcp_ip_proto.obj: ../listen_handshake_tcp_ip_proto.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="c:/ti/tirtos_tivac_2_01_00_03/products/TivaWare_C_Series-2.1.0.12573c" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=_INCLUDE_NIMU_CODE --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="listen_handshake_tcp_ip_proto.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tcpEcho.obj: ../tcpEcho.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="c:/ti/tirtos_tivac_2_01_00_03/products/TivaWare_C_Series-2.1.0.12573c" -g --gcc --define=ccs="ccs" --define=PART_TM4C1294NCPDT --define=ccs --define=TIVAWARE --define=_INCLUDE_NIMU_CODE --display_error_number --diag_warning=225 --diag_wrap=off --gen_func_subsections=on --preproc_with_compile --preproc_dependency="tcpEcho.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../tcpEcho.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"c:/ti/xdctools_3_30_03_47_core/xs" --xdcpath="c:/ti/tirtos_tivac_2_01_00_03/packages;c:/ti/tirtos_tivac_2_01_00_03/products/bios_6_40_03_39/packages;c:/ti/tirtos_tivac_2_01_00_03/products/ndk_2_23_01_01/packages;c:/ti/tirtos_tivac_2_01_00_03/products/uia_2_00_01_34/packages;c:/ti/ccsv6/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.tiva:TM4C1294NCPDT -r release -c "c:/ti/ccsv6/tools/compiler/arm_5.1.6" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd


