#include "main.hpp"

#include "fireworkManager.hpp"
#include "effects.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/ExternalComponents.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/RectTransform.hpp"

#include "HMUI/CurvedTextMeshPro.hpp"
#include <functional>

using namespace UnityEngine;

namespace TooManyFireworks {

    void CreateExtraIncrementSetting(GameObject* parent, std::string label, ConfigUtils::ConfigValue<float>& configVariable, std::function<void(float)> onValueChange = nullptr) {
        UI::HorizontalLayoutGroup* infoRow = BSML::Lite::CreateHorizontalLayoutGroup(parent);
        HMUI::CurvedTextMeshPro* labelText = BSML::Lite::CreateText(infoRow, label, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
        HMUI::CurvedTextMeshPro* valueText = BSML::Lite::CreateText(infoRow, fmt::format("{:.2f}", configVariable.GetValue()), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        // Function for each button to update the configVariable, the valueText, and also call onValueChange
        std::function<void(bool, float)> UpdateFunc = [&configVariable, valueText, onValueChange](bool reset, float increment){
            if(reset) configVariable.SetValue(configVariable.GetDefaultValue());
            else configVariable.SetValue(configVariable.GetValue() + increment);
            valueText->set_text(fmt::format("{:.2f}", configVariable.GetValue()));
            if(onValueChange) onValueChange(configVariable.GetValue());
        };

        UI::Button* resetButton = BSML::Lite::CreateUIButton(infoRow, "Reset", std::bind(UpdateFunc, true, 0));
        BSML::Lite::AddHoverHint(resetButton, fmt::format("Default {}", configVariable.GetDefaultValue()));

        UI::HorizontalLayoutGroup* extraIncrementsRow = BSML::Lite::CreateHorizontalLayoutGroup(parent);
        BSML::Lite::CreateUIButton(extraIncrementsRow, "-10",   Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, -10.0f));
        BSML::Lite::CreateUIButton(extraIncrementsRow, "-1",    Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, -1.0f));
        BSML::Lite::CreateUIButton(extraIncrementsRow, "-0.1",  Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, -0.1f));
        BSML::Lite::CreateUIButton(extraIncrementsRow, "-0.01", Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, -0.01f));
        BSML::Lite::CreateUIButton(extraIncrementsRow, "0.01",  Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, 0.01f));
        BSML::Lite::CreateUIButton(extraIncrementsRow, "0.1",   Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, 0.1f));
        BSML::Lite::CreateUIButton(extraIncrementsRow, "1",     Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, 1.0f));
        BSML::Lite::CreateUIButton(extraIncrementsRow, "10",    Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f), std::bind(UpdateFunc, false, 10.0f));
    }

    void CreateExtraIncrementSetting(GameObject* parent, std::string label, ConfigUtils::ConfigValue<Vector3>& configVariable, std::function<void(Vector3)> onValueChange = nullptr) {
        UI::HorizontalLayoutGroup* infoRow = BSML::Lite::CreateHorizontalLayoutGroup(parent);
        HMUI::CurvedTextMeshPro* labelText = BSML::Lite::CreateText(infoRow, label, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
        HMUI::CurvedTextMeshPro* valueText = BSML::Lite::CreateText(infoRow, fmt::format("({:.2f}, {:.2f}, {:.2f})", configVariable.GetValue().x, configVariable.GetValue().y, configVariable.GetValue().z), Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        // Function for each button to update the configVariable, the valueText, and also call onValueChange
        std::function<void(bool, Vector3)> UpdateFunc = [&configVariable, valueText, onValueChange](bool reset, Vector3 increment){
            if(reset) configVariable.SetValue(configVariable.GetDefaultValue());
            else configVariable.SetValue(Vector3::op_Addition(configVariable.GetValue(), increment));
            valueText->set_text(fmt::format("({:.2f}, {:.2f}, {:.2f})", configVariable.GetValue().x, configVariable.GetValue().y, configVariable.GetValue().z));
            if(onValueChange) onValueChange(configVariable.GetValue());
        };

        UI::Button* resetButton = BSML::Lite::CreateUIButton(infoRow, "Reset", std::bind(UpdateFunc, true, Vector3(0.0f, 0.0f, 0.0f)));
        BSML::Lite::AddHoverHint(resetButton, fmt::format("Default ({:.2f}, {:.2f}, {:.2f})", configVariable.GetValue().x, configVariable.GetValue().y, configVariable.GetValue().z));

        UI::HorizontalLayoutGroup* extraIncrementsRowX = BSML::Lite::CreateHorizontalLayoutGroup(parent);
        BSML::Lite::CreateText(extraIncrementsRowX, "X", Vector2(0, 0), Vector2(1, 1));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "-10",   Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(-10.0f, 0.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "-1",    Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(-1.0f, 0.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "-0.1",  Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(-0.1f, 0.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "-0.01", Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(-0.01f, 0.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "0.01",  Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.01f, 0.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "0.1",   Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.1f, 0.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "1",     Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(1.0f, 0.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowX, "10",    Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(10.0f, 0.0f, 0.0f)));

        UI::HorizontalLayoutGroup* extraIncrementsRowY = BSML::Lite::CreateHorizontalLayoutGroup(parent);
        BSML::Lite::CreateText(extraIncrementsRowY, "Y", Vector2(0, 0), Vector2(1, 1));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "-10",   Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, -10.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "-1",    Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, -1.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "-0.1",  Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, -0.1f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "-0.01", Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, -0.01f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "0.01",  Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.01f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "0.1",   Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.1f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "1",     Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 1.0f, 0.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowY, "10",    Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 10.0f, 0.0f)));

        UI::HorizontalLayoutGroup* extraIncrementsRowZ = BSML::Lite::CreateHorizontalLayoutGroup(parent);
        BSML::Lite::CreateText(extraIncrementsRowZ, "Z", Vector2(0, 0), Vector2(1, 1));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "-10",   Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, -10.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "-1",    Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, -1.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "-0.1",  Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, -0.1f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "-0.01", Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, -0.01f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "0.01",  Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, 0.01f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "0.1",   Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, 0.1f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "1",     Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, 1.0f)));
        BSML::Lite::CreateUIButton(extraIncrementsRowZ, "10",    Vector2(0.0f, 0.0f), Vector2(1.0f, 0.0f), std::bind(UpdateFunc, false, Vector3(0.0f, 0.0f, 10.0f)));
    }

    BSML::ModalView* CreateSpawnRangeModal(GameObject* parent) {
        // Popup window
        BSML::ModalView* spawnRangeModal = BSML::Lite::CreateModal(parent, Vector2(0.0f, 5.0f), Vector2(100.0f, 80.0f), nullptr);
        // Place each setting one on top of the other
        GameObject* spawnRangeModalContainer = BSML::Lite::CreateScrollableModalContainer(spawnRangeModal);
        // The container is slightly off center for some reason so move it to look a bit more centered
        spawnRangeModalContainer->GetComponent<BSML::ExternalComponents*>()->Get<RectTransform*>()->set_anchoredPosition(Vector2(4.0f, 0.0f));

        // Vector3 spawnRangeCenter panel
        CreateExtraIncrementSetting(spawnRangeModalContainer, "Center", getModConfig().spawnRangeCenter, [](Vector3 value){UpdateSpawnRange();}); // TODO Change the name of this function. Not needing to set the config value like everything else looks weird. Look into config-utils shortcut things
        // Spacer
        BSML::Lite::CreateText(spawnRangeModalContainer, "", Vector2(0.0f, 0.0f), Vector2(1.0f, 5.0f));
        // Vector3 spawnRangeSize panel
        CreateExtraIncrementSetting(spawnRangeModalContainer, "Size", getModConfig().spawnRangeSize, [](Vector3 value){UpdateSpawnRange();});

        return spawnRangeModal;
    }

    void ModConfigMenuDidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        // Only set up the menu when first clicked
        if(!firstActivation) return;

        // Create modals
        BSML::ModalView* spawnRangeModal = CreateSpawnRangeModal(self->gameObject);

        // Create container to house all UI elements
        GameObject* modMenuContainer = BSML::Lite::CreateScrollableSettingsContainer(self->gameObject);

        // Create main settings
        BSML::SliderSetting* minFrequencySlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Minimum frequency", 1.0f, getModConfig().minFrequency.GetValue(), 1.0f, 100.0f, [](float value){getModConfig().minFrequency.SetValue(value); UpdateFrequency();});
        BSML::SliderSetting* maxFrequencySlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Maximum frequency", 1.0f, getModConfig().maxFrequency.GetValue(), 1.0f, 100.0f, [](float value){getModConfig().maxFrequency.SetValue(value); UpdateFrequency();});
        BSML::ToggleSetting* rainbowToggle = BSML::Lite::CreateToggle(modMenuContainer, "Rainbow", getModConfig().rainbow.GetValue(), [](bool value) {getModConfig().rainbow.SetValue(value); ForceUpdateEachFirework(UpdateColor);});
        BSML::ColorSetting* colorColorPicker = BSML::Lite::CreateColorPicker(modMenuContainer, "Color", getModConfig().color.GetValue(), nullptr, nullptr, [](Color value){getModConfig().color.SetValue(value); ForceUpdateEachFirework(UpdateColor);}); // TODO On cancel
        BSML::SliderSetting* brightnessSlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Brightness", 0.1f, getModConfig().brightness.GetValue(), 0.0f, 50.0f, [](float value){getModConfig().brightness.SetValue(value); ForceUpdateEachFirework(UpdateBrightness);});
        BSML::SliderSetting* minSize = BSML::Lite::CreateSliderSetting(modMenuContainer, "Minimum size", 0.01f, getModConfig().minSize.GetValue(), 0.0f, 4.0f, [](float value){getModConfig().minSize.SetValue(value); ForceUpdateEachFirework(UpdateSize);});
        BSML::SliderSetting* maxSize = BSML::Lite::CreateSliderSetting(modMenuContainer, "Maximum size", 0.01f, getModConfig().maxSize.GetValue(), 0.0f, 4.0f, [](float value){getModConfig().maxSize.SetValue(value); ForceUpdateEachFirework(UpdateSize);});
        BSML::SliderSetting* numSparksSlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Number of sparks", 10.0f, getModConfig().numSparks.GetValue(), 0.0f, 10000.0f, [](float value){getModConfig().numSparks.SetValue(value); ForceUpdateEachFirework(UpdateNumSparks);});
        BSML::SliderSetting* gravitySlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Gravity", 0.1f, getModConfig().gravity.GetValue(), -5.0f, 5.0f, [](float value){getModConfig().gravity.SetValue(value); ForceUpdateEachFirework(UpdateGravity);});
        UI::Button* spawnRangeButton = BSML::Lite::CreateUIButton(modMenuContainer, "Set Range", [spawnRangeModal](){spawnRangeModal->Show();});
        BSML::ToggleSetting* enableOnLevelClearToggle = BSML::Lite::CreateToggle(modMenuContainer, "Enable on level clear", getModConfig().enableOnLevelClear.GetValue(), [](bool value) {getModConfig().enableOnLevelClear.SetValue(value);});

        // DEBUG Start and stop buttons
        UnityEngine::UI::HorizontalLayoutGroup* enableRow = BSML::Lite::CreateHorizontalLayoutGroup(modMenuContainer);
        BSML::Lite::CreateUIButton(enableRow, "Start", [](){SetFireworksEnabled(true);});
        BSML::Lite::CreateUIButton(enableRow, "Stop", [](){SetFireworksEnabled(false);});

        // Add more detailed descriptions
        BSML::Lite::AddHoverHint(minFrequencySlider, "Minimum number of fireworks per second (Default 1)");
        BSML::Lite::AddHoverHint(maxFrequencySlider, "Maximum number of fireworks per second (Default 5)");
        BSML::Lite::AddHoverHint(rainbowToggle, "Whether or not to color fireworks with a random hue (Default false)");
        BSML::Lite::AddHoverHint(colorColorPicker, "Static color of the fireworks (Default 0, 192, 255)");
        BSML::Lite::AddHoverHint(brightnessSlider, "Brightness in the center of the fireworks (Default 1)");
        BSML::Lite::AddHoverHint(minSize, "Minimum size of the entire firework (Default 0.69)");
        BSML::Lite::AddHoverHint(maxSize, "Maximum size of the entire firework (Default 1)");
        BSML::Lite::AddHoverHint(numSparksSlider, "Number of sparks in each firework (Default 70)");
        BSML::Lite::AddHoverHint(gravitySlider, "Gravity multiplier for the firework sparks (Default 0)");
        BSML::Lite::AddHoverHint(spawnRangeButton, "Move and resize the volume where fireworks can spawn");
        BSML::Lite::AddHoverHint(enableOnLevelClearToggle, "Show fireworks regardless of high score (Default false)");
    }

}