--
-- Autogenerated by Thrift
--
-- DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
-- @generated
--


local require 'Thrift'
local require 'vending_machine_ttypes'

local BeveragePreferenceServiceClient = __TObject.new(__TClient, {
  __type = 'BeveragePreferenceServiceClient'
})

function BeveragePreferenceServiceClient:GetBeverage(btype)
  self:send_GetBeverage(btype)
  return self:recv_GetBeverage(btype)
end

function BeveragePreferenceServiceClient:send_GetBeverage(btype)
  self.oprot:writeMessageBegin('GetBeverage', TMessageType.CALL, self._seqid)
  local args = GetBeverage_args:new{}
  args.btype = btype
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function BeveragePreferenceServiceClient:recv_GetBeverage(btype)
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = GetBeverage_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
  if result.success ~= nil then
    return result.success
  end
  error(TApplicationException:new{errorCode = TApplicationException.MISSING_RESULT})
end
local BeveragePreferenceServiceIface = __TObject:new{
  __type = 'BeveragePreferenceServiceIface'
}


local BeveragePreferenceServiceProcessor = __TObject.new(__TProcessor
, {
 __type = 'BeveragePreferenceServiceProcessor'
})

function BeveragePreferenceServiceProcessor:process(iprot, oprot, server_ctx)
  local name, mtype, seqid = iprot:readMessageBegin()
  local func_name = 'process_' .. name
  if not self[func_name] or ttype(self[func_name]) ~= 'function' then
    if oprot ~= nil then
      iprot:skip(TType.STRUCT)
      iprot:readMessageEnd()
      x = TApplicationException:new{
        errorCode = TApplicationException.UNKNOWN_METHOD
      }
      oprot:writeMessageBegin(name, TMessageType.EXCEPTION, seqid)
      x:write(oprot)
      oprot:writeMessageEnd()
      oprot.trans:flush()
    end
    return false, 'Unknown function '..name
  else
    return self[func_name](self, seqid, iprot, oprot, server_ctx)
  end
end

function BeveragePreferenceServiceProcessor:process_GetBeverage(seqid, iprot, oprot, server_ctx)
  local args = GetBeverage_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = GetBeverage_result:new{}
  local status, res = pcall(self.handler.GetBeverage, self.handler, args.btype)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('GetBeverage', reply_type, seqid)
  result:write(oprot)
  oprot:writeMessageEnd()
  oprot.trans:flush()
  return status, res
end

-- HELPER FUNCTIONS AND STRUCTURES

local GetBeverage_args = __TObject:new{
  btype
}

function GetBeverage_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.I32 then
        self.btype = iprot:readI32()
      else
        iprot:skip(ftype)
      end
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function GetBeverage_args:write(oprot)
  oprot:writeStructBegin('GetBeverage_args')
  if self.btype ~= nil then
    oprot:writeFieldBegin('btype', TType.I32, 1)
    oprot:writeI32(self.btype)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

GetBeverage_result = __TObject:new{
  success
}

function GetBeverage_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 0 then
      if ftype == TType.STRING then
        self.success = iprot:readString()
      else
        iprot:skip(ftype)
      end
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function GetBeverage_result:write(oprot)
  oprot:writeStructBegin('GetBeverage_result')
  if self.success ~= nil then
    oprot:writeFieldBegin('success', TType.STRING, 0)
    oprot:writeString(self.success)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end
