#include "main.hpp"

#include "GlobalNamespace/FireworksController.hpp"

#include "bsml/shared/BSML/MainThreadScheduler.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Hook to delay the OnDisable function, deleting fireworks a few seconds after the function is first called
    MAKE_HOOK_MATCH(
        SmoothDisableHook,
        &FireworksController::OnDisable,
        void,
        FireworksController* self
    ) {
        // Run function as normal if smoothDisable is off
        if(!getModConfig().smoothDisable.GetValue()) {
            SmoothDisableHook(self);
            return;
        }

        // Call the original function with a delay of how long one firework will last
        BSML::MainThreadScheduler::ScheduleAfterTime(getModConfig().duration.GetValue(), [self](){
            if(!self->enabled) SmoothDisableHook(self); // Only delete fireworks if the FireworksController wasn't re-enabled in between the delay
        });
    }

    void InstallSmoothDisableHook() {
        INSTALL_HOOK(PaperLogger, SmoothDisableHook);
    }

}