#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/Color.hpp"

// Return a highly saturated color with a random hue
UnityEngine::Color RandomSaturatedColor() {
    float h = (rand() % 256) / 256.0f;
    float s = 1.0f;
    float v = 1.0f;
    return UnityEngine::Color::HSVToRGB(h, s, v);
}

// Hook to enable random color fireworks
MAKE_HOOK_MATCH(
    FireworkColorHook, 
    &GlobalNamespace::FireworkItemController::Awake, 
    void, 
    GlobalNamespace::FireworkItemController* self
) {
    // Run original function
    FireworkColorHook(self);

    // TODO This Awake hook is only called ONCE. Also, setting _lightsColor after InitializeParticleSystem will not extend the new colors to the subparticles

    // Set specific color
    self->_lightsColor = getModConfig().color.GetValue();

    // Set the firework to be a color of random hue
    if(getModConfig().rainbow.GetValue()) self->_lightsColor = RandomSaturatedColor();
}

void InstallFireworkColorHook() {
    INSTALL_HOOK(PaperLogger, FireworkColorHook);
}