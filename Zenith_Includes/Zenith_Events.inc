#event EscKey     	   "You no longer have a target."
Sub Event_EscKey

|: Enable user Triggered Interrupt.
/varset interruptFlag TRUE

|: Reset CombatTargetID to nothing.
/varset CombatTargetID 0
/delay 5 ${CombatTargetID} == 0

|:Stop Twitch
/varset TwitchStop 1

|:Reset EnrageVar Target
/varset EnrageVar 0

|:Turn off Follow Target Param
/varset FollowTargetID 0

/varset DebuffList

|: Turn off Auto follow.
/if (${Stick.Active} && ${Stick.Status.NotEqual[OFF]}) /stick off

|:Issue a Pet Stop command.
/if (${Me.Pet.ID}) {
	/Pet stop
	/pet back off
}

|: Me on mount then Dismount.
/if (${Me.Mount.ID}) /dismount
/echo 2
/squelch /target clear

|:Make Sure Combat not Turned on.
/if (${Me.Combat} && ${Toggle-melee}) /attack off
/if (${Me.AutoFire} && ${Toggle-archery}) /autofire off

/if (${Toggle-guard}) /varset Toggle-guard FALSE
/if (${Toggle-anchor}) /varset Toggle-anchor FALSE

|: Flush all Queued Events
/doevents flush

/return