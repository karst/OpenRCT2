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
constexpr RideTypeDescriptor MultiLoopingRollerCoasterRTD =
{
    .Category = RIDE_CATEGORY_ROLLERCOASTER,
    .StartTrackPiece = TrackElemType::EndStation,
    .TrackPaintFunctions = TrackDrawerDescriptor({
        .Drawer = GetTrackPaintFunctionInMaTriangleAlt,
        .EnabledTrackPieces = {TRACK_STRAIGHT, TRACK_STATION_END, TRACK_FLAT_ROLL_BANKING, TRACK_SLOPE, TRACK_SLOPE_STEEP_UP, TRACK_SLOPE_STEEP_DOWN, TRACK_SLOPE_CURVE, TRACK_SLOPE_CURVE_STEEP, TRACK_S_BEND, TRACK_CURVE_SMALL, TRACK_CURVE, TRACK_CURVE_LARGE, TRACK_HELIX_DOWN_BANKED_HALF, TRACK_HELIX_UP_BANKED_HALF, TRACK_BRAKES, TRACK_ON_RIDE_PHOTO, TRACK_BLOCK_BRAKES, TRACK_SLOPE_ROLL_BANKING, TRACK_SLOPE_STEEP_LONG, TRACK_SLOPE_CURVE_BANKED, TRACK_SLOPE_CURVE_LARGE, TRACK_LIFT_HILL, TRACK_SLOPE_VERTICAL, TRACK_CURVE_VERTICAL, TRACK_BARREL_ROLL, TRACK_QUARTER_LOOP, TRACK_HALF_LOOP, TRACK_HALF_LOOP_MEDIUM, TRACK_HALF_LOOP_LARGE, TRACK_VERTICAL_LOOP, TRACK_CORKSCREW, TRACK_CORKSCREW_LARGE, TRACK_ZERO_G_ROLL, TRACK_ZERO_G_ROLL_LARGE},
        .ExtraTrackPieces = {TRACK_LIFT_HILL_CABLE, TRACK_BOOSTER, TRACK_POWERED_LIFT},
    }),
    .InvertedTrackPaintFunctions = {},
    .Flags = RIDE_TYPE_FLAGS_TRACK_HAS_3_COLOURS | RIDE_TYPE_FLAG_HAS_LEAVE_WHEN_ANOTHER_VEHICLE_ARRIVES_AT_STATION |
                     RIDE_TYPE_FLAGS_COMMON_COASTER | RIDE_TYPE_FLAGS_COMMON_COASTER_NON_ALT |
                     RIDE_TYPE_FLAG_PEEP_CHECK_GFORCES | RIDE_TYPE_FLAG_ALLOW_MULTIPLE_CIRCUITS | RIDE_TYPE_FLAG_ALLOW_CABLE_LIFT_HILL |
                     RIDE_TYPE_FLAG_ALLOW_REVERSED_TRAINS,
    .RideModes = EnumsToFlags(RideMode::ContinuousCircuit, RideMode::ContinuousCircuitBlockSectioned),
    .DefaultMode = RideMode::ContinuousCircuit,
    .OperatingSettings = { 10, 27 },
    .TrackSpeedSettings = { 60, 60 },
    .BoosterSettings = { 17, 68 },
    .LegacyBoosterSettings = { 17, 68, 4 },
    .Naming = { STR_RIDE_NAME_MULTI_LOOPING_ROLLER_COASTER, STR_RIDE_DESCRIPTION_MULTI_LOOPING_ROLLER_COASTER },
    .NameConvention = { RideComponentType::Train, RideComponentType::Track, RideComponentType::Station },
    .EnumName = nameof(RIDE_TYPE_MULTI_LOOPING_ROLLER_COASTER),
    .AvailableBreakdowns = (1 << BREAKDOWN_SAFETY_CUT_OUT) | (1 << BREAKDOWN_RESTRAINTS_STUCK_CLOSED) | (1 << BREAKDOWN_RESTRAINTS_STUCK_OPEN) | (1 << BREAKDOWN_VEHICLE_MALFUNCTION) | (1 << BREAKDOWN_BRAKES_FAILURE),
    .Heights = { 30, 24, 9, 11, },
    .MaxMass = 31,
    .LiftData = { OpenRCT2::Audio::SoundId::LiftClassic, 5, 13 },
    .RatingsMultipliers = { 50, 32, 10 },
    .UpkeepCosts = { 10, 20, 80, 12, 3, 40 },
    .BuildCosts = { 57.00_GBP, 2.50_GBP, 55, },
    .DefaultPrices = { 20, 20 },
    .DefaultMusic = MUSIC_OBJECT_MECHANICAL,
    .PhotoItem = ShopItem::Photo,
    .BonusValue = 120,
    .ColourPresets = TRACK_COLOUR_PRESETS(
        { COLOUR_AQUA_DARK, COLOUR_AQUA_DARK, COLOUR_WHITE }, // Altair
        { COLOUR_YELLOW, COLOUR_YELLOW, COLOUR_DARK_GREEN }, // Lightspeed
        { COLOUR_GREY, COLOUR_GREY, COLOUR_DULL_BROWN_LIGHT }, // Colossus
        { COLOUR_WHITE, COLOUR_GREY, COLOUR_BLACK }, // Sik
    ),
    .ColourPreview = { SPR_RIDE_DESIGN_PREVIEW_GIGA_COASTER_TRACK, SPR_RIDE_DESIGN_PREVIEW_GIGA_COASTER_SUPPORTS },
    .ColourKey = RideColourKey::Ride,
    .Name = "multi_loop_rc",
    .RatingsData =
    {
        RatingsCalculationType::Normal,
        { RIDE_RATING(2, 93), RIDE_RATING(0, 98), RIDE_RATING(0, 50) },
        15,
        -1,
        false,
        {
            { RatingsModifierType::BonusLength,           6000,             764, 0, 0 },
            { RatingsModifierType::BonusSynchronisation,  0,                RIDE_RATING(0, 40), RIDE_RATING(0, 05), 0 },
            { RatingsModifierType::BonusTrainLength,      0,                140434, 0, 0 },
            { RatingsModifierType::BonusMaxSpeed,         0,                43366, 88019, 35424 },
            { RatingsModifierType::BonusAverageSpeed,     0,                291271, 436906, 0 },
            { RatingsModifierType::BonusDuration,         150,              26214, 0, 0 },
            { RatingsModifierType::BonusGForces,          0,                36864, 30384, 49648 },
            { RatingsModifierType::BonusTurns,            0,                26235, 34767, 45749 },
            { RatingsModifierType::BonusDrops,            0,                29690, 46811, 49152 },
            { RatingsModifierType::BonusInversions,       0,                69420, -20000, -15000 },
            { RatingsModifierType::BonusSheltered,        0,                15420, 32768, 35108 },
            { RatingsModifierType::BonusReversedTrains,   0,                2, 20, 20 },
            { RatingsModifierType::BonusProximity,        0,                20130, 0, 0 },
            { RatingsModifierType::BonusScenery,          0,                6693, 0, 0 },
            { RatingsModifierType::RequirementDropHeight, 16,               2, 2, 2 },
            { RatingsModifierType::RequirementMaxSpeed,   0xA0000,          2, 2, 2 },
            { RatingsModifierType::RequirementNegativeGs, FIXED_2DP(0, 40), 2, 2, 2 },
            { RatingsModifierType::RequirementNumDrops,   2,                2, 2, 2 },
            { RatingsModifierType::RequirementInversions, 2,                2, 1, 1 },
            { RatingsModifierType::PenaltyLateralGs,      0,                24576, 34201, 49648 },
        },
    },
};
// clang-format on
