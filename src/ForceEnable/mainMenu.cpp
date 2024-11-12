#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/MainMenuViewController.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Hook to enable the fireworks when the main menu appears
    MAKE_HOOK_MATCH(
        ForceEnableMainMenuHook,
        &MainMenuViewController::DidActivate,
        void,
        MainMenuViewController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        ForceEnableMainMenuHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        // Enable or disable fireworks
        SetMainFireworksEnabled(getModConfig().enableInMainMenu.GetValue());
    }

    void InstallForceEnableMainMenuHook() {
        INSTALL_HOOK(PaperLogger, ForceEnableMainMenuHook);
    }

}