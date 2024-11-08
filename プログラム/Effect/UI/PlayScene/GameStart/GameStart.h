/*
* @file		GameStart.h
* @brief	ゲームスタートマネージャー
* @author	Morita
* @date		2024/10/20
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "../UIManager.h"

#include "Library/Shader/UIRenderManager.h"

class GameStart
{
public:
	//		コンストラクタ
	GameStart(GameManager* gameManager, UIManager* uiManager);

	//		デストラクタ
	~GameStart();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();
	
	//		数字の描画
	void NumberView();

	/*
	*	スリーカウント描画
	* 
	*	@return true : カウント中 false : カウントしていない
	*/
	bool ThreeCountView();

	//		タイムリミットの移動処理
	bool TimeLimitMove();

	//		タイムリミット番号のランダム処理
	bool TimeLimitNumberRandom();

	//		スリーカウントの処理
	void ThreeCountProcess();

	//		番号サイズ時間
	bool NumberSizeTime();
public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		アスペクト比
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		DirectX::SimpleMath::Vector4 number;			//		数字
	};

private:


	//		ゲームマネージャーのインスタンスのポインタ
	GameManager* m_gameManager;

	//		UIマネージャーのインスタンスのポインタ
	UIManager* m_uiManager;

	//		数字の描画
	std::unique_ptr<UIRenderManager> m_numberRender;

	//		コンストバッファ
	ConstBuffer m_constBuffer;

	//		経過時間
	float m_elapsedTime;

	//		待機時間
	float m_stayTime;

	//		番号
	int m_number;

	//		数字の更新頻度
	float m_numberUpdateFrequency;

	//		番号経過時間
	float m_numberElapsedTime;

	//		番号時間
	float m_numberTime;

	//		制限時間
	float m_limitTime;

	//		リミット処理を行うかどうか
	bool m_limitJudgement;

	//		番号待機時間
	float m_numberStayTime;

	//		スリーカウント経過時間
	float m_threeCountElapsedTime;

	//		番号サイズ時間
	float m_numberSizeTime;

	//		スリーカウント番号
	int m_threeCountNumber;

	//		終了するかどうか
	bool m_endJudgement;
};