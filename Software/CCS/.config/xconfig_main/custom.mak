## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,em4f linker.cmd package/cfg/main_pem4f.oem4f

linker.cmd: package/cfg/main_pem4f.xdl
	$(SED) 's"^\"\(package/cfg/main_pem4fcfg.cmd\)\"$""\"C:/Users/Zeus/Documents/GitHub/motherboard-squad/Software/CCS/.config/xconfig_main/\1\""' package/cfg/main_pem4f.xdl > $@
