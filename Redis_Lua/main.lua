package.path = "./?.lua;" .. package.path
pcall(require, "luarocks.require")

local redis = require 'redis'
local params = require 'ip_port'

local info = params["info"]


local ConflictDetection = params["ConflictDetection"]
local host = ConflictDetection["host"]
local port = ConflictDetection["port"]
local allkeys = {}
local index = 1
for k,v in pairs(port) do
	print(k, host, v)
	local ip_port = { host = host, port = v}
	local client = redis.connect(ip_port)
	local response = client:ping();
	if(response) then
		local key = client:keys("*")
		for keykey,keyvalue in pairs(key) do
			local flag = nil
			for kk, vv in pairs(allkeys) do
				if(vv == keyvalue) then
					print("Conflict Key :" .. keyvalue)
					break;
				else
					flag = 1
				end
			end
			if(flag ~= 1) then
				allkeys[index] = keyvalue
			end
		end
	else
		print("连接失败")
	end
end

print("===============================这是一条分割线==================================")
for k,v in pairs(info) do
	print(k, v.host, v.port)
	local client = redis.connect(v)
	local response = client:ping();
	if(response) then
		local value = client:info()
		local memory = value["memory"]
		print("used_memory_human" .. " 使用容量 " .. memory["used_memory_human"])
		print("used_memory_peak_human" .. " 内存峰值 " .. memory["used_memory_peak_human"])

		value = client:config("get","maxmemory")
		value["maxmemory"] = value["maxmemory"]/1024/1024 .. "m"
		print("maxmemory" .. " 总容量 " .. value["maxmemory"])
	else
		print("连接失败")
	end
	print("===============================这是一条分割线==================================")
end

