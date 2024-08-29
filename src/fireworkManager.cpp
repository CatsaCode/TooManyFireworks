#include "main.hpp"
#include "fireworkManager.hpp"
#include "hookInstallers.hpp"

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/FireworksController.hpp"
#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    GameObject* fireworksControllerGo = nullptr;
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
        if(fireworksControllerGo == nullptr) PaperLogger.error("Could not find FireworksController game object");

        // Get and save FireworksController component
        fireworksController = fireworksControllerGo->GetComponent<FireworksController*>();
    }

    void InstallFindFireworksControllerHook() {
        INSTALL_HOOK(PaperLogger, FindFireworksControllerHook);
    }

    // Set whether or not the fireworks are enabled
    void SetFireworksEnabled(bool enabled) {
        fireworksController->enabled = enabled;
    }

    // Set minimum number of fireworks to spawn every second
    void SetSaveMinFrequency(float minFrequency) {
        getModConfig().minFrequency.SetValue(minFrequency);
        fireworksController->_maxSpawnInterval = 1.0f / minFrequency;
    }

    // Set maximum number of fireworks to spawn every second
    void SetSaveMaxFrequency(float maxFrequency) {
        getModConfig().maxFrequency.SetValue(maxFrequency);
        fireworksController->_minSpawnInterval = 1.0f / maxFrequency;
    }

    // Set the center position of the volume where fireworks spawn
    void SetSaveSpawnVolumeCenter(Vector3 position) {
        getModConfig().spawnVolumeCenter.SetValue(position);
        fireworksControllerGo->transform->position = position;
    }

    // Set the size of the volume where fireworks spawn
    void SetSaveSpawnVolumeSize(Vector3 size) {
        getModConfig().spawnVolumeSize.SetValue(size);
        fireworksController->_spawnSize = size;
    }

    // Return a highly saturated color with a random hue
    UnityEngine::Color RandomSaturatedColor() {
        float h = (rand() % 256) / 256.0f;
        float s = 1.0f;
        float v = 1.0f;
        return UnityEngine::Color::HSVToRGB(h, s, v);
    }

    void UpdateFireworkItemController(FireworkItemController* fireworkItemController) {
        // Get the color for the fireworks
        Color color = getModConfig().color.GetValue();
        // Switch the color to be random if enabled
        if(getModConfig().rainbow.GetValue()) color = RandomSaturatedColor();


        // Set the color that gets initialized to the lights and sparks
        fireworkItemController->_lightsColor = color;
        
        // Update the sparks to use the new color
        // TODO This still doesn't set every color quite right... Perhaps the FireworkItemController is being destroyed from _lightFlashDuration before the ParticleSystem finishes with the sparks?
        // Or it might just be that you can't set the color of particles that have already been launched...?
        fireworkItemController->_particleSystems[0]->_particleSystem->main.startColor = UnityEngine::ParticleSystem::MinMaxGradient(UnityEngine::ParticleSystemGradientMode::Color, nullptr, nullptr, color, color);
    }

    void SetSaveColor(Color color) {
        getModConfig().color.SetValue(color);

        // New FireworkItemControllers will have their settings changed in FireworkItemControllerSettingsHook.
        // Here, change the settings for the FireworkItemControllers that have already been created

        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();

        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }

    

    void SetSaveRainbow(bool rainbow) {
        getModConfig().rainbow.SetValue(rainbow);
        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }


    // Set settings when a FireworkItemController is first initialized
    MAKE_HOOK_MATCH(
        FireworkItemControllerSettingsHook,
        &FireworkItemController::Awake,
        void,
        FireworkItemController* self
    ) {
        UpdateFireworkItemController(self);

        // Call the original function
        FireworkItemControllerSettingsHook(self);
    }

    void InstallFireworkItemControllerSettingsHook() {
        INSTALL_HOOK(PaperLogger, FireworkItemControllerSettingsHook);
    }

}