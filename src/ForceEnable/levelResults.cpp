#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/ScoreController.hpp"

#include "UnityEngine/Coroutine.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Variable used to calculate the accuracy percentage at the level results screen
    int trackedMaxScore = 0;

    // Hook to enable fireworks when level was cleared but no high score
    MAKE_HOOK_MATCH(
        ForceEnableLevelResultsHook,
        &ResultsViewController::DidActivate,
        void,
        ResultsViewController* self,
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
                ( getModConfig().enableOnResultsFail.GetValue()       &&  self->_levelCompletionResults->levelEndStateType != LevelCompletionResults::LevelEndStateType::Cleared     ) ||
                ( getModConfig().enableOnResultsHighscore.GetValue()  &&  self->_newHighScore                                                                                        ) ||
                ( getModConfig().enableOnResultsClear.GetValue()      &&  self->_levelCompletionResults->levelEndStateType == LevelCompletionResults::LevelEndStateType::Cleared     )
            ) && ( // "Required to turn on"
                ( !getModConfig().resultsRequireFullCombo.GetValue()  ||  self->_levelCompletionResults->fullCombo                                                                   ) &&
                ( getModConfig().enableOnResultsFail.GetValue()       ||  self->_levelCompletionResults->levelEndStateType == LevelCompletionResults::LevelEndStateType::Cleared     ) && // Don't enable fireworks if the level was failed without on fail checked
                ( getModConfig().resultsMinimumAccuracy.GetValue()    <=  (trackedMaxScore != 0 ? (float)self->_levelCompletionResults->modifiedScore / trackedMaxScore * 100 : 100) )    // If the map has a possible score then calculate the score, otherwise assume 100% accuracy
            )
        );
    }

    void InstallForceEnableLevelResultsHook() {
        INSTALL_HOOK(PaperLogger, ForceEnableLevelResultsHook);
    }


    // Hook to keep track of the maximum score so that it can be used to calculate the accuracy percentage at the level results screen
    MAKE_HOOK_MATCH(
        MaxScoreTrackerHook,
        &ScoreController::LateUpdate,
        void,
        ScoreController* self
    ) {
        // Run original function
        MaxScoreTrackerHook(self);

        // Save the maximum score to a variable so it can be retrieved at the results screen
        trackedMaxScore = self->_immediateMaxPossibleModifiedScore;
    }

    void InstallMaxScoreTrackerHook() {
        INSTALL_HOOK(PaperLogger, MaxScoreTrackerHook);
    }

}