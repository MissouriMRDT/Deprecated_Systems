local roveProtocol = Proto("ROVE","MRDT RoveComm");

local fieldVersion = ProtoField.uint8("rove.version","Version",base.DEC)
local fieldSequenceNum = ProtoField.uint16("rove.seq","Sequence Number",base.DEC_HEX)
local fieldFlags = ProtoField.uint8("rove.flags","Flags",base.HEX)
local fieldFlagsACKReq = ProtoField.bool("rove.flags.ackreq","ACK Request",8,nil,0x01)
local fieldDataId = ProtoField.uint16("rove.dataid","DataId",base.DEC_HEX)
local fieldDataSize = ProtoField.uint16("rove.datasize","Size",base.DEC)
roveProtocol.fields = { fieldVersion, fieldSequenceNum, fieldFlags, fieldFlagsACKReq, fieldDataId, fieldDataSize }

local expertBadLength = ProtoExpert.new("BadLength", "The encoded length does not equal the actual length", expert.group.MALFORMED, expert.severity.ERROR)
roveProtocol.experts = { expertBadLength }

function roveProtocol.dissector(buffer,pinfo,tree)
		pinfo.cols.protocol = "ROVE"
		
		pinfo.cols['info'] = 'DataId: ' .. buffer:range(4,2):uint() .. ', Seq: ' .. buffer:range(1,2):uint()
		
		local subtree = tree:add(roveProtocol,buffer(),"MRDT RoveComm Protocol"
			.. ', DataId: ' .. buffer:range(4,2):uint()
			.. ', Seq: ' .. buffer:range(1,2):uint())
		subtree:add(fieldVersion,buffer(0,1))
		subtree:add(fieldSequenceNum,buffer(1,2))
		local flagTree = subtree:add(fieldFlags,buffer(3,1))
			flagTree:add(fieldFlagsACKReq,buffer(3,1))
		subtree:add(fieldDataId,buffer(4,2))
		subtree:add(fieldDataSize,buffer(6,2))
		
		local actualLength = buffer:reported_length_remaining() - 8
		local expectedLength = buffer:range(6,2):uint()
		if (actualLength - expectedLength ~= 0) then subtree:add_proto_expert_info(expertBadLength) end
		
		Dissector.get("data"):call(buffer(8):tvb(),pinfo,tree)
end

local udp_encap_table = DissectorTable.get("udp.port")
udp_encap_table:add(11000,roveProtocol)