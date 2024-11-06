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

    extern GlobalNamespace::FireworksController* soloFireworksController;
    extern GlobalNamespace::FireworksController* multiplayerFireworksController;

    void ForceUpdateEachFirework(std::function<void(GlobalNamespace::FireworkItemController*)> fireworkItemControllerUpdateFunc);
    void ForceUpdateEachFireworksController(std::function<void(GlobalNamespace::FireworksController*)> fireworksControllerUpdateFunc);
    void ForceUpdateEachFireworksController();

    void SetFireworksEnabled(bool enabled);

}