|:-----------------------------------------------------------------------
|: 
|:-----------------------------------------------------------------------
Sub Toggle_checkname(Param0, Param1, Param2, Param3)
/echo Toggle Set First Then Subroutine is called.
/echo My Params are: ${Param0} ${Param1} ${Param2} ${Param3}
/return
Sub Toggle_aggro
/if (!${Toggle-aggro}) {
	|: Reset to Default Tant Setting
	/if (${Toggle-taunt} != ${Toggle-taunt-DefaultValue}) /varset Toggle-taunt ${Toggle-autobehind-DefaultValue}
	|: Reset to Default Autobehind Setting
	/if (${Toggle-autobehind} != ${Toggle-autobehind-DefaultValue}) /varset Toggle-autobehind ${Toggle-autobehind-DefaultValue}
	|: Reset to Default Autodistance Setting
	/if (${Toggle-autodistance} != ${Toggle-autodistance-DefaultValue}) /varset Toggle-autodistance ${Toggle-autobehind-DefaultValue}
	|: Reset to Default MeleeRange Setting
	/if (${MeleeRange} != ${MeleeRange-DefaultValue} && !${Toggle-autodistance}) /varset MeleeRange ${MeleeRange-DefaultValue}
}
/return