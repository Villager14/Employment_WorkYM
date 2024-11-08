/*
* @file		CommonEnemyStay.cpp
* @brief	一般的な敵待機状態
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
	//		アニメーションの更新
	m_commonEnemy->GetPlayerAnimation()->Execute(0.0f,
		m_commonEnemy->GetInformation()->GetPosition(),
		{ 0.0f, DirectX::XMConvertToDegrees(m_commonEnemy->GetInformation()->GetRotation()) },
		4.4f);

	//		視野内に入った場合
	if (m_commonEnemy->FieldOfVision())
	{
		//		状態を遷移する
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
