/*

* @file		EffectManager.cpp
* @brief	エフェクトマネージャー
* @author	Morita
* @date		2024/06/10
*/

#include "pch.h"

#include "EffectManager.h"

EffectManager::EffectManager(PlayerInformation* playerInformation,
							 PlayerCameraInformation* cameraInformation)
	:
	m_playerInformation(playerInformation),
	m_cameraInformation(cameraInformation)
{
	//		ワイヤー使用時のエフェクトの生成
	m_wireUseEffect = std::make_unique<WireUseEffect>(m_playerInformation);

	//		デジタル雨の生成
	m_degitalRain = std::make_unique<DegitalRain>(this);

	//m_signboardEffect = std::make_unique<SignboardEffect>(this);

}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	//		ワイヤー使用時のエフェクトの初期化
	m_wireUseEffect->Initialize(static_cast<int>((*m_wireInformation).size()));

	//		デジタル雨の初期化処理
	m_degitalRain->Initialzie();

	//		看板の初期化処理
	//m_signboardEffect->Initialzie();
}

void EffectManager::Update()
{
	//		ワイヤー使用時のエフェクトの更新処理

	m_wireUseEffect->BillbordUpdate(m_cameraInformation);

	for (int i = 0, max = static_cast<int>((*m_wireInformation).size()); i < max; ++i)
	{
		if (!(*m_wireInformation)[i].m_usedJudgement ||
			!m_playerInformation->GetWireJudgement())
		{
			m_wireUseEffect->ResetProcess(i);

			continue;
		}

		m_wireUseEffect->Update((*m_wireInformation)[i].position, i);
	}

	//		デジタル雨の更新処理
	m_degitalRain->Update();
}

void EffectManager::Render(PostEffectFlag::Flag flag)
{
	for (int i = 0, max = static_cast<int>((*m_wireInformation).size()); i < max; ++i)
	{
		if (!(*m_wireInformation)[i].m_usedJudgement ||
			!m_playerInformation->GetWireJudgement()) continue;

		//		ワイヤー使用時のエフェクトの描画
		m_wireUseEffect->Render((*m_wireInformation)[i].position, i, flag);
	}

	//m_signboardEffect->Render(flag);

	//		デジタル雨の描画
	m_degitalRain->Render(flag);

}

void EffectManager::Finalize()
{
	m_wireUseEffect->Finalize();

	m_wireInformation->clear();

	m_degitalRain->Finalize();
}
