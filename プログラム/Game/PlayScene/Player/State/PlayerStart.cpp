/*
* @file		PlayerStart.cpp
* @brief	�v���C���[�̃X�^�[�g���
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
	//		���X�|�[�����W���󂯎��
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetRespawnPosition());

	m_player->GetInformation()->SetPlayerHeight({
		m_player->GetInformation()->GetPosition().x,
		m_player->GetInformation()->GetPosition().y + m_player->GetInformation()->GetStandingHeight(),
		m_player->GetInformation()->GetPosition().z});

	//		�A�j���[�V�����X�^�[�g
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Start);
	
	//		���j���[���g���Ȃ��悤�ɂ���
	m_player->SetMenuUiseJudgement(false);
}

void PlayerStart::Update()
{
}

void PlayerStart::Move()
{
	//		��ԑJ�ڔ��f
	ChangeStateJudgement();
}

void PlayerStart::Animation()
{
	//		�ҋ@�A�j���[�V����
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
	//		���j���[���g���Ȃ��悤�ɂ���
	m_player->SetMenuUiseJudgement(true);
}

void PlayerStart::ChangeStateJudgement()
{
	//		�J�����̉��o���I�������
	if (m_player->GetGameManager()->FlagJudgement(GameManager::GameStart))
	{
		//		��Ԃ�J�ڂ���i�ҋ@��ԁj
		m_player->ChangeState(m_player->PlayerState::Stay);
	}
}
