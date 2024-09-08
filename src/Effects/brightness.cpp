#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"
#include "GlobalNamespace/TubeBloomPrePassLight.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the brightness of a specific firework
    void UpdateBrightness(FireworkItemController* fireworkItemController) {
        // Update properties in all 4 TubeBloomPrePassLight components that light up the center
        for(int i = 0; i < fireworkItemController->_lights->get_Length(); i++) {
            // Set brightness of the light rays
            fireworkItemController->_lights[i]->bloomFogIntensityMultiplier = getModConfig().brightness.GetValue();
        }
    }

}