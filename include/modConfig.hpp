#pragma once

#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector3.hpp"

DECLARE_CONFIG(ModConfig) {
    CONFIG_VALUE(minFrequency, float, "minFrequency", 3.0f); // Minimum fireworks per second
    CONFIG_VALUE(maxFrequency, float, "maxFrequency", 10.0f); // Maximum fireworks per second

    CONFIG_VALUE(color, UnityEngine::Color, "color", UnityEngine::Color(0.0f, 192.0f / 255.0f, 1.0f, 1.0f)); // Color of the fireworks
    CONFIG_VALUE(rainbow, bool, "rainbow", true); // Whether or not to color the fireworks with a random hue

    CONFIG_VALUE(brightness, float, "brightness", 1.0f); // Intensity of the firework bloom fog

    CONFIG_VALUE(minSize, float, "minSize", 0.69f); // Minimum size of the whole firework (Implies min start speed of 24 is about 70% size)
    CONFIG_VALUE(maxSize, float, "maxSize", 1.0f); // Maximum size of the whole firework (Implies max start speed of 34.8 is 100% size)

    CONFIG_VALUE(numSparks, int, "numSparks", 500); // Number of sparks in each firework

    CONFIG_VALUE(gravity, float, "gravity", 0.2f); // Gravity scale for the firework sparks

    CONFIG_VALUE(duration, float, "duration", 1.5f); // How many seconds fireworks last for

    CONFIG_VALUE(collision, bool, "collision", true); // Whether or not spark collisions are enabled
    CONFIG_VALUE(dampen, float, "dampen", 0.2f); // How much spark velocity is dampened on collision (Arbitrary default. Technically 0, but a value unused in the base game promotes artistic liberty)
    CONFIG_VALUE(bounce, float, "bounce", 0.2f); // How much spark velocity is reflected on collision (Arbitrary default. Technically 1, but see above)

    CONFIG_VALUE(windStrength, float, "windStrength", 0.0f); // How much a spark's position is affected by noisy air patterns
    CONFIG_VALUE(windTurbulence, float, "windTurbulence", 0.5f); // How detailed the noisy air patterns are

    CONFIG_VALUE(volume, float, "volume", 0.6f); // Volume of the explosion sound effects

    CONFIG_VALUE(spawnRangeCenter, UnityEngine::Vector3, "spawnRangeCenter", UnityEngine::Vector3(0.0f, 11.39f, 12.57f)); // Center of the firework spawn volume
    CONFIG_VALUE(spawnRangeSize, UnityEngine::Vector3, "spawnRangeSize", UnityEngine::Vector3(20.0f, 10.0f, 2.0f)); // Size of the firework spawn volume

    CONFIG_VALUE(enableOnResultsHighscore, bool, "enableOnResultsHighscore", true); // Whether or not to show the fireworks when results show a new highscore
    CONFIG_VALUE(enableOnResultsClear, bool, "enableOnResultsClear", false); // Whether or not to show the fireworks when a level is cleared with no highscore
    CONFIG_VALUE(enableOnResultsFail, bool, "enableOnResultsFail", false); // Whether or not to show the fireworks when a level is failed
    CONFIG_VALUE(resultsRequireFullCombo, bool, "resultsRequireFullCombo", false); // Whether or not a full combo is required to show fireworks at the end of a level
    CONFIG_VALUE(resultsMinimumAccuracy, float, "resultsMinimumAccuracy", 0.0f); // Minimum accuracy required for the fireworks to show at the end of a level
    CONFIG_VALUE(enableInMainMenu, bool, "enableInMainMenu", false); // Whether or not to show fireworks in the main menu
    CONFIG_VALUE(enableInLevelSelection, bool, "enableInLevelSelection", false); // Whether or not to show fireworks in the menu for selecting levels
    CONFIG_VALUE(enableInGameplay, bool, "enableInGameplay", false); // Whether or not to show fireworks while actively slicing notes
    CONFIG_VALUE(enableInPauseMenu, bool, "enableInPauseMenu", false); // Whether or not to show fireworks while the game is paused

    CONFIG_VALUE(smoothDisable, bool, "smoothDisable", true); // Whether or not firework disablement will wait for sparks to disappear

    CONFIG_VALUE(mainMenuButton, bool, "mainMenuButton", false); // Show the mod menu button in the main menu instead of the mod settings menu
};