/*
* @file		MenuSelect.h
* @brief	メニューの選択処理
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "MenuSelect.h"

MenuSelect::MenuSelect()
	:
	m_time(0.0f)
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(L"Resources/Texture/Menu/Select/Select.png",
		L"Resources/Shader/UI/MenuSelect/MenuSelectVS.cso",
		L"Resources/Shader/UI/MenuSelect/MenuSelectGS.cso",
		L"Resources/Shader/UI/MenuSelect/MenuSelectPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f , }, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);
}

MenuSelect::~MenuSelect()
{
}

void MenuSelect::Initialize()
{
	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void MenuSelect::Render(DirectX::SimpleMath::Vector2 position)
{
	m_time += LibrarySingleton::GetInstance()->GetElpsedTime();

	m_constBuffer.time = { m_time, 0.0f, 0.0f, 0.0f };

	m_shader->SetPosition(position);

	m_shader->Render(m_constBuffer);
}
