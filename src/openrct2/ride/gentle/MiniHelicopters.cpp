/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../interface/Viewport.h"
#include "../../paint/Paint.h"
#include "../../paint/support/MetalSupports.h"
#include "../../paint/support/WoodenSupports.h"
#include "../../paint/tile_element/Segment.h"
#include "../../paint/track/Segment.h"
#include "../../paint/track/Support.h"
#include "../../world/Map.h"
#include "../RideData.h"
#include "../Track.h"
#include "../TrackPaint.h"
#include "../VehiclePaint.h"

static constexpr MetalSupportType kSupportType = MetalSupportType::Stick;

/** rct2: 0x */
static void PaintMiniHelicoptersTrackStation(
    PaintSession& session, const Ride& ride, [[maybe_unused]] uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    ImageId imageId;

    if (direction == 0 || direction == 2)
    {
        imageId = GetStationColourScheme(session, trackElement).WithIndex(SPR_STATION_BASE_B_SW_NE);
        PaintAddImageAsParent(session, imageId, { 0, 0, height - 2 }, { { 0, 2, height }, { 32, 28, 1 } });

        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW);
        PaintAddImageAsChild(session, imageId, { 0, 0, height }, { { 0, 0, height }, { 32, 20, 1 } });
    }
    else if (direction == 1 || direction == 3)
    {
        imageId = GetStationColourScheme(session, trackElement).WithIndex(SPR_STATION_BASE_B_NW_SE);
        PaintAddImageAsParent(session, imageId, { 0, 0, height - 2 }, { { 2, 0, height }, { 28, 32, 1 } });

        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW);
        PaintAddImageAsChild(session, imageId, { 0, 0, height }, { { 0, 0, height }, { 20, 32, 1 } });
    }

    DrawSupportsSideBySide(session, direction, height, session.SupportColours, MetalSupportType::Boxed);
    PaintUtilPushTunnelRotated(session, direction, height, TunnelType::SquareFlat);

    TrackPaintUtilDrawStation(session, ride, direction, height, trackElement);

    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x0081F348 */
static void PaintMiniHelicoptersTrackFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    ImageId imageId;

    if (direction & 1)
    {
        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW);
        PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 3 } });
        PaintUtilPushTunnelRight(session, height, TunnelType::StandardFlat);
    }
    else
    {
        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW);
        PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
        PaintUtilPushTunnelLeft(session, height, TunnelType::StandardFlat);
    }

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::Centre, -1, height,
            session.SupportColours);
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x0081F368 */
static void PaintMiniHelicoptersTrackFlatTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    ImageId imageId;

    switch (direction)
    {
        case 0:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SW_NE);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
            PaintUtilPushTunnelLeft(session, height, TunnelType::StandardFlat);
            break;
        case 1:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NW_SE);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 3 } });
            PaintUtilPushTunnelRight(session, height, TunnelType::StandardSlopeEnd);
            break;
        case 2:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_NE_SW);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
            PaintUtilPushTunnelLeft(session, height, TunnelType::StandardSlopeEnd);
            break;
        case 3:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_TO_25_DEG_UP_SE_NW);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 3 } });
            PaintUtilPushTunnelRight(session, height, TunnelType::StandardFlat);
            break;
    }

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, -4, height, session.SupportColours);
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 48);
}

/** rct2: 0x0081F358 */
static void PaintMiniHelicoptersTrack25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    ImageId imageId;

    switch (direction)
    {
        case 0:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SW_NE);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
            PaintUtilPushTunnelLeft(session, height - 8, TunnelType::StandardSlopeStart);
            break;
        case 1:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NW_SE);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 3 } });
            PaintUtilPushTunnelRight(session, height + 8, TunnelType::StandardSlopeEnd);
            break;
        case 2:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_NE_SW);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
            PaintUtilPushTunnelLeft(session, height + 8, TunnelType::StandardSlopeEnd);
            break;
        case 3:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_SE_NW);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 3 } });
            PaintUtilPushTunnelRight(session, height - 8, TunnelType::StandardSlopeStart);
            break;
    }

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, -9, height, session.SupportColours);
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x0081F378 */
static void PaintMiniHelicoptersTrack25DegUpToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    ImageId imageId;

    switch (direction)
    {
        case 0:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SW_NE);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
            PaintUtilPushTunnelLeft(session, height - 8, TunnelType::StandardFlat);
            break;
        case 1:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NW_SE);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 3 } });
            PaintUtilPushTunnelRight(session, height + 8, TunnelType::_12);
            break;
        case 2:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_NE_SW);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
            PaintUtilPushTunnelLeft(session, height + 8, TunnelType::_12);
            break;
        case 3:
            imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_25_DEG_UP_TO_FLAT_SE_NW);
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 0, height }, { 20, 32, 3 } });
            PaintUtilPushTunnelRight(session, height - 8, TunnelType::StandardFlat);
            break;
    }

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, -7, height, session.SupportColours);
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 40);
}

/** rct2: 0x */
static void PaintMiniHelicoptersTrackFlatTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    PaintMiniHelicoptersTrack25DegUpToFlat(session, ride, trackSequence, (direction + 2) % 4, height, trackElement);
}

/** rct2: 0x0081F388 */
static void PaintMiniHelicoptersTrack25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    PaintMiniHelicoptersTrack25DegUp(session, ride, trackSequence, (direction + 2) % 4, height, trackElement);
}

/** rct2: 0x0081F3A8 */
static void PaintMiniHelicoptersTrack25DegDownToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    PaintMiniHelicoptersTrackFlatTo25DegUp(session, ride, trackSequence, (direction + 2) % 4, height, trackElement);
}

/** rct2: 0x0081F3E8 */
static void PaintMiniHelicoptersTrackLeftQuarterTurn3Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    TrackPaintUtilLeftQuarterTurn3TilesPaint(
        session, 3, height, direction, trackSequence, session.TrackColours,
        kTrackSpritesSubmarineRideMiniHelicoptersQuarterTurn3Tiles);
    TrackPaintUtilLeftQuarterTurn3TilesTunnel(session, height, TunnelType::StandardFlat, direction, trackSequence);

    switch (trackSequence)
    {
        case 0:
            MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, -1, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::topCorner),
                    direction),
                0xFFFF, 0);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::topLeftSide, PaintSegment::centre, PaintSegment::bottomLeftSide,
                        PaintSegment::leftCorner),
                    direction),
                0xFFFF, 0);
            break;
        case 3:
            MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, -1, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::topLeftSide, PaintSegment::centre, PaintSegment::bottomRightSide,
                        PaintSegment::bottomCorner),
                    direction),
                0xFFFF, 0);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static constexpr uint8_t MiniHelicoptersRightQuarterTurn3TilesToLeftTurnMap[] = {
    3,
    1,
    2,
    0,
};

/** rct2: 0x0081F3F8 */
static void PaintMiniHelicoptersTrackRightQuarterTurn3Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = MiniHelicoptersRightQuarterTurn3TilesToLeftTurnMap[trackSequence];
    PaintMiniHelicoptersTrackLeftQuarterTurn3Tiles(session, ride, trackSequence, (direction + 3) % 4, height, trackElement);
}

/** rct2: 0x0081F408 */
static void PaintMiniHelicoptersTrackLeftQuarterTurn1Tile(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    TrackPaintUtilLeftQuarterTurn1TilePaint(
        session, 1, height, 0, direction, session.TrackColours, kTrackSpritesSubmarineRideMiniHelicoptersQuarterTurn1Tile);
    TrackPaintUtilLeftQuarterTurn1TileTunnel(
        session, direction, height, 0, TunnelType::StandardFlat, 0, TunnelType::StandardFlat);

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(
                PaintSegment::leftCorner, PaintSegment::topLeftSide, PaintSegment::centre, PaintSegment::bottomLeftSide),
            direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x0081F418 */
static void PaintMiniHelicoptersTrackRightQuarterTurn1Tile(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    PaintMiniHelicoptersTrackLeftQuarterTurn1Tile(session, ride, trackSequence, (direction + 3) % 4, height, trackElement);
}

static void PaintMiniHelicoptersTrackSpinningTunnel(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    const uint32_t sprites[NumOrthogonalDirections][2] = {
        { SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW, 28773 },
        { SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW, 28774 },
        { SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW, 28773 },
        { SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW, 28774 },
    };

    ImageId imageId = session.TrackColours.WithIndex(sprites[direction][0]);
    ImageId underlay = session.TrackColours.WithIndex(sprites[direction][1]);

    PaintAddImageAsParentRotated(session, direction, underlay, { 0, 6, height - 2 }, { { 0, 6, height }, { 32, 20, 1 } });
    PaintAddImageAsChildRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
    TrackPaintUtilSpinningTunnelPaint(session, 1, height, direction);
    PaintUtilPushTunnelRotated(session, direction, height, TunnelType::StandardFlat);

    WoodenASupportsPaintSetupRotated(
        session, WoodenSupportType::Truss, WoodenSupportSubType::NeSw, direction, height,
        GetStationColourScheme(session, trackElement));

    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/**
 * rct2: 0x0081F268
 */
TRACK_PAINT_FUNCTION GetTrackPaintFunctionMiniHelicopters(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::Flat:
            return PaintMiniHelicoptersTrackFlat;

        case TrackElemType::EndStation:
        case TrackElemType::BeginStation:
        case TrackElemType::MiddleStation:
            return PaintMiniHelicoptersTrackStation;

        case TrackElemType::Up25:
            return PaintMiniHelicoptersTrack25DegUp;
        case TrackElemType::FlatToUp25:
            return PaintMiniHelicoptersTrackFlatTo25DegUp;
        case TrackElemType::Up25ToFlat:
            return PaintMiniHelicoptersTrack25DegUpToFlat;

        case TrackElemType::Down25:
            return PaintMiniHelicoptersTrack25DegDown;
        case TrackElemType::FlatToDown25:
            return PaintMiniHelicoptersTrackFlatTo25DegDown;
        case TrackElemType::Down25ToFlat:
            return PaintMiniHelicoptersTrack25DegDownToFlat;

        case TrackElemType::LeftQuarterTurn3Tiles:
            return PaintMiniHelicoptersTrackLeftQuarterTurn3Tiles;
        case TrackElemType::RightQuarterTurn3Tiles:
            return PaintMiniHelicoptersTrackRightQuarterTurn3Tiles;

        case TrackElemType::LeftQuarterTurn1Tile:
            return PaintMiniHelicoptersTrackLeftQuarterTurn1Tile;
        case TrackElemType::RightQuarterTurn1Tile:
            return PaintMiniHelicoptersTrackRightQuarterTurn1Tile;

        case TrackElemType::SpinningTunnel:
            return PaintMiniHelicoptersTrackSpinningTunnel;
    }

    return nullptr;
}
