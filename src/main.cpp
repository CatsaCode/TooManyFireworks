#include "main.hpp"

#include "scotland2/shared/modloader.h"

#include "hookInstallers.hpp"

#include "bsml/shared/BSML.hpp"
#include "UI/modConfigMenu.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};
// Stores the ID and version of our mod, and is sent to
// the modloader upon startup


// Called at the early stages of game loading
MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
    *info = modInfo.to_c();

    getModConfig().Init(modInfo);

    // File logging
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);

    PaperLogger.info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();

    // Initialize BSML UI
    BSML::Init();
    if(getModConfig().mainMenuButton.GetValue()) BSML::Register::RegisterMainMenu("TooManyFireworks", "TooManyFireworks", "Customize the fireworks!", TooManyFireworks::ModConfigMenuDidActivate);
    else BSML::Register::RegisterSettingsMenu("TooManyFireworks", TooManyFireworks::ModConfigMenuDidActivate, false);

    // Install hooks to execute custom code
    PaperLogger.info("Installing hooks...");

    // General effect hooks
    TooManyFireworks::InstallFindMainFireworksControllerHook();
    TooManyFireworks::InstallFireworksControllersPropertiesHook();
    TooManyFireworks::InstallFireworkItemControllerPropertiesHook();

    // Specific effect hooks
    TooManyFireworks::InstallSmoothDisableHook();

    // Force enable hooks
    TooManyFireworks::InstallForceEnableLevelResultsHook();
    TooManyFireworks::InstallMaxScoreTrackerHook();
    TooManyFireworks::InstallForceEnableMainMenuHook();
    TooManyFireworks::InstallForceEnableLevelSelectionHook();
    TooManyFireworks::InstallForceEnableGameplayHook();
    TooManyFireworks::InstallForceEnablePauseMenuHook();

    // Hotfix hooks
    TooManyFireworks::InstallMaxExplosionSoundsHotfixHook();
    TooManyFireworks::InstallDespawnOnSceneTransitionHotfixHook();

    PaperLogger.info("Installed all hooks!");
}