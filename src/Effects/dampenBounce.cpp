#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Set the collision dampen and bounce factor of a specific firework
    void UpdateDampenBounce(FireworkItemController* fireworkItemController) {
        auto SetDampen = il2cpp_utils::resolve_icall<void, ParticleSystem::CollisionModule*, ParticleSystem::MinMaxCurve*>("UnityEngine.ParticleSystem/CollisionModule::set_dampen_Injected");
        auto SetBounce = il2cpp_utils::resolve_icall<void, ParticleSystem::CollisionModule*, ParticleSystem::MinMaxCurve*>("UnityEngine.ParticleSystem/CollisionModule::set_bounce_Injected");

        // Get collision module
        ParticleSystem::CollisionModule collision = fireworkItemController->_particleSystems[0]->_particleSystem->collision;

        // Create dampen info object
        ParticleSystem::MinMaxCurve dampen;
        dampen.m_Mode = ParticleSystemCurveMode::Constant; // Maybe not necessary but adds clarity
        dampen.m_ConstantMax = getModConfig().dampen.GetValue();

        // Create bounce info object
        ParticleSystem::MinMaxCurve bounce;
        bounce.m_Mode = ParticleSystemCurveMode::Constant;
        bounce.m_ConstantMax = getModConfig().bounce.GetValue();

        // Set dampen and bounce info to the collision module
        SetDampen(&collision, &dampen);
        SetBounce(&collision, &bounce);
    }

}