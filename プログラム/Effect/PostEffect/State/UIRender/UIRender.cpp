/*
* @file		UIRender.cpp
* @brief	UIの描画処理
* @author	Morita
* @date		2024/10/20
*/

#include "pch.h"

#include "UIRender.h"

#include "Common/ReaData.h"

UIRender::UIRender(PostEffectManager* manager)
	:
	m_postEffectManager(manager)
{
}

UIRender::~UIRender()
{
}

void UIRender::Initialize()
{
	CreateRenderTarget();
}

void UIRender::Update()
{
}

void UIRender::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		背景色を黒にする
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::Black);

	//		レンダーターゲットの変更(オブジェクトの描画)
	m_alphaEffectTexture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());

	//		テクスチャをセットする
	m_postEffectManager->GetStandardShader()->ChangeTexture(PostEffectManager::UIType::UITexture,
		m_postEffectManager->GetShaderTexture(),
		LibrarySingleton::GetInstance()->GetScreenSize());

	//		テクスチャを描画する
	m_postEffectManager->GetStandardShader()->Render(PostEffectManager::UIType::UITexture);
}

void UIRender::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_alphaEffectTexture);
}

void UIRender::Filanize()
{
	m_renderTexture.reset();
}

void UIRender::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
