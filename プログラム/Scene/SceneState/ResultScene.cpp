/*
* @file		ResultScene.h
* @brief	���U���g�V�[��
* @author	Morita
* @date		2024/05/28
*/

#include "pch.h"

#include "ResultScene.h"

ResultScene::ResultScene(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager),
	m_score(0.0f)
{
	//		���U���g�}�l�[�W���[�̐���
	m_resultManager = std::make_unique<ResultManager>();
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
	float time = static_cast<float>(m_sceneManager->GetClearTime());

	float deth = static_cast<float>(m_sceneManager->GetDeathCount());

	float maxTime = static_cast<float>(m_sceneManager->GetMaxTime());
	
	float score = 0.0f;

	if (deth == 0)
	{
		score = 1000.0f;
	}
	else if (deth < 3)
	{
		score = 700.0f;
	}
	else
	{
		score = 200.0f;
	}

	score *= Library::Lerp(3.0f, 1.0f, time / maxTime);

	m_score = score;

	//		���U���g�}�l�[�W���[�̏�����
	m_resultManager->Initialize(static_cast<int>(m_score), m_sceneManager->GetClearTime(),
								m_sceneManager->GetDeathCount());

	//		�v���W�F�N�V�����s��̍쐻
	CreateProj();
	//		�r���[�s��̍쐻
	CreateView();

	//		BGM���Đ�����
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::ResultScene);
}

void ResultScene::Update()
{
	//		�w�i�̍X�V
	m_resultManager->BackGroundUpdate();

	//		���j���[���J���Ă���ꍇ���������Ȃ�
	if (m_sceneManager->GetMenuManager()->GetInformation()->GetMenuJudgement()) return;

	//		���j���[���g���邩�ǂ���
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_resultManager->GetMenuUseJugement());

	//		���U���g�}�l�[�W���[�̍X�V����
	m_resultManager->Update();

	if (m_resultManager->GetInformation()->GetChangeSceneJudgement())
	{
		m_sceneManager->ChangeScene(SceneManager::SceneType::Title);
	}
}

void ResultScene::Render()
{
	//		���U���g�}�l�[�W���[�̕`�揈��
	m_resultManager->Render();
}

void ResultScene::Finalize()
{
	m_resultManager->Finalize();

	m_score = 0.0f;
}

void ResultScene::CreateProj()
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

void ResultScene::CreateView()
{
	DirectX::SimpleMath::Matrix rotation;

	//		���_����
	DirectX::SimpleMath::Vector3 target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 1.0f);

	//		�A�b�v�x�N�g��
	DirectX::SimpleMath::Vector3 up = DirectX::SimpleMath::Vector3::UnitY;

	//		�r���[�s���ݒ肷��
	LibrarySingleton::GetInstance()->SetView(DirectX::SimpleMath::Matrix::CreateLookAt
	({0.0f, 0.0f, 0.0f}, target, up));
}
