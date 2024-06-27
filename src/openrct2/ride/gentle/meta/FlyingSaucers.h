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
constexpr RideTypeDescriptor FlyingSaucersRTD =
{
    .Category = RIDE_CATEGORY_GENTLE,
    .StartTrackPiece = TrackElemType::FlatTrack4x4,
    .TrackPaintFunctions = TrackDrawerDescriptor({
        .Drawer = GetTrackPaintFunctionFlyingSaucers,
        .EnabledTrackPieces = {},
        .ExtraTrackPieces = {},
    }),
    .InvertedTrackPaintFunctions = {},
    .Flags = RIDE_TYPE_FLAG_HAS_TRACK_COLOUR_MAIN | RIDE_TYPE_FLAG_HAS_TRACK_COLOUR_ADDITIONAL |
                     RIDE_TYPE_FLAG_HAS_SINGLE_PIECE_STATION | RIDE_TYPE_FLAG_CANNOT_HAVE_GAPS | RIDE_TYPE_FLAG_NO_TEST_MODE |
                     RIDE_TYPE_FLAG_TRACK_NO_WALLS | RIDE_TYPE_FLAG_FLAT_RIDE | RIDE_TYPE_FLAG_HAS_VEHICLE_COLOURS |
                     RIDE_TYPE_FLAG_MUSIC_ON_DEFAULT | RIDE_TYPE_FLAG_ALLOW_MUSIC | RIDE_TYPE_FLAG_HAS_ENTRANCE_EXIT |
                     RIDE_TYPE_FLAG_SINGLE_SESSION | RIDE_TYPE_FLAG_INTERESTING_TO_LOOK_AT,
    .RideModes = EnumsToFlags(RideMode::Dodgems),
    .DefaultMode = RideMode::Dodgems,
    .OperatingSettings = { 20, 180 },
    .Naming = { STR_RIDE_NAME_FLYING_SAUCERS, STR_RIDE_DESCRIPTION_FLYING_SAUCERS },
    .NameConvention = { RideComponentType::Car, RideComponentType::Building, RideComponentType::Station },
    .EnumName = nameof(RIDE_TYPE_FLYING_SAUCERS),
    .AvailableBreakdowns = (1 << BREAKDOWN_SAFETY_CUT_OUT),
    .Heights = { 9, 48, 2, 2, },
    .MaxMass = 255,
    .LiftData = { OpenRCT2::Audio::SoundId::Null, 5, 5 },
    .RatingsMultipliers = { 50, 25, 0 },
    .UpkeepCosts = { 90, 1, 0, 5, 0, 0 },
    .BuildCosts = { 35.00_GBP, 2.00_GBP, 1, },
    .DefaultPrices = { 15, 0 },
    .DefaultMusic = MUSIC_OBJECT_ROCK_1,
    .PhotoItem = ShopItem::Photo,
    .BonusValue = 35,
    .ColourPresets = TRACK_COLOUR_PRESETS(
        { COLOUR_DARK_PURPLE, COLOUR_GREY, COLOUR_BLACK },
        { COLOUR_BLACK, COLOUR_YELLOW, COLOUR_BLACK },
        { COLOUR_YELLOW, COLOUR_SATURATED_RED, COLOUR_BLACK },
        { COLOUR_ICY_BLUE, COLOUR_WHITE, COLOUR_BLACK },
    ),
    .ColourPreview = { SPR_RIDE_DESIGN_PREVIEW_FLYING_SAUCERS_TRACK, 0 },
    .ColourKey = RideColourKey::Ride,
    .Name = "flying_saucers",
    .RatingsData = 
    {
        RatingsCalculationType::FlatRide,
        { RIDE_RATING(2, 40), RIDE_RATING(0, 55), RIDE_RATING(0, 39) },
        32,
        0,
        false,
        {
            // Special case, passing -2 to represent division by 2
            { RatingsModifierType::BonusOperationOption, 0, 1, -2, 0 }, 
            { RatingsModifierType::BonusNumTrains,       4, RIDE_RATING(0, 80), 0, 0 },
            { RatingsModifierType::BonusScenery,         0, 5577, 0, 0 },
        },
    },
};
// clang-format on
