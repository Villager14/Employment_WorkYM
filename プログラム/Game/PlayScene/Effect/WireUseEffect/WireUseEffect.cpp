/*
* @file		WireUseEffect.cpp
* @brief	ワイヤー使用エフェクト
* @author	Morita
* @date		2024/06/10
*/


#include "pch.h"
#include "WireUseEffect.h"

WireUseEffect::WireUseEffect(PlayerInformation* playerInformation)
	:
	m_playerInformation(playerInformation)
{
	//		ビルボードエフェクトの生成
	m_billboardEffect = std::make_unique<BillboardEffect>();

	//		テクスチャの読み込み
	m_billboardEffect->LoadTexture(L"Resources/Texture/UI/WireSelect/WireSelect.png");

	//		ビルボードの作製
	m_billboardEffect->Create();

	//		ポストエフェクトフラグを生成する
	m_postEffectFlag = std::make_unique<PostEffectFlag>();

	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::Alpha);
	m_postEffectFlag->TrueFlag(PostEffectFlag::Flag::AlphaDepth);
}

WireUseEffect::~WireUseEffect()
{
}

void WireUseEffect::Initialize(int size)
{
	WireStatas wireState;

	for (int i = 0; i < size; ++i)
	{
		m_wireStatas.push_back(wireState);
	}
}

void WireUseEffect::Update(DirectX::SimpleMath::Vector3 position, int index)
{
	//		初めて更新した場合
	if (m_wireStatas[index].sclaeChangeJudgement)
	{
		if (m_wireStatas[index].firstJudgement)
		{
			//		使用済みなので別の方くを向いた際にリセットするようにする
			m_wireStatas[index].resetFlag = true;

			float length = (m_playerInformation->GetPosition() - position).Length();

			length /= 127.0f;

			m_wireStatas[index].maxScale = Library::Lerp(15.0f, 40.0f, Library::Clamp(length, 0.0f, 1.0f));

			m_wireStatas[index].firstJudgement = false;
		}


		m_wireStatas[index].time += LibrarySingleton::GetInstance()->GetElpsedTime() * 1.5f;

		m_wireStatas[index].time = Library::Clamp(m_wireStatas[index].time, 0.0f, 1.0f);

		m_wireStatas[index].scale = Library::Lerp(m_wireStatas[index].maxScale, 10.0f, 1.0f - pow(1.0f - m_wireStatas[index].time, 5.0f));

		if (m_wireStatas[index].time >= 1.0f)
		{
			m_wireStatas[index].sclaeChangeJudgement = false;
		}
	}
}

void WireUseEffect::BillbordUpdate(PlayerCameraInformation* cameraInformation)
{
	if (m_playerInformation->GetWireJudgement())
	{
		m_billboardEffect->CreateBillboard(
			cameraInformation->GetTarget(),
			cameraInformation->GetEye(),
			cameraInformation->GetUP());
	}
}

void WireUseEffect::Render(DirectX::SimpleMath::Vector3 position, int index,
	PostEffectFlag::Flag flag)
{
	UNREFERENCED_PARAMETER(flag);

	m_billboardEffect->SetScale(m_wireStatas[index].scale);

	m_billboardEffect->Render(position);
}

void WireUseEffect::Finalize()
{
	m_wireStatas.clear();
}

void WireUseEffect::ResetProcess(int index)
{
	if (!m_wireStatas[index].resetFlag) return;

	m_wireStatas[index].time = 0.0f;
	m_wireStatas[index].firstJudgement = true;
	m_wireStatas[index].sclaeChangeJudgement = true;
	m_wireStatas[index].resetFlag = false;
	m_wireStatas[index].scale = 20.0f;
}
