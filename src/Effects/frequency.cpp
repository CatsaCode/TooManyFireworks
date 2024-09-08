#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/FireworksController.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the frequency at which a FireworksController spawns fireworks
    void UpdateFrequency() {
        // Set the delay time between each FireworkItemController being spawned. Frequency in seconds has to be converted to coroutine wait seconds
        fireworksController->_maxSpawnInterval = 1.0f / getModConfig().minFrequency.GetValue();
        fireworksController->_minSpawnInterval = 1.0f / getModConfig().maxFrequency.GetValue();
    }

}