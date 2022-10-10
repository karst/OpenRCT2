/*****************************************************************************
 * Copyright (c) 2014-2022 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "RideFreezeRatingAction.h"

RideFreezeRatingAction::RideFreezeRatingAction(RideId rideIndex, RideRatingType type, ride_rating value)
    : _rideIndex(rideIndex)
    , _type(type)
    , _value(value)
{
}

void RideFreezeRatingAction::Serialise(DataSerialiser& stream)
{
    GameAction::Serialise(stream);
    stream << DS_TAG(_rideIndex) << DS_TAG(_type) << DS_TAG(_value);
}

GameActions::Result RideFreezeRatingAction::Query() const
{
    auto ride = get_ride(_rideIndex);
    if (ride == nullptr)
    {
        log_warning("Invalid game command, ride_id = %u", _rideIndex.ToUnderlying());
        return GameActions::Result(GameActions::Status::InvalidParameters, STR_NONE, STR_NONE);
    }

    if (_value <= 0)
    {
        log_warning("Rating value must be positive", _rideIndex.ToUnderlying());
        return GameActions::Result(GameActions::Status::InvalidParameters, STR_NONE, STR_NONE);
    }

    return GameActions::Result();
}

GameActions::Result RideFreezeRatingAction::Execute() const
{
    auto ride = get_ride(_rideIndex);

    switch (_type)
    {
        case RideRatingType::Excitement:
            ride->excitement = _value;
            break;
        case RideRatingType::Intensity:
            ride->intensity = _value;
            break;
        case RideRatingType::Nausea:
            ride->nausea = _value;
            break;
    }

    ride->lifecycle_flags |= RIDE_LIFECYCLE_FIXED_RATINGS;

    window_invalidate_by_number(WindowClass::Ride, _rideIndex.ToUnderlying());

    auto res = GameActions::Result();
    return res;
}
