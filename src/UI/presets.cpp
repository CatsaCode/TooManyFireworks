#include "main.hpp"

#include "UI/modConfigMenu.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    void PresetFurzz() {
        getModConfig().minFrequency.SetValue(10.0f);
        getModConfig().maxFrequency.SetValue(20.0f);
        getModConfig().rainbow.SetValue(true);
        getModConfig().color.SetValue(Color(1.0f, 1.0f, 1.0f, 1.0f));
        getModConfig().brightness.SetValue(1.0f);
        getModConfig().minSize.SetValue(0.69f);
        getModConfig().maxSize.SetValue(1.0f);
        getModConfig().numSparks.SetValue(1500.0f);
        getModConfig().duration.SetValue(2.0f);
        getModConfig().gravity.SetValue(2.0f);
        getModConfig().collision.SetValue(true);
        getModConfig().dampen.SetValue(0.2f);
        getModConfig().bounce.SetValue(0.2f);
        getModConfig().volume.SetValue(0.3f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 10.5f, 4.5f));
        getModConfig().spawnRangeSize.SetValue(Vector3(20.0f, 10.5f, 10.0f));
        getModConfig().enableOnResultsHighscore.SetValue(true);
        getModConfig().enableOnResultsClear.SetValue(true);
        getModConfig().enableOnResultsFail.SetValue(false);
        getModConfig().resultsRequireFullCombo.SetValue(false);
        getModConfig().resultsMinimumAccuracy.SetValue(0.0f);
        getModConfig().enableInMainMenu.SetValue(false);
        getModConfig().enableInLevelSelection.SetValue(false);
        getModConfig().enableInGameplay.SetValue(false);
        getModConfig().enableInPauseMenu.SetValue(false);
        getModConfig().smoothDisable.SetValue(true);

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu();
    }

}