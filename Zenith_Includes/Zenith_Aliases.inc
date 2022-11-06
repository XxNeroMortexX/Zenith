Sub Alias_Setup
	/squelch /alias /gb /echo Genbot
	|: Special Vet AAs	
	/alias /Resist /Casting "Infusion of the Faithful"
	/alias /Armor /Casting "Armor of Experience"
	/alias /DPS /Casting "Intensity of the Resolute"
	/alias /Recover /Casting "Staunch Recovery"
	/alias /Merc /Casting "Steadfast Servant"
	/alias /infusion /Casting "Infusion of the Faithful"
	/alias /intensity /Casting "Intensity of the Resolute"
	/alias /Staunch /Casting "Staunch Recovery"
	/alias /lesson /Casting "Lesson of the Devoted"
	/alias /throne /Casting "Throne of Heroes"
	|: AAs
	/alias /mgb /Casting "Mass Group Buff"
	/alias /RC /casting "Radiant Cure"
	|: REmove These Later.
	/alias /GL /squelch /nomodkey /docommand ${If[${Select[${Group.Leader},${Me.CleanName}]},/guildsay GL,]}
	/alias /Leaders /squelch /nomodkey /docommand ${If[${Select[${Group.Leader},${Me.CleanName}]},/shout ,]}
	/alias /Leadersgu /squelch /nomodkey /docommand ${If[${Select[${Group.Leader},${Me.CleanName}]},/guildsay ,]}
/return