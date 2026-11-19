#pragma once
#include "Vector2.h"

class Boss
{
public:
	static const int kMaxBullets = 100;

	struct Bullet {
		Vector2 position;
		Vector2 velocity;
		float radius;
		bool isActive;
	};

	Boss();
	void Update();
	void Draw();

private:
	void Warp();
	void FireRadialBullets();

	Vector2 position_;
	float radius_;

	int warpTimer_;
	int attackTimer_;

	Bullet bullets_[kMaxBullets];
};

