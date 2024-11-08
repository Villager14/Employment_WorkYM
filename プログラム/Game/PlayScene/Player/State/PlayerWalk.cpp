/*
* @file		PlayerWalk.cpp
* @brief	プレイヤーの歩き状態
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerWalk.h"

#include "../Player.h"

PlayerWalk::PlayerWalk(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_accelerationJudgement(false)
{
}

PlayerWalk::~PlayerWalk()
{
}

void PlayerWalk::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		現在の速度を受け取る
	m_speed = m_player->GetInformation()->GetAcceleration().Length();

	//		歩く速度より遅い場合は歩く速度を最大速度にする
	if (m_speed < m_player->GetInformation()->GetWalkSpeed())
	{
		//		加速処理をする
		m_accelerationJudgement = true;
	}

	//		アニメーション歩き状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Walk);
}

void PlayerWalk::Update()
{
	//		移動処理
	MoveProcessing();

	//		メッシュと当たった時の処理
	m_player->GetCommonProcessing()->Gravity();
}

void PlayerWalk::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		床に当たっているか
	if (!m_player->GetCommonProcessing()->FloorMeshHitJudgement())
	{
		//		状態を遷移する(落下)
		m_player->ChangeState(m_player->PlayerState::Fall);
	}

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());
	
	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerWalk::Animation()
{
	//		歩きアニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerWalk::Render()
{
}

void PlayerWalk::Finalize()
{
	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_speed = 0.0f;

	m_accelerationJudgement = false;
}

void PlayerWalk::MoveProcessing()
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
	}

	//		加速処理にするかどうか
	if (m_accelerationJudgement)
	{
		AccelerationProcess();
	}

	//		加速度を計算する
	DirectX::SimpleMath::Vector3 accelaration = m_player->GetCommonProcessing()->MoveDirection(
		m_player->GetInformation()->GetDirection()) * m_speed;

	//		加速度を設定する
	m_player->GetInformation()->SetAcceleration(accelaration);

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration() * LibrarySingleton::GetInstance()->GetElpsedTime());
}

void PlayerWalk::ChangeStateJudgement()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		キーが押されていない場合
	if (!m_keyInputJudgement)
	{
		//		状態を遷移する(待機状態)
		m_player->ChangeState(m_player->PlayerState::Stay);
	}

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	DirectX::Keyboard::State keyState = LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState();
	
	//		spaceでジャンプ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space)&&
		m_player->GetInformation()->GetJumpJudgement())
	{
		//		状態を切り替える(ジャンプ)
		m_player->ChangeState(m_player->PlayerState::Jump);
	}

	//		ゴールをしているかどうか
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		状態を切り替える（ゴール）
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		ワイヤーを飛ぶことができるかどうか
	m_player->GetCommonProcessing()->WireActionJudgement();

	//		Controlでしゃがみ
	if (keyState.IsKeyDown(DirectX::Keyboard::LeftControl))
	{
		if (m_player->GetInformation()->GetAcceleration().Length() < m_player->GetInformation()->GetCrouchingSpeed())
		{
			//		状態を切り替える(歩き)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
		else
		{
			//		状態を切り替える(スライディング)
			m_player->ChangeState(m_player->PlayerState::Sliding);
		}
	}

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift)
		&& keyState.IsKeyDown(DirectX::Keyboard::W))
	{
		//		ダッシュできるかどうか
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->PlayerState::Dash);
		}
	}
}

void PlayerWalk::AccelerationProcess()
{
	//		速度に加速度を足す
	m_speed += ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		歩く速度を超えた場合処理加速処理を終了する
	if (m_speed > m_player->GetInformation()->GetWalkSpeed())
	{
		//		速度を歩く速度にする
		m_speed = m_player->GetInformation()->GetWalkSpeed();

		//		加速処理の終了フラグ
		m_accelerationJudgement = false;
	}
}
