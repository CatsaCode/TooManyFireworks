#include "main.hpp"

#include "hookInstallers.hpp"

#include "scotland2/shared/modloader.h"

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

    PaperLogger.info("Installing hooks...");

    InstallFireworkFrequencyHook();
    InstallFireworkColorHook();
    InstallFireworkSpawnVolumeHook();

    InstallFireworksOnLevelClearHook();

    PaperLogger.info("Installed all hooks!");
}