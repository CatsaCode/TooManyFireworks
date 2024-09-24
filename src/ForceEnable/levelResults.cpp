#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"

#include "UnityEngine/Coroutine.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Hook to enable fireworks when level was cleared but no high score
    MAKE_HOOK_MATCH(
        ForceEnableLevelResultsHook,
        &GlobalNamespace::ResultsViewController::DidActivate,
        void,
        GlobalNamespace::ResultsViewController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        ForceEnableLevelResultsHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        // Level fail
        if(self->_levelCompletionResults->levelEndStateType != LevelCompletionResults::LevelEndStateType::Cleared) {
            SetFireworksEnabled(getModConfig().enableOnResultsFail.GetValue());
        }
        // Highscore
        else if(self->_newHighScore) {
            SetFireworksEnabled(getModConfig().enableOnResultsHighscore.GetValue());
            // Stop coroutine so they aren't later enabled by the original function
            if(self->_startFireworksAfterDelayCoroutine != nullptr) self->StopCoroutine(self->_startFireworksAfterDelayCoroutine);
            self->_startFireworksAfterDelayCoroutine = nullptr;
            return;
        }
        // Level clear
        else if(self->_levelCompletionResults->levelEndStateType == LevelCompletionResults::LevelEndStateType::Cleared) {
            SetFireworksEnabled(getModConfig().enableOnResultsClear.GetValue());
            return;
        }
    }

    void InstallForceEnableLevelResultsHook() {
        INSTALL_HOOK(PaperLogger, ForceEnableLevelResultsHook);
    }

}