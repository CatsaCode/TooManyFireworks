#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the duration of a specific firework
    void UpdateDuration(FireworkItemController* fireworkItemController) {
        // Set light duration and object time limit of the FireworkItemController itself
        fireworkItemController->_lightFlashDuration = getModConfig().duration.GetValue();
        if(getModConfig().duration.GetValue() == 0.0f) fireworkItemController->_lightFlashDuration = 0.01f; // Game isn't crashing, but, I'm still pretty sure division by zero errors are being spammed without this line

        // Get functions to update properties in the ParticleSystem
        static auto SetDuration = il2cpp_utils::resolve_icall<void, ParticleSystem::MainModule*, float>("UnityEngine.ParticleSystem/MainModule::set_duration_Injected");
        static auto SetLifetime = il2cpp_utils::resolve_icall<void, ParticleSystem::MainModule*, ParticleSystem::MinMaxCurve*>("UnityEngine.ParticleSystem/MainModule::set_startLifetime_Injected");

        // Get a linked copy of the MainModule
        ParticleSystem::MainModule main = fireworkItemController->_particleSystems[0]->_particleSystem->main;

        // Create startLifetime info object
        ParticleSystem::MinMaxCurve startLifetime;
        startLifetime.m_Mode = ParticleSystemCurveMode::TwoConstants; // Two constants is what gives each spark a slight offset
        startLifetime.m_ConstantMin = getModConfig().duration.GetValue() * (2.0f / 3.0f);
        startLifetime.m_ConstantMax = getModConfig().duration.GetValue();

        // Set duration and lifetime in the MainModule
        SetDuration(&main, getModConfig().duration.GetValue());
        SetLifetime(&main, &startLifetime);
    }

}