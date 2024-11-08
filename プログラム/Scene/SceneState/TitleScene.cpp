/*
* @file		TitleScene.cpp
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/05/24
*/

#include "pch.h"

#include "TitleScene.h"

TitleScene::TitleScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
	//		�^�C�g���I���}�l�[�W���[�̐���
	m_titleSelectManager = std::make_unique<TitleSelectManager>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//		�^�C�g���I���}�l�[�W���[�̏�����
	m_titleSelectManager->Initialize();

	//		�^�C�g����BGM�̍Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::TitleScene);

	//		���j���[�̏���ݒ肷��
	m_titleSelectManager->SetMenuInformation(m_sceneManager->GetMenuManager()->GetInformation());

	CreateView();

	CreateProj();
}

void TitleScene::Update()
{
	//		���j���[���g�����Ԃɂ��邩�ǂ����H
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_titleSelectManager->
														GetInformation()->GetMenuUseJudgement());

	//		�^�C�g���I���}�l�[�W���[�̍X�V����
	m_titleSelectManager->Update();

	//		�V�[�����I�����邩�ǂ���
	if (m_titleSelectManager->GetInformation()->GetChangeScnenJudgemnet())
	{
		//		�v���C�V�[���ɐ؂�ւ���
		m_sceneManager->ChangeScene(SceneManager::SceneType::Play);
	}
}

void TitleScene::Render()
{
	//		�^�C�g���I���}�l�[�W���[�̕`�揈��
	m_titleSelectManager->Render();
}

void TitleScene::Finalize()
{
	m_titleSelectManager->Finalize();
}

void TitleScene::CreateView()
{
	DirectX::SimpleMath::Matrix rotation;

	//		���_����
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);

	//		�A�b�v�x�N�g��
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	({ 0.0f, 0.0f, 0.0f }, target, up));
}

void TitleScene::CreateProj()
{
	//		�r���[�s����쐬����
	DirectX::SimpleMath::Matrix proj = DirectX::SimpleMath::Matrix::
		CreatePerspectiveFieldOfView
		(DirectX::XMConvertToRadians(60.0f), LibrarySingleton::GetInstance()->GetScreenSize().x /
			LibrarySingleton::GetInstance()->GetScreenSize().y,
			0.1f, 360.0f);

	//		�v���W�F�N�V�����s���ݒ肷��
	LibrarySingleton::GetInstance()->SetProj(proj);
}
