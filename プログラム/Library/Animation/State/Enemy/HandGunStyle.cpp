/*
* @file		HandGunStyle.h
* @brief	ƒnƒ“ƒhƒKƒ“\‚¦‚ÌƒAƒjƒ[ƒVƒ‡ƒ“
* @author	Morita
* @date		2024/08/27
*/

#include "pch.h"

#include "HandGunStyle.h"

#include "../../AnimationManager.h"

HandGunStyle::HandGunStyle(AnimationManager* PlayerAnimation)
	:
	m_elapsedTime(0.0f),
	m_animationTransration(0.0f),
	m_playerAnimation(PlayerAnimation)
{
}

HandGunStyle::~HandGunStyle()
{
}

void HandGunStyle::Initialize()
{
	m_animationTransration = 1.0f;

	m_elapsedTime = 0.0f;
}

void HandGunStyle::Update(float speed, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector2 angle, float height, std::vector<PlayerBonsInformation>* bonesInformation)
{
	UNREFERENCED_PARAMETER(speed);

	(*bonesInformation)[BonsType::Body].position = position;
	(*bonesInformation)[BonsType::Body].position.y += height - 1.8f;
	(*bonesInformation)[BonsType::Body].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f, DirectX::XMConvertToRadians(angle.y + 180.0f), 0.0f });

	(*bonesInformation)[BonsType::BodyDown].rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ 0.0f,DirectX::XMConvertToRadians(-40.0f), 0.0f });

	DirectX::SimpleMath::Quaternion LLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(20.0f),
			  DirectX::XMConvertToRadians(45.0f),
			  0.0f });

	DirectX::SimpleMath::Quaternion LLegDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-20.0f),
			  DirectX::XMConvertToRadians(0.0f),
			  0.0f });

	DirectX::SimpleMath::Quaternion RLegUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(20.0f),
			  DirectX::XMConvertToRadians(0.0f),
			  0.0f });

	DirectX::SimpleMath::Quaternion RLegDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(-20.0f),
			  DirectX::XMConvertToRadians(0.0f),
			  0.0f });

	DirectX::SimpleMath::Quaternion LArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(80.0f),
			  DirectX::XMConvertToRadians(-20.0f),
			  0.0f });

	DirectX::SimpleMath::Quaternion  LArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(10.0f),
			  DirectX::XMConvertToRadians(0.0f),
			  DirectX::XMConvertToRadians(0.0f) });

	//		‰E˜rã‚Ì‰ñ“]
	DirectX::SimpleMath::Quaternion RArmUp =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(80.0f),
			  DirectX::XMConvertToRadians(20.0f),
			  0.0f });

	//		‰E˜r‰º‚Ì‰ñ“]
	DirectX::SimpleMath::Quaternion RArmDown =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(10.0f),
			  DirectX::XMConvertToRadians(0.0f),
			  DirectX::XMConvertToRadians(0.0f) });

	//		e‚Ì‰ñ“]
	DirectX::SimpleMath::Quaternion gun =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			{ DirectX::XMConvertToRadians(0.0f),
			  DirectX::XMConvertToRadians(0.0f),
			  DirectX::XMConvertToRadians(20.0f) });

	m_animationTransration -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

	m_animationTransration = Library::Clamp(m_animationTransration, 0.0f, 1.0f);

	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmUp, bonesInformation, LArmUp, (*bonesInformation)[BonsType::LArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LArmDown, bonesInformation, LArmDown, (*bonesInformation)[BonsType::LArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmUp, bonesInformation, RArmUp, (*bonesInformation)[BonsType::RArmUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RArmDown, bonesInformation, RArmDown, (*bonesInformation)[BonsType::RArmDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::Gun, bonesInformation, gun, (*bonesInformation)[BonsType::Gun].rotation, m_animationTransration);
	
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LLegUp, bonesInformation, LLegUp, (*bonesInformation)[BonsType::LLegUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::LLegDown, bonesInformation, LLegDown, (*bonesInformation)[BonsType::LLegDown].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RLegUp, bonesInformation, RLegUp, (*bonesInformation)[BonsType::RLegUp].rotation, m_animationTransration);
	m_playerAnimation->GetCommonProcess()->AnimationMovement(BonsType::RLegDown, bonesInformation, RLegDown, (*bonesInformation)[BonsType::RLegDown].rotation, m_animationTransration);
}

void HandGunStyle::Finalize()
{
}
