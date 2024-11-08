/*
* @file		Slider.h
* @brief	スライダーの処理
* @author	Morita
* @date		2024/07/10
*/

#include "pch.h"

#include "Slider.h"

Slider::Slider()
{
	m_shader = std::make_unique<UIRenderManager>();

	m_shader->Create(L"Resources/Texture/Menu/Slide/Slide.png",
		L"Resources/Shader/UI/Slider/SliderVS.cso",
		L"Resources/Shader/UI/Slider/SliderGS.cso",
		L"Resources/Shader/UI/Slider/SliderPS.cso",
		m_constBuffer,
		{ 200.0f, -100.0f }, { 1.0f,1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	CreateUIInformation(MASTER_VOLUM_POSITION, { 1.0f, 1.0f }, 1.0f, UIType::MastarVolum);
	CreateUIInformation(BGM_VOLUM_POSITION, { 1.0f, 1.0f }, MusicLibrary::GetInstance()->FIRST_BMG_VOLUME, UIType::BGMVolum);
	CreateUIInformation(SOUND_EFFECT_POSITION, { 1.0f, 1.0f }, MusicLibrary::GetInstance()->FIRST_SOUND_EFFECT_VOLUME, UIType::SoundEffect);
	CreateUIInformation(FOV_POSITION, { 1.0f, 1.0f }, 0.0f, UIType::FOV);
	CreateUIInformation(MOUSE_POSITION, { 1.0f, 1.0f }, 0.5f, UIType::Mouse);
}

Slider::~Slider()
{
}

void Slider::Initialize()
{
	//		回転行列を送る
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		ウィンドウサイズを送る
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
}

void Slider::CreateUIInformation(DirectX::SimpleMath::Vector2 position, 
	DirectX::SimpleMath::Vector2 size, float slideVal, UIType type)
{
	UIInformation uiInformation;

	uiInformation.position = position;
	uiInformation.scale = size;
	uiInformation.slideVal = slideVal;

	m_shaderInformation.insert({ type, uiInformation });
}

void Slider::Render(UIType type, float time)
{
	m_shader->SetPosition(m_shaderInformation[type].position);
	m_shader->SetSize(m_shaderInformation[type].scale);
	m_constBuffer.time = {time, 0.0f, 0.0f, 0.0f};
	m_constBuffer.slideVal = { m_shaderInformation[type].slideVal, 0.0f, 0.0f, 0.0f};

	m_shader->Render(m_constBuffer);
}
