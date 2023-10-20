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
		{400.0f,50.0f},{0.0f,0.0f},{0.0f,-0.8f},
	};

	Vector2 startLinepos = {};
		float originposY = 650.0f;
		float directionY = -1.0f;

		//float Under = pl.pos.y - 64;

		


	//自機画像

	int player[] = { Novice::LoadTexture("./pl.png"), };
	int pljump1 = Novice::LoadTexture("./pljump1.png");
	int pljump2 = Novice::LoadTexture("./pljump2.png");
	//スコアの宣言
	int eachnumber[6] = { 0 };
	int score = 0;
	int hiscore = 0;
	int number = 0;
	int number2 = 0;
	int numgh[10] = {
		Novice::LoadTexture("./suuzi0(end).png"),
		Novice::LoadTexture("./suuzi1(end).png"),
		Novice::LoadTexture("./suuzi2(end).png"),
		Novice::LoadTexture("./suuzi3(end).png"),
		Novice::LoadTexture("./suuzi4(end).png"),
		Novice::LoadTexture("./suuzi5(end).png"),
		Novice::LoadTexture("./suuzi6(end).png"),
		Novice::LoadTexture("./suuzi7(end).png"),
		Novice::LoadTexture("./suuzi8(end).png"),
		Novice::LoadTexture("./suuzi9(end).png")
	};
	int eachnumber3[6] = { 0 };
	int numgh3[10] = {
		Novice::LoadTexture("./suuzi0(end).png"),
		Novice::LoadTexture("./suuzi1(end).png"),
		Novice::LoadTexture("./suuzi2(end).png"),
		Novice::LoadTexture("./suuzi3(end).png"),
		Novice::LoadTexture("./suuzi4(end).png"),
		Novice::LoadTexture("./suuzi5(end).png"),
		Novice::LoadTexture("./suuzi6(end).png"),
		Novice::LoadTexture("./suuzi7(end).png"),
		Novice::LoadTexture("./suuzi8(end).png"),
		Novice::LoadTexture("./suuzi9(end).png")
	};
	int eachnumber4[6] = { 0 };
	int numgh4[10] = {
		Novice::LoadTexture("./suuzi0(end).png"),
		Novice::LoadTexture("./suuzi1(end).png"),
		Novice::LoadTexture("./suuzi2(end).png"),
		Novice::LoadTexture("./suuzi3(end).png"),
		Novice::LoadTexture("./suuzi4(end).png"),
		Novice::LoadTexture("./suuzi5(end).png"),
		Novice::LoadTexture("./suuzi6(end).png"),
		Novice::LoadTexture("./suuzi7(end).png"),
		Novice::LoadTexture("./suuzi8(end).png"),
		Novice::LoadTexture("./suuzi9(end).png")
	};
	int scoreSave = 0;

	//BGM
	int voiceHandle = 0;
	int bgm = Novice::LoadAudio("./bgm.mp3");

	//フラグ
	int isPlJump = 0;
	int isDubleJump = 0;
	int isenemyspawn = 0;

	//数字
	int drinkanime = 120;

	int DubleJumpready = 0;

	//背景の宣言
	
	int bgspeed = 10;
	int bgx = 0;
	int bgx2 = 1280;
	int bg1 = Novice::LoadTexture("./Back1.png");
	int title = Novice::LoadTexture("./Title.png");
	int gameover = Novice::LoadTexture("./Gameover.png");
	int guide = Novice::LoadTexture("./guide.png");
	int Score = Novice::LoadTexture("./Score.png");

	int time = 0;
	
	//敵の宣言
	int bird1 = Novice::LoadTexture("./enemy_bird.gif");
	int bike1 = Novice::LoadTexture("./enemy_huryou.gif");
	
	int enemyposx1 = 1000;
	int enemyposx2 = 1580;
	int enemyposx3 = 1480;
	int enemyposx4 = 1780;
	
	int enemyposy1 = 580;
	int enemyposy2 = 580;
	int enemyposy3 = 100;
	int enemyposy4 = 300;
	
	int enemysize = 20;
	
	int enemyspeed = 10;

	//自機のサイズ
	int playersize = 20;

	//当たり判定
	int a = 0;
	int b = 0;
	int g = 0;
	int h = 0;
	int j = 0;
	int k = 0;
	int q = 0;
	int w = 0;

	//自機生存フラグ
	int isplayersurvive = 1;

	//アイテムの宣言
	int Item[] = { Novice::LoadTexture("./drink1.png"),
	 Novice::LoadTexture("./drink2.png"),
	 Novice::LoadTexture("./drink3.png"),
	 Novice::LoadTexture("./drink4.png"),
	 Novice::LoadTexture("./drink5.png"),
	 Novice::LoadTexture("./drink6.png"), };
	int itemposx = 1280;
	int itemposy = 600;
	int itemtime = 1800;
	int isDrinkGet = 0;
	int DrinkTimer = 1200;
	//ゲームシーン
	enum Scene {
		TITLE,
		GUIDE,
		PLAY,
		OVER,
		SCORE,
	};
	
	Scene scene = TITLE;

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
		switch(scene){
		case TITLE:
			Novice::DrawSprite(0, 0, title, 1.0f, 1.0f, 0.0f, WHITE);
		
			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE] == 0) {
				scene = GUIDE;
			}
			break;
		case GUIDE:

			Novice::DrawSprite(0, 0, guide, 1, 1, 0.0f, WHITE);
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				scene = PLAY;
			}
			break;
		case PLAY:

		
		
		//背景
		Novice::DrawSprite(bgx, 0, bg1, 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(bgx2, 0, bg1, 1, 1, 0.0f, WHITE);

		//横スク

		if (bgx >= -1280) {
			bgx -= bgspeed;
		}
		if (bgx <= -1280) {
			bgx += 1280*2;
		}
		if (bgx2 >= -1280) {
			bgx2 -= bgspeed;
		}
		if (bgx2 <= -1280) {
			bgx2 += 1280*2;
		}
		
		time += 1;
		if (time == 300) {
			bgspeed += 3;
			
			enemyspeed += 3;
		}
		if (time >= 360) {
			time = 0;
		}

		//当たり判定
		a = ((int)pl.pos.x - enemyposx1) * ((int)pl.pos.x - enemyposx1) + ((int)pl.pos.y - enemyposy1) * ((int)pl.pos.y - enemyposy1);
		b = (playersize + enemysize) * (playersize + enemysize);
		g = (playersize + enemysize) * (playersize + enemysize);
		h = ((int)pl.pos.x - enemyposx2) * ((int)pl.pos.x - enemyposx2) + ((int)pl.pos.y - enemyposy2) * ((int)pl.pos.y - enemyposy2);
		//正常に当たる
		j = (playersize + enemysize) * (playersize + enemysize);
		k = ((int)pl.pos.x - enemyposx3) * ((int)pl.pos.x - enemyposx3) + ((int)pl.pos.y  - enemyposy3) * ((int)pl.pos.y  - enemyposy3);
		//
		q = ((int)pl.pos.x - enemyposx4) * ((int)pl.pos.x - enemyposx4) + ((int)pl.pos.y  - enemyposy4) * ((int)pl.pos.y  - enemyposy4);
		w = (playersize + enemysize) * (playersize + enemysize);

		if (b == a || b > a) {
			isplayersurvive = 0;
		}
		if (g == h || g > h) {
			isplayersurvive = 0;
		}
		//
		if (k == j || j > k) {
			isplayersurvive = 0;
		}
		//
		if (w == q || w > q) {
			isplayersurvive = 0;
		}
		
		if (isplayersurvive == 1) {
			//敵表示のタイム
			isenemyspawn = 1;
			itemtime -= 1;

			//BGM
		    if (Novice::IsPlayingAudio(voiceHandle) == 0 || voiceHandle == -1) {
				voiceHandle = Novice::PlayAudio(bgm, 1, 1);
			}
			//自機
			float PltransposY = (pl.pos.y * directionY) + originposY;
			if (isPlJump == 0 && isDubleJump == 0) {
				Novice::DrawSprite((int)pl.pos.x, (int)PltransposY, player[0], 1, 1, 0, WHITE);
			}
			//敵の描画
			if (isenemyspawn == 1) {
				Novice::DrawSprite(enemyposx1, enemyposy1, bike1, 1.5, 1.5, 0.0f, WHITE);
				enemyposx1 = enemyposx1 - enemyspeed;

				Novice::DrawSprite(enemyposx2, enemyposy2, bike1, 1.5, 1.5, 0.0f, WHITE);
				enemyposx2 = enemyposx2 - enemyspeed;

				Novice::DrawSprite(enemyposx3, enemyposy3, bird1, 1.5, 1.5, 0.0f, WHITE);
				enemyposx3 = enemyposx3 - enemyspeed;

				Novice::DrawSprite(enemyposx4, enemyposy4, bird1, 1.5, 1.5, 0.0f, WHITE);
				enemyposx4 = enemyposx4 - enemyspeed;
			}
			
			if (enemyposx1 <= 0) {
				enemyposx1 = 1280;
			}
	
			if (enemyposx2 <= 0) {
				enemyposx2 = 1658;
			}
			
			if (enemyposx3 <= 0) {
				enemyposx3 = 2347;
			}
			
			if (enemyposx4 <= 0) {
				enemyposx4 = 1973;
			}
			//アイテムとったら二段ジャンプ
			if(itemtime == 0){
			    if (drinkanime <= 120 && drinkanime > 100) {
			    	Novice::DrawSprite(itemposx, itemposy, Item[0], 1, 1, 0, WHITE);
			    }
			    if (drinkanime <= 100 && drinkanime > 80) {
			    	Novice::DrawSprite(itemposx, itemposy, Item[1], 1, 1, 0, WHITE);
			    }
				if (drinkanime <= 80 && drinkanime > 60) {
					Novice::DrawSprite(itemposx, itemposy, Item[2], 1, 1, 0, WHITE);
				}
				if (drinkanime <= 60 && drinkanime > 40) {
					Novice::DrawSprite(itemposx, itemposy, Item[3], 1, 1, 0, WHITE);
				}
				if (drinkanime <= 40 && drinkanime > 20) {
					Novice::DrawSprite(itemposx, itemposy, Item[4], 1, 1, 0, WHITE);
				}
				if (drinkanime <= 20 && drinkanime >= 0) {
					Novice::DrawSprite(itemposx, itemposy, Item[5], 1, 1, 0, WHITE);
				}
				if (drinkanime == 0) {
					drinkanime = 120;

				}
			}
			if (isPlJump == 1 && isDubleJump == 0 && DubleJumpready >= 1 && preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] && isDrinkGet == 1) {
				pl.velocity.y = 20.0f;  //↑既存のジャンプ処理の所に飲み物を取っているかのフラグを書き足す
				isDubleJump = 1;
			}
			if (isDrinkGet == 1) {
				DrinkTimer--;
			}//飲み物を取ったら時間制限開始

			if (DrinkTimer == 0) {
				isDrinkGet = 0;
				DrinkTimer = 1200;
			}//制限時間が終わると値を全て戻し、二段ジャンプをできないようにする
			if (isDrinkGet == 1 && DrinkTimer > 200 || DrinkTimer < 150 && DrinkTimer>100 || DrinkTimer < 80 && DrinkTimer>60 || DrinkTimer < 40 && DrinkTimer>30 || DrinkTimer < 20 && DrinkTimer>10 || DrinkTimer < 5 && DrinkTimer>3) {
				Novice::DrawSprite((int)pl.pos.x - 10, (int)PltransposY, player[1], 1, 1, 0, WHITE);
			}//アイコンを表示し、時間が迫るとちかちかさせる

			//プレイヤーのジャンプ

			if (isPlJump == 0 && preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE]) {
				pl.velocity.y = 20.0f;
				isPlJump = 1;
			}
			if (isPlJump == 1) {
				Novice::DrawSprite((int)pl.pos.x, (int)PltransposY, pljump1, 1, 1, 0, WHITE);
			}
			
			if (isDubleJump == 1) {
				Novice::DrawSprite((int)pl.pos.x, (int)PltransposY, pljump2, 1, 1, 0, WHITE);
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

			score += 1;


		}
		
		//スコア表示

		eachnumber[0] = number / 100000;
		number = score % 100000;
		eachnumber[1] = number / 10000;
		number = score % 10000;
		eachnumber[2] = number / 1000;
		number = score % 1000;
		eachnumber[3] = number / 100;
		number = score % 100;
		eachnumber[4] = number / 10;
		number = score % 10;
		eachnumber[5] = number / 1;
		number = score % 1;

		if (score > hiscore) {
			scoreSave = score;
			hiscore = scoreSave;
		}//ハイスコアを保存している

		Novice::DrawSprite(840, -10, numgh[eachnumber[1]], 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(920, -10, numgh[eachnumber[2]], 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(1000, -10, numgh[eachnumber[3]], 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(1080, -10, numgh[eachnumber[4]], 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(1160, -10, numgh[eachnumber[5]], 1, 1, 0.0f, WHITE);
		if (isplayersurvive == 0) {
			scene = OVER;
		}

		break;

		case OVER:
			Novice::StopAudio(voiceHandle);

			Novice::DrawSprite(0, 0, gameover, 1, 1, 0.0f, WHITE);
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				scene = SCORE;
			}
			break;

		case SCORE:
			//終了画面のスコア
			Novice::DrawSprite(0, 0, Score, 1, 1, 0.0f, WHITE);
			eachnumber3[0] = number / 10000;
			number = score % 100000;
			eachnumber3[1] = number / 10000;
			number = score % 10000;
			eachnumber3[2] = number / 1000;
			number = score % 1000;
			eachnumber3[3] = number / 100;
			number = score % 100;
			eachnumber3[4] = number / 10;
			number = score % 10;
			eachnumber4[0] = number2 / 100000;
			number2 = hiscore % 100000;
			eachnumber4[1] = number2 / 10000;
			number2 = hiscore % 10000;
			eachnumber4[2] = number2 / 1000;
			number2 = hiscore % 1000;
			eachnumber4[3] = number2 / 100;
			number2 = hiscore % 100;
			eachnumber4[4] = number2 / 10;
			number2 = hiscore % 10;
			eachnumber4[5] = number2 / 1;
			number2 = hiscore % 1;
			//スコアの描画
			Novice::DrawSprite(400, 110, numgh[eachnumber[1]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(480, 110, numgh[eachnumber[2]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(560, 110, numgh[eachnumber[3]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(640, 110, numgh[eachnumber[4]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(720, 110, numgh[eachnumber[5]], 1, 1, 0.0f, WHITE);

			Novice::DrawSprite(600, 410, numgh4[eachnumber4[1]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(680, 410, numgh4[eachnumber4[2]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(760, 410, numgh4[eachnumber4[3]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(840, 410, numgh4[eachnumber4[4]], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(920, 410, numgh4[eachnumber4[5]], 1, 1, 0.0f, WHITE);
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE]==0) {
				isplayersurvive = 1;
				bgspeed = 10;
				enemyspeed = 10;
				enemyposx1 = 1000;
				enemyposx2 = 1580;
				enemyposx3 = 1480;
				enemyposx4 = 1780;
				pl.pos.y = 50;
				score = 0;
				scene = TITLE;
			}
			break;

		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		

		
		

		//Novice::ScreenPrintf(100, 100, "%f", PltransposY);
		Novice::ScreenPrintf(100, 200, "%d", isDubleJump);
		
		Novice::ScreenPrintf(100, 500, "%d", itemtime);
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
