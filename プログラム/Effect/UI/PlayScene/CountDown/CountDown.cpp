/*
* @file		CountDown.h
* @brief	カウントダウンの処理
* @author	Morita
* @date		2024/11/01
*/

#include "pch.h"

#include "CountDown.h"

CountDown::CountDown()
	:
	m_time(0.0f),
	m_alpha(0.0f)
{
}

CountDown::~CountDown()
{
}

void CountDown::Initialize()
{
	//		フェード描画の生成
	m_numberAlpha = std::make_unique<UIRenderManager>();

	m_numberAlpha->Create(L"Resources/Texture/UI/CountDown/CountDown.png",
		L"Resources/Shader/UI/NumberAlpha/NumberAlphaVS.cso",
		L"Resources/Shader/UI/NumberAlpha/NumberAlphaGS.cso",
		L"Resources/Shader/UI/NumberAlpha/NumberAlphaPS.cso",
		buffer,
		COUNT_DOWN_POSITION, { 0.8f, 0.8f });

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_numberAlpha->GetRotationMatrix();

	m_time = 0.0f;
	m_alpha = 0.0f;
}

void CountDown::Update(float time)
{
	m_time = time;
}

void CountDown::Render()
{
	if (m_time > 6.0f ||
		m_time < 1.0f) return;

	buffer.alpha = sinf(m_time - static_cast<float>(static_cast<int>(m_time))) / 2.0f;
	buffer.time = static_cast<int>(m_time);

	m_numberAlpha->Render(buffer);
}

void CountDown::Finalize()
{
	m_numberAlpha.reset();
}
