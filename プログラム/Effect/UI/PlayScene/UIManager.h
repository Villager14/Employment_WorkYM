/*
* @file		UIManager.h
* @brief	UIマネージャー
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include "Library/Shader/StandardShader.h"

class ClockManager;
class CoolTime;
class GameOverManager;
class GameClearManager;
class SpeedLine;
class GameStart;
class CountDown;

class UIManager
{
public:
	//		コンストラクタ
	UIManager(PlayerInformation* playerInformation, GameManager* gameManager);

	//		デストラクタ
	~UIManager();

	//		初期処理
	void Initialize();

	//		生成
	void Generation();

	//		更新処理
	void Update();

	//		終了処理
	void Finalize();

	void FrontRender();

	void BackRender();

	//		UIテクスチャの作製
	void CreateStandardUITexture();

public:

	enum UIType
	{
		ClockBackGround,		//		時計の背景
		ClockColon,				//		時計のコロン
		CloolTimeBackGround,	//		クールタイムの背景
		GameOver,				//		ゲームオーバー
		GameOverContinue,		//		ゲームオーバーのコンティニュー
		NextInduction,			//		次の状態の誘導
		ScreenRay,				//		スクリーンのレイ
		GameClearBarUnder,		//		ゲームクリアのバー
		GameClearBarUp,			//		ゲームクリアのバー		
		GameClearBackGround,	//		ゲームクリアの背景
		GameStartTimeLimit,		//		ゲームスタートタイムリミット
		GameStartTimeTen		//		ゲームスタートタイムリミットの点
	}; 

public:

	//		時計背景座標
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_GROUND_POSITION = { 480.0f, 200.0f };

	//		時計時間背景座標
	const DirectX::SimpleMath::Vector2 CLOCK_BACK_TIME_GROUND_POSITION = { 539.0f, 0.0f };

	//		次の状態誘導座標
	const DirectX::SimpleMath::Vector2 NEXT_INDCCTION = { 0.0f, 200.0f };

	//		メッセージバー上の座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_UP = { 0.0f, 13.0f };

	//		メッセージバー下の座標
	const DirectX::SimpleMath::Vector2 MESSAGE_BER_DOWN = { 0.0f, -13.0f };

private:
	//		時計の背景
	std::unique_ptr<ClockManager> m_clockManager;

	//		クールタイム
	std::unique_ptr<CoolTime> m_coolTime;

	//		カウントダウン
	std::unique_ptr<CountDown> m_countDonw;
		
	//		ゲームオーバー
	std::unique_ptr<GameOverManager> m_gameOver;

	//		スピードライン
	std::unique_ptr<SpeedLine> m_speedLine;

	//		ゲームスタート
	std::unique_ptr<GameStart> m_gameStart;

	//		プレイヤーの情報を受け取る
	PlayerInformation* m_playerInformation;

	//		ゲームマネージャー
	GameManager* m_gameManager;

	//		ゲームクリアマネージャー
	std::unique_ptr<GameClearManager> m_clearManager;

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<UIType>> m_standardShader;

public:

	/*
	*	スタンダードシェーダーを受け取る
	* 
	*	@return スタンダードシェーダーを受け取る
	*/
	StandardShader<UIType>* GetStandardShader() { return m_standardShader.get(); }

	/*
	*	ゲームマネージャーを受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	プレイヤーの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerInformation* GetPlayerInformation() { return  m_playerInformation; }
};