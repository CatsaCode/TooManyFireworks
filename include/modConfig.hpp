#pragma once

#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector3.hpp"

DECLARE_CONFIG(ModConfig, 
    CONFIG_VALUE(minFrequency, float, "minFrequency", 1.0f); // Minimum fireworks per second
    CONFIG_VALUE(maxFrequency, float, "maxFrequency", 5.0f); // Maximum fireworks per second

    CONFIG_VALUE(color, UnityEngine::Color, "color", UnityEngine::Color(0.0f, 192.0f / 255.0f, 1.0f, 1.0f)); // Color of the fireworks
    CONFIG_VALUE(rainbow, bool, "rainbow", false); // Whether or not to color the fireworks with a random hue

    CONFIG_VALUE(brightness, float, "brightness", 1.0f); // Intensity of the firework bloom fog

    CONFIG_VALUE(minSize, float, "minSize", 0.69f); // Minimum size of the whole firework (Implies min start speed of 24 is about 70% size)
    CONFIG_VALUE(maxSize, float, "maxSize", 1.0f); // Maximum size of the whole firework (Implies max start speed of 34.8 is 100% size)

    CONFIG_VALUE(numSparks, int, "numSparks", 70); // Number of sparks in each firework

    CONFIG_VALUE(gravity, float, "gravity", 0.0f); // Gravity scale for the firework sparks

    CONFIG_VALUE(collision, bool, "collision", false); // Whether or not spark collisions are enabled

    CONFIG_VALUE(spawnRangeCenter, UnityEngine::Vector3, "spawnRangeCenter", UnityEngine::Vector3(0.0f, 11.39f, 12.57f)); // Center of the firework spawn volume
    CONFIG_VALUE(spawnRangeSize, UnityEngine::Vector3, "spawnRangeSize", UnityEngine::Vector3(20.0f, 10.0f, 2.0f)); // Size of the firework spawn volume

    CONFIG_VALUE(enableOnResultsHighscore, bool, "enableOnResultsHighscore", true); // Whether or not to show the fireworks when results show a new highscore
    CONFIG_VALUE(enableOnResultsClear, bool, "enableOnResultsClear", false); // Whether or not to show the fireworks when a level is cleared with no highscore
    CONFIG_VALUE(enableOnResultsFail, bool, "enableOnResultsFail", false); // Whether or not to show the fireworks when a level is failed
)