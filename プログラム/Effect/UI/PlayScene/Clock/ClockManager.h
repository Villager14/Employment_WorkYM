/*
* @file		ClockManager.h
* @brief	UI時計のマネージャー
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "ClockBackGround.h"

#include "ClockTime.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "../UIManager.h"

class ClockManager
{
public:

	//		コンストラクタ
	ClockManager(UIManager* uiManager);

	//		デストラクタ
	~ClockManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(gameManager)	ゲームマネージャーのインスタンスのポインタ
	*/
	void Update(GameManager* gameManager);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	//		UIManagerのインスタンスのポインタ
	UIManager* m_uiManager;

	//		時計の背景
	std::unique_ptr<ClockBackGround> m_clockBackGround;

	//		時計の数字
	std::unique_ptr<ClockTime> m_clockTime;

	//		経過時間
	float m_elapsedTime;

public:

	float GetElapsedTime() { return m_elapsedTime; }
};