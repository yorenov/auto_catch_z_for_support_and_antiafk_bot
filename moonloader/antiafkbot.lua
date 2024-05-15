local samp = require "lib.samp.events"
local encoding = require 'encoding'
local requests = require "requests"
encoding.default = 'CP1251'
u8 = encoding.UTF8

local TOKEN_SUPER = ""
local CHAT_ID_SUPER = ""

local PACKET_CHECK = false

local state = true
local afk = false
local currentTimer = os.clock()

local currentRunning = false
local checkAdmin = false
local admins = {}
local adminBlackList = {}

local moves = {
    "under",
    "walk",
    "run",
    "jump",
    "look_right",
    "look_left"
}

function checkAdmins()
    while true do wait(5000)
        if afk and sampIsLocalPlayerSpawned() and not checkAdmin then 
            checkAdmin = true
            sampSendChat("/admins")
        end
    end
end

function samp.onServerMessage(clr, text)
    if (text:find("Àäìèíèñòðàòîð .*%[%d+%] ïîäáðîñèë Âàñ") or text:find("Erza_Scarlet")) and state and not checkAdmin then 
        sendTelegramMessage('Ïðîèçîøëî âçàèìîäåéñòâèå ñ àäìèíèñòðàòîðîì/âàìè.')
    end

    if checkAdmin and afk then 
        if text:find("Àäìèíû îíëàéí%:") then 
            return false
        end

        local id = text:match(".*%[(%d+)%]%s+%(%d+%s+lvl%)")
        if id then 
            local result, myId = sampGetPlayerIdByCharHandle(playerPed)
            if result and myId ~= id then 
                sampAddChatMessage(id, -1)
                table.insert(admins, tonumber(id))
                return false
            end
        else
            if not text:find("Àäìèíû îíëàéí%:") then 
                checkAdmin = false
            end
        end
    else 
        checkAdmin = false
    end
end

local ztimer = os.clock()

addEventHandler("onReceivePacket", function(id, bs)
    if id == 215 and PACKET_CHECK then 
        raknetBitStreamResetReadPointer(bs)
        raknetBitStreamIgnoreBits(bs, 64)
        local length = raknetBitStreamReadInt32(bs)
        if length <= 1000 and length > 0 then 
            local str = raknetBitStreamReadString(bs, length)
            local n = str:match("interface%(%'UnansweredRequests%'%)%.setRequests%(%'%[%[%[(%d+)%,0%]%]%,%d+%]%'%)")
            if n then 
                math.randomseed(os.time())
                if os.clock() - ztimer >= math.random(0, 1) then 
                    sampSendChat("/z "..n)
                    PACKET_CHECK = false

                    ztimer = os.clock()
                end
            end
        end
    end
end)

function main()
    while not isSampAvailable() do wait(100) end 

    sampRegisterChatCommand("_afk", function()
        afk = not afk
        if not afk then 
            checkAdmin = false 
            currentRunning = false
            admins = {}
            adminBlackList = {}
        end
    end)

    lua_thread.create(checkAdmins)

    local time = math.random(0, 100)
    math.randomseed(os.time())
    while true do wait(0)
        if isKeyJustPressed(0x7A) then 
            PACKET_CHECK = true
        end

        if afk and os.clock() - currentTimer >= time then 
            
            local randomMove = moves[math.random(1, 4)]

            if randomMove == "under" then 
                setGameKeyState(18, 2)
            elseif randomMove == "jump" then 
                taskJump(playerPed, true)
            elseif randomMove == "walk" or randomMove == "run" then 
                if not currentRunning then 
                    local currentPos = {getCharCoordinates(playerPed)}
                    lua_thread.create(go_to_point, {x = currentPos[1] + math.random(-3, 3), y = currentPos[2] + math.random(-3, 3)}, randomMove == "run")
                end
            end

            time = math.random(0, 100)

            currentTimer = os.clock()
        end

        for k, v in pairs(adminBlackList) do 
            if os.clock() - v >= 45 then 
                adminBlackList[k] = nil
            end
        end

        if afk then 
            local myResult, myId = sampGetPlayerIdByCharHandle(playerPed)
            for k, v in ipairs(getAllChars()) do 
                local result, id = sampGetPlayerIdByCharHandle(v)
                if result then 
                    local resultNick, playerNickname = pcall(sampGetPlayerNickname, id)
                    if resultNick then 
                        local flag = false
                        for aK, aV in ipairs(admins) do 
                            if tonumber(aV) == tonumber(id) then 
                                flag = true

                                local secondFlag = false
                                for bK, bV in pairs(adminBlackList) do 
                                    if playerNickname == bK and bV ~= nil then 
                                        secondFlag = true 
                                    end
                                end

                                if myResult and tonumber(aV) == tonumber(myId) then 
                                    flag = false
                                end

                                if secondFlag then 
                                    flag = false 
                                else 
                                    break 
                                end
                            end
                        end
                        if flag then 
                            sendTelegramMessage('Ðÿäîì íàøåëñÿ àäìèíèñòðàòîð! Íèêíåéì: '..playerNickname..'['..id..']')
                            adminBlackList[playerNickname] = os.clock()
                        end
                    end
                end
            end
        end
    end
end

--[[
    local secondflag = true 
                            for bK, bV in ipairs(adminBlackList) do 
                                if playerNickname == bK then 
                                    secondFlag = false 
                                end
                            end
]]

function go_to_point(point, is_sprint)
    currentRunning = true

    local dist
    local timer = os.clock()
    repeat
        set_camera_direction(point)
        wait(0)
        setGameKeyState(1, -255)
        local mx, my, mz = getCharCoordinates(playerPed)
        if is_sprint then setGameKeyState(16, 255) end
        dist = getDistanceBetweenCoords2d(point.x, point.y, mx, my)

        if os.clock() - timer >= 5 then 
            currentRunning = false
            break
        end
    until dist < 0.6

    currentRunning = false
end

function set_camera_direction(point)
    local c_pos_x, c_pos_y, c_pos_z = getActiveCameraCoordinates()
    local vect = {x = point.x - c_pos_x, y = point.y - c_pos_y}
    local ax = math.atan2(vect.y, -vect.x)
    setCameraPositionUnfixed(0.0, -ax)
end

function sendTelegramMessage(text)
    local URL = "https://api.telegram.org/bot" .. TOKEN_SUPER .. "/sendMessage?chat_id=" .. CHAT_ID_SUPER .. "&text=" .. text
    URL = AnsiToUtf8(URL)
    requests.get(URL)
end

local ansi_decode = {
    [128]='\208\130',[129]='\208\131',[130]='\226\128\154',[131]='\209\147',[132]='\226\128\158',[133]='\226\128\166',
    [134]='\226\128\160',[135]='\226\128\161',[136]='\226\130\172',[137]='\226\128\176',[138]='\208\137',[139]='\226\128\185',
    [140]='\208\138',[141]='\208\140',[142]='\208\139',[143]='\208\143',[144]='\209\146',[145]='\226\128\152',
    [146]='\226\128\153',[147]='\226\128\156',[148]='\226\128\157',[149]='\226\128\162',[150]='\226\128\147',[151]='\226\128\148',
    [152]='\194\152',[153]='\226\132\162',[154]='\209\153',[155]='\226\128\186',[156]='\209\154',[157]='\209\156',
    [158]='\209\155',[159]='\209\159',[160]='\194\160',[161]='\209\142',[162]='\209\158',[163]='\208\136',
    [164]='\194\164',[165]='\210\144',[166]='\194\166',[167]='\194\167',[168]='\208\129',[169]='\194\169',
    [170]='\208\132',[171]='\194\171',[172]='\194\172',[173]='\194\173',[174]='\194\174',[175]='\208\135',
    [176]='\194\176',[177]='\194\177',[178]='\208\134',[179]='\209\150',[180]='\210\145',[181]='\194\181',
    [182]='\194\182',[183]='\194\183',[184]='\209\145',[185]='\226\132\150',[186]='\209\148',[187]='\194\187',
    [188]='\209\152',[189]='\208\133',[190]='\209\149',[191]='\209\151'
}

function AnsiToUtf8(s)
    local r, b = ''
    for i = 1, s and s:len() or 0 do
        b = s:byte(i)
        if b < 128 then
            r = r..string.char(b)
        else
            if b > 239 then
                r = r..'\209'..string.char(b - 112)
            elseif b > 191 then
                r = r..'\208'..string.char(b - 48)
            elseif ansi_decode[b] then
                r = r..ansi_decode[b]
            else
                r = r..'_'
            end
        end
    end
    return r
end
