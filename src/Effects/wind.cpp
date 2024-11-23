#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the wind strength and turbulence properties of a single firework
    void UpdateWind(FireworkItemController* fireworkItemController) {
        auto SetEnabled = il2cpp_utils::resolve_icall<void, ParticleSystem::NoiseModule*, bool>("UnityEngine.ParticleSystem/NoiseModule::set_enabled_Injected");
        auto SetStrength = il2cpp_utils::resolve_icall<void, ParticleSystem::NoiseModule*, ParticleSystem::MinMaxCurve*>("UnityEngine.ParticleSystem/NoiseModule::set_strength_Injected");
        auto SetFrequency = il2cpp_utils::resolve_icall<void, ParticleSystem::NoiseModule*, float>("UnityEngine.ParticleSystem/NoiseModule::set_frequency_Injected");

        // Get noise module
        ParticleSystem::NoiseModule noise = fireworkItemController->_particleSystems[0]->_particleSystem->noise;

        // Create strength info object
        ParticleSystem::MinMaxCurve strength;
        strength.m_Mode = ParticleSystemCurveMode::Constant;
        strength.m_ConstantMax = getModConfig().windStrength.GetValue();

        // Update noise, which is linked to the NoiseModule in the original firework
        SetEnabled(&noise, true);
        SetStrength(&noise, &strength);
        SetFrequency(&noise, getModConfig().windTurbulence.GetValue());
    }

}