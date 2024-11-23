#include "main.hpp"

#include "UI/modConfigMenu.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    void PresetDefault() {
        getModConfig().minFrequency.SetValue(1.0f);
        getModConfig().maxFrequency.SetValue(5.0f);
        getModConfig().rainbow.SetValue(false);
        getModConfig().color.SetValue(Color(0.0f/255.0f, 192.0f/255.0f, 255.0f/255.0f, 1.0f));
        getModConfig().brightness.SetValue(1.0f);
        getModConfig().minSize.SetValue(0.69f);
        getModConfig().maxSize.SetValue(1.0f);
        getModConfig().numSparks.SetValue(70.0f);
        getModConfig().duration.SetValue(1.5f);
        getModConfig().gravity.SetValue(0.0f);
        getModConfig().collision.SetValue(false);
        getModConfig().dampen.SetValue(0.0f);
        getModConfig().bounce.SetValue(1.0f);
        getModConfig().windStrength.SetValue(0.0f);
        getModConfig().windTurbulence.SetValue(0.5f);
        getModConfig().volume.SetValue(0.6f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 11.39f, 12.57f));
        getModConfig().spawnRangeSize.SetValue(Vector3(20.0f, 10.5f, 2.0f));
        getModConfig().enableOnResultsHighscore.SetValue(true);
        getModConfig().enableOnResultsClear.SetValue(false);
        getModConfig().enableOnResultsFail.SetValue(false);
        getModConfig().resultsRequireFullCombo.SetValue(false);
        getModConfig().resultsMinimumAccuracy.SetValue(0.0f);
        getModConfig().enableInMainMenu.SetValue(false);
        getModConfig().enableInLevelSelection.SetValue(false);
        getModConfig().enableInGameplay.SetValue(false);
        getModConfig().enableInPauseMenu.SetValue(false);
        getModConfig().smoothDisable.SetValue(false);

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

    void PresetEnhancedDefault() {
        getModConfig().minFrequency.SetValue(3.0f);
        getModConfig().maxFrequency.SetValue(10.0f);
        getModConfig().rainbow.SetValue(true);
        getModConfig().color.SetValue(Color(0.0f/255.0f, 192.0f/255.0f, 255.0f/255.0f, 1.0f));
        getModConfig().brightness.SetValue(1.0f);
        getModConfig().minSize.SetValue(0.69f);
        getModConfig().maxSize.SetValue(1.0f);
        getModConfig().numSparks.SetValue(500.0f);
        getModConfig().duration.SetValue(1.5f);
        getModConfig().gravity.SetValue(0.2f);
        getModConfig().collision.SetValue(true);
        getModConfig().dampen.SetValue(0.2f);
        getModConfig().bounce.SetValue(0.2f);
        getModConfig().windStrength.SetValue(0.0f);
        getModConfig().windTurbulence.SetValue(0.5f);
        getModConfig().volume.SetValue(0.6f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 11.39f, 12.57f));
        getModConfig().spawnRangeSize.SetValue(Vector3(20.0f, 10.5f, 2.0f));
        getModConfig().enableOnResultsHighscore.SetValue(true);
        getModConfig().enableOnResultsClear.SetValue(false);
        getModConfig().enableOnResultsFail.SetValue(false);
        getModConfig().resultsRequireFullCombo.SetValue(false);
        getModConfig().resultsMinimumAccuracy.SetValue(0.0f);
        getModConfig().enableInMainMenu.SetValue(false);
        getModConfig().enableInLevelSelection.SetValue(false);
        getModConfig().enableInGameplay.SetValue(false);
        getModConfig().enableInPauseMenu.SetValue(false);
        getModConfig().smoothDisable.SetValue(true);

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

    void PresetRain() {
        getModConfig().minFrequency.SetValue(30.0f);
        getModConfig().maxFrequency.SetValue(30.0f);
        getModConfig().rainbow.SetValue(false);
        getModConfig().color.SetValue(Color(45.0f/255.0f, 65.0f/255.0f, 255.0f/255.0f, 1.0f));
        getModConfig().brightness.SetValue(0.1f);
        getModConfig().minSize.SetValue(1.0f);
        getModConfig().maxSize.SetValue(1.0f);
        getModConfig().numSparks.SetValue(500.0f);
        getModConfig().duration.SetValue(5.0f);
        getModConfig().gravity.SetValue(5.0f);
        getModConfig().collision.SetValue(true);
        getModConfig().dampen.SetValue(0.1f);
        getModConfig().bounce.SetValue(0.3f);
        getModConfig().windStrength.SetValue(0.0f);
        getModConfig().windTurbulence.SetValue(0.5f);
        getModConfig().volume.SetValue(0.15f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 25.0f, 0.0f));
        getModConfig().spawnRangeSize.SetValue(Vector3(10.0f, 0.0f, 10.0f));

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

    void PresetFire() {
        getModConfig().minFrequency.SetValue(20.0f);
        getModConfig().maxFrequency.SetValue(20.0f);
        getModConfig().rainbow.SetValue(false);
        getModConfig().color.SetValue(Color(255.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.0f));
        getModConfig().brightness.SetValue(25.0f);
        getModConfig().minSize.SetValue(0.5f);
        getModConfig().maxSize.SetValue(0.5f);
        getModConfig().numSparks.SetValue(1000.0f);
        getModConfig().duration.SetValue(4.8f);
        getModConfig().gravity.SetValue(-1.0f);
        getModConfig().collision.SetValue(false);
        getModConfig().windStrength.SetValue(1.3f);
        getModConfig().windTurbulence.SetValue(0.2f);
        getModConfig().volume.SetValue(0.15f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, -4.0f, 0.0f));
        getModConfig().spawnRangeSize.SetValue(Vector3(20.0f, 0.0f, 20.0f));

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

    void PresetSnow() {
        getModConfig().minFrequency.SetValue(10.0f);
        getModConfig().maxFrequency.SetValue(10.0f);
        getModConfig().rainbow.SetValue(false);
        getModConfig().color.SetValue(Color(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f));
        getModConfig().brightness.SetValue(5.0f);
        getModConfig().minSize.SetValue(0.5f);
        getModConfig().maxSize.SetValue(0.5f);
        getModConfig().numSparks.SetValue(500.0f);
        getModConfig().duration.SetValue(10.0f);
        getModConfig().gravity.SetValue(0.5f);
        getModConfig().collision.SetValue(true);
        getModConfig().dampen.SetValue(0.1f);
        getModConfig().bounce.SetValue(0.1f);
        getModConfig().windStrength.SetValue(0.5f);
        getModConfig().windTurbulence.SetValue(0.3f);
        getModConfig().volume.SetValue(0.0f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 6.0f, 0.0f));
        getModConfig().spawnRangeSize.SetValue(Vector3(10.0f, 0.0f, 10.0f));

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

    void PresetLightShow() {
        getModConfig().minFrequency.SetValue(50.0f);
        getModConfig().maxFrequency.SetValue(50.0f);
        getModConfig().rainbow.SetValue(true);
        getModConfig().brightness.SetValue(10.0f);
        getModConfig().minSize.SetValue(1.5f);
        getModConfig().maxSize.SetValue(1.5f);
        getModConfig().numSparks.SetValue(0.0f);
        getModConfig().duration.SetValue(3.0f);
        getModConfig().volume.SetValue(0.0f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 0.0f, 0.0f));
        getModConfig().spawnRangeSize.SetValue(Vector3(20.0f, 20.5f, 20.0f));

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

    void PresetConfetti() {
        getModConfig().minFrequency.SetValue(10.0f);
        getModConfig().maxFrequency.SetValue(20.0f);
        getModConfig().rainbow.SetValue(true);
        getModConfig().brightness.SetValue(1.0f);
        getModConfig().minSize.SetValue(0.69f);
        getModConfig().maxSize.SetValue(1.0f);
        getModConfig().numSparks.SetValue(1500.0f);
        getModConfig().duration.SetValue(2.0f);
        getModConfig().gravity.SetValue(2.0f);
        getModConfig().collision.SetValue(true);
        getModConfig().dampen.SetValue(0.2f);
        getModConfig().bounce.SetValue(0.2f);
        getModConfig().windStrength.SetValue(0.0f);
        getModConfig().windTurbulence.SetValue(0.5f);
        getModConfig().volume.SetValue(0.3f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 10.5f, 4.5f));
        getModConfig().spawnRangeSize.SetValue(Vector3(20.0f, 10.5f, 10.0f));

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

    void PresetSwirls() {
        getModConfig().minFrequency.SetValue(10.0f);
        getModConfig().maxFrequency.SetValue(50.0f);
        getModConfig().rainbow.SetValue(true);
        getModConfig().brightness.SetValue(0.0f);
        getModConfig().minSize.SetValue(0.01f);
        getModConfig().maxSize.SetValue(0.02f);
        getModConfig().numSparks.SetValue(1500.0f);
        getModConfig().duration.SetValue(2.5f);
        getModConfig().gravity.SetValue(0.0f);
        getModConfig().windStrength.SetValue(5.0f);
        getModConfig().windTurbulence.SetValue(0.6f);
        getModConfig().volume.SetValue(0.0f);
        getModConfig().spawnRangeCenter.SetValue(Vector3(0.0f, 5.5f, 14.5f));
        getModConfig().spawnRangeSize.SetValue(Vector3(20.0f, 10.5f, 10.0f));

        if(ForceUpdateModMenu != nullptr) ForceUpdateModMenu(false);
    }

}