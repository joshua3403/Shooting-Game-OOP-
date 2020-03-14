#pragma once
#include "stdafx.h"
#include "CBaseScene.h"
#include "CSceneManager.h"

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
	bool _introPrint;
	LARGE_INTEGER fFreq;
	LARGE_INTEGER start;
	bool bEnterEntered;
	CSceneManager* pSceneManager;
public:

	CTitleScene(CSceneManager* pSceneManager);

	~CTitleScene();

	void Update();

	// ��Ʈ�� ȭ�� ���
	void PrintIntro();

	// ȭ�� ���
	void Sprite_Draw();

	// ������ �����ϱ� ���� Ű���� �Է� �ޱ�
	bool GetKeyInput();

	bool GetEnterEntered();

};