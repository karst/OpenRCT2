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
constexpr RideTypeDescriptor LogFlumeRTD =
{
    .Category = RIDE_CATEGORY_WATER,
    .StartTrackPiece = TrackElemType::EndStation,
    .TrackPaintFunctions = TrackDrawerDescriptor({
        .Drawer = GetTrackPaintFunctionLogFlume,
        .EnabledTrackPieces = {TRACK_STRAIGHT, TRACK_STATION_END, TRACK_SLOPE, TRACK_S_BEND, TRACK_CURVE_SMALL, TRACK_ON_RIDE_PHOTO, TRACK_LOG_FLUME_REVERSER, TRACK_SLOPE_STEEP_DOWN},
        .ExtraTrackPieces = {},
    }),
    .InvertedTrackPaintFunctions = {},
    .Flags = RIDE_TYPE_FLAGS_TRACK_HAS_3_COLOURS | RIDE_TYPE_FLAG_HAS_LEAVE_WHEN_ANOTHER_VEHICLE_ARRIVES_AT_STATION |
                     RIDE_TYPE_FLAG_CAN_SYNCHRONISE_ADJACENT_STATIONS | RIDE_TYPE_FLAG_HAS_DATA_LOGGING | RIDE_TYPE_FLAG_HAS_DROPS |
                     RIDE_TYPE_FLAG_HAS_LOAD_OPTIONS | RIDE_TYPE_FLAG_PEEP_WILL_RIDE_AGAIN | RIDE_TYPE_FLAG_HAS_VEHICLE_COLOURS | RIDE_TYPE_FLAG_HAS_TRACK |
                     RIDE_TYPE_FLAG_SUPPORTS_MULTIPLE_TRACK_COLOUR | RIDE_TYPE_FLAG_ALLOW_MUSIC | RIDE_TYPE_FLAG_HAS_ENTRANCE_EXIT |
                     RIDE_TYPE_FLAG_ALLOW_MORE_VEHICLES_THAN_STATION_FITS | RIDE_TYPE_FLAG_HAS_AIR_TIME | RIDE_TYPE_FLAG_SHOW_IN_TRACK_DESIGNER |
                     RIDE_TYPE_FLAG_INTERESTING_TO_LOOK_AT,
    .RideModes = EnumsToFlags(RideMode::ContinuousCircuit),
    .DefaultMode = RideMode::ContinuousCircuit,
    .Naming = { STR_RIDE_NAME_LOG_FLUME, STR_RIDE_DESCRIPTION_LOG_FLUME },
    .NameConvention = { RideComponentType::Boat, RideComponentType::Track, RideComponentType::Station },
    .EnumName = nameof(RIDE_TYPE_LOG_FLUME),
    .AvailableBreakdowns = (1 << BREAKDOWN_SAFETY_CUT_OUT) | (1 << BREAKDOWN_CONTROL_FAILURE),
    .Heights = { 10, 24, 7, 9, },
    .MaxMass = 255,
    .LiftData = { OpenRCT2::Audio::SoundId::LiftFlume, 5, 5 },
    .RatingsMultipliers = { 80, 34, 6 },
    .UpkeepCosts = { 80, 20, 0, 9, 0, 10 },
    .BuildCosts = { 22.50_GBP, 2.50_GBP, 40, },
    .DefaultPrices = { 20, 20 },
    .DefaultMusic = MUSIC_OBJECT_WATER,
    .PhotoItem = ShopItem::Photo4,
    .BonusValue = 65,
    .ColourPresets = TRACK_COLOUR_PRESETS(
        { COLOUR_DARK_BROWN, COLOUR_DARK_BROWN, COLOUR_GREY },
        { COLOUR_OLIVE_GREEN, COLOUR_BLACK, COLOUR_GREY },
    ),
    .ColourPreview = { SPR_RIDE_DESIGN_PREVIEW_LOG_FLUME_TRACK, SPR_RIDE_DESIGN_PREVIEW_LOG_FLUME_SUPPORTS },
    .ColourKey = RideColourKey::Ride,
    .Name = "log_flume",
    .RatingsData = 
    {
        RatingsCalculationType::Normal,
        { RIDE_RATING(1, 50), RIDE_RATING(0, 55), RIDE_RATING(0, 30) },
        15,
        -1,
        false,
        {
            { RatingsModifierType::BonusLength,           2000,             7208, 0, 0 },
            { RatingsModifierType::BonusSynchronisation,  0,                RIDE_RATING(0, 40), RIDE_RATING(0, 05), 0 },
            { RatingsModifierType::BonusMaxSpeed,         0,                531372, 655360, 301111 },
            { RatingsModifierType::BonusDuration,         300,              13107, 0, 0 },
            { RatingsModifierType::BonusTurns,            0,                22291, 20860, 4574 },
            { RatingsModifierType::BonusDrops,            0,                69905, 62415, 49152 },
            { RatingsModifierType::BonusSheltered,        0,                16705, 30583, 35108 },
            { RatingsModifierType::BonusProximity,        0,                22367, 0, 0 },
            { RatingsModifierType::BonusScenery,          0,                11155, 0, 0 },
            { RatingsModifierType::RequirementDropHeight, 6,                2, 2, 2 },
        },
    },
    .UpdateRotating = UpdateRotatingDefault,
    .LightFXAddLightsMagicVehicle = nullptr,
    .StartRideMusic = OpenRCT2::RideAudio::DefaultStartRideMusicChannel,
    .DesignCreateMode = TrackDesignCreateMode::Default,
    .MusicUpdateFunction = DefaultMusicUpdate,
    .Classification = RideClassification::Ride,
    .UpdateLeaveEntrance = PeepUpdateRideLeaveEntranceDefault,
    .SpecialElementRatingAdjustment = SpecialTrackElementRatingsAjustment_LogFlume,
};
// clang-format on
