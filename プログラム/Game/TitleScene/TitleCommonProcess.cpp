/*
* @file		TitleCommonProcess.cpp
* @brief	�^�C�g�����ʏ���
* @author	Morita
* @date		2024/08/05
*/

#include "pch.h"

#include "TitleCommonProcess.h"

TitleCommonProcess::TitleCommonProcess(TitleInformation* information)
	:
	m_information(information),
	m_move(0.0f),
	m_size(0.0f),
	m_firstSize(0.0f),
	m_endSize(0.0f)
{
}

TitleCommonProcess::~TitleCommonProcess()
{
}

void TitleCommonProcess::MoveProcess(TitleInformation::MoveDirection moveDirection,
	bool direction, float time, TitleInformation::TitleUIType type)
{
	switch (moveDirection)
	{
	case TitleInformation::UP:
		CentreUP(direction, time, type);
		break;
	case TitleInformation::Down:
		CenterUnder(direction, time, type);
		break;
	case TitleInformation::Back:
		UPUnder(direction, time, type);
		break;
	default:
		break;
	}
}

void TitleCommonProcess::CentreUP(bool direction, float time, TitleInformation::TitleUIType type)
{
	//		�`�揇���Ō�ɂ���
	(*m_information->GetDraowOder())[2] = type;

	//		�ړ����������ď�����ς���
	if (direction)
	{
		m_firstPosition = m_information->CENTER_POINT;
		m_endPosition = m_information->UP_POINT;

		DecreaseValue(time);
	}
	else
	{
		m_firstPosition = m_information->UP_POINT;
		m_endPosition = m_information->CENTER_POINT;

		ElevatedValue(time);
	}

	DrawShader(type);
}

void TitleCommonProcess::CenterUnder(bool direction, float time, TitleInformation::TitleUIType type)
{
	//		�`�揇�𒆊Ԃɂ���
	(*m_information->GetDraowOder())[1] = type;

	//		�ړ����������ď�����ς���
	if (direction)
	{
		m_firstPosition = m_information->UNDER_POINT;
		m_endPosition = m_information->CENTER_POINT;

		ElevatedValue(time);
	}
	else
	{
		m_firstPosition = m_information->CENTER_POINT;
		m_endPosition = m_information->UNDER_POINT;

		DecreaseValue(time);
	}

	DrawShader(type);
}

void TitleCommonProcess::UPUnder(bool direction, float time, TitleInformation::TitleUIType type)
{
	//		�����T�C�Y
	m_firstSize = m_information->MIN_SCALE - 0.5f;
	//		�ŏI�T�C�Y
	m_endSize = m_information->MIN_SCALE;

	//		�`�揇���ŏ��ɂ���
	(*m_information->GetDraowOder())[0] = type;

	//		�ړ����������ď�����ς���
	if (direction)
	{
		m_firstPosition = m_information->UP_POINT;
		m_endPosition = m_information->UNDER_POINT;
	}
	else
	{
		m_firstPosition = m_information->UNDER_POINT;
		m_endPosition = m_information->UP_POINT;
	}

	m_move = time * time * time;

	float radian = Library::Lerp(0.0f, 360.0f, m_move);

	m_size = (cosf(DirectX::XMConvertToRadians(radian)) / 2.0f + 0.5f);

	m_size = Library::Clamp(m_size, 0.0f, 1.0f);

	DrawShader(type);
}

inline void TitleCommonProcess::DrawShader(TitleInformation::TitleUIType type)
{
	//		���W��ݒ肷��
	(*m_information->GetStandardShader()->GetUIInformation())[type].position = 
		DirectX::SimpleMath::Vector2::Lerp(m_firstPosition, m_endPosition, m_move);

	//		�T�C�Y��ݒ肷��
	(*m_information->GetStandardShader()->GetUIInformation())[type].scale = 
		DirectX::SimpleMath::Vector2::Lerp({ m_firstSize, m_firstSize }, { m_endSize, m_endSize }, m_size);
}

inline void TitleCommonProcess::DecreaseValue(float time)
{
	//		�ړ��̑J�ڗ�
	m_move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
	//		�T�C�Y�̑J�ڗ�
	m_size = 1.0f - sqrt(1.0f - pow(time, 2.0f));

	//		�����T�C�Y��ݒ�
	m_firstSize = m_information->MAX_SCALE;
	//		�ŏI�T�C�Y��ݒ�
	m_endSize = m_information->MIN_SCALE;
}

inline void TitleCommonProcess::ElevatedValue(float time)
{
	//		�ړ��̑J�ڗ�
	m_move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
	//		�T�C�Y�̑J�ڗ�
	m_size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

	//		�����T�C�Y��ݒ�
	m_firstSize = m_information->MIN_SCALE;
	//		�ŏI�T�C�Y��ݒ�
	m_endSize = m_information->MAX_SCALE;
}
