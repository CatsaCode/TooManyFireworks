#include "main.hpp"

#include "fireworkManager.hpp"

#include "GlobalNamespace/FireworksController.hpp"

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

        // Don't try to despawn fireworks if the mainFireworksController hasn't been created yet
        if(mainFireworksController == nullptr) return;

        // Loop through each active firework and call the unhooked instant despawn function
        for(int i = mainFireworksController->_activeFireworks->Count - 1; i >= 0; i--) {
			mainFireworksController->ClearFireworkItemController(mainFireworksController->_activeFireworks->ToArray()[i]);
		}
    }

    void InstallDespawnOnSceneTransitionHotfixHook() {
        INSTALL_HOOK(PaperLogger, DespawnOnSceneTransitionHotfixHook);
    }

}