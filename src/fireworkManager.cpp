#include "main.hpp"

#include "hookInstallers.hpp"
#include "fireworkManager.hpp"
#include "effects.hpp"

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/FireworksController.hpp"
#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/GameObject.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Component that manages all the fireworks in the main menu area
    FireworksController* mainFireworksController = nullptr;

    // Hook to get the main FireworksController component as soon as the main menu loads
    MAKE_HOOK_MATCH(
        FindMainFireworksControllerHook,
        &MainMenuViewController::DidActivate,
        void,
        MainMenuViewController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        FindMainFireworksControllerHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        // Only get FireworksController when the menu is loaded for the first time
        if(!firstActivation) return;

        // Get the main FireworksController component
        mainFireworksController = GameObject::FindObjectOfType<FireworksController*>();
        // Make sure component was found
        if(mainFireworksController == nullptr) {
            PaperLogger.error("Could not find main FireworksController");
            return;
        }

        // Allow main fireworks to exist outside of the main menu scene
        mainFireworksController->transform->parent = nullptr;
        GameObject::DontDestroyOnLoad(mainFireworksController->gameObject);
    }

    void InstallFindMainFireworksControllerHook() {
        INSTALL_HOOK(PaperLogger, FindMainFireworksControllerHook);
    }



    // Hook to ensure that both the main and new FireworksControllers created for multiplayer have their settings updated
    MAKE_HOOK_MATCH(
        FireworksControllersPropertiesHook,
        &FireworksController::OnEnable,
        void,
        FireworksController* self
    ) {
        // Set all of the properties for this FireworksController
        UpdateFrequency(self);
        UpdateSpawnRange(self);

        // Run original function
        // Done at the end so that the first coroutine has the correct frequency
        FireworksControllersPropertiesHook(self);
    }

    void InstallFireworksControllersPropertiesHook() {
        INSTALL_HOOK(PaperLogger, FireworksControllersPropertiesHook);
    }

    // Set settings when a FireworkItemController is first initialized
    MAKE_HOOK_MATCH(
        FireworkItemControllerPropertiesHook,
        &FireworkItemController::InitializeParticleSystem,
        void,
        FireworkItemController* self
    ) {
        // Call the original function (to be nice. Rest of this function overwrites what default InitializeParticleSystem does)
        FireworkItemControllerPropertiesHook(self);

        // Set all of the properties for the individual firework
        UpdateColor(self);
        UpdateBrightness(self);
        UpdateSize(self);
        UpdateNumSparks(self);
        UpdateDuration(self);
        UpdateGravity(self);
        UpdateCollision(self);
        UpdateDampenBounce(self);
        UpdateWind(self);
        UpdateVolume(self);
    }

    void InstallFireworkItemControllerPropertiesHook() {
        INSTALL_HOOK(PaperLogger, FireworkItemControllerPropertiesHook);
    }



    // Update a specific property of each FireworkItemController after it's been initialized
    void ForceUpdateEachMainFirework(std::function<void(FireworkItemController*)> fireworkItemControllerUpdateFunc) {
        // Don't update anything if the mainFireworksController was never found for any reason
        if(mainFireworksController == nullptr) return;

        // Loop through every FireworkItemController and pass it into the provided property update function
        for(int i = 0; i < mainFireworksController->_activeFireworks->Count; i++) fireworkItemControllerUpdateFunc(mainFireworksController->_activeFireworks->ToArray()[i]);
    }

    // Update a specific property of the main FireworksController
    void ForceUpdateMainFireworksController(std::function<void(FireworksController*)> fireworksControllerUpdateFunc) {
        // Don't update anything if the mainFireworksController was never found for any reason
        if(mainFireworksController == nullptr) return;

        // Give the main FireworksController to the update function
        fireworksControllerUpdateFunc(mainFireworksController);
    }



    // Instantly delete all of the currently visible fireworks on the mainFireworksController
    void DespawnAllActiveMainFireworks() {
        // Return if mainFireworksController was never found for any reason
        if(mainFireworksController == nullptr) return;

        // Loop through each active firework and call the unhooked instant despawn function
        for(int i = mainFireworksController->_activeFireworks->Count - 1; i >= 0; i--) {
			mainFireworksController->ClearFireworkItemController(mainFireworksController->_activeFireworks->ToArray()[i]);
		}
    }


    // Set whether or not the main menu's fireworks are enabled
    void SetMainFireworksEnabled(bool enabled) {
        // Return if mainFireworksController was never found for any reason
        if(mainFireworksController == nullptr) return;

        // Enable the main FireworksController component to make it start spawning fireworks
        // or disable it to make it delete all spawned fireworks and stop spawning more
        mainFireworksController->enabled = enabled;
    }

}