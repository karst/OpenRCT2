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
constexpr RideTypeDescriptor InvertedRollerCoasterRTD =
{
    .Category = RIDE_CATEGORY_ROLLERCOASTER,
    .StartTrackPiece = TrackElemType::EndStation,
    .TrackPaintFunctions = TrackDrawerDescriptor({
        .Drawer = GetTrackPaintFunctionInvertedRC,
        .EnabledTrackPieces = {TRACK_STRAIGHT, TRACK_STATION_END, TRACK_LIFT_HILL, TRACK_FLAT_ROLL_BANKING, TRACK_VERTICAL_LOOP, TRACK_SLOPE, TRACK_SLOPE_STEEP_UP, TRACK_SLOPE_STEEP_DOWN, TRACK_SLOPE_CURVE, TRACK_SLOPE_CURVE_STEEP, TRACK_S_BEND, TRACK_CURVE_SMALL, TRACK_CURVE, TRACK_CURVE_LARGE, TRACK_TWIST, TRACK_HALF_LOOP, TRACK_CORKSCREW, TRACK_HELIX_DOWN_BANKED_QUARTER, TRACK_HELIX_UP_BANKED_QUARTER, TRACK_BRAKES, TRACK_ON_RIDE_PHOTO, TRACK_HALF_LOOP_LARGE, TRACK_BLOCK_BRAKES, TRACK_SLOPE_ROLL_BANKING, TRACK_DIAG_BRAKES, TRACK_DIAG_BLOCK_BRAKES},
        .ExtraTrackPieces = {TRACK_BOOSTER},
    }),
    .InvertedTrackPaintFunctions = {},
    .Flags = RIDE_TYPE_FLAGS_TRACK_HAS_3_COLOURS | RIDE_TYPE_FLAG_HAS_LEAVE_WHEN_ANOTHER_VEHICLE_ARRIVES_AT_STATION |
                     RIDE_TYPE_FLAGS_COMMON_COASTER | RIDE_TYPE_FLAGS_COMMON_COASTER_NON_ALT |
                     RIDE_TYPE_FLAG_PEEP_CHECK_GFORCES | RIDE_TYPE_FLAG_ALLOW_MULTIPLE_CIRCUITS | RIDE_TYPE_FLAG_IS_SUSPENDED |
                     RIDE_TYPE_FLAG_ALLOW_REVERSED_TRAINS,
    .RideModes = EnumsToFlags(RideMode::ContinuousCircuit, RideMode::ContinuousCircuitBlockSectioned, RideMode::PoweredLaunchPasstrough, RideMode::PoweredLaunch),
    .DefaultMode = RideMode::ContinuousCircuit,
    .OperatingSettings = { 7, 27 },
    .BoosterSettings = { 0, 38 },
    .LegacyBoosterSettings = { 0, 38 },
    .Naming = { STR_RIDE_NAME_INVERTED_ROLLER_COASTER, STR_RIDE_DESCRIPTION_INVERTED_ROLLER_COASTER },
    .NameConvention = { RideComponentType::Train, RideComponentType::Track, RideComponentType::Station },
    .EnumName = nameof(RIDE_TYPE_INVERTED_ROLLER_COASTER),
    .AvailableBreakdowns = (1 << BREAKDOWN_SAFETY_CUT_OUT) | (1 << BREAKDOWN_RESTRAINTS_STUCK_CLOSED) | (1 << BREAKDOWN_RESTRAINTS_STUCK_OPEN) | (1 << BREAKDOWN_VEHICLE_MALFUNCTION) | (1 << BREAKDOWN_BRAKES_FAILURE),
    .Heights = { 42, 40, 29, 8, },
    .MaxMass = 27,
    .LiftData = { OpenRCT2::Audio::SoundId::LiftBM, 5, 7 },
    .RatingsMultipliers = { 50, 30, 10 },
    .UpkeepCosts = { 40, 20, 80, 13, 3, 10 },
    .BuildCosts = { 65.00_GBP, 2.50_GBP, 50, },
    .DefaultPrices = { 20, 20 },
    .DefaultMusic = MUSIC_OBJECT_TECHNO,
    .PhotoItem = ShopItem::Photo2,
    .BonusValue = 100,
    .ColourPresets = TRACK_COLOUR_PRESETS(
        { COLOUR_BORDEAUX_RED, COLOUR_BORDEAUX_RED, COLOUR_BLACK },
        { COLOUR_WHITE, COLOUR_YELLOW, COLOUR_WHITE },
        { COLOUR_SALMON_PINK, COLOUR_SALMON_PINK, COLOUR_GREY },
        { COLOUR_BLACK, COLOUR_BRIGHT_RED, COLOUR_BLACK },
        { COLOUR_SATURATED_BROWN, COLOUR_WHITE, COLOUR_SATURATED_BROWN },
        { COLOUR_YELLOW, COLOUR_YELLOW, COLOUR_BLACK },
        { COLOUR_BLACK, COLOUR_BLACK, COLOUR_DULL_PURPLE_LIGHT }, // Great Bear
        { COLOUR_DARK_BLUE, COLOUR_DARK_BLUE, COLOUR_SATURATED_BROWN_LIGHT }, // Montu / Oziris
        { COLOUR_DARK_PINK, COLOUR_DARK_PINK, COLOUR_SATURATED_PURPLE_DARK }, // Banshee (Renders)
    ),
    .ColourPreview = { SPR_RIDE_DESIGN_PREVIEW_INVERTED_ROLLER_COASTER_TRACK, SPR_RIDE_DESIGN_PREVIEW_INVERTED_ROLLER_COASTER_SUPPORTS },
    .ColourKey = RideColourKey::Ride,
    .Name = "inverted_rc",
    .RatingsData =
    {
        RatingsCalculationType::Normal,
        { RIDE_RATING(3, 60), RIDE_RATING(2, 80), RIDE_RATING(3, 20) },
        17,
        -1,
        true,
        {
            { RatingsModifierType::BonusLength,           6000,             764, 0, 0 },
            { RatingsModifierType::BonusSynchronisation,  0,                RIDE_RATING(0, 42), RIDE_RATING(0, 05), 0 },
            { RatingsModifierType::BonusTrainLength,      0,                187245, 0, 0 },
            { RatingsModifierType::BonusMaxSpeed,         0,                44281, 88562, 35424 },
            { RatingsModifierType::BonusAverageSpeed,     0,                291271, 436906, 0 },
            { RatingsModifierType::BonusDuration,         150,              26214, 0, 0 },
            { RatingsModifierType::BonusGForces,          0,                24576, 29789, 55606 },
            { RatingsModifierType::BonusTurns,            0,                26749, 29552, 57186 },
            { RatingsModifierType::BonusDrops,            0,                29127, 39009, 49152 },
            { RatingsModifierType::BonusSheltered,        0,                15420, 15291, 35108 },
            { RatingsModifierType::BonusReversedTrains,   0,                2, 12, 20 },
            { RatingsModifierType::BonusProximity,        0,                15657, 0, 0 },
            { RatingsModifierType::BonusScenery,          0,                8366, 0, 0 },
            { RatingsModifierType::RequirementDropHeight, 12,               2, 2, 2 },
            { RatingsModifierType::RequirementMaxSpeed,   0xA0000,          2, 2, 2 },
            { RatingsModifierType::RequirementNegativeGs, FIXED_2DP(0, 30), 2, 2, 2 },
            { RatingsModifierType::PenaltyLateralGs,      0,                24576, 29789, 55606 },
        },
    },
};
// clang-format on
