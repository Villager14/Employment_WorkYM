/*
* @file		PlayerStartCamera.h
* @brief	�v���C���[�X�^�[�g�J����
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerStartCamera : public IPlayerCamera
{
public:

	//		�R���X�g���N�^
	PlayerStartCamera(PlayerCameraManager* playerCameraManager);
	//		�f�X�g���N�^
	~PlayerStartCamera();

	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	void Finalize() override;

private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;

	//		����
	float m_time;

	//		�����`��
	bool m_firstViewJudgement;
};
