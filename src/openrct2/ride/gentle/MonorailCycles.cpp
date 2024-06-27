/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../common.h"
#include "../../interface/Viewport.h"
#include "../../paint/Paint.h"
#include "../../paint/support/MetalSupports.h"
#include "../../paint/tile_element/Segment.h"
#include "../../paint/track/Segment.h"
#include "../../paint/track/Support.h"
#include "../../world/Map.h"
#include "../Track.h"
#include "../TrackPaint.h"
#include "../VehiclePaint.h"

static constexpr MetalSupportType kSupportType = MetalSupportType::Stick;

enum
{
    SprMonorailCyclesFlatSwNe = 16820,
    SprMonorailCyclesFlatNwSe = 16821,
    SprMonorailCyclesFlatQuarterTurn5TilesSwSePart0 = 16822,
    SprMonorailCyclesFlatQuarterTurn5TilesSwSePart1 = 16823,
    SprMonorailCyclesFlatQuarterTurn5TilesSwSePart2 = 16824,
    SprMonorailCyclesFlatQuarterTurn5TilesSwSePart3 = 16825,
    SprMonorailCyclesFlatQuarterTurn5TilesSwSePart4 = 16826,
    SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart0 = 16827,
    SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart1 = 16828,
    SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart2 = 16829,
    SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart3 = 16830,
    SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart4 = 16831,
    SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart0 = 16832,
    SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart1 = 16833,
    SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart2 = 16834,
    SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart3 = 16835,
    SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart4 = 16836,
    SprMonorailCyclesFlatQuarterTurn5TilesSeNePart0 = 16837,
    SprMonorailCyclesFlatQuarterTurn5TilesSeNePart1 = 16838,
    SprMonorailCyclesFlatQuarterTurn5TilesSeNePart2 = 16839,
    SprMonorailCyclesFlatQuarterTurn5TilesSeNePart3 = 16840,
    SprMonorailCyclesFlatQuarterTurn5TilesSeNePart4 = 16841,
    SprMonorailCyclesFlatQuarterTurn3TilesSwSePart0 = 16842,
    SprMonorailCyclesFlatQuarterTurn3TilesSwSePart1 = 16843,
    SprMonorailCyclesFlatQuarterTurn3TilesSwSePart2 = 16844,
    SprMonorailCyclesFlatQuarterTurn3TilesNwSwPart0 = 16845,
    SprMonorailCyclesFlatQuarterTurn3TilesNwSwPart1 = 16846,
    SprMonorailCyclesFlatQuarterTurn3TilesNwSwPart2 = 16847,
    SprMonorailCyclesFlatQuarterTurn3TilesNeNwPart0 = 16848,
    SprMonorailCyclesFlatQuarterTurn3TilesNeNwPart1 = 16849,
    SprMonorailCyclesFlatQuarterTurn3TilesNeNwPart2 = 16850,
    SprMonorailCyclesFlatQuarterTurn3TilesSeNePart0 = 16851,
    SprMonorailCyclesFlatQuarterTurn3TilesSeNePart1 = 16852,
    SprMonorailCyclesFlatQuarterTurn3TilesSeNePart2 = 16853,
    SprMonorailCyclesSBendLeftSwNePart0 = 16854,
    SprMonorailCyclesSBendLeftSwNePart1 = 16855,
    SprMonorailCyclesSBendLeftSwNePart2 = 16856,
    SprMonorailCyclesSBendLeftSwNePart3 = 16857,
    SprMonorailCyclesSBendLeftNwSePart0 = 16858,
    SprMonorailCyclesSBendLeftNwSePart1 = 16859,
    SprMonorailCyclesSBendLeftNwSePart2 = 16860,
    SprMonorailCyclesSBendLeftNwSePart3 = 16861,
    SprMonorailCyclesSBendRightSwNePart0 = 16862,
    SprMonorailCyclesSBendRightSwNePart1 = 16863,
    SprMonorailCyclesSBendRightSwNePart2 = 16864,
    SprMonorailCyclesSBendRightSwNePart3 = 16865,
    SprMonorailCyclesSBendRightNwSePart0 = 16866,
    SprMonorailCyclesSBendRightNwSePart1 = 16867,
    SprMonorailCyclesSBendRightNwSePart2 = 16868,
    SprMonorailCyclesSBendRightNwSePart3 = 16869,
};

static constexpr uint32_t MonorailCyclesTrackPiecesFlat[2] = {
    SprMonorailCyclesFlatSwNe,
    SprMonorailCyclesFlatNwSe,
};

static constexpr uint32_t MonorailCyclesTrackPiecesFlatQuarterTurn5Tiles[4][5] = {
    {
        SprMonorailCyclesFlatQuarterTurn5TilesSwSePart0,
        SprMonorailCyclesFlatQuarterTurn5TilesSwSePart1,
        SprMonorailCyclesFlatQuarterTurn5TilesSwSePart2,
        SprMonorailCyclesFlatQuarterTurn5TilesSwSePart3,
        SprMonorailCyclesFlatQuarterTurn5TilesSwSePart4,
    },
    {
        SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart0,
        SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart1,
        SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart2,
        SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart3,
        SprMonorailCyclesFlatQuarterTurn5TilesNwSwPart4,
    },
    {
        SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart0,
        SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart1,
        SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart2,
        SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart3,
        SprMonorailCyclesFlatQuarterTurn5TilesNeNwPart4,
    },
    {
        SprMonorailCyclesFlatQuarterTurn5TilesSeNePart0,
        SprMonorailCyclesFlatQuarterTurn5TilesSeNePart1,
        SprMonorailCyclesFlatQuarterTurn5TilesSeNePart2,
        SprMonorailCyclesFlatQuarterTurn5TilesSeNePart3,
        SprMonorailCyclesFlatQuarterTurn5TilesSeNePart4,
    },
};

static constexpr uint32_t MonorailCyclesTrackPiecesSBendLeft[2][4] = {
    {
        SprMonorailCyclesSBendLeftSwNePart0,
        SprMonorailCyclesSBendLeftSwNePart1,
        SprMonorailCyclesSBendLeftSwNePart2,
        SprMonorailCyclesSBendLeftSwNePart3,
    },
    {
        SprMonorailCyclesSBendLeftNwSePart0,
        SprMonorailCyclesSBendLeftNwSePart1,
        SprMonorailCyclesSBendLeftNwSePart2,
        SprMonorailCyclesSBendLeftNwSePart3,
    },
};

static constexpr uint32_t MonorailCyclesTrackPiecesSBendRight[2][4] = {
    {
        SprMonorailCyclesSBendRightSwNePart0,
        SprMonorailCyclesSBendRightSwNePart1,
        SprMonorailCyclesSBendRightSwNePart2,
        SprMonorailCyclesSBendRightSwNePart3,
    },
    {
        SprMonorailCyclesSBendRightNwSePart0,
        SprMonorailCyclesSBendRightNwSePart1,
        SprMonorailCyclesSBendRightNwSePart2,
        SprMonorailCyclesSBendRightNwSePart3,
    },
};

static constexpr uint32_t MonorailCyclesTrackPiecesFlatQuarterTurn3Tiles[4][3] = {
    {
        SprMonorailCyclesFlatQuarterTurn3TilesSwSePart0,
        SprMonorailCyclesFlatQuarterTurn3TilesSwSePart1,
        SprMonorailCyclesFlatQuarterTurn3TilesSwSePart2,
    },
    {
        SprMonorailCyclesFlatQuarterTurn3TilesNwSwPart0,
        SprMonorailCyclesFlatQuarterTurn3TilesNwSwPart1,
        SprMonorailCyclesFlatQuarterTurn3TilesNwSwPart2,
    },
    {
        SprMonorailCyclesFlatQuarterTurn3TilesNeNwPart0,
        SprMonorailCyclesFlatQuarterTurn3TilesNeNwPart1,
        SprMonorailCyclesFlatQuarterTurn3TilesNeNwPart2,
    },
    {
        SprMonorailCyclesFlatQuarterTurn3TilesSeNePart0,
        SprMonorailCyclesFlatQuarterTurn3TilesSeNePart1,
        SprMonorailCyclesFlatQuarterTurn3TilesSeNePart2,
    },
};

/** rct2: 0x0088AD48 */
static void PaintMonorailCyclesTrackFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    auto imageId = session.TrackColours.WithIndex(MonorailCyclesTrackPiecesFlat[(direction & 1)]);
    PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });

    if (direction & 1)
    {
        PaintUtilPushTunnelRight(session, height, TunnelType::StandardFlat);
    }
    else
    {
        PaintUtilPushTunnelLeft(session, height, TunnelType::StandardFlat);
    }

    MetalASupportsPaintSetup(
        session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::Centre, -1, height,
        session.SupportColours);

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            EnumsToFlags(PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide), direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x0088ADD8 */
static void PaintMonorailCyclesStation(
    PaintSession& session, const Ride& ride, [[maybe_unused]] uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    ImageId imageId;

    if (direction == 0 || direction == 2)
    {
        imageId = GetStationColourScheme(session, trackElement).WithIndex(SPR_STATION_BASE_B_SW_NE);
        PaintAddImageAsParent(session, imageId, { 0, 0, height - 2 }, { { 0, 2, height }, { 32, 28, 1 } });

        imageId = session.TrackColours.WithIndex(SprMonorailCyclesFlatSwNe);
        PaintAddImageAsChild(session, imageId, { 0, 0, height }, { { 0, 0, height }, { 32, 20, 1 } });
    }
    else if (direction == 1 || direction == 3)
    {
        imageId = GetStationColourScheme(session, trackElement).WithIndex(SPR_STATION_BASE_B_NW_SE);
        PaintAddImageAsParent(session, imageId, { 0, 0, height - 2 }, { { 2, 0, height }, { 28, 32, 1 } });

        imageId = session.TrackColours.WithIndex(SprMonorailCyclesFlatNwSe);
        PaintAddImageAsChild(session, imageId, { 0, 0, height }, { { 0, 0, height }, { 20, 32, 1 } });
    }

    DrawSupportsSideBySide(session, direction, height, session.SupportColours, MetalSupportType::Boxed);
    PaintUtilPushTunnelRotated(session, direction, height, TunnelType::SquareFlat);

    TrackPaintUtilDrawStation(session, ride, direction, height, trackElement);

    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x0088AD88 */
static void PaintMonorailCyclesTrackLeftQuarterTurn3Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    TrackPaintUtilLeftQuarterTurn3TilesPaint(
        session, 3, height, direction, trackSequence, session.TrackColours, MonorailCyclesTrackPiecesFlatQuarterTurn3Tiles);
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

static constexpr uint8_t monorail_cycles_right_quarter_turn_3_tiles_to_left_turn_map[] = {
    3,
    1,
    2,
    0,
};

/** rct2: 0x0088AD98 */
static void PaintMonorailCyclesTrackRightQuarterTurn3Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = monorail_cycles_right_quarter_turn_3_tiles_to_left_turn_map[trackSequence];
    PaintMonorailCyclesTrackLeftQuarterTurn3Tiles(session, ride, trackSequence, (direction + 3) % 4, height, trackElement);
}

static constexpr int8_t MonorailCyclesTrackRightQuarterTurn5TilesSupportHeightOffset[][7] = {
    { -2, 0, -2, 0, 0, -3, -1 },
    { -3, 0, 0, 0, 0, 0, 0 },
    { 0 },
    { 0, 0, 0, 0, 0, -2, -3 },
};

static constexpr int8_t MonorailCyclesTrackRightQuarterTurn5TilesSupportSpecial[][7] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 1 },
    { 0, 0, 1, 0, 0, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0 },
};

/** rct2: 0x0088ADB8 */
static void PaintMonorailCyclesTrackRightQuarterTurn5Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    TrackPaintUtilRightQuarterTurn5TilesPaint(
        session, 1, height, direction, trackSequence, session.TrackColours, MonorailCyclesTrackPiecesFlatQuarterTurn5Tiles,
        nullptr, kDefaultRightQuarterTurn5TilesBoundLengths, kDefaultRightQuarterTurn5TilesBoundOffsets);

    int32_t supportHeight = height + MonorailCyclesTrackRightQuarterTurn5TilesSupportHeightOffset[direction][trackSequence];
    int32_t supportSpecial = MonorailCyclesTrackRightQuarterTurn5TilesSupportSpecial[direction][trackSequence];
    switch (trackSequence)
    {
        case 0:
            MetalASupportsPaintSetup(
                session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::Centre, supportSpecial,
                supportHeight, session.SupportColours);
            break;
        case 2:
            if (direction == 0)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::BottomRightSide,
                    supportSpecial, supportHeight, session.SupportColours);
            if (direction == 1)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::BottomLeftSide,
                    supportSpecial, supportHeight, session.SupportColours);
            if (direction == 2)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::TopLeftSide,
                    supportSpecial, supportHeight, session.SupportColours);
            if (direction == 3)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? MetalSupportType::StickAlt : kSupportType, MetalSupportPlace::TopRightSide,
                    supportSpecial, supportHeight, session.SupportColours);
            break;
        case 5:
            if (direction == 0)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? kSupportType : MetalSupportType::StickAlt, MetalSupportPlace::BottomLeftSide,
                    supportSpecial, supportHeight, session.SupportColours);
            if (direction == 1)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? kSupportType : MetalSupportType::StickAlt, MetalSupportPlace::TopLeftSide,
                    supportSpecial, supportHeight, session.SupportColours);
            if (direction == 2)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? kSupportType : MetalSupportType::StickAlt, MetalSupportPlace::TopRightSide,
                    supportSpecial, supportHeight, session.SupportColours);
            if (direction == 3)
                MetalASupportsPaintSetup(
                    session, (direction & 1) ? kSupportType : MetalSupportType::StickAlt, MetalSupportPlace::BottomRightSide,
                    supportSpecial, supportHeight, session.SupportColours);
            break;
        case 6:
            MetalASupportsPaintSetup(
                session, (direction & 1) ? kSupportType : MetalSupportType::StickAlt, MetalSupportPlace::Centre, supportSpecial,
                supportHeight, session.SupportColours);
            break;
    }

    if (direction == 0 && trackSequence == 0)
    {
        PaintUtilPushTunnelLeft(session, height, TunnelType::StandardFlat);
    }

    if (direction == 0 && trackSequence == 6)
    {
        PaintUtilPushTunnelRight(session, height, TunnelType::StandardFlat);
    }

    if (direction == 1 && trackSequence == 6)
    {
        PaintUtilPushTunnelLeft(session, height, TunnelType::StandardFlat);
    }

    if (direction == 3 && trackSequence == 0)
    {
        PaintUtilPushTunnelRight(session, height, TunnelType::StandardFlat);
    }

    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::rightCorner),
                    direction),
                0xFFFF, 0);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::bottomRightSide,
                        PaintSegment::rightCorner, PaintSegment::bottomCorner, PaintSegment::topRightSide),
                    direction),
                0xFFFF, 0);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::topCorner, PaintSegment::topLeftSide, PaintSegment::topRightSide, PaintSegment::centre),
                    direction),
                0xFFFF, 0);
            break;
        case 5:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomRightSide, PaintSegment::centre, PaintSegment::bottomLeftSide,
                        PaintSegment::leftCorner, PaintSegment::bottomCorner, PaintSegment::topLeftSide),
                    direction),
                0xFFFF, 0);
            break;
        case 6:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomRightSide, PaintSegment::centre, PaintSegment::topLeftSide,
                        PaintSegment::leftCorner),
                    direction),
                0xFFFF, 0);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x0088ADA8 */
static void PaintMonorailCyclesTrackLeftQuarterTurn5Tiles(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    PaintMonorailCyclesTrackRightQuarterTurn5Tiles(session, ride, trackSequence, (direction + 1) % 4, height, trackElement);
}

/** rct2: 0x0088ADC8 */
static void PaintMonorailCyclesTrackSBendLeft(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (direction == 2 || direction == 3)
    {
        trackSequence = 3 - trackSequence;
    }

    auto imageId = session.TrackColours.WithIndex(MonorailCyclesTrackPiecesSBendLeft[direction & 1][trackSequence]);
    switch (trackSequence)
    {
        case 0:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 0, height }, { 32, 26, 1 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 26, 1 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
            break;
    }

    if (direction == 0 || direction == 2)
    {
        if (trackSequence == 0)
        {
            PaintUtilPushTunnelLeft(session, height, TunnelType::StandardFlat);
        }

        switch (trackSequence)
        {
            case 0:
                MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 0, height, session.SupportColours);
                break;
            case 1:
                MetalASupportsPaintSetup(
                    session, kSupportType, MetalSupportPlace::TopLeftSide, 0, height, session.SupportColours);
                break;
            case 3:
                MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 0, height, session.SupportColours);
                break;
        }
    }
    else
    {
        if (trackSequence == 3)
        {
            PaintUtilPushTunnelRight(session, height, TunnelType::StandardFlat);
        }

        switch (trackSequence)
        {
            case 0:
                MetalASupportsPaintSetup(
                    session, MetalSupportType::StickAlt, MetalSupportPlace::Centre, 0, height, session.SupportColours);
                break;
            case 1:
                MetalASupportsPaintSetup(
                    session, MetalSupportType::StickAlt, MetalSupportPlace::TopRightSide, 0, height, session.SupportColours);
                break;
            case 3:
                MetalASupportsPaintSetup(
                    session, MetalSupportType::StickAlt, MetalSupportPlace::Centre, 0, height - 2, session.SupportColours);
                break;
        }
    }

    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::topCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
        case 1:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::leftCorner, PaintSegment::topLeftSide, PaintSegment::topCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::bottomCorner, PaintSegment::bottomRightSide, PaintSegment::rightCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::bottomCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
    }
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x*/
static void PaintMonorailCyclesTrackSBendRight(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (direction == 2 || direction == 3)
    {
        trackSequence = 3 - trackSequence;
    }

    auto imageId = session.TrackColours.WithIndex(MonorailCyclesTrackPiecesSBendRight[direction & 1][trackSequence]);
    switch (trackSequence)
    {
        case 0:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 26, 1 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 0, height }, { 32, 26, 1 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(session, direction, imageId, { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
            break;
    }

    if (direction == 0 || direction == 2)
    {
        if (trackSequence == 0)
        {
            PaintUtilPushTunnelLeft(session, height, TunnelType::StandardFlat);
        }

        switch (trackSequence)
        {
            case 0:
                MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 0, height, session.SupportColours);
                break;
            case 1:
                MetalASupportsPaintSetup(
                    session, kSupportType, MetalSupportPlace::BottomRightSide, 0, height - 2, session.SupportColours);
                break;
            case 3:
                MetalASupportsPaintSetup(session, kSupportType, MetalSupportPlace::Centre, 0, height, session.SupportColours);
                break;
        }
    }
    else
    {
        if (trackSequence == 3)
        {
            PaintUtilPushTunnelRight(session, height, TunnelType::StandardFlat);
        }

        switch (trackSequence)
        {
            case 0:
                MetalASupportsPaintSetup(
                    session, MetalSupportType::StickAlt, MetalSupportPlace::Centre, 0, height, session.SupportColours);
                break;
            case 1:
                MetalASupportsPaintSetup(
                    session, MetalSupportType::StickAlt, MetalSupportPlace::BottomLeftSide, 0, height, session.SupportColours);
                break;
            case 3:
                MetalASupportsPaintSetup(
                    session, MetalSupportType::StickAlt, MetalSupportPlace::Centre, 0, height, session.SupportColours);
                break;
        }
    }

    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::rightCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
        case 1:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::bottomCorner, PaintSegment::bottomRightSide, PaintSegment::rightCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::leftCorner, PaintSegment::topLeftSide, PaintSegment::topCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    EnumsToFlags(
                        PaintSegment::bottomLeftSide, PaintSegment::centre, PaintSegment::topRightSide,
                        PaintSegment::leftCorner),
                    direction & 1),
                0xFFFF, 0);
            break;
    }
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/**
 * rct2: 0x0088ac88
 */
TRACK_PAINT_FUNCTION GetTrackPaintFunctionMonorailCycles(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::Flat:
            return PaintMonorailCyclesTrackFlat;

        case TrackElemType::EndStation:
        case TrackElemType::BeginStation:
        case TrackElemType::MiddleStation:
            return PaintMonorailCyclesStation;

        case TrackElemType::LeftQuarterTurn5Tiles:
            return PaintMonorailCyclesTrackLeftQuarterTurn5Tiles;
        case TrackElemType::RightQuarterTurn5Tiles:
            return PaintMonorailCyclesTrackRightQuarterTurn5Tiles;

        case TrackElemType::SBendLeft:
            return PaintMonorailCyclesTrackSBendLeft;
        case TrackElemType::SBendRight:
            return PaintMonorailCyclesTrackSBendRight;

        case TrackElemType::LeftQuarterTurn3Tiles:
            return PaintMonorailCyclesTrackLeftQuarterTurn3Tiles;
        case TrackElemType::RightQuarterTurn3Tiles:
            return PaintMonorailCyclesTrackRightQuarterTurn3Tiles;
    }

    return nullptr;
}
