local socket = require("socket")

local host = host or "127.0.0.1"
local port = port or 10000

server = socket.bind(host, port, 1024)

local client = assert(server:accept())

client:send("hello Client")

client:close()

