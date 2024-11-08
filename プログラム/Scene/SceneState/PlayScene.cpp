/*
* @file		PlayScene.cpp
* @brief	�v���C�V�[��
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "PlayScene.h"

#include "Common/DebugDraw.h"

PlayScene::PlayScene(SceneManager* sceneManager)
	:
	m_sceneManager{sceneManager},
	m_menuCloseJugement(false)
{
	Generation();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//		�Q�[���}�l�[�W���[�̏���������
	m_gameManager->Initialize();

	//		���~�b�g�^�C����ݒ肷��
	m_gameManager->SetLimitTime(90.0f);

	//		�v���C���[�J�����}�l�[�W���[�̏���������
	m_playerCameraManager->Initialize(m_player->GetInformation());

	//		�J�����̏����󂯎��
	m_player->SetCameraInformation(m_playerCameraManager->GetInformation());

	//		�v���C���[�̏���������
	m_player->Initialize();

	//		�I�u�W�F�N�g�}�l�[�W���[�̏���������
	m_objectManager->Initialize();

	//		UI�}�l�[�W���[�̏�����
	m_uiManager->Initialize();

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̏�����
	m_postEffectManager->Initialize(m_gameManager->BACK_GROUND_COLOR);

	//		���C���[�̏����󂯎��
	m_effectManager->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		�G�t�F�N�g�}�l�[�W���[�̏�����
	m_effectManager->Initialize();

	//		���X�|�[���}�l�[�W���[�̏�����
	m_respawnManager->Initialize();

	//		�v���C�V�[������BGM���Đ�
	MusicLibrary::GetInstance()->PlayBGM(MusicLibrary::BGMType::PlayScene);

	//		����p�̏����󂯎��
	m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

	//		����p�̍X�V
	m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

	//		�J�����̑��x�̍X�V
	m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());
}

void PlayScene::Generation()
{
	//		�Q�[���}�l�[�W���[�𐶐�����
	m_gameManager = std::make_unique<GameManager>();

	//		�v���C���[�J�����}�l�[�W���[�̐���
	m_playerCameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		�v���C���[�̐���
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	m_postEffectManager = std::make_unique<PostEffectManager>(m_gameManager.get(),
															  m_sceneManager->GetMenuManager()->GetInformation());

	//		�G�t�F�N�g�}�l�[�W���[�̍쐻
	m_effectManager = std::make_unique<EffectManager>(m_player->GetInformation(), m_playerCameraManager->GetInformation());

	//		UI�}�l�[�W���[�̐���
	m_uiManager = std::make_unique<UIManager>(m_player->GetInformation(), m_gameManager.get());

	//		�����蔻��}�l�[�W���[�̐���
	m_collitionManager = std::make_unique<CollitionManager>(m_gameManager.get());

	//		�I�u�W�F�N�g�}�l�[�W���[�̐���
	m_objectManager = std::make_unique<ObjectManager>(m_gameManager.get());

	//		���X�|�[���}�l�[�W���[
	m_respawnManager = std::make_unique<RespawnManager>(m_gameManager.get());
}

bool PlayScene::MenuInformation()
{
	//		���j���[���J���Ă���ꍇ�̏���
	if (m_sceneManager->GetMenuManager()->GetInformation()->GetMenuJudgement())
	{
		//		���j���[���J���Ă���
		m_menuCloseJugement = true;

		//		����p�̏����󂯎��
		m_playerCameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

		//		����p�̍X�V
		m_playerCameraManager->ViewAngleUpdate(m_player->GetInformation());

		//		�J�����̑��x�̍X�V
		m_playerCameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());

		//		�O���C
		m_postEffectManager->Update(PostEffectFlag::Flag::Color);

		return true;
	}

	return false;
}

void PlayScene::Update()
{
	//		P�������ƃ��U���g�ɂȂ�
	if (LibrarySingleton::GetInstance()->GetKeyboardStateTracker()->GetLastState().IsKeyDown(DirectX::Keyboard::P))
	{
		m_sceneManager->ChangeScene(SceneManager::Result);

		return;
	}

	//		���j���[���J���Ă��邩�ǂ���
	if (MenuInformation()) return;

	//		���j���[���g���邩�ǂ����H
	m_sceneManager->GetMenuManager()->GetInformation()->SetMenuUseJudgement(m_player->GetMenuUseJugement());

	//		�I�u�W�F�N�g�}�l�[�W���[�̍X�V����
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		���C���[�̏����󂯎��
	m_player->SetWireInformation(m_objectManager->GetUseWireInformation());

	//		�����x�N�g����ݒ肷��
	m_player->GetInformation()->SetViewVelocity(m_playerCameraManager->GetInformation()->GetViewVelocity());

	//		�v���C���[�̍X�V����
	m_player->Update(m_playerCameraManager->GetInformation());

	//		���b�V�����󂯎��
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		�����蔻��̍X�V����
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		�����蔻��̏��
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		���b�V���A�b�v�f�[�g
	m_player->MeshUpdate();

	//		�}�E�X��΃��[�h���瑊�΃��[�h�ɐ؂�ւ�鎞��t���[���K�v�Ȃ̂�
	if (m_menuCloseJugement)
	{
		m_menuCloseJugement = false;
	}
	else
	{
		//		�J�����}�l�[�W���[�̍X�V����
		m_playerCameraManager->Update();
	}

	//		�v���C���[�ɃJ�����̊p�x�𑗂�
	m_player->GetInformation()->SetCameraAngle(m_playerCameraManager->GetInformation()->GetAngle());

	//		�A�j���[�V�����̃A�b�v�f�[�g
	m_player->AnimationUpdate();

	//		UI�}�l�[�W���[�̍X�V
	m_uiManager->Update();

	//		�|�X�g�G�t�F�N�g�̍X�V����
	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		m_postEffectManager->Update(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		�Q�[���}�l�[�W���[�̍X�V����
	m_gameManager->Update();

	//		�G�t�F�N�g�}�l�[�W���[�̕`��
	m_effectManager->Update();

	//		���X�|�[���|�C���g�̍X�V����
	m_respawnManager->Update(m_player->GetInformation()->GetPosition());

	//		���X�|�[�����W��ݒ肷��
	m_player->GetInformation()->SetRespawnPosition(m_respawnManager->GetRespownPosition());

	//		���X�|�[�����̉�]�ʂ��󂯎��
	m_playerCameraManager->SetStartDirection(m_respawnManager->GetRespownDirection());

	//		���̃V�[���ɐ؂�ւ��邩�ǂ���
	if (m_gameManager->FlagJudgement(GameManager::NextScene))
	{
		//		���̃V�[���ɐ؂�ւ���i���U���g�V�[���j
		m_sceneManager->ChangeScene(SceneManager::SceneType::Result);
	}
}

void PlayScene::Render()
{
	for (int i = 1; i <= PostEffectFlag::Flag::Fade;)
	{
		//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̕ύX
		m_postEffectManager->Render(PostEffectFlag::Flag(i));

				//�I�u�W�F�N�g�}�l�[�W���[�̕`�揈��
		m_objectManager->Render(m_player->GetCameraInformation(),
			m_player->GetInformation()->GetPlayerHeight(),
			PostEffectFlag::Flag(i), m_postEffectManager->GetPostObjectShader());

		//		�v���C���[�̃��f���`��
		m_player->ModelRender(PostEffectFlag::Flag(i));

		//		�G�t�F�N�g�}�l�[�W���[�̕`��
		m_effectManager->Render(PostEffectFlag::Flag(i));

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UI)
		{
			//		UI�}�l�[�W���[�̕`��
			m_uiManager->FrontRender();
		}

		if (PostEffectFlag::Flag(i) == PostEffectFlag::Flag::UIBack)
		{
			//		UI�}�l�[�W���[�̌�`��
			m_uiManager->BackRender();
		}

		//		�|�X�g�G�t�F�N�g�}�l�[�W���[�̃��X�g�`��
		m_postEffectManager->RastRender(PostEffectFlag::Flag(i));

		i = i + i;
	}

	//		�f�o�b�N�`��
	m_player->DebugRender();

	//		�����_�[�e�N�X�`�������Z�b�g����
	m_postEffectManager->ResetRenderTarget();

	//		�����_�[�e�N�X�`���̕`��
	m_postEffectManager->RenderTextureView();
}

void PlayScene::Finalize()
{
	//		�N���A�^�C�����󂯎��
	m_sceneManager->SetClearTime(static_cast<int>(m_gameManager->GetTime()));

	//		���S�񐔂��󂯎��
	m_sceneManager->SetDeathCount(static_cast<int>(m_gameManager->GetDeathCount()));


	m_sceneManager->SetMaxTime(static_cast<int>(m_gameManager->GetLimitTime()));

	//		�Q�[���}�l�[�W���[�̏I������
	m_gameManager->Finalize();

	m_collitionManager->Finalize();

	//		�J�����̏I������
	m_playerCameraManager->Finalize();

	//		�v���C���̏I������
	m_player->Finalize();

	//		�|�X�g�G�t�F�N�g�}�l�[�W���[
	m_postEffectManager->Finalize();

	//		���X�|�[���|�C���g�̏I������
	m_respawnManager->Finalize();

	//		�G�t�F�N�g�}�l�[�W���[
	m_effectManager->Finalize();
	
	//		UI�}�l�[�W���[�̏I������
	m_uiManager->Finalize();

	m_objectManager->Finalize();
}