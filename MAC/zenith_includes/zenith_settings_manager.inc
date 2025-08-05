|: ========================================
|: zenith_settings_manager.inc
|: Improved INI Settings Management for Zenith
|: ========================================

|: ========================================
|: Core Settings Management Functions
|: ========================================

Sub LoadSetting(string varName, string varType, string iniKey, string defaultValue)
    |: Load a setting from INI file with default value
    /declare ${varName} ${varType} outer ${Ini[${configFile},${SectionName},${iniKey},${defaultValue}]}
    |: If setting doesn't exist, create it with default
    /if (${Ini[${configFile},${SectionName},${iniKey}].Length} == 0) {
        /call WriteSetting ${iniKey} ${defaultValue}
    }
/return

Sub WriteSetting(string iniKey, string value)
    |: Write a setting to INI file
    /ini "${configFile}" "${SectionName}" "${iniKey}" "${value}"
/return

Sub GlobalLoadSetting(string sectionType, string separator, string sectionName, string lineNumber)
    |: Create section headers and comments in INI
    /if (${sectionType.Equal[INFO]}) {
        |: Add comment line
        /ini "${configFile}" "${sectionName}" "|: ${separator}" ""
    } else /if (${sectionType.Equal[|**HEADER**|]}) {
        |: Add section header
        /ini "${configFile}" "${sectionName}" "|: ========================================" ""
        /ini "${configFile}" "${sectionName}" "|: ${separator}" ""
        /ini "${configFile}" "${sectionName}" "|: ========================================" ""
    } else /if (${sectionType.Equal[|**LINE**|]}) {
        |: Add separator line
        /ini "${configFile}" "${sectionName}" "|: ${separator}" ""
    }
/return

|: ========================================
|: Bot-Specific Settings Management
|: ========================================

Sub InitializeBotSettings
    |: Initialize bot-specific configuration
    /declare configFile string outer Zenith_${Me.CleanName}.ini
    /declare SectionName string outer General
    
    |: Create basic sections
    /call CreateSection "General" "General Zenith Bot Settings"
    /call CreateSection "Combat" "Combat Settings"
    /call CreateSection "Movement" "Movement Settings"
    /call CreateSection "Spells" "Spell Settings"
    /call CreateSection "Follow" "Follow Settings"
    /call CreateSection "Debug" "Debug Settings"
    
    |: Load all settings
    /call LoadGeneralSettings
    /call LoadCombatSettings
    /call LoadMovementSettings
    /call LoadSpellSettings
    /call LoadFollowSettings
    /call LoadDebugSettings
/return

Sub CreateSection(string sectionName, string description)
    |: Create a new section in INI file
    /varset SectionName ${sectionName}
    /ini "${configFile}" "${sectionName}" "|: ========================================" ""
    /ini "${configFile}" "${sectionName}" "|: ${description}" ""
    /ini "${configFile}" "${sectionName}" "|: ========================================" ""
/return

|: ========================================
|: Settings Loading Functions
|: ========================================

Sub LoadGeneralSettings
    /varset SectionName General
    
    |: Core bot settings
    /call LoadSetting "isRunning" "bool" "AutoStart" "TRUE"
    /call LoadSetting "debugMode" "bool" "DebugMode" "FALSE"
    /call LoadSetting "chatOutput" "bool" "ChatOutput" "TRUE"
    /call LoadSetting "autoConsent" "bool" "AutoConsent" "TRUE"
    
    |: Performance settings
    /call LoadSetting "loopDelay" "int" "LoopDelay" "1"
    /call LoadSetting "maxLoopTime" "int" "MaxLoopTime" "1000"
/return

Sub LoadCombatSettings
    /varset SectionName Combat
    
    |: Combat ranges
    /call LoadSetting "meleeRange" "int" "MeleeRange" "15"
    /call LoadSetting "spellRange" "int" "SpellRange" "100"
    /call LoadSetting "assistRange" "int" "AssistRange" "200"
    
    |: Combat toggles
    /call LoadSetting "autoCombat" "bool" "AutoCombat" "TRUE"
    /call LoadSetting "autoAssist" "bool" "AutoAssist" "TRUE"
    /call LoadSetting "autoAttack" "bool" "AutoAttack" "TRUE"
/return

Sub LoadMovementSettings
    /varset SectionName Movement
    
    |: Movement settings
    /call LoadSetting "followDistance" "int" "FollowDistance" "20"
    /call LoadSetting "campRadius" "int" "CampRadius" "50"
    /call LoadSetting "leashRadius" "int" "LeashRadius" "100"
    
    |: Movement toggles
    /call LoadSetting "autoFollow" "bool" "AutoFollow" "TRUE"
    /call LoadSetting "returnToCamp" "bool" "ReturnToCamp" "TRUE"
/return

Sub LoadSpellSettings
    /varset SectionName Spells
    
    |: Spell thresholds
    /call LoadSetting "healThreshold" "int" "HealThreshold" "70"
    /call LoadSetting "buffThreshold" "int" "BuffThreshold" "90"
    /call LoadSetting "nukeThreshold" "int" "NukeThreshold" "50"
    
    |: Spell toggles
    /call LoadSetting "autoHeal" "bool" "AutoHeal" "TRUE"
    /call LoadSetting "autoBuff" "bool" "AutoBuff" "TRUE"
    /call LoadSetting "autoNuke" "bool" "AutoNuke" "TRUE"
/return

Sub LoadFollowSettings
    /varset SectionName Follow
    
    |: Follow settings
    /call LoadSetting "followTarget" "string" "FollowTarget" ""
    /call LoadSetting "isFollowing" "bool" "IsFollowing" "FALSE"
    /call LoadSetting "followDistance" "int" "FollowDistance" "20"
    
    |: Follow commands
    /call LoadSetting "followCommand" "string" "FollowCommand" "follow"
    /call LoadSetting "stopFollowCommand" "string" "StopFollowCommand" "stop follow"
/return

Sub LoadDebugSettings
    /varset SectionName Debug
    
    |: Debug settings
    /call LoadSetting "eventDebug" "bool" "EventDebug" "FALSE"
    /call LoadSetting "performanceDebug" "bool" "PerformanceDebug" "FALSE"
    /call LoadSetting "combatDebug" "bool" "CombatDebug" "FALSE"
    
    |: Logging settings
    /call LoadSetting "logToFile" "bool" "LogToFile" "FALSE"
    /call LoadSetting "logLevel" "int" "LogLevel" "1"
/return

|: ========================================
|: Settings Update Functions
|: ========================================

Sub UpdateSetting(string section, string key, string value)
    |: Update a setting and save to INI
    /varset SectionName ${section}
    /call WriteSetting ${key} ${value}
    
    |: Update the corresponding variable
    /if (${section.Equal[General]}) {
        /if (${key.Equal[AutoStart]}) /varset isRunning ${value}
        /if (${key.Equal[DebugMode]}) /varset debugMode ${value}
    } else /if (${section.Equal[Combat]}) {
        /if (${key.Equal[AutoCombat]}) /varset autoCombat ${value}
        /if (${key.Equal[MeleeRange]}) /varset meleeRange ${value}
    } else /if (${section.Equal[Follow]}) {
        /if (${key.Equal[FollowTarget]}) /varset followTarget ${value}
        /if (${key.Equal[IsFollowing]}) /varset isFollowing ${value}
    }
/return

|: ========================================
|: Settings Validation
|: ========================================

Sub ValidateSettings
    |: Validate all settings are within acceptable ranges
    /if (${meleeRange} < 1 || ${meleeRange} > 50) {
        /echo Warning: MeleeRange ${meleeRange} is outside normal range (1-50)
        /varset meleeRange 15
    }
    
    /if (${followDistance} < 5 || ${followDistance} > 100) {
        /echo Warning: FollowDistance ${followDistance} is outside normal range (5-100)
        /varset followDistance 20
    }
    
    /if (${healThreshold} < 1 || ${healThreshold} > 100) {
        /echo Warning: HealThreshold ${healThreshold} is outside normal range (1-100)
        /varset healThreshold 70
    }
/return

|: ========================================
|: Settings Backup and Restore
|: ========================================

Sub BackupSettings
    |: Create backup of current settings
    /declare backupFile string local Zenith_${Me.CleanName}_backup_${Time.YYYYMMDD_HHMMSS}.ini
    /copy "${configFile}" "${backupFile}"
    /echo Settings backed up to: ${backupFile}
/return

Sub RestoreSettings(string backupFile)
    |: Restore settings from backup
    /if (${File[${backupFile}].Exists}) {
        /copy "${backupFile}" "${configFile}"
        /echo Settings restored from: ${backupFile}
        /call InitializeBotSettings
    } else {
        /echo Backup file not found: ${backupFile}
    }
/return

|: ========================================
|: Settings Export/Import
|: ========================================

Sub ExportSettings(string exportFile)
    |: Export settings to a different file
    /copy "${configFile}" "${exportFile}"
    /echo Settings exported to: ${exportFile}
/return

Sub ImportSettings(string importFile)
    |: Import settings from a file
    /if (${File[${importFile}].Exists}) {
        /copy "${importFile}" "${configFile}"
        /echo Settings imported from: ${importFile}
        /call InitializeBotSettings
    } else {
        /echo Import file not found: ${importFile}
    }
/return