/*
* @file		TutorialScene.cpp
* @brief	�^�C�g���V�[��
* @author	Morita
* @date		2024/09/17
*/

#include "pch.h"

#include "TutorialScene.h"

TutorialScene::TutorialScene(SceneManager* sceneManager)
{
	//		�`���[�g���A���}�l�[�W���̐���
	m_tutorialManager = std::make_unique<TutorialManager>(sceneManager);
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Initialize()
{
	//		�`���[�g���A���}�l�[�W���̏���������
	m_tutorialManager->Initialize();
}

void TutorialScene::Update()
{
	//		�`���[�g���A���}�l�[�W���[�̍X�V����
	m_tutorialManager->Update();
}

void TutorialScene::Render()
{
	//		�`���[�g���A���}�l�[�W���[�̕`�揈��
	m_tutorialManager->Render();
}

void TutorialScene::Finalize()
{
	//		�I������
	m_tutorialManager->Finalize();
}
