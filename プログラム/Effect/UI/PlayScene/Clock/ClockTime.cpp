/*
* @file		ClockTime.h
* @brief	UI時計の数字
* @author	Morita
* @date		2024/05/20
*/

#include "pch.h"

#include "ClockTime.h"

ClockTime::ClockTime(GameManager* gameManager)
	:
	m_time(0),
	m_limitTime(0.0f),
	m_gameManager(gameManager)
{
}

ClockTime::~ClockTime()
{
}

void ClockTime::Initialize()
{
	//		シェーダー描画マネージャーの生成
	m_shader = std::make_unique<UIRenderManager>();

	//		数字シェーダーの作製
	m_shader->Create(L"Resources/Texture/UI/Clock/ClockNumber.png",
		L"Resources/Shader/UI/Number/NumberVS.cso",
		L"Resources/Shader/UI/Number/NumberGS.cso",
		L"Resources/Shader/UI/Number/NumberPS.cso",
		buffer,
		{ 0.0f, 0.0f }, { 0.8f, 0.8f });

	//		ウィンドウサイズを設定する
	buffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);

	//		回転量を設定する
	buffer.rotationMatrix = m_shader->GetRotationMatrix();

	m_time = 0;

	m_limitTime = m_gameManager->GetLimitTime();
}

void ClockTime::Update(float elapsedTime)
{
	m_time = static_cast<int>(m_limitTime - elapsedTime);

	if (m_time <= 0.0f)
	{
		//		時間切れ
		m_gameManager->TrueFlag(GameManager::Flag::TimeLimitJudgement);
	}
}

void ClockTime::Render()
{
	//		十分単位
	m_shader->SetPosition(TEN_PLACE_MINUTES_POSITION);
	buffer.number = { static_cast<float>(m_time / 60 / 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);

	//		分単位
	m_shader->SetPosition(ONE_PLACE_MINUTES_POSITION);
	buffer.number = { static_cast<float>(m_time / 60 % 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);

	//		十秒
	m_shader->SetPosition(TEN_PLACE_SECONDS_POSITION);
	buffer.number = { static_cast<float>(m_time % 60 / 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);

	//		秒
	m_shader->SetPosition(ONE_PLACE_SECONDS_POSITION);
	buffer.number = { static_cast<float>(m_time % 60 % 10), 0.0f, 0.0f, 0.0f };

	//		描画
	m_shader->Render(buffer);
}

void ClockTime::Finalize()
{
	m_shader.reset();
}
