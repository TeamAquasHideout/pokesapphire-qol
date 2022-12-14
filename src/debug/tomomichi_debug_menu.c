#if DEBUG
#include "global.h"
#include "ewram.h"
#include "string_util.h"
#include "palette.h"
#include "data2.h"
#include "event_data.h"
#include "constants/flags.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "overworld.h"
#include "script.h"
#include "menu.h"
#include "start_menu.h"
#include "main.h"
#include "contest_painting.h"
#include "sound.h"

// TRN: If anyone wants to translate the dummy options, they are welcome to :P

static u16 sPicTest_Species;
static u32 sPicTest_OTID;
static u32 sPicTest_Personality;
static u8 sPicTest_ContestType;
static u8 sPicTest_MuseumArtTitleType;
static u8 sPicTest_PreviewType;
static u8 sFlagAndVarTest_WhichSubmenu;
static u8 sPicTest_StringBuffer[13];
static u8 sTopMenuCursorPos;
static u8 sTrickRelatedMenuCursorPos;
static u8 sControlEventsCursorPos;
static u8 sControlFlagsCursorPos;
static u8 sControlWORKCursorPos;

static bool8 ArtMusGraphics(void);
static bool8 DummyMenuAction(void);
static bool8 ContestGraphics(void);
static bool8 ContestGraphics_Show(void);
static bool8 ControlEvents(void);
static bool8 ControlFlags(void);
static bool8 ControlWorks(void);
static bool8 MuseumGraphics_Show(void);
static bool8 PreviewData(void);
static bool8 TrickHouse(void);
static bool8 InitDebugWindow(void);
static bool8 TopMenu_HandleInput(void);
static bool8 ContestGraphics_HandleInput(void);
static bool8 ArtMusGraphics_HandleInput(void);
static bool8 PreviewData_HandleInput(void);
static bool8 TrickHouse_HandleInput(void);
static bool8 ControlEvents_HandleInput(void);
static bool8 ControlFlags_HandleInput(void);
static bool8 ControlWorks_HandleInput(void);
static bool8 ControlEvents_InitSubmenu1(void);
static bool8 ControlEvents_InitSubmenu2(void);
static bool8 ControlEvents_Events1_HandleInput(void);
static bool8 ControlEvents_Events2_HandleInput(void);
static bool8 CallScript_DoHallOfFame(void);
static bool8 CallScript_GiveCoinCaseIfNotAlreadyOwned(void);
static bool8 CallScript_SetOldaleStateAfterRoute103Rival(void);
static bool8 CallScript_OpenNewMauville(void);
static bool8 CallScript_GiveSSTicketAndDoHallOfFame(void);
static bool8 CallScript_GiveKyogreEgg(void);
static bool8 CallScript_GiveAllItems(void);
static bool8 CallScript_GiveAllDecorations(void);
static bool8 CallScript_GiveAllCoins(void);
static bool8 CallScript_OpenSootopolisGym(void);
static bool8 CallScript_SetMoneyTo0(void);
static bool8 CallScript_FillPartyWithBarboach(void);
static bool8 CallScript_FillPartyWithShroomish(void);
static bool8 CallScript_GiveBarboachEgg(void);
static bool8 CallScript_GiveShroomishEgg(void);
static bool8 debug_sub_808C280(void);
static bool8 debug_sub_808C2E4(void);
static bool8 ControlFlags_EventFlag_InitSubmenu(void);
static bool8 debug_sub_808C36C(void);
static bool8 debug_sub_808C3B0(void);
static bool8 debug_sub_808C408(void);
static bool8 debug_sub_808C460(void);
static bool8 debug_sub_808C4B8(void);
static bool8 debug_sub_808C510(void);
static bool8 debug_sub_808C568(void);
static bool8 debug_sub_808C5C0(void);
static bool8 debug_sub_808C618(void);
static bool8 debug_sub_808C670(void);
static bool8 debug_sub_808C6C8(void);
static void debug_sub_808C714(u8, u8);
static void debug_sub_808C764(u8);
static bool8 ControlFlags_VanishFlag_InitSubmenu(void);
static bool8 debug_sub_808C818(void);
static bool8 debug_sub_808C85C(void);
static bool8 debug_sub_808C8B4(void);
static bool8 debug_sub_808C90C(void);
static bool8 debug_sub_808C964(void);
static bool8 debug_sub_808C9BC(void);
static bool8 debug_sub_808CA14(void);
static bool8 debug_sub_808CA6C(void);
static bool8 debug_sub_808CAC4(void);
static bool8 debug_sub_808CB1C(void);
static bool8 debug_sub_808CB74(void);
static void debug_sub_808CBC0(u8, u8);
static void debug_sub_808CC10(u8);
static bool8 ControlFlags_TrainerFlag_InitSubmenu(void);
static bool8 debug_sub_808CCC4(void);
static bool8 debug_sub_808CD08(void);
static bool8 debug_sub_808CD60(void);
static bool8 debug_sub_808CDB8(void);
static bool8 debug_sub_808CE10(void);
static void debug_sub_808CE5C(u8, u8);
static void debug_sub_808CEAC(u8);
static bool8 ControlFlags_SysFlag_InitSubmenu(void);
static bool8 debug_sub_808CF60(void);
static bool8 debug_sub_808CFA4(void);
static bool8 debug_sub_808CFFC(void);
static bool8 debug_sub_808D054(void);
static bool8 debug_sub_808D0AC(void);
static bool8 debug_sub_808D104(void);
static bool8 debug_sub_808D15C(void);
static bool8 debug_sub_808D1B4(void);
static bool8 debug_sub_808D20C(void);
static bool8 debug_sub_808D264(void);
static bool8 debug_sub_808D2BC(void);
static void debug_sub_808D308(u8, u8);
static void debug_sub_808D358(u8);
static bool8 ControlFlags_FH_OBJ_InitSubmenu(void);
static bool8 ControlFlags_FH_OBJ_HandleInput(void);
static bool8 ControlFlags_FH_OBJ00_08_InitSubsubmenu(void);
static bool8 ControlFlags_FH_OBJ09_15_InitSubsubmenu(void);
static bool8 ControlFlags_FH_OBJ_Subsubmenu_HandleInput(void);
static void ControlFlags_FH_OBJ_FlagToggle(u8, u8);
static void ControlFlags_FH_OBJ_UpdateDisplay(u8);
static bool8 ControlFlags_FH_InitSubmenu(void);
static bool8 debug_sub_808D650(void);
static bool8 debug_sub_808D694(void);
static bool8 debug_sub_808D6EC(void);
static bool8 debug_sub_808D744(void);
static void debug_sub_808D790(u8, u8);
static void debug_sub_808D7E0(u8);
static bool8 ControlFlags_BallVanishFlag_InitSubmenu(void);
static bool8 debug_sub_808D894(void);
static bool8 debug_sub_808D8D8(void);
static bool8 debug_sub_808D930(void);
static void debug_sub_808D97C(u8, u8);
static void debug_sub_808D9CC(u8);
static bool8 ControlWorks_AnsWork_InitSubmenu(void);
static bool8 ControlWorks_AnsWork_HandleInput(void);
static void ControlWorks_AnsWork_PrintRESULT(void);
static void ControlWorks_AnsWork_AdjustRESULT(void);
static bool8 ControlWorks_SaveWork_InitSubmenu(void);
static bool8 ControlWorks_SaveWork_HandleInput(void);
static bool8 ControlWorks_SaveWork_Town_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_City_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_Route101To109_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_Route110To118_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_Route119To127_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_Route128To134_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_RoomTown_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_RoomCity_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_Dungeon_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWork_Subsubmenu_HandleInput(void);
static void debug_sub_808DF04(u8);
static void debug_sub_808DF64(u8, u8);
static bool8 ControlWorks_SaveWorkPart2_InitSubmenu(void);
static bool8 ControlWorks_SaveWorkPart2_HandleInput(void);
static bool8 ControlWorks_SaveWorkPart2_SP_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWorkPart2_RoomR110Part1TrickHouse_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWorkPart2_RoomR110Part2_InitSubsubmenu(void);
static bool8 ControlWorks_SaveWorkPart2_RoomLoad_InitSubsubmenu(void);
static bool8 debug_sub_808E1B4(void);
static bool8 debug_sub_808E20C(void);
static bool8 debug_sub_808E264(void);
static void debug_sub_808E2B0(u8);
static void debug_sub_808E310(u8, u8);
static bool8 ControlWorks_SysWork_InitSubmenu(void);
static bool8 debug_sub_808E3BC(void);
static bool8 debug_sub_808E400(void);
static bool8 debug_sub_808E458(void);
static bool8 debug_sub_808E4B0(void);
static bool8 debug_sub_808E508(void);
static bool8 debug_sub_808E560(void);
static bool8 debug_sub_808E5B8(void);
static void debug_sub_808E604(u8, u8);
static void debug_sub_808E660(u8);
static bool8 ControlWorks_LocalWork_InitSubmenu(void);
static bool8 debug_sub_808E710(void);
static bool8 debug_sub_808E754(void);
static bool8 debug_sub_808E7AC(void);
static bool8 debug_sub_808E804(void);
static void debug_sub_808E850(u8, u8);
static void debug_sub_808E8AC(u8);
static bool8 ControlWorks_ObjWork_InitSubmenu(void);
static bool8 debug_sub_808E95C(void);
static bool8 debug_sub_808E9A0(void);
static bool8 debug_sub_808E9F8(void);
static bool8 debug_sub_808EA50(void);
static void debug_sub_808EA9C(u8);
static void debug_sub_808EAFC(u8, u8);
static bool8 TrickRelated_Level_InitSubmenu(void);
static bool8 TrickRelated_TrickMaster_InitSubmenu(void);
static bool8 debug_sub_808EC10(void);
static bool8 debug_sub_808EC5C(void);
static bool8 PreviewGraphics_Show(void);
static bool8 debug_sub_808ECD0(void);
static void PicTest_SelectPokemon(void);
static void PicTest_SelectPersonality(void);
static void ContestPicTest_SelectContestType(void);
static void MuseumArtPicTest_SelectTitleType(void);
static void PreviewPicTest_SelectType(void);
static void PicTest_Redraw(u8 a0);
static void PrepareDebugOverlayBeforeShowingContestPainting(u8 a0);
static void PrintBool(u8, u8, bool8);
static void PrintUnsignedShort(u8, u8, u16);

extern const u8 DebugScript_081C1CFE[];
extern const u8 DebugScript_081C1D07[];
extern const u8 DebugScript_081C1D1E[];
extern const u8 DebugScript_081C1D24[];
extern const u8 DebugScript_081C1D2A[];
extern const u8 DebugScript_081C1D35[];
extern const u8 DebugScript_081C1D46[];
extern const u8 DebugScript_081C221F[];
extern const u8 DebugScript_081C23E2[];
extern const u8 DebugScript_081C23E6[];
extern const u8 DebugScript_081C23F6[];
extern const u8 DebugScript_081C2482[];
extern const u8 DebugScript_081C23FD[];
extern const u8 DebugScript_081C2518[];
extern const u8 DebugScript_081C2507[];

static const u8 sString_ContestGraphics[] = _("Contest graphics");
static const u8 sString_ArtMuseumGraphics[] = _("Art Mus. graphics");
static const u8 sString_PreviewData[] = _("Preview data");
static const u8 sString_TrickHouse[] = _("TRICK HOUSE");
static const u8 sString_ControlEvents[] = _("Control events");
static const u8 sString_ControlFlags[] = _("Control flags");
static const u8 sString_ControlWORK[] = _("Control WORK");

static const struct MenuAction sMenuActions_TopMenu[] = {
    {sString_ContestGraphics, ContestGraphics},
    {sString_ArtMuseumGraphics, ArtMusGraphics},
    {sString_PreviewData, PreviewData},
    {sString_TrickHouse, TrickHouse},
    {sString_ControlEvents, ControlEvents},
    {sString_ControlFlags, ControlFlags},
    {sString_ControlWORK, ControlWorks},
};

#if (ENGLISH && REVISION == 0)
static const u8 sString_ContestMenuTitle[] = _("???????????????");

static const u8 sString_Contest_PokemonNo[] = _("????????????????????????");
static const u8 sString_Contest_Personality[] = _("?????????????????????");
static const u8 sString_Contest_Type[] = _("???????????????????????????");
static const u8 sString_Contest_PokeArt[] = _("????????????");
#else
static const u8 sString_ContestMenuTitle[] = _("Contest");

static const u8 sString_Contest_PokemonNo[] = _("Pok??mon No.");
static const u8 sString_Contest_Personality[] = _("ID rnd. digit");
static const u8 sString_Contest_Type[] = _("Contest Type");
static const u8 sString_Contest_PokeArt[] = _("Pok?? Art");
#endif

static const struct MenuAction sMenuActions_ContestPicTest[] = {
    {sString_Contest_PokemonNo, DummyMenuAction},
    {sString_Contest_Personality, DummyMenuAction},
    {sString_Contest_Type, DummyMenuAction},
    {sString_Contest_PokeArt, ContestGraphics_Show}
};

#if (ENGLISH && REVISION == 0)
static const u8 sString_Contest_ArtMuseumTitle[] = _("??????????????????");

static const u8 sString_Contest_ArtMuseum_PokemonNo[] = _("????????????????????????");
static const u8 sString_Contest_ArtMuseum_Personality[] = _("?????????????????????");
static const u8 sString_Contest_ArtMuseum_Type[] = _("????????????????????????");
static const u8 sString_Contest_ArtMuseum_PokeArt[] = _("????????????");
#else
static const u8 sString_Contest_ArtMuseumTitle[] = _("Art Mus.");

static const u8 sString_Contest_ArtMuseum_PokemonNo[] = _("Pok??mon No.");
static const u8 sString_Contest_ArtMuseum_Personality[] = _("ID rnd. digit");
static const u8 sString_Contest_ArtMuseum_Type[] = _("Title Type");
static const u8 sString_Contest_ArtMuseum_PokeArt[] = _("Pok?? Art");
#endif

static const struct MenuAction sMenuActions_ArtMuseumPicTest[] = {
    {sString_Contest_ArtMuseum_PokemonNo, DummyMenuAction},
    {sString_Contest_ArtMuseum_Personality, DummyMenuAction},
    {sString_Contest_ArtMuseum_Type, DummyMenuAction},
    {sString_Contest_ArtMuseum_PokeArt, MuseumGraphics_Show}
};

#if (ENGLISH && REVISION == 0)
static const u8 sString_Contest_PreviewTitle[] = _("???????????????");

static const u8 sString_Contest_Preview_PokemonNo[] = _("????????????????????????");
static const u8 sString_Contest_Preview_Personality[] = _("?????????????????????");
static const u8 sString_Contest_Preview_Type[] = _("????????????");
static const u8 sString_Contest_Preview_PokeArt[] = _("????????????");
#else
static const u8 sString_Contest_PreviewTitle[] = _("Preview");

static const u8 sString_Contest_Preview_PokemonNo[] = _("Pok??mon No.");
static const u8 sString_Contest_Preview_Personality[] = _("ID rnd. digit");
static const u8 sString_Contest_Preview_Type[] = _("Type");
static const u8 sString_Contest_Preview_PokeArt[] = _("Pok?? Art");
#endif

static const struct MenuAction sMenuActions_PreviewPicTest[] = {
    {sString_Contest_Preview_PokemonNo, DummyMenuAction},
    {sString_Contest_Preview_Personality, DummyMenuAction},
    {sString_Contest_Preview_Type, DummyMenuAction},
    {sString_Contest_Preview_PokeArt, PreviewGraphics_Show}
};

#if (ENGLISH && REVISION == 0)
static const u8 sString_TrickRelated[] = _("????????????????????????");
#else
static const u8 sString_TrickRelated[] = _("Trick related");
#endif

static const u8 sString_TrickRelated_Level[] = _("Level");

#if (ENGLISH && REVISION == 0)
static const u8 sString_TrickRelated_TrickMaster[] = _("MASTER");
#else
static const u8 sString_TrickRelated_TrickMaster[] = _("Trick Master");
#endif

static const struct MenuAction sMenuActions_TrickRelated[] = {
    {sString_TrickRelated_Level, TrickRelated_Level_InitSubmenu},
    {sString_TrickRelated_TrickMaster, TrickRelated_TrickMaster_InitSubmenu}
};

static const u8 sString_Event1[] = DTR("?????????1", "PART 1");
static const u8 sString_Event2[] = DTR("?????????2", "PART 2");

static const struct MenuAction sMenuActions_ControlEvents[] = {
    {sString_Event1, ControlEvents_InitSubmenu1},
    {sString_Event2, ControlEvents_InitSubmenu2}
};

static const u8 sString_EventFlag[] = DTR("????????????FLAG", "EVENT FLAG");
static const u8 sString_VanishFlag[] = DTR("????????????FLAG", "VANISH FLAG");
static const u8 sString_TrainerFlag[] = DTR("???????????????FLAG", "TRAINER FLAG");
static const u8 sString_SysFlag[] = _("SYSFLAG");
static const u8 sString_BallVanishFlag[] = DTR("BALL????????????FLAG", "VANISH FLAG");
static const u8 sString_FH[] = _("FH");
static const u8 sString_FH_OBJ[] = _("FH-OBJ");

static const struct MenuAction sMenuActions_ControlFlags[] = {
    {sString_EventFlag, ControlFlags_EventFlag_InitSubmenu},
    {sString_VanishFlag, ControlFlags_VanishFlag_InitSubmenu},
    {sString_TrainerFlag, ControlFlags_TrainerFlag_InitSubmenu},
    {sString_SysFlag, ControlFlags_SysFlag_InitSubmenu},
    {sString_BallVanishFlag, ControlFlags_BallVanishFlag_InitSubmenu},
    {sString_FH, ControlFlags_FH_InitSubmenu},
    {sString_FH_OBJ, ControlFlags_FH_OBJ_InitSubmenu}
};

static const u8 sString_SaveWork[] = _("SAVEWORK");
static const u8 sString_SysWork[] = _("SYSWORK");
static const u8 sString_LocalWork[] = _("LOCALWORK");
static const u8 sString_ObjWork[] = _("OBJWORK");
static const u8 sString_AnsWork[] = _("ANSWORK");
static const u8 sString_SaveWorkPart2[] = DTR("SAVEWORK ?????????2", "SAVEWORK PART 2");

static const struct MenuAction sMenuActions_ControlWorks[] = {
    {sString_SaveWork, ControlWorks_SaveWork_InitSubmenu},
    {sString_SysWork, ControlWorks_SysWork_InitSubmenu},
    {sString_LocalWork, ControlWorks_LocalWork_InitSubmenu},
    {sString_ObjWork, ControlWorks_ObjWork_InitSubmenu},
    {sString_AnsWork, ControlWorks_AnsWork_InitSubmenu},
    {sString_SaveWorkPart2, ControlWorks_SaveWorkPart2_InitSubmenu}
};

static const u8 sString_Clear_go[] = DTR("????????????", "POSTGAME");
static const u8 sString_Coin_kounyuuka[] = DTR("?????????????????????????????????", ",Get COIN CASE");
static const u8 sString_Oldale_supporter_set[] = DTR("?????????????????????????????????", "OLDALE POST RIVAL");
static const u8 sString_New_Mauville_open[] = DTR("?????????????????????OPEN", "Open NEW MAUVILLE");
static const u8 sString_Renrakusen_ni_noreru[] = DTR("??????????????????????????????", "Get S.S. TICKET");
static const u8 sString_Egg_tsuika[] = DTR("??????????????????", "Get KYOGRE EGG");
static const u8 sString_Item_ippai[] = DTR("????????????????????????", "Max Items");
static const u8 sString_Gezzu_ippai[] = DTR("?????????????????????", "Max Decorations");
static const u8 sString_Coin_ippai[] = DTR("COIN????????????", "Max COINS");

static const struct MenuAction sMenuActions_ControlEvents_Events1[] = {
    {sString_Clear_go, CallScript_DoHallOfFame},
    {sString_Coin_kounyuuka, CallScript_GiveCoinCaseIfNotAlreadyOwned},
    {sString_Oldale_supporter_set, CallScript_SetOldaleStateAfterRoute103Rival},
    {sString_New_Mauville_open, CallScript_OpenNewMauville},
    {sString_Renrakusen_ni_noreru, CallScript_GiveSSTicketAndDoHallOfFame},
    {sString_Egg_tsuika, CallScript_GiveKyogreEgg},
    {sString_Item_ippai, CallScript_GiveAllItems},
    {sString_Gezzu_ippai, CallScript_GiveAllDecorations},
    {sString_Coin_ippai, CallScript_GiveAllCoins}
};

// Note: JP text says Dewford Gym for some reason.
static const u8 sString_SootpolisGymOpen[] = DTR("????????????OPEN", "Open SOOTOPOLIS GYM");
static const u8 sString_MoneyTo0[] = DTR("????????????0???", "Set money to 0");
static const u8 sString_BarboachFull[] = DTR("??????????????????FULL", "Full BARBOACH PARTY");
static const u8 sString_ShroomishFull[] = DTR("???????????????FULL", "Full SHROOMISH PARTY");
static const u8 sString_BarboachEgg[] = DTR("???????????????????????????", "Get BARBOACH EGG");
static const u8 sString_ShroomishEgg[] = DTR("????????????????????????", "Get SHROOMISH EGG");

static const struct MenuAction sMenuActions_ControlEvents_Events2[] = {
    {sString_SootpolisGymOpen, CallScript_OpenSootopolisGym},
    {sString_MoneyTo0, CallScript_SetMoneyTo0},
    {sString_BarboachFull, CallScript_FillPartyWithBarboach},
    {sString_ShroomishFull, CallScript_FillPartyWithShroomish},
    {sString_BarboachEgg, CallScript_GiveBarboachEgg},
    {sString_ShroomishEgg, CallScript_GiveShroomishEgg}
};

static const u8 sString_Answork_Mikansei[] = DTR("ANSWORK??????????????????", "ANSWORK Incomplete");

static const struct MenuAction sMenuActions_ControlEvents_AnsWork[] = {
    {sString_Answork_Mikansei, DummyMenuAction}
};

static const u8 sString_FH_OBJ00_08[] = _("FH???OBJ00???08");
static const u8 sString_FH_OBJ09_15[] = _("FH???OBJ09???15");

static const struct MenuAction sMenuActions_ControlFlags_FH_OBJ[] = {
    {sString_FH_OBJ00_08, ControlFlags_FH_OBJ00_08_InitSubsubmenu},
    {sString_FH_OBJ09_15, ControlFlags_FH_OBJ09_15_InitSubsubmenu}
};

static const u8 sString_FH_OBJ00[] = _("FH???OBJ00");
static const u8 sString_FH_OBJ01[] = _("FH???OBJ01");
static const u8 sString_FH_OBJ02[] = _("FH???OBJ02");
static const u8 sString_FH_OBJ03[] = _("FH???OBJ03");
static const u8 sString_FH_OBJ04[] = _("FH???OBJ04");
static const u8 sString_FH_OBJ05[] = _("FH???OBJ05");
static const u8 sString_FH_OBJ06[] = _("FH???OBJ06");
static const u8 sString_FH_OBJ07[] = _("FH???OBJ07");
static const u8 sString_FH_OBJ08[] = _("FH???OBJ08");

static const struct MenuAction sMenuActions_ControlFlags_FH_OBJ00_08[] = {
    {sString_FH_OBJ00, DummyMenuAction},
    {sString_FH_OBJ01, DummyMenuAction},
    {sString_FH_OBJ02, DummyMenuAction},
    {sString_FH_OBJ03, DummyMenuAction},
    {sString_FH_OBJ04, DummyMenuAction},
    {sString_FH_OBJ05, DummyMenuAction},
    {sString_FH_OBJ06, DummyMenuAction},
    {sString_FH_OBJ07, DummyMenuAction},
    {sString_FH_OBJ08, DummyMenuAction}
};

static const u8 sString_FH_OBJ09[] = _("FH-OBJ09");
static const u8 sString_FH_OBJ10[] = _("FH-OBJ10");
static const u8 sString_FH_OBJ11[] = _("FH-OBJ11");
static const u8 sString_FH_OBJ12[] = _("FH-OBJ12");
static const u8 sString_FH_OBJ13[] = _("FH-OBJ13");
static const u8 sString_FH_OBJ14[] = _("FH-OBJ14");
static const u8 sString_FH_OBJ15[] = _("FH-OBJ15");
static const u8 sString_Blank_083C1147[] = _("");
static const u8 sString_Blank_083C1148[] = _("");

static const struct MenuAction sMenuActions_ControlFlags_FH_OBJ09_15[] = {
    {sString_FH_OBJ09, DummyMenuAction},
    {sString_FH_OBJ10, DummyMenuAction},
    {sString_FH_OBJ11, DummyMenuAction},
    {sString_FH_OBJ12, DummyMenuAction},
    {sString_FH_OBJ13, DummyMenuAction},
    {sString_FH_OBJ14, DummyMenuAction},
    {sString_FH_OBJ15, DummyMenuAction},
    {sString_Blank_083C1147, DummyMenuAction},
    {sString_Blank_083C1148, DummyMenuAction}
};

static const u8 sControlFlags_FH_OBJ_CountsArray[] = {9, 7};

static const u16 sControlFlags_FH_OBJ_FlagsArrays[][9] = {
    {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19},
    {0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20}
};

static const u8 gUnknown_Debug_083C11BA[] = _("FH-00-08");
static const u8 gUnknown_Debug_083C11C3[] = _("FH-09-15");

static const struct MenuAction gUnknown_Debug_083C11CC[] = {
    {gUnknown_Debug_083C11BA, debug_sub_808D694},
    {gUnknown_Debug_083C11C3, debug_sub_808D6EC}
};

static const u8 gUnknown_Debug_083C11DC[] = _("FH-00");
static const u8 gUnknown_Debug_083C11E2[] = _("FH-01");
static const u8 gUnknown_Debug_083C11E8[] = _("FH-02");
static const u8 gUnknown_Debug_083C11EE[] = _("FH-03");
static const u8 gUnknown_Debug_083C11F4[] = _("FH-04");
static const u8 gUnknown_Debug_083C11FA[] = _("FH-05");
static const u8 gUnknown_Debug_083C1200[] = _("FH-06");
static const u8 gUnknown_Debug_083C1206[] = _("FH-07");
static const u8 gUnknown_Debug_083C120C[] = _("FH-08");

static const struct MenuAction gUnknown_Debug_083C1212[] = {
    {gUnknown_Debug_083C11DC, DummyMenuAction},
    {gUnknown_Debug_083C11E2, DummyMenuAction},
    {gUnknown_Debug_083C11E8, DummyMenuAction},
    {gUnknown_Debug_083C11EE, DummyMenuAction},
    {gUnknown_Debug_083C11F4, DummyMenuAction},
    {gUnknown_Debug_083C11FA, DummyMenuAction},
    {gUnknown_Debug_083C1200, DummyMenuAction},
    {gUnknown_Debug_083C1206, DummyMenuAction},
    {gUnknown_Debug_083C120C, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C125C[] = _("FH???09");
static const u8 gUnknown_Debug_083C1262[] = _("FH???10");
static const u8 gUnknown_Debug_083C1268[] = _("FH???11");
static const u8 gUnknown_Debug_083C126E[] = _("FH???12");
static const u8 gUnknown_Debug_083C1274[] = _("FH???13");
static const u8 gUnknown_Debug_083C127A[] = _("FH???14");
static const u8 gUnknown_Debug_083C1280[] = _("FH???15");
static const u8 gUnknown_Debug_083C1286[] = _("");
static const u8 gUnknown_Debug_083C1287[] = _("");

static const struct MenuAction gUnknown_Debug_083C1288[] = {
    {gUnknown_Debug_083C125C, DummyMenuAction},
    {gUnknown_Debug_083C1262, DummyMenuAction},
    {gUnknown_Debug_083C1268, DummyMenuAction},
    {gUnknown_Debug_083C126E, DummyMenuAction},
    {gUnknown_Debug_083C1274, DummyMenuAction},
    {gUnknown_Debug_083C127A, DummyMenuAction},
    {gUnknown_Debug_083C1280, DummyMenuAction},
    {gUnknown_Debug_083C1286, DummyMenuAction},
    {gUnknown_Debug_083C1287, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C12D0[] = {9, 7};

static const u16 gUnknown_Debug_083C12D2[][9] = {
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09},
    {0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10}
};

static const u8 gUnknown_Debug_083C12F6[] = DTR("BATCH", "BADGE");
static const u8 gUnknown_Debug_083C12FC[] = DTR("????????????????????????", "Towns arrived");
static const u8 gUnknown_Debug_083C1305[] = DTR("????????????????????????", "Cities arrived");
static const u8 gUnknown_Debug_083C130E[] = _("GET");
static const u8 gUnknown_Debug_083C1312[] = DTR("?????????1", "Other 1");
static const u8 gUnknown_Debug_083C1317[] = DTR("?????????2", "Other 2");
static const u8 gUnknown_Debug_083C131C[] = DTR("?????????3", "Other 3");
static const u8 gUnknown_Debug_083C1321[] = DTR("?????????4", "Other 4");
static const u8 gUnknown_Debug_083C1326[] = DTR("???????????????????????????", "Others arrived");

static const struct MenuAction gUnknown_Debug_083C1330[] = {
    {gUnknown_Debug_083C12F6, debug_sub_808CFA4},
    {gUnknown_Debug_083C12FC, debug_sub_808CFFC},
    {gUnknown_Debug_083C1305, debug_sub_808D054},
    {gUnknown_Debug_083C130E, debug_sub_808D0AC},
    {gUnknown_Debug_083C1312, debug_sub_808D104},
    {gUnknown_Debug_083C1317, debug_sub_808D15C},
    {gUnknown_Debug_083C131C, debug_sub_808D1B4},
    {gUnknown_Debug_083C1321, debug_sub_808D20C},
    {gUnknown_Debug_083C1326, debug_sub_808D264}
};

static const u8 gUnknown_Debug_083C1378[] = _("BATCH01???GET");
static const u8 gUnknown_Debug_083C1384[] = _("BATCH02???GET");
static const u8 gUnknown_Debug_083C1390[] = _("BATCH03???GET");
static const u8 gUnknown_Debug_083C139C[] = _("BATCH04???GET");
static const u8 gUnknown_Debug_083C13A8[] = _("BATCH05???GET");
static const u8 gUnknown_Debug_083C13B4[] = _("BATCH06???GET");
static const u8 gUnknown_Debug_083C13C0[] = _("BATCH07???GET");
static const u8 gUnknown_Debug_083C13CC[] = _("BATCH08???GET");

static const struct MenuAction gUnknown_Debug_083C13D8[] = {
    {gUnknown_Debug_083C1378, DummyMenuAction},
    {gUnknown_Debug_083C1384, DummyMenuAction},
    {gUnknown_Debug_083C1390, DummyMenuAction},
    {gUnknown_Debug_083C139C, DummyMenuAction},
    {gUnknown_Debug_083C13A8, DummyMenuAction},
    {gUnknown_Debug_083C13B4, DummyMenuAction},
    {gUnknown_Debug_083C13C0, DummyMenuAction},
    {gUnknown_Debug_083C13CC, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1418[] = _("T101ARRIVE");
static const u8 gUnknown_Debug_083C1423[] = _("T102ARRIVE");
static const u8 gUnknown_Debug_083C142E[] = _("T103ARRIVE");
static const u8 gUnknown_Debug_083C1439[] = _("T104ARRIVE");
static const u8 gUnknown_Debug_083C1444[] = _("T105ARRIVE");
static const u8 gUnknown_Debug_083C144F[] = _("T106ARRIVE");
static const u8 gUnknown_Debug_083C145A[] = _("T107ARRIVE");

static const struct MenuAction gUnknown_Debug_083C1465[] = {
    {gUnknown_Debug_083C1418, DummyMenuAction},
    {gUnknown_Debug_083C1423, DummyMenuAction},
    {gUnknown_Debug_083C142E, DummyMenuAction},
    {gUnknown_Debug_083C1439, DummyMenuAction},
    {gUnknown_Debug_083C1444, DummyMenuAction},
    {gUnknown_Debug_083C144F, DummyMenuAction},
    {gUnknown_Debug_083C145A, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C14A0[] = _("C101ARRIVE");
static const u8 gUnknown_Debug_083C14AB[] = _("C102ARRIVE");
static const u8 gUnknown_Debug_083C14B6[] = _("C103ARRIVE");
static const u8 gUnknown_Debug_083C14C1[] = _("C104ARRIVE");
static const u8 gUnknown_Debug_083C14CC[] = _("C105ARRIVE");
static const u8 gUnknown_Debug_083C14D7[] = _("C106ARRIVE");
static const u8 gUnknown_Debug_083C14E2[] = _("C107ARRIVE");
static const u8 gUnknown_Debug_083C14ED[] = _("C108ARRIVE");
static const u8 gUnknown_Debug_083C14F8[] = _("C109ARRIVE");

static const struct MenuAction gUnknown_Debug_083C1503[] = {
    {gUnknown_Debug_083C14A0, DummyMenuAction},
    {gUnknown_Debug_083C14AB, DummyMenuAction},
    {gUnknown_Debug_083C14B6, DummyMenuAction},
    {gUnknown_Debug_083C14C1, DummyMenuAction},
    {gUnknown_Debug_083C14CC, DummyMenuAction},
    {gUnknown_Debug_083C14D7, DummyMenuAction},
    {gUnknown_Debug_083C14E2, DummyMenuAction},
    {gUnknown_Debug_083C14ED, DummyMenuAction},
    {gUnknown_Debug_083C14F8, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C154C[] = _("SYS???POKEMON???GET");
static const u8 gUnknown_Debug_083C155C[] = _("SYS???ZUKAN???GET");
static const u8 gUnknown_Debug_083C156A[] = _("SYS???POKEGEAR???GET");
static const u8 gUnknown_Debug_083C157B[] = _("SYS???RIBBON???GET");

static const struct MenuAction gUnknown_Debug_083C158A[] = {
    {gUnknown_Debug_083C154C, DummyMenuAction},
    {gUnknown_Debug_083C155C, DummyMenuAction},
    {gUnknown_Debug_083C156A, DummyMenuAction},
    {gUnknown_Debug_083C157B, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C15AC[] = _("SYS???GAME???CLEAR");
static const u8 gUnknown_Debug_083C15BB[] = _("SYS???KAIWA???USED");
static const u8 gUnknown_Debug_083C15CA[] = _("SYS???NOW???OYAJI???MEET");
static const u8 gUnknown_Debug_083C15DD[] = _("SYS???USE???WAZA???FLASH");
static const u8 gUnknown_Debug_083C15F0[] = _("SYS???USE???WAZA???KAIRIKI");
static const u8 gUnknown_Debug_083C1605[] = _("SYS???WEATHER???CTRL");
static const u8 gUnknown_Debug_083C1616[] = _("SYS???CYCLING???ROAD");
static const u8 gUnknown_Debug_083C1627[] = _("SYS???SAFARI???MODE");
static const u8 gUnknown_Debug_083C1637[] = _("SYS???CRUISE???MODE");

static const struct MenuAction gUnknown_Debug_083C1647[] = {
    {gUnknown_Debug_083C15AC, DummyMenuAction},
    {gUnknown_Debug_083C15BB, DummyMenuAction},
    {gUnknown_Debug_083C15CA, DummyMenuAction},
    {gUnknown_Debug_083C15DD, DummyMenuAction},
    {gUnknown_Debug_083C15F0, DummyMenuAction},
    {gUnknown_Debug_083C1605, DummyMenuAction},
    {gUnknown_Debug_083C1616, DummyMenuAction},
    {gUnknown_Debug_083C1627, DummyMenuAction},
    {gUnknown_Debug_083C1637, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1690[] = _("SYS???TV???HOME");
static const u8 gUnknown_Debug_083C169C[] = _("SYS???TV???WATCH");
static const u8 gUnknown_Debug_083C16A9[] = _("SYS???TVSTART");
static const u8 gUnknown_Debug_083C16B5[] = _("SYS???POPWORD???INPUT");
static const u8 gUnknown_Debug_083C16C7[] = _("SYS???MIX???RECORD");
static const u8 gUnknown_Debug_083C16D6[] = _("SYS???CLOCK???SET");
static const u8 gUnknown_Debug_083C16E4[] = _("SYS???CAVE???SHIP");
static const u8 gUnknown_Debug_083C16F2[] = _("SYS???CAVE???WONDER");
static const u8 gUnknown_Debug_083C1702[] = _("SYS???CAVE???BATTLE");

static const struct MenuAction gUnknown_Debug_083C1712[] = {
    {gUnknown_Debug_083C1690, DummyMenuAction},
    {gUnknown_Debug_083C169C, DummyMenuAction},
    {gUnknown_Debug_083C16A9, DummyMenuAction},
    {gUnknown_Debug_083C16B5, DummyMenuAction},
    {gUnknown_Debug_083C16C7, DummyMenuAction},
    {gUnknown_Debug_083C16D6, DummyMenuAction},
    {gUnknown_Debug_083C16E4, DummyMenuAction},
    {gUnknown_Debug_083C16F2, DummyMenuAction},
    {gUnknown_Debug_083C1702, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C175C[] = _("SYS???SPECIAL???ZUKAN");
static const u8 gUnknown_Debug_083C176E[] = _("SYS???ASASE???TIDE");
static const u8 gUnknown_Debug_083C177D[] = _("SYS???RIBBON???GET");
static const u8 gUnknown_Debug_083C178C[] = _("SYS???PASO???MAYUMI");
static const u8 gUnknown_Debug_083C179C[] = _("SYS???EXDATA???ENABLE");
static const u8 gUnknown_Debug_083C17AE[] = _("SYS???TENJI???ANAWOHORU");
static const u8 gUnknown_Debug_083C17C2[] = _("SYS???TENJI???KAIRIKI");
static const u8 gUnknown_Debug_083C17D4[] = _("SYS???TENJI???WAIT");
static const u8 gUnknown_Debug_083C17E3[] = _("SYS???TENJI???SORAWOTOBU");

static const struct MenuAction gUnknown_Debug_083C17F8[] = {
    {gUnknown_Debug_083C175C, DummyMenuAction},
    {gUnknown_Debug_083C176E, DummyMenuAction},
    {gUnknown_Debug_083C177D, DummyMenuAction},
    {gUnknown_Debug_083C178C, DummyMenuAction},
    {gUnknown_Debug_083C179C, DummyMenuAction},
    {gUnknown_Debug_083C17AE, DummyMenuAction},
    {gUnknown_Debug_083C17C2, DummyMenuAction},
    {gUnknown_Debug_083C17D4, DummyMenuAction},
    {gUnknown_Debug_083C17E3, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1840[] = _("SYS???ENC???UP???ITEM");
static const u8 gUnknown_Debug_083C1850[] = _("SYS???ENE???DOWN???ITEM");
static const u8 gUnknown_Debug_083C1862[] = _("SYS???KOKORO???EVENT");
static const u8 gUnknown_Debug_083C1873[] = _("SYS???MOVE???POKE???NEWS");
static const u8 gUnknown_Debug_083C1886[] = _("SYS???ASASE???ITEM");
static const u8 gUnknown_Debug_083C1895[] = _("SYS???B???DASH");
static const u8 gUnknown_Debug_083C18A0[] = _("SYS???CTRL???OBJ???DELETE");
static const u8 gUnknown_Debug_083C18B4[] = _("");
static const u8 gUnknown_Debug_083C18B5[] = _("");

static const struct MenuAction gUnknown_Debug_083C18B8[] = {
    {gUnknown_Debug_083C1840, DummyMenuAction},
    {gUnknown_Debug_083C1850, DummyMenuAction},
    {gUnknown_Debug_083C1862, DummyMenuAction},
    {gUnknown_Debug_083C1873, DummyMenuAction},
    {gUnknown_Debug_083C1886, DummyMenuAction},
    {gUnknown_Debug_083C1895, DummyMenuAction},
    {gUnknown_Debug_083C18A0, DummyMenuAction},
    {gUnknown_Debug_083C18B4, DummyMenuAction},
    {gUnknown_Debug_083C18B5, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1900[] = _("SYS???ARRIVE???SUBMARINECAVE");
static const u8 gUnknown_Debug_083C1919[] = _("SYS???ARRIVE???BATTLETOWER");
static const u8 gUnknown_Debug_083C1930[] = _("SYS???ARRIVE???ISLAND");
static const u8 gUnknown_Debug_083C1942[] = _("SYS???ARRIVE???LEAGUE");
static const u8 gUnknown_Debug_083C1954[] = _("SYS???ARRIVE???SORANOHASHIRA");
static const u8 gUnknown_Debug_083C196D[] = _("");
static const u8 gUnknown_Debug_083C196E[] = _("");
static const u8 gUnknown_Debug_083C196F[] = _("");
static const u8 gUnknown_Debug_083C1970[] = _("");

static const struct MenuAction gDebug_0x83C1974[] = {
    {gUnknown_Debug_083C1900, DummyMenuAction},
    {gUnknown_Debug_083C1919, DummyMenuAction},
    {gUnknown_Debug_083C1930, DummyMenuAction},
    {gUnknown_Debug_083C1942, DummyMenuAction},
    {gUnknown_Debug_083C1954, DummyMenuAction},
    {gUnknown_Debug_083C196D, DummyMenuAction},
    {gUnknown_Debug_083C196E, DummyMenuAction},
    {gUnknown_Debug_083C196F, DummyMenuAction},
    {gUnknown_Debug_083C1970, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C19BC[] = {8, 7, 9, 4, 9, 9, 9, 7, 5};

static const u16 gUnknown_Debug_083C19C6[][9] = {
    {FLAG_BADGE01_GET, FLAG_BADGE02_GET, FLAG_BADGE03_GET, FLAG_BADGE04_GET, FLAG_BADGE05_GET, FLAG_BADGE06_GET, FLAG_BADGE07_GET, FLAG_BADGE08_GET},
    {FLAG_VISITED_LITTLEROOT_TOWN, FLAG_VISITED_OLDALE_TOWN, FLAG_VISITED_DEWFORD_TOWN, FLAG_VISITED_LAVARIDGE_TOWN, FLAG_VISITED_FALLARBOR_TOWN, FLAG_VISITED_VERDANTURF_TOWN, FLAG_VISITED_PACIFIDLOG_TOWN},
    {FLAG_VISITED_PETALBURG_CITY, FLAG_VISITED_SLATEPORT_CITY, FLAG_VISITED_MAUVILLE_CITY, FLAG_VISITED_RUSTBORO_CITY, FLAG_VISITED_FORTREE_CITY, FLAG_VISITED_LILYCOVE_CITY, FLAG_VISITED_MOSSDEEP_CITY, FLAG_VISITED_SOOTOPOLIS_CITY, FLAG_VISITED_EVER_GRANDE_CITY},
    {FLAG_SYS_POKEMON_GET, FLAG_SYS_POKEDEX_GET, FLAG_SYS_POKENAV_GET, FLAG_SYS_RIBBON_GET},
    {FLAG_SYS_GAME_CLEAR, FLAG_SYS_CHAT_USED, FLAG_SYS_HIPSTER_MEET, FLAG_SYS_USE_FLASH, FLAG_SYS_USE_STRENGTH, FLAG_SYS_WEATHER_CTRL, FLAG_SYS_CYCLING_ROAD, FLAG_SYS_SAFARI_MODE, FLAG_SYS_CRUISE_MODE},
    {FLAG_SYS_TV_HOME, FLAG_SYS_TV_WATCH, FLAG_SYS_TV_START, FLAG_SYS_POPWORD_INPUT, FLAG_SYS_MIX_RECORD, FLAG_SYS_CLOCK_SET, FLAG_SYS_CAVE_SHIP, FLAG_SYS_CAVE_WONDER, FLAG_SYS_CAVE_BATTLE},
    {FLAG_SYS_NATIONAL_DEX, FLAG_SYS_SHOAL_TIDE, FLAG_SYS_RIBBON_GET, FLAG_SYS_PC_LANETTE, FLAG_SYS_EXDATA_ENABLE, FLAG_SYS_BRAILLE_DIG, FLAG_SYS_BRAILLE_STRENGTH, FLAG_SYS_BRAILLE_WAIT, FLAG_SYS_BRAILLE_FLY},
    {FLAG_SYS_ENC_UP_ITEM, FLAG_SYS_ENC_DOWN_ITEM, FLAG_SYS_HAS_EON_TICKET, FLAG_SYS_TV_LATI, FLAG_SYS_SHOAL_ITEM, FLAG_SYS_B_DASH, FLAG_SYS_CTRL_OBJ_DELETE},
    {FLAG_LANDMARK_SEAFLOOR_CAVERN, FLAG_LANDMARK_BATTLE_TOWER, FLAG_LANDMARK_SOUTHERN_ISLAND, FLAG_SYS_POKEMON_LEAGUE_FLY, FLAG_LANDMARK_SKY_PILLAR}
};

static const u8 gDebug_0x83C1A68[] = DTR("FV???BALL????????????1", "FV-BALL PART 1");

static const struct MenuAction gUnknown_Debug_083C1A78[] = {
	{gDebug_0x83C1A68, debug_sub_808D8D8}
};

static const u8 gUnknown_Debug_083C1A80[] = _("FV???BALL1???78");
static const u8 gUnknown_Debug_083C1A8C[] = _("FV???BALL1???133");

static const struct MenuAction gUnknown_Debug_083C1A9C[] = {
	{gUnknown_Debug_083C1A80, DummyMenuAction},
	{gUnknown_Debug_083C1A8C, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1AAC[] = {2};

static const u16 gUnknown_Debug_083C1AAE[][9] = {
    {FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOMS_2, FLAG_ITEM_MOSSDEEP_STEVENS_HOUSE_HM08}
};

static const u8 gUnknown_Debug_083C1AC0[] = DTR("??????????????????", "GYM LEADER");
static const u8 gUnknown_Debug_083C1AC7[] = DTR("???????????????", "ELITE FOUR");
static const u8 gUnknown_Debug_083C1ACD[] = DTR("?????????/Champ?????????", "WALLY/VICTORY ROAD");

static const struct MenuAction gUnknown_Debug_083C1ADC[] = {
	{gUnknown_Debug_083C1AC0, debug_sub_808CD08},
	{gUnknown_Debug_083C1AC7, debug_sub_808CD60},
	{gUnknown_Debug_083C1ACD, debug_sub_808CDB8}
};

static const u8 gUnknown_Debug_083C1AF4[] = _("FT???GYM???01???LEADER");
static const u8 gUnknown_Debug_083C1B05[] = _("FT???GYM???02???LEADER");
static const u8 gUnknown_Debug_083C1B16[] = _("FT???GYM???03???LEADER");
static const u8 gUnknown_Debug_083C1B27[] = _("FT???GYM???04???LEADER");
static const u8 gUnknown_Debug_083C1B38[] = _("FT???GYM???05???LEADER");
static const u8 gUnknown_Debug_083C1B49[] = _("FT???GYM???06???LEADER");
static const u8 gUnknown_Debug_083C1B5A[] = _("FT???GYM???07???LEADER");
static const u8 gUnknown_Debug_083C1B6B[] = _("FT???GYM???08???LEADER");

static const struct MenuAction gUnknown_Debug_083C1B7C[] = {
	{gUnknown_Debug_083C1AF4, DummyMenuAction},
	{gUnknown_Debug_083C1B05, DummyMenuAction},
	{gUnknown_Debug_083C1B16, DummyMenuAction},
	{gUnknown_Debug_083C1B27, DummyMenuAction},
	{gUnknown_Debug_083C1B38, DummyMenuAction},
	{gUnknown_Debug_083C1B49, DummyMenuAction},
	{gUnknown_Debug_083C1B5A, DummyMenuAction},
	{gUnknown_Debug_083C1B6B, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1BBC[] = _("FT???SHITEN???01");
static const u8 gUnknown_Debug_083C1BC9[] = _("FT???SHITEN???02");
static const u8 gUnknown_Debug_083C1BD6[] = _("FT???SHITEN???03");
static const u8 gUnknown_Debug_083C1BE3[] = _("FT???SHITEN???04");

static const struct MenuAction gUnknown_Debug_083C1BF0[] = {
	{gUnknown_Debug_083C1BBC, DummyMenuAction},
	{gUnknown_Debug_083C1BC9, DummyMenuAction},
	{gUnknown_Debug_083C1BD6, DummyMenuAction},
	{gUnknown_Debug_083C1BE3, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1C10[] = _("FT???MITSURU???01???CAVE???D1301");

static const struct MenuAction gUnknown_Debug_083C1C2C[] = {
	{gUnknown_Debug_083C1C10, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1C34[] = {8, 4, 1};
static const u16 gUnknown_Debug_083C1C38[][9] = {
    {FLAG_DEFEATED_RUSTBORO_GYM, FLAG_DEFEATED_DEWFORD_GYM, FLAG_DEFEATED_MAUVILLE_GYM, FLAG_DEFEATED_LAVARIDGE_GYM, FLAG_DEFEATED_PETALBURG_GYM, FLAG_DEFEATED_FORTREE_GYM, FLAG_DEFEATED_MOSSDEEP_GYM, FLAG_DEFEATED_SOOTOPOLIS_GYM},
    {FLAG_DEFEATED_ELITE_4_SYDNEY, FLAG_DEFEATED_ELITE_4_PHOEBE, FLAG_DEFEATED_ELITE_4_GLACIA, FLAG_DEFEATED_ELITE_4_DRAKE},
    {0x04E1}
};

static const u8 gUnknown_Debug_083C1C6E[] = DTR("120/119??????????????????????????????", "ROUTE 120/119 KECLEON");
static const u8 gUnknown_Debug_083C1C80[] = DTR("?????????1???/???SUPPORTM/W", "Other 1/SUPPORT/M/W");
static const u8 gUnknown_Debug_083C1C92[] = DTR("ODAMAKI/FIGHTER1", "BIRCH/FIGHTER1");
static const u8 gUnknown_Debug_083C1CA3[] = DTR("MITSURU/TENKI", "WALLY/WEATHER");
static const u8 gUnknown_Debug_083C1CB1[] = DTR("?????????2???/DAIGO", "Other 2/STEVEN");
static const u8 gUnknown_Debug_083C1CBD[] = _("POKE/POKEMON");
static const u8 gUnknown_Debug_083C1CCA[] = _("MAMA/SUPPORT02");
static const u8 gUnknown_Debug_083C1CD9[] = DTR("HAGI", "Mr. BRINEY");
static const u8 gUnknown_Debug_083C1CDE[] = _("SUPPORT01");

static const struct MenuAction gUnknown_Debug_083C1CE8[] = {
	{gUnknown_Debug_083C1C6E, debug_sub_808C85C},
	{gUnknown_Debug_083C1C80, debug_sub_808C8B4},
	{gUnknown_Debug_083C1C92, debug_sub_808C90C},
	{gUnknown_Debug_083C1CA3, debug_sub_808C964},
	{gUnknown_Debug_083C1CB1, debug_sub_808C9BC},
	{gUnknown_Debug_083C1CBD, debug_sub_808CA14},
	{gUnknown_Debug_083C1CCA, debug_sub_808CA6C},
	{gUnknown_Debug_083C1CD9, debug_sub_808CAC4},
	{gUnknown_Debug_083C1CDE, debug_sub_808CB1C}
};

static const u8 gUnknown_Debug_083C1D30[] = _("FV???KAKUREONB???01???FIELD???R120");
static const u8 gUnknown_Debug_083C1D4B[] = _("FV???KAKURE???01???FIELD???R120");
static const u8 gUnknown_Debug_083C1D63[] = _("FV???KAKURE???02???FIELD???R120");
static const u8 gUnknown_Debug_083C1D7B[] = _("FV???KAKURE???03???FIELD???R120");
static const u8 gUnknown_Debug_083C1D93[] = _("FV???KAKURE???04???FIELD???R120");
static const u8 gUnknown_Debug_083C1DAB[] = _("FV???KAKURE???05???FIELD???R120");
static const u8 gUnknown_Debug_083C1DC3[] = _("FV???KAKURE???06???FIELD???R120");
static const u8 gUnknown_Debug_083C1DDB[] = _("FV???KAKURE???01???FIELD???R119");
static const u8 gUnknown_Debug_083C1DF3[] = _("FV???KAKURE???02???FIELD???R119");

static const struct MenuAction gUnknown_Debug_083C1E0C[] = {
	{gUnknown_Debug_083C1D30, DummyMenuAction},
	{gUnknown_Debug_083C1D4B, DummyMenuAction},
	{gUnknown_Debug_083C1D63, DummyMenuAction},
	{gUnknown_Debug_083C1D7B, DummyMenuAction},
	{gUnknown_Debug_083C1D93, DummyMenuAction},
	{gUnknown_Debug_083C1DAB, DummyMenuAction},
	{gUnknown_Debug_083C1DC3, DummyMenuAction},
	{gUnknown_Debug_083C1DDB, DummyMenuAction},
	{gUnknown_Debug_083C1DF3, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1E54[] = _("FV???BALL???01???C107???R0501");
static const u8 gUnknown_Debug_083C1E6A[] = _("FV???WORKERM1???04???FIELD???C104");
static const u8 gUnknown_Debug_083C1E84[] = _("FV???SUBMARINE???06???CAVE???D1101");
static const u8 gUnknown_Debug_083C1E9F[] = _("FV???GUEST???ALL???C106???R0102");
static const u8 gUnknown_Debug_083C1EB7[] = _("FV???HORIDASI???01???C106???R1106");
static const u8 gUnknown_Debug_083C1ED1[] = _("FV???MIDDLEM1???01???R110???R0101");
static const u8 gUnknown_Debug_083C1EEB[] = _("FV???FUNE???01???C102???R0601");
static const u8 gUnknown_Debug_083C1F01[] = _("FV???SUPPORTW???01???T101???R0202");
static const u8 gUnknown_Debug_083C1F1B[] = _("FV???SUPPORTM???01???T101???R0102");

static const struct MenuAction gUnknown_Debug_083C1F38[] = {
	{gUnknown_Debug_083C1E54, DummyMenuAction},
	{gUnknown_Debug_083C1E6A, DummyMenuAction},
	{gUnknown_Debug_083C1E84, DummyMenuAction},
	{gUnknown_Debug_083C1E9F, DummyMenuAction},
	{gUnknown_Debug_083C1EB7, DummyMenuAction},
	{gUnknown_Debug_083C1ED1, DummyMenuAction},
	{gUnknown_Debug_083C1EEB, DummyMenuAction},
	{gUnknown_Debug_083C1F01, DummyMenuAction},
	{gUnknown_Debug_083C1F1B, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C1F80[] = _("FV???ODAMAKI???01???FIELD???R101");
static const u8 gUnknown_Debug_083C1F99[] = _("FV???ODAMAKI???01???T101???R0301");
static const u8 gUnknown_Debug_083C1FB2[] = _("FV???ODAMAKI???HYOKA???T101???R0301");
static const u8 gUnknown_Debug_083C1FCE[] = _("FV???ODAMAKI???HYOKA???FIELD???R101");
static const u8 gUnknown_Debug_083C1FEA[] = _("FV???ODAMAKI???HYOKA???FIELD???R103");
static const u8 gUnknown_Debug_083C2006[] = _("FV???ODAMAKI???01???C109???R0105");
static const u8 gUnknown_Debug_083C201F[] = _("FV???FIGHTER???01???CAVE???D0201");
static const u8 gUnknown_Debug_083C2038[] = _("FV???FIGHTER???01???T106???R0201");
static const u8 gUnknown_Debug_083C2051[] = _("FV???FIGHTER???01???FIELD???R116");

static const struct MenuAction gUnknown_Debug_083C206C[] = {
	{gUnknown_Debug_083C1F80, DummyMenuAction},
	{gUnknown_Debug_083C1F99, DummyMenuAction},
	{gUnknown_Debug_083C1FB2, DummyMenuAction},
	{gUnknown_Debug_083C1FCE, DummyMenuAction},
	{gUnknown_Debug_083C1FEA, DummyMenuAction},
	{gUnknown_Debug_083C2006, DummyMenuAction},
	{gUnknown_Debug_083C201F, DummyMenuAction},
	{gUnknown_Debug_083C2038, DummyMenuAction},
	{gUnknown_Debug_083C2051, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C20B4[] = _("FV???MITSURU???01???FIELD???C101");
static const u8 gUnknown_Debug_083C20CD[] = _("FV???MITSURU???02???CAVE???D1301");
static const u8 gUnknown_Debug_083C20E6[] = _("FV???MITSURU???01???FIELD???C103");
static const u8 gUnknown_Debug_083C20FF[] = _("FV???MITSURU???01???T106???R0201");
static const u8 gUnknown_Debug_083C2118[] = _("FV???MITSURU???01???CAVE???D1301");
static const u8 gUnknown_Debug_083C2131[] = _("FV???MITSURU???01???C101???R0201");
static const u8 gUnknown_Debug_083C214A[] = _("FV???MITSURU???01???FIELD???R102");
static const u8 gUnknown_Debug_083C2163[] = _("FV???TENKI???01???R119???R101");
static const u8 gUnknown_Debug_083C2179[] = _("FV???TENKI???01???R119???R102");

static const struct MenuAction gUnknown_Debug_083C2190[] = {
	{gUnknown_Debug_083C20B4, DummyMenuAction},
	{gUnknown_Debug_083C20CD, DummyMenuAction},
	{gUnknown_Debug_083C20E6, DummyMenuAction},
	{gUnknown_Debug_083C20FF, DummyMenuAction},
	{gUnknown_Debug_083C2118, DummyMenuAction},
	{gUnknown_Debug_083C2131, DummyMenuAction},
	{gUnknown_Debug_083C214A, DummyMenuAction},
	{gUnknown_Debug_083C2163, DummyMenuAction},
	{gUnknown_Debug_083C2179, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C21D8[] = _("FV???DAIGO???01???CAVE???D0504");
static const u8 gUnknown_Debug_083C21EF[] = _("FV???DAIGO???01???FIELD???R128");
static const u8 gUnknown_Debug_083C2206[] = _("FV???DAIGO???01???FIELD???R118");
static const u8 gUnknown_Debug_083C221D[] = _("FV???DAIGO???01???C107???R0501");
static const u8 gUnknown_Debug_083C2234[] = _("FV???DAIGO???01???FIELD???R120");
static const u8 gUnknown_Debug_083C224B[] = _("FV???DAIGO???01???FIELD???R108");

static const struct MenuAction gUnknown_Debug_083C2264[] = {
	{gUnknown_Debug_083C21D8, DummyMenuAction},
	{gUnknown_Debug_083C21EF, DummyMenuAction},
	{gUnknown_Debug_083C2206, DummyMenuAction},
	{gUnknown_Debug_083C221D, DummyMenuAction},
	{gUnknown_Debug_083C2234, DummyMenuAction},
	{gUnknown_Debug_083C224B, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2294[] = _("FV???POKE1???02???CAVE???D1111");
static const u8 gUnknown_Debug_083C22AB[] = _("FV???POKE1???01???CAVE???D0601");
static const u8 gUnknown_Debug_083C22C2[] = _("FV???POKE1???02???CAVE???D0601");
static const u8 gUnknown_Debug_083C22D9[] = _("FV???POKE1???01???FIELD???R101");
static const u8 gUnknown_Debug_083C22F0[] = _("FV???POKE1???01???OPENING???ROOM01");
static const u8 gUnknown_Debug_083C230B[] = _("FV???POKE1???02???OPENING???ROOM01");
static const u8 gUnknown_Debug_083C2326[] = _("FV???POKE1???01???CAVE???D2308");
static const u8 gUnknown_Debug_083C233D[] = _("FV???POKEMON???01???CAVE???D0201");
static const u8 gUnknown_Debug_083C2356[] = _("FV???POKEMON???01???R104???R0101");

static const struct MenuAction gUnknown_Debug_083C2370[] = {
	{gUnknown_Debug_083C2294, DummyMenuAction},
	{gUnknown_Debug_083C22AB, DummyMenuAction},
	{gUnknown_Debug_083C22C2, DummyMenuAction},
	{gUnknown_Debug_083C22D9, DummyMenuAction},
	{gUnknown_Debug_083C22F0, DummyMenuAction},
	{gUnknown_Debug_083C230B, DummyMenuAction},
	{gUnknown_Debug_083C2326, DummyMenuAction},
	{gUnknown_Debug_083C233D, DummyMenuAction},
	{gUnknown_Debug_083C2356, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C23B8[] = _("FV???MAMA???01???FIELD???T101");
static const u8 gUnknown_Debug_083C23CE[] = _("FV???MAMA???01???OPENING???ROOM02");
static const u8 gUnknown_Debug_083C23E8[] = _("FV???MAMA???01???T101???R0101");
static const u8 gUnknown_Debug_083C23FE[] = _("FV???MAMA???01???T101???R0201");
static const u8 gUnknown_Debug_083C2414[] = _("FV???MAMA???02???T101???R0101");
static const u8 gUnknown_Debug_083C242A[] = _("FV???MAMA???02???T101???R0201");
static const u8 gUnknown_Debug_083C2440[] = _("FV???SUPPORT???02???FIELD???R110");
static const u8 gUnknown_Debug_083C2459[] = _("FV???SUPPORT???02???FIELD???R119");
static const u8 gUnknown_Debug_083C2472[] = _("FV???SUPPORT???02???FIELD???T104");

static const struct MenuAction gUnknown_Debug_083C248C[] = {
	{gUnknown_Debug_083C23B8, DummyMenuAction},
	{gUnknown_Debug_083C23CE, DummyMenuAction},
	{gUnknown_Debug_083C23E8, DummyMenuAction},
	{gUnknown_Debug_083C23FE, DummyMenuAction},
	{gUnknown_Debug_083C2414, DummyMenuAction},
	{gUnknown_Debug_083C242A, DummyMenuAction},
	{gUnknown_Debug_083C2440, DummyMenuAction},
	{gUnknown_Debug_083C2459, DummyMenuAction},
	{gUnknown_Debug_083C2472, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C24D4[] = _("FV???HAGI???01???FIELD???R104");
static const u8 gUnknown_Debug_083C24EA[] = _("FV???HAGI???01???R104???R0101");
static const u8 gUnknown_Debug_083C2500[] = _("FV???HAGI???01???FIELD???T103");
static const u8 gUnknown_Debug_083C2516[] = _("FV???HAGI???01???FIELD???R109");
static const u8 gUnknown_Debug_083C252C[] = _("FV???HAGI???01???C102???R0601");
static const u8 gUnknown_Debug_083C2542[] = _("FV???HAGI???01???C102???R0101");
static const u8 gUnknown_Debug_083C2558[] = _("FV???HAGI???01???CAVE???D0201");
static const u8 gUnknown_Debug_083C256E[] = _("FV???HAGI???01???FIELD???R116");
static const u8 gUnknown_Debug_083C2584[] = _("FV???HAGI???01???SP???SHIP01");

static const struct MenuAction gUnknown_Debug_083C259C[] = {
	{gUnknown_Debug_083C24D4, DummyMenuAction},
	{gUnknown_Debug_083C24EA, DummyMenuAction},
	{gUnknown_Debug_083C2500, DummyMenuAction},
	{gUnknown_Debug_083C2516, DummyMenuAction},
	{gUnknown_Debug_083C252C, DummyMenuAction},
	{gUnknown_Debug_083C2542, DummyMenuAction},
	{gUnknown_Debug_083C2558, DummyMenuAction},
	{gUnknown_Debug_083C256E, DummyMenuAction},
	{gUnknown_Debug_083C2584, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C25E4[] = _("FV???SUPPORT???01???T101???R0301");
static const u8 gUnknown_Debug_083C25FD[] = _("FV???SUPPORT???01???C109???R0105");
static const u8 gUnknown_Debug_083C2616[] = _("FV???SUPPORT???01???FIELD???C104");
static const u8 gUnknown_Debug_083C262F[] = _("FV???SUPPORT???01???FIELD???C106");
static const u8 gUnknown_Debug_083C2648[] = _("FV???SUPPORT???01???FIELD???R103");
static const u8 gUnknown_Debug_083C2661[] = _("FV???SUPPORT???01???FIELD???R110");
static const u8 gUnknown_Debug_083C267A[] = _("FV???SUPPORT???01???FIELD???R119");
static const u8 gUnknown_Debug_083C2693[] = _("FV???SUPPORT???01???FIELD???T104");
static const u8 gUnknown_Debug_083C26AC[] = _("FV???SUPPORT???01???FIELD???T102");

static const struct MenuAction gUnknown_Debug_083C26C8[] = {
	{gUnknown_Debug_083C25E4, DummyMenuAction},
	{gUnknown_Debug_083C25FD, DummyMenuAction},
	{gUnknown_Debug_083C2616, DummyMenuAction},
	{gUnknown_Debug_083C262F, DummyMenuAction},
	{gUnknown_Debug_083C2648, DummyMenuAction},
	{gUnknown_Debug_083C2661, DummyMenuAction},
	{gUnknown_Debug_083C267A, DummyMenuAction},
	{gUnknown_Debug_083C2693, DummyMenuAction},
	{gUnknown_Debug_083C26AC, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2710[] = {9, 9, 9, 9, 6, 9, 9, 9, 9};

static const u16 gUnknown_Debug_083C271A[][9] = {
    {FLAG_HIDE_KECLEON_ROUTE120_2, FLAG_HIDE_KECLEON_ROUTE120_1, FLAG_HIDE_KECLEON_ROUTE120_3, FLAG_HIDE_KECLEON_ROUTE120_4, FLAG_HIDE_KECLEON_ROUTE120_5, FLAG_HIDE_KECLEON_ROUTE120_6, FLAG_HIDE_KECLEON_ROUTE120_7, FLAG_HIDE_KECLEON_ROUTE119_1, FLAG_HIDE_KECLEON_ROUTE119_2},
    {FLAG_HIDE_BELDUM_BALL_STEVENS_HOUSE, FLAG_HIDE_DEVON_RUSTBORO, FLAG_HIDE_UNDERWATER_SUBMARINE_INTERACTION, FLAG_HIDE_LILYCOVE_MOTEL_PEOPLE, FLAG_HIDE_ROOFTOP_LADY_LILYCOVE_MART, FLAG_HIDE_TRICKMASTER_ENTRANCE, 0x352, FLAG_HIDE_MAY_UPSTAIRS, FLAG_HIDE_BRENDAN_UPSTAIRS},
    {FLAG_HIDE_BIRCH_BATTLE_POOCHYENA, FLAG_HIDE_BIRCH_IN_LAB, FLAG_UNKNOWN_BIRCH_380, FLAG_HIDE_BIRCH_ROUTE101, FLAG_HIDE_BIRCH_ROUTE103, FLAG_HIDE_BIRCH_CHAMPIONS_ROOM, FLAG_HIDE_BOYFRIEND_RUSTURF_TUNNEL, FLAG_HIDE_BOYFRIEND_WANDAS_HOUSE, FLAG_HIDE_TUNNER_DIGGER_ROUTE116},
    {FLAG_HIDE_WALLY_PETALBURG, FLAG_HIDE_WALLY_DEFEATED_VICTORY_ROAD, FLAG_HIDE_WALLY_MAUVILLE, FLAG_HIDE_WALLY_WANDAS_HOUSE, FLAG_HIDE_WALLY_BATTLE_VICTORY_ROAD, FLAG_HIDE_WALLY_PETALBURG_GYM, FLAG_UNKNOWN_363, FLAG_HIDE_WEATHER_INSTITUTE_WORKERS_1F, FLAG_HIDE_WEATHER_INSTITUTE_WORKERS_2F},
    {FLAG_HIDE_STEVEN_GRANITE_CAVE, FLAG_HIDE_STEVEN_ROUTE128, FLAG_HIDE_STEVEN_ROUTE118, FLAG_HIDE_STEVEN_STEVENS_HOUSE, FLAG_HIDE_STEVEN_ROUTE120, FLAG_HIDE_STEVEN_SOOTOPOLIS},
    {FLAG_HIDE_SLEEPING_MON_SEAFLOOR_CAVERN, FLAG_UNKNOWN_2E1, FLAG_UNKNOWN_2EC, FLAG_HIDE_POOCHYENA_ROUTE101, FLAG_HIDE_MACHOKE_MOVER_1, FLAG_HIDE_MACHOKE_MOVER_2, 0x305, FLAG_HIDE_PEEKO_RUSTURF_TUNNEL, FLAG_HIDE_PEEKO_BRINEY_HOUSE},
    {FLAG_HIDE_MOM_LITTLEROOT, FLAG_HIDE_MOM_UPSTAIRS, FLAG_HIDE_BRENDAN_MOM_DOWNSTAIRS, FLAG_HIDE_MAY_MOM_DOWNSTAIRS, FLAG_UNKNOWN_30E, FLAG_UNKNOWN_30F, FLAG_HIDE_RIVAL_ON_BIKE_ROUTE110, FLAG_HIDE_RIVAL_ROUTE119_ON_BIKE, FLAG_HIDE_RIVAL_LAVARIDGE_2},
    {FLAG_HIDE_MR_BRINEY_ROUTE104, FLAG_HIDE_MR_BRINEY_ROUTE104_HOUSE, FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN, FLAG_HIDE_MR_BRINEY_ROUTE109, FLAG_GROUDON_POSTGAME, FLAG_HIDE_BRINEY_SLATEPORT_SHIPYARD, FLAG_HIDE_BRINEY_RUSTURF_TUNNEL, FLAG_HIDE_BRINEY_ROUTE116, FLAG_HIDE_BRINEY_AND_PEEKO_SS_TIDAL},
    {FLAG_HIDE_RIVAL_BIRCH_LAB, FLAG_HIDE_RIVAL_CHAMPIONS_ROOM, FLAG_HIDE_RIVAL_RUSTBORO, FLAG_HIDE_RIVAL_LILYCOVE_MART, FLAG_HIDE_RIVAL_ROUTE103, FLAG_HIDE_RIVAL_ROUTE110, FLAG_HIDE_RIVAL_ROUTE119, FLAG_HIDE_RIVAL_LAVARIDGE_1, FLAG_HIDE_RIVAL_OLDALE_TOWN}
};

static const u8 gUnknown_Debug_083C27BC[] = DTR("FE???????????????/?????????????????????", "Field HMs/DEVON-related");
static const u8 gUnknown_Debug_083C27CC[] = DTR("FE????????????????????????PART1", "Field Key Items Part 1");
static const u8 gUnknown_Debug_083C27DC[] = DTR("?????????1", "Other 1");
static const u8 gUnknown_Debug_083C27E1[] = DTR("MITSURU/DOOR", "WALLY/Door");
static const u8 gUnknown_Debug_083C27EE[] = DTR("?????????????????????10???????????????/GYM07",
                                                "TRICK HOUSE 10 Arrows/GYM 7");
static const u8 gUnknown_Debug_083C2803[] = DTR("SUPPORT/?????????4", "Support/Other 4");
static const u8 gUnknown_Debug_083C2810[] = DTR("DAISUKI/?????????5", "FAN CLUB/Other 5");
static const u8 gUnknown_Debug_083C281D[] = DTR("?????????2", "Other 2");
static const u8 gUnknown_Debug_083C2822[] = DTR("?????????6", "Other 6");

static const struct MenuAction gUnknown_Debug_083C2828[] = {
	{gUnknown_Debug_083C27BC, debug_sub_808C3B0},
	{gUnknown_Debug_083C27CC, debug_sub_808C408},
	{gUnknown_Debug_083C27DC, debug_sub_808C460},
	{gUnknown_Debug_083C27E1, debug_sub_808C4B8},
	{gUnknown_Debug_083C27EE, debug_sub_808C510},
	{gUnknown_Debug_083C2803, debug_sub_808C568},
	{gUnknown_Debug_083C2810, debug_sub_808C5C0},
	{gUnknown_Debug_083C281D, debug_sub_808C618},
	{gUnknown_Debug_083C2822, debug_sub_808C670}
};

static const u8 gUnknown_Debug_083C2870[] = _("FE???HWAZA01???GET");
static const u8 gUnknown_Debug_083C287F[] = _("FE???HWAZA02???01???FIELDR119");
static const u8 gUnknown_Debug_083C2897[] = _("FE???HWAZA03???GET");
static const u8 gUnknown_Debug_083C28A6[] = _("FE???HWAZA04???01???T106???R0201");
static const u8 gUnknown_Debug_083C28BF[] = _("FE???HWAZA05???01???CAVE???D0502");
static const u8 gUnknown_Debug_083C28D8[] = _("FE???HWAZA04???01???C103???R0301");
static const u8 gUnknown_Debug_083C28F1[] = _("FE???DEBON???NIMOTSU???RETURN");
static const u8 gUnknown_Debug_083C2909[] = _("FE???DEBON???01???FIELD???C104");
static const u8 gUnknown_Debug_083C2920[] = _("FE???DEBON???02???FIELD???C104");

static const struct MenuAction gUnknown_Debug_083C2938[] = {
    {gUnknown_Debug_083C2870, DummyMenuAction},
    {gUnknown_Debug_083C287F, DummyMenuAction},
    {gUnknown_Debug_083C2897, DummyMenuAction},
    {gUnknown_Debug_083C28A6, DummyMenuAction},
    {gUnknown_Debug_083C28BF, DummyMenuAction},
    {gUnknown_Debug_083C28D8, DummyMenuAction},
    {gUnknown_Debug_083C28F1, DummyMenuAction},
    {gUnknown_Debug_083C2909, DummyMenuAction},
    {gUnknown_Debug_083C2920, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2980[] = _("FE???CYCLE???01???P01???P01???C103???R0201");
static const u8 gUnknown_Debug_083C299F[] = _("FE???SCOOP???01???P01???FIELD???R115");
static const u8 gUnknown_Debug_083C29BA[] = _("FE???ROPE???01???P01???FIELD???R114");
static const u8 gUnknown_Debug_083C29D4[] = _("FE???KAMA???01???P01???FIELD???R119");
static const u8 gUnknown_Debug_083C29EE[] = _("FE???ZYOURO???GET");
static const u8 gUnknown_Debug_083C29FC[] = _("FE???CUBECASE???GET");
static const u8 gUnknown_Debug_083C2A0C[] = _("FE???BORONOTURIZAO???GET");
static const u8 gUnknown_Debug_083C2A21[] = _("FE???IITURIZAO???GET");
static const u8 gUnknown_Debug_083C2A32[] = _("FE???SUGOITURIZAO???GET");

static const struct MenuAction gUnknown_Debug_083C2A48[] = {
    {gUnknown_Debug_083C2980, DummyMenuAction},
    {gUnknown_Debug_083C299F, DummyMenuAction},
    {gUnknown_Debug_083C29BA, DummyMenuAction},
    {gUnknown_Debug_083C29D4, DummyMenuAction},
    {gUnknown_Debug_083C29EE, DummyMenuAction},
    {gUnknown_Debug_083C29FC, DummyMenuAction},
    {gUnknown_Debug_083C2A0C, DummyMenuAction},
    {gUnknown_Debug_083C2A21, DummyMenuAction},
    {gUnknown_Debug_083C2A32, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2A90[] = _("FE???BOSS???01???CAVE???D0701");
static const u8 gUnknown_Debug_083C2AA6[] = _("FE???TANTIKI???RETURN");
static const u8 gUnknown_Debug_083C2AB8[] = _("FE???POKE1???01???CAVE???D1111");
static const u8 gUnknown_Debug_083C2ACF[] = _("FE???POKE1???01???CAVE???D1206");
static const u8 gUnknown_Debug_083C2AE6[] = _("FE???SHOP???01???C104???FS01");
static const u8 gUnknown_Debug_083C2AFB[] = _("FE???HUNENOTIKETT???GET");
static const u8 gUnknown_Debug_083C2B0F[] = _("FE???KAKURE???01???FIELD???C105");
static const u8 gUnknown_Debug_083C2B27[] = _("FE???KASEKI???RETURN");
static const u8 gUnknown_Debug_083C2B38[] = _("FE???WIN???01???SP???SHIP01");

static const struct MenuAction gUnknown_Debug_083C2B4C[] = {
    {gUnknown_Debug_083C2A90, DummyMenuAction},
    {gUnknown_Debug_083C2AA6, DummyMenuAction},
    {gUnknown_Debug_083C2AB8, DummyMenuAction},
    {gUnknown_Debug_083C2ACF, DummyMenuAction},
    {gUnknown_Debug_083C2AE6, DummyMenuAction},
    {gUnknown_Debug_083C2AFB, DummyMenuAction},
    {gUnknown_Debug_083C2B0F, DummyMenuAction},
    {gUnknown_Debug_083C2B27, DummyMenuAction},
    {gUnknown_Debug_083C2B38, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2B94[] = _("FE???MITSURU???01???T106???R0201");
static const u8 gUnknown_Debug_083C2BAD[] = _("FE???MITSURU???01???CAVE???D1301");
static const u8 gUnknown_Debug_083C2BC6[] = _("FE???MITSURU???02???FIELD???C103");
static const u8 gUnknown_Debug_083C2BDF[] = _("FE???MITSURU???02???T106???R0201");
static const u8 gUnknown_Debug_083C2BF8[] = _("FE???MITSURU???01???FIELD???C103");
static const u8 gUnknown_Debug_083C2C11[] = _("FE???DOOR???OPEN???01???CAVE???D1712");
static const u8 gUnknown_Debug_083C2C2C[] = _("FE???DOOR???OPEN???02???CAVE???D1712");
static const u8 gUnknown_Debug_083C2C47[] = _("FE???DOOR???OPEN???04???CAVE???D1712");
static const u8 gUnknown_Debug_083C2C62[] = _("FE???DOOR???OPEN???06???CAVE???D1712");

static const struct MenuAction gUnknown_Debug_083C2C80[] = {
    {gUnknown_Debug_083C2B94, DummyMenuAction},
    {gUnknown_Debug_083C2BAD, DummyMenuAction},
    {gUnknown_Debug_083C2BC6, DummyMenuAction},
    {gUnknown_Debug_083C2BDF, DummyMenuAction},
    {gUnknown_Debug_083C2BF8, DummyMenuAction},
    {gUnknown_Debug_083C2C11, DummyMenuAction},
    {gUnknown_Debug_083C2C2C, DummyMenuAction},
    {gUnknown_Debug_083C2C47, DummyMenuAction},
    {gUnknown_Debug_083C2C62, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2CC8[] = _("FE???KARAKURI10???SWITCH???01");
static const u8 gUnknown_Debug_083C2CE0[] = _("FE???KARAKURI10???SWITCH???02");
static const u8 gUnknown_Debug_083C2CF8[] = _("FE???KARAKURI10???SWITCH???03");
static const u8 gUnknown_Debug_083C2D10[] = _("FE???KARAKURI10???SWITCH???04");
static const u8 gUnknown_Debug_083C2D28[] = _("FE???KARAKURI10???SWITCH???05");
static const u8 gUnknown_Debug_083C2D40[] = _("FE???GYM07???SWITCH???01");
static const u8 gUnknown_Debug_083C2D53[] = _("FE???GYM07???SWITCH???02");
static const u8 gUnknown_Debug_083C2D66[] = _("FE???GYM07???SWITCH???03");
static const u8 gUnknown_Debug_083C2D79[] = _("FE???GYM07???SWITCH???04");

static const struct MenuAction gUnknown_Debug_083C2D8C[] = {
    {gUnknown_Debug_083C2CC8, DummyMenuAction},
    {gUnknown_Debug_083C2CE0, DummyMenuAction},
    {gUnknown_Debug_083C2CF8, DummyMenuAction},
    {gUnknown_Debug_083C2D10, DummyMenuAction},
    {gUnknown_Debug_083C2D28, DummyMenuAction},
    {gUnknown_Debug_083C2D40, DummyMenuAction},
    {gUnknown_Debug_083C2D53, DummyMenuAction},
    {gUnknown_Debug_083C2D66, DummyMenuAction},
    {gUnknown_Debug_083C2D79, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2DD4[] = _("FE???SUPPORT???01???FIELD???R103");
static const u8 gUnknown_Debug_083C2DED[] = _("FE???SUPPORT???01???FIELD???C106");
static const u8 gUnknown_Debug_083C2E06[] = _("FE???SUPPORT???01???FIELD???R104");
static const u8 gUnknown_Debug_083C2E1F[] = _("FE???SUPPORT???02???FIELD???C106");
static const u8 gUnknown_Debug_083C2E38[] = _("FE???SUPPORT???01???T101???R0202");
static const u8 gUnknown_Debug_083C2E51[] = _("FE???MAMA???01???P01???T101???R0101");
static const u8 gUnknown_Debug_083C2E6B[] = _("FE???CLOCK???SET");
static const u8 gUnknown_Debug_083C2E78[] = _("FE???ODAMAKI???01???P01???T101???R03");
static const u8 gUnknown_Debug_083C2E93[] = _("FE???PAPA???01???P01???C101???R0201");

static const struct MenuAction gUnknown_Debug_083C2EB0[] = {
    {gUnknown_Debug_083C2DD4, DummyMenuAction},
    {gUnknown_Debug_083C2DED, DummyMenuAction},
    {gUnknown_Debug_083C2E06, DummyMenuAction},
    {gUnknown_Debug_083C2E1F, DummyMenuAction},
    {gUnknown_Debug_083C2E38, DummyMenuAction},
    {gUnknown_Debug_083C2E51, DummyMenuAction},
    {gUnknown_Debug_083C2E6B, DummyMenuAction},
    {gUnknown_Debug_083C2E78, DummyMenuAction},
    {gUnknown_Debug_083C2E93, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C2EF8[] = _("FE???DAISUKI???GOODS???FLAG01");
static const u8 gUnknown_Debug_083C2F10[] = _("FE???DAISUKI???GOODS???FLAG02");
static const u8 gUnknown_Debug_083C2F28[] = _("FE???DAISUKI???GOODS???FLAG03");
static const u8 gUnknown_Debug_083C2F40[] = _("FE???DAISUKI???GOODS???FLAG04");
static const u8 gUnknown_Debug_083C2F58[] = _("FE???DAISUKI???GOODS???FLAG05");
static const u8 gUnknown_Debug_083C2F70[] = _("FE???BASHA???01???P01???FIELD???C101???");
static const u8 gUnknown_Debug_083C2F8C[] = _("FE???BASHA???01???P02???FIELD???C101???");
static const u8 gUnknown_Debug_083C2FA8[] = _("FE???BALL???01???P01???SP???CONTEST");
static const u8 gUnknown_Debug_083C2FC2[] = _("FE???WOMAN2???01???P01???T101???R0201");

static const struct MenuAction gUnknown_Debug_083C2FE0[] = {
    {gUnknown_Debug_083C2EF8, DummyMenuAction},
    {gUnknown_Debug_083C2F10, DummyMenuAction},
    {gUnknown_Debug_083C2F28, DummyMenuAction},
    {gUnknown_Debug_083C2F40, DummyMenuAction},
    {gUnknown_Debug_083C2F58, DummyMenuAction},
    {gUnknown_Debug_083C2F70, DummyMenuAction},
    {gUnknown_Debug_083C2F8C, DummyMenuAction},
    {gUnknown_Debug_083C2FA8, DummyMenuAction},
    {gUnknown_Debug_083C2FC2, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C3028[] = _("FE???SOUKO???OPEN???CAVE???D1704");
static const u8 gUnknown_Debug_083C3041[] = _("FE???SORAISI???01???CAVE???D0101");
static const u8 gUnknown_Debug_083C305A[] = _("FE???MAYUMI???01??????R114???R0201");
static const u8 gUnknown_Debug_083C3073[] = _("FE???KUSUNOKI???01???C102???R0601");
static const u8 gUnknown_Debug_083C308D[] = _("FE???OLDWOMAN1???01???CAVE???D0808");
static const u8 gUnknown_Debug_083C30A8[] = _("FE???TRAINERM1???01???C109???R0206");
static const u8 gUnknown_Debug_083C30C3[] = _("FE???SOONANO???TAMAGO???GET");
static const u8 gUnknown_Debug_083C30D9[] = _("FE???DASH???SHOES???GET");
static const u8 gUnknown_Debug_083C30EB[] = _("FE???DEBONSUKOOPU???GET");

static const struct MenuAction gUnknown_Debug_083C3100[] = {
    {gUnknown_Debug_083C3028, DummyMenuAction},
    {gUnknown_Debug_083C3041, DummyMenuAction},
    {gUnknown_Debug_083C305A, DummyMenuAction},
    {gUnknown_Debug_083C3073, DummyMenuAction},
    {gUnknown_Debug_083C308D, DummyMenuAction},
    {gUnknown_Debug_083C30A8, DummyMenuAction},
    {gUnknown_Debug_083C30C3, DummyMenuAction},
    {gUnknown_Debug_083C30D9, DummyMenuAction},
    {gUnknown_Debug_083C30EB, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C3148[] = _("FE???STUDYM1???01???P01???T101R0301");
static const u8 gUnknown_Debug_083C3164[] = _("FE???WORKERM1???01???C103???R0201");
static const u8 gUnknown_Debug_083C317E[] = _("FE???HIMITSU???GET");
static const u8 gUnknown_Debug_083C318D[] = _("");
static const u8 gUnknown_Debug_083C318E[] = _("");
static const u8 gUnknown_Debug_083C318F[] = _("");
static const u8 gUnknown_Debug_083C3190[] = _("");
static const u8 gUnknown_Debug_083C3191[] = _("");
static const u8 gUnknown_Debug_083C3192[] = _("");

static const struct MenuAction gUnknown_Debug_083C3194[] = {
    {gUnknown_Debug_083C3148, DummyMenuAction},
    {gUnknown_Debug_083C3164, DummyMenuAction},
    {gUnknown_Debug_083C317E, DummyMenuAction},
    {gUnknown_Debug_083C318D, DummyMenuAction},
    {gUnknown_Debug_083C318E, DummyMenuAction},
    {gUnknown_Debug_083C318F, DummyMenuAction},
    {gUnknown_Debug_083C3190, DummyMenuAction},
    {gUnknown_Debug_083C3191, DummyMenuAction},
    {gUnknown_Debug_083C3192, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C31DC[] = {9, 9, 9, 9, 9, 9, 9, 9, 3};

static const u16 gUnknown_Debug_83C31E6[][9] = {
    {FLAG_RECEIVED_HM01, FLAG_RECEIVED_HM02, FLAG_RECEIVED_HM03, FLAG_RECEIVED_HM04, FLAG_RECEIVED_HM05, FLAG_RECEIVED_HM06, FLAG_RETURNED_DEVON_GOODS, FLAG_DEVON_GOODS_STOLEN, FLAG_RECOVERED_DEVON_GOODS},
    {FLAG_RECEIVED_BIKE, 0x05B, 0x05C, 0x05D, FLAG_RECEIVED_WAILMER_PAIL, FLAG_RECEIVED_POKEBLOCK_CASE, FLAG_RECEIVED_OLD_ROD, FLAG_RECEIVED_GOOD_ROD, FLAG_RECEIVED_SUPER_ROD},
    {FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FLAG_EXCHANGED_SCANNER, FLAG_LEGEND_ESCAPED_SEAFLOOR_CAVERN, FLAG_LEGENDARY_BATTLE_COMPLETED, FLAG_RECEIVED_REPEAT_BALL, FLAG_RECEIVED_SS_TICKET, FLAG_KECLEON_FLED_FORTREE, FLAG_RECEIVED_FOSSIL_MON, FLAG_DEFEATED_SS_TIDAL_TRAINERS},
    {0x06C, FLAG_DEFEATED_WALLY_VICTORY_ROAD, FLAG_DEFEATED_WALLY_MAUVILLE, FLAG_WALLY_SPEECH, FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, FLAG_USED_ROOM_1_KEY, FLAG_USED_ROOM_2_KEY, FLAG_USED_ROOM_4_KEY, FLAG_USED_ROOM_6_KEY},
    {FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_1, FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_2, FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_3, FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_4, FLAG_TRICK_HOUSE_PUZZLE_7_SWITCH_5, FLAG_MOSSDEEP_GYM_SWITCH_1, FLAG_MOSSDEEP_GYM_SWITCH_2, FLAG_MOSSDEEP_GYM_SWITCH_3, FLAG_MOSSDEEP_GYM_SWITCH_4},
    {FLAG_DEFEATED_RIVAL_ROUTE103, FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, FLAG_MET_RIVAL_RUSTBORO, FLAG_MET_RIVAL_LILYCOVE, FLAG_MET_RIVAL_IN_HOUSE_AFTER_LILYCOVE, 0x050, FLAG_SET_WALL_CLOCK, FLAG_RESCUED_BIRCH, 0x055},
    {FLAG_RECEIVED_RED_SCARF, FLAG_RECEIVED_BLUE_SCARF, FLAG_RECEIVED_PINK_SCARF, FLAG_RECEIVED_GREEN_SCARF, FLAG_RECEIVED_YELLOW_SCARF, 0x053, 0x054, FLAG_LINK_CONTEST_ROOM_POKEBALL, FLAG_MET_RIVAL_MOM},
    {FLAG_USED_STORAGE_KEY, FLAG_MET_PROF_COSMO, FLAG_RECEIVED_DOLL_LANETTE, FLAG_EVIL_TEAM_ESCAPED_STERN_SPOKE, FLAG_RETURNED_RED_OR_BLUE_ORB, FLAG_ENTERED_ELITE_FOUR, FLAG_RECEIVED_LAVARIDGE_EGG, FLAG_RECEIVED_RUNNING_SHOES, FLAG_RECEIVED_DEVON_SCOPE},
    {FLAG_BIRCH_AIDE_MET, FLAG_DECLINED_BIKE, FLAG_RECEIVED_SECRET_POWER}
};

static const u8 gUnknown_Debug_083C3288[] = DTR("CYCLE????????????", "CYCLE-related");
static const u8 gUnknown_Debug_083C3292[] = DTR("?????????????????????", "Size comparison");
static const u8 gUnknown_Debug_083C329A[] = DTR("????????????", "Counter");
static const u8 gUnknown_Debug_083C329F[] = DTR("?????????1", "Other 1");
static const u8 gUnknown_Debug_083C32A4[] = DTR("?????????2", "Other 2");

static const struct MenuAction gUnknown_Debug_083C32AC[] = {
    {gUnknown_Debug_083C3288, debug_sub_808E400},
    {gUnknown_Debug_083C3292, debug_sub_808E458},
    {gUnknown_Debug_083C329A, debug_sub_808E4B0},
    {gUnknown_Debug_083C329F, debug_sub_808E508},
    {gUnknown_Debug_083C32A4, debug_sub_808E560}
};

static const u8 gUnknown_Debug_083C32D4[] = _("WK???CYCLE???ROAD???HIT");
static const u8 gUnknown_Debug_083C32E6[] = _("WK???CYCLE???ROAD???TIM???1");
static const u8 gUnknown_Debug_083C32FA[] = _("WK???CYCLE???ROAD???TIM???2");

static const u8 gUnknown_Debug_083C330E[] = _("WK???SIZE???KINOKOKO???OYAJI");
static const u8 gUnknown_Debug_083C3325[] = _("WK???SIZE???NAMAZO???OYAJI");

static const u8 gUnknown_Debug_083C333A[] = _("WK???SPRAY???COUNT");
static const u8 gUnknown_Debug_083C3349[] = _("WK???ICE???COUNT");
static const u8 gUnknown_Debug_083C3356[] = _("WK???ASH???GATHER???COUNT");
static const u8 gUnknown_Debug_083C336A[] = _("WK???CRUISE???COUNT");
static const u8 gUnknown_Debug_083C337A[] = _("WK???FRIENDLY???STEP???COUNT");
static const u8 gUnknown_Debug_083C3391[] = _("WK???POISON???STEP???COUNT");

static const u8 gUnknown_Debug_083C33A6[] = _("WKRECYCLE???GOODS");
static const u8 gUnknown_Debug_083C33B6[] = _("WK???FIRST???POKE");
static const u8 gUnknown_Debug_083C33C4[] = _("WK???MABOROSIRND???H");
static const u8 gUnknown_Debug_083C33D5[] = _("WK???MABOROSIRND???L");
static const u8 gUnknown_Debug_083C33E6[] = _("EV???ONE???DAY???WORK");
static const u8 gUnknown_Debug_083C33F6[] = _("EV???FANWORK");
static const u8 gUnknown_Debug_083C3401[] = _("EV???FANTIME");
static const u8 gUnknown_Debug_083C340C[] = _("WK???KARAKURI???LEVEL");
static const u8 gUnknown_Debug_083C341E[] = _("WK???POKELOT???PRIZE");

static const u8 gUnknown_Debug_083C342F[] = _("WK???SPECIAL???ZUKN");
static const u8 gUnknown_Debug_083C343F[] = _("WK???HYOUKA???DAYS");
static const u8 gUnknown_Debug_083C344E[] = _("WK???POKELOT???RND1");
static const u8 gUnknown_Debug_083C345E[] = _("WK???POKELOT???RND2");
static const u8 gUnknown_Debug_083C346E[] = _("WK???BASE???MAPNO");

static const struct MenuAction gUnknown_Debug_083C347C[] = {
    {gUnknown_Debug_083C32D4, DummyMenuAction},
    {gUnknown_Debug_083C32E6, DummyMenuAction},
    {gUnknown_Debug_083C32FA, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_083C3494[] = {
    {gUnknown_Debug_083C330E, DummyMenuAction},
    {gUnknown_Debug_083C3325, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_083C34A4[] = {
    {gUnknown_Debug_083C333A, DummyMenuAction},
    {gUnknown_Debug_083C3349, DummyMenuAction},
    {gUnknown_Debug_083C3356, DummyMenuAction},
    {gUnknown_Debug_083C336A, DummyMenuAction},
    {gUnknown_Debug_083C337A, DummyMenuAction},
    {gUnknown_Debug_083C3391, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_083C34D4[] = {
    {gUnknown_Debug_083C33A6, DummyMenuAction},
    {gUnknown_Debug_083C33B6, DummyMenuAction},
    {gUnknown_Debug_083C33C4, DummyMenuAction},
    {gUnknown_Debug_083C33D5, DummyMenuAction},
    {gUnknown_Debug_083C33E6, DummyMenuAction},
    {gUnknown_Debug_083C33F6, DummyMenuAction},
    {gUnknown_Debug_083C3401, DummyMenuAction},
    {gUnknown_Debug_083C340C, DummyMenuAction},
    {gUnknown_Debug_083C341E, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_083C351C[] = {
    {gUnknown_Debug_083C342F, DummyMenuAction},
    {gUnknown_Debug_083C343F, DummyMenuAction},
    {gUnknown_Debug_083C344E, DummyMenuAction},
    {gUnknown_Debug_083C345E, DummyMenuAction},
    {gUnknown_Debug_083C346E, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C3544[] = {3, 2, 6, 9, 5};

static const u16 gUnknown_Debug_083C354A[][9] = {
    {VAR_CYCLING_ROAD_RECORD_COLLISIONS, VAR_CYCLING_ROAD_RECORD_TIME_L, VAR_CYCLING_ROAD_RECORD_TIME_H},
    {VAR_SHROOMISH_SIZE_RECORD, VAR_BARBOACH_SIZE_RECORD},
    {VAR_REPEL_STEP_COUNT, VAR_ICE_STEP_COUNT, VAR_ASH_GATHER_COUNT, VAR_CRUISE_STEP_COUNT, VAR_HAPPINESS_STEP_COUNTER, VAR_POISON_STEP_COUNTER},
    {VAR_RECYCLE_GOODS, VAR_STARTER_MON, VAR_MIRAGE_RND_H, VAR_MIRAGE_RND_L, VAR_DAYS, VAR_FANCLUB_UNKNOWN_1, VAR_FANCLUB_UNKNOWN_2, VAR_TRICK_HOUSE_ROOMS_COMPLETED, VAR_LOTTERY_PRIZE},
    {VAR_NATIONAL_DEX, VAR_BIRCH_STATE, VAR_LOTTERY_RND_L, VAR_LOTTERY_RND_H, VAR_SECRET_BASE_MAP}
};

static const u8 gUnknown_Debug_083C35A4[] = _("OBJCHRWORK0???8");
static const u8 gUnknown_Debug_083C35B2[] = _("OBJCHRWORK9???15");

static const struct MenuAction gUnknown_Debug_083C35C4[] = {
    {gUnknown_Debug_083C35A4, debug_sub_808E9A0},
    {gUnknown_Debug_083C35B2, debug_sub_808E9F8}
};

static const u8 gUnknown_Debug_083C35D4[] = _("OBJCHRWORK1");
static const u8 gUnknown_Debug_083C35E0[] = _("OBJCHRWORK2");
static const u8 gUnknown_Debug_083C35EC[] = _("OBJCHRWORK3");
static const u8 gUnknown_Debug_083C35F8[] = _("OBJCHRWORK4");
static const u8 gUnknown_Debug_083C3604[] = _("OBJCHRWORK5");
static const u8 gUnknown_Debug_083C3610[] = _("OBJCHRWORK6");
static const u8 gUnknown_Debug_083C361C[] = _("OBJCHRWORK7");
static const u8 gUnknown_Debug_083C3628[] = _("OBJCHRWORK8");
static const u8 gUnknown_Debug_083C3634[] = _("OBJCHRWORK9");

static const u8 gUnknown_Debug_083C3640[] = _("OBJCHRWORK10");
static const u8 gUnknown_Debug_083C364D[] = _("OBJCHRWORK11");
static const u8 gUnknown_Debug_083C365A[] = _("OBJCHRWORK12");
static const u8 gUnknown_Debug_083C3667[] = _("OBJCHRWORK13");
static const u8 gUnknown_Debug_083C3674[] = _("OBJCHRWORK14");
static const u8 gUnknown_Debug_083C3681[] = _("OBJCHRWORK15");
static const u8 gUnknown_Debug_083C368E[] = _("OBJCHRWORK16");

static const struct MenuAction gUnknown_Debug_083C369C[] = {
    {gUnknown_Debug_083C35D4, DummyMenuAction},
    {gUnknown_Debug_083C35E0, DummyMenuAction},
    {gUnknown_Debug_083C35EC, DummyMenuAction},
    {gUnknown_Debug_083C35F8, DummyMenuAction},
    {gUnknown_Debug_083C3604, DummyMenuAction},
    {gUnknown_Debug_083C3610, DummyMenuAction},
    {gUnknown_Debug_083C361C, DummyMenuAction},
    {gUnknown_Debug_083C3628, DummyMenuAction},
    {gUnknown_Debug_083C3634, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_083C36E4[] = {
    {gUnknown_Debug_083C3640, DummyMenuAction},
    {gUnknown_Debug_083C364D, DummyMenuAction},
    {gUnknown_Debug_083C365A, DummyMenuAction},
    {gUnknown_Debug_083C3667, DummyMenuAction},
    {gUnknown_Debug_083C3674, DummyMenuAction},
    {gUnknown_Debug_083C3681, DummyMenuAction},
    {gUnknown_Debug_083C368E, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C371C[] = {9, 7};

static const u16 gUnknown_Debug_083C371E[][9] = {
    {VAR_OBJ_GFX_ID_0, VAR_OBJ_GFX_ID_1, VAR_OBJ_GFX_ID_2, VAR_OBJ_GFX_ID_3, VAR_OBJ_GFX_ID_4, VAR_OBJ_GFX_ID_5, VAR_OBJ_GFX_ID_6, VAR_OBJ_GFX_ID_7, VAR_OBJ_GFX_ID_8},
    {VAR_OBJ_GFX_ID_9, VAR_OBJ_GFX_ID_A, VAR_OBJ_GFX_ID_B, VAR_OBJ_GFX_ID_C, VAR_OBJ_GFX_ID_D, VAR_OBJ_GFX_ID_E, VAR_OBJ_GFX_ID_F}
};

static const u8 gUnknown_Debug_083C3742[] = _("SP");
static const u8 gUnknown_Debug_083C3745[] = DTR("????????????R110???PART1/????????????", "Room R110 Part 1/TRICK");
static const u8 gUnknown_Debug_083C3759[] = DTR("????????????R110???PART2", "Room R110 Part 2");
static const u8 gUnknown_Debug_083C3768[] = DTR("?????????????????????", "Room road"); // TRN
static const u8 gUnknown_Debug_083C3770[] = DTR("?????????1", "Other 1");
static const u8 gUnknown_Debug_083C3775[] = DTR("?????????2", "Other 2");

static const struct MenuAction sMenuActions_ControlWorks_SaveWorkPart2[] = {
    {gUnknown_Debug_083C3742, ControlWorks_SaveWorkPart2_SP_InitSubsubmenu},
    {gUnknown_Debug_083C3745, ControlWorks_SaveWorkPart2_RoomR110Part1TrickHouse_InitSubsubmenu},
    {gUnknown_Debug_083C3759, ControlWorks_SaveWorkPart2_RoomR110Part2_InitSubsubmenu},
    {gUnknown_Debug_083C3768, ControlWorks_SaveWorkPart2_RoomLoad_InitSubsubmenu},
    {gUnknown_Debug_083C3770, debug_sub_808E1B4},
    {gUnknown_Debug_083C3775, debug_sub_808E20C}
};

static const u8 gUnknown_Debug_083C37AC[] = _("WK???SCENE???SP???CONTEST");
static const u8 gUnknown_Debug_083C37C0[] = _("WK???SCENE???SP???PC");
static const u8 gUnknown_Debug_083C37CF[] = _("WK???SCENE???SP???CONTEST03");
static const u8 gUnknown_Debug_083C37E5[] = _("WK???SCENE???SP???CONTESTITEM");
static const u8 gUnknown_Debug_083C37FD[] = _("WK???SCENE???SP???OPENING");
static const u8 gUnknown_Debug_083C3811[] = _("WK???SCENE???SP???SHIP01");
static const u8 gUnknown_Debug_083C3824[] = _("");
static const u8 gUnknown_Debug_083C3825[] = _("");
static const u8 gUnknown_Debug_083C3826[] = _("");

static const u8 gUnknown_Debug_083C3827[] = _("WK???SCENE???R110???R0101");
static const u8 gUnknown_Debug_083C383B[] = _("WK???SCENE???R110???R0102");
static const u8 gUnknown_Debug_083C384F[] = _("WK???SCENE???R110???R0103");
static const u8 gUnknown_Debug_083C3863[] = _("WK???KARAKURI???DAIOU");
static const u8 gUnknown_Debug_083C3875[] = _("WK???SCENE???SHISEN");
static const u8 gUnknown_Debug_083C3885[] = _("");
static const u8 gUnknown_Debug_083C3886[] = _("");
static const u8 gUnknown_Debug_083C3887[] = _("");
static const u8 gUnknown_Debug_083C3888[] = _("");

static const u8 gUnknown_Debug_083C3889[] = _("WK???SCENE???R110???R0104");
static const u8 gUnknown_Debug_083C389D[] = _("WK???SCENE???R110???R0105");
static const u8 gUnknown_Debug_083C38B1[] = _("WK???SCENE???R110???R0106");
static const u8 gUnknown_Debug_083C38C5[] = _("WK???SCENE???R110???R0107");
static const u8 gUnknown_Debug_083C38D9[] = _("WK???SCENE???R110???R0108");
static const u8 gUnknown_Debug_083C38ED[] = _("WK???SCENE???R110???R0109");
static const u8 gUnknown_Debug_083C3901[] = _("WK???SCENE???R110???R0110");
static const u8 gUnknown_Debug_083C3915[] = _("WK???SCENE???R110???R0111");
static const u8 gUnknown_Debug_083C3929[] = _("WK???SCENE???02???R110???R0110");

static const u8 gUnknown_Debug_083C3940[] = _("WK???SCENE???R104???R0101");
static const u8 gUnknown_Debug_083C3954[] = _("WK???SCENE???R113???R0101");
static const u8 gUnknown_Debug_083C3968[] = _("");
static const u8 gUnknown_Debug_083C3969[] = _("");
static const u8 gUnknown_Debug_083C396A[] = _("");
static const u8 gUnknown_Debug_083C396B[] = _("");
static const u8 gUnknown_Debug_083C396C[] = _("");
static const u8 gUnknown_Debug_083C396D[] = _("");
static const u8 gUnknown_Debug_083C396E[] = _("");

static const u8 gUnknown_Debug_083C396F[] = _("WK???SCENE???BASE???GDOODS");
static const u8 gUnknown_Debug_083C3984[] = _("WK???SCENE???HAGI???FUNE");
static const u8 gUnknown_Debug_083C3997[] = _("WK???SCENE???FUNE???POS");
static const u8 gUnknown_Debug_083C39A9[] = _("WK???SCENE???BASE???MAKE");
static const u8 gUnknown_Debug_083C39BC[] = _("WK???SCENE???ARTIST???C106???R");
static const u8 gUnknown_Debug_083C39D3[] = _("WK???SCENE???POKE???LEAGUE");
static const u8 gUnknown_Debug_083C39E8[] = _("WK???SCENE???ROPEWAY");
static const u8 gUnknown_Debug_083C39F9[] = _("WK???SCENE???SAFARI???ZONE");
static const u8 gUnknown_Debug_083C3A0E[] = _("WK???SCENE???CYCLE???ROAD");

static const u8 gUnknown_Debug_083C3A22[] = _("WK???SCENE???R119???TENKI");
static const u8 gUnknown_Debug_083C3A36[] = _("WK???SCENE???01???C102???R0401");
static const u8 gUnknown_Debug_083C3A4D[] = _("WK???FUTAGO???01???FIELD???R104");
static const u8 gUnknown_Debug_083C3A65[] = _("WK???SCENE???BATTLE???TOWER");
static const u8 gUnknown_Debug_083C3A7B[] = _("WK???SCENE???TR???HOUSE");
static const u8 gUnknown_Debug_083C3A8D[] = _("WK???KASEKI???TYPE");
static const u8 gUnknown_Debug_083C3A9C[] = _("");
static const u8 gUnknown_Debug_083C3A9D[] = _("");
static const u8 gUnknown_Debug_083C3A9E[] = _("");

static const struct MenuAction gUnknown_Debug_083C3AA0[] = {
    {gUnknown_Debug_083C37AC, DummyMenuAction},
    {gUnknown_Debug_083C37C0, DummyMenuAction},
    {gUnknown_Debug_083C37CF, DummyMenuAction},
    {gUnknown_Debug_083C37E5, DummyMenuAction},
    {gUnknown_Debug_083C37FD, DummyMenuAction},
    {gUnknown_Debug_083C3811, DummyMenuAction},
    {gUnknown_Debug_083C3824, DummyMenuAction},
    {gUnknown_Debug_083C3825, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_83C3AE0[] = {
    {gUnknown_Debug_083C3827, DummyMenuAction},
    {gUnknown_Debug_083C383B, DummyMenuAction},
    {gUnknown_Debug_083C384F, DummyMenuAction},
    {gUnknown_Debug_083C3863, DummyMenuAction},
    {gUnknown_Debug_083C3875, DummyMenuAction},
    {gUnknown_Debug_083C3885, DummyMenuAction},
    {gUnknown_Debug_083C3886, DummyMenuAction},
    {gUnknown_Debug_083C3887, DummyMenuAction},
    {gUnknown_Debug_083C3888, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_83C3B28[] = {
    {gUnknown_Debug_083C3889, DummyMenuAction},
    {gUnknown_Debug_083C389D, DummyMenuAction},
    {gUnknown_Debug_083C38B1, DummyMenuAction},
    {gUnknown_Debug_083C38C5, DummyMenuAction},
    {gUnknown_Debug_083C38D9, DummyMenuAction},
    {gUnknown_Debug_083C38ED, DummyMenuAction},
    {gUnknown_Debug_083C3901, DummyMenuAction},
    {gUnknown_Debug_083C3915, DummyMenuAction},
    {gUnknown_Debug_083C3929, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_83C3B70[] = {
    {gUnknown_Debug_083C3940, DummyMenuAction},
    {gUnknown_Debug_083C3954, DummyMenuAction},
    {gUnknown_Debug_083C3968, DummyMenuAction},
    {gUnknown_Debug_083C3969, DummyMenuAction},
    {gUnknown_Debug_083C396A, DummyMenuAction},
    {gUnknown_Debug_083C396B, DummyMenuAction},
    {gUnknown_Debug_083C396C, DummyMenuAction},
    {gUnknown_Debug_083C396D, DummyMenuAction},
    {gUnknown_Debug_083C396E, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_83C3BB8[] = {
    {gUnknown_Debug_083C396F, DummyMenuAction},
    {gUnknown_Debug_083C3984, DummyMenuAction},
    {gUnknown_Debug_083C3997, DummyMenuAction},
    {gUnknown_Debug_083C39A9, DummyMenuAction},
    {gUnknown_Debug_083C39BC, DummyMenuAction},
    {gUnknown_Debug_083C39D3, DummyMenuAction},
    {gUnknown_Debug_083C39E8, DummyMenuAction},
    {gUnknown_Debug_083C39F9, DummyMenuAction},
    {gUnknown_Debug_083C3A0E, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_83C3C00[] = {
    {gUnknown_Debug_083C3A22, DummyMenuAction},
    {gUnknown_Debug_083C3A36, DummyMenuAction},
    {gUnknown_Debug_083C3A4D, DummyMenuAction},
    {gUnknown_Debug_083C3A65, DummyMenuAction},
    {gUnknown_Debug_083C3A7B, DummyMenuAction},
    {gUnknown_Debug_083C3A8D, DummyMenuAction},
    {gUnknown_Debug_083C3A9C, DummyMenuAction},
    {gUnknown_Debug_083C3A9D, DummyMenuAction},
    {gUnknown_Debug_083C3A9E, DummyMenuAction}
};

static const u8 sControlWorks_SaveWork_CountsArray[] = {6, 5, 9, 2, 9, 6};

static const u16 sControlWorks_SaveWork_ItemArrays[][9] = {
    {VAR_LINK_CONTEST_ROOM_STATE, VAR_CABLE_CLUB_STATE, VAR_CONTEST_LOCATION, VAR_CONTEST_PRIZE_PICKUP, VAR_LITTLEROOT_INTRO_STATE, VAR_PORTHOLE_STATE},
    {VAR_TRICK_HOUSE_ENTRANCE_STATE_2, VAR_TRICK_HOUSE_PRIZE_PICKUP, VAR_TRICK_HOUSE_STATE, VAR_TRICK_HOUSE_ENTRANCE_STATE_3, VAR_TRICK_HOUSE_ENTRANCE_STATE},
    {VAR_TRICK_HOUSE_PUZZLE_1_STATE, VAR_TRICK_HOUSE_PUZZLE_2_STATE, VAR_TRICK_HOUSE_PUZZLE_3_STATE, VAR_TRICK_HOUSE_PUZZLE_4_STATE, VAR_TRICK_HOUSE_PUZZLE_5_STATE, VAR_TRICK_HOUSE_PUZZLE_6_STATE, VAR_TRICK_HOUSE_PUZZLE_7_STATE, VAR_TRICK_HOUSE_PUZZLE_8_STATE, VAR_TRICK_HOUSE_PUZZLE_7_STATE_2},
    {VAR_BRINEY_HOUSE_STATE, VAR_GLASS_WORKSHOP_STATE},
    {VAR_SECRET_BASE_INITIALIZED, VAR_BOARD_BRINEY_BOAT_ROUTE104_STATE, VAR_BRINEY_LOCATION, VAR_INIT_SECRET_BASE, VAR_LILYCOVE_CONTEST_LOBBY_STATE, VAR_ELITE_4_STATE, VAR_CABLE_CAR_STATION_STATE, VAR_SAFARI_ZONE_STATE, VAR_CYCLING_CHALLENGE_STATE},
    {VAR_WEATHER_INSTITUTE_STATE, VAR_SLATEPORT_FAN_CLUB_STATE, 0x40BB, VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, VAR_GAME_CORNER_STATE, VAR_WHICH_FOSSIL_REVIVED}
};

static const u8 sString_Town[] = DTR("?????????", "TOWN");
static const u8 sString_City[] = DTR("?????????", "CITY");
static const u8 sString_Route_101_to_109[] = DTR("?????????101???109", "ROUTE 101-109");
static const u8 sString_Route_110_to_118[] = DTR("?????????110???118", "ROUTE 110-118");
static const u8 sString_Route_119_to_127[] = DTR("?????????119???127", "ROUTE 119-127");
static const u8 sString_Route_128_to_134[] = DTR("?????????128???134", "ROUTE 128-134");
static const u8 sString_Room_Town[] = DTR("?????????????????????", "Room Town"); // TRN
static const u8 sString_Room_City[] = DTR("?????????????????????", "Room City");
static const u8 sString_Dungeon_nai[] = DTR("?????????????????????", "DUNGEON");

static const struct MenuAction sMenuAction_ControlWorks_SaveWork[] = {
    {sString_Town, ControlWorks_SaveWork_Town_InitSubsubmenu},
    {sString_City, ControlWorks_SaveWork_City_InitSubsubmenu},
    {sString_Route_101_to_109, ControlWorks_SaveWork_Route101To109_InitSubsubmenu},
    {sString_Route_110_to_118, ControlWorks_SaveWork_Route110To118_InitSubsubmenu},
    {sString_Route_119_to_127, ControlWorks_SaveWork_Route119To127_InitSubsubmenu},
    {sString_Route_128_to_134, ControlWorks_SaveWork_Route128To134_InitSubsubmenu},
    {sString_Room_Town, ControlWorks_SaveWork_RoomTown_InitSubsubmenu},
    {sString_Room_City, ControlWorks_SaveWork_RoomCity_InitSubsubmenu},
    {sString_Dungeon_nai, ControlWorks_SaveWork_Dungeon_InitSubsubmenu}
};

static const u8 sString_WK_SCENE_FIELD_T101[] = _("WK???SCENE???FIELD???T101");
static const u8 sString_WK_SCENE_FIELD_T102[] = _("WK???SCENE???FIELD???T102");
static const u8 sString_WK_SCENE_FIELD_T103[] = _("WK???SCENE???FIELD???T103");
static const u8 sString_WK_SCENE_FIELD_T104[] = _("WK???SCENE???FIELD???T104");
static const u8 sString_WK_BASE_POSNO[] = _("WK???BASE???POSNO");
static const u8 sString_WK_SCENE_FIELD_T106[] = _("WK???SCENE???FIELD???T106");
static const u8 sString_WK_SCENE_FIELD_T107[] = _("WK???SCENE???FIELD???T107");
static const u8 sString_WK_SCENE_2_FIELD_T102[] = _("WK???SCENE???02???FIELD???T102");

static const u8 sString_WK_SCENE_FIELD_C101[] = _("WK???SCENE???FIELD???C101");
static const u8 sString_WK_SCENE_FIELD_C102[] = _("WK???SCENE???FIELD???C102");
static const u8 sString_WK_SCENE_FIELD_C103[] = _("WK???SCENE???FIELD???C103");
static const u8 sString_WK_SCENE_FIELD_C104[] = _("WK???SCENE???FIELD???C104");
static const u8 sString_WK_SCENE_FIELD_C105[] = _("WK???SCENE???FIELD???C105");
static const u8 sString_WK_SCENE_FIELD_C106[] = _("WK???SCENE???FIELD???C106");
static const u8 sString_WK_SCENE_FIELD_C107[] = _("WK???SCENE???FIELD???C107");
static const u8 sString_WK_SCENE_FIELD_C108[] = _("WK???SCENE???FIELD???C108");
static const u8 sString_WK_SCENE_FIELD_C109[] = _("WK???SCENE???FIELD???C109");

static const u8 sString_WK_SCENE_FIELD_R101[] = _("WK???SCENE???FIELD???R101");
static const u8 sString_WK_SCENE_FIELD_R102[] = _("WK???SCENE???FIELD???R102");
static const u8 sString_WK_SCENE_FIELD_R103[] = _("WK???SCENE???FIELD???R103");
static const u8 sString_WK_SCENE_FIELD_R104[] = _("WK???SCENE???FIELD???R104");
static const u8 sString_WK_SCENE_FIELD_R105[] = _("WK???SCENE???FIELD???R105");
static const u8 sString_WK_SCENE_FIELD_R106[] = _("WK???SCENE???FIELD???R106");
static const u8 sString_WK_SCENE_FIELD_R107[] = _("WK???SCENE???FIELD???R107");
static const u8 sString_WK_SCENE_FIELD_R108[] = _("WK???SCENE???FIELD???R108");
static const u8 sString_WK_SCENE_FIELD_R109[] = _("WK???SCENE???FIELD???R109");

static const u8 sString_WK_SCENE_FIELD_R110[] = _("WK???SCENE???FIELD???R110");
static const u8 sString_WK_SCENE_FIELD_R111[] = _("WK???SCENE???FIELD???R111");
static const u8 sString_WK_SCENE_FIELD_R112[] = _("WK???SCENE???FIELD???R112");
static const u8 sString_WK_SCENE_FIELD_R113[] = _("WK???SCENE???FIELD???R113");
static const u8 sString_WK_SCENE_FIELD_R114[] = _("WK???SCENE???FIELD???R114");
static const u8 sString_WK_SCENE_FIELD_R115[] = _("WK???SCENE???FIELD???R115");
static const u8 sString_WK_SCENE_FIELD_R116[] = _("WK???SCENE???FIELD???R116");
static const u8 sString_WK_SCENE_FIELD_R117[] = _("WK???SCENE???FIELD???R117");
static const u8 sString_WK_SCENE_FIELD_R118[] = _("WK???SCENE???FIELD???R118");

static const u8 sString_WK_SCENE_FIELD_R119[] = _("WK???SCENE???FIELD???R119");
static const u8 sString_WK_SCENE_FIELD_R120[] = _("WK???SCENE???FIELD???R120");
static const u8 sString_WK_SCENE_FIELD_R121[] = _("WK???SCENE???FIELD???R121");
static const u8 sString_WK_SCENE_FIELD_R122[] = _("WK???SCENE???FIELD???R122");
static const u8 sString_WK_SCENE_FIELD_R123[] = _("WK???SCENE???FIELD???R123");
static const u8 sString_WK_SCENE_FIELD_R124[] = _("WK???SCENE???FIELD???R124");
static const u8 sString_WK_SCENE_FIELD_R125[] = _("WK???SCENE???FIELD???R125");
static const u8 sString_WK_SCENE_FIELD_R126[] = _("WK???SCENE???FIELD???R126");
static const u8 sString_WK_SCENE_FIELD_R127[] = _("WK???SCENE???FIELD???R127");

static const u8 sString_WK_SCENE_FIELD_R128[] = _("WK???SCENE???FIELD???R128");
static const u8 sString_WK_SCENE_FIELD_R129[] = _("WK???SCENE???FIELD???R129");
static const u8 sString_WK_SCENE_FIELD_R130[] = _("WK???SCENE???FIELD???R130");
static const u8 sString_WK_SCENE_FIELD_R131[] = _("WK???SCENE???FIELD???R131");
static const u8 sString_WK_SCENE_FIELD_R132[] = _("WK???SCENE???FIELD???R132");
static const u8 sString_WK_SCENE_FIELD_R133[] = _("WK???SCENE???FIELD???R133");
static const u8 sString_WK_SCENE_FIELD_R134[] = _("WK???SCENE???FIELD???R134");

static const u8 sString_WK_SCENE_T101_R0101[] = _("WK???SCENE???T101???R0101");
static const u8 sString_WK_SCENE_T101_R0102[] = _("WK???SCENE???T101???R0102");
static const u8 sString_WK_SCENE_T101_R0301[] = _("WK???SCENE???T101???R0301");
static const u8 sString_WK_SCENE_T101_R0201[] = _("WK???SCENE???T101???R0201");
static const u8 sString_WK_SCENE_T101_R0202[] = _("WK???SCENE???T101???R0202");
static const u8 sString_WK_SCENE_T107_R0201[] = _("WK???SCENE???T107???R0201"); // unused string

static const u8 sString_WK_SCENE_C101_R0201[] = _("WK???SCENE???C101???R0201");
static const u8 sString_WK_SCENE_C104_R0103[] = _("WK???SCENE???C104???R0103");
static const u8 sString_WK_SCENE_C103_R0101[] = _("WK???SCENE???C103???R0101");
static const u8 sString_WK_SCENE_C106_R0202[] = _("WK???SCENE???C106???R0202");
static const u8 sString_WK_SCENE_C106_R0401[] = _("WK???SCENE???C106???R0401");
static const u8 sString_WK_SCENE_C101_R0601[] = _("WK???SCENE???C102???R0601");
static const u8 sString_WK_SCENE_C102_R0501[] = _("WK???SCENE???C102???R0501");
static const u8 sString_WK_SCENE_C104_R0102[] = _("WK???SCENE???C104???R0102");
static const u8 sString_WK_SCENE_C107_R0501[] = _("WK???SCENE???C107???R0501");

static const u8 sString_WK_SCENE_CAVE_D0601[] = _("WK???SCENE???CAVE???D0601");
static const u8 sString_WK_SCENE_CAVE_D0201[] = _("WK???SCENE???CAVE???D0201");
static const u8 sString_WK_SCENE_CAVE_D1206[] = _("WK???SCENE???CAVE???D1206");
static const u8 sString_WK_SCENE_CAVE_D1111[] = _("WK???SCENE???CAVE???D1111");
static const u8 sString_WK_SCENE_CAVE_D0701[] = _("WK???SCENE???CAVE???D0701");
static const u8 sString_WK_SCENE_CAVE_D0808[] = _("WK???SCENE???CAVE???D0808");
static const u8 sString_WK_SCENE_CAVE_D1602[] = _("WK???SCENE???CAVE???D1602");
static const u8 sString_WK_SCENE_CAVE_D0101[] = _("WK???SCENE???CAVE???D0101");
static const u8 sString_WK_SCENE_CAVE_D1301[] = _("WK???SCENE???CAVE???D1301");

static const struct MenuAction sMenuActions_SaveWork_Town[] = {
    {sString_WK_SCENE_FIELD_T101, DummyMenuAction},
    {sString_WK_SCENE_FIELD_T102, DummyMenuAction},
    {sString_WK_SCENE_FIELD_T103, DummyMenuAction},
    {sString_WK_SCENE_FIELD_T104, DummyMenuAction},
    {sString_WK_BASE_POSNO, DummyMenuAction},
    {sString_WK_SCENE_FIELD_T106, DummyMenuAction},
    {sString_WK_SCENE_FIELD_T107, DummyMenuAction},
    {sString_WK_SCENE_2_FIELD_T102, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_City[] = {
    {sString_WK_SCENE_FIELD_C101, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C102, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C103, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C104, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C105, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C106, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C107, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C108, DummyMenuAction},
    {sString_WK_SCENE_FIELD_C109, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_Route101To109[] = {
    {sString_WK_SCENE_FIELD_R101, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R102, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R103, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R104, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R105, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R106, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R107, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R108, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R109, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_Route110To118[] = {
    {sString_WK_SCENE_FIELD_R110, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R111, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R112, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R113, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R114, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R115, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R116, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R117, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R118, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_Route119To127[] = {
    {sString_WK_SCENE_FIELD_R119, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R120, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R121, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R122, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R123, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R124, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R125, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R126, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R127, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_Route128To134[] = {
    {sString_WK_SCENE_FIELD_R128, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R129, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R130, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R131, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R132, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R133, DummyMenuAction},
    {sString_WK_SCENE_FIELD_R134, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_RoomTown[] = {
    {sString_WK_SCENE_T101_R0101, DummyMenuAction},
    {sString_WK_SCENE_T101_R0102, DummyMenuAction},
    {sString_WK_SCENE_T101_R0301, DummyMenuAction},
    {sString_WK_SCENE_T101_R0201, DummyMenuAction},
    {sString_WK_SCENE_T101_R0202, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_RoomCity[] = {
    {sString_WK_SCENE_C101_R0201, DummyMenuAction},
    {sString_WK_SCENE_C104_R0103, DummyMenuAction},
    {sString_WK_SCENE_C103_R0101, DummyMenuAction},
    {sString_WK_SCENE_C106_R0202, DummyMenuAction},
    {sString_WK_SCENE_C106_R0401, DummyMenuAction},
    {sString_WK_SCENE_C101_R0601, DummyMenuAction},
    {sString_WK_SCENE_C102_R0501, DummyMenuAction},
    {sString_WK_SCENE_C104_R0102, DummyMenuAction},
    {sString_WK_SCENE_C107_R0501, DummyMenuAction}
};

static const struct MenuAction sMenuActions_SaveWork_Dungeon[] = {
    {sString_WK_SCENE_CAVE_D0601, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D0201, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D1206, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D1111, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D0701, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D0808, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D1602, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D0101, DummyMenuAction},
    {sString_WK_SCENE_CAVE_D1301, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C457C[] = {8, 9, 9, 9, 9, 7, 6, 9, 9};

static const u16 gUnknown_Debug_083C4586[][9] = {
    {VAR_LITTLEROOT_STATE, VAR_ROUTE102_ACCESSIBLE, 0x4052, VAR_LAVARIDGE_RIVAL_STATE, VAR_CURRENT_SECRET_BASE, 0x4055, 0x4056, VAR_OLDALE_STATE},
    {VAR_PETALBURG_STATE, VAR_SLATEPORT_STATE, 0x4059, VAR_RUSTBORO_STATE, 0x405B, 0x405C, 0x405D, VAR_SOOTOPOLIS_STATE, 0x405F},
    {VAR_ROUTE101_STATE, 0x4061, VAR_ROUTE103_STATE, 0x4063, 0x4064, 0x4065, 0x4066, 0x4067, 0x4068},
    {VAR_ROUTE110_STATE, 0x406A, 0x406B, 0x406C, 0x406D, 0x406E, VAR_ROUTE116_STATE, 0x4070, VAR_ROUTE118_STATE},
    {VAR_ROUTE119_STATE, 0x4073, VAR_ROUTE121_STATE, 0x4075, 0x4076, 0x4077, 0x4078, 0x4079, 0x407A},
    {VAR_ROUTE128_STATE, 0x407C, 0x407D, 0x407E, 0x407F, 0x4080, 0x4081},
    {VAR_LITTLEROOT_HOUSES_STATE, 0x4083, VAR_BIRCH_LAB_STATE, VAR_LITTLEROOT_HOUSES_STATE_2, VAR_LITTLEROOT_RIVAL_STATE, VAR_PACIFIDLOG_TM_RECEIVED_DAY},
    {VAR_PETALBURG_GYM_STATE, VAR_DEVON_CORP_3F_STATE, VAR_MAUVILLE_GYM_STATE, VAR_LILYCOVE_MUSEUM_2F_STATE, VAR_LILYCOVE_FAN_CLUB_STATE, VAR_SLATEPORT_HARBOR_STATE, VAR_SLATEPORT_MUSEUM_1F_STATE, VAR_FOSSIL_RESURRECTION_STATE, VAR_STEVENS_HOUSE_STATE},
    {VAR_PETALBURG_WOODS_STATE, VAR_RUSTURF_TUNNEL_STATE, VAR_CAVE_OF_ORIGIN_B4F_STATE, VAR_SEAFLOOR_CAVERN_STATE, 0x40A8, VAR_MT_PYRE_STATE, VAR_NEW_MAUVILLE_STATE, VAR_METEOR_FALLS_STATE, VAR_VICTORY_ROAD_1F_STATE}
};

static const u8 gUnknown_Debug_083C4628[] = _("LOCALWORK0???8");
static const u8 gUnknown_Debug_083C4635[] = _("LOCALWORK9???15");

static const struct MenuAction gUnknown_Debug_083C4644[] = {
    {gUnknown_Debug_083C4628, debug_sub_808E754},
    {gUnknown_Debug_083C4635, debug_sub_808E7AC}
};

static const u8 gUnknown_Debug_083C4654[] = _("LOCALWORK0");
static const u8 gUnknown_Debug_083C465F[] = _("LOCALWORK1");
static const u8 gUnknown_Debug_083C466A[] = _("LOCALWORK2");
static const u8 gUnknown_Debug_083C4675[] = _("LOCALWORK3");
static const u8 gUnknown_Debug_083C4680[] = _("LOCALWORK4");
static const u8 gUnknown_Debug_083C468B[] = _("LOCALWORK5");
static const u8 gUnknown_Debug_083C4696[] = _("LOCALWORK6");
static const u8 gUnknown_Debug_083C46A1[] = _("LOCALWORK7");
static const u8 gUnknown_Debug_083C46AC[] = _("LOCALWORK8");

static const u8 gUnknown_Debug_083C46B7[] = _("LOCALWORK9");
static const u8 gUnknown_Debug_083C46C2[] = _("LOCALWORK10");
static const u8 gUnknown_Debug_083C46CE[] = _("LOCALWORK11");
static const u8 gUnknown_Debug_083C46DA[] = _("LOCALWORK12");
static const u8 gUnknown_Debug_083C46E6[] = _("LOCALWORK13");
static const u8 gUnknown_Debug_083C46F2[] = _("LOCALWORK14");
static const u8 gUnknown_Debug_083C46FE[] = _("LOCALWORK15");

static const struct MenuAction gUnknown_Debug_083C470C[] = {
    {gUnknown_Debug_083C4654, DummyMenuAction},
    {gUnknown_Debug_083C465F, DummyMenuAction},
    {gUnknown_Debug_083C466A, DummyMenuAction},
    {gUnknown_Debug_083C4675, DummyMenuAction},
    {gUnknown_Debug_083C4680, DummyMenuAction},
    {gUnknown_Debug_083C468B, DummyMenuAction},
    {gUnknown_Debug_083C4696, DummyMenuAction},
    {gUnknown_Debug_083C46A1, DummyMenuAction},
    {gUnknown_Debug_083C46AC, DummyMenuAction}
};

static const struct MenuAction gUnknown_Debug_083C4754C[] = {
    {gUnknown_Debug_083C46B7, DummyMenuAction},
    {gUnknown_Debug_083C46C2, DummyMenuAction},
    {gUnknown_Debug_083C46CE, DummyMenuAction},
    {gUnknown_Debug_083C46DA, DummyMenuAction},
    {gUnknown_Debug_083C46E6, DummyMenuAction},
    {gUnknown_Debug_083C46F2, DummyMenuAction},
    {gUnknown_Debug_083C46FE, DummyMenuAction}
};

static const u8 gUnknown_Debug_083C478C[] = {9, 7};

static const u16 gUnknown_Debug_083C478E[][9] = {
    {VAR_TEMP_0, VAR_TEMP_1, VAR_TEMP_2, VAR_TEMP_3, VAR_TEMP_4, VAR_TEMP_5, VAR_TEMP_6, VAR_TEMP_7, VAR_TEMP_8},
    {VAR_TEMP_9, VAR_TEMP_A, VAR_TEMP_B, VAR_TEMP_C, VAR_TEMP_D, VAR_TEMP_E, VAR_TEMP_F}
};

#if (ENGLISH && REVISION == 0)
static const u8 gUnknown_Debug_083C47B2[] = _("?????????");
static const u8 gUnknown_Debug_083C47B8[] = _("?????????1");
static const u8 gUnknown_Debug_083C47BF[] = _("?????????2");
static const u8 gUnknown_Debug_083C47C6[] = _("?????????3");
static const u8 gUnknown_Debug_083C47CD[] = _("?????????4");
static const u8 gUnknown_Debug_083C47D4[] = _("?????????5");
static const u8 gUnknown_Debug_083C47DB[] = _("?????????6");
static const u8 gUnknown_Debug_083C47E2[] = _("?????????7");
static const u8 gUnknown_Debug_083C47E9[] = _("?????????8");
#else
static const u8 gUnknown_Debug_083C47B2[] = _("Level");
static const u8 gUnknown_Debug_083C47B8[] = _("Scene1");
static const u8 gUnknown_Debug_083C47BF[] = _("Scene2");
static const u8 gUnknown_Debug_083C47C6[] = _("Scene3");
static const u8 gUnknown_Debug_083C47CD[] = _("Scene4");
static const u8 gUnknown_Debug_083C47D4[] = _("Scene5");
static const u8 gUnknown_Debug_083C47DB[] = _("Scene6");
static const u8 gUnknown_Debug_083C47E2[] = _("Scene7");
static const u8 gUnknown_Debug_083C47E9[] = _("Scene8");
#endif

static const struct MenuAction gUnknown_Debug_083C47F0[] = {
    {gUnknown_Debug_083C47B8, DummyMenuAction},
    {gUnknown_Debug_083C47BF, DummyMenuAction},
    {gUnknown_Debug_083C47C6, DummyMenuAction},
    {gUnknown_Debug_083C47CD, DummyMenuAction},
    {gUnknown_Debug_083C47D4, DummyMenuAction},
    {gUnknown_Debug_083C47DB, DummyMenuAction},
    {gUnknown_Debug_083C47E2, DummyMenuAction},
    {gUnknown_Debug_083C47E9, DummyMenuAction}
};

#if (ENGLISH && REVISION == 0)
static const u8 gUnknown_Debug_083C4830[] = _("????????????????????????");
#else
static const u8 gUnknown_Debug_083C4830[] = _("Trick Master");
#endif

static const u8 gUnknown_Debug_083C483D[] = _("Hidden MASTER");
static const u8 gUnknown_Debug_083C484B[] = _("Inside the HOUSE");
static const u8 gUnknown_Debug_083C485C[] = _("Pass a reward");
static const u8 gUnknown_Debug_083C486A[] = _("Rig a trick");
static const u8 gUnknown_Debug_083C4876[] = _("MASTER is gone");

static const struct MenuAction gUnknown_Debug_083C4888[] = {
    {gUnknown_Debug_083C483D, DummyMenuAction},
    {gUnknown_Debug_083C484B, DummyMenuAction},
    {gUnknown_Debug_083C485C, DummyMenuAction},
    {gUnknown_Debug_083C486A, DummyMenuAction},
    {gUnknown_Debug_083C4876, DummyMenuAction}
};

#if (ENGLISH && REVISION == 0)
static const u8 sDummyNickname[] = _("??????????????????");
static const u8 sDummyTrainerName[] = _("?????????????????????");
#else
static const u8 sDummyNickname[] = _("PMNICKNAME");
static const u8 sDummyTrainerName[] = _("BREEDER");
#endif

bool8 InitTomomichiDebugWindow(void)
{
    InitDebugWindow();
    return FALSE;
}

static void debug_sub_808B868(void)
{
    CB2_ReturnToFieldContinueScriptPlayMapMusic();
}

static bool8 InitDebugWindow(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 13, 15);
    Menu_PrintItems(1, 1, ARRAY_COUNT(sMenuActions_TopMenu), sMenuActions_TopMenu);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_TopMenu), sTopMenuCursorPos, 12);
    gMenuCallback = TopMenu_HandleInput;
    return FALSE;
}

static bool8 TopMenu_HandleInput(void)
{
    if (gMain.newKeys & DPAD_UP)
    {
        PlaySE(SE_SELECT);
        sTopMenuCursorPos = Menu_MoveCursor(-1);
    }
    if (gMain.newKeys & DPAD_DOWN)
    {
        PlaySE(SE_SELECT);
        sTopMenuCursorPos = Menu_MoveCursor(+1);
    }
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        return sMenuActions_TopMenu[sTopMenuCursorPos].func();
    }
    if (gMain.newKeys & (B_BUTTON | START_BUTTON))
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static bool8 ContestGraphics(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 20, 11);
    Menu_PrintText(sString_ContestMenuTitle, 1, 1);
    Menu_PrintItems(2, 3, ARRAY_COUNT(sMenuActions_ContestPicTest), sMenuActions_ContestPicTest);
    InitMenu(0, 1, 3, ARRAY_COUNT(sMenuActions_ContestPicTest), 0, 19);
    gMenuCallback = ContestGraphics_HandleInput;
    sPicTest_Species = SPECIES_BULBASAUR;
    sPicTest_OTID = 28467;
    sPicTest_Personality = 0;
    sPicTest_ContestType = 1;
    return FALSE;
}

static bool8 ArtMusGraphics(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 20, 11);
    Menu_PrintText(sString_Contest_ArtMuseumTitle, 1, 1);
    Menu_PrintItems(2, 3, ARRAY_COUNT(sMenuActions_ArtMuseumPicTest), sMenuActions_ArtMuseumPicTest);
    InitMenu(0, 1, 3, ARRAY_COUNT(sMenuActions_ArtMuseumPicTest), 0, 19);
    gMenuCallback = ArtMusGraphics_HandleInput;
    sPicTest_Species = SPECIES_BULBASAUR;
    sPicTest_OTID = 28467;
    sPicTest_Personality = 0;
    sPicTest_MuseumArtTitleType = 1;
    return FALSE;
}

static bool8 PreviewData(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 20, 11);
    Menu_PrintText(sString_Contest_PreviewTitle, 1, 1);
    Menu_PrintItems(2, 3, ARRAY_COUNT(sMenuActions_PreviewPicTest), sMenuActions_PreviewPicTest);
    InitMenu(0, 1, 3, ARRAY_COUNT(sMenuActions_PreviewPicTest), 0, 19);
    gMenuCallback = PreviewData_HandleInput;
    sPicTest_Species = SPECIES_BULBASAUR;
    sPicTest_OTID = 28467;
    sPicTest_Personality = 0;
    sPicTest_PreviewType = 1;
    return FALSE;
}

static bool8 TrickHouse(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 7);
    Menu_PrintText(sString_TrickRelated, 1, 1);
    Menu_PrintItems(2, 3, ARRAY_COUNT(sMenuActions_TrickRelated), sMenuActions_TrickRelated);
    InitMenu(0, 1, 3, ARRAY_COUNT(sMenuActions_TrickRelated), sTrickRelatedMenuCursorPos, 23);
    gMenuCallback = TrickHouse_HandleInput;
    return FALSE;
}

static bool8 ControlEvents(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 5);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlEvents), sMenuActions_ControlEvents);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlEvents), sControlEventsCursorPos, 23);
    gMenuCallback = ControlEvents_HandleInput;
    return FALSE;
}

static bool8 ControlFlags(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 15);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlFlags), sMenuActions_ControlFlags);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlFlags), sControlFlagsCursorPos, 23);
    gMenuCallback = ControlFlags_HandleInput;
    return FALSE;
}

static bool8 ControlWorks(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 13);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlWorks), sMenuActions_ControlWorks);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlWorks), sControlWORKCursorPos, 23);
    gMenuCallback = ControlWorks_HandleInput;
    return FALSE;
}

static bool8 ContestGraphics_HandleInput(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    switch (cursorPos)
    {
        case 0:
            PicTest_SelectPokemon();
            break;
        case 1:
            PicTest_SelectPersonality();
            break;
        case 2:
            ContestPicTest_SelectContestType();
            break;
    }
    PicTest_Redraw(0);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    if (input == 3)
    {
        gMenuCallback = sMenuActions_ContestPicTest[3].func;
        return FALSE;
    }
    return FALSE;
}

static bool8 ArtMusGraphics_HandleInput(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    switch (cursorPos)
    {
        case 0:
            PicTest_SelectPokemon();
            break;
        case 1:
            PicTest_SelectPersonality();
            break;
        case 2:
            MuseumArtPicTest_SelectTitleType();
            break;
    }
    PicTest_Redraw(1);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    if (input == 3)
    {
        gMenuCallback = sMenuActions_ArtMuseumPicTest[3].func;
        return FALSE;
    }
    return FALSE;
}

static bool8 PreviewData_HandleInput(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    switch (cursorPos)
    {
        case 0:
            PicTest_SelectPokemon();
            break;
        case 1:
            PicTest_SelectPersonality();
            break;
        case 2:
            PreviewPicTest_SelectType();
            break;
    }
    PicTest_Redraw(2);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    if (input == 3)
    {
        gMenuCallback = sMenuActions_PreviewPicTest[3].func;
        return FALSE;
    }
    return FALSE;
}

static bool8 TrickHouse_HandleInput(void)
{
    if (gMain.newKeys & DPAD_UP)
    {
        PlaySE(SE_SELECT);
        sTrickRelatedMenuCursorPos = Menu_MoveCursor(-1);
    }
    if (gMain.newKeys & DPAD_DOWN)
    {
        PlaySE(SE_SELECT);
        sTrickRelatedMenuCursorPos = Menu_MoveCursor(+1);
    }
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        return sMenuActions_TrickRelated[sTrickRelatedMenuCursorPos].func();
    }
    if (gMain.newKeys & (B_BUTTON | START_BUTTON))
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static bool8 ControlEvents_HandleInput(void)
{
    if (gMain.newKeys & DPAD_UP)
    {
        PlaySE(SE_SELECT);
        sControlEventsCursorPos = Menu_MoveCursor(-1);
    }
    if (gMain.newKeys & DPAD_DOWN)
    {
        PlaySE(SE_SELECT);
        sControlEventsCursorPos = Menu_MoveCursor(+1);
    }
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        return sMenuActions_ControlEvents[sControlEventsCursorPos].func();
    }
    if (gMain.newKeys & (B_BUTTON | START_BUTTON))
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static bool8 ControlFlags_HandleInput(void)
{
    if (gMain.newKeys & DPAD_UP)
    {
        PlaySE(SE_SELECT);
        sControlFlagsCursorPos = Menu_MoveCursor(-1);
    }
    if (gMain.newKeys & DPAD_DOWN)
    {
        PlaySE(SE_SELECT);
        sControlFlagsCursorPos = Menu_MoveCursor(+1);
    }
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        return sMenuActions_ControlFlags[sControlFlagsCursorPos].func();
    }
    if (gMain.newKeys & (B_BUTTON | START_BUTTON))
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static bool8 ControlWorks_HandleInput(void)
{
    if (gMain.newKeys & DPAD_UP)
    {
        PlaySE(SE_SELECT);
        sControlWORKCursorPos = Menu_MoveCursor(-1);
    }
    if (gMain.newKeys & DPAD_DOWN)
    {
        PlaySE(SE_SELECT);
        sControlWORKCursorPos = Menu_MoveCursor(+1);
    }
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        return sMenuActions_ControlWorks[sControlWORKCursorPos].func();
    }
    if (gMain.newKeys & (B_BUTTON | START_BUTTON))
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static bool8 ControlEvents_InitSubmenu1(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 19);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlEvents_Events1), sMenuActions_ControlEvents_Events1);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlEvents_Events1), 0, 27);
    gMenuCallback = ControlEvents_Events1_HandleInput;
    return FALSE;
}

static bool8 ControlEvents_InitSubmenu2(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 13);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlEvents_Events2), sMenuActions_ControlEvents_Events2);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlEvents_Events2), 0, 27);
    gMenuCallback = ControlEvents_Events2_HandleInput;
    return FALSE;
}

static bool8 ControlEvents_Events1_HandleInput(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = sMenuActions_ControlEvents_Events1[input].func;
    return FALSE;
}

static bool8 ControlEvents_Events2_HandleInput(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = sMenuActions_ControlEvents_Events2[input].func;
    return FALSE;
}

static bool8 CallScript_DoHallOfFame(void)
{
    ScriptContext1_SetupScript(DebugScript_081C1CFE);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveCoinCaseIfNotAlreadyOwned(void)
{
    ScriptContext1_SetupScript(DebugScript_081C1D07);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_SetOldaleStateAfterRoute103Rival(void)
{
    ScriptContext1_SetupScript(DebugScript_081C1D1E);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_OpenNewMauville(void)
{
    ScriptContext1_SetupScript(DebugScript_081C1D24);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveSSTicketAndDoHallOfFame(void)
{
    ScriptContext1_SetupScript(DebugScript_081C1D2A);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveKyogreEgg(void)
{
    ScriptContext1_SetupScript(DebugScript_081C1D35);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveAllItems(void)
{
    ScriptContext1_SetupScript(DebugScript_081C1D46);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveAllDecorations(void)
{
    ScriptContext1_SetupScript(DebugScript_081C221F);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveAllCoins(void)
{
    ScriptContext1_SetupScript(DebugScript_081C23E2);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_OpenSootopolisGym(void)
{
    ScriptContext1_SetupScript(DebugScript_081C23E6);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_SetMoneyTo0(void)
{
    ScriptContext1_SetupScript(DebugScript_081C23F6);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_FillPartyWithBarboach(void)
{
    ScriptContext1_SetupScript(DebugScript_081C2482);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_FillPartyWithShroomish(void)
{
    ScriptContext1_SetupScript(DebugScript_081C23FD);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveBarboachEgg(void)
{
    ScriptContext1_SetupScript(DebugScript_081C2518);
    CloseMenu();
    return TRUE;
}

static bool8 CallScript_GiveShroomishEgg(void)
{
    ScriptContext1_SetupScript(DebugScript_081C2507);
    CloseMenu();
    return TRUE;
}

static bool8 ContestGraphics_Show(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB(0, 0, 0));
    gMenuCallback = debug_sub_808C280;
    return FALSE;
}

static bool8 debug_sub_808C280(void)
{
    if (!UpdatePaletteFade())
    {
        CloseMenu();
        PrepareDebugOverlayBeforeShowingContestPainting(0);
        SetMainCallback2(CB2_ContestPainting);
        gMain.savedCallback = debug_sub_808B868;
        return TRUE;
    }
    return FALSE;
}

static bool8 MuseumGraphics_Show(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB(0, 0, 0));
    gMenuCallback = debug_sub_808C2E4;
    return FALSE;
}

static bool8 debug_sub_808C2E4(void)
{
    if (!UpdatePaletteFade())
    {
        CloseMenu();
        PrepareDebugOverlayBeforeShowingContestPainting(1);
        SetMainCallback2(CB2_ContestPainting);
        gMain.savedCallback = debug_sub_808B868;
        return TRUE;
    }
    return FALSE;
}

static bool8 ControlFlags_EventFlag_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 19);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2828), gUnknown_Debug_083C2828);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2828), 0, 27);
    gMenuCallback = debug_sub_808C36C;
    return FALSE;
}

static bool8 debug_sub_808C36C(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C2828[input].func;
    return FALSE;
}

static bool8 debug_sub_808C3B0(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2938) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2938), gUnknown_Debug_083C2938);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2938), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C408(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2A48) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2A48), gUnknown_Debug_083C2A48);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2A48), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C460(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2B4C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2B4C), gUnknown_Debug_083C2B4C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2B4C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 2;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C4B8(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2C80) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2C80), gUnknown_Debug_083C2C80);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2C80), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 3;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C510(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2D8C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2D8C), gUnknown_Debug_083C2D8C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2D8C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 4;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C568(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2EB0) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2EB0), gUnknown_Debug_083C2EB0);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2EB0), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 5;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C5C0(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2FE0) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2FE0), gUnknown_Debug_083C2FE0);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2FE0), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 6;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C618(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C3100) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C3100), gUnknown_Debug_083C3100);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C3100), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 7;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C670(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 3 + 1);
    Menu_PrintItems(2, 1, 3, gUnknown_Debug_083C3194);
    InitMenu(0, 1, 1, 3, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 8;
    gMenuCallback = debug_sub_808C6C8;
    return FALSE;
}

static bool8 debug_sub_808C6C8(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808C714(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808C764(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808C714(u8 whichMenu, u8 cursorPos)
{
    if (gMain.newKeys & R_BUTTON)
    {
        if (!FlagGet(gUnknown_Debug_83C31E6[whichMenu][cursorPos]))
            FlagSet(gUnknown_Debug_83C31E6[whichMenu][cursorPos]);
        else
            FlagClear(gUnknown_Debug_83C31E6[whichMenu][cursorPos]);
    }
}

static void debug_sub_808C764(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C31DC[whichMenu]; i++)
    {
        PrintBool(28, 2 * i + 1, FlagGet(gUnknown_Debug_83C31E6[whichMenu][i]) ? 1 : 0);
    }
}

static bool8 ControlFlags_VanishFlag_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 19);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1CE8), gUnknown_Debug_083C1CE8);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1CE8), 0, 27);
    gMenuCallback = debug_sub_808C818;
    return FALSE;
}

static bool8 debug_sub_808C818(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C1CE8[input].func;
    return FALSE;
}

static bool8 debug_sub_808C85C(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1E0C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1E0C), gUnknown_Debug_083C1E0C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1E0C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808C8B4(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1F38) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1F38), gUnknown_Debug_083C1F38);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1F38), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808C90C(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C206C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C206C), gUnknown_Debug_083C206C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C206C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 2;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808C964(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2190) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2190), gUnknown_Debug_083C2190);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2190), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 3;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808C9BC(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2264) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2264), gUnknown_Debug_083C2264);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2264), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 4;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808CA14(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C2370) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C2370), gUnknown_Debug_083C2370);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C2370), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 5;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808CA6C(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C248C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C248C), gUnknown_Debug_083C248C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C248C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 6;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808CAC4(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C259C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C259C), gUnknown_Debug_083C259C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C259C), 0, 27);
    sFlagAndVarTest_WhichSubmenu = 7;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808CB1C(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C26C8) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C26C8), gUnknown_Debug_083C26C8);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C26C8), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 8;
    gMenuCallback = debug_sub_808CB74;
    return FALSE;
}

static bool8 debug_sub_808CB74(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808CBC0(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808CC10(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808CBC0(u8 whichMenu, u8 cursorPos)
{
    if (gMain.newKeys & R_BUTTON)
    {
        if (!FlagGet(gUnknown_Debug_083C271A[whichMenu][cursorPos]))
            FlagSet(gUnknown_Debug_083C271A[whichMenu][cursorPos]);
        else
            FlagClear(gUnknown_Debug_083C271A[whichMenu][cursorPos]);
    }
}

static void debug_sub_808CC10(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C2710[whichMenu]; i++)
    {
        PrintBool(28, 2 * i + 1, FlagGet(gUnknown_Debug_083C271A[whichMenu][i]) ? 1 : 0);
    }
}

static bool8 ControlFlags_TrainerFlag_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 2 * ARRAY_COUNT(gUnknown_Debug_083C1ADC) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1ADC), gUnknown_Debug_083C1ADC);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1ADC), 0, 27);
    gMenuCallback = debug_sub_808CCC4;
    return FALSE;
}

static bool8 debug_sub_808CCC4(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C1ADC[input].func;
    return FALSE;
}

static bool8 debug_sub_808CD08(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1B7C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1B7C), gUnknown_Debug_083C1B7C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1B7C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808CE10;
    return FALSE;
}

static bool8 debug_sub_808CD60(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1BF0) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1BF0), gUnknown_Debug_083C1BF0);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1BF0), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808CE10;
    return FALSE;
}

static bool8 debug_sub_808CDB8(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1C2C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1C2C), gUnknown_Debug_083C1C2C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1C2C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 2;
    gMenuCallback = debug_sub_808CE10;
    return FALSE;
}

static bool8 debug_sub_808CE10(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808CE5C(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808CEAC(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808CE5C(u8 whichMenu, u8 cursorPos)
{
    if (gMain.newKeys & R_BUTTON)
    {
        if (!FlagGet(gUnknown_Debug_083C1C38[whichMenu][cursorPos]))
            FlagSet(gUnknown_Debug_083C1C38[whichMenu][cursorPos]);
        else
            FlagClear(gUnknown_Debug_083C1C38[whichMenu][cursorPos]);
    }
}

static void debug_sub_808CEAC(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C1C34[whichMenu]; i++)
    {
        PrintBool(28, 2 * i + 1, FlagGet(gUnknown_Debug_083C1C38[whichMenu][i]) ? 1 : 0);
    }
}

static bool8 ControlFlags_SysFlag_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 2 * ARRAY_COUNT(gUnknown_Debug_083C1330) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1330), gUnknown_Debug_083C1330);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1330), 0, 27);
    gMenuCallback = debug_sub_808CF60;
    return FALSE;
}

static bool8 debug_sub_808CF60(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C1330[input].func;
    return FALSE;
}

static bool8 debug_sub_808CFA4(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C13D8) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C13D8), gUnknown_Debug_083C13D8);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C13D8), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808CFFC(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1465) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1465), gUnknown_Debug_083C1465);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1465), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D054(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1503) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1503), gUnknown_Debug_083C1503);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1503), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 2;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D0AC(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C158A) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C158A), gUnknown_Debug_083C158A);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C158A), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 3;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D104(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1647) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1647), gUnknown_Debug_083C1647);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1647), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 4;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D15C(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1712) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1712), gUnknown_Debug_083C1712);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1712), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 5;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D1B4(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C17F8) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C17F8), gUnknown_Debug_083C17F8);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C17F8), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 6;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D20C(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 7 + 1);
    Menu_PrintItems(2, 1, 7, gUnknown_Debug_083C18B8);
    InitMenu(0, 1, 1, 7, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 7;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D264(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 5 + 1);
    Menu_PrintItems(2, 1, 5, gDebug_0x83C1974);
    InitMenu(0, 1, 1, 5, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 8;
    gMenuCallback = debug_sub_808D2BC;
    return FALSE;
}

static bool8 debug_sub_808D2BC(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808D308(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808D358(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808D308(u8 whichMenu, u8 cursorPos)
{
    if (gMain.newKeys & R_BUTTON)
    {
        if (!FlagGet(gUnknown_Debug_083C19C6[whichMenu][cursorPos]))
            FlagSet(gUnknown_Debug_083C19C6[whichMenu][cursorPos]);
        else
            FlagClear(gUnknown_Debug_083C19C6[whichMenu][cursorPos]);
    }
}

static void debug_sub_808D358(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C19BC[whichMenu]; i++)
    {
        PrintBool(28, 2 * i + 1, FlagGet(gUnknown_Debug_083C19C6[whichMenu][i]) ? 1 : 0);
    }
}

static bool8 ControlFlags_FH_OBJ_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 2 * ARRAY_COUNT(sMenuActions_ControlFlags_FH_OBJ) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlFlags_FH_OBJ), sMenuActions_ControlFlags_FH_OBJ);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlFlags_FH_OBJ), 0, 27);
    gMenuCallback = ControlFlags_FH_OBJ_HandleInput;
    return FALSE;
}

static bool8 ControlFlags_FH_OBJ_HandleInput(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = sMenuActions_ControlFlags_FH_OBJ[input].func;
    return FALSE;
}

static bool8 ControlFlags_FH_OBJ00_08_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_ControlFlags_FH_OBJ00_08) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlFlags_FH_OBJ00_08), sMenuActions_ControlFlags_FH_OBJ00_08);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlFlags_FH_OBJ00_08), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = ControlFlags_FH_OBJ_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlFlags_FH_OBJ09_15_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 7 + 1);
    Menu_PrintItems(2, 1, 7, sMenuActions_ControlFlags_FH_OBJ09_15);
    InitMenu(0, 1, 1, 7, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = ControlFlags_FH_OBJ_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlFlags_FH_OBJ_Subsubmenu_HandleInput(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    ControlFlags_FH_OBJ_FlagToggle(sFlagAndVarTest_WhichSubmenu, cursorPos);
    ControlFlags_FH_OBJ_UpdateDisplay(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void ControlFlags_FH_OBJ_FlagToggle(u8 whichMenu, u8 cursorPos)
{
    if (gMain.newKeys & R_BUTTON)
    {
        if (!FlagGet(sControlFlags_FH_OBJ_FlagsArrays[whichMenu][cursorPos]))
            FlagSet(sControlFlags_FH_OBJ_FlagsArrays[whichMenu][cursorPos]);
        else
            FlagClear(sControlFlags_FH_OBJ_FlagsArrays[whichMenu][cursorPos]);
    }
}

static void ControlFlags_FH_OBJ_UpdateDisplay(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < sControlFlags_FH_OBJ_CountsArray[whichMenu]; i++)
    {
        PrintBool(28, 2 * i + 1, FlagGet(sControlFlags_FH_OBJ_FlagsArrays[whichMenu][i]) ? 1 : 0);
    }
}

static bool8 ControlFlags_FH_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 2 * ARRAY_COUNT(gUnknown_Debug_083C11CC) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C11CC), gUnknown_Debug_083C11CC);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C11CC), 0, 27);
    gMenuCallback = debug_sub_808D650;
    return FALSE;
}

static bool8 debug_sub_808D650(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C11CC[input].func;
    return FALSE;
}

static bool8 debug_sub_808D694(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1212) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1212), gUnknown_Debug_083C1212);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1212), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808D744;
    return FALSE;
}

static bool8 debug_sub_808D6EC(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 7 + 1);
    Menu_PrintItems(2, 1, 7, gUnknown_Debug_083C1288);
    InitMenu(0, 1, 1, 7, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808D744;
    return FALSE;
}

static bool8 debug_sub_808D744(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808D790(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808D7E0(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808D790(u8 whichMenu, u8 cursorPos)
{
    if (gMain.newKeys & R_BUTTON)
    {
        if (!FlagGet(gUnknown_Debug_083C12D2[whichMenu][cursorPos]))
            FlagSet(gUnknown_Debug_083C12D2[whichMenu][cursorPos]);
        else
            FlagClear(gUnknown_Debug_083C12D2[whichMenu][cursorPos]);
    }
}

static void debug_sub_808D7E0(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C12D0[whichMenu]; i++)
    {
        PrintBool(28, 2 * i + 1, FlagGet(gUnknown_Debug_083C12D2[whichMenu][i]) ? 1 : 0);
    }
}

static bool8 ControlFlags_BallVanishFlag_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 28, 2 * ARRAY_COUNT(gUnknown_Debug_083C1A78) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1A78), gUnknown_Debug_083C1A78);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1A78), 0, 27);
    gMenuCallback = debug_sub_808D894;
    return FALSE;
}

static bool8 debug_sub_808D894(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C1A78[input].func;
    return FALSE;
}

static bool8 debug_sub_808D8D8(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C1A9C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C1A9C), gUnknown_Debug_083C1A9C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C1A9C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808D930;
    return FALSE;
}

static bool8 debug_sub_808D930(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808D97C(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808D9CC(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808D97C(u8 whichMenu, u8 cursorPos)
{
    if (gMain.newKeys & R_BUTTON)
    {
        if (!FlagGet(gUnknown_Debug_083C1AAE[whichMenu][cursorPos]))
            FlagSet(gUnknown_Debug_083C1AAE[whichMenu][cursorPos]);
        else
            FlagClear(gUnknown_Debug_083C1AAE[whichMenu][cursorPos]);
    }
}

static void debug_sub_808D9CC(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C1AAC[whichMenu]; i++)
    {
        PrintBool(28, 2 * i + 1, FlagGet(gUnknown_Debug_083C1AAE[whichMenu][i]) ? 1 : 0);
    }
}

static bool8 ControlWorks_AnsWork_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_ControlEvents_AnsWork) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlEvents_AnsWork), sMenuActions_ControlEvents_AnsWork);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlEvents_AnsWork), 0, 28);
    gMenuCallback = ControlWorks_AnsWork_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_AnsWork_HandleInput(void)
{
    s8 input = Menu_ProcessInput();
    /*s8 cursorPos = */Menu_GetCursorPos();

    ControlWorks_AnsWork_AdjustRESULT();
    ControlWorks_AnsWork_PrintRESULT();
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void ControlWorks_AnsWork_PrintRESULT(void)
{
    PrintUnsignedShort(24, 1, gSpecialVar_Result);
}

static void ControlWorks_AnsWork_AdjustRESULT(void)
{
    u16 delta;

    if (gMain.newKeys & R_BUTTON)
    {
        delta = +1;
    }
    else if (gMain.newKeys & L_BUTTON)
    {
        delta = -1;
    }
    else
        return;
    gSpecialVar_Result += delta;
}

static bool8 ControlWorks_SaveWork_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 2 * ARRAY_COUNT(sMenuAction_ControlWorks_SaveWork) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuAction_ControlWorks_SaveWork), sMenuAction_ControlWorks_SaveWork);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuAction_ControlWorks_SaveWork), 0, 23);
    gMenuCallback = ControlWorks_SaveWork_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_HandleInput(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = sMenuAction_ControlWorks_SaveWork[input].func;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_Town_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_Town) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_Town), sMenuActions_SaveWork_Town);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_Town), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_City_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_City) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_City), sMenuActions_SaveWork_City);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_City), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_Route101To109_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_Route101To109) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route101To109), sMenuActions_SaveWork_Route101To109);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route101To109), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 2;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_Route110To118_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_Route110To118) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route110To118), sMenuActions_SaveWork_Route110To118);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route110To118), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 3;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_Route119To127_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_Route119To127) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route119To127), sMenuActions_SaveWork_Route119To127);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route119To127), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 4;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_Route128To134_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_Route128To134) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route128To134), sMenuActions_SaveWork_Route128To134);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_Route128To134), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 5;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_RoomTown_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 6 + 1);
    Menu_PrintItems(2, 1, 6, sMenuActions_SaveWork_RoomTown); // overflows into the next menu
    InitMenu(0, 1, 1, 6, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 6;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_RoomCity_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_RoomCity) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_RoomCity), sMenuActions_SaveWork_RoomCity);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_RoomCity), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 7;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_Dungeon_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(sMenuActions_SaveWork_Dungeon) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_SaveWork_Dungeon), sMenuActions_SaveWork_Dungeon);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_SaveWork_Dungeon), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 8;
    gMenuCallback = ControlWorks_SaveWork_Subsubmenu_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWork_Subsubmenu_HandleInput(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808DF64(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808DF04(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808DF04(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C457C[whichMenu]; i++)
    {
        PrintUnsignedShort(24, 2 * i + 1, VarGet(gUnknown_Debug_083C4586[whichMenu][i]));
    }
}

static void debug_sub_808DF64(u8 whichMenu, u8 cursorPos)
{
    u16 delta;

    if (gMain.newKeys & R_BUTTON)
        delta = +1;
    else if (gMain.newKeys & L_BUTTON)
        delta = -1;
    else
        return;
    VarSet(gUnknown_Debug_083C4586[whichMenu][cursorPos], VarGet(gUnknown_Debug_083C4586[whichMenu][cursorPos]) + delta);
}

static bool8 ControlWorks_SaveWorkPart2_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 2 * ARRAY_COUNT(sMenuActions_ControlWorks_SaveWorkPart2) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(sMenuActions_ControlWorks_SaveWorkPart2), sMenuActions_ControlWorks_SaveWorkPart2);
    InitMenu(0, 1, 1, ARRAY_COUNT(sMenuActions_ControlWorks_SaveWorkPart2), 0, 23);
    gMenuCallback = ControlWorks_SaveWorkPart2_HandleInput;
    return FALSE;
}

static bool8 ControlWorks_SaveWorkPart2_HandleInput(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = sMenuActions_ControlWorks_SaveWorkPart2[input].func;
    return FALSE;
}

static bool8 ControlWorks_SaveWorkPart2_SP_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 6 + 1);
    Menu_PrintItems(2, 1, 6, gUnknown_Debug_083C3AA0);
    InitMenu(0, 1, 1, 6, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808E264;
    return FALSE;
}

static bool8 ControlWorks_SaveWorkPart2_RoomR110Part1TrickHouse_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 5 + 1);
    Menu_PrintItems(2, 1, 5, gUnknown_Debug_83C3AE0);
    InitMenu(0, 1, 1, 5, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808E264;
    return FALSE;
}

static bool8 ControlWorks_SaveWorkPart2_RoomR110Part2_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_83C3B28) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_83C3B28), gUnknown_Debug_83C3B28);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_83C3B28), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 2;
    gMenuCallback = debug_sub_808E264;
    return FALSE;
}

static bool8 ControlWorks_SaveWorkPart2_RoomLoad_InitSubsubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 2 + 1);
    Menu_PrintItems(2, 1, 2, gUnknown_Debug_83C3B70);
    InitMenu(0, 1, 1, 2, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 3;
    gMenuCallback = debug_sub_808E264;
    return FALSE;
}

static bool8 debug_sub_808E1B4(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_83C3BB8) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_83C3BB8), gUnknown_Debug_83C3BB8);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_83C3BB8), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 4;
    gMenuCallback = debug_sub_808E264;
    return FALSE;
}

static bool8 debug_sub_808E20C(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * 6 + 1);
    Menu_PrintItems(2, 1, 6, gUnknown_Debug_83C3C00);
    InitMenu(0, 1, 1, 6, 0, 28);
    sFlagAndVarTest_WhichSubmenu = 5;
    gMenuCallback = debug_sub_808E264;
    return FALSE;
}

static bool8 debug_sub_808E264(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808E310(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808E2B0(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808E2B0(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < sControlWorks_SaveWork_CountsArray[whichMenu]; i++)
    {
        PrintUnsignedShort(24, 2 * i + 1, VarGet(sControlWorks_SaveWork_ItemArrays[whichMenu][i]));
    }
}

static void debug_sub_808E310(u8 whichMenu, u8 cursorPos)
{
    u16 delta;

    if (gMain.newKeys & R_BUTTON)
        delta = +1;
    else if (gMain.newKeys & L_BUTTON)
        delta = -1;
    else
        return;
    VarSet(sControlWorks_SaveWork_ItemArrays[whichMenu][cursorPos], VarGet(sControlWorks_SaveWork_ItemArrays[whichMenu][cursorPos]) + delta);
}

static bool8 ControlWorks_SysWork_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 2 * ARRAY_COUNT(gUnknown_Debug_083C32AC) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C32AC), gUnknown_Debug_083C32AC);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C32AC), 0, 23);
    gMenuCallback = debug_sub_808E3BC;
    return FALSE;
}

static bool8 debug_sub_808E3BC(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C32AC[input].func;
    return FALSE;
}

static bool8 debug_sub_808E400(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C347C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C347C), gUnknown_Debug_083C347C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C347C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808E5B8;
    return FALSE;
}

static bool8 debug_sub_808E458(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C3494) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C3494), gUnknown_Debug_083C3494);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C3494), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808E5B8;
    return FALSE;
}

static bool8 debug_sub_808E4B0(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C34A4) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C34A4), gUnknown_Debug_083C34A4);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C34A4), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 2;
    gMenuCallback = debug_sub_808E5B8;
    return FALSE;
}

static bool8 debug_sub_808E508(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C34D4) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C34D4), gUnknown_Debug_083C34D4);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C34D4), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 3;
    gMenuCallback = debug_sub_808E5B8;
    return FALSE;
}

static bool8 debug_sub_808E560(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C351C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C351C), gUnknown_Debug_083C351C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C351C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 4;
    gMenuCallback = debug_sub_808E5B8;
    return FALSE;
}

static bool8 debug_sub_808E5B8(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808E604(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808E660(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808E604(u8 whichMenu, u8 cursorPos)
{
    u16 delta;

    if (gMain.newAndRepeatedKeys & R_BUTTON)
        delta = +1;
    else if (gMain.newAndRepeatedKeys & L_BUTTON)
        delta = -1;
    else
        return;
    VarSet(gUnknown_Debug_083C354A[whichMenu][cursorPos], VarGet(gUnknown_Debug_083C354A[whichMenu][cursorPos]) + delta);
}

static void debug_sub_808E660(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C3544[whichMenu]; i++)
    {
        PrintUnsignedShort(24, 2 * i + 1, VarGet(gUnknown_Debug_083C354A[whichMenu][i]));
    }
}

static bool8 ControlWorks_LocalWork_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 2 * ARRAY_COUNT(gUnknown_Debug_083C4644) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C4644), gUnknown_Debug_083C4644);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C4644), 0, 23);
    gMenuCallback = debug_sub_808E710;
    return FALSE;
}

static bool8 debug_sub_808E710(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C4644[input].func;
    return FALSE;
}

static bool8 debug_sub_808E754(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C470C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C470C), gUnknown_Debug_083C470C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C470C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808E804;
    return FALSE;
}

static bool8 debug_sub_808E7AC(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C4754C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C4754C), gUnknown_Debug_083C4754C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C4754C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808E804;
    return FALSE;
}

static bool8 debug_sub_808E804(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808E850(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808E8AC(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808E850(u8 whichMenu, u8 cursorPos)
{
    u16 delta;

    if (gMain.newKeys & R_BUTTON)
        delta = +1;
    else if (gMain.newKeys & L_BUTTON)
        delta = -1;
    else
        return;
    VarSet(gUnknown_Debug_083C478E[whichMenu][cursorPos], VarGet(gUnknown_Debug_083C478E[whichMenu][cursorPos]) + delta);
}

static void debug_sub_808E8AC(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C478C[whichMenu]; i++)
    {
        PrintUnsignedShort(24, 2 * i + 1, VarGet(gUnknown_Debug_083C478E[whichMenu][i]));
    }
}

static bool8 ControlWorks_ObjWork_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 24, 2 * ARRAY_COUNT(gUnknown_Debug_083C35C4) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C35C4), gUnknown_Debug_083C35C4);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C35C4), 0, 23);
    gMenuCallback = debug_sub_808E95C;
    return FALSE;
}

static bool8 debug_sub_808E95C(void)
{
    s8 input = Menu_ProcessInput();

    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    gMenuCallback = gUnknown_Debug_083C35C4[input].func;
    return FALSE;
}

static bool8 debug_sub_808E9A0(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C369C) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C369C), gUnknown_Debug_083C369C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C369C), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 0;
    gMenuCallback = debug_sub_808EA50;
    return FALSE;
}

static bool8 debug_sub_808E9F8(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 29, 2 * ARRAY_COUNT(gUnknown_Debug_083C36E4) + 1);
    Menu_PrintItems(2, 1, ARRAY_COUNT(gUnknown_Debug_083C36E4), gUnknown_Debug_083C36E4);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C36E4), 0, 28);
    sFlagAndVarTest_WhichSubmenu = 1;
    gMenuCallback = debug_sub_808EA50;
    return FALSE;
}

static bool8 debug_sub_808EA50(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    debug_sub_808EAFC(sFlagAndVarTest_WhichSubmenu, cursorPos);
    debug_sub_808EA9C(sFlagAndVarTest_WhichSubmenu);
    if (input == -2)
        return FALSE;
    if (input == -1)
    {
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

static void debug_sub_808EA9C(u8 whichMenu)
{
    u8 i;

    for (i = 0; i < gUnknown_Debug_083C371C[whichMenu]; i++)
    {
        PrintUnsignedShort(24, 2 * i + 1, VarGet(gUnknown_Debug_083C371E[whichMenu][i]));
    }
}

static void debug_sub_808EAFC(u8 whichMenu, u8 cursorPos)
{
    u16 delta;

    if (gMain.newKeys & R_BUTTON)
        delta = +1;
    else if (gMain.newKeys & L_BUTTON)
        delta = -1;
    else
        return;
    VarSet(gUnknown_Debug_083C371E[whichMenu][cursorPos], VarGet(gUnknown_Debug_083C371E[whichMenu][cursorPos]) + delta);
}

static bool8 TrickRelated_Level_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 12, 2 * ARRAY_COUNT(gUnknown_Debug_083C47F0) + 3);
    Menu_PrintText(gUnknown_Debug_083C47B2, 1, 1);
    Menu_PrintItems(2, 3, ARRAY_COUNT(gUnknown_Debug_083C47F0), gUnknown_Debug_083C47F0);
    InitMenu(0, 1, 3, ARRAY_COUNT(gUnknown_Debug_083C47F0), 0, 11);
    gMenuCallback = debug_sub_808EC10;
    return FALSE;
}

static bool8 TrickRelated_TrickMaster_InitSubmenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 13, 2 * ARRAY_COUNT(gUnknown_Debug_083C4888) + 3);
    Menu_PrintText(gUnknown_Debug_083C4830, 1, 1);
    Menu_PrintItems(2, 3, ARRAY_COUNT(gUnknown_Debug_083C4888), gUnknown_Debug_083C4888);
    InitMenu(0, 1, 3, ARRAY_COUNT(gUnknown_Debug_083C4888), 0, 12);
    gMenuCallback = debug_sub_808EC5C;
    return FALSE;
}

static bool8 debug_sub_808EC10(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    if (input == -2)
    {
        return FALSE;
    }
    if (input == -1)
    {
        return FALSE;
    }
    gSaveBlock1.vars[VAR_TRICK_HOUSE_ROOMS_COMPLETED - VARS_START] = cursorPos;
    CloseMenu();
    return TRUE;
}

static bool8 debug_sub_808EC5C(void)
{
    s8 input = Menu_ProcessInput();
    s8 cursorPos = Menu_GetCursorPos();

    if (input == -2)
    {
        return FALSE;
    }
    if (input == -1)
    {
        return FALSE;
    }
    VarSet(VAR_TRICK_HOUSE_ENTRANCE_STATE_3, cursorPos);
    CloseMenu();
    return TRUE;
}

static bool8 PreviewGraphics_Show(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB(0, 0, 0));
    gMenuCallback = debug_sub_808ECD0;
    return FALSE;
}

static bool8 debug_sub_808ECD0(void)
{
    if (!UpdatePaletteFade())
    {
        CloseMenu();
        PrepareDebugOverlayBeforeShowingContestPainting(2);
        SetMainCallback2(CB2_ContestPainting);
        gMain.savedCallback = debug_sub_808B868;
        return TRUE;
    }
    return FALSE;
}

static bool8 DummyMenuAction(void)
{
    return FALSE;
}

static void PicTest_SelectPokemon(void)
{
    if (gMain.newAndRepeatedKeys & DPAD_LEFT)
    {
        if (sPicTest_Species != SPECIES_BULBASAUR)
            sPicTest_Species--;
    }
    if (gMain.newAndRepeatedKeys & DPAD_RIGHT)
    {
        if (sPicTest_Species != SPECIES_CHIMECHO)
            sPicTest_Species++;
    }
    if (gMain.newAndRepeatedKeys & L_BUTTON)
    {
        if (sPicTest_Species >= SPECIES_BULBASAUR + 10)
            sPicTest_Species -= 10;
        else
            sPicTest_Species = SPECIES_BULBASAUR;
    }
    if (gMain.newAndRepeatedKeys & R_BUTTON)
    {
        if (sPicTest_Species <= SPECIES_CHIMECHO - 10)
            sPicTest_Species += 10;
        else
            sPicTest_Species = SPECIES_CHIMECHO;
    }
}

static void PicTest_SelectPersonality(void)
{
    if (gMain.newAndRepeatedKeys & DPAD_LEFT)
    {
        if (sPicTest_Personality != 0)
            sPicTest_Personality--;
    }
    if (gMain.newAndRepeatedKeys & DPAD_RIGHT)
    {
        if (sPicTest_Personality != UINT32_MAX)
            sPicTest_Personality++;
    }
    if (gMain.newAndRepeatedKeys & L_BUTTON)
    {
        if (sPicTest_Personality >= 0x10)
            sPicTest_Personality -= 0x10;
        else
            sPicTest_Personality = 0;
    }
    if (gMain.newAndRepeatedKeys & R_BUTTON)
    {
        if (sPicTest_Personality <= UINT32_MAX - 0x10)
            sPicTest_Personality += 0x10;
        else
            sPicTest_Personality = UINT32_MAX;
    }
    if ((gMain.newKeys & (L_BUTTON | R_BUTTON)) == (L_BUTTON | R_BUTTON))
    {
        sPicTest_Personality = UINT32_MAX;
    }
}

static void ContestPicTest_SelectContestType(void)
{
    if (gMain.newAndRepeatedKeys & DPAD_LEFT)
    {
        if (sPicTest_ContestType != CONTEST_COOL + 1)
            sPicTest_ContestType--;
    }
    if (gMain.newAndRepeatedKeys & DPAD_RIGHT)
    {
        if (sPicTest_ContestType != CONTEST_TOUGH + 1)
            sPicTest_ContestType++;
    }
    if (gMain.newAndRepeatedKeys & L_BUTTON)
        sPicTest_ContestType = CONTEST_COOL + 1;
    if (gMain.newAndRepeatedKeys & R_BUTTON)
        sPicTest_ContestType = CONTEST_TOUGH + 1;
}

static void MuseumArtPicTest_SelectTitleType(void)
{
    if (gMain.newAndRepeatedKeys & DPAD_LEFT)
    {
        if (sPicTest_MuseumArtTitleType != 1)
            sPicTest_MuseumArtTitleType--;
    }
    if (gMain.newAndRepeatedKeys & DPAD_RIGHT)
    {
        if (sPicTest_MuseumArtTitleType != 15)
            sPicTest_MuseumArtTitleType++;
    }
    if (gMain.newAndRepeatedKeys & L_BUTTON)
    {
        if (sPicTest_MuseumArtTitleType >= 11)
            sPicTest_MuseumArtTitleType -= 10;
        else
            sPicTest_MuseumArtTitleType = 0; // Causes underflow when pressing left on the dpad shortly thereafter.
    }
    if (gMain.newAndRepeatedKeys & R_BUTTON)
    {
        if (sPicTest_MuseumArtTitleType <= 5)
            sPicTest_MuseumArtTitleType += 10;
        else
            sPicTest_MuseumArtTitleType = 15;
    }
}

static void PreviewPicTest_SelectType(void)
{
    if (gMain.newAndRepeatedKeys & DPAD_LEFT)
    {
        if (sPicTest_PreviewType != 1)
            sPicTest_PreviewType--;
    }
    if (gMain.newAndRepeatedKeys & DPAD_RIGHT)
    {
        if (sPicTest_PreviewType != 15)
            sPicTest_PreviewType++;
    }
    if (gMain.newAndRepeatedKeys & L_BUTTON)
    {
        if (sPicTest_PreviewType >= 11)
            sPicTest_PreviewType -= 10;
        else
            sPicTest_PreviewType = 0; // Causes underflow when pressing left on the dpad shortly thereafter.
    }
    if (gMain.newAndRepeatedKeys & R_BUTTON)
    {
        if (sPicTest_PreviewType <= 5)
            sPicTest_PreviewType += 10;
        else
            sPicTest_PreviewType = 15;
    }
}

#ifdef NONMATCHING
static void PicTest_Redraw(u8 a0)
{
    u8 i;
    u8 digit;
    u16 species;

    switch (a0)
    {
        case 0:
        case 1:
        case 2:
            for (i = 0; i < 8; i++)
            {
                digit = (sPicTest_Personality >> (4 * (7 - i))) & 0xf;
                if (digit < 10)
                    sPicTest_StringBuffer[i] = digit + CHAR_0;
                else
                    sPicTest_StringBuffer[i] = digit + CHAR_A - 10;
            }
            sPicTest_StringBuffer[i] = EOS;
            Menu_PrintText(sPicTest_StringBuffer, 12, 5);
            break;
    }
    for (i = 0; i < POKEMON_NAME_LENGTH; i++)
    {
        sPicTest_StringBuffer[i + 1] = CHAR_SPACE;
    }

    for (i = 0, species = sPicTest_Species; gSpeciesNames[species][i] != EOS && i < POKEMON_NAME_LENGTH; i++)
    {
        sPicTest_StringBuffer[i + 1] = gSpeciesNames[species][i];
    }

    sPicTest_StringBuffer[0] = 0xB1;
    sPicTest_StringBuffer[POKEMON_NAME_LENGTH + 1] = 0xB2;
    sPicTest_StringBuffer[POKEMON_NAME_LENGTH + 2] = EOS;
    switch (a0)
    {
        case 0:
        case 1:
        case 2:
            Menu_PrintText(sPicTest_StringBuffer, 8, 1);
            break;
        default:
            Menu_PrintText(sPicTest_StringBuffer, 12, 1);
            break;
    }
    sPicTest_StringBuffer[3] = EOS;
    sPicTest_StringBuffer[0] = sPicTest_Species / 100 + CHAR_0;
    sPicTest_StringBuffer[1] = (sPicTest_Species % 100) / 10 + CHAR_0;
    sPicTest_StringBuffer[2] = sPicTest_Species % 10 + CHAR_0;
    Menu_PrintText(sPicTest_StringBuffer, 12, 3);

    switch (a0)
    {
        case 0:
            sPicTest_StringBuffer[0] = sPicTest_ContestType / 100 + CHAR_0;
            sPicTest_StringBuffer[1] = (sPicTest_ContestType % 100) / 10 + CHAR_0;
            sPicTest_StringBuffer[2] = sPicTest_ContestType % 10 + CHAR_0;
            Menu_PrintText(sPicTest_StringBuffer, 12, 7);
            break;
        case 1:
            sPicTest_StringBuffer[0] = sPicTest_MuseumArtTitleType / 100 + CHAR_0;
            sPicTest_StringBuffer[1] = (sPicTest_MuseumArtTitleType % 100) / 10 + CHAR_0;
            sPicTest_StringBuffer[2] = sPicTest_MuseumArtTitleType % 10 + CHAR_0;
            Menu_PrintText(sPicTest_StringBuffer, 12, 7);
            break;
        case 2:
            sPicTest_StringBuffer[0] = sPicTest_PreviewType / 100 + CHAR_0;
            sPicTest_StringBuffer[1] = (sPicTest_PreviewType % 100) / 10 + CHAR_0;
            sPicTest_StringBuffer[2] = sPicTest_PreviewType % 10 + CHAR_0;
            Menu_PrintText(sPicTest_StringBuffer, 12, 7);
            break;
    }
}
#else
NAKED void PicTest_Redraw(u8 a0)
{
    asm("\tpush\t{r4, r5, r6, r7, lr}\n"
        "\tmov\tr7, r8\n"
        "\tpush\t{r7}\n"
        "\tlsl\tr0, r0, #0x18\n"
        "\tlsr\tr6, r0, #0x18\n"
        "\tcmp\tr6, #0x2\n"
        "\tbgt\t._653\t@cond_branch\n"
        "\tcmp\tr6, #0\n"
        "\tblt\t._653\t@cond_branch\n"
        "\tmov\tr3, #0x0\n"
        "\tldr\tr0, ._656       @ sPicTest_Personality\n"
        "\tmov\tr8, r0\n"
        "\tldr\tr4, ._656 + 4   @ sPicTest_StringBuffer\n"
        "\tmov\tr7, #0x7\n"
        "\tmov\tr5, #0xf\n"
        "._658:\n"
        "\tsub\tr0, r7, r3\n"
        "\tlsl\tr0, r0, #0x2\n"
        "\tmov\tr1, r8\n"
        "\tldr\tr2, [r1]\n"
        "\tLSR\tr2, r0\n"
        "\tand\tr2, r2, r5\n"
        "\tcmp\tr2, #0x9\n"
        "\tbhi\t._654\t@cond_branch\n"
        "\tadd\tr1, r3, r4\n"
        "\tadd\tr0, r2, #0\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tb\t._655\n"
        "._657:\n"
        "\t.align\t2, 0\n"
        "._656:\n"
        "\t.word\tsPicTest_Personality\n"
        "\t.word\tsPicTest_StringBuffer\n"
        "._654:\n"
        "\tadd\tr1, r3, r4\n"
        "\tadd\tr0, r2, #0\n"
        "\tsub\tr0, r0, #0x4f\n"
        "._655:\n"
        "\tstrb\tr0, [r1]\n"
        "\tadd\tr0, r3, #1\n"
        "\tlsl\tr0, r0, #0x18\n"
        "\tlsr\tr3, r0, #0x18\n"
        "\tcmp\tr3, #0x7\n"
        "\tbls\t._658\t@cond_branch\n"
        "\tldr\tr0, ._666       @ sPicTest_StringBuffer\n"
        "\tmov\tr1, #0xff\n"
        "\tstrb\tr1, [r0, #0x8]\n"
        "\tmov\tr1, #0xc\n"
        "\tmov\tr2, #0x5\n"
        "\tbl\tMenu_PrintText\n"
        "._653:\n"
        "\tmov\tr3, #0x0\n"
        "\tldr\tr7, ._666       @ sPicTest_StringBuffer\n"
        "\tldr\tr5, ._666 + 4   @ sPicTest_Species\n"
        "\tldr\tr2, ._666 + 8   @ gSpeciesNames\n"
        "\tmov\tr8, r2\n"
        "\tadd\tr4, r7, #0\n"
        "\tmov\tr2, #0x0\n"
        "._659:\n"
        "\tadd\tr1, r3, #1\n"
        "\tadd\tr0, r1, r4\n"
        "\tstrb\tr2, [r0]\n"
        "\tlsl\tr1, r1, #0x18\n"
        "\tlsr\tr3, r1, #0x18\n"
        "\tcmp\tr3, #0x9\n"
        "\tbls\t._659\t@cond_branch\n"
        "\tmov\tr3, #0x0\n"
        "\tldrh\tr2, [r5]\n"
        "\tmov\tr0, #0xb\n"
        "\tadd\tr1, r2, #0\n"
        "\tmul\tr1, r1, r0\n"
        "\tmov\tr2, r8\n"
        "\tadd\tr0, r1, r2\n"
        "\tldrb\tr0, [r0]\n"
        "\tcmp\tr0, #0xff\n"
        "\tbeq\t._661\t@cond_branch\n"
        "\tldr\tr0, ._666       @ sPicTest_StringBuffer\n"
        "\tmov\tip, r0\n"
        "\tmov\tr5, r8\n"
        "\tadd\tr4, r1, #0\n"
        "._662:\n"
        "\tadd\tr1, r3, #1\n"
        "\tmov\tr0, ip\n"
        "\tadd\tr2, r1, r0\n"
        "\tadd\tr0, r3, r4\n"
        "\tadd\tr0, r0, r5\n"
        "\tldrb\tr0, [r0]\n"
        "\tstrb\tr0, [r2]\n"
        "\tlsl\tr1, r1, #0x18\n"
        "\tlsr\tr3, r1, #0x18\n"
        "\tadd\tr0, r3, r4\n"
        "\tadd\tr0, r0, r5\n"
        "\tldrb\tr0, [r0]\n"
        "\tcmp\tr0, #0xff\n"
        "\tbeq\t._661\t@cond_branch\n"
        "\tcmp\tr3, #0x9\n"
        "\tbls\t._662\t@cond_branch\n"
        "._661:\n"
        "\tmov\tr0, #0xb1\n"
        "\tstrb\tr0, [r7]\n"
        "\tmov\tr0, #0xb2\n"
        "\tstrb\tr0, [r7, #0xb]\n"
        "\tmov\tr0, #0xff\n"
        "\tstrb\tr0, [r7, #0xc]\n"
        "\tcmp\tr6, #0x2\n"
        "\tbgt\t._664\t@cond_branch\n"
        "\tcmp\tr6, #0\n"
        "\tblt\t._664\t@cond_branch\n"
        "\tadd\tr0, r7, #0\n"
        "\tmov\tr1, #0x8\n"
        "\tmov\tr2, #0x1\n"
        "\tbl\tMenu_PrintText\n"
        "\tb\t._665\n"
        "._667:\n"
        "\t.align\t2, 0\n"
        "._666:\n"
        "\t.word\tsPicTest_StringBuffer\n"
        "\t.word\tsPicTest_Species\n"
        "\t.word\tgSpeciesNames\n"
        "._664:\n"
        "\tldr\tr0, ._672       @ sPicTest_StringBuffer\n"
        "\tmov\tr1, #0xc\n"
        "\tmov\tr2, #0x1\n"
        "\tbl\tMenu_PrintText\n"
        "._665:\n"
        "\tldr\tr5, ._672       @ sPicTest_StringBuffer\n"
        "\tmov\tr0, #0xff\n"
        "\tstrb\tr0, [r5, #0x3]\n"
        "\tldr\tr4, ._672 + 4   @ sPicTest_Species\n"
        "\tldrh\tr0, [r4]\n"
        "\tmov\tr1, #0x64\n"
        "\tbl\t__udivsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5]\n"
        "\tldrh\tr0, [r4]\n"
        "\tmov\tr1, #0x64\n"
        "\tbl\t__umodsi3\n"
        "\tlsl\tr0, r0, #0x10\n"
        "\tlsr\tr0, r0, #0x10\n"
        "\tmov\tr1, #0xa\n"
        "\tbl\t__udivsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5, #0x1]\n"
        "\tldrh\tr0, [r4]\n"
        "\tmov\tr1, #0xa\n"
        "\tbl\t__umodsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5, #0x2]\n"
        "\tadd\tr0, r5, #0\n"
        "\tmov\tr1, #0xc\n"
        "\tmov\tr2, #0x3\n"
        "\tbl\tMenu_PrintText\n"
        "\tcmp\tr6, #0x1\n"
        "\tbeq\t._668\t@cond_branch\n"
        "\tcmp\tr6, #0x1\n"
        "\tbgt\t._669\t@cond_branch\n"
        "\tcmp\tr6, #0\n"
        "\tbeq\t._670\t@cond_branch\n"
        "\tb\t._679\n"
        "._673:\n"
        "\t.align\t2, 0\n"
        "._672:\n"
        "\t.word\tsPicTest_StringBuffer\n"
        "\t.word\tsPicTest_Species\n"
        "._669:\n"
        "\tcmp\tr6, #0x2\n"
        "\tbeq\t._674\t@cond_branch\n"
        "\tb\t._679\n"
        "._670:\n"
        "\tldr\tr4, ._677       @ sPicTest_ContestType\n"
        "\tb\t._676\n"
        "._678:\n"
        "\t.align\t2, 0\n"
        "._677:\n"
        "\t.word\tsPicTest_ContestType\n"
        "._668:\n"
        "\tldr\tr4, ._680       @ sPicTest_MuseumArtTitleType\n"
        "._676:\n"
        "\tldrb\tr0, [r4]\n"
        "\tmov\tr1, #0x64\n"
        "\tbl\t__udivsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5]\n"
        "\tldrb\tr0, [r4]\n"
        "\tmov\tr1, #0x64\n"
        "\tbl\t__umodsi3\n"
        "\tlsl\tr0, r0, #0x18\n"
        "\tlsr\tr0, r0, #0x18\n"
        "\tmov\tr1, #0xa\n"
        "\tbl\t__udivsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5, #0x1]\n"
        "\tldrb\tr0, [r4]\n"
        "\tmov\tr1, #0xa\n"
        "\tbl\t__umodsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5, #0x2]\n"
        "\tadd\tr0, r5, #0\n"
        "\tmov\tr1, #0xc\n"
        "\tmov\tr2, #0x7\n"
        "\tbl\tMenu_PrintText\n"
        "\tb\t._679\n"
        "._681:\n"
        "\t.align\t2, 0\n"
        "._680:\n"
        "\t.word\tsPicTest_MuseumArtTitleType\n"
        "._674:\n"
        "\tldr\tr4, ._682       @ sPicTest_PreviewType\n"
        "\tldrb\tr0, [r4]\n"
        "\tmov\tr1, #0x64\n"
        "\tbl\t__udivsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5]\n"
        "\tldrb\tr0, [r4]\n"
        "\tmov\tr1, #0x64\n"
        "\tbl\t__umodsi3\n"
        "\tlsl\tr0, r0, #0x18\n"
        "\tlsr\tr0, r0, #0x18\n"
        "\tmov\tr1, #0xa\n"
        "\tbl\t__udivsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5, #0x1]\n"
        "\tldrb\tr0, [r4]\n"
        "\tmov\tr1, #0xa\n"
        "\tbl\t__umodsi3\n"
        "\tadd\tr0, r0, #0xa1\n"
        "\tstrb\tr0, [r5, #0x2]\n"
        "\tadd\tr0, r5, #0\n"
        "\tmov\tr1, #0xc\n"
        "\tmov\tr2, #0x7\n"
        "\tbl\tMenu_PrintText\n"
        "._679:\n"
        "\tpop\t{r3}\n"
        "\tmov\tr8, r3\n"
        "\tpop\t{r4, r5, r6, r7}\n"
        "\tpop\t{r0}\n"
        "\tbx\tr0\n"
        "._683:\n"
        "\t.align\t2, 0\n"
        "._682:\n"
        "\t.word\tsPicTest_PreviewType");
}
#endif // NONMATCHING

static void PrepareDebugOverlayBeforeShowingContestPainting(u8 a0)
{
    struct ContestWinner *contestEntry = &eCurContestWinner;
    contestEntry->species = sPicTest_Species;
    contestEntry->otId = sPicTest_OTID;
    contestEntry->personality = sPicTest_Personality;
    switch (a0)
    {
        case 0:
            eCurContestWinnerIsForArtist = FALSE;
            eCurContestWinnerSaveIdx = 0;
            contestEntry->contestCategory = sPicTest_ContestType - 1;
            StringCopy(contestEntry->trainerName, sDummyTrainerName);
            StringCopy(contestEntry->nickname, sDummyNickname);
            break;
        case 1:
            eCurContestWinnerIsForArtist = FALSE;
            eCurContestWinnerSaveIdx = 8;
            contestEntry->contestCategory = sPicTest_MuseumArtTitleType - 1;
            StringCopy(contestEntry->nickname, sDummyNickname);
            break;
        case 2:
            eCurContestWinnerIsForArtist = TRUE;
            eCurContestWinnerSaveIdx = 8;
            contestEntry->contestCategory = sPicTest_PreviewType - 1;
            break;
        case 3:
            eCurContestWinnerIsForArtist = FALSE;
            eCurContestWinnerSaveIdx = 8;
            contestEntry->contestCategory = 0;
            StringCopy(contestEntry->nickname, sDummyNickname);
            break;
        case 4:
            eCurContestWinnerIsForArtist = FALSE;
            eCurContestWinnerSaveIdx = 8;
            contestEntry->contestCategory = 3;
            StringCopy(contestEntry->nickname, sDummyNickname);
            break;
        case 5:
            eCurContestWinnerIsForArtist = FALSE;
            eCurContestWinnerSaveIdx = 8;
            contestEntry->contestCategory = 9;
            StringCopy(contestEntry->nickname, sDummyNickname);
            break;
    }
}

static void PrintBool(u8 a0, u8 a1, bool8 a2)
{
    if (a2 == FALSE)
        sPicTest_StringBuffer[0] = CHAR_0;
    else
        sPicTest_StringBuffer[0] = CHAR_0 + 1;
    sPicTest_StringBuffer[1] = EOS;
    Menu_PrintText(sPicTest_StringBuffer, a0, a1);
}

static void PrintUnsignedShort(u8 a0, u8 a1, u16 a2)
{
    sPicTest_StringBuffer[0] = a2 / 10000 + CHAR_0;
    sPicTest_StringBuffer[1] = (a2 % 10000) / 1000 + CHAR_0;
    sPicTest_StringBuffer[2] = (a2 % 1000) / 100 + CHAR_0;
    sPicTest_StringBuffer[3] = (a2 % 100) / 10 + CHAR_0;
    sPicTest_StringBuffer[4] = a2 % 10 + CHAR_0;
    sPicTest_StringBuffer[5] = EOS;
    Menu_PrintText(sPicTest_StringBuffer, a0, a1);
}

void debug_nullsub_66(void)
{
// This function likely serves as the entry point into this file.
}

#endif // DEBUG
