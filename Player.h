#pragma once
#include "Vector2.h"
#include "Camera.h"
#include "InputManager.h"

class Player
{
public:
	void Initialize();
	void Update(const InputManager& input);
	Vector2 GetPosition() const;
	void Draw(const Camera& camera) const;
	void Debug();

private:
	Vector2 position_ = {};
	Vector2 size_ = { 48.0f, 48.0f };
	Vector2 direction_ = { 0.0f, 1.0f };

	float speed_ = 5.0f;

};