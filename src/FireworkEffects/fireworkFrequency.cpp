#include "main.hpp"

#include "GlobalNamespace/FireworksController.hpp"
#include "modConfig.hpp"

// Hook to reduce the time delay between fireworks
MAKE_HOOK_MATCH(
    FireworkFrequencyHook, 
    &GlobalNamespace::FireworksController::OnEnable, 
    void, 
    GlobalNamespace::FireworksController* self
) {
    // Reduce time between fireworks
    // Min and max is backwards because higher fireworks per second results in a smaller interval between spawns
    self->_minSpawnInterval = 1.0f / getModConfig().maxFrequency.GetValue();
    self->_maxSpawnInterval = 1.0f / getModConfig().minFrequency.GetValue();

    // Run original function
    FireworkFrequencyHook(self);
}

void InstallFireworkFrequencyHook() {
    INSTALL_HOOK(PaperLogger, FireworkFrequencyHook);
}