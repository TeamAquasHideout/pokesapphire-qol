MountainHeart_MapScripts::
	.byte 0


TriggerGroudon::
	goto_if_unset FLAG_GROUDON_POSTGAME, TriggerGroudon_2
TriggerGroudon_1:
	release
	end

TriggerGroudon_2:
	goto StartCutscene
	goto TriggerGroudon_1


StartCutscene::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	special ShakeScreenInElevator
	applymovement 1, GroudonMoveForward
	waitstate
	waitmovement 1
	special ShakeScreenInElevator
	applymovement 1, GroudonMoveForward
	waitstate
	waitmovement 1
	special ShakeScreenInElevator
	applymovement 1, GroudonMoveForward
	waitstate
	waitmovement 1
	playmoncry SPECIES_GROUDON, 2
	setwildbattle SPECIES_GROUDON, 80, ITEM_NONE
	delay 40
	waitmoncry
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special ScrSpecial_StartGroudonKyogreBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	removeobject 1
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, 1
	call_if_eq GroudonDefeat
	setflag FLAG_GROUDON_POSTGAME
	release
	end


GroudonDefeat::
	msgbox String_GroudonDefeat, MSGBOX_DEFAULT
	closemessage
	return


GroudonMoveForward:
	walk_down
	step_end

TestScriptGroudon::
	clearflag FLAG_GROUDON_POSTGAME
	return


String_GroudonDefeat:
	.string "Groudon appears to have settled\n"
	.string "into sleep again...$"
