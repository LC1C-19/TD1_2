#include "Player.h"
#include "Camera.h"
#include "Map.h"

#include <Novice.h>
#include <math.h>

void Player::Initialize()
{
	position_ = { 640.0f, 360.0f };
	size_ = { 48.0f, 48.0f };
	direction_ = { 0.0f, 1.0f };

	speed_ = 5.0f;
}

void Player::Update(const InputManager& input)
{
	// 移動方向を取得
	Vector2 move = input.GetMoveDirection();

	position_.x += move.x * speed_;
	position_.y += move.y * speed_;

	// 右スティックの入力
	Vector2 aim = input.GetAimDirection();

	float aimLength = sqrtf(
		aim.x * aim.x + aim.y * aim.y
	);

	if (aimLength > 0.01f)
	{
		direction_.x = aim.x / aimLength;
		direction_.y = aim.y / aimLength;
	}
	else
	{
		float moveLength = sqrtf(
			move.x * move.x + move.y * move.y
		);

		if (moveLength > 0.01f)
		{
			direction_.x = move.x / moveLength;
			direction_.y = move.y / moveLength;
		}
	}

	float mapWidth = static_cast<float>(Map::GetWidth());
	float mapHeight = static_cast<float>(Map::GetHeight());

	// 画面外への移動を制限
	float halfWidth = size_.x / 2.0f;
	float halfHeight = size_.y / 2.0f;

	if (position_.x < halfWidth)
	{
		position_.x = halfWidth;
	}

	if (position_.x > mapWidth - halfWidth)
	{
		position_.x = mapWidth - halfWidth;
	}

	if (position_.y < halfHeight)
	{
		position_.y = halfHeight;
	}

	if (position_.y > mapHeight - halfHeight)
	{
		position_.y = mapHeight - halfHeight;
	}
}


void Player::Draw(const Camera& camera) const
{
	// ワールド座標からスクリーン座標へ
	Vector2 screenPosition = camera.WorldToScreen(position_);

	float drawX = screenPosition.x - size_.x / 2.0f;
	float drawY = screenPosition.y - size_.y / 2.0f;

	// プレイヤー描画
	Novice::DrawBox(
		static_cast<int>(drawX),
		static_cast<int>(drawY),
		static_cast<int>(size_.x),
		static_cast<int>(size_.y),
		0.0f, BLUE, kFillModeSolid
	);

	// 向き表示
	Novice::DrawLine(
		static_cast<int>(screenPosition.x),
		static_cast<int>(screenPosition.y),
		static_cast<int>(screenPosition.x + direction_.x * 40.0f),
		static_cast<int>(screenPosition.y + direction_.y * 40.0f),
		WHITE
	);
}

Vector2 Player::GetPosition() const
{
	return position_;
}

void Player::SetPosition(Vector2 position) {
	position_ = position;
}

void Player::Debug()
{
	Novice::ScreenPrintf(10, 30, "position {%.2f : %.2f}", position_.x, position_.y);
}