#include "main.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;

namespace TooManyFireworks {

    // Create a panel of buttons that can increment a float config value by -10, -1, -0.1, -0.01, 0.01, 0.1, 1, and 10
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

    // Create a panel of buttons that can increment each axis of a a Vector3 config value by -10, -1, -0.1, -0.01, 0.01, 0.1, 1, and 10
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

    // Create two intertwined sliders that will adjust two float config values representing the minimum and maximum of a random result
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

}