#pragma once

namespace GlobalNamespace {
    class FireworkItemController;
}

namespace TooManyFireworks {

    // These effects use the fireworksControllerGo and fireworksController variables in fireworksManager.hpp
    void UpdateFrequency();
    void UpdateSpawnRange();

    // These effects modify properties in each firework individually
    void UpdateColor(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateBrightness(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateSize(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateNumSparks(GlobalNamespace::FireworkItemController* fireworkItemController);
    void UpdateGravity(GlobalNamespace::FireworkItemController* fireworkItemController);

}