/*
* @file		ClockBackGround.cpp
* @brief	UI���v�̔w�i
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

	//		�����_�݂̂��擾����
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
	//		��]�s��̍쐻
	m_uiManager->GetStandardShader()->GetConsutBuffer()->rotationMatrix
		= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_rotation));

	//		�w�i�̕`��
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::ClockBackGround);

	//		��]�s��̏�����
	m_uiManager->GetStandardShader()->GetConsutBuffer()
		->rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		�R�����̕`��
	m_uiManager->GetStandardShader()->Render(UIManager::UIType::ClockColon);
}

void ClockBackGround::Finalize()
{
}
