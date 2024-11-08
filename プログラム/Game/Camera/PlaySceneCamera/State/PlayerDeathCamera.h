/*
* @file		PlayerDeathCamera.h
* @brief	�v���C���[�̎��S�J����
* @author	Morita
* @date		2024/05/22
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerDeathCamera : public IPlayerCamera
{
public:

	//		�R���X�g���N�^
	PlayerDeathCamera(PlayerCameraManager* playerCameraManager);
	//		�f�X�g���N�^
	~PlayerDeathCamera();
	//		����������
	void Initialize() override;

	//		�X�V����
	void Update() override;

	void Finalize() override;

private:

	//		�J�����}�l�[�W���[�̃C���X�^���X�̃|�C���^
	PlayerCameraManager* m_playerCameraManager;
};
