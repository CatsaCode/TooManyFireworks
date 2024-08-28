#include "bsml/shared/BSML.hpp"

#include "UnityEngine/GameObject.hpp"

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if(!firstActivation) return;

    UnityEngine::GameObject* container = BSML::Lite::CreateScrollableSettingsContainer(self->get_transform());
    BSML::Lite::CreateText(container->get_transform(), "Hewwo world! UwU");
}