#include <Novice.h>
#include<Vector2.h>
#define USE_MATH_DEFINE
#include <math.h>
#include <time.h>


const char kWindowTitle[] = "LC1D_07_カラサワミクム タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	//構造体

	struct Pl {
		Vector2 pos;
		Vector2 velocity;
		Vector2 acceleration;

	};


	Pl pl{
		{10.0f,50.0f},{0.0f,0.0f},{0.0f,-0.8f},
	};

	Vector2 startLinepos = {};


	//画像

	int player[] = { Novice::LoadTexture("./pl.png"), };

	int Item[] = { Novice::LoadTexture("./drink1.png"),
	 Novice::LoadTexture("./drink2.png"),
	 Novice::LoadTexture("./drink3.png"),
	 Novice::LoadTexture("./drink4.png"),
	 Novice::LoadTexture("./drink5.png"),
	 Novice::LoadTexture("./drink6.png"), };

	//フラグ
	int isPlJump = 0;
	int isDubleJump = 0;


	//数字
	int drinkanime = 120;
	int DubleJumpready = 0;

	//背景の宣言
	
	int bgspeed = 10;
	int bgx = 0;
	int bgx2 = 1280;
	int bg1 = Novice::LoadTexture("./Back1.png");
	//int bg2 = Novice::LoadTexture("./Back2.png");
	int time = 0;
	
	//int title = Novice::LoadTexture("./title.png");
	//int gameover = Novice::LoadTexture("./gameover.png");

	

	//自機生存フラグ
	//int isplayersurvive = 1;

	//ゲームシーン
	//enum Scene {
	//	TITLE,
	//	PLAY,
	//	OVER,
	//};
	//
	//Scene scene = TITLE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		//switch(scene){
		//case TITLE:
		//	Novice::DrawSprite(0, 0, title, 1.0f, 1.0f, 0.0f, WHITE);
		//
		//	if (keys[DIK_SPACE]) {
		//		scene = PLAY;
		//	}
		//	break;
		//case PLAY:
		float originposY = 500.0f;
		float directionY = -1.0f;

		//float Under = pl.pos.y - 64;

		float PltransposY = (pl.pos.y * directionY) + originposY;
		//float lineTransPosY = (startLinepos.y * directionY) + originposY;

		//横スク

	
		

		if (bgx >= -1280) {
			bgx -= bgspeed;
		}
		if (bgx <= -1280) {
			bgx = 1280;
		}
		if (bgx2 >= -1280) {
			bgx2 -= bgspeed;
		}
		if (bgx2 <= -1280) {
			bgx2 = 1280;
		}
		
		time += 1;
		if (time == 300) {
			bgspeed += 3;
			
			//enemyspeed += 3;
		}
		if (time >= 360) {
			time = 0;
		}


		if (isPlJump == 0 && preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]) {

			pl.velocity.y = 20.0f;
			isPlJump = 1;


		}

		if (isPlJump == 1 && isDubleJump == 0 && DubleJumpready >= 1 && preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]) {
			pl.velocity.y = 20.0f;
			isDubleJump = 1;
		}


		if (isPlJump == 1 && isDubleJump == 0) {
			pl.velocity.y += pl.acceleration.y;
			pl.pos.y += pl.velocity.y;
			DubleJumpready += 1;
		}
		if (isDubleJump == 1) {
			pl.velocity.y += pl.acceleration.y;
			pl.pos.y += pl.velocity.y;
		}

		if (pl.pos.y <= 50) {
			pl.pos.y = 50;
			isPlJump = 0;
			isDubleJump = 0;
			DubleJumpready = 0;
		}
		//case OVER:
		//	Novice::DrawSprite(0, 0, gameover, 1, 1, 0.0f, WHITE);
		//	if (keys[DIK_T]) {
		//		scene = TITLE;
		//		isplayersurvive = 1;
		//	}
		//}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		drinkanime -= 5;
		Novice::DrawSprite(bgx, 0, bg1, 4, 4, 0.0f, WHITE);
		Novice::DrawSprite(bgx2, 0, bg1, 4, 4, 0.0f, WHITE);
		Novice::DrawSprite((int)pl.pos.x, (int)PltransposY, player[0], 1, 1, 0, WHITE);

		if (drinkanime <= 120 && drinkanime > 100) {
			Novice::DrawSprite(0, 0, Item[0], 1, 1, 0, WHITE);
		}
		if (drinkanime <= 100 && drinkanime > 80) {
			Novice::DrawSprite(0, 0, Item[1], 1, 1, 0, WHITE);
		}
		if (drinkanime <= 80 && drinkanime > 60) {
			Novice::DrawSprite(0, 0, Item[2], 1, 1, 0, WHITE);
		}
		if (drinkanime <= 60 && drinkanime > 40) {
			Novice::DrawSprite(0, 0, Item[3], 1, 1, 0, WHITE);
		}
		if (drinkanime <= 40 && drinkanime > 20) {
			Novice::DrawSprite(0, 0, Item[4], 1, 1, 0, WHITE);
		}
		if (drinkanime <= 20 && drinkanime >= 0) {
			Novice::DrawSprite(0, 0, Item[5], 1, 1, 0, WHITE);
		}
		if (drinkanime == 0) {
			drinkanime = 120;

		}

		Novice::ScreenPrintf(100, 100, "%f", pl.velocity.y);
		Novice::ScreenPrintf(100, 200, "%d", isDubleJump);
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
