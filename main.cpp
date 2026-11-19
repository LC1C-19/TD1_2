#include <Novice.h>
#include <Xinput.h>

#include "InputManager.h"
#include "Player.h"
#include "GameConfig.h"
#include "Map.h"
#include "Camera.h"

#pragma comment(lib, "Xinput.lib")

enum Sceen
{
	TITLE,
	PLAY
};

const char kWindowTitle[] = "LC1C_09_シミズ_イツキ";

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	bool isFullScreen = false;

	// 入力管理
	InputManager input;
	input.Initialize();

	// プレイヤー
	Player player;
	player.Initialize();

	// マップ
	Map map;
	map.Initialize();

	// カメラ
	Camera camera;
	camera.Initialize(
		static_cast<float>(map.GetWidth()),
		static_cast<float>(map.GetHeight())
	);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int currentSceen = TITLE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//毎フレーム入力を受け取る
		input.Update();
		input.DrawDebug();


		//フルスクリーン
		if (input.IsKeyTrigger(DIK_F11) ||
			input.IsButtonTrigger(XINPUT_GAMEPAD_START))
		{
			isFullScreen = !isFullScreen;

			if (isFullScreen)
			{
				Novice::SetWindowMode(kFullscreen);
			}
			else
			{
				Novice::SetWindowMode(kWindowed);
			}
		}

		switch (currentSceen)
		{
		case TITLE:
		{
			Novice::ScreenPrintf(10, 10, "title");
			Novice::ScreenPrintf(10, 25, "space or A");

			//SPACEかAボタンを押したら
			if (input.IsKeyTrigger(DIK_SPACE) ||
				input.IsButtonTrigger(XINPUT_GAMEPAD_A))
			{
				currentSceen = PLAY;
			}
			break;

		}
		case PLAY:
		{
			Novice::ScreenPrintf(10, 10, "play");
			player.Debug();
			player.Update(input);
			camera.Update(player.GetPosition());

			player.Draw(camera);
			break;
		}

		}

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0 ||
			input.IsButtonTrigger(XINPUT_GAMEPAD_BACK)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
