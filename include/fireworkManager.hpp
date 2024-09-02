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
    void SetSaveMinSize(float minSize);
    void SetSaveMaxSize(float maxSize);
    void SetSaveNumSparks(int numSparks);
    void SetSaveGravity(float gravity);
    void SetSaveSpawnRangeCenter(UnityEngine::Vector3 position);
    void SetSaveSpawnRangeSize(UnityEngine::Vector3 size);

}