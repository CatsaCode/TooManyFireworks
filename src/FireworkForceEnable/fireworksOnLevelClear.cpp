#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"

namespace TooManyFireworks {

    // Hook to enable fireworks when level was cleared but no high score
    MAKE_HOOK_MATCH(
        FireworksOnLevelClearHook,
        &GlobalNamespace::ResultsViewController::DidActivate,
        void,
        GlobalNamespace::ResultsViewController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        FireworksOnLevelClearHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        // Return if not enabled
        if(!getModConfig().enableOnLevelClear.GetValue()) return;

        // Enable fireworks manually. Can't figure out coroutines like the original function
        SetFireworksEnabled(true);
    }

    void InstallFireworksOnLevelClearHook() {
        INSTALL_HOOK(PaperLogger, FireworksOnLevelClearHook);
    }

}