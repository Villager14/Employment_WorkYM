/*
* @file		GameOverManager.h
* @brief	�Q�[���I�[�o�[�}�l�[�W���[
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "../UIManager.h"

class GameOverManager
{
public:
	//		�R���X�g���N�^
	GameOverManager(GameManager* gameManager, UIManager* uiManager);

	//		�f�X�g���N�^
	~GameOverManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

private:

	//		�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	GameManager* m_gameManager;

	//		UI�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�o�ߎ���
	float m_elapsedTime;
};