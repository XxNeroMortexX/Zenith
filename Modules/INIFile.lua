-- Provides access to MacroQuest2 functions and commands
mq = require('mq');
ImGui = require('ImGui');

Debug("INIFile Script");

local inifile = {
	_VERSION = "inifile 1.0",
	_DESCRIPTION = "Inifile is a simple, complete ini parser for lua",
	_URL = "https://github.com/bartbes/inifile",
	_LICENSE = [[
		Copyright 2011-2015 Bart van Strien. All rights reserved.

		Redistribution and use in source and binary forms, with or without modification, are
		permitted provided that the following conditions are met:

		   1. Redistributions of source code must retain the above copyright notice, this list of
			  conditions and the following disclaimer.

		   2. Redistributions in binary form must reproduce the above copyright notice, this list
			  of conditions and the following disclaimer in the documentation and/or other materials
			  provided with the distribution.

		THIS SOFTWARE IS PROVIDED BY BART VAN STRIEN ''AS IS'' AND ANY EXPRESS OR IMPLIED
		WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
		FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BART VAN STRIEN OR
		CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
		CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
		SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
		ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
		NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
		ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

		The views and conclusions contained in the software and documentation are those of the
		authors and should not be interpreted as representing official policies, either expressed
		or implied, of Bart van Strien.
	]] -- The above license is known as the Simplified BSD license.
}

local defaultBackend = "io"

local backends = {
	io = {
		lines = function(name) return assert(io.open(name)):lines() end,
		write = function(name, contents)
			local file = assert(io.open(name, "w"))
			file:write(contents)
			file:close()
		end,
	},
	memory = {
		lines = function(text) return text:gmatch("([^\r\n]+)\r?\n") end,
		write = function(name, contents) return contents end,
	},
}

if love then
	backends.love = {
		lines = love.filesystem.lines,
		write = function(name, contents) love.filesystem.write(name, contents) end,
	}
	defaultBackend = "love"
end

function inifile.parse(name, backend)
	backend = backend or defaultBackend
	local t = {}
	local section
	local comments = {}
	local sectionorder = {}
	local cursectionorder
	local lineNumber = 0
	local errors = {}

	for line in backends[backend].lines(name) do
		lineNumber = lineNumber + 1
		local validLine = false

		-- Section headers
		local s = line:match("^%[([^%]]+)%]$")
		if s then
			section = s
			t[section] = t[section] or {}
			cursectionorder = {name = section}
			table.insert(sectionorder, cursectionorder)
			validLine = true
		end

		-- Comments
		s = line:match("^;(.+)$")
		if s then
			local commentsection = section or comments
			comments[commentsection] = comments[commentsection] or {}
			table.insert(comments[commentsection], s)
			validLine = true
		end

		-- Key-value pairs
		local key, value = line:match("^([%w_]+)%s-=%s-(.+)$")
		if tonumber(value) then value = tonumber(value) end
		if value == "true" then value = true end
		if value == "false" then value = false end
		if key and value ~= nil and section ~= nil then
			key = key:lower()  -- Convert key to lowercase
			t[section][key] = value
			table.insert(cursectionorder, key)
			validLine = true
		end

		if not validLine then
			table.insert(errors, ("Line %d: Invalid data found '%s'"):format(lineNumber, line))
		end
	end

	-- Store our metadata in the __inifile field in the metatable
	return setmetatable(t, {
		__inifile = {
			comments = comments,
			sectionorder = sectionorder,
		}
	}), errors
end

function inifile.save(name, t, backend)
    backend = backend or defaultBackend
    local contents = {}

    -- Get our metadata if it exists
    local metadata = getmetatable(t)
    local comments, sectionorder

    if metadata then metadata = metadata.__inifile end
    if metadata then
        comments = metadata.comments
        sectionorder = metadata.sectionorder
    end

    -- If there are comments before sections,
    -- write them out now
    if comments and comments["comments"] then
        for i, v in ipairs(comments["comments"]) do
            table.insert(contents, (";%s"):format(v))
            table.insert(contents, (";%s"):format(v))
        end
        table.insert(contents, "")
    end

    local function writevalue(section, key)
        local value = section[key]
        -- Discard if it doesn't exist (anymore)
        if value == nil then return end
        table.insert(contents, ("%s=%s"):format(key, tostring(value)))
    end

    local function tableLike(value)
        local function index()
            return value[1]
        end

        return pcall(index) and pcall(next, value)
    end

    local function writesection(section, order)
        local s = t[section]
        -- Discard if it doesn't exist (anymore)
        if not s then return end
        table.insert(contents, ("[%s]"):format(section))

        assert(tableLike(s), ("Invalid section %s: not table-like"):format(section))

        -- Write our comments out again, sadly we have only achieved
        -- section-accuracy so far
        if comments and comments[section] then
            for i, v in ipairs(comments[section]) do
                table.insert(contents, (";%s"):format(v))
            end
        end

        -- Write the key-value pairs with optional order
        local done = {}
        if order then
            for _, v in ipairs(order) do
                done[v] = true
                writevalue(s, v)
            end
        end
        for i, _ in pairs(s) do
            if not done[i] then
                writevalue(s, i)
            end
        end

        -- Newline after the section
        table.insert(contents, "")
    end

    -- Write the sections, with optional order
    local done = {}
    if sectionorder then
        for _, section in ipairs(sectionorder) do
            done[section] = true
            writesection(section)
        end
    end
    -- Write anything that wasn't ordered
    for i, _ in pairs(t) do
        if not done[i] then
            writesection(i)
        end
    end

    return backends[backend].write(name, table.concat(contents, "\n"))
end


--NeroMorte Added Features.

-- Function to check and update INI file
function update_ini(default_config)
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    if not scriptDir then
        scriptDir = getScriptDir("inifile.lua")
    end
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    if not iniDir then
        iniDir = scriptDir:gsub(FindStrings, ReplaceWith)
    end
    if not filename then
        filename = string.format("Bot_%s_%s.ini", className, cleanName)
    end
    Debug("INI File: ", filename)  -- Debug print to check the file path
    local file = io.open(iniDir .. filename, "r")
    local iniData = {}

    local config = inifile.parse(iniDir .. filename)

    -- Function to recursively update config with default values
    local function update_section(default_section, config_section)
        if not config_section then
            return default_section
        end
        for key, value in pairs(default_section) do
            if type(value) == "table" then
                config_section[key] = update_section(value, config_section[key])
            else
                config_section[key] = config_section[key] or value
            end
        end
        return config_section
    end

    for section, keys in pairs(default_config) do
        config[section] = update_section(keys, config[section])
    end

    -- Create new INI structure with ordered sections and keys
    local ordered_config = {}
    for _, section in ipairs(default_config.__inifile.sectionorder) do
        ordered_config[section] = config[section]
    end

    -- Attach comments metadata
    setmetatable(ordered_config, { __inifile = { comments = default_config.__inifile.comments, sectionorder = default_config.__inifile.sectionorder } })

    inifile.save(iniDir .. filename, ordered_config)
end

-- Function to get the directory of the current script
function getScriptDir(INIFile)
    local str = debug.getinfo(1, "S").source:sub(2);
	Debug("Script Path: ", str);  -- Debug print to check the script source path
	-- Pattern to match any file name ending with .lua, case insensitive
	local pattern = "[^/\\]+%.lua$"
    local dir = str:gsub(pattern, "")
    --local dir = str:gsub(INIFile, "")
	Debug("Script Directory: ", dir);  -- Debug print to check the script directory
	
    return dir
end

-- Function to parse an INI file
function parseIni(data)
    local iniData = {}
    local section

    for line in data:gmatch("[^\r\n]+") do
        local s = line:match("^%[([^%]]+)%]$")
        if s then
            section = s
            iniData[section] = iniData[section] or {}

            Debug("Parsed section: " .. section)
        elseif section then
			local key, value = line:match("^([^=]+)=(.*)$")
			if key and value then
				iniData[section][key] = value
				Debug("Parsed key-value pair: " .. key .. "=" .. value .. " in section: " .. section)
			elseif line and line:match("^;%s*") then
				table.insert(iniData[section], {type = "comment", text = line})
				Debug("Parsed comment: " .. line)
			elseif line and line:match("^%s*$") then
				table.insert(iniData[section], {type = "blank"})
				Debug("Parsed blank line")
			end

        end
    end

    return iniData
end

-- Function to read all INI keys and set them as global variables
--usage: readIniKeys("Modules\\inifile.lua", "BOT_INIS\\")
function readIniKeys(FindStrings, ReplaceWith)
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    if not scriptDir then 
        local scriptDir = getScriptDir("inifile.lua") 
    end
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    if not iniDir then 
        local iniDir = scriptDir:gsub(FindStrings, ReplaceWith) 
    end
    if not filename then 
        local filename = string.format("Bot_%s_%s.ini", className, cleanName)
    end
    Debug("INI File: ", filename)  -- Debug print to check the file path
    local file = io.open(iniDir .. filename, "r")
    local iniData = {}

    if file then
        iniData = parseIni(file:read("*all"))
        file:close()
    end
    -- Create a table to store the variables
    ini = {}
    
	
    for section, keys in pairs(iniData) do
        -- Debug print to check the section and keys
        --print("Debug: section:", section)
        --print("Debug: keys:", keys)
        for key, value in pairs(keys) do
            -- Debug print to check the key and value
            --print("Debug: key:", key)
            --print("Debug: value:", value)
            if type(key) == "string" and type(value) == "string" then
				Debug("Creating Global Variable [ " .. key:lower() .. " = " .. value:lower() .. " ]")
				ini[key:lower()] = value:lower() --this creates print(ini.key)
				--print("Key:" .. key .. " - " .. "Value:" .. value)
			else
				-- Convert key and value to strings, handling tables appropriately
				local keyStr = type(key) == "table" and tableToString(key) or tostring(key)
				local valueStr = type(value) == "table" and tableToString(value) or tostring(value)

				-- Print the actual text from the INI file with the desired format
				Debug(string.format("Warning - Section: [%s] Key: [%s] Text: [%s] Type: [%s]", section, keyStr, value.text, value.type))
			end
        end
    end
end

-- Function to update a key=value pair
function updateKeyValue(section, key, value)
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    local scriptDir = getScriptDir("inifile.lua")
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: ", filename)  -- Debug print to check the file path
    local file = io.open(filename, "r")
    local lines = {}
    local in_section = false

    key = key:lower()
    value = value:lower()

    if file then
        for line in file:lines() do
            if line:match("^%[.-%]") then
                in_section = line:match("^%[(.-)%]") == section
                --Debug("Entering section:", line)
            end
            if in_section then
                --Debug("In section:", section)
                local line_key = line:match("^(.-)=")
                if line_key and line_key:lower() == key then
                    Debug("Found key:", line)
                    line = key .. "=" .. value
                    Debug("Updated line:", line)
                else
                    Debug("Key not found:", line)
                end
            end
            table.insert(lines, line)
        end
        file:close()
    else
        Debug("Error: Unable to open file for reading:", filename)
        return
    end

    file = io.open(filename, "w")
    if not file then
        Debug("Error: Unable to open file for writing:", filename)
        return
    end
    for _, line in ipairs(lines) do
        file:write(line .. "\n")
    end
    file:close()
end

-- Function to delete a key=value pair
function deleteKeyValue(section, key)
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    local scriptDir = getScriptDir("inifile.lua")
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: ", filename)  -- Debug print to check the file path
    local file = io.open(filename, "r")
    local lines = {}
    local in_section = false

    key = key:lower()

    if file then
        for line in file:lines() do
            if line:match("^%[.-%]") then
                in_section = line:match("^%[(.-)%]") == section
                Debug("Entering section:", line)
            end
            if in_section then
                local line_key = line:match("^(.-)=")
                if line_key then
                    line_key = line_key:lower()
                end

                if line_key ~= key then
                    table.insert(lines, line)
                else
                    Debug("Removing key:", line)
                end
            else
                table.insert(lines, line)
            end
        end
        file:close()
    else
        Debug("Error: Unable to open file for reading:", filename)
        return
    end

    file = io.open(filename, "w")
    if not file then
        Debug("Error: Unable to open file for writing:", filename)
        return
    end
    for _, line in ipairs(lines) do
        file:write(line .. "\n")
    end
    file:close()
end

-- Function to insert a key=value pair between two existing keys
function InsertKeyValue(section, keyBefore, keyAfter, newKey, newValue)
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    local scriptDir = getScriptDir("inifile.lua")
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: ", filename)  -- Debug print to check the file path
    local file = io.open(filename, "r")
    local lines = {}
    local sectionFound = false
    local keyInserted = false

    newKey = newKey:lower()
    newValue = newValue:lower()

    if file then
        for line in file:lines() do
            if line:match("^%[" .. section .. "%]$") then
                sectionFound = true
                --Debug("Entering section:", line)
            elseif sectionFound and line:match("^%[") then
                sectionFound = false
                --Debug("Exiting section:", line)
            end

            if sectionFound then
                local lineKey = line:match("^(.-)=")
                if lineKey then
                    lineKey = lineKey:lower()
                end

                if lineKey == keyBefore:lower() then
                    Debug("Found keyBefore:", line)
                    table.insert(lines, line)
                    table.insert(lines, newKey .. "=" .. newValue)
                    Debug("Inserted new key-value:", newKey .. "=" .. newValue)
                    keyInserted = true
                elseif keyInserted and lineKey == keyAfter:lower() then
                    Debug("Found keyAfter:", line)
                    table.insert(lines, line)
                    keyInserted = false
                else
                    table.insert(lines, line)
                end
            else
                table.insert(lines, line)
            end
        end
        file:close()
    else
        Debug("Error: Unable to open file for reading:", filename)
        return
    end

    file = io.open(filename, "w")
    if not file then
        Debug("Error: Unable to open file for writing:", filename)
        return
    end
    for _, line in ipairs(lines) do
        file:write(line .. "\n")
    end
    file:close()
end
	
return inifile