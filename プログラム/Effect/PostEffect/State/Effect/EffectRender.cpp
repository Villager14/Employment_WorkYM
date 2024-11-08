/*
* @file		Transparency.cpp
* @brief	アルファエフェクトの処理
* @author	Morita
* @date		2024/10/16
*/

#include "pch.h"

#include "EffectRender.h"

#include "Common/ReaData.h"

#include "../EffectDepth/EffectDepthRender.h"

EffectRender::EffectRender(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager)
{
}

EffectRender::~EffectRender()
{
}

void EffectRender::Initialize()
{
	//		レンダーターゲットの作製
	CreateRenderTarget();

	//		深度シェーダー描画
	m_transparencyRenderManager = std::make_unique<UIRenderManager>();

	//		合成用
	m_transparencyRenderManager->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/Transparency/TransparencyVS.cso",
		L"Resources/Shader/PostEffect/Transparency/TransparencyGS.cso",
		L"Resources/Shader/PostEffect/Transparency/TransparencyPS.cso",
		m_fogShaderConstBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		定数バッファの値
	m_fogShaderConstBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_fogShaderConstBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;

	//		オブジェクトに対するシェーダーをセット
	m_objectShader = LibrarySingleton::GetInstance()->CreatePSShader
	(L"Resources/Shader/PostEffect/Transparency/TransparencyObject/TransparencyObject.cso");
}

void EffectRender::Update()
{
}

void EffectRender::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛ける
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(true);

	//		オブジェクトにシェーダーを掛ける
	m_postEffectManager->GetPostObjectShader()->SetPixselShader(m_objectShader.Get());

	m_postEffectManager->SetBackRenderColor(DirectX::Colors::Black);

	//		レンダーターゲットの変更(オブジェクトの描画)
	m_alphaEffectTexture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());
}

void EffectRender::PostEffectRender()
{
	//		レンダーターゲットの変更
	m_texture = m_postEffectManager->ChangeRenderTarget(m_transparencyRenderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	//		テクスチャサイズの変更
	m_transparencyRenderManager->SetTextureSize(static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().x),
												static_cast<int>(LibrarySingleton::GetInstance()->GetScreenSize().y));

	//		テクスチャをセットする
	m_transparencyRenderManager->SetTexture(m_alphaEffectTexture);
	m_transparencyRenderManager->SetTexture(m_postEffectManager->GetShaderTexture(), 1);
	m_transparencyRenderManager->SetTexture((*m_postEffectManager->GetPostEffectProcess())
		[PostEffectFlag::Flag::AlphaDepth]->GetTexture(), 2);

	//		フォグ処理の描画
	m_transparencyRenderManager->Render(m_fogShaderConstBuffer);

	m_postEffectManager->SetShaderTexture(m_texture);
}

void EffectRender::Filanize()
{
	m_renderTexture.reset();
	m_transparencyRenderTexture.reset();
	m_transparencyRenderManager.reset();
}

void EffectRender::LoadShader(const wchar_t* vsPath, const wchar_t* psPath)
{
	auto device = LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// ピクセルシェーダーの作成（深度用）
	std::vector<uint8_t> ps =
		DX::ReadData(psPath);
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(),
			nullptr, m_pixselShader.ReleaseAndGetAddressOf())
	);

	// 頂点シェーダーの作成（深度用）
	std::vector<uint8_t> vs =
		DX::ReadData(vsPath);
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs.data(), vs.size(),
			nullptr, m_vertexShader.ReleaseAndGetAddressOf())
	);
}

void EffectRender::SetObjectShader(PostEffectObjectShader* shader)
{
	shader->SetPixselShader(m_pixselShader.Get());
	shader->SetVertexShader(m_vertexShader.Get());
}

void EffectRender::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
	m_transparencyRenderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
