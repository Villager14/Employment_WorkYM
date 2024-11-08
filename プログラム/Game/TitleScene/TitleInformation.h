/*
* @file		TitleInformation.h
* @brief	タイトルの情報
* @author	Morita
* @date		2024/08/01
*/

#pragma once

#include "pch.h"

#include "Library/Shader/UIRenderManager.h"

#include "Library/Shader/StandardShader.h"

#include "Library/Shader/UIRenderManager.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "ITitleSelect.h"

class TitleInformation
{
public:

	//		コンストラクタ
	TitleInformation()
	:
		m_inputKey(false),
		m_backGroundMove(nullptr),
		m_fade(nullptr),
		m_standardShader(nullptr),
		m_changeSceneJudgement(false),
		m_scrollWheel(0),
		m_direction(false),
		m_menuUseJudgement(false)
	{};

	//		デストラクタ
	~TitleInformation() {};

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

	//		UIの種類
	enum TitleUIType
	{
		Play,		//		プレイ
		End,		//		終了
		Setting,	//		設定
		TitleRogo,	//		タイトルロゴ
		Space,		//		スペース
		W,			//		W
		A,			//		A
	};

	//		状態
	enum State
	{
		PlayState,		//		プレイ状態
		EndState,		//		終了状態
		SettingState,	//		設定状態
		ChangState,		//		変更状態
		StartState		//		スタート状態
	};

	enum MoveDirection
	{
		UP,
		Down,
		Back,
	};

public:

	void Initilaize(BackGroundMove* backGroundMove,
		StandardShader<TitleUIType>* standardShader,
		UIRenderManager* fade)
	{
		m_backGroundMove = backGroundMove;
		m_standardShader = standardShader;
		m_fade = fade;
	}

	void Finalize()
	{
		m_inputKey = false;
		m_changeSceneJudgement = false;
		m_scrollWheel = 0;
	}

public:

	//		タイトルロゴの座標
	const DirectX::SimpleMath::Vector2 TITLE_POINT = { 0.0f, -170.0f };

	//		中心始点
	const DirectX::SimpleMath::Vector2 CENTER_POINT = { 0.0f,120.0f };

	//		下地点
	const DirectX::SimpleMath::Vector2 UNDER_POINT = { 0.0f, 200.0f };

	//		上地点
	const DirectX::SimpleMath::Vector2 UP_POINT = { 0.0f, 40.0f };

	//		スペースのプレイ時座標
	const DirectX::SimpleMath::Vector2 SPACE_PLAY = { 300.0f, 120.0f };

	//		スペースのエンド時座標
	const DirectX::SimpleMath::Vector2 SPACE_END = { 270.0f, 120.0f };

	//		スペースの設定時座標
	const DirectX::SimpleMath::Vector2 SPACE_SETTING = { 410.0f, 120.0f };

	//		Wのプレイ時座標
	const DirectX::SimpleMath::Vector2 W_PLAY = { 120.0f, 40.0f };

	//		Wのエンド時座標
	const DirectX::SimpleMath::Vector2 W_END = { 110.0f, 40.0f };

	//		Wの設定時座標
	const DirectX::SimpleMath::Vector2 W_SETTING = { 180.0f, 40.0f };

	//		Aのプレイ時座標
	const DirectX::SimpleMath::Vector2 A_PLAY = { 120.0f, 200.0f };

	//		Aのエンド時座標
	const DirectX::SimpleMath::Vector2 A_END = { 110.0f, 200.0f };

	//		Aの設定時座標
	const DirectX::SimpleMath::Vector2 A_SETTING = { 180.0f, 200.0f };


	//		移動速度
	const float MOVE_SPEED = 7.0f;

	//		最大スケール
	const float MAX_SCALE = 1.0f;

	//		最小スケール
	const float MIN_SCALE = 0.5f;

private:

	//		背景移動
	BackGroundMove* m_backGroundMove;

	//		スタンダードシェーダー
	StandardShader<TitleUIType>* m_standardShader;

	//		フェードの処理
	UIRenderManager* m_fade;

	//		定数バッファ
	ConstBuffer m_buffer;

	//		キー入力があったかどうか
	bool m_inputKey;

	//		シーンを変更するかどうか
	bool m_changeSceneJudgement;

	//		スクロールの値
	int m_scrollWheel;

	//		移動方向
	bool m_direction;

	//		メニューを使えるかどうか
	bool m_menuUseJudgement;

	//		状態の情報
	std::unordered_map<TitleInformation::State, std::unique_ptr<ITitleSelect>> m_stateInformation;

	//		描画順を設定する
	std::vector<TitleInformation::TitleUIType> m_drawOder;

public:

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
	void SetBuffer(ConstBuffer buffer) { m_buffer = buffer;};

	/*
	*	タイトルUIマネージャーのインスタンスのポインタを受け取る
	*
	*	@return インスタンスのポインタ
	*/
	StandardShader<TitleUIType>* GetStandardShader() { return m_standardShader; }

	/*
	*	キー入力があるかどうか受け取る
	*
	*	@return true : キー入力がある false : キー入力がない
	*/
	bool GetKeyInput() { return m_inputKey; }

	/*
	*	キー入力があるかどうか受け取る
	*
	*	@param	(judgement) true : キー入力がある false : キー入力がない
	*/
	void SetKeyInput(bool judgement) { m_inputKey = judgement; }

	/*
	*	シーンを切り替えるかどうか判断する
	*
	*	@param	(judgement)	true : 切り替える false : 切り替えない
	*/
	void SetChangeSceneJudgement(bool judgement) { m_changeSceneJudgement = judgement; }

	/*
	*	シーンを切り替えるかどうか判断する
	*
	*	@return true : 切り替える false : 切り替えない
	*/
	bool GetChangeScnenJudgemnet() { return m_changeSceneJudgement; }

	/*
	*	スクロールホイールを設定する
	* 
	*	@param	(wheel)	ホイールの値
	*/
	void SetScrollWheel(int wheel) { m_scrollWheel = wheel; }

	/*
	*	スクロールホイールの値を受け取る
	* 
	*	@return スクロールの値
	*/
	int GetScrollWheel() { return m_scrollWheel; }

	/*
	*	移動方向を受け取る
	*
	*	@return true : 上 false : 下
	*/
	bool GetDirection() { return m_direction; }

	/*
	*	移動方向受け取る
	*
	*	@param	(direction) true : 上 false : 下
	*/
	void SetDirection(bool direction) { m_direction = direction; }

	/*
	*	メニューを開けるかどうか設定する
	*
	*	@param	(judgement)	true : 使える false : 使えない
	*/
	void SetMenuUseJudgement(bool judgement) { m_menuUseJudgement = judgement; }

	/*
	*	メニューを開けるかどうか設定する
	*
	*	@return	true : 使える false : 使えない
	*/
	bool GetMenuUseJudgement() { return m_menuUseJudgement; }

	/*
	*	状態の情報を受け取る
	*
	*	@return	ポインタ
	*/
	std::unordered_map<TitleInformation::State, std::unique_ptr<ITitleSelect>>* GetStateInformation() { return &m_stateInformation; }

	/*
	*	描画順の情報を受け取る
	*
	*	@return	ポインタ
	*/
	std::vector<TitleInformation::TitleUIType>* GetDraowOder() { return &m_drawOder; }

};