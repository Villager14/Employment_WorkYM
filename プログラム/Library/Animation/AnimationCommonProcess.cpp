/*
* @file		AnimationCommonProcess.cpp
* @brief	アニメーションの共通処理
* @author	Morita
* @date		2024/08/25
*/

#include "pch.h"

#include "AnimationCommonProcess.h"

#include "AnimationManager.h"

AnimationCommonProcess::AnimationCommonProcess(AnimationManager* animationManager)
	:
	m_animationManager(animationManager)
{
}

AnimationCommonProcess::~AnimationCommonProcess()
{
}

void AnimationCommonProcess::AnimationMovement(BonsType type, 
	std::vector<PlayerBonsInformation>* bonesInformation,
	DirectX::SimpleMath::Quaternion firstVal,
	DirectX::SimpleMath::Quaternion endVal,
	float transrationSpeed)
{
	if (transrationSpeed >= 0.0f)
		(*bonesInformation)[type].rotation = DirectX::SimpleMath::Quaternion::Lerp(firstVal, endVal, transrationSpeed);
	else
		(*bonesInformation)[type].rotation = firstVal;
}

void AnimationCommonProcess::AnimationLegInitialValue(
	std::vector<PlayerBonsInformation>* bonesInformation,
	float transrationSpeed)
{
	AnimationMovement(BonsType::LLegUp, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::LLegUp].rotation, transrationSpeed);
	AnimationMovement(BonsType::LLegDown, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::LLegDown].rotation, transrationSpeed);
	AnimationMovement(BonsType::RLegDown, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::RLegDown].rotation, transrationSpeed);
	AnimationMovement(BonsType::RLegUp, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::RLegUp].rotation, transrationSpeed);
	AnimationMovement(BonsType::BodyDown, bonesInformation, DirectX::SimpleMath::Quaternion::Identity, (*bonesInformation)[BonsType::BodyDown].rotation, transrationSpeed);
}

void AnimationCommonProcess::Landing(float height)
{
	//		落下時間を受け取る
	float landingTime = m_animationManager->GetInformation()->GetLandingTime();

	landingTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.0f;

	landingTime = Library::Clamp(landingTime, 0.0f, 1.0f);

	m_animationManager->GetInformation()->SetLandingTime(landingTime);

	float val = sinf(DirectX::XMConvertToRadians(Library::Lerp(0.0f, 180.0f, landingTime)));

	float lo = Library::Lerp(0.0f, -0.2f, val);

	(*m_animationManager->GetBons()->GetBonesInformation())[BonsType::Body].position.y += height - 1.8f + lo;

	if (landingTime >= 1.0f)
	{
		//		落下状態を終了する
		m_animationManager->GetInformation()->SetFallJudgement(false);
	}
}
