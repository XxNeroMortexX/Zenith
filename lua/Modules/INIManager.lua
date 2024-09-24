local mq = require("mq")

Debug("INIManager Script");

-- Function to get the directory of the current script 
function getScriptDir()
    local str = debug.getinfo(1, "S").source:sub(2);
	Debug("Debug: script source path: ", str);  -- Debug print to check the script source path
    local dir = str:gsub("INIManager.lua", "")
	Debug("Debug: script directory: ", dir);  -- Debug print to check the script directory
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

-- Function to write the INI data back to the file, including comments and blank lines
function writeIni(filename, data)
    local file = io.open(filename, "w")
    if not file then
        Debug("Error: Unable to open file for writing: " .. filename)
        return
    end

    local currentSection = nil

    for _, item in ipairs(data) do
        if item.type == "comment" then
            if item.text:sub(1, 1) == ";" then
                file:write(item.text .. "\n")  -- Write comments as is if they already start with a semicolon
            else
                file:write("; " .. item.text .. "\n")  -- Write comments with a semicolon prefix
            end
        elseif item.type == "blank" then
            file:write("\n")  -- Write a blank line
        elseif item.type == "section" then
            if item.name and item.name ~= "_global_" then
                if currentSection ~= item.name then
                    file:write("[" .. item.name .. "]\n")  -- Write the section header for settings format
                    currentSection = item.name
                end
            elseif item.section and item.section ~= "_global_" then
                if currentSection ~= item.section then
                    file:write("[" .. item.section .. "]\n")  -- Write the section header for iniData format
                    currentSection = item.section
                end
            else
                Debug("Error: item.name and item.section are nil for section header")
            end
        elseif item.type == "key" then
            file:write(item.key .. "=" .. item.value .. "\n")  -- Write key=value pairs
        end
    end

    file:close()
end


-- Function to create or update an INI file
function saveSettings(settings)
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    local scriptDir = getScriptDir()
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    -- Modify the script directory to point to the desired INI directory
    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    Debug("INI directory: " .. iniDir)

    -- Create the directory if it doesn't exist
    os.execute("mkdir \"" .. iniDir .. "\"")

    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: " .. filename)
    local file = io.open(filename, "r")
    local iniData = {}

    if file then
        iniData = parseIni(file:read("*all"))
        file:close()
    end

    -- Add missing keys/values, comments, and blank lines
    for _, item in ipairs(settings) do
        Debug("[+G+] Processing item: Section=" .. tostring(item.section) .. ", Key=" .. tostring(item.key) .. ", Value=" .. tostring(item.value) .. ", Text=" .. tostring(item.text) .. ", Type=" .. item.type)
        Debug("Checking item type: " .. item.type)
        
        if item.type == "section" then
            if iniData[item.name] then
                Debug("Section '" .. item.name .. "' already exists.")
            else
                Debug("Adding missing section: " .. item.name)
                iniData[item.name] = {}
            end
        elseif item.type == "key" then
            -- Ensure the section exists
            if not iniData[item.section] then
                iniData[item.section] = {}
            end
            
            if iniData[item.section][item.key] then
                if iniData[item.section][item.key] == item.value then
                    Debug("Key '" .. item.key .. "' already exists with the same value, skipping...")
                else
                    Debug("Key '" .. item.key .. "' exists with a different current value [" .. iniData[item.section][item.key] .. "] compared to Default value [" .. item.value .. "], skipping...")
                    item.value = iniData[item.section][item.key]
                end
            else
                Debug("Adding missing key: " .. item.key .. " with value: " .. item.value .. " in section: " .. item.section)
                iniData[item.section][item.key] = item.value
            end
        elseif item.type == "comment" then
            -- Handle comments; if no section, treat as global
            local section = item.section or "_global_"
            if not iniData[section] then
                iniData[section] = {}
            end

			local commentExists = false
			for _, line in ipairs(iniData[section]) do
				Debug("Checking line: " .. tostring(line) .. ", item.text: " .. tostring(item.text) .. ", item.type: " .. tostring(item.type) .. ", item.section: " .. tostring(item.section) .. ", item.key: " .. tostring(item.key) .. ", item.value: " .. tostring(item.value))
				for _, setting in ipairs(settings) do
					Debug("Type = " .. tostring(setting.type) .. ", Text=" .. tostring(setting.text) .. ", Line=" .. tostring(line))
					if setting.type == "comment" and setting.text == item.text then
						commentExists = true
						break
					end
				end
			end



            if commentExists then
                Debug("Comment '" .. item.text .. "' already exists, skipping...")
            else
                Debug("Adding missing comment: " .. item.text)
                table.insert(iniData[section], {type = "comment", text = item.text})
            end
        elseif item.type == "blank" then
            -- Handle blank lines; if no section, treat as global
            local section = item.section or "_global_"
            if not iniData[section] then
                iniData[section] = {}
            end

            local blankExists = false
            for _, line in ipairs(iniData[section]) do
                if line and type(line) == "string" and line:match("^%s*$") then
                    blankExists = true
                    break
                end
            end

            if blankExists then
                Debug("Blank line already exists, skipping...")
            else
                Debug("Adding missing blank line")
                table.insert(iniData[section], {type = "blank"})
            end
        end
    end

	-- Function to check if an item exists in the settings table
	local function itemExists(section, key, value)
		for _, item in ipairs(settings) do
			if item.type == "section" and item.name == section then
				return true
			elseif item.type == "key" and item.section == section and item.key == key then
				return true
			elseif item.type == "comment" and value and value.type == "comment" and item.text == value.text and (item.section == section or item.section == nil) then
				return true
			elseif item.type == "blank" and value and value.type == "blank" and (item.section == section or item.section == nil) then
				return true
			end
		end
		return false
	end


	-- Add any missing entries from iniData to settings
	for section, keys in pairs(iniData) do
		-- Add section header if it doesn't exist
		if section ~= "_global_" and not itemExists(section, nil, nil) then
			table.insert(settings, {type = "section", name = section})
		end

		for key, value in pairs(keys) do
			if type(value) == "table" then
				if value.type == "comment" then
					if not itemExists(section, nil, value) then
						Debug("Adding missing comment from iniData: " .. value.text)
						table.insert(settings, {type = "comment", text = value.text, section = section})
					end
				elseif value.type == "blank" then
					if not itemExists(section, nil, value) then
						Debug("Adding missing blank line from iniData")
						table.insert(settings, {type = "blank", section = section})
					end
				end
			else
				if not itemExists(section, key, value) then
					Debug("Adding missing key from iniData: Section=" .. section .. ", Key=" .. key .. ", Value=" .. value)
					-- Find the correct spot to insert the new key
					local inserted = false
					for i, item in ipairs(settings) do
						if item.type == "key" and item.section == section and item.key == key then
							table.insert(settings, i + 1, {type = "key", section = section, key = key, value = value})
							inserted = true
							break
						end
					end
					if not inserted then
						-- Find the correct spot to insert the new key within the section
						for i, item in ipairs(settings) do
							if item.type == "section" and item.name == section then
								table.insert(settings, i + 1, {type = "key", section = section, key = key, value = value})
								break
							end
						end
					end
				end
			end
		end
	end


    -- Write the updated INI data back to the file
    writeIni(filename, settings)
end

-- Function to update a key=value pair
function updateKeyValue(section, key, value)
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    local scriptDir = getScriptDir()
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: ", filename)  -- Debug print to check the file path
    local file = io.open(filename, "r")
    local lines = {}

    if file then
        for line in file:lines() do
            if line:match("^" .. key .. "=") then
                line = key .. "=" .. value
            end
            table.insert(lines, line)
        end
        file:close()
    end

    file = io.open(filename, "w")
    if not file then
        Debug("Error: Unable to open file for writing: ", filename)
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

    local scriptDir = getScriptDir()
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: ", filename)  -- Debug print to check the file path
    local file = io.open(filename, "r")
    local lines = {}

    if file then
        for line in file:lines() do
            if not line:match("^" .. key .. "=") then
                table.insert(lines, line)
            end
        end
        file:close()
    end

    file = io.open(filename, "w")
    if not file then
        Debug("Error: Unable to open file for writing: ", filename)
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

    local scriptDir = getScriptDir()
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

    if file then
        for line in file:lines() do
            if line:match("^%[" .. section .. "%]$") then
                sectionFound = true
            elseif sectionFound and line:match("^%[") then
                sectionFound = false
            end

            if sectionFound then
                if line:match("^" .. keyBefore .. "=") then
                    table.insert(lines, line)
                    table.insert(lines, newKey .. "=" .. newValue)
                    keyInserted = true
                elseif keyInserted and line:match("^" .. keyAfter .. "=") then
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
    end

    file = io.open(filename, "w")
    if not file then
        Debug("Error: Unable to open file for writing: ", filename)
        return
    end
    for _, line in ipairs(lines) do
        file:write(line .. "\n")
    end
    file:close()
end

-- Function to read an INI file and add its contents to the settings table
function UpdatedSettings()
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    local scriptDir = getScriptDir()
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    -- Modify the script directory to point to the desired INI directory
    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    Debug("INI directory: " .. iniDir)

    -- Create the directory if it doesn't exist
    os.execute("mkdir \"" .. iniDir .. "\"")

    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: " .. filename)
    local file = io.open(filename, "r")
    if not file then
        Debug("Error: Unable to open file " .. filename)
        return
    end

    local settings = {}
    local currentSection = nil

    for line in file:lines() do
        -- Debug line to show the current line being processed
        Debug("Processing line: " .. line)

        -- Check for comments
        if line:match("^%s*;") then
            table.insert(settings, {type = "comment", text = line})
            Debug("Added comment: " .. line)
        -- Check for blank lines
        elseif line:match("^%s*$") then
            table.insert(settings, {type = "blank"})
            Debug("Added blank line")
        -- Check for section headers
        elseif line:match("^%s*%[.-%]%s*$") then
            local sectionName = line:match("^%s*%[(.-)%]%s*$")
            table.insert(settings, {type = "section", name = sectionName})
            currentSection = sectionName
            Debug("Added section: " .. sectionName)
        -- Check for key-value pairs
        elseif line:match("^%s*[^=]+=%s*.+%s*$") then
            local key, value = line:match("^%s*([^=]+)%s*=%s*(.+)%s*$")
            table.insert(settings, {type = "key", section = currentSection, key = key, value = value})
            Debug("Added key-value pair: " .. key .. " = " .. value)
        end
    end

    file:close()

    -- Debug line to show the final settings table
    for _, setting in ipairs(settings) do
        if setting.type == "comment" then
            Debug("Comment: " .. setting.text)
        elseif setting.type == "blank" then
            Debug("Blank line")
        elseif setting.type == "section" then
            Debug("Section: " .. setting.name)
        elseif setting.type == "key" then
            Debug("Key: " .. setting.key .. " = " .. setting.value .. " (Section: " .. setting.section .. ")")
        end
    end

    return settings
end

-- Function to read all INI keys and set them as global variables
function readIniKeys()
    local className = mq.TLO.Me.Class.Name()
    local cleanName = mq.TLO.Me.CleanName()

    if not className or not cleanName then
        Debug("Error: ClassName or CleanName is nil")
        return
    end

    local scriptDir = getScriptDir()
    if not scriptDir then
        Debug("Error: Unable to determine script directory")
        return
    end

    local iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\")
    local filename = iniDir .. string.format("Bot_%s_%s.ini", className, cleanName)
    Debug("INI file path: ", filename)  -- Debug print to check the file path
    local file = io.open(filename, "r")
    local iniData = {}

    if file then
        iniData = parseIni(file:read("*all"))
        file:close()
    end

    for section, keys in pairs(iniData) do
        for key, value in pairs(keys) do
            _G[key] = value
        end
    end
end

-- Build INI Order and Data
settings = {
    {type = "comment", text = "This is a comment above the General section"},
    {type = "section", name = "General"},
    {type = "key", section = "General", key = "Key1", value = "Value1"},
    {type = "comment", text = "This is a comment above Key2"},
    {type = "key", section = "General", key = "Key2", value = "Value2"},
    {type = "blank"},
    {type = "section", name = "Section2"},
    {type = "key", section = "Section2", key = "KeyA", value = "ValueA"},
    {type = "key", section = "Section2", key = "KeyB", value = "ValueB"}
}

--settings = UpdatedSettings()
saveSettings(settings)
--updateKeyValue("General", "Key1", "NewValue1")
--InsertKeyValue("Section2", "KeyA", "KeyB", "NewKey", "NewValue")
--deleteKeyValue("General", "Key2")
--readIniKeys()