/*
* @file		SlidingAnimationState.cpp
* @brief	スライディングのアニメーション
* @author	Morita
* @date		2024/06/25
*/

#include "pch.h"

#include "SlidingAnimationState.h"

#include "../../AnimationManager.h"


SlidingAnimationState::SlidingAnimationState(AnimationManager* PlayerAnimation)
	:
	m_elapsedTime(0.0f),
	m_animationTransration(0.0f),
	m_initialize(true),
	m_angle(0.0f),
	m_playerAnimation(PlayerAnimation)
{
}

SlidingAnimationState::~SlidingAnimationState()
{
}

void SlidingAnimationState::Initialize()
{
	m_animationTransration = 1.0f;

	m_elapsedTime = 0.0f;

	m_initialize = true;
}

void SlidingAnimationState::Update(float speed, DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Vector2 angle, float height,
	std::vector<PlayerBonsInformation>* bonesInformation)
{
	if (m_initialize)
	{
		m_angle = -angle.x + 180.0f - 10.0f;
		m_initialize = false;
	}

	(*bonesInformation)[BonsType::Body].position = position;
	(*bonesInformation)[BonsType::Body].position.y += height - 1.8f;

	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * Library::Lerp(0.0f, 20.0f, speed / 70.0f);

	DirectX::SimpleMath::Quaternion Body =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(m_angle),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion BodyDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(90.0f), DirectX::XMConvertToRadians(10.0f),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion LLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-45.0f),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion RLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-20.0f), DirectX::XMConvertToRadians(0.0f),
			DirectX::XMConvertToRadians(0.0f) });

	DirectX::SimpleMath::Quaternion RLegDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-90.0f), DirectX::XMConvertToRadians(-20.0f),
			DirectX::XMConvertToRadians(0.0f) });


	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(0.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(90.0f),DirectX::XMConvertToRadians(-90.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-45.0f),DirectX::XMConvertToRadians(0.0f) , 0.0f });

	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(0.0f),DirectX::XMConvertToRadians(0.0f) , 0.0f });


	m_animationTransration -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransration = Library::Clamp(m_animationTransration, 0.0f, 1.0f);

	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmUp, bonesInformation, LArmUp, (*bonesInformation)[BonsType::LArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmDown, bonesInformation, LArmDown, (*bonesInformation)[BonsType::LArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmUp, bonesInformation, RArmUp, (*bonesInformation)[BonsType::RArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmDown, bonesInformation, RArmDown, (*bonesInformation)[BonsType::RArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LLegUp, bonesInformation, LLegUp, (*bonesInformation)[BonsType::LLegUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RLegUp, bonesInformation, RLegUp, (*bonesInformation)[BonsType::RLegUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RLegDown, bonesInformation, RLegDown, (*bonesInformation)[BonsType::RLegDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::BodyDown, bonesInformation, BodyDown, (*bonesInformation)[BonsType::BodyDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::Body, bonesInformation, Body, (*bonesInformation)[BonsType::Body].rotation, m_animationTransration);
}

void SlidingAnimationState::Finalize()
{
}
