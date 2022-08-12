|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_version
/call ChatOut 3 "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" "0"
/call ChatOut 3 "Morte's Version of Genbot Macro (${main_version})" "0"
/call ChatOut 3 "robot_settings_messages Version (${Settings_version})" "0"
/call ChatOut 3 "robot_core Version (${core_version})" "0"
/call ChatOut 3 "robot_combat Version (${combat_version})" "0"
/delay 5
/call ChatOut 3 "robot_healer Version (${healer_version})" "0"
/call ChatOut 3 "robot_spell Version (${spell_version})" "0"
/call ChatOut 3 "robot_pet Version (${pet_version})" "0"
/call ChatOut 3 "robot_change_parameters Version (${change_parameters_version})" "0"
/call ChatOut 3 "robot_spawn_tracker Version (${spawn_tracker_version})" "0"
/call ChatOut 3 "robot_ninjaloot Version (${ninjaloot_version})" "0"
/delay 5
/call ChatOut 3 "robot_smooth_moves Version (${smooth_moves_version})" "0"
/call ChatOut 3 "robot_update_progression Version (${update_progression_version})" "0"
/call ChatOut 3 "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" "0"
/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_help
/declare BotChan string local
/if (!${Defined[Param0]}) {
	/call ChatOut 3 ${HelpError-msg} "0"
/return
}
/if (${Param0.Equal[Guild]})	/varset BotChan /guildsay
/if (${Param0.Equal[Private]})	/varset BotChan /echo
/if (${Param0.Equal[Tell]})	/varset BotChan /tell ${Param1}
/if (${Param0.Equal[Group]})	/varset BotChan /gsay
/if (${Param0.NotEqual[Private]} || ${Param0.NotEqual[Tell]} || ${Param0.NotEqual[Group]}) {
/call ChatOut 3 "Please say help Private | Tell | Group. are current Params Allowed." "0"
/return
}

/docommand ${BotChan}  --------=========(Robot Help)=========----------
/docommand ${BotChan}  help - Display this information!
/docommand ${BotChan}  --[CHARACTER COMMANDS]--
/docommand ${BotChan}  /gb	- Send commands From the bot window. Ex /gb sit
/docommand ${BotChan}  camp	- Commands bot to camp out to Desktop.
/docommand ${BotChan}  disc <DiscName>	- Commands bot to fire the specified /disc.
/docommand ${BotChan}  lootup <TargetName>	- Commands bot to loot a corpse, No parameter bot loots nearest corpse.
/docommand ${BotChan}  lootall	- Commands bot to attempt to loot all corpses around it.
/docommand ${BotChan}  target <Me|yourself|TargetName>	- Causes the bot to change it's target.
/docommand ${BotChan}  ** Me - targets master.
/docommand ${BotChan}  ** yourself - bot targets itself.
/docommand ${BotChan}  ** TargetName - name of target
/docommand ${BotChan}  ** no parameter - clears your current target
/docommand ${BotChan}  notarget	- Commands bot to clear it's target.
/docommand ${BotChan}  assist	- Commands bot to assist the Master(s).
/docommand ${BotChan}  accept	- Command bot to accept the current. <group invite|Trade Window|Resurrect Window>
/docommand ${BotChan}  reject	- Command bot to reject the current. <group invite|Trade Window|Resurrect Window>
/docommand ${BotChan}  consent	<Me|TargetName> - Commands bot to give consent to. <master|TargetName>
/docommand ${BotChan}  ** Me|no parameter - Commands bot to give consent to it's master.
/docommand ${BotChan}  ** TargetName - Commands bot to give consent to TargetName.
/docommand ${BotChan}  trade	- Commands bot to hit the trade button in a trade window.
/docommand ${BotChan}  yesres	- Commands bot to hit yes on a ressurection confirm box.
/docommand ${BotChan}  random <Number>	- Commands bot to /ran Number.
/docommand ${BotChan}  sit	- Makes bot sit.
/docommand ${BotChan}  stand	- Makes bot stand.
/docommand ${BotChan}  --[COMMUNICATION]--
/docommand ${BotChan}  afk <message>	- Turn bot's afk on with optional <message>.
/docommand ${BotChan}  checkname	- Toggle if set to true, bot will only respond to commands in group or chat if the command is preceeded with BotName.
/docommand ${BotChan}  exp	- Commands bot to reply with it's current exp percent.
/docommand ${BotChan}  aaexp	- Commands bot to reply percent aaexp, total unused AA's.
/docommand ${BotChan}  norelay	- Stops bot from sending received tells to it's Master(s).
/docommand ${BotChan}  relay	- Starts bot sending received tells to it's Master(s).
/docommand ${BotChan}  reportbuffs	- Commands bot to tell it's master a list of currently active buffs.
/docommand ${BotChan}  cmds	- Asks bot to return a list of available commands.
/docommand ${BotChan}  chatin <ChannelName>	- Changes what channel the bot will use for replying to it's master.
/docommand ${BotChan}  --[MOVEMENT]--
/docommand ${BotChan}  anchor	- Causes the bot to remember it's current location and return there between fights.
/docommand ${BotChan}  anchorradius <Distance>	- Tells bot the distance within which to stop moving when it is anchored.
/docommand ${BotChan}  door	- Causes the bot to attempt to open the closest door.
/docommand ${BotChan}  duck	- Commands the bot to duck.
/docommand ${BotChan}  follow <Name>	- Command bot to follow the master or his designated target.
/docommand ${BotChan}  followmode <1|2|3>	- Sets how the bot follows.
/docommand ${BotChan}  ** 1 - (Combat mode) is facing you constantly and attempting to move directly towards you.
/docommand ${BotChan}  ** 3 - (Eq's /follow) is the native /follow command used by EQ. (group members only)
/docommand ${BotChan}  stay	- Commands bot to stop following.
/docommand ${BotChan}  stop	- Forces the bot to stop, will duck, dismount and stop moving.
/docommand ${BotChan}  getbehind	- Commands bot to move behind the specified target.
/docommand ${BotChan}  moveto <Me|Loc|Name>	- commands the bot to move to a point, then stop.
/docommand ${BotChan}  ** Me - moves bot to you
/docommand ${BotChan}  ** 225,-300 - moves bot to the location 225 , -300
/docommand ${BotChan}  ** Name - moves bot to Name
/docommand ${BotChan}  movetomode <1|2>	- Sets how the bot movesto.
/docommand ${BotChan}  ** 1 - (normal) Genbot Anchor type.
/docommand ${BotChan}  traps	- Toggles bot trying to find and disarm traps.
/docommand ${BotChan}  mount	- Commands bot to get on it's mount.
/docommand ${BotChan}  --[COMBAT]--
/docommand ${BotChan}  petona	- Toggles bot doing /pet attack on assist.
/docommand ${BotChan}  defend	- Toggles bot automatically fighting back when attacked.
/docommand ${BotChan}  protect	- Toggles bot to protect the master or not.
/docommand ${BotChan}  guard	- Toggles the bot to anchor itself and protect the nearby area from NPCs.
/docommand ${BotChan}  puller	- Controls if the bot will return to it's anchor point when attacked.
/docommand ${BotChan}  autoengage	- Controls if the bot will close and engage when in combat.
/docommand ${BotChan}  autobehind	- Controls if the bot will automatically attempt to fight behind all targets during combat.
/docommand ${BotChan}  backstab	- Toggles bot using backstab while fighting.
/docommand ${BotChan}  bash	- Toggles bot using Bash during fighting.
/docommand ${BotChan}  disarm	- Toggles bot using disarm while fighting.
/docommand ${BotChan}  evade	- Toggles bot using Hide during fighting.
/docommand ${BotChan}  flyingkick	- Toggles bot using flyingkick while fighting.
/docommand ${BotChan}  frenzy	- Toggles bot using frenzy while fighting.
/docommand ${BotChan}  kick	- Toggles bot using kick while fighting.
/docommand ${BotChan}  slam	- Toggles bot using Slam during fighting.
/docommand ${BotChan}  taunt	- Toggles bot using taunt while fighting.
/docommand ${BotChan}  archery	- Toggles bot using archery while fighting.
/docommand ${BotChan}  attack	- Commands bot to start attacking.
/docommand ${BotChan}  noattack	- Commands bot to Stop attacking.
/docommand ${BotChan}  Twist	- Twists the songs/items in the order specified (up to 10 can be specified).
/docommand ${BotChan}  Mend	- Monk life lower then 75% and mend is ready then Use Ability.
/docommand ${BotChan}  hide	- Commands bot to use it's Hide ability.
/docommand ${BotChan}  rset <distance>	- Changes the range settings used in combat.
/docommand ${BotChan}  shield	- Commands bot to /shield it's master.
/docommand ${BotChan}  sneak	- Commands bot to use it's sneak ability.
/docommand ${BotChan}  EnragedMessage	- Commands bot to stop attacking if enraged message noticed.
/docommand ${BotChan}  Raidevade 	- Bot is hit it turns off attack for 30 sec.
/docommand ${BotChan}  --[CASTING]--
/docommand ${BotChan}  reportlom	- Controls if the bot will automatically report when it's low on mana.
/docommand ${BotChan}  yaulp	- Toggles if bot will use yaulp when low on mana.
/docommand ${BotChan}  canni	- Toggles if bot will cannibalize when low on mana.
/docommand ${BotChan}  aftercastsit	- Controls if the bot will sit after casting spells.
/docommand ${BotChan}  buff <Spell> <on Target>	- Commands bot to cast buff Spell on Target, bot will automatically refresh it.
/docommand ${BotChan}  buff <Spell>	- Commands bot to cast Spell on it's master.
/docommand ${BotChan}  bufflist	- Lists all buffs currently on bot
/docommand ${BotChan}  buffkeepup	- List all buffs they are keeping up on other chars.
/docommand ${BotChan}  chainnuke <Target>	- Commands bot to start chaining nukes on Target.
/docommand ${BotChan}  chainstun <Target>	- Commands bot to start chaining stuns on Target.
/docommand ${BotChan}  evac	- Commands bot to move to it's master and cast it's evac spell.
/docommand ${BotChan}  loadlist <listname>	- Commands bot to load a spell list.
/docommand ${BotChan}  mana	- Commands bot to reply with it's current mana.
/docommand ${BotChan}  sn <spell|gemNumber|item|alt> CastName	- Commands bot to cast the specified spell or item or alt ability on master's target.
/docommand ${BotChan}  ** spell|no parameter - will cast CastName on master's target.
/docommand ${BotChan}  ** gemNumber - If spell is not already memorized, memorizes it to slot Number before casting.
/docommand ${BotChan}  ** item - will right click item CastName on master's target.
/docommand ${BotChan}  ** alt - will use alt ability CastName on master's target.
/docommand ${BotChan}  snt <spell|gemNumber|item|alt> CastName <on Target>	- Commands bot to cast <spell|item> ON Target.
/docommand ${BotChan}  ** spell|no parameter - will cast CastName on Target.
/docommand ${BotChan}  ** gemNumber - If spell is not already memorized, memorizes it to slot Number before casting.
/docommand ${BotChan}  ** item - will right click item CastName on Target.
/docommand ${BotChan}  ** alt - will use alt ability CastName on Target.
/docommand ${BotChan}  spellgem <Number>	- This sets the spell gem used when bot is required to memorize a new spell. (1 to 8 or 9 with AA's)
/docommand ${BotChan}  setlompct <Percent>	- Sets the mana percent at which the bot will report low mana.
/docommand ${BotChan}  --[HEALING]--
/docommand ${BotChan}  autoheal	- Controls if the bot will automatically use heals on group and watch targets.
/docommand ${BotChan}  autohealpets	- Controls if the bot will automatically use heals on pets.
/docommand ${BotChan}  patchheal	- Controls if the bot will automatically patch heal targets below half their heal percent.
/docommand ${BotChan}  heal <Me|yourself|TargetName>	-  Commands bot to heal TargetName.
/docommand ${BotChan}  settankheal <spell>	- Sets the spell used to heal tanks.
/docommand ${BotChan}  setcasterheal <spell>	- Sets the spell used to heal casters.
/docommand ${BotChan}  setpetheal <spell>	- Sets the spell used to heal pets.
/docommand ${BotChan}  setdefaultheal <spell>	- Sets the spell used for the heal command.
/docommand ${BotChan}  setpatchheal <spell>	- Sets the spell used to patch heal.
/docommand ${BotChan}  setcasterhealpct <percent>	- Sets the HP % at which caster's will be healed.
/docommand ${BotChan}  settankhealpct <percent>	- Sets the HP % at which tank's will be healed.
/docommand ${BotChan}  setpethealpct <percent>	- Sets the HP % at which pet's will be healed.
/docommand ${BotChan}  watchtarget	- Commands bot to monitor the hit points of <target>. Needs to have autoheal on for target to be healed.
/docommand ${BotChan}  resetwatch	- Commands bot to reaquire the ID's of it's targets, good to execute after zoning.
/docommand ${BotChan}  --[SHORTCUTS]--
/docommand ${BotChan}  shortcuts <shortcutname>	- Display what <shortcutname> does, default will list all your shortcuts.
/docommand ${BotChan}
/docommand ${BotChan} ---End of Help---
/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_sit

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF Bard: [${Me.Class.Name.Equal[Bard]}] Twisting: [${Twist.Twisting}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.Class.Name.Equal[Bard]} && ${Twist.Twisting}) /return

	/Call Debug_Spew "Not Sitting: [${Me.State.NotEqual[SIT]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.State.NotEqual[SIT]}) /squelch /nomodkey /docommand /sit

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_stand

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Not Standing: [${Me.State.NotEqual[STAND]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.State.NotEqual[STAND]}) /squelch /nomodkey /docommand /stand

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_stay

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}

	|: Enable user Triggered Interrupt.
	/varset interruptFlag TRUE
	/Call Debug_Spew "interruptFlag: [${Bool[${interruptFlag}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Sets Toon to Idle.
	/varset idle TRUE
	/Call Debug_Spew "idle: [${Bool[${idle}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Turn off MoveUtils Auto follow.
	/if (${Stick.Active}) /squelch /nomodkey /docommand /stick off
	/Call Debug_Spew "Stick Status: [${Bool[${Stick.Status}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Turn off AdvPath Auto follow.
	/squelch /nomodkey /docommand /afollow off
	/Call Debug_Spew "AdvPath Status: [${If[${AdvPath.Status} == 0,OFF,${If[${AdvPath.Status} == 1,ON,${If[${AdvPath.Status} == 2,PAUSED,]}]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: Turn off Follow Target Param
	/varset FollowTargetID 0
	/Call Debug_Spew "Clear FollowTargetID: [${Bool[${FollowTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	/varset DebuffList
	/Call Debug_Spew "DebuffList Cleared: [${If[${DebuffList.Length} == 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Flush all Queued Events
	/Call Debug_Spew "Flush ALL Events" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/doevents flush
	
	|: Issue a Pet Follow command.
	/Call Debug_Spew "Pet Commands(Stop,Stance): [${Me.Pet.Stop}, ${Me.Pet.Stance}] Pet Combat: [${Me.Pet.Combat}] Pet Target: [${If[${Me.Pet.Target} == NULL,NONE,${Me.Pet.Target}]}] Pet Taunt: [${Me.Pet.Taunt}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.Pet.ID}) {
		/squelch /nomodkey /docommand /Pet Stop
		/squelch /nomodkey /docommand /Pet Back Off
		/squelch /nomodkey /docommand /Pet Guard
	}

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_stop

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}

	|: Enable user Triggered Interrupt.
	/varset interruptFlag TRUE
	/Call Debug_Spew "interruptFlag: [${Bool[${interruptFlag}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Sets Toon to Idle.
	/varset idle TRUE
	/Call Debug_Spew "idle: [${Bool[${idle}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Turn off MoveUtils Auto follow.
	/if (${Stick.Active}) /squelch /nomodkey /docommand /stick off
	/Call Debug_Spew "Stick Status: [${Bool[${Stick.Active}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Turn off AdvPath Auto follow.
	/squelch /nomodkey /docommand /afollow off
	/Call Debug_Spew "AdvPath Status: [${If[${AdvPath.Status} == 0,OFF,${If[${AdvPath.Status} == 1,ON,${If[${AdvPath.Status} == 2,PAUSED,]}]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: Turn off Follow Target Param
	/varset FollowTargetID 0
	/Call Debug_Spew "Clear FollowTargetID: [${Bool[${FollowTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	/varset DebuffList
	/Call Debug_Spew "DebuffList Cleared: [${If[${DebuffList.Length} == 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Flush all Queued Events
	/Call Debug_Spew "Flush ALL Events" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/doevents flush
	
	|: Issue a Pet Follow command.
	/Call Debug_Spew "Pet Commands(Stop,Stance): [${Me.Pet.Stop}, ${Me.Pet.Stance}] Pet Combat: [${Me.Pet.Combat}] Pet Target: [${If[${Me.Pet.Target} == NULL,NONE,${Me.Pet.Target}]}] Pet Taunt: [${Me.Pet.Taunt}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.Pet.ID}) {
		/squelch /nomodkey /docommand /Pet Stop
		/squelch /nomodkey /docommand /Pet Back Off
		/squelch /nomodkey /docommand /Pet Follow
	}
	
	
	|: Below are Extra Variables Cleared That Command_Stay does not Clear.
	|: Reset CombatTargetID to nothing.
	/varset CombatTargetID 0
	/Call Debug_Spew "Clear CombatTargetID: [${CombatTargetID}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: Stop Twitch
	/varset TwitchStop 1
	/Call Debug_Spew "Disbale Twitch: [${Bool[${TwitchStop}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: Reset EnrageVar Target
	/varset EnrageVar 0
	/Call Debug_Spew "Clear EnrageVar: [${If[${EnrageVar} == 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: Turn off Bard Song Twisting.
	/Call Debug_Spew "Call [ExecCommand] Params: [Twist OFF]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/call ExecCommand "twist off"

	|: Me on mount then Dismount.
	/if (${Me.Mount.ID}) /squelch /nomodkey /docommand /dismount
	/Call Debug_Spew "Mounted: [${Bool[${Me.Mount.ID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/ECHO 1
	/squelch /nomodkey /docommand /target clear
	/Call Debug_Spew "Cleared Target: [${If[${Target.ID} == NULL,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: Make Sure Combat not Turned on.
	/if (${Me.Combat} && ${Toggle-melee}) /squelch /nomodkey /docommand /attack off
	/if (${Me.AutoFire} && ${Toggle-archery}) /squelch /nomodkey /docommand /autofire off
	/Call Debug_Spew "Combat/Melee: [${Me.Combat}/${Toggle-melee}] AutoFire/Archery: [${Me.AutoFire}/${Toggle-archery}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Clear Guard && Anchor IF Set.
	/Call Debug_Spew "Guard/Anchor ON: [${If[${Toggle-guard},TRUE,${If[${Bool[${IsCamp}]},TRUE,FALSE]}]}] " "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Toggle-guard} || ${Bool[${IsCamp}]}) {
		/varset IsHead
		/varset IsZone 
		/varset Ypos 
		/varset Xpos 
		/varset IsCamp 0
		/varset Toggle-guard FALSE
	}
	
	/call ChatOut 3 "I am Stopping all!" "0"
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_jumpto(string jumpTargetID)

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}

	/if (${Me.State.NotEqual[STAND]}) /squelch /nomodkey /docommand /stand

	|: Issue a Pet Follow command.
	/Call Debug_Spew "Pet Commands(Stop,Stance): [${Me.Pet.Stop}, ${Me.Pet.Stance}] Pet Combat: [${Me.Pet.Combat}] Pet Target: [${If[${Me.Pet.Target} == NULL,NONE,${Me.Pet.Target}]}] Pet Taunt: [${Me.Pet.Taunt}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.Pet.ID}) {
		/squelch /nomodkey /docommand /Pet stop
		/squelch /nomodkey /docommand /Pet back off
		/squelch /nomodkey /docommand /Pet Follow
	}

	|: Interript any Spell Casting.
	/Call Debug_Spew "Interrupt: [${If[${Bool[${Me.Casting.ID}]} && ${Me.Class.Name.NotEqual[Bard]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${Me.Casting.ID}]} && ${Me.Class.Name.NotEqual[Bard]}) /squelch /nomodkey /docommand /interrupt
	
	|: IF [CombatTargetID] then Clear it.
	/Call Debug_Spew "CombatTargetID Clear: [${Bool[${CombatTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) /varset CombatTargetID 0

	|: Clear any Event Queued up.
	/doevents flush
	
	|: Clear Guard && Anchor IF Set.
	/Call Debug_Spew "Guard/Anchor ON: [${If[${Toggle-guard},TRUE,${If[${Bool[${IsCamp}]},TRUE,FALSE]}]}] " "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Toggle-guard} || ${Bool[${IsCamp}]}) {
		/varset IsHead
		/varset IsZone 
		/varset Ypos 
		/varset Xpos 
		/varset IsCamp 0
		/varset Toggle-guard FALSE
	}
	
	|: IF No Target given use [Sender] as Target.
	/Call Debug_Spew "jumpTargetID(${Sender}): [${If[${jumpTargetID.Length} == 0,TRUE,FALSE]} || jumpTargetID(ME): [${jumpTargetID.Upper.Equal[ME]}] || jumpTargetID Set: [${If[${jumpTargetID.Length} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${jumpTargetID.Length} == 0) {

		/varset jumpTargetID ${Spawn[${Sender}].ID}
		
	|: IF Find [Me] in [jumpTargetID] use [Sender] as Target.
	} else /if (${jumpTargetID.Upper.Equal[ME]}) {

		/varset jumpTargetID ${Spawn[${Sender}].ID}
	
	|: IF Target given use as Follow Target.
	} else /if (${jumpTargetID.Length} > 0) {

		/varset jumpTargetID ${Spawn[${jumpTargetID}].ID}
	
	}
	
	/Call Debug_Spew "jumpTargetID: [${Spawn[${jumpTargetID}].ID} && ${Bool[${jumpTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Spawn[${jumpTargetID}].ID} && ${Bool[${jumpTargetID}]}) {
		/call ChatOut 3 "I am now Jumping up [${Spawn[${jumpTargetID}].CleanName}]." "0"
	} else {
		/call ChatOut 3 "Unable to Jump Torward [${jumpTargetID} - ${Spawn[${jumpTargetID}].CleanName}]. Not Found!" "0"
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/return
	}
	
	/if (!${Defined[JumpGiveUp]}) /declare JumpGiveUp timer local 100
	
	/squelch /nomodkey /docommand /stick snaproll rear id ${Spawn[${jumpTargetID}].ID} uw
	:Wait4Arrival
	/delay 25
	/Call Debug_Spew "Wait4Arrival: [${If[!${Stick.Stopped} && ${MoveUtils.Command.NotEqual[NONE]} && ${Me.Moving} && ${JumpGiveUp} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Stick.Stopped} && ${MoveUtils.Command.NotEqual[NONE]} && ${Me.Moving} && ${JumpGiveUp} > 0) {
		/goto :Wait4Arrival
	}
	
	/squelch /nomodkey /docommand /stick off
	
	/delay 10
	/squelch /nomodkey /docommand /keypress BACK HOLD
	/delay 2
	/squelch /nomodkey /docommand /keypress BACK
	/delay 5
	/squelch /nomodkey /docommand /keypress FORWARD HOLD
	/delay 2
	/squelch /nomodkey /docommand /keypress JUMP
	/delay 5
	/squelch /nomodkey /docommand /keypress FORWARD

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_follow(string fTarget, int FollowDistance)

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}

	/if (${Me.State.NotEqual[STAND]}) /squelch /nomodkey /docommand /stand

	|: Issue a Pet Follow command.
	/Call Debug_Spew "Pet Commands(Stop,Stance): [${Me.Pet.Stop}, ${Me.Pet.Stance}] Pet Combat: [${Me.Pet.Combat}] Pet Target: [${If[${Me.Pet.Target} == NULL,NONE,${Me.Pet.Target}]}] Pet Taunt: [${Me.Pet.Taunt}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.Pet.ID}) {
		/squelch /nomodkey /docommand /Pet stop
		/squelch /nomodkey /docommand /Pet back off
		/squelch /nomodkey /docommand /Pet Follow
	}

	|: Interript any Spell Casting.
	/Call Debug_Spew "Interrupt: [${If[${Bool[${Me.Casting.ID}]} && ${Me.Class.Name.NotEqual[Bard]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${Me.Casting.ID}]} && ${Me.Class.Name.NotEqual[Bard]}) /squelch /nomodkey /docommand /interrupt
	
	|: IF [CombatTargetID] then Clear it.
	/Call Debug_Spew "CombatTargetID Clear: [${Bool[${CombatTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) /varset CombatTargetID 0

	|: Clear any Event Queued up.
	/doevents flush
	
	|: Clear Guard && Anchor IF Set.
	/Call Debug_Spew "Guard/Anchor ON: [${If[${Toggle-guard},TRUE,${If[${Bool[${IsCamp}]},TRUE,FALSE]}]}] " "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Toggle-guard} || ${Bool[${IsCamp}]}) {
		/varset IsHead
		/varset IsZone 
		/varset Ypos 
		/varset Xpos 
		/varset IsCamp 0
		/varset Toggle-guard FALSE
	}
	
	|: IF No Target given use [Sender] as Target.
	/Call Debug_Spew "fTarget(${Sender}): [${If[${fTarget.Length} == 0,TRUE,FALSE]} || fTarget(ME): [${fTarget.Upper.Equal[ME]}] || fTarget Set: [${If[${fTarget.Length} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${fTarget.Length} == 0) {

		/varset FollowTargetID ${Spawn[${Sender}].ID}
		
	|: IF Find [Me] in [fTarget] use [Sender] as Target.
	} else /if (${fTarget.Upper.Equal[ME]}) {

		/varset FollowTargetID ${Spawn[${Sender}].ID}
	
	|: IF Target given use as Follow Target.
	} else /if (${fTarget.Length} > 0) {

		/varset FollowTargetID ${Spawn[${fTarget}].ID}
	
	}
	
	/if (!${Bool[${FollowDistance}]}) /varset FollowDistance 10
	/Call Debug_Spew "Set Default Distance: [${If[!${Bool[${FollowDistance}]},TRUE,FALSE]}] Set Dist: [${FollowDistance}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "FollowTargetID: [${Spawn[${FollowTargetID}].ID} && ${Bool[${FollowTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Spawn[${FollowTargetID}].ID} && ${Bool[${FollowTargetID}]}) {
		/call ChatOut 3 "I am now following [${Spawn[${FollowTargetID}].CleanName}]. Dist [${FollowDistance}]" "0"
	} else {
		/call ChatOut 3 "Unable to follow ${FollowTargetID}." "0"
		/return
	}
	
	|: 1 = Moveutils, 2 = Nav, 3 = AdvPath
	/Call Debug_Spew "followmode: [${followmode}] Style: [${If[${followmode} == 1,MQ2MoveUtils,${If[${followmode} == 2,MQ2Nav,${If[${followmode} == 3,MQ2AdvPath,Error Unknown Mode: [${followmode}]]}]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${followmode} == 1) {
		/squelch /nomodkey /docommand /stick uw ${FollowDistance} id ${Spawn[${FollowTargetID}].ID}
	} else /if (${followmode} == 2) {
		|: add To MainLoop /if (${followmode} == 2 && !${Navigation.Active} && ${Bool[${FollowTargetID}]}) /squelch /nomodkey /docommand /nav id ${Spawn[${FollowTargetID}].ID}
		/squelch /nomodkey /docommand /nav id ${Spawn[${FollowTargetID}].ID}
	} else /if (${followmode} == 3) {
		/squelch /nomodkey /docommand /afollow spawn ${Spawn[${FollowTargetID}].ID} nodoor
	}
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_moveto(string MoveToTargetID, int MoveToDistance)
	
	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}
		
	/if (${Me.State.NotEqual[STAND]}) /squelch /nomodkey /docommand /stand

	|: Issue a Pet Follow command.
	/Call Debug_Spew "Pet Commands(Stop,Stance): [${Me.Pet.Stop}, ${Me.Pet.Stance}] Pet Combat: [${Me.Pet.Combat}] Pet Target: [${If[${Me.Pet.Target} == NULL,NONE,${Me.Pet.Target}]}] Pet Taunt: [${Me.Pet.Taunt}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.Pet.ID}) {
		/squelch /nomodkey /docommand /Pet stop
		/squelch /nomodkey /docommand /Pet back off
		/squelch /nomodkey /docommand /Pet Follow
	}
	
	|: Interript any Spell Casting.
	/Call Debug_Spew "Interrupt: [${If[${Bool[${Me.Casting.ID}]} && ${Me.Class.Name.NotEqual[Bard]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${Me.Casting.ID}]} && ${Me.Class.Name.NotEqual[Bard]}) /squelch /nomodkey /docommand /interrupt
	
	|: IF [CombatTargetID] then Clear it.
	/Call Debug_Spew "CombatTargetID Clear: [${Bool[${CombatTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${CombatTargetID}]}) /varset CombatTargetID 0

	|: Clear any Event Queued up.
	/doevents flush
	
	|: Clear Guard && Anchor IF Set.
	/Call Debug_Spew "Guard/Anchor ON: [${If[${Toggle-guard},TRUE,${If[${Bool[${IsCamp}]},TRUE,FALSE]}]}] " "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Toggle-guard} || ${Bool[${IsCamp}]}) {
		/varset IsHead
		/varset IsZone 
		/varset Ypos 
		/varset Xpos 
		/varset IsCamp 0
		/varset Toggle-guard FALSE
	}
	
	|: IF No Target given use [Sender] as Target.
	/Call Debug_Spew "MoveToTargetID(${Sender}): [${If[${MoveToTargetID.Length} == 0,TRUE,FALSE]} || MoveToTargetID(ME): [${MoveToTargetID.Upper.Equal[ME]}] || MoveToTargetID Set: [${If[${MoveToTargetID.Length} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${MoveToTargetID.Length} == 0) {

		/varset MoveToTargetID ${Spawn[${Sender}].ID}
		
	|: IF Find [Me] in [MoveToTargetID] use [Sender] as Target.
	} else /if (${MoveToTargetID.Upper.Equal[ME]}) {

		/varset MoveToTargetID ${Spawn[${Sender}].ID}
	
	|: IF Target given use as MoveTo Target.
	} else /if (${MoveToTargetID.Length} > 0) {

		/varset MoveToTargetID ${Spawn[${MoveToTargetID}].ID}
	
	}
		
	/Call Debug_Spew "Set Default Distance: [${If[!${Bool[${MoveToDistance}]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Bool[${MoveToDistance}]}) /varset MoveToDistance 10
	
	/Call Debug_Spew "MoveToTargetID: [${Spawn[${MoveToTargetID}].ID} && ${Bool[${MoveToTargetID}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Spawn[${MoveToTargetID}].ID} && ${Bool[${MoveToTargetID}]}) {
		/call ChatOut 3 "I am now Moving To [${Spawn[${MoveToTargetID}].CleanName}]. Dist [${MoveToDistance}]" "0"
	} else {
		/call ChatOut 3 "Unable to Move To [${FollowTargetID} - ${Spawn[${MoveToTargetID}].CleanName}]." "0"
		/return
	}
	
	|: 1 = Moveutils, 2 = Nav, 3 = AdvPath
	/Call Debug_Spew "movetomode: [${movetomode}] Style: [${If[${movetomode} == 1,MQ2MoveUtils,${If[${movetomode} == 2,MQ2Nav,${If[${movetomode} == 3,MQ2AdvPath,Error Unknown Mode: [${movetomode}]]}]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${movetomode} == 1) {
		/squelch /nomodkey /docommand /moveto loc ${Spawn[${MoveToTargetID}].Y} ${Spawn[${MoveToTargetID}].X} dist ${MoveToDistance}
	} else /if (${movetomode} == 2) {
		/squelch /nomodkey /docommand /nav id ${Spawn[${MoveToTargetID}].ID}
	} else /if (${movetomode} == 3) {
		/squelch /nomodkey /docommand /afollow spawn ${Spawn[${MoveToTargetID}].ID} nodoor
		
		:CheckAdvPath	
		/if (${AdvPath.Idle} < 2 && ${AdvPath.Status} == 1) {
			/delay 1s
			/if (${Me.Moving}) /goto :CheckAdvPath
		}
		/squelch /nomodkey /docommand /afollow off
	}
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_assist(string Options, string AssistNameID)

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	/if (${Defined[WatchTargets]}) {
		/Call Debug_Spew "WatchTargets: [${If[${WatchTargets.Size} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"		
		/if (${WatchTargets.Size} > 0) /return
	}
	
	/Call Debug_Spew "Auto UnInvis: [${Toggle-autouninvis}] Am I Invisibile: [${Me.Invis}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Toggle-autouninvis} && ${Me.Invis}) /call Command_uninvis
	
	/Call Debug_Spew "MainAssist Set: [${MainAssist.NotEqual[${MainAssist-DefaultValue}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${MainAssist.NotEqual[${MainAssist-DefaultValue}]} && ${Options.Length} == 0 && ${AssistNameID.Length} == 0) {
		
		/Call Debug_Spew "Get [${Spawn[${MainAssist}].CleanName}] TargetofTarget." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/call TargetofTarget ${Spawn[${MainAssist}].ID}
		/delay 2
		/varset AssistNameID ${Macro.Return}
	
	} 
	
	|: If AssistNameID Not Set, Use the Senders Name. E.G; Assist
	/if (${Options.Length} == 0 && ${AssistNameID.Length} == 0) {
	
		/Call Debug_Spew "Get [${Sender}] TargetofTarget." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/call TargetofTarget ${Spawn[${Sender}].ID}
		/delay 2
		/varset AssistNameID ${Macro.Return}
		/Call Debug_Spew "AssistNameID Set To TargetofTarget: [${AssistNameID}]." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"


	|: If find Me in Parameters. E.G; Assist Me
	} else /if (${Options.Upper.Equal[ME]}) {
		
		/Call Debug_Spew "Get [${Sender}] TargetofTarget." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/call TargetofTarget ${Spawn[${Sender}].ID}
		/delay 2
		/varset AssistNameID ${Macro.Return}
		/Call Debug_Spew "AssistNameID Set To TargetofTarget: [${AssistNameID}]." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: If find ON in Parameters. E.G; Assist On ToonName/ID
	} else /if (${Options.Upper.Equal[ON]} && ${AssistNameID.Length} > 0) {
		
		/varset AssistNameID ${Spawn[${AssistNameID}].ID}
	
	|: If find ON in Parameters. E.G; Assist ToonName/ID
	} else /if (${Options.Upper.NotEqual[ME]} && ${Options.Upper.NotEqual[ON]} && ${Options.Length} > 0 && ${AssistNameID.Length} == 0) {

		/varset AssistNameID ${Spawn[${Options}].ID}
		
	} else /if (${AssistNameID.Length} == 0 || ${AssistNameID.Equal[NULL]}) {

		/call ChatOut 3 "Assist Failed AssistNameID: [${AssistNameID} - ${Spawn[${AssistNameID}].CleanName}]." "0"
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"		
		/return
	}

	/Call Debug_Spew "AssistNameID = [${Me.CleanName}] Status: [${AssistNameID.Equal[${Me.CleanName}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${AssistNameID.Equal[${Me.ID}]}) {
		/varset CombatTargetID ${Spawn[${AssistNameID}].ID}
		/delay 2
		
		/if (${Toggle-petona}) {
			|:Combatcheck Used to check if attack is on and should not be:|
			/call Combatcheck
			/delay 5
			/Call Debug_Spew "CombatTargetID [${CombatTargetID}] Status: [${If[${CombatTargetID} != 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${CombatTargetID} == 0) /return

			|: Send Pet to attack IF CombatTargetID
			/Call Debug_Spew "Have Pet: [${If[${Me.Pet.ID} == NULL,FALSE,TRUE]}] Pet Target: [${Me.Pet.Following.Name}] CombatTargetID Name: [${Spawn[${CombatTargetID}].Name}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${CombatTargetID} && ${Me.Pet.ID} && ${Me.Pet.Following.Name.NotEqual[${Spawn[${CombatTargetID}].Name}]}) {
				/squelch /nomodkey /docommand /Pet Attack ${Spawn[${CombatTargetID}].Name}
			}
		}
		
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"		
		/return
	}
	
	/Call Debug_Spew "Clear Follow Target: [${If[${FollowTargetID} != 0,TRUE,FALSE]}] CombatTargetID: [${If[${CombatTargetID} != 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Stick.Active} || ${CombatTargetID} != 0) {
		/squelch /nomodkey /docommand /stick off
		|: Clear Follow Target ID IF Set.
		/if (${FollowTargetID} != 0) /varset FollowTargetID 0
	}
	
	/varset CombatTargetID ${Spawn[${AssistNameID}].ID}
	/delay 2
	/Call Debug_Spew "CombatTargetID: [${CombatTargetID}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Combatcheck Used to check if attack is on and should not be
	/call Combatcheck ${CombatTargetID}
	/delay 5
	/Call Debug_Spew "CombatTargetID [${CombatTargetID}] Status: [${If[${CombatTargetID} != 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${CombatTargetID} == 0) /return
	
	/if (${Toggle-petona}) {

		|: Send Pet to attack IF CombatTargetID
		/Call Debug_Spew "Have Pet: [${If[${Me.Pet.ID} == NULL,FALSE,TRUE]}] Pet Target: [${Me.Pet.Following.Name}] CombatTargetID Name: [${Spawn[${CombatTargetID}].Name}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${CombatTargetID} && ${Me.Pet.ID} && ${Me.Pet.Following.Name.NotEqual[${Spawn[${CombatTargetID}].Name}]}) {
			/squelch /nomodkey /docommand /Pet Attack ${Spawn[${CombatTargetID}].Name}
		}
		
	}
	
	/Call Debug_Spew "CombatTargetID [${CombatTargetID}] Status: [${If[${CombatTargetID} != 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${CombatTargetID} != 0) {
		
		|: Call CombatMain IF Melle/Archery Enabled.
		/Call Debug_Spew "Call [CombatMain] IF Melee On: [${Toggle-melee}] || Archery On: [${Toggle-archery}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Toggle-melee} || ${Toggle-archery}) /call CombatMain


		|: Check IF autochainnuke = [ON], ChainNuke List is Set, CombatTargetID HP [Less Then] ini Setting ChainNukePct
		/Call Debug_Spew "Auto ChainNuke On: [${Toggle-autochainnuke}] Chain Nuke Settings SetL [${If[${ChainNukePct.NotEqual[${ChainNukePct-DefaultValue}]} && ${ChainNuke.NotEqual[${ChainNuke-DefaultValue}]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Toggle-autochainnuke}) {
			/if (${ChainNukePct.NotEqual[${ChainNukePct-DefaultValue}]} && ${ChainNuke.NotEqual[${ChainNuke-DefaultValue}]}) {
				/Call Debug_Spew "Call [AutoChainNuke] IF CombatTargetID HPs: [${Spawn[${CombatTargetID}].PctHPs} < ${ChainNukePct}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				/if (${Spawn[${CombatTargetID}].PctHPs} < ${ChainNukePct}) /call AutoChainNuke
			} else {
				/call ChatOut Commands "-[ASSIST] Please make sure you Change ini Settings Section[SPELL]: [ChainNukePct=, ChainNuke=]" "0"
			}
		}
		
		/Call Debug_Spew "Auto Debuffs On: [${Toggle-debuffs}] DebuffSpell#1 Set: [${DebuffSpell#1.NotEqual[${DebuffSpell#1-DefaultValue}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Toggle-debuffs}) {
			/if (${DebuffSpell#1.NotEqual[${DebuffSpell#1-DefaultValue}]}) {
				/Call Debug_Spew "Call [AssistDebuffs]." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				/call AssistDebuffs
			} else {
				/call ChatOut Commands "-[ASSIST] Please make sure you Change ini Settings Section[DEBUFFS]: [DebuffSpell#1=, DebuffSpell#X (X=Number.)]" "0"
			}
		}
	
	}
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_groupset(string GroupName)

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Group Leader: [${Bool[${Select[${Group.Leader},${Me.CleanName}]}]}] In a Group: [${If[${Int[${Group.GroupSize}]} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${Select[${Group.Leader},${Me.CleanName}]}]} && ${Int[${Group.GroupSize}]} > 0) {
		
		/Call Debug_Spew "Find Team ${GroupName}: [${If[${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (!${Bool[${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}]}]}) {

			|:Loop the Group and Save Members to tempGroup.
			/if (!${Defined[i]}) /declare i int local
			/if (!${Defined[tempGroup]}) /declare tempGroup string local
			/for i 0 to ${Math.Calc[${Int[${Group.GroupSize}]}-1]}
				/Call Debug_Spew "Saving Member[${i}]: [${Group.Member[${i}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				/varset tempGroup ${tempGroup} ${Group.Member[${i}]}
			/next i
			/Call Debug_Spew "Save Team [${tempGroup}] To [GroupTeam_${GroupName}]." "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			
			|:Save tempGroup to CORE Section in the Ini.
			/ini "${BOT_INI}" "CORE" "GroupTeam_${GroupName}" "${tempGroup}"
			/call ChatOut 3 "The Current Group Saved to [GroupTeam_${GroupName}] Under [Core] Section, Use Command [Groupup ${GroupName}] to Recall." "0"

		} else /if (${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}) {

			/call ChatOut 3 "Master [GroupTeam_${GroupName}] is already in use.  Please choose another name and try again." "0"

		}

	} else /if (${Group} == 0) {

		/call ChatOut 3 "Master You need to make a group first." "0"

	}
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_groupup(string GroupName)

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: IF Im not GroupTeam_[GroupName] Leader THEN Return.
	/Call Debug_Spew "Team [${GroupName}] Saved: [${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}]}] Am I Team Leader: [${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Arg[1, ].Equal[${Me.CleanName}]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}]} && !${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Arg[1, ].Equal[${Me.CleanName}]}]}) /return
	
	/Call Debug_Spew "Team [${GroupName}] Saved: [${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}]}] Am I Team Leader: [${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Arg[1, ].Equal[${Me.CleanName}]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}]} && ${Bool[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Arg[1, ].Equal[${Me.CleanName}]}]}) {
		
		/call ChatOut 3 "Recalling [GroupTeam_${GroupName}] Group Members..." "0"
		
		:Reinvite
		/if (!${Defined[i]}) /declare i int local
		/for i 2 to ${Math.Calc[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Count[ ]}+1].Int}
			/if (${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Length}) {
				/Call Debug_Spew "Inviting Member[${i}]: [${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Arg[${i}, ]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				/squelch /nomodkey /docommand /invite ${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Arg[${i}, ]}
				/delay 2
			}
		/next i
		
		|: Check IF Full Saved GroupTeam_[GroupName] was invited ELSE Try Again.
		/Call Debug_Spew "Group Full Team: [${If[${Int[${Group.GroupSize}]} == ${Math.Calc[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Count[ ]}+1].Int},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Int[${Group.GroupSize}]} == ${Math.Calc[${Ini[${BOT_INI},CORE,GroupTeam_${GroupName}].Count[ ]}+1].Int}) {
			/call ChatOut 3 "Finished Forming Team [GroupTeam_${GroupName}]." "0"
		} else {
			/goto :Reinvite
		}

	}
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_disband

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Raid: [${Bool[${Raid.Members}]}] Group: [${Bool[${Group.GroupSize}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	|: Disband Current Raid
	/if (${Bool[${Raid.Members}]}) {
		
		/Call Debug_Spew "Raid Disband: [${Window[RaidWindow].Child[RAID_DisbandButton]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Window[RaidWindow].Child[RAID_DisbandButton]}) {
			/squelch /nomodkey /docommand /notify RaidWindow RAID_DisbandButton leftmouseup
		}
		
	|: Disband Current Group.
	} else /if (${Bool[${Group.GroupSize}]}) {
		
		/Call Debug_Spew "Group Disband: [${Window[GroupWindow].Child[GW_DisbandButton]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Window[GroupWindow].Child[GW_DisbandButton]}) {
			/squelch /nomodkey /docommand /notify GroupWindow GW_DisbandButton leftmouseup
		}
	
	}
	
	|: Disband Current Expedition.
	/Call Debug_Spew "Expedition Name: [${If[${Bool[${DynamicZone.Name}]},${DynamicZone.Name},NONE]}] Active: [${If[${Bool[${DynamicZone.Name}]} && ${Bool[${DynamicZone.Leader}]} && ${Bool[${DynamicZone.Members}]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Bool[${DynamicZone.Name}]} && ${Bool[${DynamicZone.Leader}]} && ${Bool[${DynamicZone.Members}]}) {
		
		/Call Debug_Spew "Expedition Active: [${Window[DynamicZoneWnd].Child[DZ_Quit].Enabled}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Window[DynamicZoneWnd].Child[DZ_Quit].Enabled}) {
			 /squelch /nomodkey /docommand /notify DynamicZoneWnd DZ_Quit leftmouseup
		}
		
		/Call Debug_Spew "Expedition DialogBox: [${If[${Window[ConfirmationDialogBox].Open} && ${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[Are you sure you want to leave this expedition?]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Window[ConfirmationDialogBox].Open} && ${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[Are you sure you want to leave this expedition?]}]}) {
			/squelch /nomodkey /docommand /notify ConfirmationDialogBox CD_Yes_Button leftmouseup
		}
		
	}
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_accept

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "TradeWnd Open: [${Window[TradeWnd].Open}] DialogBox Open: [${Window[ConfirmationDialogBox].Open}] LrgDialogWnd Open: [${Window[LargeDialogWindow].Open}] Group Invited: [${Me.Invited}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Accept Open Trade Window.
	/if (${Window[TradeWnd].Open}) {
		
		/squelch /nomodkey /docommand /notify TradeWnd TRDW_Trade_Button leftmouseup
	
	|: Accept DialogBox Window Deppending on Window Type.
	} else /if (${Window[ConfirmationDialogBox].Open}) {
				
		|: Accept Resurrect.
		/Call Debug_Spew "Resurrect 100%: [${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(100 percent) upon you. Do you wish this?]}]}] Resurrect 96%: [${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(96 percent) upon you. Do you wish this?]}]}] Resurrect 90%: [${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(90 percent) upon you. Do you wish this?]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(100 percent) upon you. Do you wish this?]}]} || ${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(96 percent) upon you. Do you wish this?]}]} || ${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(90 percent) upon you. Do you wish this?]}]}) {
			/squelch /nomodkey /docommand /notify ConfirmationDialogBox CD_Yes_Button leftmouseup		
		}
		
		|: Accept Raid Invite
		/Call Debug_Spew "Raid Invited: [${Raid.Invited}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Raid.Invited}) {
		
			/Call Debug_Spew "Raid Accept: [${Window[RaidWindow].Child[RAID_AcceptButton]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Window[RaidWindow].Child[RAID_AcceptButton]}) {
				/squelch /nomodkey /docommand /notify RaidWindow RAID_AcceptButton leftmouseup
			}
			
			/Call Debug_Spew "Raid DialogBox: [${If[${Window[ConfirmationDialogBox].Open} && ${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[invites you to join a raid.  Would you like to join?]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Window[ConfirmationDialogBox].Open} && ${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[invites you to join a raid.  Would you like to join?]}) {				
				/squelch /nomodkey /docommand /notify ConfirmationDialogBox CD_Yes_Button leftmouseup			
			}
			
		}
		
	|: Accept Large DialogBox Teleport Window.
	} else /if (${Window[LargeDialogWindow].Open}) {
		
		/Call Debug_Spew "Is a TeleportWnd: [${Bool[${Window[LargeDialogWindow].Child[LDW_TextBox].Text.Find[Teleport to]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Bool[${Window[LargeDialogWindow].Child[LDW_TextBox].Text.Find[Teleport to]}]}) {
			/squelch /nomodkey /docommand /notify LargeDialogWindow LDW_YesButton leftmouseup
		}
	
	|: Accept Group Invite
	} else /if (${Me.Invited}) {
			
		/Call Debug_Spew "Group Follow: [${Window[GroupWindow].Child[GW_FollowButton]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Window[GroupWindow].Child[GW_FollowButton]}) {			
			/squelch /nomodkey /docommand /notify GroupWindow GW_FollowButton leftmouseup			
		}
	
	}

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_reject

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "TradeWnd Open: [${Window[TradeWnd].Open}] DialogBox Open: [${Window[ConfirmationDialogBox].Open}] LrgDialogWnd Open: [${Window[LargeDialogWindow].Open}] Group Invited: [${Me.Invited}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		
	|: Reject Open Trade Window.
	/if (${Window[TradeWnd].Open}) {
		
		/squelch /nomodkey /docommand /notify TradeWnd TRDW_Cancel_Button leftmouseup
	
	|: Reject DialogBox Window Deppending on Window Type.
	} else /if (${Window[ConfirmationDialogBox].Open}) {
		
		
		|: Reject Resurrect.
		/Call Debug_Spew "Resurrect 100%: [${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(100 percent) upon you. Do you wish this?]}]}] Resurrect 96%: [${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(96 percent) upon you. Do you wish this?]}]}] Resurrect 90%: [${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(90 percent) upon you. Do you wish this?]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(100 percent) upon you. Do you wish this?]}]} || ${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(96 percent) upon you. Do you wish this?]}]} || ${Bool[${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[(90 percent) upon you. Do you wish this?]}]}) {
			/squelch /nomodkey /docommand /notify ConfirmationDialogBox CD_No_Button leftmouseup
		}
		
		|: Reject Raid Invite.
		/Call Debug_Spew "Raid Invited: [${Raid.Invited}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Raid.Invited}) {
			
			/Call Debug_Spew "Raid Decline: [${Window[RaidWindow].Child[RAID_DeclineButton]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Window[RaidWindow].Child[RAID_DeclineButton]}) {
				/squelch /nomodkey /docommand /notify RaidWindow RAID_DeclineButton leftmouseup
			}
			
			/Call Debug_Spew "Raid DialogBox: [${If[${Window[ConfirmationDialogBox].Open} && ${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[invites you to join a raid.  Would you like to join?]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Window[ConfirmationDialogBox].Open} && ${Window[ConfirmationDialogBox].Child[CD_TextOutput].Text.Find[invites you to join a raid.  Would you like to join?]}) {				
				/squelch /nomodkey /docommand /notify ConfirmationDialogBox CD_No_Button leftmouseup			
			}
			
		}
	
	|: Reject Large DialogBox Teleport Window.
	} else /if (${Window[LargeDialogWindow].Open}) {
		
		/Call Debug_Spew "Is a TeleportWnd: [${Bool[${Window[LargeDialogWindow].Child[LDW_TextBox].Text.Find[Teleport to]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Bool[${Window[LargeDialogWindow].Child[LDW_TextBox].Text.Find[Teleport to]}]}) {
			/squelch /nomodkey /docommand /notify LargeDialogWindow LDW_NoButton leftmouseup
		}
	
	|: Reject Group Invite
	} else /if (${Me.Invited}) {
			
		/Call Debug_Spew "Group Reject: [${Window[GroupWindow].Child[GW_DeclineButton]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Window[GroupWindow].Child[GW_DeclineButton]}) {			
			/squelch /nomodkey /docommand /notify GroupWindow GW_DeclineButton leftmouseup			
		}
	
	}
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_moveup(string mDistance, string mHeading)
	
	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}

	|: Get Senders Heading, [Y,X] Location.
	/Call Debug_Spew "Custom Heading Set: [${If[${mHeading.Length} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${mHeading.Length} != 0 && ${Int[${mHeading}]} <= 360 && ${Int[${mHeading}]} > 0) {
		/if (!${Defined[startHeading]}) /declare startHeading float local ${Math.Calc[${mHeading}*-1]}
		/if (!${Defined[locToStart]}) /declare locToStart string local ${Spawn[PC =${Sender}].Loc}
	} else /if (${mHeading.Length} != 0 && ${Int[${mHeading}]} > 360 || ${mHeading.Length} != 0 && ${Int[${mHeading}]} == 0) {
		/call ChatOut 3 "I am unable to Moveup [${Math.Calc[${mDistance}*10].Int}/YDs] Heading [${mHeading}] Outside Faceing Degree Options [0-360]" "0"
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/return
	} else /if (${mHeading.Length} == 0) {
		/if (!${Defined[startHeading]}) /declare startHeading float local ${Math.Calc[${Spawn[PC =${Sender}].Heading.Degrees}*-1]}
		/if (!${Defined[locToStart]}) /declare locToStart string local ${Spawn[PC =${Sender}].Loc}
	}
	/Call Debug_Spew "startHeading: [${startHeading}] locToStart: [${locToStart}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Stick behind and Clear Stick
	/if (!${Defined[MoveUpGiveUp]}) /declare MoveUpGiveUp timer local 100
	
	/squelch /nomodkey /docommand /stick snaproll rear id ${Spawn[${Sender}].ID} uw
	:Wait4Arrival
	/delay 25
	/Call Debug_Spew "Wait4Arrival: [${If[!${Stick.Stopped} && ${MoveUtils.Command.NotEqual[NONE]} && ${Me.Moving} && ${MoveUpGiveUp} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Stick.Stopped} && ${MoveUtils.Command.NotEqual[NONE]} && ${Me.Moving} && ${MoveUpGiveUp} > 0) {
		/goto :Wait4Arrival
	}
	
	|: Check Distance between Object and Me Then get closer if not
	/if (!${Defined[moveTimer]}) /declare moveTimer timer local
	/Call Debug_Spew "Move Closer: [${If[${Math.Distance[${locToStart}]} > 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Math.Distance[${locToStart}]} > 8) {
	
		/varset moveTimer 50
			
		|: Check Distance between Object and Me Then get close if not
		:retryMoveto
		/squelch /nomodkey /docommand /moveto loc ${locToStart.Arg[1,,]} ${locToStart.Arg[2,,]} dist 8
				  
		/delay 10 ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8
		
		/Call Debug_Spew "Moveto OFF: [${If[${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8) /squelch /nomodkey /docommand /moveto off
		/Call Debug_Spew "Retry Move Closer: [${If[${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8) /goto :retryMoveto
			  
	}
	
	|: Stick & Moveto OFF
	/squelch /nomodkey /docommand /stick off
	/squelch /nomodkey /docommand /moveto off
		
	|: Close Bag/Inventory IF Open & Clear Target
	/squelch /nomodkey /docommand /cleanup
	/delay 2
	/if (${Window[InventoryWindow].DoClose}) /echo Close Inventory Window
		
	|: Face the Senders Heading.
	:retryFace
	/Call Debug_Spew "Face Heading: [${startHeading}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/squelch /nomodkey /docommand /face fast heading ${startHeading}
	/delay 5
	
	/Call Debug_Spew "Correct Facing: [${If[${Math.Distance[${Math.Calc[${Me.Heading.Degrees}*-1]}:${startHeading}]} >= 9,TRUE,FALSE]}] My Facing: [${Math.Calc[${Me.Heading.Degrees}*-1]}] Senders Facing: [${startHeading}] Max Degree Difference: [8]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Math.Distance[${Math.Calc[${Me.Heading.Degrees}*-1]}:${startHeading}]} >= 9) /goto :retryFace
	
	|: Change to First_Person_Camera/Look Straight ahead.
	/squelch /nomodkey /docommand /keypress First_Person_Camera
	/squelch /nomodkey /docommand /look 0
	/delay 2
	
	/call ChatOut 3 "I am attemping to move forward [${Math.Calc[${mDistance}*10].Int}/YDs] Master." "0"
	/delay 5
	
	/squelch /nomodkey /docommand /keypress FORWARD hold
	/delay ${Math.Calc[${mDistance}/0.75].Int}
	/squelch /nomodkey /docommand /keypress FORWARD
		
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_zone

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}

	|: Declare Zone Variables.
	/if (!${Defined[startHeading]}) /declare startHeading float local ${Math.Calc[${Spawn[PC =${Sender}].Heading.Degrees}*-1]}
	/if (!${Defined[locToStart]}) /declare locToStart string local ${Spawn[PC =${Sender}].Loc}
	/if (!${Defined[locToStartZ]}) /declare locToStartZ string local ${Spawn[PC =${Sender}].Z}
	/if (!${Defined[retryTimer]}) /declare retryTimer timer local 7s
	/if (!${Defined[moveTimer]}) /declare moveTimer timer local

	|: Keep Track of Current Zone bot is in.
	/if (!${Defined[cZone]}) /declare cZone int local ${Zone.ID}

	|: Delay if Casting.
	/Call Debug_Spew "Not a Bard: [${Me.Class.ShortName.NotEqual[BRD]}] Me Casting: [${If[${Me.Casting.ID},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Me.Casting.ID} && ${Me.Class.ShortName.NotEqual[BRD]}) {
		/delay 5s !${Me.Casting.ID}
		/if (${Me.Casting.ID}) /call interrupt
	}

	/call ChatOut 3 "I am attemping to Zone [${Sender}]. Please Wait.. 7 Seconds." "0"

	|: -Check that you can see the location to start from.
	/Call Debug_Spew "Line of Sight: [${LineOfSight[${Me.Loc.Replace[ ,]},${Me.Z}:${locToStart.Replace[ ,]},${locToStartZ}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${LineOfSight[${Me.Loc.Replace[ ,]},${Me.Z}:${locToStart.Replace[ ,]},${locToStartZ}]}) {

		/call ChatOut 3 "I cannot see the starting location!" "0"

	} else {
		
		/Call Debug_Spew "Distance To Loc: [${Math.Distance[${locToStart}]}] Max Distance: [75]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Math.Distance[${locToStart}]} > 75) {
		
		  /call ChatOut 3 "I am to far away from you [${Sender}] My Distance [${Math.Distance[${locToStart}]}], is Outside Max Range [75], I'm Canceling Zone Command!" "0"
		  /return
		
		}
		
		|: Stick behind and Clear Stick
		/if (!${Defined[ZoneGiveUp]}) /declare ZoneGiveUp timer local 100
	
		/squelch /nomodkey /docommand /stick snaproll rear id ${Spawn[${Sender}].ID} uw
		:Wait4Arrival
		/delay 25
		/Call Debug_Spew "Wait4Arrival: [${If[!${Stick.Stopped} && ${MoveUtils.Command.NotEqual[NONE]} && ${Me.Moving} && ${ZoneGiveUp} > 0,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (!${Stick.Stopped} && ${MoveUtils.Command.NotEqual[NONE]} && ${Me.Moving} && ${ZoneGiveUp} > 0) {
			/goto :Wait4Arrival
		}
		
		:retryZone
		|: Check Distance between Object and Me Then get closer if not
		/if (!${Defined[moveTimer]}) /declare moveTimer timer local
		/Call Debug_Spew "Move Closer: [${If[${Math.Distance[${locToStart}]} > 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Math.Distance[${locToStart}]} > 8) {
		
			/varset moveTimer 50
				
			|: Check Distance between Object and Me Then get close if not
			:retryMoveto
			/squelch /nomodkey /docommand /moveto loc ${locToStart.Arg[1,,]} ${locToStart.Arg[2,,]} dist 8
					  
			/delay 10 ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8
			
			/Call Debug_Spew "Moveto OFF: [${If[${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8) /squelch /nomodkey /docommand /moveto off
			/Call Debug_Spew "Retry Move Closer: [${If[${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8) /goto :retryMoveto
				  
		}
		
		|: Stick & Moveto OFF
		/squelch /nomodkey /docommand /stick off
		/squelch /nomodkey /docommand /moveto off
			
		|: Close Bag/Inventory IF Open & Clear Target
		/squelch /nomodkey /docommand /cleanup
		/delay 2
		/if (${Window[InventoryWindow].DoClose}) /echo Close Inventory Window
			
		  
		|: -Face the zone and run foward for 6 seconds.
		:retryFace
		/squelch /nomodkey /docommand /face fast heading ${startHeading}
		/delay 2
		
		/Call Debug_Spew "Correct Facing: [${If[${Math.Distance[${Math.Calc[${Me.Heading.Degrees}*-1]}:${startHeading}]} >= 9,TRUE,FALSE]}] My Facing: [${Math.Calc[${Me.Heading.Degrees}*-1]}] Senders Facing: [${startHeading}] Max Degree Difference: [8]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Math.Distance[${Math.Calc[${Me.Heading.Degrees}*-1]}:${startHeading}]} >= 9) /goto :retryFace
	
		|: Change to First_Person_Camera/Look Straight ahead.
		/squelch /nomodkey /docommand /keypress First_Person_Camera
		/squelch /nomodkey /docommand /look 0
		/delay 2
		  
		/squelch /nomodkey /docommand /keypress forward hold
		  
		|: -Wait to zone.
		/delay 6s !${Zone.ID} || ${Zone.ID} != ${cZone}
		
		/squelch /nomodkey /docommand /keypress back
		 
		|: -Check if I zoned.
		/Call Debug_Spew "In Same Zone: [${If[${Zone.ID} == ${cZone},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Zone.ID} == ${cZone}) {
			
			/Call Debug_Spew "Retry Zoning: [${If[${retryTimer},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${retryTimer}) {
			
				/goto :retryZone
			
			} else {
		
				/call ChatOut 3 "I have givin up on trying to run through zone line, New Zone [+y+][[+r+]${If[${Zone.ID} != ${cZone},TRUE,FALSE]}[+y+]]." "0"
				/delay 2
				/squelch /nomodkey /docommand /moveto off
				/return	
			
			}
		
		} else /if (${Zone.ID} != ${cZone}) {

			/call ChatOut 3 "I have Finsihed Zoning Now in [${Zone.Name}], New Zone [+y+][[+r+]${If[${Zone.ID} != ${cZone},TRUE,FALSE]}[+y+]]. Let Roll!" "0"
			/delay 2
			/squelch /nomodkey /docommand /moveto off
			/return	
		}
		
		
	}
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_doort
	
	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}
	
	/if (!${Defined[aDoor]}) /declare aDoor string local
	/if (!${Defined[doorLocation]}) /declare doorLocation string local
	/if (!${Defined[myLocation]}) /declare myLocation string local
	/if (!${Defined[locToStart]}) /declare locToStart string local ${Spawn[PC =${Sender}].Loc}
	
	|: Check Distance between Object and Me Then get closer if not
	/if (!${Defined[moveTimer]}) /declare moveTimer timer local
	/Call Debug_Spew "Move Closer: [${If[${Math.Distance[${locToStart}]} > 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Math.Distance[${locToStart}]} > 8) {
	
		/varset moveTimer 50
			
		|: Check Distance between Object and Me Then get close if not
		:retryMoveto
		/squelch /nomodkey /docommand /moveto loc ${locToStart.Arg[1,,]} ${locToStart.Arg[2,,]} dist 8
				  
		/delay 10 ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8
		
		/Call Debug_Spew "Moveto OFF: [${If[${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8) /squelch /nomodkey /docommand /moveto off
		/Call Debug_Spew "Retry Move Closer: [${If[${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8) /goto :retryMoveto
			  
	}
	
	|: Stick & Moveto OFF
	/squelch /nomodkey /docommand /stick off
	/squelch /nomodkey /docommand /moveto off
		
	|: Close Bag/Inventory IF Open & Clear Target
	/squelch /nomodkey /docommand /cleanup
	/delay 2
	/if (${Window[InventoryWindow].DoClose}) /echo Close Inventory Window
	
	|: Change to First_Person_Camera/Look Straight ahead.
	/squelch /nomodkey /docommand /keypress First_Person_Camera
	/squelch /nomodkey /docommand /look 0
	/delay 2

	|: Target Closest Door.
	/squelch /nomodkey /docommand /doortarget
	/delay 5
	/varset aDoor ${Switch.Name}
	/delay 5
	/varset myLocation ${Me.Loc}, ${Me.Z}
	/Call Debug_Spew "Door: [${Switch.Name}] DoorID: [${Switch.ID}] myLocation: [${myLocation}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: -Face the Same Direction as Sender.
	/Call Debug_Spew "Face DoorID: [${Switch.ID}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/squelch /nomodkey /docommand /face fast door ${Switch.ID}
		 
	|: Mouse Click Door
	/Call Debug_Spew "Left Click DoorID: [${Switch.ID}] Door Name: [${Switch.Name}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/squelch /nomodkey /docommand /click left door ${Switch.ID}
	/delay 5
	/varset doorLocation ${Me.Loc}, ${Me.Z}
		
	/call ChatOut 3 "I Finished Clicking the Object [${aDoor}], New Location [+y+][[+r+]${If[${Math.Distance[${myLocation}:${doorLocation}]} >= 8,TRUE,FALSE]}[+y+]]." "0"
	
	/Call Debug_Spew "Call [ExecCommand] Doorf Command: [${If[${Math.Distance[${myLocation}:${doorLocation}]} >= 8,FALSE,TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${If[${Math.Distance[${myLocation}:${doorLocation}]} >= 8,TRUE,FALSE]}) /call ExecCommand "doorf"

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_doorf

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Return IF: EchoText: [${EchoText.Length}] Sender: [${If[${Bool[${Spawn[pc ${Sender}].ID}]},${If[${Sender.Equal[${Me.CleanName}]},TRUE,FALSE]},TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${EchoText.Length} == 0) {
		/if (!${Bool[${Spawn[pc ${Sender}].ID}]} || ${Sender.Equal[${Me.CleanName}]}) /return
	}
		

	/if (!${Defined[aDoor]}) /declare aDoor string local
	/if (!${Defined[doorLocation]}) /declare doorLocation string local
	/if (!${Defined[myLocation]}) /declare myLocation string local
	/if (!${Defined[locToStart]}) /declare locToStart string local ${Spawn[PC =${Sender}].Loc}

	|: Check Distance between Object and Me Then get closer if not
	/if (!${Defined[moveTimer]}) /declare moveTimer timer local
	/Call Debug_Spew "Move Closer: [${If[${Math.Distance[${locToStart}]} > 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Math.Distance[${locToStart}]} > 8) {
	
		/varset moveTimer 50
			
		|: Check Distance between Object and Me Then get close if not
		:retryMoveto
		/squelch /nomodkey /docommand /moveto loc ${locToStart.Arg[1,,]} ${locToStart.Arg[2,,]} dist 8
				  
		/delay 10 ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8
		
		/Call Debug_Spew "Moveto OFF: [${If[${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} <= 8) /squelch /nomodkey /docommand /moveto off
		/Call Debug_Spew "Retry Move Closer: [${If[${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${moveTimer} && ${Math.Distance[${locToStart.Arg[1,,]},${locToStart.Arg[2,,]}]} >= 8) /goto :retryMoveto
			  
	}
	
	|: Stick & Moveto OFF
	/squelch /nomodkey /docommand /stick off
	/squelch /nomodkey /docommand /moveto off
		
	|: Close Bag/Inventory IF Open & Clear Target
	/squelch /nomodkey /docommand /cleanup
	/delay 2
	/if (${Window[InventoryWindow].DoClose}) /echo Close Inventory Window
	
	|: Change to First_Person_Camera/Look Straight ahead.
	/squelch /nomodkey /docommand /keypress First_Person_Camera
	/squelch /nomodkey /docommand /look 0
	/delay 2


	|: ----------- Cremo Doors.ini Search -----------
		
		/declare closestDoorID int local 0
		/declare closestDoorDist float local 0
		
		|: load array of doors from doors.ini:  doorid, x, y, z, name
		/Call Debug_Spew "Call [IniToArray] Params: [MACRO_FILE_PREFIXdoors.ini,${Zone.ShortName},${Zone.ShortName}# doorList]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/call IniToArray "${MACRO_INI_LOCATION_PREFIX}/${MACRO_FILE_PREFIX}_doors.ini,${Zone.ShortName},${Zone.ShortName}#" doorList outer
		
		/Call Debug_Spew "Variable Created doorList: [${Defined[doorList]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (!${Defined[doorList]}) {
		
			/bc I have no doorList for this zone let [NeroMorte#8786] on Discord Know!
		
		} else {

			/Call Debug_Spew "Doors Found in zone ${doorList.Size}" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			
			|: find the closest door to me
			/if (!${Defined[i]}) /declare i int local
			/for i 1 to ${doorList.Size}

				/Call Debug_Spew "Loop: [${i}] Door: [${doorList[${i}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}" "" "Loop[${i}]"
				/squelch /doortarget id ${doorList[${i}].Arg[1,,]}
				
				/Call Debug_Spew "Set First Door: [${If[${closestDoorDist}==0,TRUE,FALSE]}] Current Door Dist: [${DoorTarget.Distance}] Closest Door Dist: [${closestDoorDist}] Current Door Z: [${DoorTarget.DistanceZ} < 75]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}" "" "Loop[${i}]"
				/if ((${closestDoorDist}==0 || ${DoorTarget.Distance} < ${closestDoorDist}) && ${DoorTarget.DistanceZ} < 75) {
					/varset closestDoorDist ${DoorTarget.Distance}
					/varset closestDoorID ${doorList[${i}].Arg[1,,]}
				}
			/next i
		}
		
		|: Target Closest Door.
		/Call Debug_Spew "Targeting Closest Door: ${closestDoorDist} ID: ${closestDoorID}" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/doortarget id ${closestDoorID}
		
	|: ----------- Cremo Doors.ini Search -----------

	/varset aDoor ${Switch.Name}
	/delay 5
	/varset myLocation ${Me.Loc}, ${Me.Z}
	
	|: -Face the Same Direction as Sender.
	/Call Debug_Spew "Face DoorID: [${Switch.ID}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/squelch /nomodkey /docommand /face fast door ${Switch.ID}
		 
	|: Mouse Click Door
	/Call Debug_Spew "Left Click DoorID: [${Switch.ID}] Door Name: [${Switch.Name}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/squelch /nomodkey /docommand /click left door ${Switch.ID}
	/delay 5
	/varset doorLocation ${Me.Loc}, ${Me.Z}
		
	/call ChatOut 3 "I Finished Clicking the Object [${aDoor}], New Location [+y+][[+r+]${If[${Math.Distance[${myLocation}:${doorLocation}]} >= 8,TRUE,FALSE]}[+y+]]." "0"

	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_reload

	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Clearing all Chat Boxes.
	/delay 2
	/ClearAll
	
	|: Clearing MQ Boxes.
	/delay 2
	/MQClear
	
	/Call Debug_Spew "Issuing Command: [ClearAll] Issuing Command: [MQClear]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "I Desync: [${If[${Bool[${Select[${Me.CleanName},${EQBC.Names.Replace[ ,,]}]}]},FALSE,TRUE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (!${Bool[${Select[${Me.CleanName},${EQBC.Names.Replace[ ,,]}]}]}) {
		/call ChatOut 17 "Master [[+r+]${Me.CleanName}[+w+]] got [+r+]Desync from EQBC[+w+]. [+y+]Trying to Fix it now..." "0"
		/delay 2
		/bccmd force
	}
	
	/Call Debug_Spew "Starting Macro: [${Macro.Name}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/delay 2
	/mac ${Macro.Name} Reloaded

/return

|:-----------------------------------------------------------------------
|: Clear all Chat Boxes, Force a Reconnect to EQBC Server.
|:-----------------------------------------------------------------------
Sub Command_recon
	
	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	|: Clearing all Chat Boxes.
	/delay 2
	/ClearAll
	
	|: Clearing MQ Boxes.
	/delay 2
	/MQClear
	
	/delay 2
	/bccmd force
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
/return

|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Command_mount
	
	/Call Debug_Spew "Entering Subroutine. [${Macro.CurSub.Arg[1,(]}] Version: [1.00]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Mouted: [${Me.State.Equal[MOUNT]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

	/if (${Me.State.Equal[MOUNT]}) {
		/squelch /nomodkey /docommand /dismount
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/return
	}
	
	|: Set Variables for Mount Information.
	/if (!${Defined[x]}) /declare x int local
	/if (!${Defined[sMount]}) /declare sMount string local
	/if (!${Defined[SaveItemOld]}) /declare SaveItemOld string local NULL
	/if (!${Defined[SaveItemSlot]}) /declare SaveItemSlot string local NULL
	/if (!${Defined[MountSpeed]}) /declare MountSpeed string local NULL
	/if (!${Defined[Inventoryslot]}) /declare Inventoryslot int local 22


	/if (!${Defined[MountColors]}) /declare MountColors[6] string local
	
	|: Horses, Drogmors
	/varset MountColors[1] Black
	/varset MountColors[2] Brown
	/varset MountColors[3] Tan
	/varset MountColors[4] White
	|: Drogmors
	/varset MountColors[5] Green
	/varset MountColors[6] Red
	
	|: Mount Speeds
	|: %MountColors% Ornate Chain Bridle = Fast
	|: %MountColors% Chain Bridle = Run2
	|: %MountColors% Silken Bridle = Run1
	|: %MountColors% Leather Bridle = Slow2
	|: %MountColors% Rope Bridle = Slow1
	
	|: Drogmor Speeds
	|: Giant %MountColors% Drum = Run2
	|: Large %MountColors% Drum = Run1
	|: %MountColors% Drum = Slow2
	|: Small %MountColors% Drum = Slow1

	/for x 1 to ${MountColors.Size}
	
		|: Horse Mounts.
		/if (${Bool[${FindItem[=${MountColors[${x}]} Ornate Chain Bridle].ItemSlot}]}) {
			/varset sMount ${MountColors[${x}]} Ornate Chain Bridle
			/varset MountSpeed Fast
			/break
		} else /if (${Bool[${FindItem[=${MountColors[${x}]} Ornate Chain Bridle].ItemSlot}]}) {
			/varset sMount ${MountColors[${x}]} Ornate Chain Bridle
			/varset MountSpeed Fast
			/break
		} else /if (${Bool[${FindItem[=${MountColors[${x}]} Chain Bridle].ItemSlot}]}) {
			/varset sMount ${MountColors[${x}]} Chain Bridle
			/varset MountSpeed Run2
			/break
		} else /if (${Bool[${FindItem[=${MountColors[${x}]} Silken Bridle].ItemSlot}]}) {
			/varset sMount ${MountColors[${x}]} Silken Bridle
			/varset MountSpeed Run1
			/break
		} else /if (${Bool[${FindItem[=${MountColors[${x}]} Leather Bridle].ItemSlot}]}) {
			/varset sMount ${MountColors[${x}]} Leather Bridle
			/varset MountSpeed Slow2
			/break
		} else /if (${Bool[${FindItem[=${MountColors[${x}]} Rope Bridle].ItemSlot}]}) {
			/varset sMount ${MountColors[${x}]} Rope Bridle
			/varset MountSpeed Slow1
			/break
		}
		
		|: Drogmor Mounts.
		/if (${Bool[${FindItem[=Giant ${MountColors[${x}]} Drum].ItemSlot}]}) {
			/varset sMount Giant ${MountColors[${x}]} Drum
			/varset MountSpeed Run2
			/break
		} else /if (${Bool[${FindItem[=Large ${MountColors[${x}]} Drum].ItemSlot}]}) {
			/varset sMount Large ${MountColors[${x}]} Drum
			/varset MountSpeed Run1
			/break
		} else /if (${Bool[${FindItem[=${MountColors[${x}]} Drum].ItemSlot}]}) {
			/varset sMount ${MountColors[${x}]} Drum
			/varset MountSpeed Slow2
			/break
		} else /if (${Bool[${FindItem[=Small ${MountColors[${x}]} Drum].ItemSlot}]}) {
			/varset sMount Small ${MountColors[${x}]} Drum
			/varset MountSpeed Slow1
			/break
		}
	
	/next x


	/Call Debug_Spew "Loop Mounts Colors: [${MountColors.Size}] Found Mount: [${sMount}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	
	/Call Debug_Spew "Click Inventory: [${If[${FindItem[${sMount}].EffectType.Equal[Click Inventory]},TRUE,FALSE]}] Click Worn Only: [${If[${FindItem[${sMount}].EffectType.Equal[Click Worn]},TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${FindItem[${sMount}].EffectType.Equal[Click Inventory]}) {
		
		:ClearCursor0
		/Call Debug_Spew "CursorID: [${Cursor.ID}] Free Inventory: [${Me.FreeInventory}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Cursor.ID} && ${Me.FreeInventory}) /squelch /nomodkey /docommand /autoinventory
		/delay 15 !${Cursor.ID}
		
		/if (${Cursor.ID} && !${Me.FreeInventory}) {
			/call ChatOut 3 "Cursor Item [${Cursor.Name}], No Inventory Free Space. I am exiting mount command!" "0"
			/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/return
		}
		/if (${Cursor.ID}) /goto :ClearCursor0
		
		/Call Debug_Spew "[${sMount}] in AmmoSlot: [${If[${FindItem[${sMount}].ItemSlot} == 22,TRUE,FALSE]}] In a Bag Slot: [${If[${FindItem[${sMount}].ItemSlot} != 22,TRUE,FALSE]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${FindItem[${sMount}].ItemSlot} != 22) {
			
			/for x 23 to 32
				/if (${FindItem[${sMount}].ItemSlot} == ${x}) /varset Inventoryslot ${Math.Calc[${x}-22].Int}
			/next x
			
			/Call Debug_Spew "Pack${Inventoryslot} Container: [${If[${Me.Inventory[pack${Inventoryslot}].Container},TRUE,FALSE]}] Is a Bag: [${If[${Me.Inventory[pack${Inventoryslot}].Container} == 0,ITEM,${If[${Me.Inventory[pack${Inventoryslot}].Container} == NULL,BLANK,BAG]}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/if (${Me.Inventory[pack${Inventoryslot}].Container}) {
				/nomodkey /ctrlkey /itemnotify pack${Inventoryslot} rightmouseup
				/delay 15
				/nomodkey /ctrlkey /itemnotify in pack${Inventoryslot} ${Math.Calc[${FindItem[${sMount}].ItemSlot2}+1].Int} rightmouseup
				/delay 15
				/cleanup
			} else {
				/nomodkey /ctrlkey /itemnotify pack${Inventoryslot} rightmouseup
			}
			
		} else /if (${FindItem[${sMount}].ItemSlot} == 22) {
			/nomodkey /ctrlkey /itemnotify ammo rightmouseup
		}
		
		/call ChatOut 3 "Fastest Mount Found: [${MountSpeed}], Casting Mount [${sMount}]." "0"
		
	} else /if (${FindItem[${sMount}].EffectType.Equal[Click Worn]}) {
		
		/if (${Bool[${Me.Inventory[22].ID}]} || ${Bool[${Me.Inventory[ammo].ID}]}) /varset SaveItemOld ${Me.Inventory[22].Name}
		/Call Debug_Spew "Save Current Ammo Name: [${If[${Bool[${SaveItemOld}]},${SaveItemOld},Empty]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		
		:ClearCursor1
		/Call Debug_Spew "CursorID: [${Cursor.ID}] Free Inventory: [${Me.FreeInventory}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Cursor.ID} && ${Me.FreeInventory}) /squelch /nomodkey /docommand /autoinventory
		/delay 15 !${Cursor.ID}
		
		/if (${Cursor.ID} && !${Me.FreeInventory}) {
			/call ChatOut 3 "Cursor Item [${Cursor.Name}], No Inventory Free Space. I am exiting mount command!" "0"
			/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
			/return
		}
		/if (${Cursor.ID}) /goto :ClearCursor1
		
		/Call Debug_Spew "AmmoSlot Not [${sMount}]: [${Me.Inventory[22].Name.NotEqual[${sMount}]}] Ammo Slot Empty: [!${Bool[${Me.Inventory[22].Name}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Me.Inventory[22].Name.NotEqual[${sMount}]} || !${Bool[${Me.Inventory[22].Name}]}) {
			/if (${Plugin[MQ2Exchange].Name.Length}) {
				/Call Debug_Spew "Swamp Ammo Slot: [${Bool[${Me.Inventory[22].ID}]} || ${Bool[${Me.Inventory[ammo].ID}]}] Exchange: [${sMount}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
				/if (${Bool[${Me.Inventory[22].ID}]} || ${Bool[${Me.Inventory[ammo].ID}]}) {
					/call ChatOut 3 "Swapping [${Me.Inventory[22].Name}] for Mount [${sMount}]." "0"
					/squelch /nomodkey /docommand /unequip ammo
				}
				/squelch /nomodkey /docommand /exchange "${sMount}" ammo
				/delay 15
			} else {
				/call ChatOut 3 "Plugin Missing: [MQ2Exchange]. Unable to Swap Items." "0"
			}
		}
		/nomodkey /ctrlkey /itemnotify ammo rightmouseup
		
		/call ChatOut 3 "Fastest Mount Found: [${MountSpeed}], Casting Mount [${sMount}]." "0"

		
		|: Cast Over SwapItem Back if there was one.
		/Call Debug_Spew "Ammo Slot = [${SaveItemOld}]: [${Me.Inventory[22].Name.NotEqual[${SaveItemOld}]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/if (${Me.Inventory[22].Name.NotEqual[${SaveItemOld}]} && ${Bool[${SaveItemOld}]}) {
			/call ChatOut 3 "Swapping [${Me.Inventory[22].Name}] for Mount [${SaveItemOld}]." "0"
			/squelch /nomodkey /docommand /unequip ammo
			/squelch /nomodkey /docommand /exchange "${sMount}" ammo
			/delay 15
		}
		
	}

	:ClearCursor2
	/Call Debug_Spew "CursorID: [${Cursor.ID}] Free Inventory: [${Me.FreeInventory}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
	/if (${Cursor.ID} && ${Me.FreeInventory}) /squelch /nomodkey /docommand /autoinventory
	/delay 15 !${Cursor.ID}
	
	/if (${Cursor.ID} && !${Me.FreeInventory}) {
		/call ChatOut 3 "Cursor Item [${Cursor.Name}], No Inventory Free Space. I am exiting mount command!" "0"
		/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"
		/return
	}
	/if (${Cursor.ID}) /goto :ClearCursor2
	
	/Call Debug_Spew "Leaving Subroutine. [${Macro.CurSub.Arg[1,(]}]" "ALL,CORE,${Macro.CurSub.Arg[1,(]}" "${Macro.Params}" "${Macro.CurSub}" "${Macro.CurLine}" "${Macro.MemUse}" "${Macro.RunTime}" "${Macro.Name}"

/return


Sub Command_feign

/if (!${Defined[FeignSpell]}) /declare FeignSpell string local
|: Monk / Shadow Knight / Necromancer
/if (${Me.AbilityReady[Feign Death]} && ${Select[${Me.Class.ShortName.Upper},MNK]}) ) {
	/varset FeignSpell Feign Death|CA
} else /if (${Bool[${Me.AltAbility[Death Peace].ID}]} && ${Me.AltAbilityReady[Death Peace]}) {
	/varset FeignSpell Death Peace|AA
} else /if (${Me.Book[Death Peace]}) {
	/varset FeignSpell Death Peace|Spell
} else /if (${Me.Book[Comatose]}) {
	/varset FeignSpell Comatose|Spell
} else /if (${Me.Book[Feign Death]}) {
	/varset FeignSpell Feign Death|Spell
} 

/if (${Me.Combat} && ${Toggle-melee}) /attack off
/if (${CombatTargetID}) /varset CombatTargetID 0
/if (${Stick.Active}) /stick off

/if (!${Me.Feigning}) {
	
	/if (${FeignSpell.Arg[2,|].Equal[CA]}) {
		/doability "${FeignSpell.Arg[1,|]}"
	} else /if (${FeignSpell.Arg[2,|].Equal[AA]} || ${FeignSpell.Arg[2,|].Equal[Spell]}) {
		/casting "${FeignSpell.Arg[1,|]}" -invis
	}
	
	/delay 5s !${Casting.ID}
	
	:Wait4Spell
	/delay 1s
	/if (${Me.Feigning}) /call ChatOut 3 ${FeignSuccessful-msg} "0"
	/if (${Window[SpellBookWnd].Open} (${Cast.Status.Equal[M]} || ${Cast.Status.Equal[C]} || ${Cast.Status.Equal[CM]}))  /goto :Wait4Spell

}

/return

Sub Command_anchor(string Options)

/if (${Options.Lower.Equal[on]}) {
	/varset IsHead ${Me.Heading.DegreesCCW}
	/varset IsZone ${Zone.ID}
	/varset Ypos ${Me.Y}
	/varset Xpos ${Me.X}
	/varset IsCamp 1
	/call ChatOut 3 "Created anchor at Loc: ${Ypos},${Xpos}." "0"
} else /if (${Options.Lower.Equal[off]}) {
	/varset IsHead
	/varset IsZone 
	/varset Ypos 
	/varset Xpos 
	/varset IsCamp 0
	/call ChatOut 3 "Removed Anchor." "0"
}

/return

Sub Command_guard(string Options)

/if (${Options.Lower.Equal[on]}) {
	/varset IsHead ${Me.Heading.DegreesCCW}
	/varset IsZone ${Zone.ID}
	/varset Ypos ${Me.Y}
	/varset Xpos ${Me.X}
	/varset IsCamp 1
	/call ChatOut 3 "Created anchor at Loc: ${Ypos},${Xpos}." "0"
} else /if (${Options.Lower.Equal[off]}) {
	/varset IsHead
	/varset IsZone 
	/varset Ypos 
	/varset Xpos 
	/varset IsCamp 0
	/call ChatOut 3 "Removed Anchor." "0"
}

/return

Sub Command_disc(string DiscName)

/if (${Select[${Me.Class},Bard]}) {
	/if (!${Defined[CurrentTwist]}) /declare CurrentTwist string local
	/varset CurrentTwist ${Twist.List}
	/call ExecCommand "stop"
}

/if (!${Me.CombatAbilityReady[${DiscName}]}) {
	/call ChatOut 4 ${DiscErr-msg.Replace[@,$]} "0"
	/return
}

:delay_disc
/if (${Me.Casting.ID}) {
	/goto :delay_disc
} else /if (${Me.State.Equal[BIND]}) {
	/notify LootWnd DoneButton leftmouseup
	/goto :delay_disc
}

/call ChatOut 4 "Master Disc [${DiscName}] is turned on." "0"

/disc ${DiscName}

/if (${Select[${Me.Class},Bard]}) {
	/delay 10
	/call ExecCommand "twist ${CurrentTwist}"
}

/return