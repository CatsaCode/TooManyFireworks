#pragma once

#include "bsml/shared/BSML.hpp"
#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Vector3.hpp"

#include <string>
#include <functional>

namespace TooManyFireworks {

    void CreateExtraIncrementSetting(UnityEngine::GameObject* parent, std::string label, ConfigUtils::ConfigValue<float>& configVariable, std::function<void(float)> onValueChange = nullptr);
    void CreateExtraIncrementSetting(UnityEngine::GameObject* parent, std::string label, ConfigUtils::ConfigValue<UnityEngine::Vector3>& configVariable, std::function<void(UnityEngine::Vector3)> onValueChange = nullptr);

    std::vector<BSML::SliderSetting*> CreateMinMaxConfigSliderSetting(BSML::Lite::TransformWrapper parent, ConfigUtils::ConfigValue<float>& minConfigVariable, ConfigUtils::ConfigValue<float>& maxConfigVariable, std::string minLabel, std::string maxLabel, float increment, float minValue, float maxValue, std::function<void(float)> onMinValueChange, std::function<void(float)> onMaxValueChange);

}