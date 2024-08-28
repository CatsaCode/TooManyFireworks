#include "main.hpp"

#include "GlobalNamespace/FireworksController.hpp"

#include "UnityEngine/Transform.hpp"

// Hook to resize and move the firework spawn range
MAKE_HOOK_MATCH(
    FireworkSpawnVolumeHook, 
    &GlobalNamespace::FireworksController::OnEnable, 
    void,
    GlobalNamespace::FireworksController* self
) {
    // Set spawn range of fireworks
    self->transform->position = getModConfig().spawnOrigin.GetValue();
    self->_spawnSize = getModConfig().spawnSize.GetValue();

    // Run original function
    FireworkSpawnVolumeHook(self);
}

void InstallFireworkSpawnVolumeHook() {
    INSTALL_HOOK(PaperLogger, FireworkSpawnVolumeHook);
}