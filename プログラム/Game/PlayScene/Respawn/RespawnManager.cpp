/*
* @file		RespawnManager.cpp
* @brief	���X�|�[���}�l�[�W���[�̏���
* @author	Morita
* @date		2024/10/03
*/

#include "pch.h"

#include "RespawnManager.h"

RespawnManager::RespawnManager(GameManager* gameManager)
	:
	m_gameManager(gameManager),
	m_respownIndex(0),
	m_direction(0.0f)
{
	//		���X�|�[�����W�ǂݍ��݂𐶐�����
	m_respawnPointRead = std::make_unique<RespawnPointRead>();

	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	m_respownRengeModel = DirectX::Model::CreateFromCMO(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/WireRange.cmo", *m_effect);
}

RespawnManager::~RespawnManager()
{
}

void RespawnManager::Initialize()
{
	//		�����X�|�[���ʒu
	m_respawnPosition = { 0.0f, 0.0f, 0.0f };

	m_respownIndex = 0;

	//		�ǂݍ��ݏ���
	m_respawnPointRead->ReadProcess(0);
}

void RespawnManager::Update(DirectX::SimpleMath::Vector3 playerPosition)
{
	for (int i = 0, max = static_cast<int>(m_respawnPointRead->GetPosition().size());
		i < max; ++i)
	{
		//		�v�f���������ꍇ���������Ȃ�
		if (i == m_respownIndex) continue;

		//		���X�|�[���|�C���g�ɓ������Ă��邩
		CollitionProcess(playerPosition, i);
	}
}

void RespawnManager::CollitionProcess(DirectX::SimpleMath::Vector3 playerPosition, int index)
{
	//		�v���C���[�ƃ��X�|�[���|�C���g�̋���
	float length = (playerPosition - m_respawnPointRead->GetPosition()[index]).Length();

	//		���������X�|�[���͈͂ƃv���C���[�̍�����菬�����ꍇ�A�X�V����
	if (length < m_respawnPointRead->GetLength()[index] + 7.0f)
	{
		//		���X�|�[���|�C���g���X�V����
		m_respawnPosition = m_respawnPointRead->GetPosition()[index];

		//		���X�|�[���C���f�b�N�X���X�V����
		m_respownIndex = index;

		//		����
		m_direction = m_respawnPointRead->GetDirection()[index];
	}
}

void RespawnManager::DebugRender()
{
	//		�f�o�b�N�\�����ǂ���
	if (LibrarySingleton::GetInstance()->GetDebugJudgement())
	{
		for (int i = 0, max = static_cast<int>(m_respawnPointRead->GetPosition().size());
			i < max; ++i)
		{
			//		�f�o�b�N���[���h�̔��a�̑傫��
			m_respownRengeWorld = DirectX::SimpleMath::Matrix::CreateScale(m_respawnPointRead->GetLength()[i] + 7.0f);

			//		���W��ݒ肷��
			m_respownRengeWorld *= DirectX::SimpleMath::Matrix::CreateTranslation(m_respawnPointRead->GetPosition()[i]);

			//		���C���[���͂��͈�(����������)
			for (const auto& it : m_respownRengeModel->meshes)
			{
				auto mesh = it.get();

				mesh->PrepareForRendering(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
					*LibrarySingleton::GetInstance()->GetCommonState(), true);

				mesh->Draw(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDeviceContext(),
					m_respownRengeWorld, LibrarySingleton::GetInstance()->GetView(),
					LibrarySingleton::GetInstance()->GetProj());
			}
		}
	}
}

void RespawnManager::Finalize()
{
	m_respawnPointRead->Finalize();

	m_direction = 0.0f;

	m_respownIndex = 0;
}

