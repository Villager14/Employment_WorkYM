/*
* @file		GlitchNoise.h
* @brief	グリッチノイズ
* @author	Morita
* @date		2024/10/22
*/

#include "pch.h"

#include "GlitchNoise.h"

#include "Common/ReaData.h"

GlitchNoise::GlitchNoise(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
}

GlitchNoise::~GlitchNoise()
{
}

void GlitchNoise::Initialize()
{
	CreateRenderTarget();

	//		深度シェーダー描画
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		合成用
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoiseVS.cso",
		L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoiseGS.cso",
		L"Resources/Shader/PostEffect/GlitchNoise/GlitchNoisePS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		定数バッファの値
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
}

void GlitchNoise::Update()
{

}

void GlitchNoise::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		レンダーターゲットの変更(オブジェクトの描画)
	m_colorTexture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	//		テクスチャサイズの変更
	m_depthShaderView->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		テクスチャをセットする
	m_depthShaderView->SetTexture(m_postEffectManager->GetShaderTexture());

	//		Color処理の描画
	m_depthShaderView->Render(m_constBuffer);
}

void GlitchNoise::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_colorTexture);
}

void GlitchNoise::Filanize()
{
	m_renderTexture.reset();

	m_depthShaderView.reset();
}

void GlitchNoise::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
