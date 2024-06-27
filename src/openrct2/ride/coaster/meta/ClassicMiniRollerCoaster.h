/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../../RideData.h"
#include "../../ShopItem.h"
#include "../../Track.h"

// clang-format off
constexpr RideTypeDescriptor ClassicMiniRollerCoasterRTD =
{
    .Category = RIDE_CATEGORY_ROLLERCOASTER,
    .StartTrackPiece = TrackElemType::EndStation,
    .TrackPaintFunctions = TrackDrawerDescriptor({
        .Drawer = GetTrackPaintFunctionJuniorRC,
        .EnabledTrackPieces = { TRACK_STRAIGHT, TRACK_STATION_END, TRACK_LIFT_HILL, TRACK_LIFT_HILL_CURVE, TRACK_FLAT_ROLL_BANKING, TRACK_SLOPE, TRACK_SLOPE_STEEP_UP, TRACK_SLOPE_STEEP_DOWN, TRACK_SLOPE_LONG, TRACK_SLOPE_CURVE, TRACK_S_BEND, TRACK_CURVE_SMALL, TRACK_CURVE, TRACK_CURVE_LARGE, TRACK_HELIX_DOWN_BANKED_HALF, TRACK_HELIX_UP_BANKED_HALF, TRACK_BRAKES, TRACK_BLOCK_BRAKES, TRACK_BOOSTER, TRACK_DIAG_BRAKES, TRACK_DIAG_BLOCK_BRAKES},
        .ExtraTrackPieces = {TRACK_ON_RIDE_PHOTO},
    }),
    .InvertedTrackPaintFunctions = {},
    .Flags = RIDE_TYPE_FLAGS_TRACK_HAS_3_COLOURS | RIDE_TYPE_FLAG_HAS_LEAVE_WHEN_ANOTHER_VEHICLE_ARRIVES_AT_STATION |
                     RIDE_TYPE_FLAGS_COMMON_COASTER | RIDE_TYPE_FLAGS_COMMON_COASTER_NON_ALT |
                     RIDE_TYPE_FLAG_ALLOW_DOORS_ON_TRACK | RIDE_TYPE_FLAG_PEEP_CHECK_GFORCES | RIDE_TYPE_FLAG_ALLOW_MULTIPLE_CIRCUITS |
                     RIDE_TYPE_FLAG_ALLOW_REVERSED_TRAINS,
    .RideModes = EnumsToFlags(RideMode::ContinuousCircuit, RideMode::ContinuousCircuitBlockSectioned, RideMode::ReverseInclineLaunchedShuttle),
    .DefaultMode = RideMode::ContinuousCircuit,
    .BoosterSettings = { 17, 16 },
    .LegacyBoosterSettings = { 17, 16, 1 },
    .Naming = { STR_RIDE_NAME_CLASSIC_MINI_ROLLER_COASTER, STR_RIDE_DESCRIPTION_CLASSIC_MINI_COASTER },
    .NameConvention = { RideComponentType::Train, RideComponentType::Track, RideComponentType::Station },
    .EnumName = nameof(RIDE_TYPE_CLASSIC_MINI_ROLLER_COASTER),
    .AvailableBreakdowns = (1 << BREAKDOWN_SAFETY_CUT_OUT) | (1 << BREAKDOWN_RESTRAINTS_STUCK_CLOSED) | (1 << BREAKDOWN_RESTRAINTS_STUCK_OPEN) | (1 << BREAKDOWN_VEHICLE_MALFUNCTION) | (1 << BREAKDOWN_BRAKES_FAILURE),
    .Heights = { 15, 24, 4, 7, },
    .MaxMass = 18,
    .LiftData = { OpenRCT2::Audio::SoundId::LiftFrictionWheels, 4, 6 },
    .RatingsMultipliers = { 50, 30, 10 },
    .UpkeepCosts = { 40, 20, 80, 8, 3, 5 },
    .BuildCosts = { 22.50_GBP, 2.00_GBP, 40, },
    .DefaultPrices = { 20, 20 },
    .DefaultMusic = MUSIC_OBJECT_SUMMER,
    .PhotoItem = ShopItem::Photo,
    .BonusValue = 60,
    .ColourPresets = TRACK_COLOUR_PRESETS(
        { COLOUR_YELLOW, COLOUR_YELLOW, COLOUR_SATURATED_BROWN },
        { COLOUR_BORDEAUX_RED, COLOUR_BORDEAUX_RED, COLOUR_DARK_OLIVE_GREEN },
        { COLOUR_TEAL, COLOUR_YELLOW, COLOUR_TEAL },
        { COLOUR_SATURATED_BROWN, COLOUR_SATURATED_BROWN, COLOUR_OLIVE_GREEN },
        { COLOUR_BLACK, COLOUR_LIGHT_BLUE, COLOUR_BLACK },
    ),
    .ColourPreview = { SPR_RIDE_DESIGN_PREVIEW_JUNIOR_ROLLER_COASTER_TRACK, SPR_RIDE_DESIGN_PREVIEW_JUNIOR_ROLLER_COASTER_SUPPORTS },
    .ColourKey = RideColourKey::Ride,
    .Name = "classic_mini_rc",
    .RatingsData = 
    {
        RatingsCalculationType::Normal,
        { RIDE_RATING(2, 40), RIDE_RATING(2, 80), RIDE_RATING(1, 90) },
        13,
        -1,
        false,
        {
            { RatingsModifierType::BonusLength,           6000,             764, 0, 0 },
            { RatingsModifierType::BonusSynchronisation,  0,                RIDE_RATING(0, 40), RIDE_RATING(0, 05), 0 },
            { RatingsModifierType::BonusTrainLength,      0,                187245, 0, 0 },
            { RatingsModifierType::BonusMaxSpeed,         0,                44281, 88562, 35424 },
            { RatingsModifierType::BonusAverageSpeed,     0,                291271, 436906, 0 },
            { RatingsModifierType::BonusDuration,         150,              26214, 0, 0 },
            { RatingsModifierType::BonusGForces,          0,                20480, 23831, 49648 },
            { RatingsModifierType::BonusTurns,            0,                26749, 34767, 45749 },
            { RatingsModifierType::BonusDrops,            0,                29127, 46811, 49152 },
            { RatingsModifierType::BonusSheltered,        0,                25700, 30583, 35108 },
            { RatingsModifierType::BonusReversedTrains,   0,                2, 10, 12 },
            { RatingsModifierType::BonusProximity,        0,                20130, 0, 0 },
            { RatingsModifierType::BonusScenery,          0,                9760, 0, 0 },
            { RatingsModifierType::RequirementDropHeight, 6,                2, 2, 2 },
            { RatingsModifierType::RequirementMaxSpeed,   0x70000,          2, 2, 2 },
            { RatingsModifierType::RequirementNumDrops,   2,                2, 2, 2 },
            { RatingsModifierType::PenaltyLateralGs,      0,                20480, 23831, 49648 },
        },
    },
};
// clang-format on
