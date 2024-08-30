#pragma once

namespace UnityEngine {
    class Vector3;
    class Color;
}

namespace TooManyFireworks {

    void SetFireworksEnabled(bool enabled);

    void SetSaveMinFrequency(float minFrequency);
    void SetSaveMaxFrequency(float maxFrequency);
    void SetSaveColor(UnityEngine::Color color);
    void SetSaveRainbow(bool rainbow);
    void SetSaveBrightness(float brightness);
    void SetSaveMinExplosionPower(float minExplosionPower);
    void SetSaveMaxExplosionPower(float maxExplosionPower);
    void SetSaveGravity(float gravity);
    void SetSaveSpawnVolumeCenter(UnityEngine::Vector3 position);
    void SetSaveSpawnVolumeSize(UnityEngine::Vector3 size);

}