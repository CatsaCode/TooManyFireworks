#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/PauseMenuManager.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Hook to enable the fireworks when the pause menu appears
    MAKE_HOOK_MATCH(
        ForceEnablePauseMenuHook,
        &PauseMenuManager::ShowMenu,
        void,
        PauseMenuManager* self
    ) {
        // Run original function
        ForceEnablePauseMenuHook(self);

        // Enable or disable fireworks
        SetMainFireworksEnabled(getModConfig().enableInPauseMenu.GetValue());
    }

    // Hook to set the fireworks back to their enabled state before the pause menu appeared
    MAKE_HOOK_MATCH(
        ClosePauseMenuHook,
        &PauseMenuManager::StartResumeAnimation,
        void,
        PauseMenuManager* self
    ) {
        // Run original function
        ClosePauseMenuHook(self);

        // Enable or disale fireworks as they were before pausing the game
        SetMainFireworksEnabled(getModConfig().enableInGameplay.GetValue());
    }

    void InstallForceEnablePauseMenuHook() {
        INSTALL_HOOK(PaperLogger, ForceEnablePauseMenuHook);
        INSTALL_HOOK(PaperLogger, ClosePauseMenuHook);
    }

}