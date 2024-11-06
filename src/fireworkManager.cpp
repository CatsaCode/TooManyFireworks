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

    // Component that manages all the fireworks
    FireworksController* soloFireworksController = nullptr;
    FireworksController* multiplayerFireworksController = nullptr;

    // Hook to get the solo FireworksController component
    MAKE_HOOK_MATCH(
        FindSoloFireworksControllerHook,
        &MainMenuViewController::DidActivate,
        void,
        MainMenuViewController* self,
        bool firstActivation, 
        bool addedToHierarchy, 
        bool screenSystemEnabling
    ) {
        // Run original function
        FindSoloFireworksControllerHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

        // Only get FireworksController at the start of the game
        if(!firstActivation) return;

        // Get the main FireworksController component
        soloFireworksController = GameObject::FindObjectOfType<FireworksController*>();
        // Make sure component was found
        if(soloFireworksController == nullptr) {
            PaperLogger.error("Could not find solo FireworksController");
            return;
        }

        // Make sure fireworksController starts with the correctly set properties
        ForceUpdateEachFireworksController();
    }

    void InstallFindSoloFireworksControllerHook() {
        INSTALL_HOOK(PaperLogger, FindSoloFireworksControllerHook);
    }

    // Hook to get the multiplayer FireworksController component
    // This hooks directly onto the OnEnable function unlike solo version because the multiplayer 
    // version seems to load at a weird time and solo needs to be found right at the start of the game
    MAKE_HOOK_MATCH(
        FindMultiplayerFireworksControllerHook,
        &FireworksController::OnEnable,
        void,
        FireworksController* self
    ) {
        // Run original function
        FindMultiplayerFireworksControllerHook(self);

        // Return if this is the solo FireworksController
        if(self == soloFireworksController) return;

        // Return if already found
        if(multiplayerFireworksController != nullptr) return;

        // Get the multiplayer FireworksController component
        multiplayerFireworksController = self;

        // Make sure fireworksController starts with the correctly set properties
        ForceUpdateEachFireworksController();
    }

    void InstallFindMultiplayerFireworksControllerHook() {
        INSTALL_HOOK(PaperLogger, FindMultiplayerFireworksControllerHook);
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
        UpdateVolume(self);
    }

    void InstallFireworkItemControllerPropertiesHook() {
        INSTALL_HOOK(PaperLogger, FireworkItemControllerPropertiesHook);
    }



    // Update a specific property of each FireworkItemController after it's been initialized
    void ForceUpdateEachFirework(std::function<void(FireworkItemController*)> fireworkItemControllerUpdateFunc) {
        // Loop through every FireworkItemController and pass it into the provided property update function
        if(soloFireworksController != nullptr) for(int i = 0; i < soloFireworksController->_activeFireworks->Count; i++) fireworkItemControllerUpdateFunc(soloFireworksController->_activeFireworks->ToArray()[i]);
        if(multiplayerFireworksController != nullptr) for(int i = 0; i < multiplayerFireworksController->_activeFireworks->Count; i++) fireworkItemControllerUpdateFunc(multiplayerFireworksController->_activeFireworks->ToArray()[i]);
    }

    // Update a specific property of each FireworksController 
    void ForceUpdateEachFireworksController(std::function<void(FireworksController*)> fireworksControllerUpdateFunc) {
        // Set the property on both of the FireworksController components if they've been found
        if(soloFireworksController != nullptr) fireworksControllerUpdateFunc(soloFireworksController);
        if(multiplayerFireworksController != nullptr) fireworksControllerUpdateFunc(multiplayerFireworksController);
    }

    // Update all of the properties on each FireworksController
    void ForceUpdateEachFireworksController() {
        ForceUpdateEachFireworksController(UpdateFrequency);
        ForceUpdateEachFireworksController(UpdateSpawnRange);
    }
    



    // Set whether or not the fireworks are enabled
    void SetFireworksEnabled(bool enabled) {
        // Enable the FireworksController component to make it start spawning fireworks
        // or disable it to make it delete all spawned fireworks and stop spawning more
        if(soloFireworksController != nullptr) soloFireworksController->enabled = enabled;
        if(multiplayerFireworksController != nullptr) multiplayerFireworksController->enabled = enabled;
    }

}