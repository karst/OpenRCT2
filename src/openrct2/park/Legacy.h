/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../object/Object.h"

#include <cstdint>
#include <optional>
#include <string_view>

namespace OpenRCT2::RCT2
{
    struct FootpathMapping;
}
struct ObjectEntryDescriptor;
class ObjectList;
using ride_type_t = uint16_t;
using track_type_t = uint16_t;

std::string_view MapToNewObjectIdentifier(std::string_view s);
std::optional<std::string_view> GetDATPathName(std::string_view newPathName);
const OpenRCT2::RCT2::FootpathMapping* GetFootpathMapping(const ObjectEntryDescriptor& desc);
void UpdateFootpathsFromMapping(
    ObjectEntryIndex* pathToSurfaceMap, ObjectEntryIndex* pathToQueueSurfaceMap, ObjectEntryIndex* pathToRailingsMap,
    ObjectList& requiredObjects, ObjectEntryIndex& surfaceCount, ObjectEntryIndex& railingCount, ObjectEntryIndex entryIndex,
    const OpenRCT2::RCT2::FootpathMapping* footpathMapping);

/**
 * If new pieces get added to existing ride types, this could cause existing parks to change appearance,
 * since the formerly unrendered pieces were not explicitly set invisible.
 * To avoid this, this function will return true if the piece is question was added after the park was created,
 * so that import code can properly set the visibility.
 *
 * @param rideType The OpenRCT2 ride type
 * @param trackType The OpenRCT2 track type
 * @param parkFileVersion The current park file version. Pass -1 when converting S4 or S6.
 * @return
 */
bool TrackTypeMustBeMadeInvisible(ride_type_t rideType, track_type_t trackType, int32_t parkFileVersion = -1);

/**
 * Water rides used to be very slow. Convert their rollers to lift, so that the user can speed them up if desired.
 *
 * @param rideType
 * @param trackType
 * @param parkFileVersion
 * @return
 */
bool TrackTypeMustBeMadeChained(ride_type_t rideType, track_type_t trackType, int32_t parkFileVersion = -1);

/**
 * Determine if the ride needs a roller-to-chain conversion.
 *
 * @param rideType
 * @return
 */
bool RideTypeHasConvertibleRollers(ride_type_t rideType);
