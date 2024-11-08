/*
* @file		ScreenColor.h
* @brief	スクリーンの色
* @author	Morita
* @date		2024/10/21
*/

#include "pch.h"

#include "FadePostEffect.h"

#include "Common/ReaData.h"

FadePostEffect::FadePostEffect(PostEffectManager* postEffectManager)
	:
	m_postEffectManager(postEffectManager),
	m_fadeStayTime(0.0f),
	m_fadeinResetJudgement(true),
	m_fadeoutResetJudgement(false),
	m_firstJudgement(true)
{
}

FadePostEffect::~FadePostEffect()
{
}

void FadePostEffect::Initialize()
{
	CreateRenderTarget();

	//		深度シェーダー描画
	m_depthShaderView = std::make_unique<UIRenderManager>();

	//		合成用
	m_depthShaderView->Create(L"Resources/Texture/UI/Clock/ClockBackGround.png",
		L"Resources/Shader/UI/Fade/FadeShaderVS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderGS.cso",
		L"Resources/Shader/UI/Fade/FadeShaderPS.cso",
		m_constBuffer, { 0.0f, 0.0f }, { 1.0f, 1.0f },
		CENTER_POINT::MIDDLE_CENTER);

	//		定数バッファの値
	m_constBuffer.windowSize = DirectX::SimpleMath::Vector4(
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().x),
		static_cast<float>(LibrarySingleton::GetInstance()->GetScreenSize().y), 1, 1);
	m_constBuffer.rotationMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_constBuffer.time = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_fadeStayTime = 0.0f;
}

void FadePostEffect::Update()
{
	Fade();
}

void FadePostEffect::ObjectRender()
{
	//		オブジェクトに対してシェーダーを掛けないようにする
	m_postEffectManager->GetPostObjectShader()->SetUseJudgement(false);

	m_constBuffer.time = { m_fadeTime, 0.0f, 0.0f, 0.0f };

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

void FadePostEffect::PostEffectRender()
{
	m_postEffectManager->SetShaderTexture(m_colorTexture);
}

void FadePostEffect::Filanize()
{
	m_renderTexture.reset();
	m_depthShaderView.reset();
	m_fadeStayTime = 0.0f;
	m_fadeinResetJudgement = true;
	m_fadeoutResetJudgement = false;
	m_firstJudgement = true;
}

void FadePostEffect::Fade()
{
	//		終了の場合
	if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::EndJudgement))
	{
		m_fadeStayTime += LibrarySingleton::GetInstance()->GetElpsedTime();

		if (m_fadeStayTime <= 1.0f) return;

		m_fadeTime -= LibrarySingleton::GetInstance()->GetElpsedTime();

		m_fadeTime = Library::Clamp(m_fadeTime, 0.0f, 1.0f);

		//		プレイシーン終了時の音量調整
		MusicLibrary::GetInstance()->SceneLerpVolume(m_fadeTime);

		if (m_fadeTime <= 0.0f)
		{
			//		次のシーンに切り替える
			m_postEffectManager->GetGameManager()->TrueFlag(GameManager::NextScene);
		}

		return;
	}

	//		復活状態＆フェードアウトをしない状態の場合
	if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::RevivalJudgement)
		&& !m_fadeoutResetJudgement)
	{
		m_fadeoutResetJudgement = true;

		m_fadeTime = 1.0f;
	}

	//		フェードインの処理
	if (m_fadeinResetJudgement)
	{
		m_fadeTime += LibrarySingleton::GetInstance()->GetElpsedTime() * 0.5f;

		m_fadeTime = Library::Clamp(m_fadeTime, 0.0f, 1.0f);

		if (m_firstJudgement)
		{
			//		プレイシーン開始時の音量調整
			MusicLibrary::GetInstance()->SceneLerpVolume(m_fadeTime);
		}

		if (m_fadeTime >= 1.0f)
		{
			m_fadeinResetJudgement = false;
		}
	}

	//		フェードアウトの処理
	if (m_fadeoutResetJudgement)
	{
		m_fadeTime -= LibrarySingleton::GetInstance()->GetElpsedTime() * 4.0f;

		m_fadeTime = Library::Clamp(m_fadeTime, 0.0f, 1.0f);

		if (m_fadeTime <= 0.0f)
		{
			//		タイムリミット
			if (m_postEffectManager->GetGameManager()->FlagJudgement(GameManager::TimeLimitJudgement))
			{
				//		次のシーンに切り替える
				m_postEffectManager->GetGameManager()->TrueFlag(GameManager::NextScene);

				return;
			}

			m_fadeoutResetJudgement = false;

			//		復活状態を終了
			m_postEffectManager->GetGameManager()->FalseFlag(GameManager::RevivalJudgement);
			m_postEffectManager->GetGameManager()->FalseFlag(GameManager::DeathJudgement);
			m_fadeinResetJudgement = true;
		}
	}
}

void FadePostEffect::CreateRenderTarget()
{
	m_renderTexture = m_postEffectManager->GetCommonProcess()->CreateRenderTexture();
}
