-- Provides access to MacroQuest2 functions and commands 
mq = require('mq');
imgui = require('ImGui');
sql = require('Modules.lsqlite3')

Debug("GUI Script");

local className = mq.TLO.Me.Class.Name()
local cleanName = mq.TLO.Me.CleanName()
local filename = string.format("Bot_%s_%s.ini", className, cleanName)

-- Path to the INI file
--local ini_file_path = mq.configDir .. '\\BOT_INIS\\settings.ini'
local ini_file_path = mq.luaDir .. '\\Zenith\\BOT_INIS\\' .. filename
gui_settings = {Color = "White", Size = 1.5, ShowHP = true, ShowMana = true, ShowTarget = true}

-- Function to load settings from the INI file
function load_settings()
	print("Loading Settings: " .. ini_file_path)
    if not mq.TLO.Ini(ini_file_path) then
        print("INI file not found:", ini_file_path)
        return
    end
    --gui_settings.Color = mq.TLO.Ini(ini_file_path, "GUI", "Color", "White")()
    --gui_settings.Size = tonumber(mq.TLO.Ini(ini_file_path, "GUI", "Size", "1.0")())
end

-- Function to save settings back to the INI file
function save_settings()
	print(gui_settings.Color)
print(gui_settings.Size)
    --mq.cmdf('/ini "%s" "%s" "%s" "%s"', ini_file_path, "GUI", "Color", gui_settings.Color)
    --mq.cmdf('/ini "%s" "%s" "%s" "%.2f"', ini_file_path, "GUI", "Size", gui_settings.Size)
    print("Settings saved to INI file.")
end

-- Load the settings when the script starts
load_settings()

-- Global variable to control the visibility of the GUI window
local show_gui = true

local function onNameClick(botName)
-- Construct the command string
local command = string.format('/Target id ${Spawn[%s].ID}', botName)

-- Execute the command
mq.cmd(command)
end

-- Function to handle the GUI rendering
local function render_gui()

    if show_gui then
        -- Begin a new ImGui window
        imgui.Begin("Zenith 7 Settings")

        -- Begin the Tab Bar
        if imgui.BeginTabBar("SettingsTabs") then
			
            -- Tab 1: Bot Settings
            if imgui.BeginTabItem("Bot Info") then
        imgui.Text("Bot Information from MQ2NetBots")

        local botGroups = {
            "Mortefreddo|Scuranima|Mortescopocolpo|Morteastrale|Mortetorsioner|Mortalespirito",
            "Demonslayer|Morteguarisce|Morteleggenda|Mortemedita|Mortecantante|Mortestregona",
            "Morteacqua|Mortemietatori|Mortemonaco|Mortejujutsui|Morteacapella|Mortesenshi",
            "Morteshinwa|Mortespirito|Coopbestia|Mortescheletro|Morteshisai|Mortemezzoforte",
            "Mortepeyote|Morteassassino|Mortezapa|Mortearte|Mortecerchi|Voldemorta",
            "Mortesokudo|Mortemariolo|Mortefurioso|Mortejetchi|Spiritualmorte|Morteghiaccio",
            "Mortebojutsu|Mortekunoichi|Morteistintos|Morteisha|Mortesainnoto|Mortebukkyoto",
            "Mortekanfu|Mortekossori|Morteonokogeki|Mortekusuri|Mortetsuisuta|Mortemajutsushi",
            "Morteshadonaito|Mortebutai|Mortekamiubel|Morteseishin|Mortetakokan|Morteshokasen"
        }
		
		local botoffline = "show"

        local colors = {
            cYellow = ImVec4(255 / 255, 255 / 255, 53 / 255, 255 / 255),
            cRed = ImVec4(255 / 255, 0 / 255, 0 / 255, 255 / 255),
            cGreen = ImVec4(0 / 255, 255 / 255, 0 / 255, 255 / 255),
            cTeal = ImVec4(0 / 255, 255 / 255, 255 / 255, 255 / 255),
            cWhite = ImVec4(255 / 255, 255 / 255, 255 / 255, 255 / 255)
        }
		
        if imgui.BeginTable("Bot Information HUD", 12, ImGui.TableFlags_Borders) then
			imgui.TableSetupColumn("Cursed", ImGuiTableColumnFlags.WidthStretch, 15)
			imgui.TableSetupColumn("Distance", ImGuiTableColumnFlags.WidthStretch, 15)
			imgui.TableSetupColumn("State", ImGuiTableColumnFlags.WidthStretch, 25)
			imgui.TableSetupColumn("Combat", ImGuiTableColumnFlags.WidthStretch, 15)
			imgui.TableSetupColumn("#", ImGuiTableColumnFlags.WidthStretch, 10)
			imgui.TableSetupColumn("Name", ImGuiTableColumnFlags.WidthStretch, 35)
			imgui.TableSetupColumn("HP %", ImGuiTableColumnFlags.WidthStretch, 20)
			imgui.TableSetupColumn("MP/End %", ImGuiTableColumnFlags.WidthStretch, 20)
			imgui.TableSetupColumn("Target", ImGuiTableColumnFlags.WidthStretch, 50)
			imgui.TableSetupColumn("Target Dist", ImGuiTableColumnFlags.WidthStretch, 20)
			imgui.TableSetupColumn("Casting", ImGuiTableColumnFlags.WidthStretch, 50)
			imgui.TableSetupColumn("Buffs", ImGuiTableColumnFlags.WidthStretch, 10)
            imgui.TableHeadersRow()

            local botNumber = 1
            for groupIndex, group in ipairs(botGroups) do
                local bots = {}
                for bot in string.gmatch(group, '([^|]+)') do
                    table.insert(bots, bot)
                end

                for botIndex, botName in ipairs(bots) do
                    local bot_Curses, bot_Distance, bot_Lev, bot_State, bot_CombatState, bot_hp, bot_mana, bot_endurance, bot_target, bot_targetdist, bot_Casting, bot_buffs
                    local botColor = colors.cTeal
					
					if mq.TLO.NetBots(botName).Updated() == nil and botoffline ~= "show" then
						goto continue
					end
					ImGui.SetWindowFontScale(.9)
					
					-- Set frame padding
					imgui.PushStyleVar(ImGuiStyleVar.FramePadding, ImVec2(.1, .1))
					
					-- Set cell padding
					imgui.PushStyleVar(ImGuiStyleVar.CellPadding, ImVec2(.1, .1))
					
					-- Set the size of the next window
					--if botNumber >= 6 then
					--	imgui.SetWindowSize(ImVec2(1000, 170))
					--elseif botNumber >= 12 then
					--	imgui.SetWindowSize(ImVec2(1000, 272))
					--elseif botNumber >= 18 then
					--	imgui.SetWindowSize(ImVec2(1000, 374))
					--elseif botNumber >= 24 then
					--	imgui.SetWindowSize(ImVec2(1000, 476))
					--elseif botNumber >= 30 then
					--	imgui.SetWindowSize(ImVec2(1000, 578))
					--elseif botNumber >= 36 then
					--	imgui.SetWindowSize(ImVec2(1000, 680))
					--elseif botNumber >= 42 then
					--	imgui.SetWindowSize(ImVec2(1000, 782))
					--elseif botNumber >= 48 then
					--	imgui.SetWindowSize(ImVec2(1000, 884))
					--elseif botNumber >= 54 then
					--	imgui.SetWindowSize(ImVec2(1000, 920))
					--end
					
                    if Select(botName, mq.TLO.NetBots.Client(), "bool") and mq.TLO.NetBots(botName).InZone() then
                        bot_Curses = mq.TLO.NetBots(botName).Counters or ""
                        bot_Distance = math.Distance(mq.TLO.Me.Y(), mq.TLO.Me.X(), mq.TLO.Me.Z(), mq.TLO.NetBots(botName).Y(), mq.TLO.NetBots(botName).X(), mq.TLO.NetBots(botName).Z()) or ""
						bot_Lev = mq.TLO.NetBots(botName).Levitating()
						bot_State = mq.TLO.NetBots(botName).State() or ""
						bot_Grouped = mq.TLO.NetBots(botName).Grouped()
						bot_CombatState = mq.TLO.NetBots(botName).Attacking()
                        bot_hp = mq.TLO.NetBots(botName).PctHPs() .. "%" or ""
                        bot_mana = mq.TLO.NetBots(botName).PctMana() .. "%" or ""
                        bot_endurance = mq.TLO.NetBots(botName).PctEndurance() .. "%" or ""
                        bot_target = mq.TLO.Spawn(mq.TLO.NetBots(botName).TargetID()).CleanName() or ""
                        bot_targetdist = math.Distance(mq.TLO.NetBots(botName).Y(), mq.TLO.NetBots(botName).X(), mq.TLO.NetBots(botName).Z(),mq.TLO.Spawn(mq.TLO.NetBots(botName).TargetID()).Y(), mq.TLO.Spawn(mq.TLO.NetBots(botName).TargetID()).X(), mq.TLO.Spawn(mq.TLO.NetBots(botName).TargetID()).Z()) or ""
                        bot_Casting = mq.TLO.Spell(mq.TLO.NetBots(botName).Casting()).Name() or ""
                        bot_buffs = math.floor(20 - mq.TLO.NetBots(botName).FreeBuffSlots()) or ""
                    elseif not Select(botName, mq.TLO.NetBots.Client(), "bool") then
						botName = "Not Loaded"
						botColor = colors.cRed
                        bot_Curses, bot_Distance, bot_Lev, bot_State, bot_CombatState, bot_hp, bot_mana, bot_endurance, bot_target, bot_targetdist, bot_Casting, bot_buffs = "", "", "", "", "", "", "", "", "", "", "", ""
                    elseif Select(botName, mq.TLO.NetBots.Client(), "bool") and not mq.TLO.NetBots(botName).InZone() then
						botName = "Not In Zone!"
						botColor = colors.cYellow
                        bot_Curses, bot_Distance, bot_Lev, bot_State, bot_CombatState, bot_hp, bot_mana, bot_endurance, bot_target, bot_targetdist, bot_Casting, bot_buffs = "", "", "", "", "", "", "", "", "", "", "", ""
					end
					
                    imgui.TableNextRow()
					
					--Cursed Column
                    if bot_Curses ~= "" then
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
						imgui.Text(string.format("%s", bot_Curses))
						imgui.PopStyleColor()
					else
						imgui.TableNextColumn()
						imgui.Text("")
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--Distance Column
					if bot_Distance ~= "" then
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
						imgui.Text(string.format("%.2f", bot_Distance))
						imgui.PopStyleColor()
					else
						imgui.TableNextColumn()
						imgui.Text("")
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--State Column
					if bot_State ~= "" then
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cTeal)
						if bot_Lev then 
							imgui.Text(string.format("%s", bot_State .. "/" .. "LEV"))
						elseif not bot_Lev then
							imgui.Text(string.format("%s", bot_State))
						end
						imgui.PopStyleColor()
					else
						imgui.TableNextColumn()
						imgui.Text("")
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--CombatState Column
					if bot_CombatState ~= "" then
						if bot_CombatState then
							imgui.TableNextColumn()
							imgui.PushStyleColor(ImGuiCol.Text, colors.cRed)
							imgui.Text(string.format("%s",  tostring(bot_CombatState):upper()))					
							imgui.PopStyleColor()
						elseif not bot_CombatState then
							imgui.TableNextColumn()
							imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
							imgui.Text(string.format("%s",  tostring(bot_CombatState):upper()))					
							imgui.PopStyleColor()
						end
					else
						imgui.TableNextColumn()
						imgui.Text("")
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--botNumber Column
					if botNumber ~= "" then
						
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cWhite)
						imgui.Text(string.format("%s", botNumber))
						imgui.PopStyleColor()
					else
						imgui.TableNextColumn()
						imgui.Text("")
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--botName Column
					if botName ~= "Not Loaded" and botName ~= "Not In Zone!" then
						if not mq.TLO.NetBots(botName).Invis() then
							imgui.TableNextColumn()
							imgui.PushStyleColor(ImGuiCol.Text, botColor)
							if bot_Grouped then
								if imgui.Selectable(string.format("#-%s", botName), false, imgui.SelectableFlags_SpanAllColumns) then
									onNameClick(botName)
								end
							elseif not bot_Grouped then
								if imgui.Selectable(string.format("%s", botName), false, imgui.SelectableFlags_SpanAllColumns) then
									onNameClick(botName)
								end
							end
							imgui.PopStyleColor()
						elseif mq.TLO.NetBots(botName).Invis() then
							imgui.TableNextColumn()
							botColor = colors.cWhite
							if bot_Grouped then
								if imgui.Selectable(string.format("#%s", botName), false, imgui.SelectableFlags_SpanAllColumns) then
									onNameClick(botName)
								end
							elseif not bot_Grouped then
								if imgui.Selectable(string.format("%s", botName), false, imgui.SelectableFlags_SpanAllColumns) then
									onNameClick(botName)
								end
							end
							imgui.Text(string.format("(%s)", botName))
							imgui.PopStyleColor()
						end
					else
					
						if botoffline == "show" then
							imgui.TableNextColumn()
							imgui.PushStyleColor(ImGuiCol.Text, botColor)
							imgui.Text(string.format("%s", botName))
							imgui.PopStyleColor()
						end
					
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
                    --bot_HP Column
					if bot_hp ~= "" then

						if tonumber(bot_hp:sub(1, -2)) >= 50 then
							--Green Text
							imgui.TableNextColumn()
							imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
							imgui.Text(string.format("%s", bot_hp))
							imgui.PopStyleColor()
						elseif tonumber(bot_hp:sub(1, -2)) < 50 and tonumber(bot_hp:sub(1, -2)) > 25 then
							--Yellow Text
							imgui.TableNextColumn()
							imgui.PushStyleColor(ImGuiCol.Text, colors.cYellow)
							imgui.Text(string.format("%s", bot_hp))
							imgui.PopStyleColor()
						elseif tonumber(bot_hp:sub(1, -2)) <= 25 then
							--Red Text
							imgui.TableNextColumn()
							imgui.PushStyleColor(ImGuiCol.Text, colors.cRed)
							imgui.Text(string.format("%s", bot_hp))
							imgui.PopStyleColor()
						end
					else
						
						imgui.TableNextColumn()
						imgui.Text("")
					
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
            		--bot_Mana Column			
					if bot_mana ~= "" then
						if mq.TLO.NetBots(botName).MaxMana() ~= 0 and mq.TLO.NetBots(botName).Class.CanCast() then
						
							if tonumber(bot_mana:sub(1, -2)) >= 50 then
								--Green Text
								imgui.TableNextColumn()
								imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
								imgui.Text(string.format("%s", bot_mana))
								imgui.PopStyleColor()
							elseif tonumber(bot_mana:sub(1, -2)) < 50 and tonumber(bot_mana:sub(1, -2)) > 25 then
								--Yellow Text
								imgui.TableNextColumn()
								imgui.PushStyleColor(ImGuiCol.Text, colors.cYellow)
								imgui.Text(string.format("%s", bot_mana))
								imgui.PopStyleColor()
							elseif tonumber(bot_mana:sub(1, -2)) <= 25 then
								--Red Text
								imgui.TableNextColumn()
								imgui.PushStyleColor(ImGuiCol.Text, colors.cRed)
								imgui.Text(string.format("%s", bot_mana))
								imgui.PopStyleColor()
							end
						
						elseif mq.TLO.NetBots(botName).MaxMana() == 0 and not mq.TLO.NetBots(botName).Class.CanCast() then
							if tonumber(bot_endurance:sub(1, -2)) >= 50 then
								--Green Text
								imgui.TableNextColumn()
								imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
								imgui.Text(string.format("%s", bot_endurance))
								imgui.PopStyleColor()
							elseif tonumber(bot_endurance:sub(1, -2)) < 50 and tonumber(bot_endurance:sub(1, -2)) > 25 then
								--Yellow Text
								imgui.TableNextColumn()
								imgui.PushStyleColor(ImGuiCol.Text, colors.cYellow)
								imgui.Text(string.format("%s", bot_endurance))
								imgui.PopStyleColor()
							elseif tonumber(bot_endurance:sub(1, -2)) <= 25 then
								--Red Text
								imgui.TableNextColumn()
								imgui.PushStyleColor(ImGuiCol.Text, colors.cRed)
								imgui.Text(string.format("%s", bot_endurance))
								imgui.PopStyleColor()
							end
							
						end
						
					else
					
						imgui.TableNextColumn()
						imgui.Text("")
						
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--bot_TargetColumn
					if bot_target ~= "" then
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
						imgui.Text(string.format("%s", bot_target))
						imgui.PopStyleColor()
					else
						imgui.TableNextColumn()
						imgui.Text("")
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--bot_TargetDist Column
					if bot_targetdist ~= "" then	
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cGreen)
						imgui.Text(string.format("%.2f", bot_targetdist))
						imgui.PopStyleColor()
					else
						imgui.TableNextColumn()
						imgui.Text("")
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--bot_Casting Column
					if bot_Casting ~= "" then
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cYellow)
						imgui.Text(string.format("%s", bot_Casting))
						imgui.PopStyleColor()
					else
						
						imgui.TableNextColumn()
						imgui.Text("")
					
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
					--bot_Buffs
					if botName ~= "Not Loaded" and botName ~= "Not In Zone!" and bot_buffs ~= "" then
						imgui.TableNextColumn()
						imgui.PushStyleColor(ImGuiCol.Text, colors.cTeal)
						imgui.Text(string.format("%s", bot_buffs))
						imgui.PopStyleColor()
					else
						
						imgui.TableNextColumn()
						imgui.Text("")
					
					end
					if botNumber % 6 == 0 then ImGui.Separator() ImGui.Separator() end
					
                    botNumber = botNumber + 1
					
					::continue::
                end
            end

            imgui.EndTable()
        end

        imgui.EndTabItem()
    end

    imgui.EndTabBar()

        end

        -- Add a Save button to save the changes to the INI file
        if imgui.Button("Save") then
            save_settings()
        end

        -- End the ImGui window
        imgui.End()
    end
end


-- Function to toggle the visibility of the GUI
local function toggle_gui()
    show_gui = not show_gui
end

-- Bind a command to toggle the GUI
mq.bind('/togglegui', toggle_gui)

-- Main loop to keep the script running and render the GUI
mq.imgui.init("MQ2IniSettingsGUI", render_gui)
