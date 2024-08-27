#include "main.hpp"

#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"

#include "GlobalNamespace/FireworksController.hpp"

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
MAKE_HOOK_MATCH(MoreFireworks, &GlobalNamespace::FireworksController::OnEnable, void, GlobalNamespace::FireworksController* self) {
    // Reduce time between fireworks
    self->____minSpawnInterval = 0.05;
    self->____maxSpawnInterval = 0.05;

    // Run original function
    MoreFireworks(self);
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
    INSTALL_HOOK(PaperLogger,  MoreFireworks)

    PaperLogger.info("Installed all hooks!");
}