#pragma once

namespace GlobalNamespace {
    class FireworksController;
    class FireworkItemController;
}

namespace TooManyFireworks {

    // These effects use the fireworksControllerGo and fireworksController variables in fireworksManager.hpp
    void UpdateFrequency(GlobalNamespace::FireworksController* fireworksController);
    void UpdateSpawnRange(GlobalNamespace::FireworksController* fireworksController);

    // These effects modify properties in each firework individually
    void UpdateColor(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateBrightness(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateSize(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateNumSparks(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateDuration(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateGravity(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateCollision(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateDampenBounce(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateWind(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateVolume(GlobalNamespace::FireworkItemController* fireworkItemController);

}