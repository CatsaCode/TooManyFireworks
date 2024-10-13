#include "main.hpp"

#include "GlobalNamespace/FireworkItemController.hpp"

#include "UnityEngine/ParticleSystem.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Reconstructed enum for what particles collide with
    enum ReconstructedCollisionType {
        Planes,
        World
    };

    // Set whether or not spark collisions are enabled
    void UpdateCollision(FireworkItemController* fireworkItemController) {
        auto SetEnabled = il2cpp_utils::resolve_icall<void, ParticleSystem::CollisionModule*, bool>("UnityEngine.ParticleSystem/CollisionModule::set_enabled_Injected");
        auto SetType = il2cpp_utils::resolve_icall<void, ParticleSystem::CollisionModule*, ReconstructedCollisionType>("UnityEngine.ParticleSystem/CollisionModule::set_type_Injected");

        // Get collision module
        ParticleSystem::CollisionModule collision = fireworkItemController->_particleSystems[0]->_particleSystem->collision;
        // Enable collision module
        SetEnabled(&collision, getModConfig().collision.GetValue());
        // Set particle collisions to use world colliders
        SetType(&collision, ReconstructedCollisionType::World);
    }

}