-- Provides access to MacroQuest2 functions and commands
mq = require('mq');
ImGui = require('ImGui');

inifile = require("Modules.Core_Functions");	-- This module handles INI file operations.
inifile = require("Modules.inifile");	-- This module handles INI file operations.

local Me = mq.TLO.Me

-- Create a new INI file with comments and blank lines
config = {
    ["General"] = {
        Debugs = "Init|Events|Commands|Utility_Functions|inifile|Core_Functions"
    },
    ["Header1"] = {
        key1 = "value1",
        key2 = "value2"
    },
    ["Header2"] = {
        key3 = "value3",
        key4 = "value4"
    }
}

comments = {
    ["General"] = { "This is a comment for General section" },
    ["Header1"] = { "This is a comment for Header1" },
    ["Header2"] = { "This is a comment for Header2" },
    ["key1"] = { "Comment for key1" },
    ["key3"] = { "Comment for key3" }
}

sectionorder = { "General", "Header1", "Header2" }

metadata = { __inifile = { comments = comments, sectionorder = sectionorder } }
setmetatable(config, metadata)

local className = mq.TLO.Me.Class.Name();
local cleanName = mq.TLO.Me.CleanName();
scriptDir = getScriptDir("inifile.lua");
iniDir = scriptDir:gsub("Modules\\", "BOT_INIS\\");
filename = string.format("Bot_%s_%s.ini", className, cleanName);

-- Don't Create INI if it exist already else Create INI file.
if not fileExists(iniDir .. filename) then
	local inisave = inifile.save(iniDir .. filename, config)
	-- Load all INI Keys to Global Variables.
	readIniKeys("Modules\\", "BOT_INIS\\")
else
	-- Load all INI Keys to Global Variables.
	readIniKeys("Modules\\", "BOT_INIS\\")
end


-- Require necessary modules [Lua #include Global]
local moduleNames = {
	"Core_Functions",  		-- This module contains core functions.
    "INIFile",          	-- this is create INI files Module.
    "Events",          		-- This is for all BOT Handled Events.
    "Commands",        		-- This is for BOT Control Commands.
    "Utility_Functions",	-- This module contains utility functions.
    "GUI"					-- This is Zenith GUI in game for settings/Information.
   --"BushBot"			    -- This is Bushman Mod.
}

function CheckModules(modules)
	for _, moduleName in ipairs(modules) do
		print("Checking Module: " .. moduleName)
		local status, result = pcall(require, "Modules." .. moduleName)
		if status then
			_G[moduleName] = result
			print("Successfully loaded module: " .. moduleName)
			
			-- Access the loaded modules using their global variable names
			_G[moduleName:gsub("_Functions", "")] = result
		else
			print("Failed to load module: " .. moduleName)
			print("Error: " .. result)
			-- Additional logging for debugging
            if result:find("module 'Modules." .. moduleName .. "' not found") then
                print("Module not found: " .. moduleName)
            else
                print("Error details: " .. result)
            end
		end
	end
end
-- load all the rest of required modules.
CheckModules(moduleNames);

Debug("Init Script");

--:MainLoop
function MainLoop()
   
   while not terminate
	do
		background_ChatMonitor();
		--mq.delay(1000); -- Delay for 1000 milliseconds (1 second)
	end

end

function background_ChatMonitor()

	mq.doevents(Event_SelfEcho);
	mq.doevents(Event_AltTell);
	mq.doevents(Event_EQBCSAY);
	mq.doevents(Event_GGRSay);
	mq.doevents(Event_OOCSay);
	mq.doevents(Event_ShoutSay);
	mq.doevents(Event_ChannelSay);

end


-- Example default configuration
local default_config = {
    ["General"] = {
        Debugs = "Init|Events|Commands|Utility_Functions|inifile|Core_Functions"
    },
    ["Header1"] = {
        key1 = "value1",
        key2 = "value2"
    },
    ["Header2"] = {
        key3 = "value3",
        key4 = "value4"
    },
    __inifile = {
        comments = {
            ["General"] = { "This is a comment for General section" },
            ["Header1"] = { "This is a comment for Header1" },
            ["Header2"] = { "This is a comment for Header2" },
            ["key1"] = { "Comment for key1" },
            ["key3"] = { "Comment for key3" }
        },
        sectionorder = { "General", "Header1", "Header2" },
        keyorder = {
            ["General"] = { "Debugs" },
            ["Header1"] = { "key2", "key1" },
            ["Header2"] = { "key3", "key4" }
        }
    }
}

local Function MemorizeSpells()
	-- Function to check if a spell is memorized in a specific gem slot
	local function isSpellMemorizedInSlot(spell, slot)
		--printf("Checking %s = %s",mq.TLO.Me.Gem(slot).Name(), spell)
		--print(mq.TLO.Me.Gem(slot).Name() == spell)
		mq.delay(100)
		return mq.TLO.Me.Gem(slot).Name() == spell
	end

	-- Function to memorize a spell in a specific gem slot if not already memorized
	local function memorizeSpellInSlotIfNeeded(spell, slot)
		if slot <= 8 and not isSpellMemorizedInSlot(spell, slot) then
			mq.cmdf('/memorize "%s" %d', spell, slot)
			--print("Memorizing " .. spell .. " in gem slot " .. slot)
			-- Wait until the spell is fully memorized.
			while not isSpellMemorizedInSlot(spell, slot) do
				mq.delay(100)  -- Wait for 100 milliseconds before checking again
			end
			if isSpellMemorizedInSlot(spell, slot) then
				--print(spell .. " is now memorized in gem slot " .. slot)
				return true
			end
		else
			if slot <= 8 then
				--print(spell .. " is already memorized in gem slot " .. slot)
				return true
			else
				--print(spell .. "Out of Gem Slots")
				return
			end
		end
	end

	-- List of Spells to Memorize.
	local spellNames = {
		"Anarchy",
		"Cloud",
		"Color Slant",
		"Choke",
		"Glamorous Visage",
		"Gravity Flux",
		"Mana Flare",
		"Mind Wipe"
	}

	-- Calculate the total number of elements in the table
	local totalElements = #spellNames

	-- Memorize each spell in the corresponding gem slot
	for slot, spellName in ipairs(spellNames) do
		--printf("Checking Spell: [%s] in slot: [%d]", spellName, slot)
		memorizeSpellInSlotIfNeeded(spellName, slot)
		
		if slot == totalElements then
			-- Print all spells now memorized.
			print("Spells now memorized.")
		end
	end
end

MemorizeSpells
-- Update the INI file with the default configuration
--update_ini(default_config)


--updateKeyValue("Header1", "Key1", "NewValue1")
--InsertKeyValue("Header2", "Key4", "Key3", "NewKey", "NewValues")
--deleteKeyValue("Header1", "Key2")

MainLoop()