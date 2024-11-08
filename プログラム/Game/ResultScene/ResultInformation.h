/*
* @file		ResultInformation.h
* @brief	リザルト情報
* @author	Morita
* @date		2024/08/04
*/

#pragma once

#include "pch.h"

class ResultInformation
{
public:

	//		コンストラクタ
	ResultInformation()
	:
		m_shader(nullptr),
		m_backGroundMove(nullptr),
		m_fade(nullptr),
		m_playerAnimation(nullptr),
		m_riseNumber(nullptr),
		m_screenEffectManager(nullptr),
		m_changeScene(false)
	{};

	//		デストラクタ
	~ResultInformation(){};

public:

	//		リザルトのUIの種類
	enum ResultUIType
	{
		Back,			//		UI背景
		Button,			//		ボタンヒント
		EvaluationUI,	//		評価
		PlayerBack,		//		プレイヤの背景
	};

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

public:

	void Initialize(StandardShader<ResultInformation::ResultUIType>* shader,
		RiseNumberShader* riseNumber, UIRenderManager* fade,
		BackGroundMove* backGroundMove, ScreenEffectManager* screenEffectManager,
		AnimationManager* playerAnimation)
	{
		m_shader = shader;
		m_riseNumber = riseNumber;
		m_fade = fade;
		m_backGroundMove = backGroundMove;
		m_screenEffectManager = screenEffectManager;
		m_playerAnimation = playerAnimation;
	}

	void Finalize()
	{
		m_changeScene = false;
		m_buffer.time = { 0.0f, 0.0f, 0.0f, 0.0f };
	}

public:

	//		プレイヤーの回転速度
	const float PLAYER_ROTATION_SPEED = 30.0f;

	//		プレイヤーの高さ
	const float PLAYER_HEIGHT = 2.5f;

	//		プレイヤーの座標
	const DirectX::SimpleMath::Vector3 PLAYER_POSITION = { 0.0f, 0.0f, 8.0f };

	//		スコアの座標
	const DirectX::SimpleMath::Vector2 SCORE_POSITION = { 350.0f, 150.0f };

	//		次のシーンの誘導座標
	const DirectX::SimpleMath::Vector2 NEXT_SCENE = { 0.0f, 280.0f };

	//		スコアA
	const float SCORE_A = 2000.0f;

	//		スコアB
	const float SCORE_B = 1000.0f;

private:

	//		シェーダー
	StandardShader<ResultInformation::ResultUIType>* m_shader;

	//		数字の上昇シェーダー
	RiseNumberShader* m_riseNumber;

	//		コンストバッファ
	ConstBuffer m_buffer;

	//		フェード描画
	UIRenderManager* m_fade;

	//		背景の移動
	BackGroundMove* m_backGroundMove;

	//		スクリーンエフェクトマネージャー
	ScreenEffectManager* m_screenEffectManager;

	//		プレイヤーアニメーション
	AnimationManager* m_playerAnimation;

private:

	//		シーンを切り替える
	bool m_changeScene;


public:

	/*
	*	タイトルUIマネージャーのインスタンスのポインタを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	StandardShader<ResultInformation::ResultUIType>* GetStandardShader() { return m_shader; }

	/*
	*	上昇番号シェーーダーのインスタンスのポインタを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	RiseNumberShader* GetRiseNumber() { return m_riseNumber; }

	/*
	*	フェードの描画
	*
	*	@param	(time)	時間
	*/
	void FadeViewProcess(float time) {
		m_buffer.time = { time, 0.0f, 0.0f, 0.0f };
		m_fade->Render(m_buffer);
	}

	/*
	*	コンストバッファのポインタを受け取る
	*
	*	@return コンストバッファ
	*/
	ConstBuffer GetBuffer() { return m_buffer; }

	/*
	*	コンストバッファを設定する
	*
	*	@param	(buffer)	コンストバッファ
	*/
	void SetBuffer(ConstBuffer buffer) { m_buffer = buffer; };

	/*
	*	フェードを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	UIRenderManager* GetFade() { return m_fade; }

	/*
	*	背景を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	BackGroundMove* GetBackGround() { return m_backGroundMove; }

	/*
	*	スクリーンエフェクトを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	ScreenEffectManager* GetScreenEffect() { return m_screenEffectManager; }

	/*
	*	プレイヤーアニメーションを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	AnimationManager* GetAnimation() { return m_playerAnimation; }

	/*
	*	シーンを切り替えるか設定する
	*
	*	@param	(judgement)	true : 切り替える false : 切り替えない
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeScene = judgement; }

	/*
	*	シーンを切り替えるか受け取る
	*
	*	@return true : 切り替える false : 切り替えない
	*/
	bool GetChangeSceneJudgement() { return m_changeScene; }

};
