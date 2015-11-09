local roveProtocol = Proto("ROVE","MRDT RoveComm");

local fieldVersion = ProtoField.uint8("rove.version","Version",base.BASE_DEC_HEX)
local fieldSequenceNum = ProtoField.uint16("rove.seq","Sequence Number",base.BASE_DEC_HEX)
local fieldDataId = ProtoField.uint16("rove.dataid","DataId",base.BASE_DEC_HEX)
local fieldDataSize = ProtoField.uint16("rove.datasize","Size",base.BASE_DEC_HEX)

roveProtocol.fields = { fieldVersion, fieldSequenceNum, fieldDataId, fieldDataSize }

function roveProtocol.dissector(buffer,pinfo,tree)
        pinfo.cols.protocol = "ROVE"
        local subtree = tree:add(roveProtocol,buffer(),"MRDT RoveComm Protocol")
        subtree:add(fieldVersion,buffer(0,1))
        subtree:add(fieldSequenceNum,buffer(1,2))
		subtree:add(fieldDataId,buffer(3,2))
		subtree:add(fieldDataSize,buffer(5,2))
		
		Dissector.get("data"):call(buffer(7):tvb(),pinfo,tree)
end

local udp_encap_table = DissectorTable.get("udp.port")

udp_encap_table:add(11000,roveProtocol)