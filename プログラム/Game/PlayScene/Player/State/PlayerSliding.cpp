/*
* @file		PlayerSliding.cpp
* @brief	プレイヤーのスライディング
* @author	Morita
* @date		2024/04/03
*/

#include "pch.h"

#include "PlayerSliding.h"

#include "../Player.h"

PlayerSliding::PlayerSliding(Player* player)
	:
	m_player(player),
	m_keyInputJudgement(false),
	m_firstSpeed(0.0f),
	m_speed(0.0f),
	m_slopeJudgement(false),
	m_decelerationSpeed(0.0f),
	m_firstHeight(0.0f),
	m_accelerationTime(0.0f)
{
}

PlayerSliding::~PlayerSliding()
{
}

void PlayerSliding::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		初期の速度
	m_speed = m_player->GetInformation()->GetAcceleration().Length() + INTIAL_VELOCITY;

	//		減速速度
	m_decelerationSpeed = m_player->GetInformation()->GetAcceleration().Length() / 3.0f * 2.0f;

	//		
	SlopeJudgement();

	//		スライディングをしている状態にする
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(true);

	//		頭を揺らす状態にしない
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	//		アニメーション待機状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Sliding);
}

void PlayerSliding::Update()
{

	//		移動処理
	MoveProcessing();

	//		メッシュと当たった時の処理
	m_player->GetCommonProcessing()->Gravity();

}

void PlayerSliding::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		頭を揺らす状態にしない
	m_player->GetInformation()->SetHeadShakingJudgement(false);

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,m_player->GetInformation()->GetSlidngHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerSliding::Animation()
{
	//		スライディングアニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerSliding::Render()
{
	//		速度
	LibrarySingleton::GetInstance()->DebugFont(L"Speed", m_slopeJudgement, 0, 150);
}

void PlayerSliding::Finalize()
{
	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	m_firstSpeed = 0.0f;

	m_speed = 0.0f;

	m_slopeJudgement = false;

	//		スライディングをしている状態にする
	m_player->GetPlayerInformationCollition()->SetSlidingJudgement(false);
}

void PlayerSliding::MoveProcessing()
{
	//		死亡しているか判断する
	m_player->DeathJudgement();

	//		現在坂かどうか
	SlopeJudgement();

	if (m_slopeJudgement)
	{
		//		加速度を受け取る
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetInformation()->GetAcceleration();

		m_acceleration.x += m_slidingVelocity.x * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();
		m_acceleration.z += m_slidingVelocity.y * SLIDING_ACCELERATION_SPEED * LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_acceleration.Length() > 80.0f)
		{
			m_acceleration.Normalize();

			m_acceleration *= 80.0f;
		}

		m_player->GetInformation()->SetAcceleration(m_acceleration);

		//		速度上限に達しているか判断する
		m_player->GetCommonProcessing()->SpeedUpperLimit();

		//		速度を設定する
		m_speed = m_player->GetInformation()->GetAcceleration().Length();

		//		減速速度
		m_decelerationSpeed = m_player->GetInformation()->GetAcceleration().Length() * 1.5f;

		//		座標に設定する
		m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
			m_player->GetInformation()->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());

	}
	else
	{
		if (m_accelerationTime <= 0.0f)
		{
			//		速度を遅くする
			m_speed -= m_decelerationSpeed *
				LibrarySingleton::GetInstance()->GetElpsedTime();
		}
		else
		{
			m_accelerationTime -= LibrarySingleton::GetInstance()->GetElpsedTime();
		}

		//		加速度を受け取る
		DirectX::SimpleMath::Vector3 m_acceleration = m_player->GetInformation()->GetAcceleration();

		//		加速方向を正規化
		m_acceleration.Normalize();

		//		速度を掛ける
		m_acceleration *= m_speed;

		//		加速度を設定する
		m_player->GetInformation()->SetAcceleration(m_acceleration);

		//		速度上限に達しているか判断する
		m_player->GetCommonProcessing()->SpeedUpperLimit();

		//		座標に設定する
		m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
			m_player->GetInformation()->GetAcceleration() *
			LibrarySingleton::GetInstance()->GetElpsedTime());
	}
}

void PlayerSliding::ChangeStateJudgement()
{
	DirectX::Keyboard::State keyState =
		LibrarySingleton::GetInstance()->
		GetKeyboardStateTracker()->GetLastState();

	//		ワイヤーを飛ぶことができるかどうか
	m_player->GetCommonProcessing()->WireActionJudgement();

	if (m_player->GetInformation()->GetAcceleration().Length() <= 10.0f)
	{
		//		状態を遷移する(しゃがみ状態)
		m_player->ChangeState(m_player->PlayerState::Crouching);
	}

	//		ゴールをしているかどうか
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GoalJudgement))
	{
		//		状態を切り替える（ゴール）
		m_player->ChangeState(m_player->PlayerState::Goal);
	}

	//		Lcontrolを離した場合
	if (keyState.IsKeyUp(DirectX::Keyboard::LeftControl))
	{
		//		状態を遷移する(移動状態)
		m_player->ChangeState(m_player->PlayerState::Walk);
	}

	//		キーボードの取得
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		spaceでジャンプ
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space))
	{
		//		状態を切り替える(しゃがみ)
		m_player->ChangeState(m_player->PlayerState::Jump);
	}
}

void PlayerSliding::SlopeJudgement()
{
	//		当たっている床の法線があるかどうか
	if (m_player->GetCollitionInformation()->GetFloorMeshHitNormalize().size() != 1)
	{
		m_slopeJudgement = false;

		return;
	}

	//		上向きのベクトルと床の法線の内積を取る
	float dot = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f).
		Dot(m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]);

	//		坂と判定する角度かどうか判断する
	if (dot >= 1.0f || dot < 0.2f)
	{
		m_slopeJudgement = false;

		return;
	}

	//		移動方向を受け取る
	DirectX::SimpleMath::Vector2 acc2 = { 
		m_player->GetInformation()->GetAcceleration().x,
		m_player->GetInformation()->GetAcceleration().z };

	//		坂の方向を計算する
	DirectX::SimpleMath::Vector3 downhill = m_player->GetCollitionInformation()->GetFloorMeshHitNormalize()[0]
											- DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	//		下り方向を二次元にする
	m_slidingVelocity = { downhill.x, downhill.z };

	//		正規化
	m_slidingVelocity.Normalize();

	//		内積が
	if (m_slidingVelocity.Dot(acc2) > 0.8f)
	{
		//		下り処理
		m_slopeJudgement = true;

		m_accelerationTime = 1.0f;

		return;
	}

	m_slopeJudgement = false;
}
