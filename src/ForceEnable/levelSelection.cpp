#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"

#include "GlobalNamespace/LevelCollectionNavigationController.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Whether or not to skip toggling fireworks in the next call to LevelCollectionNavigationController::DidActivate
    bool skipNextActivation = false;
    
    // Skip next call when level is failed or finished
    MAKE_HOOK_MATCH(
        DetectLevelStartHook,
        &AudioTimeSyncController::StartSong,
        void,
        AudioTimeSyncController* self,
        float startTimeOffset
    ) {
        DetectLevelStartHook(self, startTimeOffset);
        
        skipNextActivation = true;
    }

    // Skip next call during transition from results screen to gameplay
    MAKE_HOOK_MATCH(
        DetectResultsRestartHook,
        &ResultsViewController::RestartButtonPressed,
        void,
        ResultsViewController* self
    ) {
        DetectResultsRestartHook(self);
        
        skipNextActivation = true;
    }

    // The menu button in the pause menu skips the results screen and therefore the second activation, cancel previously setting the flag
    MAKE_HOOK_MATCH(
        DetectMenuFromPauseHook,
        &PauseMenuManager::MenuButtonPressed,
        void,
        PauseMenuManager* self
    ) {
        DetectMenuFromPauseHook(self);
        
        skipNextActivation = false;
    }

    // Hook to enable the fireworks in the menu for selecting levels
    MAKE_HOOK_MATCH(
        ForceEnableLevelSelectionHook,
        &LevelCollectionNavigationController::DidActivate,
        void,
        LevelCollectionNavigationController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        ForceEnableLevelSelectionHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);
        
        // The LevelCollectionNavigationController has a few additional situations where it may activate; skip them
        if(skipNextActivation) {
            skipNextActivation = false;
            return;
        }

        // Enable or disable fireworks
        SetMainFireworksEnabled(getModConfig().enableInLevelSelection.GetValue());
    }

    void InstallForceEnableLevelSelectionHook() {
        INSTALL_HOOK(PaperLogger, DetectLevelStartHook);
        INSTALL_HOOK(PaperLogger, DetectResultsRestartHook);
        INSTALL_HOOK(PaperLogger, DetectMenuFromPauseHook);
        INSTALL_HOOK(PaperLogger, ForceEnableLevelSelectionHook);
    }

}