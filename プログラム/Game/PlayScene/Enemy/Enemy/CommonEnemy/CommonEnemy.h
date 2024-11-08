/*
* @file		CommonEnemy.h
* @brief	一般的な敵
* @author	Morita
* @date		2024/05/01
*/

#pragma once

#include "State/CommonEnemyStay.h"
#include "State/CommonEnemyVigilance.h"
#include "State/CommonEnemyCharge.h"
#include "State/CommonEnemyAttack.h"

#include "Library/Animation/AnimationManager.h"

#include "../EnemyInformation.h"

#include "CommonEnemyIntarface.h"

class CommonEnemy
{
public:

	//		コンストラクタ
	CommonEnemy(EnemyInformation enemyInformation);

	//		デストラクタ
	~CommonEnemy();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	*
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(timeSpeed)			時間の速度
	*/
	void Update(const DirectX::SimpleMath::Vector3& playerPosition,
		float timeSpeed);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();


public:

	enum State
	{
		Stay,		//		待機
		Vigilance,	//		警戒
		Charge,		//		チャージ
		Attack,		//		攻撃
	};

private:

	//		状態
	ICommonEnemy* m_istate;

	//		状態の情報
	std::unordered_map<State, std::unique_ptr<ICommonEnemy>> m_stateintarface;

	State m_state;

	//		プレイヤーアニメーション
	std::unique_ptr<AnimationManager> m_playerAnimation;

	//		情報
	std::unique_ptr<CommonEnemyIntarface> m_intarface;

	//		視界に入っているかどうか
	bool m_viewJudgement;

	//		エネミーの情報
	EnemyInformation m_enemyInformation;
public:

	/*
	*	状態を切り替える
	*
	*	@param	(nextState)	次の状態
	*/
	void ChangeState(State nextState)
	{
		//		同じ状態の場合処理をしない
		if (m_state == nextState) return;

		//現在の状態の終了処理
		m_istate->Finalize();

		//次の状態を切り替える
		m_state = nextState;

		//次の状態を切り替える
		m_istate = m_stateintarface[m_state].get();

		//次の状態の初期化処理
		m_istate->Initialize();
	}

	/*
	*	プレイヤーアニメーション
	*
	*	@return プレイヤーアニメーション
	*/
	AnimationManager* GetPlayerAnimation() { return m_playerAnimation.get(); }

	/*
	*	攻撃座標を受け取る
	*
	*	@return 座標
	*/
	DirectX::SimpleMath::Vector3 GetAttackPosition()
	{
		DirectX::SimpleMath::Vector3 attackPosition = m_intarface->GetPosition();

		attackPosition.y += 5.0f;

		return attackPosition;
	}

	/*
	*	情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	CommonEnemyIntarface* GetInformation() { return m_intarface.get(); }


	bool FieldOfVision();
};