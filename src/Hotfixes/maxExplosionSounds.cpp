#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/AudioSource.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Maximum number of explosions that are allowed to play at once
    const int maxFireworkAudioSources = 4;

    // Array of all the explosion sound effects that are currently making noise
    std::vector<AudioSource*> activeFireworkAudioSources = {};


    // Hook overriding the explosion sfx function to stop Unity from reaching maximum number of sfx
    MAKE_HOOK_MATCH(
        MaxExplosionSoundsHotfixHookA,
        &FireworkItemController::PlayExplosionSound,
        void,
        FireworkItemController* self
    ) {
        // If maximum number of active explosions is reached, stop the oldest one to free up a spot
        if(activeFireworkAudioSources.size() >= maxFireworkAudioSources) {
            activeFireworkAudioSources[0]->Stop();
            activeFireworkAudioSources.erase(activeFireworkAudioSources.begin());
        }

        // Run original function
        MaxExplosionSoundsHotfixHookA(self);

        // Start tracking this audio source as actively playing
        activeFireworkAudioSources.push_back(self->_audioSource.ptr());
    }

    // Hook to remove an audio source from activeFireworkAudioSources once the firework is over
    MAKE_HOOK_MATCH(
        MaxExplosionSoundsHotfixHookB,
        &FireworkItemController::OnDisable,
        void,
        FireworkItemController* self
    ) {
        // Remove this audio source from activeFireworkAudioSources if it's still in the vector
        auto index = std::find(activeFireworkAudioSources.begin(), activeFireworkAudioSources.end(), self->_audioSource.ptr());
        if(index != activeFireworkAudioSources.end()) activeFireworkAudioSources.erase(index);

        // Run original function
        MaxExplosionSoundsHotfixHookB(self);
    }

    void InstallMaxExplosionSoundsHotfixHook() {
        INSTALL_HOOK(PaperLogger, MaxExplosionSoundsHotfixHookA);
        INSTALL_HOOK(PaperLogger, MaxExplosionSoundsHotfixHookB);
    }

    

}
