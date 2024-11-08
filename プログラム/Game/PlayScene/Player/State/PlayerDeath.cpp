/*
* @file		PlayerDeath.cpp
* @brief	プレイヤーの死亡状態
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerDeath.h"

#include "../Player.h"

PlayerDeath::PlayerDeath(Player* player)
	:
	m_player(player),
	m_time(0.0f),
	m_firstHeight(0.0f),
	m_slowTime(0.0f),
	m_firstGravity(0.0f)
{
}

PlayerDeath::~PlayerDeath()
{
}

void PlayerDeath::Initialize()
{
	//		プレイヤーの高さを受け取る
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		加速度を受け取る
	m_firstAcceleration = m_player->GetInformation()->GetAcceleration();

	//		重力を受け取る
	m_firstGravity = m_player->GetInformation()->GetGravity();

	//		死亡状態にする
	m_player->GetGameManager()->TrueFlag(GameManager::DeathJudgement);

	//		死亡回数を増やす
	m_player->GetGameManager()->SetDeathCount(m_player->GetGameManager()->GetDeathCount() + 1);

	//		アニメーションジャンプ状態
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Death);
}

void PlayerDeath::Update()
{
	//		減速
	Deceleration();
}

void PlayerDeath::Move()
{
	//		壁メッシュの当たり判定
	m_player->GetCommonProcessing()->WallMeshHitJudgement();

	//		床に当たっているか
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		移動予定座標からプレイヤー座標に代入する
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		立つ処理
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight,
		m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerDeath::Animation()
{
	//		待機アニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerDeath::Render()
{
}

void PlayerDeath::Finalize()
{
	m_time = 0.0f;

	m_player->GetInformation()->SetDirection(DirectX::SimpleMath::Vector3::Zero);

	//		高さ変動時間の初期化
	m_player->GetInformation()->SetHeightTime(0.0f);

	//		プレイヤーの座標をリセットする
	m_player->GetInformation()->SetPosition({ 0.0f, 0.0f, 0.0f });
	m_player->GetInformation()->SetPlanPosition({ 0.0f, 0.0f, 0.0f });

	//		立つ処理
	m_player->GetInformation()->SetPlayerHeight({m_player->GetInformation()->GetPosition().x,
												 m_player->GetInformation()->GetPosition().y + 7.0f,
												 m_player->GetInformation()->GetPosition().z});
	m_player->GetInformation()->SetGravity(0.0f);
	m_player->GetInformation()->SetFallTime(0.0f);

	//		死亡状態を解除する
	m_player->GetGameManager()->FalseFlag(GameManager::DamageObjectHit);
	m_player->GetGameManager()->FalseFlag(GameManager::FallDead);
	//		ゲームの速度を元に戻す
	m_player->GetGameManager()->SetGameSpeed(1.0f);
}

void PlayerDeath::Deceleration()
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	if (m_time >= 1.0f) return;

	m_slowTime = 1.0f - pow(1 - m_time, 4.0f);

	DirectX::SimpleMath::Vector3 acceleration = DirectX::SimpleMath::Vector3::Lerp
	(m_firstAcceleration, DirectX::SimpleMath::Vector3::Zero, m_slowTime);

	m_player->GetInformation()->SetAcceleration(acceleration);

	//		速度と移動量を計算する
	m_player->GetInformation()->SetPlanPosition(m_player->GetInformation()->GetPosition() +
		m_player->GetInformation()->GetAcceleration()
		* LibrarySingleton::GetInstance()->GetElpsedTime());

	float gravity = Library::Lerp(m_firstGravity, 0.0f, m_slowTime);

	DirectX::SimpleMath::Vector3 position = m_player->GetInformation()->GetPlanPosition();

	position.y -= gravity * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_player->GetInformation()->SetPlanPosition(position);

	//		ゲームの速度を遅くする
	m_player->GetGameManager()->SetGameSpeed(Library::Lerp(1.0f, 0.1f, m_slowTime));
}

void PlayerDeath::ChangeStateJudgement()
{
	//		死亡状態が解除されば場合
	if (!m_player->GetGameManager()->FlagJudgement(GameManager::DeathJudgement))
	{
		//		復活状態にする
		m_player->ChangeState(m_player->PlayerState::Start);
	}
}
