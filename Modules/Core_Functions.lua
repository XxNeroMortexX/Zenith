-- Provides access to MacroQuest2 functions and commands
mq = require('mq');
ImGui = require('ImGui');

-- Function to check if a file name is in the Debug variable
function isDebugEnabled(fileName)
	-- Create a table to store the variables
	ini = {} 
	
	-- Generate parts of ini filename.
	local className = mq.TLO.Me.Class.Name();
	local cleanName = mq.TLO.Me.CleanName();
	
	-- Calculate iniDie & full filename.
	local str = debug.getinfo(1, "S").source:sub(2);
    local dir = str:gsub("Core_Functions.lua", "")
	local iniDir = dir:gsub("Modules\\", "BOT_INIS\\");
	local filename = string.format("Bot_%s_%s.ini", className, cleanName);
	
	-- Read debugs Specific Key only.
	local file = io.open(iniDir .. filename, "r")
	if not file then
		ini.debugs = "all"  -- Set ini.debugs if file does not exist
	else
		local content = file:read("*a")
		file:close()
		ini.debugs = content:match("%[General%].-[dD][eE][bB][uU][gG][sS]%s-=%s-(.-)\n")
	end
	
	if not ini.debugs then
		if ini_Core_Debug then
		
		else
		ini.debugs = ''
		end
	end
    if ini.debugs == "all" then
        return true
    end
    for file in ini.debugs:lower():gmatch("[^|]+") do

        if fileName:lower():find(file) then
            return true
        end
    end
    return false
end

-- This function takes a string as input and replaces custom color tags with the corresponding MQ2 color codes.
-- The custom tags are in the format [+color+], where "color" can be one of the predefined color codes.
-- The function returns the modified string with the appropriate color codes for MQ2.
-- Example usage:
-- local coloredText = replaceColorTags("This is [+r+]red[+reset+] and this is [+g+]green[+reset+].")
function replaceColorTags(text)
	-- [+y+] - Bright Yellow -- [+Y+] - Dark Yellow	    -- [+o+] - Bright Orange	-- [+O+] - Dark Orange
	-- [+g+] - Bright Green  -- [+G+] - Dark Green	    -- [+u+] - Bright Blue  	-- [+U+] - Dark Blue
	-- [+r+] - Bright Red    -- [+R+] - Dark Red 	    -- [+t+] - Bright Teal  	-- [+T+] - Dark Teal
	-- [+b+] - Black         -- [+m+] - Bright Magenta 	-- [+M+] - Dark Magenta	    -- [+p+] - Bright Purple
	-- [+P+] - Dark Purple	 -- [+w+] - Bright White	-- [+W+] - Grey 
	-- [+reset+] - Reset to default color

    text = text:gsub("%[%+y%+%]", "\ay");  -- Bright Yellow
    text = text:gsub("%[%+Y%+%]", "\a-y"); -- Dark Yellow
    text = text:gsub("%[%+o%+%]", "\ao");  -- Bright Orange
    text = text:gsub("%[%+O%+%]", "\a-o"); -- Dark Orange
    text = text:gsub("%[%+g%+%]", "\ag");  -- Bright Green
    text = text:gsub("%[%+G%+%]", "\a-g"); -- Dark Green
    text = text:gsub("%[%+u%+%]", "\au");  -- Bright Blue
    text = text:gsub("%[%+U%+%]", "\a-u"); -- Dark Blue
    text = text:gsub("%[%+r%+%]", "\ar");  -- Bright Red
    text = text:gsub("%[%+R%+%]", "\a-r"); -- Dark Red
    text = text:gsub("%[%+t%+%]", "\at");  -- Bright Teal
    text = text:gsub("%[%+T%+%]", "\a-t"); -- Dark Teal
    text = text:gsub("%[%+b%+%]", "\ab");  -- Black
    text = text:gsub("%[%+m%+%]", "\am");  -- Bright Magenta
    text = text:gsub("%[%+M%+%]", "\a-m"); -- Dark Magenta
    text = text:gsub("%[%+p%+%]", "\ap");  -- Bright Purple
    text = text:gsub("%[%+P%+%]", "\a-p"); -- Dark Purple
    text = text:gsub("%[%+w%+%]", "\aw");  -- Bright White
    text = text:gsub("%[%+W%+%]", "\a-w"); -- Grey
    text = text:gsub("%[%+reset%+%]", "\ax");  -- Reset to default color
    return text
end

-- This function prints the current file and line number along with any additional arguments passed to it.
-- It uses the Lua debug library to retrieve the file and line number information.
-- The function also supports custom color tags in the additional arguments, which are replaced by the replaceColorTags function.
-- Example usage:
-- Debug("Debug Message Here")
function Debug(...)
    local info = debug.getinfo(2, "Sl");
    local args = {...}
    local args_str = table.concat(args, " ");

    -- Extract the relevant part of the file path, starting from \lua
    local short_src = info.short_src:match("\\lua\\.*");
    if not short_src then
        short_src = info.short_src:match(".*\\([^\\]+\\[^\\]+)$");
    end
	
	if isDebugEnabled(short_src) then
		local output = "[+y+]" .. short_src .. "[+r+]:[+t+]" .. info.currentline .. "[+reset+]" .. " [+r+]" .. args_str
		print(replaceColorTags(output));
	end
 
end

Debug("Core Functions Script");

-- Checks if a file exists.
function fileExists(file)
    local f = io.open(file, "r")
    if f then
        f:close()
        return true
    else
        return false
    end
end

-- Returns the current working directory.
function getCurrentWorkingDirectory()
    local handle = io.popen("cd")
    local result = handle:read("*a")
    handle:close()
    return result:match("^%s*(.-)%s*$")
end

function tableToString(tbl)
	local result = {}
	for k, v in pairs(tbl) do
		table.insert(result, tostring(k) .. ": " .. tostring(v))
	end
	return "{" .. table.concat(result, ", ") .. "}"
end

function caseInsensitive(filename)
    local pattern = ""
    for i = 1, #filename do
        local char = filename:sub(i, i)
        if char:match("%a") then
            pattern = pattern .. "[" .. char:lower() .. char:upper() .. "]"
        else
            pattern = pattern .. "%" .. char
        end
    end
    return pattern
end

function math.Distance(y1, x1, z1, y2, x2, z2)
    if not y1 or not x1 or not z1 or not y2 or not x2 or not z2 then
        return ""
    end
	return math.floor(math.sqrt((x2 - x1) ^ 2 + (y2 - y1) ^ 2 + (z2 - z1) ^ 2))
end

-- Function to mimic ${Select[...]}
function Select(key, str, returnType)
    for word in string.gmatch(str, "%S+") do
        if word == key then
            if returnType == "bool" then
                return true
            elseif returnType == "string" then
                return word
            end
        end
    end
    if returnType == "bool" then
        return false
    else
        return nil
    end
end


function splitString(inputstr, sep)
    if sep == nil then
        sep = "%s"
    end
    local result = ""
    for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
        if result == "" then
            result = str
        else
            result = result .. sep .. str
        end
    end
    return result
end

function splitAndJoin(inputstr, sep)
    if sep == nil then
        sep = "%s"
    end
    local result = ""
    for str in string.gmatch(inputstr, "([^%s]+)") do
        if result == "" then
            result = str
        else
            result = result .. sep .. str
        end
    end
    return result
end
