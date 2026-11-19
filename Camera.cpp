#include "Camera.h"
#include "GameConfig.h"

// 初期化
void Camera::Initialize(
	float mapWidth,
	float mapHeight)
{
	position_ = { 0.0f, 0.0f };

	screenWidth_ = static_cast<float>(kWindowWidth);
	screenHeight_ = static_cast<float>(kWindowHeight);

	mapWidth_ = mapWidth;
	mapHeight_ = mapHeight;
}

// プレイヤーに追従
void Camera::Update(Vector2 targetPosition)
{
	// プレイヤーを画面中央に配置
	position_.x = targetPosition.x - screenWidth_ / 2.0f;

	position_.y = targetPosition.y - screenHeight_ / 2.0f;

	// 左端・上端の制限
	if (position_.x < 0.0f)
	{
		position_.x = 0.0f;
	}

	if (position_.y < 0.0f)
	{
		position_.y = 0.0f;
	}

	// 右端・下端の制限
	float maxX = mapWidth_ - screenWidth_;
	float maxY = mapHeight_ - screenHeight_;

	if (maxX < 0.0f)
	{
		maxX = 0.0f;
	}

	if (maxY < 0.0f)
	{
		maxY = 0.0f;
	}

	if (position_.x > maxX)
	{
		position_.x = maxX;
	}

	if (position_.y > maxY)
	{
		position_.y = maxY;
	}
}

// ワールド座標からスクリーン座標
Vector2 Camera::WorldToScreen(
	Vector2 worldPosition) const
{
	Vector2 result = {};

	result.x = worldPosition.x - position_.x;
	result.y = worldPosition.y - position_.y;

	return result;
}

// カメラ座標取得
Vector2 Camera::GetPosition() const
{
	return position_;
}
