#include "main.hpp"

#include "fireworkManager.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/ExternalComponents.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"

using namespace UnityEngine;

namespace TooManyFireworks {

    GameObject* randomCube = nullptr;
    int currentMaterial = 0;
    HMUI::CurvedTextMeshPro* materialNameText = nullptr;

    void UpdateMaterial() {
        // Get list of all materials
        ArrayW<Material*> materials = Resources::FindObjectsOfTypeAll<Material*>();

        // Make sure currentMaterial is in bounds
        if(currentMaterial < 0) currentMaterial = 0;
        if(currentMaterial >= materials.size()) currentMaterial = materials.size() - 1;

        // Print out all material names and highlight the one that's being shown
        // std::stringstream ss;
        // for(int i = 0; i < currentMaterial; i++) ss << (std::string)materials[i]->name << " ";
        // ss << "_____> " << (std::string)materials[currentMaterial]->name << " <_____ ";
        // for(int i = currentMaterial + 1; i < materials.size(); i++) ss << (std::string)materials[i]->name << " ";
        // PaperLogger.info("{}", ss.str());
        
        // Show what material is being viewed
        materialNameText->set_text(materials[currentMaterial]->name);

        // Set the material
        randomCube->GetComponent<MeshRenderer*>()->material = materials[currentMaterial];
    }

    BSML::ModalView* CreateSpawnRangeModal(GameObject* container) {
        BSML::ModalView* spawnRangeModal = BSML::Lite::CreateModal(container, Vector2(90.0f, 52.0f), nullptr);
        GameObject* spawnRangeModalContainer = BSML::Lite::CreateScrollableModalContainer(spawnRangeModal);
        // The container is slightly off center for some reason so move it to look a bit more centered
        spawnRangeModalContainer->GetComponent<BSML::ExternalComponents*>()->Get<RectTransform*>()->set_anchoredPosition(Vector2(3.0f, 0.0f));

        BSML::Lite::CreateIncrementSetting(spawnRangeModalContainer, "Position X", 0, 1.0f, getModConfig().spawnRangeCenter.GetValue().x, [](float value){Vector3 position = getModConfig().spawnRangeCenter.GetValue(); position.x = value; SetSaveSpawnRangeCenter(position);});
        BSML::Lite::CreateIncrementSetting(spawnRangeModalContainer, "Position Y", 0, 1.0f, getModConfig().spawnRangeCenter.GetValue().y, [](float value){Vector3 position = getModConfig().spawnRangeCenter.GetValue(); position.y = value; SetSaveSpawnRangeCenter(position);});
        BSML::Lite::CreateIncrementSetting(spawnRangeModalContainer, "Position Z", 0, 1.0f, getModConfig().spawnRangeCenter.GetValue().z, [](float value){Vector3 position = getModConfig().spawnRangeCenter.GetValue(); position.z = value; SetSaveSpawnRangeCenter(position);});

        BSML::Lite::CreateIncrementSetting(spawnRangeModalContainer, "Scale X", 0, 1.0f, getModConfig().spawnRangeSize.GetValue().x, [](float value){Vector3 size = getModConfig().spawnRangeSize.GetValue(); size.x = value; SetSaveSpawnRangeSize(size);});
        BSML::Lite::CreateIncrementSetting(spawnRangeModalContainer, "Scale Y", 0, 1.0f, getModConfig().spawnRangeSize.GetValue().y, [](float value){Vector3 size = getModConfig().spawnRangeSize.GetValue(); size.y = value; SetSaveSpawnRangeSize(size);});
        BSML::Lite::CreateIncrementSetting(spawnRangeModalContainer, "Scale Z", 0, 1.0f, getModConfig().spawnRangeSize.GetValue().z, [](float value){Vector3 size = getModConfig().spawnRangeSize.GetValue(); size.z = value; SetSaveSpawnRangeSize(size);});

        randomCube = GameObject::CreatePrimitive(PrimitiveType::Cube);
        randomCube->transform->localScale = Vector3(0.5f, 0.5f, 0.5f);
        randomCube->transform->position = Vector3(-1.0f, 1.0f, 1.0f);

        return spawnRangeModal;
    }

    void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
        // Only set up the menu when first clicked
        if(!firstActivation) return;

        // Create modals

        // Create container to house all UI elements
        GameObject* modMenuContainer = BSML::Lite::CreateScrollableSettingsContainer(self->gameObject);
        BSML::ModalView* spawnRangeModal = CreateSpawnRangeModal(modMenuContainer);

        // Create main settings
        BSML::SliderSetting* minFrequencySlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Minimum frequency", 1.0f, getModConfig().minFrequency.GetValue(), 1.0f, 100.0f, [](float value){SetSaveMinFrequency(value);});
        BSML::SliderSetting* maxFrequencySlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Maximum frequency", 1.0f, getModConfig().maxFrequency.GetValue(), 1.0f, 100.0f, [](float value){SetSaveMaxFrequency(value);});
        BSML::ToggleSetting* rainbowToggle = BSML::Lite::CreateToggle(modMenuContainer, "Rainbow", getModConfig().rainbow.GetValue(), [](bool value) {SetSaveRainbow(value);});
        BSML::ColorSetting* colorColorPicker = BSML::Lite::CreateColorPicker(modMenuContainer, "Color", getModConfig().color.GetValue(), nullptr, nullptr, [](Color value){SetSaveColor(value);}); // TODO On cancel
        BSML::SliderSetting* brightnessSlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Brightness", 0.1f, getModConfig().brightness.GetValue(), 0.0f, 50.0f, [](float value){SetSaveBrightness(value);});
        BSML::SliderSetting* minSize = BSML::Lite::CreateSliderSetting(modMenuContainer, "Minimum size", 0.01f, getModConfig().minSize.GetValue(), 0.0f, 4.0f, [](float value){SetSaveMinSize(value);});
        BSML::SliderSetting* maxSize = BSML::Lite::CreateSliderSetting(modMenuContainer, "Maximum size", 0.01f, getModConfig().maxSize.GetValue(), 0.0f, 4.0f, [](float value){SetSaveMaxSize(value);});
        BSML::SliderSetting* numSparksSlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Number of sparks", 10.0f, getModConfig().numSparks.GetValue(), 0.0f, 10000.0f, [](float value){SetSaveNumSparks((int)value);});
        BSML::SliderSetting* gravitySlider = BSML::Lite::CreateSliderSetting(modMenuContainer, "Gravity", 0.1f, getModConfig().gravity.GetValue(), -5.0f, 5.0f, [](float value){SetSaveGravity(value);});
        UI::Button* spawnRangeButton = BSML::Lite::CreateUIButton(modMenuContainer, "Set Range", [spawnRangeModal](){spawnRangeModal->Show();});
        BSML::ToggleSetting* enableOnLevelClearToggle = BSML::Lite::CreateToggle(modMenuContainer, "Enable on level clear", getModConfig().enableOnLevelClear.GetValue(), [](bool value) {getModConfig().enableOnLevelClear.SetValue(value);});

        // DEBUG Start and stop buttons
        UnityEngine::UI::HorizontalLayoutGroup* enableRow = BSML::Lite::CreateHorizontalLayoutGroup(modMenuContainer);
        BSML::Lite::CreateUIButton(enableRow, "Start", [](){SetFireworksEnabled(true);});
        BSML::Lite::CreateUIButton(enableRow, "Stop", [](){SetFireworksEnabled(false);});

        // DEBUG Material buttons
        materialNameText = BSML::Lite::CreateText(modMenuContainer, "Material name", Vector2(0.0f, 0.0f), Vector2(10.0f, 3.0f));
        UnityEngine::UI::HorizontalLayoutGroup* materialsRow = BSML::Lite::CreateHorizontalLayoutGroup(modMenuContainer);
        BSML::Lite::CreateUIButton(materialsRow, "Back", [](){currentMaterial--; UpdateMaterial();});
        BSML::Lite::CreateUIButton(materialsRow, "Next", [](){currentMaterial++; UpdateMaterial();});

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

    void InitModConfigMenu() {
        BSML::Register::RegisterSettingsMenu("Too Many Fireworks", DidActivate, false);
    }

}