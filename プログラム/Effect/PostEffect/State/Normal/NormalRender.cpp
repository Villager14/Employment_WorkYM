/*
* @file		UIRender.cpp
* @brief	UIの描画処理
* @author	Morita
* @date		2024/10/20
*/

#include "pch.h"

#include "NormalRender.h"
#include "Common/ReaData.h"

NormalRender::NormalRender(PostEffectManager* manager)
	:
	m_postEffectManager(manager)
{
}

NormalRender::~NormalRender()
{
}

void NormalRender::Initialize()
{
	CreateRenderTarget();
}

void NormalRender::Update()
{
}

void NormalRender::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	//		背景色を黒にする
	m_postEffectManager->SetBackRenderColor(DirectX::Colors::Black);

	//		レンダーターゲットの変更(オブジェクトの描画)
	m_alphaEffectTexture = m_postEffectManager->ChangeRenderTarget(m_renderTexture.get(),
		LibrarySingleton::GetInstance()->GetDeviceResources()->GetDepthStencilView());
}

void NormalRender::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_alphaEffectTexture);
}

void NormalRender::Filanize()
{
	m_renderTexture.reset();
}

void NormalRender::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
