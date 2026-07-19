#pragma once

#include "bn_optional.h"

enum class SceneType;

class Scene {
public:
    virtual ~Scene() = default;

    [[nodiscard]] virtual bn::optional<SceneType> Update() = 0;

protected:
    Scene() = default;
};
