#include "main.hpp"

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

        // Check that is in the original function before starting fireworks
        if(!addedToHierarchy) return;

        // Don't play if level wasn't cleared
        if(self->_levelCompletionResults->levelEndStateType != GlobalNamespace::LevelCompletionResults::LevelEndStateType::Cleared) return;
        // Don't play if the original function already started playing it
        if(self->_newHighScore) return;

        // Enable fireworks manually. Can't figure out coroutines like the original function
        self->_fireworksController->enabled = true;
    }

    void InstallFireworksOnLevelClearHook() {
        INSTALL_HOOK(PaperLogger, FireworksOnLevelClearHook);
    }

}