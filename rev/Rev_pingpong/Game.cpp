#include "Game.h"
#include <windows.h>
#include <thread>
#pragma once

Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, mPaddleDir(0)
	, score(0)
	, winning_round(false)
	, flag(false)
{

}

bool Game::Initialize() {
	srand((unsigned int)time(0));

	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"PingPong Game 1",
		100,
		100,
		WIN_W,
		WIN_H,
		SDL_WINDOW_RESIZABLE
	);

	if (!mWindow) {
		SDL_Log("Failed to create window : %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer) {
		SDL_Log("Failed to render window : %s", SDL_GetError);
		return false;
	}

	if(TTF_Init() == -1){
		SDL_Log("Failed to init ttf : %s", SDL_GetError());
		return false;
	}
	font = TTF_OpenFont("arial.ttf", 40);
	if (!font) {
		SDL_Log("Failed to open font : %s", SDL_GetError());
		return false;
	}
	
	Security();
	GenerateRandomArray();
	Initialize2();

	return true;
}

void Game::Initialize2() {
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = WIN_H / 2.0f;
	mPaddlePos2.x = WIN_W - 10.0f - thickness;
	mPaddlePos2.y = WIN_H / 2.0f;

	ball.clear();

	Ball _ball;
	for (int i = 0; i < ball_num; i++) {
		float t = (rand() % 10 > 5) ? 1.0f : -1.0f;
		float t2 = (rand() % 10 > 5) ? 1.0f : -1.0f;
		_ball.mBallPos.x = WIN_W / 2.0f;
		_ball.mBallPos.y = randomArray[score] % (WIN_H - thickness * 2) + thickness; // set random position
#if DEBUG
		_ball.mBallVel.x = (1.0f * (rand() % 100) + 300.0f); // maintain ball's velocity
#else
		_ball.mBallVel.x = (1.0f * (rand() % 100) + 300.0f) * t;
#endif
		_ball.mBallVel.y = (1.0f * (rand() % 200) + 100.0f) * t2;
		ball.push_back(_ball);
		save = randomArray[score]; // xor flag
	}
}

int Game::GetScore() {
	return score;
}

bool checkDebugger() {
	__try {
		CloseHandle((HANDLE)0x12345678);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return true;
	}
	return false;
}

void Game::DetectDebugger() {
	while (1) {
		if (checkDebugger()) {
#if DEBUG
			printf("Debugger Detected!");
#else
			Sleep(1000 * 60 * 3);
			mIsRunning = false;
#endif	
		}
		Sleep(1000);
	}
}

void Game::ObserveScore() {
	int before_score = 0;
	while (1) {
		if ((score - before_score) > 2) {
#if DEBUG
			printf("Speedhack Detected!");
#else
			Sleep(1000 * 5);
			mIsRunning = false;
#endif
		}
		before_score = score;
		Sleep(1000);
#if !DEBUG
		if (score > 0x100) {
			mIsRunning = false;
		}
#endif
	}
}

void Game::Security() {
	std::thread t1([&]() { DetectDebugger(); });
	std::thread t2([&]() { ObserveScore(); });
	t1.detach();
	t2.detach();
}

void Game::GenerateRandomArray() {
	int tmp;
	int rand_idx;
	for (int i = 0; i < ARRAY_NUM; i++) {
		randomArray[i] = i;
	}
	for (int i = 0; i < ARRAY_NUM; i++) {
		rand_idx = rand() % ARRAY_NUM;
		tmp = randomArray[rand_idx];
		randomArray[rand_idx] = randomArray[i];
		randomArray[i] = tmp;
	}
}

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// user paddle
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (WIN_H - paddleH / 2.0f - thickness)) {
			mPaddlePos.y = WIN_H - paddleH / 2.0f - thickness;
		}
	}

	// cpu paddle
	mPaddlePos2.y = ball[0].mBallPos.y;
	if (mPaddlePos2.y < (paddleH / 2.0f + thickness)) {
		mPaddlePos2.y = paddleH / 2.0f + thickness;
	}
	else if (mPaddlePos2.y > (WIN_H - paddleH / 2.0f - thickness)) {
		mPaddlePos2.y = WIN_H - paddleH / 2.0f - thickness;
	}
	
	// Ball movement
	for (int i = 0; i < ball_num; i++) {
#if DEBUG
		ball[i].mBallPos.x += ball[i].mBallVel.x * deltaTime * 10;
#else
		ball[i].mBallPos.x += ball[i].mBallVel.x * deltaTime;
#endif
		ball[i].mBallPos.y += ball[i].mBallVel.y * deltaTime;
		if (ball[i].mBallPos.y <= thickness && ball[i].mBallVel.y < 0.0f) {
			ball[i].mBallVel.y *= -1;
		}
		else if (ball[i].mBallPos.y >= WIN_H - thickness && ball[i].mBallVel.y > 0.0f) {
			ball[i].mBallVel.y *= -1;
		}

		// left paddle diff
		float diff = mPaddlePos.y - ball[i].mBallPos.y;
		diff = (diff < 0.0f) ? -diff : diff;
		// right paddle diff
		float diff2 = mPaddlePos2.y - ball[i].mBallPos.y;
		diff2 = (diff2 < 0.0f) ? -diff2 : diff2;

		if (ball[i].mBallPos.x <= 0.0f) {
			mIsRunning = false;
			flag = false;
		}
		else if (ball[i].mBallPos.x >= WIN_W) {
			winning_round = true;
			score += 1;
			FLAG_ARRAY[save] ^= save;
		}
		// left paddle hit ball
		else if (diff <= paddleH / 2.0f
			&& ball[i].mBallPos.x <= 25.0f && ball[i].mBallPos.x > 10.0f
			&& ball[i].mBallVel.x < 0.0f)
		{
			ball[i].mBallVel.x *= -1.0f;
		}
		// right paddle hit ball
		else if (diff2 <= paddleH / 2.0f
			&& ball[i].mBallPos.x >= WIN_W - thickness - 10.0f && ball[i].mBallPos.x < WIN_W - thickness
			&& ball[i].mBallVel.x > 0.0f)
		{
#if !DEBUG
			ball[i].mBallVel.x *= -1.0f; // bypass paddle (debug point)
#endif
		}
	}
}

void Game::ProcessInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		SDL_Log("ESCAPE!");
		mIsRunning = false;
	}
#if DEBUG
	else if (state[SDL_SCANCODE_P]) {
		SDL_Log("PAUSE!");
		system("pause");
	}
#endif
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_UP]) {
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_DOWN]) {
		mPaddleDir += 1;
	}
}

void Game::PaintText(char* str, int x, int y) {
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(font, str, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	int W = 0, H = 0;
	SDL_QueryTexture(texture, NULL, NULL, &W, &H);
	SDL_Rect dstrect = { x, y, W, H };
	SDL_RenderCopy(mRenderer, texture, NULL, &dstrect);

	// free space for surface and texture
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(
		mRenderer,
		123,
		237,
		159,
		0.6
	);
	SDL_RenderClear(mRenderer);

	SDL_Rect wall{
		0,
		0,
		WIN_W,
		thickness
	};
	SDL_SetRenderDrawColor(
		mRenderer,
		46,
		213,
		115,
		0.6
	);

	// celling wall
	SDL_RenderFillRect(mRenderer, &wall);

	// bottom wall
	wall.y = WIN_H - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_SetRenderDrawColor(
		mRenderer,
		255,
		255,
		255,
		255
	);
	
	// user paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// cpu paddle
	SDL_Rect paddle2{
		static_cast<int>(mPaddlePos2.x),
		static_cast<int>(mPaddlePos2.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	// Display ball
	for (int i = 0; i < ball_num; i++) {
		SDL_Rect ball_paint{
			static_cast<int>(ball[i].mBallPos.x - thickness / 2),
			static_cast<int>(ball[i].mBallPos.y - thickness / 2),
			thickness,
			thickness
		};
		SDL_RenderFillRect(mRenderer, &ball_paint);
	}

	// Display score
	char str[0x20] = { 0, };

	snprintf(str, 0x20, "score : %d", score);
	PaintText(str, 448, 300);

	// Display Flag
	if (score >= 0x300) {
		snprintf(str, 0x20, FLAG_ARRAY);
		PaintText(str, 150, 570);
		mIsRunning = false;
		flag = true; // winning
	}
	else { // Display Problem
		snprintf(str, 0x20, "If you scoring over than 0x300,");
		PaintText(str, 270, 100);
		
		snprintf(str, 0x20, " you can get the flag!");
		PaintText(str, 300, 150);
	}

	// Render and Display
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() {
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		if (winning_round) {
			Initialize2();
			winning_round = false;
		}
	}
	if (flag) {
		system("pause");
	}
}