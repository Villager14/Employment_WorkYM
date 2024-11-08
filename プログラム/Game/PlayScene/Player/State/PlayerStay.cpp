/*
* @file		PlayerStay.cpp
* @brief	プレイヤーの待機状態
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerStay.h"

#include "../Player.h"

PlayerStay::PlayerStay(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f)
{
}

PlayerStay::~PlayerStay()
{
}

void PlayerStay::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		アニメーション待機状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Stay);
}

void PlayerStay::Update()
{
	//		減速
	Deceleration();

	//		メッシュと当たった時の処理
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerStay::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerStay::Animation()
{
	//		待機アニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(), 
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}


void PlayerStay::Render()
{
}

void PlayerStay::Finalize()
{
	m_time = 0.0f;

	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);
}

void PlayerStay::Deceleration()
{
	//		加速
	DirectX::SimpleMath::Vector3 acceleration = m_player->GetInformation()->GetAcceleration();

	//		減速
	acceleration *= 0.8f;

	m_player->GetInformation()->SetAcceleration(acceleration);

	//		速度と移動量を計算する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration()
		* LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerStay::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		キーボードステートの取得
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		ワイヤーアクションをするかどうか
	if (m_player->GetCommonProcessing()->WireActionJudgement())
	{
		return;
	}

	//		移動キーを押したとき
	if (keyboard.IsKeyPressed(DirectX::Keyboard::W) ||
		keyboard.IsKeyPressed(DirectX::Keyboard::A) ||
		keyboard.IsKeyPressed(DirectX::Keyboard::S) ||
		keyboard.IsKeyPressed(DirectX::Keyboard::D))
	{
		//		状態を切り替える（歩き)
		m_player->ChangeState(m_player->PlayerState::Walk);

		return;
	}

	//		ゴールをしているかどうか
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		状態を切り替える（ゴール）
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		spaceでジャンプ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space)&&
		m_player->GetInformation()->GetJumpJudgement())
	{
		//		状態を切り替える(しゃがみ)
		m_player->ChangeState(m_player->PlayerState::Jump);

		return;
	}

	//		LeftControlでしゃがみ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftControl))
	{
		//		状態を切り替える(しゃがみ)
		m_player->ChangeState(m_player->PlayerState::Crouching);

		return;
	}
}
