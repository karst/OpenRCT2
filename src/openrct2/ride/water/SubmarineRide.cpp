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
#include "../../paint/tile_element/Segment.h"
#include "../../paint/track/Segment.h"
#include "../../paint/track/Support.h"
#include "../RideData.h"
#include "../Track.h"
#include "../TrackPaint.h"
#include "../Vehicle.h"
#include "../VehiclePaint.h"

static constexpr MetalSupportType kSupportType = MetalSupportType::Stick;

static uint32_t SubmarineVehicleGetBaseImageId(const Vehicle* vehicle, const CarEntry* carEntry, int32_t imageDirection)
{
    uint32_t result = imageDirection;
    if (vehicle->restraints_position >= 64)
    {
        if ((carEntry->GroupEnabled(SpriteGroupType::RestraintAnimation)) && !(imageDirection & 3))
        {
            auto restraintFrame = ((vehicle->restraints_position - 64) / 64) * 4;
            result = (carEntry->SpriteByYaw(imageDirection, SpriteGroupType::RestraintAnimation) + restraintFrame)
                    * carEntry->base_num_frames
                + carEntry->GroupImageId(SpriteGroupType::RestraintAnimation);
        }
    }
    else
    {
        result = (carEntry->SpriteByYaw(imageDirection, SpriteGroupType::SlopeFlat) * carEntry->base_num_frames)
            + carEntry->GroupImageId(SpriteGroupType::SlopeFlat) + vehicle->SwingSprite;
    }
    return result;
}

/**
 *
 *  rct2: 0x006D44D5
 */
void VehicleVisualSubmarine(
    PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const Vehicle* vehicle,
    const CarEntry* carEntry)
{
    auto baseImageId = SubmarineVehicleGetBaseImageId(vehicle, carEntry, imageDirection);
    auto imageId0 = ImageId(baseImageId + 0, vehicle->colours.Body, vehicle->colours.Trim, vehicle->colours.Tertiary);
    auto imageId1 = ImageId(baseImageId + 1, vehicle->colours.Body, vehicle->colours.Trim, vehicle->colours.Tertiary);
    if (vehicle->IsGhost())
    {
        imageId0 = ImageId(baseImageId + 0).WithRemap(FilterPaletteID::PaletteGhost);
        imageId1 = ImageId(baseImageId + 1).WithRemap(FilterPaletteID::PaletteGhost);
    }

    const auto& bb = VehicleBoundboxes[carEntry->draw_order][OpenRCT2::Entity::Yaw::YawTo16(imageDirection)];
    PaintAddImageAsParent(
        session, imageId0, { 0, 0, z },
        { { bb.offset_x, bb.offset_y, bb.offset_z + z }, { bb.length_x, bb.length_y, bb.length_z } });
    PaintAddImageAsParent(
        session, imageId1, { 0, 0, z },
        { { bb.offset_x, bb.offset_y, bb.offset_z + z - 10 }, { bb.length_x, bb.length_y, 2 } });
    assert(carEntry->effect_visual == 1);
}

static void SubmarineRidePaintTrackStation(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    const auto* stationObj = ride.GetStationObject();
    int32_t heightLower = height - 16;
    ImageId imageId;

    if (direction & 1)
    {
        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW);
        PaintAddImageAsParent(session, imageId, { 0, 0, heightLower }, { { 6, 0, heightLower }, { 20, 32, 3 } });

        PaintUtilPushTunnelRight(session, height, TunnelType::SquareFlat);
        TrackPaintUtilDrawPier(
            session, ride, stationObj, session.MapPosition, direction, height, trackElement, session.CurrentRotation);
    }
    else
    {
        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW);
        PaintAddImageAsParent(session, imageId, { 0, 0, heightLower }, { { 0, 6, heightLower }, { 32, 20, 3 } });

        PaintUtilPushTunnelLeft(session, height, TunnelType::SquareFlat);
        TrackPaintUtilDrawPier(
            session, ride, stationObj, session.MapPosition, direction, height, trackElement, session.CurrentRotation);
    }

    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void SubmarineRidePaintTrackFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    int32_t heightLower = height - 16;
    ImageId imageId;

    if (direction & 1)
    {
        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_SE_NW);
        PaintAddImageAsParent(session, imageId, { 0, 0, heightLower }, { { 6, 0, heightLower }, { 20, 32, 3 } });
        PaintUtilPushTunnelRight(session, heightLower, TunnelType::StandardFlat);
    }
    else
    {
        imageId = session.TrackColours.WithIndex(SPR_TRACK_SUBMARINE_RIDE_MINI_HELICOPTERS_FLAT_NE_SW);
        PaintAddImageAsParent(session, imageId, { 0, 0, heightLower }, { { 0, 6, heightLower }, { 32, 20, 3 } });
        PaintUtilPushTunnelLeft(session, heightLower, TunnelType::StandardFlat);
    }

    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::Centre, -1, heightLower,
            session.SupportColours);
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 16);
}

static void SubmarineRidePaintTrackLeftQuarterTurn3Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    TrackPaintUtilLeftQuarterTurn3TilesPaint(
        session, 3, height - 16, direction, trackSequence, session.TrackColours,
        kTrackSpritesSubmarineRideMiniHelicoptersQuarterTurn3Tiles);
    TrackPaintUtilLeftQuarterTurn3TilesTunnel(session, height - 16, TunnelType::StandardFlat, direction, trackSequence);

    switch (trackSequence)
    {
        case 0:
            MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, -1, height - 16, session.SupportColours);
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
            MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, -1, height - 16, session.SupportColours);
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

    PaintUtilSetGeneralSupportHeight(session, height + 16);
}

static constexpr uint8_t submarine_ride_right_quarter_turn_3_tiles_to_left_turn_map[] = {
    3,
    1,
    2,
    0,
};
static void SubmarineRidePaintTrackRightQuarterTurn3Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = submarine_ride_right_quarter_turn_3_tiles_to_left_turn_map[trackSequence];
    SubmarineRidePaintTrackLeftQuarterTurn3Tiles(session, ride, trackSequence, (direction + 3) % 4, height, trackElement);
}

static void SubmarineRidePaintTrackLeftQuarterTurn1Tile(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    TrackPaintUtilLeftQuarterTurn1TilePaint(
        session, 1, height - 16, 0, direction, session.TrackColours, kTrackSpritesSubmarineRideMiniHelicoptersQuarterTurn1Tile);
    TrackPaintUtilLeftQuarterTurn1TileTunnel(
        session, direction, height - 16, 0, TunnelType::StandardFlat, 0, TunnelType::StandardFlat);

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(
                PaintSegment::leftCorner, PaintSegment::topLeftSide, PaintSegment::centre, PaintSegment::bottomLeftSide),
            direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 16);
}

static void SubmarineRidePaintTrackRightQuarterTurn1Tile(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    SubmarineRidePaintTrackLeftQuarterTurn1Tile(session, ride, trackSequence, (direction + 3) % 4, height, trackElement);
}

/**
 * rct2: 0x008995D4
 */
TRACK_PAINT_FUNCTION GetTrackPaintFunctionSubmarineRide(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::BeginStation:
        case TrackElemType::MiddleStation:
        case TrackElemType::EndStation:
            return SubmarineRidePaintTrackStation;

        case TrackElemType::Flat:
            return SubmarineRidePaintTrackFlat;

        case TrackElemType::LeftQuarterTurn3Tiles:
            return SubmarineRidePaintTrackLeftQuarterTurn3Tiles;
        case TrackElemType::RightQuarterTurn3Tiles:
            return SubmarineRidePaintTrackRightQuarterTurn3Tiles;

        case TrackElemType::LeftQuarterTurn1Tile:
            return SubmarineRidePaintTrackLeftQuarterTurn1Tile;
        case TrackElemType::RightQuarterTurn1Tile:
            return SubmarineRidePaintTrackRightQuarterTurn1Tile;
    }

    return nullptr;
}
