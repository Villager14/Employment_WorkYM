/*
* @file		SignboardEffect.cpp
* @brief	看板エフェクト
* @author	Morita
* @date		2024/10/30
*/

#include "pch.h"

#include "SignboardEffect.h"

#include "Game/PlayScene/Effect/EffectManager.h"

SignboardEffect::SignboardEffect(EffectManager* effectManager)
	:
	m_effectManager(effectManager)
{
	m_effectShaderManager = std::make_unique<EffectShaderManager<ConstBuffer>>();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

SignboardEffect::~SignboardEffect()
{
}

void SignboardEffect::Initialzie()
{
	m_effectShaderManager->Create(
		L"Resources/Texture/Effect/Signboard/wasd.png",
		L"Resources/Shader/EffectBillboard/EffectBillboardVS.cso",
		L"Resources/Shader/EffectBillboard/EffectBillboardGS.cso",
		L"Resources/Shader/EffectBillboard/EffectBillboardPS.cso",
		m_constBuffer,
		{ 0.0f, 0.0f, 0.0f },
		{ 10.0f, 0.0f }
	);

	CreateParameta(SignboardType::Move, {0.0f, 3.0f, 0.0f}, 
		L"Resources/Texture/Effect/Signboard/wasd.png");
}

void SignboardEffect::Update()
{
}

void SignboardEffect::Render(PostEffectFlag::Flag flag)
{
	//		フラグがfalseの場合処理をしない	
	if ((flag & m_postEffectFlag->GetFlag()) == 0)
	{
		return;
	}

	m_effectShaderManager->RenderProcedure();

	for (int i = 0; i < m_parameta.size(); ++i)
	{
		m_effectShaderManager->SetPosition(m_parameta[SignboardType(i)].position);

		m_effectShaderManager->CreateBillboard
		(m_parameta[SignboardType(i)].position,
			m_effectManager->GetCameraInformation()->GetEye(),
			m_effectManager->GetCameraInformation()->GetUP());

		m_constBuffer.matWorld = m_effectShaderManager->GetBillbord().Transpose();
		m_constBuffer.matView = LibrarySingleton::GetInstance()->GetView().Transpose();
		m_constBuffer.matProj = LibrarySingleton::GetInstance()->GetProj().Transpose();

		m_effectShaderManager->ChangeTexture(m_parameta[SignboardType(i)].texture.Get(), 0);

		m_effectShaderManager->Render(m_constBuffer);
	}
}

void SignboardEffect::Finalize()
{
}

void SignboardEffect::CreateParameta(SignboardType type,
	DirectX::SimpleMath::Vector3 position, const wchar_t* path)
{
	SignboardInformation parameta;

	parameta.position = position;

	parameta.texture = m_effectShaderManager->GetLoadTexture(path);

	m_parameta.insert({ type, parameta });
}
