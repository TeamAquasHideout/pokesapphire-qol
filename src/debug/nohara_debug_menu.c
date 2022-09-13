#if DEBUG
#include "global.h"
#include "constants/flags.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/items.h"
#include "main.h"
#include "menu.h"
#include "start_menu.h"
#include "tv.h"
#include "event_data.h"
#include "string_util.h"
#include "field_specials.h"
#include "sound.h"

static u8 gDebug_03000724;
static u8 gDebug_03000725;
static u8 gDebug_03000726;

bool8 debug_sub_808F414(void);
bool8 NoharaDebugMenu_TV(void);
bool8 debug_sub_808F4AC(void);
void debug_sub_808F4EC(void);
bool8 debug_sub_808F560(void);
bool8 debug_sub_808F594(void);
bool8 debug_sub_808F5D8(void);
bool8 debug_sub_808F648(void);
void debug_sub_808F6BC(void);
void debug_sub_808F7B4(void);
bool8 debug_sub_808F8AC(void);
void debug_sub_808F8CC(void);
bool8 debug_sub_808F93C(void);
void debug_sub_808FA88(u8, u8);
bool8 debug_sub_808FEBC(void);
void debug_sub_808FECC(void);
bool8 debug_sub_808FF3C(void);
void debug_sub_8090080(u8, u8);
bool8 debug_sub_80900AC(void);
bool8 NoharaDebugMenu_Fan(void);
bool8 debug_sub_80901A4(void);
bool8 debug_sub_80901E4(void);
bool8 debug_sub_80901F8(void);
bool8 debug_sub_8090238(void);
bool8 debug_sub_809029C(void);
bool8 debug_sub_80902E4(void);
bool8 debug_sub_80902FC(void);
bool8 debug_sub_8090310(void);
bool8 debug_sub_8090324(void);
bool8 debug_sub_8090338(void);
bool8 debug_sub_8090278(void);
bool8 NoharaDebugMenu_BattleVSDad(void);
bool8 NoharaDebugMenu_DadAfterBattle(void);
bool8 NoharaDebugMenu_SootopolisCity(void);
bool8 NoharaDebugMenu_Embark(void);
bool8 NoharaDebugMenu_Yes9999(void);
bool8 NoharaDebugMenu_LegendsFlagOn(void);
bool8 NoharaDebugMenu_AddNumWinningStreaks(void);

const u8 gUnknown_Debug_083C48C4[] = _("TV");
const u8 gUnknown_Debug_083C48C7[] = DTR("Fan", "LILYCOVE TRAINER FAN CLUB");
const u8 gUnknown_Debug_083C48CB[] = _("Battle (vs Dad)");
const u8 gUnknown_Debug_083C48DB[] = _("Dad after battle");
const u8 gUnknown_Debug_083C48EC[] = _("SOOTOPOLIS CITY");
const u8 gUnknown_Debug_083C48FC[] = DTR("Embark", "Reset Mr. BRINEY");
const u8 gUnknown_Debug_083C4903[] = _("Yes 9999");
const u8 gUnknown_Debug_083C490C[] = _("Legends flag ON");
const u8 gUnknown_Debug_083C491C[] = _("Add num of winning streaks");

const struct MenuAction gUnknown_Debug_083C4938[] = {
    {gUnknown_Debug_083C48C4, NoharaDebugMenu_TV},
    {gUnknown_Debug_083C48C7, NoharaDebugMenu_Fan},
    {gUnknown_Debug_083C48CB, NoharaDebugMenu_BattleVSDad},
    {gUnknown_Debug_083C48DB, NoharaDebugMenu_DadAfterBattle},
    {gUnknown_Debug_083C48EC, NoharaDebugMenu_SootopolisCity},
    {gUnknown_Debug_083C48FC, NoharaDebugMenu_Embark},
    {gUnknown_Debug_083C4903, NoharaDebugMenu_Yes9999},
    {gUnknown_Debug_083C490C, NoharaDebugMenu_LegendsFlagOn},
    {gUnknown_Debug_083C491C, NoharaDebugMenu_AddNumWinningStreaks}
};

bool8 InitNoharaDebugMenu(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 19, 19);
    Menu_PrintItems(1, 1, ARRAY_COUNT(gUnknown_Debug_083C4938), gUnknown_Debug_083C4938);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C4938), 0, 18);
    gMenuCallback = debug_sub_808F414;
    return FALSE;
}

bool8 debug_sub_808F414(void)
{
    s8 input = Menu_ProcessInput();
    switch (input)
    {
        default:
            gMenuCallback = gUnknown_Debug_083C4938[input].func;
            return FALSE;
        case -2:
            return FALSE;
        case -1:
            CloseMenu();
            return TRUE;
    }
}

#if (ENGLISH && REVISION == 0)
const u8 gUnknown_Debug_083C4980[] = _("ひみつがたを すぐみれるように    ひだりキーで\n"
                                       "データタイプを へんこうしますか？  きりかえ");
#else
const u8 gUnknown_Debug_083C4980[] = _("Want to change data type{CLEAR_TO 143}Press　Left\n"
                                       "to see secret type now？{CLEAR_TO 143}to　switch");
#endif

const u8 gUnknown_Debug_083C49CA[] = _("Choose the TV data you wish to\n"
                                       "create to check a transmission。");

const u8 gUnknown_Debug_083C4A09[] = DTR("ほうそうの　はっせいりつを　セット\n"
                                         "してください　？ぶんの1に　なります",
                                         "Please set the transmission frequency\n"
                                         "Part 1");

const u8 gUnknown_Debug_083C4A2E[] = _("SURVEY");
const u8 gUnknown_Debug_083C4A35[] = _("RECENT HAPPENINGS");
const u8 gUnknown_Debug_083C4A47[] = _("Pokémon FAN CLUB");
const u8 gUnknown_Debug_083C4A58[] = DTR("ジム", "GYM");
const u8 gUnknown_Debug_083C4A5B[] = _("OUTBREAKS");
const u8 gUnknown_Debug_083C4A65[] = _("NAME RATER");
const u8 gUnknown_Debug_083C4A70[] = _("CONTEST");
const u8 gUnknown_Debug_083C4A78[] = _("INTRODUCTION");
const u8 gUnknown_Debug_083C4A85[] = _("SHOPPING");
const u8 gUnknown_Debug_083C4A8E[] = _("MISFORTUNE");
const u8 gUnknown_Debug_083C4A99[] = _("FISHING");
const u8 gUnknown_Debug_083C4AA1[] = _("MEMORABLE DAY");
const u8 gUnknown_Debug_083C4AAF[] = _("BRAVO TRAINER");

const u8 gUnknown_Debug_083C4ABD[] = {
    TVSHOW_FAN_CLUB_LETTER,
    TVSHOW_RECENT_HAPPENINGS,
    TVSHOW_PKMN_FAN_CLUB_OPINIONS,
    TVSHOW_MASS_OUTBREAK,
    TVSHOW_NAME_RATER_SHOW,
    TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE,
    TVSHOW_POKEMON_TODAY_CAUGHT,
    TVSHOW_SMART_SHOPPER,
    TVSHOW_POKEMON_TODAY_FAILED,
    TVSHOW_FISHING_ADVICE,
    TVSHOW_WORLD_OF_MASTERS,
    TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE
};

const u8 *const gUnknown_Debug_083C4ACC[] = {
    gUnknown_Debug_083C4A2E,
    gUnknown_Debug_083C4A35,
    gUnknown_Debug_083C4A47,
    gUnknown_Debug_083C4A5B,
    gUnknown_Debug_083C4A65,
    gUnknown_Debug_083C4A70,
    gUnknown_Debug_083C4A78,
    gUnknown_Debug_083C4A85,
    gUnknown_Debug_083C4A8E,
    gUnknown_Debug_083C4A99,
    gUnknown_Debug_083C4AA1,
    gUnknown_Debug_083C4AAF
};

const u8 gDebugText_BigSale[] = _("BIG SALE");

const u8 gUnknown_Debug_083C4B05[] = _("SERVICE DAY");
const u8 gUnknown_Debug_083C4B11[] = _("CLEAR-OUT SALE");
const u8 gUnknown_Debug_083C4B20[] = {1, 2, 3};

const u8 *const gUnknown_Debug_083C4B24[] = {
    gDebugText_BigSale,
    gUnknown_Debug_083C4B05,
    gUnknown_Debug_083C4B11
};

const u8 gUnknown_Debug_083C4B30[] = _("Secret type");
const u8 gUnknown_Debug_083C4B3C[] = _("Start");
const u8 gUnknown_Debug_083C4B42[] = _("Create TV");
const u8 gUnknown_Debug_083C4B4C[] = _("All clear");
const u8 gUnknown_Debug_083C4B56[] = _("All seen");
const u8 gUnknown_Debug_083C4B5F[] = _("Create CM");
const u8 gUnknown_Debug_083C4B69[] = _("Not yet seen");
const u8 gUnknown_Debug_083C4B76[] = _("Hit Table");
const u8 gUnknown_Debug_083C4B80[] = _("Set full");

// Normaly these would be struct MenuAction, but the prototype of
// member .func is not consistent.
const struct {
    const u8 * text;
    void *func;
} gUnknown_Debug_083C4B8C[] = {
    {gUnknown_Debug_083C4B30, debug_sub_808F4EC},
    {gUnknown_Debug_083C4B3C, debug_sub_808F8AC},
    {gUnknown_Debug_083C4B42, debug_sub_808F8CC},
    {gUnknown_Debug_083C4B4C, debug_sub_808FEBC},
    {gUnknown_Debug_083C4B56, debug_sub_808F560},
    {gUnknown_Debug_083C4B5F, debug_sub_808FECC},
    {gUnknown_Debug_083C4B69, debug_sub_808F594},
    {gUnknown_Debug_083C4B76, debug_sub_808F5D8},
    {gUnknown_Debug_083C4B80, debug_sub_80900AC}
};

bool8 NoharaDebugMenu_TV(void)
{
    gDebug_03000726 = 0;
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 10, 19);
    Menu_PrintItems(1, 1, ARRAY_COUNT(gUnknown_Debug_083C4B8C), gUnknown_Debug_083C4B8C);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C4B8C), 0, 9);
    gMenuCallback = debug_sub_808F4AC;
    return FALSE;
}

bool8 debug_sub_808F4AC(void)
{
    s8 input = Menu_ProcessInput();
    switch (input)
    {
        default:
            gMenuCallback = (MenuFunc)gUnknown_Debug_083C4B8C[input].func;
            return FALSE;
        case -2:
            return FALSE;
        case -1:
            CloseMenu();
            return TRUE;
    }
}

void debug_sub_808F4EC(void)
{
    debug_sub_808F6BC();
    sub_8071F40(gUnknown_Debug_083C4980);
    DisplayYesNoMenu(3, 3, 1);
    gMenuCallback = debug_sub_808F648;
}

void debug_sub_808F518(void)
{
    u8 i;

    for (i = 0; i < 24; i++)
    {
        if (gSaveBlock1.tvShows[i].common.kind >= TVSHOW_POKEMON_TODAY_CAUGHT &&
            gSaveBlock1.tvShows[i].common.kind < TVSHOW_MASS_OUTBREAK &&
            !gSaveBlock1.tvShows[i].common.active)
            gSaveBlock1.tvShows[i].common.active = TRUE;
    }
}

bool8 debug_sub_808F560(void)
{
    u8 i;

    for (i = 0; i < 24; i++)
        gSaveBlock1.tvShows[i].common.active = FALSE;
    CloseMenu();
    return TRUE;
}

bool8 debug_sub_808F594(void)
{
    u8 i;

    for (i = 0; i < 24; i++)
    {
        if (gSaveBlock1.tvShows[i].common.kind != 0)
            gSaveBlock1.tvShows[i].common.active = TRUE;
    }
    CloseMenu();
    return TRUE;
}

const u8 gUnknown_Debug_083C4BD4[][12] = {
    {0x0C, 0x04},
    {0x0C, 0x08},
    {0x0C, 0x0A},
    {0x0E, 0x06},
    {0x0E, 0x08},
    {0x0E, 0x0A},
    {0x10, 0x04},
    {0x10, 0x06},
    {0x10, 0x0A},
    {0x12, 0x04},
    {0x12, 0x06},
    {0x12, 0x0A}
};

bool8 debug_sub_808F5D8(void)
{
    u8 i;

    for (i = 0; i < 12; i++)
    {
        gSpecialVar_0x8004 = i;
        ConvertIntToDecimalStringN(gStringVar1, GetSlotMachineId(), STR_CONV_MODE_LEFT_ALIGN, 1);
        Menu_PrintText(gStringVar1, gUnknown_Debug_083C4BD4[i][0], gUnknown_Debug_083C4BD4[i][1]);
    }
    gSpecialVar_0x8004 = 0;
    gMenuCallback = debug_sub_8090278;
    return FALSE;
}

bool8 debug_sub_808F648(void)
{
    if (gMain.newKeys & DPAD_LEFT)
    {
        Menu_EraseWindowRect(10, 0, 29, 13);
        gDebug_03000726 ^= 1;
        if (gDebug_03000726)
            debug_sub_808F7B4();
        else
            debug_sub_808F6BC();
        return FALSE;
    }
    else
    {
        s8 input = Menu_ProcessInputNoWrap_();
        switch (input)
        {
            case -2:
                return FALSE;
            case 0:
                debug_sub_808F518();
                // fallthrough
            case -1:
            default:
                CloseMenu();
                return TRUE;
        }
    }
}

void debug_sub_808F6BC(void)
{
    u8 i;

    for (i = 0; i < 5; i++)
    {
        ConvertIntToDecimalStringN(gStringVar1, gSaveBlock1.tvShows[i].common.kind, STR_CONV_MODE_LEFT_ALIGN, 2);
        Menu_PrintText(gStringVar1, i * 2 + 10, 0);
    }

    for (i = 5; i < 24; i++)
    {
        ConvertIntToDecimalStringN(gStringVar1, gSaveBlock1.tvShows[i].common.kind, STR_CONV_MODE_LEFT_ALIGN, 2);
        if (i < 15)
            Menu_PrintText(gStringVar1, i * 2, 3);
        else
            Menu_PrintText(gStringVar1, i * 2 - 20, 6);
    }

    for (i = 0; i < 16; i++)
    {
        ConvertIntToDecimalStringN(gStringVar1, gSaveBlock1.pokeNews[i].kind, STR_CONV_MODE_LEFT_ALIGN, 2);
        if (i < 8)
            Menu_PrintText(gStringVar1, i * 2 + 10, 9);
        else
            Menu_PrintText(gStringVar1, i * 2 - 6, 12);
    }
}

void debug_sub_808F7B4(void)
{
    u8 i;

    for (i = 0; i < 5; i++)
    {
        ConvertIntToDecimalStringN(gStringVar1, gSaveBlock1.tvShows[i].common.active, STR_CONV_MODE_LEFT_ALIGN, 2);
        Menu_PrintText(gStringVar1, i * 2 + 10, 0);
    }

    for (i = 5; i < 24; i++)
    {
        ConvertIntToDecimalStringN(gStringVar1, gSaveBlock1.tvShows[i].common.active, STR_CONV_MODE_LEFT_ALIGN, 2);
        if (i < 15)
            Menu_PrintText(gStringVar1, i * 2, 3);
        else
            Menu_PrintText(gStringVar1, i * 2 - 20, 6);
    }

    for (i = 0; i < 16; i++)
    {
        ConvertIntToDecimalStringN(gStringVar1, gSaveBlock1.pokeNews[i].state, STR_CONV_MODE_LEFT_ALIGN, 2);
        if (i < 8)
            Menu_PrintText(gStringVar1, i * 2 + 10, 9);
        else
            Menu_PrintText(gStringVar1, i * 2 - 6, 12);
    }
}

bool8 debug_sub_808F8AC(void)
{
    FlagSet(FLAG_SYS_TV_START);
    FlagSet(FLAG_VISITED_MAUVILLE_CITY);
    CloseMenu();
    return TRUE;
}

void debug_sub_808F8CC(void)
{
    gDebug_03000724 = 0;
    sub_8071F40(gUnknown_Debug_083C49CA);
    Menu_BlankWindowRect(13, 6, 26, 8);
    Menu_PrintText(gUnknown_Debug_083C4ACC[0], 14, 7);
    Menu_BlankWindowRect(22, 1, 24, 2);
    ConvertIntToDecimalStringN(gStringVar1, 0, STR_CONV_MODE_LEFT_ALIGN, 2);
    Menu_PrintText(gStringVar1, 23, 1);
    gMenuCallback = debug_sub_808F93C;
}

bool8 debug_sub_808F93C(void)
{
    bool8 updateDisplay = FALSE;
    if (gMain.newKeys & DPAD_UP)
    {
        gDebug_03000725++;
        if (gDebug_03000725 == 24)
            gDebug_03000725 = 0;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }
    if (gMain.newKeys & DPAD_DOWN)
    {
        if (gDebug_03000725 == 0)
            gDebug_03000725 = 24;
        gDebug_03000725--;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }
    if (gMain.newKeys & DPAD_RIGHT)
    {
        gDebug_03000724++;
        if (gDebug_03000724 == 12)
            gDebug_03000724 = 0;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }
    if (gMain.newKeys & DPAD_LEFT)
    {
        if (gDebug_03000724 == 0)
            gDebug_03000724 = 12;
        gDebug_03000724--;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }
    if (updateDisplay)
    {
        Menu_BlankWindowRect(13, 6, 26, 8);
        Menu_PrintText(gUnknown_Debug_083C4ACC[gDebug_03000724], 14, 7);
        Menu_BlankWindowRect(22, 1, 24, 2);
        ConvertIntToDecimalStringN(gStringVar1, gDebug_03000725, STR_CONV_MODE_LEFT_ALIGN, 2);
        Menu_PrintText(gStringVar1, 23, 1);
    }
    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_PIN);
        debug_sub_808FA88(gDebug_03000725, gUnknown_Debug_083C4ABD[gDebug_03000724]);
    }
    if (gMain.newKeys & (B_BUTTON | START_BUTTON))
    {
        sub_80BF588(gSaveBlock1.tvShows);
        CloseMenu();
        return TRUE;
    }
    return FALSE;
}

void debug_sub_808FA88(u8 a0, u8 a1)
{
    u8 i;
    u8 leadMonIndex = GetLeadMonIndex();
    u8 channel;

// This is garbage.
#define GF_ACCESS(x) ((struct x*)(&(gSaveBlock1.tvShows[a0])))
#define TERU_ACCESS(x) show->x
#define DECLARE_TERU_POINTER TVShow * show = gSaveBlock1.tvShows + a0

    gSaveBlock1.tvShows[a0].common.kind = a1;
    gSaveBlock1.tvShows[a0].common.active = TRUE;
    for (i = 0; i < 0x22; i++)
        gSaveBlock1.tvShows[a0].common.pad02[i] = 1;

    channel = GetTVChannelByShowType(a1);
    switch (channel)
    {
        case 2:
        case 4:
            sub_80BE160(&gSaveBlock1.tvShows[a0]);
            break;
        case 3:
            sub_80BE138(&gSaveBlock1.tvShows[a0]);
            break;
    }

#if (ENGLISH && REVISION == 0)
    switch (a1)
    {
        case TVSHOW_FAN_CLUB_LETTER:
        case TVSHOW_RECENT_HAPPENINGS:
        {
            GF_ACCESS(TVShowFanClubLetter)->species = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowFanClubLetter)->playerName, gSaveBlock2.playerName);
            GF_ACCESS(TVShowFanClubLetter)->language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
        {
            GF_ACCESS(TVShowFanclubOpinions)->var02 = 1;
            StringCopy(GF_ACCESS(TVShowFanclubOpinions)->playerName, gSaveBlock2.playerName);
            GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_NICKNAME, GF_ACCESS(TVShowFanclubOpinions)->var10);
            GF_ACCESS(TVShowFanclubOpinions)->language = GAME_LANGUAGE;
            GF_ACCESS(TVShowFanclubOpinions)->var0E = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_LANGUAGE);
            break;
        }
        case TVSHOW_UNKN_SHOWTYPE_04:
        {
            break;
        }
        case TVSHOW_NAME_RATER_SHOW:
        {
            GF_ACCESS(TVShowNameRaterShow)->species = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_SPECIES);
            GF_ACCESS(TVShowNameRaterShow)->var1C = 1;
            StringCopy(GF_ACCESS(TVShowNameRaterShow)->trainerName, gSaveBlock2.playerName);
            GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_NICKNAME, GF_ACCESS(TVShowNameRaterShow)->pokemonName);
            GF_ACCESS(TVShowNameRaterShow)->language = GAME_LANGUAGE;
            GF_ACCESS(TVShowNameRaterShow)->pokemonNameLanguage = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_LANGUAGE);
            break;
        }
        case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
        {
            GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->species = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->playerName, gSaveBlock2.playerName);
            GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_NICKNAME, GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->pokemonNickname);
            GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->language = GAME_LANGUAGE;
            GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->var1f = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_LANGUAGE);
            break;
        }
        case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
        {
            GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->species = SPECIES_BULBASAUR;
            GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->defeatedSpecies = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->trainerName, gSaveBlock2.playerName);
            StringCopy(GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->enemyTrainerName, gSaveBlock2.playerName);
            GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_MASS_OUTBREAK:
        {
            GF_ACCESS(TVShowMassOutbreak)->species = SPECIES_BULBASAUR;
            GF_ACCESS(TVShowMassOutbreak)->daysLeft = 1;
            break;
        }
        case TVSHOW_POKEMON_TODAY_CAUGHT:
        {
            GF_ACCESS(TVShowPokemonToday)->species = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowPokemonToday)->playerName, gSaveBlock2.playerName);
            GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_NICKNAME, GF_ACCESS(TVShowPokemonToday)->nickname);
            GF_ACCESS(TVShowPokemonToday)->language = GAME_LANGUAGE;
            GF_ACCESS(TVShowPokemonToday)->language2 = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_LANGUAGE);
            break;
        }
        case TVSHOW_SMART_SHOPPER:
        {
            StringCopy(GF_ACCESS(TVShowSmartShopper)->playerName, gSaveBlock2.playerName);
            GF_ACCESS(TVShowSmartShopper)->language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_POKEMON_TODAY_FAILED:
        {
            GF_ACCESS(TVShowPokemonTodayFailed)->species = SPECIES_BULBASAUR;
            GF_ACCESS(TVShowPokemonTodayFailed)->species2 = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowPokemonTodayFailed)->playerName, gSaveBlock2.playerName);
            GF_ACCESS(TVShowPokemonTodayFailed)->language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_FISHING_ADVICE:
        {
            GF_ACCESS(TVShowPokemonAngler)->var04 = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowPokemonAngler)->playerName, gSaveBlock2.playerName);
            GF_ACCESS(TVShowPokemonAngler)->language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_WORLD_OF_MASTERS:
        {
            GF_ACCESS(TVShowWorldOfMasters)->var04 = SPECIES_BULBASAUR;
            GF_ACCESS(TVShowWorldOfMasters)->var08 = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowWorldOfMasters)->playerName, gSaveBlock2.playerName);
            GF_ACCESS(TVShowWorldOfMasters)->language = GAME_LANGUAGE;
            break;
        }
    }
#else
// Murakawa must have really hated working with GF code. He devised his own, less complicated
// access method after US rev0. Also, this iteration of the code has his self inserts: TERUKUN,
// TERU, and TERUDA. Who all love Wigglytuff.
    switch (a1)
    {
        case TVSHOW_FAN_CLUB_LETTER:
        case TVSHOW_RECENT_HAPPENINGS:
        {
            DECLARE_TERU_POINTER;
            
            GF_ACCESS(TVShowFanClubLetter)->species = SPECIES_BULBASAUR; // Yet he didn't change Game Freak's lines.
            StringCopy(GF_ACCESS(TVShowFanClubLetter)->playerName, gSaveBlock2.playerName);
            TERU_ACCESS(fanclubLetter).language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_PKMN_FAN_CLUB_OPINIONS:
        {
            DECLARE_TERU_POINTER;
            
            GF_ACCESS(TVShowFanclubOpinions)->var02 = 1;
            StringCopy(GF_ACCESS(TVShowFanclubOpinions)->playerName, gSaveBlock2.playerName);
            GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_NICKNAME, GF_ACCESS(TVShowFanclubOpinions)->var10);
            TERU_ACCESS(fanclubOpinions).language = GAME_LANGUAGE;
            TERU_ACCESS(fanclubOpinions).var0E = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_LANGUAGE);
            break;
        }
        case TVSHOW_UNKN_SHOWTYPE_04:
        {
            break;
        }
        case TVSHOW_NAME_RATER_SHOW:
        {
            u16 species = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_SPECIES);
            DECLARE_TERU_POINTER;
            
            GF_ACCESS(TVShowNameRaterShow)->species = species;
            GF_ACCESS(TVShowNameRaterShow)->var1C = 1;
            StringCopy(GF_ACCESS(TVShowNameRaterShow)->trainerName, gSaveBlock2.playerName);
            GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_NICKNAME, GF_ACCESS(TVShowNameRaterShow)->pokemonName);
            TERU_ACCESS(nameRaterShow).language = GAME_LANGUAGE;
            TERU_ACCESS(nameRaterShow).pokemonNameLanguage = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_LANGUAGE);
            break;
        }
        case TVSHOW_BRAVO_TRAINER_POKEMON_PROFILE:
        {
            DECLARE_TERU_POINTER;
            
            GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->species = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->playerName, gSaveBlock2.playerName);
            GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_NICKNAME, GF_ACCESS(TVShowBravoTrainerPokemonProfiles)->pokemonNickname);
            TERU_ACCESS(bravoTrainer).language = GAME_LANGUAGE;
            TERU_ACCESS(bravoTrainer).var1f = GetMonData(&gPlayerParty[leadMonIndex], MON_DATA_LANGUAGE);
            break;
        }
        case TVSHOW_BRAVO_TRAINER_BATTLE_TOWER_PROFILE:
        {
            DECLARE_TERU_POINTER;
            
            GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->species = SPECIES_BULBASAUR;
            GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->defeatedSpecies = SPECIES_BULBASAUR;
            StringCopy(GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->trainerName, gSaveBlock2.playerName);
            StringCopy(GF_ACCESS(TVShowBravoTrainerBattleTowerSpotlight)->enemyTrainerName, gSaveBlock2.playerName);
            TERU_ACCESS(bravoTrainerTower).language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_MASS_OUTBREAK:
        {
            GF_ACCESS(TVShowMassOutbreak)->species = SPECIES_BULBASAUR;
            GF_ACCESS(TVShowMassOutbreak)->daysLeft = 1;
            break;
        }
        case TVSHOW_POKEMON_TODAY_CAUGHT:
        {
            DECLARE_TERU_POINTER;
            u8 gUnknown_Debug_083C4C64[] = _("TERUKUN");
            u8 gUnknown_Debug_083C4C6C[] = _("TERUTERUDA");

            TERU_ACCESS(pokemonToday).var12 = 255;
            StringCopy(TERU_ACCESS(pokemonToday).playerName, gUnknown_Debug_083C4C64);
            StringCopy(TERU_ACCESS(pokemonToday).nickname, gUnknown_Debug_083C4C6C);
            TERU_ACCESS(pokemonToday).ball = ITEM_PREMIER_BALL;
            TERU_ACCESS(pokemonToday).species = SPECIES_WIGGLYTUFF;
            TERU_ACCESS(pokemonToday).language = GAME_LANGUAGE;
            TERU_ACCESS(pokemonToday).language2 = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_SMART_SHOPPER:
        {
            DECLARE_TERU_POINTER;
            u8 gUnknown_Debug_083C4C64[] = _("TERUKUN");
            int ii;

            for (ii = 0; ii < 3; ii++)
                TERU_ACCESS(smartshopperShow).itemAmounts[ii] = 254;
            TERU_ACCESS(smartshopperShow).priceReduced = TRUE;
            TERU_ACCESS(smartshopperShow).shopLocation = 40;
            for (ii = 0; ii < 3; ii++)
                TERU_ACCESS(smartshopperShow).itemIds[ii] = ITEM_ENERGY_POWDER;
            StringCopy(TERU_ACCESS(smartshopperShow).playerName, gUnknown_Debug_083C4C64);
            TERU_ACCESS(smartshopperShow).language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_POKEMON_TODAY_FAILED:
        {
            DECLARE_TERU_POINTER;
            u8 gUnknown_Debug_083C4C64[] = _("TERUKUN");

            TERU_ACCESS(pokemonTodayFailed).species = SPECIES_WIGGLYTUFF;
            TERU_ACCESS(pokemonTodayFailed).species2 = SPECIES_WIGGLYTUFF;
            TERU_ACCESS(pokemonTodayFailed).var12 = 3;
            TERU_ACCESS(pokemonTodayFailed).var10 = 0xff;
            TERU_ACCESS(pokemonTodayFailed).var11 = 1;
            StringCopy(TERU_ACCESS(pokemonTodayFailed).playerName, gUnknown_Debug_083C4C64);
            TERU_ACCESS(pokemonTodayFailed).language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_FISHING_ADVICE:
        {
            DECLARE_TERU_POINTER;
            u8 gUnknown_Debug_083C4C64[] = _("TERUKUN");

            TERU_ACCESS(pokemonAngler).var02 = 0xff;
            TERU_ACCESS(pokemonAngler).var03 = 0;
            TERU_ACCESS(pokemonAngler).var04 = 40;
            StringCopy(TERU_ACCESS(pokemonAngler).playerName, gUnknown_Debug_083C4C64);
            TERU_ACCESS(pokemonAngler).language = GAME_LANGUAGE;
            break;
        }
        case TVSHOW_WORLD_OF_MASTERS:
        {
            DECLARE_TERU_POINTER;
            u8 gUnknown_Debug_083C4C64[] = _("TERUKUN");

            TERU_ACCESS(worldOfMasters).var02 = 0xffff;
            TERU_ACCESS(worldOfMasters).var06 = 0xffff;
            TERU_ACCESS(worldOfMasters).var04 = 40;
            TERU_ACCESS(worldOfMasters).var08 = 40;
            TERU_ACCESS(worldOfMasters).var0a = 3;
            StringCopy(TERU_ACCESS(worldOfMasters).playerName, gUnknown_Debug_083C4C64);
            TERU_ACCESS(worldOfMasters).language = GAME_LANGUAGE;
            break;
        }
    }
#endif
}

bool8 debug_sub_808FEBC(void)
{
    ClearTVShowData();
    CloseMenu();
    return TRUE;
}

void debug_sub_808FECC(void)
{
    gDebug_03000724 = 0;
    sub_8071F40(gUnknown_Debug_083C49CA);
    Menu_BlankWindowRect(13, 6, 23, 8);
    Menu_PrintText(gUnknown_Debug_083C4B24[0], 14, 7);
    Menu_BlankWindowRect(22, 1, 24, 2);
    ConvertIntToDecimalStringN(gStringVar1, 0, STR_CONV_MODE_LEFT_ALIGN, 2);
    Menu_PrintText(gStringVar1, 23, 1);
    gMenuCallback = debug_sub_808FF3C;
}

bool8 debug_sub_808FF3C(void)
{
    bool8 updateDisplay = FALSE;

    if (gMain.newKeys & DPAD_UP)
    {
        gDebug_03000725++;
        if (gDebug_03000725 == 16)
            gDebug_03000725 = 0;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }

    if (gMain.newKeys & DPAD_DOWN)
    {
        if (gDebug_03000725 == 0)
            gDebug_03000725 = 16;
        gDebug_03000725--;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }

    if (gMain.newKeys & DPAD_RIGHT)
    {
        gDebug_03000724++;
        if (gDebug_03000724 == 3)
            gDebug_03000724 = 0;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }

    if (gMain.newKeys & DPAD_LEFT)
    {
        if (gDebug_03000724 == 0)
            gDebug_03000724 = 3;
        gDebug_03000724--;
        PlaySE(SE_SELECT);
        updateDisplay = TRUE;
    }

    if (updateDisplay)
    {
        Menu_BlankWindowRect(13, 6, 23, 8);
        Menu_PrintText(gUnknown_Debug_083C4B24[gDebug_03000724], 14, 7);
        Menu_BlankWindowRect(22, 1, 24, 2);
        ConvertIntToDecimalStringN(gStringVar1, gDebug_03000725, STR_CONV_MODE_LEFT_ALIGN, 2);
        Menu_PrintText(gStringVar1, 23, 1);
    }

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_PIN);
        debug_sub_8090080(gDebug_03000725, gUnknown_Debug_083C4B20[gDebug_03000724]);
    }

    if (gMain.newKeys & (B_BUTTON | START_BUTTON))
    {
        sub_80BEC40();
        CloseMenu();
        return TRUE;
    }

    return FALSE;
}

void debug_sub_8090080(u8 a0, u8 a1)
{
    gSaveBlock1.pokeNews[a0].kind = a1;
    gSaveBlock1.pokeNews[a0].state = 1;
    gSaveBlock1.pokeNews[a0].days = 4;
}

bool8 debug_sub_80900AC(void)
{
    u8 i;
    u8 j;

    j = 0;
    for (i = 0; i < 24; i++)
    {
        if (gSaveBlock1.tvShows[i].common.kind == 0)
        {
            if (j == 12)
                j = 0;
            debug_sub_808FA88(i, gUnknown_Debug_083C4ABD[j]);
            gSaveBlock1.tvShows[i].common.active = FALSE;
            j++;
        }
    }

    j = 0;
    for (i = 0; i < 16; i++)
    {
        if (gSaveBlock1.pokeNews[i].kind == 0)
        {
            if (j == 3)
                j = 0;
            debug_sub_8090080(i, gUnknown_Debug_083C4B20[j]);
            j++;
        }
    }

    CloseMenu();
    return TRUE;
}
// These represent the people in Lilycove Fan Club.
// TRN: These translations are probably wrong but it is really hard to tell with
// the abbreviations. They are mosly based on observation
// The first one is selected by default when there are no fans.
const u8 gUnknown_Debug_083C4C77[] = DTR("1　スクル", "1 LASS/NONE"); // school (girl)
const u8 gUnknown_Debug_083C4C7D[] = DTR("2　ミドル", "2 MIDDLE AGE MAN"); // middle
const u8 gUnknown_Debug_083C4C83[] = DTR("3　オジヨ", "3 DAUGHTER"); // おしょう (daughter)
const u8 gUnknown_Debug_083C4C89[] = DTR("4　ボーヤ", "4 YOUNG BOY"); // 坊や (boy)
const u8 gUnknown_Debug_083C4C8F[] = DTR("5　ボーイ", "5 BOY"); // boy
const u8 gUnknown_Debug_083C4C95[] = DTR("6　ヤング", "6 YOUNG MAN"); // young
const u8 gUnknown_Debug_083C4C9B[] = DTR("7　ヲーカ", "7 MOM"); // お母さん? (probably typo)
const u8 gUnknown_Debug_083C4CA1[] = DTR("8　オルド", "8 OLD LADY"); // old

const u8 *const gUnknown_Debug_083C4CA8[] = {
    gUnknown_Debug_083C4C77,
    gUnknown_Debug_083C4C7D,
    gUnknown_Debug_083C4C83,
    gUnknown_Debug_083C4C89,
    gUnknown_Debug_083C4C8F,
    gUnknown_Debug_083C4C95,
    gUnknown_Debug_083C4C9B,
    gUnknown_Debug_083C4CA1
};

const u8 gUnknown_Debug_083C4CC8[] = _("Start"); // Starts the "Oh! I've heard of you' script"
const u8 gUnknown_Debug_083C4CCE[] = _("Increase"); // Increases popularity
const u8 gUnknown_Debug_083C4CD7[] = _("Reduce"); // reduces popularity
const u8 gUnknown_Debug_083C4CDE[] = _("Points");
const u8 gUnknown_Debug_083C4CE5[] = _("Play time 6");
const u8 gUnknown_Debug_083C4CF1[] = _("P ELITE FOUR");
const u8 gUnknown_Debug_083C4CFE[] = _("P SECRET BASE");
const u8 gUnknown_Debug_083C4D0C[] = _("P CONTEST");
const u8 gUnknown_Debug_083C4D16[] = _("P BATTLE TOWER");

const struct MenuAction gUnknown_Debug_083C4D28[] = {
    {gUnknown_Debug_083C4CC8, debug_sub_80901E4},
    {gUnknown_Debug_083C4CCE, debug_sub_80901F8},
    {gUnknown_Debug_083C4CD7, debug_sub_8090238},
    {gUnknown_Debug_083C4CDE, debug_sub_809029C},
    {gUnknown_Debug_083C4CE5, debug_sub_80902E4},
    {gUnknown_Debug_083C4CF1, debug_sub_80902FC},
    {gUnknown_Debug_083C4CFE, debug_sub_8090310},
    {gUnknown_Debug_083C4D0C, debug_sub_8090324},
    {gUnknown_Debug_083C4D16, debug_sub_8090338}
};

bool8 NoharaDebugMenu_Fan(void)
{
    Menu_EraseScreen();
    Menu_DrawStdWindowFrame(0, 0, 11, 19);
    Menu_PrintItems(1, 1, ARRAY_COUNT(gUnknown_Debug_083C4D28), gUnknown_Debug_083C4D28);
    InitMenu(0, 1, 1, ARRAY_COUNT(gUnknown_Debug_083C4D28), 0, 10);
    gMenuCallback = debug_sub_80901A4;
    return FALSE;
}

bool8 debug_sub_80901A4(void)
{
    s8 input = Menu_ProcessInput();
    switch (input)
    {
        default:
            gMenuCallback = gUnknown_Debug_083C4D28[input].func;
            return FALSE;
        case -2:
            return FALSE;
        case -1:
            CloseMenu();
            return TRUE;
    }
}

bool8 debug_sub_80901E4(void)
{
    ResetFanClub();
    UpdateTrainerFanClubGameClear();
    CloseMenu();
    return TRUE;
}

bool8 debug_sub_80901F8(void)
{
    u8 r0 = sub_810FB9C();
    Menu_PrintText(gUnknown_Debug_083C4CA8[gUnknown_083F8408[r0] - 8], 14, 7);
    gMenuCallback = debug_sub_8090278;
    return FALSE;
}

bool8 debug_sub_8090238(void)
{
    u8 r0 = sub_810FC18();
    Menu_PrintText(gUnknown_Debug_083C4CA8[gUnknown_083F8410[r0] - 8], 14, 7);
    gMenuCallback = debug_sub_8090278;
    return FALSE;
}

bool8 debug_sub_8090278(void)
{
    if (gMain.newKeys & A_BUTTON)
    {
        CloseMenu();
        return TRUE;
    }

    return FALSE;
}

bool8 debug_sub_809029C(void)
{
    ConvertIntToDecimalStringN(gStringVar1, gSaveBlock1.vars[VAR_FANCLUB_UNKNOWN_1 - VARS_START] & 0x7F, STR_CONV_MODE_LEFT_ALIGN, 2);
    Menu_PrintText(gStringVar1, 16, 7);
    gMenuCallback = debug_sub_8090278;
    return FALSE;
}

bool8 debug_sub_80902E4(void)
{
    gSaveBlock2.playTimeHours += 6;
    CloseMenu();
    return TRUE;
}

bool8 debug_sub_80902FC(void)
{
    sub_810FB10(0);
    CloseMenu();
    return TRUE;
}

bool8 debug_sub_8090310(void)
{
    sub_810FB10(1);
    CloseMenu();
    return TRUE;
}

bool8 debug_sub_8090324(void)
{
    sub_810FB10(2);
    CloseMenu();
    return TRUE;
}

bool8 debug_sub_8090338(void)
{
    sub_810FB10(3);
    CloseMenu();
    return TRUE;
}

bool8 NoharaDebugMenu_BattleVSDad(void)
{
    VarSet(VAR_PETALBURG_GYM_STATE, 6);
    CloseMenu();
    return TRUE;
}

bool8 NoharaDebugMenu_DadAfterBattle(void)
{
    VarSet(VAR_PETALBURG_GYM_STATE, 7);
    CloseMenu();
    return TRUE;
}

bool8 NoharaDebugMenu_SootopolisCity(void)
{
    FlagSet(FLAG_LEGEND_ESCAPED_SEAFLOOR_CAVERN);
    FlagSet(FLAG_LEGENDARY_BATTLE_COMPLETED);
    FlagClear(FLAG_HIDE_WALLACE_SOOTOPOLIS_GYM);
    CloseMenu();
    return TRUE;
}

bool8 NoharaDebugMenu_Embark(void)
{
    FlagClear(FLAG_HIDE_MR_BRINEY_ROUTE104_HOUSE);
    VarSet(VAR_BRINEY_HOUSE_STATE, 1);
    CloseMenu();
    return TRUE;
}

bool8 NoharaDebugMenu_Yes9999(void)
{
    VarSet(VAR_ASH_GATHER_COUNT, 9999);
    CloseMenu();
    return TRUE;
}

bool8 NoharaDebugMenu_LegendsFlagOn(void)
{
    FlagSet(FLAG_REGI_DOORS_OPENED);
    CloseMenu();
    return TRUE;
}

bool8 NoharaDebugMenu_AddNumWinningStreaks(void)
{
    if (gSaveBlock2.battleTower.bestBattleTowerWinStreak < 50)
        gSaveBlock2.battleTower.bestBattleTowerWinStreak = 50;
    else if (gSaveBlock2.battleTower.bestBattleTowerWinStreak < 100)
        gSaveBlock2.battleTower.bestBattleTowerWinStreak = 100;
    else if (gSaveBlock2.battleTower.bestBattleTowerWinStreak < 1000)
        gSaveBlock2.battleTower.bestBattleTowerWinStreak = 1000;
    else if (gSaveBlock2.battleTower.bestBattleTowerWinStreak < 5000)
        gSaveBlock2.battleTower.bestBattleTowerWinStreak = 9990;
    else if (gSaveBlock2.battleTower.bestBattleTowerWinStreak < 9990)
        gSaveBlock2.battleTower.bestBattleTowerWinStreak = 9999;
    CloseMenu();
    return TRUE;
}

#endif
