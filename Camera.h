#pragma once

#include "Vector2.h"
#include "GameConfig.h"

class Camera
{
public:
    void Initialize(
        float mapWidth,
        float mapHeight
    );

    void Update(Vector2 targetPosition);

    // ワールド座標をスクリーン座標に変換
    Vector2 WorldToScreen(Vector2 worldPosition) const;

    // カメラの座標を取得
    Vector2 GetPosition() const;

private:
    Vector2 position_ = {};

    float screenWidth_ = static_cast<float>(kWindowWidth);
    float screenHeight_ = static_cast<float>(kWindowHeight);

    float mapWidth_ = 0.0f;
    float mapHeight_ = 0.0f;
};
