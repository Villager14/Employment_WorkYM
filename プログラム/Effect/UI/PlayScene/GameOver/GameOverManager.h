/*
* @file		GameOverManager.h
* @brief	ゲームオーバーマネージャー
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "../UIManager.h"

class GameOverManager
{
public:
	//		コンストラクタ
	GameOverManager(GameManager* gameManager, UIManager* uiManager);

	//		デストラクタ
	~GameOverManager();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	//		ゲームマネージャーのインスタンスのポインタ
	GameManager* m_gameManager;

	//		UIマネージャーのインスタンスのポインタ
	UIManager* m_uiManager;

	//		経過時間
	float m_elapsedTime;
};