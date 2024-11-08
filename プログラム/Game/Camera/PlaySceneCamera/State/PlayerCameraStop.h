/*
* @file		PlayerCameraStop.h
* @brief	�v���C���[�����Ȃ��̃J����
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerCameraStop : public IPlayerCamera
{
public:

	//		�R���X�g���N�^
	PlayerCameraStop(PlayerCameraManager* playerCameraManager);
	//		�f�X�g���N�^
	~PlayerCameraStop();
	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	void Finalize() override;

private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;
};
