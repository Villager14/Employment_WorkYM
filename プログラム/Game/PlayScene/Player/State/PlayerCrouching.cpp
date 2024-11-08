/*
* @file		PlayerCrouching.cpp
* @brief	プレイヤーのしゃがみ状態
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerCrouching.h"

#include "../Player.h"

PlayerCrouching::PlayerCrouching(Player* player)
	:
	m_player(player),
	m_firstHeight(0.0f),
	m_keyInputJudgement(false)
{
}

PlayerCrouching::~PlayerCrouching()
{
}

void PlayerCrouching::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;
}

void PlayerCrouching::Update()
{
	//		移動処理
	MoveProcessing();

	//		メッシュと当たった時の処理
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerCrouching::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		しゃがみ高さにする処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetCrouchingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerCrouching::Animation()
{
	if (m_keyInputJudgement)
	{
		//		歩き状態
		m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->CrouchingWalk);

	}
	else
	{
		//		しゃがみ停止アニメーション
		m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->CrouchingStay);
	}

	//		しゃがみ歩きアニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerCrouching::Render()
{
}

void PlayerCrouching::Finalize()
{
	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_firstHeight = 0.0f;
}

void PlayerCrouching::MoveProcessing()
{
	//		キーを押しているかどうか
	m_keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->GetCommonProcessing()->Direction(&m_keyInputJudgement);

	//		正規化
	direction.Normalize();

	//		キーが押されている状態の場合
	if (m_keyInputJudgement)
	{
		//		移動する方向を設定する
		m_player->GetInformation()->SetDirection(direction);

		//		速度処理
		SpeedProcessing();
	}
	else
	{
		m_player->GetInformation()->SetAcceleration(
			m_player->GetInformation()->GetAcceleration() * 0.8f);
	}

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(
		m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerCrouching::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		キーボードステートの取得
	DirectX::Keyboard::State keyboardState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();

	//		ゴールをしているかどうか
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		状態を切り替える（ゴール）
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		ワイヤーを飛ぶことができるかどうか
	m_player->GetCommonProcessing()->WireActionJudgement();

	//		キーを離した場合
	if (keyboard.IsKeyReleased(DirectX::Keyboard::LeftControl))
	{
		//		移動キーが押されている場合
		if (keyboardState.IsKeyDown(DirectX::Keyboard::W) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::A) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::S) ||
			keyboardState.IsKeyDown(DirectX::Keyboard::D))
		{
			//		状態を遷移する(歩き状態)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
		else
		{
			//		状態を遷移する(待機状態)
			m_player->ChangeState(m_player->PlayerState::Stay);
		}
	}
}

void PlayerCrouching::SpeedProcessing()
{
	//		加速度を受け取る
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetInformation()->GetAcceleration();

	//		加速度の処理
	accelaration += m_player->GetCommonProcessing()->MoveDirection(m_player->GetInformation()->GetDirection())
		* 2000.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		もし歩きの速さより早くなった場合
	if (accelaration.Length() > m_player->GetInformation()->GetCrouchingSpeed())
	{
		//		正規化
		accelaration.Normalize();

		//		加速度に歩きの速さを掛ける
		accelaration *= m_player->GetInformation()->GetCrouchingSpeed();
	}

	//		加速度を設定する
	m_player->GetInformation()->SetAcceleration(accelaration);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(
		m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime()
	);
}