|** 
	Zenith_Core Subroutine Line Index 
	|: Line:19 	 SUB - [ShortCut]
	|: Line:60 	 SUB - [AddCommands]
	|: Line:78 	 SUB - [AddToggle]
	|: Line:179	 SUB - [SetToggle]
	|: Line:179	 SUB - [LoadSetting]
	|: Line:332	 SUB - [CollapseParams]
	|: Line:373	 SUB - [ListDelbyArg]
	|: Line:388	 SUB - [ListReplacebyArg]
	|: Line:403	 SUB - [StringReplaceAll]
	|: Line:421	 SUB - [ListDelbyName]
	|: Line:438	 SUB - [ListAppendElement]
	|: Line:452	 SUB - [ListPrependElement]
	|: Line:466	 SUB - [ListFindStringArg]
	|: Line:473	 SUB - [array2String]
**|
|**
-------------------------------------------------------------------------
- [Core] Events
-------------------------------------------------------------------------
**|
|**
#chat guild
#chat group
#chat tell
#chat say
#chat shout
#chat group**|
|: #chat group
|: #chat tell
#event SelfEcho   	 	 "[MQ2] Zenith #1#"
|: MQ2EQBC Chat Channel
#event EQBCSAY      	 "<#1#> #2#"
#event EQBCSAY     	 	 "[#1#(#*#)] #2#"
|**
-------------------------------------------------------------------------
	Zenith BOT Debug Spew To [Echo,INI] to help debug the macro.
-------------------------------------------------------------------------
**|
Sub Debug_Spew(string Debug_Msg, string Debug_Section, string MacroParams, string Subrountine, string SubCurrentLine, int MemoryUsage, int RunTime, string MacroName, string NoReplace, string LoopSpew)
	|: DebugError = (@{Subrountine.Left[@{Math.Calc[@{Subrountine.Find[(]}-1]}]}):@{SubCurrentLine}
	|**
		/echo Debug_Message:     ${Debug_Msg}
		/echo Debug_Section:     ${Debug_Section}
		/echo Debug_MacroParams: ${MacroParams}
		/echo Sub_Rountine:      ${Subrountine}
		/echo Cur_Line:          ${SubCurrentLine}
		/echo MemUsage:          ${MemoryUsage}mb
		/echo RunTime:           ${RunTime}
		/echo MacroName:         ${MacroName}
	**|
	/if (!${Defined[tmpDebugError]}) /declare tmpDebugError string local ${DebugError}
	/if (!${Defined[tmpDebugErrorFull]}) /declare tmpDebugErrorFull string local ${DebugErrorFull}
	/if (!${Defined[DebugList]}) /declare DebugList string local ${Ini[${BOT_INI},CORE,DebugList]}
	/if (!${Defined[x]}) /declare x int local
	/if (!${Defined[i]}) /declare i int local
	/for i 1 to ${Math.Calc[${DebugList.Count[|]}+1]}
		/for x 1 to ${Math.Calc[${Debug_Section.Count[,]}+1]}
			/if (${Bool[${DebugList.Arg[${i},|].Upper.Equal[${Debug_Section.Arg[${x},,].Upper}]}]}) {
				/if (${Bool[${NoReplace}]}) {
					/echo |- ${tmpDebugError.Replace[@,$]} ${Debug_Msg}
				} else {
					/echo |- ${tmpDebugError.Replace[@,$]} ${Debug_Msg.Replace[@,$]}
				}
				/if (${Bool[${DebugList.Arg[${i},|].Upper.Equal[FULL]}]}) {
					/if (${Bool[${NoReplace}]}) {
						/ini "${ERRORLOG_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_ErrorLogs" "${Me.CleanName}" "${tmpDebugErrorFull.Replace[@,$]}${LoopSpew}" "${Debug_Msg}"
					} else {
						/ini "${ERRORLOG_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_ErrorLogs" "${Me.CleanName}" "${tmpDebugErrorFull.Replace[@,$]}${LoopSpew}" "${Debug_Msg.Replace[@,$]}"
					}
				} else {
					/if (${Bool[${NoReplace}]}) {
						/ini "${ERRORLOG_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_ErrorLogs" "${Me.CleanName}" "${tmpDebugError.Replace[@,$]}${LoopSpew}" "${Debug_Msg}"
					} else {
						/ini "${ERRORLOG_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_ErrorLogs" "${Me.CleanName}" "${tmpDebugError.Replace[@,$]}${LoopSpew}" "${Debug_Msg.Replace[@,$]}"
					}
				}
			}
		/next x
	/next i
/return
|**
-------------------------------------------------------------------------
	INITIALIZATION Zenith BOT CONTROL SUBROUTINES
-------------------------------------------------------------------------
**|
|:-----------------------------------------------------------------------
|: Event_Chat: This Section Fixes Spaces/Commas in ChatSenders Name, Removes Linked Items Code leaving just item text name.
|: Check is Sender is able to Control Bot, also Checks for BOT Control Password.
|: Check for Specific Bot/Class Commands to do. E.G; BotName,Enc,Enchanter,Melees,Priests,Casters,Hybirds,Hybrids,PetClass,Group#,Leaders
|: Once all Verified Call ExecCommand With Commands.
|:-----------------------------------------------------------------------
Sub Event_Chat(string ChatType,string ChatSender,string ChatText)
	|: Correct ChatSender if Space Found.
	/if (${ChatSender.Left[1].Compare[ ]} < 0) {
		/varset Sender ${ChatSender.Right[-2].Left[-1]}
	} else {
		/varset Sender ${ChatSender}
	}
	|: Check Sender is in Same Zone. [ID, InZone, Distance]
	/if (!${Bool[${Spawn[pc ${Sender}].ID}]}) {
		/if (!${Defined[ParamLoop]}) /declare ParamLoop int local
		/for ParamLoop 1 to ${Math.Calc[${CrossZoneCommands.Count[|]}+1]}
			/if (${ChatText.Arg[${ParamLoop}, ].NotEqual[${CrossZoneCommands}]}) /return
		/next ParamLoop
	}
	|: Fix Mysterious Comma in ChatText.
	/if (${ChatText.Left[1].Equal[']}) {
		/varset ChatText ${ChatText.Right[-1]}
	}
	|: Fix Item Links [0003EA000000000000000000000000000000000000000000932D4F15Cloth Veil]
	/if (${ChatText.Find[000]}) {
		|:/varset ChatText ${ChatText.Right[-45]}
		|:/varset ChatText ${ChatText.Right[${Math.Calc[${ChatText.Length} - (57+5)]}].Left[-1]}
		/varset ChatText ${ChatText.Right[${Math.Calc[${ChatText.Length} - (57)]}].Left[-1]}
	}
	|: |: ${Select[${CurrCommand},${cmds-CHRotation.Replace[|,,]}]} && ${Toggle-cheals} && ${Select[${Spawn[${Sender}].Guild.Replace[ ,_]},${Me.Guild.Replace[ ,_]}]} || 
	|: Check [PublicCommands] Commands Allowed by all. ${Select[${Spawn[${Sender}].Guild.Replace[ ,_]},${Me.Guild.Replace[ ,_]}]} || ${Spawn[${Sender}].ID}
	/if (${PublicCommands.NotEqual[${PublicCommands-DefaultValue}]}) {
		/if (!${Defined[ParamLoop]}) /declare ParamLoop int local
		/for ParamLoop 1 to ${Math.Calc[${PublicCommands.Count[|]}+1]}
			/if (${ChatText.Find[${PublicCommands.Arg[${ParamLoop}]}]} || ${Toggle-dopublic} || ${Sender.Find[Morte]} || ${Select[${Sender.Left[5]},Morte,Morta,Demon,Spiri,Scura,Coopb]}) {
				/goto :SkipMasters			
			}
		/next ParamLoop
	}
	|: Check Command Sender is Allowed to Command Bot, If not Cancel Given Command.
	/if (!${Bool[${Select[${Sender},${Masters.Replace[|,,]},${EQBC.Names.Replace[ ,,]},${Me.Name}]}]}) {
		/return
	}
	:SkipMasters
	|: IF Bot [Paused] only Listen to Pause Toggle On/Off Command.
	/if (${Toggle-pause} && !${Bool[${ChatText.Find[pause]}]}) {
		/return
	}
	|: IF ChatText Find [[ChatOut]-] Then Return its just a Message not a Command.
	/if (${Bool[${ChatText.Find[[ChatOut]-]}]} || ${Bool[${ChatText.Arg[1].Equal[[ChatOut]-]}]}) {
		/return
	}
	|: Allow Anyone with BOT Password to take Temporary Control of Bot.
	/if (${Bool[${ChatText.Find[${ControlPass}]}]}) /call AddTempMaster ${Sender}
	|: Relay Tells when Bot Receives a Message.
	/if (${Toggle-relaytells} && ${ChatType.Equal[tell]}) {
			/call ChatOut CORE "[+y+][${Time.Time12}] [+r+]${ChatSender} [+w+]Told me: [+y+]${ChatText}" "0"
	}
	|: Check IF Bot Listening in Channel Sending Command.
	/if (${Bool[${Select[${ChatType.Upper},${ListenInChannels.Upper}]}]}) {
		|: Remove Bots Name from Command, Continue Command Given.
		/if (${ChatText.Arg[1].Lower.Equal[${Me.CleanName.Lower}]} || ${ChatText.Arg[1].Lower.Equal[${Me.Surname}]}) {
			/if (!${Defined[NameLength]}) /declare NameLength int local ${ChatText.Arg[1].Length}
			/varcalc NameLength ${NameLength}+1
			/varset ChatText ${ChatText.Right[-${NameLength}]}
		} else {
			|: Cancel Bot Command Because Bot Name not Given, CheckName is Enabled.
			/if (${Toggle-checkname}) /return
			|: Check List of Command Bot will Ignore.
			/if (${Bool[${IgnGroupList.NotEqual[${IgnGroupList-DefaultValue}]}]}) {
				/if (!${Defined[GenString]}) /declare GenString string local
				/varset GenString |${IgnGroupList}|
				/if (${GenString.Find[|${ChatText.Arg[1]}|]}) /return
			}
		}
		|:Check for Specific Bot/Class Commands to do.
		|:Set Class Types: Melee(mClassTypes), Priest(pClassTypes), Caster(cClassTypes), Hybird(hClassTypes), PetClass(PetClassTypes)
		/if (!${Defined[ParamLoop]}) /declare ParamLoop int local
		/if (!${Defined[FindBot]}) /declare FindBot int local 0
		:CheckSpecBot
		/for ParamLoop 1 to ${Math.Calc[${ChatText.Count[ ]}+1].Int}
			|: If Find (Me Class Shortname or Longname)
			/if (${ChatText.Arg[${ParamLoop},].Lower.Equal[${Me.Class.ShortName.Lower}]} || ${ChatText.Arg[${ParamLoop},].Lower.Equal[${Me.Class.Name.Lower}]}) {
				/if (${Select[${Me.Class.ShortName.Lower},${mClassTypes.Lower},${pClassTypes.Lower},${cClassTypes.Lower},${hClassTypes.Lower}]}) {
					/if (${ChatText.Arg[${ParamLoop},].Lower.Equal[${Me.Class.ShortName.Lower}]}) /varset ChatText ${ChatText.Lower.Replace[${Me.Class.ShortName.Lower} ,]}
					/if (${ChatText.Arg[${ParamLoop},].Lower.Equal[${Me.Class.Name.Lower}]}) /varset ChatText ${ChatText.Lower.Replace[${Me.Class.Name.Lower} ,]}
					/varset FindBot 1
				}
			}
			|: If Find (Melee,Priest,Caster,Hybird,PetClass) true,on,1,yes,false,off,0,no
			/if (${ChatText.Arg[${ParamLoop},].Lower.Equal[melees]} || ${ChatText.Arg[${ParamLoop},].Lower.Equal[priests]} || ${ChatText.Arg[${ParamLoop},].Lower.Equal[casters]}  || ${ChatText.Arg[${ParamLoop},].Lower.Equal[hybirds]} || ${ChatText.Arg[${ParamLoop},].Lower.Equal[hybrids]} || ${ChatText.Arg[${ParamLoop},].Lower.Equal[petclass]}) {
				/if (${ChatText.Arg[${ParamLoop},].Lower.Equal[melees]} && ${Select[${Me.Class.ShortName.Lower},${mClassTypes.Lower}]}) {
					|:Melees
					/varset ChatText ${ChatText.Lower.Replace[melees ,]}
					/varset FindBot 1
				} else /if (${ChatText.Arg[${ParamLoop},].Lower.Equal[priests]} && ${Select[${Me.Class.ShortName.Lower},${pClassTypes.Lower}]}) {
					|:Priests
					/varset ChatText ${ChatText.Lower.Replace[priests ,]}
					/varset FindBot 1
				} else /if (${ChatText.Arg[${ParamLoop},].Lower.Equal[casters]} && ${Select[${Me.Class.ShortName.Lower},${cClassTypes.Lower}]}) {
					|:Casters
					/varset ChatText ${ChatText.Lower.Replace[casters ,]}
					/varset FindBot 1
				} else /if ((${ChatText.Arg[${ParamLoop},].Lower.Equal[hybirds]} || ${ChatText.Arg[${ParamLoop},].Lower.Equal[hybrids]}) && ${Select[${Me.Class.ShortName.Lower},${hClassTypes.Lower}]}) {
					|:Hybirds | Hybrids
					/if (${ChatText.Find[hybirds]}) {
						/varset ChatText ${ChatText.Lower.Replace[hybirds ,]}
					} else {
						/varset ChatText ${ChatText.Lower.Replace[hybrids ,]}
					}
					/varset FindBot 1
				} else /if (${ChatText.Arg[${ParamLoop},].Lower.Equal[petclass]} && ${Select[${Me.Class.ShortName.Lower},${PetClassTypes.Lower}]}) {
					|:Pet Classes
					/varset ChatText ${ChatText.Lower.Replace[petclass ,]}
					/varset FindBot 1
				}
			}
			|: If Find (Group.Leader)
			/if (${ChatText.Arg[${ParamLoop},].Lower.Equal[leaders]}) {
				|:Group Leaders
				/if (${Bool[${Select[${Group.Leader},${Me.CleanName}]}]}) {
					/varset ChatText ${ChatText.Lower.Replace[leaders ,]}
					/varset FindBot 1
				}
			}
			|: Find My Group Number
			/if (!${Defined[GroupLeaderOrder]}) /declare GroupLeaderOrder string local
			/if (!${Defined[GroupNum]}) /declare GroupNum string local
			/if (!${Defined[GenFor]}) /declare GenFor int local
			/varset GroupNum ${ChatText.Arg[${ParamLoop},].Right[-5]}
			/if (${ChatText.Arg[${ParamLoop},].Lower.Left[5].Equal[Group]}) {
				/if (${GrpLeadersOrder.Equal[${GrpLeadersOrder-DefaultValue}]}) {
					/for GenFor 1 to ${Math.Calc[${NetBots.Client.Count[ ]}+1].Int}
						/if (${Bool[${NetBots[${NetBots.Client[${GenFor}]}].Grouped}]}) {
							/if (${Bool[${NetBots[${NetBots.Client[${GenFor}]}].Leader}]}) {
								/if (!${GroupLeaderOrder.Find[${NetBots[${NetBots.Client[${GenFor}]}].Leader}]}) {
									/varset GroupLeaderOrder ${GroupLeaderOrder} ${NetBots[${NetBots.Client[${GenFor}]}].Leader}
								}
							}
						}
					/next GenFor
				}
			} else {
				/varset GroupLeaderOrder ${GrpLeadersOrder.Replace[|, ]}
			}
			|: Group Leaders
			/if (${Me.Grouped} && ${Bool[${Select[${Group.Leader},${GroupLeaderOrder.Arg[${GroupNum}].Replace[ ,,]}]}]}) {
				/varset ChatText ${ChatText.Lower.Replace[group${GroupNum} ,]}
				/varset FindBot 1
			}
		/next ParamLoop
		|: Cancel Bot Command Because Specific Bot Check Failed.
		/if (${Select[${ChatText.Arg[1].Lower},${mClassTypes.Lower},${pClassTypes.Lower},${cClassTypes.Lower},${hClassTypes.Lower}]} || ${Select[${ChatText.Arg[1].Lower},melees,priests,casters,hybirds,hybrids,petclass,leaders,group1,group2,group3,group4,group5,group6,group7,group8,group9]}) {
			/if (${Select[${ChatText.Arg[2].Lower},${mClassTypes.Lower},${pClassTypes.Lower},${cClassTypes.Lower},${hClassTypes.Lower}]} || ${Select[${ChatText.Arg[2].Lower},melees,priests,casters,hybirds,hybrids,petclass,leaders,group1,group2,group3,group4,group5,group6,group7,group8,group9]} || ${Bool[${FindBot}]}) {
				/varset ChatText ${ChatText.Right[-${Math.Calc[${ChatText.Arg[1].Length}+1]}]}
				/goto :CheckSpecBot
			}
			/if (${Select[${ChatText.Arg[1].Lower},${mClassTypes.Lower},${pClassTypes.Lower},${cClassTypes.Lower},${hClassTypes.Lower}]}) /return
			/if (${Select[${ChatText.Arg[1].Lower},melees,priests,casters,hybirds,hybrids,petclass,leaders]}) /return
		}
		|: Execute Command given to Bot, Strip Double //
		/if (${Bool[${ChatText.Find[//]}]}) /varset ChatText ${ChatText.Replace[//,/]}
		|: After all checks pass now, Execute Command to make Bot do.
		/call ExecCommand "${ChatText}"	
	}
/return
|:-----------------------------------------------------------------------
|: ExecCommand: This Section Handles, Routes all Given Commands to Proper Subrountine.
|:-----------------------------------------------------------------------
Sub ExecCommand(string Commands)
	|: Set macro ExecCommand
	/varset CommandText ${Commands}
	|: IF Command is more then one Parameter. Then Param1 is Command, Rest is CommandParam.
	/varset CurrCommand ${CommandText.Arg[1]}
	/if (${CommandText.Arg[2].Length}) {
		/varset CommandParam ${CommandText.Right[-${Math.Calc[${CurrCommand.Length}+1].Int}]}
	} else {
		/varset CommandParam
	}
	|: Obey ingame slash commands from Masters only unless dopublic equal on.
	/if (${CommandText.Left[1].Equal[/]}) {
		/squelch /nomodkey /docommand ${CommandText}
		/return
	}
	|: Check if Command is a Shortcut, Do Shortcut Command.
	/if (${Defined[cmds-Shortcuts]}) {
		/if (!${Defined[GenStr]}) /declare GenStr string local |${cmds-Shortcuts.Lower}|
		/if (${Bool[${GenStr.Find[|${CurrCommand.Lower}|]}]}) {
			/if (!${Defined[Name]}) /declare Name string local
			/if (!${Defined[ParseText]}) /declare ParseText string local
			|: Set Name,ParseText based on IF | or Space Delimiters Found.
			/if (${CurrCommand.Find[|]}) {
				/varset Name ${CurrCommand.Arg[1,|].Lower}
				/varset ParseText ${ShortCuts-${Name}-Text}
			} else {
				/varset Name ${CurrCommand.Arg[1].Lower}
				/varset ParseText ${ShortCuts-${Name}-Text}
			}
			/if (${Bool[${CommandText.Find[on]}]} || ${Bool[${ParseText.Find[on]}]}) {
				/if (${CurrCommand.Count[|]} > 0) {
					|: Do All Commands Given.
					/if (!${Defined[GenFor]}) /declare GenFor int local
					/for GenFor 1 to ${Math.Calc[${CurrCommand.Count[|]}+1].Int}
						/varset Name ${CurrCommand.Arg[${GenFor},|].Lower}
						/varset ParseText ${ShortCuts-${Name}-Text}
						/squelch /nomodkey /docommand /gb ${ParseText.Replace[ @{NameS},]} ${CommandParam}
					/next GenFor
				} else {
					/squelch /nomodkey /docommand /gb ${ParseText.Replace[ @{NameS},]} ${CommandParam}
				}
			} else {
				/if (${CurrCommand.Count[|]} > 0) {
					|: Do All Commands Given.
					/if (!${Defined[GenFor]}) /declare GenFor int local
					/for GenFor 1 to ${Math.Calc[${CommandText.Count[|]}+1].Int}
						/varset Name ${CurrCommand.Arg[${GenFor},|].Lower}
						/varset ParseText ${ShortCuts-${Name}-Text}
						/squelch /nomodkey /docommand /gb ${ParseText.Replace[@{NameS},on]} ${Sender}
					/next GenFor
				} else {
					/squelch /nomodkey /docommand /gb ${ParseText.Replace[@{NameS},on]} ${Sender}
				}
			}
			/return
		}
	}
	|: Check if Command is a Toggle, Do Toggle Command.
	/if (${Defined[Toggle-${CurrCommand.Lower}]}) {
		|: Change Current Command Toggle State: [TRUE/FALSE] Deppending on its current Status.
		/call SetToggle "${Macro.CurSub}" "${Macro.CurLine}" ${CurrCommand.Lower} "${CommandParam}"
		|: Call Command_ SUB if Toggle has one.
		/if (${Bool[${Toggle-${CurrCommand}-CallSub}]}) {
			/call Toggle_${CurrCommand.Lower} ${CommandParam}
			/return
		}
	}
	|: Do All Other Macro Commands.
	/if (!${Defined[GenFor]}) /declare GenFor int local
	/for GenFor 1 to ${Math.Calc[${SectionsList.Count[ ]}+1].Int}
		/if (!${Defined[GenStr]}) /declare GenStr string local
		/varset GenStr |${cmds-${SectionsList.Arg[${GenFor}]}}|
		|:  && !${Defined[Toggle-${CurrCommand.Lower}]}
		/if (${Bool[${GenStr.Find[|${CurrCommand}|]}]} && !${Defined[Toggle-${CurrCommand.Lower}]}) {
			/call Command_${CurrCommand.Lower} ${CommandParam}
			/return
		}	
	/next GenFor
/return
|:-----------------------------------------------------------------------
|: Event_EQBCSAY: Commands Bot to Parse EQBC Channel for Commands and Pass to [Event_Chat] to Route all Given Commands
|:-----------------------------------------------------------------------
Sub Event_EQBCSAY(string line ,string EQBCSender, string EQBCText)
	|: IF Toggle-pause ON then Cancel all command given unless Toggle-pause.
	/if (${Toggle-pause} && !${Bool[${EQBCText.Find[pause]}]}) /return
	|: Set the ChatType to EQBC
	/if (!${Defined[ChatType]}) /declare ChatType string local EQBC
	|: Call Event_Chat with Params to Parse.
	/call Event_Chat "${ChatType}" "${EQBCSender}" "${EQBCText}"
/return
|:-----------------------------------------------------------------------
|: Event_SelfEcho: Commands Bot to do Self-Only Commands.
|:-----------------------------------------------------------------------
Sub Event_SelfEcho(string line, string SelfEchoText)
	|: IF Toggle-pause ON then Cancel all command given unless Toggle-pause.
	/if (${Toggle-pause} && !${Bool[${SelfEchoText.Find[pause]}]}) /return
	|: Set the Senders Name to Self, Set Outer: [EchoText] to be used in Macro for Self only Commands.
	/varset Sender ${Me.CleanName}
	/varset EchoText ${SelfEchoText}
	/call ExecCommand "${EchoText}"
	|: Clear EchoText Variable we are done using it now.
	/varset EchoText
/return
|:-----------------------------------------------------------------------
|: ChatOut: Commands Bot to send Messages to [ChatIn] Channel in ini.
|:-----------------------------------------------------------------------
Sub ChatOut(string Section, string ChatText, int Delay)
	|: IF ChatOut = Hide Then Cancel ChatOut Output from Displaying.
	/if (${ChatOut.Upper.Equal[HIDE]}) /return
	|: IF ChatOut = Show or Current Section Name Calling Chatout Then Display Output.
	/if (${ChatOut.Upper.Equal[SHOW]} || ${ChatOut.Upper.Equal[${Section}]}) {
		|: Replace any "@"'s with "$"'s in string "${ChatText}", Reset ChatText.
		/if (${Bool[${ChatText.Count[@]} > 0]}) {
			/call CollapseParams "@" "$" "${ChatText}"
			/varset ChatText ${Macro.Return}
			|:/varset ChatText ${ChatText.Replace[@,$]}
		}
		|: Deppending on ChatIn = tell|group|raid|say|channel|guild|eqbc Then Send Chat Message to ChatIn Channel.
		/if (${ChatIn.Lower.Equal[tell]}) {
				/docommand /timed ${Delay} /tell ${Masters.Arg[1,|]} [ChatOut]-${If[${DebugList.Equal[Chatout]},[${Section}] ,]} ${ChatText}
		} else /if (${ChatIn.Lower.Equal[group]}) {
			/docommand /timed ${Delay} /gsay [ChatOut]-${If[${DebugList.Equal[Chatout]},[${Section}] ,]} ${ChatText}
		} else /if (${ChatIn.Lower.Equal[raid]}) {
			/docommand /timed ${Delay} /rsay [ChatOut]-${If[${DebugList.Equal[Chatout]},[${Section}] ,]} ${ChatText}
		} else /if (${ChatIn.Lower.Equal[say]}) {
			/docommand /timed ${Delay} /say [ChatOut]-${If[${DebugList.Equal[Chatout]},[${Section}] ,]} ${ChatText}
		} else /if (${ChatIn.Lower.Equal[guild]}) {
			/docommand /timed ${Delay} /guildsay  [ChatOut]-${If[${DebugList.Equal[Chatout]},[${Section}] ,]} ${ChatText}
		} else /if (${ChatIn.Lower.Equal[eqbc]}) {
			/docommand /timed ${Delay} /bc [ChatOut]-${If[${DebugList.Equal[Chatout]},[${Section}] ,]} ${ChatText}
		} else /if (${ChatIn.Left[1].Equal[/]}) {
			/docommand /timed ${Delay} ${ChatIn} [ChatOut]-${If[${DebugList.Equal[Chatout]},[${Section}] ,]} ${ChatText}
		} 
	}
/return
|:-----------------------------------------------------------------------
|: AddCommands: add commands to a Certian Section.
|:-----------------------------------------------------------------------
Sub AddCommands(string Param0, string Param1, string Param2, string Param3, string Param4, string Param5, string Param6, string Param7, string Param8, string Param9, string Param10, string Param11, string Param12)
	/if (!${Defined[GenFor]}) /declare GenFor int local 0
	/if (!${Defined[GenStr]}) /declare GenStr string local |${cmds-${SectionName}}|
	/for GenFor 0 to ${Math.Calc[${Macro.Params}-1]}
		/if (!${GenStr.Find[|${Param${GenFor}}|]}) {
			/call ListAppendElement cmds-${SectionName} ${Param${GenFor}} "|"
		}
	/next GenFor
/return
|:----------------------------------------------------------------------
|: AddToggle: add a toggle command and load initial setting from .ini
|:----------------------------------------------------------------------
Sub AddToggle(string Subrountine, string SubCurrentLine, string Name, string TogDefault, string TogType, string OffText, string OnText, string CallSub)
	/if (!${Defined[Toggle-${Name}]}) {
		/declare Toggle-${Name} bool outer
		/declare Toggle-${Name}-DefaultValue bool outer
		/declare Toggle-${Name}-OffText string outer
		/declare Toggle-${Name}-OnText string outer
		/declare Toggle-${Name}-ToggleType string outer
		/declare Toggle-${Name}-CallSub bool outer
	}
	|: Set Toggle Variables for Macro to use.
	/varset Toggle-${Name}-OffText ${OffText}
	/varset Toggle-${Name}-OnText ${OnText}
	/varset Toggle-${Name}-ToggleType ${TogType}
	|: Have Toggles Call a Sub Rountine for Extra Code to perform.
	/if (${CallSub.Lower.Equal[callsub]} || ${CallSub.Lower.Equal[true]} || ${CallSub.Lower.Equal[${Name}]}) {
		/varset Toggle-${Name}-CallSub TRUE
	} else {
		/varset Toggle-${Name}-CallSub FALSE
	}
	|: Set Toggle to FALSE if TogDefault = noini, Else Call LoadSetting for Toggles Ini Setting.
	/if (${TogDefault.Equal[noini]}) {
		/varset Toggle-${Name} FALSE
		|: IF it's a string, set the varname-DefaultValue variable
		/if (!${Defined[Toggle-${Name}-DefaultValue]}) {
			/declare Toggle-${Name}-DefaultValue string outer
		}
		/varset Toggle-${Name}-DefaultValue ${Toggle-${Name}}
	} else {
		/call LoadSetting "${Macro.CurSub}" "${Macro.CurLine}" ${Name} toggle ${Name}(On/Off) ${TogDefault}
	}
	|: Loop to check if Toggle added to Cmds-SectionName Variable.
	/if (!${Defined[GenStr]}) /declare GenStr string local |${cmds-${SectionName}}|
	/if (!${GenStr.Find[|${Name}|]} && ${Bool[${Toggle-${Name}-CallSub}]}) {
		/call ListAppendElement cmds-${SectionName} ${Name} "|"
	}
/return
|:----------------------------------------------------------------------
|: SetToggle: set the value of the .ini and repeat current setting
|:----------------------------------------------------------------------
Sub SetToggle(string Subrountine, string SubCurrentLine, string Name, string newValue)
	/declare TrueString string local
	/declare FalseString string local
	|: IF Not Defined [newValue] Then Toggle it.
	/if (!${Defined[newValue]}) {
		/if (${Toggle-${Name}-ToggleType.Equal[toggle]}) {
			/if (${${Toggle-${Name}}}) {
				/declare newValue string local 0
			} else {
				/declare newValue string local 1
			}
		} else {
			/declare newValue string local ${${Toggle-${Name}}}
		}
		|: If it has an argument, set according to argument, and clear newValue. :|
	} else {
		/varset TrueString true on 1 yes
		/varset FalseString false off 0 no
		/if (${TrueString.Find[${newValue.Arg[1]}]}) {
			/varset Toggle-${Name} 1
			/varset Toggle-${Name}-DefaultValue 1
		} else /if (${FalseString.Find[${newValue.Arg[1]}]}) {
			/varset Toggle-${Name} 0
			/varset Toggle-${Name}-DefaultValue 0
		}
	}
	|: If we're still initializing, don't output the setting. :|
	/if (${SectionName.Length}) /return
	|: Check IF Toggle Also Has a Sub Command_ToggleName, Call Toggles Sub Rountine with Params Given.
	/if (!${Defined[GenFor]}) /declare GenFor int local
	/for GenFor 1 to ${Math.Calc[${SectionsList.Count[ ]}+1].Int}
		/if (!${Defined[GenStr]}) /declare GenStr string local
		/varset GenStr |${cmds-${SectionsList.Arg[${GenFor}]}}|
		/if (${Bool[${GenStr.Find[|${Name}|]}]} && ${Toggle-${Name.Lower}-CallSub}) {
			/call Toggle_${Name.Lower} ${CommandParam}
			/break
		}
	/next GenFor
	|: Find the appropriate response string for new toggle setting. :|
	/if (!${Defined[ToggleMsg]}) /declare ToggleMsg string local
	/if (${Toggle-${Name}}) {
		/varset ToggleMsg ${Toggle-${Name}-OnText}
	} else {
		/varset ToggleMsg ${Toggle-${Name}-OffText}
	}
	|: Replace any @'s with $'s for runtime values. :|
	/if (${ToggleMsg.Count[@]}) {
	|:	/call CollapseParams "@" "$" "${ToggleMsg}"
	|:	/varset ToggleMsg ${Macro.Return}
		/varset ToggleMsg ${ToggleMsg.Replace[@,$]}
	}
	|: Say what you've come to say. :|
	/call ChatOut CORE "${ToggleMsg}" "0"
/return
|:----------------------------------------------------------------------
|: LoadSetting: load a variable value from the .ini file
|:----------------------------------------------------------------------
Sub LoadSetting(string Subrountine, string SubCurrentLine, string VarName, string VarType, string KeyName, string DefaultValue)
	|: Create bot_Masters.ini IF Not Exist.
	/if (!${Bool[${Ini[${Masters_INI},CORE,Masters]}]}) /ini ${Masters_INI} "CORE" "Masters" "List all of your BOTS Here Seperated by |"
	|: Set RealSection Loaclly to SectionName for Subrountine Processing.
	/if (!${Defined[RealSection]}) /declare RealSection string local ${SectionName.Upper}
	/if (${VarType.Lower.Equal[shortcuts]} || ${VarType.Lower.Equal[events]}) /varset RealSection ${VarType.Upper}
	|: Setup Blank & Line Variable for INIs files.
	/if (${VarName.Upper.Equal[|**LINE**|]} || ${VarName.Upper.Equal[|**BLANK**|]} || ${VarName.Upper.Equal[|**HEADER**|]}) {
		|: Create Current Blank Line Space Count
		/if (!${Defined[sBlankLine]}) /declare sBlankLine string local  
		/if (!${Defined[x]}) /declare x int local
		/if (!${Defined[BlankLoopN]}) /declare BlankLoopN int local ${Int[${DefaultValue}]}
		/for x 1 to ${BlankLoopN}
			/varset sBlankLine ${sBlankLine} 
		/next x
		|: This creates a Header Line inside INI File.
		/if (!${Bool[${Ini[${BOT_INI},${RealSection},"#${DefaultValue}꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊${VarType}"]}]}) {
			/if (${VarName.Upper.Equal[|**HEADER**|]} && ${VarType.Upper.Equal[=]} && ${Bool[${KeyName}]}==TRUE && ${Bool[${DefaultValue}]}==TRUE) {
				/ini ${BOT_INI} "${RealSection}" "#${DefaultValue}꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊(" "-${KeyName}-=)꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊#"
				/return
			}
		}
		|: This creates a Line Break inside INI File.
		/if (!${Bool[${Ini[${BOT_INI},${RealSection},"#${DefaultValue}꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊"]}]}) {
			/if (${VarName.Upper.Equal[|**LINE**|]} && ${VarType.Upper.Equal[=]} && ${KeyName.Upper.Equal[=]} && ${Bool[${DefaultValue}]}==TRUE) {
				/ini ${BOT_INI} "${RealSection}" "#${DefaultValue}꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊" "꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊꞊#"
				/return
			}
		}
		|: This creates a Blank Line inside INI File.
		|: Space between " " && [BlankLine] && Replace[ , ] is not a Space is ASCII CODE: Alt+0160 , U+00A0 [No-Break Space]
		/if (${VarName.Upper.Equal[|**BLANK**|]} && ${VarType.Upper.Equal[=]} && ${KeyName.Upper.Equal[=]} && ${Bool[${DefaultValue}]}==TRUE) {
			/if (!${Defined[BlankLine]}) /declare BlankLine string local                                                                                                                                                                                                                                                                
			/ini ${BOT_INI} "${RealSection}"   "${BlankLine.Replace[ , ]}${sBlankLine}" ""
			/return
		}
		/return
	}
	|:Add Comments to Ini for User Information.
	/if (${VarType.Equal[Comments]} && !${Bool[${Ini[${BOT_INI},${RealSection},"#${KeyName}"]}]}) {
		/ini ${BOT_INI} "${RealSection}" "#${KeyName}" "${DefaultValue}"
		/return
	} else /if (${VarType.Equal[Comments]}) {
		|: Comment Exisit Cancel adding again and just Return
		/return
	}
	|: Read value from .Ini file :|
	/declare IniValue string local ${Ini[${BOT_INI},${RealSection},${KeyName},NOTFOUND]}
	|: Change Value of Deleted Unused Variables. So user knows they can remove from there Ini File.
	/if (${VarName.Equal[DeleteMe]} && ${VarType.Equal[DeleteMe]}) {
		/if (!${Defined[DeleteMe]}) /declare DeleteMe string local |** NOT USED DELETE ME ]--[ NOT USED DELETE ME **|
		/if (${Bool[${Ini[${BOT_INI},${RealSection},"${KeyName}"].NotEqual[${DeleteMe}]}]}) {
			/ini ${BOT_INI} "${RealSection}" "${KeyName}" "${DefaultValue}"
			/varset IniValue ${DefaultValue}
		}
	|: Create Ini Entry if IniValue = NOTFOUND
	} else {
		/if (${IniValue.Equal[NOTFOUND]} && ${Bool[${KeyName}]}==TRUE && ${Bool[${DefaultValue}]}==TRUE) {
			/ini ${BOT_INI} "${RealSection}" "${KeyName}" "${DefaultValue}"
			/varset IniValue ${DefaultValue}
		}
	}
	|: If it's a array
	/if (${VarType.Equal[array]}) {
		/if (!${Defined[TempAryC]}) /declare TempAryC string local 0
		/if (!${Defined[TempAryParams]}) /declare TempAryParams string local 0
		/if (${DefaultValue.Find[,]} && ${IniValue.Equal[${DefaultValue}]}) {
			/varset TempAryC ${Math.Calc[${DefaultValue.Count[,]}+1].Int}
			/varset TempAryParams ${VarName.Mid[${Math.Calc[${VarName.Length}-1].Int},1]}
			/if (${TempAryParams} == ${TempAryC}) {
				/if (!${Defined[${VarName.Left[-3]}]}) {
					/declare ${VarName.Left[-3]}[${TempAryC}] string outer
				}
				/declare ${VarName.Left[-3]}-DefaultValue[${TempAryC}] string outer
			} else {
				/if (!${Defined[${VarName.Left[-3]}]} && ${IniValue.Equal[${DefaultValue}]}) {
					/declare ${VarName.Left[-3]}[${VarName.Mid[${Math.Calc[${VarName.Length}-1].Int},1]}] string outer ${DefaultValue}
				}
				/declare ${VarName.Left[-3]}-DefaultValue[${VarName.Mid[${Math.Calc[${VarName.Length}-1].Int},1]}] string outer ${DefaultValue}
			}
		} else {
			/if (!${Defined[${VarName}]}) {
				/declare ${VarName.Left[-3]}[${VarName.Mid[${Math.Calc[${VarName.Length}-1].Int},1]}] string outer
			}
			/declare ${VarName.Left[-3]}-DefaultValue[${VarName.Mid[${Math.Calc[${VarName.Length}-1].Int},1]}] string outer ${DefaultValue}
		}
			/if (${IniValue.NotEqual[${${VarName.Left[-3]}-DefaultValue[1]}]}) {
					/varset ${VarName.Left[-3]}[1] ${IniValue.Arg[1,,]}
				/if (!${Defined[x]}) /declare x int local
				/for x 2 to ${Math.Calc[${IniValue.Count[,]}]}
					/call StackArray ${VarName.Left[-3]} ${IniValue.Arg[${x},,]}
				/next x
			}
	}
	|: IF it's a string, set the varname-DefaultValue variable
	/if (${VarType.Equal[string]}) {
		/if (!${Defined[${VarName}-DefaultValue]}) {
			/declare ${VarName}-DefaultValue ${VarType} outer
		}
		/varset ${VarName}-DefaultValue ${DefaultValue}
	}
	|: IF it's a int, set the varname-DefaultValue variable :|
	/if (${VarType.Equal[int]}) {
		/if (!${Defined[${VarName}-DefaultValue]}) {
			/declare ${VarName}-DefaultValue ${VarType} outer
		}
		/varset ${VarName}-DefaultValue ${DefaultValue}
	}	
	|: IF it's a toggle, set the varname-DefaultValue variable :|
	/if (${VarType.Equal[toggle]}) {
		/if (!${Defined[Toggle-${VarName}-DefaultValue]}) {
			/declare Toggle-${VarName}-DefaultValue string outer
		}
		/varset Toggle-${VarName}-DefaultValue ${DefaultValue}
	}
	|: IF it's a shortcut, set the varname-DefaultValue variable :|
	/if (${VarType.Equal[shortcut]}) {
		/if (!${Defined[shortcut-${VarName}-DefaultValue]}) {
			/declare shortcut-${VarName}-DefaultValue string outer
		}
		/varset shortcut-${VarName}-DefaultValue ${DefaultValue}
	}
	|: IF it's a event, set the varname-DefaultValue variable :|
	/if (${VarType.Equal[event]}) {
		/if (!${Defined[event-${VarName}-DefaultValue]}) {
			/declare event-${VarName}-DefaultValue string outer
		}
		/varset event-${VarName}-DefaultValue ${DefaultValue}
	}
	|: IF it's a array, set the varname-DefaultValue variable :|
	/if (${VarType.Equal[array]}) {
		/if (!${Defined[array-${VarName}-DefaultValue]}) {
			/declare array-${VarName}-DefaultValue string outer
		}
		/varset array-${VarName}-DefaultValue ${DefaultValue}
	}
	|: If it's a shortcut, then set the shortcut var and add to the list of shortcuts
	/if (${VarType.Equal[shortcuts]} || ${VarType.Equal[event]}) {
		/if (!${IniValue.Lower.Equal[none]}) {
			/if (!${Defined[ShortCuts-${VarName.Lower}-Text]}) {
				/declare ShortCuts-${VarName.Lower}-Text string outer
			}
			/varset ShortCuts-${VarName.Lower}-Text ${IniValue}
			/call ListAppendElement cmds-Shortcuts ${VarName.Lower} "|"
		}
		/return
	}
	|: If it's a toggle, then use SetToggle sub to give the value.
	/if (${VarType.Equal[toggle]}) {
		/call SetToggle "${Macro.CurSub}" "${Macro.CurLine}" ${VarName.Lower} ${IniValue}
		/return
	}
	|: Must be not a shortcut nor a toggle, since not /returned yet.
	/if (${VarType.NotEqual[array]}) {
		/if (!${Defined[${VarName}]}) {
			/declare ${VarName} ${VarType} outer
		}
		/varset ${VarName} ${IniValue}
	} else {
		/if (${TempAryParams} == ${TempAryC} && ${TempAryC} != 0) {
			/if (!${Defined[x]}) /declare x int local
			/for x 1 to ${TempAryC}
				/varset ${VarName.Left[-3]}[${x}] ${DefaultValue.Arg[${x},,]}
				/varset ${VarName.Left[-3]}-DefaultValue[${x}] ${DefaultValue.Arg[${x},,]}
			/next x
		} else {
			/if (${${VarName.Left[-3]}[1].Equal[${${VarName.Left[-3]}-DefaultValue[1]}]}) {
				/varset ${VarName.Left[-3]}[${VarName.Mid[${Math.Calc[${VarName.Length}-1].Int},1]}] ${DefaultValue}
				/varset ${VarName.Left[-3]}-DefaultValue[${VarName.Mid[${Math.Calc[${VarName.Length}-1].Int},1]}] ${DefaultValue}
			}
		}
	}
/return
|:----------------------------------------------------------------------
|: CollapseParams: replace @'s with $'s to evaluate datavars at runtime
|:----------------------------------------------------------------------
|: Example /call CollapseParams "@" "$" "My Name is: @{Me} I Am Level: @{Me.Level}, Class is: @{Me.Class}"
|: Will output: My Name is: YourName I Am Level: YourLevel, Class is: YourClass
Sub CollapseParams(string Delimitator, string ReplaceWith, string Parms)
	|: IF Delimitator && ReplaceWith are not Set us Defaults.
	/if (${Defined[Delimitator]} && ${Defined[ReplaceWith]} && ${Defined[Parms]}) {
		/if (${Delimitator.Length} == 0) /varset Delimitator @
		/if (${ReplaceWith.Length} == 0) /varset ReplaceWith $
	}
	/if (!${Defined[sint]}) /declare sint int local
	/varset sint ${Math.Calc[${Parms.Count[${Delimitator}]}].Int}  
	/if (${Bool[${sint}]}) {
		/if (!${Defined[stemp]}) /declare stemp string local
		/varset stemp ${Parms.Arg[${Math.Calc[${sint}+1].Int},${Delimitator}]}
		|: Loop Through Delimitators Found
		/if (!${Defined[GenFor]}) /declare GenFor int local
		/for GenFor ${sint} downto 1
			/if (${Parms.Arg[${GenFor},${Delimitator}].Length}) {
				/varset stemp ${Parms.Arg[${GenFor},${Delimitator}]}${ReplaceWith}${stemp}
			} 
		/next GenFor
		|: Set Parms to New Replaced Results.
		/varset Parms ${stemp}
	}
/return ${Parms}
|:----------------------------------------------------------------------
|: ListDelbyArg: Remove Argument [sArg] From [sList] Seperated by: [sDiv]
|:----------------------------------------------------------------------
|: Example /call ListDelbyArg "one two three four" 1 " "
|: Will output: two three four
Sub ListDelbyArg(string sList, int sArg, string sDiv)
	|: Check make sure Given [sArg] is Correct Value.
	/if (!${Defined[sDiv]}) /declare sDiv string local |
	/if (${sArg} > ${Math.Calc[${sList.Count[${sDiv}]}+1].Int} || ${sArg} == 0) {
		/if (${sArg} == 0) 
		/if (${sArg} > ${Math.Calc[${sList.Count[${sDiv}]}+1].Int}) 
		/return Error Invalid!
	}
	|: Get String Value to be Removed.
	/if (!${Defined[splaceholder]}) /declare splaceholder string local ${sList}
	/varset splaceholder ${splaceholder.Arg[${sArg},${sDiv}]}
	|: Find String Location to be Remove from Left side.
	/if (!${Defined[sleft]}) /declare sleft int local
	/varcalc sleft  ${sList.Find[${sDiv}${splaceholder}${sDiv}]}
	/varset splaceholder ${splaceholder}${sDiv}
	|: Find String Location to be Removed from Right side.
	/if (!${Defined[sright]}) /declare sright int local
	/varcalc sright ${sleft}+${splaceholder.Length}
	|: Calculate Correct way to splice string with our 3 Values: [sleft], [sright], [splaceholder]
	/if (${sleft} == 0) {
		/if (${sArg} == ${Math.Calc[${sList.Count[${sDiv}]}+1].Int}) {
			/varset sList ${sList.Left[-${sright}]}
		} else {
			/varset sList ${sList.Right[-${sright}]}
		}
	} else {
		/varset sList ${sList.Left[${sleft}]}${sList.Right[-${sright}]}
	}
/return ${sList}
|:----------------------------------------------------------------------
|: ListReplacebyArg: Replace Argument [sArg] From [sList] Seperated by: [sDiv] ReplaceWith: [sElement]
|:----------------------------------------------------------------------
|: Example /call ListReplacebyArg "one two three four" "Replaced" 2 " "
|: Will output: one Replaced three four
Sub ListReplacebyArg(string sList, string sElement, string sArg, string sDiv)
	|: Check make sure Given [sArg] is Correct Value.
	/if (!${Defined[sDiv]}) /declare sDiv string local |
	/if (${sArg} > ${Math.Calc[${sList.Count[${sDiv}]}+1].Int} || ${sArg} == 0) {
		/if (${sArg} == 0) 
		/if (${sArg} > ${Math.Calc[${sList.Count[${sDiv}]}+1].Int}) 
		/return Error Invalid!
	}
	|: Get String Value to be Removed.
	/if (!${Defined[splaceholder]}) /declare splaceholder string local ${sList}
	/varset splaceholder ${splaceholder.Arg[${sArg},${sDiv}]}
	|: Find String Location to be Remove from Left side.
	/if (!${Defined[sleft]}) /declare sleft int local
	/varcalc sleft  ${sList.Find[${sDiv}${splaceholder}${sDiv}]}
	/varset splaceholder ${splaceholder}${sDiv}
	|: Find String Location to be Removed from Right side.
	/if (!${Defined[sright]}) /declare sright int local
	/varcalc sright ${sleft}+${splaceholder.Length}
	|: Calculate Correct way to splice string with our 3 Values: [sleft], [sright], [splaceholder]
	/if (${sleft} == 0) {
		/if (${sArg} == ${Math.Calc[${sList.Count[${sDiv}]}+1].Int}) {
			/varset sList ${sList.Left[-${sright}]}${sDiv}${sElement}
		} else {
			/varset sList ${sElement}${sDiv}${sList.Right[-${sright}]}
		}
	} else {
		/varset sList ${sList.Left[${sleft}]}${sElement}${sDiv}${sList.Right[-${sright}]}
	}
/return ${sList}
|:----------------------------------------------------------------------
|: StringReplaceAll: Replace ALL [oldElement] ReplaceWith: [newElement] FROM [sList]
|:----------------------------------------------------------------------
|: Example /call StringReplaceAll "one two three four" "two" "Replaced"
|: Will output: one Replaced three four
Sub StringReplaceAll(string sList, string oldElement, string newElement)
	:SearchAgain
	/if (${sList.Find[${oldElement}]}) {
		/if (!${Defined[sleft]}) /declare sleft int local
		/varcalc sleft  ${sList.Find[${oldElement}]}-1
		/if (!${Defined[sright]}) /declare sright int local
		/varcalc sright ${sleft}+${oldElement.Length}
		/if (${sleft} == 0) {
			/varset sList ${newElement}${sList.Right[-${sright}]}
		} else {
			/varset sList ${sList.Left[${sleft}]}${newElement}${sList.Right[-${sright}]}
		}
	} else {
	}
	/if (${sList.Find[${oldElement}]}) /goto :SearchAgain
/return ${sList}
|: Need to FIX NOT WORKING
Sub ListDelbyName(string sList,string sName,string sDiv)
	/echo List [${sList}]  TO Delete: [${sName}]
	/if (!${Defined[sDiv]}) /declare sDiv string local |
	/echo sList: [${sList}]
	/if (!${Defined[sleft]}) /declare sleft int local
	/if (!${Defined[splaceholder]}) /declare splaceholder string local ${sList}
	/if (${Bool[${splaceholder.Find[${sDiv}${sName}${sDiv}]}]}) {
		/varcalc sleft  ${splaceholder.Find[${sDiv}${sName}${sDiv}]}
		/echo sleft[1]: [${sleft}]
	} else /if (${Bool[${splaceholder.Find[${sDiv}${sName}]}]}) {
		/varcalc sleft  ${splaceholder.Find[${sDiv}${sName}]}
		/echo sleft[2]: [${sleft}]
	} else {
		/varcalc sleft  ${splaceholder.Find[${sName}${sDiv}]}
		/echo sleft[3]: [${sleft}]
	}
	/varset splaceholder ${sName}${sDiv}
	/if (!${Defined[sright]}) /declare sright int local
	/varcalc sright ${sleft}+${splaceholder.Length}
	/echo sright: [${sright}]
	/if (${sleft} == 0) {
		/varset sList ${sList.Right[-${sright}]}
		|:/varset sList ${sList.Left[-${sright}]}
	} else {
		/if (${sright} > ${sList.Length}) {
			/varset sList ${sList.Left[${sleft}]}${sList.Right[-${sright}]}
			/varset sList ${sList.Left[-1]}
		} else {
			/varset sList ${sList.Left[${sleft}]}${sList.Right[-${sright}]}
		}
	}
	/echo List [${sList}]  Deleted: [${sName}]
/return ${sList}
|:----------------------------------------------------------------------
|: ListAppendElement: This adds Element To [END] New/Exisiting Variable: [sList] Add Element: [sElement] Seperated by: [sDiv]
|:----------------------------------------------------------------------
|: Example /call ListAppendElement "ListName" "NewElement" "|"
|: Will output: Variable [ListName] = ListData1|NewElement|
Sub ListAppendElement(string sList, string sElement, string sDiv)
	|:This adds sElement to End of sList.
	/if (!${Defined[sDiv]}) /declare sDiv string local |
	/if (!${Defined[${sList}]}) /declare ${sList} string outer
	/if (${${sList}.Length}) {
		/varset ${sList} ${${sList}}${sDiv}${sElement}
	} else {
		/varset ${sList} ${sElement}
	}
/return ${${sList}}
|:----------------------------------------------------------------------
|: ListAppendElement: This adds Element To [Start] New/Exisiting Variable: [sList] Add Element: [sElement] Seperated by: [sDiv]
|:----------------------------------------------------------------------
|: Example /call ListAppendElement "ListName" "NewElement" "|"
|: Will output: Variable [ListName] = NewElement|ListData1
Sub ListPrependElement(string sList, string sElement, string sDiv)
	|:This adds sElement to the Start of sList.
	/if (!${Defined[sDiv]}) /declare sDiv string local |
	/if (!${Defined[${sList}]}) /declare ${sList} string outer
	/if (${${sList}.Length}) {
		/varset ${sList} ${sElement}${sDiv}${${sList}}
	} else {
		/varset ${sList} ${sElement}
	}
/return ${${sList}}
|:----------------------------------------------------------------------
|: ListFindStringArg: This will find Strings Argument Number: String [sString]  Seperated by: [sDiv] From: [sList]
|:----------------------------------------------------------------------
|: Example /call ListFindStringArg "one two three four" "four" " "
|: Will output: [4]
Sub ListFindStringArg(string sList, string sString, string sDiv)
	/if (!${Defined[sDiv]}) /declare sDiv string local |
	/if (!${Defined[sReturn]}) /declare sReturn int local
	/varcalc sReturn ${sList.Left[${sList.Find[${sString}]}].Count[${sDiv}]}+1
/return ${sReturn}
|:----------------------------------------------------------------------
|: array2String: Convert Array to String Arrays Name: 
|: [ArrayName] Array String Name: [ArrayName_str] Seperated by: [Delimitator] Delete Array: [ArrayDelete]
|:----------------------------------------------------------------------
|: Example /call array2String "ArrayName" "ArrayName_str" " " FALSE
|: Will output: ArrayName_str[Delimitator]Array[1] Array[2] Array[3]
Sub array2String(string ArrayName, string ArrayString, string Delimitator, bool ArrayDelete)
	/if (!${Defined[x]}) /declare x int local
	/if (${ArrayString.Length} > 0) {
		/if (!${Defined[${ArrayString}]}) /declare ${ArrayString} string outer
	} else {
		|:Default StringName to [ArrayName_str] if not set.
		/if (!${Defined[${ArrayName}_str]}) /declare ${ArrayName}_str string outer
		/varset ArrayString ${ArrayName}_str
	}
	|: IF Array[x].Length Greater then 0, Then Convert Array[x] to String && Remove [Delimitator] From Last Array.
	/for x 1 to ${${ArrayName}.Size}
		/if (${x} < ${${ArrayName}.Size}) {
			/if (${${ArrayName}[${x}].Length} > 0) /varset ${ArrayString} ${${ArrayString}}${${ArrayName}[${x}]}${Delimitator}
		} else {
			/if (${${ArrayName}[${x}].Length} > 0) /varset ${ArrayString} ${${ArrayString}}${${ArrayName}[${x}]}
		}
	/next x
	|: Delete Space in Front OR End of String.
	/if (${${ArrayString}.Right[1].Equal[ ]}) {
		/varset ${ArrayString} ${${ArrayString}.Left[-1]}
	} else /if (${${ArrayString}.Left[1].Equal[ ]}) {	
		/varset ${ArrayString} ${${ArrayString}.Right[-1]}
	}
	/if (${ArrayDelete}) /deletevar ${ArrayName}
/return ${ArrayString}${Delimitator}${${ArrayString}}
|:----------------------------------------------------------------------
|: Validates Ini entries from supplied Ini keys, and creates arrays
|:----------------------------------------------------------------------													
|: Example: /call IniToArray "${MACRO_INI_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_doors.ini,${Zone.ShortName},${Zone.ShortName}#" doorList outer
Sub IniToArray(string IniKey, string ArrayName, string ArrayScope)
	/if (${Defined[${ArrayName}]}) /deletevar ${ArrayName}
	/if (${Ini[${IniKey}1].Length} || ${Ini[${IniKey}1(Spell|Gem|Pct)].Length}) {
		/if (!${Defined[count]}) /declare count int local 0
		/if (!${Defined[i]}) /declare i int local 1
		/if (!${Defined[tmp${ArrayName}]}) /declare tmp${ArrayName} string local
		:NextKey
		/if (${Ini[${IniKey}${i}].Length} || ${Ini[${IniKey}${i}(Spell|Gem|Pct)].Length}) {
		  /varset count ${i}
		  /varcalc i ${i}+1
		  /goto :NextKey
		}
		/declare ${ArrayName}[${count}] string ${ArrayScope}
		/for i 1 to ${count}
			/if (${Ini[${IniKey}${i}].Length}) {
				/varset ${ArrayName}[${i}] ${Ini[${IniKey}${i}]}
				/if (${ArrayScope.Upper.Equal[LOCAL]}) /varset tmp${ArrayName} ${tmp${ArrayName}} ${ArrayName}[${i}]|${Ini[${IniKey}${i}]}
			} else /if (${Ini[${IniKey}${i}(Spell|Gem|Pct)].Length}) {
				/varset ${ArrayName}[${i}] ${Ini[${IniKey}${i}(Spell|Gem|Pct)]}
				/if (${ArrayScope.Upper.Equal[LOCAL]}) /varset tmp${ArrayName} ${tmp${ArrayName}} ${ArrayName}[${i}]|${Ini[${IniKey}${i}]}
			}
		/next i
	} else {
		/declare ${ArrayName}[0] string ${ArrayScope}
	}
/return ${tmp${ArrayName}}
|:----------------------------------------------------------------------
|: Validates Ini entries from supplied Ini keys, and creates variables
|:----------------------------------------------------------------------
|:Example: /call IniToVar "${MACRO_INI_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_Bot.ini,Core,movetomode" movetomode int outer			
Sub IniToVar(string Ini_Key, string VarToMake, string VarType, string VarScope)
	|: Check for the specified ini key.
	/if (!${Ini[${Ini_Key}].Length}) {
	} else {
		|: Validate VarType as Bool.
		/if (${VarType.Upper.Equal[BOOL]}) {
			/if (${Defined[${VarToMake}]}) /deletevar ${VarToMake}
			/if (!${Defined[new_VarName]}) /declare new_VarName string outer
			/declare ${VarToMake} bool ${VarScope} ${If[${Select[${Ini[${Ini_Key}]},TRUE,ON,YES,1]},TRUE,FALSE]}
		|: Validate VarType as Int.
		} else /if (${VarType.Upper.Equal[INT]}) {
			/if (${Defined[${VarToMake}]}) /deletevar ${VarToMake}
			/declare ${VarToMake} int ${VarScope} ${Ini[${Ini_Key}]}
		|: Validate VarType as Float.
		} else /if (${VarType.Upper.Equal[FLOAT]}) {
			/if (${Defined[${VarToMake}]}) /deletevar ${VarToMake}
			/declare ${VarToMake} float ${VarScope} ${Ini[${Ini_Key}]}
		|: Validate VarType as String or Timer.
		} else {
			/if (${Defined[${VarToMake}]}) /deletevar ${VarToMake}
			/declare ${VarToMake} ${VarType} ${VarScope} ${Ini[${Ini_Key}]}
		}
	}
/return ${VarToMake}|${${VarToMake}}
|:----------------------------------------------------------------------
|: Creates new arrays, or stacks onto existing arrays.	
|:----------------------------------------------------------------------
|:Example  /call BuildArray ArrayName Data
Sub BuildArray(string ArrayName, string Data)
	|: IF the array is not defined, declare it.
	/if (!${Defined[${ArrayName}]}) {
		/declare ${ArrayName}[1] string outer
		/varset ${ArrayName}[1] ${Data}
	|: Else, if the array is already defined.
	} else {
		|: Create a copy of the existing array.
		/declare ${ArrayName}Copy[${${ArrayName}.Size}] string local
		/if (!${Defined[i]}) /declare i int local
		/for i 1 to ${${ArrayName}.Size}
			/varset ${ArrayName}Copy[${i}] ${${ArrayName}[${i}]}
		/next i
		|: Delete the existing array.
		/deletevar ${ArrayName}
		|: Build a resized array.
		/declare ${ArrayName}[${Math.Calc[${${ArrayName}Copy.Size}+1].Int}] string outer
		/for i 1 to ${${ArrayName}.Size}
			/if (${i} == ${${ArrayName}.Size}) {
				|: Insert new data into the array.
				/varset ${ArrayName}[${${ArrayName}.Size}] ${Data}
			} else {
				/varset ${ArrayName}[${i}] ${${ArrayName}Copy[${i}]}
			}
		/next i
	}
/return ${ArrayName}
|:----------------------------------------------------------------------
|: Removes elements from an existing array.
|:----------------------------------------------------------------------
Sub SortArray(string ArrayName, string Data)
	|: Create a copy of the existing array.
	/declare ${ArrayName}Copy[${${ArrayName}.Size}] string local
	/if (!${Defined[i]}) /declare i int local
	/for i 1 to ${${ArrayName}.Size}
		/varset ${ArrayName}Copy[${i}] ${${ArrayName}[${i}]}
	/next i
	|: Delete the existing array.
	/deletevar ${ArrayName}
	|: Count array elements that do not match 'Data'.
	/if (!${Defined[x]}) /declare x int local 0
	/for i 1 to ${${ArrayName}Copy.Size}	
		/if (${${ArrayName}Copy[${i}].NotEqual[${Data}]}) {
			/varcalc x ${x} + 1
		} else {
		}
	/next i
	|: If there are elements that do not match 'Data', rebuild the array.
	/if (${Bool[${x}]}) {
		|: Declare a resized array.
		/declare ${ArrayName}[${x}] string outer
		|: Copy the old array, skipping elements that match 'Data'.
		/varset x 1
		/for i 1 to ${${ArrayName}Copy.Size}
			/if (${${ArrayName}Copy[${i}].NotEqual[${Data}]}) {
				/varset ${ArrayName}[${x}] ${${ArrayName}Copy[${i}]}
				/varcalc x ${x} + 1
			}
		/next i
	}
/return
|:----------------------------------------------------------------------
|: Adds [Data} to End of [ArrayName], Can Convert Array to String.
|:----------------------------------------------------------------------
Sub StackArray(string ArrayName, string Data, bool Conv2Str)
	/declare ${ArrayName}Copy[${${ArrayName}.Size}] string local
	/if (!${Defined[i]}) /declare i int local
	|: Copy Old Array to Restack it.
	/for i 1 to ${${ArrayName}.Size}
		/varset ${ArrayName}Copy[${i}] ${${ArrayName}[${i}]}
	/next i
	|: Delete Old Array.
	/deletevar ${ArrayName}
	|: Recreate Array we Copied.
	/if (!${Defined[${ArrayName}]}) {
		/declare ${ArrayName}[${Math.Calc[${${ArrayName}Copy.Size}+1].Int}] string outer
		/for i 1 to ${Math.Calc[${${ArrayName}.Size}-1]}
			/varset ${ArrayName}[${i}] ${${ArrayName}Copy[${i}]}
		/next i
		/varset ${ArrayName}[${${ArrayName}.Size}] ${Data}
	}
	/if (${Conv2Str}) /call array2String ${ArrayName} ${ArrayName}_str " "
/return ${ArrayName}
|:----------------------------------------------------------------------
|: Creates entries, and writes settings to specified inis.				
|:
|: Will not over-write existing entries, unless indicated.				
|:----------------------------------------------------------------------
|: Syntax: /call WriteToIni "Ini_Key" "WhatToWrite" OverWrite(TRUE/FALSE)	
|:
|: /call WriteToIni "${MACRO_INI_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_Loot.ini,B,Bone Chips" "Destroy" TRUE
Sub WriteToIni(string Ini_Key, string WhatToWrite, bool OverWrite)
	|: If the Ini_Key does not exist, create it.
	/if (!${Bool[${Ini[${Ini_Key}].Length}]}) {
		|: If there is something to write, write it.
		/if (${Defined[WhatToWrite]}) {
			/ini "${Ini_Key.Arg[1,,]}" "${Ini_Key.Arg[2,,]}" "${Ini_Key.Arg[3,,]}" "${WhatToWrite}"
		|: Else, create the entry only.
		} else {
			/ini "${Ini_Key.Arg[1,,]}" "${Ini_Key.Arg[2,,]}" "${Ini_Key.Arg[3,,]}"
		}
	|: Else, if the Ini_Key does exist, and OverWrite is true, write to the existing Ini_Key.
	} else /if (${OverWrite}) {
		|: If there is something to write, write it.
		/if (${Defined[WhatToWrite]}) {
			/ini "${Ini_Key.Arg[1,,]}" "${Ini_Key.Arg[2,,]}" "${Ini_Key.Arg[3,,]}" "${WhatToWrite}"
		|: Else, create the entry only.
		} else {
			/ini "${Ini_Key.Arg[1,,]}" "${Ini_Key.Arg[2,,]}" "${Ini_Key.Arg[3,,]}"
		}
	}
/return
|:----------------------------------------------------------------------
|: Reliably targets specified Target.IDs.
|:----------------------------------------------------------------------
Sub TrueTarget(string TargetIDs)
	|: Check if the target is in zone. 
	/if (${SpawnCount[id ${Spawn[${TargetIDs}].ID}]}) {
		/declare TargetRetry int local 0
		:Target_Loop
		/squelch /target id ${Spawn[${TargetIDs}].ID}
		/delay 1 ${Target.ID} == ${Spawn[${TargetIDs}].ID}
		|:If I don't have the correct target, and I haven't exceeded the limit, try again.
		/if (${Target.ID} != ${Spawn[${TargetIDs}].ID} && ${TargetRetry} < 20) {
			/varcalc TargetRetry ${TargetRetry} + 1
			/goto :Target_Loop
		}
	}
/return
|:----------------------------------------------------------------------
|: Creates timers, at the specified duration, and adds their names to timerArray.
|:----------------------------------------------------------------------
Sub createTimer(timerName, timerSetting)
	|: Delete old timer.
	/if (${Defined[${timerName}]}) /deletevar ${timerName}
	|: Declare new timer.
	/declare ${timerName} timer outer ${timerSetting}
	|: Add the timer's name to the timerArray.
	/call BuildArray timerArray ${timerName}
/return ${timerArray[1]}|${timerName}
|:----------------------------------------------------------------------
|: Deletes spent timers made by 'Sub createTimer'.
|:----------------------------------------------------------------------
sub check_macroTimers
	/declare SpentTimerCounter int local
	|: Check each entry of the timer array, count spent timers.	
	/if (${Defined[timerArray]}) {
		/if (!${Defined[i]}) /declare i int local
		/for i 1 to ${timerArray.Size}
			/if (!${${timerArray[${i}]}}) {
				/varcalc SpentTimerCounter ${SpentTimerCounter} + 1
				/if (${Defined[${timerArray[${i}]}]}) {
					/deletevar ${timerArray[${i}]}
				}
			}
		/next i
		|: If all the timers listed on timerArray are spent, delete timerArray.
		/if (${SpentTimerCounter} == ${timerArray.Size}) {
			/deletevar timerArray
		}
	} else {
	}
/return
|: Need to FIX Test
Sub forage_Handle
	/if (${Math.Calc[${Ini[${FORAGE_INI}].Count[|]}-1]} != 26}) /call BuildForageIni
	/declare check int local 0
	:checkitem
	/if (${Cursor.ID}) {
		/if (!${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}].Length}) {
			/call ChatOut CORE "You have foraged a new item! [${Cursor.Name}] has been added to your [${FORAGE_INI}] file under Section [${Cursor.Name.Left[1]}] With Default Value [20]." "0"
			/ini ${FORAGE_INI} ${Cursor.Name.Left[1]} "${Cursor.Name}" 20
			/call clearCursor
		} else /if (${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}].Length}) {
			/if (!${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) {
				/if (${Verbosity}) /echo Destroying [${Cursor.Name}]
				/destroy
			}
			/if (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1]} <= ${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) {
				/if (${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}]} && !${check}) /echo Foraged [${Cursor}] (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1].Int} of ${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}]})
				/call clearCursor
			} else /if (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1]} > ${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) {
				/if (${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}]} && !${check}) /echo Foraged [${Cursor}] (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1].Int} of ${Ini[${FORAGE_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) destroying.
				/destroy
			}
		}		
	}
	/if (${Cursor.ID} && ${check} < 15) {
		/varcalc check ${check}+1
		/goto :checkitem
	}
/return
|:----------------------------------------------------------------------
|: Builds the Forage Ini.
|:----------------------------------------------------------------------
Sub BuildForageINI
	/ini "${FORAGE_INI}" A A NULL
	/ini "${FORAGE_INI}" B B NULL
	/ini "${FORAGE_INI}" C C NULL
	/ini "${FORAGE_INI}" D D NULL
	/ini "${FORAGE_INI}" E E NULL
	/ini "${FORAGE_INI}" F F NULL
	/ini "${FORAGE_INI}" G G NULL
	/ini "${FORAGE_INI}" H H NULL
	/ini "${FORAGE_INI}" I I NULL
	/ini "${FORAGE_INI}" J J NULL
	/ini "${FORAGE_INI}" K K NULL
	/ini "${FORAGE_INI}" L L NULL
	/ini "${FORAGE_INI}" M M NULL
	/ini "${FORAGE_INI}" N N NULL
	/ini "${FORAGE_INI}" O O NULL
	/ini "${FORAGE_INI}" P P NULL
	/ini "${FORAGE_INI}" Q Q NULL
	/ini "${FORAGE_INI}" R R NULL
	/ini "${FORAGE_INI}" S S NULL
	/ini "${FORAGE_INI}" T T NULL
	/ini "${FORAGE_INI}" U U NULL
	/ini "${FORAGE_INI}" V V NULL
	/ini "${FORAGE_INI}" W W NULL
	/ini "${FORAGE_INI}" X X NULL
	/ini "${FORAGE_INI}" Y Y NULL
	/ini "${FORAGE_INI}" Z Z NULL
	/if (${Math.Calc[${Ini[${FORAGE_INI}].Count[|]}-1]} == 26}) {
	}
/return
|: Need to FIX Test
Sub pickpocket_Handle
	/if (${Math.Calc[${Ini[${PICKPOCKET_INI}].Count[|]}-1]} != 26}) /call BuildPickPocketINI
	/declare check int local 0
	:checkitem
	/if (${Cursor.ID}) {
		/if (!${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}].Length}) {
			/if (!${check}) /echo You have foraged a new item! [${Cursor}] has been added to your ${PICKPOCKET_INI} file.
			/ini ${PICKPOCKET_INI} ${Cursor.Name.Left[1]} "${Cursor.Name}" 20
			/call clearCursor
		} else /if (${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}].Length}) {
			/if (!${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) {
				/if (${Verbosity}) /echo Destroying [${Cursor.Name}]
				/destroy
			}
			/if (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1]} <= ${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) {
				/if (${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}]} && !${check}) /echo Foraged [${Cursor}] (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1].Int} of ${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}]})
				/call clearCursor
			} else /if (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1]} > ${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) {
				/if (${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}]} && !${check}) /echo Foraged [${Cursor}] (${Math.Calc[${FindItemCount[${Cursor.Name}]}+1].Int} of ${Ini[${PICKPOCKET_INI},${Cursor.Name.Left[1]},${Cursor.Name}]}) destroying.
				/destroy
			}
		}		
	}
	/if (${Cursor.ID} && ${check} < 15) {
		/varcalc check ${check}+1
		/goto :checkitem
	}
/return
|:----------------------------------------------------------------------
|: Builds the PickPocket Ini.
|:----------------------------------------------------------------------
Sub BuildPickPocketINI
	/ini "${PICKPOCKET_INI}" A A NULL
	/ini "${PICKPOCKET_INI}" B B NULL
	/ini "${PICKPOCKET_INI}" C C NULL
	/ini "${PICKPOCKET_INI}" D D NULL
	/ini "${PICKPOCKET_INI}" E E NULL
	/ini "${PICKPOCKET_INI}" F F NULL
	/ini "${PICKPOCKET_INI}" G G NULL
	/ini "${PICKPOCKET_INI}" H H NULL
	/ini "${PICKPOCKET_INI}" I I NULL
	/ini "${PICKPOCKET_INI}" J J NULL
	/ini "${PICKPOCKET_INI}" K K NULL
	/ini "${PICKPOCKET_INI}" L L NULL
	/ini "${PICKPOCKET_INI}" M M NULL
	/ini "${PICKPOCKET_INI}" N N NULL
	/ini "${PICKPOCKET_INI}" O O NULL
	/ini "${PICKPOCKET_INI}" P P NULL
	/ini "${PICKPOCKET_INI}" Q Q NULL
	/ini "${PICKPOCKET_INI}" R R NULL
	/ini "${PICKPOCKET_INI}" S S NULL
	/ini "${PICKPOCKET_INI}" T T NULL
	/ini "${PICKPOCKET_INI}" U U NULL
	/ini "${PICKPOCKET_INI}" V V NULL
	/ini "${PICKPOCKET_INI}" W W NULL
	/ini "${PICKPOCKET_INI}" X X NULL
	/ini "${PICKPOCKET_INI}" Y Y NULL
	/ini "${PICKPOCKET_INI}" Z Z NULL
	/if (${Math.Calc[${Ini[${PICKPOCKET_INI}].Count[|]}-1]} == 26}) {
	}
/return
|:----------------------------------------------------------------------
|: Auto inventories items from your cursor.
|:
|: Alerts the user, if there is no free inventory space available.
|:----------------------------------------------------------------------
|: Need to FIX Test
Sub ClearCursor
	/declare dumpSlot string local
	|: If I have an item on my cursor, check what type of item it is.
	:auto_inv
	|: If the item is not a container.
	/if (!${Cursor.Container}) {
		|: If I have free inventory space, autoinventory the item.
		/if (${Me.FreeInventory}) {
			/autoinventory
			/delay 1
		|: Else, if I'm out of free inventory space, alert the user, and end the macro.
		} else {
			/call ChatOut 3 "I have run out of inventory space and I have a bag on my cursor!!!" "0"
			/if (!${Defined[i]}) /declare i int local 1
			/for i 1 to 5
				/beep
			/next i
			/varset Toggle-ninjaloot FALSE
		}
	|: If the item is a container.
	} else {
		|: Check for a free pack slot.
		/if (!${Defined[i]}) /declare i int local 1
		/for i 1 to 10
		/if (${InvSlot[pack${i}].Item.Container}) {
			/next i
			|: If I have no free pack slots, alert the user, and end the macro.
			/if (${InvSlot[pack8].Item.Container}) {
				/call ChatOut 3 "I have run out of inventory space and I have a bag on my cursor!!!" "0"
				/if (!${Defined[i]}) /declare i int local 1
				/for i 1 to 7
					/beep
				/next i
				/varset Toggle-ninjaloot FALSE
			}
		|: Else, if I have a free pack slot, drop the backpack.
		} else /if (!${InvSlot[pack${i}].Item.Container}) {
			/nomodkey /itemnotify pack${i} leftmouseup
		}
	}
	|: If I still have something on my cursor, try again to clear it.
	/if (${Cursor.ID}) /goto :auto_inv
/return
Sub TargetofTarget(int intSpawnID)
/if (!${Spawn[${intSpawnID}].ID}) {
	/varset intSpawnID ${Spawn[${Sender}].ID}
}
/squelch /target ID ${intSpawnID}
/delay 2
/if (!${Target.ID}) /return 0
/return ${Me.TargetOfTarget.ID}
Sub idleCheck
|:/echo $[idle} - ${Math.Calc[${idleTimer}/10]}
/if (${Float[${Me.X}].Int} == ${Float[${last_X}].Int} && ${Float[${Me.Y}].Int} == ${Float[${last_Y}].Int} && !${idle} && ${idleTimer} == 0) {
	/varset idle TRUE
} else /if (${Float[${Me.X}].Int} != ${Float[${last_X}].Int} && ${Float[${Me.Y}].Int} != ${Float[${last_Y}].Int} && ${idle} && ${idleTimer} == 0) {
	/varset idle FALSE
	/varset idleTimer 10s
}
/if (${Float[${Me.X}].Int} == ${Float[${last_X}].Int} && ${Float[${Me.Y}].Int} == ${Float[${last_Y}].Int} && !${Buffidle} && ${BuffidleTimer} == 0) {
	/varset Buffidle TRUE
} else /if (${Float[${Me.X}].Int} != ${Float[${last_X}].Int} && ${Float[${Me.Y}].Int} != ${Float[${last_Y}].Int} && ${Buffidle} && ${BuffidleTimer} == 0) {
	/varset Buffidle FALSE
	/varset BuffidleTimer 5m
}
/varset last_X ${Me.X}
/varset last_Y ${Me.Y}
/return
Sub CheckCamp
/if (${IsCamp} && ${Math.Distance[${Ypos},${Xpos}]} >= 10 && !${Toggle-puller} && ${Me.State.NotEqual[BIND]}) {
	|:Make sure puller goes to Anchor
	:MovetoAnchor
	:GotoCamp
	/call Background_Events
	|: Check IF Zone Changed && Turn Guard & Anchor OFF
	/if (${Zone.ID} != ${IsZone} && ${IsCamp}==1) {
		/if (${Toggle-guard}) /call ExecCommand "guard off"
		/if (${IsCamp}==1) /call ExecCommand "anchor off"
	}
	|: Check IF My X,Y > 10 && Not Moving or Sticking THEN GOTO Anchor X,Y Location.
	/if (${Math.Distance[${Ypos},${Xpos}]} > 10 && ${MoveUtils.Command.Equal[NONE]} && ${Bool[${Ypos}]} && ${Bool[${Xpos}]}) {
		/if (${MoveUtils.Command.Equal[NONE]} && !${Me.Moving} && ${Me.State.NotEqual[BIND]}) /moveto loc ${Ypos} ${Xpos}
		/goto :GotoCamp
	}
	|: Check IF Not Moving Then Turn and Face Fast Random Direction.
	/if (${MoveUtils.Command.Equal[NONE]} && !${Me.Moving}) {
		|:${Me.Heading.DegreesCCW}!=${IsHead}
		/face fast heading ${Math.Rand[360]}
		/delay 2
	}
	|: Check IF Anchor X,Y < 10 && Not Moving THEN RETURN
	/if (${Math.Distance[${Ypos},${Xpos}]} <= 10 && ${MoveUtils.Command.Equal[NONE]} && !${Me.Moving}) /return
	|: Check if Guard OFF THEN RETURN
	/if (!${Toggle-guard}) /return
	/goto :GotoCamp
}
/if (${Toggle-puller} && ${Math.Distance[${Ypos},${Xpos}]} <= ${Math.Calc[${GuardRadius}/3]} && ${MoveUtils.Command.Equal[NONE]} && !${Me.Moving} && ${idle} && ${Me.State.NotEqual[FEIGN]} && ${Me.State.NotEqual[BIND]}) /goto :MovetoAnchor
/return
Sub Background_Events
	|: Check For Commands
	/doevents EQBCSAY
/return