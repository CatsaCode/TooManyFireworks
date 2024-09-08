#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Reimplementation of UnityEngine::ParticleSystem::Burst
    struct ParticleSystemBurst {
        float time;
        // Number of particles in the Burst
        ParticleSystem::MinMaxCurve count;
        int repeatCount;
        float repeatInterval;
        float invProbability;
    };
    

    // Set the number of sparks in a specific firework
    void UpdateNumSparks(FireworkItemController* fireworkItemController) {
        // Set maximum number of sparks in the MainModule of the ParticleSystem to handle the number of sparks being requested
        fireworkItemController->_particleSystems[0]->_particleSystem->main.maxParticles = getModConfig().numSparks.GetValue();

        // Most of the EmissionModule is missing from bs-cordl headers. Fetch the functions with an internal call instead
        // Function to retrieve information about a ParticleSystem's Burst at a specific index
        auto GetBurst = il2cpp_utils::resolve_icall<void, ParticleSystem::EmissionModule*, int, ParticleSystemBurst*>("UnityEngine.ParticleSystem/EmissionModule::GetBurst_Injected");
        // Function to set the Burst used by a ParticleSystem at a specific index
        auto SetBurst = il2cpp_utils::resolve_icall<void, ParticleSystem::EmissionModule*, int, ParticleSystemBurst*>("UnityEngine.ParticleSystem/EmissionModule::SetBurst_Injected");

        // Create a copy of the EmissionModule because the icall wants the address of an object that can't be deleted
        ParticleSystem::EmissionModule emission = fireworkItemController->_particleSystems[0]->_particleSystem->emission;

        // Create an object to hold all the information gathered about the ParticleSystem's single burst of sparks
        ParticleSystemBurst returnedBurst;
        // Retrieve information from the ParticleSystem's Burst of sparks and store it in the returnedBurst object
        GetBurst(&emission, 0, &returnedBurst);
        // Set the number of particles in the Burst. The MinMaxCurve is set to constant mode which means it looks to _ConstantMax for a value
        returnedBurst.count.m_ConstantMax = getModConfig().numSparks.GetValue();
        // Put the modified Burst information back into the EmissionModule
        SetBurst(&emission, 0, &returnedBurst);
        // The original ParticleSystem's EmissionModule does not need to be updated because the EmissionModule has a pointer to the ParticleSystem. 
        // The property's setter is also undefined so it doesn't work anyway.
        // Actually, this is completely intended behavior described here: https://docs.unity3d.com/ScriptReference/ParticleSystem.html
    }

}