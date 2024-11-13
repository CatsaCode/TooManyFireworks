#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/SelectLevelCategoryViewController.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Hook to enable the fireworks in the menu for selecting levels
    MAKE_HOOK_MATCH(
        ForceEnableLevelSelectionHook,
        &SelectLevelCategoryViewController::DidActivate,
        void,
        SelectLevelCategoryViewController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        ForceEnableLevelSelectionHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        // For some reason, this activates when the results screen appears? Then again after closing the results screen? And these seem to be the only two instances where addedToHierarchy is false? Um... sort this weirdness out I guess
        static bool lastAddedToHierarchy = false;
        if(lastAddedToHierarchy && !addedToHierarchy) {
            lastAddedToHierarchy = addedToHierarchy;
            return;
        }
        lastAddedToHierarchy = addedToHierarchy;

        // Enable or disable fireworks
        SetMainFireworksEnabled(getModConfig().enableInLevelSelection.GetValue());
    }

    void InstallForceEnableLevelSelectionHook() {
        INSTALL_HOOK(PaperLogger, ForceEnableLevelSelectionHook);
    }

}