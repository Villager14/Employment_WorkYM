/*
* @file		ClockBackGround.cpp
* @brief	UIŒv‚Ì”wŒi
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockBackGround.h"

ClockBackGround::ClockBackGround(UIManager* uiManager)
	:
	m_rotationMax(ROTATION_RADIAN),
	m_rotationMin(0.0f),
	m_pastTime(0.0f),
	m_uiManager(uiManager),
	m_rotation(0.0f)
{
}

ClockBackGround::~ClockBackGround()
{
}

void ClockBackGround::Initialize()
{

}

void ClockBackGround::Update(float elapsedTime)
{
	float time = elapsedTime;

	//		¬”“_‚Ì‚İ‚ğæ“¾‚·‚é
	int integer = static_cast<int>(elapsedTime);

	time -= static_cast<float>(integer);

	if (m_pastTime > time)
	{
		m_rotationMin += ROTATION_RADIAN;
		m_rotationMax += ROTATION_RADIAN;
	}

	float move = 0.0f;
	
	if (time == 0.0f)
	{
		move = 0.0f;
	}
	else
	{
		move = pow(2.0f, 10.0f * time - 10.0f);
	}
	
	m_rotation = Library::Lerp(m_rotationMin, m_rotationMax, move);

	m_pastTime = time;
}

void ClockBackGround::Render()
{
	//		‰ñ“]s—ñ‚Ìì»
	m_uiManager->GetStandardShader()->GetConsutBuffer()->rotationMatrix
		= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation));

	//		”wŒi‚Ì•`‰æ
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::ClockBackGround);

	//		‰ñ“]s—ñ‚Ì‰Šú‰»
	m_uiManager->GetStandardShader()->GetConsutBuffer()
		->rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ƒRƒƒ“‚Ì•`‰æ
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::ClockColon);
}

void ClockBackGround::Finalize()
{
}
