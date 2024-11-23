#pragma once

#include <functional>

namespace GlobalNamespace {
    class FireworksController;
    class FireworkItemController;
}

namespace UnityEngine {
    class Vector3;
    class Color;
    class GameObject;
}

namespace TooManyFireworks {

    extern GlobalNamespace::FireworksController* mainFireworksController;

    void ForceUpdateEachMainFirework(std::function<void(GlobalNamespace::FireworkItemController*)> fireworkItemControllerUpdateFunc);
    void ForceUpdateMainFireworksController(std::function<void(GlobalNamespace::FireworksController*)> fireworksControllerUpdateFunc);

    void DespawnAllActiveMainFireworks();

    void SetMainFireworksEnabled(bool enabled);

}