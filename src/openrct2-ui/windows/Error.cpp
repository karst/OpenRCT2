/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include <algorithm>
#include <openrct2-ui/interface/Widget.h>
#include <openrct2-ui/windows/Window.h>
#include <openrct2/Context.h>
#include <openrct2/OpenRCT2.h>
#include <openrct2/audio/audio.h>
#include <openrct2/drawing/Drawing.h>
#include <openrct2/drawing/Font.h>
#include <openrct2/interface/Screenshot.h>
#include <openrct2/localisation/Formatter.h>
#include <openrct2/localisation/Localisation.h>

namespace OpenRCT2::Ui::Windows
{
    // clang-format off
enum {
    WIDX_BACKGROUND
};

static Widget window_error_widgets[] = {
    MakeWidget({0, 0}, {200, 42}, WindowWidgetType::ImgBtn, WindowColour::Primary),
    kWidgetsEnd,
};
    // clang-format on

    class ErrorWindow final : public Window
    {
    private:
        std::string _text;
        uint16_t _numLines;
        uint8_t _staleCount;
        bool _autoClose;

    public:
        ErrorWindow(std::string text, uint16_t numLines, bool autoClose)
            : _text(std::move(text))
            , _numLines(numLines)
            , _autoClose(autoClose)
        {
        }

        void OnOpen() override
        {
            window_error_widgets[WIDX_BACKGROUND].right = width;
            window_error_widgets[WIDX_BACKGROUND].bottom = height;

            widgets = window_error_widgets;
            _staleCount = 0;
            if (!gDisableErrorWindowSound)
            {
                OpenRCT2::Audio::Play(OpenRCT2::Audio::SoundId::Error, 0, windowPos.x + (width / 2));
            }
        }

        void OnDraw(DrawPixelInfo& dpi) override
        {
            ScreenCoordsXY leftTop{ windowPos };
            ScreenCoordsXY rightBottom{ windowPos + ScreenCoordsXY{ width - 1, height - 1 } };
            ScreenCoordsXY leftBottom{ leftTop.x, rightBottom.y };
            ScreenCoordsXY rightTop{ rightBottom.x, leftTop.y };

            GfxFilterRect(
                dpi, ScreenRect{ leftTop + ScreenCoordsXY{ 1, 1 }, rightBottom - ScreenCoordsXY{ 1, 1 } },
                FilterPaletteID::Palette45);
            GfxFilterRect(dpi, ScreenRect{ leftTop, rightBottom }, FilterPaletteID::PaletteGlassSaturatedRed);

            GfxFilterRect(
                dpi, ScreenRect{ leftTop + ScreenCoordsXY{ 0, 2 }, leftBottom - ScreenCoordsXY{ 0, 2 } },
                FilterPaletteID::PaletteDarken3);
            GfxFilterRect(
                dpi, ScreenRect{ rightTop + ScreenCoordsXY{ 0, 2 }, rightBottom - ScreenCoordsXY{ 0, 2 } },
                FilterPaletteID::PaletteDarken3);
            GfxFilterRect(
                dpi, ScreenRect{ leftBottom + ScreenCoordsXY{ 2, 0 }, rightBottom - ScreenCoordsXY{ 2, 0 } },
                FilterPaletteID::PaletteDarken3);
            GfxFilterRect(
                dpi, ScreenRect{ leftTop + ScreenCoordsXY{ 2, 0 }, rightTop - ScreenCoordsXY{ 2, 0 } },
                FilterPaletteID::PaletteDarken3);

            GfxFilterRect(
                dpi, ScreenRect{ rightTop + ScreenCoordsXY{ 1, 1 }, rightTop + ScreenCoordsXY{ 1, 1 } },
                FilterPaletteID::PaletteDarken3);
            GfxFilterRect(
                dpi, ScreenRect{ rightTop + ScreenCoordsXY{ -1, 1 }, rightTop + ScreenCoordsXY{ -1, 1 } },
                FilterPaletteID::PaletteDarken3);
            GfxFilterRect(
                dpi, ScreenRect{ leftBottom + ScreenCoordsXY{ 1, -1 }, leftBottom + ScreenCoordsXY{ 1, -1 } },
                FilterPaletteID::PaletteDarken3);
            GfxFilterRect(
                dpi, ScreenRect{ rightBottom - ScreenCoordsXY{ 1, 1 }, rightBottom - ScreenCoordsXY{ 1, 1 } },
                FilterPaletteID::PaletteDarken3);

            DrawStringCentredRaw(
                dpi, { leftTop + ScreenCoordsXY{ (width + 1) / 2 - 1, 1 } }, _numLines, _text.data(), FontStyle::Medium);
        }

        void OnPeriodicUpdate() override
        {
            // Close the window after 8 seconds of showing
            _staleCount++;
            if (_staleCount >= 8)
            {
                Close();
            }
        }

        void OnUpdate() override
        {
            // Automatically close previous screenshot messages before new screenshot is taken
            if (_autoClose && gScreenshotCountdown > 0)
            {
                Close();
            }
        }
    };

    WindowBase* ErrorOpen(std::string_view title, std::string_view message, bool autoClose)
    {
        std::string buffer = "{BLACK}";
        buffer.append(title);

        // Format the message
        if (!message.empty())
        {
            buffer.push_back('\n');
            buffer.append(message);
        }

        LOG_VERBOSE("show error, %s", buffer.c_str() + 1);

        // Don't do unnecessary work in headless. Also saves checking if cursor state is null.
        if (gOpenRCT2Headless)
        {
            return nullptr;
        }

        // Check if there is any text to display
        if (buffer.size() <= 1)
        {
            return nullptr;
        }

        // Close any existing error windows if they exist.
        WindowCloseByClass(WindowClass::Error);

        int32_t width = GfxGetStringWidthNewLined(buffer.data(), FontStyle::Medium);
        width = std::clamp(width, 64, 196);

        int32_t numLines{};
        GfxWrapString(buffer, width + 1, FontStyle::Medium, &buffer, &numLines);

        width = width + 3;
        int32_t height = (numLines + 1) * FontGetLineHeight(FontStyle::Medium) + 4;
        int32_t screenWidth = ContextGetWidth();
        int32_t screenHeight = ContextGetHeight();
        const CursorState* state = ContextGetCursorState();
        ScreenCoordsXY windowPosition = state->position - ScreenCoordsXY(width / 2, -26);
        windowPosition.x = std::clamp(windowPosition.x, 0, screenWidth);
        windowPosition.y = std::max(22, windowPosition.y);
        int32_t maxY = screenHeight - height;
        if (windowPosition.y > maxY)
        {
            windowPosition.y = std::min(windowPosition.y - height - 40, maxY);
        }

        auto errorWindow = std::make_unique<ErrorWindow>(std::move(buffer), numLines, autoClose);
        return WindowCreate(
            std::move(errorWindow), WindowClass::Error, windowPosition, width, height,
            WF_STICK_TO_FRONT | WF_TRANSPARENT | WF_RESIZABLE);
    }

    WindowBase* ErrorOpen(StringId title, StringId message, const Formatter& args, bool autoClose)
    {
        auto titlez = FormatStringIDLegacy(title, args.Data());
        auto messagez = FormatStringIDLegacy(message, args.Data());
        return ErrorOpen(titlez, messagez, autoClose);
    }
} // namespace OpenRCT2::Ui::Windows
