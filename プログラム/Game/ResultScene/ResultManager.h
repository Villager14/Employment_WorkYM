/*
* @file		ResultManager.h
* @brief	リザルトマネージャー
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include <unordered_map>

#include "IResultManager.h"

#include "Effect/UI/TitleScene/BackGroundMove.h"

#include "Library/Shader/UIRenderManager.h"

#include "Game/PlayScene/ScreenEffect/ScreenEffectManager.h"

#include "Library/Animation/AnimationManager.h"

#include "Library/Shader/StandardShader.h"

#include "Effect/UI/ResultScene/RiseNumberShader.h"

#include "ResultInformation.h"

class ResultManager
{
public:

	//		リザルトマネージャー
	ResultManager();

	//		リザルトマネージャー
	~ResultManager();

	//		初期化処理
	/*
	*	初期化処理
	* 
	*	@param	(score)			スコア
	*	@param	(time)			タイム
	*	@param	(deathCount)	死亡カウント
	*/
	void Initialize(int score, int time, int deathCount);

	//		生成
	void Generation();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		状態を作成する
	void CreateState();

	//		アニメーションスキップ
	void AnimationSkip();

	//		シェーダーの作製
	void CreateStandardShader();

	//		背景の更新
	void BackGroundUpdate();

public:


	//		状態
	enum State
	{
		Start,			//		スタート
		NumberMove,		//		番号
		Evaluation,		//		評価
		Stay,			//		待機
		End,			//		終了
	};

private:
	
	//		スコア
	int m_score;

	//		時間
	int m_time;

	//		死亡カウント
	int m_deathCount;

	//		回転量
	float m_rotation;

	//		メニューを使えるかどうか
	bool m_menuUseJudgement;

	//		情報
	std::unique_ptr<ResultInformation> m_information;

	//		状態
	IResultManager* m_iState;

	//		状態の情報
	std::unordered_map<State, std::unique_ptr<IResultManager>> m_stateInformation;

	//		状態
	State m_state;

	//		数字の上昇シェーダー
	std::unique_ptr<RiseNumberShader> m_riseNumber;

	//		スタンダードシェーダー
	std::unique_ptr<StandardShader<ResultInformation::ResultUIType>> m_shader;

	//		フェード描画
	std::unique_ptr<UIRenderManager> m_fade;

	//		背景移動の描画
	std::unique_ptr<BackGroundMove> m_backGroundMove;

	//		スクリーンエフェクトマネージャー
	std::unique_ptr<ScreenEffectManager> m_screenEffectManager;

	//		プレイヤーアニメーション
	std::unique_ptr<AnimationManager> m_playerAnimation;

public:

	/*
	*	状態を変更する
	*
	*	@param	(state)	状態
	*/
	void ChangeState(State state);

	/*
	*	メニューを使えるかどうか受け取る
	* 
	*	@return true : 使える false : 使えない
	*/
	bool GetMenuUseJugement() { return m_menuUseJudgement; }

	/*
	*	メニューを使えるかどうか設定する
	*
	*	@param	(judgement) true : 使える false : 使えない
	*/
	void SetMenuUseJugement(bool judgement) { m_menuUseJudgement = judgement; }

	/*
	*	情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	ResultInformation* GetInformation() { return m_information.get(); }

	
};