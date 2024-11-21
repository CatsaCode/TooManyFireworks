#pragma once

#include <functional>

namespace HMUI {
    class ViewController;
}

namespace TooManyFireworks {

    extern std::function<void()> ForceUpdateModMenu;

    void ModConfigMenuDidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

}