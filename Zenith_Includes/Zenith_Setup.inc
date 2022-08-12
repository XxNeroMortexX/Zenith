Sub Main_Setup

	|: --------------------------------------------|
	|: - Check EQ [General Tab] Consent Setting. - |
	|: --------------------------------------------|
	|: Corpse Consentt Auto ON Always
	
	|: Make sure Auto Consent Group Enabled
	/if (!${Window[OptionsGeneralPage].Child[OGP_AutoConsentGroupCheckbox].Checked}) {
		/notify OptionsGeneralPage OGP_AutoConsentGroupCheckbox leftmouseup
	}
	
	|: Make sure Auto Consent Raid Enabled
	/if (!${Window[OptionsGeneralPage].Child[OGP_AutoConsentRaidCheckbox].Checked}) {
		/notify OptionsGeneralPage OGP_AutoConsentRaidCheckbox leftmouseup
	}
	
	|: Make sure Auto Consent Guild Enabled
	/if (!${Window[OptionsGeneralPage].Child[OGP_AutoConsentGuildCheckbox].Checked}) {
		/notify OptionsGeneralPage OGP_AutoConsentGuildCheckbox leftmouseup
	}
	
	/if (${Toggle-autoleaderaa}) {
		/if (!${Window[LeadershipWindow].Child[LEW_OnButton].Checked}) {
			/notify LeadershipWindow LEW_OnButton leftmouseup
			|: /notify LeadershipWindow LEW_OffButton leftmouseup
		}
	}
	
	|: Setup NinjaLooter
	/if (${Toggle-ninjaloot} && !${Bool[${Ini[${NINJALOOT_INI}].Length}]}) /call SetupAdvLootVars

/return

Sub Init_Setup_Ini

/return

|**
-------------------------------------------------------------------------
	 Create [CORE] Commands for BOT
-------------------------------------------------------------------------
|: /call AddCommand "Command one" "Command two" "Command Three"
**|
Sub Init_Core_Ini(int i)
	
	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: - To Notifiy User of [CORE] INI Entry Not used Anymore
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" DeleteMe DeleteMe MaxLootRadius "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" DeleteMe DeleteMe CorpseItemSave "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" DeleteMe DeleteMe FollowLeash "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"


	|:This sets BOT's [CORE] variable commands with Sub Command_NamesBelow:|
	/call AddCommands version help
	/call AddCommands sit stand stay stop jumpto mount
	/call AddCommands follow moveto assist
	/call AddCommands groupset groupup
	/call AddCommands disband accept reject
	/call AddCommands moveup zone doort doorf
	/call AddCommands reload recon
	
	|:/call AddCommands mainassist trade tradeitem pet
	|:/call AddCommands chatin cmds popupdate gl botsglow
	|:/call AddCommands exp aaexp stats equip unequip link find
	|:/call AddCommands followmode movetomode anchor guard 
	|:/call AddCommands summon lootall loot lootrezed consent corpsedrag rez  clickit 
	|:/call AddCommands getflag shortcuts
	|:/call AddCommands con mem twist feign uninvis square cross triangle line camp
	|:/call AddCommands alt aalist enchant random
	|:/call AddCommands swap magic fire cold poison disease
	|:/call AddCommands guildinvite
	|:/call AddCommands setmaster chant wait4rez scribe swarm hotzones mainsettings botsettings

	|: --------------------------------------------|
	|: -       Declare BOT [Core] Variables      - |
	|: --------------------------------------------|
	|: -- 
	
	|: Declare MQ2Hud Bot Status Tracker Window.
	/declare GlobalLoadSettingSetup string local HUDBotTrackerGrp1 HUDBotTrackerGrp2 HUDBotTrackerGrp3 HUDBotTrackerGrp4
	/declare GlobalToggleSetup string local hudgroup1 hudgroup2 hudgroup3 hudgroup4 spawnlist
	/if (!${Defined[x]}) /declare x int local 0

	/for x 1 to ${Math.Calc[${GlobalLoadSettingSetup.Count[ ]}+1]}
		/if (!${Defined[${GlobalLoadSettingSetup.Arg[${x}]}]}) /declare ${GlobalLoadSettingSetup.Arg[${x}]} string global
		/if (!${Defined[${GlobalLoadSettingSetup.Arg[${x}]}-DefaultValue]}) /declare ${GlobalLoadSettingSetup.Arg[${x}]}-DefaultValue string global
	/next x

	/for x 1 to ${Math.Calc[${GlobalToggleSetup.Count[ ]}+1]}
		/if (!${Defined[Toggle-${GlobalToggleSetup.Arg[${x}]}]}) /declare Toggle-${GlobalToggleSetup.Arg[${x}]} bool global
		/if (!${Defined[Toggle-${GlobalToggleSetup.Arg[${x}]}-OffText]}) /declare Toggle-${GlobalToggleSetup.Arg[${x}]}-OffText string global
		/if (!${Defined[Toggle-${GlobalToggleSetup.Arg[${x}]}-OnText]}) /declare Toggle-${GlobalToggleSetup.Arg[${x}]}-OnText string global
		/if (!${Defined[Toggle-${GlobalToggleSetup.Arg[${x}]}-ToggleType]}) /declare Toggle-${GlobalToggleSetup.Arg[${x}]}-ToggleType string global
		/if (!${Defined[Toggle-${GlobalToggleSetup.Arg[${x}]}-CallSub]}) /declare Toggle-${GlobalToggleSetup.Arg[${x}]}-CallSub string global
	/next x

	|: Set Main Target IDs Variables for BOT to use. 
	/if (!${Defined[CombatTargetID]}) /declare CombatTargetID int outer 0
	/if (!${Defined[FollowTargetID]}) /declare FollowTargetID int outer 0
	
	|: Set Main BOT Command Variables for BOT to use. 
	/if (!${Defined[CommandParam]}) /declare CommandParam string outer
	/if (!${Defined[CurrCommand]}) /declare CurrCommand string outer
	/if (!${Defined[CommandText]}) /declare CommandText string outer

	|: Set Main BOT Ninjaloot Variables for BOT to use.
	/declare CorpseList string outer

	|: Set Main BOT Wait4Rez Variables for BOT to use.
	/declare lootable string outer 0

	|: Set Anchor Variables for BOT to use.
	/declare IsHead float outer ${Me.Heading.DegreesCCW}
	/declare IsZone int outer ${Zone.ID}
	/declare Ypos string outer ${Me.Y}
	/declare Xpos string outer ${Me.X}
	/declare IsCamp int outer 0
	
	|: Current CombatTargetID DebuffList so no double Casting debuffs spells.
	/declare DebuffList string outer
	
	|: Set Outer Variable for Person asking for BOT to do Command. 
	/declare Sender string outer
	
	|: Set Self Command Text so BOT knows he is the only one to do the Command.
	/declare EchoText string outer

	|: Setup Integer/Alpabet Array for Looping.
	/declare Integer[10] int outer
	/declare Alphabet[26] string outer
	/declare FullAlpabet string local a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
	
	/if (!${Defined[x]}) /declare x int local
	/for x 1 to 26
		/varset Alphabet[${x}] ${FullAlpabet.Arg[${x},,]}
	/next x
	
	/if (!${Defined[x]}) /declare x int local
	/for x 1 to 10
		/varset Integer[${x}] ${Math.Calc[${x} -1].Int}
	/next x
	
	|: Bots Idle/Buff Idle Status Variables
	/if (!${Defined[idle]}) /declare idle bool outer TRUE
	/declare Buffidle bool outer TRUE
	/declare last_X int outer 0
	/declare last_Y int outer 0

	|: Declare Variables for Scribing (Buying/Meming) Spells
	/declare HasVoA int outer 1
	/declare InvScribeSlot int outer 1
	/declare MyDeity string outer ${Me.Deity}
	/declare MaxInvSlots int outer 10
	/declare MinLevel int outer 1
	/declare MaxLevel int outer ${Me.Level}
	/declare DoLoop int outer 0
	/declare mName string outer

	|: Declare Timers:|
	/declare DelayTimer timer outer 0
	/declare idleTimer timer outer 0
	/declare BuffidleTimer timer outer 0
	/declare Desync timer outer 0
	/if (!${Defined[DialogMsgTimer]}) /declare DialogMsgTimer timer outer 0

	|: Bard Current Twisting List. This is Used to Pause/Unpause Twist for Swarms
	/declare TwistList string outer

	|: CorpseDrag Command
	/declare numcorpses int outer 0
	/declare loopcorpse1 int outer 1
	/declare loopcorpse2 int outer 1
	/declare badcorpseid int outer 0
	
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**HEADER**|" "=" "[Options to Control Specific Bots]" "1" |: Ini Blank Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ClassTypes[Melees/Priests/Casters/Hybirds/Hybrids/PetClass/Group#] "These Setting are for when Call out Specific Bots only." |: Ini Comments Line
	
	|:Set Class Types: Melee(mClassTypes), Priest(pClassTypes), Caster(cClassTypes), Hybird(hClassTypes)
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" mClassTypes string MeleeClass "Berserker,Ber,Monk,Mnk,Rogue,Rog,Warrior,War,Melees"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" pClassTypes string PriestClass "Cleric,Clr,Druid,Dru,Shaman,Shm,Priests"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" cClassTypes string CasterClass "Enchanter,Enc,Nagician,Mag,Necromancer,Nec,Wizard,Wiz,Casters"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" hClassTypes string HybridClass "Bard,Brd,Beastlord,Bst,Paladin,Pal,Ranger,Rng,Shadow Knight,Shd,Hybirds,Hybrids"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" PetClassTypes string PetClass "Shadow Knight,Shd,Beastlord,Bst,Necromancer,Nec,Enchanter,Enc,Magician,Mag,Druid,Dru,Shaman,Shm,PetClass"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments GrpLeadersOrder "When Using [Group#] to Command a Group of Bots, List your group leaders name in order. Spereated by |" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" GrpLeadersOrder string GrpLeadersOrder "List your group leaders name in order. Spereated by |"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**LINE**|" "=" "=" "1" |: Ini Line Seperator
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments Masters "List of character names allowed to command your bot. Also allow to add another Bots ini file here E.G; bot_Mortefreddo_Enchancter.ini Seperated by |" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" Masters string Masters "bot_Masters.ini"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	|:----------------------------------------------------------------------
	|:Initialize Masters as Ini File (characters that can control this bot)
	|:----------------------------------------------------------------------
	/if (${Bool[${Masters.Find[.ini]}]}) {
		/if (${Bool[${Masters.Find[/]}]} && ${Bool[${Ini[${Masters},Core,Masters]}]}) {
			/varset Masters ${Ini[${Masters},Core,Masters]}
		} else /if (!${Bool[${Masters.Find[/]}]} && ${Bool[${Ini[${INI_LOCATION_PREFIX}/${Masters},Core,Masters]}]}) {
			/varset Masters ${Ini[${INI_LOCATION_PREFIX}/${Masters},Core,Masters]}
		} else /if (${Bool[${Ini[${Masters},Core,Masters]}]}) {
			/varset Masters ${Ini[${Masters},Core,Masters]}
		} else {
			/echo Unable to Find Masters File: [${Masters}]. Please Fix your File Path Location. INI Root Directory is: Macros/ Use ../ to Go back a Directory.
			/end
		}
	}
		
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ChatOut "Determine if Bots will Send Chat into ChatIn. Options: SHOW|HIDE|Settings|Events|Core|Combat|Healer|Spell|Pets|Params|Routines|Update|Ini" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ChatOut string ChatOut Show
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ChatIn "Changes what channel the bot will use for replying to it's master. Options: EQBC|GUILD|GROUP|SAY|RAID|TELL|IRC|CHANNEL|/ChannelName" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ChatIn string ChatIn EQBC
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ListenInChannels "Determines what channel the bot will Listen for Commands from it's master. Options: CHAT,GUILD,GROUP,TELL,SAY,SHOUT,RAID,IRC,EQBC" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ListenInChannels string ListenInChannels EQBC,GUILD,GROUP,TELL,SAY,RAID
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments checkname "Toggle(On/Off) if set to true, bot will only respond to commands if the command is preceeded with Bots Name first." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" checkname off return "I will respond to all commands." "I will only respond to commands that are addressed to me."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments IgnGroupList "List of command Spereated by | to Ignore in group chat." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" IgnGroupList string IgnGroupList "List of command Spereated by | to Ignore in group chat."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments dopublic "Toggle(On/Off) if set to true, Bot will Obay Commands from everyone." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" dopublic off return "I will not Obay other commands only the master(s)." "I will Obay other commands."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments PublicCommands "List Command(s) you want to be public seperated by |" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" PublicCommands string PublicCommands "GL|Cheals|GO"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments CrossZoneCommands "List Command(s) you want to be able to call across zone lines. seperated by |" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" CrossZoneCommands string CrossZoneCommands "Find"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments relaytells "Toggle(On/Off) Bot will Send all Tells into [ChatIn] Channel" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" relaytells off return "I will not relay tells to my master." "I will relay tells to my master."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autobeep "Toggle(On/Off) This will Keep doin System Beeping when you receive a [Tell] untill autobeep off Command Given." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autobeep off return "I will not Beep on Tells unlimited." "I will Beep on Tells unlimited."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments movetomode "Allows you to change the way bot moves. 1 = Moveutils, 2 = Nav, 3 = AdvPath" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" movetomode int movetomode 1
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments followmode "Allows you to change the way bot follows. 1 = Moveutils, 2 = Nav, 3 = AdvPath" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" followmode int followmode 1
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autofollow "Bot Auto Follow [autofollowTarget] automatically after any current Commands Pending is done." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autofollow off return "I will not autofollow [@{autofollowTarget}]  now." "I will now autofollow [@{autofollowTarget}] ."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autofollowTarget "This is the Target Bot will Auto Follow when autofollow=ON" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" autofollowTarget string autofollowTarget None
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments FollowLeash(Min|Max) "Bot Distance Check for autofollow. Might Remove This" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" FollowLeashSetting string FollowLeash(Min|Max) 45|200
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments bottracker "Bot will Track other Bots Lost, Not in Zone." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" bottracker on return "I will not auto track my bots anymore." "I will auto track all my bots."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments BotTrackerDistance "The Distance Bots have to be before it will Start tracking others." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BotTrackerDistance string BotTrackerDistance 200
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	|: Just a Pause Macro Command No INI needed.
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" pause noini return "I will obey Commands." "I will not obey Commands."

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments DebugList "This is to have Macro Show Debug information. To Locate problems Options: None|ALL|Core|Main|Shortcuts|Subrountine Name" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" DebugList string DebugList "None"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ControlPass "If anyone sends your Bot This Keyword they will be added to Masters List Temporary, Allowed Full Control over you." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ControlPass string ControlPass ![Gentrol]
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments factionhits "Bots will Display what Faction hits they Received in ChatIn Channel. " |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" factionhits off return "I will not Display Factions Hits." "I will Display all Faction Hits."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autoaaexp "Bot will Auto Change AA Percent based on Current XP/Level. E.G; Check IF (Level < 70 || Level == 70 && XP < 80 Set AA 0) || (Level == 70 && XP > 97 Set AA 100)" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autoaaexp on return "I will not Auto Adjust AA EXP Percentage." "I will Auto Adjust AA EXP Percentage."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autoleaderaa "This will make sure your Leadership AAs are always ON." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autoleaderaa on return "I will not Auto Enable Leadership AA EXP." "I will Auto Enable Leadership AA EXP."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments reportexp "This will have bots Report to ChatIn Channel when they Receive XP." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" reportexp off return "I will not Report my Experience Gains to you Master!." "I will Report my Experience Gains to you Master!."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**HEADER**|" "=" "[MQ2HUD INI Settings]" "2" |: Ini Blank Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments HUDBotTrackerGrp1-3 "List of character names to Track in MQ2Hud. Seperated by |" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" HUDBotTrackerGrp1 string HUDBotTrackerGrp1 Mortefreddo|Mortetorsioner|Morteastrale|Mortalespirito|Morteleggenda|Mortescopocolpo
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" HUDBotTrackerGrp2 string HUDBotTrackerGrp2 Demonslayer|Morteassassino|Mortestregona|Spiritualmorte|Mortezapa|Mortecantante
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" HUDBotTrackerGrp3 string HUDBotTrackerGrp3 Morteacqua|Mortespirito|Scuranima|Mortescheletro|Morteacapella|Coopbestia
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" HUDBotTrackerGrp4 string HUDBotTrackerGrp4 Morteacqua|Mortespirito|Scuranima|Mortescheletro|Morteacapella|Coopbestia
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments hudgroup1-4 "" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" hudgroup1 off return "I will not Display Bot Group [1] on hud!." "I will Display Bot Group [1] on hud!."
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" hudgroup2 off return "I will not Display Bot Group [2] on hud!." "I will Display Bot Group [2] on hud!."
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" hudgroup3 off return "I will not Display Bot Group [3] on hud!." "I will Display Bot Group [3] on hud!."
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" hudgroup4 off return "I will not Display Bot Group [4] on hud!." "I will Display Bot Group [4] on hud!."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments spawnlist "" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" spawnlist off return "I will not Display Spawn List to you Master!." "I will Display Spawn List to you Master!."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**LINE**|" "=" "=" "2" |: Ini Line Seperator
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1

	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autorelog "This will Force Bot to Automatically Log back into game when they LD/Crash to Character Select Screen." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autorelog off return "I will not Auto Login on LD/Crash." "I will Auto Login on LD/Crash."
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
/return ${i}

Sub Init_Wait4Rez_Ini

|: --------------
|: -- For each command
|: -- /call AddCommand "Command Section" "Command Phrase" "Called Sub"
|: -- Command Section - where the command will be listed in response to the cmd phrase
|: -- Command Phrase to trigger bot - End User can change to suit prefferences
|: -- Called Sub - Routine to execute in response to Command Phrase
|: --------------

|:This sets genbot's avaiable commands with Sub Command_NamesBelow:|
|:/call AddCommands mainassist disband accept reject trade tradeitem pet


|:##--------------------------------##:|
|:Declare Core Variables:|
|:##--------------------------------##:|



|:##--------------------------------##:|
|:Declare Timers:|
|:##--------------------------------##:|

|:use_Wait4Rez
/call LoadSetting INFO Comments wait4rez "This will auto start Wait for Rez Dialog, Loot Corpse, Mem Spells when you Die." |: Ini Comments Line
/call AddToggle wait4rez on return "I will not Auto Wait for Rez Message." "I will Auto Wait for Rez Message."

|:use_Wait4Rez
/call LoadSetting INFO Comments autoaccept "This will auto Accept Rez Window" |: Ini Comments Line
/call AddToggle autoaccept on return "I will not Auto Accept Rez Window." "I will Auto Accept Rez Window."

|:Wait4RezAlert
/call LoadSetting INFO Comments Wait4RezAlert(Beeps) "The Number Amount of Beeps you want macro to do when bot Dies. ex; Wait4RezAlert(Beeps)=3 will beep 3 times." |: Ini Comments Line
/call LoadSetting Wait4RezAlert string Wait4RezAlert(Beeps) 3

|:use_Wait4Rez
/call LoadSetting INFO Comments buffAfterRez "This will auto ask for buffs After he accepts Rez" |: Ini Comments Line
/call AddToggle buffafterrez on return "I will not ask for BUFFS after im Rezed!" "I will ask for BUFFS after im Rezed!"
/call LoadSetting INFO Comments RezBuffList "List Buff seperated by | an ex; Buffme|SHORTCUTS or voq|god|vq" |: Ini Comments Line
/call LoadSetting RezBuffList string RezBuffList buffme

/return

Sub Init_BoxingSetup_Ini

|: --------------
|: -- For each command
|: -- /call AddCommand "Command Section" "Command Phrase" "Called Sub"
|: -- Command Section - where the command will be listed in response to the cmd phrase
|: -- Command Phrase to trigger bot - End User can change to suit prefferences
|: -- Called Sub - Routine to execute in response to Command Phrase
|: --------------

|:This sets genbot's avaiable commands with Sub Command_NamesBelow:|
|:/call AddCommands mainassist disband accept reject trade tradeitem pet


|:##--------------------------------##:|
|:Declare Core Variables:|
|:##--------------------------------##:|



|:##--------------------------------##:|
|:Declare Timers:|
|:##--------------------------------##:|


/call LoadSetting INFO Comments boxsetup "This will auto start Game Setup Box/Main Settings for Optimization." |: Ini Comments Line
/call AddToggle boxsetup off return "I will not Auto Setup Box/Main Game Settings." "I will Auto Setup Box/Main Game Settings."

/call LoadSetting INFO Comments autoboxbga "This will Automatically Adjust Bots in Background to Lowest Settings." |: Ini Comments Line
/call AddToggle autoboxbga off return "I will not Auto Adjust Bots Lowest Settings in Background." "I will Auto Adjust Bots Lowest Settings in Background."

/call LoadSetting INFO Comments advancesettings_boxsetup "This will Automatically Adjust EQClient.ini for More Optimization. IF AdvanceSettings(WinEQ2_EQClient) is Set will Edit that ini file for WINEQ2 Profile. IF Enabled Must fill out [AdvanceSettings(EQPath)] to use this Option." |: Ini Comments Line
/call AddToggle advancesettings_boxsetup off return "I will Not Change EQClient.ini Settings." "I will Change EQClient.ini Settings."

/call LoadSetting INFO Comments AdvanceSettings(WinEQ2_EQClient) "This is the [EQClient.ini] Setting. You Set in WinEQ2 EQ Profile Option for Each WinEQ2 Profile. If Left Un-Edited will use Defaul: EQClient.ini" |: Ini Comments Line
/call LoadSetting AdvanceSettings_WinEQ2_EQClient string AdvanceSettings(WinEQ2_EQClient) "WinEQ2 Profile [EQClient.ini] eqclient.ini"

/call LoadSetting INFO Comments advancesettings_memory "This will Automatically Adjust Memory.ini file for Further Optimization. Turning this [OFF] Revert Settings to Default. IF Enabled Must fill out [AdvanceSettings(EQPath)] to use this Option." |: Ini Comments Line
/call AddToggle advancesettings_memory off return "I will Not Change memory.ini settings." "I will change memory.ini settings."

/call LoadSetting INFO Comments AdvanceSettings(EQPath) "This is the Full Path To you EverQuest Install Directory." |: Ini Comments Line
/call LoadSetting AdvanceSettings_EQPath string AdvanceSettings(EQPath) "FULL EQ Game Path  ex; E:\Games\Sony\EverQuest_rof2"

/call LoadSetting INFO Comments SoundOption(On/Off) "This is to Auto turn Sound ON or OFF" |: Ini Comments Line
/call LoadSetting SoundOption string SoundOption(OFF|LOW|MED|HIGH|MAX|CUSTOM) OFF

/call LoadSetting INFO Comments DisplayOption(On/Off) "This is to Auto Adjust Display Options.  Main_Default: [High] Bot_Default: [OFF]" |: Ini Comments Line
/call LoadSetting DisplayOption string DisplayOption(OFF|LOW|MED|HIGH|MAX|CUSTOM) OFF

/call LoadSetting SoundSetting string SoundSetting(Custom#5) 0|0|0|0|0
/call LoadSetting DisplaySetting_Section1 string DisplaySetting_Section1(Custom#5) 0|0|0|0|0
/call LoadSetting DisplaySetting_Section2 string DisplaySetting_Section2(Custom#8) 0|0|0|0|0|0|0|0
/call LoadSetting DisplaySetting_Section3 string DisplaySetting_Section3(Custom#5) 1|1|1|0|0
/call LoadSetting DisplaySetting_Section4_Tab1 string DisplaySetting_Section4_Tab1(Custom#4) 1|1|1|0
/call LoadSetting DisplaySetting_Section4_Tab2 string DisplaySetting_Section4_Tab2(Custom#3) 1|1|0
/call LoadSetting DisplaySetting_Section4_Tab3 string DisplaySetting_Section4_Tab3(Custom#4) 1|1|1|0
/call LoadSetting DisplaySetting_Advanced_Section1 string DisplaySetting_Advanced_Section1(Custom#5) 0|1|1|1|1
/call LoadSetting DisplaySetting_Advanced_Section2 string DisplaySetting_Advanced_Section2(Custom#11) 0|0|0|0|0|0|0|0|0|0|0
/call LoadSetting DisplaySetting_Advanced_Section3 string DisplaySetting_Advanced_Section3(Custom#4) 0|0|0|0

/call LoadSetting INFO Comments CustomVariableHelp "Variable Values: CheckBox = [ 0=OFF 1=ON ] | ComboBox = [ 1-10 ] - Varys Deppending on Combo Box Check In-Game Option. | Slider = [ 0-100 ]" |: Ini Comments Line
/call LoadSetting INFO Comments SoundSetting(Custom#5) "Sound Realism [Silder] | Music Volume [Silder] | Sound Volume[Silder]| Environment Sounds [CheckBox] | Combat Music [CheckBox]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Section1(Custom#5) " Show PC Names [CheckBox] | Show NPC Names [CheckBox] | Show 3D Target Ring [CheckBox] | Level of Detail [CheckBox] | Show My Helm [CheckBox]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Section2(Custom#8) "Allow Window Resizing [CheckBox] | Overlap Windows Taskbar [CheckBox] | Show Buff Timer [CheckBox] | Show Buff Counters [CheckBox] | Show Buff Limit Uses [CheckBox] | Show Song Timer [CheckBox] | Show Song Counters [CheckBox] | Show Song Limit[CheckBox]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Section3(Custom#5) "Loading Screen [ComboBox] | Sky Type [ComboBox] | New Armor [ComboBox] | Gamma [Slider] | Far Clip Plane [Slider]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Section4_Tab1(Custom#4) "Near Clip [ComboBox] | Density [ComboBox] | On For [ComboBox] | Opacity [Silder]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Section4_Tab2(Custom#3) "Near Clip [ComboBox] | Density [ComboBox] | Opacity [Silder]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Section4_Tab3(Custom#4) "Near Clip [ComboBox] | Density [ComboBox] | On For [ComboBox] | Opacity [Silder]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Advanced_Section1(Custom#5) "Use new water [CheckBox] | Dynamic Sky Reflection Size [ComboBox] | Sky Reflection Update Interval [ComboBox] | Terrain Texture Quality [ComboBox] | Memory Mode [ComboBox]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Advanced_Section2(Custom#11) "Allow hw Vertex Shaders [CheckBox] | Allow 1.1 Pixel Shaders [CheckBox] | Allow 1.4 Pixel Shaders [CheckBox] | Allow 2.0 Pixel Shaders [CheckBox] | Use Advanced Lighting [CheckBox] | Shadows [CheckBox] | Radial Flora [CheckBox] | Stream Item Textures [CheckBox] | Disable Tattoos [CheckBox] | Post Effects [CheckBox] | Bloom Effects [CheckBox]" |: Ini Comments Line
/call LoadSetting INFO Comments DisplaySetting_Advanced_Section3(Custom#4) "Shadow Clip Plane [Silder] | Actor Clip Plane [Silder] | Max Foreground FPS [Silder] | Max Background FPS [Silder]" |: Ini Comments Line
	
/return

Sub Init_Combat_Ini

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|:Add Delete Text [|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|] to unused Ini Settings
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" DeleteMe DeleteMe ProtectList "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"

	|:This sets genbot's avaiable commands with Sub Command_NamesBelow:|
	/call AddCommands anchor guard
	/call AddCommands disc burn getbehind shield clickoff tribute jolt multiaggro melee archery


	|:##--------------------------------##:|
	|:Declare Combat Variables:|
	|:##--------------------------------##:|
	/declare EnrageVar int outer 0
	/declare RogueStrike string outer
	/declare i int local 1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autobehind "Forces the bot to always get behind target on assist." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autobehind off return "I won't position myself behind the mob." "I will position myself behind the mob."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autoengage "The bot will use (MQ2MoveUtils) to stick to assist target." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autoengage on return "I will not Auto Engage when attack is on." "I will Auto Engage when attack is on."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autosnap "Forces the bot to always Face the Target." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autosnap on return "I will not snap back to Targets." "I will snap back to Targets."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments raidevade "Forces the bot to turn attack off if they are hit." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" raidevade off return "Auto Attack off if hit. Is now off." "Auto Attack off if hit. Is now on."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments MaxTargetRange "Max Range Bots will Assist at." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" MaxTargetRange int MaxTargetRange 150
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	|: Set MQ2MoveUtils Default Settings
	/squelch /nomodkey /docommand /stick set breakdist ${MaxTargetRange}
	/squelch /nomodkey /docommand /stick set BreakOnGate on
	/squelch /nomodkey /docommand /stick set BreakOnWarp on
	/squelch /nomodkey /docommand /stick save
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments melee "This will turn Bot Melee on automatically. When in Combat." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" melee on return "The Melee is set to off." "The Melee is set to on."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments archery "This will turn Bot Archery autofire on automatically. When in Combat." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" archery off return "The Archery is set to off." "The Archery is set to on."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments MeleeRange "This is Bots Melee Distance from Target bot will Assist at." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" MeleeRange int MeleeRange 12
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ArcheryRange "This is Bots Archery Distance from Target bot will Assist at. Minimum Setting=34" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ArcheryRange int ArcheryRange 34
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments AutoArrowType "NOT WORKING ATM." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" AutoArrowType string AutoArrowType "Frost Arrows"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autodistance "Forces the Bot to Set Combat Distance Depending on Targets MaxRangeTo Value." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autodistance on return "I will Not Automatically Set my Combat Distance Depending on Target." "I will Automatically Set my Combat Distance Depending on Target"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments pvpmode "Allows Bot to be able to Attack PC Players/Pets" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" pvpmode off return "I will not attack players on assist/attack." "I will attack players on assist/attack."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autostand "Forces Bot to Standup Automatically if Sitting or Feign only when in Combat." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autostand on return "Auto Standup is now off." "Auto Standup is now on."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments defend "Bot will Automatically Attack Back if hit by a NPC." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" defend off return "I will not defend myself if atttacked." "I will defend myself if atttacked."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments enrage "Forces Bot to turn attack off if Target Enrages, Turns Attack back on after Enrage Done Automatically." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" enrage on return "Auto Enrage is now off." "Auto Enrage is now on."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments MainAssist "Bot uses this Target as Assist Target when you call Command (Assist) without any Params." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" MainAssist string MainAssist "Assist automatically if no Target on Assist Command"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments GuardRadius "The Distance Around Bot that he will Automatically Attack Targets." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" GuardRadius int GuardRadius 75
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ProtectRadius "The Distance bot will Check from Protect Targets." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ProtectRadius int ProtectRadius 75
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments guard "This will make Bot Guard a Certian Area for NPCs" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" guard off return "I will not defend this area from intruders." "I will defend this area from intruders."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments GuardXTar "" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" GuardXTar string GuardXTar(On/Off|Position) off|Top
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments GuardMA "" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" GuardMA string GuardMA(On/Off|MainAssist)  off|MainAssist
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments protect "This will make Bot Protect Names on ProtectionList." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" protect off return "I will not protect [Protection List]." "I will protect [Protection List]."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments puller "This will allow you to pull Trgets When Guard is on, Guard will only Automatically Take over when within 1/3 Distance from Guard Location." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" puller off return "I'm not the puller." "I'm the puller."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments ProtectionList "This is a List of Bots to Automatically Protect when they get Attacked." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ProtectionList string ProtectionList "Add Names of [People to Protect] separated by |"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments NeverKill "List of NPCs Bots will never Attack." |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" NeverKill string NeverKill "things you never want to attack separated by |"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments Guard_Protect_Alert "The numbers of times to Beep when Monster Attacks ProtectList or Near Guard Location. Ex. 3" |: Ini Comments Line
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" Guard_Protect_Alert string Guard_Protect_Alert "numbers of times to Beep"
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autotarget "This Will Allow you to Switch Target in middle of Combat." |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autotarget off return "I will not stay on Target & will Switch." "I will stay on Target & will Not Switch."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autotargetclear "" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autotargetclear off return "I will not Automatically keep Targets Clear." "I will Automatically keep Targets Clear."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments manualmode "This will Stop Bot from Automatically Turning Melee/Archery/Casting ON" |: Ini Comments Line
	/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" manualmode off return "I will Auto Toggle [Combat,Archery] ON!." "I will not Auto Toggle [Combat,Archery] ON!."
	/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
	/varcalc i ${i}+1
	
	|: BER,MNK,ROG,WAR,CLR,DRU,SHM,ENC,MAG,NEC,WIZ,BRD,BST,PAL,RNG,SHD
	/if (${Select[${Me.Class.ShortName.Upper},BRD,BST,MNK,SHD,WAR]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments aggro "This will have Bot Automatically do everything the Bot can to get and hold aggro" |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" aggro off return "I will not do anything to grab aggro." "I will do everything I can to get aggro." aggro
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" aggro noini return "I will not do anything to grab aggro." "I will do everything I can to get aggro."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	}
	
	/if (${Select[${Me.Class.ShortName.Upper},BRD,BST,PAL,ROG,SHD]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments hide "Automatically click Hide when in Combat." |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" hide off return "Auto Hide is now off." "Auto Hide is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" hide noini return "Auto Hide is now off." "Auto Hide is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	}
	
	/if (${Me.Class.Name.Equal[Bard]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autofade "Automatically use Fade Memories AA if Bards HP Percent = (AutoFadePct)" |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autofade off return "Auto Fading Memories is now off." "Auto Fading Memories is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
		
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments AutoFadePct "The Bards HP Percent the Bot will use if (autofade) is ON" |: Ini Comments Line
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" AutoFadePct int AutoFadePct 10	
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	}
	
	
	/if (${Select[${Me.Class.ShortName.Upper},BST,RNG,BER,MNK,WAR]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments kick "Automatically click Kick when in Combat." |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" kick on return "Auto Kick is now off." "Auto Kick is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" kick noini return "Auto Kick is now off." "Auto Kick is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	}
	
	/if (${Select[${Me.Class.ShortName.Upper},NEC,MNK,SHD]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments autofeigndeath "The Bot will Automatically Feign when HP% = (AutoFeignPct)" |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autofeigndeath on return "Auto Feign Death is now off." "Auto Feign Death is now on."
		
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments AutoFeignPct "The Percent Bot will Use Auto Feign." |: Ini Comments Line
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" AutoFeignPct int AutoFeignPct 15
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autofeigndeath noini return "Auto Feign Death is now off." "Auto Feign Death is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	}
	
	/if (${Select[${Me.Class.ShortName.Upper},PAL,RNG,BER,MNK,ROG,SHD,WAR]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments disarm "Automatically click Disarm when in Combat." |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" disarm off return "Auto Disarm is now off." "Auto Disarm is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" disarm noini return "Auto Disarm is now off." "Auto Disarm is now on."
	}
	
	/if (${Select[${Me.Class.ShortName.Upper},PAL,SHD,WAR]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments bash "Automatically click Bash when in Combat." |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" bash off return "Auto Bash is now off." "Auto Bash is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" bash noini return "Auto Bash is now off." "Auto Bash is now on."
	}
	
	/if (${Select[${Me.Class.ShortName.Upper},PAL,RNG,SHD,WAR]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments taunt "Automatically click Taunt when in Combat." |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" taunt off return "Auto Taunt is now off." "Auto Taunt is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" taunt noini return "Auto Taunt is now off." "Auto Taunt is now on."
	}
	
	/if (${Select[${Me.Class.ShortName.Upper},WAR]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" INFO Comments slam "" |: Ini Comments Line
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" slam off return "Auto Slam is now off." "Auto Slam is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" "|**BLANK**|" "=" "=" "${i}" |: Ini Blank Line
		/varcalc i ${i}+1
	} else {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" slam noini return "Auto Slam is now off." "Auto Slam is now on."
	}
	
	/if (${Me.Class.Name.Equal[Bard]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Deftdance Discipline|Disc,Boastful Bellow|AA"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
	
	}
	/if (${Me.Class.Name.Equal[Beastlord]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Bestial Fury|Disc"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" ba noini return "I will not keep 'Bestial Alignment' Up." "I will make sure 'Bestial Alignment' stays on."

	}
	/if (${Me.Class.Name.Equal[Magician]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"

	}
	/if (${Me.Class.Name.Equal[Necromancer]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"

	}
	/if (${Me.Class.Name.Equal[Paladin]}) {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" autoloh on return "I will not auto [Lay of Hands] any Targets." "I will now auto [Lay of Hands] Targets."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" lohSetting string loh(Target|Pct) "The Targets Name|Percent of there life to Lay of Hands Them."
			
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"

	}
	/if (${Me.Class.Name.Equal[Ranger]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Frost Arrows|AA,Trueshot Discipline|Disc,Guardian of the Forest|AA"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"

	}
	/if (${Me.Class.Name.Equal[Shaman]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
	}
	/if (${Me.Class.Name.Equal[Wizard]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Mana Burn|AA,Call of Xuzl|AA,Harvest of Druzzil|AA,Harvest|Gem"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
	}
	/if (${Me.Class.Name.Equal[Berserker]}) {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" frenzy off return "Auto Frenzy is now off." "Auto Frenzy is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Focused Fury|Disc"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
	}
	/if (${Me.Class.Name.Equal[Monk]}) {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" flyingkick on return "Auto FlyingKick is now off." "Auto FlyingKick is now on."
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" roundkick off return "Auto Round Kick is now off." "Auto Round Kick is now on."
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" eaglestrike off return "Auto Eagle Strike is now off." "Auto Eagle Strike is now on."
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" tigerclaw off return "Auto Tiger Claw is now off." "Auto Tiger Claw is now on."
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" mend on return "Auto Mend is now off." "Auto Mend is now on."
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" intimidation on return "Auto Intimidation is now off." "Auto Intimidation is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" PctMend int PctMend 75
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Speed Focus Discipline|Disc"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
	}
	/if (${Me.Class.Name.Equal[Rogue]}) {
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" assassinate off return "Auto Assassinate is now off." "Auto Assassinate is now on."
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" backstab on return "Auto Backstab is now off." "Auto Backstab is now on."
		/call AddToggle "${Macro.CurSub}" "${Macro.CurLine}" pickpockets off return "Auto Pick Pocket is now off." "Auto Pick Pocket is now on."
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Twisted Chance|Disc"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"

	}
	/if (${Me.Class.Name.Equal[Shadow Knight]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Leechcurse|Disc"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
	}
	/if (${Me.Class.Name.Equal[Warrior]}) {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_1 string BurnDiscLvl_1 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_2 string BurnDiscLvl_2 "Fellstrike|Disc"
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" BurnDiscLvl_3 string BurnDiscLvl_3 "Your Disc, AA, Spells, Items to Burn. Ex. Disc Name|disc,Spell Name|gem,AA Ability Name|aa,Item Name|item"
	}

	/if (!${Defined[Defend-msg]}) /declare Defend-msg string outer "I've been attacked by [@{NPCName}]!  Attacking right back!"
	/if (!${Defined[Guard-msg]}) /declare Guard-msg string outer "Intruder alert!  Attacking the trespassing [@{NPCName}]!."
	/if (!${Defined[Protect-msg]}) /declare Protect-msg string outer "How dare [@{NPCName}] attacks my master [@{ProtectionList.Arg[@{GenFor}, ]}]?!  I must punish this insolence!"
		
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
/return


Sub Init_AutoCombat_Ini

|:##--------------------------------##:|
|:Declare AutoCombat Variables:|
|:##--------------------------------##:|
/declare autoic_num int outer
/declare combatclick_num int outer
/declare itemclick_num int outer
/declare combatclick_delay int outer
/declare itemclick_Mana  int outer
/declare itemclick_HP  int outer
/declare aAANum int outer
/declare aDiscNum int outer

/call AddToggle autocharm off return "I will not do auto Charming. Good Luck!" "I will do my own auto Charming. Your Safe"
/call LoadSetting autocharmtries string autocharmtries "The Amount of Tries to recharm set to 0 for unlimited Default: 5 "
/call AddToggle autocharmda off return "I will not automatically cast Damage Absorb Spell." "I will automatically cast Damage Absorb Spell."

/call AddToggle autosnare off return "I will not ask [@{autosnare_opts.Arg[1,|]}] for Snare help." "I will ask [@{autosnare_opts.Arg[1,|]}] for Snare help."
/call LoadSetting autosnare_opts string autosnare(Name|Spell|Delay) "Characters Name|Snare Spell to use|Delay for Recharm in Seconds"

/call AddToggle itemclick off return "I will not use auto item clicking always." "I will use auto item clicking always."
/call LoadSetting itemclick_name#1 string itemclick_name#1(Name|Mana|HP) "Complete Item Name|Less Than Mana Percent|More than HP Percent"

/call AddToggle autouninvis off return "I will not auto Uninvis on Assist." "I will auto Uninvis on Assist."

/call AddToggle autoic off return "I will not use auto item clicking when in combat/always." "I will use auto item clicking when in combat/always."
/call LoadSetting autoitemclick_name#1 string autoitemclick_name#1 "Change 1 to 2,3 etc for each item and value equal item name."

/call AddToggle combatclick off return "I will not use auto item clicking when in combat/always." "I will use auto item clicking when in combat/always."
/call LoadSetting combatclick_name#1 string combatclick_name#1(Name|Delay) "Change 1 to 2,3 etc for each item and value equal item name."
/call LoadSetting combatclick_delay string combatclick_delay "Set delay to click item (amount Seconds/Minutes #s/m) Default:60s"

/call AddToggle autopotion off return "I will not automatically use potions in combat." "I will use potions in combat automatically."
/call LoadSetting autoPot#1 string autoPot#1(Name|Pct[h/m/na]) "Distillate of Celestial Healing X|45h"
/call LoadSetting autoPot#2 string autoPot#2(Name|Pct[h/m/na]) "Distillate of Alacrity X|NA"

/if (${Me.Class.Name.Equal[Beastlord]}) {
	/call AddToggle autospell on return "I will not automatically use spells in combat." "I will use spells in combat automatically."
	/call LoadSetting aSpellName string aSpellName "Trushar's Frost"
}
/if (${Me.Class.Name.Equal[Ranger]}) {
	/call AddToggle autospell on return "I will not automatically use spells in combat." "I will use spells in combat automatically."
	/call LoadSetting aSpellName string aSpellName "Frozen Wind|Sylvan Burn"
}
/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	/call AddToggle autospell on return "I will not automatically use spells in combat." "I will use spells in combat automatically."
	/call LoadSetting aSpellName string aSpellName "Miasmic Spear"
}
/if (${Me.Class.Name.Equal[Bard]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "Boastful Bellow|100h"
}
/if (${Me.Class.Name.Equal[Beastlord]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "Feral Swipe|90h"
}
/if (${Me.Class.Name.Equal[Cleric]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Druid]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Enchanter]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Magician]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Necromancer]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Paladin]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Ranger]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "Frost Arrows|100h"
}
/if (${Me.Class.Name.Equal[Shaman]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Wizard]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "Harvest of Druzzil|85m"
}
/if (${Me.Class.Name.Equal[Berserker]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Monk]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Rogue]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}
/if (${Me.Class.Name.Equal[Warrior]}) {
	/call AddToggle autoaa off return "I will not automatically use AAs in combat." "I will use AAs in combat automatically."
	/call LoadSetting aAASetting string autoAA#1(Name|Pct[h/m]) "AA Ability Name|60h"
}

/if (${Me.Class.Name.Equal[Bard]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Beastlord]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Cleric]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Druid]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Enchanter]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Magician]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Necromancer]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Paladin]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Ranger]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Shaman]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Wizard]}) {
}
/if (${Me.Class.Name.Equal[Berserker]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Monk]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Thunderkick Discipline|100h"
}
/if (${Me.Class.Name.Equal[Rogue]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}
/if (${Me.Class.Name.Equal[Warrior]}) {
	/call AddToggle autodisc off return "I will not automatically use Disc in combat." "I will use Disc in combat automatically."
	/call LoadSetting aDiscSetting string autoDisc#1(Name|Pct[h/m]) "Combat Disc Name|60h"
}

/call AddToggle guard off return "I will not defend this area from intruders." "I will defend this area from intruders."

/return

Sub Init_Spell_Ini


/declare cmds-SPELL string outer Spell:
|: --------------
|: -- For each command
|: -- /call AddCommand "Command Section" "Command Phrase" "Called Sub"
|: -- Command Section - where the command will be listed in response to the cmd phrase
|: -- Command Phrase to trigger bot - End User can change to suit prefferences
|: -- Called Sub - Routine to execute in response to Command Phrase
|: --------------

|:This sets genbot's avaiable commands with Sub Command_NamesBelow:|
/call AddCommands buffs buffg selfbuff bufflist buffkeepup mana evac port loadss
/call AddCommands snt twitch coh spellgem


|:##--------------------------------##:|
|:Declare Spell Variables:|
|:##--------------------------------##:|
/declare EQBCBuff_num int outer

|:Set Class Types: Melee(mClassTypes), Priest(pClassTypes), Caster(cClassTypes), Hybird(hClassTypes)
/declare mClassTypes string outer Berserker,Ber,Monk,Mnk,Rogue,Rog,Warrior,War,Melee
/declare pClassTypes string outer Cleric,Clr,Druid,Dru,Shaman,Shm,Priest
/declare cClassTypes string outer Enchanter,Enc,Nagician,Mag,Necromancer,Nec,Wizard,Wiz,Caster
/declare hClassTypes string outer Bard,Brd,Beastlord,Bst,Paladin,Pal,Ranger,Rng,Shadow Knight,Shd,Hybird
/declare PetClassTypes string outer Shadow Knight,Shd,Beastlord,Bst,Necromancer,Nec,Enchanter,Enc,Magician,Mag,Druid,Dru,Shaman,Shm,PetClass

|:General Casting
/declare CastTarget string outer
/declare CastType string outer
/declare CastingID string outer
/declare CasterNameID string outer
/declare CasterOptions string outer


|:Wiz/Druid Ports
/declare SpellToCast string outer

|:Chain Nuke
/declare ChainNukeTarget int outer 0
/declare NukeNum int outer 1
/declare ChainNukeCNum int outer 0

|:Current Song Notes
/declare SongNotes string outer

|:Chain Stun
/declare ChainStunNum int outer 1

|:CastingCheck Variables
/declare Distance int outer
/declare hCheck int outer 0
/declare dCheck int outer 0
/declare mCheck int outer 0
/declare MedBreak string outer
/declare tCheck int outer 0
/declare sCheck int outer 0
/declare cnCheck int outer 0

|:Enchanter AutoMez Targets to Ignore
/declare PlayerTargets string outer

|:##-------------------------------##:|
|:Declare MQ2Cast Variables:|
|:##-------------------------------##:|
/declare DefaultCastTarget string outer
/declare DefaultCastType string outer
/declare DefaultCastOpt string outer
/declare interruptFlag bool outer FALSE

|:Spell Casting on Target
/declare CastText string outer
/declare CastTargetClean string outer

|:##--------------------------------##:|
|:Declare Timers:|
|:##--------------------------------##:|
/declare ChainStunTime timer outer
/declare ChainHealTime timer outer

|:CastingChecking
/declare ccIdle string outer 0
/declare ccInvis string outer 0
/declare ccCasting string outer 0
/declare ccMoving string outer 0

|:Complete Heal Rotation
/declare chTimer timer outer -1
/declare chRotAmt int outer
/declare chealTarget string outer
/declare cHealRotation string outer



/if (${Me.Class.Name.Equal[Bard]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
}
/if (${Me.Class.Name.Equal[Beastlord]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Spiritual Dominion"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with | Ex. Spiritual Dominion"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	
	
}
/if (${Me.Class.Name.Equal[Cleric]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call AddToggle cheals noini return "I won't cast [Complete Heal] Automatically." "I will cast [Complete Heal] Automatically."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Armor of the Zealot|Aura of Reverence"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with | Ex. Hand of Virtue"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with | Ex. Virtue"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
}
/if (${Me.Class.Name.Equal[Druid]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call AddToggle cheals noini return "I won't cast [Karana's Renewal] Automatically." "I will cast [Karana's Renewal] Automatically."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with |"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with |"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
}
/if (${Me.Class.Name.Equal[Enchanter]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Ex. Shield of Maelin"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with | Ex. Voice of Quellious|Vallon's Quickening|Guard of Druzzil"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
}
/if (${Me.Class.Name.Equal[Magician]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Ex. Shield of Maelin"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with | Ex. Maelstrom of Ro"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
}
/if (${Me.Class.Name.Equal[Necromancer]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Ex. Shield of Maelin"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with |"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
}
/if (${Me.Class.Name.Equal[Paladin]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Ex. Holy Order"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with | Ex. Brell's Mountainous Barrier"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	
}
/if (${Me.Class.Name.Equal[Ranger]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Ex. Protection of the Wild|Eagle Eye|Mask of the Stalker|Cry of Thunder|Barbcoat"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with | Ex. Strength of Tunare|Spirit of the Predator"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with | Ex. Call of the Rathe|Regrowth"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	
}
/if (${Me.Class.Name.Equal[Shaman]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with |"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with |"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle buffbots noini return "I will not use my auto buff list." "I will use my auto buff list."
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	
}
/if (${Me.Class.Name.Equal[Wizard]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with | Ex. Shield of Maelin|Iceflame of E`ci|Force Shield"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with |"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
}
/if (${Me.Class.Name.Equal[Berserker]}) {
}
/if (${Me.Class.Name.Equal[Monk]}) {
}
/if (${Me.Class.Name.Equal[Rogue]}) {
}
/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	/call LoadSetting SpellGem int DefaultSpellGem 8
	/call LoadSetting DefaultSpellSet string DefaultSpellSet "Fight-Set"
	/call addtoggle med off return "I will not stay sitting to Mediate mana back." "I will stay sitting to Mediate mana back."
	/call AddToggle dobuff on return "I won't cast buffs until commanded." "I will cast buffs."
	/call LoadSetting BuffSelfList string SelfBuffList "Self Buffs you wish to maintain on yourself separated with |"
	/call LoadSetting GroupBuffList string GroupBuffList "Group Buffs you wish to cast on others separated with |"
	/call LoadSetting	SingleBuffList string SingleBuffList "Single Target Buffs you wish to cast on others separated with |"
	/call LoadSetting BuffTargetSetting string BuffTarget#1(Target|Spell|Gem) "Buffs you wish to keepup on your Bots  separated with |"
	/call LoadSetting	WornOffList string WornOffList "Buffs you wish to have Reported that they Worn off Target. separated with |"
	/call AddToggle autochainnuke off return "I will not cast chainnuke on assist." "I will now cast chainnuke on assist."
	/call LoadSetting ChainNuke string ChainNuke "Your Chain Nuke Spells separated with |."
	/call LoadSetting ChainNukePct string ChainNukePct "The Percent to Start Chain Nuking. Default: 98"
	/call LoadSetting ChainNukeAmt string ChainNukeAmt "The Amount of times to cast Chain Nuking. Default: 0 for Unlimited."	
	
}
/if (${Me.Class.Name.Equal[Warrior]}) {
}

/return

Sub Init_CHRotation_Ini

/if (${Me.Class.Name.Equal[Cleric]} || ${Me.Class.Name.Equal[Druid]} || ${Me.Class.Name.Equal[Shaman]}) {

	|: --------------
	|: -- For each command
	|: -- /call AddCommand "Command Section" "Command Phrase" "Called Sub"
	|: -- Command Section - where the command will be listed in response to the cmd phrase
	|: -- Command Phrase to trigger bot - End User can change to suit prefferences
	|: -- Called Sub - Routine to execute in response to Command Phrase
	|: --------------

	|:This sets genbot's avaiable commands with Sub Command_NamesBelow:|
	|:/echo ${cmds-CHRotation.Replace[|,,]}
	/call AddCommands go clericadd clericremove tankswap tankchange variable_change chealssync


	|:##--------------------------------##:|
	|:Declare Core Variables:|
	|:##--------------------------------##:|



	|:##--------------------------------##:|
	|:Declare Timers:|
	|:##--------------------------------##:|


	/call LoadSetting INFO Comments boxsetup "This will turn on/off Auto Chain Complete Heals" |: Ini Comments Line
	/call AddToggle cheals off return "I will not Start Auto Chain Complete Heals." "I will Start Auto Chain Complete Heals."


	/call LoadSetting INFO Comments CHRotChatIn "The Chat Channel The Complete Heal Bot will Talk/Listen in" |: Ini Comments Line
	/call LoadSetting CHRotChatIn string CHRotChatIn "rsay"


	/call LoadSetting INFO Comments Cleric_List "Edit this line to include the names of your clerics in the chain" |: Ini Comments Line
	/call LoadSetting Cleric_List string Cleric_List "Morteastrale Morteacqua Spiritualmorte"


	/call LoadSetting INFO Comments Tank_List "Edit this line to include the names of your tanks in rotation" |: Ini Comments Line
	/call LoadSetting Tank_List string Tank_List "Demonslayer"


	/call LoadSetting INFO Comments CHDelay "Edit this to change the default delay that macro starts on" |: Ini Comments Line
	/call LoadSetting CHDelay string CHDelay "6"


	/call LoadSetting INFO Comments CHInterrupt "Edit this to change to ignore interrupts on CH 1=ON 0=off" |: Ini Comments Line
	/call LoadSetting CHInterrupt string CHInterrupt "1"


	/call LoadSetting INFO Comments StopHP "Edit this to change what hp% to stop casts if tank is above (will alway wait until 1.5s from completed cast)" |: Ini Comments Line
	/call LoadSetting StopHP string StopHP "95"


	/call LoadSetting INFO Comments ${Me.Class.ShortName}_HealSpell "Edit this to change what hp% to stop casts if tank is above (will alway wait until 1.5s from completed cast)" |: Ini Comments Line


	/if (${Me.Class.Name.Equal[Cleric]}) {
		/call LoadSetting ${Me.Class.ShortName}_HealSpell string ${Me.Class.ShortName}_HealSpell "Complete Heal"
	}
	/if (${Me.Class.Name.Equal[Druid]}) {
		/call LoadSetting ${Me.Class.ShortName}_HealSpell string ${Me.Class.ShortName}_HealSpell "Karana's Renewal"
	}
	/if (${Me.Class.Name.Equal[Shaman]}) {
		/call LoadSetting ${Me.Class.ShortName}_HealSpell string ${Me.Class.ShortName}_HealSpell "Yoppa's Mending"
	}


	|: ----------------------------DO NOT EDIT BELOW THIS LINE-------------------------------------|
	|: --------------------------------------------------------------------------------------------|
	|: --------------------------------------------------------------------------------------------|

	/declare Cleric_Int int outer 0
	/declare MaxCLR int outer ${Math.Calc[${Cleric_List.Count[ ]}+1].Int}
	/declare NextClr string outer NULL
	/declare FindCleric int outer 0
	/declare NewCleric_List string outer 
	/declare TankRebuild_Int int outer
	/declare Tank_Int int outer 0
	/declare MaxTNK int outer ${Math.Calc[${Tank_List.Count[ ]}+1].Int}
	/declare TankID int outer 0
	/declare NewTank_List string outer
	

}

/return

Sub Init_Cures_Ini


/declare cmds-CURES string outer Cures:
|: --------------
|: -- For each command
|: -- /call AddCommand "Command Section" "Command Phrase" "Called Sub"
|: -- Command Section - where the command will be listed in response to the cmd phrase
|: -- Command Phrase to trigger bot - End User can change to suit prefferences
|: -- Called Sub - Routine to execute in response to Command Phrase
|: --------------

|:This sets genbot's avaiable commands with Sub Command_NamesBelow:|


|:##--------------------------------##:|
|:Declare Spell Variables:|
|:##--------------------------------##:|
/declare autoCures_num int outer

	/if (${Me.Class.Name.Equal[Bard]}) {
	}
	/if (${Me.Class.Name.Equal[Beastlord]}) {
	}
	/if (${Me.Class.Name.Equal[Cleric]}) {
		/call AddToggle docures off return "I won't cast Cures Automatically." "I will cast Cures Automatically."
		/call LoadSetting CureSpell#1 string CureSpell#1(Spell|Gem|Curse|Disease|Poison) "Pure Blood|8|0|18|18"
		/call LoadSetting CureSpell#2 string CureSpell#2(Spell|Gem|Curse|Disease|Poison) "Remove Greater Curse|8|45|0|0"
	}
	/if (${Me.Class.Name.Equal[Druid]}) {
		/call AddToggle docures off return "I won't cast Cures Automatically." "I will cast Cures Automatically."
		/call LoadSetting CureSpell#1 string CureSpell#1(Spell|Gem|Curse|Disease|Poison) "Pure Blood|8|0|18|18"
		/call LoadSetting CureSpell#2 string CureSpell#2(Spell|Gem|Curse|Disease|Poison) "Remove Greater Curse|8|45|0|0"
	}
	/if (${Me.Class.Name.Equal[Enchanter]}) {
	}
	/if (${Me.Class.Name.Equal[Magician]}) {
	}
	/if (${Me.Class.Name.Equal[Necromancer]}) {
	}
	/if (${Me.Class.Name.Equal[Paladin]}) {
		/call AddToggle docures off return "I won't cast Cures Automatically." "I will cast Cures Automatically."
		/call LoadSetting CureSpell#1 string CureSpell#1(Spell|Gem|Curse|Disease|Poison) "Remove Greater Curse|8|45|0|0"
	}
	/if (${Me.Class.Name.Equal[Ranger]}) {
	}
	/if (${Me.Class.Name.Equal[Shaman]}) {
		/call AddToggle docures off return "I won't cast Cures Automatically." "I will cast Cures Automatically."
		/call LoadSetting CureSpell#1 string CureSpell#1(Spell|Gem|Curse|Disease|Poison) "Disinfecting Aura|8|0|20|20"
		/call LoadSetting CureSpell#2 string CureSpell#2(Spell|Gem|Curse|Disease|Poison) "Remove Greater Curse|8|45|0|0"
		/call LoadSetting CureSpell#3 string CureSpell#3(Spell|Gem|Curse|Disease|Poison) "Blood of Nadox|8|0|18|18"
	}
	/if (${Me.Class.Name.Equal[Wizard]}) {
	}
	/if (${Me.Class.Name.Equal[Berserker]}) {
	}
	/if (${Me.Class.Name.Equal[Monk]}) {
		/call AddToggle docures off return "I won't cast Cures Automatically." "I will cast Cures Automatically."
		/call LoadSetting CureSpell#1 string CureSpell#1(Spell|Gem|Curse|Disease|Poison) "Purify Body|alt|36|36|36"
	}
	/if (${Me.Class.Name.Equal[Rogue]}) {
		/call AddToggle docures off return "I won't cast Cures Automatically." "I will cast Cures Automatically."
		/call LoadSetting CureSpell#1 string CureSpell#1(Spell|Gem|Curse|Disease|Poison) "Purge Poison|alt|0|0|99"
	}
	/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	}
	/if (${Me.Class.Name.Equal[Warrior]}) {
	}

/return
Sub Init_Debuffs_Ini

/declare cmds-DEBUFFS string outer Debuffs:

|:##--------------------------------##:|
|:Declare Debuffs Variables:|
|:##--------------------------------##:|
/declare autoDebuffs_num int outer

/call LoadSetting DeleteMe DeleteMe DebuffSpell#1(Spell|Gem) "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"
/call LoadSetting DeleteMe DeleteMe DebuffSpell#2(Spell|Gem) "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"
/call LoadSetting DeleteMe DeleteMe DebuffSpell#3(Spell|Gem) "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"

/if (${Me.Class.Name.Equal[Bard]}) {
}
/if (${Me.Class.Name.Equal[Beastlord]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Sha's Revenge|7|98"
	/call LoadSetting DebuffSpell#2 string DebuffSpell#2(Spell|Gem|Pct) "Incapacitate|6|98"
}
/if (${Me.Class.Name.Equal[Cleric]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Mark of Kings|7|98"
}
/if (${Me.Class.Name.Equal[Druid]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Mire Thorns|7|98"
}
/if (${Me.Class.Name.Equal[Enchanter]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Howl of Tashan|1|98"
	/call LoadSetting DebuffSpell#2 string DebuffSpell#2(Spell|Gem|Pct) "Dreary Deeds|8|98"
	/call LoadSetting DebuffSpell#3 string DebuffSpell#3(Spell|Gem|Pct) "Cripple|7|98"
}
/if (${Me.Class.Name.Equal[Magician]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Malosinia|4|98"
}
/if (${Me.Class.Name.Equal[Necromancer]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Spell|Gem|Pct"
}
/if (${Me.Class.Name.Equal[Paladin]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Spell|Gem|Pct"
}
/if (${Me.Class.Name.Equal[Ranger]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Entrap|7|98"
}
/if (${Me.Class.Name.Equal[Shaman]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Malo|8|98"
	/call LoadSetting DebuffSpell#2 string DebuffSpell#2(Spell|Gem|Pct) "Balance of the Nihil|7|98"
	/call LoadSetting DebuffSpell#3 string DebuffSpell#3(Spell|Gem|Pct) "Cripple|6|98"
}
/if (${Me.Class.Name.Equal[Wizard]}) {
}
/if (${Me.Class.Name.Equal[Berserker]}) {
}
/if (${Me.Class.Name.Equal[Monk]}) {
}
/if (${Me.Class.Name.Equal[Rogue]}) {
}
/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	/call AddToggle debuffs off return "I won't cast debuffs on Assist." "I will cast debuffs on Assits."
	/call LoadSetting DebuffSpell#1 string DebuffSpell#1(Spell|Gem|Pct) "Spell|Gem|Pct"
}
/if (${Me.Class.Name.Equal[Warrior]}) {
}
/return

Sub Init_ClassSpec_Ini

/declare cmds-CLASSSPEC string outer ClassSpec:

/declare TwitchStop int outer 0
/declare CohMode int outer 0
|:##--------------------------------##:|
|:Declare AutoCombat Variables:|
|:##--------------------------------##:|
/declare NecroManaRegen string outer
/declare ShadowManaRegen string outer

/if (${Me.Class.Name.Equal[Bard]}) {
	/call LoadSetting TwistInvis string TwistInvis "Selo's Song of Travel"
	/call LoadSetting TwistSpeed string TwistSpeed "Selo's Accelerating Chorus"
	/call LoadSetting TwistMana string TwistMana "Chorus of Marr"
	/call AddToggle forage off return "I will no longer auto forage." "I will use auto forage now."
	/call AddToggle traps off return "Auto Sense Traps is now off." "Auto Sense Traps is now on."
}
/if (${Me.Class.Name.Equal[Beastlord]}) {
}
/if (${Me.Class.Name.Equal[Cleric]}) {
	/call AddToggle yaulp on return "I won't Yaulp for mana." "I will Yaulp for mana."
	/call LoadSetting YaulpSetting string Yaulp(Spell|Gem|Pct) "Yaulp VI|8|95"
	/call LoadSetting ResurrectionSetting  string Resurrection(Spell|Gem) "Reviviscence|8"
}
/if (${Me.Class.Name.Equal[Druid]}) {
	/call LoadSetting EvacSpell string EvacSpell "Enter the name of your Evac spell here."
	/call AddToggle forage off return "I will no longer auto forage." "I will use auto forage now."
	/call LoadSetting ResurrectionSetting  string Resurrection(Spell|Gem) "Incarnate Anew|8"
}
/if (${Me.Class.Name.Equal[Enchanter]}) {
	/call AddToggle illusions off return "I will not cast Illusions on Command by tells." "I will cast Illusions on Command by tells."
	/call AddToggle stuns noini return "I will Stop my Chain-Stun Rotation." "I will Start my Chain-Stun Rotation."
	/call LoadSetting ChainStun string ChainStun(Spell|Gem) "Your Chain Stun Spells separated with |. Ex. Color Cloud|8|Color Slant|7|Color Skew|6"
	/call LoadSetting ChainStunRune string ChainStunRune(Spell|Gem|On/Off) "Your Rune Spell|Gem|ON or OFF To Keep Up. |. Ex. Ethereal Rune|4|ON"
	/call AddToggle automez off return "I will not crowd control targets near me." "I will crowd control all targets near me."
	/call LoadSetting MezSettings string CrowdControl(Spell|Gem|Radius|RuneSpell|Gem|TashSpell|Gem) "The Spell you want to Mesmerize with separated by |"
}
/if (${Me.Class.Name.Equal[Magician]}) {
	/call LoadSetting PetToys string PetToys(Radius|Item|Amount) "250|Blazing Stone of Demise|2|Girdle of Magi'Kot|1|Muzzle of Mardu|1"
}
/if (${Me.Class.Name.Equal[Necromancer]}) {
	/call AddToggle dotwitch off return "I won't feed other any of my mana." "I will feed others my mana."
	/call LoadSetting TwitchSetting string twitch(Spell|Gem|MinMana) "Sedulous Subversion|6|45|Covetous Subversion|7|45"
	/call AddToggle manadump off return "I won't feed my mana to Group." "I will feed my mana to Group."
	/call LoadSetting ManaDumpSetting string ManaDump(Spell|Gem|Pct) "Sedulous Subversion|6|75|Covetous Subversion|7|75"
	/call AddToggle lich off return "I won't Stay in Skeletion form to regen Mana." "I will stay in Skeletion form to regen Mana."
}
/if (${Me.Class.Name.Equal[Paladin]}) {
	/call AddToggle yaulp off return "I won't Yaulp for mana." "I will Yaulp for mana."
	/call LoadSetting YaulpSetting string Yaulp(Spell|Gem|Pct) "Yaulp|8|95"
}
/if (${Me.Class.Name.Equal[Ranger]}) {
	/call AddToggle forage off return "I will no longer auto forage." "I will use auto forage now."
}
/if (${Me.Class.Name.Equal[Shaman]}) {
	/call AddToggle canni off return "I won't eat myself for mana." "I will eat myself for mana."
	/call LoadSetting CanniSetting string Cannibalize(Spell|Gem|Pct|Limit) "Cannibalize IV|8|75|35"
	/call LoadSetting CanniHoTSetting string CanniHealOverTime(Spell|Gem|Pct) "Quiescence|8|45"
	/call LoadSetting ResurrectionSetting  string Resurrection(Spell|Gem) "Incarnate Anew|8"
}
/if (${Me.Class.Name.Equal[Wizard]}) {
	/call AddToggle harvest off return "I will use my Harvest of Druzzil ability." "I will use my Harvest of Druzzil ability."
	/call LoadSetting HarvestMana string HarvestManaPct "75"
	/call LoadSetting EvacSpell string EvacSpell "Enter the name of your Evac spell here."
	/call AddToggle stuns off return "I will Stop my Chain-Stun Rotation." "I will Start my Chain-Stun Rotation."
	/call LoadSetting ChainStun string ChainStun "Your Chain Stun Spells separated with |. Tears of Marr|Tears of Arlyxir|Tears of Druzzil"
}
/if (${Me.Class.Name.Equal[Berserker]}) {
}
/if (${Me.Class.Name.Equal[Monk]}) {
	/call AddToggle forage off return "I will no longer auto forage." "I will use auto forage now."
}
/if (${Me.Class.Name.Equal[Rogue]}) {
	/call AddToggle forage off return "I will no longer auto forage." "I will use auto forage now."
	/call AddToggle traps off return "Auto Sense Traps is now off." "Auto Sense Traps is now on."
}
/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	/call AddToggle forage off return "I will no longer auto forage." "I will use auto forage now."
	/call AddToggle lich off return "I won't Stay in Skeletion form to regen Mana." "I will stay in Skeletion form to regen Mana."
}
/if (${Me.Class.Name.Equal[Warrior]}) {
	/call AddToggle autoaetaunt off return "I will no longer use ability AETaunt." "I will use ability AETaunt now."
	/call LoadSetting AETaunt string AETaunt(Amount|Radius) "5|50"
	/call AddToggle autoshield off return "I will no longer auto shield anyone." "I will now use auto shield when needed."
	/call LoadSetting Shielding string Shielding(Target|Pct) "|10"
}
/return

Sub Init_Pets_Ini

/declare cmds-PETS string outer Pets:

|:##--------------------------------##:|
|:Declare Pets Variables:|
|:##--------------------------------##:|
/declare SuspendedMinion bool outer
/declare Petheld bool outer


/if (${Me.Class.Name.Equal[Bard]}) {
}
/if (${Me.Class.Name.Equal[Beastlord]}) {
	/call AddToggle pets on return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call AddToggle petona off return "I won't send pet in on assist." "I will send pet in on assist."
	/call AddToggle pethold off return "I will not give pet hold command after combat." "I will give pet hold command after combat."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "Spirit of Sorsha|8|None"
	/call AddToggle petautoshrink off return "I won't automatically Shrink my Pets" "I will automatically Shrink my Pets."
	/call LoadSetting PetHealSetting string PetHeal(Spell|Gem|Pct) "Healing of Sorsha|8|51"
	/call LoadSetting PetMendPct string PetMend(Pct) "25"
	/call LoadSetting PetBuffSetting string PetBuff(Spell|Gem) "Spirit of Rellic|8|Arag's Celerity|7|Growl of the Leopard|6"
}
/if (${Me.Class.Name.Equal[Cleric]}) {
}
/if (${Me.Class.Name.Equal[Druid]}) {
	/call AddToggle pets on return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call AddToggle petona off return "I won't send pet in on assist." "I will send pet in on assist."
	/call AddToggle pethold off return "I will not give pet hold command after combat." "I will give pet hold command after combat."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "Nature Walker's Behest|8|None"
	/call AddToggle petautoshrink off return "I won't automatically Shrink my Pets" "I will automatically Shrink my Pets."
	/call LoadSetting PetHealSetting string PetHeal(Spell|Gem|Pct) "off"
	/call LoadSetting PetBuffSetting string PetBuff(Spell|Gem) "off"
}
/if (${Me.Class.Name.Equal[Enchanter]}) {
	/call AddToggle pets off return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call AddToggle petona off return "I won't send pet in on assist." "I will send pet in on assist."
	/call AddToggle pethold off return "I will not give pet hold command after combat." "I will give pet hold command after combat."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "Aeldorb's Animation|8|Tiny Dagger"
	/call AddToggle petautoshrink off return "I won't automatically Shrink my Pets" "I will automatically Shrink my Pets."
	/call LoadSetting PetHealSetting string PetHeal(Spell|Gem|Pct) "off"
	/call LoadSetting PetBuffSetting string PetBuff(Spell|Gem) "off"
}
/if (${Me.Class.Name.Equal[Magician]}) {
	/call AddToggle pets on return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call AddToggle petona off return "I won't send pet in on assist." "I will send pet in on assist."
	/call AddToggle pethold off return "I will not give pet hold command after combat." "I will give pet hold command after combat."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "Rathe's Son|8|Malachite"
	/call AddToggle petautoshrink off return "I won't automatically Shrink my Pets" "I will automatically Shrink my Pets."
	/call LoadSetting PetHealSetting string PetHeal(Spell|Gem|Pct) "off"
	/call LoadSetting PetMendPct string PetMend(Pct) "25"
	/call LoadSetting PetBuffSetting string PetBuff(Spell|Gem) "off"
}
/if (${Me.Class.Name.Equal[Necromancer]}) {
	/call AddToggle pets on return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call AddToggle petona off return "I won't send pet in on assist." "I will send pet in on assist."
	/call AddToggle pethold off return "I will not give pet hold command after combat." "I will give pet hold command after combat."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "Child of Bertoxxulous|8|Bone Chips"
	/call AddToggle petautoshrink off return "I won't automatically Shrink my Pets" "I will automatically Shrink my Pets."
	/call LoadSetting PetHealSetting string PetHeal(Spell|Gem|Pct) "off"
	/call LoadSetting PetMendPct string PetMend(Pct) "25"
	/call LoadSetting PetBuffSetting string PetBuff(Spell|Gem) "off"
}
/if (${Me.Class.Name.Equal[Paladin]}) {
}
/if (${Me.Class.Name.Equal[Ranger]}) {
}
/if (${Me.Class.Name.Equal[Shaman]}) {
	/call AddToggle pets on return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call AddToggle petona off return "I won't send pet in on assist." "I will send pet in on assist."
	/call AddToggle pethold off return "I will not give pet hold command after combat." "I will give pet hold command after combat."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "True Spirit|8|None"
	/call AddToggle petautoshrink off return "I won't automatically Shrink my Pets" "I will automatically Shrink my Pets."
	/call LoadSetting PetHealSetting string PetHeal(Spell|Gem|Pct) "off"
	/call LoadSetting PetBuffSetting string PetBuff(Spell|Gem) "off"
}
/if (${Me.Class.Name.Equal[Wizard]}) {
	/call AddToggle pets on return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "Greater Familiar|8|None"
}
/if (${Me.Class.Name.Equal[Berserker]}) {
}
/if (${Me.Class.Name.Equal[Monk]}) {
}
/if (${Me.Class.Name.Equal[Rogue]}) {
}
/if (${Me.Class.Name.Equal[Shadow Knight]}) {
	/call AddToggle pets on return "I won't automatically keep my Pet up." "I will automatically keep my Pet up."
	/call AddToggle petona off return "I won't send pet in on assist." "I will send pet in on assist."
	/call AddToggle pethold off return "I will not give pet hold command after combat." "I will give pet hold command after combat."
	/call LoadSetting PetClassSetting string Pet(Spell|Gem|Reagent) "Invoke Death|8|Bone Chips"
	/call AddToggle petautoshrink off return "I won't automatically Shrink my Pets" "I will automatically Shrink my Pets."
	/call LoadSetting PetBuffSetting string PetBuff(Spell|Gem) "off"
}
/if (${Me.Class.Name.Equal[Warrior]}) {
}

/return

Sub Init_Healer_Ini

/declare cmds-HEALER string outer Healer:
|: --------------
|: -- For each command
|: -- /call AddCommand "Command Section" "Command Phrase" "Called Sub"
|: -- Command Section - where the command will be listed in response to the cmd phrase
|: -- Command Phrase to trigger bot - End User can change to suit prefferences
|: -- Called Sub - Routine to execute in response to Command Phrase
|: --------------

|:This sets genbot's avaiable commands with Sub Command_NamesBelow:|
/call AddCommands watchtarget cheals


|:##--------------------------------##:|
|:Declare Healer Variables:|
|:##--------------------------------##:|
/declare HealTargets[21] int outer 0
/declare LowHealthCheck int outer 0
/declare WatchTargetList string outer

|:##--------------------------------##:|
|:Declare Timers:|
|:##--------------------------------##:|
|: For robot_healer.inc
/declare CastMsgTimerHealer_1 timer outer
/declare CastMsgTimerHealer_2 timer outer
/declare CastMsgTimerHealer_3 timer outer
|: For robot_combat.inc
/declare CastMsgTimerCombat_1 timer outer
|: For robot_core.inc
/declare CastMsgTimerCore_1 timer outer

|:##--------------------------------##:|
|:Load settings & Toggles:|
|:##--------------------------------##:|
/if (${Me.Class.Name.Equal[Cleric]}) {
	/call AddToggle doheal on return "I will not heal anyone unless commanded." "I will watch and cast heal spells as necessary."
	/call LoadSetting CasterSetting string Caster(Spell|Gem|Pct) "Supernal Remedy|8|80"
	/call LoadSetting TankSetting string Tank(Spell|Gem|Pct) "Holy Light|8|75"

	/call AddToggle patchheal off return "I'm not a patch Healer." "I'm a patch Healer."
	/call LoadSetting PatchSetting string Patch(Spell|Gem|Pct) "Supernal Light|8|55"
	
	/call AddToggle groupheal off return "I will not use group heals." "I will use group heals."
	/call LoadSetting GroupSetting string Group(Spell|Gem|Pct|Amount) "Word of Vigor|8|81|3"

	/call AddToggle petsheal off return "I will not heal the pets." "I will heal the pets."
	/call LoadSetting PetSetting string Pet(Spell|Gem|Pct) "Heal Spell|8|51"

	/call AddToggle autoregen off return "I will not use Celestial Regeneration." "I will use my Celestial Regeneration."
	/call LoadSetting CelestialSetting string CelestialRegen(Pct|Amount) "35|4"
	
	/call AddToggle chainheals noini return "I will Stop Auto Chain Healing." "I will Start Auto Chain Healing."
	
}
/if (${Me.Class.Name.Equal[Druid]}) {
	/call AddToggle doheal on return "I will not heal anyone unless commanded." "I will watch and cast heal spells as necessary."
	/call LoadSetting CasterSetting string Caster(Spell|Gem|Pct) "Sylvan Infusion|8|75"
	/call LoadSetting TankSetting string Tank(Spell|Gem|Pct) "Karana's Renewal|8|85"

	/call AddToggle patchheal off return "I'm not a patch Healer." "I'm a patch Healer."
	/call LoadSetting PatchSetting string Patch(Spell|Gem|Pct) "Sylvan Infusion|8|45"

	/call AddToggle petsheal off return "I will not heal the pets." "I will heal the pets."
	/call LoadSetting PetSetting string Pet(Spell|Gem|Pct) "Heal Spell|8|51"

	/call AddToggle chainheals noini return "I will Stop Auto Chain Healing." "I will Start Auto Chain Healing."
	
}
/if (${Me.Class.Name.Equal[Shaman]}) {
	/call AddToggle doheal on return "I will not heal anyone unless commanded." "I will watch and cast heal spells as necessary."
	/call LoadSetting CasterSetting string Caster(Spell|Gem|Pct) "Daluda's Mending|8|75"

	/call LoadSetting TankSetting string Tank(Spell|Gem|Pct) "Daluda's Mending|8|65"

	/call AddToggle patchheal off return "I'm not a patch Healer." "I'm a patch Healer."
	/call LoadSetting PatchSetting string Patch(Spell|Gem|Pct) "Daluda's Mending|8|45"

	/call AddToggle petsheal off return "I will not heal the pets." "I will heal the pets."
	/call LoadSetting PetSetting string Pet(Spell|Gem|Pct) "Heal Spell|8|51"

	/call AddToggle chainheals noini return "I will Stop Auto Chain Healing." "I will Start Auto Chain Healing."

}
/if (${Me.Class.Name.Equal[Paladin]}) {
	/call AddToggle doheal on return "I will not heal anyone unless commanded." "I will watch and cast heal spells as necessary."
	
	/call AddToggle groupheal off return "I will not use group heals." "I will use group heals."
	/call LoadSetting GroupSetting string Group(Spell|Gem|Pct|Amount) "Wave of Trushar|8|81|3"

	/call AddToggle patchheal on return "I'm not a patch Healer." "I'm a patch Healer."
	/call LoadSetting PatchSetting string Patch(Spell|Gem|Pct) "Light of Order|8|75"

	/call AddToggle petsheal off return "I will not heal the pets." "I will heal the pets."
	/call LoadSetting PetSetting string Pet(Spell|Gem|Pct) "Light of Order|8|51"
}
/if (${Me.Class.Name.Equal[Ranger]}) {
	/call AddToggle doheal on return "I will not heal anyone unless commanded." "I will watch and cast heal spells as necessary."
	/call AddToggle patchheal on return "I'm not a patch Healer." "I'm a patch Healer."
	/call LoadSetting PatchSetting string Patch(Spell|Gem|Pct) "Sylvan Light|8|75"
}
/if (${Me.Class.Name.Equal[Beastlord]}) {
	/call AddToggle doheal off return "I will not heal anyone unless commanded." "I will watch and cast heal spells as necessary."
	/call AddToggle patchheal off return "I'm not a patch Healer." "I'm a patch Healer."
	/call LoadSetting PatchSetting string Patch(Spell|Gem|Pct) "Trushar's Mending|8|75"
}
/if (${Me.Class.Name.Equal[Beastlord]} || ${Me.Class.Name.Equal[Magician]} || ${Me.Class.Name.Equal[Necromancer]} || ${Me.Class.Name.Equal[Shadow knight]}) {
	/call AddToggle petsheal off return "I will not heal the pets." "I will heal the pets."
	/call LoadSetting PetSetting string Pet(Spell|Gem|Pct) "Heal Spell|8|51"
}
/if (${Me.Class.Name.Equal[Cleric]} || ${Me.Class.Name.Equal[Druid]} || ${Me.Class.Name.Equal[Paladin]} || ${Me.Class.Name.Equal[Shaman]} || ${Me.Class.Name.Equal[Ranger]} || ${Me.Class.Name.Equal[Beastlord]}) {
	/call LoadSetting PriorityTargets string PriorityTargets "List of Target(s) to heal first seperated by |"
	/call LoadSetting TankList string TankList "Warrior|Shadow Knight|Paladin|Monk|Beastlord|Ranger|Rogue|Berserker|Bard"
	/call LoadSetting CasterList string CasterList "Necromancer|Wizard|Enchanter|Magician|Druid|Cleric|Shaman"
}
/if (${Me.Class.Name.Equal[Necromancer]}) /call LoadSetting HealerList string HealerList "Cleric|Druid|Shaman"
/return


Sub Init_cParams_Ini

/declare cmds-CPARAMS string outer cParams:

|: Healer Section to Change Genbot Settings.
/call AddCommands set

|: Core Section to Change Genbot Settings.
/call AddCommands varset rset mrset chainlist

/return

Sub Init_SpawnTracker_Ini
/call AddToggle spawntracker off return "BOD Spawntime Database updater [Stopped]." "BOD Spawntime Database updater [Started]."

|:-=-=-=-=-=-= (Add to Delcare_TrackerSection) =-=-=-=-=-=--

/call LoadSetting HostName_Insert string HostName_Insert "The Database Address to Connect to."
/call LoadSetting UserName_Insert string UserName_Insert "The UserName for the Database."
/call LoadSetting PassWord_Insert string PassWord_Insert "The Password for the Database."
/call LoadSetting DataBase_Insert string DataBase_Insert "The Database Table to Select."

|:Current client Timezone.
/call LoadSetting Client_TimeZone string Client_TimeZone "Enter Your Current Timezone."

|:The List to Auto Track if dead, Add to Database.
/call LoadSetting Tracklist string Tracklist "a List of Mobs seperated by | to auto update Respawn Timer."

|:The numbers of times to Beep when Insert Death/Spawn into ini. Ex. 2
/call LoadSetting SpawnTracker_Alert string SpawnTracker_Alert "The numbers of times to Beep when Insert Death/Spawn into ini. Ex. 2"

|:Have bot Automatically Camp out Once Done Tracking.
/call LoadSetting Tacker_AutoCamp string Tacker_AutoCamp "Have bot Automatically Camp out Once Done Tracking. [ 1=ON OR OFF ] [Seperated by | ] When [Spawn OR Death] AND [Seperated by | ] Amount Tracking [The # Spawns tracking] to camp. Ex. 1|Death|1 OR 1|Spawn|3 OR OFF"

|:Convert Spaces to Underscore 2 SearchDB.
|:/varset Tracklist ${Tracklist.Replace[ ,_]}

|:Spawn Tracker Killed List.
/declare Killed_List string outer
/declare Spawned_List string outer
/declare SpawnTracker_Camp string outer 0

/return

Sub Init_NinjaLoot_Ini
	/call LoadSetting DeleteMe DeleteMe NinjaLoot_Looters "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"
	/call LoadSetting DeleteMe DeleteMe MinItemValue(Platinum) "|** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|"

	/call LoadSetting INFO Comments ninjaloot "This will Turn On/Off the Auto loot Corpse Feature." |: Ini Comments Line
	/call AddToggle ninjaloot off return "I will not auto NinjaLoot Corpses no more." "I will auto NinjaLoot Corpses Now."

	/call LoadSetting INFO Comments ninjabypass "This will stop macro from turnning off ninjaloot when full inventory." |: Ini Comments Line
	/call AddToggle ninjabypass off return "I will not loot corpses if Inventory full." "I will loot Corpses Now even if Inventory full."
	
	/call LoadSetting INFO Comments ninjalink "This will stop macro from auto looting items off corpses, Link them only." |: Ini Comments Line
	/call AddToggle ninjalink off return "I will not only link items from corpses." "I will only link items from corpses."

	/call LoadSetting INFO Comments NinjaLoot_Alert "The numbers of times to Beep when inventory Full. Ex. 3" |: Ini Comments Line
	/call LoadSetting NinjaLoot_Alert string NinjaLoot_Alert "The numbers of times to Beep when inventory Full. Ex. 3"

	/call LoadSetting INFO Comments Seek_Radius "The Distance NinjaLoot will Search for a Corpse." |: Ini Comments Line
	/call LoadSetting Seek_Radius string Seek_Radius "The Distance NinjaLoot will Search for a Corpse."
/return

|:----------------------------------------------------------------------
|: Init_Shortcuts: to load in shortcuts from the .ini file
|:----------------------------------------------------------------------

Sub Init_Shortcuts_Ini

/if (!${Defined[GenFor]}) /declare GenFor int local 1
/declare Short string local 0

/if (!${Defined[Shortcutlist]}) /declare Shortcutlist string outer
/varset Shortcutlist ${Ini[${BOT_INI},SHORTCUTS,,Undefined]}
/if (${Shortcutlist.NotEqual[Undefined||]}) {
	:shortcuts
	/if (${Shortcutlist.Arg[${GenFor},|].Length}) {
		/varset Short ${Shortcutlist.Arg[${GenFor},|].Lower}
		 |:string VarName, string VarType, string KeyName, string DefaultValue
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ${Short} shortcuts ${Short} None
		/varcalc GenFor ${GenFor}+1
		/goto :shortcuts
	}
} else {
	/if (${Me.Class.Name.Equal[Bard]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS Resist "twist Psalm of Veeshan"
		/ini ${BOT_INI} SHORTCUTS Reflect "twist Dark Echo"
	}
	/if (${Me.Class.Name.Equal[Beastlord]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS SD "snt Spiritual Dominion @{NameS}"
		/ini ${BOT_INI} SHORTCUTS SV "snt Spiritual Vigor @{NameS}"
		/ini ${BOT_INI} SHORTCUTS ToA "snt Talisman of Altuna @{NameS}"
		/ini ${BOT_INI} SHORTCUTS BuffList "/gb SV|SD|ToA"
		/ini ${BOT_INI} SHORTCUTS BuffParty "/keypress F1|BuffList|/keypress F2|BuffList|/keypress F3|BuffList|/keypress F4|BuffList|/keypress F5|BuffList|/keypress F6|BuffList"
	}
	/if (${Me.Class.Name.Equal[Cleric]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS HoV "snt Hand of Virtue @{NameS}"
		/ini ${BOT_INI} SHORTCUTS HoC "snt Hand of Conviction @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Virtue "snt Virtue @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Kazad "snt Kazad's Mark @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Bali "snt Balikor's Mark @{NameS}"
		/ini ${BOT_INI} SHORTCUTS WoG "snt Ward of Gallantry @{NameS}"
		/ini ${BOT_INI} SHORTCUTS WoV "snt Ward of Valiance @{NameS}"
		/ini ${BOT_INI} SHORTCUTS BoR "snt Blessing of Reverence @{NameS}"
		/ini ${BOT_INI} SHORTCUTS AoR "snt Aura of Reverence @{NameS}"
		/ini ${BOT_INI} SHORTCUTS AoD "snt Aura of Devotion @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Hot "snt Pious Elixir @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Hotg "snt Elixir of Divinity @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Cheal "snt Complete Heal @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Healt "snt Pious Light @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Healc "snt Pious Remedy @{NameS}"
		/ini ${BOT_INI} SHORTCUTS gHeal "snt Word of Replenishment @{NameS}"
		/ini ${BOT_INI} SHORTCUTS AAHoT "alt Celestial Regeneration"
		/ini ${BOT_INI} SHORTCUTS RGC "snt Remove Greater Curse @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Cure "snt Antidote @{NameS}"
		/ini ${BOT_INI} SHORTCUTS DI "snt Divine Intervention @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Buffme "Bali|AoD"
		/ini ${BOT_INI} SHORTCUTS BuffParty "/keypress F1|BuffList|/keypress F2|BuffList|/keypress F3|BuffList|/keypress F4|BuffList|/keypress F5|BuffList|/keypress F6|BuffList"
	}
	/if (${Me.Class.Name.Equal[Druid]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS BoT9 "snt Blessing of the Nine @{NameS}"
		/ini ${BOT_INI} SHORTCUTS PoT9 "snt Protection of the Nine @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Regen "snt Blessing of Replenishment @{NameS}"
		/ini ${BOT_INI} SHORTCUTS sRegen "snt Replenishment @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Heal "snt Nature's Touch @{NameS}"
		/ini ${BOT_INI} SHORTCUTS CoS "snt Circle of Seasons @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Str "snt Nature's Might @{NameS}"
		/ini ${BOT_INI} SHORTCUTS DS "snt Legacy of Bracke @{NameS}"
		/ini ${BOT_INI} SHORTCUTS FOE "snt Flight of Eagles @{NameS}"
		/ini ${BOT_INI} SHORTCUTS GroupWolf "snt Share Form of the Great Wolf @{NameS}"
		/ini ${BOT_INI} SHORTCUTS GroupInvis "snt Foliage Shield @{NameS}"
		/ini ${BOT_INI} SHORTCUTS BuffList "/gb HPSBuff|HPSRegen"
		/ini ${BOT_INI} SHORTCUTS BuffParty "/keypress F1|BuffList|/keypress F2|BuffList|/keypress F3|BuffList|/keypress F4|BuffList|/keypress F5|BuffList|/keypress F6|BuffList"
	}
	/if (${Me.Class.Name.Equal[Enchanter]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS VOQ "snt Voice of Quellious @{NameS}"
		/ini ${BOT_INI} SHORTCUTS VQ "snt Vallon's Quickening @{NameS}"
		/ini ${BOT_INI} SHORTCUTS GOD "snt Guard of Druzzil @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Crow "snt Night's Dark Terror @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Imp "snt Trickster's Augmentation @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Wolf "snt Boon of the Garou @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Lev "snt Levitation @{NameS}"
		/ini ${BOT_INI} SHORTCUTS EB "snt Everlasting Breath @{NameS}"
	}
	/if (${Me.Class.Name.Equal[Magician]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS DSSBuff "snt Flameshield of Ro @{NameS}"
		/ini ${BOT_INI} SHORTCUTS DS "snt Maelstrom of Ro @{NameS}"
	}
	/if (${Me.Class.Name.Equal[Necromancer]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS HPFlow "snt Shadowbond @{NameS}"
		/ini ${BOT_INI} SHORTCUTS ManaFlow "snt Sedulous Subversion @{NameS}"
		/ini ${BOT_INI} SHORTCUTS DMF "snt Dead Men Floating @{NameS}"
		/ini ${BOT_INI} SHORTCUTS IVU "snt Invisibility versus Undead @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Corpse "snt Conjure Corpse @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Sac "snt Sacrifice @{NameS}"
	}
	/if (${Me.Class.Name.Equal[Paladin]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS BSS "snt Brell's Stalwart Shield @{NameS}"
	}
	/if (${Me.Class.Name.Equal[Ranger]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS SOT "snt Strength of Tunare @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Tunare "snt Strength of Tunare @{NameS}"
		/ini ${BOT_INI} SHORTCUTS SOTP "snt Spirit of the Predator @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Pred "snt Spirit of the Predator @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Rathe "snt Call of the Rathe @{NameS}"
		/ini ${BOT_INI} SHORTCUTS SoE "snt Spirit of Eagle @{NameS}"
		/ini ${BOT_INI} SHORTCUTS SoW "snt Spirit of Wolf @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Regen "snt Regrowth @{NameS}"
		/ini ${BOT_INI} SHORTCUTS DS "snt Shield of Spikes @{NameS}"
		/ini ${BOT_INI} SHORTCUTS BuffList "COTR|HPSRegen"
		/ini ${BOT_INI} SHORTCUTS BuffParty "/keypress F1|BuffList|/keypress F2|BuffList|/keypress F3|BuffList|/keypress F4|BuffList|/keypress F5|BuffList|/keypress F6|BuffList"
	}
	/if (${Me.Class.Name.Equal[Shaman]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS Fo7 "snt Focus of the Seventh @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Heal "snt Daluda's Mending @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Focus "snt Focus of Soul @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Haste "snt Talisman of Celerity @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Billy "snt Spirit of Bih`li @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Regen "snt Blessing of Replenishment @{NameS}"
		/ini ${BOT_INI} SHORTCUTS HoT "snt Breath of Thrushar @{NameS}"
		/ini ${BOT_INI} SHORTCUTS FA "snt Ferine Avatar @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Shrink "snt Tiny Terror @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Agi "snt Talisman of the Wrulan @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Dex "snt Talisman of the Raptor @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Sta "snt Talisman of the Boar @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Str "snt Talisman of the Diaku @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Tribunal "snt Talisman of the Tribunal @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Jag "snt Spirit of the Jaguar @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Shrink "snt Shrink @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Tiny "snt Tiny Terror @{NameS}"
		/ini ${BOT_INI} SHORTCUTS GroupShrink "snt Tiny Terror @{NameS}"
		/ini ${BOT_INI} SHORTCUTS RGC "snt Remove Greater Curse @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Cure "snt Disinfecting Aura @{NameS}"
		/ini ${BOT_INI} SHORTCUTS AG "snt Ancestral Guard @{NameS}"
		/ini ${BOT_INI} SHORTCUTS BuffList "HPSBuff|HPSRegen|StatsBuff|AG"
		/ini ${BOT_INI} SHORTCUTS BuffParty "/keypress F1|BuffList|/keypress F2|BuffList|/keypress F3|BuffList|/keypress F4|BuffList|/keypress F5|BuffList|/keypress F6|BuffList"
	}
	/if (${Me.Class.Name.Equal[Wizard]}) {
		/ini ${BOT_INI} SHORTCUTS default "/echo Put yer shortcuts in your .ini file!"
		/ini ${BOT_INI} SHORTCUTS Barin "snt Barindu Portal @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Nati "snt Natimbi Portal @{NameS}"
		/ini ${BOT_INI} SHORTCUTS POK "snt Knowledge Portal @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Nexus "snt Nexus Portal @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Teleport "snt Teleport @{NameS}"
		/ini ${BOT_INI} SHORTCUTS tBarin "snt Translocate Barindu @{NameS}"
		/ini ${BOT_INI} SHORTCUTS tNati "snt Translocate Natimbi @{NameS}"
		/ini ${BOT_INI} SHORTCUTS tPOK "snt Translocate Knowledge @{NameS}"
		/ini ${BOT_INI} SHORTCUTS tNexus "snt Translocate Nexus @{NameS}"
		/ini ${BOT_INI} SHORTCUTS Absorb "snt Spellshield @{NameS}"
		/ini ${BOT_INI} SHORTCUTS MSDMG "snt Protection of Calrena @{NameS}"
		/ini ${BOT_INI} SHORTCUTS BuffList "Absorb|MSDMG"
		/ini ${BOT_INI} SHORTCUTS BuffParty "keypress F1|BuffList|/keypress F2|BuffList|/keypress F3|BuffList|/keypress F4|BuffList|/keypress F5|BuffList|/keypress F6|BuffList"
	}
	/if (${Me.Class.Name.Equal[Shadow Knight]}) {
		/ini ${BOT_INI} SHORTCUTS Voice "snt Voice of Thule @{NameS}"
	}
	/if (${Me.Class.Name.Equal[Berserker]} || ${Me.Class.Name.Equal[Monk]} || ${Me.Class.Name.Equal[Rogue]} || ${Me.Class.Name.Equal[Warrior]}) {
	/return
}
}
/return

Sub Init_SmoothMoves_Ini

/declare cmds-SMOOTHMOVES string outer SmoothMoves:

|:Killians Routes
/call AddCommands route goto click run

/return