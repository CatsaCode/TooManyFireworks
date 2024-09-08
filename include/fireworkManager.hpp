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

    extern UnityEngine::GameObject* fireworksControllerGo;
    extern GlobalNamespace::FireworksController* fireworksController;

    void ForceUpdateAllFireworks(std::function<void(GlobalNamespace::FireworkItemController*)> fireworkItemControllerUpdateFunc);

    void SetFireworksEnabled(bool enabled);

}