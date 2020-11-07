#pragma once
#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2main.lib")
#pragma comment (lib, "SDL2_ttf.lib")
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <ctime>

#define WIN_W 0x400
#define WIN_H 0x300
#define ARRAY_NUM WIN_H

//#define DEBUG true

const int thickness = 15;
const float paddleH = 100.0f;
const int ball_num = 1;
static char dummy[0x100] = { 0, };
//static char FLAG_ARRAY[ARRAY_NUM] = "FMCD\x7fQNN[VCXSKBNWVUTSRQP_^]\\[Zc\x1f";
static char FLAG_ARRAY[ARRAY_NUM] = "KBVE\x7fW5qm{?NSH`H!\x7f!vf$xpG(ID],i+YR}mA`B\x14lvL\x1b~r{\x1aM";

struct Vector2 {
	float x;
	float y;
};

struct Ball {
	Vector2 mBallPos;
	Vector2 mBallVel;
};

class Game {
public:
	Game();
	bool Initialize();
	void Initialize2();
	void RunLoop();
	void Shutdown();
	int GetScore();
	bool flag;				// win or lose game
private:
	void ProcessInput();
	void Security();        // detect debugger and observe score's adding interval time
	void DetectDebugger();
	void ObserveScore();
	void UpdateGame();
	void GenerateOutput();
	void PaintText(char* str, int x, int y);
	void GenerateRandomArray();

	Uint32 mTicksCount;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	bool winning_round;
	std::vector<Ball>ball;

	int mPaddleDir;
	int mPaddleDir2;
	Vector2 mPaddlePos;
	Vector2 mPaddlePos2;
	TTF_Font* font;
	int score;
	int scorex, scorey, scorez;
	int save; // save initial ball position
	int randomArray[ARRAY_NUM] = { 0, };
};