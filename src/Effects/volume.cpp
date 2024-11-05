#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/AudioSource.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the explosion volume of a specific firework
    void UpdateVolume(FireworkItemController* fireworkItemController) {
        // Set the volume property of the AudioSource component
        fireworkItemController->_audioSource->volume = getModConfig().volume.GetValue();
    }

}