/*
* @file		PlayerStart.cpp
* @brief	プレイヤーのスタート状態
* @author	Morita
* @date		2024/05/21
*/

#include "pch.h"

#include "PlayerStart.h"

#include "../Player.h"

PlayerStart::PlayerStart(Player* player)
	:
	m_player(player)
{
}

PlayerStart::~PlayerStart()
{
}

void PlayerStart::Initialize()
{
	//		リスポーン座標を受け取る
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetRespawnPosition());

	m_player->GetInformation()->SetPlayerHeight({
		m_player->GetInformation()->GetPosition().x,
		m_player->GetInformation()->GetPosition().y + m_player->GetInformation()->GetStandingHeight(),
		m_player->GetInformation()->GetPosition().z});

	//		アニメーションスタート
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Start);
	
	//		メニューを使えないようにする
	m_player->SetMenuUiseJudgement(false);
}

void PlayerStart::Update()
{
}

void PlayerStart::Move()
{
	//		状態遷移判断
	ChangeStateJudgement();
}

void PlayerStart::Animation()
{
	//		待機アニメーション
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerStart::Render()
{
}

void PlayerStart::Finalize()
{
	//		メニューを使えないようにする
	m_player->SetMenuUiseJudgement(true);
}

void PlayerStart::ChangeStateJudgement()
{
	//		カメラの演出が終わったら
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GameStart))
	{
		//		状態を遷移する（待機状態）
		m_player->ChangeState(m_player->PlayerState::Stay);
	}
}
