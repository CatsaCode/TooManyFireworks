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

    // GameObject named "FireworksController" with the FireworksController component
    GameObject* fireworksControllerGo = nullptr;
    // Component that manages all the fireworks
    FireworksController* fireworksController = nullptr;

    // Hook to get the FireworksController component
    MAKE_HOOK_MATCH(
        FindFireworksControllerHook,
        &MainMenuViewController::DidActivate,
        void,
        MainMenuViewController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        FindFireworksControllerHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        // Only get FireworksController at the start of the game
        if(!firstActivation) return;

        // Get game object with the FireworksController component
        fireworksControllerGo = GameObject::Find("FireworksController");
        // Make sure game object was found
        if(fireworksControllerGo == nullptr) {
            PaperLogger.error("Could not find FireworksController game object");
            return;
        }

        // Get and save FireworksController component
        fireworksController = fireworksControllerGo->GetComponent<FireworksController*>();

        // Make sure fireworksController starts with the correctly set properties
        ForceUpdateFireworksController();
    }

    void InstallFindFireworksControllerHook() {
        INSTALL_HOOK(PaperLogger, FindFireworksControllerHook);
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
    }

    void InstallFireworkItemControllerPropertiesHook() {
        INSTALL_HOOK(PaperLogger, FireworkItemControllerPropertiesHook);
    }



    // Update a specific property of each FireworkItemController after it's been initialized
    void ForceUpdateEachFirework(std::function<void(FireworkItemController*)> fireworkItemControllerUpdateFunc) {
        // Don't update anything if the FireworksController was never found for any reason
        if(fireworksController == nullptr) return;

        // Loop through every FireworkItemController and pass it into the provided property update function
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) fireworkItemControllerUpdateFunc(fireworksController->_activeFireworks->ToArray()[i]);
    }
    
    // Update the properties on the FireworksController and its GameObject
    void ForceUpdateFireworksController() {
        // Don't update anything if the FireworksController was never found for any reason
        if(fireworksController == nullptr) return;

        // Set the few properties on the fireworksController and fireworksControllerGO variables
        UpdateFrequency();
        UpdateSpawnRange();
    }



    // Set whether or not the fireworks are enabled
    void SetFireworksEnabled(bool enabled) {
        // Return if the FireworksController was never found for any reason
        if(fireworksController == nullptr) return;

        // Enable the FireworksController component to make it start spawning fireworks
        // or disable it to make it delete all spawned fireworks and stop spawning more
        fireworksController->enabled = enabled;
    }

}