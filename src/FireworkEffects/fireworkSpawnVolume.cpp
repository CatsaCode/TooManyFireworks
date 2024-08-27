#include "main.hpp"

#include "GlobalNamespace/FireworksController.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"

// Hook to resize and move the firework spawn range
MAKE_HOOK_MATCH(
    FireworkSpawnVolumeHook, 
    &GlobalNamespace::FireworksController::OnEnable, 
    void,
    GlobalNamespace::FireworksController* self
) {
    // Set spawn range of fireworks
    self->_spawnSize = UnityEngine::Vector3(1, 1, 1);
    self->transform->position = UnityEngine::Vector3(0, 0, 0);

    // Run original function
    FireworkSpawnVolumeHook(self);
}

void InstallFireworkSpawnVolumeHook() {
    INSTALL_HOOK(PaperLogger, FireworkSpawnVolumeHook);
}