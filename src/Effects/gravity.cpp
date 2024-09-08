#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the gravity of a specific firework
    void UpdateGravity(FireworkItemController* fireworkItemController) {
        // Set the gravity muliplier inside the MainModule of the ParticleSystem
        fireworkItemController->_particleSystems[0]->_particleSystem->main.gravityModifierMultiplier = getModConfig().gravity.GetValue();
    }

}