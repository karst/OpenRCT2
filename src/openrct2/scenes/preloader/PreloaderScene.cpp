/*****************************************************************************
 * Copyright (c) 2014-2024 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "PreloaderScene.h"

#include "../../Context.h"
#include "../../Game.h"
#include "../../GameState.h"
#include "../../OpenRCT2.h"
#include "../../audio/audio.h"
#include "../../drawing/IDrawingContext.h"
#include "../../drawing/IDrawingEngine.h"
#include "../../interface/Viewport.h"
#include "../../interface/Window.h"
#include "../../localisation/LocalisationService.h"
#include "../../localisation/StringIds.h"
#include "../../windows/Intent.h"

#include <sstream>

using namespace OpenRCT2;

PreloaderScene::PreloaderScene(IContext& context)
    : Scene(context)
    , _jobs(1)
{
}

void PreloaderScene::Load()
{
    LOG_VERBOSE("PreloaderScene::Load()");

    gScreenFlags = SCREEN_FLAGS_PLAYING;
    gameStateInitAll(GetGameState(), DEFAULT_MAP_SIZE);
    ViewportInitAll();
    ContextOpenWindow(WindowClass::MainWindow);
    WindowResizeGui(ContextGetWidth(), ContextGetHeight());

    // Reset screen
    auto* engine = GetContext().GetDrawingEngine();
    auto* drawingContext = engine->GetDrawingContext();
    drawingContext->Clear(*engine->GetDrawingPixelInfo(), PALETTE_INDEX_10);

    LOG_VERBOSE("PreloaderScene::Load() finished");
}

void PreloaderScene::Tick()
{
    gInUpdateCode = true;

    ContextHandleInput();
    WindowInvalidateAll();

    gInUpdateCode = false;

    if (_jobs.CountPending() == 0 && _jobs.CountProcessing() == 0)
    {
        // Make sure the job is fully completed.
        _jobs.Join();

        FinishScene();
    }
}

void PreloaderScene::Stop()
{
    Audio::StopAll();
}
