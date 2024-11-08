/*
* @file		TitleCommonProcess.cpp
* @brief	タイトル共通処理
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
	//		描画順を最後にする
	(*m_information->GetDraowOder())[2] = type;

	//		移動方向を見て処理を変える
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
	//		描画順を中間にする
	(*m_information->GetDraowOder())[1] = type;

	//		移動方向を見て処理を変える
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
	//		初期サイズ
	m_firstSize = m_information->MIN_SCALE - 0.5f;
	//		最終サイズ
	m_endSize = m_information->MIN_SCALE;

	//		描画順を最初にする
	(*m_information->GetDraowOder())[0] = type;

	//		移動方向を見て処理を変える
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
	//		座標を設定する
	(*m_information->GetStandardShader()->GetUIInformation())[type].position = 
		DirectX::SimpleMath::Vector2::Lerp(m_firstPosition, m_endPosition, m_move);

	//		サイズを設定する
	(*m_information->GetStandardShader()->GetUIInformation())[type].scale = 
		DirectX::SimpleMath::Vector2::Lerp({ m_firstSize, m_firstSize }, { m_endSize, m_endSize }, m_size);
}

inline void TitleCommonProcess::DecreaseValue(float time)
{
	//		移動の遷移量
	m_move = sqrt(1.0f - pow(time - 1.0f, 2.0f));
	//		サイズの遷移量
	m_size = 1.0f - sqrt(1.0f - pow(time, 2.0f));

	//		初期サイズを設定
	m_firstSize = m_information->MAX_SCALE;
	//		最終サイズを設定
	m_endSize = m_information->MIN_SCALE;
}

inline void TitleCommonProcess::ElevatedValue(float time)
{
	//		移動の遷移量
	m_move = 1.0f - sqrt(1.0f - pow(time, 2.0f));
	//		サイズの遷移量
	m_size = sqrt(1.0f - pow(time - 1.0f, 2.0f));

	//		初期サイズを設定
	m_firstSize = m_information->MIN_SCALE;
	//		最終サイズを設定
	m_endSize = m_information->MAX_SCALE;
}
