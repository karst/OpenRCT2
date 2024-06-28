/*****************************************************************************
 * Copyright (c) 2014-2023 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../drawing/Drawing.h"
#include "../../interface/Viewport.h"
#include "../../paint/Paint.h"
#include "../../paint/support/MetalSupports.h"
#include "../../paint/tile_element/Paint.TileElement.h"
#include "../../paint/tile_element/Segment.h"
#include "../../paint/track/Segment.h"
#include "../../paint/track/Support.h"
#include "../../sprites.h"
#include "../../world/Map.h"
#include "../RideData.h"
#include "../TrackData.h"
#include "../TrackPaint.h"

static constexpr MetalSupportType kSupportType = MetalSupportType::Tubes;

static constexpr uint32_t _InMaTriangleAltBrakeImages[NumOrthogonalDirections][2] = {
    { SPR_G2_GIGA_RC_BRAKE_ALT_OPEN_NE_SW, SPR_G2_GIGA_RC_BRAKE_ALT_CLOSED_NE_SW },
    { SPR_G2_GIGA_RC_BRAKE_ALT_OPEN_NW_SE, SPR_G2_GIGA_RC_BRAKE_ALT_CLOSED_NW_SE },
    { SPR_G2_GIGA_RC_BRAKE_ALT_OPEN_SW_NE, SPR_G2_GIGA_RC_BRAKE_ALT_CLOSED_SW_NE },
    { SPR_G2_GIGA_RC_BRAKE_ALT_OPEN_SE_NW, SPR_G2_GIGA_RC_BRAKE_ALT_CLOSED_SE_NW },
};

static constexpr uint32_t _InMaTriangleAltBlockBrakeImages[NumOrthogonalDirections][2] = {
    { SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_OPEN_NE_SW, SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_CLOSED_NE_SW },
    { SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_OPEN_NW_SE, SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_CLOSED_NW_SE },
    { SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_OPEN_SW_NE, SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_CLOSED_SW_NE },
    { SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_OPEN_SE_NW, SPR_G2_GIGA_RC_BLOCK_BRAKE_ALT_CLOSED_SE_NW },
};

static void InMaTriangleTrackAltStation(
    PaintSession& session, const Ride& ride, [[maybe_unused]] uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (ride.mode == RideMode::PoweredLaunch || ride.mode == RideMode::PoweredLaunchBlockSectioned
        || ride.mode == RideMode::PoweredLaunchPasstrough)
    {
        static constexpr uint32_t imageIds[4][2] = {
            { SPR_G2_GIGA_RC_BOOSTER_ALT_NE_SW, SPR_STATION_BASE_A_SW_NE },
            { SPR_G2_GIGA_RC_BOOSTER_ALT_NW_SE, SPR_STATION_BASE_A_NW_SE },
            { SPR_G2_GIGA_RC_BOOSTER_ALT_SW_NE, SPR_STATION_BASE_A_SW_NE },
            { SPR_G2_GIGA_RC_BOOSTER_ALT_SE_NW, SPR_STATION_BASE_A_NW_SE },
        };

        PaintAddImageAsParentRotated(
            session, direction, session.TrackColours.WithIndex(imageIds[direction][0]), { 0, 0, height },
            { { 0, 6, height + 3 }, { 32, 20, 1 } });

        PaintAddImageAsParentRotated(
            session, direction, GetStationColourScheme(session, trackElement).WithIndex(imageIds[direction][1]),
            { 0, 0, height }, { 32, 32, 1 });
    }
    else
    {
        static constexpr uint32_t imageIds[4][2] = {
            { SPR_G2_GIGA_RC_DRIVE_TYRE_NE_SW, SPR_STATION_BASE_A_SW_NE },
            { SPR_G2_GIGA_RC_DRIVE_TYRE_NW_SE, SPR_STATION_BASE_A_NW_SE },
            { SPR_G2_GIGA_RC_DRIVE_TYRE_SW_NE, SPR_STATION_BASE_A_SW_NE },
            { SPR_G2_GIGA_RC_DRIVE_TYRE_SE_NW, SPR_STATION_BASE_A_NW_SE },
        };
        if (trackElement.GetTrackType() == TrackElemType::EndStation)
        {
            bool isClosed = trackElement.IsBrakeClosed();
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(_InMaTriangleAltBlockBrakeImages[direction][isClosed]),
                { 0, 0, height }, { { 0, 6, height + 3 }, { 32, 20, 1 } });
        }
        else
        {
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(imageIds[direction][0]), { 0, 0, height },
                { { 0, 6, height + 3 }, { 32, 20, 1 } });
        }

        PaintAddImageAsParentRotated(
            session, direction, GetStationColourScheme(session, trackElement).WithIndex(imageIds[direction][1]),
            { 0, 0, height }, { 32, 32, 1 });
    }
    DrawSupportsSideBySide(session, direction, height, session.SupportColours, kSupportType);
    TrackPaintUtilDrawStation2(session, ride, direction, height, trackElement, 9, 11);
    PaintUtilPushTunnelRotated(session, direction, height, TunnelType::SquareFlat);
    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void InMaTriangleTrackAltBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    bool isClosed = trackElement.IsBrakeClosed();
    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours.WithIndex(_InMaTriangleAltBrakeImages[direction][isClosed]), { 0, 0, height },
        { { 0, 6, height }, { 32, 20, 3 } });

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 0, height, session.SupportColours);
    }
    PaintUtilPushTunnelRotated(session, direction, height, TunnelType::SquareFlat);
    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::centre, PaintSegment::topRightSide, PaintSegment::bottomLeftSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void InMaTriangleTrackAltBlockBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    bool isClosed = trackElement.IsBrakeClosed();
    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours.WithIndex(_InMaTriangleAltBlockBrakeImages[direction][isClosed]),
        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 0, height, session.SupportColours);
    }
    PaintUtilPushTunnelRotated(session, direction, height, TunnelType::SquareFlat);
    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::centre, PaintSegment::topRightSide, PaintSegment::bottomLeftSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void InMaTriangleTrackAltBooster(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_G2_GIGA_RC_BOOSTER_ALT_NE_SW), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_G2_GIGA_RC_BOOSTER_ALT_NW_SE), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_G2_GIGA_RC_BOOSTER_ALT_SW_NE), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_G2_GIGA_RC_BOOSTER_ALT_SE_NW), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
    }
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 0, height, session.SupportColours);
    }
    PaintUtilPushTunnelRotated(session, direction, height, TunnelType::SquareFlat);
    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::centre, PaintSegment::topRightSide, PaintSegment::bottomLeftSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void InMaTriangleTrackAltPoweredLift(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours.WithIndex(SPR_G2_GIGA_RC_POWERED_LIFT_ALT_1 + direction), { 0, 0, height },
        { { 0, 6, height }, { 32, 20, 3 } });

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 8, height, session.SupportColours);
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, TunnelType::SquareSlopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, TunnelType::SquareSlopeEnd);
    }
    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::centre, PaintSegment::topRightSide, PaintSegment::bottomLeftSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

TRACK_PAINT_FUNCTION GetTrackPaintFunctionInMaTriangleAlt(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::EndStation:
        case TrackElemType::BeginStation:
        case TrackElemType::MiddleStation:
            return InMaTriangleTrackAltStation;
        case TrackElemType::Brakes:
            return InMaTriangleTrackAltBrakes;
        case TrackElemType::BlockBrakes:
            return InMaTriangleTrackAltBlockBrakes;
        case TrackElemType::Booster:
            return InMaTriangleTrackAltBooster;
        case TrackElemType::PoweredLift:
            return InMaTriangleTrackAltPoweredLift;
    }
    return GetTrackPaintFunctionInMaTriangle(trackType);
}
