/*
To Do:
1. security
2. obfuscate score
3. obfuscate string
*/ 

#pragma once
#include "Game.h"
#include <windows.h>

void lose() {
	MessageBox(NULL,
		TEXT("ㅍㅇㅌㅍㅇㅌ\n"), 
		TEXT("ㅎㅅㅎ"), 
		MB_OK);
}

int main(int argc, char* argv[]) {
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	if (!game.flag) {
		lose();
	}
	game.Shutdown();
	return 0;
}