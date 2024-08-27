#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/Color.hpp"

// Hook to enable random color fireworks
MAKE_HOOK_MATCH(
    FireworkColorHook, 
    &GlobalNamespace::FireworkItemController::Awake, 
    void, 
    GlobalNamespace::FireworkItemController* self
) {
    // Run original function
    FireworkColorHook(self);

    // Set the firework to be a randomly generated color
    float h = (rand() % 256) / 256.0f;
    float s = 1.0f;
    float v = 1.0f;
    self->_lightsColor = UnityEngine::Color::HSVToRGB(h, s, v);

    // // Set the firework to be red
    // self->_lightsColor.r = 1.0f;
    // self->_lightsColor.g = 0.0f;
    // self->_lightsColor.b = 0.0f;
}

void InstallFireworkColorHook() {
    INSTALL_HOOK(PaperLogger, FireworkColorHook);
}