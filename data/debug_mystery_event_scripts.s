.if DEBUG
#include "constants/decorations.h"
#include "constants/flags.h"
#include "constants/game_stat.h"
#include "constants/items.h"
#include "constants/event_objects.h"
#include "constants/maps.h"
#include "constants/moves.h"
#include "constants/opponents.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/weather.h"
#include "constants/vars.h"
	.include "include/macros.inc"
	.include "constants/constants.inc"
	.include "include/macros/event.inc"

	.section .rodata

.ifdef ENGLISH
    .set unkConstant, 2
.else @ GERMAN
    .set unkConstant, 4
.endif @ GERMAN

.ifdef SAPPHIRE
    .set versionMask, 0x100
.else @ RUBY
    .set versionMask, 0x80
.endif @ RUBY

gUnknown_Debug_845DAE1::
	me_checkcompat gUnknown_Debug_845DAE1, unkConstant, unkConstant, 0x4, versionMask
	me_crc 0x0, _0845DAFF, _0845DAFFEnd
_0845DAFF:
	me_initramscript MAP_PETALBURG_CITY_GYM, 0x1, _845DB56, _845DB56End
	me_setrecordmixinggift 0x1, 0x5, ITEM_EON_TICKET
	me_runscript _0845DD0D
	me_end

.ifdef ENGLISH
_0845DB16:
	.string "Go see your father at the GYM in\n"
	.string "PETALBURG.$"
.else @ GERMAN
_0845DB16:
	.string "Lauf und besuche deinen Vater in der\n"
	.string "ARENA von BLÜTENBURG CITY.$"
.endif @ GERMAN
_845DB56:
	setvaddress _845DB56
	checkitem ITEM_EON_TICKET, 0x1
	compare VAR_RESULT, 0x1
	vgoto_if 0x1, _0845DBB4
	checkpcitem ITEM_EON_TICKET, 0x1
	compare VAR_RESULT, 0x1
	vgoto_if 0x1, _0845DBB4
	checkflag FLAG_ENCOUNTERED_LATIAS_OR_LATIOS
	vgoto_if 0x1, _0845DBB4
	lock
	faceplayer
	vmessage _0845DBBE
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_EON_TICKET, 0x1
	compare VAR_RESULT, 0x0
	vgoto_if 0x1, _0845DBB5
	setorcopyvar VAR_0x8000, ITEM_EON_TICKET
	setorcopyvar VAR_0x8001, 0x1
	callstd 0x0
	setflag FLAG_SYS_HAS_EON_TICKET
	vmessage _0845DC00
	waitmessage
	waitbuttonpress
	release
_0845DBB4:
	killscript
_0845DBB5:
	vmessage _0845DC94
	waitmessage
	waitbuttonpress
	release
	end

.ifdef ENGLISH
_0845DBBE:
	.string "DAD: {PLAYER}! Good to see you!\n"
	.string "There's a letter here for you, {PLAYER}.$"
_0845DC00:
	.string "DAD: It appears to be a ferry TICKET,\n"
	.string "but I've never seen one like it before.\p"
	.string "You should visit LILYCOVE and ask\n"
	.string "about it there.$"

_0845DC94:
	.string "DAD: {PLAYER}, the KEY ITEMS POCKET in\n"
	.string "your BAG is full.\p"
	.string "Move some key items for safekeeping\n"
	.string "in your PC, then come see me.$"
.else @ GERMAN
_0845DBBE:
	.string "VATER: {PLAYER}! Schön, dich zu sehen!\n"
	.string "Hier ist ein Brief für dich, {PLAYER}.$"
_0845DC00:
	.string "VATER: Ich bin mir nicht sicher, es\n"
	.string "könnte ein TICKET für eine Fähre sein.\p"
	.string "Du solltest nach SEEGRASULB CITY gehen\n"
	.string "und dich dort genauer erkundigen.$"

_0845DC94:
	.string "VATER: {PLAYER}, die BASIS-TASCHE\n"
	.string "deines BEUTELS ist voll.\p"
	.string "Lagere einige deiner Basis-Items in\n"
	.string "deinem PC und komm dann wieder.$"
.endif @ GERMAN

_845DB56End:
	.size _845DB56, _845DB56End - _845DB56

_0845DD0D:
	setvaddress _0845DD0D
	checkitem ITEM_EON_TICKET, 0x1
	compare VAR_RESULT, 0x1
	vgoto_if 0x1, _0845DD53
	checkpcitem ITEM_EON_TICKET, 0x1
	compare VAR_RESULT, 0x1
	vgoto_if 0x1, _0845DD53
	checkflag FLAG_ENCOUNTERED_LATIAS_OR_LATIOS
	vgoto_if 0x1, _0845DD53
	checkitemspace ITEM_EON_TICKET, 0x1
	compare VAR_RESULT, 0x0
	vgoto_if 0x1, _0845DD5B
	vloadptr _0845DB16
	setmysteryeventstatus 0x2
	end

_0845DD53:
	vloadptr _0845DD63
	setmysteryeventstatus 0x3
	end

_0845DD5B:
	vloadptr _0845DD95
	setmysteryeventstatus 0x3
	end

.ifdef ENGLISH
_0845DD63:
	.string "This EVENT may be played only once.$"
_0845DD95:
	.string "Your BAG's KEY ITEMS POCKET is full.$"
.else @ GERMAN
_0845DD63:
	.string "Dieses GESCHEHEN kann nur einmal\n"
	.string "gespielt werden.$"
_0845DD95:
	.string "Deine BASIS-TASCHE ist voll.$"
.endif @ GERMAN

_0845DAFFEnd:
	.size _0845DAFF, _0845DAFFEnd - _0845DAFF
gUnknown_Debug_845DAE1End::

gUnknown_Debug_845DDB2::
	me_checkcompat gUnknown_Debug_845DDB2, unkConstant, unkConstant, 0x4, versionMask
	me_checksum 0x0, _0845DDD0, _0845DDD0End
_0845DDD0:
	me_setenigmaberry gUnknown_Debug_845DDD6
	me_end

gUnknown_Debug_845DDD6::
	.space 0x530
_0845DDD0End:
	.size _0845DDD0, _0845DDD0End - _0845DDD0
gUnknown_Debug_845DDB2End::

gUnknown_Debug_845E306::
	me_checkcompat gUnknown_Debug_845E306, unkConstant, unkConstant, 0x4, versionMask
	me_runscript _0845E329
	me_setmsg 0x2, _0845E34F
	me_setmsg 0x3, _0845E387
	me_end

_0845E329:
	setvaddress _0845E329
	getpartysize
	compare VAR_RESULT, 0x6
	vgoto_if 0x1, _0845E34C
	givemon SPECIES_LUVDISC, 15, ITEM_BERRY_JUICE
	setmysteryeventstatus 0x2
	end

_0845E34C:
	setmysteryeventstatus 0x3
	end

.ifdef ENGLISH
_0845E34F:
	.string "A Pokémon was added to the\n"
	.string "player's party.$"

_0845E387:
	.string "The player's party is full.\n"
	.string "A Pokémon couldn't be added.$"
.else @ GERMAN
_0845E34F:
	.string "Ein Pokémon wurde in das Team des\n"
	.string "Spielers aufgenommen.$"

_0845E387:
	.string "Das Team des Spielers ist vollständig.\n"
	.string "Es kann kein weiteres Pokémon\l"
	.string "aufgenommen werden.$"
.endif @ GERMAN

gUnknown_Debug_845E3E0::
	me_checkcompat gUnknown_Debug_845E3E0, unkConstant, unkConstant, 0x4, versionMask
	me_crc 0x0, _0845E3FE, _0845E3FEEnd
_0845E3FE:
	me_giveribbon 0x0, 0x1
	me_end
_0845E3FEEnd:
	.size _0845E3FE, _0845E3FEEnd - _0845E3FE
gUnknown_Debug_845E3E0End::

gUnknown_Debug_845E402::
	me_checkcompat gUnknown_Debug_845E402, unkConstant, unkConstant, 0x4, versionMask
	me_crc 0x0, _0845E420, _0845E420End
_0845E420:
	me_givenationaldex
	me_end
_0845E420End:
	.size _0845E420, _0845E420End - _0845E420
gUnknown_Debug_845E402End::

gUnknown_Debug_845E422::
	me_checkcompat gUnknown_Debug_845E422, unkConstant, unkConstant, 0x4, versionMask
	me_crc 0x0, _0845E440, _0845E440End
_0845E440:
	me_addrareword 0x1
	me_end
_0845E440End:
	.size _0845E440, _0845E440End - _0845E440
gUnknown_Debug_845E422End::

gUnknown_Debug_845E443::
	me_checkcompat gUnknown_Debug_845E443, unkConstant, unkConstant, 0x4, versionMask
	me_crc 0x0, _0845E461, _0845E461End
_0845E461:
	me_givepokemon gUnknown_Debug_845E467
	me_end

gUnknown_Debug_845E467::
	.space 100

gUnknown_Debug_845E4CB::
	.space 36
_0845E461End:
	.size _0845E461, _0845E461End - _0845E461
gUnknown_Debug_845E443End::

gUnknown_Debug_845E4EF::
	me_checkcompat gUnknown_Debug_845E4EF, unkConstant, unkConstant, 0x4, versionMask
	me_addtrainer gUnknown_Debug_845E506
	me_end

gUnknown_Debug_845E506::
	.space 256
gUnknown_Debug_845E4EFEnd::

gUnknown_Debug_845E606::
	me_checkcompat gUnknown_Debug_845E606, unkConstant, unkConstant, 0x4, versionMask
	me_enableresetrtc
	me_end
gUnknown_Debug_845E606End::

gUnknown_Debug_845E619::
	me_checkcompat gUnknown_Debug_845E619, unkConstant, unkConstant, 0x4, versionMask
	me_checksum 0x0, _0845E637, _0845E637End
_0845E637:
	me_initramscript MAP_PETALBURG_CITY_GYM, 0x1, _0845E683, _0845E683End
	me_setmsg 0xff, _0845E64C
	me_setstatus 0x2
	me_end

.ifdef ENGLISH
_0845E64C:
	.string "Go see your dad at the\n"
	.string "PETALBURG GYM.$"
.else @ GERMAN
_0845E64C:
	.string "Besuche deinen Vater in der ARENA\n"
	.string "von BLÜTENBURG CITY.$"
.endif @ GERMAN

_0845E683:
	setvaddress _0845E683
	checkitem ITEM_GANLON_BERRY, 0x1
	compare VAR_RESULT, 0x1
	vgoto_if 0x1, _0845E6BF
	checkpcitem ITEM_GANLON_BERRY, 0x1
	compare VAR_RESULT, 0x1
	vgoto_if 0x1, _0845E6BF
	lock
	faceplayer
	vmessage _0845E6C0
	waitmessage
	waitbuttonpress
	setorcopyvar VAR_0x8000, ITEM_GANLON_BERRY
	setorcopyvar VAR_0x8001, 0x1
	callstd 0x0
	release
	killscript
_0845E6BF:
	gotoram

.ifdef ENGLISH
_0845E6C0:
	.string "DAD: Hi, {PLAYER}!\p"
	.string "I just received a rare BERRY.\n"
	.string "I'd like you to have it.$"
.else @ GERMAN
_0845E6C0:
	.string "VATER: Hi, {PLAYER}!\p"
	.string "Ich habe gerade diese seltene BEERE\n"
	.string "erhalten. Ich schenke sie dir!$"
.endif @GERMAN

_0845E637End:
	.size _0845E637, _0845E637End - _0845E637
_0845E683End:
	.size _0845E683, _0845E683End - _0845E683
gUnknown_Debug_845E619End::

gUnknown_Debug_845E712::
	me_checkcompat gUnknown_Debug_845E712, unkConstant, unkConstant, 0x4, versionMask
	me_crc 0x0, _0845E730, _0845E730End
_0845E730:
	me_runscript _0845E736
	me_end

_0845E736:
	setvaddress _0845E736
	bufferdecorationname 0x0, DECOR_REGISTEEL_DOLL
	adddecoration DECOR_REGISTEEL_DOLL
	compare VAR_RESULT, 0x0
	vgoto_if 0x1, _0845E755
	vloadptr _0845E75D
	setmysteryeventstatus 0x2
	end

_0845E755:
	vloadptr _0845E771
	setmysteryeventstatus 0x3
	end

.ifdef ENGLISH
_0845E75D:
	.string "{STR_VAR_1} was received!$"
_0845E771:
	.string "There was no room to accept\n"
	.string "{STR_VAR_1}...$"
.else @ GERMAN
_0845E75D:
	.string "{STR_VAR_1} wurde übergeben.$"
_0845E771:
	.string "Es ist kein Platz für {STR_VAR_1}\n"
	.string "vorhanden...$"
.endif @ GERMAN

_0845E730End:
	.size _0845E730, _0845E730End - _0845E730
gUnknown_Debug_845E712End::

gUnknown_Debug_845E797::
	me_checkcompat gUnknown_Debug_845E797, unkConstant, unkConstant, 0x4, versionMask
	me_crc 0x0, gUnknown_Debug_845E7B5, gUnknown_Debug_845E7B5End
gUnknown_Debug_845E7B5::
	me_setrecordmixinggift 0x1, 0x3, ITEM_POTION
	me_end
gUnknown_Debug_845E7B5End:
	.size gUnknown_Debug_845E7B5, gUnknown_Debug_845E7B5End - gUnknown_Debug_845E7B5
gUnknown_Debug_845E797End::

.endif @ DEBUG
