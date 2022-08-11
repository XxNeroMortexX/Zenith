Sub Alias_Setup

	/squelch /alias /gb /echo Genbot

	|: Special Vet AAs	
	/alias /Resist /echo Genbot alt Infusion of the Faithful
	/alias /Armor /echo Genbot alt Armor of Experience
	/alias /DPS /echo Genbot alt Intensity of the Resolute
	/alias /Recover /echo Genbot alt Staunch Recovery
	/alias /Merc /echo Genbot alt Steadfast Servant

	/alias /intensity /echo Genbot alt Intensity of the Resolute
	/alias /infusion /echo Genbot alt Infusion of the Faithful
	/alias /lesson /echo Genbot alt Lesson of the Devoted
	/alias /mgb /echo Genbot alt Mass Group Buff
	/alias /throne /echo Genbot alt Throne of Heroes
	/alias /rCure /echo Genbot alt Radiant Cure

	|: REmove These Later.
	/alias /GL /squelch /nomodkey /docommand ${If[${Select[${Group.Leader},${Me.CleanName}]},/guildsay GL,]}
	/alias /Leaders /squelch /nomodkey /docommand ${If[${Select[${Group.Leader},${Me.CleanName}]},/shout ,]}

/return