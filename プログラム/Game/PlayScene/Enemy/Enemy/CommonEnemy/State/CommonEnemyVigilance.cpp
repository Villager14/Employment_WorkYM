/*
* @file		CommonEnemyVigilance.h
* @brief	ˆê”Ê“I‚È“GŒx‰úó‘Ô
* @author	Morita
* @date		2024/05/01
*/

#include "pch.h"

#include "CommonEnemyVigilance.h"

#include "../CommonEnemy.h"

CommonEnemyVigilance::CommonEnemyVigilance(CommonEnemy* commonEnemy)
	:
	m_commonEnemy(commonEnemy),
	m_coolTime(0.0f)
{
}

CommonEnemyVigilance::~CommonEnemyVigilance()
{
}

void CommonEnemyVigilance::Initialize()
{
	m_commonEnemy->GetPlayerAnimation()->ChangeState(AnimationManager::HandGunStyleA);
}

void CommonEnemyVigilance::Update()
{
	DirectX::SimpleMath::Vector3 velocity = m_commonEnemy->GetInformation()->GetPlayerPosition() - m_commonEnemy->GetInformation()->GetPosition();
	
	DirectX::SimpleMath::Vector3 angleVelocity = DirectX::SimpleMath::Vector3
	(sinf(m_commonEnemy->GetInformation()->GetRotation()), 0.0f, cosf(m_commonEnemy->GetInformation()->GetRotation()));

	DirectX::SimpleMath::Vector3 move = velocity - angleVelocity;

	angleVelocity += move * 0.1f * m_commonEnemy->GetInformation()->GetTimeSpeed() * LibrarySingleton::GetInstance()->GetElpsedTime();

	m_commonEnemy->GetInformation()->SetRotation(atan2(angleVelocity.x, angleVelocity.z));

	m_commonEnemy->GetPlayerAnimation()->Execute(0.0f,
		m_commonEnemy->GetInformation()->GetPosition(),
		{ 0.0f, DirectX::XMConvertToDegrees(m_commonEnemy->GetInformation()->GetRotation()) },
		4.4f);
}

void CommonEnemyVigilance::Render()
{
	m_commonEnemy->GetPlayerAnimation()->Render();
}

void CommonEnemyVigilance::Finalize()
{
	m_coolTime = 0.0f;
}
