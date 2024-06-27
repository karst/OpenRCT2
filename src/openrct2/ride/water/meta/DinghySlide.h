/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../../../sprites.h"
#include "../../RideData.h"
#include "../../ShopItem.h"
#include "../../Track.h"

// clang-format off
constexpr RideTypeDescriptor DinghySlideRTD =
{
    .Category = RIDE_CATEGORY_WATER,
    .StartTrackPiece = TrackElemType::EndStation,
    .TrackPaintFunctions = TrackDrawerDescriptor(
        {
            .Drawer = GetTrackPaintFunctionDinghySlide,
            .EnabledTrackPieces = { TRACK_STRAIGHT, TRACK_STATION_END, TRACK_LIFT_HILL, TRACK_SLOPE, TRACK_SLOPE_STEEP_UP, TRACK_SLOPE_STEEP_DOWN, TRACK_S_BEND, TRACK_CURVE_SMALL, TRACK_CURVE },
            .ExtraTrackPieces = {},
        }, 
        {
            .Drawer = GetTrackPaintFunctionDinghySlideCovered,
            .EnabledTrackPieces = {TrackElemType::Flat, TrackElemType::Up25, TrackElemType::Up60, TrackElemType::FlatToUp25, TrackElemType::Up25ToUp60, TrackElemType::Up60ToUp25, TrackElemType::Up25ToFlat, TrackElemType::Down25, TrackElemType::Down60, TrackElemType::FlatToDown25, TrackElemType::Down25ToDown60, TrackElemType::Down60ToDown25, TrackElemType::Down25ToFlat, TrackElemType::LeftQuarterTurn5Tiles, TrackElemType::RightQuarterTurn5Tiles, TrackElemType::SBendLeft, TrackElemType::SBendRight, TrackElemType::LeftQuarterTurn3Tiles,TrackElemType::RightQuarterTurn3Tiles},
            .ExtraTrackPieces = {},
        }
    ),
    .InvertedTrackPaintFunctions = {},
    .Flags = RIDE_TYPE_FLAGS_TRACK_HAS_3_COLOURS | RIDE_TYPE_FLAG_HAS_LEAVE_WHEN_ANOTHER_VEHICLE_ARRIVES_AT_STATION |
                     RIDE_TYPE_FLAG_CAN_SYNCHRONISE_ADJACENT_STATIONS | RIDE_TYPE_FLAG_HAS_G_FORCES |
                     RIDE_TYPE_FLAG_HAS_DATA_LOGGING | RIDE_TYPE_FLAG_HAS_DROPS | RIDE_TYPE_FLAG_TRACK_ELEMENTS_HAVE_TWO_VARIETIES |
                     RIDE_TYPE_FLAG_HAS_LOAD_OPTIONS | RIDE_TYPE_FLAG_PEEP_WILL_RIDE_AGAIN | RIDE_TYPE_FLAG_HAS_VEHICLE_COLOURS |
                     RIDE_TYPE_FLAG_CHECK_FOR_STALLING | RIDE_TYPE_FLAG_HAS_TRACK | RIDE_TYPE_FLAG_SUPPORTS_MULTIPLE_TRACK_COLOUR |
                     RIDE_TYPE_FLAG_ALLOW_MUSIC | RIDE_TYPE_FLAG_HAS_ENTRANCE_EXIT | RIDE_TYPE_FLAG_HAS_AIR_TIME |
                     RIDE_TYPE_FLAG_SHOW_IN_TRACK_DESIGNER | RIDE_TYPE_FLAG_INTERESTING_TO_LOOK_AT,
    .RideModes = EnumsToFlags(RideMode::ContinuousCircuit),
    .DefaultMode = RideMode::ContinuousCircuit,
    .Naming = { STR_RIDE_NAME_DINGHY_SLIDE, STR_RIDE_DESCRIPTION_DINGHY_SLIDE },
    .NameConvention = { RideComponentType::Boat, RideComponentType::Track, RideComponentType::Station },
    .EnumName = nameof(RIDE_TYPE_DINGHY_SLIDE),
    .AvailableBreakdowns = (1 << BREAKDOWN_SAFETY_CUT_OUT),
    .Heights = { 15, 24, 5, 7, },
    .MaxMass = 5,
    .LiftData = { OpenRCT2::Audio::SoundId::LiftFrictionWheels, 4, 5 },
    .RatingsMultipliers = { 50, 30, 10 },
    .UpkeepCosts = { 40, 20, 80, 4, 3, 10 },
    .BuildCosts = { 20.00_GBP, 2.00_GBP, 40, },
    .DefaultPrices = { 20, 20 },
    .DefaultMusic = MUSIC_OBJECT_WATER,
    .PhotoItem = ShopItem::Photo4,
    .BonusValue = 55,
    .ColourPresets = TRACK_COLOUR_PRESETS(
        { COLOUR_DARK_GREEN, COLOUR_SATURATED_BROWN, COLOUR_DARK_GREEN },
        { COLOUR_TEAL, COLOUR_BORDEAUX_RED, COLOUR_TEAL },
        { COLOUR_BRIGHT_RED, COLOUR_GREY, COLOUR_SATURATED_RED },
    ),
    .ColourPreview = { SPR_RIDE_DESIGN_PREVIEW_DINGHY_SLIDE_TRACK, SPR_RIDE_DESIGN_PREVIEW_DINGHY_SLIDE_SUPPORTS },
    .ColourKey = RideColourKey::Ride,
    .Name = "dinghy_slide",
    .RatingsData = 
    {
        RatingsCalculationType::Normal,
        { RIDE_RATING(2, 70), RIDE_RATING(2, 00), RIDE_RATING(1, 50) },
        13,
        -1,
        false,
        {
            { RatingsModifierType::BonusLength,           6000,             764, 0, 0 },
            { RatingsModifierType::BonusSynchronisation,  0,                RIDE_RATING(0, 50), RIDE_RATING(0, 05), 0 },
            { RatingsModifierType::BonusTrainLength,      0,                187245, 0, 0 },
            { RatingsModifierType::BonusMaxSpeed,         0,                44281, 88562, 35424 },
            { RatingsModifierType::BonusAverageSpeed,     0,                291271, 436906, 0 },
            { RatingsModifierType::BonusDuration,         150,              26214, 0, 0 },
            { RatingsModifierType::BonusGForces,          0,                65536, 29789, 49648 },
            { RatingsModifierType::BonusTurns,            0,                26749, 34767, 45749 },
            { RatingsModifierType::BonusDrops,            0,                29127, 46811, 49152 },
            { RatingsModifierType::BonusSheltered,        0,                15420, 32768, 35108 },
            { RatingsModifierType::BonusProximity,        0,                11183, 0, 0 },
            { RatingsModifierType::BonusScenery,          0,                5577, 0, 0 },
            { RatingsModifierType::RequirementDropHeight, 12,               2, 2, 2 },
            { RatingsModifierType::RequirementMaxSpeed,   0x70000,          2, 2, 2 },
            { RatingsModifierType::RequirementLength,     0x8C0000,         2, 2, 2 },
            { RatingsModifierType::PenaltyLateralGs,      0,                65536, 29789, 49648 },
        },
    },
};
// clang-format on
