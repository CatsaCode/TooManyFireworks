#include "main.hpp"

#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"

#include "GlobalNamespace/FireworksController.hpp"
#include "GlobalNamespace/FireworkItemController.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/SongPreviewPlayer.hpp"
#include "UnityEngine/AudioClip.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"

#include "scotland2/shared/modloader.h"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};
// Stores the ID and version of our mod, and is sent to
// the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
// other config tools such as config-utils don't use this config, so it can be
// removed if those are in use
Configuration &getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Create a hook struct named LevelUIHook
// targeting the method "StandardLevelDetailViewController::DidActivate", which takes the following arguments:
// bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling
// and returns void.

// General format: MAKE_HOOK_MATCH(hook name, hooked method, method return type, method class pointer, arguments...) {
//     HookName(self, arguments...);
//     your code here
// }


MAKE_HOOK_MATCH(LevelUIHook, &GlobalNamespace::StandardLevelDetailViewController::ShowContent, void, GlobalNamespace::StandardLevelDetailViewController* self, ::GlobalNamespace::__StandardLevelDetailViewController__ContentType contentType, ::StringW errorText) {
    // Run the original method before our code.
    // Note that you can run the original method after our code or even in the middle
    // if you want to change arguments or do something before it runs.
    LevelUIHook(self, contentType, errorText);

    // Get the actionButton text object by accessing the actionButton field and some simple Unity methods.
    // Note that auto can be used instead of declaring the full type in many cases.
    GlobalNamespace::StandardLevelDetailView* standardLevelDetailView = self->_standardLevelDetailView;
    UnityEngine::UI::Button* actionButton = standardLevelDetailView->actionButton;
    UnityEngine::GameObject* gameObject = actionButton->get_gameObject();
    HMUI::CurvedTextMeshPro* actionButtonText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro*>();

    // Set the text
    actionButtonText->set_text("YEET!");
}

// Hook to reduce the time delay between fireworks
MAKE_HOOK_MATCH(MoreFireworksHook, &GlobalNamespace::FireworksController::OnEnable, void, GlobalNamespace::FireworksController* self) {
    // Reduce time between fireworks
    self->_minSpawnInterval = 0.05f;
    self->_maxSpawnInterval = 0.05f;

    // Set spawn range
    self->_spawnSize = UnityEngine::Vector3(1, 1, 1);
    self->transform->position = UnityEngine::Vector3(0, 0, 0);

    // Run original function
    MoreFireworksHook(self);
}

// Hook to enable random color fireworks
MAKE_HOOK_MATCH(FireworkSettingsHook, &GlobalNamespace::FireworkItemController::Awake, void, GlobalNamespace::FireworkItemController* self) {
    // Run original function
    FireworkSettingsHook(self);

    // // Set firework to be red
    // self->_lightsColor.r = 1.0f;
    // self->_lightsColor.g = 0.0f;
    // self->_lightsColor.b = 0.0f;

    // Set the firework to be a randomly generated color
    float h = (rand() % 256) / 256.0f;
    float s = 1.0f;
    float v = 1.0f;
    self->_lightsColor = UnityEngine::Color::HSVToRGB(h, s, v);
}

// Hook to enable fireworks even without a high score
MAKE_HOOK_MATCH(
    FireworksStartHook,
    &GlobalNamespace::ResultsViewController::DidActivate,
    void,
    GlobalNamespace::ResultsViewController* self,
    bool firstActivation, 
    bool addedToHierarchy, 
    bool screenSystemEnabling
) {
    // Run original function
    FireworksStartHook(self, firstActivation, addedToHierarchy, screenSystemEnabling);

    // Check that is in the original function before starting fireworks
    if(!addedToHierarchy) return;

    // Don't play if level wasn't cleared
    if(self->_levelCompletionResults->levelEndStateType != GlobalNamespace::LevelCompletionResults::LevelEndStateType::Cleared) return;
    // Don't play if the original function already started playing it
    if(self->_newHighScore) return;

    // Enable fireworks manually. Can't figure out coroutines like the original function
    self->_fireworksController->enabled = true;
    // Call the audio function in the original function
	self->_songPreviewPlayer->CrossfadeTo(self->_levelClearedAudioClip, -4, 0, self->_levelClearedAudioClip->length, nullptr);
}



// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    getConfig().Load();

    // File logging
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);

    PaperLogger.info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    PaperLogger.info("Installing hooks...");

    INSTALL_HOOK(PaperLogger, LevelUIHook);
    INSTALL_HOOK(PaperLogger, MoreFireworksHook);
    INSTALL_HOOK(PaperLogger, FireworkSettingsHook);
    INSTALL_HOOK(PaperLogger, FireworksStartHook);

    PaperLogger.info("Installed all hooks!");
}