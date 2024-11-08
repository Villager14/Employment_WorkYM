/*
* @file		PlayerFall.cpp
* @brief	プレイヤーの落下状態
* @author	Morita
* @date		2024/07/19
*/

#include "pch.h"

#include "PlayerFall.h"

#include "../Player.h"

PlayerFall::PlayerFall(Player* player)
	:
	m_player(player),
	m_firstHeight(0.0f),
	m_speed(0.0f),
	m_rayHitJudgement(false),
	m_keyInputJudgement(false)
{
}

PlayerFall::~PlayerFall()
{
}

void PlayerFall::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		アニメーション待機状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Fall);

	//		現在の速度を受け取る
	m_speed = m_player->GetInformation()->GetAcceleration().Length();

	//		カメラの回転量を受け取る
	m_cameraMatrix = DirectX::SimpleMath::Matrix::CreateRotationY
	(DirectX::XMConvertToRadians(m_player->GetInformation()->GetCameraAngle().x));

}

void PlayerFall::Update()
{
	MoveProcess();

	//		メッシュと当たった時の処理
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerFall::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

			//		当たった場所がなければ処理をしない
	if (m_player->GetCollitionInformation()->GetFloorMeshHitPoint().size() != 0)
	{
		if (abs(m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y -
			m_player->GetInformation()->GetPlanPosition().y) < 1.0f)
		{
			DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPlanPosition();

			position.y = m_player->GetCollitionInformation()->GetFloorMeshHitPoint()[0].y;

			m_player->GetInformation()->SetPlanPosition(position);

			m_player->GetInformation()->SetFallTime(0.0f);

			m_rayHitJudgement = true;
		}
	}


	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerFall::Animation()
{
	//		待機アニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(), 
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}


void PlayerFall::Render()
{
}

void PlayerFall::Finalize()
{
	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_speed = 0.0f;

	m_rayHitJudgement = false;

	m_keyInputJudgement = false;
}

void PlayerFall::ChangeStateJudgement()
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

	//		床に当たっている時
	if (m_rayHitJudgement)
	{
		//		キーが押されていない場合
		if (!m_keyInputJudgement)
		{
			//		状態を遷移する(待機状態)
			m_player->ChangeState(m_player->PlayerState::Stay);
		}
		else if (keyboardState.IsKeyDown(DirectX::Keyboard::LeftControl))
		{
			//		状態を遷移する(スライディング)
			m_player->ChangeState(m_player->PlayerState::Sliding);
		}
		else
		{
			//		状態を切り替える(歩き状態)
			m_player->ChangeState(m_player->PlayerState::Walk);
		}
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

	if (keyboard.IsKeyPressed(DirectX::Keyboard::LeftShift)
		&& keyboardState.IsKeyDown(DirectX::Keyboard::W))
	{
		//		ダッシュできるかどうか
		if (m_player->GetInformation()->GetDashJudgement())
		{
			//		状態を切り替える(ダッシュ)
			m_player->ChangeState(m_player->PlayerState::Dash);
		}
	}
}

void PlayerFall::MoveProcess()
{
	//		キーを押しているかどうか
	m_keyInputJudgement = false;

	//		移動する向き
	DirectX::SimpleMath::Vector3 direction =
		DirectX::SimpleMath::Vector3::Zero;

	//		移動する方向を受け取る
	direction = m_player->GetCommonProcessing()->Direction(&m_keyInputJudgement);

	//		移動する方向を設定する
	m_player->GetInformation()->SetDirection(direction);

	DirectX::SimpleMath::Vector3 acceleation = m_player->GetInformation()->GetAcceleration();

	acceleation += DirectX::SimpleMath::Vector3::Transform(
		direction, m_cameraMatrix.Invert()) * 60.0f * LibrarySingleton::GetInstance()->GetElpsedTime();

	if (acceleation.Length() > m_speed)
	{
		acceleation.Normalize();

		acceleation *= m_speed;
	}

	m_player->GetInformation()->SetAcceleration(acceleation);

	DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPosition();

	position.y = m_player->GetInformation()->GetPlanPosition().y;

	//		座標に設定する
	m_player->GetInformation()->SetPlanPosition(position +
		m_player->GetInformation()->GetAcceleration() *
		LibrarySingleton::GetInstance()->GetElpsedTime());
}
