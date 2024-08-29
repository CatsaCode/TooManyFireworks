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
        BSML::SliderSetting* minimumFrequencySlider = BSML::Lite::CreateSliderSetting(mainContainer->transform, "Minimum frequency", 1.0f, getModConfig().minFrequency.GetValue(), 1.0f, 30.0f, [](float value){SetSaveMinFrequency(value);});
        BSML::SliderSetting* maximumFrequencySlider = BSML::Lite::CreateSliderSetting(mainContainer->transform, "Maximum frequency", 1.0f, getModConfig().maxFrequency.GetValue(), 1.0f, 30.0f, [](float value){SetSaveMaxFrequency(value);});
        BSML::ToggleSetting* rainbowToggle = BSML::Lite::CreateToggle(mainContainer->transform, "Rainbow", getModConfig().rainbow.GetValue(), [](bool value) {SetSaveRainbow(value);});
        BSML::ToggleSetting* enableOnLevelClearToggle = BSML::Lite::CreateToggle(mainContainer->transform, "Enable on level clear", getModConfig().enableOnLevelClear.GetValue(), [](bool value) {getModConfig().enableOnLevelClear.SetValue(value);});

        // TODO On cancel
        BSML::Lite::CreateColorPicker(mainContainer, "Color", getModConfig().color.GetValue(), nullptr, nullptr, [](Color value){SetSaveColor(value);});

        // DEBUG Start and stop buttons
        UnityEngine::UI::HorizontalLayoutGroup* enableRow = BSML::Lite::CreateHorizontalLayoutGroup(mainContainer->transform);
        BSML::Lite::CreateUIButton(enableRow->transform, "Start", [](){SetFireworksEnabled(true);});
        BSML::Lite::CreateUIButton(enableRow->transform, "Stop", [](){SetFireworksEnabled(false);});

        // Add more detailed descriptions
        BSML::Lite::AddHoverHint(minimumFrequencySlider->transform, "Minimum number of fireworks per second (Default 1)");
        BSML::Lite::AddHoverHint(maximumFrequencySlider->transform, "Maximum number of fireworks per second (Default 5)");
        BSML::Lite::AddHoverHint(rainbowToggle->transform, "Whether or not to color fireworks with a random hue (Default false)");
        BSML::Lite::AddHoverHint(enableOnLevelClearToggle->transform, "Show fireworks regardless of high score (Default false)");
    }

    void InitModConfigMenu() {
        BSML::Register::RegisterSettingsMenu("Too Many Fireworks", DidActivate, false);
    }

}