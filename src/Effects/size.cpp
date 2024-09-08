#include "main.hpp"
#include "fireworkManager.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"
#include "GlobalNamespace/TubeBloomPrePassLight.hpp"

#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the size of a specific firework
    void UpdateSize(FireworkItemController* fireworkItemController) {
        // Calculate a random size for the firework
        float size = (rand() % 1000) / 1000.0 * (getModConfig().maxSize.GetValue() - getModConfig().minSize.GetValue()) + getModConfig().minSize.GetValue();

        // Set how much velocity the sparks start with inside the MainModule of the ParticleSystem
        fireworkItemController->_particleSystems[0]->_particleSystem->main.startSpeedMultiplier = size * 34.8f;

        // Update properties in all 4 TubeBloomPrePassLight components that light up the center
        for(int i = 0; i < fireworkItemController->_lights->get_Length(); i++) {
            // Set the length of the rays
            fireworkItemController->_lights[i]->length = size * 10.0f;

            // TODO Is it the center property that changes the width of the center light?
        }
    }

}