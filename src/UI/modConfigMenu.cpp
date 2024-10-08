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
#include "HMUI/ViewController.hpp"

#include "custom-types/shared/delegate.hpp"

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

    std::vector<BSML::SliderSetting*> CreateMinMaxConfigSliderSetting(BSML::Lite::TransformWrapper parent, ConfigUtils::ConfigValue<float>& minConfigVariable, ConfigUtils::ConfigValue<float>& maxConfigVariable, std::string minLabel, std::string maxLabel, float increment, float minValue, float maxValue, std::function<void(float)> onMinValueChange, std::function<void(float)> onMaxValueChange) {
        // Create both sliders without an onChange function
        BSML::SliderSetting* minSlider = BSML::Lite::CreateSliderSetting(parent, minLabel, increment, minConfigVariable.GetValue(), minValue, maxValue, nullptr);
        BSML::SliderSetting* maxSlider = BSML::Lite::CreateSliderSetting(parent, maxLabel, increment, maxConfigVariable.GetValue(), minValue, maxValue, nullptr);
        
        // Set the onChange function on each slider
        minSlider->onChange = [maxSlider, &minConfigVariable, &maxConfigVariable, onMinValueChange](float value){
            // Update config variable
            minConfigVariable.SetValue(value);
            // Update max slider if min slider was set higher
            if(minConfigVariable.GetValue() > maxConfigVariable.GetValue()) {
                // Update config variable
                maxConfigVariable.SetValue(minConfigVariable.GetValue());
                // Update slider's appearance
                maxSlider->set_Value(maxConfigVariable.GetValue());
            }
            // Call the user defined onChange function
            if(onMinValueChange != nullptr) onMinValueChange(value);
        };

        maxSlider->onChange = [minSlider, &minConfigVariable, &maxConfigVariable, onMaxValueChange](float value){
            // Update config variable
            maxConfigVariable.SetValue(value);
            // Update min slider if max slider was set lower
            if(maxConfigVariable.GetValue() < minConfigVariable.GetValue()) {
                // Update config variable
                minConfigVariable.SetValue(maxConfigVariable.GetValue());
                // Update slider's appearance
                minSlider->set_Value(minConfigVariable.GetValue());
            }
            // Call the user defined onChange function
            if(onMaxValueChange != nullptr) onMaxValueChange(value);
        };

        return {minSlider, maxSlider};
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
        // Enable fireworks when menu is opened
        SetFireworksEnabled(true);


        // Only set up the menu when first clicked
        if(!firstActivation) return;

        // Set up fireworks to disable once menu is closed
        std::function<void(bool, bool)> ModConfigMenuDidDeactivate = [](bool removedFromHierarchy, bool screenSystemDisabling){
            SetFireworksEnabled(false);
        };
        self->add_didDeactivateEvent(custom_types::MakeDelegate<HMUI::ViewController::DidDeactivateDelegate*>(ModConfigMenuDidDeactivate));

        // Create modals
        BSML::ModalView* spawnRangeModal = CreateSpawnRangeModal(self->gameObject);

        // Create container to house all UI elements
        GameObject* modMenuContainer = BSML::Lite::CreateScrollableSettingsContainer(self->gameObject);

        // Create main settings
        auto frequencySliders = CreateMinMaxConfigSliderSetting(modMenuContainer, getModConfig().minFrequency, getModConfig().maxFrequency, "Minimum frequency", "Maximum frequency", 1.0f, 1.0f, 100.0f, [](float value){UpdateFrequency();}, [](float value){UpdateFrequency();});
        BSML::ToggleSetting* rainbowToggle = BSML::Lite::CreateToggle(modMenuContainer, "Rainbow", getModConfig().rainbow.GetValue(), [](bool value) {getModConfig().rainbow.SetValue(value); ForceUpdateEachFirework(UpdateColor);});
        BSML::ColorSetting* colorColorPicker = BSML::Lite::CreateColorPicker(modMenuContainer, "Color", getModConfig().color.GetValue(), nullptr, nullptr, [](Color value){getModConfig().color.SetValue(value); ForceUpdateEachFirework(UpdateColor);}); // TODO On cancel
        BSML::SliderSetting* brightnessSlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Brightness", 0.1f, getModConfig().brightness.GetValue(), 0.0f, 50.0f, [](float value){getModConfig().brightness.SetValue(value); ForceUpdateEachFirework(UpdateBrightness);});
        auto sizeSliders = CreateMinMaxConfigSliderSetting(modMenuContainer, getModConfig().minSize, getModConfig().maxSize, "Minimum size", "Maximum size", 0.01f, 0.0f, 4.0f, [](float value){ForceUpdateEachFirework(UpdateSize);}, [](float value){ForceUpdateEachFirework(UpdateSize);});
        BSML::SliderSetting* numSparksSlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Number of sparks", 10.0f, getModConfig().numSparks.GetValue(), 0.0f, 10000.0f, [](float value){getModConfig().numSparks.SetValue(value); ForceUpdateEachFirework(UpdateNumSparks);});
        BSML::SliderSetting* gravitySlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Gravity", 0.1f, getModConfig().gravity.GetValue(), -5.0f, 5.0f, [](float value){getModConfig().gravity.SetValue(value); ForceUpdateEachFirework(UpdateGravity);});
        UI::Button* spawnRangeButton = BSML::Lite::CreateUIButton(modMenuContainer, "Set Range", [spawnRangeModal](){spawnRangeModal->Show();});
        BSML::ToggleSetting* enableOnResultsHighscoreToggle = BSML::Lite::CreateToggle(modMenuContainer, "Enable on highscore", getModConfig().enableOnResultsHighscore.GetValue(), [](bool value) {getModConfig().enableOnResultsHighscore.SetValue(value);});
        BSML::ToggleSetting* enableOnResultsClearToggle = BSML::Lite::CreateToggle(modMenuContainer, "Enable on level clear", getModConfig().enableOnResultsClear.GetValue(), [](bool value) {getModConfig().enableOnResultsClear.SetValue(value);});
        BSML::ToggleSetting* enableOnResultsFailToggle = BSML::Lite::CreateToggle(modMenuContainer, "Enable on level fail", getModConfig().enableOnResultsFail.GetValue(), [](bool value) {getModConfig().enableOnResultsFail.SetValue(value);});

        // Add more detailed descriptions
        BSML::Lite::AddHoverHint(frequencySliders[0], "Minimum number of fireworks per second (Default 1)");
        BSML::Lite::AddHoverHint(frequencySliders[1], "Maximum number of fireworks per second (Default 5)");
        BSML::Lite::AddHoverHint(rainbowToggle, "Whether or not to color fireworks with a random hue (Default false)");
        BSML::Lite::AddHoverHint(colorColorPicker, "Static color of the fireworks (Default 0, 192, 255)");
        BSML::Lite::AddHoverHint(brightnessSlider, "Brightness in the center of the fireworks (Default 1)");
        BSML::Lite::AddHoverHint(sizeSliders[0], "Minimum size of the entire firework (Default 0.69)");
        BSML::Lite::AddHoverHint(sizeSliders[1], "Maximum size of the entire firework (Default 1)");
        BSML::Lite::AddHoverHint(numSparksSlider, "Number of sparks in each firework (Default 70)");
        BSML::Lite::AddHoverHint(gravitySlider, "Gravity multiplier for the firework sparks (Default 0)");
        BSML::Lite::AddHoverHint(spawnRangeButton, "Move and resize the volume where fireworks can spawn");
        BSML::Lite::AddHoverHint(enableOnResultsHighscoreToggle, "Show fireworks on the results screen when a new highscore was achieved (Default true)");
        BSML::Lite::AddHoverHint(enableOnResultsClearToggle, "Show fireworks on the results screen when the level was cleared without a highscore (Default false)");
        BSML::Lite::AddHoverHint(enableOnResultsFailToggle, "Show fireworks on the results screen when the level was failed (Default false)");
    }

}