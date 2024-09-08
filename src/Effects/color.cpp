#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/Color.hpp"
#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Return a highly saturated color with a random hue
    Color RandomSaturatedColor() {
        float h = (rand() % 256) / 256.0f;
        float s = 1.0f;
        float v = 1.0f;
        return Color::HSVToRGB(h, s, v);
    }

    // Set the color of a specific firework
    void UpdateColor(FireworkItemController* fireworkItemController) {
        // Get the color for the fireworks
        Color color = getModConfig().color.GetValue();
        // Switch the color to be random if rainbow mode is enabled
        if(getModConfig().rainbow.GetValue()) color = RandomSaturatedColor();

        // Set the color used for the bloom fog
        fireworkItemController->_lightsColor = color;

        // Set the color of the sparks manually for if _lightsColor was changed after FireworkItemController::InitializeParticleSystem()
        fireworkItemController->_particleSystems[0]->_particleSystem->main.startColor = UnityEngine::ParticleSystem::MinMaxGradient(UnityEngine::ParticleSystemGradientMode::Color, nullptr, nullptr, color, color);
    }


}
