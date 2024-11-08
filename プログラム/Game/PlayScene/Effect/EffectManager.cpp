/*

* @file		EffectManager.cpp
* @brief	�G�t�F�N�g�}�l�[�W���[
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
	//		���C���[�g�p���̃G�t�F�N�g�̐���
	m_wireUseEffect = std::make_unique<WireUseEffect>(m_playerInformation);

	//		�f�W�^���J�̐���
	m_degitalRain = std::make_unique<DegitalRain>(this);

	//m_signboardEffect = std::make_unique<SignboardEffect>(this);

}

EffectManager::~EffectManager()
{
}

void EffectManager::Initialize()
{
	//		���C���[�g�p���̃G�t�F�N�g�̏�����
	m_wireUseEffect->Initialize(static_cast<int>((*m_wireInformation).size()));

	//		�f�W�^���J�̏���������
	m_degitalRain->Initialzie();

	//		�Ŕ̏���������
	//m_signboardEffect->Initialzie();
}

void EffectManager::Update()
{
	//		���C���[�g�p���̃G�t�F�N�g�̍X�V����

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

	//		�f�W�^���J�̍X�V����
	m_degitalRain->Update();
}

void EffectManager::Render(PostEffectFlag::Flag flag)
{
	for (int i = 0, max = static_cast<int>((*m_wireInformation).size()); i < max; ++i)
	{
		if (!(*m_wireInformation)[i].m_usedJudgement ||
			!m_playerInformation->GetWireJudgement()) continue;

		//		���C���[�g�p���̃G�t�F�N�g�̕`��
		m_wireUseEffect->Render((*m_wireInformation)[i].position, i, flag);
	}

	//m_signboardEffect->Render(flag);

	//		�f�W�^���J�̕`��
	m_degitalRain->Render(flag);

}

void EffectManager::Finalize()
{
	m_wireUseEffect->Finalize();

	m_wireInformation->clear();

	m_degitalRain->Finalize();
}
