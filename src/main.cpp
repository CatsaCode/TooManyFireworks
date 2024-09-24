/* Important information for contributors!!
Or more likely me when I forget everything

The FireworksController is the main component. It is attatched to a GameObject called "FireworksController".
This class is responsible for spawning each FireworkItemController from a pool.
It's properties include:
- Center of cube where fireworks spawn (its own position).
- Size of cube where fireworks spawn (_spawnSize).
- Number of seconds between each firework spawning (_minSpawnInterval & _maxSpawnInterval).
It has a list of DirectionalLight components, but the FireworkController used in-game does not have any specified.
Therefore, these properties are useless:
- Array of DirectionalLight components (_directionalLights).
- Intensity of the directional lights (_lightsIntensity).
- Something that's incremented in FireworksController::SpawningCoroutine() for some reason (_currentLightId).
When the component is enabled, it starts the loop of spawning fireworks named FireworksController::SpawningCoroutine().
When the component is disabled, it goes through each currently spawned FireworkItemController and calls FireworksController::ClearFireworkItemController(fireworkItemController) to incinerate it.
This function is also called through an Action when a FireworkItemController when it reaches a specified time.

*/

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
    BSML::Register::RegisterSettingsMenu("Too Many Fireworks", TooManyFireworks::ModConfigMenuDidActivate, false);

    // Install hooks to execute custom code
    PaperLogger.info("Installing hooks...");

    TooManyFireworks::InstallFindFireworksControllerHook();
    TooManyFireworks::InstallFireworkItemControllerPropertiesHook();

    TooManyFireworks::InstallForceEnableLevelResultsHook();

    PaperLogger.info("Installed all hooks!");
}