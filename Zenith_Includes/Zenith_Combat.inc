Sub CombatMain
|:/echo MAIN COMBAT
	
	|:Check For ESC Key Press
	/doevents EscKey
	
	|: Check IF Following or Auto Following a Target
	/call CheckFollowing
	
	|: Turn Attack off 15 10th's of a Seconds if im CombatTargetID's Target.
	/if (${Me.TargetOfTarget.Name.Equal[${Me.CleanName}]} && ${Toggle-raidevade}) /call RaidEvade 15
	
	|:Check if set to on for auto positioning
	/if (${Toggle-autoengage} && ${CombatTargetID}) {
			
			/if (${Toggle-archery} && ${ArcheryRange} < 34) /varset ArcheryRange 34

			|:Make sure Auto Distance is Setup Correct
			/if (!${Toggle-aggro} && ${Toggle-autodistance}) /call AutoCombatDistance
			
			
			/if (${Toggle-melee}) {
				
				|: Fix for Stick Bouncing
				/if (${Math.Calc[${Target.Distance}].Int} < 1) /stick off
				
				|:Check if Distance to close for set MeleeRange.
				/if (${Math.Calc[${Target.Distance}].Int} < ${MeleeRange} && !${Me.Moving}) {
					/keypress back hold
					/delay ${If[${Math.Calc[${Target.Distance}].Int} > 3,3,1]}
					/keypress back
					/if (!${Toggle-autobehind}) {
						/if (${Stick.Behind}) /nomodkey /docommand /stick uw ${Math.Calc[${MeleeRange}+4].Int}
					} else /if (${Toggle-autobehind}) {
						/if (${Stick.Behind}) /squelch /nomodkey /docommand /stick uw ${Math.Calc[${MeleeRange}+4].Int}
						/if (!${Stick.Behind}) /squelch /nomodkey /docommand /stick snaproll rear uw ${Math.Calc[${MeleeRange}+4].Int}
					}
					/delay 1
				}

				|:Check if Distance to far for set MeleeRange.
				/if (${Math.Calc[${Target.Distance}].Int} > ${MeleeRange} && !${Me.Moving}) {
					/keypress forward hold
					/delay ${If[${Math.Calc[${Target.Distance}].Int} > 3,3,1]}
					/keypress forward
					/if (!${Toggle-autobehind}) {
						/if (!${Toggle-aggro}) /nomodkey /docommand /stick uw ${Math.Calc[${MeleeRange}+4].Int}
					} else /if (${Toggle-autobehind}) {
						/if (${Stick.Behind}) /squelch /nomodkey /docommand /stick uw ${Math.Calc[${MeleeRange}+4].Int}
						/if (!${Stick.Behind}) /squelch /nomodkey /docommand /stick snaproll rear uw ${Math.Calc[${MeleeRange}+4].Int}
					}
					/delay 1
				}
				
			}

			/if (${Toggle-archery}) {
				
				|: Fix for Stick Bouncing
				/if (${Math.Calc[${Target.Distance}].Int} < 1) /stick off
				
				|:Check if genbot's Distance to close for set ArcheryRange.
				/if (${Math.Calc[${Target.Distance}].Int} < ${ArcheryRange}) {
					/keypress back hold
					/delay 1
					/keypress back
					/if (!${Toggle-autobehind}) {
						/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
							/squelch /nomodkey /docommand /stick moveback snaproll face uw ${Math.Calc[${ArcheryRange}+2]}
						} 
					} else /if (${Toggle-autobehind}) {
						/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
							/squelch /nomodkey /docommand /stick moveback snaproll rear uw ${Math.Calc[${ArcheryRange}+2]}
						}
					}
					/delay 1
				}
			
				|:Check if genbot's Distance to far for set ArcheryRange.		
				/if (${Math.Calc[${Target.Distance}].Int} > ${ArcheryRange}) {
						/keypress forward hold
						/delay 1
						/keypress forward
					/if (!${Toggle-autobehind}) {
						/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
							/squelch /nomodkey /docommand /stick snaproll face uw ${Math.Calc[${ArcheryRange}+2]}
						}
					} else /if (${Toggle-autobehind}) {
						/if (${Me.TargetOfTarget.Name.NotEqual[${Me.CleanName}]}) {
							/squelch /nomodkey /docommand /stick snaproll rear uw ${Math.Calc[${ArcheryRange}+2]}
						}
					}
					/delay 1
				}
				
			}	
		
	}
	|:Need to FIX
	|:Check if genbot has to use abilities automaticaly
	|:/call MeleeAbility

	|:auto click potion at a certian percentage.
	|:/call AutoPotionUse

	|:auto cast spell when available.
	|:/call AutoSpellCast

	|:auto use aa ability when available.
	|:/call AutoAAUse

	|:auto use disc when available.
	|:/call AutoDiscUse

	|:auto use item clicky when available.
	|: need to Fix Change way this works [combatclick_delay]
	|:/if (${Toggle-combatclick}) {
	|:	/if (${autoicTimer} == 0) {
	|:		/call AutoItemClick "combat"
	|:		/varset autoicTimer ${combatclick_delay}
	|:	}
	|:}
	
/return

Sub AutoCombatDistance
|: MaxRange		The max distance from this spawn for it to hit you
|: MaxRangeTo	The Max distance from this spawn for you to hit it

/if (${Toggle-melee} && ${Toggle-autoengage}) {
	/if (${MeleeRange} != ${Math.Calc[${Spawn[id ${CombatTargetID}].MaxRangeTo}*.9].Int}) {
		/varset MeleeRange ${Math.Calc[${Spawn[id ${CombatTargetID}].MaxRangeTo}*.9].Int}
		/if (${Stick.Active}) /stick off
	}
}

/if (${Toggle-archery} && ${Toggle-autoengage}) {
	/if (${Math.Calc[${Spawn[id ${CombatTargetID}].MaxRangeTo}*.9].Int} > 34 && ${ArcheryRange} != ${Math.Calc[${Spawn[id ${CombatTargetID}].MaxRangeTo}*.9].Int}) {
		/varset ArcheryRange ${Math.Calc[${Spawn[id ${CombatTargetID}].MaxRangeTo}*.9].Int}
		/if (${Stick.Active}) /stick off
	} else /if (${ArcheryRange} < 34) {
		/varset ArcheryRange 34
		/if (${Stick.Active}) /stick off
	}
}
/return

|:-----------------------------------------------------------------------
|: Combatcheck Used to check if attack is on and should not be.
|:-----------------------------------------------------------------------
Sub Combatcheck(string CombatID)
	
	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Set CombatTargetID to Target.ID  (AcceptableTargetTypes)
	/Call Debug_Spew "CombatTargetID: [${Bool[${CombatTargetID}]}] TargetID: [${Target.ID}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Bool[${CombatTargetID}]} && ${Bool[${Target.ID}]}) {
		/Call Debug_Spew "[Combatcheck] EQ Attack Modes: [${Me.Combat} || ${Me.AutoFire} || ${Bool[${Me.Casting.ID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Me.Combat} || ${Me.AutoFire} || ${Bool[${Me.Casting.ID}]}) {
			/Call Debug_Spew "[Combatcheck] Bot Modes: [${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-debuffs}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-debuffs}) {
				/Call Debug_Spew "[Combatcheck] PVP-Mode: [${Toggle-pvpmode}] Target Type: [${Spawn[${Target.ID}].Type}] Pets Master: [${If[${Spawn[${Target.ID}].Type.Equal[Pet]},${Spawn[${Target.ID}].Master.Type}],Not A Pet]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				/if (${Toggle-pvpmode}) {
					/if (${CombatTargetID} && ${Select[${Spawn[${Target.ID}].State},DEAD,UNKNOWN,NULL]} && ${Select[${Spawn[${Target.ID}].Type},Untargetable,Mount,Corpse,Chest,Trigger,Trap,Timer,Item,Mercenary,Aura,Object,Banner,Campfire,Flyer,NULL]}) {
						/varset CombatTargetID 0
					} else /if (${Select[${Spawn[${Target.ID}].Type},NPC,PC]}) {
						/varset CombatTargetID ${Target.ID}
					} else /if (${Select[${Spawn[${Target.ID}].Type},Pet]} && ${Select[${Spawn[${Target.ID}].Master.Type},NPC,PC]}) {
						/varset CombatTargetID ${Target.ID}
					}
				} else {
					/if (${CombatTargetID} && ${Select[${Spawn[${Target.ID}].State},DEAD,UNKNOWN,NULL]} && ${Select[${Spawn[${Target.ID}].Type},Untargetable,Mount,Corpse,Chest,Trigger,Trap,Timer,Item,Mercenary,Aura,Object,Banner,Campfire,Flyer,NULL]}) {
						/varset CombatTargetID 0
					} else /if (${Select[${Spawn[${Target.ID}].Type},NPC]}) {
						/varset CombatTargetID ${Target.ID}
					} else /if (${Select[${Spawn[${Target.ID}].Type},Pet]} && ${Select[${Spawn[${Target.ID}].Master.Type},NPC]}) {
						/varset CombatTargetID ${Target.ID}
					}
				}
			}
		}
		
	} else /if (${Bool[${CombatTargetID}]}) {
		
		/Call Debug_Spew "[Combatcheck] EQ Attack Modes: [${Me.Combat} || ${Me.AutoFire} || ${Bool[${Me.Casting.ID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Me.Combat} || ${Me.AutoFire} || ${Bool[${Me.Casting.ID}]}) {
			/Call Debug_Spew "[Combatcheck] Bot Modes: [${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-debuffs}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-debuffs}) {
				/Call Debug_Spew "[Combatcheck] PVP-Mode: [${Toggle-pvpmode}] CombatTargetID Type: [${Spawn[${CombatTargetID}].Type}] Pets Master: [${If[${Spawn[${CombatTargetID}].Type.Equal[Pet]},${Spawn[${CombatTargetID}].Master.Type}],Not A Pet]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				|: [Type] ACCEPTED: PC,NPC,Pet
				|: [Type] NOT ACCEPTED: Untargetable,Mount,Corpse,Chest,Trigger,Trap,Timer,Item,Mercenary,Aura,Object,Banner,Campfire,Flyer
				|: [State] STAND, SIT, DUCK, BIND, FEIGN, DEAD, STUN, HOVER, MOUNT, UNKNOWN
				/if (${Select[${Spawn[${CombatTargetID}].State},DEAD,UNKNOWN,NULL]} && ${Select[${Spawn[${CombatTargetID}].Type},Untargetable,Mount,Corpse,Chest,Trigger,Trap,Timer,Item,Mercenary,Aura,Object,Banner,Campfire,Flyer,NULL]}) {
					/varset CombatTargetID 0
				} else /if (!${Toggle-pvpmode}) {
					/if (${Select[${Spawn[${CombatTargetID}].Type},PC]} || ${Select[${Spawn[${Target.ID}].Type},PC]}) {
						/varset CombatTargetID 0
					} else /if (${Select[${Spawn[${CombatTargetID}].Type},Pet]} && ${Select[${Spawn[${CombatTargetID}].Master.Type},PC]} || ${Select[${Spawn[${Target.ID}].Type},Pet]} && ${Select[${Spawn[${Target.ID}].Master.Type},PC]}) {
						/varset CombatTargetID 0
					} else /if (${Target.ID} != ${CombatTargetID}) {
						|:/if (${Toggle-autotarget} || !${Bool[${Target.ID}]}) /Target id ${CombatTargetID}
					}
				} else /if (${Target.ID} != ${CombatTargetID}) {
					|:/if (${Toggle-autotarget} || !${Bool[${Target.ID}]}) /Target id ${CombatTargetID}
				}
			}
		}
		
	}
	
	:EndCombat
	/Call Debug_Spew "CombatTargetID: [${CombatTargetID}] CombatTargetID Cleared: [${If[${Bool[${CombatTargetID}]},FALSE,TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Bool[${CombatTargetID}]} || !${Bool[${CombatTargetID}]} && ${Bool[${Target.ID}]}) {
		/if (${Select[${Spawn[${CombatTargetID}].State},DEAD,UNKNOWN,NULL]} && ${Select[${Spawn[${CombatTargetID}].Type},Untargetable,Mount,Corpse,Chest,Trigger,Trap,Timer,Item,Mercenary,Aura,Object,Banner,Campfire,Flyer,NULL]}) {
			/if (${Toggle-autotargetclear}) /squelch /nomodkey /docommand /Target clear
		}
		/if (${Me.Combat} || ${Me.AutoFire} || ${Bool[${Me.Casting.ID}]}) {
			
			/Call Debug_Spew "Shutting Combat Down." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			
			|: Clear Combat Variables.
			/varset CombatTargetID 0
			/varset EnrageVar 0
			/varset DebuffList
			/varset interruptFlag TRUE
			
			|: Turn Stick, Combat, Archery, Casting OFF.
			/if (${Stick.Active}) /squelch /nomodkey /docommand /stick off
			/if (${Me.Combat} && ${Toggle-melee}) /squelch /nomodkey /docommand /attack off
			/if (${Me.AutoFire} && ${Toggle-archery}) /squelch /nomodkey /docommand /autofire off
			/if (${Me.Casting.ID} && ${Toggle-debuffs} || ${Me.Casting.ID} && ${Toggle-autochainnuke}) /squelch /nomodkey /docommand /interrupt
			/Call Debug_Spew "Stick Status: [${Stick.Active}] Combat Status: [${Me.Combat} && ${Toggle-melee}] Archery Status: [${Me.AutoFire} && ${Toggle-archery}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			
			|: IF AutoFollow = On, Then Reaquire Follow Target after Combat.
			/if (!${Bool[${CombatTargetID}]}) {
				|:Autofollow Leashing if Distance Less then ${FollowLeashSetting.Arg[2,|]} and > then ${FollowLeashSetting.Arg[1,|]}.
				/Call Debug_Spew "AutoFollowTarget: [${If[${Bool[${autofollowTarget}]},${autofollowTarget},NONE]}] Dead: [${Spawn[${autofollowTarget}].State.Equal[DEAD]}] Corpse: [${Spawn[${autofollowTarget}].Type.Equal[Corpse]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				/if (${Spawn[${autofollowTarget}].State.NotEqual[DEAD]} && ${Spawn[${autofollowTarget}].Type.NotEqual[Corpse]}) {
					/Call Debug_Spew "${Spawn[${autofollowTarget}].Distance.Int} > ${FollowLeashSetting.Arg[1,|]} && ${Spawn[${autofollowTarget}].Distance.Int} < ${FollowLeashSetting.Arg[2,|]} && ${Toggle-autofollow}" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
					/if (${Spawn[${autofollowTarget}].Distance.Int} > ${FollowLeashSetting.Arg[1,|]} && ${Spawn[${autofollowTarget}].Distance.Int} < ${FollowLeashSetting.Arg[2,|]} && ${Toggle-autofollow}) /call FollowReAquire
				}
			}
	
		} else {
			/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/return
		}
	}
	
	|: Turn Attack OFF IF Melee & Archery OFF
	/Call Debug_Spew "Turn Melee/Archery OFF: [${If[${Me.Combat} && !${Toggle-melee},TRUE,FALSE]}/${If[${Me.AutoFire} && !${Toggle-archery},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) {
		/if (${Me.Combat} && !${Toggle-melee}) /attack off
		/if (${Me.AutoFire} && !${Toggle-archery}) /autofire off
	}

	|: Target CombatTargetID
	/Call Debug_Spew "TargetID: [${Target.ID}] CombatTargetID: [${CombatTargetID}] CombatTargetID In Zone: [${If[${SpawnCount[id ${CombatTargetID}]} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) {
		/if (${Target.ID} != ${CombatTargetID} && ${SpawnCount[id ${CombatTargetID}]} > 0) {
			/if (${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-debuffs}) {
				/if (!${Toggle-autotarget}) {
					/if (${CombatID.Equal[NULL]} || ${CombatID.Length} == 0) /varset CombatID 0
					|: && ${CombatID} != 0
					/if (${Bool[${Target.ID}]} && ${CombatID} != ${CombatTargetID}) /varset CombatTargetID ${Target.ID}
					/Target id ${CombatTargetID}	
				} else {
					/Target id ${CombatTargetID}
				}
			}
		}
	}

			
	|: Turn Attack on [IF] CombatTargetID
	/Call Debug_Spew "Turn Melee/Archery ON: [${If[!${Me.Combat} && ${Toggle-melee} && !${Toggle-manualmode},TRUE,FALSE]}/${If[!${Me.AutoFire} && ${Toggle-archery} && !${Toggle-manualmode},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) {
		/if (!${Me.AutoFire} || !${Me.Combat}) {
			/if (!${Window[SpellBookWnd].Open} && ${Me.State.NotEqual[FEIGN]}) {
				/if (!${Me.Combat} && ${Toggle-melee} && !${Toggle-manualmode}) /attack on
				/if (!${Me.AutoFire} && ${Toggle-archery} && !${Toggle-manualmode}) /autofire on
			}
		}
	}

	|: Face Target [IF] AutoSnap == ON
	/Call Debug_Spew "Auto Face Target: [${If[${Toggle-autosnap},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) {
		/if (${Toggle-autosnap}) /squelch /Face fast
	}
	
	|: Stand IF CombatTargetID
	/Call Debug_Spew "Auto Stand: []" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) {
			/if (${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-debuffs}) {
				/if (${Toggle-autostand} && ${Me.State.NotEqual[STAND]} && !${Window[SpellBookWnd].Open}) /squelch /stand
			}
	}
	
	|: Check Targets to Never Attack Name/ID
	/Call Debug_Spew "Call [CheckNeverKill] Params: [${CombatTargetID}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${CombatTargetID}) /call CheckNeverKill
	
	/Call Debug_Spew "Return [CheckNeverKill] End Combat: [${If[${Bool[${CombatTargetID}]},FALSE,TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Bool[${CombatTargetID}]}) /goto :EndCombat
	
	|: Check IF [CombatTargetID].Distance > [MaxTargetRange].
	/Call Debug_Spew "CombatID: [${CombatTargetID}] Distance Check: [${Spawn[${CombatTargetID}].Distance.Int} > ${MaxTargetRange}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Spawn[${CombatTargetID}].Distance.Int} > ${MaxTargetRange}) {
		/call ChatOut COMBAT "The Target [${Target.CleanName}] is outside MaxTargetRange of ${MaxTargetRange}, He is at Distance [${Spawn[${CombatTargetID}].Distance.Int}]" "0"
		/varset CombatTargetID 0
		/if (!${Bool[${CombatTargetID}]}) /goto :EndCombat
	}

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
/return

|:-----------------------------------------------------------------------
|: CheckNeverKill: Checks Ini File for Target to Never kill.
|:-----------------------------------------------------------------------
Sub CheckNeverKill(string CheckID)

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/if (${CheckID.Length} == 0 && ${Bool[${CombatTargetID}]}) /varset CheckID ${CombatTargetID}
	
	|: IF NeverKill Not Set THEN Return TRUE
	/Call Debug_Spew "Check NeverKill Not Set: [${NeverKill.Equal[${NeverKill-DefaultValue}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${NeverKill.Equal[${NeverKill-DefaultValue}]}) {
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/return TRUE
	}
	
	|: Cleanup [NeverKill] Names Replacing Space with _
	/if (${NeverKill.Find[ ]}) /varset NeverKill ${NeverKill.Replace[ ,_]}
	
	|: IF Find CHECKID.Name in NeverKill List Return FALSE
	/Call Debug_Spew "Find: [${CheckID}] IN NeverKill: [${Select[${Spawn[${CheckID}].CleanName.Replace[ ,_]},${NeverKill.Replace[|,,]}]}]  " "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Select[${Spawn[${CheckID}].CleanName.Replace[ ,_]},${NeverKill.Replace[|,,]}]}) {
		/varset CombatTargetID 0
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/return FALSE
	}

	|: IF Find CHECKID.ID in NeverKill List Return FALSE
	/Call Debug_Spew "Find: [${CheckID}] IN NeverKill: [${Select[${Spawn[${CheckID}].ID},${NeverKill.Replace[|,,]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Select[${Spawn[${CheckID}].ID},${NeverKill.Replace[|,,]}]}) {
		/varset CombatTargetID 0
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/return FALSE
	}
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		
/return TRUE


|:----------------------------------------------------------------------
|: Used for checking if an NPC is attacking someone.
|: Usage /call CheckIsLookingAt "id of mob to check" "id of PC to check"
|:----------------------------------------------------------------------

Sub CheckIsLookingAt(int MobID,int PCID)
/declare MobHeading int local 0
/declare HeadingToPC int local
/declare DeltaX local float
/declare DeltaY local float
/declare HeadingDelta local Float

/Target id ${Spawn[id ${MobID}].ID}

/if (${Spawn[id ${MobID}].ID}) {
	/varcalc MobHeading ${Spawn[id ${MobID}].Heading.Degrees}
	/varcalc DeltaX ${Spawn[id ${PCID}].X}-${Spawn[id ${MobID}].X}
	/varcalc DeltaY ${Spawn[id ${PCID}].Y}-${Spawn[id ${MobID}].Y}
	/if (${DeltaX} > 0) {
		/varcalc HeadingToPC ${Math.Atan[${DeltaY}/${DeltaX}]}+270
	} else /if (${DeltaX} < 0) {
		/varcalc HeadingToPC ${Math.Atan[${DeltaY}/${DeltaX}]}+90
	} else {
		/if (${DeltaY} > 0) {
			/varcalc HeadingToPC 90
		} else {
			/varcalc HeadingToPC 270
		}
	}
	/varcalc HeadingDelta ${Math.Abs[${HeadingToPC}-${MobHeading}]}
	|:/echo DeltaY ${DeltaY} DeltaX ${DeltaX}  Atan ${Math.Atan[${DeltaY}/${DeltaX}]}
	|:/echo Mob ${Spawn[id ${MobID}].Name} MobHeading ${MobHeading} HeadingToPC ${HeadingToPC} HeadingDelta ${HeadingDelta}
	/if (${Me.TargetOfTarget.ID} == ${Spawn[id ${PCID}].ID}) {
		/if (${HeadingDelta} < 4 || ${HeadingDelta} > 356) {
			/return TRUE
		}
	}

}

/return FALSE


Sub RaidEvade(string EvadeDelay)

/if (!${Defined[tmpCombatTargetID]}) /declare tmpCombatTargetID int local 0

/if (${Me.TargetOfTarget.Name.Equal[${Me.CleanName}]} && ${Me.Combat} || ${Me.TargetOfTarget.Name.Equal[${Me.CleanName}]} && ${Me.AutoFire}) {
	
	|: Set Temp Variable with CombatTargetID
	/varset tmpCombatTargetID ${CombatTargetID}
	/call ChatOut 3 "I grabbed argo from [${Spawn[id ${tmpCombatTargetID}].CleanName}], turning off attack temporary." "0"
	
	|: Clear Current CombatTargetID & Turn Attack|Archery OFF
	/varset CombatTargetID 0
	/if (${Me.Combat} && ${Toggle-melee}) /squelch /nomodkey /docommand /attack off
	/if (${Me.AutoFire} && ${Toggle-archery}) /squelch /nomodkey /docommand /autofire off
	
	|: Disable Sticking to Current Target & Clear Target.
	/if (${Stick.Active}) /squelch /nomodkey /docommand /stick off
	/if (${Target.ID}) /squelch /nomodkey /docommand /Target clear
	
	|: Flush all Current Events.
	/doevents flush
	
	|: IF MONK|Shadow Knight|Necromancer Doability Feign & Wait 15 Tenths of a Second.
	/if (${Select[${Me.Class.ShortName.Upper},MNK,SHD,NEC]}) /call ExecCommand "feign"
	/delay ${EvadeDelay}
	
	|: Stand IF Feign & Resume CombatTargetID 
	/if (${Me.State.NotEqual[STAND]}) /squelch /nomodkey /docommand /stand
	/varset CombatTargetID ${tmpCombatTargetID}
	
	|: Combatcheck Used to check if attack is on and should not be
	/call Combatcheck ${CombatTargetID}
	/Call Debug_Spew "CombatTargetID [${CombatTargetID}] Status: [${If[${CombatTargetID} != 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${CombatTargetID} == 0) /return
	
	/squelch /nomodkey /docommand /Target id ${CombatTargetID}
	/call ChatOut 3 "My target is now [${Target.CleanName}]." "0"

	/if (!${Me.Combat} && ${Toggle-melee}) /squelch /nomodkey /docommand /attack on
	/if (!${Me.AutoFire} && ${Toggle-archery}) /squelch /nomodkey /docommand /autofire on
	
}

/return


Sub AutoProtect

	/if (!${Defined[i]}) /declare i int local
	/if (!${Defined[GenFor]}) /declare GenFor int local
	/declare MobID int local
	/declare NPCName string local
	/if (!${Defined[a]}) /declare a int local
		
	|:Check if I need to Protect my ProtectionList.

	/if (${Bool[${ProtectionList.Find[|]}]}) {

		/if (${ProtectionList.Find[People to Protect]}) {
			/varset ProtectionList ${Masters.Replace[|, ]} 	
		} else /if (${ProtectionList.Upper.Find[BOTS]}) {
			/if (${ProtectionList.Upper.Find[|BOTS]}) {
				/varset ProtectionList ${ProtectionList.Replace[|BOTS,]}
				/varset ProtectionList ${Masters.Replace[|, ]} ${ProtectionList.Replace[|, ]}
			} else /if (${ProtectionList.Upper.Find[BOTS|]}) {
				/varset ProtectionList ${ProtectionList.Replace[BOTS|,]}
				/varset ProtectionList ${Masters.Replace[|, ]} ${ProtectionList.Replace[|, ]}
			} else /if (${ProtectionList.Upper.Find[ BOTS]}) {
				/varset ProtectionList ${ProtectionList.Replace[ BOTS,]}
				/varset ProtectionList ${Masters.Replace[|, ]} ${ProtectionList}
			} else /if (${ProtectionList.Upper.Find[BOTS ]}) {
				/varset ProtectionList ${ProtectionList.Replace[BOTS ,]}
				/varset ProtectionList ${Masters.Replace[|, ]} ${ProtectionList}
			} else /if (${ProtectionList.Upper.Find[BOTS]}) {
				/varset ProtectionList ${ProtectionList.Replace[BOTS,]}
				/varset ProtectionList ${Masters.Replace[|, ]} ${ProtectionList}
			}
		} else  /if (${ProtectionList.Find[|]}) {
			/varset ProtectionList ${ProtectionList.Replace[|, ]}
		}
		
	}
		
	/if (${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-petona} && ${Me.Pet.ID} || ${Toggle-debuffs}) {
		
		/for GenFor 1 to ${Math.Calc[${ProtectionList.Count[ ]}+1].Int}
			/if (${Int[${Spawn[pc ${ProtectionList.Arg[${GenFor}, ]}].NearestSpawn[${GenFor}, NPC zradius 15, radius ${ProtectRadius} los].ID}]} != 0) {
				/varset MobID ${Spawn[pc ${ProtectionList.Arg[${GenFor}, ]}].NearestSpawn[${GenFor}, NPC zradius 15, radius ${ProtectRadius} los].ID}
				/call CheckIsLookingAt ${MobID} ${Spawn[pc ${ProtectionList.Arg[${GenFor}, ]}].ID}
				/if (${Macro.Return}) /break
			}
		/next GenFor

		:Protect
		/if (${MobID} && ${CombatTargetID} != ${MobID}) {
	
			/for GenFor 1 to ${Math.Calc[${ProtectionList.Count[ ]}+1].Int}
				
				/if (${Macro.Return}) {
					
					/call CheckNeverKill ${MobID}

					/if (${Macro.Return} && !${CombatTargetID} && ${MobID} != ${CombatTargetID}) {
						
						/if (${Int[${Guard_Protect_Alert}]} != 0) { 
							|: Alert Spawns
							/for a 1 to ${Guard_Protect_Alert}
								/beep
								/delay 3
							/next a
						}
						
						/Target id ${MobID}
						/varset CombatTargetID ${MobID}
						/varset NPCName ${Spawn[${MobID}].CleanName.Replace[ ,_]}
						/delay 5
			
						/call ChatOut 3 "How dare [${NPCName}] attacks my master [${ProtectionList.Arg[${GenFor}, ]}]?!  I must punish this insolence!" "0"
						
						|:Combatcheck Used to check if attack is on and should not be:|
						/call Combatcheck
						
						|: Send Pet to attack IF CombatTargetID
						/if (${CombatTargetID} && ${Toggle-petona} && ${Me.Pet.ID} && !${Bool[${Me.Pet.Following}]}) {
							/if (${Target.ID} != ${CombatTargetID}) /Target id ${CombatTargetID}
							/squelch /Pet Attack
						}	
						
						|:Send Bot to attack IF CombatTargetID
						/if (${CombatTargetID} != 0 && ${Toggle-melee} || ${CombatTargetID} != 0 && ${Toggle-archery}) /call CombatMain


						|: Check IF autochainnuke = [ON], I have CombatTargetID Set, CombatTargetID HP [Less Then] ini Setting ChainNukePct
						/if (${Toggle-autochainnuke} && ${ChainNukePct.NotEqual[${ChainNukePct-DefaultValue}]}) {
							/if (${CombatTargetID} && ${Spawn[id ${CombatTargetID}].PctHPs} < ${ChainNukePct}) /call AutoChainNuke
						}

						/if (${Toggle-debuffs} && ${CombatTargetID}) /call AssistDebuffs

					}

				}
			
			/next GenFor
		}

	}

/return

Sub AutoGuard
	|: https://www.redguides.com/wiki/TLO:SpawnSort
	|: https://docs.macroquest.org/reference/data-types/datatype-xtarget/
	|: ${Me.XTarget} = Count
	|: ${Me.XTarget[1]} or ${XTarget[1]}
	|: ${XTarget.Max} = Max xTarget
	|: /xtarget set ${i} autohater
	|: ${Me.XTarget[1].PctAggro}
	|: ${Me.XTarget[1].TargetType}
	|: guardxtar = ON/OFF | Top/Bottom
	|: guardMA = ON/OFF | Target
	

	|:Check if I need to Search and Scan area for Enemy.
	|:${Spawn[npc radius ${GuardRadius}].ID} && ${Spawn[npc radius ${GuardRadius}].LineOfSight}

	|:/varset IsHead ${Me.Heading.DegreesCCW}
	|:/varset IsZone ${Zone.ID}
	|:/varset Ypos ${Me.Y}
	|:/varset Xpos ${Me.X}
	
	|: Move Bot back to Guard Location & Check if Guard should be ON.
	/if (${IsCamp} == 1 && !${CombatTargetID} && ${Math.Distance[${Ypos},${Xpos}]} > ${GuardRadius}) /call CheckCamp

	/if (${Math.Distance[${Ypos},${Xpos}]} <= ${GuardRadius}) {
		
		/if (!${Defined[nearSpawn]}) /declare nearSpawn int local 0
		/if (!${Defined[gLoopMinMax]}) /declare gLoopMinMax string local
		
		/if (!${CombatTargetID} && ${GuardXTar.Arg[1,|].Upper.Equal[ON]} && ${GuardMA.Arg[1,|].Upper.Equal[OFF]}) {
			/if (${GuardXTar.Arg[2,|].Upper.Equal[TOP]}) /varset gLoopMinMax 1|${XTarget.Max}|to
			/if (${GuardXTar.Arg[2,|].Upper.Equal[Bottom]}) /varset gLoopMinMax ${XTarget.Max}|1|downto
			
			/if (!${Defined[i]}) /declare i int local
			/for i ${gLoopMinMax.Arg[1,|]} ${gLoopMinMax.Arg[3,|]} ${gLoopMinMax.Arg[2,|]}
				/if (${Me.XTarget[${i}].ID} != NULL) /varset nearSpawn ${Me.XTarget[${i}].ID}
				/if (${nearSpawn}) /break
			/next i
		} else /if (!${CombatTargetID} && ${GuardMA.Arg[1,|].Upper.Equal[ON]} && ${GuardXTar.Arg[1,|].Upper.Equal[OFF]}) {
			/call TargetofTarget ${Spawn[${GuardMA.Arg[2,|]}].ID}
			/delay 2
			/if (${Bool[${Macro.Return}]}) /varset nearSpawn ${Macro.Return}
		} else /if (!${CombatTargetID} && ${GuardXTar.Arg[1,|].Upper.Equal[OFF]} && ${GuardMA.Arg[1,|].Upper.Equal[OFF]}) {
			/if (!${Defined[i]}) /declare i int local
			/for i 1 to 25
				/if (${Int[${NearestSpawn[${i}, NPC zradius 15, radius ${GuardRadius} los].ID}]} != 0) /varset nearSpawn ${NearestSpawn[${i}, NPC zradius 15, radius ${GuardRadius} los].ID}
				/if (${nearSpawn}) /break
			/next i
		} else /if (${GuardXTar.Arg[1,|].Upper.Equal[ON]} && ${GuardMA.Arg[1,|].Upper.Equal[ON]}) {
			/call ChatOut 3 "Something went wrong turning Guard OFF!, Please only Enable one Guard Method Current GuardXTar:[${GuardXTar.Arg[1,|]}] GuardMA:[${GuardMA.Arg[1,|]}]" "0"
			/varset Toggle-guard FALSE
		}
				
		|: Move Bot back to Guard Location & Check if Guard should be ON.
		/if (${IsCamp} == 1 && !${CombatTargetID}) /call CheckCamp
		
		/if (${Int[${nearSpawn}]} == 0) /return
		/if (${Spawn[ID ${nearSpawn}].Type.Equal[npc]} && ${Spawn[ID ${nearSpawn}].Distance} <= ${GuardRadius} && ${Spawn[ID ${nearSpawn}].LineOfSight}) {

			/if (!${CombatTargetID} && ${Math.Distance[${Ypos},${Xpos}]} <= ${GuardRadius}) {
				
				|: IF PULLER and Not in 1/3 Distance of of Guard Location Wait till Closer.
				/if (${Toggle-puller} && ${Math.Distance[${Ypos},${Xpos}]} > ${Math.Calc[${GuardRadius}/3]}) /return
				
				|: Set [CombatTargetID].
				/if (${Toggle-melee} || ${Toggle-archery} || ${Toggle-autochainnuke} || ${Toggle-petona} && ${Me.Pet.ID} || ${Toggle-debuffs}) /varset CombatTargetID ${nearSpawn}
				/delay 2
				
				|:Combatcheck Used to check if attack is on and should not be:|
				/call Combatcheck
				
				/if (${CombatTargetID}) {
					
					|: Have Bot do Beeps if Set to ON.
					/if (!${Defined[a]}) /declare a int local
					/if (${Int[${Guard_Protect_Alert}]} != 0) { 
						|: Alert Spawns
						/for a 1 to ${Guard_Protect_Alert}
							/beep
							/delay 3
						/next a
					}
							
					/if (${Target.ID} != ${CombatTargetID}) /Target id ${CombatTargetID}
							
					/call ChatOut 3 "Intruder alert!  Attacking the trespassing [${Spawn[ID ${CombatTargetID}].Name}]!." "0"

					|: Send Pet to attack IF CombatTargetID
					/if (${Toggle-petona} && ${Me.Pet.ID} && !${Bool[${Me.Pet.Following}]}) /squelch /Pet Attack
							
					|:Send Bot to attack IF CombatTargetID
					/if (${CombatTargetID} != 0 && ${Toggle-melee} || ${CombatTargetID} != 0 && ${Toggle-archery}) /call CombatMain


					|: Check IF autochainnuke = [ON], I have CombatTargetID Set, CombatTargetID HP [Less Then] ini Setting ChainNukePct
					/if (${Toggle-autochainnuke} && ${ChainNukePct.NotEqual[${ChainNukePct-DefaultValue}]}) {
						/if (${CombatTargetID} && ${Spawn[id ${CombatTargetID}].PctHPs} < ${ChainNukePct}) /call AutoChainNuke
					}

					/if (${Toggle-debuffs} && ${CombatTargetID}) /call AssistDebuffs

				}
			
			}
		}
	
	}
	
/return


#event Attacking       "You pierce #*#"
#event Attacking       "You slash #*#"
#event Attacking       "You Hit #*#"
#event Attacking       "You Bash #*#"
Sub Event_Attacking

/return


#event DisarmTrap      "You have disarmed #*#"
Sub Event_DisarmTrap
/call Delay 2s
/call ChatOut 17 ${DisarmTrap-msg} "0"
/return

|------------------------------------------------------------|
|- Turns off attack, when a mob you're attacking enrages.	-|
|------------------------------------------------------------|
#event EnrageOn "#1# has become ENRAGED."
#event EnrageOn "#*#|${Spawn[id ${CombatTargetID}].CleanName}| has become ENRAGED#*#"
Sub Event_EnrageOn

	|: Check IF Enrage = OFF & Melee OFF OR IF Enrage = OFF & Archery OFF OR Enrage Target ID Defined THEN Return.
	/if (!${Toggle-enrage} && ${EnrageVar} > 0) /return

	/if (${Toggle-enrage} && ${CombatTargetID} && (${Toggle-melee} || ${Toggle-archery})) {
		|: Set EnrageVar TO CombatTargetID && Clear CombatTargetID
		/varset EnrageVar ${CombatTargetID}
		/varset CombatTargetID 0
		
		|: Turn OFF Stick,Attack,Archery && Back Off Pets!
		/if (${Stick.Active}) /stick off
		/if (${Me.Combat} && ${Toggle-melee}) /attack off
		/if (${Me.AutoFire} && ${Toggle-archery}) /autofire off
		/if (${Toggle-petona} && ${Me.Pet.ID} && ${Bool[${Me.Pet.Following}]}) /pet back off
		
		|: Call Out Bot Enrage Message.
		/call ChatOut 17 "[+r+][Enrage Detected!] [+w+]Target: [+y+]${Spawn[${EnrageVar}].CleanName}[+r+]!" "0"
	}

/return

|------------------------------------------------|
|- Turns attack back on, after enrage is over.	-|
|------------------------------------------------|
#event EnrageOff "#1# is no longer enraged."
#event EnrageOff "#*#|${Spawn[id ${CombatTargetID}].CleanName}| is no longer enraged#*#"
Sub Event_EnrageOff

	|: Check IF Enrage Target ID & Spawn Exist & Spawn NOT = Corpse.
	/if (${EnrageVar} != 0 && ${Spawn[${EnrageVar}].ID} && ${Spawn[${EnrageVar}].Type.NotEqual[Corpse]}) {
		|: Reset Enrage Variables 
		/varset CombatTargetID ${EnrageVar}
		/varset EnrageVar 0
		/delay 2
		
		|: Re-Acquire Target CombatTargetID 
		/Target id ${CombatTargetID}
		/delay 5 ${Target.ID}==${CombatTargetID}
		
		|:Display Message No Longer Enraged!
		/call ChatOut 17 "[+r+][Enrage Done!] [+w+]Target: [+y+]${Spawn[${CombatTargetID}].CleanName}[+r+]!" "0"
		
		|: Turn Attack Back ON
		/if (!${Me.Combat} && ${Toggle-melee}) /attack on
		/if (!${Me.AutoFire} && ${Toggle-archery}) /autofire on
		/if (${Target.ID} == ${CombatTargetID} && ${Toggle-petona} && ${Me.Pet.ID} && !${Bool[${Me.Pet.Following}]}) /pet attack
		
		|: Jump Back INTO CombatMain
		/if (${CombatTargetID} && !${Toggle-autochainnuke} || ${Me.Combat} || ${Me.AutoFire}) /call CombatMain
		
	} else {
		/varset EnrageVar 0
	}

/return


#event UnderAttack "#1# tries to #*# YOU, but #*#"
#event UnderAttack "#1# bashes YOU for #*#"
#event UnderAttack "#1# crushes YOU for #*#"
#event UnderAttack "#1# hits YOU for #*#"
#event UnderAttack "#1# kicks YOU for #*#"
#event UnderAttack "#1# punches YOU for #*#"
#event UnderAttack "#1# slashes YOU for #*#"
Sub Event_UnderAttack(string Line, string Attacker)

	|: Turn Attack off 15 10th's of a Seconds if im CombatTargetID's Target.
	/if (${Me.TargetOfTarget.Name.Equal[${Me.CleanName}]} && ${Toggle-raidevade}) /call RaidEvade 15

	/if (!${CombatTargetID} && ${Toggle-defend}) {
		
		/if (!${Defined[MobID]}) /declare MobID string local 0
		/if (!${Defined[NPCName]}) /declare NPCName string local

		/varset MobID ${NearestSpawn[1, npc "${Attacker}"].ID}
		/delay 10
		
		/if (${Spawn[${MobID}].Distance} < ${MaxTargetRange}) {
			
			/call CheckNeverKill ${MobID}

			/if (${Macro.Return}) {
				/Target id ${MobID}
				
				/if (${Target.Type.Equal[NPC]}) {
					/varset CombatTargetID ${MobID}
					/varset NPCName ${Spawn[${MobID}].CleanName.Replace[ ,_]}
					/delay 5
					
					/call ChatOut 17 "I've been attacked by [${NPCName}]!  Attacking right back!" "0"
					
					|:Combatcheck Used to check if attack is on and should not be:|
					/call Combatcheck
					
					|: Send Pet to attack IF CombatTargetID
					/if (${CombatTargetID} && ${Toggle-petona} && ${Me.Pet.ID} && !${Bool[${Me.Pet.Following}]}) {
						/if (${Target.ID} != ${CombatTargetID}) /Target id ${CombatTargetID}
						/squelch /Pet Attack
					}	
					
					|:Send Bot to attack IF CombatTargetID
					/if (${CombatTargetID}) {
					
						/if (${Toggle-autochainnuke}) {
							/if (${ChainNukePct.NotEqual[${ChainNukePct-DefaultValue}]} && ${ChainNuke.NotEqual[${ChainNuke-DefaultValue}]}) {
								/if (${Spawn[${CombatTargetID}].PctHPs} < ${ChainNukePct}) /call AutoChainNuke
							}
						}
						
						/if (${Toggle-debuffs} && ${DebuffSpell#1.NotEqual[${DebuffSpell#1-DefaultValue}]}) /call AssistDebuffs
						
						/if (${Toggle-melee} || ${Toggle-archery} || ${Me.Combat} || ${Me.AutoFire}) /call CombatMain
					
					}


				}
			}
		}

	}
	
/return


|:----------------------------------------------------------------------
|: MeleeAbility Used to do melee abilities if vars are set to.
|: Usage /call MeleeAbility
|:----------------------------------------------------------------------

Sub MeleeAbility
	/if (!${Defined[localName]}) /declare localName string local ${Me.Name}
	/if (!${Defined[localrace]}) /declare localrace string local ${Me.Race}

	|: Taunt ability - 
	/if (${Toggle-taunt} && ${Me.AbilityReady[Taunt]} && ${Me.PctAggro} < 100) /doability "Taunt"
	|: ---

	|: Slam ability
	/if (${Toggle-slam}) {
		/if (!${Defined[AbilityCheck]}) /declare AbilityCheck string local First|Second|Third|Fourth|Fifth|Sixth|
		/if (!${Defined[i]}) /declare i int local
		/for i 1 to ${AbilityCheck.Count[|]}
			|: 1-6 First | Second | Third | Fourth | Fifth | Sixth && ${Target.Distance.Int} <= 17
			/if (${i} <= 6) {
				/if (${Window[ActionsAbilitiesPage].Child[AAP_${AbilityCheck.Arg[${i},|]}AbilityButton].Text.Equal[Slam]} && !${Window[ActionsAbilitiesPage].Child[AAP_${AbilityCheck.Arg[${i},|]}AbilityButton].Checked}) {
					/notify ActionsAbilitiesPage AAP_${AbilityCheck.Arg[${i},|]}AbilityButton LeftMouseUp
					/break
				} else /if (${Window[ActionsAbilitiesPage].Child[AAP_${AbilityCheck.Arg[${i},|]}AbilityButton].Checked}) {
					/break
				}
			}
			
			|: 1-4 First | Second | Third | Fourth && ${Target.Distance.Int} <= 17
			/if (${i} <= 4) {
				/if (${Window[ActionsCombatPage].Child[ACP_${AbilityCheck.Arg[${i},|]}AbilityButton].Text.Equal[Slam]} && !${Window[ActionsCombatPage].Child[ACP_${AbilityCheck.Arg[${i},|]}AbilityButton].Checked}) {
					/notify ActionsCombatPage ACP_${AbilityCheck.Arg[${i},|]}AbilityButton LeftMouseUp
					/break
				} else /if (${Window[ActionsCombatPage].Child[ACP_${AbilityCheck.Arg[${i},|]}AbilityButton].Checked}) {
					/break
				}
			}
		/next i
	}
	|: ---

	|: Bash ability  - [Cleric,Paladin,Shadow Knight,Warrior] ${Target.Distance.Int} <= 15
	/if (${Toggle-bash} && ${Me.AbilityReady[Bash]}) {
		/if (${Me.Inventory[Offhand].Type.Equal[Shield]}) /doability "Bash"
		/if (!${Me.Inventory[Offhand].Type.Equal[Shield]} && ${Me.AltAbilityReady[2 Hand Bash]}) {
			/if  (${Me.Inventory[Mainhand].Type.Left[2].Equal[2H]}) /doability "Bash"
		}
	}
	|: ---

	|: Kick ability - [Warrior,BeastLord,Berserker,Monk,Ranger] ${Target.Distance.Int} <= 15
	/if (${Toggle-kick} && ${Me.AbilityReady[Kick]} && !${Toggle-archery}) {
		/doability "Kick"
	}
	|: ---

	|: Disarm ability
	/if (${Toggle-disarm} && ${Me.AbilityReady[Disarm]}) {
		/doability "Disarm"
	}
	|: ---

	/if (${Select[${Me.Class.ShortName.Upper},MNK]}) {
		|: Flying Kick ability
		/if (${Toggle-flyingkick} && ${Me.AbilityReady[Flying Kick]}) {
			/doability "Flying Kick"
		}
		|: ---

		|: Round Kick ability
		/if (${Toggle-roundkick} && ${Me.AbilityReady[Round Kick]}) {
			/doability "Round Kick"
		}
		|: ---

		|: Eagle Strike ability
		/if (${Toggle-eaglestrike} && ${Me.AbilityReady[Eagle Strike]}) {
			/doability "Eagle Strike"
		}
		|: ---

		|: Tiger Claw ability
		/if (${Toggle-tigerclaw} && ${Me.AbilityReady[Tiger Claw]}) {
			/doability "Tiger Claw"
		}
		|: ---

		|: Mend ability
		/if (${Toggle-mend} && ${Me.AbilityReady[Mend]} && ${Me.PctHPs} <= ${PctMend}) {
			/doability "Mend"
		}
		|: ---
		
		|: Intimidation ability
		/if (${Toggle-intimidation} && ${Me.AbilityReady[Intimidation]}) {
			/doability "Intimidation"
		}
		|: ---

	}

	/if (${Select[${Me.Class.ShortName.Upper},BER]}) {
		|: Frenzy ability
		/if (${Toggle-frenzy} && ${Me.AbilityReady[Frenzy]}) {
			/doability "Frenzy"
		}
		|: ---
	}

	|: Backstab ability - [Rogue]
	/if (${Select[${Me.Class.ShortName.Upper},ROG]}) {
		/if (${Toggle-backstab} && ${Me.AbilityReady[Backstab]}) {
			
			/if (!${Me.CombatAbilityReady[${RogueStrike}]} && !${Toggle-assassinate}) /doability "Backstab"
				
			|: Assassinate ability
			/if (${Toggle-assassinate} && ${Me.AbilityReady[Backstab]}) {
				
				|: Set Best Available Assassinate Disc
				/if (${Me.CombatAbilityReady[Daggerfall]}) {
					/varset RogueStrike Daggerfall
				} else /if (${Me.CombatAbilityReady[Ancient: Chaos Strike]}) {
					/varset RogueStrike Ancient: Chaos Strike
				} else /if (${Me.CombatAbilityReady[Kyv Strike]}) {
					/varset RogueStrike Kyv Strike
				} else /if (${Me.CombatAbilityReady[Assassin's Strike]}) {
					/varset RogueStrike Assassin's Strike
				} else /if (${Me.CombatAbilityReady[Thief's Vengeance]}) {
					/varset RogueStrike Thief's Vengeance
				} else /if (${Me.CombatAbilityReady[Sneak Attack]}) {
					/varset RogueStrike Sneak Attack
				}
				
				/if (${Me.AbilityReady[Hide]} && ${Me.AbilityReady[Sneak]} && ${Me.AbilityReady[Backstab]} && ${Me.CombatAbilityReady[${RogueStrike}]} && ${Target.Distance} <= ${MeleeRange}) {

					|:Turn off Attack
					/if (${Stick.Active}) /stick off
					/if (${Me.Combat} && ${Toggle-melee}) /attack off

					/if (!${Bool[${Me.ActiveDisc.ID}]}) { 
						/if (${Me.Invis}) {
							/doability "Hide"
							/delay 2
						}
						/doability "Hide"
						/delay 5
						/doability "Sneak" 
						
						|:Target and Getbehind.
						/if (${Target.ID} != ${CombatTargetID}) /Target id ${CombatTargetID}
						/if (!${Stick.Behind}) /stick snaproll rear uw ${Math.Calc[${MeleeRange}+2]} id ${CombatTargetID}
					
						/delay 4s
						
						/if (${Me.Invis} && ${Me.Sneaking} && ${Target.ID}) {
							/call Command_disc "${RogueStrike}"
						} else {
							/if (${Target.ID}) {
								/call ChatOut 4 "Master I have Failed to Assassinate I'm not Invis." "0"
							} else {
								/call ChatOut 4 "Master I have Failed to Assassinate I have no Target." "0"
							}
						}
						
						/delay 5 ${Bool[${Me.ActiveDisc.ID}]}
						/delay 3
						/if (${Stick.Behind} && ${Target.ID} == ${CombatTargetID}) {
							/doability "Backstab"
						} else {
							/if (!${Stick.Behind}) {
								/call ChatOut 4 "Master I have Failed to Assassinate I'm not behind my Target." "0"
							} else {
								/call ChatOut 4 "Master I have Failed to Assassinate My Target is not Correct." "0"
							}
						}
					}
					
				}
					
			}
			
			/if (${Me.Invis}) {
				/doability "Hide"
				/delay 2
			}
			
			/if (${Target.ID} != ${CombatTargetID}) /Target id ${CombatTargetID}
			/if (${CombatTargetID} && !${Me.Combat} && ${Toggle-melee}) /attack on
		}
	}
	|: ---

	|: Pickpocket ability
	/if (${Select[${Me.Class.ShortName.Upper},ROG]}) {
	
		/if (${Toggle-pickpockets} && ${Me.AbilityReady[Pick Pockets]}) {
			
			/if (${Me.Combat} && ${Toggle-melee}) /attack off
			/if (${Me.AutoFire} && ${Toggle-archery}) /autofire off
			/if (${Me.Casting.ID}) /interrupt

			
			/if (!${Cursor.ID}) {
				
				|: Do the Hide Ability.
				/if (!${Me.Invis}) /doability "Hide"
				/delay 5
				
				|: Do the Pickpocket Ability.
				/if (${Me.AbilityReady[Pick Pockets]}) /doability "Pick Pockets"
				/delay 15 ${Cursor.ID}
				
				|: Check Pickpocket INI how to handle Pickpocket Item.
				/if (${Cursor.ID}) /call pickpocket_Handle
				|: Make sure Cursor is Cleared.
				/if (${Cursor.ID}) /call ClearCursor
				|: Turn off HIDE Ability.
				/if (${Me.Invis}) /doability "Hide"
				
			}
			
			/if (${Target.ID} != ${CombatTargetID}) /Target id ${CombatTargetID}
			/if (!${Me.Combat} && ${Toggle-melee}) /attack on
			/if (!${Me.AutoFire} && ${Toggle-archery}) /autofire on
		}
	}
	|: ---

	|: Aggro ability - [Paladin,Ranger,Shadow Knight,Warrior]
	/if (${Toggle-aggro}) {
	
		/if (${Me.Class.Name.Equal[Paladin]}) {
			
			|: Set Best Available Stun Spell
			/if (!${Defined[HateSpells]}) /declare HateSpells string local 
			/if (${Me.Gem[Ancient: Force of Chaos]}) /varset HateSpells ${HateSpells}Ancient: Force of Chaos|
			/if (${Me.Gem[Quellious' Word of Serenity]}) /varset HateSpells ${HateSpells}Quellious' Word of Serenity|
			/if (${Me.Gem[Force of Akilae]}) /varset HateSpells ${HateSpells}Force of Akilae|
						
			|:Keeps you up on Hate List
			/if (!${Toggle-taunt}) /varset Toggle-taunt true
			|:Make sure Autobehind off
			/if (!${Toggle-autobehind}) /varset Toggle-autobehind false
			|:Make sure autodistance off
			/if (${Toggle-autodistance}) /varset Toggle-autodistance false
			|:make sure archery is off
			/if (${Toggle-archery}) /varset Toggle-archery false
			|:Make sure Tank Close
			/if (${MeleeRange} > 7) /varset MeleeRange 7
			
			|:Increase Hate by 1
			/if (${Me.PctAggro} < 100) {
				/if (!${Defined[i]}) /declare i int local
				/for i 1 to ${HateSpells.Count[|]}
				
					/if (${CombatTargetID} == ${Target.ID} && ${Me.SpellReady[${HateSpells.Arg[${i},|]}]}) /casting "${HateSpells.Arg[${i},|]}" -targetid|${CombatTargetID}
					/delay 2
					
					/if (!${Me.SpellReady[${HateSpells.Arg[${i},|]}]}) /goto :NextSpell
					/if (${Me.PctAggro} >= 100) /break
					
					:Wait4Casting
					/if (${Me.Casting.ID}) {
						/delay 5
						/goto :Wait4Casting
					}
					
					:NextSpell
					
				/next i
			}
		} else /if (${Me.Class.Name.Equal[Ranger]}) {
			
			|: Make sure Archery is off
			/if (${Toggle-archery}) /varset Toggle-archery false
			|: Make sure Melee is on
			/if (!${Toggle-melee}) /varset Toggle-melee true
			|:Keeps you up on Hate List
			/if (!${Toggle-taunt}) /varset Toggle-taunt true
			|:Make sure Autobehind off
			/if (${Toggle-autobehind}) /varset Toggle-autobehind false
			|:Make sure autodistance off
			/if (${Toggle-autodistance}) /varset Toggle-autodistance false
			|:Make sure Tank Close
			/if (${MeleeRange} > 7) /varset MeleeRange 7
			
			|:SelfBuff with Stun Proc
			/if (${Int[${Me.Buff[Sylvan Call].ID}]} == 0 && ${Me.Gem[Sylvan Call]}) /casting "Sylvan Call"
			
			
		} else /if (${Me.Class.Name.Equal[Shadow Knight]}) {
			
			|: Set Best Available Terror Spell
			/if (!${Defined[HateSpells]}) /declare HateSpells string local 
			/if (${Me.Gem[Dread Gaze]}) /varset HateSpells ${HateSpells}Dread Gaze|
			/if (${Me.Gem[Terror of Discord]}) /varset HateSpells ${HateSpells}Terror of Discord|
			/if (${Me.Gem[Terror of Thule]}) /varset HateSpells ${HateSpells}Terror of Thule|
			/if (${Me.Gem[Terror of Terris]}) /varset HateSpells ${HateSpells}Terror of Terris|
			/if (${Me.Gem[Terror of Death]}) /varset HateSpells ${HateSpells}Terror of Death|
			/if (${Me.Gem[Terror of Shadows]}) /varset HateSpells ${HateSpells}Terror of Shadows|
			/if (${Me.Gem[Terror of Darkness]}) /varset HateSpells ${HateSpells}Terror of Darkness|
			
			|:Keeps you up on Hate List
			/if (!${Toggle-taunt}) /varset Toggle-taunt true
			|:Make sure Autobehind off
			/if (!${Toggle-autobehind}) /varset Toggle-autobehind false
			|:Make sure autodistance off
			/if (${Toggle-autodistance}) /varset Toggle-autodistance false
			|:Make sure Tank Close
			/if (${MeleeRange} > 7) /varset MeleeRange 7
			
			|:Increase Hate by 1
			/if (${Me.PctAggro} < 100) {
				/if (!${Defined[i]}) /declare i int local
				/for i 1 to ${HateSpells.Count[|]}
				
					/if (${CombatTargetID} == ${Target.ID} && ${Me.SpellReady[${HateSpells.Arg[${i},|]}]}) {
						/casting "${HateSpells.Arg[${i},|]}" -targetid|${CombatTargetID}
						/delay 2
					} else /if (!${Me.SpellReady[${HateSpells.Arg[${i},|]}]}) {
						/goto :NextSpell
					}
					
					/if (${Me.PctAggro} >= 100) /break
					
					:Wait4Casting
					/if (${Me.Casting.ID}) {
						/delay 5
						/goto :Wait4Casting
					}
					
					:NextSpell
					
				/next i
			}
		} else /if (${Me.Class.Name.Equal[Warrior]}) {
			
			|:Increase Hate
			/if (${Me.CombatAbilityReady[Mock]}) {
				/disc Mock
			} else /if (${Me.CombatAbilityReady[Bazu Bellow]}) {
				/disc Bazu Bellow
			} else /if (${Me.CombatAbilityReady[Bellow of the Mastruq]}) {
				/disc Bellow of the Mastruq
			} else /if (${Me.CombatAbilityReady[Ancient: Chaos Cry]}) {
				/disc Ancient: Chaos Cry
			} else /if (${Me.CombatAbilityReady[Incite]}) {
				/disc Incite
			} else /if (${Me.CombatAbilityReady[Berate]}) {
				/disc Berate
			} else /if (${Me.CombatAbilityReady[Bellow]}) {
				/disc Bellow
			} else /if (${Me.CombatAbilityReady[Provoke]}) {
				/disc Provoke
			} else /if (${Me.CombatAbilityReady[Elbow Strike]}) {
				/disc Elbow Strike
			} else /if (${Me.CombatAbilityReady[Throw Stone]}) {
				/disc Throw Stone
			}
		
			|:Help Hold Aggro
			/if (${localrace.NotEqual[Iksar]} && !${Toggle-slam} && ${Me.Inventory[Offhand].Type.NotEqual[Shield]}) /varset Toggle-slam false
			/if (!${Toggle-bash} && ${Me.Inventory[Offhand].Type.Equal[Shield]}) /varset Toggle-bash true
			|:Keeps you up on Hate List
			/if (!${Toggle-taunt}) /varset Toggle-taunt true
			|:Make sure Autobehind off
			/if (${Toggle-autobehind}) /varset Toggle-autobehind false
			|:Make sure autodistance off
			/if (${Toggle-autodistance}) /varset Toggle-autodistance false
			|:Make sure Tank Close
			/if (${MeleeRange} > 7) /varset MeleeRange 7
		}
	}
	|: ---

/return

|------------------------------------------------|
|- Adjust Archery distance if too far Close msg -|
|------------------------------------------------|
#Event TooClose "Your target is too close to use a ranged weapon!!"
Sub Event_TooClose
	|:/if (${CombatTargetID} && ${MoveUtils.Command.NotEqual[NONE]} && !${Me.Moving}) {
	|:	/doevents flush TooClose
	|:	|:Check if set to on for auto positioning
	|:	/if (${Toggle-autoengage}) /varcalc ArcheryRange ${ArcheryRange} + 1
	|:}
/return
						
|------------------------------------------------|
|- Adjust Melee distance if too far away msg   	-|
|------------------------------------------------|
#EVENT TooFar "Your target is too far away, get closer!"
Sub EVENT_TooFar
	|:/if (${CombatTargetID} && ${MoveUtils.Command.NotEqual[NONE]} && !${Me.Moving}) {
	|:	/doevents flush TooFar
	|:	/if (${Toggle-autoengage}) /varcalc MeleeRange ${MeleeRange} - 1
	|:}
/return