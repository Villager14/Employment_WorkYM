/*
* @file		GameOverManager.cpp
* @brief	�Q�[���I�[�o�[�}�l�[�W���[
* @author	Morita
* @date		2024/05/23
*/

#include "pch.h"

#include "GameOverManager.h"


GameOverManager::GameOverManager(GameManager* gameManager, UIManager* uiManager)
	:
	m_gameManager(gameManager),
	m_elapsedTime(0.0f),
	m_uiManager(uiManager)
{
}

GameOverManager::~GameOverManager()
{
}

void GameOverManager::Initialize()
{
}

void GameOverManager::Update()
{
	//		�Q�[���I�[�o�[��Ԃł͂Ȃ��Ȃ珈�������Ȃ�
	if (!m_gameManager->FlagJudgement(GameManager::DeathJudgement))
	{
		m_elapsedTime = 0.0f;

		return;
	}

	//		�o�ߎ���
	m_elapsedTime += LibrarySingleton::GetInstance()->GetElpsedTime();
}

void GameOverManager::Render()
{
	//		�^�C�����~�b�g
	if (m_gameManager->FlagJudgement(GameManager::TimeLimitJudgement))
	{
		m_uiManager->GetStandardShader()->Render(UIManager::UIType::GameOver);

		m_uiManager->GetStandardShader()->Render(UIManager::UIType::NextInduction);

		return;
	}

	//		�Q�[���I�[�o�[��Ԃł͂Ȃ��Ȃ珈�������Ȃ�
	if (!m_gameManager->FlagJudgement(GameManager::DeathJudgement)) return;
	
	if (m_elapsedTime < 3.0f)
	{
		m_uiManager->GetStandardShader()->Render(UIManager::UIType::GameOver);
	}
	else
	{
		m_uiManager->GetStandardShader()->Render(UIManager::UIType::GameOverContinue);
		m_uiManager->GetStandardShader()->Render(UIManager::UIType::NextInduction);
	}
}

void GameOverManager::Finalize()
{
}
