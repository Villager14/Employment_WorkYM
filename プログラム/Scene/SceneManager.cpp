/*
* @file		SceneManager.cpp
* @brief	�V�[���}�l�[�W���[
* @author	Morita
* @date		2024/03/30
*/

#include "pch.h"

#include "SceneManager.h"

SceneManager::SceneManager()
	:
	m_scene{},
	m_deathCount(0),
	m_clearTime(0),
	m_maxTime(0),
	m_sceneType{},
	m_endJudgement(false)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	//		���j���[�}�l�[�W���[�̐���
	m_menuManager = std::make_unique<MenuManager>(this);

	//		���j���[�}�l�[�W���[�̏�����
	m_menuManager->Initialize();

	//		�V�[�����쐬����
	m_sceneInformation.insert({ SceneType::Title, std::make_unique<TitleScene>(this) });
	m_sceneInformation.insert({ SceneType::Play, std::make_unique<PlayScene>(this) });
	m_sceneInformation.insert({ SceneType::Result, std::make_unique<ResultScene>(this) });
	m_sceneInformation.insert({ SceneType::Tutorial, std::make_unique<TutorialScene>(this) });

	//		�����̃V�[���^�C�v��ݒ肷��
	m_sceneType = SceneType::Title;

	//		�V�[����ݒ肷��
	m_scene = m_sceneInformation[m_sceneType].get();

	//		�V�[��������������
	m_scene->Initialize();
}

void SceneManager::Update()
{
	if (m_endJudgement)
	{
		Finalize();

		return;
	}

	//		�V�[���̍X�V����
	m_scene->Update();

	//		���j���[�}�l�[�W���[�̍X�V
	m_menuManager->Update();
}

void SceneManager::Render()
{
	if (m_endJudgement) return;

	//		�V�[���̕`�揈��
	m_scene->Render();

	//		���j���[�}�l�[�W���[�̕`��
	m_menuManager->Render();
}

void SceneManager::Finalize()
{
	//		���݂̏�Ԃ̏I������������
	m_scene->Finalize();

	m_sceneInformation.clear();
}

void SceneManager::ChangeScene(SceneType type)
{
	//		�����V�[���̏ꍇ���������Ȃ�
	if (m_sceneType == type) return;

	//		���݂̏�Ԃ̏I������������
	m_scene->Finalize();

	//		��Ԃ�؂�ւ���
	m_sceneType = type;

	m_scene = m_sceneInformation[m_sceneType].get();

	//		�V������Ԃ̏���������������
	m_scene->Initialize();
}
