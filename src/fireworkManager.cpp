#include "main.hpp"
#include "fireworkManager.hpp"
#include "hookInstallers.hpp"

#include "GlobalNamespace/MainMenuViewController.hpp"
#include "GlobalNamespace/FireworksController.hpp"
#include "GlobalNamespace/FireworkItemController.hpp"
#include "GlobalNamespace/TubeBloomPrePassLight.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

// Reimplementation of UnityEngine::ParticleSystem::Burst
struct ParticleSystemBurst {
    float time;
    ParticleSystem::MinMaxCurve count;
    int repeatCount;
    float repeatInterval;
    float invProbability;
};

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

        // Size of the whole firework
        float size = (rand() % 1000) / 1000.0 * (getModConfig().maxSize.GetValue() - getModConfig().minSize.GetValue()) + getModConfig().minSize.GetValue();


        // Set the color used for the bloom fog
        fireworkItemController->_lightsColor = color;
        // Set the color of the sparks
        fireworkItemController->_particleSystems[0]->_particleSystem->main.startColor = UnityEngine::ParticleSystem::MinMaxGradient(UnityEngine::ParticleSystemGradientMode::Color, nullptr, nullptr, color, color);

        // Brightness
        // Loop through all 4 TubeBloomPrePassLight components
        for(int i = 0; i < fireworkItemController->_lights->get_Length(); i++) {
            // Set brightness of the light rays
            fireworkItemController->_lights[i]->bloomFogIntensityMultiplier = getModConfig().brightness.GetValue();

            // Set length of the light rays
            fireworkItemController->_lights[i]->length = size * 10.0f;

            // TODO Is it the center property that changes the width of the center light?
        }

        // Explosion power
        fireworkItemController->_particleSystems[0]->_particleSystem->main.startSpeedMultiplier = size * 34.8f;
        
        // Gravity
        fireworkItemController->_particleSystems[0]->_particleSystem->main.gravityModifierMultiplier = getModConfig().gravity.GetValue();

        // Number of sparks
        fireworkItemController->_particleSystems[0]->_particleSystem->main.maxParticles = getModConfig().numSparks.GetValue();
        auto GetBurst = il2cpp_utils::resolve_icall<void, ParticleSystem::EmissionModule*, int, ParticleSystemBurst*>("UnityEngine.ParticleSystem/EmissionModule::GetBurst_Injected");
        auto SetBurst = il2cpp_utils::resolve_icall<void, ParticleSystem::EmissionModule*, int, ParticleSystemBurst*>("UnityEngine.ParticleSystem/EmissionModule::SetBurst_Injected");
        ParticleSystemBurst returnedBurst;
        ParticleSystem::EmissionModule emission = fireworkItemController->_particleSystems[0]->_particleSystem->emission;
        GetBurst(&emission, 0, &returnedBurst);
        returnedBurst.count.m_ConstantMax = getModConfig().numSparks.GetValue();
        SetBurst(&emission, 0, &returnedBurst);
    }

    // Set settings when a FireworkItemController is first initialized
    MAKE_HOOK_MATCH(
        FireworkItemControllerSettingsHook,
        &FireworkItemController::InitializeParticleSystem,
        void,
        FireworkItemController* self
    ) {
        // Call the original function (to be nice. UpdateFireworkItemController overwrites what default InitializeParticleSystem does)
        FireworkItemControllerSettingsHook(self);

        UpdateFireworkItemController(self);
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
        // TODO Does the pool need to be cleared anymore with the InitializeParticleSystem hook?
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

    // Set the intensity of the firework bloom fog
    void SetSaveBrightness(float brightness) {
        getModConfig().brightness.SetValue(brightness);
        // All light intensity stuff is for DirectionalLights, of which none exist
        // fireworksController->_lightsIntensity = brightness;

        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }

    // Set the minimum size of the whole firework
    void SetSaveMinSize(float minSize) {
        getModConfig().minSize.SetValue(minSize);
        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }

    // Set the maximum size of the whole firework
    void SetSaveMaxSize(float maxSize) {
        getModConfig().maxSize.SetValue(maxSize);
        // Clear the pool of FireworkItemControllers so that currently disabled fireworks will have to call FireworkItemControllerSettingsHook again
        fireworksController->_fireworkItemPool->Clear();
        // Loop through and update all of the enabled FireworkItemControllers on the FireworksController
        for(int i = 0; i < fireworksController->_activeFireworks->Count; i++) UpdateFireworkItemController(fireworksController->_activeFireworks->ToArray()[i]);
    }

    // Set the number of sparks in each firework
    void SetSaveNumSparks(int numSparks) {
        getModConfig().numSparks.SetValue(numSparks);
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