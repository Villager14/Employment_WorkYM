/*
* @file		CommonEnemyBullet.h
* @brief	��ʓI�ȓG�̒e
* @author	Morita
* @date		2024/05/06
*/

#include "pch.h"

#include "CommonEnemyBullet.h"

CommonEnemyBullet::CommonEnemyBullet()
	:
	m_firingJudgement(false),
	m_elapsedTime(0.0f)
{
}

CommonEnemyBullet::~CommonEnemyBullet()
{
}

void CommonEnemyBullet::Initialize()
{
	//		�G�t�F�N�g�t�@�N�g���[���󂯎��
	DirectX::EffectFactory* m_effect = LibrarySingleton
		::GetInstance()->GetEffectFactory();

	//		�摜�̓ǂݍ���
	m_effect->SetDirectory(L"Resources/Models");

	//		���f���̓ǂݍ���
	m_model = DirectX::Model::CreateFromCMO
	(LibrarySingleton::GetInstance()->GetDeviceResources()->GetD3DDevice(),
		L"Resources/Models/CommonBullet.cmo", *m_effect);
}

void CommonEnemyBullet::Update(float timeSpeed)
{
	if (!m_firingJudgement) return;

	float speed = 80.0f;

	m_position += m_velocity * speed * timeSpeed * LibrarySingleton::GetInstance()->GetElpsedTime();

	//		�o�ߎ���
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();

	//		��莞�Ԍo�ߌ�
	if (m_elapsedTime > 10.0f)
	{
		//		�I������
		Finalize();
	}
}

void CommonEnemyBullet::Render()
{
	if (!m_firingJudgement) return;

	//		���[���h���W
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	//		���f���̕`��
	m_model->Draw(LibrarySingleton::GetInstance()
		->GetDeviceResources()->GetD3DDeviceContext(),
		*LibrarySingleton::GetInstance()->GetCommonState(),
		world, LibrarySingleton::GetInstance()->GetView(),
		LibrarySingleton::GetInstance()->GetProj());
}

void CommonEnemyBullet::Finalize()
{
	m_elapsedTime = 0.0f;

	m_firingJudgement = false;
}
