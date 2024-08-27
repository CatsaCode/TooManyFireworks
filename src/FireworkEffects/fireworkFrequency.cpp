#include "main.hpp"

#include "GlobalNamespace/FireworksController.hpp"

// Hook to reduce the time delay between fireworks
MAKE_HOOK_MATCH(
    FireworkFrequencyHook, 
    &GlobalNamespace::FireworksController::OnEnable, 
    void, 
    GlobalNamespace::FireworksController* self
) {
    // Reduce time between fireworks
    self->_minSpawnInterval = 0.05f;
    self->_maxSpawnInterval = 0.05f;

    // Run original function
    FireworkFrequencyHook(self);
}

void InstallFireworkFrequencyHook() {
    INSTALL_HOOK(PaperLogger, FireworkFrequencyHook);
}