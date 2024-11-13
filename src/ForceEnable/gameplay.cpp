#include "main.hpp"

#include "fireworkManager.hpp"

#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Hook to enable the fireworks when the GameCore scene loads
    MAKE_HOOK_MATCH(
        ForceEnableGameplayHook,
        &SceneManagement::SceneManager::Internal_ActiveSceneChanged,
        void,
        SceneManagement::Scene previousActiveScene, 
        SceneManagement::Scene newActiveScene
    ) {
        // Run original function
        ForceEnableGameplayHook(previousActiveScene, newActiveScene);

        // Check in the original function
        if(!newActiveScene.IsValid()) return;

        // Only affect fireworks in this case if it is the main gameplay scene that was loaded
        if(!newActiveScene.name->Equals("GameCore")) return;

        // Enable or disable fireworks
        SetMainFireworksEnabled(getModConfig().enableInGameplay.GetValue());
    }

    void InstallForceEnableGameplayHook() {
        INSTALL_HOOK(PaperLogger, ForceEnableGameplayHook);
    }

}