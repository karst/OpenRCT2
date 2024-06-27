/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "T6Exporter.h"

#include "../Context.h"
#include "../core/FileStream.h"
#include "../core/MemoryStream.h"
#include "../localisation/Localisation.h"
#include "../localisation/StringIds.h"
#include "../object/ObjectList.h"
#include "../rct12/SawyerChunkWriter.h"
#include "../rct2/RCT2.h"
#include "../ride/Ride.h"
#include "../ride/RideData.h"
#include "../ride/Station.h"
#include "../ride/Track.h"
#include "../ride/TrackData.h"
#include "../ride/TrackDesign.h"
#include "../ride/TrackDesignRepository.h"
#include "../windows/Intent.h"

#include <functional>

namespace RCT2
{
    T6Exporter::T6Exporter(TrackDesign* trackDesign)
        : _trackDesign(trackDesign)
    {
    }

    bool T6Exporter::SaveTrack(const utf8* path)
    {
        try
        {
            auto fs = OpenRCT2::FileStream(path, OpenRCT2::FILE_MODE_WRITE);
            return SaveTrack(&fs);
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("Unable to save track design: %s", e.what());
            return false;
        }
    }

    bool T6Exporter::SaveTrack(OpenRCT2::IStream* stream)
    {
        OpenRCT2::MemoryStream tempStream;
        tempStream.WriteValue<uint8_t>(OpenRCT2RideTypeToRCT2RideType(_trackDesign->type));
        tempStream.WriteValue<uint8_t>(_trackDesign->vehicleType);
        tempStream.WriteValue<uint32_t>(0);
        tempStream.WriteValue<uint8_t>(static_cast<uint8_t>(_trackDesign->rideMode));
        tempStream.WriteValue<uint8_t>((_trackDesign->colourScheme & 0x3) | (2 << 2));
        for (auto i = 0; i < RCT2::Limits::kMaxVehicleColours; i++)
        {
            tempStream.WriteValue<uint8_t>(_trackDesign->vehicleColours[i].Body);
            tempStream.WriteValue<uint8_t>(_trackDesign->vehicleColours[i].Trim);
        }
        tempStream.WriteValue<uint8_t>(0);
        auto entranceStyle = GetStationStyleFromIdentifier(_trackDesign->stationObjectIdentifier);
        tempStream.WriteValue<uint8_t>(entranceStyle);
        tempStream.WriteValue<uint8_t>(_trackDesign->totalAirTime);
        tempStream.WriteValue<uint8_t>(_trackDesign->departFlags);
        tempStream.WriteValue<uint8_t>(_trackDesign->numberOfTrains);
        tempStream.WriteValue<uint8_t>(_trackDesign->numberOfCarsPerTrain);
        tempStream.WriteValue<uint8_t>(_trackDesign->minWaitingTime);
        tempStream.WriteValue<uint8_t>(_trackDesign->maxWaitingTime);
        tempStream.WriteValue<uint8_t>(_trackDesign->operationSetting);
        tempStream.WriteValue<int8_t>(_trackDesign->maxSpeed);
        tempStream.WriteValue<int8_t>(_trackDesign->averageSpeed);
        tempStream.WriteValue<uint16_t>(_trackDesign->rideLength);
        tempStream.WriteValue<uint8_t>(_trackDesign->maxPositiveVerticalG);
        tempStream.WriteValue<int8_t>(_trackDesign->maxNegativeVerticalG);
        tempStream.WriteValue<uint8_t>(_trackDesign->maxLateralG);
        tempStream.WriteValue<uint8_t>(
            _trackDesign->type == RIDE_TYPE_MINI_GOLF ? _trackDesign->holes : _trackDesign->inversions);
        tempStream.WriteValue<uint8_t>(_trackDesign->drops);
        tempStream.WriteValue<uint8_t>(_trackDesign->highestDropHeight);
        tempStream.WriteValue<uint8_t>(_trackDesign->excitement);
        tempStream.WriteValue<uint8_t>(_trackDesign->intensity);
        tempStream.WriteValue<uint8_t>(_trackDesign->nausea);
        tempStream.WriteValue<money16>(ToMoney16(_trackDesign->upkeepCost));
        tempStream.WriteArray(_trackDesign->trackSpineColour, Limits::kNumColourSchemes);
        tempStream.WriteArray(_trackDesign->trackRailColour, Limits::kNumColourSchemes);
        tempStream.WriteArray(_trackDesign->trackSupportColour, Limits::kNumColourSchemes);
        tempStream.WriteValue<uint32_t>(0);
        tempStream.Write(&_trackDesign->vehicleObject.Entry, sizeof(RCTObjectEntry));
        tempStream.WriteValue<uint8_t>(_trackDesign->spaceRequiredX);
        tempStream.WriteValue<uint8_t>(_trackDesign->spaceRequiredY);
        for (auto i = 0; i < RCT2::Limits::kMaxVehicleColours; i++)
        {
            tempStream.WriteValue<uint8_t>(_trackDesign->vehicleColours[i].Tertiary);
        }
        tempStream.WriteValue<uint8_t>(_trackDesign->liftHillSpeed | (_trackDesign->numCircuits << 5));

        const auto& rtd = GetRideTypeDescriptor(_trackDesign->type);
        if (rtd.HasFlag(RIDE_TYPE_FLAG_IS_MAZE))
        {
            for (const auto& mazeElement : _trackDesign->mazeElements)
            {
                tempStream.WriteValue<int8_t>(mazeElement.location.x);
                tempStream.WriteValue<int8_t>(mazeElement.location.y);
                tempStream.WriteValue<uint16_t>(mazeElement.mazeEntry);
            }

            for (const auto& entranceElement : _trackDesign->entranceElements)
            {
                tempStream.WriteValue<int8_t>(entranceElement.location.x);
                tempStream.WriteValue<int8_t>(entranceElement.location.y);
                tempStream.WriteValue<int8_t>(entranceElement.location.direction);
                tempStream.WriteValue<int8_t>(
                    EnumValue(entranceElement.isExit ? TD46MazeElementType::Exit : TD46MazeElementType::Entrance));
            }

            tempStream.WriteValue<uint32_t>(0);
        }
        else
        {
            for (const auto& trackElement : _trackDesign->trackElements)
            {
                auto trackType = OpenRCT2TrackTypeToRCT2(trackElement.Type);
                if (trackType == TrackElemType::MultiDimInvertedUp90ToFlatQuarterLoop)
                {
                    trackType = TrackElemType::InvertedUp90ToFlatQuarterLoopAlias;
                }
                tempStream.WriteValue<uint8_t>(static_cast<uint8_t>(trackType));
                auto flags = ConvertToTD46Flags(trackElement);
                tempStream.WriteValue<uint8_t>(flags);
            }

            tempStream.WriteValue<uint8_t>(0xFF);

            for (const auto& entranceElement : _trackDesign->entranceElements)
            {
                tempStream.WriteValue<uint8_t>(
                    entranceElement.location.z == -1 ? static_cast<uint8_t>(0x80) : entranceElement.location.z);
                tempStream.WriteValue<uint8_t>(entranceElement.location.direction | (entranceElement.isExit << 7));
                auto xy = entranceElement.location.ToCoordsXY();
                tempStream.WriteValue<int16_t>(xy.x);
                tempStream.WriteValue<int16_t>(xy.y);
            }

            tempStream.WriteValue<uint8_t>(0xFF);
        }

        for (const auto& sceneryElement : _trackDesign->sceneryElements)
        {
            auto flags = sceneryElement.flags;
            if (sceneryElement.sceneryObject.Entry.GetType() == ObjectType::Walls)
            {
                flags &= ~0xFC;
                flags |= (sceneryElement.tertiaryColour << 2);
            }

            tempStream.Write(&sceneryElement.sceneryObject.Entry, sizeof(RCTObjectEntry));
            auto tileCoords = TileCoordsXYZ(sceneryElement.loc);
            tempStream.WriteValue<int8_t>(tileCoords.x);
            tempStream.WriteValue<int8_t>(tileCoords.y);
            tempStream.WriteValue<int8_t>(tileCoords.z);
            tempStream.WriteValue<uint8_t>(flags);
            tempStream.WriteValue<uint8_t>(sceneryElement.primaryColour);
            tempStream.WriteValue<uint8_t>(sceneryElement.secondaryColour);
        }

        tempStream.WriteValue<uint8_t>(0xFF);

        SawyerChunkWriter sawyerCoding(stream);
        sawyerCoding.WriteChunkTrack(tempStream.GetData(), tempStream.GetLength());
        return true;
    }
} // namespace RCT2
