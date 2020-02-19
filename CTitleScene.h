#pragma once
#include "stdafx.h"
#include "CBaseScene.h"

class CTitleScene : public CBaseScene
{
private:
	char szTitleBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH] = {
" _______  ___   ______    _______  _______    _______  _______  __   __  _______ \0",
"|       ||   | |    _ |  |       ||       |  |       ||   _   ||  |_|  ||       |\0",
"|    ___||   | |   | ||  |  ____ ||_     _|  |    ___||  |_|  ||       ||    ___|\0",
"|   |___ |   | |   |_||_ | |_____   |   |    |   | __ |       ||       ||   |___ \0",
"|    ___||   | |    __	||_____  |  |   |    |   ||  ||       ||       ||    ___|\0",
"|   |    |   | |   |  | | _____| |  |   |    |   |_| ||   _   || ||_|| ||   |___ \0",
"|___|    |___| |___|  |_||_______|  |___|    |_______||__| |__||_|   |_||_______|\0"
"",
"",
"",
"",
"",
"",
"                               Press Enter Key To Start...                       \0"
};
	bool intro_print;
	LARGE_INTEGER fFreq;
	LARGE_INTEGER start;
	bool bEnterEntered;
public:

	CTitleScene();

	~CTitleScene();

	void Update();

	// 인트로 화면 출력
	void PrintIntro();

	// 화면 출력
	void Sprite_Draw();

	// 게임을 시작하기 위한 키보드 입력 받기
	bool GetKeyInput();

	bool GetEnterEntered();

};