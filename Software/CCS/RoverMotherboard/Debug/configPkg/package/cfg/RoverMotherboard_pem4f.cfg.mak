# invoke SourceDir generated makefile for RoverMotherboard.pem4f
RoverMotherboard.pem4f: .libraries,RoverMotherboard.pem4f
.libraries,RoverMotherboard.pem4f: package/cfg/RoverMotherboard_pem4f.xdl
	$(MAKE) -f /home/mrdtdev/Motherboard/Software/CCS/RoverMotherboard/src/makefile.libs

clean::
	$(MAKE) -f /home/mrdtdev/Motherboard/Software/CCS/RoverMotherboard/src/makefile.libs clean

