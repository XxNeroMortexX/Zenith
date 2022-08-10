Sub CheckFollowing

	|:Check IF CombatTargetID, IF Sticking to Target, IF i have FollowTargetID Set.
	/if (${Target.ID} != ${CombatTargetID} && ${Stick.Active} && ${Bool[${Spawn[pc ${FollowTargetID}].ID}]} && ${Bool[${FollowTargetID}]} != 0) {
		/if (${MoveUtils.Command.NotEqual[NONE]} && !${Me.Moving}) /squelch /nomodkey /docommand /stick off
	}
	
/return