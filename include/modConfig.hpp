#pragma once

#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector3.hpp"

DECLARE_CONFIG(ModConfig, 
    CONFIG_VALUE(minFrequency, float, "minFrequency", 1.0f); // Minimum fireworks per second
    CONFIG_VALUE(maxFrequency, float, "maxFrequency", 5.0f); // Maximum fireworks per second

    CONFIG_VALUE(color, UnityEngine::Color, "color", UnityEngine::Color(0.0f, 192.0f / 255.0f, 1.0f, 1.0f)); // Color of the fireworks
    CONFIG_VALUE(rainbow, bool, "rainbow", false); // Whether or not to color the fireworks with a random hue

    CONFIG_VALUE(spawnOrigin, UnityEngine::Vector3, "spawnOrigin", UnityEngine::Vector3(0.0f, 11.39f, 12.57f)); // Center of the spawn volume
    CONFIG_VALUE(spawnSize, UnityEngine::Vector3, "spawnSize", UnityEngine::Vector3(20.0f, 10.0f, 2.0f)); // Size of the spawn volume

    CONFIG_VALUE(enableOnLevelClear, bool, "enableOnLevelClear", false) // Whether or not to show the fireworks on any level clear instead of just high score
)