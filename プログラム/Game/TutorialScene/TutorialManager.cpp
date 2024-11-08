/*
* @file		TutorialManager.cpp
* @brief	�`���[�g���A���Ǘ�
* @author	Morita
* @date		2024/09/17
*/

#include "pch.h"

#include "TutorialManager.h"

#include "Scene/SceneManager.h"

TutorialManager::TutorialManager(SceneManager* sceneManager)
	:
	m_sceneManager(sceneManager)
{
	//		����
	Generation();
}

TutorialManager::~TutorialManager()
{
}

void TutorialManager::Initialize()
{
	//		�`���[�g���A�����}�b�v�ɒǉ�
	m_tutorialInformation[TutorialState::Walk] = std::make_unique<TutorialWalkState>(this);

	//		�����̏��(Walk)
	m_tutorialState = TutorialState::Walk;

	//		���݂̃`���[�g���A����ԃI�u�W�F�N�g���擾
	m_state = m_tutorialInformation[m_tutorialState].get();

	//		����������
	m_state->Initialize();

	//		�I�u�W�F�N�g�}�l�[�W���[�̏���������
	m_objectManager->Initialize();

	//		�v���C���[�̏���������
	m_player->Initialize();

	//		�v���C���[�J�����}�l�[�W���[�̏���������
	m_cameraManager->Initialize(m_player->GetInformation());

	//		�J�����̏����󂯎��
	m_player->SetCameraInformation(m_cameraManager->GetInformation());

	//		����p�̏����󂯎��
	m_cameraManager->GetInformation()->SetViewAngle(m_sceneManager->GetMenuManager()->GetInformation()->GetViewAngle());

	//		����p�̍X�V
	m_cameraManager->ViewAngleUpdate(m_player->GetInformation());

	//		�J�����̑��x�̍X�V
	m_cameraManager->GetInformation()->SetCameraSpeed(m_sceneManager->GetMenuManager()->GetInformation()->GetCameraSpeed());

	//		�J�����̏�Ԃ��X�^���_�[�h�ɂ���
	m_cameraManager->ChangeState(PlayerCameraManager::Standard);
}

void TutorialManager::Update()
{
	//		�����x�N�g����ݒ肷��
	m_player->GetInformation()->SetViewVelocity(m_cameraManager->GetInformation()->GetViewVelocity());

	//		�v���C���[�̃��[���h���W���󂯎��
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		�I�u�W�F�N�g�}�l�[�W���[�̍X�V����
	m_objectManager->Update(m_player->GetInformation()->GetPosition());

	//		�v���C���[�̍X�V����
	m_player->Update(m_cameraManager->GetInformation());

	//		�J�����̍X�V����
	m_cameraManager->Update();

	//		�v���C���[�ɃJ�����̊p�x�𑗂�
	m_player->GetInformation()->SetCameraAngle(m_cameraManager->GetInformation()->GetAngle());

	//		���b�V���A�b�v�f�[�g
	m_player->MeshUpdate();

	//		���b�V�����󂯎��
	m_collitionManager->SetObjectMesh(m_objectManager->GetMesh());

	//		�����蔻��̍X�V����
	m_collitionManager->Update(m_player->GetPlayerInformationCollition());

	//		�����蔻��̏��
	m_player->SetCollitionInformation(m_collitionManager->GetCollitionInformation());

	//		�A�j���[�V�����̃A�b�v�f�[�g
	m_player->AnimationUpdate();

}

void TutorialManager::Render()
{
	//		�I�u�W�F�N�g�}�l�[�W���[�̕`�揈��
	//m_objectManager->Render(m_player->GetCameraInformation()->GetViewVelocity(),
	//	m_player->GetInformation()->GetPlayerHeight(),
	//	);

	//		���f���̕`��
	//m_player->ModelRender();

	//		�f�o�b�N�`��
	m_player->DebugRender();
}

void TutorialManager::Finalize()
{
}

void TutorialManager::Generation()
{
	//		�Q�[���}�l�[�W���[�𐶐�����
	m_gameManager = std::make_unique<GameManager>();

	//		�v���C���[�𐶐�����
	m_player = std::make_unique<Player>(m_gameManager.get());

	//		�J�����}�l�[�W���[�𐶐�����
	m_cameraManager = std::make_unique<PlayerCameraManager>(m_gameManager.get());

	//		�I�u�W�F�N�g�}�l�[�W���[
	m_objectManager = std::make_unique<ObjectManager>(m_gameManager.get());

	//		�����蔻��}�l�[�W���[�̐���
	m_collitionManager = std::make_unique<CollitionManager>(m_gameManager.get());

	//		�`���[�g���A���̏��𐶐�����
	m_information = std::make_unique<TutorialInformation>();

	//		�`���[�g���A���̏��̏�����
	m_information->Initialize(m_player.get());
}
