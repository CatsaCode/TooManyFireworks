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

        // Stop fireworks start coroutine so they aren't later enabled by the original function
        if(self->_startFireworksAfterDelayCoroutine != nullptr) self->StopCoroutine(self->_startFireworksAfterDelayCoroutine);
        self->_startFireworksAfterDelayCoroutine = nullptr;

        // Enable fireworks if the results match the mod preferences
        SetMainFireworksEnabled(
            ( // "Asked to turn on"
                (getModConfig().enableOnResultsFail.GetValue() && self->_levelCompletionResults->levelEndStateType != LevelCompletionResults::LevelEndStateType::Cleared) ||
                (getModConfig().enableOnResultsHighscore.GetValue() && self->_newHighScore) ||
                (getModConfig().enableOnResultsClear.GetValue() && self->_levelCompletionResults->levelEndStateType == LevelCompletionResults::LevelEndStateType::Cleared)
            ) && ( // "Required to turn on"
                (!getModConfig().resultsRequireFullCombo.GetValue() || self->_levelCompletionResults->fullCombo)
            )
        );
    }

    void InstallForceEnableLevelResultsHook() {
        INSTALL_HOOK(PaperLogger, ForceEnableLevelResultsHook);
    }

}