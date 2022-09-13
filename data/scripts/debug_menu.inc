DebugMenu::
    lockall
    multichoice 0, 0, 17, 0
    switch VAR_RESULT
    case 0, TP_Yes
    case 1, TP_No
    release
    end

TP_Yes::
    givemon SPECIES_HAUNTER, 50, ITEM_MOON_STONE
    end

TP_No::
    release
    end
