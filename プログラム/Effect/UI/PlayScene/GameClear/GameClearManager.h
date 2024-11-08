/*
* @file		GameOverManager.h
* @brief	�Q�[���I�[�o�[�}�l�[�W���[
* @author	Morita
* @date		2024/05/23
*/

#pragma once

#include "Game/PlayScene/GameManager/GameManager.h"

#include "../UIManager.h"

#include "Library/Shader/UIRenderManager.h"

class GameClearManager
{
public:
	//		�R���X�g���N�^
	GameClearManager(GameManager* gameManager, UIManager* uiManager);

	//		�f�X�g���N�^
	~GameClearManager();

	//		����������
	void Initialize();

	//		�X�V����
	void Update();

	//		�`�揈��
	void Render();

	//		�I������
	void Finalize();

public:

	//		�R���X�g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;
		DirectX::SimpleMath::Matrix  rotationMatrix;
		DirectX::SimpleMath::Vector4 time;
	};

private:

	//		UI�}�l�[�W���[�̃C���X�^���X�̃|�C���^
	UIManager* m_uiManager;

	//		�Q�[���}�l�[�W���[�̃C���X�^���X�̃|�C���^
	GameManager* m_gameManager;

	//		���b�Z�[�W�̃V�F�[�_�[�`��
	std::unique_ptr<UIRenderManager> m_messageShader;

	ConstBuffer buffer;

	//		�o�ߎ���
	float m_elapsedTime;

	//		�X�P�[��
	float m_scale;

	//		�ړ���
	float m_move;
};