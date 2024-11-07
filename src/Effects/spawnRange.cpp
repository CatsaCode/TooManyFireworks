#include "main.hpp"

#include "GlobalNamespace/FireworksController.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the center position and size of where fireworks are allowed to spawn
    void UpdateSpawnRange(FireworksController* fireworksController) {
        // Set the center position of the spawn volume. This is controlled by the position of the FireworksController's GameObject
        fireworksController->transform->position = getModConfig().spawnRangeCenter.GetValue();
        // Set the size of the spawn volume. This is controller by the _spawnSize property on the FireworksController component
        fireworksController->_spawnSize = getModConfig().spawnRangeSize.GetValue();
    }

}