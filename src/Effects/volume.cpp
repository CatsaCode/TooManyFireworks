#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/AudioSource.hpp"
#include "UnityEngine/Audio/AudioMixerGroup.hpp"
#include "UnityEngine/Resources.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // AudioMixerGroup that the main volume setting controls
    Audio::AudioMixerGroup* mainAudioMixerGroup = nullptr;

    // Set the explosion volume of a specific firework
    void UpdateVolume(FireworkItemController* fireworkItemController) {
        // Set the volume property of the AudioSource component
        fireworkItemController->_audioSource->volume = getModConfig().volume.GetValue();

        // Find what might be the main AudioMixerGroup. Index 0 is definitely for sound effects like misses, indices 1 and 2 don't seem different at first glance
        if(mainAudioMixerGroup == nullptr) mainAudioMixerGroup = Resources::FindObjectsOfTypeAll<Audio::AudioMixerGroup*>()[1];
        // Switch the AudioSource's AudioMixerGroup from SFX to main
        fireworkItemController->_audioSource->outputAudioMixerGroup = mainAudioMixerGroup;
    }

}