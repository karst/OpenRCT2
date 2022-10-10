/*****************************************************************************
 * Copyright (c) 2014-2022 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../drawing/Drawing.h"
#include "../../interface/Viewport.h"
#include "../../paint/Paint.h"
#include "../../paint/Supports.h"
#include "../../paint/tile_element/Paint.TileElement.h"
#include "../../sprites.h"
#include "../../world/Map.h"
#include "../RideData.h"
#include "../TrackData.h"
#include "../TrackPaint.h"

/** rct2: 0x0087694C */
static void heartline_twister_rc_track_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackElement.HasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21354), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21356), { 0, 0, height }, { 32, 1, 26 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21355), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21357), { 0, 0, height }, { 32, 1, 26 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21358), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21360), { 0, 0, height }, { 32, 1, 26 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21359), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21361), { 0, 0, height }, { 32, 1, 26 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21294), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21296), { 0, 0, height }, { 32, 1, 26 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21295), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21297), { 0, 0, height }, { 32, 1, 26 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

static void heartline_twister_rc_track_station(
    paint_session& session, const Ride& ride, [[maybe_unused]] uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    static constexpr const uint32_t imageIds[4][3] = {
        { 19732, SPR_STATION_BASE_B_SW_NE },
        { 19733, SPR_STATION_BASE_B_NW_SE },
        { 19732, SPR_STATION_BASE_B_SW_NE },
        { 19733, SPR_STATION_BASE_B_NW_SE },
    };

    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(imageIds[direction][0]), { 0, 0, height },
        { 32, 20, 1 }, { 0, 6, height + 3 });
    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours[SCHEME_MISC].WithIndex(imageIds[direction][1]), { 0, 0, height },
        { 32, 32, 1 });
    track_paint_util_draw_station_metal_supports_2(session, direction, height, session.TrackColours[SCHEME_SUPPORTS], 0);
    track_paint_util_draw_station(session, ride, direction, height, trackElement);
    PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_SQUARE_FLAT);
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
}

/** rct2: 0x0087695C */
static void heartline_twister_rc_track_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackElement.HasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21378), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21382), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21379), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21383), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21380), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21384), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21381), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21385), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21322), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21326), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 9, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21323), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21327), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 10, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21324), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21328), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 11, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21325), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21329), { 0, 0, height }, { 32, 1, 50 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 12, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, TUNNEL_1);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, TUNNEL_2);
    }
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 56, 0x20);
}

/** rct2: 0x008769FC */
static void heartline_twister_rc_track_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackElement.HasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21402), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21406), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 21, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21403), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21407), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 22, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21404), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21408), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 23, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21405), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21409), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 24, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21346), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21350), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 21, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21347), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21351), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 22, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21348), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21352), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 23, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21349), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21353), { 0, 0, height }, { 32, 1, 98 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 24, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, TUNNEL_1);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 56, TUNNEL_2);
    }
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 104, 0x20);
}

/** rct2: 0x0087696C */
static void heartline_twister_rc_track_flat_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackElement.HasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21362), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21366), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21363), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21367), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21364), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21368), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21365), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21369), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21306), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21310), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21307), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21311), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21308), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21312), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21309), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21313), { 0, 0, height }, { 32, 1, 42 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_2);
    }
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 48, 0x20);
}

/** rct2: 0x008769BC */
static void heartline_twister_rc_track_25_deg_up_to_60_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackElement.HasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21386), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21390), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 13, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21387), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21391), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 14, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21388), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21392), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 15, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21389), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21393), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21330), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21334), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 13, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21331), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21335), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 14, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21332), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21336), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 15, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21333), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21337), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 16, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, TUNNEL_1);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 24, TUNNEL_2);
    }
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 72, 0x20);
}

/** rct2: 0x008769CC */
static void heartline_twister_rc_track_60_deg_up_to_25_deg_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackElement.HasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21394), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21398), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 17, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21395), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21399), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 18, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21396), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21400), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 19, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21397), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21401), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 20, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21338), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21342), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 17, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21339), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21343), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 18, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                session.WoodenSupportsPrependTo = PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21340), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21344), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 19, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21341), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21345), { 0, 0, height }, { 32, 1, 66 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 20, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, TUNNEL_1);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 24, TUNNEL_2);
    }
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 72, 0x20);
}

/** rct2: 0x0087697C */
static void heartline_twister_rc_track_25_deg_up_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    if (trackElement.HasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21370), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21374), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 5, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21371), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21375), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 6, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21372), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21376), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 7, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21373), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21377), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21314), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21318), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 5, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21315), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21319), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 6, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21316), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21320), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 6, 7, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21317), { 0, 0, height }, { 32, 20, 2 },
                    { 0, 6, height });
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21321), { 0, 0, height }, { 32, 1, 34 },
                    { 0, 27, height });
                WoodenASupportsPaintSetup(session, 7, 8, height, session.TrackColours[SCHEME_SUPPORTS]);
                break;
        }
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, TUNNEL_0);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, TUNNEL_12);
    }
    PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 40, 0x20);
}

/** rct2: 0x0087698C */
static void heartline_twister_rc_track_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    heartline_twister_rc_track_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x00876A0C */
static void heartline_twister_rc_track_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    heartline_twister_rc_track_60_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x0087699C */
static void heartline_twister_rc_track_flat_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    heartline_twister_rc_track_25_deg_up_to_flat(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008769DC */
static void heartline_twister_rc_track_25_deg_down_to_60_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    heartline_twister_rc_track_60_deg_up_to_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008769EC */
static void heartline_twister_rc_track_60_deg_down_to_25_deg_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    heartline_twister_rc_track_25_deg_up_to_60_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x008769AC */
static void heartline_twister_rc_track_25_deg_down_to_flat(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    heartline_twister_rc_track_flat_to_25_deg_up(session, ride, trackSequence, (direction + 2) & 3, height, trackElement);
}

/** rct2: 0x00876A6C */
static void heartline_twister_rc_track_heartline_transfer_up(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21306), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21310), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 6, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21307), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21311), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 7, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21308), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21312), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 6, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21309), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21313), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 7, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            }
            else
            {
                PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_2);
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21314), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21308), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21318), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21312), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 6, 5, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21315), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21309), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21319), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21313), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 7, 6, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21316), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21306), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21320), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21310), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 6, 7, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21317), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21307), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21321), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21311), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 7, 8, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21298), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21302), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21299), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21303), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21300), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21304), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21301), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21305), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21316), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21320), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21317), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21321), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21314), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21318), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21315), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21319), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            }
            else
            {
                PaintUtilPushTunnelRotated(session, direction, height - 16, TUNNEL_0);
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x00876A7C */
static void heartline_twister_rc_track_heartline_transfer_down(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21316), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21320), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21317), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21321), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21314), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21318), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21315), { 0, 0, height - 8 },
                        { 32, 20, 2 }, { 0, 6, height - 7 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21319), { 0, 0, height - 8 },
                        { 32, 1, 34 }, { 0, 27, height - 8 });
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            }
            else
            {
                PaintUtilPushTunnelRotated(session, direction, height - 16, TUNNEL_0);
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21314), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21308), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21318), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21312), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 6, 5, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21315), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21309), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21319), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21313), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 7, 6, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21316), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21306), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21320), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21310), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 6, 7, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21317), { 0, 0, height + 8 },
                        { 32, 20, 2 }, { 0, 6, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21307), { 0, 0, height + 16 },
                        { 32, 20, 2 }, { 0, 6, height + 16 });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21321), { 0, 0, height + 8 },
                        { 32, 1, 34 }, { 0, 27, height + 8 });
                    PaintAddImageAsChildRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21311), { 0, 0, height + 16 },
                        { 32, 1, 34 }, { 0, 27, height + 16 });
                    WoodenASupportsPaintSetup(session, 7, 8, height + 8, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21298), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21302), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21299), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21303), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21300), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21304), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21301), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21305), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21306), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21310), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 6, 1, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21307), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21311), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 7, 2, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21308), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21312), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 6, 3, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21309), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21313), { 0, 0, height },
                        { 32, 20, 0 }, { 0, 6, height + 23 });
                    WoodenASupportsPaintSetup(session, 7, 4, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            }
            else
            {
                PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_2);
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48, 0x20);
            break;
    }
}

/** rct2: 0x00876A4C */
static void heartline_twister_rc_track_left_heartline_roll(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21410), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21422), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21413), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21425), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21416), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21428), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21419), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21431), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21411), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21423), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21414), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21426), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21417), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21429), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21420), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21432), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21412), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21424), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21415), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21427), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21418), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21430), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21421), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21433), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21418), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21430), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21421), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21433), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21412), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21424), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21415), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21427), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21417), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21429), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21420), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21432), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21411), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21423), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21414), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21426), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21416), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21428), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21419), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21431), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21410), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21422), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21413), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21425), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
    }
}

/** rct2: 0x00876A5C */
static void heartline_twister_rc_track_right_heartline_roll(
    paint_session& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21434), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21446), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21437), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21449), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21440), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21452), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21443), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21455), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21435), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21447), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21438), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21450), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21441), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21453), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21444), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21456), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21436), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21448), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21439), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21451), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21442), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21454), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21445), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21457), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21442), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21454), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21445), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21457), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21436), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21448), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21439), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21451), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21441), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21453), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21444), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21456), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21435), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21447), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21438), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21450), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21440), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21452), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21443), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21455), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21434), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21446), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 6, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21437), { 0, 0, height },
                        { 32, 20, 2 }, { 0, 6, height });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours[SCHEME_TRACK].WithIndex(21449), { 0, 0, height },
                        { 32, 1, 26 }, { 0, 27, height });
                    WoodenASupportsPaintSetup(session, 7, 0, height, session.TrackColours[SCHEME_SUPPORTS]);
                    break;
            }
            PaintUtilPushTunnelRotated(session, direction, height, TUNNEL_0);
            PaintUtilSetSegmentSupportHeight(session, SEGMENTS_ALL, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32, 0x20);
            break;
    }
}

TRACK_PAINT_FUNCTION get_track_paint_function_heartline_twister_rc(int32_t trackType)
{
    switch (trackType)
    {
        case TrackElemType::Flat:
            return heartline_twister_rc_track_flat;
        case TrackElemType::EndStation:
        case TrackElemType::BeginStation:
        case TrackElemType::MiddleStation:
            return heartline_twister_rc_track_station;
        case TrackElemType::Up25:
            return heartline_twister_rc_track_25_deg_up;
        case TrackElemType::Up60:
            return heartline_twister_rc_track_60_deg_up;
        case TrackElemType::FlatToUp25:
            return heartline_twister_rc_track_flat_to_25_deg_up;
        case TrackElemType::Up25ToUp60:
            return heartline_twister_rc_track_25_deg_up_to_60_deg_up;
        case TrackElemType::Up60ToUp25:
            return heartline_twister_rc_track_60_deg_up_to_25_deg_up;
        case TrackElemType::Up25ToFlat:
            return heartline_twister_rc_track_25_deg_up_to_flat;
        case TrackElemType::Down25:
            return heartline_twister_rc_track_25_deg_down;
        case TrackElemType::Down60:
            return heartline_twister_rc_track_60_deg_down;
        case TrackElemType::FlatToDown25:
            return heartline_twister_rc_track_flat_to_25_deg_down;
        case TrackElemType::Down25ToDown60:
            return heartline_twister_rc_track_25_deg_down_to_60_deg_down;
        case TrackElemType::Down60ToDown25:
            return heartline_twister_rc_track_60_deg_down_to_25_deg_down;
        case TrackElemType::Down25ToFlat:
            return heartline_twister_rc_track_25_deg_down_to_flat;
        case TrackElemType::HeartLineTransferUp:
            return heartline_twister_rc_track_heartline_transfer_up;
        case TrackElemType::HeartLineTransferDown:
            return heartline_twister_rc_track_heartline_transfer_down;
        case TrackElemType::LeftHeartLineRoll:
            return heartline_twister_rc_track_left_heartline_roll;
        case TrackElemType::RightHeartLineRoll:
            return heartline_twister_rc_track_right_heartline_roll;
    }
    return nullptr;
}
