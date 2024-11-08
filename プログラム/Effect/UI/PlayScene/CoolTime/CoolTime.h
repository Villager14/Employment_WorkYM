/*
* @file		CoolTime.h
* @brief	クールタイム
* @author	Morita
* @date		2024/05/20
*/

#pragma once

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "Library/Shader/UIRenderManager.h"

#include "../UIManager.h"

class CoolTime
{
public:

	//		コンストラクタ
	CoolTime(UIManager* uiManager);

	//		デストラクタ
	~CoolTime();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	*	
	*	プレイヤーの情報を受けとる
	*/
	void Update(PlayerInformation* playerInformation);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		数字の描画
	void NumberView();

private:

	enum State
	{
		None,		//		何もない状態
		Reduce,		//		減らす状態
		Increase	//		増やす状態
	};

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		アスペクト比
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		DirectX::SimpleMath::Vector4 number;			//		数字
	};

	//		コンストバッファ回転
	struct ConstBufferCircle
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 rotation;
	};


private:

	//		数字の中心の座標
	const float NUMBER_CENTER_POSITION = 1179.0f;

	//		数字の間隔
	const float NUMBER_INTERVAL = 30.0f;

	//		クールタイムの座標
	const DirectX::SimpleMath::Vector2 COOL_TIME_POSITION = { 270.0f, 0.0f };

private:

	//		UIマネージャのインスタンスのポインタ
	UIManager* m_uiManager;

	//		角度
	float m_angle;

	//		時間
	float m_time;

	//		パーセント
	float m_ratio;

	//		クールタイムに入ったかどうか判断する
	bool m_coolTimeJudgement;

	//		状態
	State m_state;

	//		シェーダー
	std::unique_ptr<UIRenderManager> m_coolTimeNumberShader;

	//		回転シェーダー
	std::unique_ptr<UIRenderManager> m_coolTImeShader;

	//		コンストバッファ
	ConstBuffer buffer;

	//		回転コンストバッファ
	ConstBufferCircle circleBuffer;
};
