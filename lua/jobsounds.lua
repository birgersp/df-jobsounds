-- Adds job sounds.
-- @ module = true
--[====[

Job sounds
===========
Connects to a socket (tcp), checks the current job of dwarves and sends messages

]====] local script_name = 'jobsounds'

local function init_socket() socket = tcp:connect('127.0.0.1', 56730) end

local function start()
    luasocket = require("plugins.luasocket")
    tcp = luasocket.tcp
    dfhack.println(script_name .. " connecting...")
    socket = nil
    pcall(init_socket)
    if (socket ~= nil) then
        dfhack.println(script_name .. " connected")
        stop = false
        time_last_send = os.time()
        loop()
    else
        dfhack.println(script_name .. " could not connect")
    end
end

local function send(msg)
    if (pcall(socket.send, socket, msg) == true) then
        time_last_send = os.time()
    else
        stop = true
    end
end

local function trigger_job_sound(unit, job_type)
    if (socket ~= nil) then
        if (df.global.window_z == unit.pos.z and df.global.window_x < unit.pos.x and
            df.global.window_x + 90 > unit.pos.x and df.global.window_y <
            unit.pos.y and df.global.window_y + 60 > unit.pos.y) then
            send(unit.id .. " " .. job_type .. "\0")
        end
    end
end

local function handle_dwarf(unit)
    if (unit.job.current_job ~= nil) then
        local job_pos = unit.job.current_job.pos
        local dx = math.abs(job_pos.x - unit.pos.x)
        local dy = math.abs(job_pos.y - unit.pos.y)
        local dz = math.abs(job_pos.z - unit.pos.z)
        if (dx <= 1 and dy <= 1 and dz <= 1) then
            trigger_job_sound(unit, unit.job.current_job.job_type)
        end
    end
end

local function check_dwarves()
    for k, unit in ipairs(df.global.world.units.active) do
        if (dfhack.units.isDwarf(unit)) then handle_dwarf(unit) end
    end
end

function loop()
    if (stop == true) then
        dfhack.println(script_name .. " stopped")
        return
    end

    if (df.global.pause_state == false) then check_dwarves() end

    dfhack.timeout(15, 'ticks', loop)
end

start()
