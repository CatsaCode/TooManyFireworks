#include "main.hpp"

#include "fireworkManager.hpp"

#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Hook to despawn all of the active fireworks when the scene is changed
    MAKE_HOOK_MATCH(
        DespawnOnSceneTransitionHotfixHook,
        &SceneManagement::SceneManager::Internal_ActiveSceneChanged,
        void,
        SceneManagement::Scene previousActiveScene, 
        SceneManagement::Scene newActiveScene
    ) {
        // Run original function
        DespawnOnSceneTransitionHotfixHook(previousActiveScene, newActiveScene);

        // Check in the original function
        if(!newActiveScene.IsValid()) return;

        DespawnAllActiveMainFireworks();
    }

    void InstallDespawnOnSceneTransitionHotfixHook() {
        INSTALL_HOOK(PaperLogger, DespawnOnSceneTransitionHotfixHook);
    }

}