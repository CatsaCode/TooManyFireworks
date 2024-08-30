#include "main.hpp"

#include "fireworkManager.hpp"

#include "bsml/shared/BSML.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"

using namespace UnityEngine;

namespace TooManyFireworks {

    void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        // Only set up the menu when first clicked
        if(!firstActivation) return;

        // Create container to house all UI elements
        UnityEngine::GameObject* mainContainer = BSML::Lite::CreateScrollableSettingsContainer(self->transform);

        // Create main settings
        BSML::SliderSetting* minimumFrequencySlider = BSML::Lite::CreateSliderSetting(mainContainer, "Minimum frequency", 1.0f, getModConfig().minFrequency.GetValue(), 1.0f, 100.0f, [](float value){SetSaveMinFrequency(value);});
        BSML::SliderSetting* maximumFrequencySlider = BSML::Lite::CreateSliderSetting(mainContainer, "Maximum frequency", 1.0f, getModConfig().maxFrequency.GetValue(), 1.0f, 100.0f, [](float value){SetSaveMaxFrequency(value);});
        BSML::ToggleSetting* rainbowToggle = BSML::Lite::CreateToggle(mainContainer, "Rainbow", getModConfig().rainbow.GetValue(), [](bool value) {SetSaveRainbow(value);});
        BSML::ColorSetting* colorColorPicker = BSML::Lite::CreateColorPicker(mainContainer, "Color", getModConfig().color.GetValue(), nullptr, nullptr, [](Color value){SetSaveColor(value);}); // TODO On cancel
        BSML::SliderSetting* brightnessSlider = BSML::Lite::CreateSliderSetting(mainContainer, "Brightness", 0.1f, getModConfig().brightness.GetValue(), 0.0f, 50.0f, [](float value){SetSaveBrightness(value);});
        BSML::SliderSetting* gravitySlider = BSML::Lite::CreateSliderSetting(mainContainer, "Gravity", 0.1f, getModConfig().gravity.GetValue(), -5.0f, 5.0f, [](float value){SetSaveGravity(value);});
        BSML::ToggleSetting* enableOnLevelClearToggle = BSML::Lite::CreateToggle(mainContainer, "Enable on level clear", getModConfig().enableOnLevelClear.GetValue(), [](bool value) {getModConfig().enableOnLevelClear.SetValue(value);});

        // DEBUG Start and stop buttons
        UnityEngine::UI::HorizontalLayoutGroup* enableRow = BSML::Lite::CreateHorizontalLayoutGroup(mainContainer);
        BSML::Lite::CreateUIButton(enableRow, "Start", [](){SetFireworksEnabled(true);});
        BSML::Lite::CreateUIButton(enableRow, "Stop", [](){SetFireworksEnabled(false);});

        // Add more detailed descriptions
        BSML::Lite::AddHoverHint(minimumFrequencySlider, "Minimum number of fireworks per second (Default 1)");
        BSML::Lite::AddHoverHint(maximumFrequencySlider, "Maximum number of fireworks per second (Default 5)");
        BSML::Lite::AddHoverHint(rainbowToggle, "Whether or not to color fireworks with a random hue (Default false)");
        BSML::Lite::AddHoverHint(colorColorPicker, "Static color of the fireworks (Default 0, 192, 255)");
        BSML::Lite::AddHoverHint(brightnessSlider, "Brightness in the center of the fireworks (Default 1)");
        BSML::Lite::AddHoverHint(gravitySlider, "Gravity multiplier for the firework sparks (Default 0)");
        BSML::Lite::AddHoverHint(enableOnLevelClearToggle, "Show fireworks regardless of high score (Default false)");
    }

    void InitModConfigMenu() {
        BSML::Register::RegisterSettingsMenu("Too Many Fireworks", DidActivate, false);
    }

}