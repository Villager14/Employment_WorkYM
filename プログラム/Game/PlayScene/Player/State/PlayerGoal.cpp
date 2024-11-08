/*
* @file		PlayerGoal.h
* @brief	�v���C���[�S�[�����
* @author	Morita
* @date		2024/05/27
*/

#include "pch.h"

#include "PlayerGoal.h"

#include "../Player.h"

PlayerGoal::PlayerGoal(Player* player)
	:
	m_player(player),
	m_firstHeight(0.0f)
{
}

PlayerGoal::~PlayerGoal()
{
}

void PlayerGoal::Initialize()
{

		//		�v���C���[�̍������󂯎��
	m_firstHeight = m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y;

	//		�A�j���[�V�����������
	m_player->GetAnimation()->ChangeState(m_player->GetAnimation()->Upright);

	//		���j���[���g���Ȃ��悤�ɂ���
	m_player->SetMenuUiseJudgement(false);

	//		�����x���O�ɂȂ�
	m_player->GetInformation()->SetAcceleration(DirectX::SimpleMath::Vector3::Zero);
}

void PlayerGoal::Update()
{
	//		���b�V���Ɠ����������̏���
	m_player->GetCommonProcessing()->Gravity();
}

void PlayerGoal::Move()
{
	//		���ɓ������Ă��邩
	m_player->GetCommonProcessing()->FloorMeshHitJudgement();

	//		�ړ��\����W����v���C���[���W�ɑ������
	m_player->GetInformation()->SetPosition(m_player->GetInformation()->GetPlanPosition());

	//		������
	m_player->GetCommonProcessing()->PlayerHeightTransition(m_firstHeight, m_player->GetInformation()->GetStandingHeight(), 3.0f);

	//		�V�[����؂�ւ��邩�ǂ���
	ChangeSceneJudgement();
}

void PlayerGoal::Animation()
{
	//		�ҋ@�A�j���[�V����
	m_player->GetAnimation()->Execute(
		m_player->GetInformation()->GetAcceleration().Length(),
		m_player->GetInformation()->GetPosition(),
		m_player->GetCameraInformation()->GetAngle(),
		m_player->GetInformation()->GetPlayerHeight().y - m_player->GetInformation()->GetPosition().y);
}

void PlayerGoal::Render()
{
}

void PlayerGoal::Finalize()
{
}

void PlayerGoal::ChangeSceneJudgement()
{
	//		�L�[�{�[�h�̎擾
	DirectX::Keyboard::KeyboardStateTracker keyboard = *LibrarySingleton::GetInstance()->GetKeyboardStateTracker();

	//		�}�E�X�̎擾
	DirectX::Mouse::ButtonStateTracker mouse = *LibrarySingleton::GetInstance()->GetButtonStateTracker();

	//		Space�܂��͍��N���b�N���������ꍇ��������
	if (keyboard.IsKeyPressed(DirectX::Keyboard::Space) ||
		mouse.leftButton == DirectX::Mouse::ButtonStateTracker::PRESSED)
	{
		//		���U���g�V�[����
		m_player->GetGameManager()->TrueFlag(GameManager::EndJudgement);
	}
}
