/*
* @file		CommonEnemyStay.cpp
* @brief	��ʓI�ȓG�ҋ@���
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemyStay.h"

#include "../CommonEnemy.h"

CommonEnemyStay::CommonEnemyStay(CommonEnemy* commonEnemy)
	:
	m_commonEnemy(commonEnemy)
{
}

CommonEnemyStay::~CommonEnemyStay()
{
}

void CommonEnemyStay::Initialize()
{
}

void CommonEnemyStay::Update()
{
	//		�A�j���[�V�����̍X�V
	m_commonEnemy->GetPlayerAnimation()->Execute(0.0f,
		m_commonEnemy->GetInformation()->GetPosition(),
		{ 0.0f, DirectX::XMConvertToDegrees(m_commonEnemy->GetInformation()->GetRotation()) },
		4.4f);

	//		������ɓ������ꍇ
	if (m_commonEnemy->FieldOfVision())
	{
		//		��Ԃ�J�ڂ���
		m_commonEnemy->ChangeState(CommonEnemy::State::Vigilance);
	}
}

void CommonEnemyStay::Render()
{
	m_commonEnemy->GetPlayerAnimation()->Render();
}

void CommonEnemyStay::Finalize()
{
}
