**Zenith v1.0.0 Bot**
-----------------------------------------------------------------

Thanks for Using NeroMorte Macro Zenith
* **Guild:** Blades of Discord
* **Created By:** NeroMorte
* **Discord:** NeroMorte#8786
* **Created for SERVER:** [PEQ] The Grand Creation - Omens of War

-------

<p align="center">
    <a href="#what-is-zenith">What is Zenith?</a> &bull;
    <a href="#to-call-out-specific-bots">Call Specific Bots</a> &bull;
    <a href="#movement-commands">Bot Movement</a> &bull;
    <a href="#attack-commands">Bot Attack</a> &bull;
    <a href="#heal-commands">Bot Heal</a> &bull;
    <a href="#buff-commands">Bot Buff</a> &bull;
    <a href="#misc-commands">Bot Misc</a> &bull;
    <a href="#travel-commands">Bot Travel</a> &bull;
    <a href="../wiki/attack">attack</a> &bull;
    <a href="https://github.com/XxNeroMortexX/Zenith/archive/refs/heads/main.zip">Download Zenith</a>
</p>

-------

# What is Zenith?

In 2009 I took over the "Genbot Project", made some changes bring it to version 14.4.5, I maintain the Updates and changes up to version v15.0.7 in 2016. I have stopped playing EverQuest for awhile then in 2020 I came back and decided to Completely Rewrite Genbot and Update all the Code with new MQ2 Base Code. I have decided to rename the macro from "Genbot" to "Zenith" only because I have rewritten over 95% of the Code, only left the idea of how Genbot use to work alive. Now Zenith is a Multi Class MQ2 Macro for EverQuest, was Inspired by Original "Genbot", I have re-wrote all Subrountines with new updated MQ2 2017 Base Code.

I have left the same idea of how Commands, Toggles, Shortcuts all work in the code.

### Included Scripts:
* **Smooth Moves v2.5** Created and developed by Killians from [EQEMU PEQTGC Server](http://www.projecteq.net/)
   * Records and saves Routes/Waypoints to Ini file.
   * Routes can be recalled later to run you from one place to another automatically.

* **Ninja Advance loot v6.1** by Maskoi in 11/12/2019

* **Wait4Rez v1.4** by A_Druid_00 (originally written by fantum409)

------

```
Genbot History:

Genbot was released by GrimJack sometime in early 2003 and eventually became one of the more popular
bot macros. Genbot was originally designed as a core set of scripts to handle all of the non class
specific functions needed in a bot while providing a means to easily "plug in" any extra code
needed for a specific character.

Version 0 - 8.8 Genbot created and developed by GrimJack
Version 8.8 - ? GrimJack stopped playing Everquest, Lasher took over the code.
Version ? - 12.34 Lord Giddeon maintained the code.
Version 12.35 - 13.3 Vexix took over the code.
Version 13.3 - 15.0.7 NeroMorte took over the code.
```

# To Call out Specific Bots:

<b>Before Any Command to your Bot Add any of the Following in front of the command minus [ | ].</b>

<Pre>

[<i>Bots Name</i>] <b>Command</b>

<sub>Melee Classes</sub>
[<i>Berserker|Ber|Monk|Mnk|Rogue|Rog|Warrior|War|Melees</i>] <b>Command</b>

<sub>Priest Classes</sub>
[<i>Cleric|Clr|Druid|Dru|Shaman|Shm|Priests</i>] <b>Command</b>

<sub>Caster Classes</sub>
[<i>Enchanter|Enc|Nagician|Mag|Necromancer|Nec|Wizard|Wiz|Casters</i>] <b>Command</b>

<sub>Hybrid Classes</sub>
[<i>Bard|Brd|Beastlord|Bst|Paladin|Pal|Ranger|Rng|Shadow Knight|Shd|Hybirds|Hybrids</i>] <b>Command</b>

<sub>Archetype Classes</sub>
[<i>Melees|Priests|Casters|Hybirds|Hybrids|PetClass</i>] <b>Command</b>

<sub>Other Types (Group Leaders Only)|(Group Number Replace # with 1-9 <a href="#GrpLeadersOrder">See <b>GrpLeadersOrder</b> Below</a>)</sub>
[<i>leaders|Group#</i>] <b>Command</b>

</Pre>

# Ini Comments:

<Pre>
<b>[CORE]</b>
</pre>

#### ClassTypes
  > * These Setting are for when Call out Specific Bots only.
#### GrpLeadersOrder
  > * When Using [Group#] to Command a Group of Bots, List your group leaders name in order. Spereated by |
#### Masters
  > * List of character names allowed to command your bot. Also allow to add another Bots ini file here E.G; bot_Mortefreddo_Enchancter.ini Seperated by |
#### ChatOut
  > * Determine if Bots will Send Chat into ChatIn. Options: SHOW|HIDE|Settings|Events|Core|Combat|Healer|Spell|Pets|Params|Routines|Update|Ini
#### ChatIn
  > * Changes what channel the bot will use for replying to it's master. Options: EQBC|GUILD|GROUP|SAY|RAID|TELL|IRC|CHANNEL|/ChannelName
#### ListenInChannels
  > * Determines what channel the bot will Listen for Commands from it's master. Options: CHAT,GUILD,GROUP,TELL,SAY,SHOUT,RAID,IRC,EQBC
#### checkname
  > * Toggle(On/Off) if set to true, bot will only respond to commands if the command is preceeded with Bots Name first.
#### IgnGroupList
  > * List of command Spereated by | to Ignore in group chat.
#### dopublic
  > * Toggle(On/Off) if set to true, Bot will Obay Commands from everyone.
#### PublicCommands
  > * List Command(s) you want to be public seperated by |
#### CrossZoneCommands
  > * List Command(s) you want to be able to call across zone lines. seperated by |
#### relaytells
  > * Toggle(On/Off) Bot will Send all Tells into [ChatIn] Channel
#### autobeep
  > * Toggle(On/Off) This will Keep doin System Beeping when you receive a [Tell] untill autobeep off Command Given.
#### movetomode
  > * Allows you to change the way bot moves. 1  =  Moveutils, 2  =  Nav, 3  =  AdvPath
#### followmode
  > * Allows you to change the way bot follows. 1  =  Moveutils, 2  =  Nav, 3  =  AdvPath
#### autofollow
  > * Bot Auto Follow [autofollowTarget] automatically after any current Commands Pending is done.
#### autofollowTarget
  > * This is the Target Bot will Auto Follow when autofollow = ON
#### FollowLeash(Min|Max)
  > * Bot Distance Check for autofollow. Might Remove This
#### bottracker
  > * Bot will Track other Bots Lost, Not in Zone.
#### BotTrackerDistance
  > * The Distance Bots have to be before it will Start tracking others.
#### DebugList
  > * This is to have Macro Show Debug information. To Locate problems Options: None|ALL|Core|Main|Shortcuts|Subrountine Name
#### ControlPass
  > * If anyone sends your Bot This Keyword they will be added to Masters List Temporary, Allowed Full Control over you.
#### factionhits
  > * Bots will Display what Faction hits they Received in ChatIn Channel. 
#### autoaaexp
  > * Bot will Auto Change AA Percent based on Current XP/Level. E.G; Check IF (Level < 70 || Level == 70 && XP < 80 Set AA 0) || (Level == 70 && XP > 97 Set AA 100)
#### autoleaderaa
  > * This will make sure your Leadership AAs are always ON.
#### reportexp
  > * This will have bots Report to ChatIn Channel when they Receive XP.
#### HUDBotTrackerGrp1-3
  > * List of character names to Track in MQ2Hud. Seperated by |
#### spawnlist
  > * 
#### autorelog
  > * This will Force Bot to Automatically Log back into game when they LD/Crash to Character Select Screen.

<Pre>
<b>[COMBAT]</b>
</pre>

#### autobehind
  > * Forces the bot to always get behind target on assist.
#### autoengage
  > * The bot will use (MQ2MoveUtils) to stick to assist target.
#### autosnap
  > * Forces the bot to always Face the Target.
#### raidevade
  > * Forces the bot to turn attack off if they are hit.
#### MaxTargetRange
  > * Max Range Bots will Assist at.
#### melee
  > * This will turn Bot Melee on automatically. When in Combat.
#### archery
  > * This will turn Bot Archery autofire on automatically. When in Combat.
#### MeleeRange
  > * This is Bots Melee Distance from Target bot will Assist at.
#### ArcheryRange
  > * This is Bots Archery Distance from Target bot will Assist at. Minimum Setting = 34
#### AutoArrowType
  > * NOT WORKING ATM.
#### autodistance
  > * Forces the Bot to Set Combat Distance Depending on Targets MaxRangeTo Value.
#### pvpmode
  > * Allows Bot to be able to Attack PC Players/Pets
#### autostand
  > * Forces Bot to Standup Automatically if Sitting or Feign only when in Combat.
#### defend
  > * Bot will Automatically Attack Back if hit by a NPC.
#### enrage
  > * Forces Bot to turn attack off if Target Enrages, Turns Attack back on after Enrage Done Automatically.
#### MainAssist
  > * Bot uses this Target as Assist Target when you call Command (Assist) without any Params.
#### GuardRadius
  > * The Distance Around Bot that he will Automatically Attack Targets.
#### ProtectRadius
  > * The Distance bot will Check from Protect Targets.
#### guard
  > * This will make Bot Guard a Certian Area for NPCs
#### GuardXTar
  > * 
#### GuardMA
  > * 
#### protect
  > * This will make Bot Protect Names on ProtectionList.
#### puller
  > * This will allow you to pull Trgets When Guard is on, Guard will only Automatically Take over when within 1/3 Distance from Guard Location.
#### ProtectionList
  > * This is a List of Bots to Automatically Protect when they get Attacked.
#### NeverKill
  > * List of NPCs Bots will never Attack.
#### Guard_Protect_Alert
  > * The numbers of times to Beep when Monster Attacks ProtectList or Near Guard Location. Ex. 3
#### autotarget
  > * This Will Allow you to Switch Target in middle of Combat.
#### autotargetclear
  > * 
#### manualmode
  > * This will Stop Bot from Automatically Turning Melee/Archery/Casting ON
  
  
# Movement Commands:

#### Sit
 > * Coomands bot to Sit.
#### Stand
 > * Commands bot to Stand
#### Stay
 > * Commands bot to stop following, Clear Queued Events, Pet stop & Pet hold, Guard on if autoguard Set.
#### Stop
 > * Commands bot to stop following, Clear Combat Target, Stops Twitch, Clears WatchTarget, Clears Anchors, Stop Bard Twist, Clear Queued Events,  Pet stop, Dismount, Turn Attack off, Guard off if autoguard Set.
#### Follow
 > * Follow <Target Optional [Me|Target]> Commands bot to Follow <[Me|Target]> As long as They are less then 250 Distance.
#### MoveTo
 > * MoveTo <Target Optional [Me|Target|Y X Z><Optional Dist> Commands bot to move to Target/Location given.
#### Moveup
 > * Moveup <Distance in Fifths> Commands bot to Move Forward the Set Distance.
#### Jump
 > * Commands bot to Press Forward key and Jump.
#### Anchor
 > * Anchor <ON|OFF> Commands bot to Set [X,Y,Z] Location, if Attacking/Moving once done Automatically goto Anchor Location.
#### Mount
 > * Commands bot to Cast Any Mount in [Bags/Ammo], If mounted will Dismount Automatically otherwise will Get on Mount.
#### Zone
 > * Commands bot to goto ur X,Y,Z Location Face same Direction you are and Keypress FORWARD till Zoned.
#### Clickit
 > * Clickit <Optional NoZone> Commands bot to goto ur X,Y,Z Location Face same Direction you are and Try Click Object.

# Attack Commands:

# Heal Commands:

# Buff Commands:

# Misc Commands:

# Travel Commands:

