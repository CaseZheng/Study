local socket = require("socket")

local host = host or "127.0.0.1"
local port = port or 10000

cli = assert(socket.connect(host, port))

cli:send("fefefefe")
local s, status, partial = cli:receive()
print(s)
print(partial)
if status == "closed" then 
    print("cli close")
end

cli:close()

