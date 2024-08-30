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

    // Return a highly saturated color with a random hue
    UnityEngine::Color RandomSaturatedColor() {
        float h = (rand() % 256) / 256.0f;
        float s = 1.0f;
        float v = 1.0f;
        return UnityEngine::Color::HSVToRGB(h, s, v);
    }

    // Force update the settings on a FireworkItemController
    void UpdateFireworkItemController(FireworkItemController* fireworkItemController) {
        // Color
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

        // Brightness
        // Loop through all 4 TubeBloomPrePassLight components
        for(int i = 0; i < fireworkItemController->_lights->get_Length(); i++) {
            // fireworkItemController->_lights[i]->bloomFogIntensityMultiplier = 10; // Undefined
            // fireworkItemController->_lights[i]->_bloomFogIntensityMultiplier = 10; // Undefined
            // fireworkItemController->_lights[i]->set_bloomFogIntensityMultiplier(10); // Undefined
            // fireworkItemController->_lights[i]->__cordl_internal_set__bloomFogIntensityMultiplier(10); // Undefined
            fireworkItemController->_lights[i]->____bloomFogIntensityMultiplier = getModConfig().brightness.GetValue(); // Only one that's defined. If I don't make further comments, it will seem like I know what I'm doing
        }
        
        // Gravity
        fireworkItemController->_particleSystems[0]->_particleSystem->main.gravityModifierMultiplier = getModConfig().gravity.GetValue();
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



    // Set whether or not the fireworks are enabled
    void SetFireworksEnabled(bool enabled) {
        fireworksController->enabled = enabled;
    }

    // Set the minimum number of fireworks to spawn every second
    void SetSaveMinFrequency(float minFrequency) {
        getModConfig().minFrequency.SetValue(minFrequency);
        fireworksController->_maxSpawnInterval = 1.0f / minFrequency;
    }

    // Set the maximum number of fireworks to spawn every second
    void SetSaveMaxFrequency(float maxFrequency) {
        getModConfig().maxFrequency.SetValue(maxFrequency);
        fireworksController->_minSpawnInterval = 1.0f / maxFrequency;
    }

    // Set the static color of the fireworks
    void SetSaveColor(Color color) {
        getModConfig().color.SetValue(color);
        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }

    // Set the fireworks to use a random hue
    void SetSaveRainbow(bool rainbow) {
        getModConfig().rainbow.SetValue(rainbow);
        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }

    // Set the intensity of the firework directional lights
    void SetSaveBrightness(float brightness) {
        getModConfig().brightness.SetValue(brightness);
        // All light intensity stuff is for DirectionalLights, of which none exist
        // fireworksController->_lightsIntensity = brightness;

        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }

    // Set the gravity multiplier of the firework sparks
    void SetSaveGravity(float gravity) {
        getModConfig().gravity.SetValue(gravity);
        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
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

}