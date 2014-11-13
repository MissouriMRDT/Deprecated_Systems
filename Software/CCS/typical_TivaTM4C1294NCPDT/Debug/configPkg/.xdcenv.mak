#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/tirtos_tivac_2_01_00_03/packages;C:/ti/tirtos_tivac_2_01_00_03/products/bios_6_40_03_39/packages;C:/ti/tirtos_tivac_2_01_00_03/products/ndk_2_23_01_01/packages;C:/ti/tirtos_tivac_2_01_00_03/products/uia_2_00_01_34/packages;C:/ti/ccsv6/ccs_base
override XDCROOT = c:/ti/xdctools_3_30_03_47_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/tirtos_tivac_2_01_00_03/packages;C:/ti/tirtos_tivac_2_01_00_03/products/bios_6_40_03_39/packages;C:/ti/tirtos_tivac_2_01_00_03/products/ndk_2_23_01_01/packages;C:/ti/tirtos_tivac_2_01_00_03/products/uia_2_00_01_34/packages;C:/ti/ccsv6/ccs_base;c:/ti/xdctools_3_30_03_47_core/packages;..
HOSTOS = Windows
endif
