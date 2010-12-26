/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_SUNWELLPLATEAU_H
#define DEF_SUNWELLPLATEAU_H

extern uint64 KalecWall;
enum
{
    /*** Encounters ***/
    DATA_KALECGOS_EVENT         = 0,
    DATA_SATHROVARR_EVENT       = 28,
    DATA_BRUTALLUS_EVENT        = 1,
    DATA_FELMYST_EVENT          = 2,
    DATA_EREDAR_TWINS_EVENT     = 3,
    DATA_MURU_EVENT             = 4,
    DATA_KILJAEDEN_EVENT        = 5,
    DATA_DECIVER                = 29,
    DATA_SACROLASH_EVENT        = 40,
    DATA_ALYSTHESS_EVENT        = 41,

    /*** Creatures ***/
    DATA_KALECGOS_DRAGON        = 6,
    DATA_KALECGOS_HUMAN         = 7,
    DATA_SATHROVARR             = 8,
    DATA_BRUTALLUS              = 9,
    DATA_FELMYST                = 10,
    DATA_ALYTHESS               = 11,
    DATA_SACROLASH              = 12,
    DATA_MURU                   = 13,
    DATA_ENTROPIUS              = 32,
    DATA_KILJAEDEN              = 14,
    DATA_KILJAEDEN_CONTROLLER   = 15,
    DATA_ANVEENA                = 16,

    /*** GameObjects ***/
    DATA_GO_FORCEFIELD          = 17,
    DATA_GO_FIRE_BARRIER        = 18,
    DATA_GATE_1                 = 19,
    DATA_GATE_2                 = 20,
    DATA_GATE_3                 = 21,
    DATA_GATE_4                 = 22,
    DATA_GATE_5                 = 23,
    DATA_KALECGOS_GATE          = 28,
    DATA_KALECGOS_FIGHT_GATE_A  = 29,
    DATA_KALECGOS_FIGHT_GATE_B  = 30,
    DATA_FELMIST_GATE           = 31,

    /*** Misc ***/
    DATA_PLAYER_SPECTRAL_REALM  = 24,
    DATA_SET_SPECTRAL_CHECK     = 25,
    DATA_RANDOM_SPECTRAL_PLAYER = 26,
    DATA_INST_EJECT_PLAYERS     = 27
};
#endif
