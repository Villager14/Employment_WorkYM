/*
* @file		ScreenColor.h
* @brief	スクリーンの色
* @author	Morita
* @date		2024/10/21
*/

#include "pch.h"

#include "ScreenColor.h"

#include "Common/ReaData.h"

ScreenColor::ScreenColor(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager),
	m_elapsedTime(0.0f),
	m_menuOpenJudgement(false)
{
}

ScreenColor::~ScreenColor()
{
}

void ScreenColor::Initialize()
{
	CreateRenderTarget();

	//		深度シェーダー描画
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		合成用
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/PostEffect/ScreenColor/ScreenColorVS.cso",
		L"Resources/Shader/PostEffect/ScreenColor/ScreenColorGS.cso",
		L"Resources/Shader/PostEffect/ScreenColor/ScreenColorPS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		定数バッファの値
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_constBuffer.elasedTime = 0.0f;
	m_constBuffer.color = { 1.0f, 0.0f, 0.0f, 1.0f };

	m_elapsedTime = 0.0f;

}

void ScreenColor::Update()
{
	if (RedScreen()) return;

	if (GrayScreen()) return;

	m_elapsedTime = 0.0f;
}

void ScreenColor::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	m_constBuffer.elasedTime = m_elapsedTime;

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

void ScreenColor::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_colorTexture);
}

void ScreenColor::Filanize()
{
	m_renderTexture.reset();

	m_elapsedTime = 0.0f;

	m_menuOpenJudgement = 0.0f;

	m_depthShaderView.reset();
}

bool ScreenColor::RedScreen()
{
	//		死亡した場合
	if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::DeathJudgement) ||
		m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::TimeLimitJudgement))
	{
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

		//		色を赤にする
		m_constBuffer.color = { 1.0f, 0.0f, 0.0f, 1.0f };

		//		時間をコンストバッファに代入する
		m_constBuffer.elasedTime = m_elapsedTime;

		return true;
	}

	return false;
}

bool ScreenColor::GrayScreen()
{
	//		メニューが開いた時
	if (m_postEffectManager->GetMenuInformation()->GetMenuTransrationJudgement() && !m_menuOpenJudgement)
	{
		m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

		m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

		//		色をグレーにする
		m_constBuffer.color = { 0.5f, 0.5f, 0.5f, 1.0f };

		if (m_elapsedTime >= 1.0f)
		{
			//		メニューが開いている状態にする
			m_menuOpenJudgement = true;
		}

		return true;
	}

	//		メニューを開いている時
	if (m_menuOpenJudgement && !m_postEffectManager->GetMenuInformation()->GetMenuTransrationJudgement())
	{
		m_elapsedTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 2.0f;

		m_elapsedTime = Library::Clamp(m_elapsedTime, 0.0f, 1.0f);

		if (m_elapsedTime <= 0.0f)
		{
			//		メニューが開いている状態にする
			m_menuOpenJudgement = false;
		}

		return true;
	}

	//		メニューを開いている状態の場合は処理をしない
	if (m_menuOpenJudgement) return true;

	return false;
}

void ScreenColor::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
