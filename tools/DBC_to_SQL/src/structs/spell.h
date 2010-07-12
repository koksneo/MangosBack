/*
 * DBC to SQL Converter
 * Copyright (C) 2009  David Vas, Anubisss
 * <http://code.google.com/p/dbctosql/>
 * updated by Przemratajczak

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SPEL_H__
#define __SPEL_H__

char const *SPELL_DBC   = "Spell.dbc";
char const *SPELL_SQL   = "spell.sql";
char const *SPELL_TABLE = "spell";

#define SPELL_DBC_CLIENT_BUILD  12340 // 3.3.5

#define SPELL_DBC_COLUMN_NUMS   234
#define SPELL_DBC_ROWS_NUMS     49839

// Spell.dbc struct: MaNGOS 9740
char const *spell_translation[SPELL_DBC_COLUMN_NUMS][2] =
{
    {"uint32",   "Id"},                                           // 0        m_ID
    {"uint32",   "Category"},                                     // 1        m_category
    {"uint32",   "Dispel"},                                       // 2        m_dispelType
    {"uint32",   "Mechanic"},                                     // 3        m_mechanic
    {"uint32",   "Attributes"},                                   // 4        m_attribute
    {"uint32",   "AttributesEx"},                                 // 5        m_attributesEx
    {"uint32",   "AttributesEx2"},                                // 6        m_attributesExB
    {"uint32",   "AttributesEx3"},                                // 7        m_attributesExC
    {"uint32",   "AttributesEx4"},                                // 8        m_attributesExD
    {"uint32",   "AttributesEx5"},                                // 9        m_attributesExE
    {"uint32",   "AttributesEx6"},                                // 10       m_attributesExF
    {"uint32",   "unk_320_1"},                                    // 11       3.2.0 (0x20 - totems, 0x4 - paladin auras, etc...)
    {"uint32",   "Stances"},                                      // 12       m_shapeshiftMask
    {"uint32",   "unk_320_2"},                                    // 13       3.2.0
    {"uint32",   "StancesNot"},                                   // 14       m_shapeshiftExclude
    {"uint32",   "unk_320_3"},                                    // 15       3.2.0
    {"uint32",   "Targets"},                                      // 16       m_targets
    {"uint32",   "TargetCreatureType"},                           // 17       m_targetCreatureType
    {"uint32",   "RequiresSpellFocus"},                           // 18       m_requiresSpellFocus
    {"uint32",   "FacingCasterFlags"},                            // 19       m_facingCasterFlags
    {"uint32",   "CasterAuraState"},                              // 20       m_casterAuraState
    {"uint32",   "TargetAuraState"},                              // 21       m_targetAuraState
    {"uint32",   "CasterAuraStateNot"},                           // 22       m_excludeCasterAuraState
    {"uint32",   "TargetAuraStateNot"},                           // 23       m_excludeTargetAuraState
    {"uint32",   "casterAuraSpell"},                              // 24       m_casterAuraSpell
    {"uint32",   "targetAuraSpell"},                              // 25       m_targetAuraSpell
    {"uint32",   "excludeCasterAuraSpell"},                       // 26       m_excludeCasterAuraSpell
    {"uint32",   "excludeTargetAuraSpell"},                       // 27       m_excludeTargetAuraSpell
    {"uint32",   "CastingTimeIndex"},                             // 28       m_castingTimeIndex
    {"uint32",   "RecoveryTime"},                                 // 29       m_recoveryTime
    {"uint32",   "CategoryRecoveryTime"},                         // 30       m_categoryRecoveryTime
    {"uint32",   "InterruptFlags"},                               // 31       m_interruptFlags
    {"uint32",   "AuraInterruptFlags"},                           // 32       m_auraInterruptFlags
    {"uint32",   "ChannelInterruptFlags"},                        // 33       m_channelInterruptFlags
    {"uint32",   "procFlags"},                                    // 34       m_procTypeMask
    {"uint32",   "procChance"},                                   // 35       m_procChance
    {"uint32",   "procCharges"},                                  // 36       m_procCharges
    {"uint32",   "maxLevel"},                                     // 37       m_maxLevel
    {"uint32",   "baseLevel"},                                    // 38       m_baseLevel
    {"uint32",   "spellLevel"},                                   // 39       m_spellLevel
    {"uint32",   "DurationIndex"},                                // 40       m_durationIndex
    {"uint32",   "powerType"},                                    // 41       m_powerType
    {"uint32",   "manaCost"},                                     // 42       m_manaCost
    {"uint32",   "manaCostPerlevel"},                             // 43       m_manaCostPerLevel
    {"uint32",   "manaPerSecond"},                                // 44       m_manaPerSecond
    {"uint32",   "manaPerSecondPerLevel"},                        // 45       m_manaPerSecondPerLeve
    {"uint32",   "rangeIndex"},                                   // 46       m_rangeIndex
    {"float",    "speed"},                                        // 47       m_speed
    {"uint32",   "modalNextSpell"},                               // 48       m_modalNextSpell not used
    {"uint32",   "StackAmount"},                                  // 49       m_cumulativeAura
    {"uint32",   "Totem0"},                                       // 50       m_totem
    {"uint32",   "Totem1"},                                       // 51       m_totem
    {"int32",    "Reagent0"},                                     // 52       m_reagent
    {"int32",    "Reagent1"},                                     // 53       m_reagent
    {"int32",    "Reagent2"},                                     // 54       m_reagent
    {"int32",    "Reagent3"},                                     // 55       m_reagent
    {"int32",    "Reagent4"},                                     // 56       m_reagent
    {"int32",    "Reagent5"},                                     // 57       m_reagent
    {"int32",    "Reagent6"},                                     // 58       m_reagent
    {"int32",    "Reagent7"},                                     // 59       m_reagent
    {"uint32",   "ReagentCount0"},                                // 60       m_reagentCount
    {"uint32",   "ReagentCount1"},                                // 61       m_reagentCount
    {"uint32",   "ReagentCount2"},                                // 62       m_reagentCount
    {"uint32",   "ReagentCount3"},                                // 63       m_reagentCount
    {"uint32",   "ReagentCount4"},                                // 64       m_reagentCount
    {"uint32",   "ReagentCount5"},                                // 65       m_reagentCount
    {"uint32",   "ReagentCount6"},                                // 66       m_reagentCount
    {"uint32",   "ReagentCount7"},                                // 67       m_reagentCount
    {"int32",    "EquippedItemClass"},                            // 68       m_equippedItemClass (value)
    {"int32",    "EquippedItemSubClassMask"},                     // 69       m_equippedItemSubclass (mask)
    {"int32",    "EquippedItemInventoryTypeMask"},                // 70       m_equippedItemInvTypes (mask)
    {"uint32",   "Effect0"},                                      // 71       m_effect
    {"uint32",   "Effect1"},                                      // 72       m_effect
    {"uint32",   "Effect2"},                                      // 73       m_effect
    {"int32",    "EffectDieSides0"},                              // 74       m_effectDieSides
    {"int32",    "EffectDieSides1"},                              // 75       m_effectDieSides
    {"int32",    "EffectDieSides2"},                              // 76       m_effectDieSides
    {"float",    "EffectRealPointsPerLevel0"},                    // 77       m_effectRealPointsPerLevel
    {"float",    "EffectRealPointsPerLevel1"},                    // 78       m_effectRealPointsPerLevel
    {"float",    "EffectRealPointsPerLevel2"},                    // 79       m_effectRealPointsPerLevel
    {"int32",    "EffectBasePoints0"},                            // 80       m_effectBasePoints (don't must be used in spell/auras explicitly, must be used 
    {"int32",    "EffectBasePoints1"},                            // 81       m_effectBasePoints (don't must be used in spell/auras explicitly, must be used 
    {"int32",    "EffectBasePoints2"},                            // 82       m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    {"uint32",   "EffectMechanic0"},                              // 83       m_effectMechanic
    {"uint32",   "EffectMechanic1"},                              // 84       m_effectMechanic
    {"uint32",   "EffectMechanic2"},                              // 85       m_effectMechanic
    {"uint32",   "EffectImplicitTargetA0"},                       // 86       m_implicitTargetA
    {"uint32",   "EffectImplicitTargetA1"},                       // 87       m_implicitTargetA
    {"uint32",   "EffectImplicitTargetA2"},                       // 88       m_implicitTargetA
    {"uint32",   "EffectImplicitTargetB0"},                       // 89       m_implicitTargetB
    {"uint32",   "EffectImplicitTargetB1"},                       // 90       m_implicitTargetB
    {"uint32",   "EffectImplicitTargetB2"},                       // 91       m_implicitTargetB
    {"uint32",   "EffectRadiusIndex0"},                           // 92       m_effectRadiusIndex - spellradius.dbc
    {"uint32",   "EffectRadiusIndex1"},                           // 93       m_effectRadiusIndex - spellradius.dbc
    {"uint32",   "EffectRadiusIndex2"},                           // 94       m_effectRadiusIndex - spellradius.dbc
    {"uint32",   "EffectApplyAuraName0"},                         // 95       m_effectAura
    {"uint32",   "EffectApplyAuraName1"},                         // 96       m_effectAura
    {"uint32",   "EffectApplyAuraName2"},                         // 97       m_effectAura
    {"uint32",   "EffectAmplitude0"},                             // 98       m_effectAuraPeriod
    {"uint32",   "EffectAmplitude1"},                             // 99       m_effectAuraPeriod
    {"uint32",   "EffectAmplitude2"},                             // 100      m_effectAuraPeriod
    {"float",    "EffectMultipleValue0"},                         // 101      m_effectAmplitude
    {"float",    "EffectMultipleValue1"},                         // 102      m_effectAmplitude
    {"float",    "EffectMultipleValue2"},                         // 103      m_effectAmplitude
    {"uint32",   "EffectChainTarget0"},                           // 104      m_effectChainTargets
    {"uint32",   "EffectChainTarget1"},                           // 105      m_effectChainTargets
    {"uint32",   "EffectChainTarget2"},                           // 106      m_effectChainTargets
    {"uint32",   "EffectItemType0"},                              // 107      m_effectItemType
    {"uint32",   "EffectItemType1"},                              // 108      m_effectItemType
    {"uint32",   "EffectItemType2"},                              // 109      m_effectItemType
    {"int32",    "EffectMiscValue0"},                             // 110      m_effectMiscValue
    {"int32",    "EffectMiscValue1"},                             // 111      m_effectMiscValue
    {"int32",    "EffectMiscValue2"},                             // 112      m_effectMiscValue
    {"int32",    "EffectMiscValueB0"},                            // 113      m_effectMiscValueB
    {"int32",    "EffectMiscValueB1"},                            // 114      m_effectMiscValueB
    {"int32",    "EffectMiscValueB2"},                            // 115      m_effectMiscValueB
    {"uint32",   "EffectTriggerSpell0"},                          // 116      m_effectTriggerSpell
    {"uint32",   "EffectTriggerSpell1"},                          // 117      m_effectTriggerSpell
    {"uint32",   "EffectTriggerSpell2"},                          // 118      m_effectTriggerSpell
    {"float",    "EffectPointsPerComboPoint0"},                   // 119      m_effectPointsPerCombo
    {"float",    "EffectPointsPerComboPoint1"},                   // 120      m_effectPointsPerCombo
    {"float",    "EffectPointsPerComboPoint2"},                   // 121      m_effectPointsPerCombo
    {"uint32",   "EffectSpellClassMaskA0"},                       // 122      m_effectSpellClassMaskA, effect 0
    {"uint32",   "EffectSpellClassMaskA1"},                       // 123      m_effectSpellClassMaskA, effect 0
    {"uint32",   "EffectSpellClassMaskA2"},                       // 124      m_effectSpellClassMaskA, effect 0
    {"uint32",   "EffectSpellClassMaskB0"},                       // 125      m_effectSpellClassMaskB, effect 1
    {"uint32",   "EffectSpellClassMaskB1"},                       // 126      m_effectSpellClassMaskB, effect 1
    {"uint32",   "EffectSpellClassMaskB2"},                       // 127      m_effectSpellClassMaskB, effect 1
    {"uint32",   "EffectSpellClassMaskC0"},                       // 128      m_effectSpellClassMaskC, effect 2
    {"uint32",   "EffectSpellClassMaskC1"},                       // 129      m_effectSpellClassMaskC, effect 2
    {"uint32",   "EffectSpellClassMaskC2"},                       // 130      m_effectSpellClassMaskC, effect 2
    {"uint32",   "SpellVisual0"},                                 // 131      m_spellVisualID
    {"uint32",   "SpellVisual1"},                                 // 132      m_spellVisualID
    {"uint32",   "SpellIconID"},                                  // 133      m_spellIconID
    {"uint32",   "activeIconID"},                                 // 134      m_activeIconID
    {"uint32",   "spellPriority"},                                // 135      m_spellPriority not used
    {"char*",    "SpellName0"},                                   // 136      m_name_lang
    {"char*",    "SpellName1"},                                   // 137      m_name_lang
    {"char*",    "SpellName2"},                                   // 138      m_name_lang
    {"char*",    "SpellName3"},                                   // 139      m_name_lang
    {"char*",    "SpellName4"},                                   // 140      m_name_lang
    {"char*",    "SpellName5"},                                   // 141      m_name_lang
    {"char*",    "SpellName6"},                                   // 142      m_name_lang
    {"char*",    "SpellName7"},                                   // 143      m_name_lang
    {"char*",    "SpellName8"},                                   // 144      m_name_lang
    {"char*",    "SpellName9"},                                   // 145      m_name_lang
    {"char*",    "SpellName10"},                                  // 146      m_name_lang
    {"char*",    "SpellName11"},                                  // 147      m_name_lang
    {"char*",    "SpellName12"},                                  // 148      m_name_lang
    {"char*",    "SpellName13"},                                  // 149      m_name_lang
    {"char*",    "SpellName14"},                                  // 150      m_name_lang
    {"char*",    "SpellName15"},                                  // 151      m_name_lang
    {"uint32",   "SpellNameFlag"},                                // 152      not used
    {"char*",    "Rank0"},                                        // 153      m_nameSubtext_lang
    {"char*",    "Rank1"},                                        // 154      m_nameSubtext_lang
    {"char*",    "Rank2"},                                        // 155      m_nameSubtext_lang
    {"char*",    "Rank3"},                                        // 156      m_nameSubtext_lang
    {"char*",    "Rank4"},                                        // 157      m_nameSubtext_lang
    {"char*",    "Rank5"},                                        // 158      m_nameSubtext_lang
    {"char*",    "Rank6"},                                        // 159      m_nameSubtext_lang
    {"char*",    "Rank7"},                                        // 160      m_nameSubtext_lang
    {"char*",    "Rank8"},                                        // 161      m_nameSubtext_lang
    {"char*",    "Rank9"},                                        // 162      m_nameSubtext_lang
    {"char*",    "Rank10"},                                       // 163      m_nameSubtext_lang
    {"char*",    "Rank11"},                                       // 164      m_nameSubtext_lang
    {"char*",    "Rank12"},                                       // 165      m_nameSubtext_lang
    {"char*",    "Rank13"},                                       // 166      m_nameSubtext_lang
    {"char*",    "Rank14"},                                       // 167      m_nameSubtext_lang
    {"char*",    "Rank15"},                                       // 168      m_nameSubtext_lang
    {"uint32",   "RankFlags"},                                    // 169      not used
    {"text",     "Description0"},                                 // 170      m_description_lang not used
    {"char*",    "Description1"},                                 // 171      m_description_lang not used
    {"char*",    "Description2"},                                 // 172      m_description_lang not used
    {"char*",    "Description3"},                                 // 173      m_description_lang not used
    {"char*",    "Description4"},                                 // 174      m_description_lang not used
    {"char*",    "Description5"},                                 // 175      m_description_lang not used
    {"char*",    "Description6"},                                 // 176      m_description_lang not used
    {"char*",    "Description7"},                                 // 177      m_description_lang not used
    {"char*",    "Description8"},                                 // 178      m_description_lang not used
    {"char*",    "Description9"},                                 // 179      m_description_lang not used
    {"char*",    "Description10"},                                // 180      m_description_lang not used
    {"char*",    "Description11"},                                // 181      m_description_lang not used
    {"char*",    "Description12"},                                // 182      m_description_lang not used
    {"char*",    "Description13"},                                // 183      m_description_lang not used
    {"char*",    "Description14"},                                // 184      m_description_lang not used
    {"char*",    "Description15"},                                // 185      m_description_lang not used
    {"uint32",   "DescriptionFlags"},                             // 186      not used
    {"char*",    "ToolTip0"},                                     // 187      m_auraDescription_lang not used
    {"char*",    "ToolTip1"},                                     // 188      m_auraDescription_lang not used
    {"char*",    "ToolTip2"},                                     // 189      m_auraDescription_lang not used
    {"char*",    "ToolTip3"},                                     // 190      m_auraDescription_lang not used
    {"char*",    "ToolTip4"},                                     // 191      m_auraDescription_lang not used
    {"char*",    "ToolTip5"},                                     // 192      m_auraDescription_lang not used
    {"char*",    "ToolTip6"},                                     // 193      m_auraDescription_lang not used
    {"char*",    "ToolTip7"},                                     // 194      m_auraDescription_lang not used
    {"char*",    "ToolTip8"},                                     // 195      m_auraDescription_lang not used
    {"char*",    "ToolTip9"},                                     // 196      m_auraDescription_lang not used
    {"char*",    "ToolTip10"},                                    // 197      m_auraDescription_lang not used
    {"char*",    "ToolTip11"},                                    // 198      m_auraDescription_lang not used
    {"char*",    "ToolTip12"},                                    // 199      m_auraDescription_lang not used
    {"char*",    "ToolTip13"},                                    // 200      m_auraDescription_lang not used
    {"char*",    "ToolTip14"},                                    // 201      m_auraDescription_lang not used
    {"char*",    "ToolTip15"},                                    // 202      m_auraDescription_lang not used
    {"uint32",   "ToolTipFlags"},                                 // 203      not used
    {"uint32",   "ManaCostPercentage"},                           // 204      m_manaCostPct
    {"uint32",   "StartRecoveryCategory"},                        // 205      m_startRecoveryCategory
    {"uint32",   "StartRecoveryTime"},                            // 206      m_startRecoveryTime
    {"uint32",   "MaxTargetLevel"},                               // 207      m_maxTargetLevel
    {"uint32",   "SpellFamilyName"},                              // 208      m_spellClassSet
    {"uint32",   "SpellFamilyFlags0"},                            // 209      m_spellClassMask NOTE: size is 12 bytes!!!
    {"uint32",   "SpellFamilyFlags1"},                            // 210      m_spellClassMask NOTE: size is 12 bytes!!!
    {"uint32",   "SpellFamilyFlags2"},                            // 211      addition to m_spellClassMask
    {"uint32",   "MaxAffectedTargets"},                           // 212      m_maxTargets
    {"uint32",   "DmgClass"},                                     // 213      m_defenseType
    {"uint32",   "PreventionType"},                               // 214      m_preventionType
    {"uint32",   "StanceBarOrder"},                               // 215      m_stanceBarOrder not used
    {"float",    "DmgMultiplier0"},                               // 216      m_effectChainAmplitude
    {"float",    "DmgMultiplier1"},                               // 217      m_effectChainAmplitude
    {"float",    "DmgMultiplier2"},                               // 218      m_effectChainAmplitude
    {"uint32",   "MinFactionId"},                                 // 219      m_minFactionID not used
    {"uint32",   "MinReputation"},                                // 220      m_minReputation not used
    {"uint32",   "RequiredAuraVision"},                           // 221      m_requiredAuraVision not used
    {"uint32",   "TotemCategory0"},                               // 222      m_requiredTotemCategoryID
    {"uint32",   "TotemCategory1"},                               // 223      m_requiredTotemCategoryID
    {"int32",    "AreaGroupId"},                                  // 224      m_requiredAreaGroupId
    {"uint32",   "SchoolMask"},                                   // 225      m_schoolMask
    {"uint32",   "runeCostID"},                                   // 226      m_runeCostID
    {"uint32",   "spellMissileID"},                               // 227      m_spellMissileID not used
    {"uint32",   "PowerDisplayId"},                               // 228      PowerDisplay.dbc, new in 3.1
    {"float",    "unk_320_40"},                                   // 229      3.2.0
    {"float",    "unk_320_41"},                                   // 230      3.2.0
    {"float",    "unk_320_42"},                                   // 231      3.2.0
    {"uint32",   "spellDescriptionVariableID"},                   // 232      3.2.0
    {"uint32",   "SpellDifficultyId"}                             // 233      3.3.0
};

char const *SPELL_TABLE_INDEX = spell_translation[0][1];

#endif
